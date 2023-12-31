/*
 * Copyright (C) 2020 The Android Open Source Project
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

#pragma once
#include <memory>
#include PATH(android/hardware/audio/common/COMMON_TYPES_FILE_VERSION/types.h)
#include PATH(android/hardware/audio/CORE_TYPES_FILE_VERSION/types.h)
#include "ireader.h"

namespace android {
namespace hardware {
namespace audio {
namespace CPP_VERSION {
namespace implementation {

using namespace ::android::hardware::audio::common::COMMON_TYPES_CPP_VERSION;
using namespace ::android::hardware::audio::CORE_TYPES_CPP_VERSION;

struct DevicePortSink {
    virtual ~DevicePortSink() {}
    virtual Result getPresentationPosition(uint64_t &frames, TimeSpec &ts) = 0;
    virtual size_t write(float volume, size_t bytesToWrite, IReader &) = 0;

    static std::unique_ptr<DevicePortSink> create(size_t readerBufferSizeHint,
                                                  const DeviceAddress &,
                                                  const AudioConfig &,
                                                  const hidl_vec<AudioInOutFlag> &,
                                                  uint64_t initialFrames);

    static int getLatencyMs(const DeviceAddress &, const AudioConfig &);
    static bool validateDeviceAddress(const DeviceAddress &);
};

}  // namespace implementation
}  // namespace CPP_VERSION
}  // namespace audio
}  // namespace hardware
}  // namespace android
