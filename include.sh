#!/usr/bin/env bash
set -e

AC_ADD_SCRIPT("${CMAKE_CURRENT_SOURCE_DIR}/src")

AC_ADD_CONFIGURATION_FILE("${CMAKE_CURRENT_SOURCE_DIR}/conf/my_custom.conf.dist")
