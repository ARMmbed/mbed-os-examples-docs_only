/*
* Copyright (c) 2019 ARM Limited. All rights reserved.
* SPDX-License-Identifier: Apache-2.0
* Licensed under the Apache License, Version 2.0 (the License); you may
* not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "mbed.h"


// Creates static event queue
static EventQueue queue(0);

void handler(int count);

// Creates events for later bound
auto event1 = make_user_allocated_event(handler, 1);
auto event2 = make_user_allocated_event(handler, 2);

// Creates event bound to the specified event queue
auto event3 = queue.make_user_allocated_event(handler, 3);
auto event4 = queue.make_user_allocated_event(handler, 4);

void handler(int count)
{
    printf("UserAllocatedEvent = %d \n", count);
    return;
}

void post_events(void)
{
    // Single instance of user allocated event can be posted only once.
    // Event can be posted again if the previous dispatch has finished or event has been canceled.

    // bind & post
    event1.call_on(&queue);

    // event cannot be posted again until dispatched or canceled
    bool post_succeed = event1.try_call();
    assert(!post_succeed);

    queue.cancel(&event1);

    // try to post
    post_succeed = event1.try_call();
    assert(post_succeed);

    // bind & post
    post_succeed = event2.try_call_on(&queue);
    assert(post_succeed);

    // post
    event3.call();

    // post
    event4();
}

int main()
{
    printf("*** start ***\n");
    Thread event_thread;

    // The event can be manually configured for special timing requirements
    // specified in milliseconds
    // Starting delay - 100 msec
    // Delay between each event - 200msec
    event1.delay(100);
    event1.period(200);
    event2.delay(100);
    event2.period(200);
    event3.delay(100);
    event3.period(200);
    event4.delay(100);
    event4.period(200);

    event_thread.start(callback(post_events));

    // Posted events are dispatched in the context of the queue's dispatch function
    queue.dispatch(400);        // Dispatch time - 400msec
    // 400 msec - Only 2 set of events will be dispatched as period is 200 msec

    event_thread.join();
}
