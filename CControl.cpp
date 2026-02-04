/*
Filename: CControl.cpp
Date: January 29, 2026
Author: Leo Li
Set: 3T
Description: Function definitions for CControl.h  
Notes: 11 for joystick x, 4 for joystick y, 0-3 for servo, 5 6 7 accelerometer,
33 for SW1, 32 for SW2 (both active low)
*/

#include "stdafx.h"
#include "CControl.h"

#include <windows.h>

// --------------------------
// Helpers (local to this .cpp)
// --------------------------
static std::vector<std::string> list_candidate_ports()
{
    std::vector<std::string> ports;
    ports.reserve(256);
    for (int i = 1; i <= 256; ++i)
        ports.push_back("COM" + std::to_string(i));
    return ports;
}

// Win32 needs "\\\\.\\COM10" format for COM10+
static std::string normalize_windows_port_name(const std::string& port)
{
    if (port.rfind("COM", 0) == 0)
    {
        try
        {
            int n = std::stoi(port.substr(3));
            if (n >= 10)
                return "\\\\.\\" + port;
        }
        catch (...) {}
    }
    return port;
}

CControl::CControl()
{
}

CControl::~CControl()
{
    if (_com.is_open())
        _com.close();
}

bool CControl::is_connected()
{
    return _com.is_open();
}

// Handshake: uses an existing "safe" GET that should always respond on your board.
// If your board resets on open, we allow a short delay before calling this.
bool CControl::handshake_ok()
{
    int tmp = 0;

    // Use a read that is unlikely to change anything.
    // DIGITAL SW1 is active-low, but reading it is safe.
    // You can swap this to JOYX_CHANNEL analog read if you prefer.
    if (!get_data(DIGITAL, SW1_CHANNEL, tmp))
        return false;

    return true;
}

// Try open + handshake on a single port.
// Returns true if this is the microcontroller.
bool CControl::try_connect_on_port(const std::string& portName)
{
    std::string winPort = normalize_windows_port_name(portName);

    if (!_com.open(winPort.c_str()))
        return false;

    // Many boards reset when the port is opened; give it a moment.
    Sleep(250);

    // Clear junk from boot messages
    _com.flush();

    if (!handshake_ok())
    {
        _com.close();
        return false;
    }

    _active_port = portName;
    std::cout << "Connected on " << portName << std::endl;
    return true;
}

// Auto-detect the board by scanning all COM ports.
// This call will BLOCK until the device is found.
void CControl::init_com()
{
    // If already connected, keep it
    if (is_connected())
        return;

    while (true)
    {
        for (const auto& port : list_candidate_ports())
        {
            if (try_connect_on_port(port))
                return;
        }

        // Not found: wait then scan again
        Sleep(250);
    }
}

// Call this periodically while running.
// If disconnected, it will attempt to rescan and reconnect (non-blocking per call).
void CControl::ensure_connected()
{
    // If connected, validate connection with a quick handshake.
    if (is_connected())
    {
        if (handshake_ok())
            return;

        // If handshake failed, assume unplugged.
        std::cout << "Device disconnected. Rescanning..." << std::endl;
        _com.close();
        _active_port.clear();
    }

    // Not connected: try one scan pass
    for (const auto& port : list_candidate_ports())
    {
        if (try_connect_on_port(port))
            return;
    }
}

bool CControl::get_data(int type, int channel, int &result)
{
    if (!is_connected())
        return false;
    _com.flush();
    string tx_str = "G " + to_string(type) + " " + to_string(channel) + "\n";
    string rx_str;

    //// temporary storage
    char buff[2];

    // Send TX string
    if (!_com.write(tx_str.c_str(), tx_str.length()))
        return false;
    Sleep(10); // wait for ADC conversion, etc. May not be needed?

    rx_str = "";
    // start timeout count
    double start_time = cv::getTickCount();

    buff[0] = 0;
    // Read 1 byte and if an End Of Line then exit loop
// Timeout after 1 second, if debugging step by step this will cause you to exit the loop
    while (buff[0] != '\n' && (cv::getTickCount() - start_time) / cv::getTickFrequency() < 1.0)
    {
        if (_com.read(buff, 1) > 0)
        {
            rx_str = rx_str + buff[0];
        }
    }

    // If we timed out or got nothing, fail
    if (rx_str.empty() || rx_str.find('\n') == std::string::npos)
        return false;

    _last_channel = channel;
    result = stoi(rx_str.substr(6));
    //printf("\nRX: %s", rx_str.c_str());
    cv::waitKey(1);
    return true;
}

bool CControl::set_data(int type, int channel, int val)
{
    if (!is_connected())
        return false;
    _com.flush();
    string tx_str = "S " + to_string(type) + " " + to_string(channel) + " " + to_string(val) + "\n";
    if(!_com.write(tx_str.c_str(), tx_str.length()))
        return false;

    return true;
}

bool CControl::get_analog(int &x, int &y)
{
    if (!get_data(ANALOG, JOYX_CHANNEL, x))
        return false;
    _channel_x = _last_channel;
    if (!get_data(ANALOG, JOYY_CHANNEL, y))
        return false;
    _channel_y = _last_channel;
    return true;
}

bool CControl::get_button(int &dig_input)
{
    static int stable = 1;
    static int last_state = 1;
    static double last_time = 0;

    int state;
    if (!get_data(DIGITAL, SW1_CHANNEL, state))
        return false;

    double current_time = cv::getTickCount();

    if (state != last_state)
    {
        last_state = state;
        last_time = current_time;
    }

    if ((current_time - last_time) / cv::getTickFrequency() >= 0.01)
        stable = last_state;

    dig_input = stable;
    _channel_x = _last_channel;
    return true;
}
int CControl::get_last_channel(void)
{
    return _last_channel;
}
int CControl::get_channel_x(void)
{
    return _channel_x;
}
int CControl::get_channel_y(void)
{
    return _channel_y;
}




