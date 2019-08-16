#include <iostream>
#include "../includes/Game.class.hpp"


int main(int ac, char **)
{
    if (ac < 2) 
    { 
        int size;
        std::cout << "Enter field size (25 - 75): " << std::endl;
        std::cin >> size;
        if (size <= 75 && size >= 25)
        {   
            Game game(size);
            game.play();
        }
        else 
            std::cout << "Wrong value" << std::endl;
    }
    else 
        std::cout << "Too much arguments" << std::endl;
    return 0;
}