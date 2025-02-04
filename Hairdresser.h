#ifndef HAIRDRESSER_H
#define HAIRDRESSER_H

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

class Haidresser
{
public:
	Haidresser();
	~Haidresser();
	void Cut();
	bool Take();
private:
	std::mutex m_isSleep;
};


#endif