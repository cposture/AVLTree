/***************************************************************************************
*	File Name				: AVLTree.h
*	CopyRight				:
*	ModuleName			    :
*
*	CPU						:
*	RTOS					:
*
*	Create Data				:	2015/06/10
*	Author/Corportation		:	陈家启
*
*	Abstract Description	:	平衡二叉树
*
*--------------------------------Revision History--------------------------------------
*	No	version		Data			Revised By			Item			Description
*	1   v1.0        2015/06/10      陈家启              All             Create the file      
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
//关键字类型
typedef int KeyType;

//元素类型
typedef struct RcdType{
    KeyType key;
}RcdType;

//状态枚举类型
typedef enum {          
    TRUE,FALSE,OVERFLOW
}Status;

//平衡二叉树结点类型
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
*	Description....:	初始化平衡二叉树
*	Param..........:	t:指向平衡二叉树指针的指针
*	Return.........:    TRUE:初始化成功
                        FALSE:初始化失败
*	Precondition...:    使用前要先定义一个AVLTreePtr类型变量，将其地址作为实参
*	Postcondition..:    *t指向一棵空树
**/
Status  initAVLTree(AVLTreePtr *t);

/**
*	Name...........:    Status  destroyAVLTree(AVLTreePtr *t);
*	Description....:	销毁平衡二叉树
*	Param..........:	t：指向平衡二叉树指针的指针
*	Return.........:    TRUE：销毁成功
                        FALSE：销毁失败
*	Precondition...:
*	Postcondition..:    如果树中有数据，那么所有数据会被销毁，*t指向一棵空树
**/
Status  destroyAVLTree(AVLTreePtr *t);

/**
*	Name...........:    AVLTreePtr  searchAVLTree(AVLTreePtr t, KeyType key);
*	Description....:	在平衡二叉树查找指定关键字
*	Param..........:	t：平衡二叉树指针
                        key：要查找的指定关键字
*	Return.........:    NULL：平衡二叉树没有指定关键字
                        非NULL：指定关键字结点指针
*	Precondition...:    
*	Postcondition..:    
**/
AVLTreePtr  searchAVLTree(AVLTreePtr t, KeyType key);

/**
*	Name...........:    Status  insertAVLTree(AVLTreePtr *t, RcdType elem);
*	Description....:	在平衡二叉树插入指定元素
*	Param..........:	t：指向平衡二叉树指针的指针
                        elem：指定插入的元素
*	Return.........:    TRUE：插入成功
                        FALSE：插入失败
*	Precondition...:    
*	Postcondition..:    若插入成功，*t将指向一棵插入了新结点的平衡二叉树；若插入失败，*t（平衡二叉树)不会改变
**/
Status  insertAVLTree(AVLTreePtr *t, RcdType elem);

/**
*	Name...........:    Status  deleteAVLTree(AVLTreePtr *t, KeyType key);
*	Description....:	在平衡二叉树删除指定关键字
*	Param..........:	t：指向平衡二叉树指针的指针
                        key：要删除的指定关键字
*	Return.........:    TRUE：删除成功
                        FALSE：删除失败
*	Precondition...:
*	Postcondition..:    若删除成功，*t将指向一棵删除了结点的平衡二叉树；若删除失败，*t（平衡二叉树)不会改变
**/

Status  deleteAVLTree(AVLTreePtr *t, KeyType key);

/**
*	Name...........:    Status isEmpty_AVLTree(AVLTreePtr t);
*	Description....:	判断树是否为空
*	Param..........:	t：平衡二叉树指针
*	Return.........:    TRUE：空
                        FALSE：非空
*	Precondition...:
*	Postcondition..:    
**/
Status isEmpty_AVLTree(AVLTreePtr t);

/**
*	Name...........:    int getHeight_AVLTree(AVLTreePtr t);
*	Description....:	获取树的高度
*	Param..........:	t：平衡二叉树指针
*	Return.........:    树的高度，0表示空树
*	Precondition...:
*	Postcondition..:
**/
int getHeight_AVLTree(AVLTreePtr t);

/**
*	Name...........:    int getNumberOfNodes_AVLTree(AVLTreePtr t);
*	Description....:	获取树的结点数
*	Param..........:	t：平衡二叉树指针
*	Return.........:    树的结点数，0表示空树
*	Precondition...:
*	Postcondition..:
**/
int getNumberOfNodes_AVLTree(AVLTreePtr t);
/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif