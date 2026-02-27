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
	_last_enemy_fire = std::chrono::steady_clock::now();
	static const int INV_ROWS = 3;
	bool _row_frame[INV_ROWS] = { false,false,false };
	std::chrono::steady_clock::time_point _row_last_toggle[INV_ROWS];
	init();
}

CSpaceInvadersGame::~CSpaceInvadersGame()
{
}

void CSpaceInvadersGame::gpio()
{
	cc.ensure_connected();

	if (!cc.is_connected())
	{
		return;
	}
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
		_game_over = false;
		return;
	}
	if (_game_over)
		return;

	auto now = std::chrono::steady_clock::now();
	for (int r = 0; r < INV_ROWS; r++)
	{
		double dt = std::chrono::duration<double>(
			now - _row_last_toggle[r]).count();

		if (dt >= 0.30)
		{
			_row_frame[r] = !_row_frame[r];
			_row_last_toggle[r] = now;
		}
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
				_score += 10;
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

	// --- Enemy Random Shooting ---
	auto current = std::chrono::steady_clock::now();
	double dt_fire = std::chrono::duration<double>(current - _last_enemy_fire).count();

	if (dt_fire >= _enemy_fire_cooldown && !_invaders_vec.empty())
	{
		_last_enemy_fire = current;

		// Random number generator
		static std::mt19937 rng((unsigned)std::chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> pick(0, (int)_invaders_vec.size() - 1);

		int idx = pick(rng);
		Point2f inv_pos = _invaders_vec[idx].get_pos();

		// Spawn missile going DOWN
		Point2f missile_pos(inv_pos.x + 5, inv_pos.y + 15); // adjust to your sizes
		_enemy_missles_vec.emplace_back(missile_pos, Point2f(0, 200));
	}

	for (auto& m : _enemy_missles_vec)
		m.move();

	for (auto& m : _enemy_missles_vec)
	{
		if (m.collide_wall(_canvas.size()))
			m.set_lives(0);
	}

	_enemy_missles_vec.erase(
		remove_if(_enemy_missles_vec.begin(), _enemy_missles_vec.end(),
			[](CMissle& m) { return m.get_lives() <= 0; }),
		_enemy_missles_vec.end());

	for (auto& m : _enemy_missles_vec)
	{
		if (m.collide(cs))
		{
			m.set_lives(0);
			cs.hit();   // reduce ship life
			break;
		}
	}

	if (cs.get_lives() <= 0 || _invaders_vec.size() == 0)
		_game_over = true;
}

void CSpaceInvadersGame::draw()
{

	_canvas.setTo(Scalar(0,0,0));
	cs.draw(_canvas);
	for (auto& inv : _invaders_vec)
	{
		inv.draw(_canvas, _row_frame[inv.get_row()]);
	}

	for (int m = 0; m < _missles_vec.size(); m++)
	{
		_missles_vec[m].draw(_canvas);
	}

	for (auto& m : _enemy_missles_vec)
		m.draw(_canvas);


	cvui::text(_canvas, 10, 10, "SCORE: " + to_string(_score));
	cvui::text(_canvas, 150, 10, "LIVES: " + to_string(cs.get_lives()));
	cvui::text(_canvas, 260, 10, "MISSILES: " + (to_string(_missles_vec.size() + _enemy_missles_vec.size())));

	if (_game_over)
	{
		if (_invaders_vec.size() == 0)
			cvui::text(_canvas, 120, _canvas.rows / 2, "WIN");
			
		else 
			cvui::text(_canvas, 120, _canvas.rows / 2, "YOU LOSE");
	}	

	cvui::update();
	imshow("Space Invaders", _canvas);
}

void CSpaceInvadersGame::init()
{
	_score = 0;
	_ship_lives = 3;
	_invaders_vec.clear();
	_missles_vec.clear();
	_enemy_missles_vec.clear();
	cs.set_lives(3);
	cs.set_pos(Point2f(_canvas.cols / 2.0f, _canvas.rows - 50.0f));
	
	int rows = 3; 
	int cols = 10;

	float gap_x = 35, gap_y = 35;
	float start_x = _canvas.cols / 2 - (gap_x * 5);
	float start_y = 100;

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			Point2f pos(start_x + c * gap_x, start_y + r * gap_y);
			_invaders_vec.push_back(CInvader(pos, r));
		}
	}

}
