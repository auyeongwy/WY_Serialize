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

/**
 * \file DemoObj1.hpp
 * Example demo code to illustrate the use of the WY_Serialize library.
*/
#ifndef _DEMO_OBJ_1_HPP_
#define _DEMO_OBJ_1_HPP_

#include "WY_SerializeObj.hpp"
#include "WY_SerializeTypes.hpp"

#pragma once
namespace WY_Serialize {

/**
 * Example demo object to illustrate the use of the WY_Serialize library.
*/
class DemoObj1: public WY_SerializeObj
{
public:
    /**
     * Constructor.
     */
    DemoObj1() noexcept;

    /**
     * Implements the WY_SerializeObj virtual function. Mandatory to implement - this returns the data that needs to be saved.
     * \param p_data The data that needs to be saved.
     * \return 0 if success. -1 if error - usually I/O error in this implementation. 
    */
    int get_save_data(S_SerializeData *__restrict__ const p_data) noexcept;

    /**
     * Implements the WY_SerializeObj virtual function. Mandatory to implement - this returns the data from the savefile that needs to be loaded into the object.
     * \param p_size Size of the data that needs to be loaded.
     * \param p_data The data that needs to be loaded.
     * \return 0 if success. -1 if error - usually I/O error in this implementation. 
    */
    int get_load_data(const unsigned int p_size, const unsigned char *__restrict__ const p_data) noexcept;

    /**
     * Implements the WY_SerializeObj virtual function. Optional to implement. This function is provided for internal checks of the object data if required.
     * @return 0 if success. -1 if error. 
     */
    int check_data() noexcept;

private:
    /**
     * The data structure of this demo object. 
     */
    struct {
        int s_int; /**< Demo integer value. */
        char s_char[32]; /**< Demo char array. */
    } m_data;
};

}

#endif