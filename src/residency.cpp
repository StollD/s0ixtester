// SPDX-License-Identifier: GPL-2.0-or-later

#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <system_error>

#include "residency.hpp"

static const std::string CPU_RESIDENCY_PATHS[] = {
	"/sys/devices/system/cpu/cpuidle/low_power_idle_cpu_residency_us",
};

static const std::string S0IX_RESIDENCY_PATHS[] = {
	"/sys/kernel/debug/pmc_core/slp_s0_residency_usec",
};

static const std::string SYSTEM_RESIDENCY_PATHS[] = {
	"/sys/devices/system/cpu/cpuidle/low_power_idle_system_residency_us",
};

bool Residency::read_usecs(std::string path, std::chrono::microseconds *usecs)
{
	std::uint64_t __usecs;
	std::ifstream stream;

	stream.open(path);
	if (!stream.is_open())
		return false;

	stream >> __usecs;
	stream.close();

	*usecs = std::chrono::microseconds(__usecs);
	return true;
}

std::chrono::microseconds Residency::get_from_paths(const std::string *paths,
		std::size_t size)
{
	std::chrono::microseconds usecs(0);

	for (size_t i = 0; i < size; i++) {
		if (Residency::read_usecs(paths[i], &usecs))
			break;
	}

	return usecs;
}

std::chrono::microseconds Residency::get_residency(Type type)
{
	const std::string *paths;
	std::size_t size;

	switch(type) {
	case Type::CPU:
		paths = CPU_RESIDENCY_PATHS;
		size = std::size(CPU_RESIDENCY_PATHS);
		break;
	case Type::SYSTEM:
		paths = SYSTEM_RESIDENCY_PATHS;
		size = std::size(SYSTEM_RESIDENCY_PATHS);
		break;
	case Type::S0IX:
		paths = S0IX_RESIDENCY_PATHS;
		size = std::size(S0IX_RESIDENCY_PATHS);
		break;
	default:
		return std::chrono::microseconds(0);
	}

	return Residency::get_from_paths(paths, size);
}
