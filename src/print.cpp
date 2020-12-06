// SPDX-License-Identifier: GPL-2.0-or-later

#include <chrono>
#include <fmt/chrono.h>
#include <fmt/core.h>

#include "measurement.hpp"
#include "print.hpp"
#include "residency.hpp"

void Print::print_raw(Residency::Type type)
{
	std::chrono::microseconds usecs = Residency::get_residency(type);
	fmt::print("{}\n", usecs.count());
}

void Print::print(Residency::Type type)
{
	std::chrono::microseconds usecs = Residency::get_residency(type);

	switch (type) {
	case Residency::Type::CPU:
		fmt::print("CPU:    {:%H:%M:%S}\n", usecs);
		break;
	case Residency::Type::SYSTEM:
		fmt::print("SYSTEM: {:%H:%M:%S}\n", usecs);
		break;
	case Residency::Type::S0IX:
		fmt::print("S0IX:   {:%H:%M:%S}\n", usecs);
		break;
	default:
		break;
	}
}

void Print::print_all(void)
{
	Print::print(Residency::Type::CPU);
	Print::print(Residency::Type::SYSTEM);
	Print::print(Residency::Type::S0IX);
}

void Print::print_diff(Measurement a, Measurement b)
{
	std::chrono::time_point<std::chrono::system_clock> time_a(a.time);
	std::chrono::time_point<std::chrono::system_clock> time_b(b.time);

	fmt::print("FROM:     {:%Y-%m-%d %H:%M:%S}\n", time_a);
	fmt::print("TO:       {:%Y-%m-%d %H:%M:%S}\n", time_b);
	fmt::print("DURATION: {:%H:%M:%S}\n", time_b - time_a);
	fmt::print("CPU:      {:%H:%M:%S}\n", b.cpu - a.cpu);
	fmt::print("SYSTEM:   {:%H:%M:%S}\n", b.system - a.system);
	fmt::print("S0IX:     {:%H:%M:%S}\n", b.s0ix - a.s0ix);
}
