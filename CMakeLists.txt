CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(dovzhyna VERSION 0.0.0)

ADD_LIBRARY(dovzhyna STATIC dovzhyna.cc dovzhyna.hh op_basic_info.hh op_basic_info_0f.hh)
SET_TARGET_PROPERTIES(dovzhyna PROPERTIES PUBLIC_HEADER "dovzhyna.hh")

ADD_EXECUTABLE(dovzhyna_test test.cc)
TARGET_LINK_LIBRARIES(dovzhyna_test dovzhyna)

INSTALL(TARGETS dovzhyna
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER DESTINATION include)

SET(DESCRIPTION "dovzhyna - x86 (IA32) instruction length decoding library")
SET(PACKAGE_NAME "dovzhyna")
SET(AUTHOR "Egor")
