The task is to develop a program that analyzes numbers from a given interval. The problem is an extension of the simpler variant. The analyzed numbers will not always be binary. Instead, the program shall analyze the sequences of numbers written in different bases.

An instance of the problem is defined by the radix R, a lower boundary LO, and an upper boundary HI. Assume all integers from the interval [LO;HI] written as radix-R numbers. The numbers form a sequence of digits. The program shall:

    compute the overall length of the sequence (i.e., the total number of digits),
    compute the number of zeros in the sequence, or
    compute the longest contiguous run of zeros in the sequence.

For example, input problem instance r4:[10;20] defines sequence of numbers from 10 to 20 written as base-4 numbers. The sequence is:

  22 23 30 31 32 33 100 101 102 103 110 

The sequence is 27 digits long, out of which, there are 7 zeros. The longest contiguous run of zeros is of length 2. Similarly, input input problem instance r13:[10;20] defines a sequence of numbers from 10 to 20 written as base-13 numbers. The sequence is:

  A B C 10 11 12 13 14 15 16 17 

The sequence is 19 digits long, out of which, there is 1 zero, and the longest zero sequence is just 1.

The input of the program is a list of problem instances to solve. In general, the problem list may be of any length. Each problem instance is defined as a radix, a closed interval of numbers, and a code of the desired computation. The input may have two forms:

rR: <LO;HI> OP
<LO;HI> OP

where R is a decimal integer that defines the radix. If the radix is omitted (the second short form), we assume radix R=10. Values LO and HI are decimal integers that define a closed interval of numbers to analyze. Finally, OP is the code of the desired computation. It is a single character:

    l to compute the overall length of the sequence,
    z to compute the number of zeros in the sequence, or
    s to compute the longest run of zeros in the sequence.

There is a list of problem instances in the program's input. The program shall read the individual problems instances, process them, and display the desired result. The processing of the input ends when the program reaches the end of file (EOF).

The output of the program is the result of the desired computation; the result is shown for each input problem instance. The exact output format is shown in the sample runs below.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below), and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:

    the radix or the interval boundaries are invalid (are not valid decimal integers),
    the boundaries are negative,
    the lower bound is greater than the upper bound,
    the radix is not in the range 2 to 36,
    the desired computation is not any of l, z, and s, or
    there are missing/redundant separators (angle brace, semicolon).

