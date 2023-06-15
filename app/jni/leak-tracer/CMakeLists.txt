set(leaktracer "leaktracer")

set(leaktracer_source
    ${CMAKE_CURRENT_LIST_DIR}/src/MemoryTrace.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AllocationHandlers.cpp
)
add_library(${leaktracer} STATIC ${leaktracer_source})
target_include_directories(${leaktracer} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)