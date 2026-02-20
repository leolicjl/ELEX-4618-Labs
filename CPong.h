/*
Filename: CPong.h
Date: February 18, 2026
Author: Leo Li
Set: 3T
Description: Header file for CPong.cpp
*/
#pragma once
#define WINDOW_WIDTH 200
#define WINDOW_HEIGHT 250
#define UI_BAR_X 30 
#define UI_BAR_Y 10
#define LINE_THICKNESS 1
#include "CBase4618.h"

class CPong : public CBase4618
{
private:
	Point _joystick; ///< stores coordinates of joystick
	Point _lcd; ///<stores coordinates of lcd
	Point _accel; ///<accelerometer not used; placeholder
	Point _prev_point = Point(-1, -1); ///< stores previous point
	int _state_SW1 = 0; ///< stores current button 1 state
	int _last_state_SW1 = 1; ///< stores last button 1 state
	int _p1_score = 0;
	int _comp_score = 0;
	char _buffer[64];

	double _ball_radius = 50.0;
	double _ball_speed = 200.0;

public:

	/**
	* @brief Default constructor
	* @param canvas_size reference variable
	*/
	CPong(Size& canvas_size);

	/**
	* @brief Destructor
	*
	* Cleans up the CSketch object
	*/
	~CPong();

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

