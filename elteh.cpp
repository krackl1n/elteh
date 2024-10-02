// elteh.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Core.h"

int main()
{
    const std::vector<float> resistance = {14, 7, 17, 38};

    int option;

    std::cout << "Option: " << std::endl;
    std::cin >> option;
    std::cout << "Hello, my friend. I special wrote this message" << std::endl;
    Core core(resistance, option*19, option*11, option*6);

    return 0;

}