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

#ifndef _WY_SERIALIZE_TYPES_HPP_
#define _WY_SERIALIZE_TYPES_HPP_ 

namespace WY_Serialize {

/** 
 * Provides IDs to the different serializable types. Overwrite the IDs here for different implementations.
 */
enum SERIALIZE_TYPE {
    DEMO_OBJ1 = 1,
    DEMO_OBJ2
};
}

#endif