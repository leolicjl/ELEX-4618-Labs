/*
Filename: CGameObject.cpp
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description:
*/
#include "stdafx.h"
#include "CGameObject.h"

void CGameObject::move()
{
	auto now = std::chrono::steady_clock::now();

	if (_first_move) {
		_last_move = now;
		_first_move = false;
		return;
	}

	double move_dt = std::chrono::duration<double>(now - _last_move).count();
	_last_move = now;

	_position += _velocity * move_dt;

}
bool CGameObject::collide(CGameObject& obj)
{
	Rect a(_position.x, _position.y, _shape.width, _shape.height);
	Rect b(obj._position.x, obj._position.y, obj._shape.width, obj._shape.height);
	return (a & b).area() > 0;
}

bool CGameObject::collide_wall(Size board)
{
	if (_position.x < 0) return true;
	if (_position.y < 0) return true;
	if (_position.x + _shape.width >= board.width) return true;
	if (_position.y + _shape.height >= board.height) return true;
	return false;
}

void CGameObject::hit()
{
	_lives--;
}

void CGameObject::draw(Mat& im)
{
	Rect r;
	r.x = _position.x;
	r.y = _position.y;
	r.width = _shape.width;
	r.height = _shape.height;
	rectangle(im, r,  Scalar(255, 255, 255), -1);

}

