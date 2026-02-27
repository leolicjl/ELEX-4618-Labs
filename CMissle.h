/*
Filename: CMissle.h
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description: Header File for CMissle.cpp
*/
#pragma once
#include "CGameObject.h"

class CMissle : public CGameObject
{
public:
	CMissle(Point2f pos, Point2f vel);
	~CMissle();
};

