
project(NavigatorServer)
message("Generate project ${PROJECT_NAME}...")

include_directories(
  ${PROJECT_SOURCE_DIR}/include/
  PRIVATE ${PostgreSQL_INCLUDE_DIRS}
  PRIVATE ${LevelDB_INCLUDE}
)
 
file(GLOB SOURCE_FILES
  ${PROJECT_SOURCE_DIR}/src/Server.cpp

  ${PROJECT_SOURCE_DIR}/src/db/model/*.cpp
  ${PROJECT_SOURCE_DIR}/src/db/log/*.cpp

  ${PROJECT_SOURCE_DIR}/src/request/*.cpp
  ${PROJECT_SOURCE_DIR}/src/request/content/*.cpp
  ${PROJECT_SOURCE_DIR}/src/request/controller/*.cpp
  ${PROJECT_SOURCE_DIR}/src/request/layout/*.cpp
  ${PROJECT_SOURCE_DIR}/src/request/route/*.cpp

  ${PROJECT_SOURCE_DIR}/src/app/*.cpp

)

# Сборка проекта
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC
  Poco::Foundation
  Poco::SQL
  Poco::SQLPostgreSQL
  Poco::Net 
  Poco::NetSSL 
  Poco::Crypto
  Poco::JSON
  Poco::XML
  OpenSSL::SSL 
  OpenSSL::Crypto
  ${LevelDB_LIBRARY}
  snappy
)

message("Generate project ${PROJECT_NAME} Done")
