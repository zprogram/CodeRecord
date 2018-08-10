#include "stdafx.h"
#include "Mytree.h"





CMyTree::~CMyTree()
{
	//ClearList();
}

/************************************
* Access:    public
* ��������:  ��L�е�i��Ԫ��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1
*
* �����б�:
*   ElementType e:   [in] �������Ԫ��
*   int i:           [in] �����λ��
*
* ����ֵ:    Status
*
*************************************/
Status CMyTree::Insert(ElemType e, PNODE pNode/* = nullptr */)
{
	if (m_pRoot == nullptr)
	{
		m_pRoot = new NODE;
		m_pRoot->Data = e;

		m_nCurrNum++;
		if (pNode)
		{
			*pNode = *m_pRoot;
		}
		return RESULT_TRUE;
	}
	PNODE pReNode;
	Status checkIsHave = LocateElem(m_pRoot, e, PNODE pNode);
	if (checkIsHave = RESULT_TRUE)
	{
		return RESULT_ERR_PARAMTER;

	}
	PNODE pNewNode = new NODE();
	pNewNode->Data = e;
	pNewNode->pFather = pReNode;
	if (e<pReNode->Data)
	{
		pReNode->pLChild = pNewNode;
	}
	else if (e>pReNode->Data)
	{
		pReNode->pLChild = pNewNode;
	}

	m_nCurrNum++;

	if (pNode)
	{
		*pNode = *pNewNode;
	}
	return RESULT_TRUE;
}

 
Status CMyTree::Insert(ElemType e, PNODE pNode/* = nullptr */)
{
	if (m_pRoot == nullptr)
	{
		m_pRoot = new NODE;
		m_pRoot->Data = e;

		m_nCurrNum++;
		if (pNode)
		{
			*pNode = *m_pRoot;

	}

	PNODE pReNode;
	Status checkIsHave = LocateElem(m_pRoot, e, pReNode);
	if (checkIsHave == RESULT_FALSE)
	{
		return RESULT_ERR_PARAMTER;
	}
	while (true)
	{
		if (pReNode->pLChild == nullptr && pReNode->pRChild == nullptr)
		{

			if (pReNode->pFather->pLChild == pReNode)
			{
				pReNode->pFather->pLChild = nullptr;
			}
			else
			{
				pReNode->pFather->pRChild = nullptr;


			}

			if (pNode)
			{
				*pNode = *pReNode;

			}
			delete pReNode;

			break;

		}

		int LChildDepyh, RChilDepth;
		BiTreeDepth(pReNode->pLChild, LChildDepyh);
		BiTreeDepth(pNode->pRChild, RChilDepth);
		PNODE pExchangeNode;
		if (LChildDepyh > RChilDepth)
		{

			GetMax(pReNode > pLChild, pExchangeNode);

		}
		else
		{
			GetMin(pNode->pLChild, pExchangeNode);
		}
		pReNode->Data = pExchangeNode->Data;
		pReNode = pExchangeNode;
	}
	m_nCurrNum--;

	return RESULT_TRUE;

}
