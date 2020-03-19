//
//  skiplist.cpp
//  Assignment4
//  This is the implementation of skiplist.h
//
//  Created by Sung Ho Park on 11/6/19.
//  Copyright © 2019 Sung Ho Park. All rights reserved.
//

#include "skiplist.h"
#include <iostream>
#include <random>
#include <climits>
#include <stdio.h>

using namespace std;

SkipList::SkipList(int theDepth)
{
    depth = theDepth;
    //Dynamically allocate the guards with the depth
    frontGuards = new SNode*[depth];
    rearGuards = new SNode*[depth];
    
    //For each depth...
    for(int i = 0; i < depth; i++)
    {
        //Have the node min and max
        SNode* ptr1 = new SNode(INT_MIN);
        SNode* ptr2 = new SNode(INT_MAX);
        
        //Point to that node that has min and max
        frontGuards[i] = ptr1;
        rearGuards[i] = ptr2;
        
        //Have the next and previous
        frontGuards[i]->next = rearGuards[i];
        rearGuards[i]->prev = frontGuards[i];
        
        
        //Connect the upper level and the down level
        frontGuards[i]->upLevel = frontGuards[i + 1];
        frontGuards[i]->downLevel = frontGuards[i - 1];
        rearGuards[i]->upLevel = rearGuards[i + 1];
        rearGuards[i]->downLevel = rearGuards[i - 1];
        
    }
}

SkipList::~SkipList()
{
    //For each level...
    for(int i = 0; i < depth; i++)
    {
        //...Delete the node inside the array...
        SNode* temp = frontGuards[i];
        
        //Save the next node after current.
        SNode* current = temp->next;
        
        //Set every pointer to null
        temp->next = nullptr;
        temp->prev = nullptr;
        temp->downLevel = nullptr;
        temp->upLevel = nullptr;
        
        //Then delete temp.
        delete temp;
        
        //... then delete the nodes in between.
        while(current->next != nullptr)
        {
            SNode* temp = current->next;
            current->next = temp->next;
            
            //Then delete temp.
            delete temp;
            //Set every pointer to null
            temp->next = nullptr;
            temp->prev = nullptr;
            temp->downLevel = nullptr;
            temp->upLevel = nullptr;
            
        }
        //Once it exits, the current is the rearGuard array.
        //Delete that.
        
        rearGuards[i]->next = nullptr;
        rearGuards[i]->upLevel = nullptr;
        rearGuards[i]->downLevel = nullptr;
        delete current;
    }
    
    //Delete the pointers to the array.
    delete[] frontGuards;
    delete[] rearGuards;
} 

bool SkipList::Add(int d)
{
    //Layer correlates to depth.
    int layer = 0;
    
    //Set SNode*, such nextNode to be frontGuards[0]->next.
    //We know that nothing can come before the frontGuards[0],
    //so the nextNode from the one we will insert should be at
    //least frontGuards[0]->next
    SNode* nextNode = frontGuards[0]->next;

    //As long as nextNode->next is not null
    //and nextNode->data < data, keep moving nextNode to the right
    while(nextNode->next != NULL && nextNode->data < d)
    {
        nextNode = nextNode->next;
    }
    //No duplicates
    if(nextNode->data == d)
    {
        return false;
    }
    
    //If not, create a new SNode called newNode, put the data in
    //it and call addBefore(newNode, nextNode)
    //to connect all the pointers together.
    SNode* newNode = new SNode(d);
    addBefore(newNode, nextNode);
    
    //If there is more levels...
    if(depth > 1)
    {
        //If alsoHigher is true and that 50% chance of being
        //at the higher level is true.
        bool coinToss = alsoHigher();
        
        while(coinToss == true && layer < depth - 1)
        {
            layer++;
            //Create another node to be inserted at the higher level
            SNode* newUpper = new SNode(newNode->data);
            newNode->upLevel = newUpper;
            newUpper->downLevel = newNode;

            //Starting from newNode that was inserted, keep going back,
            //until you've reached INT_MIN or a valid upLevel link
            while((newNode->prev != NULL))
            {
                newNode = newNode->prev;
            }
        
            //Go up one level
            SNode* nextUpper = frontGuards[layer]->next;
        
            //Go towards INT_MAX and if the next is not NULL
            //and nextUpper->data < newUpper->data, keep moving nextUpper to the right
            while(nextUpper->data != INT_MAX
                  && nextUpper->data < newUpper->data)
            {
                nextUpper = nextUpper->next;
            }
            
            //Set the newUpper to newNode to update newNode for the next level
            //(only if the coinToss is true)
            newNode = newUpper;
        
            //Then, add newUpper before the nextUpper
            addBefore(newNode, nextUpper);

            //Toss again to see if it can go higher in level
            coinToss = alsoHigher();
        }
    }
    return true;
}

void SkipList::addBefore(SNode *newNode, SNode *nextNode)
{
    //Make a temporary variable that has the previous Node of
    //nextNode
    SNode* temp = nextNode->prev;
    
    //Set the nextNode->prev to the newNode and set the newNode->next
    //to the nextNode
    nextNode->prev = newNode;
    newNode->next = nextNode;
    
    //Set the newNode->prev to the temp and set the temp->next
    //to the newNode;
    newNode->prev = temp;
    temp->next = newNode;
}

bool SkipList::Contains(int d)
{
    //Start at top-left, highest level frontGuards[depth-1],
    //let's call this node current
    int layers = depth - 1;
    SNode* current = frontGuards[layers];
    
    //As long as current is not nullptr...
    while(current != nullptr && layers > -1)
    {
        //In case some number in between frontGuards[depth -1]
        //and current->next->data needs to be searched.
    
        //Keep moving right as long as the
        //current->next->data is less than value
        while(current->next->data < d)
        {
            current = current->next;
        }
        
        //If current->next->data is equal to d, return true.
        if(current->next->data == d)
        {
            return true;
        }
        //else set current to be the node down one
        //level from current node
        else
        {
            current = current->downLevel;
            layers--;
        }
    }
    
    //If current is nullptr, the item is not in SkipList
    if(current == nullptr)
    {
        return false;
    }
    return false;
}

bool SkipList::Remove(int d)
{
    //Basically the same implementation as the contains.
    int layers = depth - 1;
    SNode* deleteN = frontGuards[layers];
    while(deleteN != nullptr && layers > -1)
    {
        while(deleteN->next->data < d)
        {
            deleteN = deleteN->next;
        }
        //Once the value is found...
        if(deleteN->next->data == d)
        {
            //...Check to see if the down level is not null.
            while(deleteN->next->downLevel != nullptr)
            {
                //Make temporary variables for deletion.
                SNode* tempDelete = deleteN->next;
                SNode* nextTemp = tempDelete->next;
                
                //Disconnect the links and reconnect without
                //the value.
                deleteN->next = nextTemp;
                nextTemp->prev = deleteN;
                
                //Go down a level
                deleteN = deleteN->downLevel;
                
                //Delete that value
                tempDelete->downLevel = nullptr;
                tempDelete->next = nullptr;
                tempDelete->prev = nullptr;
                tempDelete->downLevel = nullptr;
                delete tempDelete;
                
                //Check to see if the downlevel next is the value.
                while(deleteN->next->data < d)
                {
                    //If not, go right.
                    deleteN = deleteN->next;
                }
            }
            //This is for the last level because of...
            //...while(deleteN->next->downLevel != nullptr) call.
            SNode* tempDelete = deleteN->next;
            SNode* nextTemp = tempDelete->next;

            deleteN->next = nextTemp;
            nextTemp->prev = deleteN;

            deleteN = deleteN->downLevel;
            delete tempDelete;
            
            //Do the same thing and delete the value in the last level.
            //Return true if its all good.
            return true;
        }
        else
        {
            deleteN = deleteN->downLevel;
            layers--;
        }
    }
    if(deleteN == nullptr)
    {
        return false;
    }
    return false;
}

ostream &operator<<(ostream &os, const SkipList &list)
{
    //For each depth,
    os << "Skiplist: \n";
    
    for(int i = list.depth - 1; i > -1; i--)
    {
        //...have a head and a rear
        SkipList::SNode* head = list.frontGuards[i];
        SkipList::SNode* rear = list.rearGuards[i];
        os << "Level " << i << ": ";

        //As long as the head is not equal to the rear
        while(head->data != rear->data)
        {
            //Print out the head
            os << head->data << ", ";
            //Traverse
            head = head->next;
        }
        os << rear->data;
        os << endl;
    }
    return os;
}

bool SkipList::alsoHigher() const
{
    //If a random number is odd, then return true,
    //otherwise, return false.
    if((rand() % 2) == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
