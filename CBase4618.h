/*
Filename: CBase4618.h
Date: February 5, 2026
Author: Leo Li
Set: 3T
Description: Header file for CBase4618.cpp
*/
#pragma once
#include "CControl.h"
#include "cvui.h"


using namespace cv;
class CBase4618 {

protected:
	CControl cc;
	Mat _canvas;
	bool _quit = false;
	void request_quit() { _quit = true; }

public:

	CBase4618();
	~CBase4618();

	virtual void gpio() = 0;

	virtual void update() = 0;
	
	virtual void draw() = 0;

	bool run(char user_quit = 'q');

};

