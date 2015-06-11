/***************************************************************************************
*	FileName				:	AVLTree.c
*	CopyRight				:
*	ModuleName				:	
*
*	CPU						:	
*	RTOS					:
*
*	Create Date				:	2015/06/10
*	Author/Corportation		:	�¼���
*
*	Abstract Description	:   ƽ�������
*
*--------------------------------Revision History--------------------------------------
*	No	version		Date		    Revised By			Item			Description
*	1   v1.0        2015/06/10      �¼���              All             Create the file 
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
*	Description....:	��ʼ��ƽ�������
*	Param..........:	t:ָ��ƽ�������ָ���ָ��
*	Return.........:    TRUE:��ʼ���ɹ�
                        FALSE:��ʼ��ʧ��
*	Precondition...:    ʹ��ǰҪ�ȶ���һ��AVLTreePtr���ͱ����������ַ��Ϊʵ��
*	Postcondition..:    *tָ��һ�ÿ���
**/
Status  initAVLTree(AVLTreePtr *t)
{
    *t = NULL;
    return TRUE;
}

/**
*	Name...........:    Status  destroyAVLTree(AVLTreePtr *t);
*	Description....:	����ƽ�������
*	Param..........:	t��ָ��ƽ�������ָ���ָ��
*	Return.........:    TRUE�����ٳɹ�
                        FALSE������ʧ��
*	Precondition...:
*	Postcondition..:    ������������ݣ���ô�������ݻᱻ���٣�*tָ��һ�ÿ���
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
*	Description....:	��ƽ�����������ָ���ؼ���
*	Param..........:	t��ƽ�������ָ��
                        key��Ҫ���ҵ�ָ���ؼ���
*	Return.........:    NULL��ƽ�������û��ָ���ؼ���
                        ��NULL��ָ���ؼ��ֽ��ָ��
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
*	Description....:	��ƽ�����������ָ��Ԫ��
*	Param..........:	t��ָ��ƽ�������ָ���ָ��
                        elem��ָ�������Ԫ��
*	Return.........:    TRUE������ɹ�
                        FALSE������ʧ��
*	Precondition...:
*	Postcondition..:    ������ɹ���*t��ָ��һ�ò������½���ƽ���������������ʧ�ܣ�*t��ƽ�������)����ı�
**/
Status  insertAVLTree_Interface(AVLTreePtr *t, RcdType elem)
{
    Status  taller;
    return insertAVLTree_Interface(t, elem, &taller);
}

/**
*	Name...........:    Status isEmpty_AVLTree(AVLTreePtr t);
*	Description....:	�ж����Ƿ�Ϊ��
*	Param..........:	t��ƽ�������ָ��
*	Return.........:    TRUE����
                        FALSE���ǿ�
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
*	Description....:	��ȡ���ĸ߶�
*	Param..........:	t��ƽ�������ָ��
*	Return.........:    ���ĸ߶ȣ�0��ʾ����
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
*	Description....:	��ȡ���Ľ����
*	Param..........:	t��ƽ�������ָ��
*	Return.........:    ���Ľ������0��ʾ����
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
*	Description....:	��ƽ�����������ָ��Ԫ��
*	Param..........:	t��ָ��ƽ�������ָ���ָ��
                        elem��ָ�������Ԫ��
                        taller����־ֵ������ʱ������һ��Status��������ֵʵ�μ���
*	Return.........:    TRUE������ɹ�
                        FALSE������ʧ��
*	Precondition...:
*	Postcondition..:    ������ɹ���*t��ָ��һ�ò������½���ƽ���������������ʧ�ܣ�*t��ƽ�������)����ı䣬*taller����ΪFALSE
**/
static Status  insertAVLTree_Interface(AVLTreePtr *t, RcdType elem, Status *taller)
{
    if (NULL == *t) //��Ϊ�գ���ֱ������һ����㣬����Ϊ���ڵ�
    {
        *t = (AVLTreePtr)malloc(sizeof(AVLTreeNode));
        if (NULL == *t)
            return OVERFLOW;
        (*t)->bf = EH;
        (*t)->data = elem;
        (*t)->lchild = (*t)->rchild = NULL;
        *taller = TRUE; //�������½�㣬��*tallerΪTRUE
        return TRUE;
    }
    else if (elem.key == (*t)->data.key)    //Ҫ����Ľ��͸������ͬ�����ò���
    {
        *taller = FALSE;
        return FALSE;
    }
    else if (elem.key < (*t)->data.key) //elemֵ�ȸ����С������뵽������
    {
        if (FALSE == insertAVLTree_Interface((*t)->rchild, elem, taller))
            return FALSE;
        if (TRUE == *taller)
        {
            switch ((*t)->bf)
            {
            case LH:    //��������������������߶Ȳ�Ϊ2    
                leftBalance(t); //��ƽ�⴦��
                *taller = FALSE;    //����󣬲����ٴ����ˣ���tallerΪFALSE
                break;
            case EH:    //ԭ���������ȸ�
                (*t)->bf = LH;  //�������������ƽ�����ӱ�Ϊ1
                *taller = TRUE; //��tallerΪTRUE
                break;
            case RH:    //ԭ����������������
                (*t)->bf = EH;  //�������������ƽ�����ӱ�Ϊ0
                *taller = FALSE;
                break;
            }
        }
    }
    else if (elem.key > (*t)->data.key) //elemֵ�ȸ���������뵽������
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
*	Description....:	LL��ʧ�������������������˳ʱ�룩
*	Param..........:	p��ָ����Сʧ������ָ���ָ��
*	Return.........:    
*	Precondition...:
*	Postcondition..:    ��Сʧ�������ָ�ƽ�⣻��Сʧ������A������ΪB������ת�ɹ���B����A��λ�ã�A��ΪB���Һ��ӣ����B�����Һ���Br����Br��ΪA��������
**/
static void R_Rotate(AVLTreePtr *p)
{
    AVLTreePtr lc;

    if (NULL == *p)
        return;

    lc = (*p)->lchild;  // lcָ��p��������
    (*p)->lchild = lc->rchild;  //lc������������Ϊp����������
    lc->rchild = *p;    //��p���Ϊlc����������
    *p = lc;    //pָ���µĸ����
}

/**
*	Name...........:    static void L_Rotate(AVLTreePtr *p);
*	Description....:	RR��ʧ���������������������ʱ�룩
*	Param..........:	p��ָ����Сʧ������ָ���ָ��
*	Return.........:    
*	Precondition...:
*	Postcondition..:    ��Сʧ�������ָ�ƽ�⣻��Сʧ������A���Һ���ΪB��B����A��Ϊ��Сʧ���������¸���A��ΪB�����ӣ����B�����ӣ���Bl��ΪA���Һ���
**/
static void L_Rotate(AVLTreePtr *p)
{
    AVLTreePtr rc;

    if (NULL == *p)
        return;

    rc = (*p)->rchild;  //rc������p���Һ���
    (*p)->rchild = rc->lchild; //p���Һ��ӵ����ӶϿ�������p���Һ���
    *p = rc; //rc��Ϊp���¸�
}

/**
*	Name...........:    static void leftBalance(AVLTreePtr *p)
*	Description....:	��ƽ�⺯�������½����뵽������������ʧ��ʱ�����ô˺����ɻָ�ƽ��
*	Param..........:	p��ָ����Сʧ������ָ���ָ��
*	Return.........:
*	Precondition...:    
*	Postcondition..:    ��Сʧ�������ָ�ƽ�⣻*pָ��ָ�ƽ�������
**/
static void leftBalance(AVLTreePtr *p)
{
    AVLTreePtr  lc, rd;
    
    if (NULL == *p)
        return;

    lc = (*p)->lchild;
    switch (lc->bf)
    {
    case LH:    //LL�ͣ���Ҫ����������˳ʱ��
        (*p)->bf = lc->bf = EH;
        R_Rotate(p);
        break;
    case RH:    //LR�ͣ���Ҫ˫��ת
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
        L_Rotate(&((*p)->lchild));  //���ﲻ��ΪL_Rotate(&lc);�����޸ĵ���lc��ֵ����p��������ָ�벻��ı�
        R_Rotate(p);
        break;
    }
}

/**
*	Name...........:    static void rightBalance(AVLTreePtr *p)
*	Description....:	��ƽ�⺯�������½����뵽������������ʧ��ʱ�����ô˺����ɻָ�ƽ��
*	Param..........:	p��ָ����Сʧ������ָ���ָ��
*	Return.........:
*	Precondition...:
*	Postcondition..:    ��Сʧ�������ָ�ƽ�⣻*pָ��ָ�ƽ�������
**/
static void rightBalance(AVLTreePtr *p)
{
    AVLTreePtr rc, ld;

    if (NULL == *p)
        return;
    rc = (*p)->rchild;
    switch (rc->bf)
    {
    case LH:    //�����ͣ���Ҫ����˫��������˳ʱ�룬����ʱ����ת
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
    case RH:    //�����ͣ����е���������ʱ��
        rc->bf = (*p)->bf = EH;
        L_Rotate(p);
        break;
    }
}



