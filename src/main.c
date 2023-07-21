/*
 * Copyright (c) 2020 BayLibre, SAS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <stdio.h>
#define USER_STACKSIZE	2048

#include "rust_app.h"

extern void cpp_out();

struct k_thread user_thread;
K_THREAD_STACK_DEFINE(user_stack, USER_STACKSIZE);


void callback(const char* string) {
    printf("%s\n", string);
}


static void user_function(void *p1, void *p2, void *p3)
{
	printf("Hello from %s (%s)\n",
	       k_is_user_context() ? "UserSpace!" : "privileged mode.",
	       CONFIG_BOARD);
	__ASSERT(k_is_user_context(), "User mode execution was expected");
	cpp_out();
	get_string_in_callback(callback);
}


int main(void)
{
	k_thread_create(&user_thread, user_stack, USER_STACKSIZE,
			user_function, NULL, NULL, NULL,
			-1, K_USER, K_MSEC(0));
	return 0;
}
