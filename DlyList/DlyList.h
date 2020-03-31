
#ifndef TTS_DLY_LIST_H
#define TTS_DLY_LIST_H

#include "../TimTrigSched/TTSCfg.h"
#include "../PriQueue/PriQueue.h"

typedef int (*TickCompareFun) (unsigned int* tick, void* elem);

typedef struct 
{
    PriQueue (*dlyListArray)[2];
    unsigned int curListIdx;
    unsigned int* tick;
    TickCompareFun TickCompare;
}DlyList;

TTSResult DlyList_Init(  DlyList* dL, 
                        PriQueue (*dlyListArray)[2],
                        unsigned int* tick,
                        TickCompareFun TickCompare);
TTSResult DlyList_In(DlyList* dL, void* inElem);
TTSResult DlyList_Out(DlyList* dL, void** outElem);
TTSResult DlyList_GetHead(DlyList* dL, void** headElem);

#endif
