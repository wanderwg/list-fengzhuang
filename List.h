#pragma once
namespace wg
{
	template<class T>
	struct ListNode
	{
		ListNode(const T& data = T())
			:_pNext(nullptr)
			, _pPre(nullptr)
			, _data(data)
		{}

		ListNode<T>* _pNext;
		ListNode<T>* _pPre;
		T _data;
	};

	template<class T>
	struct listiterator
	{
		typedef ListNode<T> Node;
		typedef listiterator<T> Self;
	public:
		listiterator(Node* pNode)
			:_pNode(pNode)
		{}

		T& operator*()
		{
			return _pNode->_data;
		}
		T* operator->()
		{
			return &(operator*());
		}

		//移动
		Self& operator++()
		{
			_pNode = _pNode->_pNext;
			return *this;
		}
		Self operator++(int)
		{
			Self temp(*this);
			_pNode = _pNode->_pNext;
			return temp;
		}
		Self& operator--()
		{
			_pNode = _pNode->_pPre;
			return *this;
		}
		Self operator--(int)
		{
			Self temp(*this);
			_pNode = _pNode->_pPre;
			return temp;
		}

		//比较
		bool operator!=(const Self& s)const
		{
			return _pNode != s._pNode;
		}
		bool operator==(const Self& s)const
		{
			return _pNode == s._pNode;
		}

		Node* _pNode;
	};
	template<class T>
	class list
	{
		typedef ListNode<T> Node;
	public:
		typedef listiterator<T> iterator;
	public:
		list()
		{
			CreateHead();
		}
		list(int n, const T& data)
		{
			CreateHead();
			for (int i = 0; i < n; ++i)
				push_back(data);
		}
		list(const list<T>& L)
		{
			CreateHead();
			Node* pCur = L._pHead->_pNext;
			while (pCur!=L._pHead)
			{
				push_back(pCur->_data);
				pCur = pCur->_pNext;
			}
		}
		template<class Iterator>
		list(Iterator first, Iterator last)
		{
			CreateHead();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		////////////////////////////////////////////////
		list<T>& operator=(const list<T> L)
		{
			this->swap(L);
			return *this;
		}
		~list()
		{
			clear();
			delete _pHead;
			_pHead = nullptr;
		}

		///////////////////////////////////////////////////
		//iterator
		iterator begin()
		{
			return iterator(_pHead->_pNext);
		}
		iterator end()
		{
			return iterator(_pHead);
		}
		///////////////////////////////////////////////////
		//capacity
		bool empty()const
		{
			return _pHead->_pNext == _pHead;
		}

		size_t size()const
		{
			size_t count = 0;
			Node* pCur = _pHead->_pNext;
			while (pCur != _pHead)
			{
				count++;
				pCur = pCur->_pNext;
			}
			return count;
		}
		void resize(size_t newsize, const T& data = T())
		{
			size_t oldsize = size();
			if (newsize <= oldsize)
			{
				for (size_t i = newsize; i < oldsize; ++i)
					pop_back();
			}
			else
			{
				for (size_t i = oldsize; i < newsize; ++i)
					push_back(data);
			}
		}

		///////////////////////////////////////////////////////////////////
		//access
		T& front()
		{
			return _pHead->_pNext->_data;
		}
		const T& front()const
		{
			return _pHead->_pNext->_data;
		}

		T& back()
		{
			return _pHead->_pPre->_data;
		}
		const T& back()const
		{
			return _pHead->_pPre->_data;
		}
		////////////////////////////////////////////////
		//modify
		void push_back(const T& data)
		{
			Node* pNewNode = new Node(data);
			pNewNode->_pPre = _pHead->_pPre;
			pNewNode->_pNext = _pHead;
			_pHead->_pPre->_pNext = pNewNode;
			_pHead->_pPre = pNewNode;
		}
		void pop_back()
		{
			if (empty())
				return;
			Node* pDel = _pHead->_pPre;
			pDel->_pPre->_pNext = _pHead;
			_pHead->_pPre = pDel->_pPre;
			delete pDel;
		}
		void push_front(const T& data)
		{
			Node* pNewNode = new Node(data);
			pNewNode->_pPre = _pHead;
			pNewNode->_pNext = _pHead->_pNext;
			_pHead->_pNext->_pPre = pNewNode;
			_pHead->_pNext = pNewNode;

		}
		void pop_front()
		{
			if (empty())
				return;
			Node* pDel = _pHead->_pNext;
			_pHead->_pNext = pDel->_pNext;
			pDel->_pNext->_pPre = _pHead;
			delete pDel;
		}
		void clear()
		{
			Node* pCur = _pHead->_pNext;
			while (pCur != _pHead)//ͷɾ
			{
				_pHead->_pNext = pCur->_pNext;
				delete pCur;
				pCur = _pHead->_pNext;
			}
			_pHead->_pNext = _pHead;
			_pHead->_pPre = _pHead;
		}
		void swap(list<T>& l)
		{
			swap(_pHead, l._pHead);
		}

		iterator insert(iterator pos, const T& data)
		{
			Node* pNewNode = new Node(data);
			Node* pCur = pos._pNode;
			pNewNode->_pNext = pCur;
			pNewNode->_pPre = pCur->_pPre;
			pNewNode->_pPre->_pNext = pNewNode;
			pCur->_pPre = pCur;

			return iterator(pNewNode);
		}

		iterator erase(iterator pos)
		{
			if (pos == end())
				return end();
			Node* pDel = pos._pNode;
			Node* pRet = pDel->_pNext;
			pDel->_pNext->_pPre = pDel->_pPre;
			pDel->_pPre->_pNext = pDel->_pNext;
			delete pDel;

			return iterator(pRet);
		}

	private:
		void CreateHead()
		{
			_pHead = new Node;
			_pHead->_pNext = _pHead;
			_pHead->_pPre = _pHead;
		}
	private:
		Node* _pHead;
	};
}

#include <iostream>
#include <vector>
using namespace std;

void TestList()
{
	wg::list<int> L1;
	wg::list<int> L2(10, 2);

}