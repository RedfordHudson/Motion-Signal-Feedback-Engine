# SPDX-License-Identifier: MIT
#
# SPDX-FileCopyrightText: Copyright (c) 2019-2023 Lars Melchior and contributors

# set(CPM_DOWNLOAD_VERSION 1.0.0-development-version)
set(CPM_DOWNLOAD_VERSION 0.40.8)

set(CPM_HASH_SUM "CPM_HASH_SUM_PLACEHOLDER")

set(CPM_DOWNLOAD_LOCATION "${LIB_DR}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

# Expand relative path. This is important if the provided path contains a tilde (~)
get_filename_component(CPM_DOWNLOAD_LOCATION ${CPM_DOWNLOAD_LOCATION} ABSOLUTE)

# variable_watch(DOWNLOAD_URL)

set(DOWNLOAD_URL https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake)
# message("DOWNLOAD_URL: ${DOWNLOAD_URL}")
 
#[[

file(DOWNLOAD 
    DOWNLOAD_URL 
    ${CPM_DOWNLOAD_LOCATION} EXPECTED_HASH SHA256=${CPM_HASH_SUM}
)

error:

CMake Error at cmake/cpm.cmake:20 (file):
[cmake]   file DOWNLOAD cannot compute hash on failed download
[cmake] 
[cmake]     status: [6;"Could not resolve hostname"]

solution:

downloaded manually

# ]]
# message("CPM_DOWNLOAD_LOCATION: ${CPM_DOWNLOAD_LOCATION}")
include(${CPM_DOWNLOAD_LOCATION})