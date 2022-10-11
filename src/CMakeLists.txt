get_filename_component(LIB_PATH "." ABSOLUTE)

file(GLOB_RECURSE LIB_CXX_SOURCES ${LIB_PATH}/*.cpp)
file(GLOB_RECURSE LIB_HEADERS ${LIB_PATH}/*.hpp ${LIB_PATH}/*.ipp)

add_library(compiler STATIC ${LIB_CXX_SOURCES} ${LIB_HEADERS})
target_link_libraries(compiler PUBLIC fmt::fmt)
target_include_directories(compiler PUBLIC ${LIB_PATH})

# Configure llvm

find_package(LLVM REQUIRED CONFIG)

target_include_directories(compiler PRIVATE ${LLVM_INCLUDE_DIRS})
target_link_libraries(compiler PRIVATE ${llvm_libs})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader)

