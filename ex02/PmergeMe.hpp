#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <sstream>
#include <climits>
#include <exception>
#include <sys/time.h>

class PmergeMe
{
    public:
        PmergeMe(void); 
        PmergeMe(const std::string& numSequence);
        PmergeMe(const PmergeMe& other);
        PmergeMe&   operator=(const PmergeMe& other);
        ~PmergeMe(void);

        int getVectorSize(void) const;
        int getListSize(void) const;

        void    vectorFordJohnson(int begin, int end);
        void    listFordJohnson(int begin, int end);

        void    checkVectorSort(void);
        void    checkListSort(void);

        void    displayVector(unsigned int value) const;
        void    displayList(unsigned int value) const;

    private:
        std::vector<int>    _vector;
        std::list<int>      _list;

        void    _fillContainer(std::string& numSequence);
        void    _vectorInsertionSort(int begin, int end);
        void    _vectorMergeSort(int begin, int end);
        void    _listInsertionSort(int begin, int end);
        void    _listMergeSort(int begin, int end);
};

#endif