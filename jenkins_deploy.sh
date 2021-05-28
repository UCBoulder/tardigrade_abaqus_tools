#!/usr/bin/env bash

set -x
# Override default permissions. Set group to rx with no write permissions.
umask 0022

date
script=`basename "$0"`
echo "Running ${script}"

# Parse branch basename from expected path-like name, e.g. origin/branch.
branch=$(basename ${GIT_BRANCH})

# Deploy master branch against release environment. All other branches against beta.
if [ ${branch} == master ]; then
    environment='release'
    env_alias='sv3r'
    master=true
elif [ ${branch} == dev ]; then
    environment='beta'
    env_alias='sv3b'
    master=false
else
    echo "Unexpected branch name. Exiting..."
    exit 1
fi

# Activate W-13 Python environment
case $(hostname) in
    sstelmo.lanl.gov|mayhem.lanl.gov)
        projects="/projects"
        module load python/2020.07-python-3.8
        ${env_alias}
        ;;  # No fall through
    sn-fey?.lanl.gov|sn-rfe?.lanl.gov|sn???.lanl.gov)
        projects="/usr/projects/ea"
        module load python/3.8-anaconda-2020.07
        source activate /usr/projects/ea/python/${environment}
        module load intel
        ;;
    *)
        echo "Unknown or unsupported host $(hostname)."
        exit 2
esac

# Can treat bash like a scripting language after conda activation
set -Eeuxo pipefail

# For master branch, update tags before building documentation and whl
if ${master}; then
    echo "master branch deployment is not yet configured"
    exit 3
# TODO: setup version tag updates for master branch
# TODO: setup common code for determining version number per branch
fi

# Build project
./BUILD.sh

# Install project into conda environment by expected whl name.
./INSTALL.sh

# TODO: deploy documentation
