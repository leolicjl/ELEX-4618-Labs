/*
Filename: CSketch.h
Date: February 5, 2026
Author: Leo Li
Set: 3T
Description: Header file for CSketch.cpp
*/
#pragma once
#include "CBase4618.h"
#define WINDOW_SIZE 250
#define RATIO (250.0f) / (4095.0f)
#define LINE_THICKNESS 1

using namespace cv;

class CSketch : public CBase4618
{
private:
	int _joystick_x, _joystick_y, _lcd_x, _lcd_y;
	int _state_SW1 = 0;
	int _last_state_SW1 = 1;
	int _state_SW2 = 0;
	int _last_state_SW2 = 1;
	string _color_text = "BLUE";
	Point _prev_point = Point(-1, -1);

	Scalar _colors[3] = { Scalar(255,0,0), Scalar(0,255,0),  Scalar(0,0,255) };
	
	int _color_index = 0;
	int _prev_color = 0;
	Scalar _current_color = _colors[_color_index];

	const float _center_x = 2060.0f;
	const float _center_y = 1995.0f;
public:

	CSketch(Size &canvas_size);
	~CSketch();
	
	void gpio() override;

	void update() override;

	void draw() override;
};

