project(Database)
message("Generate library Database from ${PROJECT_SOURCE_DIR}...")

include_directories(
  ${PROJECT_SOURCE_DIR}/include/
  PRIVATE ${PostgreSQL_INCLUDE_DIRS}
  PRIVATE ${LevelDB_INCLUDE}
)
 
file(GLOB SOURCE_FILES
  ${PROJECT_SOURCE_DIR}/src/Database.cpp


)

# Сборка библиотеки
add_library(Database ${SOURCE_FILES})
add_library(mp::Database ALIAS Database)

target_link_libraries(Database PUBLIC
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

message("Generate library Database Done")
