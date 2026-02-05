#pragma once

#include <string>
#include <windows.h>

typedef std::basic_string<TCHAR> tstring;

/** Serial.h
 *
 * A very simple serial port control class that does NOT require MFC/AFX.
 *
 * License: This source code can be used and/or modified without restrictions.
 * It is provided as is and the author disclaims all warranties, expressed
 * or implied, including, without limitation, the warranties of
 * merchantability and of fitness for any purpose. The user must assume the
 * entire risk of using the Software.
 *
 * @author Hans de Ruiter
 *
 * @version 0.1 -- 28 October 2008
 */
class Serial
{
private:
	HANDLE commHandle;

public:
	Serial();

	virtual ~Serial();

	/**
	 * @brief Opens and configures a serial communication port.
	 *
	 * Attempts to establish a connection to the specified COM port using
	 * the provided baud rate and default serial parameters (8 data bits,
	 * no parity, 1 stop bit).
	 *
	 * @param commPortName Name of the COM port (e.g., "COM5").
	 * @param bitRate Communication baud rate. Default is 115200.
	 *
	 * @return bool True if the port was successfully opened and configured,
	 *              false otherwise.
	 */
	bool open (std::string commPortName, int bitRate = 115200);

	/**
	 * @brief Closes the currently open serial port.
	 *
	 * Safely releases the operating system handle associated with the
	 * serial port. If the port is not open, the function does nothing.
	 */
	void close();

	/**
	 * @brief Checks whether the serial port is currently open.
	 *
	 * Determines if a valid communication handle exists for the port.
	 *
	 * @return bool True if the serial port is open and ready for use,
	 *              false otherwise.
	 */
	bool is_open();

	/** Writes a string of bytes to the serial port.
	 *
	 * @param buffer pointer to the buffer containing the bytes
	 * @param buffLen the number of bytes in the buffer
	 *
	 * @return int the number of bytes written
	 */
	int write(const char *buffer, int buffLen);

	/** Reads a string of bytes from the serial port.
	 *
	 * @param buffer pointer to the buffer to be written to
	 * @param buffLen the size of the buffer
	 *
	 * @return int the number of bytes read
	 */
	int read(char *buffer, int buffLen);

	/**
	 * @brief Clears the serial port receive buffer.
	 *
	 * Reads and discards any remaining data currently waiting in the
	 * serial input buffer to ensure future reads start with fresh data.
	 */
	void flush();
};
