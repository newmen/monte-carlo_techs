# coding: utf-8

require 'docopt'
require 'gnuplot'
require 'singleton'

EXT_MC = 'mcr'
EXT_PERF = 'prf'

def doc
<<HEREHELP
Usage:
  #{__FILE__} -d RESULTS_DIR [options]

Options:
  -h, --help                Show this
  -d DIR, --dir=DIR         Directory with results
  -f, --format=ext          Format of output files (png|eps|svg) [default: png]
  -c, --coding=encode       Encoding inscriptions, in the case of format eps (cp1251|uft8) [default: cp1251]
  -k, --key=value           Key location as it setup in Gnuplot (top|left|center|right|bottom|reverse) [default: right top]
  -l, --linetype=type       Type of lines (lines|linespoints|points) [default: linespoints]
  -w, --linewidth=width     Width of lines [default: 1]
  -n, --normalize           Normalize the time by the number of iterations
  -r, --recursively         Recursive searching a result files
  -s, --size=width,height   Size of plots when output file has png format
  -a, --abbreviations       Abbreviations of calculation methods
  -t, --time=unit           Mean unit of time (hour|min|sec) [default: sec]
  --log                     Logarithmic performance time scale
  --font=fontname           Font to be used when output file is not png format [default: Times-New-Roman]
  --fontsize=size           Font size to be used when output file is not png format [default: 32]
  --notitles                Not include titles in pictures
  --nolabels                Not include axis labels in pictures
  --names=NAMES             Set the names of curves separated by commas

Range options:
  --time-x-range=min,max  or  --time-x-range=min,step,max   Values for X axis on time plots
  --time-y-range=min,max  or  --time-y-range=min,step,max   Values for Y axis on time plots
  --phases-range=min,max  or  --phases-range=min,step,max   Values for all axis on C-C plots
  --perf-x-range=min,max  or  --perf-x-range=min,step,max   Values for X axis on performance plots
  --perf-y-range=min,max  or  --perf-y-range=min,step,max   Values for Y axis on performance plots
HEREHELP
end

class PlotsConfig
  include Singleton

  attr_reader :result_dir, :format, :coding, :linetype, :linewidth, :key, :size, :names,
              :normalize, :recursively, :abbreviations, :notitles, :nolabels, :log

  def initialize
    options = Docopt::docopt(doc)
    @result_dir = options.delete('--dir').first

    @names = options.delete('--names')
    @names = @names ? @names.split(',') : []

    define_range_method = -> method_name, min, max do
      self.class.class_eval do
        define_method("#{method_name}range") { "[#{min}:#{max}]" }
      end
    end

    num_rx = '[-+]?[0-9]+\.?[0-9]*(?:[eE][-+]?[0-9]+)?'

    options.each do |dashed_k, v|
      k = dashed_k[2..dashed_k.length]
      if k =~ /range\Z/
        if v
          method_name = k.gsub('-', '_')
          method_name['range'] = ''
          if v =~ /(#{num_rx}),#{num_rx},(#{num_rx})/
            define_range_method[method_name, $1, $2]
            self.class.class_eval do
              define_method("#{method_name}tics") { v }
            end
          elsif v =~ /(#{num_rx}),(#{num_rx})/
            define_range_method[method_name, $1, $2]
          else
            raise Docopt::Exit, "Invalid #{k} value"
          end
        end
      else
        instance_variable_set("@#{k}".to_sym, v)
      end
    end

    unless %w(hour min sec).include?(@time)
      raise Docopt::Exit, "Invalid time value\n"
    end

    if @fontsize !~ /\A\d+\Z/
      raise Docopt::Exit, "Invalid fontsize value\n"
    end
  end

  def change_dir(dir)
    @result_dir = dir
  end

  def seconds_step
    time_value(3600, 60, 1).to_f
  end

  def time_unit
    unit = time_value('час', 'мин', 'сек')
    unit = "log10(#{unit})" if log
    unit
  end

  def font_setup
    %Q(font "#{@font},#{@fontsize}")
  end

  def method_missing(method_name, *args)
    method_name =~ /(?:range|tics)\Z/ ? nil : super
  end

  private

  def time_value(hour, min, sec)
    case @time
    when 'hour' then hour
    when 'min' then min
    when 'sec' then sec
    end
  end
end

def config
  PlotsConfig.instance
end

def data_set(data, &block)
  Gnuplot::DataSet.new(data) do |ds|
    ds.with = config.linetype
    ds.linewidth = config.linewidth
    block.call(ds)
  end
end

def make_gnuplot(file_name, title, xlabel, ylabel, &block)
  Gnuplot.open do |gp|
    Gnuplot::Plot.new(gp) do |plot|
      plot.output("#{file_name}.#{config.format}")
      case config.format
      when 'eps'
        plot.set("enc #{config.coding}")
        plot.set("term postscript eps #{config.font_setup}")
      when 'png'
        plot.set('terminal png')
        plot.set('terminal png size #{config.size}') if config.size
      else
        plot.set("terminal #{config.format}")
        # plot.set("terminal #{config.format} #{config.font_setup}")
      end

      plot.set("key #{config.key}")

      plot.title(title) unless config.notitles
      unless config.nolabels
        plot.xlabel(xlabel)
        plot.ylabel(ylabel)
      end

      block.call(plot)
    end
  end
end

def make_mc_time_gnuplot(file_name, title, &block)
  make_gnuplot(file_name, title, 'Время (сек)', 'Концентрация (%)') do |plot|
    plot.xrange(config.time_x_range) if config.time_x_range
    plot.yrange(config.time_y_range) if config.time_y_range
    plot.xtics(config.time_x_tics) if config.time_x_tics
    plot.ytics(config.time_y_tics) if config.time_y_tics

    block.call(plot)
  end
end

def make_mc_concentrations_gnuplot(file_name, title, a_title, b_title, &block)
  make_gnuplot(file_name, title, "Концентрация #{a_title} (%)", "Концентрация #{b_title} (%)") do |plot|
    if config.phases_range
      plot.xrange(config.phases_range)
      plot.yrange(config.phases_range)
    end
    if config.phases_tics
      plot.xtics(config.phases_tics)
      plot.ytics(config.phases_tics)
    end

    block.call(plot)
  end
end

def make_perf_gnuplot(file_name, title, ylabel, &block)
  make_gnuplot(file_name, title, 'Размер поля (кол-во ячеек x1000)', ylabel) do |plot|
    plot.xrange(config.perf_x_range) if config.perf_x_range
    plot.yrange(config.perf_y_range) if config.perf_y_range
    plot.xtics(config.perf_x_tics) if config.perf_x_tics
    plot.ytics(config.perf_y_tics) if config.perf_y_tics

    block.call(plot)
  end
end

def make_mc_time_data(data, &block)
  data[1].map do |name, arr_y|
    data_set([data[0], arr_y]) do |ds|
      block.call(name, ds)
    end
  end
end

def make_mc_concentrations_data(a_data, b_data, &block)
  data_set([a_data, b_data]) do |ds|
    block.call(ds)
  end
end

def configure_original(ds, name)
  ds.linewidth = config.linewidth
  ds.title = "Original #{name}"
end

def original_time_data(original)
  make_mc_time_data(original) do |name, ds|
    configure_original(ds, name)
  end
end

def original_concentrations_data(a_data, b_data)
  make_mc_concentrations_data(a_data, b_data) do |ds|
    configure_original(ds, 'time')
  end
end

def mc_concentrations_data(a_data, b_data)
  make_mc_concentrations_data(a_data, b_data) do |ds|
    # ds.title = 'MC time'
    ds.title = 'time'
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
    plot.data = org_data + make_mc_time_data(mc) do |name, ds|
      # ds.title = "MC #{name}"
      ds.title = name
    end
  end
end

def draw_perf_graph(arr_x, arrs_y, file_name)
  title, ylabel = '', ''
  case file_name
  when /(faster|times)/
    title = 'Сравнение времён расчёта'
    ylabel = "Время расчёта (#{config.time_unit})"
  when 'iterations'
    title = 'Сравнение количества итераций'
    ylabel = 'Всего итераций'
  when 'virtuals'
    title = 'Сравнение потребления памяти'
    ylabel = 'Использовано памяти (КБ)'
  when 'rss'
    title = 'Сравнение потребления памяти'
    ylabel = 'Выделено памяти (КБ)'
  end

  make_perf_gnuplot(file_name, title, ylabel) do |plot|
    plot.data = arrs_y.map do |c_name, arr_y|
      # кусочек жести строкой ниже
      next if file_name =~ /time/ && file_name !~ /\Afaster/ &&
        fasters(arrs_y).include?(c_name) && c_name != slow_faster(arrs_y)

      if config.abbreviations
        prefix = c_name =~ /птими|ptimi/ ? 'O' : ''
        prefix = "M#{prefix}" if c_name =~ /(?:олее|ore) /
        c_name = case c_name
        when /инамический|ynamic/ then 'D'
        when /инетический|inetic/ then 'K'
        when /сумм|free/ then 'RF'
        when /отказа/ then 'R'
        else
          if c_name =~ /\A.+\((\d) .+\)\Z/
            c_name.sub(/\A.+\((\d) .+\)\Z/, 'F\1')
          elsif c_name =~ /\A.+\(бинарный|binary\)\Z/
            'FB'
          else
            'F2'
          end
        end
        c_name = "#{prefix}#{c_name}"
      end

      data_set([arr_x, arr_y]) do |ds|
        ds.title = c_name
      end
    end.compact
  end
end

def slow_faster(arrs_y)
  @slow_faster ||= arrs_y.map do |c_name, arr_y|
    [c_name, (fasters(arrs_y).include?(c_name) ? arr_y.max : 0)]
  end.max { |a, b| a[1] <=> b[1] }[0]
end

def most_max(arrs_y)
  @most_max ||= arrs_y.map { |_, arr_y| arr_y.max }.max
end

def fasters(arrs_y)
  @fasters ||= arrs_y.map do |c_name, arr_y|
    (arr_y.max < most_max(arrs_y) / (config.log ? 2 : 100).to_f) ? c_name : nil
  end.compact
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

        if arrs_y.empty?
          (config.names + ('A'..'Z').to_a)[0...(values.size)].each do |char|
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
        arrs_y.each do |_, arr_y|
          arr_y << values[i].to_f
          i += 1
        end
      end
    end
  end

  puts " complete"
  [arr_x, arrs_y.to_a]
end

def draw_perf_file(arr_x, arrs_y, base_file_name)
  draw_perf_graph(arr_x, arrs_y, base_file_name)

  if base_file_name == 'times'
    faster_arrs_y = arrs_y.select { |c_name, arr_y| fasters(arrs_y).include?(c_name) }
    draw_perf_graph(arr_x, faster_arrs_y, 'faster-times')
  end
end

def decrease_each_y_value(arrs_y, coef)
  arrs_y.map! do |name, values|
    [name, values.map { |v| v / coef }]
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
    base_file_name = File.basename(file_name, ".#{EXT_MC}")
    draw_mc_time_graph(original, mc, base_file_name)
    draw_concentrations_graphs(base_file_name, original, mc)
  end
end

def read_and_draw_perf_plots
  iterations_data = nil
  times_data = nil

  Dir["*.#{EXT_PERF}"].each do |file_name|
    data = read_perf_file(file_name)
    arr_x, arrs_y = data
    base_file_name = File.basename(file_name, ".#{EXT_PERF}")
    is_time_file = (base_file_name =~ /time/)

    arr_x.map! { |x| x * 0.001 }

    if is_time_file
      decrease_each_y_value(arrs_y, config.seconds_step)
      if config.log
        arrs_y.map! do |name, values|
          [name, values.map { |v| Math.log10(v) }]
        end
      end
    elsif base_file_name =~ /(virtuals|rss)/
      decrease_each_y_value(arrs_y, 1000.0)
    end

    if config.normalize
      iterations_data = data if base_file_name == 'iterations'
      times_data = data if is_time_file
    end

    unless config.normalize && is_time_file
      draw_perf_file(arr_x, arrs_y, base_file_name)
    end
  end

  return unless iterations_data && times_data

  iter_arr_x, iter_arrs_y = iterations_data
  time_arr_x, time_arrs_y = times_data
  raise "Size values do not match" unless iter_arr_x == time_arr_x

  normalize_iters = []
  time_arrs_y.each do |name, values|
    values.each_index do |i|
      values[i] /= iter_arrs_y[name][i]
      normalize_iters[i] ||= []
      normalize_iters[i] << iter_arrs_y[name][i]
    end
  end

  normalize_iters.map! do |slice|
    slice.inject(:+) / slice.size
  end

  time_arrs_y.each do |name, values|
    values.each_index do |i|
      values[i] *= normalize_iters[i]
    end
  end

  draw_perf_file(time_arr_x, time_arrs_y, 'times')
end

def draw_into_dir
  print "Entering into #{File.expand_path(config.result_dir)}..."
  Dir.chdir(config.result_dir)
  puts " complete"

  read_and_draw_mc_plots
  read_and_draw_perf_plots

  return unless config.recursively

  Dir['*/'].each do |dir|
    config.change_dir(dir)
    draw_into_dir
    Dir.chdir('..')
  end
end

def main
  # TODO:
  # 1. нужно предоставлять возможность указывать логарифмическую шкалу времени
  # 2. предоставлять возможность указывать какие из имеющихся результатов методов обрабатывать

  begin
    if config.result_dir
      draw_into_dir

      if config.format == 'eps' && config.coding != 'utf8'
        Dir['*.eps'].each do |eps_file|
          content = File.read(eps_file)#.encode(config.coding).gsub('x1000', '×1000')
          File.open(eps_file, "w:#{config.coding}") { |f| f.write(content) }
        end
      end
    else
      puts doc
    end
  rescue Docopt::Exit => e
    puts e.message
    # puts doc
  end
end

main
