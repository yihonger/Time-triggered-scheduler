
#include "TimTrigSched.h"

static unsigned int sysTick;

static Task task[TASK_MAX_NUMS];
static Task* taskArray[3][TASK_MAX_NUMS];
static PriQueue dlyArray[2];

static DlyList dlyList; //延时表
static PriQueue rdyList;//就绪表
static unsigned char registry[ (TASK_MAX_NUMS + 7) / 8 ] = {0};


TTSResult TTS_InitTask(enum TaskName name, const TaskCfg* cfg)
{
    if (!cfg && !cfg->taskFun) return TTS_ERR;

    task[name].cycle = cfg->cycle;
    task[name].priority = cfg->priority;
    task[name].runTick = 0;
    task[name].taskFun = cfg->taskFun;

    return TTS_OK;
}

TTSResult TTS_Init(TaskFun IdleTaskFun)
{
    TaskCfg cfg = {0};
    cfg.taskFun = IdleTaskFun;

    if (!TTS_InitTask(IDLE, &cfg)) return TTS_ERR;
    else registry[0] |= 0x01;

    PriQueue_Init(&rdyList, (void**)taskArray[0], TASK_MAX_NUMS, Task_PriCompareEE);
    PriQueue_Init(&dlyArray[0], (void**)taskArray[1], TASK_MAX_NUMS, Task_tickCompareEE);
    PriQueue_Init(&dlyArray[1], (void**)taskArray[2], TASK_MAX_NUMS, Task_tickCompareEE);
    DlyList_Init(&dlyList, &dlyArray, &sysTick, Task_tickCompareTE);

    return TTS_OK;
}

TTSResult TTS_CreateTask(enum TaskName name, unsigned int dlyTick)
{
    TTSResult rtn;
    
    unsigned int idx = name >> 3;
    unsigned int offset = name & 0x07;
    unsigned int pos = 0x01u << offset;

    if (registry[idx] & pos)    return TTS_ERR;

    if (dlyTick == 0)
    {
        rtn = PriQueue_In(&rdyList, &task[name]);
    }
    else
    {
        task[name].runTick = sysTick + dlyTick;
        rtn = DlyList_In(&dlyList, &task[name]);
    }
    
    if (rtn) registry[idx] |= pos;

    return rtn;
}

TTSResult TTS_SetTask(enum TaskName name, unsigned int cycle)
{
    task[name].cycle = cycle;
    
    return TTS_OK;
}




//call in tick interrupt
TTSResult TTS_Sched(void)
{
    sysTick++;
    Task* rdyTask = 0;
    while (DlyList_GetHead(&dlyList, (void**)&rdyTask))
    {
        if (rdyTask->runTick == sysTick)
        {
            DlyList_Out(&dlyList, (void**)&rdyTask);
            PriQueue_In(&rdyList, (void*)rdyTask);
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
            else
            {
                unsigned int offset = rdyTask - &task[IDLE];
                unsigned int idx = offset >> 3;
                offset  = offset & 0x07;
                registry[idx] ^= 0x01u << offset;
            }
            
        }
        else
        {
            task[IDLE].taskFun();
        }        
    }
}
