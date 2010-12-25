Gem::Specification.new do |s|
  s.name = 'gab_buffer'
  s.version = '0.1'
  s.date = '2010-10-25'
  s.authors = ['Lourens Naudé', 'Hsin Tsao']
  s.email = ['lourens@methodmissing.com', 'stsao@lazyhacker.com']
  s.description = 'WIP implementation of a Gap Buffer for Ruby MRI.'
  s.homepage = 'http://github.com/methodmissing/gap_buffer'
  s.summary = 'WIP implementation of a Gap Buffer for Ruby MRI.'
  s.extensions = 'ext/gap_buffer/extconf.rb'
  s.files = Dir.glob("{ext,test,bench}/**/*") + %w[README Rakefile gap_buffer.gemspec]
  s.has_rdoc = true
  s.extra_rdoc_files = Dir['ext/gap_buffer/*.c']
end