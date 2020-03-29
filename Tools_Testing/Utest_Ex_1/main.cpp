/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "greentea-client/test_env.h"
#include "unity.h"
#include "utest.h"

using namespace utest::v1;

void test_simple()
{
    TEST_ASSERT_EQUAL(0, 0);
    printf("Simple test called\n");
}

utest::v1::status_t test_repeats_setup(const Case *const source, const size_t index_of_case)
{
    // Call the default handler for proper reporting
    utest::v1::status_t status = greentea_case_setup_handler(source, index_of_case);
    printf("Setting up for '%s'\n", source->get_description());
    return status;
}
control_t test_repeats(const size_t call_count)
{
    printf("Called for the %u. time\n", call_count);
    TEST_ASSERT_NOT_EQUAL(3, call_count);
    // Specify how often this test is repeated i.e. n total calls
    return (call_count < 2) ? CaseRepeatAll : CaseNext;
}

void test_callback_validate()
{
    // You may also use assertions here
    TEST_ASSERT_EQUAL_PTR(0, 0);
    // Validate the callback
    Harness::validate_callback();
}

// Specify all your test cases here
Case cases[] = {
    Case("Simple Test", test_simple),
    Case("Repeating Test", test_repeats_setup, test_repeats)
};

// Custom setup handler required for proper Greentea support
utest::v1::status_t greentea_setup(const size_t number_of_cases)
{
    GREENTEA_SETUP(20, "default_auto");
    // Call the default reporting function
    return greentea_test_setup_handler(number_of_cases);
}

// Declare your test specification with a custom setup handler
Specification specification(greentea_setup, cases);

int main()
{
    // Run the test specification
    Harness::run(specification);
}
