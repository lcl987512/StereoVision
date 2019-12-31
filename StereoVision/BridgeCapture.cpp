#include "stdafx.h"
#include "BridgeCapture.h"
#include <conio.h>

BridgeCapture::BridgeCapture() {
  m_isOpened = false;
  m_frame = nullptr;
  m_isLeft = 0;
}

bool BridgeCapture::init(int is_left, Mat& frame) {
  m_isLeft = is_left;
  m_frame = &frame;
  return true;
}

BridgeCapture::~BridgeCapture() {}

bool BridgeCapture::open(int device) {
  if (device != -1) {
    if (!m_capture.open(device)) {
      m_isOpened = false;
      return false;
    }
  }

  m_isOpened = true;

  return true;
}

void BridgeCapture::release() {
  if (m_capture.isOpened()) m_capture.release();

  m_isOpened = 0;
}

bool BridgeCapture::isOpened() const { return m_isOpened; }

BridgeCapture& BridgeCapture::operator>>(CV_OUT Mat& image) {
  int64 start = cvGetTickCount();
  int64 end;
  
  if (m_isLeft == 3) { m_capture >> image; } else if (m_isLeft == 0) {
    if (m_capture.isOpened()) {
      Mat frame;
      m_capture >> frame;
      end = cvGetTickCount();
      _cprintf("m_capture >> *m_frame == %ld ms\n", (end - start) / 1000);
      //m_capture >> *m_frame;
      frame.copyTo(*m_frame);
      end = cvGetTickCount();
      _cprintf("m_capture >> *m_frame == %ld ms\n", (end - start) / 1000);
      
      
      Rect rect(m_frame->cols / 2, 0, m_frame->cols / 2, m_frame->rows);
      (*m_frame)(rect).copyTo(image);
    }
  } else {
   
    Rect rect(0, 0, m_frame->cols / 2, m_frame->rows);
    (*m_frame)(rect).copyTo(image);
  }
  end = cvGetTickCount();
  _cprintf("%ld ms\n", (end - start) / 1000);
  //cout << (end - start)/1000 << " ms" << endl;
  
  return *this;
}
