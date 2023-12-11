#include "dynstr.h"
#include "dynstr_codes.h"
#include <stdlib.h>
#include <string.h>

void _set_err_(int *err, int status)
{
    if (err)
    {
        *err = status;
    }
}

unsigned char *_sub_str_alloc_(unsigned long from, unsigned long to, unsigned char *text, int *err)
{
    const unsigned long text_len = strlen(text);
    const unsigned long sub_text_len = to - from + 1;

    if (from > to || to >= text_len)
    {
        _set_err_(err, DYNSTR_ILLEGAL_INDEX);
        return NULL;
    }

    const unsigned long txt_size = sizeof(unsigned char) * text_len;
    const unsigned long sub_txt_size = sizeof(unsigned char) * (sub_text_len + 1);

    unsigned char *chars = (unsigned char *)malloc(sub_txt_size);

    if (!chars)
    {
        _set_err_(err, DYNSTR_ERR_ALLOC_MEM);
        return NULL;
    }

    memcpy(chars, text + from, sub_txt_size);
    memset(chars + sub_text_len, 0, sizeof(unsigned char));

    return chars;
}

int _insert_at_(unsigned char *text, unsigned long at, struct _dynstr_ *str)
{
    const unsigned long text_len = strlen(text);
    const unsigned long buff_len = str->length;
    const unsigned long result_buff_len = text_len + buff_len;

    const unsigned long text_size = sizeof(unsigned char) * text_len;
    const unsigned long buff_size = sizeof(unsigned char) * buff_len;
    const unsigned long raw_buff_size = sizeof(unsigned char) * result_buff_len;

    unsigned char *buff = (unsigned char *)realloc(str->characters, raw_buff_size + sizeof(unsigned char));

    if (!buff)
    {
        DYNSTR_ERR_ALLOC_MEM;
    }

    unsigned char buff_cpy[buff_len];
    memcpy(buff_cpy, buff, buff_size);

    unsigned long from = 0;

    memcpy(buff, buff_cpy, sizeof(unsigned char) * at);
    from += at;

    memcpy(buff + from, text, text_size);
    from += text_len;

    memcpy(buff + from, buff_cpy + at, sizeof(unsigned char) * (buff_len - at));
    from += buff_len - at;

    memset(buff + from, 0, sizeof(unsigned char));

    str->characters = buff;
    str->length = result_buff_len;

    return DYNSTR_OK;
}

int _insert_at_start_(char *text, struct _dynstr_ *str)
{
    return _insert_at_(text, 0, str);
}

int _insert_at_end_(unsigned char *text, struct _dynstr_ *str)
{
    if (str->length == 0)
    {
        return _insert_at_(text, 0, str);
    }
    else
    {
        return _insert_at_(text, str->length, str);
    }
}

int _insert_(unsigned long at, char *text, struct _dynstr_ *str)
{
    if (at > str->length && str->length > 0)
    {
        return DYNSTR_ILLEGAL_INDEX;
    }

    if (at == 0)
    {
        return _insert_at_start_(text, str);
    }
    else if (at == str->length)
    {
        return _insert_at_end_(text, str);
    }
    else
    {
        return _insert_at_(text, at, str);
    }
}

struct _dynstr_ *dynstr_empty(int *err)
{
    struct _dynstr_ *str = (struct _dynstr_ *)malloc(sizeof(struct _dynstr_));

    if (!str)
    {
        _set_err_(err, DYNSTR_ERR_ALLOC_MEM);
        return NULL;
    }

    str->length = 0;
    str->characters = NULL;

    return str;
}

struct _dynstr_ *dynstr_create(unsigned char *text, int *err)
{
    struct _dynstr_ *str = dynstr_empty(err);

    if (_insert_(0, text, str))
    {
        free(str);

        _set_err_(err, DYNSTR_ERR_ALLOC_MEM);
        return NULL;
    }

    _set_err_(err, DYNSTR_OK);
    return str;
}

int dynstr_set(unsigned char *text, struct _dynstr_ *str)
{
    const unsigned long text_len = strlen(text);
    const unsigned long text_size = sizeof(unsigned char) * text_len;

    unsigned char *buffer = realloc(str->characters, text_size + sizeof(unsigned char));

    if (!buffer)
    {
        return DYNSTR_ERR_ALLOC_MEM;
    }

    memcpy(buffer, text, text_size);
    memset(buffer + text_len, 0, sizeof(unsigned char));

    str->characters = buffer;
    str->length = text_len;

    return DYNSTR_OK;
}

int dynstr_insert_at(unsigned char *text, unsigned long at, struct _dynstr_ *str)
{
    return _insert_(at, text, str);
}

unsigned char *dynstr_sub_str(unsigned long from, unsigned long to, struct _dynstr_ *str, int *err)
{
    return _sub_str_alloc_(from, to, str->characters, err);
}

void dynstr_destroy(struct _dynstr_ *str)
{
    if (!str)
    {
        return;
    }

    if (str->characters)
    {
        free(str->characters);
    }

    str->length = 0;
    str->characters = NULL;

    free(str);
}