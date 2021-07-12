# Test dev branch against beta environment. All other branches against release
environment='release'
env_alias='sv3r'
if [[ ${CI_MERGE_REQUEST_TARGET_BRANCH_NAME} == dev ]] || [[ ${CI_COMMIT_BRANCH} == dev ]]; then
    environment='beta'
    env_alias='sv3b'
# Deploy master branch against release environment. All other branches against beta.
elif [[ ${CI_COMMIT_BRANCH} == master ]]; then
    environment='release'
    env_alias='sv3r'
fi

# Activate W-13 Python environment
case $(hostname) in
    sstelmo.lanl.gov|mayhem.lanl.gov)
        projects="/projects"
        module load python/2020.07-python-3.8
        ${env_alias}
        export PATH=$PATH:/apps/abaqus/Commands/
        ;;  # No fall through
    sn-fey?.lanl.gov|sn-rfe?.lanl.gov|sn???.lanl.gov)
        module load python/3.8-anaconda-2020.07
        source activate /usr/projects/ea/python/${environment}
        export PATH=$PATH:/usr/projects/ea/abaqus/Commands/
        ;;
    *)
        echo "Unknown or unsupported host $(hostname)."
esac
