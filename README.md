# CSS342-SkipList
Working with dynamic arrays, pointers, doubly linked lists.

For this assignment, you will write a Skip List data structure 
to store integers. When searching a Skip List, items can be found 
in ​O(log n)​ time. No duplicates are allowed.

A ​SkipList​ can have multiple levels. ​SkipList​ of depth 1 
is similar to a doubly linked list. All elements are inserted 
into a single doubly linked list.

When a ​SkipList​has multiple levels, all elements are inserted at 
level = 0. 50% of those inserted at level = 0, are also inserted at
level = 1. 50% of those inserted at level = 1 are also inserted at 
level = 2, and so on.

