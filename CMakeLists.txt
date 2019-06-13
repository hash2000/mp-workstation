
# Версия CMake
cmake_minimum_required(VERSION 3.0.0)

# Модули CMake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Подключение макросов CMake
include(Utils)

# Версия приложения
set(NAVIGATOR_VERSION_MAJOR 1)
set(NAVIGATOR_VERSION_MINOR 0)

# Параметры компилятора
set_target_properties(${TARGET} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
) 

set(COMPILER_FLAGS -Wall -Wextra -Wunused-parameter -ggdb)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message("Dependent libraries")

# Поиск библиотек OpenSSL
find_package(OpenSSL REQUIRED)
message("OpenSSL Libs = " ${OPENSSL_SSL_LIBRARY})
message("OpenSSL Eay Libs = " ${SSL_EAY_LIBRARY_RELEASE})

# Поиск библиотек PostgreSQL
#   для подключения PostgreSQL требуется установка пакетов 
#   apt-get install libpq-dev postgresql-server-dev-all
find_package(PostgreSQL REQUIRED)
message("PostgreSQL Dirs = " ${PostgreSQL_INCLUDE_DIRS})
message("PostgreSQL Lib Dirs = " ${PostgreSQL_LIBRARY_DIRS})
message("PostgreSQL Libs = " ${PostgreSQL_LIBRARIES})

# Поиск библиотек wxWidgets
find_package(wxWidgets REQUIRED net gl core base adv aui) 
set(wxWidgets_CONFIG_OPTIONS --toolkit=gtk2 --version=3.0 --unicode=yes --static=no)
message("wxWidgets Files = " ${wxWidgets_USE_FILE})
message("wxWidgets Libs = " ${wxWidgets_LIBRARIES})
message("wxWidgets Options = " ${wxWidgets_CONFIG_OPTIONS})

# Поиск библиотек Poco Project
if (WIN32)
  find_package(Poco REQUIRED Foundation SQLPostgreSQL Net NetSSLWin CONFIG)
else ()
  find_package(Poco REQUIRED Foundation SQLPostgreSQL Net NetSSL Crypto CONFIG)  
endif ()

# Поиск библиотек LevelDB
find_package(LevelDB REQUIRED)
message("LevelDB Files = " ${LevelDB_INCLUDE})
message("LevelDB Libs = " ${LevelDB_LIBRARY})


# папки с подключаемыми заголовочными файлыми
include_directories(
  "/usr/include/"
#   для wxWidgets требуется указать дополнительные пути
  "/usr/include/wx-3.0/"
  "/usr/lib/x86_64-linux-gnu/wx/include/gtk2-unicode-3.0/"
)

# Добавление конфигураций проектов

add_subdirectory(Tools/Navigator)
add_subdirectory(Server)

