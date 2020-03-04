/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "platform/SharedPtr.h"

int main(void)
{
    struct MyStruct {
        int a;
    };

    // Create shared pointer
    SharedPtr<MyStruct> ptr(new MyStruct);

    // Increase reference count
    SharedPtr<MyStruct> ptr2(ptr);

    ptr = nullptr; // Reference to the struct instance is still held by ptr2

    ptr2 = nullptr; // The raw pointer is freed
}
