#include <iostream>
#include "../includes/Game.class.hpp"


int main(void)
{
    int size;
    std::cout << "Enter field size (25 - 75): " << std::endl;
    std::cin >> size;
    if (size <= 75 && size >= 25)
    {   
        Game game(size);
        game.play();
    }
    return 0;
}