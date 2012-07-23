# coding: utf-8

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

def make_mc_gnuplot(file_name, title, &block)
  make_gnuplot(file_name, title, 'Время (сек)', 'Концентрация (%)') do |plot|
    plot.xrange('[0:2250]')
    
    block.call(plot)
  end
end

def make_perf_gnuplot(file_name, title, ylabel, &block)
  make_gnuplot(file_name, title, 'Размер поля (кол-во ячеек)', ylabel) do |plot|
    block.call(plot)
  end
end

def make_mc_data(data, ds_with, &block)
  data[1].map do |name, arr_y|
    percent_arr_y = arr_y.map { |x| x * 100 }
    Gnuplot::DataSet.new([data[0], percent_arr_y]) do |ds|
      ds.with = ds_with

      block.call(name, ds)
    end
  end
end

def original_data(original)
  make_mc_data(original, 'lines') do |name, ds|
    ds.linewidth = 2
    ds.title = "Original #{name}"
  end
end

def draw_original(original)
  make_mc_gnuplot('original', 'ОДУ') do |plot|
    plot.data = original_data(original)
  end
end

def draw_mc_graph(original, mc, file_name)
  make_mc_gnuplot(file_name, mc[2]) do |plot|
    org_data = []
    org_data += original_data(original) if original
    plot.data = org_data + make_mc_data(mc, 'linespoints') do |name, ds|
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
    draw_original(original)
  else
    original = nil
  end

  mc_files = Dir["*.#{EXT_MC}"] - [original_file]
  mc_files.each do |file_name|
    mc = read_mc_file(file_name)
    draw_mc_graph(original, mc, File.basename(file_name, ".#{EXT_MC}"))
  end
end

def read_and_draw_perf_plots
  Dir["*.#{EXT_PERF}"].each do |file_name|
    read_and_draw_perf_file(file_name)
  end
end

def main
  result_dir = ARGV[0]
  if result_dir
    Dir.chdir(result_dir)

    read_and_draw_mc_plots
    read_and_draw_perf_plots
  else
    puts "Неправильный запуск"
    puts "Необходимо передавать первым параметром путь до директории с результатами расчёта"
  end
end

main
