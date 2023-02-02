#include <iostream>

int main();

int main() {
	double x{};
	
	std::cout << "Enter value of x: ";
	std::cin >> x;
	
	// This local variable should hold the result of stair( x )
	int stair{};
	
	// TASK: write code that calculates an integer value
	// corresponding to the value of the function stair( x ) here
	
	int i = -9999;
	while(i < 9999)
	{
		if(x >= i && x < i+1)
		{
			stair = i;
			break;
		}
		i+=1;
		//printf("%d\r\n", i);
	}
	

	std::cout << "The value of stair(x) is: ";
	std::cout << stair;
	std::cout << std::endl;
	
	return 0;
}