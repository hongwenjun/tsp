#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tsp_node.h"






int main()
{
    TSP_NODE first = {-803.701800, 540.718400, 0, 3 };
    TSP_NODE second = {169.229300, 257.756100, 3, 6 };
    print_node(first);
    print_node(second);

    char filename[] = "R:\\TSP";
    // read_node(filename);
    return 0;
}
