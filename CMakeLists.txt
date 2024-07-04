cmake_minimum_required(VERSION 3.22.2)
project(GenericADT C)

message(STATUS "Using CMake version ${CMAKE_VERSION}")

 # Default the filename postfix when debug is target build
set(CMAKE_DEBUG_POSTFIX d)

# Add our cmake folder to the module path
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
message("Added ${PROJECT_NAME}'s module path to CMakes module path")
 
include(Macros)
message("Included macros")
include(GNUInstallDirs)
message("Inlcuded GNU install dirs")


# Data structure library options
option(INC_HTBL "Includes the hashtable ADT" OFF)
option(BUILD_TEST "Run tests on the selected ADTs" OFF)

set(ADT_SRC)        # Initial Source Files
set(ADT_PUBLIC_API) # Initial Interface files

# Convert to function, macro, or is my approach flawed?
if(INC_HTBL)
    append_to_api(ADT_PUBLIC_API "src/hashtable/hashtable.h")
    add_subdirectory("./src/hashtable")

    if(BUILD_TEST)
        message("Including Hashtable tests")
        add_executable(htbl_test "./tests/TestHashtable.c")
        target_link_libraries(htbl_test Unity objHtbl)      # Connect the tests with the framework and the htbl.o file
        add_test(NAME htbl_test COMMAND $<TARGET_FILE:htbl_test>)
    endif()

endif()

# I read somewhere this is terrible practice and should be burned... I'll look into it.
# Add required elements for testing
if(BUILD_TEST)
    include(CTest)
    add_subdirectory(external) # Add testing framework
    add_subdirectory(tests)
else()

    #--------- ---- Main Target -------------------
    add_library(${PROJECT_NAME} STATIC $<TARGET_OBJECTS:objHtbl>)

    #-------------- Includes ---------------------

    set(${PROJECT_NAME}_PUBLIC_HEADERS ADT_PUBLIC_API)    # Source and header files for selected data structs

    target_include_directories(${PROJECT_NAME}
        PUBLIC
            # I don't think this line is right - we want to include specific subdirs of src based on provided options
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
            # Include this projects directory when make --install
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
    )

    set_target_properties(${PROJECT_NAME}
        PROPERTIES
            C_STANDARD 11
            C_STANDARD_REQUIRED ON
            PUBLIC_HEADER "${${PROJECT_NAME}_PUBLIC_HEADERS}"
    )
endif()

