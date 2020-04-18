
#ifndef TTS_TASK_H
#define TTS_TASK_H

#include "../TimTrigSched/TTSCfg.h"

typedef struct
{
    TaskFun taskFun;
    unsigned int cycle;
    unsigned int priority;
    unsigned int runTick;  
}Task;

TTSResult Task_Init(    Task* task,
                        TaskFun taskFun,
                        unsigned int cycle,
                        unsigned int priority);

int Task_PriCompareEE(void* elemA, void* elemB);
int Task_tickCompareEE(void* elemA, void* elemB);
int Task_tickCompareTE(unsigned int* tick, void* elem);

#endif
