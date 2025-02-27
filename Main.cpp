#include <iostream>

#include <mutex>
#include <semaphore>

#define NBR_STOOLS 8
#define NBR_HAIREDRESSER 2

static std::counting_semaphore stools(NBR_STOOLS);
static std::counting_semaphore hairedresser(NBR_HAIREDRESSER);
//static std::mutex hairedresserMutex;
static unsigned int nbrCustomer = 0;

unsigned int ClientRefused = 0;
unsigned int ClientAccepted = 0;
unsigned int ClientFromStool = 0;

void Cut(int _idCustomer)
{
	ClientAccepted++;
	//std::cout << "The customer " << _idCustomer << " gets a haircut\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	//std::cout << "The customer " << _idCustomer << " pays and leaves the hairdresser\n";
	hairedresser.release();
	//hairedresserMutex.unlock();
}

void HairdresserFunc()
{
	srand(time(NULL));
	rand();

	auto lambda = [&]()
		{
			int id = nbrCustomer++;

			//std::cout << "The customer " << id << " arrives\n";
			if (hairedresser.try_acquire())
			//if (hairedresserMutex.try_lock())
			{
				Cut(id);
				return;
			}

			if (!stools.try_acquire())
			{
				//std::cout << "Customer " << id << " leaves because there's no stools :'c\n";
				ClientRefused++;
				return;
			}

			//std::cout << "the customer " << id << " sits on a stool\n";
			while (true)
			{
				//if (hairedresserMutex.try_lock())
				if (hairedresser.try_acquire())
				{
					stools.release();
					ClientFromStool++;
					//std::cout << "The customer " << id << " leaves the stool\n";
					Cut(id);
					return;
				}
			}

		};

	auto whileLambda = [&]()
		{
			while (true)
			{
				std::thread thread(lambda);
				thread.detach();

				//std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 300));

				

			}
		};

	while (true)
	{
		std::thread threadWhile(whileLambda);
		threadWhile.detach();

		if (nbrCustomer % 100 == 0)
		{

			std::cout << "Accepted : " << ClientAccepted << " : " << " Refused : " << ClientRefused << " Customer : " << nbrCustomer <<
				" From Stools " << ClientFromStool <<
				std::endl;
		}
	}

	


}

int main()
{
	HairdresserFunc();
}