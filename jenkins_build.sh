#!/usr/bin/env bash

set -x

# Test dev branch against beta environment. All other branches against release
environment='release'
env_alias='sv3r'
if [ ${targetBranch} == dev ]; then
    environment='beta'
    env_alias='sv3b'
fi

# Activate W-13 Python environment
case $(hostname) in
    sstelmo.lanl.gov|mayhem.lanl.gov)
        module load python/2020.07-python-3.8
        ${env_alias}
        export PATH=$PATH:/apps/abaqus/Commands/
        ;;  # No fall through
    sn-fey?.lanl.gov|sn-rfe?.lanl.gov|sn???.lanl.gov)
        module load python/3.8-anaconda-2020.07
        source activate /usr/projects/ea/python/${environment}
        export PATH=$PATH:/usr/projects/ea/abaqus/Commands/
        ;;
esac

# Make bash script more like high-level languages.
set -Eeuxo pipefail

# report conda environment
conda info

# Clean and build project
./BUILD.sh

# Run project tests
./TEST.sh
