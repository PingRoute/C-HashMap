#ifndef _MARKET_H
#define _MARKET_H

#include <pthread.h>
#include <stdio.h>

/** The type of actions **/
enum alert_type { NO_ACTION, SELL, BUY};

/** The prediction information **/
struct prediction {
    double SSO;
    double signal_line;
    enum alert_type alert;
};

/** The function for market thread */
void *market(void *arg);

/**
 * Specifying the input file and symbol
 * Must be called before creating market thread
 */
void init_market(FILE *, char *);

/** Return the next a few lines of the input data */
char *get_inputs(unsigned int *);

#endif
