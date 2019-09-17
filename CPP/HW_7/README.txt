The task is to develop a generic class CRoute that can find a path connecting two given places.

We assume a map with nodes (e.g. cities, computers, ...) and edges that connect node pairs (e.g. roads, railroads, network links, ...). Class CRoute stores the map. Since the map is general, the data types describing nodes and edges will be implemented as generic parameters.

The class will provide a method to insert edges and a method to search a path. The exact interface is:

default constructor
    prepares an empty CRoute instance.
method Add (u1, u2, e)
    this method adds a new edge connecting nodes u1 and u2. The third parameter e is the description of the edge, e.g. the speed of the line, type of road, ... The edge is assume two-way edge.
method Find (u1, u2, [,f] )

    this method will search the map to find a path from u1 to u2. The result is a list (std::list) with the nodes along the path from u1 to u2. The first node in the list shall be u1, the last u2.

    It may be the case that there is no path connecting u1 to u2. In that case the method throws NoRouteException. Moreover, there may exist many different ways to get from u1 to u2. In that case, the method returns the shortest path (the path with the lowest number of intermediate nodes). Finally, if there are several options of the path with the lowest number of intermediate nodes, the result may be any of them.

    The method shall be provided in two variants: with and without the third optional parameter f. If present, the third parameter acts as a filter that enables/disables individual edges. The filter is provided in the form of a function/functor/lambda expression. It shall be applied to the edges. If the filter returns false, the edge must not be included in the resulting path. Thus, the filter may be used to remove certain edges from the search, i.e. we may consider only edges with some properties (speed, quality, ...).

Generic parameter _T is the data type that represents nodes. Your implementation may use the following operations with _T:

    copy constructor,
    operator =,
    relational operators (==, !=, <, <=, > >=),
    destructor,
    output operator <<.
    Further operations may exist, however, they are not guaranteed.

Generic parameter _T is the data type that represents edges. Your implementation may use the following operations with _E:

    copy constructor,
    operator =,
    destructor.
    Further operations may exist, however, they are not guaranteed.

