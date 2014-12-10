
#include <NEW_Util.h>
#include <global/global.h>

edict_t *NEW_FirstEdict;
bool NEW_Initialized;

/**
 * This is called on the first Spawn() ever hooked.  This would be worldspawn (index 0)
 */
void NEW_Initialize(edict_t *Entity)
{
	if(NEW_Initialized)
		return;

	NEW_FirstEdict=Entity;
	NEW_Initialized=true;
}

/**
 * Converts an integer index into an edict pointer
 */
edict_t *INDEXENT_NEW(const int Index)
{
	return (edict_t *)(NEW_FirstEdict + Index);
};

/**
 * Converts an edict pointer into an integer index
 */
int ENTINDEX_NEW(const edict_t *Ent)
{
	return (int)(Ent - NEW_FirstEdict);
};

// Inlined replacement of MF_GetAmxAddr

REAL amx_ctof2_(cell x)
{
	return *(REAL*)&x;
}

cell amx_ftoc2_(REAL x)
{
	return *(cell*)&x;
}

int PrivateToIndex(const void *pdata)
{
	if (pdata==NULL)
	{
		return -1;
	}
	char *ptr=(char*)pdata;

	ptr += Global::PEV;
	
	entvars_t *pev=*(entvars_t **)ptr;

	if (pev==NULL)
	{
		return -1;
	}
	
	if (pev->pContainingEntity==NULL)
	{
		return -1;
	}

	return ENTINDEX_NEW(pev->pContainingEntity);
};

void *IndexToPrivate(int index)
{
	return INDEXENT_NEW(index)->pvPrivateData;
};

entvars_t *IndexToEntvar(int index)
{
	return &(INDEXENT_NEW(index)->v);
};

int EntvarToIndex(entvars_t *pev)
{
	if (pev==NULL)
	{
		return -1;
	}
	
	if (pev->pContainingEntity==NULL)
	{
		return -1;
	}

	return ENTINDEX_NEW(pev->pContainingEntity);
};

edict_t *EntvarToEdict(entvars_t *pev)
{
	if (pev==NULL)
	{
		return NULL;
	}
	
	return pev->pContainingEntity;
};
