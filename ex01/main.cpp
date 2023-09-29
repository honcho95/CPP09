#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout<<"Error : The program must take 1 argument !" << std::endl;
        return 1;
    }
    RPN obj;
    obj.checkAndCalculate(av[1]);
    return 0;
}