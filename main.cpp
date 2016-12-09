#include <iostream>
#include <vector>
#include <iterator>
#include <memory>

class Iterator : public std::iterator<std::input_iterator_tag, int>
{
private:
    std::vector<int>::const_iterator curr;
    std::vector<int>::const_iterator last;
    
public:
    Iterator(const std::vector<int> & nums) {
	curr = nums.begin();
	last = nums.end();
    }

    virtual ~Iterator(){};

    int next() {
	int rtn = *curr;
	++curr;
	return rtn;
    }

    bool hasNext() const {
	return curr != last;
    }
};

class PeekingIterator : public Iterator {
public:
    PeekingIterator(const std::vector<int> & nums)
	: Iterator(nums) {
	currVal = Iterator::next();
	advanced = true;
    }

    // returns the next element in the iteration without advancing the iterator
    int peek() {
	if (!advanced) {
	    currVal = Iterator::next();
	    advanced = true;
	}
	return currVal;
    }

    int next() {
	if (advanced) {
	    advanced = false;
	    return currVal;
	}
	return Iterator::next();
    }

    bool hasNext() const {
	return Iterator::hasNext();
    }

private:
    int currVal;
    bool advanced;
};

int main() {
    std::vector<int> nums{1,2,3};

    PeekingIterator it{nums};
    
    std::cout << "peek = " << it.peek() << std::endl;
    std::cout << "next = " << it.next() << std::endl;
    std::cout << "peek = " << it.peek() << std::endl;
    std::cout << "peek = " << it.peek() << std::endl;
    std::cout << "next = " << it.next() << std::endl;
    std::cout << "peek = " << it.peek() << std::endl;
    std::cout << "next = " << it.next() << std::endl;
    
    std::cout << std::boolalpha << it.hasNext() << std::endl;
}
