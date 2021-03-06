#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define TEST_NUM 4*1024*1024
//#define TEST_NUM 5000000
/*4M page*/
#define PAGE 4*1024*1024
/*Run 100 times for average*/
#define AVGTIMES 100
/*Shift to avoid cache line prefetching*/
#define OFFSET 64

#define measure(type,struct_ptr,verbose)                            \
    for(int loop = 0;loop<AVGTIMES;loop++){                         \
        clock_gettime(CLOCK_REALTIME, &start);                      \
        for (int i = 0; i < TEST_NUM; i++) {                        \
            ptr = (((char *)struct_ptr)+(64* (i%(PAGE/OFFSET))));   \
            if(verbose) printf(""#struct_ptr":  %p\n",ptr);         \
            ((type *)ptr) -> b =1;                                  \
            ((type *)ptr) -> b +=1;                                 \
        }                                                           \
        clock_gettime(CLOCK_REALTIME, &end);                        \
        count += diff_in_us(start, end);                            \
    }                                                               \
    printf(""#struct_ptr": \t\t %lu us\n", count / AVGTIMES);       \
    count = 0;

struct align_struct{
    char a;
    long b;
    short c;
};

struct small_align_struct{
    long b;
    char a;
    short c;
};

struct non_align_struct{
    char a;
    short c;
    long b;
}__attribute__((packed, aligned(1)));

static long diff_in_us(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec * 1000000.0 + diff.tv_nsec / 1000.0);
}

int main(){

    struct align_struct *align;
    struct small_align_struct *small;
    struct non_align_struct *non;
    struct timespec start, end;
    void *ptr;
    unsigned long count = 0;

    /*alloc page size for each struct*/
    align = malloc(PAGE);
    small = malloc(PAGE);
    non = malloc(PAGE);
    
    printf("size of align : %ld\n",sizeof(*align));
    printf("size of small : %ld\n",sizeof(*small));
    printf("size of non : %ld\n",sizeof(*non));

    measure(struct align_struct,align,0);
    measure(struct small_align_struct,small,0);
    measure(struct non_align_struct,non,0);

}
