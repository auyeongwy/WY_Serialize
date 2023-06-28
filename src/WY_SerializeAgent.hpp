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

#ifndef _WY_SERIALIZE_AGENT_HPP_
#define _WY_SERIALIZE_AGENT_HPP_

#include <fstream>
#include "WY_SerializeObj.hpp"
#include "DemoObj1.hpp"
#pragma once
namespace WY_Serialize
{

/** Implements serialization.
 * Usage: \n
 * \n
 * WY_SerializeAgent agent; \n
 * S_SerializableData s_data; \n
 * init_serializable_data(&s_data); \n
 * ... // Copy serializable data into s_data. \n
 * \n
 * try { \n
 *  agent.set_file_name("savefile"); \n
 *  agent.prepare_save_file(); \n
 *  agent.append_save_file(&s_data); // Writes data to file. \n
 *  agent.finalise_save_file(); // Saves the file. \n
 *  \n
 *  ..... \n
 *  agent.load_from_file(); // Load all file content into memory. \n
 *  init_serializable_data(&s_data); // Clean up the data structure before use. \n
 *  agent.get_next_serializable_data(&s_data); // Gets the next chunk of serializable data. \n
 *  .... // Copy and process the data in s_data as required. \n
 *  agent.clear_loaded_serializable_data(&s_data); \n
 * } catch (int &e) { \n
 *  std::cout << "IO error" << "\n"; \n
 * } \n
 */
class WY_SerializeAgent
{
public:
    WY_SerializeAgent(); /**< Constructor.*/
    ~WY_SerializeAgent(); /**< Destructor.*/

    /**
     * Sets name of the current file to work on. It is mandatory to set this before calling any other file operation.
     * \param p_name Name of the file. In this implementation we use the C++ string class so an exception is thrown if the size of the file name exceeds the system-allowed length.
     * \throw Non-0 integer if error.
    */
    void set_file_name(const char *__restrict__ const p_name);

    /** 
     * Opens and loads data from the save file and then closes the file. 
     * Writes size into m_file_data_size and data into m_file_data.
     * \return 0 if no error. Else non-zero.
    */
    void load_from_file();

    /** 
     * Prepares a save file for saving data. This erases any existing content in the file. The file remains open until finalise_save_file() is called.
     * \throw Non-0 integer if error.
    */
    void prepare_save_file();

    /** 
     * Saves the currently opened save file to IO. 
     * \throw Non-0 integer if error.
    */
    void finalise_save_file();

    /** Appends save data to an opened save file. Saved data is only finalised after a call to finalise_save_file().
     * \throw Non-0 integer if error.
    */
    void append_save_file(S_SerializeData *__restrict__ const p_data);

    /**
     * Loads the next block of serializable data from data in the save file.
     * \param p_data Returns the next block of serialized data from the loaded save file.
     * \return 0 if non-error. -1 if there is an error with the next serializable block of data.
    */
    int load_next_serializable_data(S_SerializeData *__restrict__ const p_data) noexcept;

    /**
     * This is a dealloc cleanup operation that clears buffers after a load_from_file() and we are done reading loaded data. Mandatory to call. 
    */
    void clear_loaded_file_buffer() noexcept;

private:
    /** 
     * Clears content of m_file_data_size and m_file_data.
    */
    void clear_file_buffer() noexcept;

    unsigned long m_file_data_size; /**< Size of the serializable data. Only used for loading operations. */
    unsigned long m_file_data_offset; /**< Current offset in m_file_data. */
    
    std::string m_file_name; /**< Name of the file currently worked on. */
    std::fstream m_file; /**< The serializable file object. Only used for saving operations. */
    char * __restrict__ m_file_data; /**< The serializable data. Only used for loading operations.*/
};
}

#endif