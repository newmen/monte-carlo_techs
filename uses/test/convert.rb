require 'docopt'

class Converter
  def initialize(docopts)
    @animation_name = docopts['--name']
    @format = docopts['--format']
    @is_movie = (@format != 'gif')
    @rate = docopts['--hund-second'] || (!@is_movie && 100)
    @geometry = docopts['--resize']
  end

  def convert(dir)
    Dir.chdir(dir)
    Dir['*.png'].each do |file_name|
      numbers = file_name.split('.')
      seconds_str = numbers[0].rjust(5, '0')
      micro_seconds_str = numbers[1] =~ /^\d+$/ ? numbers[1] : '0'
      micro_seconds_str = micro_seconds_str.ljust(4, '0')
      
      zerofiled_name = seconds_str
      zerofiled_name << '.' unless is_movie
      zerofiled_name << micro_seconds_str
      short_name = zerofiled_name[0..10]

      convert_file(file_name, short_name)
    end

    create_animation
  end

private

  attr_reader :animation_name, :format, :is_movie, :rate, :geometry

  def mp4_origin_files_ext
    'png'
  end

  def convert_file(from, to)
    if is_movie
      from_to_str = "#{from} #{to}.#{mp4_origin_files_ext}"
      # if geometry
      #   `convert -resize #{geometry} #{from_to_str}`
      #   `rm #{from}`
      # else
        `mv #{from_to_str}`
      # end
    else
      command = "convert -colors 4"
      command << " -resize #{geometry}" if geometry
      command << " #{from} #{to}.#{format}"
      `#{command}`
      # `rm #{from}`
    end
  end

  def create_animation
    `#{is_movie ? create_mp4_command : create_gif_command}`
  end

  def create_gif_command
    "convert -delay #{rate} -loop 0 *.#{format} #{out_name}.#{format}"
  end

  def create_mp4_command
    command = %(ffmpeg -f image2 -i "%09d.#{mp4_origin_files_ext}")
    command << " -r #{rate}" if rate
    command << " -s #{geometry}" if geometry
    command << " #{out_name}.#{format}"
    command
  end

  def result_dir
    '..'
  end

  def out_name
    "#{result_dir}/#{animation_name}"
  end
end

def main
  doc = <<DOC
Usage:
  #{__FILE__} [options]

Options:
  -h, --help                      This help
  -d, --dir=DIR                   Setup current dir
  -s, --hund-second=HUND_SECONDS  Hundredths of a second
  -n, --name=NAME                 Name of result animation file [default: animation]
  -f, --format=EXT                Format of output files (gif|mp4) [default: gif]
  -r, --resize=GEOMETRY           Resize to geometry
DOC

  begin
    options = Docopt::docopt(doc)

    dir = options['--dir']
    if dir
      Converter.new(options).convert(dir)
    else
      puts 'Need to specify the directory'
      puts doc
    end
  rescue Docopt::Exit => e
    puts e.message
  end
end

main
