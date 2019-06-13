
project(NavigatorServer)
message("Generate project ${PROJECT_NAME}...")

include_directories(
  ${PROJECT_SOURCE_DIR}/include/
  PRIVATE ${PostgreSQL_INCLUDE_DIRS}
)
 
file(GLOB SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/Server.cpp
  )

# Сборка проекта
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC
  Poco::Foundation
  Poco::SQL
  #Poco::SQLPostgreSQL
  Poco::Net 
  Poco::NetSSL 
  Poco::Crypto
  OpenSSL::SSL 
  OpenSSL::Crypto
  #PostgreSQL::client
)

message("Generate project ${PROJECT_NAME} Done")
