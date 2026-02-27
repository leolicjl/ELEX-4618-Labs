/*
Filename: CInvader.h
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description: header file for CInvader.cpp
*/
#pragma once
#include "CGameObject.h"

/**
* 
* @brief CInvader object using CGameObject
*
*
* @author Leo Li A01412091
*/
class CInvader : public CGameObject
{
private:
	Mat _sprite1;
	Mat _sprite2;
	std::chrono::steady_clock::time_point _last_toggle = std::chrono::steady_clock::now();
	int _row = 0;
public:
	/**
	* @brief Default constructor
	* @param none
	*/
	CInvader();

	/**
	* @brief constructor overrude
	* @param start position as floating point
	*/
	CInvader(Point2f start_pos, int row);

	/**
	* @brief Default deconstructor
	* @param none
	*/
	~CInvader();

	/**
	 * @brief Draws the object onto an image.
	 *
	 * Draws a filled rectangle at the object's current position.
	 *
	 * @param im Reference to image (canvas)
	 */
	void draw(Mat& im, bool frame);

	int get_row() const { return _row; }
};

