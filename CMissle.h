/*
Filename: CMissle.h
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description: Header File for CMissle.cpp
*/
#pragma once
#include "CGameObject.h"

/**
*
* @brief CMissle object using CGameObject
*
*
* @author Leo Li A01412091
*/
class CMissle : public CGameObject
{
public:
	/**
	* @brief Default constructor
	* @param position floating point
	* @param velocity floating point
	*/
	CMissle(Point2f pos, Point2f vel);

	/**
	* @brief Default destructor
	* @param none
	*/
	~CMissle();

	/**
	 * @brief Draws the object onto an image.
	 *
	 * Draws a filled rectangle at the object's current position.
	 *
	 * @param im Reference to image (canvas)
	 */
	void draw(Mat& im);
};

