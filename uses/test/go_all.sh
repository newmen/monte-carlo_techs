#!/bin/sh

min_size=20
max_size=100
step_size=20

for f in bin/sep/*; do
    ruby job_creator.rb `basename $f` crv
    qsub run.job

    for i in `seq ${min_size} ${step_size} ${max_size}`; do
        ruby job_creator.rb `basename $f` $i
        qsub run.job
    done
done
