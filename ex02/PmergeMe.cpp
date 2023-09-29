#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) { }

PmergeMe::PmergeMe(const std::string& numSequence)
{
    std::string integers = numSequence;
    try
    {
        this->_fillContainer(integers);
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error("Error");
    }
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
    int vectorIndex = 0;
    this->_vector.reserve(other._vector.size());
    for (std::list<int>::const_iterator it = other._list.begin(); it != other._list.end(); ++it)
    {
        this->_list.push_back(*it);
        this->_vector.push_back(other._vector[vectorIndex++]);
    }
}

PmergeMe&   PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        int vectorIndex = 0;
        this->_vector.clear();
        this->_list.clear();
        this->_vector.reserve(other._vector.size());
        for (std::list<int>::const_iterator it = other._list.begin(); it != other._list.end(); ++it)
        {
            this->_list.push_back(*it);
            this->_vector.push_back(other._vector[vectorIndex++]);
        }
    }
    return *this;
}

PmergeMe::~PmergeMe(void) { }

void    PmergeMe::_fillContainer(std::string& numSequence)
{
    long long   integer;
    size_t      forbiddenChars = numSequence.find_first_not_of(" +0123456789");
    if (forbiddenChars != std::string::npos)
        throw std::runtime_error("Error");
    else
    {
        size_t  whitespace = numSequence.find(' ');
        while (1)
        {
            std::stringstream numStream(numSequence.substr(0, whitespace));
            numStream >> integer;
            if (integer == 0  || integer > INT_MAX)
            {
                this->_vector.clear();
                this->_list.clear();
                throw std::runtime_error("Error");
                return ;
            }
            this->_vector.push_back(static_cast<int>(integer));
            this->_list.push_back(static_cast<int>(integer));
            numSequence = numSequence.substr(whitespace + 1);
            if (whitespace == std::string::npos)
                break ;
            whitespace = numSequence.find(' ');
        }
    }
}

void PmergeMe::_vectorMergeSort(int begin, int end)
{
    int mid = (begin + end) / 2;    // Calculer l'index médian du vecteur
    int i = begin;                  // Initialiser 'i' au début de la première moitié du vecteur
    int j = mid + 1;                // Initialiser 'j' au début de la deuxième moitié du vecteur
    int index = 0;                  // Initialiser index pour le vecteur temporaire 'tmp'
    
    std::vector<int> tmp(end - begin + 1);  // Créer un vecteur temporaire 'tmp' avec une taille égale à celle du sous-vecteur

    while (i <= mid && j <= end)            // Fusionner les deux moitiés du vecteur dans 'tmp' en ordre trié
    {
        // Si l'élément à 'i' est plus petit, l'ajouter à 'tmp', sinon ajouter l'élément à 'j'
        if (_vector[i] < _vector[j])
            tmp[index++] = _vector[i++];
        else
            tmp[index++] = _vector[j++];
    }
        // S'il reste des éléments dans la première moitié, les ajouter à 'tmp'
    while (i <= mid)
        tmp[index++] = _vector[i++];
    
        // S'il reste des éléments dans la deuxième moitié, les ajouter à 'tmp'
    while (j <= end)
        tmp[index++] = _vector[j++];
    
        // Copier les éléments triés de 'tmp' dans le vecteur original '_vector'
    for (int i = 0; i < index; ++i)
        _vector[begin + i] = tmp[i];
}


void PmergeMe::vectorFordJohnson(int begin, int end)
{
    if (end <= begin) // vector size 1 or less
        return;
    int mid = (begin + end) / 2;
    vectorFordJohnson(begin, mid);            // sort left half
    vectorFordJohnson(mid + 1, end);          // sort right half
    _vectorMergeSort(begin, end);             // merge
}

int PmergeMe::getVectorSize(void) const { return this->_vector.size(); }

void    PmergeMe::displayVector(unsigned int value) const
{
    if (_vector.empty() ==  true || value == 0)
        return ;
    std::vector<int>::const_iterator    it = _vector.begin();
    std::cout << *it;
    it++;
    for (; it != _vector.end() && --value; ++it)
        std::cout<<" "<<*it;
    if (it != _vector.end())
    {
        std::vector<int>::const_iterator    it1 = _vector.end();
        if (it1 - it > 2)
            std::cout<<" ...";
        for (int i = 0; i < 2 && it1 > it; ++i)
            it1--;
        for (; it1 != _vector.end(); ++it1)
            std::cout<<" "<<*it1;
    }
    std::cout << std::endl;
}

void    PmergeMe::_listMergeSort(int begin, int end)
{
    std::list<int>::iterator    mid = _list.begin();
    std::advance(mid, (begin + end) / 2);
    std::list<int>::iterator    left = _list.begin();
    std::advance(left, begin);
    std::list<int>::iterator    right = mid;
    std::advance(right, 1);
    std::list<int>::iterator    endIt = _list.begin();
    std::advance(endIt, end + 1);
    std::list<int>::iterator    midNext = mid;
    std::advance(midNext, 1);
    
    std::list<int>  tmp;
    while (left != midNext && right != endIt)
    {
        if (*left < *right)
            tmp.push_back(*left++);
        else
            tmp.push_back(*right++);
    }
    while (left != midNext)
        tmp.push_back(*left++);
    while (right != endIt)
        tmp.push_back(*right++);
    left = _list.begin();
    std::advance(left, begin);
    std::list<int>::iterator    tmpIt = tmp.begin();
    while (left != endIt)
        *left++ = *tmpIt++;
}

void PmergeMe::listFordJohnson(int begin, int end)
{
    if (end <= begin)
        return;
    int mid = (begin + end) / 2;
    listFordJohnson(begin, mid);            // sort left half
    listFordJohnson(mid + 1, end);          // sort right half
    _listMergeSort(begin, end);             // merge
}

int PmergeMe::getListSize(void) const {return this->_list.size(); }

void    PmergeMe::displayList(unsigned int value) const
{
    unsigned int val = 10;
    if (_list.empty() == true || value == 0)
        return ;
    std::list<int>::const_iterator  it = _list.begin();
    std::cout << *it;
    it++;
    for (; it != _list.end() && (--val); ++it)
        std::cout<<" " << *it;
    if (it != _list.end())
    {
        std::list<int>::const_iterator  it1 = _list.end();
        if (std::distance(it, it1) > 10)
            std::cout << " [...]";
        for (int i = 0; i < 10 && (std::distance(it, it1) > 0); ++i)
            it1--;
        for (; it1 != _list.end(); ++it1)
            std::cout<<" "<<*it1;
    }
    std::cout << std::endl;
}