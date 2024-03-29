
project(NavigatorServer)
message("Generate project ${PROJECT_NAME} from ${PROJECT_SOURCE_DIR}...")

include_directories(
  ${PROJECT_SOURCE_DIR}/include/
  PRIVATE ${PostgreSQL_INCLUDE_DIRS}
  PRIVATE ${LevelDB_INCLUDE}
)
 
file(GLOB SOURCE_FILES
  ${PROJECT_SOURCE_DIR}/src/Server.cpp

  ${PROJECT_SOURCE_DIR}/src/db/log/*.cpp
  ${PROJECT_SOURCE_DIR}/src/db/manager/*.cpp
  ${PROJECT_SOURCE_DIR}/src/db/model/*.cpp
  ${PROJECT_SOURCE_DIR}/src/db/model/system/*.cpp

  ${PROJECT_SOURCE_DIR}/src/request/*.cpp
  ${PROJECT_SOURCE_DIR}/src/request/controller/*.cpp
  ${PROJECT_SOURCE_DIR}/src/request/controller/Admin/*.cpp
  ${PROJECT_SOURCE_DIR}/src/request/controller/System/Objects/*.cpp
  ${PROJECT_SOURCE_DIR}/src/request/controller/System/ObjectTypes/*.cpp
  
  ${PROJECT_SOURCE_DIR}/src/request/layout/*.cpp
  ${PROJECT_SOURCE_DIR}/src/request/layout/html/*.cpp
  ${PROJECT_SOURCE_DIR}/src/request/route/*.cpp
  ${PROJECT_SOURCE_DIR}/src/request/route/content/*.cpp

  ${PROJECT_SOURCE_DIR}/src/app/*.cpp

)

# Сборка проекта
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC
  Poco::Foundation
  Poco::Data
  Poco::DataPostgreSQL
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
