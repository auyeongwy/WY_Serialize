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
 * \file Demo.cpp
 * This is an example application for using the WY_Serialize library. 
*/
#include <iostream>
#include <cstring>
#include "DemoObj1.hpp"
#include "DemoObj2.hpp"
#include "WY_SerializeMgr.hpp"
#include "WY_DebugIO.hpp"

using namespace WY_Serialize;

int main(int argc, char * argv[])
{
    WY_DebugIO::set_debug_print(true); /* Or don't call this so debug IO function calls won't work. */
    WY_DebugIO::debug_print("Debug IO initialized.");

    DemoObj1 obj1; /*Create a demo obj.*/
    obj1.check_data();
    char tmp[] = "Hello World!";
    DemoObj2 obj2;
    if(obj2.set_data(std::strlen(tmp)+1, (unsigned char *)tmp)== -1) {
        std::cout << "Caught Exception. Exit." << "\n";
        return -1;
    }
    obj2.check_data();

    try {
        WY_SerializeMgr mgr; /*Create the serialize mgr.*/
        mgr.add_serialize_obj(&obj1); /* Add objects that need to be serialized to WY_SerializeMgr. */
        mgr.add_serialize_obj(&obj2);
        mgr.save_all_objs("savefile"); /* Save all objects to file. */
        mgr.load_all_objs("savefile"); /* Now load all data from file back into the objects. */
        obj1.check_data();
        obj2.check_data();
    } catch (int &e) {
        std::cout << "Caught Exception. Exit." << "\n";
    }

    return 0;
}