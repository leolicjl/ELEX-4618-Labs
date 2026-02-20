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
	int _last_state_SW1 = 1; ///<stores last button 1 state
	int _p1_score = 0; ///<stores player 1 score
	int _comp_score = 0; ///<stores computer score
	char _buffer[64]; ///< buffer space for fps

	double _ball_radius = 15.0; ///<ball radius
	double _ball_speed = 250.0f; ///<ball speed
	Point _ball = Point(1300/2, 600/2); ///<ball position
	float _ball_invert_x = -1; ///<stores sign of x direction of ball
	float _ball_invert_y = -1; ///<stores sign of y direction of ball

	Point _l_paddle_tl = Point(0, 250); ///<top left position of left paddle
	Point _l_paddle_br = Point(20, 350); ///<bottom right position of left paddle
	Point _r_paddle_tl = Point(1280, 250); ///<top left position of right paddle
	Point _r_paddle_br = Point(1300, 350); ///<bottom right position of right paddle
	float _r_paddle_y = 250.0f; ///<stores y value of paddle based on joystick position

public:

	/**
	 * @brief Represents the current state of the game.
	 */
	enum GameState { 
		PLAYING, ///< Game is currently running
		GAME_OVER ///< Game is in end state
	};

	/**
	 * @brief Stores the current game state.
	 */
	GameState _state = PLAYING;

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
	
	/**
	 * @brief resets UI to starting positions
	 *
	 * resets score, paddle positions, ball size and positions
	 *
	 * @param none
	 * @return none
	 */
	void reset_ui(); 


};

