/*
Filename: CSpaceInvadersGame.h
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description: header file for CSpaceInvadersGame.cpp
*/
#pragma once
#include "CBase4618.h"
#include "CInvader.h"
#include "CShip.h"
#include "CMissle.h"
#include <random>

/**
*
* @brief CSpaceInvadersGame class overrides CBase4618
*
* @author Leo Li A01412091
*/
class CSpaceInvadersGame : public CBase4618
{
private:
	CShip cs; ///<object of CShip
	CInvader ci; ///< object of CInvader
	vector<CInvader> _invaders_vec; ///< vector filled with invaders
	vector<CMissle> _missles_vec; ///< vector filled with ship missiles
	vector<CMissle> _enemy_missles_vec; ///< vector filled with ship
	int _state_SW1 = 0; ///< stores current button 1 state
	int _state_SW2 = 0; ///< stores current button 2 state
	int _last_state_SW1 = 1; ///<stores last button 1 state
	int _last_state_SW2 = 1; ///<stores last button 2 state
	bool _fire_flag = false; ///<stores flag if fire button pressed
	bool _reset_flag = false; ///<stores flag if reset button pressed
	Point _joystick; ///< stores coordinates of joystick
	Point2f _joy_percent; ///<stores coordinates of joystik in percentage
	Point _accel; ///<accelerometer not used; placeholder
	int _score = 0; ///< stores game score
	int _ship_lives = 3; ///< stores ships lives, initialized as 3
	bool _game_over = false; ///< stores game state
	float _invader_speed = 60.0f; ///< stores invader velocity
	int _invader_dir = 1; ///< stores invader x direction
	std::chrono::steady_clock::time_point _last_enemy_fire; ///< stores last enemy fire time
	float _enemy_fire_cooldown = 0.8f; ///< cooldown for enemy missle fire

	static const int INV_ROWS = 3;
	bool _row_frame[INV_ROWS] = { false,false,false };
	std::chrono::steady_clock::time_point _row_last_toggle[INV_ROWS];

public:

	/**
	 * @brief Default constructor.
	 *
	 * @param canvas size 
	 * 
	 */
	CSpaceInvadersGame(Size& canvas_size);

	/**
	 * @brief Default destructor.
	 *
	 */
	~CSpaceInvadersGame();

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
	 * @brief Initializes the invaders as individual objects
	 * and push into the invaders vector
	 *
	 * overrides to virtual in CBase4618
	 *
	 * @param none
	 * @return none
	 */
	void init();
};

