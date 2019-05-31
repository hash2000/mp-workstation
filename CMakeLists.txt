cmake_minimum_required(VERSION 3.0.0)

set(NAVIGATOR_VERSION_MAJOR 1)
set(NAVIGATOR_VERSION_MINOR 0)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
message(${CMAKE_INSTALL_PREFIX})


set(COMPILER_FLAGS -Wall -Wextra -Wunused-parameter -ggdb)

set(wxWidgets_CONFIG_OPTIONS --toolkit=gtk2 --version=3.0 --unicode=yes --static=no)
message(${wxWidgets_CONFIG_OPTIONS})

add_subdirectory(Tools/Navigator)