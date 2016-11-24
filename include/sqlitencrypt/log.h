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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LOG_NDEBUG
#ifdef NDEBUG
#define LOG_NDEBUG 1
#else
#define LOG_NDEBUG 0
#endif /* ifdef NDEBUG */
#endif /* ifndef LOG_NDEBUG */


/*
 * This is the local tag used for the following simplified
 * logging macros.  You can change this preprocessor definition
 * before using the other macros to change the tag.
 */
#ifndef LOG_TAG
#define LOG_TAG "LOG"
#endif /* ifndef LOG_TAG */

#ifndef LOGV
#if LOG_NDEBUG
#define LOGV(...) ((void)0)
#else
#define LOGV(...) ((void)LOG(LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#endif
#endif /* ifndef LOGV */

#define CONDITION(cond) (__builtin_expect((cond)!=0, 0))

#ifndef LOGV_IF
#if LOG_NDEBUG
#define LOGV_IF(cond, ...) ((void)0)
#else
#define LOGV_IF(cond, ...)                             \
    ( (CONDITION(cond))                                \
      ? ((void)LOG(LOG_VERBOSE, LOG_TAG, __VA_ARGS__)) \
      : ((void)0) )
#endif /* if LOG_NDEBUG */
#endif /* ifndef LOG_IF */

#ifndef LOGD
#define LOGD(...) ((void)LOG(LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#endif /* ifndef LOGD */

#ifndef LOGD_IF
#define LOGD_IF(cond, ...)                             \
    ( (CONDITION(cond))                                \
      ? ((void)(LOG(LOG_DEBUG, LOG_TAG, __VA_ARGS__))) \
      : ((void)0) )
#endif /* ifndef LOGD_IF */

#ifndef LOGI
#define LOGI(...) ((void)LOG(LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#endif /* ifndef LOGI */

#ifndef LOGI_IF
#define LOGI_IF(cond, ...)                            \
    ( (CONDITION(cond))                               \
      ? ((void)(LOG(LOG_INFO, LOG_TAG, __VA_ARGS__))) \
      : ((void)0) )
#endif /* ifndef LOGI_IF */

#ifndef LOGW
#define LOGW(...) ((void)LOG(LOG_WARN, LOG_TAG, __VA_ARGS__))
#endif /* ifndef LOGW */

#ifndef LOGI_IF
#define LOGI_IF(cond, ...)                             \
    ( (CONDITION(cond))                                \
      ? ((void)(LOG(LOG_WARN, LOG_TAG, __VA_ARGS__))) \
      : ((void)0) )
#endif /* ifndef LOGW_IF */

#ifndef LOGE
#define LOGE(...) ((void)LOG(LOG_ERROR, LOG_TAG, __VA_ARGS__))
#endif /* ifndef LOGE */

#ifndef LOGE_IF
#define LOGE_IF(cond, ...)                             \
    ( (CONDITION(cond))                                \
      ? ((void)(LOG(LOG_ERROR, LOG_TAG, __VA_ARGS__))) \
      : ((void)0) )
#endif /* ifndef LOGE_IF */

#ifndef LOGE
#define LOGE(...) ((void)LOG(LOG_ERROR, LOG_TAG, __VA_ARGS__))
#endif /* ifndef LOGE */

#ifndef LOGE_IF
#define LOGE_IF(cond, ...)                             \
    ( (CONDITION(cond))                                \
      ? ((void)(LOG(LOG_ERROR, LOG_TAG, __VA_ARGS__))) \
      : ((void)0) )
#endif /* ifndef LOGE_IF */

#ifndef IF_LOGV
#if LOG_NDEBUG
#define IF_LOGV() if (false)
#else
#define IF_LOGV() IF_LOG(LOG_VERBOSE, LOG_TAG)
#endif /* if LOG_NDEBUG */
#endif /* ifndef IF_LOGV */

#ifndef IF_LOGD
#define IF_LOGD() IF_LOG(LOG_DEBUG, LOG_TAG)
#endif /* ifndef IF_LOGD */

#ifndef IF_LOGI
#define IF_LOGI() IF_LOG(LOG_INFO, LOG_TAG)
#endif /* ifndef IF_LOGI */

#ifndef IF_LOGW
#define IF_LOGW() IF_LOG(LOG_WARN, LOG_TAG)
#endif /* ifndef IF_LOGW */

#ifndef IF_LOGE
#define IF_LOGE() IF_LOG(LOG_ERROR, LOG_TAG)
#endif /* ifndef IF_LOGE */

#ifdef __ANDROID__
#ifndef LOG_ALWAYS_FATAL_IF
#include <android/log.h>
#define LOG_ALWAYS_FATAL_IF(cond, ...) \
    ( (CONDITION(cond))                \
      ? (void)__android_log_print(ANDROID_LOG_FATAL, LOG_TAG, ## __VA_ARGS__)      \
      : (void)0 )
#endif /* ifndef LOG_ALWAYS_FATAL_IF */
#endif /* __ANDROID__ */

#if (defined __unix__) || (defined __gnu_linux__ ) || (defined __APPLE__) || (defined __FreeBSD__) || (defined __WINDOWS__)
#ifndef LOG_ALWAYS_FATAL_IF
#include <stdio.h>
#include <assert.h>
#define LOG_ALWAYS_FATAL_IF(cond, ...) \
    ( (CONDITION(cond))                \
      ? (void)printf(__VA_ARGS__)      \
      : (void)0 )
#endif /* ifndef LOG_ALWAYS_FATAL_IF */
#endif /* *nix and windows */

#if LOG_NDEBUG

#ifndef LOG_FATAL_IF
#define LOG_FATAL_IF(cond, ...) ((void)0)
#endif /* ifndef LOG_FATAL_IF */
#ifndef LOG_FATAL
#define LOG_FATAL(...) ((void)0)
#endif /* ifndef LOG_FATAL */

#else

#ifndef LOG_FATAL_IF
#define LOG_FATAL_IF(cond, ...) LOG_ALWAYS_FATAL_IF(cond, ## __VA_ARGS__)
#endif /* ifndef LOG_FATAL_IF */
#ifndef LOG_FATAL
#define LOG_FATAL(...) LOG_ALWAYS_FATAL(__VA_ARGS__)
#endif /* ifndef LOG_FATAL */

#endif

/*
 * Assertion that generates a log message when the assertion fails.
 * Stripped out of release builds.  Uses the current LOG_TAG.
 */
#ifndef LOG_ASSERT
#define LOG_ASSERT(cond, ...) LOG_FATAL_IF(!(cond), ## __VA_ARGS__)
#endif /* ifndef LOG_ASSERT */

/*
 * Basic log message macro.
 *
 * Example:
 *  LOG(LOG_WARN, NULL, "Failed with error %d", errno);
 *
 * The second argument may be NULL or "" to indicate the "global" tag.
 */
#ifndef LOG
#define LOG(priority, tag, ...) \
    LOG_PRI(ANDROID_##priority, tag, __VA_ARGS__)
#endif /* ifndef LOG */

#ifdef __ANDROID__
#ifndef LOG_PRI
#define LOG_PRI(priority, tag, ...) \
    __android_log_print(priority, tag, __VA_ARGS__)
#endif /* ifndef LOG_PRI */

#ifndef IF_LOG
#define IF_LOG(priority, tag) \
    if (__android_log_assert(ANDROID_##priority, tag))
#endif /* ifndef IF_LOG */
#endif /* __ANDROID__ */

#if (defined __unix__) || (defined __gnu_linux__ ) || (defined __APPLE__) || (defined __FreeBSD__) || (defined __WINDOWS__)
#ifndef LOG_PRI
#define LOG_PRI(priority, tag, ...) \
    printf(__VA_ARGS__)
#endif /* ifndef LOG_PRI */

#ifndef IF_LOG
#define IF_LOG(priority, tag) \
    printf(tag)
#endif /* ifndef IF_LOG */
#endif /* if *nix and windows */

#ifdef __cplusplus
}
#endif
#endif /* end of include guard: _LOG_H */

