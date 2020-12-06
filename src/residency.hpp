// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef _S0IXTESTER_RESIDENCY_HPP_
#define _S0IXTESTER_RESIDENCY_HPP_

#include <chrono>
#include <string>

class Residency
{
public:
	enum Type {
		CPU,
		SYSTEM,
		S0IX
	};

	static std::chrono::microseconds get_residency(Type type);

private:
	static bool read_usecs(std::string path,
			std::chrono::microseconds *usecs);
	static std::chrono::microseconds get_from_paths(
		const std::string *paths, std::size_t size);
};

#endif // _S0IXTESTER_RESIDENCY_HPP_
