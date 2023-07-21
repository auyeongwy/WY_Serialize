[TOC]
Introduction
============
WY_Serialize is a C++ library that provides serialization capabilities to other applications. This means applications can save the different data state of their components to a savefile and load it back. Or an even simpler way of explaining it - it allows applications to create save files and load it back.

Of course applications will have to manage what data to save and what data to load. WY_Serialize provides an API that abstracts the saving and loading features, including a save/load structure/flow that hopefully helps applications implement these features easily.

The library is developed on a Linux system, so some porting effort may be required to build it on other systems. I have adhered to using only standard C++ library APIs so hopefully the only porting effort required is to modify the build system. 

File Organisation
=================
There are 3 directories in the base directory: 

src: Contains all source code files.

build: Contains the following: 
- The Makefile.
- A sample savefile for the demo.
- After compilation, the objects files, a library lib_WY_Serialize.a and a demo application named Demo will be generated in this directory.

doc: Contains all documentation files: 
- A README.md and Doxyfile for doxygen. 
- Running doygen will generate all HTML documentation in this directory. 

Compilation and usage
=====================
Refer to the following example files for how to use the library. This is probably the best illustration as to how to use the library:

WY_SerializeTypes.hpp (Modify this for your application.) <br>
Demo.cpp <br>
DemoObj1.hpp <br>
DemoObj1.cpp <br>
DemoObj2.hpp <br>
DemoObj2.cpp <br>

To compile, enter the build directory and enter "make". This generates:
- A library file lib_WY_Serialize.a.
- A demo application Demo.

The Makefile uses the following compilation flags by default. So modify these flags for your own build system.

    CFLAGS = -O2 -Wall -march=native -DENABLE_WY_DEBUGIO

To use the library in your own application, include the necessary header files in your code and link to the library file.

`make clean` cleans up the object files. `make distclean` removes the library file and demo application as well. 

Explanation of Implementation
=============================

Saving A File
-------------
To save any data to a file, 
- The data needs to be encapsulated in an class that inherits the WY_SerializeObj class.
- Said class needs to implement the WY_SerializeObj::get_save_data() virtual function.
- Said function is of course, application-specific so you have to implement exactly what needs to be saved. See the DemoObj1 and DemoObj2 sample codes for examples.
- Add a pointer of this object to a WY_SerializeMgr object using the WY_SerializeMgr::add_serialize_obj() function.
- The order in which object pointers are added to WY_SerializeMgr will be the order in which their data will be saved.
- Call WY_SerializeMgr::save_all_objs() to save data to a file.
- The WY_SerializeMgr::save_all_objs() function will call the WY_SerializeObj::get_save_data() function in every WY_SerializeObj object added to WY_SerializeMgr to retrieve the data that needs to be saved and save it to file.

Loading A File
--------------
To load data from a file, 
- The data needs to be encapsulated in an class that inherits the WY_SerializeObj class.
- Said class needs to implement the WY_SerializeObj::get_load_data() virtual function.
- Said function is of course, application-specific so you have to implement how to copy loaded data from the file into your object. See the DemoObj1 and DemoObj2 sample codes for examples.
- Add a pointer of this object to a WY_SerializeMgr object using the WY_SerializeMgr::add_serialize_obj() function.
- The order in which object pointers are added to WY_SerializeMgr will be the order in which their data will be loaded.
- Call WY_SerializeMgr::load_all_objs() to load data from a file.
- The WY_SerializeMgr::load_all_objs() function will call the WY_SerializeObj::get_load_data() function in every WY_SerializeObj object added to WY_SerializeMgr to load the data that needs to be loaded into each object.

Memory Management
-----------------
WY_SerializeMgr will not deallocate the WY_SerializeObj objects added to it. Deallocation of these will have to be handled externally AFTER the WY_SerializeMgr itself is deallocated.

Debug IO
--------
The library uses the functions provided by the WY_DebugIO class to print debug messages. This gives the flexibility to deactive or activate all debug print messages globally as required. For example:

    C_Debug_IO::set_debug_print(true); // Debug print won't do anything unless this is called. 
    C_Debug_IO::debug_print("Debug print is activated.");  
    C_Debug_IO::set_debug_print(false); 
    C_Debug_IO::debug_print("Test."); // Nothing happens as debug print is deactivated.

If debug printing is really not required, we can optimize further by NOT passing the ENABLE_WY_DEBUGIO macro during compilation. (Example: g++ -DENABLE_WY_DEBUGIO) 