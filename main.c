#define QUEUE_SIZE 16
#include "easy_queue.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


void print_queue(const EasyQueue *which)
{
    printf("head, tail: %d, %d; ", which->head, which->tail );
    printf("length: %d (%d)\n[", which->length, QUEUE_SIZE );
    for (int i=0; i<QUEUE_SIZE; i++)
    {
        if (i == which->head && i == which->tail)
            printf("$^%3d,", which->buffer[i] );
        else if (i == which->head)
            printf("^%4d,", which->buffer[i] );
        else if (i == which->tail)
            printf("$%4d,", which->buffer[i] );
        else
            printf("%5d,", which->buffer[i] );
    }

    printf("]\n");
}

int main(int argc, char const *argv[])
{
    EasyQueue first_q;
    EasyQueue second_q;
    int failed_test_count = 0;

    printf("Init tests:\n");
    failed_test_count += zq_init( &first_q );
    failed_test_count += zq_init( &second_q );

    printf("Is empty tests:\n");
    failed_test_count += zq_is_empty( &first_q ) ? 0 : 1;
    failed_test_count += zq_is_empty( &second_q ) ? 0 : 1;

    printf("Push & pop tests:\n");
    print_queue( &second_q );

    for (uint8_t i = 0; i < 6; i++)
    {
        failed_test_count += zq_push( &second_q, 'a'+(char)i );
    }
    print_queue( &second_q );

    printf("Pops: ");
    for (uint8_t i = 0; i < 6; i++)
    {
        uint8_t outcome;
        failed_test_count += zq_pop( &second_q, &outcome );
        printf( " %c,", (char)outcome );
    }
    printf("\n");
    print_queue( &second_q );

    for (uint8_t i = 0; i < 16; i++)
    {
        failed_test_count += zq_push( &second_q, 'a'+(char)i );
    }
    print_queue( &second_q );

    printf("Pops: ");
    for (uint8_t i = 0; i < 16; i++)
    {
        uint8_t outcome;
        failed_test_count += zq_pop( &second_q, &outcome );
        printf( " %c,", (char)outcome );
    }
    printf("\n");
    print_queue( &second_q );

    return 0;
}
