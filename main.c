#define QUEUE_SIZE 16
#include "easy_queue.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

char printable( uint8_t x )
{
    return (x < 32) ? '.' : x;
}

void print_queue(const EasyQueue_st *which)
{
    printf("head, tail: %d, %d\n[", which->head, which->tail );
    printf("length: %d\n", which->length );
    for (int i=0; i<(QUEUE_SIZE-1); i++)
    {
        printf(" ");
        if (i == which->head)
            printf("^");
        if (i == which->tail)
            printf("$");
        printf("%c", printable(which->buffer[i]) );
        printf(",");
    }

    printf(" ");
    if (QUEUE_SIZE-1 == which->head)
        printf("^");
    if (QUEUE_SIZE-1 == which->tail)
        printf("$");
    printf("%c", printable(which->buffer[QUEUE_SIZE-1]) );

    printf("]\n");
}

int main(int argc, char const *argv[])
{
    EasyQueue_st first_q;
    EasyQueue_st second_q;
    int failed_test_count = 0;

    printf("Init tests:\n");
    easy_reset_queue( &first_q );
    failed_test_count += easy_queue_failed() ? 1 : 0;
    easy_reset_queue( &second_q );
    failed_test_count += easy_queue_failed() ? 1 : 0;

    printf("Is empty tests:\n");
    failed_test_count += easy_is_queue_empty( &first_q ) ? 0 : 1;
    failed_test_count += easy_queue_failed() ? 1 : 0;
    failed_test_count += easy_is_queue_empty( &second_q ) ? 0 : 1;
    failed_test_count += easy_queue_failed() ? 1 : 0;

    printf("Push & pop tests:\n");
    print_queue( &second_q );

    for (uint8_t i = 0; i < 6; i++)
    {
        easy_push( &second_q, 'a'+(char)i );
        failed_test_count += easy_queue_failed() ? 1 : 0;
    }
    print_queue( &second_q );

    printf("Pops: ");
    for (uint8_t i = 0; i < 6; i++)
    {
        uint8_t outcome;
        easy_pop( &second_q, &outcome );
        printf( " %c,", (char)outcome );
        failed_test_count += easy_queue_failed() ? 1 : 0;
    }
    printf("\n");
    print_queue( &second_q );

    for (uint8_t i = 0; i < 16; i++)
    {
        easy_push( &second_q, 'a'+(char)i );
        failed_test_count += easy_queue_failed() ? 1 : 0;
    }
    print_queue( &second_q );

    printf("Pops: ");
    for (uint8_t i = 0; i < 16; i++)
    {
        uint8_t outcome;
        easy_pop( &second_q, &outcome );
        printf( " %c,", (char)outcome );
        failed_test_count += easy_queue_failed() ? 1 : 0;
    }
    printf("\n");
    print_queue( &second_q );


    printf("Tests without overflow:\n");
    char sample[] = "ten bytes.";
    print_queue( &first_q );

    easy_enqueue( &first_q, (uint8_t *)sample, strlen(sample) );
    failed_test_count += easy_queue_failed() ? 1 : 0;
    print_queue( &first_q );

    char buffer[6] = "      ";
    easy_dequeue( (uint8_t *)buffer, &first_q, 5);
    failed_test_count += easy_queue_failed() ? 1 : 0;
    buffer[5]='\0';
    printf("first chunk: %s\n", buffer );

    easy_dequeue( (uint8_t *)buffer, &first_q, 5);
    failed_test_count += easy_queue_failed() ? 1 : 0;
    buffer[5]='\0';
    printf("second chunk: %s\n", buffer );

    print_queue( &first_q );

    printf("Tests with ring overflow:\n");
    easy_enqueue( &first_q, (uint8_t *)sample, strlen(sample) );
    failed_test_count += easy_queue_failed() ? 1 : 0;
    print_queue( &first_q );

    easy_dequeue( (uint8_t *)buffer, &first_q, 5);
    failed_test_count += easy_queue_failed() ? 1 : 0;
    buffer[5]='\0';
    printf("first chunk: %s\n", buffer );

    easy_dequeue( (uint8_t *)buffer, &first_q, 5);
    failed_test_count += easy_queue_failed() ? 1 : 0;
    buffer[5]='\0';
    printf("second chunk: %s\n", buffer );

    print_queue( &first_q );
    printf("Errors count: %d\n", failed_test_count);

    return failed_test_count;
}
