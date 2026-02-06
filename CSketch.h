/*
Filename: CSketch.h
Date: February 5, 2026
Author: Leo Li
Set: 3T
Description: Header file for CSketch.cpp
*/
#pragma once
#include "CBase4618.h"
#define RATIO (250.0f) / (4095.0f)
#define LINE_THICKNESS 1

using namespace cv;

class CSketch : public CBase4618
{
private:
	int _joystick_x, _joystick_y, _lcd_x, _lcd_y;
	int _state = 0;
	int _last_state = 1;
	Point _prev_point = Point(-1, -1);

	Scalar _colors[3] = { Scalar(255,0,0), Scalar(0,255,0),  Scalar(0,0,255) };
	
	int _color_index = 0;
	Scalar _current_color = _colors[_color_index];

public:

	CSketch();
	~CSketch();
	
	void gpio() override;

	void update() override;

	void draw() override;
};

