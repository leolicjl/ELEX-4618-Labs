/*
Filename: CGameObject.h
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description: header file for CGameObject.cpp
*/
#pragma once
#include "CSpaceInvadersGame.h"

class CGameObject
{
protected:
	Point2f _position;
	Point2f _velocity;
	Rect _shape;
	int _lives;

public:
	void move();
	bool collide(CGameObject& obj);
	void hit();
	int get_lives() { return _lives; }
	void set_lives(int lives) { _lives = lives; }
	void set_pos(Point2f pos) { _position = pos; }
	Point2f get_pos() { return _position; }
	void draw(Mat& im);
};

