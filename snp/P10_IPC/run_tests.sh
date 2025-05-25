#!/bin/bash
# Run this script in WSL to execute tests

# Change to P10_IPC directory 
cd /mnt/c/Users/sheng/git_repos/miscellaneous-temporary-repo/snp/P10_IPC

# Explicitly set paths
export SNP_TESTLIB="/mnt/c/Users/sheng/git_repos/miscellaneous-temporary-repo/snp/testlib"
export SNP_DOXYFILE="/mnt/c/Users/sheng/git_repos/miscellaneous-temporary-repo/snp/Doxyfile"
export SNP_SHARED_MAKEFILE="/mnt/c/Users/sheng/git_repos/miscellaneous-temporary-repo/snp/shared.mk"

# Create tests directory if it doesn't exist
mkdir -p tests

# Run make test
make test

exit $?
