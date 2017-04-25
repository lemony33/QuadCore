#pragma once


#include <chrono>			// timer
#include <iostream>



class Timer
{
public:
	// 싱글톤 필요성?
	Timer()
	{
	}

	virtual ~Timer()
	{
	}

	// 카운터를 설정한다
	static void SetCounter(float counter)
	{
		m_sinCounter = sinf(counter);	// sin counter
		m_cosCounter = cosf(counter);	// cos counter
	}

	static float m_sinCounter;
	static float m_cosCounter;

	// 경과시간을 카운터 값으로 받아온다																				
	float GetCounter_timer()
	{
		//auto start = std::chrono::high_resolution_clock::now();
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = end - start;
		auto i_millis = std::chrono::duration_cast<std::chrono::milliseconds>(dur);
		auto f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(dur);
		//std::cout << i_millis.count() << '\n';
		std::cout << f_secs.count() << '\n';
		return f_secs.count();
	}

	void Reset_Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	// Timer 기능, 클래스 분할 가능한 부분 (static으로 사용하는 것이 좋을 수 있음)
private:
	std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now();	// 시작시간
};

