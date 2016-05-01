# Copyright (C) 2016, Robin Chou (robin.m.chou@gmail.com)
# All rights reserved.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# http://www.apache.org/licenses/LICENSE-2.0
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := $(call my-dir)/../..

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include                   \
                    $(LOCAL_PATH)/wxsqlite3/sqlite3/include \

LOCAL_SRC_FILES := src/content_values.cpp                       \
                   src/sqlite_db.cpp                            \
                   src/sqlite_record.cpp                        \
                   src/sqlite_table.cpp                         \
                   src/utils.cpp                                \
                   wxsqlite3/sqlite3/secure/src/sqlite3secure.c \

LOCAL_MODULE := sqlitencrypt
OCAL_LDLIBS := -lpthread -ldl -llog
LOCAL_CFLAGS := -DSQLITE_HAS_CODEC

include $(BUILD_SHARED_LIBRARY)
