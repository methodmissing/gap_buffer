#include "gap_buffer.h"
#include <ruby.h>

#ifndef RSTRING_PTR
#define RSTRING_PTR(obj) RSTRING(obj)->ptr
#endif
 
#ifndef RSTRING_LEN
#define RSTRING_LEN(obj) RSTRING(obj)->len
#endif

#define GetGapBuffer(obj) \
    GapBuffer *gb = NULL; \
    Data_Get_Struct((obj), GapBuffer, gb); \
    if (!gb) \
        rb_raise(rb_eException, "No gap buffer!");

#define GapBufferChar(chr) \
    char c = (chr); \
    if (c == 0) return rb_str_tmp_new(0); \
    return rb_str_new(&c, 1);

VALUE rb_cGapBuffer;

static void rb_gap_buffer_free(void *gb)
{
    if(gb) delete((GapBuffer*) gb);
}

static VALUE rb_gap_buffer_new(int argc, VALUE *argv, VALUE obj)
{
    VALUE size;
    rb_scan_args(argc, argv, "01", &size);
    if (NIL_P(size)) size = rb_const_get(rb_cGapBuffer, rb_intern("GAP_SIZE"));
    GapBuffer *gb = NULL;
    gb = new GapBuffer(NUM2INT(size));
    if (!gb)
       rb_raise(rb_eException, "No gap buffer!");
    return Data_Wrap_Struct(rb_cGapBuffer, 0, rb_gap_buffer_free, (void*)gb);
}

static VALUE rb_gap_buffer_size(VALUE obj)
{
    GetGapBuffer(obj);
    return INT2FIX(gb->BufferSize());
}

static VALUE rb_gap_buffer_gap_size(VALUE obj)
{
    GetGapBuffer(obj);
    return INT2FIX(gb->SizeOfGap());
}

static VALUE rb_gap_buffer_print(VALUE obj)
{
    GetGapBuffer(obj);
    gb->PrintBuffer();
    return Qnil;
}

static VALUE rb_gap_buffer_append(VALUE obj, VALUE str)
{
    GetGapBuffer(obj);
    Check_Type(str, T_STRING);
    gb->InsertString(RSTRING_PTR(str), (unsigned int)RSTRING_LEN(str));
    return obj;
}

static VALUE rb_gap_buffer_offset(VALUE obj)
{
    GetGapBuffer(obj);
    return INT2FIX(gb->PointOffset());
}

static VALUE rb_gap_buffer_offset_equals(VALUE obj, VALUE offset)
{
    GetGapBuffer(obj);
    gb->SetPoint(FIX2INT(offset));
    return offset;
}

static VALUE rb_gap_buffer_move(VALUE obj)
{
    GetGapBuffer(obj);
    gb->MoveGapToPoint();
    return rb_gap_buffer_offset(obj);
}

static VALUE rb_gap_buffer_get(VALUE obj)
{
    GetGapBuffer(obj);
    GapBufferChar(gb->GetChar());
}

static VALUE rb_gap_buffer_previous(VALUE obj)
{
    GetGapBuffer(obj);
    GapBufferChar(gb->PreviousChar());
}

static VALUE rb_gap_buffer_next(VALUE obj)
{
    GetGapBuffer(obj);
    GapBufferChar(gb->NextChar());
}

static VALUE rb_gap_buffer_replace(VALUE obj, VALUE str)
{
    GetGapBuffer(obj);
    Check_Type(str, T_STRING);
    char c = *RSTRING_PTR(str);
    gb->ReplaceChar(c);
    return Qnil;
}

static VALUE rb_gap_buffer_put(VALUE obj, VALUE str)
{
    GetGapBuffer(obj);
    Check_Type(str, T_STRING);
    char c = *RSTRING_PTR(str);
    gb->PutChar(c);
    return Qnil;
}

static VALUE rb_gap_buffer_insert(VALUE obj, VALUE str)
{
    GetGapBuffer(obj);
    Check_Type(str, T_STRING);
    char c = *RSTRING_PTR(str);
    gb->InsertChar(c);
    return Qnil;
}

static VALUE rb_gap_buffer_delete(VALUE obj, VALUE size)
{
    GetGapBuffer(obj);
    gb->DeleteChars(FIX2INT(size));
    return Qnil;
}

static VALUE rb_gap_buffer_to_s(VALUE obj, VALUE size)
{
    GetGapBuffer(obj);
    return(rb_str_new2(gb->GetBuffer()));
}

static VALUE rb_gap_buffer_insert_at(VALUE obj, VALUE offset, VALUE str)
{
    GetGapBuffer(obj);
    Check_Type(str, T_STRING);
    char c = *RSTRING_PTR(str);
    gb->SetPoint(FIX2INT(offset));
    gb->InsertChar(c);
    return Qnil;
}

static VALUE rb_gap_buffer_delete_at(VALUE obj, VALUE offset)
{
    GetGapBuffer(obj);
    gb->SetPoint(FIX2INT(offset));
    gb->DeleteChars(1);
    return Qnil;
}

extern "C" void Init_gap_buffer()
{
    rb_cGapBuffer = rb_define_class("GapBuffer", rb_cObject);
    rb_define_const(rb_cGapBuffer, "GAP_SIZE", INT2NUM(20));

    rb_define_module_function(rb_cGapBuffer, "new", (VALUE(*)(...))rb_gap_buffer_new, -1);
    rb_define_method(rb_cGapBuffer, "size", (VALUE(*)(...))rb_gap_buffer_size, 0);
    rb_define_method(rb_cGapBuffer, "gap_size", (VALUE(*)(...))rb_gap_buffer_gap_size, 0);
    rb_define_method(rb_cGapBuffer, "print", (VALUE(*)(...))rb_gap_buffer_print, 0);
    rb_define_method(rb_cGapBuffer, "<<", (VALUE(*)(...))rb_gap_buffer_append, 1);
    rb_define_method(rb_cGapBuffer, "offset", (VALUE(*)(...))rb_gap_buffer_offset, 0);
    rb_define_method(rb_cGapBuffer, "position", (VALUE(*)(...))rb_gap_buffer_offset, 0);
    rb_define_method(rb_cGapBuffer, "offset=", (VALUE(*)(...))rb_gap_buffer_offset_equals, 1);
    rb_define_method(rb_cGapBuffer, "position=", (VALUE(*)(...))rb_gap_buffer_offset_equals, 1);
    rb_define_method(rb_cGapBuffer, "move", (VALUE(*)(...))rb_gap_buffer_move, 0);
    rb_define_method(rb_cGapBuffer, "get", (VALUE(*)(...))rb_gap_buffer_get, 0);
    rb_define_method(rb_cGapBuffer, "previous", (VALUE(*)(...))rb_gap_buffer_previous, 0);
    rb_define_method(rb_cGapBuffer, "next", (VALUE(*)(...))rb_gap_buffer_next, 0);
    rb_define_method(rb_cGapBuffer, "replace", (VALUE(*)(...))rb_gap_buffer_replace, 1);
    rb_define_method(rb_cGapBuffer, "put", (VALUE(*)(...))rb_gap_buffer_put, 1);
    rb_define_method(rb_cGapBuffer, "insert", (VALUE(*)(...))rb_gap_buffer_insert, 1);
    rb_define_method(rb_cGapBuffer, "delete", (VALUE(*)(...))rb_gap_buffer_delete, 1);
    rb_define_method(rb_cGapBuffer, "to_s", (VALUE(*)(...))rb_gap_buffer_to_s, 0);
    rb_define_method(rb_cGapBuffer, "to_str", (VALUE(*)(...))rb_gap_buffer_to_s, 0);
    rb_define_method(rb_cGapBuffer, "insert_at", (VALUE(*)(...))rb_gap_buffer_insert_at, 2);
    rb_define_method(rb_cGapBuffer, "delete_at", (VALUE(*)(...))rb_gap_buffer_delete_at, 1);
}