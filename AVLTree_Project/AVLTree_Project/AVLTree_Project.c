// AVLTree_Project.cpp : 定义控制台应用程序的入口点。
//
#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <stdint.h>
#include <stdio.h>
#include "AVLTree.h"

#define PRINT_TO_FILE 0

Status visit(RcdType *d)
{
    if (NULL == d)
        return FALSE;

    d->key++;
    return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
    /*
    测试步骤：
    （1）建立一棵空树
    （2）按照顺序插入数据 data_insert[]；并分别显示生成的树、树的结点数、高度
    （3）分别删除数据data_delete[]并分别显示删除后的树、树的结点数、高度
    （4）分别搜索数据data_search[]并显示搜索结果，"存在或不存在"
    （5）遍历树，每个结点关键字加1，并输出
    （6）销毁树，并显示树、结点数、高度
    */

    AVLTreePtr T, temp;
    RcdType elem;
    int i;
    char s[50];
    Status flag;
    int data_insert[] = { 6, 3, 8, 2, 9, 1, 0, 4, 5, 7 };
    int data_delete[] = { 10, 0, 4, 7, 9 };
    int data_search[] = { 3, 5, 4, 7 };

    #if PRINT_TO_FILE == 1
    FILE* fp = 0;
    if (0 == (fp = freopen("result.txt", "a", stdout)))
        printf("Cannot open file.\n");
    #endif

    //建立一棵空树
    flag = initAVLTree(&T);
    if (TRUE == flag)
        printf("树初始化成功");
    else
        printf("树初始化失败");

    //按照顺序插入数据 data_insert[]；并分别显示生成的树、树的结点数、高度
    for (i = 0; i < sizeof(data_insert)/sizeof(int); i++)
    {
        elem.key = data_insert[i];
        flag = insertAVLTree(&T, elem);
        if (TRUE == flag)
            sprintf(s, "%d 插入成功\n", data_insert[i]); 
        else
            sprintf(s, "%d 插入失败\n", data_insert[i]);
        printf("%s",s);
        printf("树的结点数为%d，高度为%d\n", getNumberOfNodes_AVLTree(T), getHeight_AVLTree(T));
        printAVLTree(T);
        printf("\n\n");
    }
    //分别删除数据data_delete[]并分别显示删除后的树、树的结点数、高度
    for (i = 0; i < sizeof(data_delete) / sizeof(int); i++)
    {
        flag = deleteAVLTree(&T, data_delete[i]);
        if (TRUE == flag)
            sprintf(s, "%d 删除成功\n", data_delete[i]);
        else
            sprintf(s, "%d 不存在，删除失败\n", data_delete[i]);
        printf("%s", s);
        printf("树的结点数为%d，高度为%d\n", getNumberOfNodes_AVLTree(T), getHeight_AVLTree(T));
        printAVLTree(T);
        printf("\n\n");
    }

    //分别搜索数据data_search[]并显示搜索结果，"存在或不存在"
    for (i = 0; i < sizeof(data_search) / sizeof(int); i++)
    {
        temp = searchAVLTree(T, data_search[i]);
        if (NULL != temp)
            sprintf(s, "%d 存在\n", data_search[i]);
        else
            sprintf(s, "%d 不存在\n", data_search[i]);
        printf("%s", s);
        printAVLTree(T);
        printf("\n\n");
    }

    //遍历树，每个结点关键字加1，并输出
    printf("遍历树，每个结点的值增1\n");
    printf("遍历前：");
    printAVLTree(T);
    traverseAVLTree(T, visit);
    printf("\n遍历后：");
    printAVLTree(T);

    //销毁树
    printf("\n\n销毁树\n");
    flag = destroyAVLTree(&T);
    if (TRUE == flag)
        printf("销毁成功");
    else
        printf("销毁失败");

    #if PRINT_TO_FILE == 1
    fclose(fp);
    #endif

    return 0;
}

