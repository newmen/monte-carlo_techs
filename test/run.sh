#!/bin/sh

min_size=1000
max_size=2000
size_step=1000
repeats=3

test_mc_dir=`pwd`
#test_mc_bin=${test_mc_dir}/test_mc
test_mc_bin=${test_mc_dir}/heap_test
plots_script=${test_mc_dir}/plots.rb
#results_dir=${test_mc_dir}/results
results_dir=${test_mc_dir}/ht_results

export HEAPCHECK=normal

if [ -x ${results_dir} ]; then
    echo "Clearing ${results_dir} dir..."
    rm -f ${results_dir}/*
else
    mkdir ${results_dir}
    echo "${results_dir} dir was created"
fi

echo "Executing calculations..."

#${test_mc_bin} ${results_dir} ${max_size} ${max_size} 1 true

for i in `seq ${min_size} ${size_step} ${max_size}`; do
    ${test_mc_bin} ${results_dir} ${i} ${i} ${repeats}
done

#ruby ${plots_script} ${results_dir}
