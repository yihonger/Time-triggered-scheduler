
#include "PriQueue.h"

TTSResult PriQueue_Init( PriQueue* pQ, 
                        void** array, 
                        unsigned int size, 
                        ElemCompareFun ElemCompare)
{
    pQ->array = array;
    pQ->rear = 1;
    pQ->size = size;
    pQ->ElemCompare = ElemCompare;

    return TTS_OK;
}

TTSResult PriQueue_IsEmpty(PriQueue* pQ)
{
    return (TTSResult)(pQ->rear == 1);
}

TTSResult PriQueue_IsFull(PriQueue* pQ)
{
    return (TTSResult)(pQ->rear == pQ->size);
}

static void ElemFloatUp(PriQueue* pQ)
{
    if (PriQueue_IsEmpty(pQ)) return;

    unsigned int child = pQ->rear - 1;
    unsigned int parent = child >> 1;
    void* temp;

    while(parent != 0)
    {
        if (pQ->ElemCompare(pQ->array[child], pQ->array[parent]) == -1)
        {
            temp = pQ->array[parent];
            pQ->array[parent] = pQ->array[child];
            pQ->array[child] = temp;
        }
        else
        {
            break;
        }

        child = parent;
        parent = child >> 1;
    }
}

static void ElemSinkDown(PriQueue* pQ)
{
    if (PriQueue_IsEmpty(pQ)) return;

    unsigned int parent = 1;
    unsigned int Lchild = parent << 1;
    unsigned int Rchild = Lchild + 1;
    void* temp;

    while (Lchild < pQ->rear)
    {
        if ((Rchild < pQ->rear ) 
         && (pQ->ElemCompare(pQ->array[Lchild], pQ->array[Rchild]) == 1))
        {
            Lchild = Rchild;
        }

        if (pQ->ElemCompare(pQ->array[parent], pQ->array[Lchild]) == 1)
        {
            temp = pQ->array[parent];
            pQ->array[parent] = pQ->array[Lchild];
            pQ->array[Lchild] = temp;
        }
        else
        {
            break;
        }
        
        parent = Lchild;
        Lchild = parent << 1;
        Rchild = Lchild + 1;
    }
}

TTSResult PriQueue_In(PriQueue* pQ, void* inElem)
{
    if (PriQueue_IsFull(pQ)) return TTS_ERR;
    
    TTS_CRITICAL_ENTER;
    
    pQ->array[pQ->rear++] = inElem;
    ElemFloatUp(pQ);

    TTS_CRITICAL_EXIT;

    return TTS_OK;
}

TTSResult PriQueue_Out(PriQueue* pQ, void** outElem)
{
    if (PriQueue_IsEmpty(pQ)) return TTS_ERR;

    TTS_CRITICAL_ENTER;

    *outElem = pQ->array[1];
    
    pQ->array[1] = pQ->array[--pQ->rear];
    ElemSinkDown(pQ);

    TTS_CRITICAL_EXIT;

    return TTS_OK;
}

TTSResult PriQueue_GetHead(PriQueue* pQ, void** headElem)
{
    if (PriQueue_IsEmpty(pQ)) return TTS_ERR;

    *headElem = pQ->array[1];
    
    return TTS_OK;
}
