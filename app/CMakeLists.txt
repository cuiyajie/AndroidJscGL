cmake_minimum_required(VERSION 3.4.1)

file(GLOB app_src_files
       "src/main/cpp/*.cpp" )

add_library( native-lib SHARED ${app_src_files} )

add_library( jsc SHARED IMPORTED)

set_target_properties( jsc
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libjsc.so )

find_library( log-lib log )
target_link_libraries( native-lib ${log-lib} jsc EGL GLESv2 )