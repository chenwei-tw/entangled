#include "get_trytes.h"

get_trytes_req_t* get_trytes_req_new() {
  get_trytes_req_t* req =
      (get_trytes_req_t*)malloc(sizeof(get_trytes_req_t));
  utarray_new(req->hashes, &ut_str_icd);
  return req;
}

void get_trytes_req_free(get_trytes_req_t* req) {
  if (req) {
    utarray_free(req->hashes);
    free(req);
  }
}

void get_trytes_req_add_hash(get_trytes_req_t* req,
                             char* hash) {
  utarray_push_back(req->hashes, &hash);
}
