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
 * \file DemoObj1.cpp
 * Example demo code to illustrate the use of the WY_Serialize library.
*/
#include <cstring>
#include <iostream>
#include "DemoObj1.hpp"
using namespace WY_Serialize;


DemoObj1::DemoObj1() noexcept
{
    m_data.s_int = 123;
    strncpy(m_data.s_char, "Hello 123", 31);
}


int DemoObj1::get_save_data(S_SerializeData *__restrict__ const p_data) noexcept
{
    p_data->m_type = DEMO_OBJ1;
    p_data->m_size = sizeof(m_data);
    p_data->m_data = (unsigned char *)&m_data;
    return 0;
}


int DemoObj1::get_load_data(const unsigned long p_size, const unsigned char *__restrict__ const p_data) noexcept
{
    if(p_size == sizeof(m_data))
    {
        memcpy(&m_data, p_data, p_size);
        return 0;
    }
    else
        return -1;
}


int DemoObj1::check_data() noexcept
{
    std::cout << "DemoObj1: " << m_data.s_int << "\n" << "DemoObj1: " << m_data.s_char << "\n";
    return 0;
}
