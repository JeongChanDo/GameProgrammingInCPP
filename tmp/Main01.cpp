#include <iostream>
#include <vector>
#include <algorithm>

void main()
{
	std::vector<int*> mInts;
	std::vector<int*> deadInts;

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	mInts.push_back(&a);
	mInts.push_back(&b);
	mInts.push_back(&c);
	mInts.push_back(&d);

	for (auto intVal : mInts)
	{
		std::cout << *intVal << " " << intVal << std::endl;

		if (*intVal == 3)
		{
			deadInts.emplace_back(intVal);
		}
	}

	std::cout << std::endl;
	std::cout << std::endl;

	for (auto intVal : mInts)
	{
		std::cout << *intVal << " " << intVal << std::endl;
	}
	std::cout << std::endl;
	for (auto intVal : deadInts)
	{
		std::cout << *intVal << " " << intVal << std::endl;

		auto iter = std::find(mInts.begin(), mInts.end(), intVal);
		if (iter != mInts.end())
		{

			std::iter_swap(iter, mInts.end() - 1);

			std::cout << "after swap" << std::endl;

			for (auto intVal : mInts)
			{
				std::cout << *intVal << " " << intVal << std::endl;
			}

			std::cout << "swap finished" << std::endl;


			mInts.pop_back();
		}
		std::cout << "deleted" << std::endl;

	}

	std::cout << std::endl;
	std::cout << std::endl;

	for (auto intVal : mInts)
	{
		std::cout << *intVal << " " << intVal << std::endl;
	}

}