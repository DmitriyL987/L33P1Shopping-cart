#include <iostream>
#include "service.hpp"

int main() {
    std::cout << "+++ Shopping cart +++" << std::endl;
    std::cout << "Commands: add, remove, add in base" << std::endl;
	std::cout << "The correct article contains 5 numbers, otherwise an exception is thrown\n" << std::endl;
    Service serv;
    while(true){
        std::string answer;
        std::cout << "command: " << std::endl;
        std::getline(std::cin, answer);
        if (answer == "exit") break;
        else if (answer == "add" || answer == "2") serv.add();
        else if (answer == "remove" || answer == "3") serv.remove();
        else if (answer == "add in base" || answer == "1") serv.addBase();
        std::cin.ignore(64, '\n');
    }
    return 0;
}
