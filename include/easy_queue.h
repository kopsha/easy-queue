/**
 * @brief A typical queue and ring buffer static implementation in ANSI C.
 * Static implementations are really fast, portable (if you're not bothered
 * by compiling) and safe.
 *
 * The implementation cannot be super generic to cover each possible use
 * case, but hopefully its simplicity allows you to easily customize it
 * to your own needs.
 *
 * For example it would worth to parametrize the type of the underlying
 * type. For the moment, I have considered a byte as it is the most
 * versatile.
 *
 * The only thing to do before using it is to define the QUEUE_SIZE which
 * will be used for all further queues. That's the price to pay for the
 * speed of static implementations.
 */

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

/**
 * @brief Initializes the queue properties and sets the whole array to 0xFF.
 * No queue can be used before inializing.
 *
 * @param queue* Address of the queue you wish to initialize
 * @return true if successfull,
 * @return false otherwise
 */
bool zq_init(EasyQueue *queue)
{
    if (!queue)
    {
        return false;
    }

    memset( queue->buffer, 0xFF, QUEUE_SIZE );
    queue->head = 0;
    queue->tail = 0;
    queue->length = 0;

    return true;
}

/**
 * @brief Verifies if queue is empty, cpt. Obvious
 *
 * @param queue*
 * @return true when queue is actually empty, or
 * @return false otherwise or when queue is null
 */
bool zq_is_empty(const EasyQueue *queue)
{
    return queue && queue->length == 0;
}

/**
 * @brief Pushes a single value to the tail (right) side of the queue.
 * When the queue is full, the value will be ignored. If you are
 * looking for a ring buffer behavior, you should try `zq_ringpush()`.
 *
 * @param queue*
 * @param byte the value you need to add to queue
 * @return true when successfull, or
 * @return false otherwise
 */
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

/**
 * @brief Pops a single value from the tail (right) side of the queue.
 * When the queue is empty, an error will be returned and the output
 * value will be untouched.
 *
 * @param queue*
 * @param byte* the address where to store the popped value
 * @return true when successfull, or
 * @return false otherwise
 */
bool zq_pop(EasyQueue *queue, uint8_t *byte)
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

/**
 * @brief Pushes a single value to the head (left) side of the queue.
 * When the queue is full, the value will be ignored. If you are
 * looking for a ring buffer like behavior, please remember that the
 * direction should not matter, and a clean implementation should
 * use the `zq_ringpush()` which will add to the tail side.
 *
 * @param queue*
 * @param byte
 * @return true
 * @return false
 */
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

/**
 * @brief Pops a single value from the head (left) side of the queue.
 * When the queue is empty, an error will be returned and the output
 * value will be untouched.
 *
 * @param queue*
 * @param byte* the address where to store the popped value
 * @return true when successfull, or
 * @return false otherwise
 */
bool zq_leftpop(EasyQueue *queue, uint8_t *byte)
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

/**
 * @brief Pushes a single value to the tail (right) side of the queue.
 * When the queue is full, the value will be stored and the head will
 * advance one position, thus loosing the last value. If you are
 * looking for a standard queue buffer behavior, you should try
 * `zq_push()`.
 *
 * @param queue*
 * @param byte the value you need to add to queue
 * @return true when successfull, or
 * @return false otherwise
 */
bool zq_ringpush(EasyQueue *queue, const uint8_t byte)
{
    if (!queue)
    {
        return false;
    }

    queue->buffer[queue->tail] = byte;
    queue->tail = (queue->tail + 1) % QUEUE_SIZE;

    if (queue->length < QUEUE_SIZE)
    {
        queue->length++;
    }
    else
    {
        queue->head = (queue->head + 1) % QUEUE_SIZE;
    }

    return true;
}

#endif
