#include "DictionaryExercise.h"
#include <stdio.h>


size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 8463;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

struct dictionary *dictionary_new(const size_t hashmap_size)
{
    struct dictionary *dict = malloc(sizeof(struct dictionary));
    if (!dict)
    {
        return NULL;
    }
    dict->hashmap_size = hashmap_size;
    dict->entries = calloc(dict->hashmap_size, sizeof(struct dict_entry *));
    if (!dict->entries)
    {
        free(dict);
        return NULL;
    }
    return dict;
}

void dictionary_print(struct dictionary *dict)
{
    for (size_t i = 0; i < dict->hashmap_size; i++)
    {
        printf("Index %zu: ", i);
        struct dict_entry *entry = dict->entries[i];
        while (entry)
        {
            printf("(%s, %s) -> ", entry->key, entry->value);
            entry = entry->next;
        }
        printf("NULL\n");
    }
}

void dictionary_free(struct dictionary *dict)
{
    if (!dict)
    {
        return;
    }

    for (size_t i = 0; i < dict->hashmap_size; i++)
    {
        struct dict_entry *current = dict->entries[i];
        while (current)
        {
            struct dict_entry *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(dict->entries);
    free(dict);
}

struct dict_entry *dictionary_search(struct dictionary *dict, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % dict->hashmap_size;
    struct dict_entry *current = dict->entries[index];

    while (current)
    {
        if (current->key_len == key_len && strncmp(current->key, key, key_len) == 0)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

int dictionary_insert(struct dictionary *dict, const char *key, const size_t key_len, const char *value)
{
    if (dictionary_search(dict, key, key_len))
    {
        return 0;
    }

    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % dict->hashmap_size;
    struct dict_entry *head = dict->entries[index];

    struct dict_entry *new_entry = malloc(sizeof(struct dict_entry));
    if (!new_entry)
    {
        return 0; 
    }
    new_entry->key = key;
    new_entry->key_len = key_len;
    new_entry->value = value;
    new_entry->next = head;
    dict->entries[index] = new_entry;

    return 1;
}

const char *dictionary_get(struct dictionary *dict, const char *key, const size_t key_len)
{
    struct dict_entry *entry = dictionary_search(dict, key, key_len);
    return entry ? entry->value : NULL;
}

int dictionary_remove(struct dictionary *dict, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % dict->hashmap_size;
    struct dict_entry *head = dict->entries[index];
    struct dict_entry *prev = NULL;
    struct dict_entry *current = head;

    while (current)
    {
        if (current->key_len == key_len && strncmp(current->key, key, key_len) == 0)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                dict->entries[index] = current->next;
            }
            free(current);
            return 1; 
        }
        prev = current;
        current = current->next;
    }

    return 0;
}
