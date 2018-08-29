/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef CCLIENT_RESPONSE_GET_TRYTES_H
#define CCLIENT_RESPONSE_GET_TRYTES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types/types.h"

typedef struct {
  UT_array* trytes;
  size_t numTransactions;
} get_trytes_res_t;

get_trytes_res_t* get_trytes_res_new();
void get_trytes_res_free(get_trytes_res_t* res);
char *get_trytes_res_tryte_at(get_trytes_res_t* in, int index);
int get_trytes_res_tryte_num(get_trytes_res_t* in);

#ifdef __cplusplus
}
#endif

#endif  // CCLIENT_RESPONSE_GET_TRYTES_H
