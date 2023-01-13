#ifndef DEFINES_H_
#define DEFINES_H_

typedef void(*FuncPtr)(void);

#define ENABLED    2u
#define DISABLED   1u

#define BUSY       0u
#define IDLE       1u

#define NULL			((void*)0)


#define OK				0u
#define NOK				1u
#define NULL_PTR_ERR	2u
#define TIMEOUT_ERR     3u
#define BUSY_STATE_ERR  4u

#endif
