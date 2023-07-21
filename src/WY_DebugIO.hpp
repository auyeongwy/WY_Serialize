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
 * These print functions are only activated if the macro ENABLE_WY_DEBUGIO is passed during compilation (In g++, by using the -D option).<br>
 * <br>
 * The purpose of these functions is so that debug print-to-IO code can be written into source code but can be globally deactivated or activated by a function call.<br>
 * <br>
 * To optimize even further if these functions are not needed, simply DO NOT pass the ENABLE_WY_DEBUGIO macro during compilation.<br>
 * <br>
 * By default, debug IO is deactivated so calls to this function will not do anything though there is a function call and debug status check overhead. But we don't worry too much about the overhead since IO itself is high latency. <br>
 * <br>
 * Usage: <br>
 * @code
 * C_Debug_IO::set_debug_print(true); // Debug print won't do anything unless this is called. 
 * C_Debug_IO::debug_print("Debug print is activated.");  
 * C_Debug_IO::set_debug_print(false); 
 * C_Debug_IO::debug_print("Test."); // Nothing happens as debug print is deactivated. 
 * @endcode
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
        #ifdef ENABLE_WY_DEBUGIO
        if(m_debug) {
            std::cout << p_msg << "\n";
        }
        #endif
    }

#ifdef ENABLE_WY_DEBUGIO
private:
    static bool m_debug; /**< The debug status. */
#endif
};
}

#endif
