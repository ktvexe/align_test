#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define NUM 5000000
#define measure(type,struct_ptr,name,verbose) \
    for(int loop = 0;loop<100;loop++){ \
        clock_gettime(CLOCK_REALTIME, &start); \
        for (int i = 0; i < NUM; i++) { \
            ptr = (((char *)struct_ptr)+(64* (i%64))); \
            if(verbose) printf("%s:  %p\n",name,ptr); \
            ((type *)ptr) -> b =1; \
            ((type *)ptr) -> b +=1; \
        }   \
        clock_gettime(CLOCK_REALTIME, &end);    \
        count += diff_in_us(start, end);    \
    }   \
    printf("%s: \t\t %lf us\n",name, count /100.0); \
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

    //alloc 4K size for each struct
    align = malloc(4096);
    small = malloc(4096);
    non = malloc(4096);
    
    printf("size of align : %ld\n",sizeof(*align));
    printf("size of small : %ld\n",sizeof(*small));
    printf("size of non : %ld\n",sizeof(*non));

    measure(struct align_struct,align,"align",0);
    measure(struct small_align_struct,small,"small",0);
    measure(struct non_align_struct,non,"non",0);

}
