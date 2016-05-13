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
#ifndef _JNI_HELPER_H
#define _JNI_HELPER_H

#include "log.h"

#ifdef __cplusplus
extern "C" {
#endif
#define FIND_CLASS(var, className)                                                                  \
        jclass mLocalRef = env->FindClass(className);                                               \
        var = (jclass)env->NewGlobalRef(mLocalRef);                                                 \
        env->DeleteLocalRef(mLocalRef);                                                             \
        LOG_FATAL_IF(! var, "%s:%u Error:Unable to find class %s", __FILE__, __LINE__, className)

#define GET_METHOD_ID(var, clazz, methodName, fieldDescriptor)                                      \
        var = env->GetMethodID(clazz, methodName, fieldDescriptor);                                 \
        LOG_FATAL_IF(! var, "%s:%u Error:Unable to find method %s", __FILE__, __LINE__, methodName)
#ifdef __cplusplus
}
#endif
#endif /* end of include guard: _JNI_HELPER_H */
