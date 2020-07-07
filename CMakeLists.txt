CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(dovzhyna VERSION 0.0.0 LANGUAGES C)

ADD_LIBRARY(dovzhyna STATIC dovzhyna.c dovzhyna.h x86optab.h)
SET_TARGET_PROPERTIES(dovzhyna PROPERTIES PUBLIC_HEADER "dovzhyna.h")

ADD_EXECUTABLE(dovzhyna_test test.c)
TARGET_LINK_LIBRARIES(dovzhyna_test dovzhyna)

INSTALL(TARGETS dovzhyna
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER DESTINATION include)

SET(DESCRIPTION "dovzhyna - x86 (IA32) instruction length decoding library")
SET(PACKAGE_NAME "dovzhyna")
SET(AUTHOR "Egor")
