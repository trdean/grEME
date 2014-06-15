# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND eme_sources
    source_code_ss_impl.cc
    interleave_ii_impl.cc
    graycode_ii_impl.cc
    fsk_modulate_if_impl.cc
    add_sync_ii_impl.cc
    deinterleave_ii_impl.cc
    ungraycode_ii_impl.cc
    packet_no_rs_source_impl.cc
    packet_rs_source_impl.cc
    )

add_library(gnuradio-eme SHARED ${eme_sources})
target_link_libraries(gnuradio-eme ${Boost_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES})
set_target_properties(gnuradio-eme PROPERTIES DEFINE_SYMBOL "gnuradio_eme_EXPORTS")

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-eme
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_eme_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_eme.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_eme.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_ungraycode_ii.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_deinterleave_ii.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_add_sync_ii.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_fsk_modulate_if.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_graycode_ii.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_interleave_ii.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_source_code_ss.cc
)

add_executable(test-eme ${test_eme_sources})

target_link_libraries(
  test-eme
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-eme
)

GR_ADD_TEST(test_eme test-eme)
