#!/bin/tcsh
#

setenv OMP_NUM_THREADS 4
limit coredumpsize unlimited

./xdevs.exec
