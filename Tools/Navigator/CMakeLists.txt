
project(Navigator)

message("Generate project ${PROJECT_NAME}...")


include_directories(
  ${PROJECT_SOURCE_DIR}/images/
  ${PROJECT_SOURCE_DIR}/include/
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


# Сборка проекта
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include(${wxWidgets_USE_FILE})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

message("Generate project ${PROJECT_NAME} Done")
