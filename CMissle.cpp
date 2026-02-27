/*
Filename: CMissle.cpp
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description:
*/
#include "stdafx.h"
#include "CMissle.h"

CMissle::CMissle(Point2f pos, Point2f vel)
{
    _position = pos;
    _velocity = vel;
    _shape = Rect(0, 0, 6, 12);
    _lives = 1;
}

CMissle::~CMissle()
{

}