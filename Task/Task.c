
#include "Task.h"

TTSResult Task_Init(    Task* task,
                        TaskFun taskFun,
                        unsigned int cycle,
                        unsigned int priority)
{
    task->taskFun = taskFun;
    task->cycle = cycle;
    task->priority = priority;
    task->runTick = 0;

    return TTS_OK;
}

int Task_PriCompareEE(void* elemA, void* elemB)
{
    if (((Task*)elemA)->priority < ((Task*)elemB)->priority) return -1;
    else if (((Task*)elemA)->priority == ((Task*)elemB)->priority) return 0;
    else return 1;
}

int Task_tickCompareEE(void* elemA, void* elemB)
{
    if (((Task*)elemA)->runTick < ((Task*)elemB)->runTick) return -1;
    else if (((Task*)elemA)->runTick == ((Task*)elemB)->runTick) return 0;
    else return 1;
}

int Task_tickCompareTE(unsigned int* tick, void* elem)
{
    if (*tick < ((Task*)elem)->runTick) return -1;
    else if (*tick == ((Task*)elem)->runTick) return 0;
    else return 1;
}
