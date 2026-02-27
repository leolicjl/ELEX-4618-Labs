/*
Filename: CBase4618.cpp
Date: February 5, 2026
Author: Leo Li
Set: 3T
Description: Base class in which all labs will inherit from
Notes: imshow() is already called here for safety.
*/

#include "stdafx.h"
#include "CBase4618.h"

CBase4618::CBase4618()
{
}

CBase4618::~CBase4618()
{
}

bool CBase4618::run(char user_quit, string window_name)
{
	_quit = false;

	auto next_frame = chrono::steady_clock::now();
	auto last_frame = next_frame;

	while (!_quit)
	{
		next_frame += frame_duration;

		gpio();
		update();
		draw();

		auto now = chrono::steady_clock::now();
		_dt = std::chrono::duration<double>(now - last_frame).count();

		if (_dt > 0.0)
		{

			for (int i = 9; i > 0; i--)
			{
				_fps_array[i] = _fps_array[i - 1];
			}
			_fps = 1.0 / _dt;
			_fps_array[0] = _fps;
			double sum = 0;
			for (int i = 0; i < 10; i++)
				sum += _fps_array[i];

			_fps = sum / 10;

		}

		last_frame = now;

		int key = waitKey(1);
		if (key == user_quit)
			_quit = true;

		if (cv::getWindowProperty(window_name, WND_PROP_VISIBLE) < 1)
			_quit = true;

		this_thread::sleep_until(next_frame);
	}

	destroyWindow(window_name);
	return true;
}

//void CBase4618::update_thread()
//{
//	auto next_frame = chrono::steady_clock::now();
//	auto last_frame = next_frame;
//	while (!_quit.load())
//	{
//		next_frame += frame_duration;
//
//		{
//			lock_guard<mutex> lock(_mtx);
//			gpio();
//			update();
//		}
//
//		auto now = chrono::steady_clock::now();
//		_dt = std::chrono::duration<double>(now - last_frame).count();
//
//		if (_dt > 0.0)
//		{
//
//			for (int i = 9; i > 0; i--)
//			{
//				_fps_array[i] = _fps_array[i - 1];
//			}
//
//			_fps = 1.0 / _dt;
//			_fps_array[0] = _fps;
//
//			double sum = 0;
//			for (int i = 0; i < 10; i++)
//				sum += _fps_array[i];
//
//			_fps = sum / 10;
//
//		}
//
//		last_frame = now;
//
//		this_thread::sleep_until(next_frame);
//
//	}
//
//}
//
//void CBase4618::draw_thread()
//{
//
//	auto next_frame = chrono::steady_clock::now();
//
//	while (!_quit.load())
//	{
//		next_frame += frame_duration;
//
//		{
//			lock_guard<mutex> lock(_mtx);
//			draw();
//		}
//
//		this_thread::sleep_until(next_frame);
//	}
//
//}
//
//bool CBase4618::run(char user_quit, string window_name)
//{
//
//	_quit.store(false);
//
//	namedWindow(window_name, WINDOW_AUTOSIZE);
//
//	_updateThread = thread(&CBase4618::update_thread, this);
//	_drawThread = thread(&CBase4618::draw_thread, this);
//
//	while (!_quit.load())
//	{
//		{
//			std::lock_guard<std::mutex> lock(_mtx);
//			cv::imshow(window_name, _canvas);
//		}
//		int key = cv::waitKey(1);
//		if (key == user_quit)
//			request_quit();
//
//		if (cv::getWindowProperty(window_name, cv::WND_PROP_VISIBLE) < 1)
//			request_quit();
//	}
//
//	if (_updateThread.joinable())
//		_updateThread.join();
//
//	if (_drawThread.joinable())
//		_drawThread.join();
//	
//	destroyWindow(window_name);
//	return true;
//}