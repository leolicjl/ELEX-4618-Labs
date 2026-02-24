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

void CBase4618::update_thread()
{
	auto next_frame = chrono::steady_clock::now();
	auto last_frame = next_frame;
	while (!_quit.load())
	{
		next_frame += frame_duration;

		gpio();

		{
			lock_guard<mutex> lock(_mtx);
			update();
		}

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
			for (int i = 0; i < 9; i++)
				sum += _fps_array[i];

			_fps = sum / 10;

		}

		last_frame = now;

		this_thread::sleep_until(next_frame);

	}

}

void CBase4618::draw_thread(char user_quit, string window_name)
{
	namedWindow(window_name, WINDOW_AUTOSIZE);

	while (!_quit.load())
	{
		{
			lock_guard<mutex> lock(_mtx);
			draw();
		}

		imshow(window_name, _canvas);

		int key = cv::waitKey(1);
		if (key == user_quit)
			request_quit();

		if (!window_name.empty() && getWindowProperty(window_name, WND_PROP_VISIBLE) < 1)
		{
			request_quit();
		}
	}

	if (!window_name.empty())
		destroyWindow(window_name);
}

bool CBase4618::run(char user_quit, string window_name)
{

	_quit.store(false);

	cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

	_updateThread = std::thread(&CBase4618::update_thread, this);

	while (!_quit.load())
	{
		{
			std::lock_guard<std::mutex> lock(_mtx);
			draw(); 
		}

		cv::imshow(window_name, _canvas);

		int key = cv::waitKey(1);
		if (key == user_quit)
			request_quit();

		if (cv::getWindowProperty(window_name, cv::WND_PROP_VISIBLE) < 1)
			request_quit();
	}

	if (_updateThread.joinable())
		_updateThread.join();

	cv::destroyWindow(window_name);
	return true;
}