/*
 * utils.c
 *
 *  Created on: Sep 19, 2019
 *      Author: pc
 */

#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <hal/errors.h>
#include "TLM_management.h"
#include <SubSystemModules/Housekepping/TelemetryFiles.h>

static int errCount[2000] = {0};
static int errLastTime[2000] = {0};

void timeU2time(time_unix utime, Time *time){
    struct tm  ts;
    char       buf[80];

	ts = *localtime(&utime);
	time->seconds = ts.tm_sec;
	time->minutes = ts.tm_min;
	time->hours = ts.tm_hour;
	time->date = ts.tm_mday;
	time->month = ts.tm_mon+1;
	time->year = ts.tm_year-100;

    //strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
    //printf("Local Time %s\n", buf);
	//printf("year: %d\n", time->year);

}

int logError(int error ,char* msg){
	int error_abs=0;
	if(error != E_NO_SS_ERR){
		if(error < 0 ){
		    error_abs = abs(error) + 1000;
		 }


		int timeFromLastError = Time_getUptimeSeconds() - errLastTime[error];

		if (timeFromLastError > MAX_TIME_BETWEEN_ERRORS){
			errCount[error_abs] = 0;
		}else{
			errCount[error_abs]++;
		}

		if (errCount[error_abs] < MAX_ERRORS){
			logData_t log_;
			sprintf(log_.msg, "err %d %s", error ,msg);
			write2File(&log_.msg , tlm_log);
			//printf("[%d] Logging error number:%d\n", errCount[error], error);
			errLastTime[error_abs] = Time_getUptimeSeconds();
		}


	}

	return error;

}

int logInfo(char *info){
	printf("info: %s\n",info);
	logData_t log_;
	memcpy(log_.msg, info, MAX_LOG_STR);
	log_.error = 0;
	write2File(&log_ , tlm_log);

	return 0;
}
