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
#define JOYY_CHANNEL 4
#define JOYX_CHANNEL 11
#define SW1_CHANNEL 33
#define	SERVO_CHANNEL 0

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
	string _active_port;


	bool handshake_ok();

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
	 * @param comport COM port number to open 
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
	 * @param x Reference variable ADC joystick x
	 * @param y Reference variable ADC Joystick y
	 * @return true if succeeded.
	 */
	bool get_analog(int &x, int &y);

	/**
	 * @brief Reads and debounces a digital button input.
	 *
	 * Reads a digital input channel and applies software debouncing
	 * using a 1-second timeout to prevent false triggering.
	 *
	 * @param dig_input Reference variable to store the button state.
	 * @returns true if succeeded.
	 */
	bool get_button(int &dig_input);

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

	bool is_connected(void);

	void ensure_connected();

};


