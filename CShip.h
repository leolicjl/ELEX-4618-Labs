/*
Filename: CShip.h
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description: header file for CShip.cpp
*/
#pragma once
#include "CGameObject.h"

class CShip : public CGameObject
{
public:
	/**
	* @brief Default constructor
	* @param none
	*/
	CShip();

	/**
	* @brief Default destructor
	* @param none
	*/
	~CShip();

	/**
	 * @brief Draws the object onto an image.
	 *
	 * Draws a filled rectangle at the object's current position.
	 *
	 * @param im Reference to image (canvas)
	 */
	void draw(Mat& im);

};

