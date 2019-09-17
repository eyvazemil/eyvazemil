Your task is to develop a program that solves findword puzzle.

Findword puzzle is defined by a 2D array of letters and a list of words. To solve the puzzle all words from the list must be located in the 2D array of letters and the letters corresponding to the word shall be "struck out". When all words from the list are completed, the remaining letters (which were not struck out) read int left-to-right, top-to-bottom manner form the solution of the puzzle. The words may be located anywhere in the 2D array - they may be read left-to-right, right-to-left, top-down, down-top, or even diagonally. One letter may participate in several words, the words may overlap, a word from the list may appear several times in the 2D array (all instances must be struck out).

The input of your program is the findword puzzle. The input consists of the 2D array, an empty line, and a list of words to search for. The 2D array must be of a rectangular shape, only lowercase letters and period character may appear in the 2D array (the period stands for an unused cell). The list of words is delivered as one word per line. The word list ends with the end of the input.

The output is the solution of the puzzle. The solution may be rather long, thus your program shall wrap it to 60 characters per line + the remaining letters (if any) on the last line.

The program shall detect invalid input. If the input is invalid, it shall print out an error message and terminate. The following is considered invalid:

    the array is not at least 1x1 character in size,
    the array is not of a rectangular shape,
    there is a character different from lowercase letter or period in the 2D array,
    the empty line separator is missing,
    a word from the list does not appear in the 2D array (caution, the error message is different here, see below).

Please strictly adhere the format of the output. The output must exactly match the output of the reference program. The comparison is done by a machine, the machine requires an exact match. If your program provides output different from the reference, the program is considered malfunctioning. Be very careful, the machine is sensitive event to whitespace characters (spaces, newlines, tabulators). Please note that all output lines are followed by a newline character (\n). This applies even to the last line of the output, moreover, this applies even to the error message. Download the enclosed archive. The attached archive contains a set of testing inputs and the expected outputs.
