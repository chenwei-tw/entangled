/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __CIRI_CONF_CONF_DEFAULT_H__
#define __CIRI_CONF_CONF_DEFAULT_H__

// Command line arguments default values

#define CONF_DEFAULT_API_PORT 14265
#define CONF_DEFAULT_NEIGHBORS NULL
#define CONF_DEFAULT_CONF_FILE NULL
#define CONF_DEFAULT_TCP_RECEIVER_PORT 15600
#define CONF_DEFAULT_UDP_RECEIVER_PORT 14600
#define CONF_DEFAULT_TESTNET false
#define CONF_DEFAULT_REMOTE false
#define CONF_DEFAULT_REMOTE_AUTH_TOKEN NULL
#define CONF_DEFAULT_REMOTE_LIMIT_API NULL
#define CONF_DEFAULT_SEND_LIMIT 0
#define CONF_DEFAULT_MAX_PEERS 0
#define CONF_DEFAULT_DNS_RESOLUTION true

// Network configuration

#define PACKET_TX_SIZE 1604
#define PACKET_TX_TRITS_SIZE 8019
#define MAINNET_PACKET_REQ_HASH_SIZE 46
#define TESTNET_PACKET_REQ_HASH_SIZE 49
#define MAINNET_PACKET_SIZE PACKET_TX_SIZE + MAINNET_PACKET_REQ_HASH_SIZE
#define TESTNET_PACKET_SIZE PACKET_TX_SIZE + TESTNET_PACKET_REQ_HASH_SIZE

#endif  // __CIRI_CONF_CONF_DEFAULT_H__
