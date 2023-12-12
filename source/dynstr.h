// DynStr 1.0.0

#ifndef _DYNSTR_H_
#define _DYNSTR_H_

/**
 * @brief Very basic mutable string.
 *
 */
struct _dynstr_
{
    unsigned long length;      // The length of characters (not inclunding the NULL char at end)
    unsigned char *characters; // Valid C string (with NULL char at end).
};

typedef struct _dynstr_ *DynStr; // Pointer to a dynstr structre.

/**
 * @brief Creates a empty string.
 *
 * @param err Pointer updated with the status result.
 * A positive number in case of error, zero otherwise.
 * this parameter can be NULL.
 * @return NULL, in case of error, a pointer to
 * the dynstr structure, otherwise.
 */
struct _dynstr_ *dynstr_empty(int *err);

/**
 * @brief Creates a populated string.
 *
 * @param text The text used to populate dynstr. Must not be NULL.
 * @param err Pointer updated with the status result.
 * A positive number, indicating the error (if any), zero otherwise.
 * this parameter can be NULL.
 * @return NULL, in case of error, a pointer to
 * the dynstr structure, otherwise.
 */
struct _dynstr_ *dynstr_create(unsigned char *text, int *err);

/**
 * @brief Replace the current content of the string
 * with a new one.
 *
 * @param text The text that will replace the current
 * int the string. Must not be NULL.
 * @param str Pointer to the dynstr structure. Must not be NULL.
 * @return A positive number, indicating the error (if any), zero otherwise.
 */
int dynstr_set(unsigned char *text, struct _dynstr_ *str);

/**
 * @brief Insert the given text in the given place specified
 * by 'at' parameter. The character in the position specified
 * by 'at', will be moved forward. This function can be called in
 * a empty string, but 'at' must be 0 in that case. To insert
 * something at end of populated string, specify the length of the string
 *
 * @param text The text to be inserted. Must not be NULL.
 * @param at The position from which insert the text. This parameter
 * should range from 0 to str's length, inclusive.
 * @param str Pointer to the dynstr structure. Must not be NULL.
 * @return A positive number, indicating the error, if 'at' is
 * greater than dynstr length. Zero otherwise.
 */
int dynstr_insert_at(unsigned char *text, unsigned long at, struct _dynstr_ *str);

/**
 * @brief Creates a sub string from the specified range. The length of
 * the dynstr must be greater than zero.
 *
 * @param from Specify where the sub string starts (inclusive).
 * @param to Specify where the sub string ends (inclusive).
 * @param str Pointer to a dynstr structure from which create
 * the sub string. Must not be NULL.
 * @param err Pointer updated with the status result.
 * A positive number, indicating the error (if any), zero otherwise.
 * this parameter can be NULL.
 * @return NULL, if 'from' is greater than 'to', 'to' equals or greater than
 * dynstr size, or failed to allocate memory for the sub string. Otherwise, a
 * pointer of type unsiged char (not a dynstr structure).
 */
unsigned char *dynstr_sub_str(unsigned long from, unsigned long to, struct _dynstr_ *str, int *err);

/**
 * @brief Destroys the dynstr structure, freeing any allocated resource.
 *
 * @param str Pointer to the dynstr structure. Can be NULL.
 */
void dynstr_destroy(struct _dynstr_ *str);

/**
 * @brief Returns a valid C string from the dynstr structre.
 * Parameter must be valid.
 *
 */
#define dynstr_print(str) (str->characters)

/**
 * @brief Returns a char at the given 'index' position.
 * Parameters must be valid. Index must range from 0 (inclusive)
 * to dynstr length (not inclusive).
 *
 */
#define dynstr_char_at(index, str) (str->characters[index])

/**
 * @brief Insert 'text' at the start of dynstr. Either 'text' and
 * str must not be NULL. It's ok to call on empty dynstr.
 *
 */
#define dynstr_insert_start(text, str) (dynstr_insert_at(text, 0, str))

/**
 * @brief Insert 'text' at the end of dynstr (at start if
 * dynstr is empty). Either 'text' and str must not be NULL.
 * It's ok to call on empty dynstr.
 *
 */
#define dnystr_insert_end(text, str) (dynstr_insert_at(text, str->length, str))

/**
 * @brief The same as 'dnystr_insert_end'. So, the same rules applies.
 *
 */
#define dynstr_append(text, str) (dnystr_insert_end(text, str))

#endif