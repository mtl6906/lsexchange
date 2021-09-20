project(lsexchange)

cmake_minimum_required(VERSION 3.10)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

include_directories(include)

link_directories(/usr/local/lib)

aux_source_directory(src/ls/exchange SRC)

add_library(lsexchange SHARED ${SRC})

install(TARGETS lsexchange DESTINATION lib)

install(DIRECTORY include/ls/exchange DESTINATION include/ls)

#target_link_libraries(testcase lshttp lsexception lscstring lsitem lscopyableitem lslogger lstime lsssl lsio ssl lsbuffer lsnet lsepoll lsjson lssha256)
