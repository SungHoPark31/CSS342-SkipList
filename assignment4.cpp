//
//  main.cpp
//  skiplist
//
//  Created by Sung Ho Park on 11/6/19.
//  Copyright © 2019 Sung Ho Park. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "skiplist.h"

using namespace std;

void Test1()
{
    //Test all 5 levels
    cout << "-------------------TEST ";
    cout << "1----------------------" << endl;
    SkipList s(5);

    for (int i = 0; i < 10; i++)
    {
        int num = rand() % 100;
        s.Add(num);
        cout << "After adding " << num << endl;
        cout << s << endl;
    }
    //Prints out 1 because it is true.
    cout << "True = 1, False = 0: " << endl;
    cout << s.Contains(7) << endl;
    cout << s.Contains(65) << endl;
    cout << s.Contains(30) << endl;
    cout << s.Contains(44) << endl;
   
    //Print out 0 because it is false.
    cout << s.Contains(100) << endl;
    cout << s.Contains(80) << endl;
    cout << s.Contains(32) << endl;
    cout << s.Contains(3)<< endl;
    
    s.Remove(7);
    cout << "Removing 7: " << endl;
    cout << s << endl;
    
    s.Remove(33);
    cout << "Removing 33: " << endl;
    cout << s << endl;
    
    s.Remove(12);
    cout << "Removing 12: " << endl;
    cout << s << endl;
}

void Test2()
{
    //Test all 4 levels
    cout << "-------------------TEST ";
    cout << "2----------------------" << endl;
    SkipList s(4);

    for (int i = 0; i < 20; i++)
    {
        int num = rand() % 100;
        s.Add(num);
        cout << "After adding " << num << endl;
        cout << s << endl;
    }
     //Prints out 1 because it is true.
     cout << "True = 1, False = 0: " << endl;
     cout << s.Contains(33) << endl;
     cout << s.Contains(67) << endl;
    
    
     //Print out 0 because it is false.
     cout << s.Contains(100) << endl;
     cout << s.Contains(80)<< endl;
     cout << s.Contains(32) << endl;
     cout << s.Contains(2) << endl;
     
     s.Remove(33);
     cout << "Removing 33: " << endl;
     cout << s << endl;
     
     s.Remove(96);
     cout << "Removing 96: " << endl;
     cout << s << endl;
     
     s.Remove(63);
     cout << "Removing 63: " << endl;
     cout << s << endl;
}

void Test3()
{
    //Test all 3 levels
    cout << "-------------------TEST ";
    cout << "3----------------------" << endl;
    SkipList s(3);

    for (int i = 0; i < 5; i++)
    {
        int num = rand() % 100;
        s.Add(num);
        cout << "After adding " << num << endl;
        cout << s << endl;
    }
    
    cout << "Deleting 44: " << endl;
    s.Remove(44);
    cout << s << endl;
    
}
void Test4()
{
    //Test all 5 levels
    cout << "-------------------TEST ";
    cout << "4----------------------" << endl;
    SkipList s(2);

    for (int i = 0; i < 35; i++)
    {
        int num = rand() % 100;
        s.Add(num);
        cout << "After adding " << num << endl;
        cout << s << endl;
    }
    s.Remove(1);
    cout << "Removing 1: " << endl;
    cout << s << endl;
    
    s.Remove(21);
    cout << "Removing 21: " << endl;
    cout << s << endl;
    
    s.Remove(33);
    cout << "Removing 33: " << endl;
    cout << s << endl;
}

void Test5()
{
    //Test all 5 levels
    cout << "-------------------TEST ";
    cout << "5----------------------" << endl;
    SkipList s(1);

    for (int i = 0; i < 15; i++)
    {
        int num = rand() % 100;
        s.Add(num);
        cout << "After adding " << num << endl;
        cout << s << endl;
    }
     //Prints out 1 because it is true.
    cout << "True = 1, False = 0: " << endl;
     cout << s.Contains(44) << endl;
    
    cout << "Deleting 23: " << endl;
    s.Remove(23);
    cout << s << endl;
}

void Test6()
{
    //Test all 5 levels
    cout << "-------------------TEST ";
    cout << "6----------------------" << endl;
    SkipList s(5);

    for (int i = 0; i < 15; i++)
    {
        int num = rand() % 100;
        s.Add(num);
        cout << "After adding " << num << endl;
        cout << s << endl;
        cout << "Now Deleting " << num << endl;
        s.Remove(num);
        cout << s << endl;
    }
    
    cout << "Now List should be empty but the Guards: " << endl;
    cout << s << endl;
}

int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();

    cout << "Done!" << endl;
    return 0;
}
