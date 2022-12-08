// hashtable.c - Implement a hashtable using robinhood probing
// TODO: Dynamic resize of table
#include "hashtable.h"

#define T htbl_T

typedef struct tbl_entry
{
    const char *key;
    void *value;
    unsigned int _psl;  // Probe sequence length - offset from optimal hash
} tbl_entry;


struct T {
    struct tbl_entry* entries;
    size_t capacity;
    size_t population; /* Total number of entries currently hashed */

    unsigned int _lpsl;            /* Longest Probe Sequence Length - bounds searches */
    unsigned int _avg_probe_depth; /* Smart search optimization */
    float _load_factor;            /* Ratio of population to capacity */
};


void htbl_print_keys(T htbl)
{
    printf("Printing Keys Start\n");
    for(int i = 0; i < htbl->capacity; i++)
    {
        if(htbl->entries[i].key)
        {
            printf("Key %i: %s\n", i, htbl->entries[i].key);
        }
    }
    printf("Printing Keys Ends\n");
}

/* 
 *   http://www.cse.yorku.ca/~oz/hash.html
 *   https://cs.uwaterloo.ca/research/tr/1986/CS-86-14.pdf
 *
 *  The original paper talks about utilizing a hash function of the form
 *  'h(k,i)' where k is the key and i is the probe position. Within the
 *  algorithms this hash function is continuously called whenever the
 *  value stored at the hash is not the thing being looked for. This seems
 *  excessive given the change to the hash is incrementing or decrementing
 *  depending on which algorithm is utilizing it.
*/
static unsigned long
hash(const char *key)
{
    unsigned long hash = 5381;
    int c;
    
    while ( (c = *key++) ) { hash = ((hash << 5) + hash) + c; }
    return hash;
}


/* Helper function for replacing entries during insert */
static void
_swap(tbl_entry *A, tbl_entry *B)
{
    tbl_entry temp = *A;
    *A = *B;
    *B = temp;
}


static void
_update_meta_info(T htbl)
{
    float psl_sum = 0;     // Float to avoid automatic boxing
    htbl->population = 0;

    for(unsigned int idx = 0; idx < htbl->capacity; idx++)
    {
        if(htbl->entries[idx].key) { 
            psl_sum += htbl->entries[idx]._psl;
            htbl->_lpsl = htbl->entries[idx]._psl < htbl->_lpsl ? htbl->_lpsl : htbl->entries[idx]._psl;
            htbl->population++;
        }
    }
    htbl->_avg_probe_depth = (int)ceilf( psl_sum / htbl->population);
    htbl->_load_factor = (float)htbl->population / htbl->capacity;
}


static int
_find_index(const T htbl, const char *key)
{
    signed short int backward_offset = htbl->_avg_probe_depth;
    unsigned int forward_offset = backward_offset + 1;

    /* Smart Search */
    while(backward_offset >= 0 && forward_offset <= htbl->_lpsl){
        if(strcmp(htbl->entries[backward_offset].key, key) == 0){
            return backward_offset;
        }
        if(strcmp(htbl->entries[forward_offset].key, key) == 0){
            return forward_offset;
        }
        backward_offset--;
        forward_offset++;
    }
    /* Decay to linear search of remaining space */
   for(;backward_offset >= 0; backward_offset--){
        if(htbl->entries[backward_offset].key && (strcmp(htbl->entries[backward_offset].key, key) == 0)){
            return backward_offset;
        }
    }
    // TODO: Implement bounding search by lpsl
    for(;forward_offset < htbl->capacity; forward_offset++){
        if(htbl->entries[forward_offset].key && (strcmp(htbl->entries[forward_offset].key, key) == 0)){
            return forward_offset;
        }
    }
    return -1;
}


/**
 * @brief 
 * 
 * @param htbl 
 * @param key 
 * @param item 
 * @return int 1 if item was added, 0 if item was updated, and -1 if error.
 */
static int
_put(tbl_entry *entries, unsigned int arr_size, const char *key, void *item)
{
    if(key == NULL)
    {
        fprintf(stderr,"Unable to add NULL key to htbl\n");
        return -1;
    }

    unsigned long idx = hash(key) % arr_size;
    tbl_entry curr_item = {.key = key, .value = item, ._psl = 0};
  
    while(entries[idx].value != NULL)
    {
        if(strcmp(entries[idx].key, curr_item.key) == 0)
        {
            entries[idx].value = curr_item.value;
            return 0;
        }

        if(curr_item._psl > entries[idx]._psl)
        {
            _swap(&curr_item, &entries[idx]);
        }
        curr_item._psl++;
        idx = (idx + 1) % arr_size;  /* Wrap when at end of array */
    }
    _swap(&curr_item, &entries[idx]);
    return 1;
}


static void
_reset_entry(tbl_entry *entry)
{
        entry->key = NULL;
        entry->value = NULL;
        entry->_psl = 0;
}


/**
 * @brief Helper function to resize and rehash arrays
 * 
 * @param htbl Pointer to hashtable to resize
 * @return unsigned 
 */
static unsigned int
_resize(T htbl)
{
    size_t new_size = htbl->population * 2;
    tbl_entry *new_entries;
    
    if(new_size <= htbl->population) /* Unsigned int effectively overflowed - C18 std 6.2.5.9  */
    {
        fprintf(stderr,"Internal error - New size must be larger than the current size.\n");
        return 0;
    }

    if( (new_entries = calloc(new_size, sizeof(tbl_entry))) ==  NULL)
    {
        fprintf(stderr,"Unable to generate new array for resizing\n");
        return 0;
    }

    for(unsigned int idx = 0; idx < htbl->population; idx++)
    {
        _put(new_entries, new_size, htbl->entries[idx].key, htbl->entries[idx].value);
        _reset_entry(&htbl->entries[idx]);
    }
    free(htbl->entries);
    htbl->entries = new_entries;
    htbl->capacity = new_size;

    return new_size;
}


/* Constructor for new htbl */
T
htbl_new(const unsigned int capacity)
{
    if(capacity <= 0)
    {
        // Only potential issue where errno is not set by the calling method
        fprintf(stderr,"Table capacity must be a non-zero positive integer\n");
        return NULL;
    }

    struct T *htbl = malloc(sizeof(struct T));
    if(!htbl) return NULL;

    htbl->capacity = capacity;
    htbl->entries = calloc(htbl->capacity, sizeof(struct tbl_entry));
    if(!htbl->entries)
    {
        free(htbl);
        htbl = NULL;
    }
    else
    {
        htbl->_lpsl = 0;
        htbl->population = 0;
    }
    return htbl;
}


void
htbl_free(T *htbl)
{
    for(int idx = 0; idx < (int)(*htbl)->capacity; idx++)
    {
        (*htbl)->entries[idx].key = NULL;
        (*htbl)->entries[idx].value = NULL;
        (*htbl)->entries[idx].key = NULL;
    }
    free((*htbl)->entries);
    (*htbl)->entries = NULL;

    free((*htbl));
    *htbl = NULL;
}

int
htbl_put(T htbl, const char *key, void *item)
{
    int result = _put(htbl->entries, htbl->capacity, key, item);
    _update_meta_info(htbl);

    if(htbl->_load_factor > LOAD_FACTOR_THRESHOLD)
    {
        _resize(htbl);
        _update_meta_info(htbl);
    }
    return result;
}


void*
htbl_find(const T htbl, const char *key)
{
    int idx = _find_index(htbl, key);
    if(idx == -1) { return NULL; }
    else { return htbl->entries[idx].value; }
}

void* htbl_remove(T htbl, const char *key)
{
    void* evicted;
    int idx = _find_index(htbl, key);

    if(idx == -1) {
        fprintf(stderr,"ERROR: Key \"%s\" does not exist\n", key);
        return NULL;
    }
    evicted = htbl->entries[idx].value;

    htbl->entries[idx]._psl = 0;
    htbl->entries[idx].value = NULL; // Item isn't malloced so shouldn't need to free
    htbl->entries[idx].key = NULL;

    idx = (idx + 1) % htbl->capacity;
    tbl_entry curr_item = htbl->entries[idx];

    // From the initial index, iterate forward shifting items back one until an item
    // whose already optimally hashed is encountered.
    while(curr_item._psl != 0)
    {
        curr_item._psl--;
        if(idx == 0) { _swap(&curr_item, &htbl->entries[htbl->capacity - 1]); }
        else         { _swap(&curr_item, &htbl->entries[idx - 1]); }
    }
    _update_meta_info(htbl);
    return evicted;
}

unsigned int htbl_capacity(const T tbl) { return tbl->capacity; }