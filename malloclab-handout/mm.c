/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))
/***************************************************/
// Macros from book

// Basic constants and macros
#define WSIZE 4
#define DSIZE 8
#define CHUNKSIZE (1<<12)

#define MAX(x,y)  ( (x>y)? x:y )

// pack a size and allocated bit into a word
#define PACK(size, alloc) ((size | alloc))

// Read and write a word at address p
#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

// Read the size and allocated fields from address p
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

// Given block ptr bp, compute address of its header and footer
#define HEADERP(bp) ((char *)(bp) - WSIZE)
#define FOOTERP(bp) ((char *)(bp) + GET_SIZE(HEADERP(bp)) - DSIZE)

// Given block ptr bp, compute address of next and previous blocks
#define NEXT_BLKP(bp) ((char *)bp + GET_SIZE(((char *)bp - WSIZE)))
#define PREV_BLKP(bp) ((char *)bp - GET_SIZE(((char *)bp - DSIZE)))

/***************************************************/
// Global variables
#define DEBUG 0
#define TRACE 1
void *prolog = NULL;


// function declare
static void *extend_heap(size_t words);
int mm_init(void);
int epichk(void *bp);
static void *coalesce(void *bp);
static void place(void *bp, size_t asize);
static char *find_fit(size_t asize);
void *mm_malloc(size_t size);
void mm_free(void *ptr);
void *mm_realloc(void *ptr, size_t size);
/****************************************************/


int epichk(void *bp) {
	if (GET_SIZE(HEADERP(bp)) == 0 && GET_ALLOC(HEADERP(bp))) return 1;
	else return 0;
}

/*
* extend_heap - extend heap and move prolog block
*/
static void *extend_heap(size_t words) {
	if (DEBUG){
		printf("extend_heap %d words", words);
	}
	char *bp;
	size_t size;

	// extend heap with alignment rule
	size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
	if ((long)(bp = mem_sbrk(size)) == -1)
		return NULL;

	// Set free block header, footer and move prolog block
	PUT(HEADERP(bp), PACK(size, 0));
	PUT(FOOTERP(bp), PACK(size, 0));
	PUT(HEADERP(NEXT_BLKP(bp)), PACK(0, 1));

	bp = coalesce(bp);
	return bp;

}





/*
* coalesce - do coalesce
*/
static void *coalesce(void *bp) {
	size_t prev = GET_ALLOC(FOOTERP(PREV_BLKP(bp)));
	size_t next = GET_ALLOC(HEADERP(NEXT_BLKP(bp)));
	size_t size = GET_SIZE(HEADERP(bp));

	if (DEBUG){
		printf("coalesce %d %d %d ", prev, next, size);
	}

	size_t cases = 1 + (!prev << 1) + !next;
	if (DEBUG) printf("case %d\n", cases);
	switch (cases) {
		case 1:
			
			return bp;

		case 2:
			size += GET_SIZE(HEADERP(NEXT_BLKP(bp)));
			PUT(HEADERP(bp), PACK(size, 0));
			PUT(FOOTERP(bp), PACK(size, 0));
			break;

		case 3:
			size += GET_SIZE(FOOTERP(PREV_BLKP(bp)));
			PUT(FOOTERP(bp), PACK(size, 0));
			PUT(HEADERP(PREV_BLKP(bp)), PACK(size, 0));
			bp = PREV_BLKP(bp);
			break;

		case 4:
			size += GET_SIZE(HEADERP(NEXT_BLKP(bp))) + GET_SIZE(FOOTERP(PREV_BLKP(bp)));
			PUT(HEADERP(PREV_BLKP(bp)), PACK(size, 0));
			PUT(FOOTERP(NEXT_BLKP(bp)), PACK(size, 0));
			bp = PREV_BLKP(bp);
			break;
	}

	return bp;
}






static void place(void *bp, size_t asize) {
	size_t remainder;
	if (GET_SIZE(HEADERP(bp)) == asize) {
		if (DEBUG){
			printf("place %d at %x\n", asize, bp);
		}
		PUT(HEADERP(bp), PACK(asize, 1));
		PUT(FOOTERP(bp), PACK(asize, 1));
	} else {
		if (DEBUG){
			printf("place %d at %x with splitting\n", asize, bp);
		}
		remainder = GET_SIZE(HEADERP(bp)) - asize;
		PUT(HEADERP(bp), PACK(asize, 1));
		PUT(FOOTERP(bp), PACK(asize, 1));
		PUT(HEADERP(NEXT_BLKP(bp)), PACK(remainder, 0));
		PUT(FOOTERP(NEXT_BLKP(bp)), PACK(remainder, 0));
	}
}

static char *find_fit(size_t asize) {
	if (DEBUG){
		printf("find_fit. ");
	}

	char *bp = prolog;
	int nullchk = 1;
	while (!epichk(bp)) {
		if (GET_SIZE(HEADERP(bp)) >= asize && !GET_ALLOC(HEADERP(bp))) {
			nullchk = 0;
			if (DEBUG){
				printf("%x OK\n",bp);
			}
			break;
		}
		if (DEBUG){
			printf("%x ",bp);
		}
		bp = NEXT_BLKP(bp);
		//printf("shit\n")
	}
	if (nullchk) return NULL;
	return bp;
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*
* mm_init - initialize the malloc package.
*/
int mm_init(void) {
	if (DEBUG || TRACE) {
		printf("initialize...\n");
	}
	// get 4 word and set prolog block
	char * heap_listp = mem_heap_lo();
	if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void *)-1)
		return -1;
	PUT(heap_listp, 0); // Alignment Padding
	PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); // Prolog Header
	PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1)); // Prolog Footer
	PUT(heap_listp + (3 * WSIZE), PACK(0, 1)); // Epilogue Header

	prolog = heap_listp + DSIZE;

	if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
		return -1;

	return 0;
}

/*
* mm_malloc - Allocate a block by incrementing the brk pointer.
*     Always allocate a block whose size is a multiple of the alignment.
*/
void *mm_malloc(size_t size) {
	size_t asize;
	size_t extendsize;
	char *bp;
	if (DEBUG || TRACE) {
		printf("malloc size : %d\n", size);
	}
	if (size == 0) return NULL;

	if (size <= DSIZE) asize = 2 * DSIZE;
	else asize = ALIGN(size + DSIZE);

	if ((bp = find_fit(asize)) != NULL) {

		place(bp, asize);
		if (DEBUG) printf("nice! %x\n", bp);
		return bp;

	} else {

		extendsize = MAX(asize, CHUNKSIZE);

		if (((bp = extend_heap(extendsize / WSIZE)) == NULL)) {
			printf("eroororo\n", bp);
			return NULL;
		} else {
			if (DEBUG) printf("nice! %x\n", bp);
			place(bp, asize);

			return bp;
		}
	}
}


/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr){
	
	size_t size = GET_SIZE(HEADERP(ptr));

	if (DEBUG || TRACE) {
		printf("free %x %d\n", ptr, size);
	}

	PUT(HEADERP(ptr), PACK(size, 0));
	PUT(FOOTERP(ptr), PACK(size, 0));
	coalesce(ptr);

}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size){
	if (ptr == NULL) return mm_malloc(size);
	if (size == 0) {
		mm_free(ptr);
		return NULL;
	}
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;
    
    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
	copySize = GET_SIZE(HEADERP(ptr)) - DSIZE;
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}














