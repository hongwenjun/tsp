#include "tsp_node.h"

char* read_node(char* filename)
{
    char* line = (char*) malloc(1024);
    char* pch = NULL;
    FILE* file = fopen(filename, "r");
    while (fgets(line, 1024, file) != NULL) {
        printf("%s", line);
    }

    free(line);
    fclose(file);
    return line;
}

void print_node(TSP_NODE pn)
{
    printf("%f %f %d %d\n", pn.x, pn.y, pn.id, pn.next_node);
}
