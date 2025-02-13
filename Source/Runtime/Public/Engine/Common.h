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

#pragma once

#include "Platform/Platform.h"
#include "Math/Math.h"

BE_NAMESPACE_BEGIN

class CmdArgs;

class Common {
public:
    struct PlatformId {
        enum Enum {
            ID_Windows,
            ID_Linux,
            ID_MacOS,
            ID_IOS,
            ID_Android
        };
    };

    void                Init(const char *baseDir);
    void                Shutdown();

    void                RunFrame(int frameMsec);

    PlatformId::Enum    GetPlatformId() const;

    Str                 GetAppPreferenceDir() const;

    Random              random;

    int                 realTime;       // absolute time in milliseconds
    int                 frameTime;      // frame time in milliseconds
    float               frameSec;       // frame time in seconds

private:
    void                SaveConfig(const char *filename);

    int                 ProcessPlatformEvent();
    void                GetPlatformEvent(Platform::Event *ev);

    static void         Cmd_Version(const CmdArgs &args);
    static void         Cmd_Error(const CmdArgs &args);
    static void         Cmd_Quit(const CmdArgs &args);
};

extern Common           common;

BE_NAMESPACE_END
