#ifndef LIBDANDELION_H
#define LIBDANDELION_H

#include <stdbool.h>

typedef struct {
  unsigned int  sz;
  unsigned int* bits;
} bloom_filter;

bool maybe_present(bloom_filter* filter, char* word);

void insert(bloom_filter* filter, char* word);

bloom_filter* new_bloom_filter(unsigned int sz);

float get_false_positive_rate(unsigned int array_sz, unsigned int num_els);

// False positive rate: P = (1 - (1 - (1/m))^k*n  )^k
// n = expected els in filter
// k = num hash functions
// m = size of bit array

// Size of array
// m = -1 * (n ln P) / (ln2)^2
// n = num els
// P = desired false positive probability

// Optimum num hash fns
// m = size of arr
// n = num els to be inserted
// k = m/n * ln2

// hash fn should be fast, and uniformly distributed
// e.g. murmur, FNV, Jenkins

#endif /* LIBDANDELION_H */
