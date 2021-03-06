/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#include "consensus/entry_point_selector/entry_point_selector.h"
#include "consensus/milestone/milestone.h"
#include "utils/logger_helper.h"
#include "utils/macros.h"

#define ENTRY_POINT_SELECTOR_LOGGER_ID "consensus_entry_point_selector"

retcode_t iota_consensus_entry_point_selector_init(
    entry_point_selector_t *const eps, milestone_t *const milestone,
    tangle_t *const tangle, bool const testnet) {
  logger_helper_init(ENTRY_POINT_SELECTOR_LOGGER_ID, LOGGER_INFO, true);
  eps->milestone = milestone;
  eps->tangle = tangle;
  eps->testnet = testnet;
  return RC_OK;
}

retcode_t iota_consensus_get_entry_point(entry_point_selector_t *const eps,
                                         size_t const depth,
                                         trit_array_p const ep) {
  retcode_t ret = RC_OK;
  size_t milestone_index =
      MAX(eps->milestone->latest_milestone_index - depth - 1, 0);
  TRIT_ARRAY_DECLARE(msv, NUM_TRITS_HASH);

  if ((ret = iota_consensus_find_closest_next_milestone(
           eps->tangle, eps->testnet, milestone_index,
           eps->milestone->milestone_start_index, &msv))) {
    log_error(
        ENTRY_POINT_SELECTOR_LOGGER_ID,
        "Finding closest next milestone failed with error %\" PRIu64 \"\n",
        ret);
    return ret;
  }

  if (msv.trits != NULL) {
    memcpy(ep->trits, msv.trits, FLEX_TRIT_SIZE_243);
  } else {
    memcpy(ep->trits, eps->milestone->latest_solid_milestone_hash,
           FLEX_TRIT_SIZE_243);
  }

  return RC_OK;
}

retcode_t iota_consensus_entry_point_selector_destroy(
    entry_point_selector_t *const eps) {
  logger_helper_destroy(ENTRY_POINT_SELECTOR_LOGGER_ID);
  eps->milestone = NULL;
  eps->tangle = NULL;
  return RC_OK;
}
