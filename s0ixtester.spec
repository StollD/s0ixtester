%global debug_package %{nil}
%global __meson_wrap_mode default

Name: s0ixtester
Version: 0.1
Release: 1%{?dist}
Summary: Stupid s0ix residency tester
License: GPLv2+

URL: https://github.com/StollD/s0ixtester
Source: {{{ git_dir_pack }}}

Source1: %{name}-sleep

BuildRequires: meson
BuildRequires: g++
BuildRequires: fmt-devel

Requires: fmt

%description
Stupid S0ix residency tester

%prep
{{{ git_dir_setup_macro }}}

%build
%meson
%meson_build

%install
%meson_install

install -Dpm 0755 %{SOURCE1} \
	%{buildroot}/usr/lib/systemd/system-sleep/%{name}-sleep

%check
%meson_test

%files
%license LICENSE
%{_bindir}/%{name}
/usr/lib/systemd/system-sleep/%{name}-sleep
