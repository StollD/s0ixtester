// SPDX-License-Identifier: GPL-2.0-or-later

#include <chrono>
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <sstream>

#include "measurement.hpp"
#include "residency.hpp"

bool Measurement::load(std::uint32_t id, Measurement *m)
{
	std::uint64_t time;
	std::uint64_t cpu;
	std::uint64_t system;
	std::uint64_t s0ix;

	std::ifstream stream;

	stream.open(fmt::format("/tmp/s0ixtester/{}", id));
	if (!stream.is_open())
		return false;

	stream >> time;
	stream >> cpu;
	stream >> system;
	stream >> s0ix;

	m->time = std::chrono::seconds(time);
	m->cpu = std::chrono::microseconds(cpu);
	m->system = std::chrono::microseconds(system);
	m->s0ix = std::chrono::microseconds(s0ix);

	stream.close();
	return true;
}

bool Measurement::save(Measurement m)
{
	std::ofstream stream;

	stream.open(fmt::format("/tmp/s0ixtester/{}", m.id));
	if (!stream.is_open())
		return false;

	stream << m.time.count() << " "
	       << m.cpu.count() << " "
	       << m.system.count() << " "
	       << m.s0ix.count();

	stream.close();
	return true;
}

std::uint32_t Measurement::latest(void)
{
	std::uint32_t max = 0;

	if (!std::filesystem::exists("/tmp/s0ixtester"))
		std::filesystem::create_directory("/tmp/s0ixtester");

	std::filesystem::directory_iterator itr("/tmp/s0ixtester");

	for (auto& p : itr) {
		if (!p.is_regular_file())
			continue;

		std::uint32_t n = 0;
		std::stringstream s(p.path().filename());

		s >> n;
		if (n > max)
			max = n;
	}

	return max;
}

bool Measurement::take(void)
{
	Measurement m;

	m.id = Measurement::latest() + 1;
	m.time = std::chrono::seconds(std::time(nullptr));

	m.cpu = Residency::get_residency(Residency::Type::CPU);
	m.system = Residency::get_residency(Residency::Type::SYSTEM);
	m.s0ix = Residency::get_residency(Residency::Type::S0IX);

	return Measurement::save(m);
}
