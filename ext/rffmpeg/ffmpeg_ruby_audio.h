#ifndef	__FFMPEG_RUBY_AUDIO_H__
#define	__FFMPEG_RUBY_AUDIO_H__

#include "ffmpeg_ruby.h"

#define AUDIO_BUFFER_SIZE		8192


typedef struct _audio_internal {
	AVFormatContext *	format;
	
	VALUE streams;
	VALUE metadata;
} audio_internal_t;

// Object Lifetime
VALUE audio_register_class(VALUE module, VALUE super);
VALUE audio_initialize(VALUE self, VALUE filename);
VALUE audio_alloc(VALUE klass);
void audio_free(void * opaque);
void audio_mark(void * opaque) 

/*properties*/
VALUE audio_metadata(VALUE self);
VALUE audio_streams(VALUE self);

#endif // __FFMPEG_RUBY_AUDIO_H__
