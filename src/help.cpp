// SPDX-License-Identifier: GPL-2.0-or-later

#include <fmt/core.h>

#include "help.hpp"

void Help::print(void)
{
	fmt::print("usage: s0ixtester print [residency] ...\n");
	fmt::print("\n");
	fmt::print("Arguments:\n");
	fmt::print("  residency: The residency to print (cpu, system, s0ix)\n");
	fmt::print("             Defaults to printing all of them\n");
}

void Help::get(void)
{
	fmt::print("usage: s0ixtester get residency ...\n");
	fmt::print("\n");
	fmt::print("Arguments:\n");
	fmt::print("  residency: The residency to fetch (cpu, system, s0ix)\n");
}

void Help::compare(void)
{
	fmt::print("usage: s0ixtester compare [a] [b] ...\n");
	fmt::print("\n");
	fmt::print("Arguments:\n");
	fmt::print("  a: The earlier measurement to be used for comparison\n");
	fmt::print("     Defaults to the second last one\n");
	fmt::print("  b: The later measurement to be used for comparison\n");
	fmt::print("     Defaults to the last one\n");
}

void Help::all(void)
{
	fmt::print("usage: s0ixtester {{print,get,measure,compare,help}} ...\n");
	fmt::print("\n");
	fmt::print("Commands:\n");
	fmt::print("  If no command is specified the print command is run\n");
	fmt::print("    print:   Print the residency values in a human readable form\n");
	fmt::print("    get:     Print the raw residency values in microseconds\n");
	fmt::print("    measure: Save the current residency values into a new measurement\n");
	fmt::print("    compare: Compare previous measurements\n");
	fmt::print("    help:    Print help (of a subcommand)\n");
}
