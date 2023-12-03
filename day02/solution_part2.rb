#!/usr/bin/env ruby

data = File.read('data.txt')

target = { red: 12, green: 13, blue: 14 }

result = 0

data.lines.each do |line|
  min_red = 0
  min_green = 0
  min_blue = 0

  line.split(';').each do |game|
    red = game.match(/(\d+)\sred/)&.captures&.first.to_i
    green = game.match(/(\d+)\sgreen/)&.captures&.first.to_i
    blue = game.match(/(\d+)\sblue/)&.captures&.first.to_i

    min_red = red > min_red ? red : min_red
    min_green = green > min_green ? green : min_green
    min_blue = blue > min_blue ? blue : min_blue
  end
  result += ((min_red.infinite? ? 1 : min_red) * (min_green.infinite? ? 1 : min_green) * (min_blue.infinite? ? 1 : min_blue))
end

puts result
