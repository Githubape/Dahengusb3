#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <QThread>
#include <QMutex>
//#include "DahengCamera.h"

//using namespace cv;
class Daheng;
class Matthread:public QThread
{

	Q_OBJECT

public:
	Matthread();
/*	static Matthread * Get()
	{
		printf("多线程构建\n\a");
	    Matthread vt;
		return &vt;
	}*/
	~Matthread();
	Matthread * Getptr()
	{
		return this;
	}
	void run();
    
public slots:
	void setconp(Daheng*);

public:
	Daheng* cam;
signals:
	void ViewImage(cv::Mat); 
protected:
	
	QMutex mutex;

};

