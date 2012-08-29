#!/bin/sh

if [ ! $# == 2 ]; then
    echo "run: $0 NAME CALC"
    exit
fi

#min_size=20
max_size=100
#size_step=20
repeats=2

name=$1
calc=$2

test_mc_dir=`pwd`
test_mc_bin=${test_mc_dir}/bin/sep/${name}
plots_script=${test_mc_dir}/plots.rb
#results_dir=/tmp/results/${name}
results_dir=${test_mc_dir}/results/${name}-${calc}

gcc_path=/share/home/tools/gcc-4.7.1
export LD_LIBRARY_PATH=${gcc_path}/lib:${gcc_path}/lib64

if [ -x ${results_dir} ]; then
    echo "Clearing ${results_dir} dir..."
    rm -f ${results_dir}/*
else
    mkdir -p ${results_dir}
    echo "${results_dir} dir was created"
fi

echo "Executing calculations..."

if [ "$calc" == "crv" ]; then
    ${test_mc_bin} ${results_dir} ${max_size} ${max_size} 1 true
fi

#for i in `seq ${min_size} ${size_step} ${max_size}`; do
#    ${test_mc_bin} ${results_dir} ${i} ${i} ${repeats}
#done
if [ "$calc" != "crv" ]; then
    ${test_mc_bin} ${results_dir} ${calc} ${calc} ${repeats}
fi

#home_results=${test_mc_dir}/results
#mkdir -p ${home_results}
#mv ${results_dir} ${home_results}/

#ruby ${plots_script} -d ${results_dir}
