#pragma once
#ifndef KALMANTRACKER_H_
#define KALMANTRACKER_H_

#include <vector>
#include <array>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;

#define MAX_TRACKS 20

namespace RCV
{
	class KalmanTracker
	{
	public:
		KalmanTracker();

		void initRectangleList(vector<Rect2d> &rect);

		void trackRectangle(Mat &frame);

	private:
		/// Vector to update the rectangles
		vector<Rect2d> rectangles;

		/// List of trackers corresponding to rectangles
		array<Ptr<TrackerKCF>, MAX_TRACKS> trackList;

		/// count indicates the number of object to be tracked
		int count;
	};
}

#endif //KALMANTRACKER_H_