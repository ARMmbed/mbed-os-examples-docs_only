#include "mbed.h"

using namespace std::chrono_literals;

#define SAMPLE_FLAG1 (1UL << 0)
#define SAMPLE_FLAG2 (1UL << 9)

EventFlags event_flags;

void worker_thread_fun()
{
    printf("Waiting for any flag from 0x%08lx.\r\n", SAMPLE_FLAG1 | SAMPLE_FLAG2);
    uint32_t flags_read = 0;
    while (true) {
        flags_read = event_flags.wait_any(SAMPLE_FLAG1 | SAMPLE_FLAG2);
        printf("Got: 0x%08lx\r\n", flags_read);
    }
}

int main()
{
    Thread worker_thread;
    worker_thread.start(mbed::callback(worker_thread_fun));

    while (true) {
        ThisThread::sleep_for(1s);
        event_flags.set(SAMPLE_FLAG1);
        ThisThread::sleep_for(500ms);
        event_flags.set(SAMPLE_FLAG2);
    }
}
