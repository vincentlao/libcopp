﻿/*
 * this_task.cpp
 *
 *  Created on: 2014年4月2日
 *      Author: owent
 *
 *  Released under the MIT license
 */


#include <libcotask/this_task.h>

namespace cotask {
    namespace this_task {
        impl::task_impl* get_task() UTIL_CONFIG_NOEXCEPT {
            return impl::task_impl::this_task();
        }
    }
}
