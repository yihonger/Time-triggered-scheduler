
#include "DlyList.h"

TTSResult DlyList_Init(DlyList* dL, 
                        PriQueue (*dlyListArray)[2],
                        unsigned int* tick,
                        TickCompareFun TickCompare)
{
    dL->dlyListArray = dlyListArray;
    dL->curListIdx = 0;
    dL->tick = tick;
    dL->TickCompare = TickCompare;
    return TTS_OK;
}

TTSResult DlyList_In(DlyList* dL, void* inElem)
{
    unsigned int insertList = dL->curListIdx;
    if (dL->TickCompare(dL->tick, inElem) == 1)
    {
        insertList ^= 1u;
    }

    return PriQueue_In(dL->dlyListArray[insertList], inElem);
}

TTSResult DlyList_Out(DlyList* dL, void** outElem)
{
    unsigned int anotherListIdx = dL->curListIdx ^ 1u;

    if ((!PriQueue_IsEmpty(&(*dL->dlyListArray)[anotherListIdx]))
     && (PriQueue_IsEmpty(&(*dL->dlyListArray)[dL->curListIdx])))
    {
        dL->curListIdx = anotherListIdx;
    }

    return PriQueue_Out(dL->dlyListArray[dL->curListIdx], outElem);
}

TTSResult DlyList_GetHead(DlyList* dL, void** headElem)
{
    unsigned int anotherListIdx = dL->curListIdx ^ 1u;

    if ((!PriQueue_IsEmpty(&(*dL->dlyListArray)[anotherListIdx]))
     && (PriQueue_IsEmpty(&(*dL->dlyListArray)[dL->curListIdx])))
    {
        dL->curListIdx = anotherListIdx;
    }

    return PriQueue_GetHead(dL->dlyListArray[dL->curListIdx], headElem);  
}


