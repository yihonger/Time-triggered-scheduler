/*********************************************
How to use time-triggered scheduler (TTS)

0. Redefine the macros TTS_CRITICAL_ENTER and TTS_CRITICAL_EXIT to adapt to your MCU.

1. Add task name to "enum TaskName" and define task function.
eg.
enum TaskName{
    IDLE,           //must be the first member
    EXAMPLE,
    TASK_MAX_NUMS   //must be the last member
};

//----------------------------

void ExampleStateOne(int* state)
{
    printf("This is an example task state one.");
    *state = two;
    TTS_SetTask(EXAMPLE, 50);
}

void ExampleStateTwo(int* state)
{
    printf("This is an example task state two.");
    *state = one;
    TTS_SetTask(EXAMPLE, 50);
}

void (* const ExampleTaskState[])(int*) = {
    ExampleStateOne,
    ExampleStateTwo,
};

void ExampleTask(void)
{
    static int state = one;
    ExampleTaskState[state](&state);
}

//------------------------------------------------------

2. System tick interrupt handle must call to "TTS_Sched";
eg.
void SysTickHandle(void)
{
    TTS_Sched();
}

3. Idle task definition and use the TTS.
eg.
void ExampleIdleTask(void)
{
    printf("This an example idle task.");
}

int main(void)
{
    TTS_Init(&ExampleIdleTask);
    
    TaskCfg taskCfg;
    taskCfg.cycle = 0;  //once
    taskCfg.taskFun = ExampleTask;
    taskCfg.priority = 1;
    TTS_InitTask(EXAMPLE, &taskCfg);

    TTS_CreateTask(EXAMPLE, 0);
    
    SysTickInit();
    
    TTS_Run();

    return 0;
}

**************************************************/

#include "../TimTrigSched/TimTrigSched.h"
#include <stdio.h>
#include "ARMCM3.h"

enum{
    one,
    two,
};

void DemoStateOne(int* state)
{
    printf("This is a demo task state one.\n");
    *state = two;
    TTS_SetTask(DEMO, 50);
}

void DemoStateTwo(int* state)
{
    printf("This is a demo task state two.\n");
    *state = one;
    TTS_SetTask(DEMO, 50);
}

void (* const DemoTaskState[])(int*) = {
    DemoStateOne,
    DemoStateTwo,
};

void DemoTask(void)
{
    static int state = one;
    DemoTaskState[state](&state);
}



void ExampleIdleTask(void)
{
//    printf("This an example idle task.\n");
}


int main(void)
{
    SystemCoreClockUpdate();
    
    TTS_Init(&ExampleIdleTask);
    
    TaskCfg taskcfg;
    
    taskcfg.cycle = 0;
    taskcfg.priority = 1;
    taskcfg.taskFun = DemoTask;
    TTS_InitTask(DEMO, &taskcfg);
    
    TTS_CreateTask(DEMO, 0);
    
    SysTick_Config(SystemCoreClock/100);
    
    TTS_Run();
}



void SysTick_Handler(void)
{
    TTS_Sched();
}




#define ITM_PORT8(n)         (*(volatile unsigned char *)(0xe0000000 + 4*(n)))
#define ITM_PORT16(n)        (*(volatile unsigned short *)(0xe0000000 + 4*(n)))
#define ITM_PORT32(n)        (*(volatile unsigned long *)(0xe0000000 + 4*(n)))
#define DEMCR                (*(volatile unsigned long *)(0xE000EDFC))
#define TRCENA               0X01000000

int fputc(int ch, FILE *f)
{
    if(DEMCR & TRCENA)
    {
        while(ITM_PORT32(0) == 0);                                                                                                                                                                                                                                                                                      
        ITM_PORT8(0) = ch;
    }
    return ch; 
}
