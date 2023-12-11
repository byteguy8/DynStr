#ifndef _DYNSTR_H_
#define _DYNSTR_H_

struct _dynstr_
{
    unsigned long length;
    unsigned char *characters;
};

typedef struct _dynstr_ *DynStr;

struct _dynstr_ *dynstr_empty(int *err);

struct _dynstr_ *dynstr_create(unsigned char *text, int *err);

int dynstr_set(unsigned char *text, struct _dynstr_ *str);

int dynstr_insert_at(unsigned char *text, unsigned long at, struct _dynstr_ *str);

char *dynstr_sub_str(unsigned long from, unsigned long to, struct _dynstr_ *str, int *err);

void dynstr_destroy(struct _dynstr_ *str);

#define dynstr_print(str) (str->characters)

#define dynstr_char_at(index, str) (str->characters[index])

#define dynstr_insert_start(text, str) (dynstr_insert_at(text, 0, str))

#define dnystr_insert_end(text, str) (dynstr_insert_at(text, str->length, str))

#define dynstr_append(text, str) (dnystr_insert_end(text, str))

#endif