#include "easy_queue.h"

#include <memory.h>

static bool last_error = false;

bool easy_queue_failed(void)
{
    return last_error;
}

void easy_clear_error(void)
{
    last_error = false;
}

void easy_reset_queue(EasyQueue_st *which)
{
    if (which)
    {
        memset( which->buffer, 0x00, QUEUE_SIZE );
        which->head = 0;
        which->tail = 0;
    }
    else
    {
        last_error = true;
    }
}

bool easy_is_queue_empty(const EasyQueue_st *which)
{
    if (which)
    {
        return (which->head == which->tail);
    }

    return false;
}
int16_t easy_queue_length(const EasyQueue_st *which)
{
    if (which)
    {
        if (which->head <= which->tail)
        {
            return (which->tail - which->head);    
        }
        else
        {
            return (which->tail + QUEUE_SIZE - which->head);
        }
    }

    return -1;
}

bool easy_enqueue(EasyQueue_st *which, const uint8_t *what, const uint8_t how_much)
{
    if (!which || !what || (how_much == 0))
    {
        last_error = true;
        return false;
    }

    int16_t free_capacity;
    if (which->head <= which->tail)
    {
        free_capacity = QUEUE_SIZE - (which->tail - which->head);
    }
    else
    {
        free_capacity = which->head - which->tail - 1;
    }

    if (free_capacity < how_much)
    {
        last_error = true;
        return false;
    }

    if (which->head <= which->tail)
    {
        int16_t first_chunk_len = (which->tail + how_much) > QUEUE_SIZE ? QUEUE_SIZE - which->tail : how_much;
        int16_t second_chunk_len = how_much - first_chunk_len;
        if (first_chunk_len > 0)
        {
            memcpy( &which->buffer[which->tail], what, first_chunk_len );
        }
        if (second_chunk_len > 0)
        {
            memcpy( which->buffer, what + first_chunk_len, second_chunk_len );
        }
    }
    else
    {
        memcpy( which->buffer, what, how_much );
    }
    which->tail = (which->tail + how_much) % QUEUE_SIZE;

    return true;
}

bool easy_dequeue(uint8_t *where, EasyQueue_st *which, const uint8_t how_much)
{
    if (!which || !where || (how_much == 0) || (how_much > easy_queue_length(which)))
    {
        last_error = true;
        return false;
    }

    if (which->head <= which->tail)
    {
        memcpy( where, &which->buffer[which->head], how_much );
    }
    else
    {
        int16_t first_chunk_len = QUEUE_SIZE - which->head;
        int16_t second_chunk_len = how_much - first_chunk_len;
        if (first_chunk_len > 0)
        {
            memcpy( where, &which->buffer[which->head], first_chunk_len );
        }
        if (second_chunk_len > 0)
        {
            memcpy( where + first_chunk_len, which->buffer, second_chunk_len );
        }
    }

    which->head = (which->head + how_much) % QUEUE_SIZE;
    return true;
}
