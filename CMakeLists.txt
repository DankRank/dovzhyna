CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(dovzhyna VERSION 0.0.0)

ADD_LIBRARY(dovzhyna STATIC dovzhyna.c dovzhyna.h op_basic_info.h op_basic_info_0f.h)
SET_TARGET_PROPERTIES(dovzhyna PROPERTIES PUBLIC_HEADER "dovzhyna.h")

ADD_EXECUTABLE(dovzhyna_test test.cc)
TARGET_LINK_LIBRARIES(dovzhyna_test dovzhyna)

INSTALL(TARGETS dovzhyna
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER DESTINATION include)

SET(DESCRIPTION "dovzhyna - x86 (IA32) instruction length decoding library")
SET(PACKAGE_NAME "dovzhyna")
SET(AUTHOR "Egor")
