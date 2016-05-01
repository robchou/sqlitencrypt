/* 
 * Copyright (C) 2016, Robin Chou (robin.m.chou@gmail.com)
 * All rights reserved.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _LOG_H
#define _LOG_H

#ifdef __ANDROID__

#include <android/log.h>

#ifndef MY_LOG_TAG
#define MY_LOG_TAG "SQLite"
#endif

#ifndef MY_LOG_LEVEL
#define MY_LOG_LEVEL ANDROID_LOG_VERBOSE
#endif

#endif  /*__ANDROID__*/

#if (defined __unix__) || (defined __gnu_linux__ ) || (defined __APPLE__) || (defined __FreeBSD__) || (defined __WINDOWS__)
#include <stdio.h>
#ifndef MY_LOG_TAG
#define MY_LOG_TAG "SQLite"
#endif

#ifndef UNIX_LOG_VERBOSE 
#define UNIX_LOG_VERBOSE 0
#endif /* ifndef UNIX_LOG_VERBOSE  */

#ifndef UNIX_LOG_DEBUG
#define UNIX_LOG_DEBUG 1
#endif /* ifndef UNIX_LOG_DEBUG */

#ifndef UNIX_LOG_INFO
#define UNIX_LOG_INFO 2
#endif /* ifndef UNIX_LOG_INFO */

#ifndef UNIX_LOG_WARN
#define UNIX_LOG_WARN 3
#endif /* ifndef UNIX_LOG_WARN */

#ifndef UNIX_LOG_ERROR
#define UNIX_LOG_ERROR 4
#endif /* ifndef UNIX_LOG_ERROR */

#ifndef UNIX_LOG_FATAL
#define UNIX_LOG_FATAL 5
#endif /* ifndef UNIX_LOG_FATAL */

#ifndef MY_LOG_LEVEL
#define MY_LOG_LEVEL UNIX_LOG_VERBOSE
#endif

#define MY_LOG_PRINT(fmt, ...) \
    printf("(%s:%u)%s: " fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
    printf("\n") \

#define MY_LOG_NOOP (void)0

#if UNIX_LOG_VERBOSE >= MY_LOG_LEVEL
#define LOGV(fmt, ...) MY_LOG_PRINT(fmt, ##__VA_ARGS__)
#else
        #define LOGV(...) MY_LOG_NOOP
#endif

#if UNIX_LOG_DEBUG >= MY_LOG_LEVEL
#define LOGD(fmt, ...) MY_LOG_PRINT(fmt, ##__VA_ARGS__)
#else
        #define LOGD(...) MY_LOG_NOOP
#endif

#if UNIX_LOG_INFO >= MY_LOG_LEVEL
#define LOGI(fmt, ...) MY_LOG_PRINT(fmt, ##__VA_ARGS__)
#else
        #define LOGI(...) MY_LOG_NOOP
#endif

#if UNIX_LOG_WARN >= MY_LOG_LEVEL
#define LOGW(fmt, ...) MY_LOG_PRINT(fmt, ##__VA_ARGS__)
#else
        #define LOGW(...) MY_LOG_NOOP
#endif

#if UNIX_LOG_ERROR >= MY_LOG_LEVEL
#define LOGE(fmt, ...) MY_LOG_PRINT(fmt, ##__VA_ARGS__)
#else
        #define LOGE(...) MY_LOG_NOOP
#endif

#if UNIX_LOG_FATAL >= MY_LOG_LEVEL
#define LOGF(fmt, ...) MY_LOG_PRINT(fmt, ##__VA_ARGS__)
#else
        #define LOGF(...) MY_LOG_NOOP
#endif

#endif  /* __*nix__ and __WINDOWS__ */
#endif  /* _LOG_H */
