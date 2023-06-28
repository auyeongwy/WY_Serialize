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

#ifndef _WY_SERIALIZE_MGR_HPP_
#define _WY_SERIALIZE_MGR_HPP_

#include "WY_SerializeAgent.hpp"
#include "DemoObj1.hpp"
#include "WY_SerializeObj.hpp"
#pragma once
namespace WY_Serialize
{
/**
 * Implements the serialization manager. 
 *  
 * Each application has its own unique serialization structure. Some may have components which are developed by different teams that need to be serialized. The strategy is that a manager class orchestrates all the different components that need to save or load data. It decides what order will the data be saved or loaded, what happens if there is an error, etc. The different teams in charge of the different components will have to inherit the WY_SerializeObj abstract class and implement their own save() and load() functions for serialization. \n
 * \n
 * In this manner, each serializable component is wholly in charge of what data to save and how to load their saved data retrieved from a save file. They can make changes to their own data and only need to ensure their save() and load() functions are correctly implemented. No code changes are required in this WY_SerializeMgr class. \n
 * \n
 * Example usage: \n
 * \n
 * #include "WY_DebugIO.hpp" // Optional to use debug print. \n
 * #include "WY_SerializeMgr.hpp" \n
 * using namespace WY_Serialize; \n
 * ...... \n
 * set_debug_print(true); // Optional to use debug print. \n
 * DemoObj1 obj1; // Object that inherits and implements the WY_SerializeObj class. \n
 * DemoObj2 obj2; // Object that inherits and implements the WY_SerializeObj class. \n
 * try { \n
 *  C_SerializeMgr mgr; \n
 *  mgr.add_serialize_obj(&obj1); \n
 *  mgr.add_serialize_obj(&obj2); \n
 *  mgr.save_all_objs(); // Saves data to file. \n
 * } catch (int &e) { \n
 *      std::cout << "IO errors" << "\n"; \n
 * } \n
 * \n
 * mgr.save_all_objs(); \n 
 * 
 */
class WY_SerializeMgr
{
public:
    /**
     * Constructor.
     * \param p_size Max number of WY_SerializeObj supported. Defaults to 8.
     * \throw Integer exception if error. 
    */
    WY_SerializeMgr(const unsigned long p_size=8);

    /**
     * Destructor.
    */
    ~WY_SerializeMgr();


    /**
     * Saves all WY_SerializeObj objects added to the WY_SerializeMgr to file. This is done in the exact same sequence where WY_SerializeObj objects are added. So the sequence where the objects are loaded must match the sequence where they are saved.
     * \param p_file Name of the file to save to,
     * \throw -1 integer exception if there is an error - usually a file IO error. An easy way to debug is to call the global static function set_debug_print(true);
    */
    void save_all_objs(const char *__restrict__ const p_file);

    /**
     * Loads all content from the save file into WY_SerializeObj objects added to the WY_SerializeMgr. This is done in the exact same sequence where WY_SerializeObj objects are added. So the sequence where the objects are loaded must match the sequence where they are saved.
     * \param p_file Name of the file to load from.
     * \throw -1 integer exception if there is an error - usually a file IO error. An easy way to debug is to call the global static function set_debug_print(true);
    */
    void load_all_objs(const char *__restrict__ const p_file);

    /**
     * Adds a WY_SerializeObj to be managed by this WY_SerializeMgr. Only the pointer to the WY_SerializeObj object is copied, so deallocation of the original object needs to be handled separately. 
     * \param p_obj A WY_SerializeObj to be managed by this WY_SerializeMgr.
     * \return 0 if no error. -1 if error - usually caused by insufficient space allocated to this WY_SerializeMgr object.
    */
    int add_serialize_obj(WY_SerializeObj *__restrict__ const p_obj) noexcept;

private:
    unsigned long m_serializeobj_array_size; /**< Max size of the number of WY_SerializeObj supported. */
    unsigned long m_serializeobj_array_offset; /**< Current offset of the WY_SerializeObj array. */
    std::string m_file_name; /**< The current file that is being processed. */
    WY_SerializeObj ** m_serializeobj_array; /**< The array of pointers to WY_SerializeObj. */
};
}

#endif
