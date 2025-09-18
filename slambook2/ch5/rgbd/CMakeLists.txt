find_package(Sophus REQUIRED)
# include_directories( ${Sophus_INCLUDE_DIRS} ) # I have no idea why this can't work
include_directories(${PROJECT_SOURCE_DIR}/../3rdparty/Sophus)

find_package(Pangolin REQUIRED)

add_executable(joinMap joinMap.cpp)
target_link_libraries(joinMap ${OpenCV_LIBS} ${Pangolin_LIBRARIES})