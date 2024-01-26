#!/bin/bash
export LD_LIBRARY_PATH=/root/SLS-VIDEO/base-3.14.7/lib/linux-x86:$LD_LIBRARY_PATH
#export LD_LIBRARY_PATH=/usr/local/epics3.14.6/base-3.14.6/lib/linux-x86:$LD_LIBRARY_PATH
export EPICS_CA_MAX_ARRAY_BYTES=4000000
firewire $1

