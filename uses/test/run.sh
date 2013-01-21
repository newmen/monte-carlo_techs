#!/bin/sh

min_size=150
max_size=150
size_step=25
repeats=3

name=$1
if [ "$name" == "" ]; then
    echo "run: $0 NAME_OF_CALC"
    exit
fi

test_mc_dir=`pwd`
test_mc_bin=${test_mc_dir}/test_mc
plots_script=${test_mc_dir}/plots.rb
results_dir=${test_mc_dir}/results/${name}

if [ -x ${results_dir} ]; then
    echo "Clearing ${results_dir} dir..."
    rm -f ${results_dir}/*
else
    mkdir -p ${results_dir}
    echo "${results_dir} dir was created"
fi

echo "Executing calculations..."

${test_mc_bin} ${results_dir} ${max_size} ${max_size} 1 true

#for i in `seq ${min_size} ${size_step} ${max_size}`; do
#    ${test_mc_bin} ${results_dir} ${i} ${i} ${repeats}
#done

ruby ${plots_script} -d ${results_dir}
