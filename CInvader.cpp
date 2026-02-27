/*
Filename: CInvader.cpp
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description:
*/
#include "stdafx.h"
#include "CInvader.h"

CInvader::CInvader()
{

}
CInvader::CInvader(Point2f start_pos)
{
	_position = start_pos;
	_shape = Rect(0, 0, 15, 15);
	_lives = 1;
	_velocity = Point2f(0, 0);
}

CInvader::~CInvader()
{

}

