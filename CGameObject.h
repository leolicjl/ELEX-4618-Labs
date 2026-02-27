/*
Filename: CGameObject.h
Date: February 26, 2026
Author: Leo Li
Set: 3T
Description: header file for CGameObject.cpp
*/
#pragma once
using namespace cv;

/**
*
* @brief CGameObject class
* 
* has characteristics of the object to be drawn
*
*
* @author Leo Li A01412091
*/
class CGameObject
{
protected:
	Point2f _position; ///< Current position of the oobject
	Point2f _velocity; ///< Velocity vector (pxls per second)
	Rect _shape; ///< Rectangle width and height of the object
	int _lives; ///< number of lives remaining

	std::chrono::steady_clock::time_point _last_move; ///< time of last movement update
	bool _first_move = true; ///< flag to intialize first movement timing

public:

	/**
	* @brief Default constructor
	* @param none
	*/
	CGameObject();

	/**
	* @brief Default destructor
	* @param none
	*/
	~CGameObject();

	/**
	 * @brief Updates object position using velocity and delta time.
	 *
	 * Computes elapsed time since last move and updates
	 * position using: position = position + velocity * dt.
	 */
	void move();

	/**
	 * @brief Detects collision with another game object.
	 *
	 * Uses rectangular intersection to determine overlap.
	 *
	 * @param obj Reference to another CGameObject
	 * @return true if objects overlap, false otherwise
	 */
	bool collide(CGameObject& obj);

	/**
	 * @brief Detects collision with the screen boundaries.
	 *
	 * @param board Size of the game canvas
	 * @return true if object is outside the boundaries
	 */
	bool collide_wall(Size board);

	/**
	 * @brief Reduces object lives by one.
	 */
	void hit();

	/**
	 * @brief Gets remaining lives.
	 * @return Current number of lives
	 */
	int get_lives() { return _lives; }

	/**
	 * @brief Sets number of lives.
	 * @param lives New life value
	 */
	void set_lives(int lives) { _lives = lives; }

	/**
	 * @brief Sets object position.
	 * @param pos New position
	 */
	void set_pos(Point2f pos) { _position = pos; }

	/**
	* @brief Gets current position.
	* @return Current position
	*/
	Point2f get_pos() { return _position; }

	/**
	 * @brief Sets object velocity.
	 * @param v Velocity vector (pixels per second)
	 */
	void set_velocity(Point2f v) { _velocity = v; }

	/**
	 * @brief Gets object velocity.
	 * @return Current velocity vector
	 */
	Point2f get_velocity() { return _velocity; }
};

