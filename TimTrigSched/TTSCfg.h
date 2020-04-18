
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


//--------------user config -----------------------

enum TaskName{
    IDLE,           //must be the first member
    DEMO,
    TASK_MAX_NUMS   //must be the last member
};

#define TTS_CRITICAL_ENTER  //__disable_irq()
#define TTS_CRITICAL_EXIT   //__enable_irq()

#if !defined(TTS_CRITICAL_ENTER) && !defined(TTS_CRITICAL_EXIT)
#error "The macros TTS_CRITICAL_ENTER and TTS CRITICAL EXIT must be defined."
#endif

//--------------------------------------------

#endif
