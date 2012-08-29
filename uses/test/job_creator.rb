def content(method, calc_name)
<<HERE
#PBS -l walltime=200:0:0,nodes=1:ppn=1
#PBS -N #{method}-#{calc_name}

#!/bin/bash
cd /home/newmen/monte_carlo_techs/uses/test
./run.sh #{method} #{calc_name}
HERE
end

method = ARGV[0]
calc_name = ARGV[1]
unless method && calc_name
  puts "need pass method name and calculation name"
  exit
end

File.open('run.job', 'w') do |f|
  f.write(content(method, calc_name))
end
