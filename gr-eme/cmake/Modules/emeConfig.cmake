INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_EME eme)

FIND_PATH(
    EME_INCLUDE_DIRS
    NAMES eme/api.h
    HINTS $ENV{EME_DIR}/include
        ${PC_EME_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREEFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    EME_LIBRARIES
    NAMES gnuradio-eme
    HINTS $ENV{EME_DIR}/lib
        ${PC_EME_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(EME DEFAULT_MSG EME_LIBRARIES EME_INCLUDE_DIRS)
MARK_AS_ADVANCED(EME_LIBRARIES EME_INCLUDE_DIRS)

