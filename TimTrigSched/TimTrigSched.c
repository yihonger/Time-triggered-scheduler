
#include "TimTrigSched.h"

static unsigned int sysTick;
static Task* taskArray[3][TASK_MAX_NUMS+1];
static PriQueue dlyArray[2];

static DlyList dlyList; //延时表
static PriQueue rdyList;//就绪表
static Task idleTask;

TTSResult TTS_Init(TaskFun IdleTaskFun)
{
    Task_Init(&idleTask, IdleTaskFun, 0, 0);
    PriQueue_Init(&rdyList, (void**)taskArray[0], TASK_MAX_NUMS + 1, Task_PriCompareEE);
    PriQueue_Init(&dlyArray[0], (void**)taskArray[1], TASK_MAX_NUMS + 1, Task_tickCompareEE);
    PriQueue_Init(&dlyArray[1], (void**)taskArray[2], TASK_MAX_NUMS + 1, Task_tickCompareEE);
    DlyList_Init(&dlyList, &dlyArray, &sysTick, Task_tickCompareTE);
    return TTS_OK;
}

TTSResult TTS_CreateTask(Task* task, unsigned int dlyTick)
{
    TTSResult rtn;
    
    if (dlyTick == 0)
    {
        rtn = PriQueue_In(&rdyList, (void*)task);
    }
    else
    {
        task->runTick = sysTick + dlyTick;
        rtn = DlyList_In(&dlyList, (void*)task);
    }
    
    return rtn;
}

TTSResult TTS_SetTask(Task* task, unsigned int cycle)
{
    task->cycle = cycle;
    
    return TTS_OK;
}


//call in tick interrupt
TTSResult TTS_Sched(void)
{    
    sysTick++;
    Task* task = 0;
    while (DlyList_GetHead(&dlyList, (void**)&task))
    {
        if (task->runTick == sysTick)
        {
            DlyList_Out(&dlyList, (void**)&task);
            PriQueue_In(&rdyList, (void*)task);
        }
        else
        {
            break;
        }
    }
    return TTS_OK;
}

TTSResult TTS_Run(void)
{
    Task* rdyTask = 0;
    while (1)
    {
        if (PriQueue_Out(&rdyList, (void**)&rdyTask))
        {
            rdyTask->taskFun();
            if (rdyTask->cycle != 0)
            {
                rdyTask->runTick = sysTick + rdyTask->cycle;
                DlyList_In(&dlyList, (void*)rdyTask);
            }
        }
        else
        {
            idleTask.taskFun();
        }        
    }
    return TTS_OK;
}
