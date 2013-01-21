#!/bin/sh

if [ ! $# == 5 ]; then
    echo "run: $0  BIN_DIR  NAME  RESULTS_DIR  CALC  SIZE_OR_REPEATS"
    exit
fi

bin_dir=$1
name=$2
base_results_dir=$3
calc=$4
size_or_repeats=$5

test_mc_dir=`pwd`
test_mc_bin=${test_mc_dir}/${bin_dir}/${name}
plots_script=${test_mc_dir}/plots.rb
results_dir=/tmp/${base_results_dir}/${name}
#results_dir=${test_mc_dir}/${base_results_dir}/${name}-${calc}

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
    ${test_mc_bin} ${results_dir} ${size_or_repeats} ${size_or_repeats} 1 true
fi

if [ "$calc" != "crv" ]; then
    ${test_mc_bin} ${results_dir} ${calc} ${calc} ${size_or_repeats}
fi

home_results=${test_mc_dir}/${base_results_dir}
mkdir -p ${home_results}
mv ${results_dir} ${home_results}/

#ruby ${plots_script} -d ${results_dir}
