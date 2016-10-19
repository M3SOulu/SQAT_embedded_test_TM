/*
 * display_test.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: timppa
 */

#include "gtest_inc.h"

#include "chip.h"

#include "tm.h"

namespace TM2_test_namespace {
	//
	// dependency injection
	//
	int i2c_read(int addr,char* cmd,int cmdlen,char* buffer,int length);
	//
	// dependency injection
	//
	void tm_update_average(int temp);
	//
	// dependency injection
	//
// YOU MAY ADD MORE
	//
	// target code is included instead of (direct) compilation:
	//   This allows to cut the dependencies (such as I2C_write above)
	//
	#include "../src/tm2.cpp"
}

using ::testing::Test;

#define PLAY_I2C_READ_VALUES 10
#define RECORD_TEMP_VALUES    8

/**********************************************************************
 *
 * GoogleTest test-class for 7-segment display testing
 *
 **********************************************************************/
class unittest_TM2 : public Test
{
public:
	//
	// constructor just resets attributes to some default values
	//
	unittest_TM2()
	{
		mRc = -1;
	}
	virtual ~unittest_TM2(){}
protected:
	//
	// SetUp performs the per-test initialization/setup of test instance
	//
	virtual void SetUp()
	{
		mRc = -1;
		memset(mPlay_i2c_read_values,0,
				sizeof(mPlay_i2c_read_values));
		unittest_TM2::mPlay_index = 0;
		unittest_TM2::mRecord_i2c_addr = 0;
		unittest_TM2::mRecord_i2c_length = 0;
		memset(unittest_TM2::mRecord_update_average_temp,0,
				sizeof(unittest_TM2::mRecord_update_average_temp));
		unittest_TM2::mRecord_index = 0;
	}
	//
	// TearDown cleans-up test instance
	//
	virtual void TearDown()
	{
	}
	//
	// add one (char) value to i2c_read data for mock to return
	//
	void add_i2c_read_value(int value,int index)
	{
		if ( index < 10 && index>=0 ){
			mPlay_i2c_read_values[ index ] = value;
		}
	}
	void set_i2c_read_indx(int i)
	{
		mPlay_index = i;
	}
	int get_temp_value_at_index(int index)
	{
		if ( index>=0 && index < RECORD_TEMP_VALUES )
			return unittest_TM2::mRecord_update_average_temp[index];
		else return -1;
	}
protected:

	int mRc;
	//
	// this "friend" access lets the "TM_test_namespace::I2C_write" code below
	//   to access the variables used to record the parameters
	//
	friend int TM2_test_namespace::i2c_read(int addr,char* cmd,int cmdlen,char* buffer,int length);
	static char mPlay_i2c_read_values[PLAY_I2C_READ_VALUES];
	static int mPlay_index;
	static int mRecord_i2c_addr;
	static int mRecord_i2c_length;
	friend void TM2_test_namespace::tm_update_average(int temp);
	static int mRecord_update_average_temp[RECORD_TEMP_VALUES];
	static int mRecord_index;
};

//
// note: this data is reset in SetUp
//
char unittest_TM2::mPlay_i2c_read_values[PLAY_I2C_READ_VALUES]={
		0,0,0,0,0,
		0,0,0,0,0
};

int unittest_TM2::mPlay_index = 0;
int unittest_TM2::mRecord_i2c_addr = 0;
int unittest_TM2::mRecord_i2c_length = 0;

//
// note: this data is reset in SetUp
//
int unittest_TM2::mRecord_update_average_temp[RECORD_TEMP_VALUES] = {
		0,0,0,0,
		0,0,0,0
};
int unittest_TM2::mRecord_index = 0;

//
// DEPENDENCY
//
// i2c_read mock: this provides input values you have submitted
//   via add_i2c_read_value() above
//
int TM2_test_namespace::i2c_read(int addr,char* cmd,int cmdlen,char* buffer,int length)
{
	unittest_TM2::mRecord_i2c_addr = addr;
	unittest_TM2::mRecord_i2c_length = length;

	if ( buffer!=0 && length>0 ){
		buffer[0]=unittest_TM2::mPlay_i2c_read_values[ unittest_TM2::mPlay_index ];
		//
		// increment and loop automatically, you may want to disable this
		//
		unittest_TM2::mPlay_index++;
		if ( unittest_TM2::mPlay_index == PLAY_I2C_READ_VALUES )
			unittest_TM2::mPlay_index=0;
		return 1;
	}
	return -1;
}

//
// DEPENDENCY
//
// this records the last 8 calls to tm_update_average (if used)
//
void TM2_test_namespace::tm_update_average(int temp)
{
	int index = unittest_TM2::mRecord_index;
	unittest_TM2::mRecord_update_average_temp[ index ] = temp;
	index++;
	if ( index>RECORD_TEMP_VALUES )index=0;
	unittest_TM2::mRecord_index = index;
}

/**********************************************************************
 *
 * quick verification of test fixture
 * - this helps detect problems in test setup
 *
 **********************************************************************/
TEST_F( unittest_TM2, test_fixture )
{
	EXPECT_EQ( -1, mRc );
}

/**********************************************************************
 *
 * quick verification of test setup/construction
 * - this helps detect problems in test setup
 *
 **********************************************************************/

TEST_F( unittest_TM2, test_constructor )
{
}

/**********************************************************************
 *
 * test cases: these are examples
 *
 **********************************************************************/

TEST_F( unittest_TM2, reads_temperature_from_i2c )
{
	const int i2cvalue_1 = 12;
	const int i2cvalue_2 = 55;
	//
	// TODO: remove?
	//
	add_i2c_read_value( i2cvalue_1,0 );
	add_i2c_read_value( i2cvalue_2,1 );

	int temperature = TM2_test_namespace::tm_handle_sensor();

	EXPECT_EQ( -1, temperature );
	EXPECT_EQ( 0, mRecord_i2c_addr );
	EXPECT_EQ( 0, get_temp_value_at_index(0) );

	temperature = TM2_test_namespace::tm_handle_sensor();

	EXPECT_EQ( -1, temperature );
	EXPECT_EQ( 0, mRecord_i2c_addr );
	EXPECT_EQ( 0, get_temp_value_at_index(1) );
}
