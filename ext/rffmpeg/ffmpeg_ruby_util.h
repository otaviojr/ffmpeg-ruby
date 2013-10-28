#ifndef	__FFMPEG_RUBY_UTIL_H__
#define	__FFMPEG_RUBY_UTIL_H__

VALUE streams_to_ruby_array(VALUE self, AVFormatContext * format);
VALUE av_dictionary_to_ruby_hash(AVDictionary * dict);

#endif	// __FFMPEG_RUBY_UTIL_H__
