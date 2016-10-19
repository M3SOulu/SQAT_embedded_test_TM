/*
 * gtest_inc.h
 *
 *  Created on: May 29, 2016
 *      Author: timppa
 */

#ifndef TEST_GTEST_INC_H_
#define TEST_GTEST_INC_H_

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wextra"
#endif

#include "gtest/gtest.h"

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

TEST_F(LPC_SWM,swm_is_not_initialized_if_SYSCON_param_is_null){
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	Expect_EQ("same",trend);
}

TEST_F(LPC_SWM,swm_is_not_initialized_if_SYSCON_param_is_null){
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	Expect_EQ("ames",trend);
}

TEST_F(LPC_SWM,swm_is_not_initialized_if_SYSCON_param_is_null){
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	Expect_EQ("mesa",trend);
}

TEST_F(LPC_SWM,swm_is_not_initialized_if_SYSCON_param_is_null){
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	Expect_EQ("esam",trend);
}

TEST_F(LPC_SWM,swm_is_not_initialized_if_SYSCON_param_is_null){
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	Expect_EQ("up",trend);
}

TEST_F(LPC_SWM,swm_is_not_initialized_if_SYSCON_param_is_null){
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	Expect_EQ("pu",trend);
}

TEST_F(LPC_SWM,swm_is_not_initialized_if_SYSCON_param_is_null){
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	Expect_EQ("down",trend);
}

TEST_F(LPC_SWM,swm_is_not_initialized_if_SYSCON_param_is_null){
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	Expect_EQ("ownd",trend);
}

TEST_F(LPC_SWM,swm_is_not_initialized_if_SYSCON_param_is_null){
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	Expect_EQ("wndo",trend);
}

TEST_F(LPC_SWM,swm_is_not_initialized_if_SYSCON_param_is_null){
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	trend = SWM_LPC::i2c_write(1,LPC_SWM);
	Expect_EQ("ndow",trend);
}

#endif /* TEST_GTEST_INC_H_ */
