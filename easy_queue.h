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
  	// WARNING: don't mess with these in your code
    uint8_t buffer[QUEUE_SIZE];
    int16_t head;     	// NOTE: first position with usefull data
    int16_t tail;  		// NOTE: first free position
    uint16_t length;
} EasyQueue_st;

bool easy_queue_failed(void);
void easy_clear_error(void);

void easy_reset_queue(EasyQueue_st *which);
bool easy_is_queue_empty(const EasyQueue_st *which);

bool easy_push(EasyQueue_st *which, const uint8_t byte);
bool easy_pop(EasyQueue_st *which, uint8_t *byte);

// WARNING: assumed a 256 chunk limit (uint8_t)
bool easy_enqueue(EasyQueue_st *which, const uint8_t *what, const uint8_t how_much);
bool easy_dequeue(uint8_t *where, EasyQueue_st *which, const uint8_t how_much);

#endif
