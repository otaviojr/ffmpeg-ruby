#include "ffmpeg_ruby.h"

#include "ffmpeg_ruby_audio.h"

// Globals
static VALUE _klass;

/*
**	Deinitialize.
*/
void DeInit_ruby_ffmpeg(VALUE data) {
	(void)data;
}

/*
**	Initialize.
*/
void Init_ruby_ffmpeg_ext(void) {

	// FFMPEG
	avcodec_register_all();
	av_register_all();
	avfilter_register_all();
	
	av_log_set_level(AV_LOG_QUIET);

	// Ruby
	rb_set_end_proc(DeInit_ruby_ffmpeg, Qnil);

	VALUE module = rb_define_module("RFFMPEG");

	//movie_register_class(module, rb_cObject);
	audio_register_class(module, rb_cObject);
}
