// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2015-2021, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <cstdint>
#include <initializer_list>

namespace CryptoNote {
namespace parameters {

const uint64_t CRYPTONOTE_MAX_BLOCK_NUMBER                   = 500000000;
const size_t   CRYPTONOTE_MAX_BLOCK_BLOB_SIZE                = 500000000;
const size_t   CRYPTONOTE_MAX_TX_SIZE                        = 1000000000;
const uint64_t CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX       = 0x321589488; // Prosus
const size_t   CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW          = 60;
const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT            = 60 * 60 * 2;
const size_t   BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW             = 60;

// PROSUS MONEY SUPPLY =>  18'446'744 coins, 12 decimals
const uint64_t MONEY_SUPPLY                                  = (uint64_t)(-1); // atomic units
const size_t   CRYPTONOTE_DISPLAY_DECIMAL_POINT              = 12;

//const unsigned EMISSION_SPEED_FACTOR                       = 21; // prosus_v0.2 (año 2015)
const unsigned EMISSION_SPEED_FACTOR                         = 18;
static_assert(EMISSION_SPEED_FACTOR <= 8 * sizeof(uint64_t), "Bad EMISSION_SPEED_FACTOR");
const size_t CRYPTONOTE_COIN_VERSION                         = 1; 
const uint64_t TAIL_EMISSION_REWARD                          = UINT64_C(10000000000); 

const size_t   CRYPTONOTE_REWARD_BLOCKS_WINDOW               = 100;
const size_t   CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE        = 600;

const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE     = 10000; 
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V2  = 2000000; 
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V3  = 3000000; 
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE; 

const uint64_t MINIMUM_FEE                                   = 100000;
const uint64_t DEFAULT_DUST_THRESHOLD                        = MINIMUM_FEE;
const uint64_t MAX_TX_MIXIN_SIZE                             = 60;

const uint64_t DIFFICULTY_TARGET                             = 120; // seconds
const uint64_t EXPECTED_NUMBER_OF_BLOCKS_PER_DAY             = 24 * 60 * 60 / DIFFICULTY_TARGET;
const size_t   DIFFICULTY_WINDOW                             = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY; 
const size_t   DIFFICULTY_WINDOW_V2                          = 60; // blocks
const size_t   DIFFICULTY_WINDOW_V3                          = 60; // blocks 
const size_t   DIFFICULTY_CUT                                = 60; // timestamps to cut after sorting
const size_t   DIFFICULTY_LAG                                = 15;
static_assert(2 * DIFFICULTY_CUT <= DIFFICULTY_WINDOW - 2, "Bad DIFFICULTY_WINDOW or DIFFICULTY_CUT");

const size_t   MAX_BLOCK_SIZE_INITIAL                        =  20 * 1024;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_NUMERATOR         = 100 * 1024;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_DENOMINATOR       = 365 * 24 * 60 * 60 / DIFFICULTY_TARGET;

const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS     = 1;
const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS    = DIFFICULTY_TARGET * CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS;

const uint64_t CRYPTONOTE_MEMPOOL_TX_LIVETIME                = 60 * 60 * 24;     //seconds, one day
const uint64_t CRYPTONOTE_MEMPOOL_TX_FROM_ALT_BLOCK_LIVETIME = 60 * 60 * 24 * 7; //seconds, one week
const uint64_t CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL = 7;  // CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL * CRYPTONOTE_MEMPOOL_TX_LIVETIME = time to forget tx

const size_t   FUSION_TX_MAX_SIZE                            = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT * 30 / 100;
const size_t   FUSION_TX_MIN_INPUT_COUNT                     = 12;
const size_t   FUSION_TX_MIN_IN_OUT_COUNT_RATIO              = 4;

const uint32_t UPGRADE_HEIGHT_V2                             = 400000; // LWMA
const uint32_t UPGRADE_HEIGHT_V3                             = 405400; // cnv7 antiASIC
const unsigned UPGRADE_VOTING_THRESHOLD                      = 90; // (percent)
const uint32_t UPGRADE_VOTING_WINDOW                         = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY; 
const uint32_t UPGRADE_WINDOW                                = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY; 

const char     CRYPTONOTE_BLOCKS_FILENAME[]                  = "blocks.dat";
const char     CRYPTONOTE_BLOCKINDEXES_FILENAME[]            = "blockindexes.dat";
const char     CRYPTONOTE_BLOCKSCACHE_FILENAME[]             = "blockscache.dat";
const char     CRYPTONOTE_POOLDATA_FILENAME[]                = "poolstate.bin";
const char     P2P_NET_DATA_FILENAME[]                       = "p2pstate.bin";
const char     CRYPTONOTE_BLOCKCHAIN_INDICES_FILENAME[]      = "blockchainindices.dat";
const char     MINER_CONFIG_FILE_NAME[]                      = "miner_conf.json";
} // (namespace_parameters)



const char     CRYPTONOTE_NAME[]                             = "prosus";

const uint8_t  CURRENT_TRANSACTION_VERSION                   =  1;
const uint8_t  BLOCK_MAJOR_VERSION_1                         =  1;
const uint8_t  BLOCK_MAJOR_VERSION_2                         =  2; 
const uint8_t  BLOCK_MAJOR_VERSION_3                         =  3; 
const uint8_t  BLOCK_MINOR_VERSION_0                         =  0;
const uint8_t  BLOCK_MINOR_VERSION_1                         =  1;

const size_t   BLOCKS_IDS_SYNCHRONIZING_DEFAULT_COUNT        =  10000;  // blocks ids count in synchronizing
const size_t   BLOCKS_SYNCHRONIZING_DEFAULT_COUNT            =  20;     // blocks count in blocks downloading
const size_t   COMMAND_RPC_GET_BLOCKS_FAST_MAX_COUNT         =  1000;

const int      P2P_DEFAULT_PORT                              = 16180;
const int      RPC_DEFAULT_PORT                              = 16190;

const size_t   P2P_LOCAL_WHITE_PEERLIST_LIMIT                =  1000;
const size_t   P2P_LOCAL_GRAY_PEERLIST_LIMIT                 =  5000;

const size_t   P2P_CONNECTION_MAX_WRITE_BUFFER_SIZE          = 16 * 1024 * 1024; // 16 MB
const uint32_t P2P_DEFAULT_CONNECTIONS_COUNT                 = 8;
const size_t   P2P_DEFAULT_WHITELIST_CONNECTIONS_PERCENT     = 70;
const uint32_t P2P_DEFAULT_HANDSHAKE_INTERVAL                = 60;            // seconds
const uint32_t P2P_DEFAULT_PACKET_MAX_SIZE                   = 50000000;      // 50'000'000 bytes maximum packet size
const uint32_t P2P_DEFAULT_PEERS_IN_HANDSHAKE                = 250;
const uint32_t P2P_DEFAULT_CONNECTION_TIMEOUT                = 5000;          // 5 seconds
const uint32_t P2P_DEFAULT_PING_CONNECTION_TIMEOUT           = 2000;          // 2 seconds
const uint64_t P2P_DEFAULT_INVOKE_TIMEOUT                    = 60 * 2 * 1000; // 2 minutes
const size_t   P2P_DEFAULT_HANDSHAKE_INVOKE_TIMEOUT          = 5000;          // 5 seconds
const char     P2P_STAT_TRUSTED_PUB_KEY[]                    = "8f80f9a5a434a9f1510d13336228debfee9c918ce505efe225d8c94d045fa115";
const uint32_t P2P_IP_BLOCKTIME                              = (60 * 60 * 24);// 24 hour 
const uint32_t P2P_IP_FAILS_BEFORE_BLOCK                     = 10; // *v0.6

const std::initializer_list<const char*> SEED_NODES = { 
    "seed01.prosus.money:16180",
	"seed02.prosus.money:16180",
	"seed03.prosus.money:16180",
    "seed04.prosus.money:16180"
};

struct CheckpointData {
  uint32_t height;
  const char* blockId;
};

#ifdef __GNUC__
__attribute__((unused))
#endif

const std::initializer_list<CheckpointData> CHECKPOINTS = {
//	{    1626, "55c456b87abc26b4ff62ad53b75c6f1033536507f60d7f7f1aed22950f4994bd" }, // cambiamos recompensa
//	{    3150, "6571b301402d7b677c53333cdb59f811dc902ac63ab5262ece30a4f66940f8f6" }, // secuestramos red
    {  100000, "7da57e40ecd2b332370bed0351c101d4e122129eee05a721f1a49dd4e524c143" },
//	{  164520, "b41826f1c6411d6e31fae5b887020d33324996e28415941c73a9a00737a468c1" }, // primer stuck, parchamos
    {  200000, "e0fb878c4de045c471dc72e3186b4aafcc55001d4f8707c73e3ba9386c7246b0" },
//	{  230106, "fcdd9a8a6753c2c046dfe6b961c713a4e4da57377b6be1e3ad5b5273f57bdef0" }, // segundo stuck, parchamos
    {  300000, "f7f29b6da24f8594b8f5e2528c9cc6892f34089c4e331fe82130607396e22667" },
    {  400000, "daababef97070394b438d1ac7b5550519ae58af819053166c89e660bc7dbed9b" }, 
//	{  400165, "3ef8ea39741b9ca7c5e07ce23d4554fcfa75466c61602d8dc4bd6757385857d3" }, // Reward_Zone_v2
	{  405500, "a85b9dfe6538bf253c8fa8125dea75233ee1da35188e10f194030acb102effef" }, // LWMA + antiasic
//	{  500000, "0000000000000000000000000000000000000000000000000000000000000000" },
//	{  600000, "0000000000000000000000000000000000000000000000000000000000000000" },
//	{  700000, "0000000000000000000000000000000000000000000000000000000000000000" },
//	{  800000, "0000000000000000000000000000000000000000000000000000000000000000" },
//	{  900000, "0000000000000000000000000000000000000000000000000000000000000000" },
//	{ 1000000, "0000000000000000000000000000000000000000000000000000000000000000" }
};
} // (namespace_CryptoNote)

#define ALLOW_DEBUG_COMMANDS



 