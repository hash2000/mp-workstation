cmake_minimum_required(VERSION 3.0.0)

set(NAVIGATOR_VERSION_MAJOR 1)
set(NAVIGATOR_VERSION_MINOR 0)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/bin/)

# set(WX_CONFIG_UNICODE_FLAG --unicode=yes)
# set(WX_CONFIG_SHARED_FLAG --static=yes)
# set(WX_TOOLKIT_FLAGS --toolkit=gtk2)
# set(WX_VERSION_FLAG --version=3.0)
# set(WX_CXX_FLAGS --cxxflags)
# set(WX_LIBRARIES --libs core,base,adv)

# set(WX_CONFIG wx-config)
# set(WX_CONFIG_FLAGS ${WX_CONFIG_UNICODE_FLAG} ${WX_TOOLKIT_FLAGS} ${WX_VERSION_FLAG} )

# execute_process(COMMAND ${WX_CONFIG} ${WX_CXX_FLAGS} ${WX_CONFIG_FLAGS} ${WX_LIBRARIES}
#     OUTPUT_VARIABLE WX_COMPILER_FLAGS    
#     )
# message("wxWidgets comtiler flags")
# message(${WX_COMPILER_FLAGS})
# message("wxWidgets comtiler flags")

set(COMPILER_FLAGS -Wall -Wextra -Wunused-parameter -ggdb ${WX_COMPILER_FLAGS})

# file(STRINGS "${PROJECT_SOURCE_DIR}/include/wxdeps.d"
#     WX_DEPENDS_FILES
#     NEWLINE_CONSUME
#     )



add_subdirectory(Tools/Navigator)