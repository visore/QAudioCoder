# Find the native QAudioCoder includes and library
#
# This module defines
#  QAUDIOCODER_INCLUDE_DIR: QAudioCoder headers
#  QAUDIOCODER_LIBRARY: QAudioCoder library
#  QAUDIOCODER_FOUND: If QAudioCoder was found or not

#=============================================================================
# Copyright 2011-2012 Christoph Stallmann
#
# University of Pretoria
# Department of Computer Science
#
# Distributed under the GNU Lesser General Public License Version 3 (LGPLv3)
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#=============================================================================

FIND_PACKAGE(Qt COMPONENTS Core REQUIRED)

IF(QT_QTCORE_FOUND)

	GET_FILENAME_COMPONENT(THIS "${CMAKE_CURRENT_LIST_FILE}" PATH)
	FIND_PATH(QAUDIOCODER_INCLUDE_DIR qaudiocoder.h /usr/include/qaudiocoder)

	SET(QAUDIOCODER_NAMES ${QAUDIOCODER_NAMES} qaudiocoder libqaudiocoder)
	FIND_LIBRARY(QAUDIOCODER_LIBRARY NAMES ${QAUDIOCODER_NAMES} PATHS ${THIS})

	IF(QAUDIOCODER_LIBRARY AND QAUDIOCODER_INCLUDE_DIR)
		SET(QAUDIOCODER_FOUND "TRUE")
	ENDIF(QAUDIOCODER_LIBRARY AND QAUDIOCODER_INCLUDE_DIR)

ENDIF(QT_QTCORE_FOUND)
