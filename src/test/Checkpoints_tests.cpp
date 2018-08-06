// Copyright (c) 2011-2013 The Bitcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

//
// Unit tests for block-chain checkpoints
//

#include "checkpoints.h"

#include "uint256.h"

#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(Checkpoints_tests)

BOOST_AUTO_TEST_CASE(sanity)
{
    uint256 p0 = uint256("0x000003616197a9a9093a9cdda330cb4e0d52c4d7d3585dd985602913d93dfc0a");
    uint256 p1 = uint256("0x0000019624ca84395dc1da138d91bf9f0bb9824cf55ed4611cb9c59ae8afe310");
    BOOST_CHECK(Checkpoints::CheckBlock(0, p0));

    // Wrong hashes at checkpoints should fail:
    BOOST_CHECK(!Checkpoints::CheckBlock(0, p1));

    BOOST_CHECK(Checkpoints::GetTotalBlocksEstimate() >= 0);
}

BOOST_AUTO_TEST_SUITE_END()
