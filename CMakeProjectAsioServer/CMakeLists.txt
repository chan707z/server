# CMakeList.txt: CMakeProjectAsioServer에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#
cmake_minimum_required (VERSION 3.8)

# 프로젝트 이름 및 버전
PROJECT ( "CMakeProjectAsioServer" )
SET ( PROJECT_VERSION_MAJOR 0 )
SET ( PROJECT_VERSION_MINOR 1 )

# 빌드 형상(Configuration) 및 Makefile 생성 여부
SET ( CMAKE_VERBOSE_MAKEFILE true )

# 빌드 대상 바이너리 파일명 및 소스 파일 목록
SET ( dir ${CMAKE_CURRENT_SOURCE_DIR}/../Bin/)

include_directories(${PROJECT_SOURCE_DIR})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

SET (Boost_ROOT ${PROJECT_SOURCE_DIR}/../Lib/boost_1_80_0/)
SET (Boost_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/../Lib/boost_1_80_0/stage/lib)
SET (Boost_INCLUDE_DIR ${Boost_ROOT})

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})


# 공통 링크 라이브러리 디렉토리 (-L)
IF(CMAKE_BUILD_TYPE MATCHES Debug)
	ADD_DEFINITIONS( -D_DEBUG=1 )
	SET ( OUTPUT_ELF "${CMAKE_PROJECT_NAME}_d.out" )

# 공통 링크 라이브러리 (-l)
	#LINK_LIBRARIES( ${PROJECT_SOURCE_DIR}/../Lib64/Debug/libboost_system.lib )

ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
	ADD_DEFINITIONS( -DNDEBUG=1 )
	SET ( OUTPUT_ELF "${CMAKE_PROJECT_NAME}.out" )

	# 공통 링크 라이브러리 (-l)
	#LINK_LIBRARIES( ${PROJECT_SOURCE_DIR}/../Lib64/Release/libboost_system.lib )

ENDIF()

# 출력 디렉토리
SET ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir} )

# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_executable (${CMAKE_PROJECT_NAME} "CMakeProjectAsioServer.cpp" "CMakeProjectAsioServer.h" "AsioServer.h" "AsioServer.cpp" "AsioSection.h" "AsioSection.cpp" "AsioSectionManager.h" "AsioSectionManager.cpp" "TestWorker.cpp" "TestWorker.h" "UserBase.h" "UserBase.cpp" "PoolBuffer.h" "PoolBuffer.cpp"   "ThreadManager.h" "ThreadManager.cpp"   "Buffer.h" "Buffer.cpp"   "Protocol.h" "BaseSection.h" "BaseSection.cpp" "ProtocolEnum.h" "ErrorCode.h" "User.h" "User.cpp" "UserManager.h" "UserManager.cpp" "Singleton.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()