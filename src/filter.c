#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libdandelion.h"

typedef struct {
  unsigned int a;
  unsigned int b;
  unsigned int c;
  unsigned int d;
} indices;

static unsigned int
h1 (char* word, unsigned int sz)
{
  unsigned int hash = 0;
  for (unsigned int i = 0; i < strlen(word); i++) {
    hash = (hash + ((int)word[i]));
    hash = hash % sz;
  }

  return hash;
}

static unsigned int
h2 (char* word, unsigned int sz)
{
  unsigned int hash = 1;
  for (unsigned int i = 0; i < strlen(word); i++) {
    hash = hash + pow(19, i) * word[i];
    hash = hash % sz;
  }

  return hash % sz;
}

static unsigned int
h3 (char* word, unsigned int sz)
{
  unsigned int hash = 7;
  for (unsigned int i = 0; i < strlen(word); i++) {
    hash = (hash * 31 + word[i]) % sz;
  }

  return hash % sz;
}

static unsigned int
h4 (char* word, unsigned int sz)
{
  unsigned int hash = 3;
  for (unsigned int i = 0; i < strlen(word); i++) {
    hash += hash * 7 + word[0] * pow(7, i);
    hash  = hash % sz;
  }

  return hash;
}

static indices
hash (char* word, unsigned int sz)
{
  return (indices){
    .a = h1(word, sz),
    .b = h2(word, sz),
    .c = h3(word, sz),
    .d = h4(word, sz),
  };
}

static inline bool
test (bloom_filter* F, char* word)
{
  indices i = hash(word, F->sz);

  return (F->bits[i.a] && F->bits[i.b] && F->bits[i.c] && F->bits[i.d]);
}

bool
maybe_present (bloom_filter* F, char* word)
{
  return test(F, word);
}

void
insert (bloom_filter* F, char* word)
{
  indices i    = hash(word, F->sz);

  F->bits[i.a] = 1;
  F->bits[i.b] = 1;
  F->bits[i.c] = 1;
  F->bits[i.d] = 1;
}

bloom_filter*
new_bloom_filter (unsigned int sz)
{
  bloom_filter* F = malloc(sizeof(bloom_filter));
  if (!F) {
    fprintf(stderr, "failed to malloc\n");
    exit(EXIT_FAILURE);
  }

  F->bits = malloc(sz * sizeof(unsigned int));
  if (!F->bits) {
    fprintf(stderr, "failed to malloc\n");
    exit(EXIT_FAILURE);
  }

  F->sz = sz;

  return F;
}

float
get_false_positive_rate (unsigned int array_sz, unsigned int num_els)
{
  unsigned int num_hash_fns = 4;

  return pow(
    1.0 - pow(1.0 - (1.0 / array_sz), num_hash_fns * num_els),
    num_hash_fns
  );
}
