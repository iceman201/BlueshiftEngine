// Copyright(c) 2017 POLYGONTEK
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Precompiled.h"
#include "Core/ByteOrder.h"

BE_NAMESPACE_BEGIN

ByteOrder::Endianness::Enum ByteOrder::systemEndianness = Endianness::Unknown;

void ByteOrder::Init() {
    byte swaptest[2] = { 1, 0 };

    // runtime byte order test.
    if (*(int16_t *)swaptest == 1) {
        systemEndianness = Endianness::LittleEndian;
    } else {
        systemEndianness = Endianness::BigEndian;
    }
}

BE_NAMESPACE_END
