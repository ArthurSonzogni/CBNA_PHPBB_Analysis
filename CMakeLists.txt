cmake_minimum_required (VERSION 3.1)
project (CBNA_PHPBB_importer)

# Add a new module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# LIB(CURL)
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

# Build Cumbo-parser
file(GLOB_RECURSE source-gumbo-parser "lib/gumbo-parser/src/*.c")
add_library(gumbo-parser ${source-gumbo-parser})

# Build Cumbo-parser
file(GLOB_RECURSE source-gumbo-query "lib/gumbo-query/src/*.cpp")
add_library(gumbo-query ${source-gumbo-query})
target_include_directories(gumbo-query PUBLIC "lib/gumbo-parser/src")
include_directories("lib")


# EXECUTABLE(importer)
file(GLOB_RECURSE source "src/*.cpp")
add_executable(importer ${source})
target_link_libraries(importer PUBLIC
    ${CURL_LIBRARIES}
		gumbo-query
		gumbo-parser
)
include_directories(src)

# ENABLE(c++11)
set_property(TARGET importer PROPERTY CXX_STANDARD 11)
