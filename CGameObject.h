/*
Filename: CGameObject.h
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description: header file for CGameObject.cpp
*/
#pragma once
using namespace cv;

class CGameObject
{
protected:
	Point2f _position;
	Point2f _velocity;
	Rect _shape;
	int _lives;

	std::chrono::steady_clock::time_point _last_move;
	bool _first_move = true;

public:
	void move();
	bool collide(CGameObject& obj);
	bool collide_wall(Size board);
	void hit();
	int get_lives() { return _lives; }
	void set_lives(int lives) { _lives = lives; }
	void set_pos(Point2f pos) { _position = pos; }
	Point2f get_pos() { return _position; }
	void set_velocity(Point2f v) { _velocity = v; }
	Point2f get_velocity() { return _velocity; }
	void draw(Mat& im);
};

