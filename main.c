#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/// A struct representing a Linear Allocator
struct Lal {
    size_t size;
    int ptr;
    int lastAllocSize;
    unsigned char bytes[];
};

/// Constructs and returns a Lal (a struct representing a Linear Allocator) based on given size
struct Lal conLal(size_t size) {
    struct Lal lal;
    lal.size = size;
    lal.ptr = 0;
    lal.lastAllocSize = 0;
    return lal;
}

/// Checks if the given bytes array fits in the allocator
bool lalInBounds(struct Lal *lal, size_t size) {
    return lal->ptr + size <= lal->size;
}

/// Allocates memory as a Linear Allocator
void lalloc(struct Lal *lal, unsigned char bytes[], size_t size) {

    // Debugging
//    printf("Lal size: %llu \n", lal->size);
//    printf("Lal ptr: %d \n", lal->ptr);
//
//    printf("Bytes size: %llu \n", size);

    // Checks if the given bytes array fits in the allocator, otherwise prints error message
    if (lalInBounds(lal, size)) {
        lal->lastAllocSize = (int) size;
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

/// Deallocates the last allocated memory as a Linear Allocator
bool delalloc(struct Lal *lal) {
    if (lal->lastAllocSize) {
        lal->ptr = lal->ptr - lal->lastAllocSize;
        lal->lastAllocSize = 0;
        return 1;
    } else {
        printf("Can't deallocate when no previous allocations have been made! \n\n");
        return 0;
    }
}

/// Reallocates the last allocated memory as a Linear Allocator
void relalloc(struct Lal *lal, unsigned char bytes[], size_t size) {
    if (lalInBounds(lal, size)) {
        if (delalloc(lal)) {
            lalloc(lal, bytes, size);
        }
    }
}

/// Force deallocates the byte bellow the point, as long as there are bytes left in the Linear Allocator
bool forceDelalloc(struct Lal *lal) {
    if (lal->ptr) {
        lal->ptr--;
        if (lal->lastAllocSize) {
            lal->lastAllocSize--;
        }
        return 1;
    } else {
        printf("Can't deallocate when the allocation is empty! \n\n");
        return 0;
    }
}


/// Force reallocates the byte bellow the point, as long as there are bytes left in the Linear Allocator
void forceRelalloc(struct Lal *lal, unsigned char byte) {
    if (lalInBounds(lal, 1)) {
        if (forceDelalloc(lal)) {
            unsigned char bytes[1];
            bytes[0] = byte;
            lalloc(lal, bytes, 1);
        }
    }
}

/// Resets memory to an empty Linear Allocator
void lreset(struct Lal *lal) {
    lal->ptr = 0;
    lal->lastAllocSize = 0;
}

/// Gets the byte bellow the pointer from the Linear Allocator
unsigned char lget(struct Lal *lal) {
    // TODO: Fix the return, add check if pointer has values bellow
//    printf("ptr: %d, value:%d", lal->ptr, lal->bytes[lal->ptr - 1]);
    return lal->bytes[lal->ptr - 1];
}

/// Prints the filled elements of a Linear Allocator, with current fill level
void printLal(struct Lal *lal) {
    const int sections = 40;
    const char filledChar = '#';

    printf("Pointer at: byte %d \n", lal->ptr);
    printf("Size of the last allocation: %d bytes \n", lal->lastAllocSize);

    // Calculates percentage filled
    int filled = (int) ((float) lal->ptr / (float) lal->size * (float) sections);
    int filledPercent = (int) ((float) filled / (float) sections * 100);
    int rest = sections - filled;

    // TODO: Fix this mess
    // Prints percentage filled
    printf("Filled: %d%% \n", filledPercent);
    printf("[");
    for(;filled--;printf("%c", filledChar));
    for(;rest--;printf("%c", ' '));
    printf("] \n\n");

    printf("Filled bytes: \n");
    for (int i = 0; i < lal->ptr; i++) {
        printf("\t Byte %d: %d \n", i, lal->bytes[i]);
    }
    printf("\n");
}

/// A struct representing an Arena Allocator
// (Most likely going to be replaced with mate allocator)
struct Aal {
    unsigned char* ptr;
    unsigned char bytes[4096];
};

/// Constructs and returns an Arena Allocator based on given size
struct Aal conAal() {
    struct Aal aal;
    aal.ptr = aal.bytes;
    return aal;
}

/// Mate (Buddy) Allocator (coming soon™)
struct Mal {

};

int main() {
    // Testing the Linear Allocator
    struct Lal lal = conLal(sizeof(int) * 20);

    unsigned char bytes[] = {67, 57, 23, 145};

    lalloc(&lal, bytes, sizeof bytes);
    lalloc(&lal, bytes, sizeof bytes);
    lalloc(&lal, bytes, sizeof bytes);

    printLal(&lal);

    bytes[0] = 0;
    bytes[1] = 0;
    bytes[2] = 0;
    bytes[3] = 0;

//    delalloc(&lal);
    relalloc(&lal, bytes, sizeof bytes);
    delalloc(&lal);
    relalloc(&lal, bytes, sizeof bytes);

    printf("Get value at current pointer: %d \n\n", lget(&lal));

    printLal(&lal);

    forceDelalloc(&lal);
    forceDelalloc(&lal);

    printLal(&lal);

    forceDelalloc(&lal);

    printLal(&lal);

    forceRelalloc(&lal, 8);

    printLal(&lal);

    lreset(&lal);

    printLal(&lal);

    delalloc(&lal);
    relalloc(&lal, bytes, sizeof bytes);

    printf("Get value at current pointer: %d \n\n", lget(&lal));

    return 0;
}
