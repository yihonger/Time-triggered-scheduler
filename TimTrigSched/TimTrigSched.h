
#ifndef TTS_TIM_TRIG_SCHED_H
#define TTS_TIM_TRIG_SCHED_H

#include "TTSCfg.h"
#include "../PriQueue/PriQueue.h"
#include "../DlyList/DlyList.h"
#include "../Task/Task.h"

TTSResult TTS_Init(TaskFun IdleTaskFun);
TTSResult TTS_CreateTask(Task* task, unsigned int dlyTick);
TTSResult TTS_SetTask(Task* task, unsigned int cycle);
TTSResult TTS_Sched(void);
TTSResult TTS_Run(void);

#endif
