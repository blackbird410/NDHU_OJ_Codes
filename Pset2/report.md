# Description
Report on the solutions of the problems of week 2.

## Problem 1
請寫一個程式，讀入一個浮點數，然後分別顯示他的 round off 跟 round down 到小數點後二位的結果

Write a program to read in a floating point number and display the round off and round down to second decimal place of the number.

### Solution provided
* Take the user input and multiply by 100; 
* Display first the round off value by using the **round** function in *math.h* on the number, divide it by 100 use two decimal points when using the float specifier.
* Secondly, the round down value by using the **floor** function also in *math.h* on the number, divide it by 100 use two decimal points when using the float specifier.

## Problem 2
讀入一個四位數，把它反轉後輸出。

Read a 4 digit number, reverse it and display it.

### Solution provided
* Read the integer input from the user
* Initalize an array of characters
* Until the number is 0
    * Add the modulo 10 of the number to the array
    * [Reduce] Divide the number by 10
* End the array with the null character '\0'
* Display the result

### Note
It would have been simpler to add the digits when reading them to a sum variable each time, **but multiply the sum by 10 everytime you are adding a digit.**

## Problem 3
我們可以用兩個點在一維座標上定義一個線段，請寫一隻程式決定兩個線段是否重疊。

We use two points to present a segment in one dimensional coordinates. Give you two segment, your job is to determine two segment are overlay or not.

### Solution provided 
* Sort the points of the segments in ascending order by swapping them when necessary.
* If the endpoint of the first segment is greater than the starting point of the second segment, then they are overlay, otherwise NO.

### Note
This algorithm passed the test cases of the online judge but there is one test case that it will not work for. 

## Problem 4
三個線段的長度分別為 a b c ，c為最大值，如果 a + b > c 則三個線段可以構成一個三角形。如果 a * a + b * b = c * c 我們稱這樣的三角形為直角三角形，如果 a * a + b * b > c * c 則為銳角三角形，如果 a * a + b * b < c * c 則為鈍角三角形，請寫一個程式判斷三個線段是否能構成一個三角形，如果可以又是怎樣的三角形。

Three segment length a, b, c, c has maximum length, if a + b > c than these three segment can construct a triangle. If a * a + b * b = c * c it will be a "right triangle", if a * a + b * b > c * c it will be a "acute triangle", if a * a + b * b < c * c it will be a "obtuse triangle". Write a program to determine what kind of triangle it will be.

### Solution provided
* First check if we can construct a triangle
* If possible, check the conditions for each type of triangle described as follows:
    - Right angle triangle : $a^2 + b^2 = c^2$
    - Acute triangle : $a^2 + b^2 > c^2$
    - else Obtuse triangle