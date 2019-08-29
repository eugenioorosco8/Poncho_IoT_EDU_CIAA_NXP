/*
 * rtc.h
 *
 *  Created on: 4 jul. 2018
 *      Author: usuario
 */

#ifndef RTC_H_
#define RTC_H_
#endif /* RTC_H_ */

#include "chip.h"
#include "rtc_18xx_43xx.h"
//#include "lcd.h"

void rtc_init(void);
void rtc_set(int SECOND, int MINUTE, int HOUR, int DAYOFMONTH, int DAYOFWEEK, int DAYOFYEAR, int MONTH, int YEAR);
int  rtc_get_parametro(RTC_TIMEINDEX_T time);
void rtc_printf(int X ,int Y, RTC_TIMEINDEX_T time);//NO USAR




