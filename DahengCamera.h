#pragma once
#include "GalaxyIncludes.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "Matthread.h"
//#include "GxSingleCamDlg.h"
class Matthread;
//using namespace cv;
class Camera
{
public:
	bool Camopen;
	bool Capstart;
	bool saveauto;

	virtual void init(int i)=0;
	virtual void end()=0;
	virtual void startcap()=0;
	virtual void stopcap()=0;
	virtual cv::Mat grab()=0;
};


class Daheng:public Camera
{
	class CSampleCaptureEventHandler :public ICaptureEventHandler
	{
		//---------------------------------------------------------------------------------
		/**
		\brief   The capture callback function
		\param   objImageDataPointer      image process parameter
		\param   pFrame                   custom defined parameter

		\return  void
		*/
		//----------------------------------------------------------------------------------
	
		void DoOnImageCaptured(CImageDataPointer& objImageDataPointer, void* pUserParam)
		{
		  if(thread->cam->Callback)
			{


			 if (thread->cam->Camopen) {
					if (thread->cam->Capstart)
					{
						printf("call\n");
						void* pRaw8Buffer = NULL;
						//假设原始数据是Mono8图像
						pRaw8Buffer = objImageDataPointer->ConvertToRaw8(GX_BIT_0_7);
						thread->cam->curr =cv::Mat(objImageDataPointer->GetHeight(), objImageDataPointer->GetWidth(), CV_8UC1);
						memcpy(thread->cam->curr.data, pRaw8Buffer, (objImageDataPointer->GetHeight())*(objImageDataPointer->GetWidth()));

						cv::resize(thread->cam->curr, thread->cam->currr, cv::Size(500, 500));
				    	//cv:: cvtColor(thread->cam->currr, thread->cam->currr, cv::COLOR_BGR2RGB);
						thread->ViewImage(thread->cam->currr);

						//thread->msleep(40);
						/*
						cv::imshow("suut", thread->cam->curr);
						cv::waitKey(15);  */
			
					}
				}
			}
		}
	public:
		Matthread* thread;

	}; 
public:
	Daheng();
	~Daheng();
	bool Callback;

    //bool Capstart;
	void setexposure(int);
	void init(int);
	void end();
	void startcap();
	void stopcap(); 
	void callback();
	void discallback();
	void Triggeron();
	void Triggeroff();
	cv::Mat grab();
	CGXDevicePointer                  m_objDevicePtr;             ///< The device handle
	CGXStreamPointer                  m_objStreamPtr;             ///< The stream handle
	CGXFeatureControlPointer          m_objFeatureControlPtr;     ///< The object for device feature control
	CImageDataPointer                  m_objImageDataPtr;                    ///< The pointer for acquired image data 
	CSampleCaptureEventHandler*       m_pSampleCaptureEventHandle;
	GxIAPICPP::gxdeviceinfo_vector m_vectorDeviceInfo;
	cv::Mat curr;
	cv::Mat currr;
};