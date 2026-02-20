/*
Filename: CSketch.cpp
Date: January 29, 2026
Author: Leo Li
Set: 3T
Description: Etch A Sketch Lab
*/

#include "stdafx.h"
#include "CSketch.h"



CSketch::CSketch(Size &canvas_size)
{
	cc.init_com();
	_canvas = Mat(canvas_size, CV_8UC3, Scalar(0,0,0));
	cvui::init(_etch_window);
	cvui::text(_canvas, 12, 10, "Color = " + _color_text);
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

	if (!cc.get_analog(_joystick, _accel))
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
		_canvas.setTo(Scalar(0, 0, 0));
		_prev_point = Point(-1, -1);
		cvui::text(_canvas, 12, 10, "Color = " + _color_text);
	}

	_last_state_SW2 = _state_SW2;


	float nx = ((float)_joystick.x- _center_x) / 2047.0f;
	float ny = (_center_y - (float)_joystick.y) / 2047.0f;

	nx = max(-1.0f, min(nx, 1.0f));
	ny = max(-1.0f, min(ny, 1.0f));

	float r = sqrt(nx*nx + ny*ny);
	if (r > 1.0f)
	{
		nx /= r;
		ny /= r;
		r = 1.0f;
	}

	float a = atan2(ny, nx);
	float c = fabs(cos(a));
	float s = fabs(sin(a));
	float m = (c > s) ? c : s;    

	float sx = (m > 1e-6f) ? (r * cos(a) / m) : 0.0f;
	float sy = (m > 1e-6f) ? (r * sin(a) / m) : 0.0f;

	_lcd.x = (int)((sx * 0.5f + 0.5f) * (_canvas.cols - 1));
	_lcd.y = (int)((sy * 0.5f + 0.5f) * (_canvas.rows - 1));


	_lcd.x = std::max(0, std::min(_lcd.x, _canvas.cols - 1));
	_lcd.y = std::max(0, std::min(_lcd.y, _canvas.rows - 1));
}

void CSketch::draw()
{
	if (!cc.is_connected())
		return;

	Point _current_point(_lcd.x, _lcd.y);

	if (_prev_point.x == -1) {
		_prev_point = _current_point;
	}
	else {
		line(_canvas, _prev_point, _current_point, _current_color, LINE_THICKNESS, LINE_AA);
		_prev_point = _current_point;
	}

	if (cvui::button(_canvas, 20, 80, 40, 30, "Exit"))
	{
		request_quit();
		return;
	}

	if (cvui::button(_canvas, 20, 40, 40, 30, "Reset"))
	{
		_canvas.setTo(Scalar(0,0,0));
		_prev_point = Point(-1, -1);
		cvui::text(_canvas, 12, 10, "Color = " + _color_text);
	}

	if ((_accel.x > ACCEL_CENTERX + ACCEL_MIN_SHAKE) || 
		(_accel.x < ACCEL_CENTERX - ACCEL_MIN_SHAKE) || 
		(_accel.y > ACCEL_CENTERY + ACCEL_MIN_SHAKE) || 
		(_accel.y < ACCEL_CENTERY - ACCEL_MIN_SHAKE))
	{
		_canvas.setTo(Scalar(0, 0, 0));
		_prev_point = Point(-1, -1);
		cvui::text(_canvas, 12, 10, "Color = " + _color_text);
	}

	if (_prev_color != _color_index)
	{
		Rect ui_bar(0, 0, _canvas.cols, 20);
		_canvas(ui_bar).setTo(Scalar(0, 0, 0));
		cvui::text(_canvas, 12, 10, "Color = " + _color_text);
		_prev_color = _color_index;
	}
	cvui::update();
	imshow("Etch-A-Sketch", _canvas);

}
