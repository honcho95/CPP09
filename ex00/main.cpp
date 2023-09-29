#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	std::ifstream dataFile, inputFile;
	
	if (ac != 2)
    {
        std::cout <<"Error : Invalid number of arguments ! (only expecting the input file)" << std::endl;
		return 1;
    }
	dataFile.open("data.csv");		
	if (!dataFile.is_open())
    {
        std::cout << "Error : No such file !" << std::endl;
        return 2;
    }
    inputFile.open(av[1]);
	if (!inputFile.is_open())
    {
        std::cout << "Error : No such file !" << std::endl;
        return 3;
    }
	BitcoinExchange btc(dataFile); // constructor called
	btc.displayResult(inputFile);
	dataFile.close();
	inputFile.close();
	return 0;
}