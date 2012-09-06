#!/bin/sh

bin_dir='bin/406'
results_dir='406r'

min_size=20
max_size=100
step_size=20
repeats=2

run_qsub() {
    ruby job_creator.rb ${bin_dir} $1 ${results_dir} $2 $3
    qsub run.job
}

for f in ${bin_dir}/*; do
    curr_name=`basename $f`

    run_qsub ${curr_name} crv ${max_size}

    for i in `seq ${min_size} ${step_size} ${max_size}`; do
        run_qsub ${curr_name} ${i} ${repeats}
    done
done
