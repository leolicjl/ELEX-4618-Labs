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
CInvader::CInvader(Point2f start_pos, int row) : _row(row)
{
	_position = start_pos;
	_shape = Rect(0, 0, 30, 30);
	_lives = 1;
	_velocity = Point2f(0, 0);

	if (_sprite1.empty())
	{
		_sprite1 = imread("sprite1.png", IMREAD_GRAYSCALE);
		_sprite2 = imread("sprite2.png", IMREAD_GRAYSCALE);
	}
}

CInvader::~CInvader()
{

}

void CInvader::draw(Mat& im, bool frame)
{
    if (_lives <= 0) return;

    Mat sprite = (frame ? _sprite2 : _sprite1);

    if (sprite.empty())
    {
        // fallback if image missing
        Rect r(_position.x, _position.y, _shape.width, _shape.height);
        rectangle(im, r, Scalar(255, 255, 255), -1);
        return;
    }

    Mat resized;
    resize(sprite, resized, Size(_shape.width, _shape.height), 0, 0, INTER_NEAREST);

    Rect roi(_position.x, _position.y, resized.cols, resized.rows);
    if (roi.x >= 0 && roi.y >= 0 &&
        roi.x + roi.width <= im.cols &&
        roi.y + roi.height <= im.rows)
    {
        Mat mask;
        threshold(resized, mask, 10, 255, THRESH_BINARY);
        cvtColor(resized, resized, COLOR_GRAY2BGR);
        resized.copyTo(im(roi), mask);
    }

}

