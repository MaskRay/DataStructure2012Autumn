n = ARGV[0].to_i
q = ARGV[1].to_i
m = ARGV[2].to_i

puts "#{n} #{q} #{m}"
while n > 0 or q > 0
  if rand(n+q) < n
    x = rand 10000
    puts "#{x}"
    n -= 1
  else
    x = Random.rand(m)
    puts "#{-x}"
    q -= 1
  end
end
