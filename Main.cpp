#include <iostream>

#include <mutex>
#include <semaphore>

#define NBR_STOOLS 4
#define NBR_HAIREDRESSER 1

static std::counting_semaphore stools(NBR_STOOLS);
static std::counting_semaphore hairedresser(NBR_HAIREDRESSER);
static int nbrCustomer = 0;

void Cut(int _idCustomer)
{
	std::cout << "The customer "<< _idCustomer << " gets a haircut\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(600));
	std::cout << "The customer "<< _idCustomer << " pays and leaves the hairdresser\n";
	hairedresser.release();
}

void HairdresserFunc()
{
	srand(time(NULL));
	rand();

	auto lambda = [&]()
		{
			int id = nbrCustomer++;

			std::cout << "The customer " << id << " arrives\n";
			if (hairedresser.try_acquire())
			{
				Cut(id);
				return;
			}

			if (!stools.try_acquire())
			{
				std::cout << "Customer " << id << " leaves because there's no stools :'c\n";
				return;
			}

			std::cout << "the customer " << id << " sits on a stool\n";
			while (true)
			{

				if (hairedresser.try_acquire())
				{
					stools.release();
					std::cout << "The customer " << id << " leaves the stool\n";
					Cut(id);
					
					return;
				}
			}

		};

	while (true)
	{
		std::thread thread(lambda);
		thread.detach();

		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 300 + 300));
	}
}

int main()
{
	HairdresserFunc();
}