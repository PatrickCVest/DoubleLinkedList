#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include <iostream>
#include <vector>
using namespace std;

template <typename dataType>
class doubleLinkedList{
    public:

        doubleLinkedList();

        doubleLinkedList(dataType array[], int size);

        doubleLinkedList(vector<dataType> vector);

        doubleLinkedList(const doubleLinkedList &source);

        void addFront(dataType value);

        void addEnd(dataType value);

        /**
         * @brief Removes the first occurance of value from the linked list
         * 
         * @param value 
         * @returns -1 if the value was not in the list, 0 otherwise
         */
        int removeValue(dataType value);

        int removeIndex(int index);

        void removeFront();

        void removeEnd();

        /**
         * @brief Inserts the given value into the listList, pushing all other values back. Can take in an index equal to the length of the list, which will append the new item.
         * 
         * @param index 
         * @param value 
         */
        void insert(int index, dataType value);

        dataType& at(int index);

        dataType& operator[](int index);

        bool operator!=(const doubleLinkedList &rightSide);

        bool operator==(const doubleLinkedList &rightSide);

        doubleLinkedList& operator=(const doubleLinkedList &rightSide);

        doubleLinkedList<dataType>& operator=(const vector<dataType> &rightSide);

        doubleLinkedList operator+(const doubleLinkedList &rightSide);

        doubleLinkedList& operator+=(const doubleLinkedList &rightSide);

        template <typename outDataType>
        friend ostream& operator<<(ostream& out, const doubleLinkedList<outDataType> &listToPrint);

        /**
         * @brief Gets the length of the list
         * 
         * @return The length of the list 
         */
        int length();

        /**
         * @brief Checks if the list is empty
         * 
         * @returns true - if the list is empty, false - if the list is not empty
         */
        bool isEmpty();

        /** 
         * @brief Performs a linear search of the DoubleLinkedList looking for item "searchFor".
         * 
         * @param searchValue Element that is seached for.
         * @return Index of first occurance of "searchFor" or -1 if "searchFor" is not found.
         */
        int search(dataType searchValue);
        
        /**
         * @brief Destroys the Double Linked List object
         * 
         */
        ~doubleLinkedList();

        dataType npos = dataType();

    private:
        struct doubleLinkedListNode{
            doubleLinkedListNode* next = nullptr;
            doubleLinkedListNode* previous = nullptr;
            dataType value;
            doubleLinkedListNode(dataType value){
                this->value = value;
            }
        };
        
        doubleLinkedListNode* first = nullptr;
        doubleLinkedListNode* last = nullptr;
        int size = 0;
        bool isEmptyValue = true;

        doubleLinkedListNode* getNodeFrontBack(int index);
};
#endif