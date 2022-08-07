#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "tsp_node.h"

std::vector<TSP_NODE> node;

char* read_node(char* filename)
{
    char* line = (char*) malloc(1024);
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


void print_node_line_total(char* filename)
{
    TSP_NODE_LINE tsp;
    FILE* file = fopen(filename, "r");

    fscanf(file, "%d %d\n", &tsp.node_total, &tsp.line_total);
    printf("%d %d\n", tsp.node_total, tsp.line_total);

    TSP_NODE pn;
    fscanf(file, "%lf %lf\n", &pn.x, &pn.y);
    printf("%f %f %d %d\n", pn.x, pn.y, pn.id, pn.next_node);

    fclose(file);
}


int read_tsp_to_vecter(char* filename)
{

    TSP_NODE_LINE tsp;
    TSP_NODE pn;
    FILE* file = fopen(filename, "r");
    FILE* tmpf = fopen("TSP.txt", "w+");


    fscanf(file, "%d %d\n", &tsp.node_total, &tsp.line_total);
    printf("%d %d\n", tsp.node_total, tsp.line_total);

    if (tsp.node_total != tsp.line_total)
        return 0;

    fprintf(tmpf, "%d %d\n", tsp.node_total, tsp.line_total);

    for (auto i = 0 ; i != tsp.node_total ; i++) {
        fscanf(file, "%lf %lf\n", &pn.x, &pn.y);
        pn.id = i;
        pn.next_node = 0;
        node.push_back(pn);
    }

    int id;
    int next_node;
    int fork;
    for (auto i = 0 ; i != tsp.line_total ; i++) {
        fscanf(file, "%d %d %d\n", &id, &next_node, &fork);
        node[id].next_node = next_node;

      //  printf("%f %f %d %d\n", node[id].x, node[id].y, node[id].id, node[id].next_node);
        fprintf(tmpf, "%f %f\n", node[id].x, node[id].y);
    }

//    for (auto it = node.begin(); it != node.end(); ++it) {
//        pn = *it;
//        printf("%f %f %d %d\n", pn.x, pn.y, pn.id, pn.next_node);
//    }

    fclose(file);
    fseek (tmpf, 0, SEEK_END);   // non-portable
    int fsize=ftell (tmpf);


    rewind(tmpf);

    char* buf = (char*) malloc(fsize);
    memset(buf, 0, fsize);

    fseek (tmpf , 0, SEEK_SET );
    fread(buf, 1, fsize-1 , tmpf);

    printf("%s", buf);
    CopyTextToClipboard(buf);
    free(buf);
    fclose(tmpf);
    return tsp.node_total;
}


// 读取剪贴板中的文本
char* GetClipboardText(char* buf)
{
    OpenClipboard(nullptr);
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == NULL)
        return "Not is CF_TEXT!";

    char* pszText = static_cast<char*>(GlobalLock(hData));
    strcpy(buf, pszText);

    GlobalUnlock(hData);
    CloseClipboard();
    return buf;
}

// 复制文本到剪贴板
bool CopyTextToClipboard(const char* text)
{
    int i = 0, j = 0;
    for (; i < 6; i++) {
        //打开剪切板
        j = OpenClipboard(NULL);

        //判断是否打开成功，如果打开失败则重新尝试5次
        if (j == 0 && i < 5)
            Sleep(60);
        if (j == 0 && i == 5)
            return false;
        if (j != 0) {
            i = 0;
            j = 0;
            break;
        }
    }
    //分配字节数，HGLOBAL表示一个内存块
    HGLOBAL hmem = GlobalAlloc(GHND, strlen(text) + 1);

    //锁定内存中指定的内存块，并返回一个地址值令其指向内存块的起始处
    char* pmem = (char*)GlobalLock(hmem);

    //清空剪切板并释放剪切板内数据的句柄
    EmptyClipboard();
    memcpy(pmem, text, strlen(text) + 1);
    SetClipboardData(CF_TEXT, hmem);        //写入数据
    CloseClipboard();                       //关闭剪切板
    GlobalFree(hmem);                       //释放内存块

    return true;     //返回成功
}
