#ifndef __PID_H__
#define __PID_H__
//---------------user includes------------------------------------------//
#include "bldc.h"
//---------------constant define------------------------------------------//

//---------------variable define------------------------------------------//

//---------------function define------------------------------------------//
uint16_t pid_regulate(int16_t reference, int16_t present_fb, pid_struct_t *pid);
void     pid_init(pid_struct_t *pid);

#endif /* __PID_H__ */