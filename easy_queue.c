#include "easy_queue.h"

#include <memory.h>

static bool last_error = false;

bool did_queue_failed(void)
{
    return last_error;
}

void clear_queue_error(void)
{
    last_error = false;
}

void init_easy_queue(EasyQueue_st *which)
{
    if (which)
    {
        memset( which->buffer, 0x00, QUEUE_SIZE );
        which->head = 0;
        which->tail = -1;
    }
    else
    {
        last_error = true;
    }
}

bool is_queue_empty(const EasyQueue_st *which)
{
    if (which)
    {
        return (which->head == (which->tail+1));
    }
    else
    {
        last_error = true;
    }

    return true;
}

bool enqueue(EasyQueue_st *which, const uint8_t *what, const uint8_t how_much)
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
        int16_t first_chunk_len = QUEUE_SIZE - (which->tail+1);
        int16_t second_chunk_len = how_much - first_chunk_len;
        if (first_chunk_len > 0)
        {
            memcpy( &which->buffer[which->tail + 1], what, first_chunk_len );
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
