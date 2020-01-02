/* 
 * File:   timer.h
 * Author: seims
 *
 * Created on September 2, 2017, 10:28 AM
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

void timer_init();
extern void timer_interrupt();

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

