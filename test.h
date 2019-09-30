#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_test.h"
#include "DahengCamera.h"
class test : public QMainWindow
{
	Q_OBJECT

public:
	test(QWidget *parent = Q_NULLPTR);
	~test();
	void initport();
	//GxIAPICPP::gxdeviceinfo_vector* vectorDeviceInfo;
	void saveimage(int a, int b);
public slots:
	void start();
	void pause();
	void initmat();
	void exit();
	void opTrigger();
	void shTrigger();
	void Callbackon();
	void Callbackoff();
	void chanmaj();
	void chanpos();
	void setexp();
	void saveauto();
	void saveautooff();
signals:
	//参数传递信号 同时启动多线程
	void transconp(Daheng *);
	void transconp2(Daheng *);
	void transconp3(Daheng*);
	void transconp4(Daheng *);
private:
	Ui::testClass ui;
};
