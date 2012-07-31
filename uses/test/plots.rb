# coding: utf-8

require 'docopt'
require 'gnuplot'

EXT_MC = 'mcr'
EXT_PERF = 'prf'

def make_gnuplot(file_name, title, xlabel, ylabel, &block)
  Gnuplot.open do |gp|
    Gnuplot::Plot.new(gp) do |plot|
      
      plot.output("#{file_name}.png")
      plot.terminal('png truecolor')
#      plot.size("5,3")

      plot.title(title)
      plot.xlabel(xlabel)
      plot.ylabel(ylabel)

      block.call(plot)
    end
  end
end

def make_mc_time_gnuplot(file_name, title, &block)
  make_gnuplot(file_name, title, 'Время (сек)', 'Концентрация (%)') do |plot|
#    plot.xrange('[0:50]')
    
    block.call(plot)
  end
end

def make_mc_concentrations_gnuplot(file_name, title, a_title, b_title, &block)
  make_gnuplot(file_name, title, "Концентрация #{a_title} [%]", "Концентрация #{b_title} [%]") do |plot|
    block.call(plot)
  end
end

def make_perf_gnuplot(file_name, title, ylabel, &block)
  make_gnuplot(file_name, title, 'Размер поля (кол-во ячеек)', ylabel) do |plot|
    block.call(plot)
  end
end

def make_mc_time_data(data, ds_with, &block)
  data[1].map do |name, arr_y|
    Gnuplot::DataSet.new([data[0], arr_y]) do |ds|
      ds.with = ds_with

      block.call(name, ds)
    end
  end
end

def make_mc_concentrations_data(a_data, b_data, ds_with, &block)
  Gnuplot::DataSet.new([a_data, b_data]) do |ds|
    ds.with = ds_with
    block.call(ds)
  end
end

def configure_original(ds, name)
  ds.linewidth = 2
  ds.title = "Original #{name}"
end

def original_time_data(original)
  make_mc_time_data(original, 'lines') do |name, ds|
    configure_original(ds, name)
  end
end

def original_concentrations_data(a_data, b_data)
  make_mc_concentrations_data(a_data, b_data, 'lines') do |ds|
    configure_original(ds, 'time')
  end
end

def mc_concentrations_data(a_data, b_data)
  make_mc_concentrations_data(a_data, b_data, 'linespoints') do |ds|
    ds.title = "MC time"
  end
end

def draw_original_time(original)
  make_mc_time_gnuplot('original', 'ОДУ') do |plot|
    plot.data = original_time_data(original)
  end
end

def draw_concentrations_graphs(filename, original, mc)
  original_data = original[1].to_a.combination(2).to_a if original
  mc_data = mc[1].to_a.combination(2).to_a if mc

  name = mc ? mc[2] : original[2]
  current_data = original ? original_data : mc_data
  current_data.each_with_index do |data, i|
    a_data, b_data = data
    mc_a_data, mc_b_data = mc_data[i] if original && mc
    a, b = a_data[0], b_data[0]
    make_mc_concentrations_gnuplot("#{filename}_#{a}_#{b}", "#{name} #{a}/#{b}", a, b) do |plot|
      org_data = []
      if original
        org_data << original_concentrations_data(a_data[1], b_data[1])
        org_data << mc_concentrations_data(mc_a_data[1], mc_b_data[1]) if mc
      else
        org_data << mc_concentrations_data(a_data[1], b_data[1])
      end
      plot.data = org_data
    end
  end
end

def draw_mc_time_graph(original, mc, file_name)
  make_mc_time_gnuplot(file_name, mc[2]) do |plot|
    org_data = []
    org_data += original_time_data(original) if original
    plot.data = org_data + make_mc_time_data(mc, 'linespoints') do |name, ds|
      ds.title = "MC #{name}"
    end
  end
end

def draw_perf_graph(arr_x, arrs_y, name)
  title, ylabel = '', ''
  case name
  when 'times', 'faster'
    title = 'Сравнение времён расчёта'
    ylabel = 'Время расчёта (сек)'
  when 'virtuals'
    title = 'Сравнение потребления памяти'
    ylabel = 'Использовалось памяти (байт)'
  when 'rss'
    title = 'Сравнение потребления памяти'
    ylabel = 'Всего выделено памяти (байт)'
  end

  make_perf_gnuplot(name, title, ylabel) do |plot|
    plot.data = arrs_y.map do |name, arr_y|
      Gnuplot::DataSet.new([arr_x, arr_y]) do |ds|
        ds.with = "linespoints"
        ds.linewidth = 2
        ds.title = name
      end
    end
  end

end

def read_mc_file(file_name)
  name = ''
  arr_x = []
  arrs_y = {}

  print "Reading #{file_name}..."
  File.open(file_name) do |f|
    f.readlines.each do |line|
      if line =~ /^#/
        line.chomp!
        name = line[2...line.length]
      else
        values = line.split("\t").map { |v| v.to_f }
        arr_x << values.shift

        if (arrs_y.empty?)
          ('A'..'Z').to_a[0...(values.size)].each do |char|
            arrs_y[char.to_sym] = []
          end
        end

        arrs_y.each do |_, arr|
          arr << values.shift
        end

      end
    end
  end

  puts " complete"

  [arr_x, arrs_y, name]
end

def read_and_draw_perf_file(file_name)
  arr_x = []
  arrs_y = {}

  print "Reading #{file_name}..."

  File.open(file_name) do |f|
    f.readlines.each do |line|
      line.chomp!
      next if line == ''

      if line =~ /^#/
        line.split(/\t/).each do |tech|
          next if tech == '#' || tech == ''
          arrs_y[tech] = []
        end
      else
        line = line.split(/\t/)
        size = line[0].to_i
        arr_x << size

        i = 1
        arrs_y.each do |k, v|
          v << line[i].to_f
          i += 1
        end
      end
    end
  end

  puts " complete"

  base_file_name = File.basename(file_name, ".#{EXT_PERF}")
  draw_perf_graph(arr_x, arrs_y, base_file_name)

  if base_file_name == 'times'
    faster_arrs_y = {}
    i = 0
    arrs_y.each do |k, v|
      if i > 3
        faster_arrs_y[k] = v
      end
      i += 1
    end

    draw_perf_graph(arr_x, faster_arrs_y, 'faster')
  end
end

def read_and_draw_mc_plots
  original_file = "original.#{EXT_MC}"
  if File.exist?(original_file) && File.size(original_file) > 0
    original = read_mc_file(original_file)
    draw_original_time(original)
    draw_concentrations_graphs('original', original, nil)
  else
    original = nil
  end

  mc_files = Dir["*.#{EXT_MC}"] - [original_file]
  mc_files.each do |file_name|
    mc = read_mc_file(file_name)
    base_filename = File.basename(file_name, ".#{EXT_MC}")
    draw_mc_time_graph(original, mc, base_filename)
    draw_concentrations_graphs(base_filename, original, mc)
  end
end

def read_and_draw_perf_plots
  Dir["*.#{EXT_PERF}"].each do |file_name|
    read_and_draw_perf_file(file_name)
  end
end

def draw_into_dir(result_dir, recursively = false)
  print "Entering into #{File.expand_path(result_dir)}..."
  Dir.chdir(result_dir)
  puts " complete"

  read_and_draw_mc_plots
  read_and_draw_perf_plots

  return unless recursively

  Dir['*/'].each do |dir|
    draw_into_dir(dir, true)
    Dir.chdir('..')
  end
end

def main
  doc = <<HEREHELP
Usage: ruby #{__FILE__} options
Options:
  -h, --help         Show this
  -d DIR, --dir=DIR  Directory with results
  -r, --recursively  Recursive searching a result files
HEREHELP

  options = Docopt(doc)
  result_dir = options[:dir]
  if result_dir
    draw_into_dir(result_dir, options[:recursively])
  else
    puts "Wrond run!"
    puts doc
  end
end

main
