# Copyright (C) 2024-2026 landerrosette <57791410+landerrosette@users.noreply.github.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.21)
project(algs4)

add_library(algs4 INTERFACE)
target_include_directories(algs4 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(algs4 INTERFACE cxx_std_20)

option(ALGS4_BUILD_CLIENTS "Build clients" ${PROJECT_IS_TOP_LEVEL}) # Do not build clients when included as a subproject
if (ALGS4_BUILD_CLIENTS)
    add_subdirectory(clients)
endif ()
