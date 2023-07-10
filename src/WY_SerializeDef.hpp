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

#ifndef _WY_SERIALIZE_DEF_HPP_
#define _WY_SERIALIZE_DEF_HPP_

#include <cstddef>
#pragma once
namespace WY_Serialize 
{

/** 
 * Struct for saving serializable data object.
 */
struct S_SerializeData {
    unsigned int m_type; /**< Type of data, defined from enum SERIALIZE_TYPE. */
    unsigned int m_size; /**< Size of the serializable data. */
    unsigned char * m_data; /**< The data itself. */
};


/**
 * Inline helper function to init a S_SerializeData struct before use. Call this before using of re-using any S_SerializeData. 
 * \param p_data The S_SerializeData struct to initialise. 
 */
inline void init_serializable_data(S_SerializeData *__restrict__ const p_data) noexcept {
    p_data->m_type = 0;
    p_data->m_size = 0;
    p_data->m_data = NULL;
}

/**
 * Inline function to get the total size within a S_SerializeData structure.
 * \param p_data The S_SerializeData structure to get the size from.
 * \return Size of p_data.
 */
inline unsigned int get_total_data_len(S_SerializeData *__restrict__ const p_data) noexcept {
    return sizeof(p_data->m_type) + sizeof(p_data->m_size) + p_data->m_size;
}

/**
 * Inline helper function to clear a S_SerializeData struct after it was loaded with save data from a file. This is because this data is definitely dynamically allocated. This function also automatically calls init_serializable_data() implicitly so the struct is ready for reuse.  
 * \param p_data The S_SerializeData struct to clear. 
 */
inline void clear_loaded_serializable_data(S_SerializeData *__restrict__ const p_data) noexcept {
    if(p_data->m_size > 0) {
        delete[] p_data->m_data;
    }
    init_serializable_data(p_data);
}

}

#endif