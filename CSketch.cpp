/*
Filename: CSketch.cpp
Date: January 29, 2026
Author: Leo Li
Set: 3T
Description: 
*/

#include "stdafx.h"
#include "CSketch.h"



CSketch::CSketch(Size &canvas_size)
{
	cc.init_com();
	_canvas = Mat(canvas_size, CV_8UC3, Scalar(255,255,255));
	cvui::init("Etch-A-Sketch");
	cvui::text(_canvas, 12, 25, "Color = " + _color_text);
	cc.set_data(cc.DIGITAL, BLUE_LED, 1);
	Sleep(2);
	cc.set_data(cc.DIGITAL, GREEN_LED, 0);
	Sleep(2);
	cc.set_data(cc.DIGITAL, RED_LED, 0);

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

	cc.get_button_SW1(_state_SW1, SW1_CHANNEL);
	cc.get_button_SW2(_state_SW2, SW2_CHANNEL);


}

void CSketch::update()
{
	if (!cc.is_connected())
		return;


	if (_last_state_SW1 == 1 && _state_SW1 == 0)
	{

		if (_color_index < 2)
			_color_index++;
		else
			_color_index = 0;

		if (_color_index == 0)
		{
			_color_text = "BLUE";
			cc.set_data(cc.DIGITAL, BLUE_LED, 1);
			Sleep(2);
			cc.set_data(cc.DIGITAL, GREEN_LED, 0);
			Sleep(2);
			cc.set_data(cc.DIGITAL, RED_LED, 0);
		}
		if (_color_index == 1)
		{
			_color_text = "GREEN";
			cc.set_data(cc.DIGITAL, BLUE_LED, 0);
			Sleep(2);
			cc.set_data(cc.DIGITAL, GREEN_LED, 1);
			Sleep(2);
			cc.set_data(cc.DIGITAL, RED_LED, 0);
		}
		if (_color_index == 2)
		{
			_color_text = "RED";
			cc.set_data(cc.DIGITAL, BLUE_LED, 0);
			Sleep(2);
			cc.set_data(cc.DIGITAL, GREEN_LED, 0);
			Sleep(2);
			cc.set_data(cc.DIGITAL, RED_LED, 1);
		}

		_current_color = _colors[_color_index];
	}

	_last_state_SW1 = _state_SW1;

	if (_last_state_SW2 == 1 && _state_SW2 == 0)
	{
		_canvas.setTo(Scalar(255, 255, 255));
		_prev_point = Point(-1, -1);
		cvui::text(_canvas, 12, 25, "Color = " + _color_text);
	}

	_last_state_SW2 = _state_SW2;

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

	if (cvui::button(_canvas, 20, 80, 200, 30, "Exit"))
	{
		request_quit();
		return;
	}

	if (cvui::button(_canvas, 20, 40, 200, 30, "Reset"))
	{
		_canvas.setTo(Scalar(255,255,255));
		_prev_point = Point(-1, -1);
		cvui::text(_canvas, 12, 25, "Color = " + _color_text);
	}

	if (_prev_color != _color_index)
	{
		Rect ui_bar(0, 0, _canvas.cols, 35);
		_canvas(ui_bar).setTo(Scalar(255, 255, 255));
		cvui::text(_canvas, 12, 25, "Color = " + _color_text);
		_prev_color = _color_index;
	}

	cvui::update();
	imshow("Etch-A-Sketch", _canvas);

}
