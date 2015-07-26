#include <Thread.hpp>

class MyThread : public varlib::Thread
{
public:
	long run()
	{
		while(1)		
		{
			std::cout << "111111111111"	 << std::endl;
		}
	}
};

int main()
{
	MyThread c;
	c.start();
	return 0;
}
