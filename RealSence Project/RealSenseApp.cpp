#include "RealSenseApp.h"

#include <pxcsensemanager.h>


RealSenseApp::RealSenseApp()
{
}


RealSenseApp::~RealSenseApp()
{
	if (senseManager != nullptr)
	{
		senseManager->Release();
		senseManager = nullptr;		//
	}
}


void RealSenseApp::initialize()
{
	// Sense Manager ����
	senseManager = PXCSenseManager::CreateInstance();
	if (senseManager == nullptr)
	{
		throw std::runtime_error("SenseMangaer ������ �����Ͽ����ϴ�.");
	}

	// �÷� ��Ʈ���� Ȱ��ȭ�մϴ�
	auto sts = senseManager->EnableStream(PXCCapture::StreamType::STREAM_TYPE_COLOR, COLOR_WIDTH, COLOR_HEIGHT, COLOR_FPS);

	if (sts < PXC_STATUS_NO_ERROR)
	{
		throw std::runtime_error("�÷� ��Ʈ�� Ȱ��ȭ�� �����߽��ϴ�.");
	}

	// ������ ������ �ʱ�ȭ
	sts = senseManager->Init();
	if (sts < PXC_STATUS_NO_ERROR)
	{
		throw std::runtime_error("������ ������ �ʱ�ȭ�� �����߽��ϴ�");
	}

	// �̷� ǥ��
	senseManager->QueryCaptureManager()->QueryDevice()->SetMirrorMode(PXCCapture::Device::MIRROR_MODE_HORIZONTAL);
}


void RealSenseApp::run()
{
	while (1)
	{
		// ������ ������ ������Ʈ
		updateFrame();

		// ǥ��
		auto ret = showImage();
		if (!ret)
		{
			break;
		}
	}
}


void RealSenseApp::updateFrame()
{
	// ������ ��������
	auto sts = senseManager->AcquireFrame(false);
	if (sts < PXC_STATUS_NO_ERROR)
	{
		return;
	}

	// ������ ������ ��������
	const PXCCapture::Sample* sample = senseManager->QuerySample();
	if (sample != nullptr)
	{
		// �� �����͸� ǥ��
		updateColorImage(sample->color);
	}

	// ������ ������
	senseManager->ReleaseFrame();
}


// �̹��� ǥ���ϱ�
bool RealSenseApp::showImage()
{
	// ǥ��
	cv::imshow("Color Image", colorImage);
	int c = cv::waitKey(10);
	if ((c == 27) || (c == 'q') || (c == 'Q'))
	{
		// ESC || q || Q for Exit
		return false;
	}
	return true;
}


void RealSenseApp::updateColorImage(PXCImage* colorFrame)
{
	if (colorFrame == nullptr)
	{
		return;
	}

	// ������ ��������
	PXCImage::ImageData data;
	pxcStatus sts = colorFrame->AcquireAccess(PXCImage::Access::ACCESS_READ,
											  PXCImage::PixelFormat::PIXEL_FORMAT_RGB32,
											  &data);
	if (sts < PXC_STATUS_NO_ERROR)
	{
		throw std::runtime_error("�÷� �̹��� �������� ����");
	}

	// ������ ����
	PXCImage::ImageInfo info = colorFrame->QueryInfo();

	colorImage = cv::Mat(info.height, info.width, CV_8UC4);
	memcpy(colorImage.data, data.planes[0], data.pitches[0] * info.height);

	// ������ ����
	colorFrame->ReleaseAccess(&data);
}