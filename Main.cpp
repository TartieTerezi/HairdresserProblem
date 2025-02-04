#include <iostream>

#include "Hairdresser.h"
#include "Stool.h"
#include "vector"

#define NBR_STOOLS 4

static Stool* stools = new Stool[NBR_STOOLS];
static Haidresser hairdresser;

int main()
{
	std::vector<std::thread> Customers = std::vector<std::thread>();

	auto lambda = [&]()
		{
			if (hairdresser.Take())
			{
				hairdresser.Cut();
				return;
			}
			
			int index = -1;
			for (size_t i = 0; i < NBR_STOOLS; i++)
			{
				if (stools[i].Take())
				{
					stools[i].Taking();
					index = i;
					i = NBR_STOOLS;
				}
			}

			if (index != -1)
			{
				while (true)
				{
					if (hairdresser.Take())
					{
						stools[index].Drop();
						hairdresser.Cut();
						return;
					}
				}
			}
			else
			{
				std::cout << "Le client quitte le coiffeur" << std::endl;
			}
		};

	while (true)
	{
		Customers.push_back (std::thread(lambda));
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 300 +200));
	}

	for (size_t i = 0; i < Customers.size(); i++)
	{
		Customers[i].join();
	}
}