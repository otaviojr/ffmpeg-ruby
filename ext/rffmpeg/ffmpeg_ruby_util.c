#include "ffmpeg_ruby.h"
#include "ffmpeg_ruby_util.h"

// Wrap streams in Ruby objects
VALUE streams_to_ruby_array(VALUE self, AVFormatContext * format) 
{
	VALUE streams = rb_ary_new();

	unsigned i = 0;
	for(; i < format->nb_streams; ++i) {
		switch (format->streams[i]->codec->codec_type) {
			case AVMEDIA_TYPE_VIDEO: {
				// Video stream
				rb_ary_push(streams, video_stream_new(self, format->streams[i]));
				break;
			}
			case AVMEDIA_TYPE_AUDIO: {
				// Audio stream
				rb_ary_push(streams, audio_stream_new(self, format->streams[i]));
				break;
			}
			default: {
				// All other streams
				rb_ary_push(streams, stream_new(self, format->streams[i]));
				break;
			}
		}
	}

	return streams;
}