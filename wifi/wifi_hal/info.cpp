/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "info.h"

#include <sys/stat.h>

#include <string>

static const char* const kInterfaceNames[] = {"wlan0", "wlan1"};

Info::Info() {
    mInterfaces.reserve(sizeof(kInterfaceNames) / sizeof(kInterfaceNames[0]));
    mInterfaceHandles.reserve(sizeof(kInterfaceNames) / sizeof(kInterfaceNames[0]));
    for (const auto& name : kInterfaceNames) {
        std::string test_path = std::string("/sys/class/net/") + name;
        struct stat ignored_statbuf;
        if (stat(test_path.c_str(), &ignored_statbuf) == 0) {
            mInterfaces.emplace_back(mNetlink, name);
            auto handle = reinterpret_cast<wifi_interface_handle>(&mInterfaces.back());
            mInterfaceHandles.emplace_back(handle);
        }
    }
}

bool Info::init() {
    if (!mNetlink.init()) {
        return false;
    }
    for (auto& iface : mInterfaces) {
        if (!iface.init()) {
            return false;
        }
    }
    return true;
}

void Info::eventLoop() {
    mNetlink.eventLoop();
}

void Info::stop(StopHandler stopHandler) {
    mNetlink.stop(stopHandler);
}

wifi_error Info::getInterfaces(int* num, wifi_interface_handle** interfaces) {
    if (num == nullptr || interfaces == nullptr) {
        return WIFI_ERROR_INVALID_ARGS;
    }
    *num = mInterfaceHandles.size();
    *interfaces = mInterfaceHandles.data();

    return WIFI_SUCCESS;
}

