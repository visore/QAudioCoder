#############################################################################
# Setup and CMake
#############################################################################

PROJECT(QAudioCoder)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
CMAKE_POLICY(SET CMP0012 NEW) #Ensures that TRUE can be used as a boolean
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -fPIC)

#############################################################################
# Setup directory paths
#############################################################################

SET(ROOT ${CMAKE_CURRENT_SOURCE_DIR})
SET(HEADERS ${ROOT}/headers)
SET(SOURCES ${ROOT}/sources)
SET(EXTERNAL ${ROOT}/external)
SET(EXAMPLES ${ROOT}/examples)

#############################################################################
# Set System
#############################################################################

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	SET(MACOSX 1)
	ADD_DEFINITIONS(-DMACOSX)
	SET(SYSTEM "MACOSX" CACHE INTERNAL "Current system")
	SET(DISTRO "" CACHE INTERNAL "Linux distrobution")    
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	ADD_DEFINITIONS(-DLINUX)
	SET(SYSTEM "LINUX" CACHE INTERNAL "Current system")
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	ADD_DEFINITIONS(-DWINDOWS)
	SET(SYSTEM "WINDOWS" CACHE INTERNAL "Current system")
	SET(DISTRO "" CACHE INTERNAL "Linux distrobution")
ENDIF()

#############################################################################
# Setup installation directory paths
#############################################################################

IF(${SYSTEM} MATCHES "WINDOWS")
	SET(INSTALL_LIB_DIR lib)
	SET(INSTALL_INCLUDE_DIR include)
ELSEIF(${SYSTEM} MATCHES "LINUX" AND ${DISTRO} MATCHES "Redhat" AND ${ARCHITECTURE} MATCHES "64bit")
	SET(INSTALL_LIB_DIR lib64/qaudiocoder)
	SET(INSTALL_INCLUDE_DIR include/qaudiocoder)
ELSE()
	SET(INSTALL_LIB_DIR lib/qaudiocoder)
	SET(INSTALL_INCLUDE_DIR include/qaudiocoder)
ENDIF()

#############################################################################
# Setup Packaging and Version
#############################################################################

SET(CMAKE_MODULE_PATH ${ROOT}/cmake)
INCLUDE(Version)
INCLUDE(Macros)

#############################################################################
# Setup Qt
#############################################################################

SET(CMAKE_AUTOMOC ON)
SET(QT5_DIR "/usr/local/Qt-5.0.0" CACHE PATH "Qt5 install location (containing the bin, include and lib directories - eg: /usr/local/Qt-5.0.0)")
SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT5_DIR})
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Multimedia REQUIRED)
FIND_PACKAGE(Qt5Gui)
FIND_PACKAGE(Qt5Widgets)

INCLUDE_DIRECTORIES(${Qt5Multimedia_INCLUDE_DIRS}) # for qaudio.h

#############################################################################
# Include common headers
#############################################################################

HEADER_DIRECTORIES(GLOBAL_HEADERS)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ${GLOBAL_HEADERS})

#############################################################################
# Initiate source files
#############################################################################

FILE(GLOB BUILD_SOURCES ${SOURCES}/*.cpp ${SOURCES}/*/*.cpp ${EXTERNAL}/resample/*/*.c)
FILE(GLOB BUILD_HEADERS ${HEADERS}/*.h ${HEADERS}/*/*.h ${EXTERNAL}/resample/*/*.h)
FILE(GLOB INSTALL_HEADER_FILES ${HEADERS}/*.h ${HEADERS}/*/*.h)

#############################################################################
# Create shared library
#############################################################################

ADD_LIBRARY(qaudiocoder SHARED ${BUILD_HEADERS} ${BUILD_SOURCES})
QT5_USE_MODULES(qaudiocoder Core Multimedia)
SET_TARGET_PROPERTIES(qaudiocoder PROPERTIES LINKER_LANGUAGE CXX)
SET_TARGET_PROPERTIES(qaudiocoder PROPERTIES VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
SET_TARGET_PROPERTIES(qaudiocoder PROPERTIES SOVERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

#############################################################################
# Install library and header
#############################################################################

INSTALL(TARGETS qaudiocoder DESTINATION ${INSTALL_LIB_DIR})
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	INSTALL(FILES ${ROOT}/cmake/QAudioCoderConfig.cmake DESTINATION ${INSTALL_LIB_DIR})
ENDIF()
INSTALL(FILES ${INSTALL_HEADER_FILES} DESTINATION ${INSTALL_INCLUDE_DIR})

#############################################################################
# Examples
#############################################################################

IF(${Qt5Widgets_FOUND} AND ${Qt5Gui_FOUND})
	ADD_EXECUTABLE(play ${EXAMPLES}/play.cpp)
	TARGET_LINK_LIBRARIES(play qaudiocoder)
	QT5_USE_MODULES(play Widgets Gui)

	ADD_EXECUTABLE(record ${EXAMPLES}/record.cpp)
	TARGET_LINK_LIBRARIES(record qaudiocoder)
	QT5_USE_MODULES(record Widgets Gui)

	ADD_EXECUTABLE(convert ${EXAMPLES}/convert.cpp)
	TARGET_LINK_LIBRARIES(convert qaudiocoder)
	QT5_USE_MODULES(convert Widgets Gui)
ENDIF()

#############################################################################
# Packaging
#############################################################################

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	INCLUDE(Packaging)
ENDIF()
