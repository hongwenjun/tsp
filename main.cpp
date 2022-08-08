#include <stdio.h>
#include <windows.h>
#include "tsp_node.h"

int main()
{
    char filename[] = "C:\\TSP\\CDR_TO_TSP";

    char buf[64];
    FILE* file = fopen(filename, "r");
    if (fgets(buf, 64, file) == NULL) {
        system("mkdir C:\\TSP\\");
    }


    int ret = read_tsp_to_vecter(filename);
    if (ret > 200){
       system("start  https://262235.xyz/index.php/tag/vba/");
       system("start  C:\\TSP\\TSP.txt");;
       }
    return 0;
}


#ifdef TSP_TSET

//  打印节点数据结构
TSP_NODE first = {-803.701800, 540.718400, 0, 3 };
TSP_NODE second = {169.229300, 257.756100, 3, 6 };
print_node(first);
print_node(second);

//  读取节点数和连接线数量
print_node_line_total(filename);

// 读取文件测试
read_node(filename);

#endif

