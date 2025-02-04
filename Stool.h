#ifndef STOOL_H
#define STOOL_H

#include <mutex>
#include <iostream>

static int NUMBER_STOOLS = 0;

class Stool
{
public:
	Stool();
	~Stool();

	void Taking();
	bool Take();
	void Drop();
private:
	int m_id;
	std::mutex m_isTake;
};


#endif // !STOOL_H
