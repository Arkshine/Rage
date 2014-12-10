
// Taken from Hamsandwich

#ifndef NEW_UTIL_H
#define NEW_UTIL_H

#include "amxxmodule.h"

extern edict_t *NEW_FirstEdict;
extern bool NEW_Initialized;

/**
 * This is called on the first Spawn() ever hooked.  This would be worldspawn (index 0)
 */
extern void NEW_Initialize(edict_t *Entity);

/**
 * Converts an integer index into an edict pointer
 */
extern edict_t *INDEXENT_NEW(const int Index);

/**
 * Converts an edict pointer into an integer index
 */
extern int ENTINDEX_NEW(const edict_t *Ent);

// Inlined replacement of MF_GetAmxAddr

extern REAL amx_ctof2_(cell x);
extern cell amx_ftoc2_(REAL x);

extern int PrivateToIndex(const void *pdata);

extern void *IndexToPrivate(int index);

extern entvars_t *IndexToEntvar(int index);

extern int EntvarToIndex(entvars_t *pev);

extern edict_t *EntvarToEdict(entvars_t *pev);

#endif // NEW_UTIL_H

