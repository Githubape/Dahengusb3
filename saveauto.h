#pragma once

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <QThread>
#include <QMutex>
//#include "DahengCamera.h"

//using namespace cv;
class Daheng;
class Saveauto :public QThread
{

	Q_OBJECT

public:
	Saveauto();
	/*	static Matthread * Get()
		{
			printf("多线程构建\n\a");
			Matthread vt;
			return &vt;
		}*/
	~Saveauto();
	Saveauto * Getptr()
	{
		return this;
	}
	void run();

public slots:
	void setconp(Daheng*);

public:
	Daheng* cam;
signals:
	void saver();
protected:

	QMutex mutex;

};

