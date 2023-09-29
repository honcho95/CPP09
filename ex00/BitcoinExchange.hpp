#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
#include <cmath>
#include <numeric>
#include <climits>

class BitcoinExchange
{
    public:
        BitcoinExchange(void);
        BitcoinExchange(std::ifstream& dataFile);
        BitcoinExchange(const BitcoinExchange& other);
        ~BitcoinExchange(void);
        BitcoinExchange&    operator=(const BitcoinExchange& other);
        void                displayResult(std::ifstream& inputFile);
    
    private:
        void                            _splitStr(std::string& lineStr);
        unsigned int                    _calculateDays(int year, int month, int day);
        unsigned int                    _checkDate(const std::string& dateStr);
        std::pair<std::string, float>   _checkValue(const std::string& valueStr);

        std::map<unsigned int, float>   _data;
};

#endif
