/*
Filename: CControl.h
Date: January 29, 2026
Author: Leo Li
Set: 3T
Description: Header file for CControl.cpp
*/
#pragma once
#include "Serial.h"
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <regex>
#include <fstream>
#define GREEN_LED 38
#define RED_LED 39
#define BLUE_LED 37
#define JOYY_CHANNEL 4
#define JOYX_CHANNEL 11
#define SW1_CHANNEL 33
#define SW2_CHANNEL 32
#define	SERVO_CHANNEL 0
#define ACCX_CHANNEL 7
#define ACCY_CHANNEL 6
#define ACCZ_CHANNEL 5
//Lab 4 defines
#define RATIO (250.0f) / (4095.0f) //conversion to amount of pixels on LCD

using namespace std;

/**
* @class CControl
* @brief PC-side interfacce for serial communication with the embedded system. 
* 
* Allows PC based system access to GPIO w/ analog,
* digital inputs and outputs, and servo controls.
* 
* 
* @author Leo Li A01412091
*/
class CControl {
private:
	Serial _com; ///<Serial communicaiton object
	int _last_channel; ///<stores last channel number from from get_data()
	int _channel_x; ///<analog channel of joystick x
	int _channel_y; ///<analog channel of joystick y
	string _active_port; ///<selected com port


	/**
	 * @brief Makes sure both PC and controller communicates with each other
	 *
	 * @param none
	 * @return true/false
	 */
	bool handshake_ok();

	/**
	 * @brief Try open + handshake on a single port
	 *
	 * @param portName Constant string reference variable
	 * @return true if this is the controller
	 */
	bool try_connect_on_port(const string& portName);

public:

	enum IOType{DIGITAL, ANALOG, SERVO}; ///< Digital = 0, analog = 1, servo = 2
	/**
	* @brief Default constructor
	*/
	CControl(); 
	/**
	* @brief Destructor
	* 
	* Cleans up the CControl object
	*/
	~CControl();

	/**
	 * @brief Initializes the serial communication port.
	 *
	 * Opens the specified COM port and prepares it for communication
	 * with the embedded system.
	 *
	 * @param none
	 * @return none
	 */
	void init_com();

	/**
	* @brief Sends a get command to the embedded system
	* 
	* Requests data from either GPIO, analog, or servo
	* 
	* @param type Data type (Digital,Analog, Servo)
	* @param channel Channel number to read from
	* @param result Reference variable where the returned value is stored
	* @return true if command succeeds, false if timeout
	* 
	*/
	bool get_data(int type, int channel, int &result);

	/**
	 * @brief Sends a set command to the embedded system.
	 *
	 * Sets the value of a specified digital output or servo channel
	 *
	 * @param type Data type (DIGITAL or SERVO).
	 * @param channel Channel number to write to.
	 * @param val Value to set.
	 * @return true if the command succeeded, false if a timeout occurred.
	 */
	bool set_data(int type, int channel, int val);

	/**
	 * @brief Reads an analog input and returns it as a normalized value.
	 *
	 * Calls get_data() internally and converts the 12-bit ADC result
	 * to a floating-point value between 0.0 and 1.0.
	 *
	 * @param joy Point reference variable for joystick
	 * @param accel Point reference variable for accelerometer
	 * @return true if succeeded.
	 */
	bool get_analog(cv::Point &joy, cv::Point &accel);

	/**
	 * @brief Reads and debounces a digital button input.
	 *
	 * Reads a digital input channel and applies software debouncing
	 * using a 1-second timeout to prevent false triggering.
	 *
	 * @param dig_input Reference variable to store the button state.
	 * #param button_num stores button channel number
	 * @returns true if succeeded.
	 */
	bool get_button_SW1(int &dig_input, int button_num);

	/**
	 * @brief Reads and debounces a digital button input.
	 *
	 * Reads a digital input channel and applies software debouncing
	 * using a 1-second timeout to prevent false triggering.
	 *
	 * @param dig_input Reference variable to store the button state.
	 * #param button_num stores button channel number
	 * @returns true if succeeded.
	 */
	bool get_button_SW2(int& dig_input, int button_num);

	/**
	* @brief Getter function for the last channel recorded.
	*
	* @param none
	* @return integer
	*/
	int get_last_channel(void);

	/**
	* @brief Getter function for the channel number of joystick x
	* 
	* @param none
	* @return integer
	*/
	int get_channel_x(void);

	/**
	* @brief Getter function for the channel number of joystick y
	*
	* @param none
	* @return integer
	*/
	int get_channel_y(void);

	/**
	* @brief Helper function to see if com port has been opened and connected. 
	*
	* @param none
	* @return true
	*/
	bool is_connected(void);

	/**
	* @brief Function to be periodically called to check com is still connected. 
	* 
	* If disconnected, it will attempt to re-scan and re-connect. 
	*
	* @param none
	* @return true
	*/
	void ensure_connected();

};


