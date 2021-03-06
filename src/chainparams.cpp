// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        //using HAVW in hex
        pchMessageStart[0] = 0x39;
        pchMessageStart[1] = 0x4a;
        pchMessageStart[2] = 0x41;
        pchMessageStart[3] = 0x55;
        vAlertPubKey = ParseHex("04230591895a2a274a733989e10bd15f9cf7bfc26fcfcriki3d72d584378bd208c59f7809220154bd808b53ccbd422e864f359105f277a30026752fd404a0fc76");
        nDefaultPort = 5555;
        nRPCPort = 5551;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "Fivebalance Made With Love 22 october 2018";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1504607927, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1540209717;
        genesis.nBits    = 0x1e0ffff0; 
        genesis.nNonce   = 38710;

          

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000a2b5f83f5e91b41f8530b9706e9afaa56c716a5edd58bef7332e36697c4f"));
        assert(genesis.hashMerkleRoot == uint256("0xed0ff62b45bc2d0d36919595340cb2771ff7c66ed4f98d50c447627ad561a180"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,36);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,123);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,115);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,117);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x03)(0x88)(0xC3)(0x2E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x03)(0x88)(0xD3)(0xE2).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("0",  "seed0.fivebalance.com"));
        vSeeds.push_back(CDNSSeedData("1",  "seed1.fivebalance.com"));
        vSeeds.push_back(CDNSSeedData("2",  "seed2.fivebalance.com"));
        vSeeds.push_back(CDNSSeedData("3",  "seed3.fivebalance.com"));
        vSeeds.push_back(CDNSSeedData("4",  "seed4.fivebalance.com"));
        vSeeds.push_back(CDNSSeedData("5",  "seed5.fivebalance.com"));
        vSeeds.push_back(CDNSSeedData("6",  "seed6.fivebalance.com"));
         convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        
        strDarksendPoolDummyAddress = "FaxZ9cKvK2vrWUGLhJXhknpNSAGF6TJCYt";
        nLastPOWBlock = 5000000;
        nPOSStartBlock = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x48;
        pchMessageStart[1] = 0x4d;
        pchMessageStart[2] = 0x43;
        pchMessageStart[3] = 0x54;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04230591895a2a274a733989e10bd15f9cf7bfc26fcfcriki3d72d584378bd208c59f7809220154bd808b53ccbd422e864f359105f277a30026752fd404a0fc76");
        nDefaultPort = 4444;
        nRPCPort = 4441;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 504365040; 
       genesis.nNonce   = 38710;
        
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000a2b5f83f5e91b41f8530b9706e9afaa56c716a5edd58bef7332e36697c4f"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,43);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,135);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,123);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,83);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x13)(0x06)(0x16)(0x27).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x13)(0x05)(0x17)(0x34).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 5000000;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
