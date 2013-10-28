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

// Convert FFMPEG dictionary to Ruby hash
VALUE av_dictionary_to_ruby_hash(AVDictionary * dict) 
{
	VALUE metadata = rb_hash_new();

	AVDictionaryEntry * temp = NULL;
	while ((temp = av_dict_get(dict, "", temp, AV_DICT_IGNORE_SUFFIX)) != NULL) {
		rb_hash_aset(metadata, ID2SYM(rb_intern(temp->key)), rb_str_new2(temp->value));
	}

	return metadata;
}
