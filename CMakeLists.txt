
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
SET(CMAKE_CXX_FLAGS "-std=c++17")
project(main)
include(FindROOT.cmake)

find_package(Geant4 REQUIRED)
find_package(ROOT REQUIRED)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()


#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories("/home/wadermane/goodBuildSingleDetectorSim/singleDetectorSim/simLib/include")
link_directories("/home/wadermane/goodBuildSingleDetectorSim/singleDetectorSim/simLib/build")

ROOT_GENERATE_DICTIONARY(mySimlibs_Dict SimEvent.h LINKDEF my_SimLibs_LinkDef.h)


#include_directories("/home/7jn/G4Projects/simLib/include")
set(SimEvent_LIBRARIES "/home/wadermane/goodBuildSingleDetectorSim/singleDetectorSim/simLib/build/libmySim.so")
#target_link_libraries(main ${SimEvent_LIBRARIES})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
if(ROOT_FOUND)
add_definitions(-DG4ANALYSIS_USE_ROOT)
include(${Geant4_USE_FILE})
include_directories(${ROOT_INCLUDE_DIR} ${Geant4_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/include)
else()
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
endif()

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(main main.cc ${sources} ${headers})
target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${SimEvent_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build fission. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(my_SCRIPTS
    vis.mac
    init_vis.mac
  )

foreach(_script ${my_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


install(TARGETS main DESTINATION .)
