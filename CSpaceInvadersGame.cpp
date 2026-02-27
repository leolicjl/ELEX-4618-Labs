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
	init();
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
	if (_reset_flag) 
	{
		init();
		_reset_flag = false;
	}
	cout << fixed << setprecision(2) << "X Pos: " << _joy_percent.x << "Y Pos: " << _joy_percent.y << endl;

	float x_pixel = (_joy_percent.x / 100.0f) * _canvas.cols;
	float y_fixed = _canvas.rows - 50.0f;
	x_pixel = max(0.0f, x_pixel);
	x_pixel = min(_canvas.cols - 40.0f, x_pixel);
	cs.set_pos(cv::Point2f(x_pixel, y_fixed));

	if (_fire_flag) 
	{
		Point2f ship_pos = cs.get_pos();
		Point2f missle_pos(ship_pos.x + 10, ship_pos.y - 15);
		_missles_vec.emplace_back(missle_pos, Point2f(0, -250));
		_fire_flag = false;
	}

	for (auto& m : _missles_vec) m.move();

	for (auto& m : _missles_vec)
	{
		if (m.collide_wall(_canvas.size()))
			m.set_lives(0);
	}
	for (auto& m : _missles_vec)
	{
		if (m.get_lives() <= 0) continue;

		for (auto& inv : _invaders_vec)
		{
			if (inv.get_lives() <= 0) continue;

			if (m.collide(inv))
			{
				m.set_lives(0);
				inv.set_lives(0);
				_score += 100;
				break;
			}
		}
	}

	_missles_vec.erase(remove_if(_missles_vec.begin(), _missles_vec.end(),
		[](CMissle& m) { return m.get_lives() <= 0; }), _missles_vec.end());

	_invaders_vec.erase(remove_if(_invaders_vec.begin(), _invaders_vec.end(),
		[](CInvader& i) { return i.get_lives() <= 0; }), _invaders_vec.end());

	for (auto& inv : _invaders_vec)
	{
		inv.set_velocity(cv::Point2f(_invader_speed * _invader_dir, 0));
		inv.move();
	}

	bool hit_edge = false;
	for (auto& inv : _invaders_vec)
	{
		if (inv.collide_wall(_canvas.size()))
		{
			hit_edge = true;
			break;
		}
	}

	if (hit_edge)
	{
		_invader_dir *= -1;
	}

	if (cs.get_lives() <= 0)
		_game_over = true;
}

void CSpaceInvadersGame::draw()
{
	_canvas.setTo(Scalar(0,0,0));
	cs.draw(_canvas);
	for (int i = 0; i < _invaders_vec.size(); i++)
	{
		_invaders_vec[i].draw(_canvas);
	}

	for (int m = 0; m < _missles_vec.size(); m++)
	{
		_missles_vec[m].draw(_canvas);
	}

	cvui::text(_canvas, 10, 10, "SCORE: " + to_string(_score));
	cvui::text(_canvas, 150, 10, "LIVES: " + to_string(cs.get_lives()));
	cvui::text(_canvas, 260, 10, "MISSILES: " + to_string(_missles_vec.size()));

	if (_game_over)
		cvui::text(_canvas, 120, _canvas.rows / 2, "YOU LOSE");

	cvui::update();
	imshow("Space Invaders", _canvas);
}

void CSpaceInvadersGame::init()
{
	_score = 0;
	_ship_lives = 3;
	_invaders_vec.clear();
	_missles_vec.clear();
	cs.set_lives(3);
	cs.set_pos(Point2f(_canvas.cols / 2.0f, _canvas.rows - 50.0f));
	
	int rows = 3; 
	int cols = 10;

	float gap_x = 25, gap_y = 25;
	float start_x = _canvas.cols / 2 - (gap_x * 5);
	float start_y = 100;

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			Point2f pos(start_x + c * gap_x, start_y + r * gap_y);
			_invaders_vec.push_back(CInvader(pos));
		}
	}

}
