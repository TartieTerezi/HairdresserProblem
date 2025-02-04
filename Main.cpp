#include <iostream>

#include "vector"
#include <mutex>

#define NBR_STOOLS 8

static std::mutex* stools = new std::mutex[NBR_STOOLS]{};
static std::mutex hairdresser;

void Cut()
{
	std::cout << "Le coiffeur coupe un client" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "fini, le client s'en va " << std::endl;
	hairdresser.unlock();
}

bool CanCut()
{
	return hairdresser.try_lock();
}

int main()
{
	auto lambda = [&]()
		{
			if (CanCut())
			{
				Cut();
				return;
			}

			int index = -1;
			for (size_t i = 0; i < NBR_STOOLS; i++)
			{
				if (stools[i].try_lock())
				{
					std::cout << "Le client s'asseoit" << std::endl;
					index = i;
					i = NBR_STOOLS;
				}
			}

			if (index != -1)
			{
				while (true)
				{
					if (CanCut())
					{
						stools[index].unlock();
						Cut();
						return;
					}
				}
			}
			else
			{
				std::cout << "Le client quitte le coiffeur mécontent :'c" << std::endl;
			}
		};

	
	srand(time(NULL));


	while (true)
	{
		if (rand() % 2 == 0)
		{
			std::cout << "Un client arrive" << std::endl;
			std::thread thread(lambda);
			thread.detach();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 300 + 200));
	}
}