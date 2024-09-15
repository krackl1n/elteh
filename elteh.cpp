// elteh.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Core.h"

int main()
{
    const std::vector<float> resistance = {14, 7, 17, 38};
    int option = 13;

    Core core(resistance, option*19, option*11, option*6);

    return 0;

}