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
    plot.data = arrs_y.map do |c_name, arr_y|
      Gnuplot::DataSet.new([arr_x, arr_y]) do |ds|
        ds.with = "linespoints"
        ds.linewidth = 2
        ds.title = c_name
      end
    end
  end

end

def read_mc_file(file_name, names)
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

        if arrs_y.empty?
          (names + ('A'..'Z').to_a)[0...(values.size)].each do |char|
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

def read_perf_file(file_name)
  arr_x = []
  arrs_y = {}

  print "Reading #{file_name}..."

  File.open(file_name) do |f|
    f.readlines.each do |line|
      line.chomp!
      next if line == ''

      if line =~ /\A#/
        # если первая строка - заполняем названия, инитим кривые
        line.split(/\t/).each do |tech|
          next if tech == '#' || tech == ''
          arrs_y[tech] = []
        end
      else
        values = line.split(/\t/)
        size = values[0].to_i
        arr_x << size

        i = 1
        arrs_y.each do |k, v|
          v << values[i].to_f
          i += 1
        end
      end
    end
  end

  puts " complete"
  [arr_x, arrs_y]
end

def draw_perf_file(arr_x, arrs_y, base_file_name)
  draw_perf_graph(arr_x, arrs_y, base_file_name)

  if base_file_name == 'times'
    faster_arrs_y = {}
    arrs_y.each do |k, v|
      faster_arrs_y[k] = v if k =~ /\A(F|f)aster/
    end

    draw_perf_graph(arr_x, faster_arrs_y, 'faster-times')
  end
end

def read_and_draw_mc_plots(names)
  original_file = "original.#{EXT_MC}"
  if File.exist?(original_file) && File.size(original_file) > 0
    original = read_mc_file(original_file, names)
    draw_original_time(original)
    draw_concentrations_graphs('original', original, nil)
  else
    original = nil
  end

  mc_files = Dir["*.#{EXT_MC}"] - [original_file]
  mc_files.each do |file_name|
    mc = read_mc_file(file_name, names)
    base_file_name = File.basename(file_name, ".#{EXT_MC}")
    draw_mc_time_graph(original, mc, base_file_name)
    draw_concentrations_graphs(base_file_name, original, mc)
  end
end

def read_and_draw_perf_plots(time_coef, is_average_time)
  iterations_data = nil
  times_data = nil

  Dir["*.#{EXT_PERF}"].each do |file_name|
    data = read_perf_file(file_name)
    arr_x, arrs_y = data
    base_file_name = File.basename(file_name, ".#{EXT_PERF}")

    if is_average_time
      iterations_data = data if base_file_name == 'iterations'
      times_data = data if base_file_name == 'times'
    end

    unless is_average_time && base_file_name == 'times'
      draw_perf_file(arr_x, arrs_y, base_file_name)
    end
  end

  return unless iterations_data && times_data

  iter_arr_x, iter_arrs_y = iterations_data
  time_arr_x, time_arrs_y = times_data
  raise "Size values do not match" unless iter_arr_x == time_arr_x
  
  average_iters = []
  time_arrs_y.each do |name, values|
    values.each_index do |i|
      values[i] /= iter_arrs_y[name][i]
      average_iters[i] ||= []
      average_iters[i] << iter_arrs_y[name][i]
    end
  end

  average_iters.map! do |slice|
    sum = slice.inject(0) { |acc, x| acc + x }
    sum / slice.size
  end

  time_arrs_y.each do |name, values|
    values.each_index do |i|
      values[i] *= average_iters[i]
    end
  end

  draw_perf_file(time_arr_x, time_arrs_y, 'times')
end

def draw_into_dir(config)
  print "Entering into #{File.expand_path(config.result_dir)}..."
  Dir.chdir(config.result_dir)
  puts " complete"

  read_and_draw_mc_plots(config.names)
  read_and_draw_perf_plots(config.time, config.average)

  return unless config.recursively

  Dir['*/'].each do |dir|
    config.change_dir(dir)
    draw_into_dir(config)
    Dir.chdir('..')
  end
end

class PlotsConfig
  attr_reader :result_dir, :recursively, :average, :time, :names

  def initialize(options)
    @result_dir = options.delete('--dir')

    @names = options.delete('--names')
    @names = @names ? @names.split(',') : []

    options.each do |dashed_k, v|
      k = dashed_k[2..dashed_k.length]
      instance_variable_set("@#{k}".to_sym, v)
    end

    unless %w(hour min sec).include?(@time)
      raise Docopt::Exit, "Invalid time value\n"
    end
  end

  def change_dir(dir)
    @result_dir = dir
  end

  def time
    case @time
    when 'hour' then 3600
    when 'min' then 60
    when 'sec' then 1
    end
  end
end

def main
  doc = <<HEREHELP
Usage: 
  #{__FILE__} [options]

Options:
  -h, --help         Show this
  -d DIR, --dir=DIR  Directory with results
  -r, --recursively  Recursive searching a result files
  -a, --average      Average the time by the number of iterations
  -t, --time=UNIT    Mean unit of time (hour|min|sec) [default: sec]
  --names=NAMES      Set the names of curves separated by commas
HEREHELP

  begin
    options = Docopt::docopt(doc)
    config = PlotsConfig.new(options)

    if config.result_dir
      draw_into_dir(config)
    else
      puts "Wrond run!"
      puts doc
    end
  rescue Docopt::Exit
    puts doc
  end
end

main
