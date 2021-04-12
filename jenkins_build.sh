#!/usr/bin/env bash

# Identify W-13 specific common paths automatically
case $OSTYPE in
    darwin*)
        apps="/Users/apps"
        projects="/Users/projects"
        ;;
    linux-gnu*)
        apps="/apps"
        projects="/projects"
        ;;
    *)
        echo "Detected OS $OSTYPE is not supported. Exiting."
        exit 1
        ;;
esac

# Activate conda environment
rel='release'
if [ -f "${apps}/anaconda/2019.10-python-3.7/etc/profile.d/conda.sh" ]; then
    . "${apps}/anaconda/2019.10-python-3.7/etc/profile.d/conda.sh"
    conda activate
    conda activate "${projects}/python/${rel}"
else
    export PATH="${apps}/anaconda/5.0.1-python-3.6/bin:$PATH"
    source activate
    source activate "${projects}/python/${rel}"
fi

# Make bash script more like high-level languages.
set -Eeuxo pipefail

# report conda environment
conda info

# Debugging
whoami
groups
ls -l $HOME/include || true
ls -l $HOME/.local/include || true

# Source common shell script variables
workdir=${PWD}

#================================================= TEST AGAINST g++ or c++ COMPILER ===
case $OSTYPE in
    darwin*)
        compiler='c++'
        ;;
    linux-gnu*)
        compiler='g++'
        ;;
esac
./new_build.sh ${compiler}

# Perform repo tests
cd "build"
ctest --verbose --output-log results.tex

# Append the path of the compiler
echo "$(command -v ${compiler})" >> results.tex
echo -e "$(${compiler} --version)" >> results.tex
# Rename results according to compiler
mv results.tex "${compiler}_results.tex"

# Return to working directory
cd ${workdir}
cp "build/${compiler}_results.tex" .

#============================================================= CHECK RESULTS ===
# Check for failed tests
cd ${workdir}
result_files=(`find . -maxdepth 1 -name "*_results.tex"`)
echo "Result files: ${result_files[@]}"
echo "Number of results files found: ${#result_files[@]}"

# Check number of results files to check find globbing
# TODO: fix the expected compiler count by OSTYPE or HOSTNAME
if [ ${#result_files[@]} -lt 1 ]; then
    echo "Found the wrong number of result files: ${#result_files[@]}"
    echo "result files found: ${result_files[@]}"
    exit 2
fi
