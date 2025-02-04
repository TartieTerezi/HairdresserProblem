#include "Hairdresser.h"

Haidresser::Haidresser()
{
}

Haidresser::~Haidresser()
{
}

void Haidresser::Cut()
{
	std::cout << "Le coiffeur coupe" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "Le coiffeur a fini sa coupe" << std::endl;
	std::cout << "Le Coiffeur fait payer le client" << std::endl;
	m_isSleep.unlock();
}

bool Haidresser::Take()
{
	return m_isSleep.try_lock();
}

