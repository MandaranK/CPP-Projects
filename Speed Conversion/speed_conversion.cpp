#include <iostream>

int main();

int main() {

    double speed{};
    std::cout << "Enter the speed in miles per hour: ";
    std::cin >> speed;
    std::cout << std::endl;

    double mph{speed};
    double fps{speed*5280/3600};
    double mps{(speed*5280/3.28084)/3600};
    double kph{speed*5280/3.28084/1000};
    double fpf{(speed*5280/3.28084*201.168)*24*14};

    std::cout << "The speed is " << mph << " miles per hour." << std::endl;
    std::cout << "The speed is " << fps << " feet per second." << std::endl;
    std::cout << "The speed is " << mps << " meters per second." << std::endl;
    std::cout << "The speed is " << kph << " kilometers per hour." << std::endl;
    std::cout << "The speed is " << fpf << " furlongs per fortnight." << std::endl;

    return 0;

}