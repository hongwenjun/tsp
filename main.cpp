#include <stdio.h>
#include <windows.h>
#include "tsp_node.h"
#include "base64.h"
#include <string>

int main()
{
    char filename[] = "C:\\TSP\\CDR_TO_TSP";
    std::string web_base64 = "c3RhcnQgIGh0dHBzOi8vMjYyMjM1Lnh5ei9pbmRleC5waHAvdGFnL3ZiYS8=";
    std::string vba_262235 = base64_decode(web_base64);

    char buf[64];
    FILE* file = fopen(filename, "r");
    if (fgets(buf, 64, file) == NULL) {
        system("mkdir C:\\TSP\\");
    }

    int ret = read_tsp_to_vecter(filename);
    ret += read_tsp_to_lines(filename);
    if (ret > 400) {
        system(vba_262235.c_str());
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

std::string web = "start  https://262235.xyz/index.php/tag/vba/";
std::string encoded = base64_encode(web);
printf("%s\n", encoded.c_str());
std::string decoded = base64_decode(encoded);
printf("%s\n", decoded.c_str()) ;
#endif

