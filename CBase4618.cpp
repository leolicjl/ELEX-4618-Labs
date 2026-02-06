/*
Filename: CBase4618.cpp
Date: February 5, 2026
Author: Leo Li
Set: 3T
Description: 
*/

#include "stdafx.h"
#include "CBase4618.h"

CBase4618::CBase4618()
{
}

CBase4618::~CBase4618()
{
}

bool CBase4618::run(char user_quit)
{
	_quit = false;

	while (!_quit)
	{
		gpio();
		update();
		draw();

		int key = waitKey(1);
		
		if (key == user_quit)
			_quit = true;

		if (cv::getWindowProperty("Etch-A-Sketch", WND_PROP_VISIBLE) < 1)
			_quit = true;
	}

	cv::destroyWindow("Etch-A-Sketch");
	return true;
}
