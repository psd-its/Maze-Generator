#include <vector>
#include <algorithm>
#include <stdexcept>
#include <climits>
#include "../constants/constants.h"

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

// Template for our binary heap
using namespace mazer2016sp1oua;
template <class T>
class heap
{
    private:
        // Data structure that holds the heap
        std::vector<T> _arr;
        // get left child of n
        constexpr int l_child(int n)
        {
            return n * 2 + 1;
        }
        // get right child of n
        constexpr int r_child(int n)
        {
            return l_child(n) + 1;
        }
		// sort to maintain a min heap
        void sort(int index)
        {
            int length = _arr.size();
            int left = l_child(index);
            int right = r_child(index);
            // exit the sort 
            if(left >= length)
                return; 
            
            int min = index;

            // node is bigger then left child
            if(_arr[index] > _arr[left])
            {
                min = left;
            }
            // node is bigger then right child
            if((right < length) && (_arr[min] > _arr[right]))
            {
                min = right;
            }

            // need to swap nodes
            if(min != index)
            {
                T temp = _arr[index];
                _arr[index] = _arr[min];
                _arr[min] = temp;
                sort(min);
            }
        }
		
    public:
        // Constructor from an existing vector
        heap<T>(std::vector<T>& vector) : _arr(vector)
        {
            for (unsigned int i = _arr.size()-1; i >= 0; --i)
            {
                sort(i);
            }
        }
        // Default constructor
        heap<T>()
        {
        }
        // Get the start of the heap
        T front()
        {
            if (_arr.empty())
            {
                throw std::out_of_range("heap::front(): Heap is empty");
            }
            return _arr.front();    
        }
        //Delete the first element
        void pop()
        {
            if (_arr.empty())
            {
                throw std::out_of_range("heap::pop(): Heap is empty");
            }
            _arr.erase(_arr.begin() + constants::START);
            sort(constants::START);
        }
        // Insert an element into the heap
        void push(T t)
        {
            _arr.insert(_arr.begin(), t);
            sort(constants::START);
        }
        // Returns true if heap is empty
        bool empty()
        {
            return _arr.empty();
        }
		// get the size of the heap
        int size()
        {
            return _arr.size();
        }

};


