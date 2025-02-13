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

#include "Core/Str.h"

BE_NAMESPACE_BEGIN

class BE_API CmdArgs {
public:
    CmdArgs() { numArgs = 0; }
    CmdArgs(const CmdArgs &other) { *this = other; }
    CmdArgs(const char *text, bool keepAsStrings);

                            /// Copy from another.
    CmdArgs &               operator=(const CmdArgs &rhs);

                            /// Clears
    void                    Clear() { numArgs = 0; }

                            /// Takes a null terminated string and breaks the string up into arg tokens.
                            /// Does not need to be /n terminated.
                            /// Set keepAsStrings to true to only seperate tokens from whitespace and comments, ignoring punctuation
    void                    TokenizeString(const char *text, bool keepAsStrings);

                            /// Returns the number of arguments.
    int                     Argc() const { return numArgs; }

                            /// Returns a argument string with the given index.
                            /// Returns empty string if index is not in valid range.
    const char *            Argv(int index) const { return (index >= 0 && index < numArgs) ? argPtrs[index] : ""; }

                            /// Returns a single string containing argv(start) to argv(end) separated by ' '
    const char *            Args(int start = 0, int end = -1) const;

                            /// Tests if matched argument found.
    bool                    CheckArg(const char *arg, bool caseSensitive = true) const;

                            /// Append a argument at the end of the arguments list
    void                    AppendArg(const char *arg);

private:
    static constexpr int    MaxCommandArgs = 64;
    static constexpr int    MaxCommandString = 2048;

    int                     numArgs;                        ///< Number of arguments
    char *                  argPtrs[MaxCommandArgs];        ///< Array of argument pointers that points into tokenized
    char                    tokenized[MaxCommandString];    ///< text buffer
};

BE_INLINE CmdArgs::CmdArgs(const char *text, bool keepAsStrings) {
    TokenizeString(text, keepAsStrings); 
}

BE_INLINE CmdArgs &CmdArgs::operator=(const CmdArgs &rhs) {
    numArgs = rhs.numArgs;
    memcpy(tokenized, rhs.tokenized, sizeof(tokenized));
    for (int i = 0; i < numArgs; i++) {
        int offset = (int)(rhs.argPtrs[i] - rhs.tokenized);
        argPtrs[i] = &tokenized[offset];
    }

    return *this;
}

BE_INLINE bool CmdArgs::CheckArg(const char *arg, bool caseSensitive) const {
    for (int i = 0; i < numArgs; i++) {
        if (!(caseSensitive ? Str::Cmp(argPtrs[i], arg) : Str::Icmp(argPtrs[i], arg))) {
            return true;
        }
    }

    return false;
}

BE_NAMESPACE_END
