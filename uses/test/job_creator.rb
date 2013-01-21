def content(method, calc_name)
<<PBSTASK
#PBS -l walltime=555:0:0,nodes=1:ppn=1
#PBS -N #{method}-#{calc_name}

#!/bin/bash
cd /home/newmen/monte_carlo_techs/uses/test
./run.sh #{ARGV.join(' ')}
PBSTASK
end

unless ARGV.size == 5
  puts "need pass: bin_dir method_name results_dir calculation_name size_or_repeats"
  exit
end

File.open('run.job', 'w') do |f|
  f.write(content(ARGV[1], ARGV[3]))
end
