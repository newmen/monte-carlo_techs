PNO = 3.7e-6
PCO = 3e-6

K1 = 1.93e5
K2 = 1.93e5
K3 = 0.5e15
K4 = 2e15
K5 = 1e15

E3 = 24.5e3
E4 = 37e3
E5 = 37.5e3

Eps3NO = -2e3
Eps4NO = 1.8e3
Eps5NO = 2.2e3
Eps3CO = -0.8e3
Eps4CO = 2.2e3
Eps5CO = 1e3

T = 404
R = 1.987
RT = R * T

def rate(name, nNO, nCO, k, e, epsNO, epsCO)
  r = k * Math.exp(-(e + nNO * epsNO + nCO * epsCO) / RT)
  [r, "#{name} [NO: #{nNO}, CO: #{nCO}]"]
end

def rate3(nNO, nCO)
  rate('dual(3)', nNO, nCO, K3, E3, Eps3NO, Eps3CO)
end

def rate4(nNO, nCO)
  rate('mono(4)', nNO, nCO, K4, E4, Eps4NO, Eps4CO)
end

def rate5(nNO, nCO)
  rate('mono(5)', nNO, nCO, K5, E5, Eps5NO, Eps5CO)
end

def separator
  puts '-------------'
end

def show_rates(name, maxN)
  results = []
  (0..maxN).each do |x|
    (0..maxN).each do |y|
      unless x + y > maxN
        results << eval("#{name}(x, y)")
      end
    end
  end

  results.sort! { |a, b| a[0] <=> b[0] }
  results.each do |r, info|
    puts "#{info} -> #{r}"
  end

  separator
end

separator

puts "mono(1) -> #{K1 * PNO}"
separator
puts "mono(2) -> #{K2 * PCO}"

separator

show_rates('rate3', 6)
show_rates('rate4', 4)
show_rates('rate5', 4)
