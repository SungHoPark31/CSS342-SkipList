

/*
 skiplist.h
 Assignment4
 
 Description: In this program, we created a Skip List data structure to store integers.
 When searching a Skip List, items can be found in O(log n) time. No duplicates are allowed.
 A SkipList can have multiple levels. SkipList of depth 1 is similar to a doubly linked list. All
 elements are inserted into a single doubly linked list. When a SkipListhas multiple levels,
 all elements are inserted at level = 0. 50% of those inserted at level = 0, are also inserted
 at level = 1. 50% of those inserted at level = 1 are also inserted at level = 2, and so on.
 
 Created by Sung Ho Park on 11/6/19
 Copyright © 2019 Sung Ho Park. All rights reserved.
 */

#ifndef skiplist_h
#define skiplist_h

#include <stdio.h>
#include <iostream>
#include <limits>
#include <stdio.h>

using namespace std;

class SkipList
{
    /*
     This is the friend function. The purpose of this function is to display the
     private instance variables in this class.
     */
    friend ostream &operator<<(ostream &os, const SkipList &list);

public:
    /*
     Description: default SkipList has depth of 1, just one doubly-linked list
     
     Precondition: The value bring passed in is a integer value and is a valid
     value.
     
     Postcondition: Creates a doubly linked list with a depth of the number
     passed in.
     */
    explicit SkipList(int depth = 1);

    /*
     Description: Destroys everything in the list and destroys the list.
     
     Precondition: The object is created.
     
     Postcondition: Destroys everything in the list and destroys the
     object.
     */
    virtual ~SkipList();

    /*
     Description: Adds the value being passed in and orders the list.
     
     Precondition: The value bring passed in is a integer value and is a valid
     value.
     Postcondition: Return true if successfully added, no duplicates.
     */
    bool Add(int d);

    /*
     Description: Removes the value being passed in.
     
     Precondition: The value bring passed in is a integer value and is a valid
     value.
     Postcondition: Return true if successfully removed.
     */
    bool Remove(int d);

    // return true if found in SkipList
    bool Contains(int d);
    
private:
    class SNode
    {
    public:
        
        /*
         Description: Constructor for SNode
         
         Precondition: The data bring passed in is a integer value and is a valid
         value.
         
         Postcondition: Set the data, set all other pointers to nullptr
         */
        explicit SNode(int d)
        {
            data = d;
            next = nullptr;
            prev = nullptr;
            upLevel = nullptr;
            downLevel = nullptr;
        }
        
        // data for SNode
        int data;

        // link to next SNode
        SNode *next;

        // link to prev SNode
        SNode *prev;

        // link to up one level
        SNode *upLevel;

        // link to down one level
        SNode *downLevel;

        friend class SkipList;
    };
    // depth of SkipList, levels are 0 to depth-1
    int depth;
        
    // array of depth SNode* objects as frontGuards linking levels
    // if depth = 2, we'd have frontGuards[0] and frontGuards[1]
    SNode **frontGuards;

    // array of depth SNode* objects as rearGuards linking levels
    SNode **rearGuards;
    
    // given a SNode, place it before the given NextNode
    void addBefore(SNode *newNode, SNode *nextNode);

    // return true 50% of time,
    // each node has a 50% chance of being at higher level
    bool alsoHigher() const;
    
};

#endif /* skiplist_h */
