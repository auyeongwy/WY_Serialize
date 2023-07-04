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

#include <exception>
#include <fstream>
#include <cstring>
#include <iostream>
#include "WY_SerializeAgent.hpp"
#include "WY_DebugIO.hpp"
using namespace WY_Serialize;


WY_SerializeAgent::WY_SerializeAgent()
{
    m_file_data_size = 0;
    m_file_data_offset = 0;
    m_file_data = NULL;
}


WY_SerializeAgent::~WY_SerializeAgent()
{
    clear_file_buffer();
    if(m_file.is_open())
        m_file.close();
}


void WY_SerializeAgent::set_file_name(const char *__restrict__ const p_name)
{
    try {
        m_file_name = p_name;
        WY_DebugIO::debug_print("Set file: ");
        WY_DebugIO::debug_print(p_name);
    } catch (std::exception &e) {
        throw -1;
    }
}


void WY_SerializeAgent::load_from_file()
{
    if(m_file_name.size()==0) {
        WY_DebugIO::debug_print("File name undefined.");
        throw -1;
    } 

    clear_file_buffer(); /* Ensure buffers are clear. */
    if(m_file.is_open()) /* A file still open. */
        m_file.close();

    m_file.open(m_file_name, std::fstream::in | std::fstream::binary);
    if(!m_file.is_open()) {/* File error at the start, exit with error. */
        WY_DebugIO::debug_print("Open file for reading failed.");
        throw -1;
    }

    m_file.seekg(0, m_file.end); /* Go to end of file. */
    int tmp = m_file.tellg(); /* Get size of file content. */
    m_file.seekg(0, m_file.beg); /* Return to start of file. */
    if((tmp>=0) && (m_file.good())) 
        m_file_data_size = tmp;
    else {
        WY_DebugIO::debug_print("Parsing file failed.");
        goto err_exit;
    }

    try {
        m_file_data = new char[m_file_data_size];
        m_file.read(m_file_data, m_file_data_size); /* Get file content into buffer. */
        if(m_file.good())
            goto good_exit;
        else
            WY_DebugIO::debug_print("Read file content failed.");
    } catch (std::exception &e) { 
        goto err_exit;
    }

err_exit: /* All errors exit from here.*/
    clear_file_buffer();
    throw -1;
good_exit: /* Good exit without errors.*/
    m_file.close();
    WY_DebugIO::debug_print("File data loaded.");
}


void WY_SerializeAgent::prepare_save_file()
{
    if(m_file_name.size()==0) {
        WY_DebugIO::debug_print("File name undefined.");
        throw -1;
    }

    /* Opens file for output, discard all current content. */
    m_file.open(m_file_name, std::fstream::out | std::fstream::binary | std::fstream::trunc);
    if(m_file.fail()) {
        WY_DebugIO::debug_print("Open file failed.");
        throw -1;        
    }

    WY_DebugIO::debug_print("File opened.");
}


void WY_SerializeAgent::finalise_save_file()
{
    m_file.close();
    if(m_file.fail()) {
        WY_DebugIO::debug_print("Saving file failed.");
        throw -1;
    }

    WY_DebugIO::debug_print("File saved.");
}


void WY_SerializeAgent::append_save_file(S_SerializeData *__restrict__ const p_data)
{
    const unsigned int min_size = sizeof(S_SerializeData::m_type) + sizeof(S_SerializeData::m_size); /* Min size of data. */
    if(!m_file.is_open()) {
        WY_DebugIO::debug_print("Trying to save to non-opened file.");
        throw -1;
    }

    m_file.write((char *)p_data, min_size);
    m_file.write((char *)(p_data->m_data), p_data->m_size);
    if(m_file.fail()){
        WY_DebugIO::debug_print("Write to file NOK. Data Type: ");
        WY_DebugIO::debug_print(p_data->m_type);
        throw -1;
    }

    WY_DebugIO::debug_print("Write to file OK. Data Type / size: ");
    WY_DebugIO::debug_print(p_data->m_type);
    WY_DebugIO::debug_print(min_size + p_data->m_size);
}


void WY_SerializeAgent::clear_loaded_file_buffer() noexcept
{
    clear_file_buffer();
}


int WY_SerializeAgent::load_next_serializable_data(S_SerializeData *__restrict__ const p_data) noexcept
{
    const unsigned int min_size = sizeof(S_SerializeData::m_type) + sizeof(S_SerializeData::m_size); /* Min size of data required. */
    if((m_file_data_size-m_file_data_offset) >= min_size) { /* Is there enough data in m_file_data. */
        memcpy(p_data, m_file_data+m_file_data_offset, min_size);
        m_file_data_offset += min_size;
    } else
        return -1;
    
    if(m_file_data_size - m_file_data_offset >= p_data->m_size) {
        try {
            p_data->m_data = new unsigned char[p_data->m_size];
            memcpy(p_data->m_data, m_file_data+m_file_data_offset, p_data->m_size);
        } catch (std::exception &e) {
            WY_DebugIO::debug_print("Memory alloc error loading data segment. Data Type: ");
            WY_DebugIO::debug_print(p_data->m_type);        
            return -1;
        }
    } else
        return -1;

    m_file_data_offset += p_data->m_size;
    WY_DebugIO::debug_print("Data segment loaded. Data Type / size: ");
    WY_DebugIO::debug_print(p_data->m_type);
    WY_DebugIO::debug_print(min_size + p_data->m_size);
    return 0;
}


void WY_SerializeAgent::clear_file_buffer() noexcept
{
    m_file_data_size = 0;
    m_file_data_offset = 0;
    if(m_file_data != NULL) {
        delete[] m_file_data;
        m_file_data = NULL;
    }
}
