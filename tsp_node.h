#ifndef TSP_NODE_H_INCLUDED
#define TSP_NODE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tsp_node_id_next_node {
    double x;
    double y;
    int id;
    int next_node;
} TSP_NODE ;

char* read_node(char* filename);
void print_node(TSP_NODE pn);

#endif // TSP_NODE_H_INCLUDED
