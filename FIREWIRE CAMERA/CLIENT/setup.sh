# setup environment for firewire tests

export EPICS_CA_MAX_ARRAY_BYTES=4000000
export HOST_ARCH=linux-x86
#export EPICS_BASE=/prod/epics3.14.1/base-3.14.1/
export EPICS_BASE=~dach/EPICS3.14.7/base-3.14.7/
#export EPICS_BASE=~/tmp/PROJECTS/subsystems/TEST/SMH/redhat/BUILD/base-3.14.4
export PATH=../src:$PATH
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
