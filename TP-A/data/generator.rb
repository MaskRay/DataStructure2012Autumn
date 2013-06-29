#!/usr/bin/env ruby
def f n, nn
  raise if 2 * nn < n*n+5*n
  p nn
  n.times do |i|
    puts "a #{i} #{i}"
  end
  n.times do |i|
    puts "b #{i+1}"
    (i+1).times do |j|
      puts "b #{n+(i+2)*(i+1)/2+j}"
    end
  end

  o = [0,1,2]
  ((n*n+5*n)/2+1).upto nn do |m|
    if rand(2) == 0
      x = rand 3
      puts "a #{o[x]} #{rand(12345678)}"
      o[x] = m
    else
      x = rand 3
      puts "b #{o[x]}"
      o[x] = m
    end
  end
end

f (ARGV[0] || 3).to_i, (ARGV[1] || 20).to_i
