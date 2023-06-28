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
 * \file DemoObj2.cpp
 * Example demo code to illustrate the use of the WY_Serialize library.
*/
#include <cstring>
#include <iostream>
#include "DemoObj2.hpp"
using namespace WY_Serialize;


DemoObj2::DemoObj2() noexcept
{
    m_data.s_size = 0;
    m_data.s_data = NULL;
}


DemoObj2::~DemoObj2()
{
    clear_data();
}


int DemoObj2::set_data(const unsigned long p_size, const unsigned char *__restrict__ const p_data) noexcept
{
    clear_data();
    try{
        m_data.s_data = new unsigned char[p_size];        
    } catch (std::exception &e) {
        m_data.s_data = NULL;
        return -1;
    }
    memcpy(m_data.s_data, p_data, p_size);
    m_data.s_size = p_size;
    return 0;
}


int DemoObj2::get_save_data(S_SerializeData *__restrict__ const p_data) noexcept
{
    p_data->m_type = DEMO_OBJ2;
    p_data->m_size = m_data.s_size;
    p_data->m_data = m_data.s_data;
    return 0;
}


int DemoObj2::get_load_data(const unsigned long p_size, const unsigned char *__restrict__ const p_data) noexcept
{
    clear_data();
    
    try {
        m_data.s_data = new unsigned char[p_size];
    } catch (std::exception &e) {
        m_data.s_data = NULL;
        return -1;
    }
    memcpy(m_data.s_data, p_data, p_size);
    m_data.s_size = p_size;
    return 0;
}


int DemoObj2::check_data() noexcept
{
    std::cout << "DemoObj2: " << m_data.s_data << "\n";
    return 0;
}


inline void DemoObj2::clear_data() noexcept
{
    if(m_data.s_size > 0) {
       delete[] m_data.s_data;
       m_data.s_data = NULL;
       m_data.s_size = 0; 
    }
}
