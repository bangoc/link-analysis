project(LinkAnalysis)
add_subdirectory(third-party/eigen)
add_subdirectory(third-party/glog)
add_subdirectory(third-party/json)
add_subdirectory(third-party/Simple-Web-Server)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(third-party/eigen
                    third-party/json/single_include
                    $ENV{BOOST_HOME}
                    third_party/Simple-Web-Server)
add_executable(hello hello.cc)

SET(LIB_Src pagerank.cc
            hits.cc
            format_helper.cc
            input_helper.cc)
add_executable(la ${LIB_Src}
                  link_analyzer_main.cc)
target_link_libraries(la glog)

add_executable(server ${LIB_Src}
                      link_analysis_server.cc)
target_link_libraries(server simple-web-server glog)

add_executable(test_string_parser test/parse_string.cc ${LIB_Src})
target_link_libraries(test_string_parser glog)
