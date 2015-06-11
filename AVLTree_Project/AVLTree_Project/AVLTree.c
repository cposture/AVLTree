/***************************************************************************************
*	FileName				:	AVLTree.c
*	CopyRight				:
*	ModuleName				:	
*
*	CPU						:	
*	RTOS					:
*
*	Create Date				:	2015/06/10
*	Author/Corportation		:	陈家启
*
*	Abstract Description	:   平衡二叉树
*
*--------------------------------Revision History--------------------------------------
*	No	version		Date		    Revised By			Item			Description
*	1   v1.0        2015/06/10      陈家启              All             Create the file 
*
***************************************************************************************/



/**************************************************************
*	Debug switch Section
**************************************************************/

/**************************************************************
*	Include File Section
**************************************************************/
#include "AVLTree.h"

/**************************************************************
*	Macro Define Section
**************************************************************/
#define LH  +1  
#define EH  0
#define RH  -1
/**************************************************************
*	Struct Define Section
**************************************************************/

/**************************************************************
*	Prototype Declare Section
**************************************************************/
static void R_Rotate(AVLTreePtr *p);
static void L_Rotate(AVLTreePtr *p);
static Status  insertAVLTree_Interface(AVLTreePtr *t, RcdType elem, Status *taller);
static void leftBalance(AVLTreePtr *p);
static void rightBalance(AVLTreePtr *p);
/**************************************************************
*	Global Variable Declare Section
**************************************************************/

/**************************************************************
*	File Static Variable Define Section
**************************************************************/

/**************************************************************
*	Function Define Section
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
Status  initAVLTree(AVLTreePtr *t)
{
    *t = NULL;
    return TRUE;
}

/**
*	Name...........:    Status  destroyAVLTree(AVLTreePtr *t);
*	Description....:	销毁平衡二叉树
*	Param..........:	t：指向平衡二叉树指针的指针
*	Return.........:    TRUE：销毁成功
                        FALSE：销毁失败
*	Precondition...:
*	Postcondition..:    如果树中有数据，那么所有数据会被销毁，*t指向一棵空树
**/
Status  destroyAVLTree(AVLTreePtr *t)
{
    if (NULL != *t)
    {
        destroyAVLTree(&(*t)->lchild);
        destroyAVLTree(&(*t)->rchild);
        free(*t);
        *t = NULL;
    }
    return TRUE;
}

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
AVLTreePtr  searchAVLTree(AVLTreePtr t, KeyType key)
{
    if (NULL == t)
        return NULL;
    if (t->data.key > key)
        return searchAVLTree(t->lchild, key);
    else if (t->data.key < key)
        return searchAVLTree(t->rchild, key);
    else
        return t;
}

/**
*	Name...........:    Status  insertAVLTree_Interface(AVLTreePtr *t, RcdType elem);
*	Description....:	在平衡二叉树插入指定元素
*	Param..........:	t：指向平衡二叉树指针的指针
                        elem：指定插入的元素
*	Return.........:    TRUE：插入成功
                        FALSE：插入失败
*	Precondition...:
*	Postcondition..:    若插入成功，*t将指向一棵插入了新结点的平衡二叉树；若插入失败，*t（平衡二叉树)不会改变
**/
Status  insertAVLTree_Interface(AVLTreePtr *t, RcdType elem)
{
    Status  taller;
    return insertAVLTree_Interface(t, elem, &taller);
}

/**
*	Name...........:    Status isEmpty_AVLTree(AVLTreePtr t);
*	Description....:	判断树是否为空
*	Param..........:	t：平衡二叉树指针
*	Return.........:    TRUE：空
                        FALSE：非空
*	Precondition...:
*	Postcondition..:
**/
Status isEmpty_AVLTree(AVLTreePtr t)
{
    if (NULL == t)
        return TRUE;
    else
        return FALSE;
}

/**
*	Name...........:    int getHeight_AVLTree(AVLTreePtr t);
*	Description....:	获取树的高度
*	Param..........:	t：平衡二叉树指针
*	Return.........:    树的高度，0表示空树
*	Precondition...:
*	Postcondition..:
**/
int getHeight_AVLTree(AVLTreePtr t)
{
    int l_height, r_height;

    if (NULL == t)
        return 0;
    l_height = getHeight_AVLTree(t->lchild);
    r_height = getHeight_AVLTree(t->rchild);
    return (1 + (l_height >= r_height ? l_height : r_height));
}

/**
*	Name...........:    int getNumberOfNodes_AVLTree(AVLTreePtr t);
*	Description....:	获取树的结点数
*	Param..........:	t：平衡二叉树指针
*	Return.........:    树的结点数，0表示空树
*	Precondition...:
*	Postcondition..:
**/
int getNumberOfNodes_AVLTree(AVLTreePtr t)
{
    if (NULL == t)
        return 0;
    return (1 + getNumberOfNodes_AVLTree(t->lchild) + getNumberOfNodes_AVLTree(t->rchild));
}

/**
*	Name...........:    static Status  insertAVLTree_Interface(AVLTreePtr *t, RcdType elem, Status *taller);
*	Description....:	在平衡二叉树插入指定元素
*	Param..........:	t：指向平衡二叉树指针的指针
                        elem：指定插入的元素
                        taller：标志值，调用时传入了一个Status类型任意值实参即可
*	Return.........:    TRUE：插入成功
                        FALSE：插入失败
*	Precondition...:
*	Postcondition..:    若插入成功，*t将指向一棵插入了新结点的平衡二叉树；若插入失败，*t（平衡二叉树)不会改变，*taller最终为FALSE
**/
static Status  insertAVLTree_Interface(AVLTreePtr *t, RcdType elem, Status *taller)
{
    if (NULL == *t) //树为空，则直接生成一个结点，并作为根节点
    {
        *t = (AVLTreePtr)malloc(sizeof(AVLTreeNode));
        if (NULL == *t)
            return OVERFLOW;
        (*t)->bf = EH;
        (*t)->data = elem;
        (*t)->lchild = (*t)->rchild = NULL;
        *taller = TRUE; //插入了新结点，置*taller为TRUE
        return TRUE;
    }
    else if (elem.key == (*t)->data.key)    //要插入的结点和根结点相同，则不用插入
    {
        *taller = FALSE;
        return FALSE;
    }
    else if (elem.key < (*t)->data.key) //elem值比根结点小，则插入到左子树
    {
        if (FALSE == insertAVLTree_Interface((*t)->rchild, elem, taller))
            return FALSE;
        if (TRUE == *taller)
        {
            switch ((*t)->bf)
            {
            case LH:    //插入后，左子树与右子树高度差为2    
                leftBalance(t); //左平衡处理
                *taller = FALSE;    //处理后，不用再处理了，置taller为FALSE
                break;
            case EH:    //原左右子树等高
                (*t)->bf = LH;  //在左子树插入后，平衡因子变为1
                *taller = TRUE; //置taller为TRUE
                break;
            case RH:    //原右子树高于左子树
                (*t)->bf = EH;  //在左子树插入后，平衡因子变为0
                *taller = FALSE;
                break;
            }
        }
    }
    else if (elem.key > (*t)->data.key) //elem值比根结点大，则插入到右子树
    {
        if (FALSE == insertAVLTree_Interface((*t)->rchild, elem, taller))
            return FALSE;
        if (TRUE == *taller)
        {
            switch ((*t)->bf)
            {
            case LH:
                (*t)->bf = EH;
                *taller = FALSE;
                break;
            case EH:
                (*t)->bf = RH;
                *taller = TRUE;
                break;
            case RH:
                rightBalance(t);
                *taller = FALSE;
                break;
            }
        }
    }
    return TRUE;
}

/**
*	Name...........:    static void R_Rotate(AVLTreePtr *p);
*	Description....:	LL型失衡二叉树的右旋调整（顺时针）
*	Param..........:	p：指向最小失衡子树指针的指针
*	Return.........:    
*	Precondition...:
*	Postcondition..:    最小失衡子树恢复平衡；最小失衡子树A的左孩子为B，若旋转成功，B顶替A的位置，A成为B的右孩子，如果B存在右孩子Br，则Br成为A的左子树
**/
static void R_Rotate(AVLTreePtr *p)
{
    AVLTreePtr lc;

    if (NULL == *p)
        return;

    lc = (*p)->lchild;  // lc指向p结点的左孩子
    (*p)->lchild = lc->rchild;  //lc结点的右子树置为p结点的左子树
    lc->rchild = *p;    //置p结点为lc结点的右子树
    *p = lc;    //p指向新的根结点
}

/**
*	Name...........:    static void L_Rotate(AVLTreePtr *p);
*	Description....:	RR型失衡二叉树的左旋调整（逆时针）
*	Param..........:	p：指向最小失衡子树指针的指针
*	Return.........:    
*	Precondition...:
*	Postcondition..:    最小失衡子树恢复平衡；最小失衡子树A的右孩子为B，B顶替A成为最小失衡子树的新根，A成为B的左孩子，如果B有左孩子，则Bl成为A的右孩子
**/
static void L_Rotate(AVLTreePtr *p)
{
    AVLTreePtr rc;

    if (NULL == *p)
        return;

    rc = (*p)->rchild;  //rc先连接p的右孩子
    (*p)->rchild = rc->lchild; //p的右孩子的左孩子断开，连接p的右孩子
    *p = rc; //rc成为p的新根
}

/**
*	Name...........:    static void leftBalance(AVLTreePtr *p)
*	Description....:	左平衡函数；当新结点插入到左子树导致树失衡时，调用此函数可恢复平衡
*	Param..........:	p：指向最小失衡子树指针的指针
*	Return.........:
*	Precondition...:    
*	Postcondition..:    最小失衡子树恢复平衡；*p指向恢复平衡的子树
**/
static void leftBalance(AVLTreePtr *p)
{
    AVLTreePtr  lc, rd;
    
    if (NULL == *p)
        return;

    lc = (*p)->lchild;
    switch (lc->bf)
    {
    case LH:    //LL型，需要进行右旋，顺时针
        (*p)->bf = lc->bf = EH;
        R_Rotate(p);
        break;
    case RH:    //LR型，需要双旋转
        rd = lc->rchild;
        switch (rd->bf)
        {
        case LH:
            (*p)->bf = RH;
            lc->bf = EH;
            break;
        case EH:
            (*p)->bf = lc->bf = EH;
            break;
        case RH:
            (*p)->bf = EH;
            lc->bf = LH;
            break;
        }
        rd->bf = EH;
        L_Rotate(&((*p)->lchild));  //这里不能为L_Rotate(&lc);否则修改的是lc的值，而p的左子树指针不会改变
        R_Rotate(p);
        break;
    }
}

/**
*	Name...........:    static void rightBalance(AVLTreePtr *p)
*	Description....:	右平衡函数；当新结点插入到右子树导致树失衡时，调用此函数可恢复平衡
*	Param..........:	p：指向最小失衡子树指针的指针
*	Return.........:
*	Precondition...:
*	Postcondition..:    最小失衡子树恢复平衡；*p指向恢复平衡的子树
**/
static void rightBalance(AVLTreePtr *p)
{
    AVLTreePtr rc, ld;

    if (NULL == *p)
        return;
    rc = (*p)->rchild;
    switch (rc->bf)
    {
    case LH:    //右左型，需要进行双旋处理，先顺时针，再逆时针旋转
        ld = rc->lchild;
        switch (ld->bf)
        {
        case LH:
            (*p)->bf = EH;
            rc->bf = RH;
            break;
        case EH:
            (*p)->bf = rc->bf = EH;
            break;
        case RH:
            (*p)->bf = LH;
            rc->bf = EH;
            break;
        }
        ld->bf = EH;
        R_Rotate(&((*p)->rchild));
        L_Rotate(p);
        break;
    case RH:    //右右型，进行单旋处理，逆时针
        rc->bf = (*p)->bf = EH;
        L_Rotate(p);
        break;
    }
}



