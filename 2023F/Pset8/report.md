# Description

Report on the solutions of the problems of week 8.

## Problem 1

Write a program to read the compressed matrix and print out the original matrix.

### Solution provided

- Create a two dimensional array of size of at least 100 and initialize all values of the array to 0
- Take the dimensions of the matrix and the number of values in the sparse matrix
- As you are taking the inputs, store them in the two dimensional array while considering the first input as row, the second as column and the last as the value at the specified coordinates.
- Lastly output the array

## Problem 2

Give you a 2-D array represent a maze, in this maze, 1 is wall and 0 is a space you can walk on. You can move 4 direction, up, down, left and right.
Write a program to see if a maze has a way from start to the end.

### Solution provided

As the task at hand is to verify whether there is a path or not inside the maze, it became innefficient to travel the maze and find the path as a human being would instinctively do.
Here the flood fill algorithm is more efficient, because we only need to check in a more abstract way, if water is flooded at the starting location of the maze, will it reach the exit.

### The flood fill algorithm applied to the maze

- Starts by marking the entrance
- Set a flag to 1 before entering the loop
- Set the flag to 0 after entering the loop
- Stop the parsing if the flag returned to the loop condition is 0
- Parse the rest of the column and for each position:
  - If the current position has been marked already or it is a wall, skip it;
  - Else if the current position is a space that has a direct neighbor marked, mark it and set the flag to 1 to mark a change
- If there is no change in while parsing the maze, the loop will stop
- If at the end the exit is of the maze if marked, then there is a path, otherwise no.

## Problem 3

Give you a matrix. Please output the elements in clockwise spiral order.

### Solution provided

- Take the matrix in a two dimensional array of a size at least 100 x 100
- Walk in the array from the first element at (0, 0) in clockwise direction by following this pattern:
  - Display the current element
  - Mark it as you are leaving it
  - Find the direction to go if it is safe, considering this pattern:
    - If you were going RIGHT and it is not SAFE (out of boundary or null) to keep going RIGHT, go DOWN.
    - Else if you were going DOWN and it is is not SAFE to keep going DOWN, go LEFT.
    - Else if you were going LEFT and it is not SAFE to keep going LEFT, go UP.
    - Else if you were going UP and it is not SAFE to keep going UP, go RIGHT if it is SAFE, otherwise that's the END.

#### Note

- I used the recursive method because we are doing the same process of displaying an element of the array at different position.
- Everytime a recursive call is done, the number of element we have to display is reduced by one.
- We are doing the same task everytime but on a smaller problem.

## Problem 4

You have 2 tables,coursesandscores.coursesconsists 3 columns,sid,student_id, andcourse_id.scoresconsists 2 columns,sidandscore. Please find that how many students failed on at least one course.
你有 2 個表單,courses和scores。courses有 3 個欄位，sid、student_id、course_id。scores有 2 個欄位，sid和score。請分析有多少學生被當掉至少一科。

### Solution provided

In this problem you can either create an array of 5 columns or as I did, create a data structure that for the courses where the components are :

- sid
- student_id
- course_id
- total_score (which will be all the grades of the current student for the number of courses registered)
- n_courses (number of courses registered)

### Algorithm

- Take the number of rows (m) and cols (n) in the courses table inside the courses data structure created or the array if you prefer
- As you are adding those inputs, count the **number of students**, if a student has already counted DO NOT count him/her again
- As you are taking the scores inputs, add them in the scores table (as you are summing) by the **sid** because it is associated to the student_id
- Update the n_courses everytime that you are actually adding a score for a student
- After computing the sum of all scores and the number of courses of each student, count the number of students that have failed _at least one course_:
  - Initialize a counter
  - For each student, compute the average score by dividing the total_score by the n_courses;
  - If the average score is less than 60, increase the counter;
  - Return the counter as the number of students that have failed at least one course.

## Problem 5

五子棋是一個有著簡單規則的遊戲，由雙方各持白子或黑子進行遊戲，只要其中一方能在 19 \* 19 的棋盤上連著擺出 5 個一樣顏色的旗子就算是贏得遊戲，請寫一個程式，判斷遊戲是否有贏家產生。

Gomoku, also called Five in a Row, is an abstract strategy board game. It is traditionally played with black and white stones on a 19×19 board. The winner is the first player to form an unbroken chain of five stones horizontally, vertically, or diagonally. Please write a program to determine if there is a winner or not.

### Solution provided

- Take the inputs and store them in a 2D array of characters.
  - Take the inputs line by line
  - **After taking the inputs with fgets, DO NOT FORGET to empty the buffer in order to take a new line properly in memory.**
- To find if there is a winner or not you will follow this pattern:
  - Check horizontally if there is five sucessive BLACK or five successive WHITE on a row by counting, if found return the winner
  - Check vertically if there is five sucessive BLACK or five successive WHITE on a column by counting, if found return the winner
  - Check diagonally from left to right if there is five sucessive BLACK or five successive WHITE on a column by counting:
    - The range to parse the rows are 0 to 14, because lower than that you cannot have five successive values diagonally;
    - Check first by starting from col 0 to col 14, and counting the values diagonally in a SOUTH-EAST direction;
    - Then check by starting from col 4 to col 18, and counting the values diagonally in a SOUTH-WEST direction;
  - After all checking from those directions, if there is still no winner, return NO_WINNER.
