/***************************************************************************************
*	File Name				: AVLTree.h
*	CopyRight				:
*	ModuleName			    :
*
*	CPU						:
*	RTOS					:
*
*	Create Data				:	2015/06/10
*	Author/Corportation		:	�¼���
*
*	Abstract Description	:	ƽ�������
*
*--------------------------------Revision History--------------------------------------
*	No	version		Data			Revised By			Item			Description
*	1   v1.0        2015/06/10      �¼���              All             Create the file      
*
***************************************************************************************/


/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef _AVLTREE_H
#define _AVLTREE_H

/**************************************************************
*	Debug switch Section
**************************************************************/
#include <stddef.h>

/**************************************************************
*	Include File Section
**************************************************************/


/**************************************************************
*	Macro Define Section
**************************************************************/

/**************************************************************
*	Struct Define Section
**************************************************************/
//�ؼ�������
typedef int KeyType;

//Ԫ������
typedef struct RcdType{
    KeyType key;
}RcdType;

//״̬ö������
typedef enum {          
    TRUE,FALSE,OVERFLOW
}Status;

//ƽ��������������
typedef struct AVLTreeNode{ 
    RcdType data;
    int     bf;
    struct AVLTreeNode *lchild;
    struct AVLTreeNode *rchild;
}AVLTreeNode,*AVLTreePtr;

/**************************************************************
*	Prototype Declare Section
**************************************************************/
/**
*	Name...........:    Status  initAVLTree(AVLTreePtr *t);
*	Description....:	��ʼ��ƽ�������
*	Param..........:	t:ָ��ƽ�������ָ���ָ��
*	Return.........:    TRUE:��ʼ���ɹ�
                        FALSE:��ʼ��ʧ��
*	Precondition...:    ʹ��ǰҪ�ȶ���һ��AVLTreePtr���ͱ����������ַ��Ϊʵ��
*	Postcondition..:    *tָ��һ�ÿ���
**/
Status  initAVLTree(AVLTreePtr *t);

/**
*	Name...........:    Status  destroyAVLTree(AVLTreePtr *t);
*	Description....:	����ƽ�������
*	Param..........:	t��ָ��ƽ�������ָ���ָ��
*	Return.........:    TRUE�����ٳɹ�
                        FALSE������ʧ��
*	Precondition...:
*	Postcondition..:    ������������ݣ���ô�������ݻᱻ���٣�*tָ��һ�ÿ���
**/
Status  destroyAVLTree(AVLTreePtr *t);

/**
*	Name...........:    AVLTreePtr  searchAVLTree(AVLTreePtr t, KeyType key);
*	Description....:	��ƽ�����������ָ���ؼ���
*	Param..........:	t��ƽ�������ָ��
                        key��Ҫ���ҵ�ָ���ؼ���
*	Return.........:    NULL��ƽ�������û��ָ���ؼ���
                        ��NULL��ָ���ؼ��ֽ��ָ��
*	Precondition...:    
*	Postcondition..:    
**/
AVLTreePtr  searchAVLTree(AVLTreePtr t, KeyType key);

/**
*	Name...........:    Status  insertAVLTree(AVLTreePtr *t, RcdType elem);
*	Description....:	��ƽ�����������ָ��Ԫ��
*	Param..........:	t��ָ��ƽ�������ָ���ָ��
                        elem��ָ�������Ԫ��
*	Return.........:    TRUE������ɹ�
                        FALSE������ʧ��
*	Precondition...:    
*	Postcondition..:    ������ɹ���*t��ָ��һ�ò������½���ƽ���������������ʧ�ܣ�*t��ƽ�������)����ı�
**/
Status  insertAVLTree(AVLTreePtr *t, RcdType elem);

/**
*	Name...........:    Status  deleteAVLTree(AVLTreePtr *t, KeyType key);
*	Description....:	��ƽ�������ɾ��ָ���ؼ���
*	Param..........:	t��ָ��ƽ�������ָ���ָ��
                        key��Ҫɾ����ָ���ؼ���
*	Return.........:    TRUE��ɾ���ɹ�
                        FALSE��ɾ��ʧ��
*	Precondition...:
*	Postcondition..:    ��ɾ���ɹ���*t��ָ��һ��ɾ���˽���ƽ�����������ɾ��ʧ�ܣ�*t��ƽ�������)����ı�
**/

Status  deleteAVLTree(AVLTreePtr *t, KeyType key);

/**
*	Name...........:    Status isEmpty_AVLTree(AVLTreePtr t);
*	Description....:	�ж����Ƿ�Ϊ��
*	Param..........:	t��ƽ�������ָ��
*	Return.........:    TRUE����
                        FALSE���ǿ�
*	Precondition...:
*	Postcondition..:    
**/
Status isEmpty_AVLTree(AVLTreePtr t);

/**
*	Name...........:    int getHeight_AVLTree(AVLTreePtr t);
*	Description....:	��ȡ���ĸ߶�
*	Param..........:	t��ƽ�������ָ��
*	Return.........:    ���ĸ߶ȣ�0��ʾ����
*	Precondition...:
*	Postcondition..:
**/
int getHeight_AVLTree(AVLTreePtr t);

/**
*	Name...........:    int getNumberOfNodes_AVLTree(AVLTreePtr t);
*	Description....:	��ȡ���Ľ����
*	Param..........:	t��ƽ�������ָ��
*	Return.........:    ���Ľ������0��ʾ����
*	Precondition...:
*	Postcondition..:
**/
int getNumberOfNodes_AVLTree(AVLTreePtr t);
/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif