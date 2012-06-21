#!/bin/sh

test_mc_dir='/home/newmen/c++/Qt/qt_mc/test'
result_dir=${test_mc_dir}/results

${test_mc_dir}/test_mc ${result_dir} 200 200 1 true

${test_mc_dir}/test_mc ${result_dir} 20 20 10
${test_mc_dir}/test_mc ${result_dir} 40 40 10
${test_mc_dir}/test_mc ${result_dir} 60 60 10
${test_mc_dir}/test_mc ${result_dir} 80 80 10
${test_mc_dir}/test_mc ${result_dir} 100 100 10
${test_mc_dir}/test_mc ${result_dir} 120 120 10
${test_mc_dir}/test_mc ${result_dir} 140 140 10
${test_mc_dir}/test_mc ${result_dir} 160 160 10
${test_mc_dir}/test_mc ${result_dir} 180 180 10
${test_mc_dir}/test_mc ${result_dir} 200 200 10
