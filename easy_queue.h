#ifndef __EASY_QUEUE_H
#define __EASY_QUEUE_H

#include <stdint.h>
#include <stdbool.h>

#ifndef QUEUE_SIZE
// NOTE: define this before include to configure the size you need
#define QUEUE_SIZE 16
#endif

typedef struct
{
    uint8_t buffer[QUEUE_SIZE];
    int16_t head;      // NOTE: first position with usefull data
    int16_t tail;      // NOTE: last position with usefull data
} EasyQueue_st;

bool did_queue_failed(void);
void clear_queue_error(void);

void init_easy_queue(EasyQueue_st *which);
bool is_queue_empty(const EasyQueue_st *which);

bool enqueue(EasyQueue_st *which, const uint8_t *what, const uint8_t how_much);     // WARNING: how_much includes itself (aka +1 for length storage)
uint8_t dequeue(EasyQueue_st *which, uint8_t *where); // WARNING: assumed a 256 size limit (uint8_t)

#endif
