#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) { }

BitcoinExchange::BitcoinExchange(std::ifstream& dataFile)
{
    size_t  datePart;
    size_t  comma;
    std::pair<std::string, float>   rateAndText;
    std::string                     eachLine, date, rate = "";

    std::getline(dataFile, eachLine);
    while (std::getline(dataFile, eachLine))
    {
        comma = eachLine.find(',');
        date = eachLine.substr(0, comma);
        if (comma != std::string::npos)
            rate = eachLine.substr(comma + 1);
        datePart = _checkDate(date);
        if (!datePart)
        {
            _data.clear();
            std::cout << "Error: bad input " << date << std::endl;
            return ;
        }
        rateAndText = _checkValue(rate);
        if (rateAndText.first != "valid")
        {
            _data.clear();
            std::cout << "[data.csv] " << rateAndText.first;
            return ;
        }
        _data[datePart] = rateAndText.second;  
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    for (std::map<unsigned int, float>::const_iterator it = other._data.begin();
        it != other._data.end(); ++it)
            this->_data[(*it).first] = (*it).second;
}

BitcoinExchange&    BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        this->_data.clear();
        for (std::map<unsigned int, float>::const_iterator it = other._data.begin();
            it != other._data.end(); ++it)
                this->_data[(*it).first] = (*it).second;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange(void) { }

void    BitcoinExchange::_splitStr(std::string& lineStr)
{
    size_t  begin = lineStr.find_first_not_of(" \f\n\r\t\v");
    lineStr.erase(0, begin);
    size_t  end = lineStr.find_last_not_of(" \f\n\r\t\v");
    lineStr.erase(end + 1);
}

unsigned int BitcoinExchange::_calculateDays(int year, int month, int day)
{
    int february = 28 + (year % 4 == 0);
    int months[12] = {31, february, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysTillDate = std::accumulate(months, months + (month - 1), 0) + day;
    int leapYears = (year-1)/4;
    unsigned int daysCalculated = leapYears + 365 * (year - 1) + daysTillDate;
    return daysCalculated;
}

unsigned int BitcoinExchange::_checkDate(const std::string& dateStr)
{
    int year;
    int month;
    int day;

    if (dateStr.length() != 10 || dateStr[4] != '-' || dateStr[7] != '-')
        return 0;
    std::istringstream dateStream(dateStr.substr(0, 4) + " " + dateStr.substr(5, 2) + " " + dateStr.substr(8, 2));
    dateStream >> year >> month >> day;

    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
        return 0;

    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2)
    {
        bool isLeapYear = (year % 4 == 0);
        daysInMonth[1] += isLeapYear;
    }
    if (day > daysInMonth[month - 1])
        return 0;
    return _calculateDays(year, month, day);
}

std::pair<std::string, float>   BitcoinExchange::_checkValue(const std::string& valueStr)
{
    if (valueStr == "" || valueStr == "+" || valueStr == "-")
        return std::make_pair( "Error: missing value :  ", 0.0);
    size_t  forbiddenChars = valueStr.find_first_not_of("0123456789");
    if (valueStr[0] == '-' || valueStr[0] == '+')
        forbiddenChars = valueStr.substr(1).find_first_not_of("0123456789");
    if (forbiddenChars == std::string::npos)
    {
        std::stringstream  valueStream(valueStr);
        long long integerValue;
        valueStream >> integerValue;
        if (integerValue > INT_MAX)
            return std::make_pair("Error: too large a number.\n", 0.0);
        if (integerValue < INT_MIN)
            return std::make_pair("Error: too small a number.\n", 0.0);
        if (integerValue < 0)
            return std::make_pair("Error: not a positive number.\n", 0.0);
        return std::make_pair("valid", static_cast<float>(integerValue));
    }
    char*   end;
    float   floatValue = strtof(valueStr.c_str(), &end);
    if (*end != '\0')
        return std::make_pair("Error: the number isn't valid.\n", 0.0);
    if (floatValue == HUGE_VALF)
        return std::make_pair("Error: the number is too big.\n", 0.0);
    if (floatValue < -HUGE_VALF)
        return std::make_pair("Error: the number is too small.\n", 0.0);
    if (floatValue < 0)
        return std::make_pair("Error: the number is negative.\n", 0.0);
    return std::make_pair("valid", floatValue);
}

void    BitcoinExchange::displayResult(std::ifstream& inputFile)
{
    if (_data.empty())
        return ;
    size_t  datePart;
    size_t  pipe;
    std::string eachLine;
    std::string date;
    std::string value;
    std::pair<std::string, float>   valueAndText;
    std::map<unsigned int, float>::iterator it;
    std::map<unsigned int, float>::iterator startIt;

    startIt = _data.begin();
    std::getline(inputFile, eachLine);
    while(std::getline(inputFile, eachLine))
    {
        pipe    = eachLine.find('|');
        date    = eachLine.substr(0, pipe);
        value   = "";
        if (pipe != std::string::npos)
            value = eachLine.substr(pipe + 1);
        this->_splitStr(date);
        this->_splitStr(value);
        datePart = _checkDate(date);
        if (datePart)
        {
            it = _data.find(datePart);
            while (--datePart && datePart >= startIt->first && it == _data.end())
                it = _data.find(datePart);
            if (it == _data.end())
                std::cout << "Error: no such date and couldn't find a lower date : " << date << std::endl;
            else
            {
                valueAndText = _checkValue(value);
                if (valueAndText.first != "valid")
                {
                    std::cout << valueAndText.first;
                    if (value == "")
                        std::cout << date << std::endl;
                }
                else if (valueAndText.second > 1000)
                    std::cout << "Error: the price is greater than 1000 : " << value << std::endl;
                else
                {
                    std::cout << date << " => " << valueAndText.second << " = " << valueAndText.second * (*it).second << std::endl;
                }
            }
        }
        else
            std::cout << "Error: bad input : " << date << std::endl;
    }
}
