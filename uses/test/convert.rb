require 'docopt'

def convert(dir, hundredths_of_second, name_of_animation)
  Dir.chdir(dir)
  Dir['*.png'].each do |file_name|
    numbers = file_name.split('.')
    zerofiled_name = "#{numbers[0].rjust(4, '0')}.#{numbers[1]}"
    short_name = zerofiled_name[0..7]
    `convert -colors 4 #{file_name} #{short_name}.gif`
    # `rm #{file_name}`
  end

  `convert -delay #{hundredths_of_second} -loop 0 *.gif ../#{name_of_animation}.gif`
end

def main
  doc = <<DOC
Usage:
  #{__FILE__} [options]

Options:
  -h, --help                      This help
  -d, --dir=DIR                   Setup current dir [default: #{File.dirname(__FILE__)}]
  -s, --hund-second=HUND_SECONDS  Hundredths of a second [default: 100]
  -n, --name=NAME                 Name of result animation file
DOC

  options = Docopt::docopt(doc)
  convert(options['--dir'], options['--hund-second'], options['--name'])
end

main
