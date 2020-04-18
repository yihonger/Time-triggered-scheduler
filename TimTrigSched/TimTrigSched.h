
#ifndef TTS_TIM_TRIG_SCHED_H
#define TTS_TIM_TRIG_SCHED_H

#include "TTSCfg.h"
#include "../PriQueue/PriQueue.h"
#include "../DlyList/DlyList.h"
#include "../Task/Task.h"

typedef struct 
{
    TaskFun taskFun;
    unsigned int cycle; //run cycle, 0 for once
    unsigned int priority;
}TaskCfg;


TTSResult TTS_Init(TaskFun IdleTaskFun);
TTSResult TTS_InitTask(enum TaskName name, const TaskCfg* cfg);
TTSResult TTS_CreateTask(enum TaskName name, unsigned int dlyTick);
TTSResult TTS_SetTask(enum TaskName name, unsigned int cycle);
TTSResult TTS_Sched(void);
TTSResult TTS_Run(void);

#endif
