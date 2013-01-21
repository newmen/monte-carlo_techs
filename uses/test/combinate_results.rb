require 'docopt'
require 'fileutils'

class Combain
  def initialize(bins_dir, results_dir, out_name)
    @bins_dir, @results_dir, @out_name = bins_dir, results_dir, out_name
  end

  def create_out_if_not_exist
    unless File.directory?(@out_name)
      print "Makes #@out_name directory..."
      FileUtils.mkdir(@out_name)
      puts " complete"
    end
  end

  def copy_curve_files
    each_file_into_dirs(curve_dirs) do |filename_with_path, inner_filename|
      FileUtils.cp(filename_with_path, "#@out_name/#{inner_filename}")
    end
  end

  def write_measure_files
    combinated_maps.each do |filename, file_map|
      names = all_names(file_map).sort
      all_values = []
      file_map.each do |size, size_map|
        all_values << [size]
        current_values = all_values.last
        names.each do |name|
          value = size_map[name]
          current_values << (value ? value : '0')
        end
      end
      all_values.sort! { |a, b| a.first.to_i <=> b.first.to_i }

      File.open("#@out_name/#{filename}", 'w') do |f|
        f.write(names.unshift('#').join("\t") + "\n")
        all_values.each do |values|
          f.write(values.join("\t") + "\n")
        end
      end
    end
  end

private

  def method_names
    bd = "bin/#@bins_dir"
    check_directory_exist(bd)
    Dir["#{bd}/*"].map { |file| File.basename(file) }
  end

  def result_dirs
    methods = method_names
    check_directory_exist(@results_dir)
    Dir["#@results_dir/*"].select do |name|
      File.directory?(name) &&
        methods.inject(false) { |acc, method| acc || File.basename(name) =~ /\A#{method}/ } # foldl Haskell style :)
    end
  end

  def curve_dirs
    result_dirs.select do |name|
      name.split('-').last.to_i == 0
    end
  end

  def measure_dirs
    result_dirs - curve_dirs
  end

  def each_file_into_dirs(dirs)
    dirs.each do |current_dir|
      Dir[current_dir + '/*'].each do |filename_with_path|
        yield(filename_with_path, File.basename(filename_with_path))
      end
    end
  end

  def combinated_maps
    total_map = {}
    each_file_into_dirs(measure_dirs) do |filename_with_path, inner_filename|
      total_map[inner_filename] ||= {}
      file_map = total_map[inner_filename]
      File.open(filename_with_path) do |f|
        lines = f.readlines
        names = lines.shift.split("\t").map { |n| n.strip }
        names.shift

        lines.each do |line|
          values = line.split("\t").map { |v| v.strip }
          size = values.shift
          file_map[size] ||= {}
          size_map = file_map[size]
          values.each_index do |i|
            size_map[names[i]] = values[i]
          end
        end
      end
    end
    total_map
  end

  def all_names(file_map)
    names = []
    file_map.each do |_, size_map|
      size_map.each do |name, _|
        names << name unless names.include?(name)
      end
    end
    names
  end

  def check_directory_exist(dir)
    raise "No such #{dir} directory" unless File.directory?(dir)
  end
end

def main
  doc = <<HELPDOC
Usage:
  #{__FILE__} -b BINS_DIR -d RESULTS_DIR -o NAME

Options:
  -h, --help                         Show this
  -b BINS_DIR, --bin=BINS_DIR        Directory with binaries
  -d RESULTS_DIR, --dir=RESULTS_DIR  Directory with results
  -o NAME, --out=NAME                Name of output directory
HELPDOC

  begin
    options = Docopt::docopt(doc)
    if (bins_dir = options['--bin']) && (results_dir = options['--dir']) && (out_name = options['--out'])
      c = Combain.new(bins_dir, results_dir, out_name)
      c.create_out_if_not_exist
      c.copy_curve_files
      c.write_measure_files
    else
      puts "Wrong run!"
      puts doc
    end
  rescue Docopt::Exit => e
    puts e.message
  end
end

main

