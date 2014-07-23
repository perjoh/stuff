// RaytracerTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest.h"
#include "../src/BasicTypes.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

