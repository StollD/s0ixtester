// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef _S0IXTESTER_MEASUREMENT_HPP_
#define _S0IXTESTER_MEASUREMENT_HPP_

#include <chrono>
#include <cstdint>
#include <ctime>

class Measurement
{
public:
	std::chrono::seconds time;
	std::chrono::microseconds cpu;
	std::chrono::microseconds system;
	std::chrono::microseconds s0ix;

	std::uint32_t id;

	static bool take(void);
	static bool load(std::uint32_t id, Measurement *m);
	static std::uint32_t latest(void);

private:
	static bool save(Measurement m);
};

#endif // _S0IXTESTER_MEASUREMENT_HPP_
