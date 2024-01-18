#include "libdandelion.h"
#include "tap.c/tap.h"
#include "tests.h"

static void
presence_test (void)
{
  unsigned int  filter_sz = 1000;
  bloom_filter* bf        = new_bloom_filter(filter_sz);

  char* words[30]         = {
    "systematic", "consumer", "will",      "joystick",  "assault", "highlight",
    "terminal",   "lose",     "fraction",  "translate", "rally",   "creep",
    "character",  "youth",    "plaintiff", "refuse",    "virus",   "decade",
    "effect",     "order",    "forbid",    "patience",  "chew",    "can",
    "adventure",  "village",  "wonder",    "manual",    "member",  "innovation",
  };

  for (unsigned int i = 0; i < sizeof(words) / sizeof(char*); i++) {
    insert(bf, words[i]);
  }

  for (unsigned int i = 0; i < sizeof(words) / sizeof(char*); i++) {
    ok(
      maybe_present(bf, words[i]) == true,
      "tells us the inserted word may be present"
    );

    char buffer[16];
    sprintf(buffer, "%s%s", words[i], "x");

    ok(
      maybe_present(bf, buffer) == false,
      "tells us the inserted word is not present"
    );
  }
}

int
main (void)
{
  plan(60);

  presence_test();

  done_testing();
}
