#!/usr/bin/env ruby

datafile = File.read('data1.txt')

result = 0

datafile.lines.each do |line|
  captures = line.match(/Card\s*\d*:\s*([\d\s]+)\s*\|\s([\d\s]+)/)&.captures

  winning_numbers = captures[0].scan(/\d+/).map(&:to_i)
  numbers = captures[1].scan(/\d+/).map(&:to_i)

  numbers_in_both = numbers.filter { |number| winning_numbers.include? number }
  numbers_in_both_size = numbers_in_both.size

  result += 2**(numbers_in_both_size - 1) if numbers_in_both_size.positive?
end

puts result
