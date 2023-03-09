cmake_minimum_required(VERSION 3.4.1)
find_library(log-lib log)
include_directories(${CMAKE_CURRENT_LIST_DIR}/jni/ffmpeg/include)

set(third-party-libs
    avformat
    avcodec
    avfilter
    swresample
    swscale
    avutil
)
add_library(native-lib SHARED src/main/cpp/native-lib.cpp)

# 静态库的添加方式
# link_directories(${CMAKE_CURRENT_LIST_DIR}/jni/ffmpeg/prebuilt/android/${CMAKE_ANDROID_ARCH_ABI})
# target_link_libraries(native-lib ${log-lib} ${third-party-libs})

# 动态库的添加方式
foreach(lib ${third-party-libs})
    add_library(${lib} SHARED IMPORTED)
    set_target_properties(${lib} PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/jni/ffmpeg/prebuilt/android/${CMAKE_ANDROID_ARCH_ABI}/lib${lib}.so
    )
    target_link_libraries(native-lib ${lib})
endforeach()

target_link_libraries(native-lib ${log-lib})