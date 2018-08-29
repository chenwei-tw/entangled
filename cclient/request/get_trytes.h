/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef CCLIENT_REQUEST_GET_TRYTES_H
#define CCLIENT_REQUEST_GET_TRYTES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types/types.h"

typedef struct {
  /**
   * List of tx hashes for which request should get trytes
   */
  UT_array* hashes;

} get_trytes_req_t;

get_trytes_req_t* get_trytes_req_new();
void get_trytes_req_free(get_trytes_req_t* req);

void get_trytes_req_add_hash(get_trytes_req_t* req,
                             char* hash);

#ifdef __cplusplus
}
#endif

#endif  // CCLIENT_REQUEST_GET_TRYTES_H
