# coding: utf-8

require 'docopt'
require 'gnuplot'

EXT_MC = 'mcr'
EXT_PERF = 'prf'

class Gnuplot::DataSet
  attr_accessor :linenumber

  alias_method '_plot_args', 'plot_args'
  def plot_args(io = "")
    _plot_args(io)

    @@counter ||= 1
    if @@counter % 3 == 0
      @@counter = 1
      io << " with lines"
    else
      @@counter += 1
      io << " with linespoints"
      # io << " with lines"
    end

    io << " ls #{linenumber}" if linenumber
    io
  end
end

def color(i)
  # colors = ['gray', 'black']
  colors = ['black']
  colors[i % colors.size]
end

def reset_lines
  @ln, @lt, @lw = 0, 0, 6
end

def make_line(plot)
  @ln += 1
  # plot.set("style", "line #@ln linetype #@lt linewidth #@lw linecolor rgb \"#{color(@ln)}\"")
  plot.set("style", "line #@ln linetype #@lt linewidth #@lw pointsize 2")
  @lt += 1
  @ln
end

def make_gnuplot(file_name, title, xlabel, ylabel, &block)
  Gnuplot.open do |gp|
    Gnuplot::Plot.new(gp) do |plot|
      
      # plot.output("#{file_name}.png")
      # # plot.terminal('png truecolor')
      # plot.set('term png size 355,255')
      # plot.set('term png font', '",12"')

      plot.output("#{file_name}.eps")
      plot.set('enc cp1251')
      # plot.set('terminal postscript eps monochrome 26')
      # plot.set('term postscript eps font "URWPalladioL-Roma,26"')
      # plot.set('term postscript eps font "URWPalladioL-Roma,26" fontfile "/usr/share/fonts/default/Type1/p052003l.pfb"')
      plot.set('term postscript eps font "Times-New-Roman,32"')

      # plot.set("fontpath '/home/newmen/Downloads'")
      # plot.set("term post eps enh 'SFBSR17' 26")

      plot.set('key left reverse')

      # plot.title(title)
      plot.xlabel(xlabel)
      plot.ylabel(ylabel)
      
      block.call(plot)

      # puts plot.to_gplot
      # puts plot.store_datasets
    end
  end
end

def make_mc_time_gnuplot(file_name, title, &block)
  make_gnuplot(file_name, title, 'Время (сек)', 'Концентрация (%)') do |plot|
    # plot.xrange('[45:70]')
    # plot.xrange('[0:100]')
    # plot.xrange('[0:50]')
    
    block.call(plot)
  end
end

def make_mc_concentrations_gnuplot(file_name, title, a_title, b_title, &block)
  make_gnuplot(file_name, title, "Концентрация #{a_title} (%)", "Концентрация #{b_title} (%)") do |plot|
    plot.xtics('0, 0.1, 0.6')
    plot.xrange('[0:0.6]')
    plot.ytics('0, 0.1, 0.6')
    plot.yrange('[0:0.6]')
    # plot.ytics('0, 0.1, 1')
    # plot.yrange('[0:1]')

    block.call(plot)
  end
end

def make_perf_gnuplot(file_name, title, ylabel, &block)
  make_gnuplot(file_name, title, 'Размер поля (кол-во ячеек x1000)', ylabel) do |plot|
    plot.xtics('0, 2, 10')
    plot.xrange('[0:10]')
    # plot.ytics('12, 4, 28')
    # plot.yrange('[11:29]')
    # plot.ytics('0, 10, 40')
    # plot.yrange('[0:44]')
    plot.ytics('0, 0.02, 0.08')
    plot.yrange('[0:0.08]')
    block.call(plot)
  end
end

def make_mc_time_data(plot, data, &block)
  data[1].map do |name, arr_y|
    Gnuplot::DataSet.new([data[0], arr_y]) do |ds|
      # ds.with = ds_with
      # ds.with = 'linespoints'
      ds.linenumber = make_line(plot)

      block.call(name, ds)
    end
  end
end

def make_mc_concentrations_data(a_data, b_data, linenumber, &block)
  Gnuplot::DataSet.new([a_data, b_data]) do |ds|
    # ds.with = ds_with
    # ds.with = 'linespoints'
    ds.linenumber = linenumber
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

def mc_concentrations_data(plot, a_data, b_data)
  # make_mc_concentrations_data(a_data, b_data, 'linespoints') do |ds|
  make_mc_concentrations_data(a_data, b_data, make_line(plot)) do |ds|
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
        org_data << mc_concentrations_data(plot, mc_a_data[1], mc_b_data[1]) if mc
      else
        org_data << mc_concentrations_data(plot, a_data[1], b_data[1])
      end
      plot.data = org_data
    end
  end
end

def draw_mc_time_graph(original, mc, file_name)
  make_mc_time_gnuplot(file_name, mc[2]) do |plot|
    org_data = []
    org_data += original_time_data(original) if original
    # plot.data = org_data + make_mc_time_data(mc, "linespoints") do |name, ds|
    plot.data = org_data + make_mc_time_data(plot, mc) do |name, ds|
      # ds.title = "MC #{name}"
      ds.title = name
    end
  end
end

def draw_perf_graph(arr_x, arrs_y, name, unit = nil)
  title, ylabel = '', ''
  case name
  when /(faster|times)/
    title = 'Сравнение времён расчёта'
    ylabel = "Время расчёта (#{unit || 'сек'})"
  when 'iterations'
    title = 'Сравнение количества итераций'
    ylabel = 'Всего итераций'
  when 'virtuals'
    title = 'Сравнение потребления памяти'
    ylabel = "Использовано памяти (#{unit || 'КБ'})"
  when 'rss'
    title = 'Сравнение потребления памяти'
    ylabel = "Выделено памяти (#{unit || 'КБ'})"
  end

  make_perf_gnuplot(name, title, ylabel) do |plot|
    plot.data = arrs_y.map do |c_name, arr_y|
      c_name = case c_name
      when /Динамический/ then 'D '
      when /Кинетический/ then 'K '
      when /отказа/ then 'R '
      when /сумм/ then 'RF'
      else
        if c_name =~ /\A.+\((\d) .+\)\Z/
          c_name.sub /\A.+\((\d) .+\)\Z/, 'F\1'
        elsif c_name =~ /\A.+\(бинарный|binary\)\Z/
          'FB'
        else
          'F2'
        end
      end

      next if c_name =~ /\AF/ && c_name != 'F4' && name !~ /\Afaster/

      Gnuplot::DataSet.new([arr_x, arr_y]) do |ds|
        # ds.with = "linespoints"
        # ds.linewidth = 2
        ds.title = c_name
        ds.linenumber = make_line(plot)
      end
    end.compact
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
  [arr_x, arrs_y.to_a]
end

def draw_perf_file(arr_x, arrs_y, base_file_name, unit = nil)
  draw_perf_graph(arr_x, arrs_y, base_file_name, unit)

  if base_file_name == 'times'
    faster_arrs_y = {}
    arrs_y.each do |k, v|
      faster_arrs_y[k] = v if k =~ /\A(F|f)aster/ || k =~ /\A(М|м)ного/
    end

    draw_perf_graph(arr_x, faster_arrs_y, 'faster-times', unit)
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
    reset_lines
    mc = read_mc_file(file_name, names)
    base_file_name = File.basename(file_name, ".#{EXT_MC}")
    draw_mc_time_graph(original, mc, base_file_name)
    draw_concentrations_graphs(base_file_name, original, mc)
  end
end

def decrease_any_y_value!(arrs_y, coef)
  arrs_y.map! do |name, values|
    [name, values.map { |v| v / coef }]
  end
end

def read_and_draw_perf_plots(time_coef, normalize_time, step_seconds, time_unit)
  iterations_data = nil
  times_data = nil

  Dir["*.#{EXT_PERF}"].each do |file_name|
    reset_lines

    data = read_perf_file(file_name)
    arr_x, arrs_y = data
    base_file_name = File.basename(file_name, ".#{EXT_PERF}")
    is_time_file = (base_file_name =~ /time/)

    arr_x.map! { |x| x * 0.001 }

    if is_time_file
      decrease_any_y_value!(arrs_y, step_seconds)
    elsif base_file_name =~ /(virtuals|rss)/
      decrease_any_y_value!(arrs_y, 1000.0)
    end

    if normalize_time
      iterations_data = data if base_file_name == 'iterations'
      times_data = data if is_time_file
    end

    if !normalize_time || !is_time_file
      if is_time_file
        draw_perf_file(arr_x, arrs_y, base_file_name, time_unit)
      else
        draw_perf_file(arr_x, arrs_y, base_file_name)
      end
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
    sum = slice.inject(0) { |acc, x| acc + x }
    sum / slice.size
  end

  time_arrs_y.each do |name, values|
    values.each_index do |i|
      values[i] *= normalize_iters[i]
    end
  end

  draw_perf_file(time_arr_x, time_arrs_y, 'times', time_unit)
end

def draw_into_dir(config)
  print "Entering into #{File.expand_path(config.result_dir)}..."
  Dir.chdir(config.result_dir)
  puts " complete"

  read_and_draw_mc_plots(config.names)
  read_and_draw_perf_plots(config.time, config.normalize, config.seconds_step, config.time_unit)

  return unless config.recursively

  Dir['*/'].each do |dir|
    config.change_dir(dir)
    draw_into_dir(config)
    Dir.chdir('..')
  end
end

class PlotsConfig
  attr_reader :result_dir, :recursively, :normalize, :time, :names

  def initialize(options)
    @result_dir = options.delete('--dir').first

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

  def seconds_step
    time_value(3600, 60, 1).to_f
  end

  def time_unit
    time_value('час', 'мин', 'сек')
  end

  private

  def time_value(hour, min, sec)
    case time
    when 'hour' then hour
    when 'min' then min
    when 'sec' then sec
    end
  end
end

def main
  doc = <<HEREHELP
Usage: 
  #{__FILE__} -d RESULTS_DIR [options]

Options:
  -h, --help         Show this
  -d DIR, --dir=DIR  Directory with results
  -r, --recursively  Recursive searching a result files
  -n, --normalize    Normalize the time by the number of iterations
  -t, --time=unit    Mean unit of time (hour|min|sec) [default: sec]
  --names=NAMES      Set the names of curves separated by commas
HEREHELP

  # TODO:
  # 1. так и не запилен пересчёт времени, с учётом указанного параметра
  # 2. нужно предоставлять возможность указывать логарифмическую шкалу времени
  # 3. предоставлять возможность указывать какие из имеющихся результатов методов обрабатывать
  # 4. выбирать диапазон рисуемых графиков концентраций (в секундах)
  # 5. определять рисовать ли title графика

  begin
    options = Docopt::docopt(doc)
    config = PlotsConfig.new(options)

    if config.result_dir
      draw_into_dir(config)

      Dir['*.eps'].each do |eps_file|
        content = File.read(eps_file)#.encode('cp1251').gsub('x1000', '×1000')
        File.open(eps_file, 'w:CP1251') { |f| f.write(content) }
      end
    else
      puts "Wrond run!"
      puts doc
    end
  rescue Docopt::Exit
    puts doc
  end
end

main
