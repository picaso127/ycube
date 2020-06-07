/*
 * utils.h
 *
 *  Created on: Sep 19, 2019
 *      Author: pc
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "GlobalStandards.h"
#include <hal/Timing/Time.h>


#define E_CANT_TRANSMIT    		-200
#define E_TOO_EARLY_4_BEACON    -201
#define E_INVALID_PARAMETERS    -204
#define TRXVU_MUTE_TOO_LONG    	-202
#define TRXVU_IDLE_TOO_LONG    	-203
#define TRXVU_IDLE_WHILE_TRANSPONDER -205
#define BEACON_INTRAVL_TOO_SMALL -206

#define MAX_ERRORS       				 20 // max errors we want to log from the same type toghether
#define MAX_TIME_BETWEEN_ERRORS          2 // max seconds we allow between errors
#define MAX_LOG_STR				40

typedef struct data
{
	int error;
	char msg[MAX_LOG_STR];
} logData_t;


/*
 * convert unix time to Time struct
 */
void timeU2time(time_unix utime, Time *time);
/*
 * log error message
 */
int logError(int error);

/*
 * log info message
 */
int logInfo(char *info);

#endif /* UTILS_H_ */

