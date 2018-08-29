#include "get_trytes.h"

get_trytes_res_t* get_trytes_res_new() {
  get_trytes_res_t* res =
      (get_trytes_res_t*)malloc(sizeof(get_trytes_res_t));
  utarray_new(res->trytes, &ut_str_icd);
  res->numTransactions = 0;
  return res;
}

void get_trytes_res_free(get_trytes_res_t* res) {
  if (res) {
    utarray_free(res->trytes);
    free(res);
  }
}

char *get_trytes_res_tryte_at(get_trytes_res_t* in, int index) {
  if (utarray_len(in->trytes) > index) {
    char** p = NULL;
    p = (char**)utarray_eltptr(in->trytes, index);
    if (p) {
      return *p;
    }
  }
  return '\0';
}

int get_trytes_res_tryte_num(get_trytes_res_t* in) {
  return in->numTransactions;
}
