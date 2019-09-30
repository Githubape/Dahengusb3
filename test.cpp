#include "test.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "Matthread.h"
#include "saveauto.h"
#include <iostream>
using namespace std;

using namespace cv;
test::test(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	initport();

	Matthread* M1 =new(Matthread);
	qRegisterMetaType<cv::Mat>("cv::Mat");
	QObject::connect(M1,
		SIGNAL(ViewImage(cv::Mat)),
		ui.openGLWidget,
		SLOT(SetImage(cv::Mat)),
		Qt::DirectConnection
	);

	//实现主次线程参数传递
	qRegisterMetaType<Daheng>("Daheng");
	QObject::connect(this,
		SIGNAL(transconp(Daheng*)),
		M1,
		SLOT(setconp(Daheng*))
	);

	Matthread* M2 = new(Matthread);
	qRegisterMetaType<cv::Mat>("cv::Mat");
	QObject::connect(M2,
		SIGNAL(ViewImage(cv::Mat)),
		ui.openGLWidget_2,
		SLOT(SetImage(cv::Mat)),
		Qt::DirectConnection
	);

	//实现主次线程参数传递
	qRegisterMetaType<Daheng>("Daheng");
	QObject::connect(this,
		SIGNAL(transconp2(Daheng*)),
		M2,
		SLOT(setconp(Daheng*))
	);

	Matthread* M3 = new(Matthread);
	qRegisterMetaType<cv::Mat>("cv::Mat");
	QObject::connect(M3,
		SIGNAL(ViewImage(cv::Mat)),
		ui.openGLWidget_3,
		SLOT(SetImage(cv::Mat)),
		Qt::DirectConnection
	);

	//实现主次线程参数传递
	qRegisterMetaType<Daheng>("Daheng");
	QObject::connect(this,
		SIGNAL(transconp3(Daheng*)),
		M3,
		SLOT(setconp(Daheng*))
	);
	
	Saveauto *s1 = new(Saveauto);
	QObject::connect(s1,
		SIGNAL(saver()),
		this,
		SLOT(chanmaj()),
		Qt::DirectConnection
	);
	qRegisterMetaType<Daheng>("Daheng");
	QObject::connect(this,
		SIGNAL(transconp4(Daheng*)),
		s1,
		SLOT(setconp(Daheng*))
	);


}
test::~test() {
	IGXFactory::GetInstance().Uninit();
}


void test::start()
{
	printf("********************开始********************\n");
	switch (ui.port->currentIndex()) {
	case 0:
		ui.openGLWidget->Dcam->startcap();
		ui.openGLWidget->Dcam->Capstart = 1;
		break;

	case 1:
		ui.openGLWidget_2->Dcam->startcap();
		ui.openGLWidget_2->Dcam->Capstart = 1;
		break;
	case 2:
		ui.openGLWidget_3->Dcam->startcap();
		ui.openGLWidget_3->Dcam->Capstart = 1;
		break;
	default:
		break;

	}
	/*
	ui.stopcapbut->setEnabled(true);
	ui.startcapbut->setEnabled(false);
	*/
	printf("********************开始********************\n");

}
//停止 button callback
void test::pause()
{

	printf("********************停止********************\n");
	switch (ui.port->currentIndex()) {
	case 0:
		ui.openGLWidget->Dcam->Capstart = 0;
		ui.openGLWidget->Dcam->stopcap();
		break;
	case 1:
		ui.openGLWidget_2->Dcam->Capstart = 0;
		ui.openGLWidget_2->Dcam->stopcap();
		break;
	case 2:
		ui.openGLWidget_3->Dcam->Capstart = 0;
		ui.openGLWidget_3->Dcam->stopcap();
		break;
	default:
		break;
	}
	/*
	ui.stopcapbut->setEnabled(false);
	ui.startcapbut->setEnabled(true);
	*/
	printf("********************停止********************\n");
	                                                                           
}
//打开箱机button callback
void test::initmat()
{
	printf("********************打开相机********************\n");
	printf("%d\n", ui.port->currentIndex());
	switch (ui.port->currentIndex()) {
	case 0:
		//相机初始化
		ui.openGLWidget->Dcam->init(0);
		//开始
	   // ui.openGLWidget->Dcam->startcap();
		//初始化控件
		ui.openGLWidget->Dcam->Camopen = 1;
		ui.openGLWidget->Dcam->Capstart = 0;
		//传递控制模块
		transconp(ui.openGLWidget->Dcam);
		break;
	case 1:
		//相机初始化
		ui.openGLWidget_2->Dcam->init(1);
		//开始
	   // ui.openGLWidget->Dcam->startcap();
		//初始化控件
		ui.openGLWidget_2->Dcam->Camopen = 1;
		ui.openGLWidget_2->Dcam->Capstart = 0;
		//传递控制模块
		transconp2(ui.openGLWidget_2->Dcam);
		break;
	case 2:
		//相机初始化
		ui.openGLWidget_3->Dcam->init(2);
		//开始
	   // ui.openGLWidget->Dcam->startcap();
		//初始化控件
		ui.openGLWidget_3->Dcam->Camopen = 1;
		ui.openGLWidget_3->Dcam->Capstart = 0;
		//传递控制模块
		transconp3(ui.openGLWidget_3->Dcam);
		break;
	default:
		break;
		
		
	}
	
	
	/*
	ui.startcapbut->setEnabled(true);
	ui.tribut->setEnabled(true);
	ui.trioffbut->setEnabled(true);
	ui.endbut->setEnabled(true);
	ui.cabonbut->setEnabled(true);
	ui.openbut->setEnabled(false);
	*/
	printf("********************打开相机********************\n");

}
// 关闭 button callback
void test::exit()
{
	printf("********************关闭相机********************\n");
	switch (ui.port->currentIndex()) {
	case 0:
		//锁定控制参数
		ui.openGLWidget->Dcam->Camopen = 0;
		ui.openGLWidget->Dcam->Capstart = 0;
		//stopcap
		//ui.openGLWidget->Dcam->stopcap();

		//关闭相机
		ui.openGLWidget->Dcam->end();
		break;
	case 1:
		//锁定控制参数
		ui.openGLWidget_2->Dcam->Camopen = 0;
		ui.openGLWidget_2->Dcam->Capstart = 0;
		//stopcap
		//ui.openGLWidget->Dcam->stopcap();

		//关闭相机
		ui.openGLWidget_2->Dcam->end();
		break;
	case 2:
		//锁定控制参数
		ui.openGLWidget_3->Dcam->Camopen = 0;
		ui.openGLWidget_3->Dcam->Capstart = 0;
		//stopcap
		//ui.openGLWidget->Dcam->stopcap();

		//关闭相机
		ui.openGLWidget_3->Dcam->end();
		break;
	default:
		break;
	}
	/*
	ui.openbut->setEnabled(true);
	ui.startcapbut->setEnabled(false);
	ui.stopcapbut->setEnabled(false);
	ui.tribut->setEnabled(false);
	ui.trioffbut->setEnabled(false);
	ui.endbut->setEnabled(false);
	ui.cabonbut->setEnabled(false);
	ui.calshubut->setEnabled(false);
	*/
	printf("********************关闭相机********************\n");

}

void test::opTrigger()
{
	printf("********************Trigger on********************\n");
	switch (ui.port->currentIndex())
	{
	case 0:
		ui.openGLWidget->Dcam->Triggeron();
		break;
	case 1:
		ui.openGLWidget_2->Dcam->Triggeron();
		break;
	case 2:
		ui.openGLWidget_3->Dcam->Triggeron();
		break;
	default:
		break;
	}
	printf("********************Trigger on********************\n");

}
void test::shTrigger()
{
	
	printf("********************Trigger off********************\n");
	switch (ui.port->currentIndex())
	{
	case 0:
		ui.openGLWidget->Dcam->Triggeroff();
		break;
	case 1:
		ui.openGLWidget_2->Dcam->Triggeroff();
		break;
	case 2:
		ui.openGLWidget_3->Dcam->Triggeroff();
		break;
	default:
		break;
	}
	printf("********************Trigger off********************\n");

}
void test::Callbackon()
{
	printf("********************Callback on********************\n");
	switch (ui.port->currentIndex()) {
	case 0:
		ui.openGLWidget->Dcam->callback();
		ui.openGLWidget->Dcam->Callback = 1;
		break;
	case 1:
		ui.openGLWidget_2->Dcam->callback();
		ui.openGLWidget_2->Dcam->Callback = 1;
		break;
	case 2:
		ui.openGLWidget_3->Dcam->callback();
		ui.openGLWidget_3->Dcam->Callback = 1;
		break;
	default:
		break;

	}
	//ui.calshubut->setEnabled(true);
//	ui.cabonbut->setEnabled(false);
	printf("********************Callback on********************\n");
	
}
void test::Callbackoff()
{
	printf("********************Callback off********************\n");
	switch (ui.port->currentIndex()) {
	case 1:
		ui.openGLWidget->Dcam->Callback = 0;
		ui.openGLWidget->Dcam->discallback();
		break;
	case 2:
		ui.openGLWidget_2->Dcam->Callback = 0;
		ui.openGLWidget_2->Dcam->discallback();
		break;
	case 3:
		ui.openGLWidget_3->Dcam->Callback = 0;
		ui.openGLWidget_3->Dcam->discallback();
		break;
	default:
		break;
	}

	//ui.calshubut->setEnabled(false);
	//ui.cabonbut->setEnabled(true);
	printf("********************Callback off********************\n");

}

void test::initport()
{
	IGXFactory::GetInstance().Init();
	//枚举设备
	static GxIAPICPP::gxdeviceinfo_vector vectorDeviceInfo;
	IGXFactory::GetInstance().UpdateDeviceList(1000, vectorDeviceInfo);
	if (vectorDeviceInfo.size()== 0)
	{
		printf("nocamera\n");
	}
	else
	{
		for (int i = 1; i <= vectorDeviceInfo.size(); i++)
		{
			
			ui.port->addItem("Cam%d", i);
			ui.openGLWidget->Dcam->m_vectorDeviceInfo = vectorDeviceInfo;
			ui.openGLWidget_2->Dcam->m_vectorDeviceInfo = vectorDeviceInfo;
			ui.openGLWidget_3->Dcam->m_vectorDeviceInfo = vectorDeviceInfo;

		}
	}
}


void test::chanmaj()
{
	QString input_data1 = ui.lineEdit1->text();
	QString input_data2 = ui.lineEdit_2->text();
	QString input_data3 = ui.lineEdit_3->text();
	QString input_data4 = ui.lineEdit_5->text();
	int a = input_data1.toInt();
	int t= input_data3.toInt();
	int max = input_data4.toInt();
	for (int b = 1; b <= max; b++)
	{
		saveimage(a, b);
		printf("save %d_%d\n", a, b);
	//	ui.lineEdit_2->setText(input_data2.setNum(b));
		Sleep(t);
	}
	ui.lineEdit1->setText(input_data1.setNum(a + 1));
	ui.lineEdit_2->setText(input_data2.setNum(0));
	//printf("样本号：%d", a);
	
}

void test::chanpos()
{
	QString input_data1 = ui.lineEdit1->text();
	int a = input_data1.toInt();

	QString input_data2 = ui.lineEdit_2->text();
	int b = input_data2.toInt();
	ui.lineEdit_2->setText(input_data2.setNum(b + 1));
	//printf("位置号：%d", b);
	
	saveimage(a, b);
}




void test::saveimage(int a, int b) {


	//string im = "1.tif";
	//ui.openGLWidget_2->Dcam->curr = imread(im, 0);
	char s[] = ".tif";
	char buffer1[200],
		s1[] = "../images1/";

	char buffer2[200],
		s2[] = "../images2/";
	char buffer3[200],
		s3[] = "../images3/";


	int j, k, q;

	if (ui.openGLWidget->Dcam->Camopen&&ui.openGLWidget->Dcam->Capstart)
	{
		j = sprintf_s(buffer1, 200, "%s", s1);
		j += sprintf_s(buffer1 + j, 200 - j, "yangben%d", a);
		j += sprintf_s(buffer1 + j, 200 - j, "weizhi%d", b);
		j = sprintf_s(buffer1 + j, 200 - j, "%s", s);
		imwrite(buffer1, ui.openGLWidget->Dcam->curr);
	}
	if (ui.openGLWidget_2->Dcam->Camopen&&ui.openGLWidget_2->Dcam->Capstart)
	{
		k = sprintf_s(buffer2, 200, "%s", s2);
		k += sprintf_s(buffer2 + k, 200 - k, "yangben%d", a);
		k += sprintf_s(buffer2 + k, 200 - k, "weizhi%d", b);
		k = sprintf_s(buffer2 + k, 200 - k, "%s", s);
		imwrite(buffer2, ui.openGLWidget_2->Dcam->curr);
	}
	if (ui.openGLWidget_3->Dcam->Camopen&&ui.openGLWidget_3->Dcam->Capstart)
	{
		q = sprintf_s(buffer3, 200, "%s", s3);
		q += sprintf_s(buffer3 + q, 200 - q, "yangben%d", a);
		q += sprintf_s(buffer3 + q, 200 - q, "weizhi%d", b);
		q  = sprintf_s(buffer3 + q, 200 - q, "%s", s);
		imwrite(buffer3, ui.openGLWidget_3->Dcam->curr);
	}
}

void test::setexp()
{
	QString a = ui.lineEdit->text();
	int m = a.toInt();
	ui.openGLWidget->Dcam->setexposure(m);
}

void test::saveauto()
{
	ui.openGLWidget_2->Dcam->saveauto = 1;
	transconp4(ui.openGLWidget_3->Dcam);
	ui.pushButton_4->setEnabled(true);
	ui.pushButton_3->setEnabled(false);
}

void test::saveautooff()
{
	ui.openGLWidget_2->Dcam->saveauto = 0;
	ui.pushButton_4->setEnabled(false);
	ui.pushButton_3->setEnabled(true);

}
