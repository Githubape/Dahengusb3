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
	printf("���߳̽���\n\a");
}

void Saveauto::setconp(Daheng *con)
{
	cam = con;
	//con->m_pSampleCaptureEventHandle->thread = this;
	start();

	printf("���߳̿�ʼ\n\a");
}