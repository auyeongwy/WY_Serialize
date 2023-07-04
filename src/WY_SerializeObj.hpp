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

#ifndef _WY_SERIALIZE_OBJ_HPP_
#define _WY_SERIALIZE_OBJ_HPP_

#include "WY_SerializeDef.hpp"
#pragma once
namespace WY_Serialize
{
/** 
 * Virtual class to implement serialization with virtual functions.
 * The virtual functions allow other callers to trigger a save/load operations on this class. 
*/
class WY_SerializeObj
{
public:
    /** 
     * Virtual destructor.
    */
    virtual ~WY_SerializeObj() {};

    /** 
     * Virtual function that returns the data to be saved. This is called so the caller can save the data prepared. Any data should be deallocated only after the data is saved.
     * \param p_data Returns the data to be saved.
     * \return 0 if no error, non-zero if error.
    */ 
    virtual int get_save_data(S_SerializeData *__restrict__ const p_data) noexcept {return -1;};
    
    /** 
     * Virtual function that gets the data that is loaded from file.
     * \param p_size Size of the data that is loaded.
     * \param p_data The loaded data.
     * \return 0 if no error, non-zero if error.
    */     
    virtual int get_load_data(const unsigned int p_size, const unsigned char *__restrict__ const p_data) noexcept {return -1;};

    /**
     * Virtual function to check the serializable data. Specific to implementation, so this can be ignored if so desired.
     * \return 0 iff no error. Non-zero if error.
    */
    virtual int check_data() noexcept {return -1;};
};
}

#endif