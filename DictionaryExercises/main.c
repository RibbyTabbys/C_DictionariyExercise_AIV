#include <stdio.h>
#include "DictionaryExercise.h"

int main()
{
    struct dictionary *dict = dictionary_new(8);
    if (!dict)
    {
        printf("Failed to create dictionary\n");
        return 1;
    }

    dictionary_insert(dict, "key1", strlen("key1"), "value1");
    dictionary_insert(dict, "key2", strlen("key2"), "value2");
    dictionary_insert(dict, "key3", strlen("key3"), "value3");
    dictionary_insert(dict, "key4", strlen("key4"), "value4");
    dictionary_insert(dict, "key5", strlen("key5"), "value5");
    dictionary_insert(dict, "key6", strlen("key6"), "value6");
    dictionary_insert(dict, "key7", strlen("key7"), "value7");

    if (!dictionary_insert(dict, "key1", strlen("key1"), "value1_duplicate"))
    {
        printf("Failed to insert duplicate key\n");
    }

    const char *value = dictionary_get(dict, "key2", strlen("key2"));
    if (value)
    {
        printf("Value for key 'key2': %s\n", value);
    }
    else
    {
        printf("Key 'key2' not found\n");
    }

    if (dictionary_remove(dict, "key2", strlen("key2")))
    {
        printf("Key 'key2' removed successfully\n");
    }
    else
    {
        printf("Key 'key2' not found for removal\n");
    }

    dictionary_print(dict);

    dictionary_free(dict);

    return 0;
}
