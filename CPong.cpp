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
	line(_canvas, Point(1300/2, 0), Point(1300 / 2, 600), Scalar(255,255,255), LINE_THICKNESS, LINE_AA);
	
}

CPong::~CPong()
{
}

void CPong::gpio() 
{
	cc.ensure_connected();

	if (!cc.is_connected())
		return;

	cc.get_analog(_joystick, _accel);
}


void CPong::update()
{
	if (!cc.is_connected())
		return;
	if (_last_state_SW1 == 1 && _state_SW1 == 0)
	{
		_last_state_SW1 = _state_SW1;
	}


}


void CPong::draw()
{
	if (!cc.is_connected())
		return;

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
		_canvas.setTo(Scalar(0, 0, 0));
		_prev_point = Point(-1, -1);
	}

	if (cvui::button(_canvas, UI_BAR_X + 120, UI_BAR_Y + 200, 50, 30, "Exit"))
	{
		request_quit();
		return;
	}

	cvui::update();
	imshow("Pong", _canvas);

}
