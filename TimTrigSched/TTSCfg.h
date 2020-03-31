
#ifndef TTS_TTSCFG_H
#define TTS_TTSCFG_H

//-----TTS system type-------------------

typedef enum
{
    TTS_ERR = 0,
    TTS_OK = !TTS_ERR,
}TTSResult;

typedef void (*TaskFun) (void);
//---------------------------------------


//---user config ---------------------------

enum TaskName{

    
    TASK_MAX_NUMS   //must be the last member
};

// #define TTS_CRITICAL_ENTER  //__disable_irq()
// #define TTS_CRITICAL_EXIT   //__enable_irq()

#if !defined(TTS_CRITICAL_ENTER) && !defined(TTS_CRITICAL_EXIT)
#error "The macros TTS_CRITICAL_ENTER and TTS CRITICAL EXIT must be defined."
#endif

//--------------------------------------------


/*********************************************
How to use time-triggered scheduler (TTS)

0. Redefine the macros TTS_CRITICAL_ENTER and TTS_CRITICAL_EXIT to adapt to the MCU.

1. Add task name to "enum TaskName" and define task function.
eg.
enum TaskName{
    EXAMPLE,
    TASK_MAX_NUMS   //must be the last member
};

//-------

void ExampleStateOne(int* state)
{
    printf("This is an example task state one.");
    *state = two;
    TTS_SetTask(&task[EXAMPLE], 50);
}

void ExampleStateTwo(int* state)
{
    printf("This is an example task state two.");
    *state = one;
    TTS_SetTask(&task[EXAMPLE], 50);
}

void (* const ExampleTaskState)[](int*) = {
    ExampleStateOne,
    ExampleStateTwo,
};

void ExampleTask(void)
{
    static int state = one;
    ExampleTaskState[state](&state);
}

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

    TaskInit(&task[EXAMPLE], ExampleTask, 0, 0);
    
    TTS_CreateTask(&task[EXAMPLE], 0);
    
    SysTickInit();
    
    TTS_Run();

    return 0;
}

***********************************************/

#endif
