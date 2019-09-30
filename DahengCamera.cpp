#include "DahengCamera.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/opencv.hpp"
//#include "GxSingleCamDlg.h"
using namespace cv;
Daheng::Daheng()
{
	m_pSampleCaptureEventHandle = new CSampleCaptureEventHandler();
	Camopen = 0;
	Capstart = 0;
	Callback = 0;
	saveauto = 0;
}
Daheng::~Daheng()
{

}
void Daheng::init(int i)
{
	
	
		//打开设备
		printf("opennumber%d\n", i);
		 m_objDevicePtr = IGXFactory::GetInstance().OpenDeviceBySN(
			m_vectorDeviceInfo[i].GetSN(),
			GX_ACCESS_EXCLUSIVE);
		m_objStreamPtr = m_objDevicePtr->OpenStream(0);
		m_objFeatureControlPtr = m_objDevicePtr->GetRemoteFeatureControl();

		printf("open success\n");
	

}
void Daheng::end()
{


	m_objStreamPtr->UnregisterCaptureCallback();

	//m_objStreamPtr->Close();
	m_objDevicePtr->Close();



	printf("end success\n");
}


void Daheng::startcap()
{ 
	 // m_objStreamPtr->RegisterCaptureCallback(m_pSampleCaptureEventHandle, NULL);

		m_objStreamPtr->StartGrab();
		//给设备发送开采命令
		m_objFeatureControlPtr->GetCommandFeature("AcquisitionStart")->Execute();
		printf("start success\n");
	
}

void Daheng::stopcap()
{
	

		//停采
		m_objFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();
		m_objStreamPtr->StopGrab();
		printf("stop success\n");


}
Mat Daheng::grab()
{
	try {
		m_objImageDataPtr = m_objStreamPtr->GetImage(500);//超时时间使用500ms，用户可以自行设定

		//Register the CaptureCallback function
		//m_objStreamPtr->RegisterCaptureCallback(m_pSampleCaptureEventHandle, this);

		//Send AcquisitionStart command 
		m_objFeatureControlPtr->GetCommandFeature("AcquisitionStart")->Execute();

		if (m_objImageDataPtr->GetStatus() == GX_FRAME_STATUS_SUCCESS)
		{

			void* pRaw8Buffer = NULL;
			//假设原始数据是Mono8图像
			pRaw8Buffer = m_objImageDataPtr->ConvertToRaw8(GX_BIT_0_7);
			curr=cv::Mat(m_objImageDataPtr->GetHeight(), m_objImageDataPtr->GetWidth(), CV_8UC1);
			memcpy(curr.data, pRaw8Buffer, (m_objImageDataPtr->GetHeight())*(m_objImageDataPtr->GetWidth()));

			cv::resize(curr, currr, Size(500, 500));
			
			waitKey(15);

			return currr;
		}
	}
	catch(CGalaxyException& e)
	{
		Mat  a(500,500,CV_8UC1);
		printf("no image\n");
		return a;
	}

}

void Daheng::Triggeron()
{
	printf("omT\n");
	//设置采集模式连续采集
	//m_objFeatureControlPtr->GetEnumFeature("AcquisitionMode")->SetValue("Continuous");
	//设置触发模式为开
	m_objFeatureControlPtr->GetEnumFeature("TriggerMode")->SetValue("On");
	//m_objFeatureControlPtr->GetEnumFeature("TriggerSource")->SetValue("Software");
	m_objFeatureControlPtr->GetEnumFeature("LineSelector")->SetValue("Line0");
	//m_objFeatureControlPtr->GetEnumFeature("LineSource")->SetValue("Strobe");
	//m_objFeatureControlPtr->GetEnumFeature("LineMode")->SetValue("Output");
	//cameraFeature.GetEnumFeature("UserOutputSelector").SetValue("UserOutput0");

	
}
void Daheng::Triggeroff()
{
	printf("offT\n");

	m_objFeatureControlPtr->GetEnumFeature("TriggerMode")->SetValue("Off");
}

void Daheng::callback()
{
	m_objFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();
	m_objStreamPtr->StopGrab();

	m_objStreamPtr->RegisterCaptureCallback(m_pSampleCaptureEventHandle, NULL);

	m_objStreamPtr->StartGrab();
	//给设备发送开采命令
	m_objFeatureControlPtr->GetCommandFeature("AcquisitionStart")->Execute();
}
void Daheng::discallback()
{
	m_objFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();
	m_objStreamPtr->StopGrab();

	m_objStreamPtr->UnregisterCaptureCallback();

	m_objStreamPtr->RegisterCaptureCallback(m_pSampleCaptureEventHandle, NULL);

	m_objStreamPtr->StartGrab();
	
}
 
void Daheng::setexposure(int a)
{
	printf("%d\n",a);
	m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->SetValue(a);
}

