#!/usr/bin/env bash

set -x
# Override default permissions. Set group to rx with no write permissions.
umask 0022

date
script=`basename "$0"`
echo "Running ${script}"

# Can treat bash like a scripting language after conda activation
set -Eeuxo pipefail

# For master branch, update tags before building documentation and whl
if [[ ${CI_COMMIT_BRANCH} == master ]]; then
    # Find cmake3 executable
    if [ -x "$(command -v cmake3)" ]; then
        cmake_exec=$(command -v cmake3)
    elif [ -x "$(command -v cmake)" ]; then
        cmake_exec=$(command -v cmake)
    else
        echo "Could not find cmake executable"
        exit 1
    fi
    # Build VERSION file from GetVersionFromGit.cmake without a full CMake configuration
    ${cmake_exec} -D PROJECT_NAME=abaqus_tools -D VERSION_UPDATE_FROM_GIT=True -P src/cmake/GetVersionFromGitTag.cmake
    # GetVersionFromGit.cmake bumps micro/patch version. Retrieve next release from VERSION
    production_version=$(cut -f 1 -d '*' VERSION)
    developer_version=${production_version}+dev
    # Tag production commit and previous developer commit. Continue if already tagged.
    git config user.name "${GITLAB_USER_NAME}"
    git config user.email "${GITLAB_USER_EMAIL}"
    git remote add oauth2-origin https://gitlab-ci-token:${GITLAB_ACCESS_TOKEN}@re-git.lanl.gov/${CI_PROJECT_PATH}.git
    git tag -a ${production_version} -m "production release ${production_version}" || true
    last_merge_hash=$(git log --pretty=format:"%H" --merges -n 2 | tail -n 1)  # Assume last merge was dev->master. Pick previous
    git tag -a ${developer_version} -m "developer release ${developer_version}" ${last_merge_hash} || true
    git push oauth2-origin --tags
elif [[ ! ${CI_COMMIT_BRANCH} == dev ]]; then
    echo "Only production branches, master and dev, are deployable"
    exit 2
fi

# Build project
./BUILD.sh

# Install project into conda environment by expected whl name.
./INSTALL.sh
