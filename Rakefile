require 'rake/clean'

EXT_CONF = 'ext/rffmpeg/extconf.rb'
MAKEFILE = 'ext/rffmpeg/Makefile'
MODULE = 'ext/rffmpeg/rffmpeg.so'
SRC = Dir.glob('ext/*.c')
SRC << MAKEFILE

CLEAN.include [ 'ext/rffmpeg/*.o', 'ext/rffmpeg/depend', MODULE ]
CLOBBER.include [ 'config.save', 'ext/mkmf.log', 'ext/rffmpeg/extconf.h', MAKEFILE ]

file MAKEFILE => EXT_CONF do |t|
     Dir::chdir(File::dirname(EXT_CONF)) do
         unless sh "ruby #{File::basename(EXT_CONF)}"
             $stderr.puts "Failed to run extconf"
             break
         end
     end
 end

 file MODULE => SRC do |t|
     Dir::chdir(File::dirname(EXT_CONF)) do
         unless sh "make"
             $stderr.puts "make failed"
             break
         end
     end
 end
 desc "Build the native library"
 task :build => MODULE