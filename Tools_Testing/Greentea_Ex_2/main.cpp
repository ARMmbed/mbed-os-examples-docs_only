/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "utest/utest.h"
#include "unity/unity.h"
#include "greentea-client/test_env.h"

using namespace utest::v1;

static control_t hello_world_test(const size_t call_count)
{
    // send a message to the host runner
    greentea_send_kv("init", "hello");

    // wait until we get a message back
    // if this takes too long, the timeout will trigger, so no need to handle this here
    char _key[20], _value[128];
    while (1) {
        greentea_parse_kv(_key, _value, sizeof(_key), sizeof(_value));

        // check if the key equals init, and if the return value is 'world'
        if (strcmp(_key, "init") == 0) {
            TEST_ASSERT_EQUAL(0, strcmp(_value, "world"));
            break;
        }
    }

    return CaseNext;
}

utest::v1::status_t greentea_setup(const size_t number_of_cases)
{
    // here, we specify the timeout (60s) and the host runner (the name of our Python file)
    GREENTEA_SETUP(60, "hello_world_tests");
    return greentea_test_setup_handler(number_of_cases);
}

Case cases[] = {
    Case("hello world", hello_world_test)
};

Specification specification(greentea_setup, cases);

int main()
{
    return !Harness::run(specification);
}
