PNO = 4e-7
PCO = 3e-7

K1 = 2.21e5
K2 = 2.21e5
K3 = 1.7e15
K4 = 1e15
K5 = 5e8 / 4
K6 = 5e14 / 4

E3 = 37e3
E4 = 37.5e3
E5 = 12e3
E6 = 28e3

Eps3NO = 1.5e3
Eps4NO = 1.5e3
Eps6NO = -1.5e3
Eps3CO = 1.5e3
Eps4CO = 1e3
Eps6CO = 0
Eps3O = 1.5e3
Eps4O = 1.5e3
Eps6O = -1.5e3

T = 410
R = 1.987
RT = R * T

def rate(name, nNO, nCO, nO, k, e, epsNO, epsCO, epsO, maxN)
  # r = k * Math.exp(-(e + nNO * epsNO + nCO * epsCO) / RT)
  # r = k * Math.exp(-e / RT) * (1 + nNO * (Math.exp(epsNO / RT) - 1) + nCO * (Math.exp(epsCO / RT) - 1)) ** maxN
  r = k * Math.exp((-e + nNO * epsNO + nCO * epsCO + nO * epsO) / RT)
  [r, "#{name} [NO: #{nNO}, CO: #{nCO}, O: #{nO}]"]
end

def rate3(nNO, nCO, nO)
  rate('mono(3)', nNO, nCO, nO, K3, E3, Eps3NO, Eps3CO, Eps3O, 4)
end

def rate4(nNO, nCO, nO)
  rate('mono(4)', nNO, nCO, nO, K4, E4, Eps4NO, Eps4CO, Eps4O, 4)
end

def rate6(nNO, nCO, nO)
  rate('dual(6)', nNO, nCO, nO, K6, E6, Eps6NO, Eps6CO, Eps6O, 6)
end

def separator
  puts '-------------'
end

def show_rates(name, maxN)
  results = []
  (0..maxN).each do |x|
    (0..maxN).each do |y|
      (0..maxN).each do |z|
        unless x + y + z > maxN
          results << eval("#{name}(x, y, z)")
        end
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

show_rates('rate3', 4)
show_rates('rate4', 4)
puts "dual(5) -> #{K5 * Math.exp(-E5 / RT)}"
separator
show_rates('rate6', 6)
