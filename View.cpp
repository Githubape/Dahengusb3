#include "View.h"
#include <QPainter>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;


View::View(QWidget *p) :QOpenGLWidget(p)
{
	Dcam = new(Daheng);
}


View::~View()
{
	delete Dcam;
}

void View::paintEvent(QPaintEvent *e)
{

	QPainter painter;

	painter.begin(this);
	painter.drawImage(QPoint(0, 0), img);
	painter.end();
	printf("endcap\n");

}

void View::SetImage(Mat mat)
{
	/* imshow("a", mat);
	waitKey(30);  
	if (img.isNull())
	{
		uchar *buf = new uchar[width()*height()*2];
		img = QImage(buf, width(), height(), QImage::Format_Indexed8);

	}
	memcpy(img.bits(), mat.data, mat.cols*mat.rows*mat.elemSize());*/
	img = QImage((const uchar*)(mat.data), mat.cols, mat.rows, mat.cols * mat.channels(), QImage::Format_RGB888);
	
	update();
}