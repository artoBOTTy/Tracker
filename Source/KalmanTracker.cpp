#include "KalmanTracker.h"

RCV::KalmanTracker::KalmanTracker()
{
	count = 0;
	for (int i = 0; i < 20; i++)
	{
		trackList.at(i) = TrackerKCF::create();
	}
}

void RCV::KalmanTracker::initRectangleList(vector<Rect2d> &rect)
{
	vector<Rect2d>::iterator it;
	for (it = rect.begin(); it != rect.end(); it++)
	{
		rectangles.push_back(*it);
		count++;
		if (count > MAX_TRACKS)
			break;
	}
}

void RCV::KalmanTracker::trackRectangle(Mat &frame)
{
	vector<Rect2d>::iterator it;
	int i = 0;
	for (it = rectangles.begin(); it != rectangles.end(); it++)
	{
		rectangle(frame, *it, Scalar(255, 0, 0), 2, 1);
		TrackerKCF *tracker = (trackList.at(i));
		tracker->init(frame, *it);
		bool ok = tracker->update(frame, *it);
		if (ok)
		{
			// Tracking success : Draw the tracked object
			rectangle(frame, *it, Scalar(255, 0, 0), 2, 1);
		}
		else
		{
			// Tracking failure detected.
			//putText(frame, "Tracking failure detected", Point(100, 80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
			//rectangles.erase(it);
		}
		i++;
		//imshow("Tracking", frame);
	}
}
