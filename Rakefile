#!/usr/bin/env rake
require 'rake/testtask'
require 'rake/clean'
$:.unshift(File.expand_path('lib'))
GAP_BUFFER_ROOT = 'ext/gap_buffer'

desc 'Default: test'
task :default => :test

desc 'Run gap_buffer tests.'
Rake::TestTask.new(:test) do |t|
  t.libs = [GAP_BUFFER_ROOT]
  t.pattern = 'test/test_*.rb'
  t.ruby_opts << '-rtest'
  t.libs << 'test'
  t.warning = true
  t.verbose = true
end
task :test => :build

namespace :build do
  file "#{GAP_BUFFER_ROOT}/rubymain.cpp"
  file "#{GAP_BUFFER_ROOT}/extconf.rb"
  file "#{GAP_BUFFER_ROOT}/Makefile" => %W(#{GAP_BUFFER_ROOT}/rubymain.cpp #{GAP_BUFFER_ROOT}/extconf.rb) do
    Dir.chdir(GAP_BUFFER_ROOT) do
      ruby 'extconf.rb'
    end
  end

  desc "generate makefile"
  task :makefile => %W(#{GAP_BUFFER_ROOT}/Makefile #{GAP_BUFFER_ROOT}/rubymain.cpp)

  dlext = Config::CONFIG['DLEXT']
  file "#{GAP_BUFFER_ROOT}/gap_buffer.#{dlext}" => %W(#{GAP_BUFFER_ROOT}/Makefile #{GAP_BUFFER_ROOT}/rubymain.cpp) do
    Dir.chdir(GAP_BUFFER_ROOT) do
      sh 'make' # TODO - is there a config for which make somewhere?
    end
  end

  desc "compile gap buffer extension"
  task :compile => "#{GAP_BUFFER_ROOT}/gap_buffer.#{dlext}"

  task :clean do
    Dir.chdir(GAP_BUFFER_ROOT) do
      sh 'make clean'
    end if File.exists?("#{GAP_BUFFER_ROOT}/Makefile")
  end

  CLEAN.include("#{GAP_BUFFER_ROOT}/Makefile")
  CLEAN.include("#{GAP_BUFFER_ROOT}/gap_buffer.#{dlext}")
end

task :clean => %w(build:clean)

desc "compile"
task :build => %w(build:compile)

task :install do |t|
  Dir.chdir(GAP_BUFFER_ROOT) do
    sh 'sudo make install'
  end
end

desc "clean build install"
task :setup => %w(clean build install)

desc 'Run benchmarks'
task :bench do
  ruby "bench/gap_buffer.rb"
end
task :bench => :build