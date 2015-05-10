// vim: set ts=4 sw=4 tw=99 noet:
//
// AMX Mod X, based on AMX Mod by Aleksander Naszko ("OLO").
// Copyright (C) The AMX Mod X Development Team.
//
// This software is licensed under the GNU General Public License, version 3 or higher.
// Additional exceptions apply. For full license details, see LICENSE.txt or visit:
//     https://alliedmods.net/amxmodx-license

//
// Ham Sandwich Module
//

#ifndef RETURNHANDLER_H
#define RETURNHANDLER_H

#include "ham_utils.h" 
#include <am-vector.h>
#include <am-string.h>
#include <sh_stack.h>

#include "CStaticVector.h"
#include "sh_static_stack.h"


enum
{
	RET_VOID,
	RET_BOOL,
	RET_INTEGER,
	RET_SHORT,
	RET_FLOAT,
	RET_VECTOR,
	RET_STRING,
	RET_CBASE,
	RET_ENTVAR,
	RET_EDICT,
	RET_TRACE,
	RET_ITEMINFO
};

typedef struct
{
	int iSlot;
	int iPosition;
	const char *pszAmmo1;
	int iMaxAmmo1;
	const char *pszAmmo2;
	int iMaxAmmo2;
	const char *pszName;
	int iMaxClip;
	int iId;
	int iFlags;
	int iWeight;
}
ItemInfo;

enum
{
	ItemInfo_iSlot,
	ItemInfo_iPosition,
	ItemInfo_pszAmmo1,
	ItemInfo_iMaxAmmo1,
	ItemInfo_pszAmmo2,
	ItemInfo_iMaxAmmo2,
	ItemInfo_pszName,
	ItemInfo_iMaxClip,
	ItemInfo_iId,
	ItemInfo_iFlags,
	ItemInfo_iWeight
};

// Container for return and parameter data.
// Contains a void pointer, and a flag telling what it contains.
class Data
{
private:
	void		*m_data;
	int			*m_index;
	int			 m_type;

	bool IsSet(void)
	{
		return (m_type != RET_VOID &&
				m_data != NULL);
	};
	bool IsType(const int type)
	{
		return (m_type == type);
	};

public:
	Data()
	{ /* nothing */	};

	Data(int type, void *ptr) : m_data(ptr), m_index(NULL), m_type(type)
	{ /* nothing */ };

	Data(int type, void *ptr, int *cptr) : m_data(ptr), m_index(NULL), m_type(type)
	{ /* nothing */ };

	~Data()
	{ /* nothing */	};

	void Init(int type, void *ptr)
	{
		m_data = ptr;
		m_index = NULL;
		m_type = type;
	}

	void Init(int type, void *ptr, int *cptr)
	{
		m_data = ptr;
		m_index = NULL;
		m_type = type;
	}

	int GetType()
	{
		return m_type;
	};

	// All Get/Set value natives return < 0 on failure.
	// -1: Wrong type
	// -2: Bad data pointer (void, etc).
	int SetInt(cell *data)
	{
		if (!IsSet())
		{
			return -2;
		}
		if (IsType(RET_INTEGER))
		{
			*(reinterpret_cast<int *>(m_data))=*data;
			return 0;
		}
		else if (IsType(RET_BOOL))
		{
			*(reinterpret_cast<bool *>(m_data)) = *data > 0;
			return 0;
		}
		else if (IsType(RET_SHORT))
		{
			*(reinterpret_cast<short *>(m_data)) = *data;
			return 0;
		}
		else if (IsType(RET_ITEMINFO))
		{
			*(reinterpret_cast<int *>(m_data)) = *data;
			return 0;
		}
		else if (IsType(RET_TRACE))
		{
			*(reinterpret_cast<int *>(m_data))=*data;
			return 0;
		}

		return -1;
	};

	int SetFloat(cell *data)
	{
		if (!IsSet())
		{
			return -2;
		}
		if (!IsType(RET_FLOAT))
		{
			return -1;
		}
		*(reinterpret_cast<REAL *>(m_data))=amx_ctof2(*data);

		return 0;
	};
	int SetVector(cell *data)
	{
		if (!IsSet())
		{
			return -2;
		}
		if (!IsType(RET_VECTOR))
		{
			return -1;
		}
		Vector *vec=reinterpret_cast<Vector *>(m_data);

		vec->x=amx_ctof2(data[0]);
		vec->y=amx_ctof2(data[1]);
		vec->z=amx_ctof2(data[2]);

		return 0;
	};
	int SetString(cell *data)
	{
		if (!IsSet())
		{
			return -2;
		}
		if (!IsType(RET_STRING))
		{
			return -1;
		}

		ke::AString *str=reinterpret_cast<ke::AString *>(m_data);

		cell *i=data;
		size_t len=0;

		while (*i!=0)
		{
			i++;
			len++;
		};
		char *temp=new char[len+1];
		i=data;
		char *j=temp;

		while ((*j++=*i++)!=0)
		{
			/* nothing */
		}

		*str = temp;

		delete[] temp;

		return 0;
	};

	int SetEntity(cell *data)
	{
		if (!IsSet())
		{
			return -2;
		}
		if (IsType(RET_CBASE))
		{
			*(reinterpret_cast<void **>(m_data))=IndexToPrivate(*data);
			if (m_index != 0)
			{
				*m_index=*data;
			}

			return 0;
		}
		else if (IsType(RET_ENTVAR))
		{
			*(reinterpret_cast<entvars_t **>(m_data))=IndexToEntvar(*data);
			if (m_index != 0)
			{
				*m_index=*data;
			}

			return 0;
		}
		else if (IsType(RET_EDICT))
		{
			*(reinterpret_cast<edict_t **>(m_data)) = IndexToEdict(*data);
			if (m_index != 0)
			{
				*m_index = *data;
			}

			return 0;
		}
		return -1;
	};

	int GetInt(cell *data)
	{
		if (!IsSet())
		{
			return -2;
		}
		if (IsType(RET_INTEGER))
		{
			*data=*(reinterpret_cast<int *>(m_data));

			return 0;
		}
		else if (IsType(RET_BOOL))
		{
			*data = *(reinterpret_cast<bool *>(m_data));

			return 0;
		}

		else if (IsType(RET_SHORT))
		{
			*data = *(reinterpret_cast<short *>(m_data));

			return 0;
		}
		else if (IsType(RET_ITEMINFO))
		{
			*data = *(reinterpret_cast<int *>(m_data));

			return 0;
		}
		else if (IsType(RET_TRACE))
		{
			*data=*(reinterpret_cast<int *>(m_data));

			return 0;
		}

		return -1;
	};
	int GetFloat(cell *data)
	{
		if (!IsSet())
		{
			return -2;
		}
		if (!IsType(RET_FLOAT))
		{
			return -1;
		}
		*data=amx_ftoc2(*(reinterpret_cast<REAL *>(m_data)));

		return 0;
	};
	int GetVector(cell *data)
	{
		if (!IsSet())
		{
			return -2;
		}
		if (!IsType(RET_VECTOR))
		{
			return -1;
		}
		Vector *vec=reinterpret_cast<Vector *>(m_data);
		data[0]=amx_ftoc2(vec->x);
		data[1]=amx_ftoc2(vec->y);
		data[2]=amx_ftoc2(vec->z);

		return 0;
	};
	int GetString(cell *data, int len)
	{
		if (!IsSet())
		{
			return -2;
		}
		if (!IsType(RET_STRING))
		{
			return -1;
		}
		const char *i=(reinterpret_cast<ke::AString *>(m_data)->chars());

		while (len-- && 
			  (*data++=*i++)!='\0')
		{
			/* nothing */
		};
		return 0;
	};
	int GetEntity(cell *data)
	{
		if (!IsSet())
		{
			return -2;
		}
		if (IsType(RET_CBASE))
		{
			*data=PrivateToIndex(m_data);

			return 0;
		}
		else if (IsType(RET_ENTVAR))
		{
			*data=EntvarToIndex(reinterpret_cast<entvars_t *>(m_data));

			return 0;
		}
		else if (IsType(RET_EDICT))
		{
			*data = EdictToIndex(reinterpret_cast<edict_t *>(m_data));

			return 0;
		}
		return -1;
	}
};

#define HAM_MAX_FORWARD_PARAMS 16
#define HAM_MAX_CALL_DEPTH 64

typedef CStaticVector<Data*, HAM_MAX_FORWARD_PARAMS> CParamsStorage;

extern CStaticStack<Data*, HAM_MAX_CALL_DEPTH> ReturnStack;
extern CStaticStack<Data*, HAM_MAX_CALL_DEPTH> OrigReturnStack;
extern CStaticStack<CParamsStorage*, HAM_MAX_CALL_DEPTH> ParamStack;
extern CStaticStack<int*, HAM_MAX_CALL_DEPTH> ReturnStatus;

#endif
