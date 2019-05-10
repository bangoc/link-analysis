project(LinkAnalysis)
add_subdirectory(third-party/eigen)
add_subdirectory(third-party/glog)
add_subdirectory(third-party/json)
add_subdirectory(third-party/Simple-Web-Server)
include_directories(third-party/eigen
                    third-party/json/single_include
                    $ENV{BOOST_HOME}
                    third_party/Simple-Web-Server)
add_executable(hello hello.cc)
add_executable(la pagerank.cc
                  hits.cc
                  link_analyzer_main.cc
                  format_helper.cc
                  input_helper.cc)
target_link_libraries(la glog)

add_executable(server link_analysis_server.cc)
target_link_libraries(server simple-web-server glog)