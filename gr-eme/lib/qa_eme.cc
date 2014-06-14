/*
 * Copyright 2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/*
 * This class gathers together all the test cases for the gr-filter
 * directory into a single test suite.  As you create new test cases,
 * add them here.
 */

#include "qa_eme.h"
#include "qa_source_code_ss.h"
#include "qa_interleave_ii.h"
#include "qa_graycode_ii.h"
#include "qa_fsk_modulate_if.h"
#include "qa_add_sync_ii.h"

CppUnit::TestSuite *
qa_eme::suite()
{
  CppUnit::TestSuite *s = new CppUnit::TestSuite("eme");
  s->addTest(gr::eme::qa_source_code_ss::suite());
  s->addTest(gr::eme::qa_interleave_ii::suite());
  s->addTest(gr::eme::qa_graycode_ii::suite());
  s->addTest(gr::eme::qa_fsk_modulate_if::suite());
  s->addTest(gr::eme::qa_add_sync_ii::suite());

  return s;
}
