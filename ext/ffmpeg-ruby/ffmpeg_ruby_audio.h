#ifndef	__FFMPEG_RUBY_AUDIO_H__
#define	__FFMPEG_RUBY_AUDIO_H__

#include "ffmpeg_ruby.h"

typedef struct _audio_internal {
	VALUE io;
} audio_internal_t;

// Object Lifetime
VALUE audio_register_class(VALUE module, VALUE super);

#endif // __FFMPEG_RUBY_AUDIO_H__
