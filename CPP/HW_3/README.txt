The task is to develop a C++ classes CRange and CRangeList. The classes will represent an interval of integers and a list of integer intervals, respectively.

Assume an interval of integers. The interval may be either just 1 number or several numbers. Intervals of length 1 number will be denoted as a single integer, e.g., 42. Longer intervals will be denoted as two points (the boundaries) in angle braces. For example, interval <1..5> represents integers 1,2,3,4,5. The intervals are implemented by the CRange class. The integer/boundaries in CRange will be stored as long long values (negative values are supported). The interface of CRange is:

constructor (lo, hi)
    initializes the interval from lo to hi. The constructor checks the boundaries, i.e., lo ≤ hi. If the condition fails, the constructor throws InvalidRangeException (the exception class is implemented in the testing environment).
further
    further interface may be needed, study the attached source and add methods to support the desired behavior. You are free to add your own methods that are needed for your implementation. The only limit is the size of the instance, two long long integers maximum.

Class CRangeList implements a list of intervals. The class must be efficient when storing the intervals, i.e. overlapping intervals will be merged. The interface of CRangeList offers methods to add / remove intervals, compare instances, and print to an output stream. Moreover, there is an extended interface (in the bonus test) that adds more functionality. The required interface is:

default constructor
    initializes an empty list of intervals,
destructor, copy constructor, op=
    implemented if your representation requires them. In general, we recommend to use an appropriate STL container and let the compiler implement the copying/destruction.
Includes(long long) / Includes (CRange)
    the methods test whether the list of intervals includes the given value / interval. The methods return true (contains the value/interval) or false (does not contain).
+=
    this operator adds interval(s) to the list, indeed it is a set union operation. The operator is responsible for the compact representation, i.e., it must merge the overlapping intervals. Since the intervals represent integers, the merging is a bit unusual. Naturally, the following intervals are merged:

        <10..20> and <15..30>,
        <10..30> and <15..18>, and
        <10..20> and <20..30>,

    Surprisingly, intervals <10..20> and <21..30> are merged although they do not overlap or touch. Nevertheless, they together cover all integers from in the range, thus represent interval <10..30>. On the other hand, intervals <10..19> and <21..30> are not merged, number 20 is not included.
-=
    this operator is complementary to operator +=. The interval(s) on the right-hand side are removed from the interval list. The operation may be seen as a set difference. Once again, the representation must be efficient, thus unneeded intervals must be removed.
=
    this operator may be used to replace the contents with the intervals on the right-hand side.
==, !=
    the operators compare two instances of CRangeList. Two instances are identical if the list of intervals is the same.
<<
    the operator prints out the contents to the given output stream. The resulting list will be enclosed in curly braces, individual intervals are separated by a comma. The list is printed in an ascending order. Intervals of length 1 are printed as a single integers, longer intervals are printed in angle braces. The output format is clear from the attached examples.

The task offers a bonus test for extra points, the bonus requires additional interface that simplifies some operations. You are free to either implement the extra interface, or not. However:

    if you decide not to implement the extra interface, keep the preprocessor directive EXTENDED_SYNTAX in a comment. The additional construct will not be compiled, bonus test will be skipped, and bonus points will not be awarded,
    if you decide to implement the extra interface, define preprocessor directive EXTENDED_SYNTAX (i.e., remove the comment). In this case, the testing environment will include the extra test in compilation and will execute the bonus test.
    Caution. The compilation fails if you uncomment the EXTENDED_SYNTAX directive without the implementation of the extra interface.

The extra interface required for the bonus test:

constructor to initialize CRangeList from a list of values
    the list of integers is interpreted as the intervals included in the new instance,
range for loop
    range for loops must be able to handle CRangeList instances. The intervals will be iterated in an ascending order,
output operator must always display the output in radix 10, however, it must preserve the former settings of the ostream object. 
