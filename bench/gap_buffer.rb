$:.unshift "."
require 'benchmark'
require File.dirname(__FILE__) + '/../ext/gap_buffer/gap_buffer'

TESTS = 1000
ITEMS = (0..TESTS).to_a

def prepare
  string = ITEMS.join
  gb = GapBuffer.new(TESTS)
  gb << ITEMS.join
  [string, gb]
end

Benchmark.bmbm do |results|
  results.report("[String] random insert") do
    string, gb = prepare
    TESTS.times{ r = rand(TESTS); string[r] = r.to_s }
  end
  results.report("[GapBuffer] random insert") do
    string, gb = prepare
    TESTS.times{ r = rand(TESTS); gb.insert_at(r, r.to_s); }
  end
  results.report("[String] insert") do
    string, gb = prepare
    TESTS.times{|i| string[i] = i.to_s }
  end
  results.report("[GapBuffer] insert") do
    string, gb = prepare
    TESTS.times{|i| gb.insert_at(i, i.to_s); }
  end
  results.report("[String] random remove") do
    string, gb = prepare
    TESTS.times{ r = rand(TESTS); string.delete!(r.to_s) }
  end
  results.report("[GapBuffer] random remove") do
    string, gb = prepare
    TESTS.times{ r = rand(TESTS); gb.delete(r) }
  end
end
