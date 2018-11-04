#if 0
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;
#endif

#include "KalmanTracker.h"

// Convert to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()

#if 0
int main(int argc, char **argv)
{
	// List of tracker types in OpenCV 3.4.1
	string trackerTypes[8] = { "BOOSTING", "MIL", "KCF", "TLD","MEDIANFLOW", "GOTURN", "MOSSE", "CSRT" };
	// vector <string> trackerTypes(types, std::end(types));

	// Create a tracker
	string trackerType = trackerTypes[2];

	Ptr<Tracker> tracker1;
	Ptr<Tracker> tracker2;

#if (CV_MINOR_VERSION < 3)
	{
		tracker = Tracker::create(trackerType);
	}
#else
	{
		/*if (trackerType == "BOOSTING")
			tracker = TrackerBoosting::create();
		if (trackerType == "MIL")
			tracker = TrackerMIL::create();*/
		//if (trackerType == "KCF")
			tracker1 = TrackerKCF::create();
			tracker2 = TrackerKCF::create();
		/*
		if (trackerType == "TLD")
			tracker = TrackerTLD::create();
		if (trackerType == "MEDIANFLOW")
			tracker = TrackerMedianFlow::create();
		if (trackerType == "GOTURN")
			tracker = TrackerGOTURN::create();*/
	}
#endif
	// Read video
	VideoCapture video("SampleVideo03.mp4");

	// Exit if video is not opened
	if (!video.isOpened())
	{
		cout << "Could not read video file" << endl;
		return 1;
	}

	// Read first frame 
	Mat frame;
	bool ok = video.read(frame);

	// Define initial bounding box 
	Rect2d bbox1(92 + 92, 75, 150, 150);
	Rect2d bbox2(92 + 92 + 30 + 150, 75, 150, 150);

	// Uncomment the line below to select a different bounding box 
	// bbox = selectROI(frame, false); 
	// Display bounding box. 
	rectangle(frame, bbox1, Scalar(255, 0, 0), 2, 1);
	rectangle(frame, bbox2, Scalar(255, 0, 0), 2, 1);

	//imshow("Tracking2", frame);

	imshow("Tracking", frame);
	tracker1->init(frame, bbox1);
	tracker2->init(frame, bbox2);

	while (video.read(frame))
	{
		// Start timer
		double timer = (double)getTickCount();

		// Update the tracking result
		bool ok1 = tracker1->update(frame, bbox1);
		bool ok2 = tracker2->update(frame, bbox2);

		// Calculate Frames per second (FPS)
		float fps = getTickFrequency() / ((double)getTickCount() - timer);

		if (ok1 && ok2)
		{
			// Tracking success : Draw the tracked object
			rectangle(frame, bbox1, Scalar(255, 0, 0), 2, 1);
			rectangle(frame, bbox2, Scalar(255, 0, 0), 2, 1);
		}
		else
		{
			// Tracking failure detected.
			putText(frame, "Tracking failure detected", Point(100, 80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
		}

		// Display tracker type on frame
		// putText(frame, trackerType + " Tracker", Point(100, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

		// Display FPS on frame
		// putText(frame, "FPS : " + SSTR(int(fps)), Point(100, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

		// Display frame.
		imshow("Tracking", frame);

		// Exit if ESC pressed.
		int k = waitKey(1);
		if (k == 27)
		{
			break;
		}

	}
}

#endif


int main()
{
	RCV::KalmanTracker objectTracker;

	// Read video
	VideoCapture video("SampleVideo04.mp4");

	// Exit if video is not opened
	if (!video.isOpened())
	{
		cout << "Could not read video file" << endl;
		return 1;
	}

	// Read first frame 
	Mat frame;
	bool ok = video.read(frame);

	imshow("Tracking", frame);

	Rect2d bbox1(40, 75, 130, 180);
	//Rect2d bbox2(300, 75, 20, 60);

	vector<Rect2d> objectList;
	objectList.push_back(bbox1);
	//objectList.push_back(bbox2);

	objectTracker.initRectangleList(objectList);

	while (video.read(frame))
	{

		objectTracker.trackRectangle(frame);

		imshow("Tracking", frame);

		// Exit if ESC pressed.
		int k = waitKey(1);
		if (k == 27)
		{
			break;
		}
	}

}
void trackObject(Ptr<Tracker> &tracker, Rect2d &object, Mat &frame)
{

}