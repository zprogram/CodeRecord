#pragma once

//����ͳһ�Ĵ�����
enum Status
{
	RESULT_FALSE = 0,       //ʧ��
	RESULT_TRUE,            //�ɹ�
	RESULT_ERR_OVERFLOW,    //����_����Խ��
	RESULT_ERR_PARAMTER,    //����_��������
	RESULT_ERR_OVERMAXSIZE, //����_�����������
	RESULT_ERR_UNKOWN       //����_δ֪����
};

#define ElemType int

class CMyTree
{
public:
	//�������ڵ�
	typedef struct _NODE
	{
		ElemType Data;
		_NODE * pLChild;  //������
		_NODE * pRChild;  //������
		_NODE * pFather;  //���ڵ�
	}NODE, *PNODE;
public:
	CMyTree();
	virtual ~CMyTree();


	virtual Status Insert(  /**�����в����½ڵ�,����ֵ��Ϊe,Ԫ�ظ�����1*/
		ElemType e,            //[in] �������ֵ
		PNODE pNode = nullptr  //[out] ���ز���Ľڵ�����
		);

	virtual Status Delete(  /**��ֵΪe�Ľڵ�������ɾ��,Ԫ�ظ�����1*/
		ElemType e,            //[in] ɾ����Ԫ��ֵ
		PNODE pNode = nullptr  //[out]����ɾ���Ľڵ�����(ֻ�и��ڵ�ָ����Ч)
		);

	Status ClearBiTree( /**����������Ϊ����*/
		);

	Status BiTreeEmpty( /**����Ϊ��,����true,���򷵻�false*/
		bool & isEmpty   //[out]�Ƿ�Ϊ��
		);

	Status BiTreeDepth( /**�����������*/
		PNODE pChildTree,//[in] ��Ҫ����ȵ�����
		int & nTreeDepth //[out]�������
		);

	Status PreOrderTraverse(        /**ǰ�����������*/
		PNODE pChildTree,            //[in]��Ҫ����������
		Status(*Visit)(ElemType &e)//[in]��ÿ���ڵ�,�����ô˺���
		);

	Status InOrderTraverse(       /**�������������*/
		PNODE pChildTree,          //[in]��Ҫ����������
		Status(*Visit)(ElemType &e)//[in]��ÿ���ڵ�,�����ô˺���
		);

	Status PostOrderTraverse(     /**�������������*/
		PNODE pChildTree,          //[in]��Ҫ����������
		Status(*Visit)(ElemType &e)//[in]��ÿ���ڵ�,�����ô˺���
		);

	Status LevelOrderTraverse(    /**�������������*/
		PNODE pChildTree,          //[in]��Ҫ����������
		Status(*Visit)(ElemType &e)//[in]��ÿ���ڵ�,�����ô˺���
		);

	/**��������ʾ,��ӡ�������������Ľṹ*/
	void show();
	void printTree(PNODE & pChildNode, int nLayer);

	PNODE m_pRoot;      //���ڵ�ָ��

protected:
	int m_nCurrNum;     //��ǰԪ�ظ���

	/**���ش�ָ��������ʼ��,�ҵ���һ��ֵ��e��ȵ�Ԫ��;
	�ҵ��򷵻ظýڵ�ָ��,
	û�ҵ��򷵻ز���λ�õĸ��ڵ�ָ��*/
	Status LocateElem(PNODE pChildTree,
		ElemType e,
		PNODE & pTree);

	/**ȡ�����е����ֵ*/
	Status GetMax(PNODE pChildTree, PNODE & pNode);
	/**ȡ�����е���Сֵ*/
	Status GetMin(PNODE pChildTree, PNODE & pNode);

	/**��������Ϊ����*/
	Status ClearBiTree(PNODE & pChildTree);
};



