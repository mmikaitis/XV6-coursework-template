#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

typedef struct block_t {
  struct block_t *next;
  int size;
  int free;
} block_t;

#define META_SIZE sizeof(block_t)

void print_mem_blocks();
block_t* get_block_ptr(void* block);
block_t* search_blocks(block_t** last, int size);
block_t* allocate_space(block_t* last, int size);
void merge_free_continuous_blocks();
void split_block(block_t* block, int size);
void* _malloc(int size);
void _free(void* block);

#endif
