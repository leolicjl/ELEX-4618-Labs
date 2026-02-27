/*
Filename: CInvader.h
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description: header file for CInvader.cpp
*/
#pragma once
#include "CGameObject.h"

class CInvader : public CGameObject
{
public:
	CInvader();
	CInvader(Point2f start_pos);
	~CInvader();
};

