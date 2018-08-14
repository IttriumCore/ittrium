// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Ittrium developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
	
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions

static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (1, uint256("0x000008e58d4d75851e8f8a4047c185d80d6ba82b7c2f95552c38edb9793495d2"))
        (369, uint256("0x63bf0d467cddf1aa2133dc55d0c9c89bd72fda54504bd48d1a175a671df5efe4"))
 	(1033, uint256("0x67c70e40ba675e9cb323239b6524b1965b1399deb8ac3a2493d1522178dc9dd8"))
 	(3333, uint256("0x0a720043f8a3ee41dfddc1241ef2912ad0d2188f845d1610279fe6f4ecdcf07e"))
 	(6133, uint256("0x7f91e176ce9c6cdff238be16505b6f93444225e1bcfbbfb3dcb370a2b97e5569"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1533333333, 	// * UNIX timestamp of last checkpoint block
    6133,    			// * total number of transactions between genesis and last checkpoint
    				//   (the tx=... number in the SetBestChain debug.log lines)
    1440        	// * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1533333336,
    0,
    1440};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1533333339,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
		pchMessageStart[0] = 0xf9;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xb9;
        pchMessageStart[3] = 0xf0;
        vAlertPubKey = ParseHex("0434d2de40d30b1ae724823c08a401c3194606043b6ed77642f42122eab9acc92d37015a5110c9fd4f51205a1f09479ab727151fc76cc46c2be85633ef2a743c5f");
        nDefaultPort = 39993;
        bnProofOfWorkLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000"); // XIT starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 3 * 60; // XIT: 1 minutes
        nTargetSpacing = 60;  // XIT: 1 minute
        nLastPOWBlock = 300;
        nMaturity = 60;
        nMasternodeCountDrift = 20;
        nModifierUpdateBlock = 1;  //***CHECK-->615800***
        nMaxMoneyOut = 33000000 * COIN;

        /**
		block.nTime = 1533333333 
		block.nNonce = 445453 
		block.GetHash = 000000fdacddaba54eb66a4c09dc795efbfc75fcd0572c99f489424367bc9ec9
		block.merkle = fc052cd7cd34c839bde40a2c9e484ef50c48858667c3d6dd2938b6668479c374
		CBlock(hash=b7b24912fde3422f1749cb74a650c5e804606d7e74f40c04db63e2bce3cadd8b, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=fc052cd7cd34c839bde40a2c9e484ef50c48858667c3d6dd2938b6668479c374, nTime=1533333333, nBits=1e0ffff0, nNonce=0, vtx=1)
		CTransaction(hash=fc052cd7cd, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    	CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01043e42696e616e636520746f204d6565742047726f77696e672044656d616e647320666f72204c6971756964697479206f662043727970746f20417373657473)
    	CTxOut(nValue=250.00000000, scriptPubKey=047afd6a2c8b303847c3ebb170743a)
 		vMerkleTree:  fc052cd7cd34c839bde40a2c9e484ef50c48858667c3d6dd2938b6668479c374
		*/
				 
        const char* pszTimestamp = "Binance to Meet Growing Demands for Liquidity of Crypto Assets";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("047afd6a2c8b303847c3ebb170743afdb70220682e2303577465bf17814e87e81e2f50807ca63f5f7474d818f4cfa5203250529c32872016f442d20ca9863b5df5") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1533333333;
        genesis.nBits = 0x1e0ffff0; //bnProofOfWorkLimit.GetCompact();;
        genesis.nNonce = 445453;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000000fdacddaba54eb66a4c09dc795efbfc75fcd0572c99f489424367bc9ec9"));
        assert(genesis.hashMerkleRoot == uint256("0xfc052cd7cd34c839bde40a2c9e484ef50c48858667c3d6dd2938b6668479c374"));

	vSeeds.push_back(CDNSSeedData("01.ittriumno.de", "01.ittriumno.de"));
	vSeeds.push_back(CDNSSeedData("02.ittriumno.de", "02.ittriumno.de"));
	vSeeds.push_back(CDNSSeedData("03.ittriumno.de", "03.ittriumno.de"));
	vSeeds.push_back(CDNSSeedData("04.ittriumno.de", "04.ittriumno.de"));
	vSeeds.push_back(CDNSSeedData("05.ittriumno.de", "05.ittriumno.de"));

        // Ittrium addresses start with 'i'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 103);
        // Ittrium script addresses start with '3'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 6);
        // Ittrium private keys start with 'K'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        // Ittrium BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Ittrium BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xde).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04d37d371dde4335c7f3a80efab4848024b0d782bb5b4a36c21f9a8fd5c620c6a7a09821f77776b77987a947efd3218336d4aa59670a4e309a93a8dc6026ed03d8";
        strObfuscationPoolDummyAddress = "ifd6BU5MDvKsTW9Vfqyo6SNW3KFjv7YEz";
        nStartMasternodePayments = 150; 
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
	     	pchMessageStart[0] = 0x3c;
        pchMessageStart[1] = 0x73;
        pchMessageStart[2] = 0x27;
        pchMessageStart[3] = 0xcb;
        vAlertPubKey = ParseHex("04ca98d12a22622005f8c8a60b3b6f89b501b65147b47506b194d8dc5490314d2b1e88f838e486d03c4eace547b1e6cbd70c1e1ce5e1d3339cac28989f44fc6dbd");
        nDefaultPort = 3993;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 3 * 60; // XIT: 3 minutes
        nTargetSpacing = 1 * 60;  // XIT: 1 minute
        nLastPOWBlock = 300;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; 
        nMaxMoneyOut = 33000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1533333336;
        genesis.nNonce = 2138748;
/*
		block.nTime = 1533333336 
		block.nNonce = 2138748 
		block.GetHash = 00000f036ca027597072fe7ea639a6a58839be8e3e3126f113d0a7d03b355b26
		block.merkle = fc052cd7cd34c839bde40a2c9e484ef50c48858667c3d6dd2938b6668479c374	
		CBlock(hash=44a458bab8bdb92f392e6b80681a2c868cf67d12e9bacaf037732fdde21fd9e3, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=fc052cd7cd34c839bde40a2c9e484ef50c48858667c3d6dd2938b6668479c374, nTime=1533333336, nBits=1e0ffff0, nNonce=0, vtx=1)
		CTransaction(hash=fc052cd7cd, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    	CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01043e42696e616e636520746f204d6565742047726f77696e672044656d616e647320666f72204c6971756964697479206f662043727970746f20417373657473)
    	CTxOut(nValue=250.00000000, scriptPubKey=047afd6a2c8b303847c3ebb170743a)
  		vMerkleTree:  fc052cd7cd34c839bde40a2c9e484ef50c48858667c3d6dd2938b6668479c374
*/
	
		hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000f036ca027597072fe7ea639a6a58839be8e3e3126f113d0a7d03b355b26"));

        vFixedSeeds.clear();
        vSeeds.clear();

        //vSeeds.push_back(CDNSSeedData("xxx.xxx.xxx.xxx", "xxx.xxx.xxx.xxx"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 140); // Testnet XIT addresses start with 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 128);  // Testnet XIT script addresses start with 't'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with 'k' 
        // Testnet Ittrium BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Ittrium BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet ittrium BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        //strSporkKey = "040182ab1fac9a519cf3f49f0e4dd7d364f966c29ebbc29de2a5cfa0ff9dbd64a92805cc9edc221ae15f07405d6da4264d798e68e9a43603f55954a2ce2ddb0677";
        //strObfuscationPoolDummyAddress = "";
        nStartMasternodePayments = 150; 
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // XIT: 1 day
        nTargetSpacing = 1 * 60;        // XIT: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1533333339;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 653367;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51476;
/*
		block.nTime = 1533333339 
		block.nNonce = 653367 
		block.GetHash = 0000096b80f36f2a16531c1172b5beaaa1a14a4c5c79c3c5769b122ed84dd67f
		block.merkle = fc052cd7cd34c839bde40a2c9e484ef50c48858667c3d6dd2938b6668479c374
		CBlock(hash=cc9972772cafc85ffa942e6d7b9e2e3548f23d356c27cbc416c80ac66083f2b6, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=fc052cd7cd34c839bde40a2c9e484ef50c48858667c3d6dd2938b6668479c374, nTime=1533333339, nBits=207fffff, nNonce=0, vtx=1)
		CTransaction(hash=fc052cd7cd, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    	CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01043e42696e616e636520746f204d6565742047726f77696e672044656d616e647320666f72204c6971756964697479206f662043727970746f20417373657473)
    	CTxOut(nValue=250.00000000, scriptPubKey=047afd6a2c8b303847c3ebb170743a)
  		vMerkleTree:  fc052cd7cd34c839bde40a2c9e484ef50c48858667c3d6dd2938b6668479c37
*/

       assert(hashGenesisBlock == uint256("0x0000096b80f36f2a16531c1172b5beaaa1a14a4c5c79c3c5769b122ed84dd67f"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
