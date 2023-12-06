#include <string>
using namespace std;

#include "rotate-array.h"

RotatableArray :: RotatableArray()
{
    data = new int[DEFAULT_CAPACITY];
    capacity = DEFAULT_CAPACITY;
    size = 0;
}

RotatableArray :: RotatableArray (const RotatableArray& copy)
{
    size = copy.size;
    capacity = copy.capacity;
    for (int i = 0; i < capacity; i++)
    {
        data[i] = copy.data[i];
    }
}

RotatableArray :: RotatableArray (RotatableArray&& move)
{
    size = move.size;
    capacity = move.capacity;
    data = move.data;
    move.data = nullptr;
}

RotatableArray& RotatableArray :: operator=(const RotatableArray& copy)
{
    delete[] data;
    size = copy.size;
    capacity = copy.capacity;
    data = new int[capacity];
    for(int i = 0; i < size; i++)
        data[i] = copy.data[i];
    return *this;
}

RotatableArray& RotatableArray :: operator=(RotatableArray&& move)
{
    delete[] data;
    size = move.size;
    capacity = move.capacity;
    data = move.data;
    move.data = nullptr;
    return *this;

}

RotatableArray::~RotatableArray()
{
    delete data;
}

void RotatableArray::push_back(int element)
{
    if(size >= capacity)
    {
        capacity *= 2;
    }
    data[size] = element;
    size++;
}

int RotatableArray::pop_back()
{
    if(size > 0)
    {
        size--;
    }
    else if(size==0)
        return 0;
    return *this -> data;
}

int RotatableArray :: operator[](int index) const
{
    return data[index];
}

int &RotatableArray :: operator[](int index)
{
    return data[index];
}
//NOT DONE 

void RotatableArray::rotate(int rotateNumber)
{
    //range of int: -(size - 1) to (size - 1)
    //positive arguments rotate to the right
    //negative arguments rotate to the left
    if(rotateNumber >= -(size - 1) || rotateNumber <= (size - 1))
    {
        if(rotateNumber > 0)
        {
            rotateNumber = size - rotateNumber;//rotate n element to the right is same to rotate (size - n) element to the left.
        }
        else if(rotateNumber < 0)
        {
            rotateNumber *= (-1);//rotate to the left n elements.
        }
        //store the elements rotate in array to temp array;
        int *temp = new int[rotateNumber];
        //copy n element to the temp array
        for(int i = 0; i < rotateNumber; i++)
        {
            temp[i] = data[i];
        }
        //assign the value of array elements to the next rotateNumber
        for (int i = 0; i < rotateNumber; i++)
        {
            data[i] = data[i + rotateNumber];
        }
        //put the temp to the back of array
        for(int i = size - rotateNumber; i < size; i++)
        {
            data[i] = temp[i - (size - rotateNumber)];
        }     
    }
}

ostream& operator <<(ostream& out, const RotatableArray& myarray)
{
    for(int i = 0; i < myarray.getSize(); i++)
    {
        out << myarray.data[i] << " ";
    }    
    return out;
}