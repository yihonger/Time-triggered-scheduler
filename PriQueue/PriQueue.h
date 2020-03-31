
#ifndef TTS_PRI_QUEUE_H
#define TTS_PRI_QUEUE_H

#include "../TimTrigSched/TTSCfg.h"

typedef int (*ElemCompareFun)(void*, void*);

typedef struct 
{
    void** array;
    unsigned int rear;
    unsigned int size;
    ElemCompareFun ElemCompare;
}PriQueue;

TTSResult PriQueue_Init( PriQueue* pQ, 
                        void** array, 
                        unsigned int size, 
                        ElemCompareFun ElemCompare);
TTSResult PriQueue_IsEmpty(PriQueue* pQ);
TTSResult PriQueue_IsFull(PriQueue* pQ);
TTSResult PriQueue_In(PriQueue* pQ, void* inElem);
TTSResult PriQueue_Out(PriQueue* pQ, void** outElem);
TTSResult PriQueue_GetHead(PriQueue* pQ, void** headElem);

#endif
