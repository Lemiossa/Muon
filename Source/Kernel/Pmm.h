/**
 * Pmm.h
 * Created by Matheus Leme Da Silva
 */
#ifndef PMM_H
#define PMM_H
#include "Types.h"
#include "E820.h"

void PMMInit(struct E820Entry *table, U8 entries);
void *PMMAllocPage(void);
void PMMFreePage(void *p);

#endif // PMM_H
