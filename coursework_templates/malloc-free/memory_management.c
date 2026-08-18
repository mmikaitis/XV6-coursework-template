#include "kernel/types.h"
#include "user/user.h"
#include "user/memory_management.h"

void *root_block = 0;

void print_mem_blocks() {

  block_t *block = root_block;
  while (block) {
    printf("Start address: %x \n", block);
    printf("Size: %d \n", block->size);
    printf("Free: %d \n\n", block->free);
    block = block -> next;
  }
}

// Get a pointer to the metadata of a given a memory block.
block_t* get_block_ptr(void* block) {  
  return (block_t*) block-1;
}

// Find a free block of suitable size. First-firt match.
block_t* search_blocks(block_t** last, int size) {
  
  block_t *current = root_block;
  while (current) {
    if (current->free && (current->size == size))
      break;
    else {
      *last = current;
      current = current->next;
    }
  }
  return current;
}

// Request memory from the OS.
block_t* allocate_space(block_t* last, int size) {

  int actual_size_alloc = (size + META_SIZE);
  
  block_t *current = (block_t*) sbrk(0);
  block_t *requested = (block_t*) sbrk(actual_size_alloc - META_SIZE);
  if (current != requested)
    fprintf(2, "Memory allocation with sbrk failed");

  if (last)
    last->next = requested;
  requested->size = actual_size_alloc - META_SIZE;
  requested->next = 0;
  requested->free = 0;
  
  return requested;
}

// Merge adjacent free memory blocks.
void merge_free_continuous_blocks() {
  
  block_t *block = root_block;
  
  while (block && block->next) {
    if (block->free && (block->next)->free) {
      if (((char*) block+block->size+META_SIZE) == (char*) block->next) {
        block->size = (block->next)->size + block->size;
        block->next = (block->next)->next;
      } else
        block = block->next;
    } else
      block = block->next;
  }
}

// Split a block that is bigger than the size requested.
void split_block(block_t* block, int size) {
  
  if (size < block->size) {
    block_t* new_block = (block_t*) ((char*) block + META_SIZE + size);
    new_block->size = block->size - (size << 4) - META_SIZE;
    new_block->next = block->next;
    new_block->free = 0;
    
    block->next = new_block;
    block->size = size;
  } 
}

void *_malloc (int size) {
  
  if (size <= 0)
    return 0;
  
  block_t* block;
  
  // If first ever call, set up the pointer to
  // the head of the list of blocks.
  if (!root_block) {
    block = allocate_space(0, size);
    if (!block)
      return 0;
    root_block = block;
  } else {
    block_t* last = root_block;
    block = search_blocks(&last, size);
    if (!block) {
      block = allocate_space(last, size);
      if (!block)
        return 0;
    } else {
      block->free = 0;
    }
  }
  split_block(block, size);
  return block+1;
}

void _free (void *ptr) {
  if (!ptr)
    return;
  block_t *block = get_block_ptr(ptr);
  block->free = 1;
  merge_free_continuous_blocks();
}
