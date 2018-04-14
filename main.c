#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define NUM 5000000
#define measure(structure,name) \
    clock_gettime(CLOCK_REALTIME, &start); \
    for (int i = 0; i < NUM; i++) { \
        structure.b = 1;    \
        structure.b += 1;   \
    }   \
    clock_gettime(CLOCK_REALTIME, &end);    \
    printf("%s: \t\t %ld us\n",name, diff_in_us(start, end));


struct align_struct{
    char a;
    int b;
    short c;
};

struct small_align_struct{
    int b;
    char a;
    short c;
};

struct non_align_struct{
    char a;
    short c;
    int b;
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

    struct align_struct align;
    struct small_align_struct small;
    struct non_align_struct non;
    struct timespec start, end;
    printf("size of align : %ld\n",sizeof(align));
    printf("size of small : %ld\n",sizeof(small));
    printf("size of non : %ld\n",sizeof(non));

    measure(align,"align");
    measure(small,"small");
    measure(non,"non");

}
