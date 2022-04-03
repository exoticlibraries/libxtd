/*! gcc {0} -I../include/ -I../../libmetaref/include/ -o out.exe; ./out.exe */

#include <exotic/cester.h>
#include <exotic/xtd/xcommon.h>
#include <exotic/xtd/xcircular_buffer.h>

CESTER_BODY(
    SETUP_XCIRCULAR_BUFFER_FOR(int)
)

CESTER_TEST(test_stack, _, {
    xcircular_buffer(int) *numbers;
    int value;

    xcircular_buffer_new(int)(&numbers, 5);
    xcircular_buffer_enqueue(int)(numbers, 10);
    xcircular_buffer_enqueue(int)(numbers, 20);
    xcircular_buffer_enqueue(int)(numbers, 30);
    xcircular_buffer_enqueue(int)(numbers, 40);
    xcircular_buffer_enqueue(int)(numbers, 50);

    xcircular_buffer_dequeue(int)(numbers, &value); printf("Dequeued Value: %d\n", value);
    xcircular_buffer_dequeue(int)(numbers, &value); printf("Dequeued Value: %d\n", value);

    xcircular_buffer_enqueue(int)(numbers, 100);
    xcircular_buffer_enqueue(int)(numbers, 200);
    
    xcircular_buffer_dequeue(int)(numbers, &value); printf("Dequeued Value: %d\n", value);
    xcircular_buffer_dequeue(int)(numbers, &value); printf("Dequeued Value: %d\n", value);
    xcircular_buffer_dequeue(int)(numbers, &value); printf("Dequeued Value: %d\n", value);
    xcircular_buffer_dequeue(int)(numbers, &value); printf("Dequeued Value: %d\n", value);
    xcircular_buffer_dequeue(int)(numbers, &value); printf("Dequeued Value: %d\n", value);
    xcircular_buffer_dequeue(int)(numbers, &value); printf("Dequeued Value: %d\n", value);

    xcircular_buffer_destroy(numbers);
})

