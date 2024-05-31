#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#include <string.h>

struct dict_entry
{
    const char *key;
    size_t key_len;
    const char *value;
    struct dict_entry *next;
};

struct dictionary
{
    struct dict_entry **entries;
    size_t hashmap_size;
};

struct dictionary *dictionary_new(const size_t hashmap_size);
void dictionary_print(struct dictionary *dict);
void dictionary_free(struct dictionary *dict);
int dictionary_insert(struct dictionary *dict, const char *key, const size_t key_len, const char *value);
const char *dictionary_get(struct dictionary *dict, const char *key, const size_t key_len);
int dictionary_remove(struct dictionary *dict, const char *key, const size_t key_len);

#endif /* DICTIONARY_H */
