
project(DatabaseCmd)
message("Generate project ${PROJECT_NAME} from ${PROJECT_SOURCE_DIR}...")

include_directories(
  ${PROJECT_SOURCE_DIR}/include/
  PRIVATE ${PostgreSQL_INCLUDE_DIRS}
  PRIVATE ${LevelDB_INCLUDE}
)
 
file(GLOB SOURCE_FILES
  ${PROJECT_SOURCE_DIR}/src/DatabaseCmd.cpp



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
