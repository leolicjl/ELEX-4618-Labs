/*
Filename: CPong.cpp
Date: February 18, 2026
Author: Leo Li
Set: 3T
Description: Pong lab 5
*/
#include "stdafx.h"
#include "CPong.h"

CPong::CPong(Size& canvas_size)
{
	cc.init_com();
	_canvas = Mat(canvas_size, CV_8UC3, Scalar(0, 0, 0));
	cvui::init("Pong");
	reset_ui();
}

CPong::~CPong()
{
}

void CPong::gpio() 
{
	cc.ensure_connected();

	if (!cc.is_connected())
		return;

	cc.get_button_SW1(_state_SW1, SW1_CHANNEL);

}


void CPong::update()
{
	if (!cc.is_connected())
		return;

	if (_p1_score == 5 || _comp_score == 5)
	{
		_state = GAME_OVER;
	}

	if (_state == GAME_OVER)
		return;

	cc.get_analog(_joystick, _accel);

	float input = (4095.0f - _joystick.y) / 4095.0f;

	_r_paddle_y = input * (_canvas.rows - 100.0f);
	_r_paddle_y = std::max(0.0f, _r_paddle_y);
	_r_paddle_y = std::min(_canvas.rows - 100.0f, _r_paddle_y);

	_r_paddle_tl = Point(_canvas.cols - 20, _r_paddle_y);
	_r_paddle_br = Point(_canvas.cols, _r_paddle_y + 100);

	_ball.x += _ball_invert_x * _ball_speed * _dt;
	_ball.y += _ball_invert_y * _ball_speed * _dt;

	if (_ball.y - _ball_radius < 0) {
		_ball.y = _ball_radius;
		_ball_invert_y *= -1.0f;
	}
	if (_ball.y + _ball_radius > _canvas.rows) {
		_ball.y = _canvas.rows - _ball_radius;
		_ball_invert_y *= -1.0f;
	}

	if (_ball.x < 0 )
	{
		_ball = Point(_canvas.cols / 2, _canvas.rows / 2);
		_p1_score++;
	}
	
	if (_ball.x > _canvas.cols)
	{
		_ball = Point(_canvas.cols / 2, _canvas.rows / 2);
		_comp_score++;

	}

	if (_last_state_SW1 == 1 && _state_SW1 == 0)
	{
		reset_ui();
	}


	_last_state_SW1 = _state_SW1;


}


void CPong::draw()
{
	_canvas.setTo(cv::Scalar(0, 0, 0));
	if (!cc.is_connected())
		return;

	if (_state == GAME_OVER)
	{
		putText(_canvas, "GAME OVER", Point(_canvas.cols / 2 - 150, 100), FONT_HERSHEY_SIMPLEX, 2.0, Scalar(255, 255, 255), 4);
	}
	cout << "cleared" << endl;
	line(_canvas, Point(_canvas.cols / 2, 0), Point(_canvas.cols / 2, 600), Scalar(255, 255, 255), LINE_THICKNESS, LINE_AA);

	sprintf(_buffer, "Pong (FPS = %.6f)", _fps);
	cvui::window(_canvas, UI_BAR_X, UI_BAR_Y, WINDOW_WIDTH, WINDOW_HEIGHT, _buffer);
	cvui::printf(_canvas, UI_BAR_X + 5, UI_BAR_Y + 25, "Player = %d", _p1_score);
	cvui::printf(_canvas, UI_BAR_X + 100, UI_BAR_Y + 25, "Computer = %d", _comp_score);
	cvui::text(_canvas, UI_BAR_X + 80, UI_BAR_Y + 50, "Radius");
	cvui::trackbar(_canvas, UI_BAR_X + 5, UI_BAR_Y + 50, 180, &_ball_radius, (double)5.0, (double)100.0);
	cvui::text(_canvas, UI_BAR_X + 80, UI_BAR_Y + 125, "Speed");
	cvui::trackbar(_canvas, UI_BAR_X + 5, UI_BAR_Y + 125, 180, &_ball_speed, (double)100.0, (double)400.0);

	if (cvui::button(_canvas, UI_BAR_X + 30, UI_BAR_Y + 200, 50, 30, "Reset"))
	{
		reset_ui();
	}

	if (cvui::button(_canvas, UI_BAR_X + 120, UI_BAR_Y + 200, 50, 30, "Exit"))
	{
		request_quit();
		return;
	}

	circle(_canvas, _ball, _ball_radius, Scalar(255, 255, 255), -1);
	rectangle(_canvas, _l_paddle_tl, _l_paddle_br, Scalar(255, 255, 255), -1);
	rectangle(_canvas, _r_paddle_tl, _r_paddle_br, Scalar(255, 255, 255), -1);


	cvui::update();
	imshow("Pong", _canvas);

}

void CPong::reset_ui()
{
	_p1_score = 0;
	_comp_score = 0;
	_ball_radius = 15.0;
	_ball_speed = 250.0;
	_ball = Point(1300 / 2, 600 / 2);
	_l_paddle_tl = Point(0, 250);
	_l_paddle_br = Point(20, 350);
	_r_paddle_tl = Point(1280, 250);
	_r_paddle_br = Point(1300, 350);
	_state = PLAYING;

	_canvas.setTo(cv::Scalar(0, 0, 0));
	line(_canvas, Point(1300 / 2, 0), Point(1300 / 2, 600), Scalar(255, 255, 255), LINE_THICKNESS, LINE_AA);
	circle(_canvas, _ball, _ball_radius, Scalar(255, 255, 255), -1);
	rectangle(_canvas, _l_paddle_tl, _l_paddle_br, Scalar(255, 255, 255), -1);
	rectangle(_canvas, _r_paddle_tl, _r_paddle_br, Scalar(255, 255, 255), -1);
}
