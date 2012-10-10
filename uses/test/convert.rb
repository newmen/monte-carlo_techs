require 'docopt'

def convert(dir)
  Dir.chdir(dir)
  Dir['*.png'].each do |file_name|
    numbers = file_name.split('.')
    zerofiled_name = "#{numbers[0].rjust(4, '0')}.#{numbers[1]}"
    short_name = zerofiled_name[0..7]
    `convert -colors 4 #{file_name} #{short_name}.gif`
    # `rm #{file_name}`
  end

  `convert -delay 1 -loop 0 *.gif ../animation.gif`
end

def main
  doc = <<DOC
Usage:
  #{__FILE__} [options]

Options:
  -d, --dir=DIR     Setup current dir
DOC

  options = Docopt::docopt(doc)
  options['--dir'] ||= File.dirname(__FILE__)

  convert(options['--dir'])
end

main
