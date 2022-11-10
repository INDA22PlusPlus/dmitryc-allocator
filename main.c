#include <stdio.h>
#include <stdlib.h>

// A struct representing a Linear Allocator
struct Lal {
    size_t size;
    int ptr;
    unsigned char bytes[];
};

// Constructs and returns a Lal (a struct representing a Linear Allocator) based on given size
struct Lal conLal(size_t size) {
    struct Lal lal;
    lal.size = size;
    lal.ptr = 0;
    return lal;
}

// Allocates memory using a Linear Allocator
void lalloc(struct Lal *lal, unsigned char bytes[], size_t size) {

//    printf("Lal size: %llu \n", lal->size);
//    printf("Lal ptr: %d \n", lal->ptr);
//
//    printf("Bytes size: %llu \n", size);


    if (lal->ptr + size <= lal->size) {
        for (int i = 0; i < size; i++) {
            lal->bytes[lal->ptr] = bytes[i];

//            printf("%d \n", lal->ptr);
//            printf("%d \n", lal->bytes[i]);
//            printf("%d \n", bytes[i]);

            lal->ptr++;
        }
    }
    else {
        printf("Bytes array larger than space left in the allocator: \n");
        printf("\t Allocator pointer at: %d \n", lal->ptr);
        printf("\t Allocator size: %llu \n", lal->size);
        printf("\t Allocator space left: %llu \n", lal->size - lal->ptr);
        printf("\t Bytes array size: %llu \n\n", size);
    }
}

// Prints
void printLal(struct Lal *lal) {
    const int sections = 40;
    const char filledChar = '#';

    int filled = (int) (((float) lal->ptr / (float) lal->size) * sections);
    int filledPercent = (int) ((float) filled / (float) sections * 100);
    int rest = sections - filled;

    printf("Filled: %d%% \n", filledPercent);
    printf("[");
    for(;filled--;printf("%c", filledChar));
    for(;rest--;printf("%c", ' '));
    printf("] \n\n");

//    printf("ptr: %d \n", lal->ptr);

    printf("Filled bytes: \n");
    for (int i = 0; i < lal->ptr; i++) {
        printf("\t Byte %d: %d \n", i + 1, lal->bytes[i]);
    }
}


int main() {
    struct Lal lal = conLal(sizeof(int) + 1);
//    lal.bytes[1] = ;
//    printf("%d \n", lal.bytes[1]);

//    printf("%d \n", lal.ptr);
//    printf("%d \n", lal.ptr);

    unsigned char bytes[] = {67, 57};

//    lalloc(lal, bytes, sizeof bytes);
    lalloc(&lal, bytes, sizeof bytes);
//    bytes[0] = 32;
//    bytes[1] = 44;
    lalloc(&lal, bytes, sizeof bytes);
    lalloc(&lal, bytes, sizeof bytes);
//    printf("%d", lal.ptr);
    printLal(&lal);

//    lput(lal, );

//    printf("%p \n", lal);

    return 0;
}
