
#ifndef __TRAIL_ENCODE_H__
#define __TRAIL_ENCODE_H__

#include <stdio.h>
#include <stdint.h>

#include <Judy.h>

#include "breadcrumbs_encoder.h"

#define EDGE_INCREMENT 1000000

struct cookie_logline{
    uint64_t values_offset;
    uint32_t num_values;
    uint32_t timestamp;
    uint64_t cookie_id;
};

uint32_t edge_encode_fields(const uint32_t *values,
                            uint32_t **encoded,
                            uint32_t *encoded_size,
                            uint32_t *prev_values,
                            const struct cookie_logline *line);

void store_trails(const uint64_t *cookie_pointers,
                  uint64_t num_cookies,
                  struct logline *loglines,
                  uint64_t num_loglines,
                  const uint32_t *values,
                  uint64_t num_values,
                  uint32_t num_fields,
                  const uint64_t *field_cardinalities,
                  const char *root);

/* trail_encode_model */

struct gram_bufs{
    uint64_t *chosen;
    uint64_t *scores;
    uint8_t *covered;
    uint32_t num_fields;
};

void init_gram_bufs(struct gram_bufs *b, uint32_t num_fields);
void free_gram_bufs(struct gram_bufs *b);

uint32_t choose_grams(const uint32_t *encoded,
                      int num_encoded,
                      const Pvoid_t gram_freqs,
                      struct gram_bufs *g,
                      uint64_t *grams,
                      const struct cookie_logline *line);

Pvoid_t make_grams(FILE *grouped,
                   uint64_t num_loglines,
                   const uint32_t *values,
                   uint32_t num_fields,
                   const Pvoid_t unigram_freqs);

Pvoid_t collect_unigrams(FILE *grouped,
                         uint64_t num_loglines,
                         const uint32_t *values,
                         uint32_t num_fields);

#endif /* __TRAIL_ENCODE_H__ */