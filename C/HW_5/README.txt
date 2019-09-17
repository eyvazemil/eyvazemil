The task is to develop a program to compute the toll.

Assume a toll collection system. The toll is always computed as the number of kilometers times the toll rate. However, the rates are different, e.g. the use of the highway, ecology fee, road taxes, ... For the sake of simplicity, we assume there is 26 such rates, denoted by upper case letters A to Z.

The rates may vary for different sections of the highway. The input defines the length of the highway section and the list of toll rates. The list does not have to be complete, the unlisted toll rates will be copied from the previous highway section. For example:

{ 
  [ 50: A=10.5, E=80 ], 
  [ 30: Z=20, A=7.5, X=130 ], 
  [ 200: A=0, E=300 ] 
}

is interpreted as:

    the first highway section is 50 km long (from 0 km to 50 km). Toll rate A is 10.5 per km and toll rate E is 80 per km. The other rates are zero (the first highway section does not have any previous section to copy the remaining toll rates from),
    the second section is 30 km long (from 50 km to 80 km). Toll rate A is changed to 7.5 per km, toll rate E is copied from the predecessor as 80 per km, rate X is 130 per km, and rate Z is 20 per km. The other toll rates remain zero,
    the third section is 200 km long (from 80 km to 280 km). Rate A is zero, rate E is 300 per km, X 130 per km, and Z is 20 per km (both X and Z are copied from the previous section). The other rates are zero.

Having the toll rates set, the program is to compute the toll to pay. The program is given a list of pairs of integers. The integers represent the entry/exit point on the highway (in kilometers). Given that interval, the program displays all nonzero toll fees A to Z to pay.

The input of the program is the list of highway sections and the toll rates in the sections. The list is enclosed in curly braces, each section is enclosed in square brackets. The length of the section is a positive integer, the toll rates are identified by uppercase letters A to Z, the toll rate is a decimal number (positive or zero). Following the sections, there is a list of queries. Each query consists of two integers, the entry/exit kilometer of the highway. The order of the entry/exit kilometer may be either entry < exit or entry > exit (driving in the opposite direction). The queries are processed until end-of-file is reached.

If the entry/exit kilometer is exactly equal to the boundary of a highway section (with different toll fees), then there apply only the toll rates from the section relevant to the direction of travel. In the example highway sections above, the queries:

40 50
50 10

are computed using the toll rates only from the first section. On the other hand, queries:

50 60
70 50

are computed using the toll rates only from the second section. If the query covers more than one highway section, the individual sections contribute to the toll based on the number of kilometers, e.g.:

30 75    20km in the first section and 25km in the second section
100 20   30km in the first section, 30km in the second section (whole section) and 20km in the third section

The program must detect an invalid input. The following is considered invalid:

    the length of the highway section is not a positive integer (zero is invalid too),
    the toll rate is not identified by an uppercase letter A to Z,
    the toll rate is not a decimal or is negative (i.e., toll rate must be either positive or zero),
    there is no section defined for the highway (valid highways must define at least one section),
    a query is not formed by two integers,
    highway entry and exit kilometer are the same,
    highway entry/exit kilometer are outside of the highway (smaller than zero, or greater than the overall length of the highway),
    there are missing or redundant some separators (square braces, curly braces, colons, commas).

