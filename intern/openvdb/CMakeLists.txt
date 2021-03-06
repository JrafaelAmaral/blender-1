# ***** BEGIN GPL LICENSE BLOCK *****
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# The Original Code is Copyright (C) 2015, Blender Foundation
# All rights reserved.
# ***** END GPL LICENSE BLOCK *****

set(INC
  .
  intern
)

set(INC_SYS
)

set(SRC
  openvdb_capi.h
)

set(LIB
)

if(WITH_OPENVDB)
  add_definitions(
    -DWITH_OPENVDB
    ${OPENVDB_DEFINITIONS}
  )

  if(WITH_OPENVDB_3_ABI_COMPATIBLE)
    add_definitions(
      -DOPENVDB_3_ABI_COMPATIBLE
    )
  endif()

  list(APPEND INC_SYS
    ${BOOST_INCLUDE_DIR}
    ${TBB_INCLUDE_DIRS}
    ${OPENEXR_INCLUDE_DIRS}
    ${OPENVDB_INCLUDE_DIRS}
  )

  list(APPEND SRC
    intern/openvdb_dense_convert.cc
    intern/openvdb_reader.cc
    intern/openvdb_writer.cc
    openvdb_capi.cc
    openvdb_util.cc

    intern/openvdb_dense_convert.h
    intern/openvdb_reader.h
    intern/openvdb_writer.h
    openvdb_util.h
  )

  if(WITH_OPENVDB_BLOSC)
    add_definitions(
      -DWITH_OPENVDB_BLOSC
    )
  endif()
endif()

blender_add_lib(bf_intern_openvdb "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
