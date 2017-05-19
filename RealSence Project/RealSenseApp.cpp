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
	// Sense Manager 생성
	senseManager = PXCSenseManager::CreateInstance();
	if (senseManager == nullptr)
	{
		throw std::runtime_error("SenseMangaer 생성에 실패하였습니다.");
	}

	// 컬러 스트림을 활성화합니다
	auto sts = senseManager->EnableStream(PXCCapture::StreamType::STREAM_TYPE_COLOR, COLOR_WIDTH, COLOR_HEIGHT, COLOR_FPS);

	if (sts < PXC_STATUS_NO_ERROR)
	{
		throw std::runtime_error("컬러 스트림 활성화에 실패했습니다.");
	}

	// 파이프 라인을 초기화
	sts = senseManager->Init();
	if (sts < PXC_STATUS_NO_ERROR)
	{
		throw std::runtime_error("파이프 라인의 초기화에 실패했습니다");
	}

	// 미러 표시
	senseManager->QueryCaptureManager()->QueryDevice()->SetMirrorMode(PXCCapture::Device::MIRROR_MODE_HORIZONTAL);
}


void RealSenseApp::run()
{
	while (1)
	{
		// 프레임 데이터 업데이트
		updateFrame();

		// 표시
		auto ret = showImage();
		if (!ret)
		{
			break;
		}
	}
}


void RealSenseApp::updateFrame()
{
	// 프레임 가져오기
	auto sts = senseManager->AcquireFrame(false);
	if (sts < PXC_STATUS_NO_ERROR)
	{
		return;
	}

	// 프레임 데이터 가져오기
	const PXCCapture::Sample* sample = senseManager->QuerySample();
	if (sample != nullptr)
	{
		// 각 데이터를 표시
		updateColorImage(sample->color);
	}

	// 프레임 릴리즈
	senseManager->ReleaseFrame();
}


// 이미지 표시하기
bool RealSenseApp::showImage()
{
	// 표시
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

	// 데이터 가져오기
	PXCImage::ImageData data;
	pxcStatus sts = colorFrame->AcquireAccess(PXCImage::Access::ACCESS_READ,
											  PXCImage::PixelFormat::PIXEL_FORMAT_RGB32,
											  &data);
	if (sts < PXC_STATUS_NO_ERROR)
	{
		throw std::runtime_error("컬러 이미지 가져오기 실패");
	}

	// 데이터 복사
	PXCImage::ImageInfo info = colorFrame->QueryInfo();

	colorImage = cv::Mat(info.height, info.width, CV_8UC4);
	memcpy(colorImage.data, data.planes[0], data.pitches[0] * info.height);

	// 데이터 해제
	colorFrame->ReleaseAccess(&data);
}