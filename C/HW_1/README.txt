The task is to develop a program that compares two given triangles in a 2D plane. The problem is an extension of the simple variant. This version accepts input triangles entered either by their vertices or by the lengths of their sides. Starting with the simple problem is highly recommended.

There are given two triangles in a 2D plane. Each triangle is defined either by its vertices or by the lengths of its sides:

    triangle defined by its vertices is entered in the form of three coordinates. The three coordinates are enclosed in curly braces; individual coordinates are separated by commas. A coordinate consists of two decimal numbers separated by a semicolon, the two numbers are enclosed in square braces. An example:

    { [ 1.5; 2 ], [3;4.2], [ 0.5 ; 0.6 ] }

    triangle defined by its sides is entered in the form of three decimal numbers. The three numbers are enclosed in curly braces and separated by commas. An example:

    {2.1, 3, 3.4}

Your program reads the triangles from the standard input. Next, the program decides one of the 4 cases:

    the input does not form a triangle (the three vertices defining the triangle are on a common line, or the sides do not obey triangle inequality),
    the triangles are identical,
    the triangles are not identical while their circumference is the same, or
    the triangles are entirely different.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below), and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:

    the coordinates or sides are invalid (are not valid decimals),
    some coordinate(s) or sides are missing,
    there are missing some separators (braces, commas, semicolons).

