													CSE-106
							  				  Assignment on Stack


------------------

In this assignment the task was to 
1. Define a Stack ADT.
2. Implement the stack using dynamic arrays.
3. Implement the stack using linked lists.
4. Test implementations for correctness.

------------------

1) Define a Stack ADT: The abstract class Stack was already provided in the file stack.h. It contained the required methods definitions. So i didn't have to modify this file and didn't have to write any code.

------------------

2) ArrayStack Implementation: The skeleton code of arraystack.cpp was given. I had to deallocate and allocate the array properly and had to ensure there were no memory leak. Also wrote the function for dynamically changing the array size. Edge cases were handled gracefully. Push,pop,top,size,empty,clear,print functions were created. It was made sure that array capacity couldn't be less than 10.

------------------

3) ListStack Implementations: The skeleton code for liststack.cpp was provided. Constructor and destructor were created for proper memory allocation and deallocation. Edge cases were handled gracefully. Push,pop,top,size,empty,clear,print functions were created. Nodes were inserted at the head of the list for efficient operations. 

------------------

4) Testing: A testing framework was provided.As instructed i didn't modify the framework itself.My task was to implement individual test cases to test if the stack implementations worked properly.
3 testing methods were provided. I had top code for test_size(), test_empty(), test_clear(), test_multiple_push_pop(), test_empty_operations(), test_array_resizing(), test_stress(). I think i could not implement test_array_resizing() properly as i was not allowed to change stack.h or use new functions in arraystack.cpp

------------------

For Compiling and Running: 
 g++ test.cpp arraystack.cpp liststack.cpp -o test.exe
 .\test.exe
commands were added in the terminal

------------------

All 20 tests were passed and there were no errors.	

------------------

Name: Sadman Zaman
ID: 2305075
CSE -23 Section: B (B1)	