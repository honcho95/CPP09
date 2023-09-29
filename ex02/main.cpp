#include "PmergeMe.hpp"

int main(int ac, char **av)
{
   std::string  numSequence;
   for (int i = 1; i < ac; ++i)
    {
        numSequence += av[i];
        if (i != ac - 1)
        numSequence += " ";
    }

    PmergeMe obj;
    try
    {
        obj = PmergeMe(numSequence);
    }
    catch (const std::exception& e)
    {
        std::cout<<e.what()<<std::endl;
        return 1;
    }

    std::cout << "Before: ";
    obj.displayList(10);

    struct timeval  time;
    gettimeofday(&time, NULL);
    long long   vectorBefore = time.tv_sec * 1000000LL + time.tv_usec;
    obj.vectorFordJohnson(0, obj.getVectorSize() - 1);
    gettimeofday(&time, NULL);
    long long   vectorAfter = time.tv_sec * 1000000LL + time.tv_usec;

    gettimeofday(&time, NULL);
    long long   listBefore = time.tv_sec * 1000000LL + time.tv_usec;
    obj.listFordJohnson(0, obj.getListSize() - 1);
    gettimeofday(&time, NULL);
    long long   listAfter = time.tv_sec * 1000000LL + time.tv_usec;

    std::cout << "After: ";
    obj.displayList(10);

    std::cout << "Time to process a range of " << obj.getVectorSize();
    std::cout <<" elements with std::vector :  ";
    std::cout << (vectorAfter - vectorBefore) / 1000.0<<" us" << std::endl;

    std::cout << "Time to process a range of " << obj.getListSize();
    std::cout << " elements with std::list :  ";
    std::cout << (listAfter - listBefore) / 1000.0 << " us" << std::endl;
    return 0;
}