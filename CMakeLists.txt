PROJECT(trainsManager)
cmake_minimum_required(VERSION 3.5)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(trainsManager ${DIR_SRCS})
