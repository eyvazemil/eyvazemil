The task is to develop a program to solve arithmetic puzzles with roman numbers.

Assume a sequence of characters - the roman digits I, V, X, L, C, D, and M. The puzzle is to place + signs into the sequence such that the result is a string that consists of valid roman numbers and the sum of the roman numbers equals to some given value n. For example, input IVIIIVI and n=13 may result into the following valid expressions:

13 = I+V+I+I+IV+I
13 = I+V+II+IV+I
13 = I+VI+I+IV+I
13 = I+VII+IV+I
13 = IV+I+I+I+V+I
13 = IV+I+I+I+VI
13 = IV+I+II+V+I
13 = IV+I+II+VI
13 = IV+II+I+V+I
13 = IV+II+I+VI
13 = IV+III+V+I
13 = IV+III+VI

The program must be able to find all possible solutions of the puzzle and count the number of such solutions.

The first line of the input is a sequence of uppercase letters. The letters are not separated by any whitespace. This is the puzzle to solve, the program is about to place the + operators somewhere into this sequence. Following the first line, there is a list of commands. The commands are of two kinds:

    count n computes the number of solutions for the puzzle (i.e., how may options there exist such that the sum is equal to n,
    list n is similar to the previous command, moreover, the program shall print out all solutions.

The output of the program is either the number of solutions (command count n) or the list of solutions and their count (command list n). The exact output format is shown in the examples below.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below), and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:

    there are invalid characters in the input sequence (only I, V, X, L, C, D, and M is valid),
    the command is neither list n nor count n,
    the number n is invalid, not an integer, negative, or zero.

