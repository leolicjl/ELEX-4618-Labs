/*
Filename: CSpaceInvadersGame.cpp
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description: 
*/
#include "stdafx.h"
#include "CSpaceInvadersGame.h"

CSpaceInvadersGame::CSpaceInvadersGame(Size& canvas_size)
{
	cc.init_com();
	_canvas = Mat(canvas_size, CV_8UC3, Scalar(0, 0, 0));
	cvui::init("Space Invaders");
}

CSpaceInvadersGame::~CSpaceInvadersGame()
{
}
void CSpaceInvadersGame::gpio()
{
	cc.ensure_connected();

	if (!cc.is_connected())
		return;


	cc.get_button_SW1(_state_SW1, SW1_CHANNEL);

	if (_last_state_SW1 == 1 && _state_SW1 == 0)
	{
		_fire_flag = true;
		cout << "Fire button pressed" << endl;
	}
	_last_state_SW1 = _state_SW1;

	cc.get_button_SW2(_state_SW2, SW2_CHANNEL);

	if (_last_state_SW2 == 1 && _state_SW2 == 0)
	{
		_reset_flag = true;
		cout << "Reset button pressed" << endl;
	}

	_last_state_SW2 = _state_SW2;

	cc.get_analog(_joystick, _accel);
	_joy_percent.x = (_joystick.x / 4095.0f) * 100.0f;
	_joy_percent.y = (_joystick.y / 4095.0f) * 100.0f;
}

void CSpaceInvadersGame::update()
{
	if (_fire_flag) {
		// create missile
		_fire_flag = false;  // reset flag after handling
	}

	if (_reset_flag) {
		// reset game
		_reset_flag = false;
	}

	cout << fixed << setprecision(2) << "X Pos: " << _joy_percent.x << "Y Pos: " << _joy_percent.y << endl;

}

void CSpaceInvadersGame::draw()
{

}

void CSpaceInvadersGame::init()
{
	_invaders_vec.clear();
	
	int rows = 3; 
	int cols = 10;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			CInvader inv;

			_invaders_vec.push_back(inv);
		}
	}

}