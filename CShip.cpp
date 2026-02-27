/*
Filename: CShip.cpp
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description:
*/
#include "stdafx.h"
#include "CShip.h"

CShip::CShip()
{
	_shape = Rect(0, 0, 40, 20);
	_velocity = Point2f(0, 0);
	_position = Point2f(0, 0);
}

CShip::~CShip()
{
}

void CShip::draw(Mat& im)
{
	Rect r;
	r.x = _position.x;
	r.y = _position.y;
	r.width = _shape.width;
	r.height = _shape.height;
	rectangle(im, r, Scalar(255, 255, 255), -1);

}