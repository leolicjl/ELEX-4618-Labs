/*
Filename: CSketch.cpp
Date: January 29, 2026
Author: Leo Li
Set: 3T
Description: 
*/

#include "stdafx.h"
#include "CSketch.h"



CSketch::CSketch()
{
	cc.init_com();
	_canvas = Mat(250, 250, CV_8UC3, Scalar(255,255,255));
	cvui::init("Etch-A-Sketch");

}
CSketch::~CSketch()
{
}

void CSketch::gpio()
{
	cc.ensure_connected();

	if (!cc.is_connected())
	{
		Sleep(50);
		return;
	}

	if (!cc.get_analog(_joystick_x, _joystick_y))
	{
		Sleep(1);
	}

	cc.get_button(_state);


}

void CSketch::update()
{
	if (!cc.is_connected())
		return;

	if (_last_state == 1 && _state == 0)
	{
		if (_color_index < 2)
			_color_index++;
		else
			_color_index = 0;

		_current_color = _colors[_color_index];
	}

	_last_state = _state;

	_lcd_x = RATIO * _joystick_x;
	_lcd_y = RATIO * _joystick_y;

}

void CSketch::draw()
{
	if (!cc.is_connected())
		return;

	Point _current_point(_lcd_x, _lcd_y);

	if (_prev_point.x == -1) {
		_prev_point = _current_point;
	}
	else {
		line(_canvas, _prev_point, _current_point, _current_color, LINE_THICKNESS, LINE_AA);
		_prev_point = _current_point;
	}

	if (cvui::button(_canvas, 20, 40, 200, 30, "Exit"))
	{
		request_quit();
		return;
	}
	cvui::text(_canvas, 12, 25, "Color = " + to_string(_color_index));
	cvui::update();
	imshow("Etch-A-Sketch", _canvas);

}
