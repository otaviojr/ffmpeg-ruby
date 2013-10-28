Gem::Specification.new do |s|
  s.name        = "ffmpeg-ruby"
  s.version     = "0.0.1"
  s.date        = "2013-10-28"
  s.summary     = "Ruby bindings for Libav/FFMPEG libraries"
  s.description = "ruby-ffmpeg is a Ruby extension for the Libav/FFMPEG set of libraries; libavformat, libavcodec, libavutil, and libswscale."
  s.authors     = [ "Otávio Ribeiro" ]
  s.email       = "otavio.ribeiro@gmail.com"
  s.files       = Dir.glob("lib/**/*.rb") + Dir.glob("ext/**/*.{c,h,rb}")
  s.extensions  = [ "ext/ffmpeg-ruby/extconf.rb" ]
  s.homepage    = "http://github.com/tja/ffmpeg-ruby"
end
