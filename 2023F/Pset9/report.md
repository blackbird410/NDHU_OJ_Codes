# Description

Report on the solutions of the problems of week 9.

## Problem 1

There is a pointer p pointing to a block of memory contains an int, a char and a float inside respectively and keep the order as description.

Write a segment of code to display the value of them.

### Solution provided

- Display the values in memory by dereferencing the pointer for each value, but adding the shift value to the adress of the pointer to find the correct address:
  - Add the size of an integer datatype to find the address of the character value
  - Add the size of an integer plus the size of a character datatype to find the float value

## Problem 2

There is a pointer p pointing to a 2D int array with size 9 by 7.

Please write a segment of code to display the value of element in row 0 column 4 and element in row 4 column 3.

### Solution provided

Because the pointer is the the integer datatype, therefore the compiler already know when we increment the pointer that we are asking it to shift the address in memory to the size of an integer.

- To display the first value, add the value 4 to the pointer, it will shift the address in the pointer by 4 \* 4 bytes.
- To display the second value, add 4 \* 7 + 3 to the pointer to find the correct address.

## Problem 3

There are two pointers _str_ and _key_ both pointing to string.

Please write a code to count the number of time that _key_ appear in _str_.

For example, if _str_ point to "banana" and key point to "ana", then _key_ appear twice in _str_.

### Solution provided

- Use an integer variable to parse the string by adding this value the pointer _str_ and dereferencing it everytime to check if we arrive at the end of the string.
- The count (j) starts at every position of the string and stops when a character is different than the one in _key_ or if we have parsed every character in the _key_
- After parsing the _key_ string each time, if we have arrived at the end of it we increase the counter.
- Lastly return the counter.

## Problem 4

There is a pointer _str_ pointing to a string that consists some integers.

Write a segment of code to sum up all integers in _str_.

For example, _str_ "Average value is 12.33." contains 2 integers 12 and 33, thus the answer should be 45.

### Solution provided

- Initialize a _sum_ and _n_ variable
- Use a variable _i_ to parse the string by adding it to the pointer
- When the character of a number is found, multiply _n_ by 10, add the number value to _n_.
- When other characters are found and if _n_ is not 0, add _n_ to _sum_ and set _n_ to 0.
- Display **sum + n** because it is possible that the last value of _n_ is not 0.

## Problem 5

There are two pointers a and b both pointing to an integer.

Write a segment of code to find the summation of all integer after pointer a and before pointer b , include a but not b.

### Solution provided

- Initialize a sum to 0
- Use an integer variable i to parse memory between a and b while adding the values between and checking the address the pointer is pointing to is different than b.
- Add the values in memory by dereferencing the address the pointer is currently pointing to.
