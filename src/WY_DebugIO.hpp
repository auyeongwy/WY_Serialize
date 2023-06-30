/*
* Copyright 2023 Au Yeong Wing Yau
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef _WY_DEBUG_IO_HPP_
#define _WY_DEBUG_IO_HPP_

#pragma once
namespace WY_Serialize {

/**
 * Provides debug print static functions. 
 * 
 * By default, debug IO is deactivated so calls to this function will not do anything though there is a function call and variable check overhead. This is usually integrated in a latency-heavy function such as IO-based function calls so we don't care about the overhead - the IO itself is high latency. \n
 * \n
 * Usage: \n
 * C_Debug_IO::set_debug_print(true); // Debug print won't do anything unless this is called. \n
 * C_Debug_IO::debug_print("Debug print is activated."); \n
 * ... \n
 * C_Debug_IO::set_debug_print(false); \n
 * C_Debug_IO::debug_print("Test."); // Nothing happens as debug print is deactivated. \n
 */
class WY_DebugIO
{
public:
    /**
     * Sets the debug print status. Defaults to false.
     * \param p_status The status to set.
    */
    static void set_debug_print(const bool p_status) noexcept;

    /**
     * Prints a debug message to stdout using a template function.
     * \param p_msg The message to print.
    */
    template<typename P>
    static void debug_print(const P p_msg) {
        if(m_debug) {
            std::cout << p_msg << "\n";
        }
    }

private:
    static bool m_debug; /**< The debug status. */
};
}

#endif
