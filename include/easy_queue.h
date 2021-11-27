#ifndef __EASY_QUEUE_H
#define __EASY_QUEUE_H

#ifndef QUEUE_SIZE
    #error You must define a QUEUE_SIZE before include
#endif

#include <stdint.h>
#include <stdbool.h>
#include <memory.h>


typedef struct
{
    uint8_t buffer[QUEUE_SIZE];
    int16_t head;     	// NOTE: first position with usefull data
    int16_t tail;  		// NOTE: first free position
    uint16_t length;
} EasyQueue;


// TODO: add initial value
bool zq_init(EasyQueue *queue)
{
    if (!queue)
    {
        return false;
    }

    memset( queue->buffer, 0x00, QUEUE_SIZE );
    queue->head = 0;
    queue->tail = 0;
    queue->length = 0;

    return true;
}

bool zq_is_empty(const EasyQueue *queue)
{
    return queue && queue->length == 0;
}

bool zq_push(EasyQueue *queue, const uint8_t byte)
{
    if (!queue || queue->length >= QUEUE_SIZE)
    {
        return false;
    }

    queue->buffer[queue->tail] = byte;
    queue->tail = (queue->tail + 1) % QUEUE_SIZE;
    queue->length++;

    return true;
}

bool zq_leftpush(EasyQueue *queue, const uint8_t byte)
{
    if (!queue || queue->length >= QUEUE_SIZE)
    {
        return false;
    }

    queue->head = (queue->head - 1 + QUEUE_SIZE) % QUEUE_SIZE;
    queue->buffer[queue->head] = byte;
    queue->length++;

    return true;
}

bool zq_pop(EasyQueue *queue, uint8_t *byte)
{
    if (!queue || !byte || queue->length <= 0)
    {
        return false;
    }

    *byte = queue->buffer[queue->head];
    queue->head = (queue->head + 1) % QUEUE_SIZE;
    queue->length--;

    return true;
}

bool zq_rightpop(EasyQueue *queue, uint8_t *byte)
{
    if (!queue || !byte || queue->length <= 0)
    {
        return false;
    }

    queue->tail = (queue->tail - 1 + QUEUE_SIZE) % QUEUE_SIZE;
    *byte = queue->buffer[queue->tail];
    queue->length--;

    return true;
}

#endif
