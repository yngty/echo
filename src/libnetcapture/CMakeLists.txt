project(netcapture)

find_library (LIBPCAP pcap)
find_library (LIBPTHREAD pthread)

file(GLOB HEAD_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/util/*.h)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/util SRC_FILES)

message(${LIBPTHREAD})
message(${LIBPCAP})
add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${HEAD_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${LIBPCAP}
    ${LIBPTHREAD})