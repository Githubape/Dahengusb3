#pragma once
#include <QOpenGLWidget> 
#include <Qimage>
#include "DahengCamera.h"

class View:public  QOpenGLWidget
{
	Q_OBJECT

public:
	View(QWidget *p);
	~View();
	void paintEvent(QPaintEvent *e);
	Daheng* Dcam;

public slots:
	void SetImage(cv::Mat);
protected:
	QImage img;
};

