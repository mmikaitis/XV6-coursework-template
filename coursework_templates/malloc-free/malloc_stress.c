#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#include "user/memory_management.h"

#ifndef NULL
#define NULL 0
#else
#endif

#define N_NULL 0

#define USER_MALLOC _malloc
#define USER_FREE _free

void test_malloc_not_null(){
  printf("test_malloc_not_null");
  close(1);

	void * ptr = USER_MALLOC(4097);

  if(ptr==N_NULL){
    exit(-1);
  }

	void * ptr1 = USER_MALLOC(1);
  if(ptr1==N_NULL){
    exit(-1);
  }

	void * ptr2 = USER_MALLOC(100);

  if(ptr2==N_NULL){
    exit(-1);
  }

  exit(0);
}

void test_malloc_null(){
  printf("test_malloc_null");
  close(1);

  void * ptr = USER_MALLOC(0);

  if(ptr!=N_NULL){
    USER_FREE(ptr);
  }

  void * ptr1 = USER_MALLOC(100);

  if(ptr1==N_NULL){
    printf("malloc(100) return null ptr (2).\n");
    exit(-1);
  }

  void * ptr2 = USER_MALLOC(0);

  if(ptr2!=N_NULL){
    USER_FREE(ptr);
  }
  exit(0);
}

void test_malloc_sbrk(){
  printf("test_malloc_sbrk");
  close(1);

  void * before_ptr = sbrk(0);
  void * malloc_ptr = USER_MALLOC(100);
  void * after_ptr = sbrk(0);
  if(before_ptr >= after_ptr) {
      exit(-1);
  }

  if(malloc_ptr < before_ptr  || malloc_ptr > after_ptr){
    exit(-1);
  }
  exit(0);
}

void test_malloc_ptr(){
  printf("test_malloc_ptr");
  close(1);

  void * ptr = USER_MALLOC(100);
	void * ptr1 = USER_MALLOC(100);
	if(ptr1< ptr+100){
    exit(-1);
  }
  exit(0);
}

void test_malloc_massive(){
  printf("test_malloc_massive");
  close(1);

  char * before_ptr = sbrk(0);
  char * ptr = USER_MALLOC(8190);
  char * after_ptr = sbrk(0);
  if(after_ptr - before_ptr < 8190){
    exit(-1);
  }
  if(ptr< before_ptr){
    exit(-1);
  }
  exit(0);
}

void test_malloc_too_much(){
  printf("test_malloc_too_much");
  close(1);


  char * before_ptr = sbrk(0);
  USER_MALLOC(100);
  char * after_ptr = sbrk(0);
  if(after_ptr - before_ptr > 65536){
    exit(-1);
  }

  exit(0);
}

void test_malloc_align(){
  printf("test_malloc_align");
  close(1);

	char * ptr = USER_MALLOC(10);
	char * ptr1 = USER_MALLOC(3);

  if (((long) ptr) % 4 != 0){
    exit(-1);
  }
  if (((long) ptr1) % 4 != 0){
    exit(-1);
  }
  exit(0);
}

void test_alloc(){
  printf("test_alloc");

  void * ptr = USER_MALLOC(100);
  USER_FREE(ptr);
  exit(0);
}

void test_alloc_null_ptr(){
  printf("test_alloc_null_ptr");
  close(1);

  void * ptr = USER_MALLOC(0);
	USER_FREE(ptr);
  exit(0);
}

void test_alloc_give_back(){
  printf("test_alloc_give_back");
  close(1);

  void * ptr = USER_MALLOC(8190);
	void * before_ptr = sbrk(0);
	USER_FREE(ptr);
	void * after_ptr = sbrk(0);
	if(after_ptr >= before_ptr){
    exit(-1);
  }

  exit(0);
}

void test_next_merge_space_0(){
  printf("test_next_merge_space_0");
  close(1);

  void * ptr_0 = USER_MALLOC(1000);
	void * ptr_1 = USER_MALLOC(1000);
	void * ptr_2 = USER_MALLOC(1000);
	USER_FREE(ptr_1);
	USER_FREE(ptr_0);
	void * ptr_3 = USER_MALLOC(1500);

  if(ptr_3 > ptr_2){
    exit(-1);
  }

  if(ptr_3 > ptr_1){
    exit(-1);
  }

  if(ptr_3 < ptr_0){
    exit(-1);
  }

  exit(0);
}

void test_prev_merge_space_1(){
  printf("test_prev_merge_space_1");
  close(1);

  void * ptr_0 = USER_MALLOC(1000);
	void * ptr_1 = USER_MALLOC(1000);
	void * ptr_2 = USER_MALLOC(1000);
	USER_FREE(ptr_0);
	USER_FREE(ptr_1);
	void * ptr_3 = USER_MALLOC(1500);
  if(ptr_3 > ptr_2){
    exit(-1);
  }

  if(ptr_3 > ptr_1){
    exit(-1);
  }

  if(ptr_3 < ptr_0){
    exit(-1);
  }

  exit(0);
}

void test_prev_next_merge_space_2(){
  printf("test_prev_next_merge_space_2");
//  close(1);

  void * ptr_0 = USER_MALLOC(1000);
	void * ptr_1 = USER_MALLOC(1000);
	void * ptr_2 = USER_MALLOC(1000);
	USER_FREE(ptr_2);
	USER_FREE(ptr_0);
	USER_FREE(ptr_1);
	void * ptr_3 = USER_MALLOC(1500);

	if(ptr_3 > ptr_2){
    exit(-1);
  }

  if(ptr_3 > ptr_1){
    exit(-1);
  }


  if(ptr_3 < ptr_0 ){
    exit(-1);
  }

  exit(0);
}

void test_merge_space_3(){
  printf("test_merge_space_3");
  close(1);

  char * ptr_0 = USER_MALLOC(1000);
	char * ptr_1 = USER_MALLOC(1000);
	char * ptr_2 = USER_MALLOC(1000);
	USER_FREE(ptr_0);
	USER_FREE(ptr_1);
	USER_FREE(ptr_2);

  char * ptr_3 = USER_MALLOC(2700);
	char * after_ptr = sbrk(0);

  if(ptr_3 < ptr_0){
    exit(-1);
  }

  if(ptr_3 >= ptr_1){
    exit(-1);
  }
  if(ptr_3 + 2700 > after_ptr){
    exit(-1);
  }

  exit(0);
}

void test_reuse_space(){
  printf("test_reuse_space");
  close(1);

  void * ptr_0 = USER_MALLOC(1000);
  void * ptr_1 = USER_MALLOC(1000);
  USER_MALLOC(1000);
  USER_FREE(ptr_0);

  void * ptr_3 = USER_MALLOC(100);
  if(ptr_3 < ptr_0 || ptr_3 >= ptr_1){
    exit(-1);
  }
  exit(0);
}

void test_split_space(){
  printf("test_split_space");
  close(1);

	void * ptr_0 = USER_MALLOC(1000);
  void * ptr_1 = USER_MALLOC(1000);
  USER_MALLOC(1000);
  USER_FREE(ptr_0);

	void * ptr_3 = USER_MALLOC(100);
if(ptr_3 < ptr_0 || ptr_3 >= ptr_1){
    exit(-1);
  }
	void * ptr_4 = USER_MALLOC(100);
if(ptr_4 < ptr_0 || ptr_4 >= ptr_1){
    exit(-1);
  }
}

void test_sbrk_opt(){
  printf("test_sbrk_opt");
  close(1);

  char * pre = sbrk(0);
	USER_MALLOC(32);
	char * post = sbrk(0);
  if((post - pre) != 0x1000){
    exit(-1);
  }
}


void (*test_func[17])() =
    {
      test_malloc_not_null,
      test_malloc_null,
      test_malloc_sbrk,
      test_malloc_ptr,
      test_malloc_massive,
      test_malloc_too_much,
      test_malloc_align,
      test_alloc,
      test_alloc_null_ptr,
      test_alloc_give_back,
      test_next_merge_space_0,
      test_prev_merge_space_1,
      test_prev_next_merge_space_2,
      test_merge_space_3,
      test_reuse_space,
			test_split_space,
      test_sbrk_opt};

int
main(int argc, char *argv[])
{
  printf("Starting test suite...\n");

  for(int i = 0; i < 17; i++){
    void (*func_ptr)();

    func_ptr = test_func[i];


      if (fork() == 0){
        func_ptr();
      } else {
        int ret;
        int * ptr = &ret;
        //int c_pid =
        wait(ptr);

        if(ret==0){
          printf("\tPassed.....\n");
        } else {
          printf("\tFailed.....\n");
        }
      }



  }
    exit(0);
}
