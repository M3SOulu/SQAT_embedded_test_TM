/*
 * display_test.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: timppa
 */

#include "gtest_inc.h"

#include "chip.h"

#include "tm.h"

namespace TM_test_namespace {
	//
	// dependency injection
	//
//	subroutine1();
	//
	// dependency injection
	//
//	subroutine1();
	//
	// target code is included instead of (direct) compilation:
	//   This allows to cut the dependencies (such as I2C_write above)
	//
	#include "../src/tm1.cpp"
}

using ::testing::Test;

/**********************************************************************
 *
 * GoogleTest test-class for 7-segment display testing
 *
 **********************************************************************/
class unittest_TM : public Test
{
public:
	//
	// constructor just resets attributes to some default values
	//
	unittest_TM()
	{
		mRc = -1;
	}
	virtual ~unittest_TM(){}
protected:
	//
	// SetUp performs the per-test initialization/setup of test instance
	//
	virtual void SetUp()
	{
		mRc = -1;
	}
	//
	// TearDown cleans-up test instance
	//
	virtual void TearDown()
	{
	}
protected:
	int mRc;
};

/**********************************************************************
 *
 * quick verification of test fixture
 * - this helps detect problems in test setup
 *
 **********************************************************************/
TEST_F( unittest_TM, test_fixture )
{
	EXPECT_EQ( -1, mRc );
}

/**********************************************************************
 *
 * quick verification of test setup/construction
 * - this helps detect problems in test setup
 *
 **********************************************************************/

TEST_F( unittest_TM, test_constructor )
{
}

/**********************************************************************
 *
 * test cases: these are examples
 *
 **********************************************************************/

//
// this test matches the empty implementation, both need fixes
//
TEST_F( unittest_TM, reset_data_zeroes_table )
{
	TM_test_namespace::tm_reset_data();

	EXPECT_EQ( 0, TM_test_namespace::tm_get_temperature(0) );
	EXPECT_EQ( 0, TM_test_namespace::tm_get_temperature(1) );
	EXPECT_EQ( 0, TM_test_namespace::tm_get_temperature(2) );
	EXPECT_EQ( 0, TM_test_namespace::tm_get_temperature(3) );
	EXPECT_EQ( 0, TM_test_namespace::tm_get_temperature(4) );
	EXPECT_EQ( 0, TM_test_namespace::tm_get_temperature(5) );
	EXPECT_EQ( 0, TM_test_namespace::tm_get_temperature(6) );
	EXPECT_EQ( 0, TM_test_namespace::tm_get_temperature(7) );
}

//
// bad test but matches the empty implemementation
//
TEST_F(unittest_TM, average_is_updated_correctly )
{
	TM_test_namespace::tm_reset_data();

	TM_test_namespace::tm_update_average(8);

	EXPECT_EQ(1, TM_test_namespace::tm_get_average());
}

TEST_F( unittest_TM, removal_of_oldest_value_after_average )
{
	TM_test_namespace::tm_reset_data();
	TM_test_namespace::tm_update_average( 12);
	TM_test_namespace::tm_update_average( 10);
	TM_test_namespace::tm_update_average( 11);
	TM_test_namespace::tm_update_average( 12);
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 18);
	TM_test_namespace::tm_update_average( 12);
	TM_test_namespace::tm_update_average( 11);
	TM_test_namespace::tm_update_average( 15);

	EXPECT_EQ(15, TM_test_namespace::tm_get_temperature(7));

}
//
// bad name for test
//
TEST_F( unittest_TM, tend_is_correct_case_1 )
{
	TM_test_namespace::tm_reset_data();
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 12);

	display_message_t trend = TM_test_namespace::tm_get_trend();
	EXPECT_EQ( DISP_MSG_DOWN, trend );

}

TEST_F( unittest_TM, increasing_trend )
{
	TM_test_namespace::tm_reset_data();
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 15);
	TM_test_namespace::tm_update_average( 20);
	TM_test_namespace::tm_update_average( 21);
	TM_test_namespace::tm_update_average( 22);
	TM_test_namespace::tm_update_average( 23);

	display_message_t trend = TM_test_namespace::tm_get_trend();
	EXPECT_EQ( DISP_MSG_UP, trend );

}
