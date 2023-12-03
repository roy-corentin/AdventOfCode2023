#!/usr/bin/env ruby

data = File.read('data1.txt')
puts data.lines

target = { red: 12, green: 13, blue: 14 }

result = 0

data.lines.each do |line|
  id, = line.match(/Game (\d+):/).captures
  game_validations = line.split(';').map do |game|
    red, = game.match(/(\d+)\sred/)&.captures || 0
    green, = game.match(/(\d+)\sgreen/)&.captures || 0
    blue, = game.match(/(\d+)\sblue/)&.captures || 0

    red.to_i <= target[:red] && green.to_i <= target[:green] && blue.to_i <= target[:blue]
  end

  result += id.to_i if game_validations.all?
end

puts result
