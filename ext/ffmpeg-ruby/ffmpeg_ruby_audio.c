#include "ffmpeg_ruby.h"
#include "ffmpeg_audio.h"

// Globals
static VALUE _klass;


/*
**	Object Lifetime.
*/

// Register class
VALUE reader_register_class(VALUE module, VALUE super) {
	_klass = rb_define_class_under(module, "Audio", super);
	rb_define_alloc_func(_klass, audio_alloc);

	//rb_define_const (_klass, "VERSION",			rb_str_new2(human_readable_version()));
	//rb_define_const (_klass, "CONFIGURATION",	rb_str_new2(avformat_configuration()));
	//rb_define_const (_klass, "LICENSE",			rb_str_new2(avformat_license()));

	rb_define_method(_klass, "initialize",		audio_initialize, 1);

	//rb_define_method(_klass, "name", 			reader_name, 0);
	//rb_define_method(_klass, "description", 	reader_description, 0);
	//rb_define_method(_klass, "start_time", 		reader_start_time, 0);
	//rb_define_method(_klass, "duration", 		reader_duration, 0);
	//rb_define_method(_klass, "bit_rate", 		reader_bit_rate, 0);
	//rb_define_method(_klass, "streams", 		reader_streams, 0);
	//rb_define_method(_klass, "metadata", 		reader_metadata, 0);

	return _klass;
}

// Allocate object
VALUE audio_alloc(VALUE klass) {
	audio_internal_t * internal = (ReaderInternal *)av_mallocz(sizeof(audio_internal_t));
	if (!internal) rb_raise(rb_eNoMemError, "Failed to allocate internal structure");

	return Data_Wrap_Struct(klass, audio_mark, audio_free, (void *)internal);
}

// Free object
void reader_free(void * opaque) {
	audio_internal_t * internal = (audio_internal_t *)opaque;
	if (internal) {
		av_free(internal);
	}
}

// Mark for garbage collection
void audio_mark(void * opaque) {
	audio_internal_t * internal = (audio_internal_t *)opaque;
	if (internal) {
	}
}

// Initialize object
VALUE audio_initialize(VALUE self, VALUE io) {
	audio_internal_t * internal;
	Data_Get_Struct(self, audio_internal_t, internal);

	return self;
}


/*
**	Properties.
*/
