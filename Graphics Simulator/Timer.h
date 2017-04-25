#pragma once


#include <chrono>			// timer
#include <iostream>



class Timer
{
public:
	// �̱��� �ʿ伺?
	Timer()
	{
	}

	virtual ~Timer()
	{
	}

	// ī���͸� �����Ѵ�
	static void SetCounter(float counter)
	{
		m_sinCounter = sinf(counter);	// sin counter
		m_cosCounter = cosf(counter);	// cos counter
	}

	static float m_sinCounter;
	static float m_cosCounter;

	// ����ð��� ī���� ������ �޾ƿ´�																				
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

	// Timer ���, Ŭ���� ���� ������ �κ� (static���� ����ϴ� ���� ���� �� ����)
private:
	std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now();	// ���۽ð�
};

