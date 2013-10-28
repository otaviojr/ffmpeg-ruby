#include "ffmpeg_ruby.h"
#include "ffmpeg_ruby_audio.h"

/*
**	Object Lifetime.
*/

// Register class
VALUE audio_register_class(VALUE module, VALUE super) {
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
	rb_define_method(_klass, "streams", 		audio_streams, 0);
	rb_define_method(_klass, "metadata", 		audio_metadata, 0);

	return _klass;
}

// Allocate object
VALUE audio_alloc(VALUE klass) {
	audio_internal_t * internal = (audio_internal_t *)av_mallocz(sizeof(audio_internal_t));
	if (!internal) rb_raise(rb_eNoMemError, "Failed to allocate internal structure");
	
	internal->format = avformat_alloc_context();
	if (!internal->format) rb_raise(rb_eNoMemError, "Failed to allocate FFMPEG format context");

	return Data_Wrap_Struct(klass, audio_mark, audio_free, (void *)internal);
}


// Free object
void audio_free(void * opaque) 
{
	audio_internal_t * internal = (audio_internal_t *)opaque;
	if (internal) {
		if (internal->format){
			avformat_close_input(internal->format);
			avformat_free_context(internal->format);
		}
			
		av_free(internal);
	}
}

// Mark for garbage collection
void audio_mark(void * opaque) 
{
	audio_internal_t * internal = (audio_internal_t *)opaque;
	if (internal) {
		rb_gc_mark(internal->streams);
		rb_gc_mark(internal->metadata);
	}
}

// Initialize object
VALUE audio_initialize(VALUE self, VALUE filename) 
{
	audio_internal_t * internal;
	Data_Get_Struct(self, audio_internal_t, internal);
	
	/*Open media file*/
	int err = avformat_open_input(&internal->format, filename, NULL, NULL);
	if (err) rb_raise_av_error(rb_eLoadError, err);
	
    int err = avformat_find_stream_info(&internal->format, NULL);
    if (err) rb_raise_av_error(rb_eLoadError, err);
	
	int err = av_find_best_stream(&internal->format, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    if (err) rb_raise_av_error(rb_eLoadError, err);
    
	internal->streams = streams_to_ruby_array(self, internal->format);
	internal->metadata = av_dictionary_to_ruby_hash(internal->format->metadata);
	
	return self;
}


/*
**	Properties.
*/

// Media streams
VALUE audio_streams(VALUE self) 
{
	audio_internal_t * internal;
	Data_Get_Struct(self, audio_internal_t, internal);

	return internal->streams;
}

// Metadata
VALUE audio_metadata(VALUE self) 
{
	audio_internal_t * internal;
	Data_Get_Struct(self, audio_internal_t, internal);
	
	return internal->metadata;
}
