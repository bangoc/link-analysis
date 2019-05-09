project(LinkAnalysis)
add_subdirectory(third-party/eigen)
add_subdirectory(third-party/glog)
add_subdirectory(third-party/json)
include_directories(third-party/eigen
                    third-party/json/single_include)
add_executable(hello hello.cc)
add_executable(la pagerank.cc
                  hits.cc
                  link_analyzer_main.cc
                  format_helper.cc)
target_link_libraries(la glog)