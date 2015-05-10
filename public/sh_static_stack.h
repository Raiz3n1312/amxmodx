/* ======== SourceMM ========
* Copyright (C) 2004-2005 Metamod:Source Development Team
* No warranties of any kind
*
* License: zlib/libpng
*
* Author(s): Pavol "PM OnoTo" Marko
* ============================
*/

#ifndef __SH_STATICSTACK_H__
#define __SH_STATICSTACK_H__

//namespace SourceHook
//{/
	// Vector
	template <class T, unsigned int t_sz> class CStaticStack
	{
		T m_Elements[t_sz];
		size_t m_UsedSize;

	public:
		friend class iterator;
		class iterator
		{
			CStaticStack<T, t_sz> *m_pParent;
			size_t m_Index;
		public:
			iterator(CStaticStack<T, t_sz> *pParent, size_t id) : m_pParent(pParent), m_Index(id)
			{
			}

			iterator(CStaticStack<T, t_sz> *pParent) : m_pParent(pParent), m_Index(0)
			{
			}
			
			iterator() : m_pParent(NULL), m_Index(0)
			{
			}

			T &operator *()
			{
				return m_pParent->m_Elements[m_Index];
			}
			const T &operator *() const
			{
				return m_pParent->m_Elements[m_Index];
			}
			
			T * operator->()
			{
				return m_pParent->m_Elements + m_Index;
			}

			const T * operator->() const
			{
				return m_pParent->m_Elements + m_Index;
			}

			iterator & operator++()		// preincrement
			{
				++m_Index;
				return (*this);
			}

			iterator operator++(int)	// postincrement
			{
				iterator tmp = *this;
				++m_Index;
				return tmp;
			}

			iterator & operator--()		// predecrement
			{
				--m_Index;
				return (*this);
			}

			iterator operator--(int)	// postdecrememnt
			{
				iterator tmp = *this;
				--m_Index;
				return tmp;
			}

			bool operator==(const iterator & right) const
			{
				return (m_pParent == right.m_pParent && m_Index == right.m_Index);
			}

			bool operator!=(const iterator & right) const
			{
				return !(*this == right);
			}
		};

		CStaticStack() :
			m_UsedSize(0)
		{
		}

		CStaticStack(size_t size) : 
			m_UsedSize(0)
		{
		}

		CStaticStack(const CStaticStack &other) :
			m_UsedSize(0)
		{
			m_UsedSize = other.m_UsedSize;
			for (size_t i = 0; i < m_UsedSize; ++i)
				m_Elements[i] = other.m_Elements[i];
		}

		~CStaticStack()
		{
		}
		
		void operator=(const CStaticStack &other)
		{
			m_UsedSize = other.m_UsedSize;
			for (size_t i = 0; i < m_UsedSize; ++i)
				m_Elements[i] = other.m_Elements[i];
		}

		bool push(const T &val)
		{
			if (m_UsedSize + 1 >= t_sz)
			{
				return false;
			}
			m_Elements[m_UsedSize++] = val;
			return true;
		}

		void pop()
		{
			--m_UsedSize;
		}

		T &front()
		{
			return m_Elements[m_UsedSize - 1];
		}

		const T &front() const
		{
			return m_Elements[m_UsedSize - 1];
		}

		iterator begin()
		{
			return iterator(this, 0);
		}
		iterator end()
		{
			return iterator(this, m_UsedSize);
		}

		size_t size()
		{
			return m_UsedSize;
		}
		size_t capacity()
		{
			return t_sz;
		}
		bool empty()
		{
			return m_UsedSize == 0 ? true : false;
		}
	};
//};	//namespace SourceHook

#endif
