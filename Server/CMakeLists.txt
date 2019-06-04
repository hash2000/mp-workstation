
project(NavigatorServer)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
  ) 


file(GLOB SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/Navigator.cpp

    ## logger files
    ${PROJECT_SOURCE_DIR}/src/log/*.cpp
    ${PROJECT_SOURCE_DIR}/src/log/view/*.cpp

    ## taskbar
    ${PROJECT_SOURCE_DIR}/src/taskbar/*.cpp

    ## program views
    ${PROJECT_SOURCE_DIR}/src/view/panel/*.cpp
    ${PROJECT_SOURCE_DIR}/src/view/*.cpp
  )


add_executable(${PROJECT_NAME} ${SOURCE_FILES})


find_package(wxWidgets REQUIRED net gl core base adv aui) 
include(${wxWidgets_USE_FILE})



# and for each of your dependent executable/library targets:
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
