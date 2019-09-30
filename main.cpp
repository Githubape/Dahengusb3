#include "test.h"
#include <QtWidgets/QApplication>
#include "DahengCamera.h"
#include "opencv2/opencv.hpp"
//using namespace cv;

int main(int argc, char *argv[])
{



	QApplication a(argc, argv);
	test w;
	w.show();
	return a.exec();
}

