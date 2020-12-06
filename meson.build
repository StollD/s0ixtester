project(
	's0ixtester', 'cpp',
	version: '0.1',
	license: 'GPL-2.0-or-later',
	default_options: [
		'cpp_std=c++17',
		'warning_level=3',
		'werror=true',
		'default_library=static',
	]
)

sources = [
	'src/help.cpp',
	'src/main.cpp',
	'src/measurement.cpp',
	'src/print.cpp',
	'src/residency.cpp',
]

deps = [
	dependency('fmt', version: '>=7.1.0', fallback: [
		'fmt',
		'fmt_dep'
	], required: true),
]

executable('s0ixtester', sources, dependencies: deps, install: true)
