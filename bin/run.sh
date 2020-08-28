#!/bin/tcsh
#

export OMP_NUM_THREADS=4
limit coredumpsize unlimited

./xdev.exec
