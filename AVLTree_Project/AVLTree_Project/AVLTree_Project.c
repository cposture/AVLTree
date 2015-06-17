// AVLTree_Project.cpp : �������̨Ӧ�ó������ڵ㡣
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
    ���Բ��裺
    ��1������һ�ÿ���
    ��2������˳��������� data_insert[]�����ֱ���ʾ���ɵ��������Ľ�������߶�
    ��3���ֱ�ɾ������data_delete[]���ֱ���ʾɾ������������Ľ�������߶�
    ��4���ֱ���������data_search[]����ʾ���������"���ڻ򲻴���"
    ��5����������ÿ�����ؼ��ּ�1�������
    ��6��������������ʾ������������߶�
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

    //����һ�ÿ���
    flag = initAVLTree(&T);
    if (TRUE == flag)
        printf("����ʼ���ɹ�");
    else
        printf("����ʼ��ʧ��");

    //����˳��������� data_insert[]�����ֱ���ʾ���ɵ��������Ľ�������߶�
    for (i = 0; i < sizeof(data_insert)/sizeof(int); i++)
    {
        elem.key = data_insert[i];
        flag = insertAVLTree(&T, elem);
        if (TRUE == flag)
            sprintf(s, "%d ����ɹ�\n", data_insert[i]); 
        else
            sprintf(s, "%d ����ʧ��\n", data_insert[i]);
        printf("%s",s);
        printf("���Ľ����Ϊ%d���߶�Ϊ%d\n", getNumberOfNodes_AVLTree(T), getHeight_AVLTree(T));
        printAVLTree(T);
        printf("\n\n");
    }
    //�ֱ�ɾ������data_delete[]���ֱ���ʾɾ������������Ľ�������߶�
    for (i = 0; i < sizeof(data_delete) / sizeof(int); i++)
    {
        flag = deleteAVLTree(&T, data_delete[i]);
        if (TRUE == flag)
            sprintf(s, "%d ɾ���ɹ�\n", data_delete[i]);
        else
            sprintf(s, "%d �����ڣ�ɾ��ʧ��\n", data_delete[i]);
        printf("%s", s);
        printf("���Ľ����Ϊ%d���߶�Ϊ%d\n", getNumberOfNodes_AVLTree(T), getHeight_AVLTree(T));
        printAVLTree(T);
        printf("\n\n");
    }

    //�ֱ���������data_search[]����ʾ���������"���ڻ򲻴���"
    for (i = 0; i < sizeof(data_search) / sizeof(int); i++)
    {
        temp = searchAVLTree(T, data_search[i]);
        if (NULL != temp)
            sprintf(s, "%d ����\n", data_search[i]);
        else
            sprintf(s, "%d ������\n", data_search[i]);
        printf("%s", s);
        printAVLTree(T);
        printf("\n\n");
    }

    //��������ÿ�����ؼ��ּ�1�������
    printf("��������ÿ������ֵ��1\n");
    printf("����ǰ��");
    printAVLTree(T);
    traverseAVLTree(T, visit);
    printf("\n������");
    printAVLTree(T);

    //������
    printf("\n\n������\n");
    flag = destroyAVLTree(&T);
    if (TRUE == flag)
        printf("���ٳɹ�");
    else
        printf("����ʧ��");

    #if PRINT_TO_FILE == 1
    fclose(fp);
    #endif

    return 0;
}

