#ifndef TSP_NODE_H_INCLUDED
#define TSP_NODE_H_INCLUDED
#include <windows.h>
#include <string.h>

bool CopyTextToClipboard(const char* text);
char* GetClipboardText(char* buf);


typedef struct tsp_node_id_next_node {
    double x;
    double y;
    int id;
    int next_node;
} TSP_NODE ;


typedef struct tsp_node_and_line {
    int node_total;
    int line_total;
} TSP_NODE_LINE ;

char* read_node(char* filename);

void print_node(TSP_NODE pn);
void print_node_line_total(char* filename);

int read_tsp_to_vecter(char* filename);

#endif // TSP_NODE_H_INCLUDED
