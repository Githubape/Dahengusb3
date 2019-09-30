#include "Matthread.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "DahengCamera.h"

using namespace cv;


Matthread::Matthread()
{
	//start();
}


Matthread::~Matthread()
{
	//delete cam;
}

void Matthread::run()
{
	static int i = 0;
	printf("xianchgn:::%d", i);
	i++;
	printf("������߳�\n\a");
	cv::Mat mat(500, 500, CV_8UC1);

	while (cam->Camopen) {
		while (!cam->Callback) {
			if (cam->Capstart)
			{
				printf("mat\n");

				mat = cam->grab();//���ò���������mat

	
				cv::cvtColor(mat, mat, COLOR_BGR2RGB);
				//mat = dealwmat(mat);  //����ͼ��
				ViewImage(mat);
			}
		}
	}
	printf("���߳̽���\n\a");
}

void Matthread::setconp(Daheng *con)
{  
	cam = con;
	con->m_pSampleCaptureEventHandle->thread =this;
	start();
	
	printf("���߳̿�ʼ\n\a");
}

