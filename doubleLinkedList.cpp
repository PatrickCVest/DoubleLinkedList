#include <iostream>
#include<vector>
#include "doubleLinkedList.h"
using namespace std;

template <typename dataType>
doubleLinkedList<dataType>::doubleLinkedList(){
    //this doesn't have to do anything
}

template <typename dataType>
doubleLinkedList<dataType>::doubleLinkedList(dataType array[], int size){
    for (int i = 0; i < size; i++){
        this->addEnd(array[i]);
    }
}

template <typename dataType>
doubleLinkedList<dataType>::doubleLinkedList(vector<dataType> vector){
    for (int i = 0; i < vector.size(); i++){
        addEnd(vector.at(i));
    }
}

template <typename dataType>
doubleLinkedList<dataType>::doubleLinkedList(const doubleLinkedList &source){
    for (doubleLinkedListNode* iterator = source.first; iterator; iterator = iterator->next){
        addEnd(iterator->value);
    }
}

template <typename dataType>
void doubleLinkedList<dataType>::addFront(dataType value){
    if (isEmptyValue){
        first = new doubleLinkedListNode(value);
        last = first;
        isEmptyValue = false;
        size++;
    }
    else{
        first->previous = new doubleLinkedListNode(value);
        first->previous->next = first;
        first = first->previous;
        size++;
    }
}

template <typename dataType>
void doubleLinkedList<dataType>::addEnd(dataType value){
    if (isEmptyValue){
        first = new doubleLinkedListNode(value);
        last = first;
        isEmptyValue = false;
        size++;
    }
    else{
        last->next = new doubleLinkedListNode(value);
        last->next->previous = last;
        last = last->next;
        size++;
    }
}

template <typename dataType>
int doubleLinkedList<dataType>::removeValue(dataType value){
    for (doubleLinkedListNode* iterator = first; iterator; iterator = iterator->next){
        if (iterator->value == value){
            if (iterator == last){
                removeEnd();
                return 0;
            }
            iterator->previous->next = iterator->next;
            iterator->next->previous = iterator->previous;
            delete iterator;
            size--;
            if (size == 0){
                isEmptyValue = true;
            }
            return 0;
        }
    }
    return -1;
}

template <typename dataType>
int doubleLinkedList<dataType>::removeIndex(int index){
    if (index >= size || index < 0){
        return -1;
    }
    if (index == 0){
        removeFront();
        return 0;
    }
    if (index == size - 1){
        removeEnd();
        return 0;
    }
    doubleLinkedListNode* removeMe = getNodeFrontBack(index);
    removeMe->previous->next = removeMe->next;
    removeMe->next->previous = removeMe->previous;
    delete removeMe;
    size--;
    return 0;
}

template <typename dataType>
void doubleLinkedList<dataType>::removeFront(){
    if (size == 0){
        return;
    }
    if (size == 1){
        this->~doubleLinkedList();
        return;
    }
    doubleLinkedListNode* temp = first;
    first = first->next;
    first->previous = nullptr;
    delete temp;
    size--;
    if (size == 0){
        isEmptyValue = true;
    }
}

template <typename dataType>
void doubleLinkedList<dataType>::removeEnd(){
    if (size == 0){
        return;
    }
    if (size == 1){
        this->~doubleLinkedList();
        return;
    }
    doubleLinkedListNode* temp = last;
    last = last->previous;
    last->next = nullptr;
    delete temp;
    size--;
    if (size == 0){
        isEmptyValue = true;
    }
    
}

template <typename dataType>
void doubleLinkedList<dataType>::insert(int index, dataType value){
    if (index > size){
        cout << "Index: " << index << " out of bound for linked list of size: " << size << '\n';
        return;
    }
    if (index == 0){
        addFront(value);
        return;
    }
    if (index == size){
        addEnd(value);
        return;
    }
    if (index == size-1){
        doubleLinkedListNode* insertValue = new doubleLinkedListNode(value);
        insertValue->next = last;
        insertValue->previous = last->previous;
        last->previous->next = insertValue;
        return;
    }
    doubleLinkedListNode* pushBack = getNodeFrontBack(index);
    doubleLinkedListNode* insertValue = new doubleLinkedListNode(value);
    insertValue->next = pushBack;
    insertValue->previous = pushBack->previous;
    pushBack->previous->next = insertValue;
    pushBack->next->previous = insertValue;
    return;
}

template <typename dataType>
typename doubleLinkedList<dataType>::doubleLinkedListNode* doubleLinkedList<dataType>::getNodeFrontBack(int index){
    doubleLinkedListNode* iterator;
    int count = 0;
    if (index < size / 2){
        for (iterator = first; count < index; iterator = iterator = iterator->next){
            count++;
        }
    }
    else{
        for (iterator = last; count < size - index - 1; iterator = iterator->previous){
            count++;
        }
    }
    return iterator;
}

template <typename dataType>
dataType& doubleLinkedList<dataType>::at(int index){
    if (index >= size || index < 0){
        cout << "Index: " << index << " out of bound for linked list of size: " << size << '\n';
        return npos;
    }
    return getNodeFrontBack(index)->value;
}

//overload assignment= for array

template <typename dataType>
dataType& doubleLinkedList<dataType>::operator[](int index){
    return this->at(index); 
}

template <typename dataType>
bool doubleLinkedList<dataType>::operator!=(const doubleLinkedList &rightSide){
    return !(*this == rightSide);
}

template <typename dataType>
bool doubleLinkedList<dataType>::operator==(const doubleLinkedList &rightSide){
    if (this->size != rightSide.size){
        return false;
    }
    doubleLinkedListNode* leftIterator = this->first;
    doubleLinkedListNode* rightIterator = rightSide.first;
    while (leftIterator && rightIterator){
        if (leftIterator->value != rightIterator->value){
            return false;
        }
        leftIterator = leftIterator->next;
        rightIterator = rightIterator->next;
    } 
    return true;
}

template <typename dataType>
doubleLinkedList<dataType>& doubleLinkedList<dataType>::operator=(const doubleLinkedList &rightSide){
    this->~doubleLinkedList();
    for (doubleLinkedListNode* iterator = rightSide.first; iterator; iterator = iterator->next){
        addEnd(iterator->value);
    }
    return *this;
}

template <typename dataType>
doubleLinkedList<dataType> doubleLinkedList<dataType>::operator+(const doubleLinkedList &rightSide){
    doubleLinkedList returnList = *this;
    for (doubleLinkedListNode* iterator = rightSide.first; iterator; iterator = iterator->next){
        returnList.addEnd(iterator->value);
    }
    return returnList;
}

template <typename dataType>
doubleLinkedList<dataType>& doubleLinkedList<dataType>::operator+=(const doubleLinkedList &rightSide){
    for (doubleLinkedListNode* iterator = rightSide.first; iterator; iterator = iterator->next){
        addEnd(iterator->value);
    }
    return *this;
}

template <typename outDataType>
ostream& operator<<(ostream& out, const doubleLinkedList<outDataType> &listToPrint){
    out << '[';
    for (typename doubleLinkedList<outDataType>::doubleLinkedListNode* iterator = listToPrint.first; iterator; iterator = iterator->next){
        if (iterator != listToPrint.last)
            out << iterator->value << ", ";
        else
            out << iterator->value;
    }
    out << ']';
    return out;
}

template <typename dataType>
int doubleLinkedList<dataType>::length(){
    return size;
}

template <typename dataType>
bool doubleLinkedList<dataType>::isEmpty(){
    return isEmptyValue;
}

template <typename dataType>
int doubleLinkedList<dataType>::search(dataType searchValue){
    int i = 0;
    for (doubleLinkedListNode* iterator = first; iterator; iterator = iterator->next){
        if (iterator->value == searchValue){
            return i;
        }
        i++;
    }
    return -1;
}

template <typename dataType>
doubleLinkedList<dataType>::~doubleLinkedList(){
    doubleLinkedListNode* iterator = this->first;
    doubleLinkedListNode* temp;
    while (iterator){
        temp = iterator;
        iterator = iterator->next;
        delete temp;
    }
    size = 0;
    isEmptyValue = true;
    first = last = nullptr;
}