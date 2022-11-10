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

    // Debugging
//    printf("Lal size: %llu \n", lal->size);
//    printf("Lal ptr: %d \n", lal->ptr);
//
//    printf("Bytes size: %llu \n", size);

    // Checks if the given bytes array fits in the allocator, otherwise prints error message
    if (lal->ptr + size <= lal->size) {
        // Allocates the bytes
        for (int i = 0; i < size; i++) {
            lal->bytes[lal->ptr] = bytes[i];

            // Debugging
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

// Deallocates memory using a Linear Allocator
void delalloc(struct Lal *lal, unsigned char bytes[], size_t size) {

}

// Reallocates memory using a Linear Allocator
void relalloc(struct Lal *lal, unsigned char bytes[], size_t size) {

}

// Resets memory to an empty Linear Allocator
void lreset(struct Lal *lal) {

}

// Prints the filled elements of a Linear Allocator, with current fill level
void printLal(struct Lal *lal) {
    const int sections = 40;
    const char filledChar = '#';

    int filled = (int) (((float) lal->ptr / (float) lal->size) * sections);
    int filledPercent = (int) ((float) filled / (float) sections * 100);
    int rest = sections - filled;

    // TODO: Fix this mess
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
    // Testing the Linear Allocator
    struct Lal lal = conLal(sizeof(int) + 1);

    unsigned char bytes[] = {67, 57};

    lalloc(&lal, bytes, sizeof bytes);
    lalloc(&lal, bytes, sizeof bytes);
    lalloc(&lal, bytes, sizeof bytes);

    printLal(&lal);

    return 0;
}
