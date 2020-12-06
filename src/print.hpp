// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef _S0IXTESTER_PRINT_HPP_
#define _S0IXTESTER_PRINT_HPP_

#include "measurement.hpp"
#include "residency.hpp"

class Print
{
public:
	static void print_diff(Measurement a, Measurement b);
	static void print_raw(Residency::Type type);
	static void print(Residency::Type type);
	static void print_all(void);
};

#endif // _S0IXTESTER_PRINT_HPP_
