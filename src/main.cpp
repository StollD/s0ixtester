// SPDX-License-Identifier: GPL-2.0-or-later

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <iostream>
#include <sstream>
#include <string>

#include "help.hpp"
#include "measurement.hpp"
#include "print.hpp"
#include "residency.hpp"

int help(int argc, char **argv)
{
	if (argc < 3 || strcmp(argv[1], "help") != 0) {
		Help::all();
		return 0;
	}

	if (strcmp(argv[2], "print") == 0) {
		Help::print();
		return 0;
	}

	if (strcmp(argv[2], "get") == 0) {
		Help::get();
		return 0;
	}

	if (strcmp(argv[2], "compare") == 0) {
		Help::compare();
		return 0;
	}

	Help::all();
	return 0;
}

int print(int argc, char **argv)
{
	if (argc < 3) {
		Print::print_all();
		return 0;
	}

	if (strcmp(argv[2], "cpu") == 0) {
		Print::print(Residency::Type::CPU);
		return 0;
	}

	if (strcmp(argv[2], "system") == 0) {
		Print::print(Residency::Type::SYSTEM);
		return 0;
	}

	if (strcmp(argv[2], "s0ix") == 0) {
		Print::print(Residency::Type::S0IX);
		return 0;
	}

	return 0;
}

int get(int argc, char **argv)
{
	if (argc < 3)
		return help(argc, argv);

	if (strcmp(argv[2], "cpu") == 0) {
		Print::print_raw(Residency::Type::CPU);
		return 0;
	}

	if (strcmp(argv[2], "system") == 0) {
		Print::print_raw(Residency::Type::SYSTEM);
		return 0;
	}

	if (strcmp(argv[2], "s0ix") == 0) {
		Print::print_raw(Residency::Type::S0IX);
		return 0;
	}

	return 0;
}

int measure(void)
{
	if (!Measurement::take()) {
		fmt::print(stderr, "ERROR: Failed to take measurement\n");
		return EXIT_FAILURE;
	}

	return 0;
}

int compare(int argc, char **argv)
{
	std::uint32_t b = Measurement::latest();
	std::uint32_t a = b - 1;

	if (argc > 2) {
		std::stringstream s(argv[2]);
		s >> a;
	}

	if (argc > 3) {
		std::stringstream s(argv[3]);
		s >> b;
	}

	Measurement m1;
	Measurement m2;

	if (!Measurement::load(a, &m1) || !Measurement::load(b, &m2)) {
		fmt::print(stderr, "ERROR: Failed to load measurement\n");
		return EXIT_FAILURE;
	}

	Print::print_diff(m1, m2);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc < 2 || strcmp(argv[1], "print") == 0)
		return print(argc, argv);

	if (strcmp(argv[1], "get") == 0)
		return get(argc, argv);

	if (strcmp(argv[1], "measure") == 0)
		return measure();

	if (strcmp(argv[1], "compare") == 0)
		return compare(argc, argv);

	return help(argc, argv);
}
