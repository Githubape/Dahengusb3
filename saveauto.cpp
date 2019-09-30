#include "saveauto.h"
#include "DahengCamera.h"

Saveauto::Saveauto()
{
	//start();
}


Saveauto::~Saveauto()
{
	//delete cam;
}

void Saveauto::run()
{

	while (cam->saveauto)
	{
		saver();

	}
	printf("多线程结束\n\a");
}

void Saveauto::setconp(Daheng *con)
{
	cam = con;
	//con->m_pSampleCaptureEventHandle->thread = this;
	start();

	printf("多线程开始\n\a");
}