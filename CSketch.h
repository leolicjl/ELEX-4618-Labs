/*
Filename: CSketch.h
Date: February 5, 2026
Author: Leo Li
Set: 3T
Description: Header file for CSketch.cpp
*/
#pragma once
#include "CBase4618.h"
#define WINDOW_SIZE 250
#define RATIO (250.0f) / (4095.0f)
#define LINE_THICKNESS 1
#define ACCEL_CENTERX 3712
#define ACCEL_CENTERY 2116
#define ACCEL_MIN_SHAKE 300

using namespace cv;

/**
* @class CSketch
* @brief Creates an etch-a-sketch game
*
* Allows the joystick to control the coordinates on the screen
* Button 1 to change the color, button 2 to clear the screen
*
*
* @author Leo Li A01412091
*/
class CSketch : public CBase4618
{
private:
	Point _joystick; ///< stores coordinates of joystick
	Point _lcd; ///<stores coordinates of lcd
	Point _accel; ///<stores coordinates of accelerometer
	int _state_SW1 = 0; ///< stores current button 1 state
	int _last_state_SW1 = 1; ///< stores last button 1 state
	int _state_SW2 = 0; ///< stores current button 2 state
	int _last_state_SW2 = 1; ///< stores last button 2 state 
	string _color_text = "BLUE"; ///<  stores name of color displayed on window
	Point _prev_point = Point(-1, -1); ///< stores previous point

	Scalar _colors[3] = { Scalar(255,0,0), Scalar(0,255,0),  Scalar(0,0,255) }; ///< array holding Blue, red, green
	
	int _color_index = 0; ///< index for the _colors list
	int _prev_color = 0; ///< stores previous color
	Scalar _current_color = _colors[_color_index]; ///< stores current color

	const float _center_x = 2060.0f; ///< defines joystick x at rest
	const float _center_y = 1995.0f; ///< defines joystick y at rest
public:

	/**
	* @brief Default constructor
	* @param canvas_size reference variable
	*/
	CSketch(Size &canvas_size);

	/**
	* @brief Destructor
	*
	* Cleans up the CSketch object
	*/
	~CSketch();
	
	/**
	 * @brief Initializes the gpio actions
	 *
	 * overrides to virtual in CBase4618
	 *
	 * @param none
	 * @return none
	 */
	void gpio() override;

	/**
	 * @brief Initializes the update actions
	 *
	 * overrides to virtual in CBase4618
	 *
	 * @param none
	 * @return none
	 */
	void update() override;

	/**
	 * @brief Initializes the draw actions
	 *
	 * overrides to virtual in CBase4618
	 *
	 * @param none
	 * @return none
	 */
	void draw() override;
};

