/*
Filename: CBase4618.h
Date: February 5, 2026
Author: Leo Li
Set: 3T
Description: Header file for CBase4618.cpp
*/
#pragma once
#define TARGET_FPS 30
#include "CControl.h"
#include "cvui.h"
#include <chrono>
#include <thread>


using namespace cv;

/**
* @class CBase4618
* @brief Provides base functions to be used for any game
*
* Includes a gpio, update, and draw function
*
*
* @author Leo Li A01412091
*/
class CBase4618 {

protected:
	CControl cc; ///< CControl class object
	Mat _canvas; ///< Mat object
	bool _quit = false; ///< stores game quit
	double _fps = 0.0; ///<stores fps
	double _dt = 0; ///<change in time it took to run
	const chrono::milliseconds frame_duration = chrono::milliseconds(1000 / TARGET_FPS); ///< fixed frame rate cal
	double _fps_array[10] = {}; ///stores 10 fps values for averaging

	/**
	 * @brief Function if user wants to quit
	 *
	 * @param _quit initialized as true
	 * @return none
	 */
	void request_quit() { _quit = true; }

public:
	/**
	* @brief Default constructor
	*/
	CBase4618();

	/**
	* @brief Destructor
	*
	* Cleans up CBase4618 object
	*/
	~CBase4618();

	/**
	 * @brief Performs read and write processes to interact with the microcontroller
	 *
	 *
	 * @param none
	 * @return none
	 */
	virtual void gpio() = 0;

	/**
	 * @brief Updates the state of the screen before it gets drawn
	 *
	 *
	 * @param none
	 * @return none
	 */
	virtual void update() = 0;

	/**
	 * @brief Performs all drawings on Mat image and displays the image on the scree.
	 *
	 *
	 * @param none
	 * @return none
	 */
	virtual void draw() = 0;

	/**
	 * @brief quits if q is pressed
	 *
	 * includes timing and frame locking
	 *
	 * @param user_quit = 'q' , string window_name
	 * @return true
	 */
	bool run(char user_quit = 'q', string window_name = "");


};

