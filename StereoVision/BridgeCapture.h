#pragma once

#include <string>

#include "opencv2/highgui/highgui.hpp"
#include "CvvImage.h"
#include "PointCloudAnalyzer.h"
using namespace std;
using namespace cv;

class BridgeCapture {
public:
  BridgeCapture();
  ~BridgeCapture();

  bool init(int is_left, Mat& frame); // 0:left 1:right 3:normal
  bool open(const string& filename);
  bool open(int device);
  bool isOpened() const;
  void release();

  BridgeCapture& operator>>(CV_OUT Mat& image);


public:
  VideoCapture m_capture;
private:
  bool m_isOpened;
  Mat* m_frame;
  int m_isLeft;
};

