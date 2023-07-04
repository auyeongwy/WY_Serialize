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

#include <cstdlib>
#include <iostream>
#include "WY_SerializeMgr.hpp"
#include "WY_SerializeAgent.hpp"
using namespace WY_Serialize;


WY_SerializeMgr::WY_SerializeMgr(const unsigned int p_size)
{    
    m_serializeobj_array = NULL;
    m_file_name.clear();
    try {
        m_serializeobj_array = new WY_SerializeObj * [p_size];
        m_serializeobj_array_size = p_size;
        m_serializeobj_array_offset = 0;
    } catch (std::exception &e) {
        throw -1;
    }
}


WY_SerializeMgr::~WY_SerializeMgr()
{
    if(m_serializeobj_array_size > 0)
        delete[] m_serializeobj_array;
}


void WY_SerializeMgr::save_all_objs(const char *__restrict__ const p_file)
{
    WY_SerializeAgent agent;
    S_SerializeData data;

    try {
        agent.set_file_name(p_file);
        agent.prepare_save_file();

        for(unsigned int i=0; i<m_serializeobj_array_offset; i++) {
            init_serializable_data(&data);
            m_serializeobj_array[i]->get_save_data(&data);
            agent.append_save_file(&data);            
        }
        agent.finalise_save_file();
    } catch (int &e) {
        throw -1;
    }
}


void WY_SerializeMgr::load_all_objs(const char *__restrict__ const p_file)
{
    WY_SerializeAgent agent;
    S_SerializeData data;

    try {
        agent.set_file_name(p_file);
        agent.load_from_file();
        init_serializable_data(&data);

        for(unsigned int i=0; i<m_serializeobj_array_offset; i++) {
            agent.load_next_serializable_data(&data);
            m_serializeobj_array[i]->get_load_data(data.m_size, data.m_data);
            clear_loaded_serializable_data(&data);
        }
        agent.clear_loaded_file_buffer();
    } catch (int &e) {
        throw -1;
    }
}


int WY_SerializeMgr::add_serialize_obj(WY_SerializeObj *__restrict__ const p_obj) noexcept
{
    if(m_serializeobj_array_offset+1 < m_serializeobj_array_size) {
        m_serializeobj_array[m_serializeobj_array_offset] = p_obj;
        ++m_serializeobj_array_offset;
        return 0;
    } else
        return -1;
}
