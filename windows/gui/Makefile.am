# libguestfs
# Copyright (C) 2013-2026 Red Hat Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

include $(top_srcdir)/subdir-rules.mk

bin_PROGRAMS = windows-pca-gui

windows_pca_gui_SOURCES = \
	ui.cpp \
	$(NULL)
windows_pca_gui_CXXFLAGS = \
	$(WARNINGS_CFLAGS) \
	$(WX_CFLAGS) \
	$(NULL)
windows_pca_gui_LDADD = \
	$(WX_LIBS) \
	$(NULL)

# Recent versions of Wine no longer look for DLLs along the path.
# Instead you have to copy the DLLs into the binary directory.  This
# list of DLLs will only work for a specific, recent version of
# Fedora.  This is all completely stupid, but here we are.
DLLS = \
	libgcc_s_dw2-1.dll \
	libgcc_s_seh-1.dll \
	libjpeg-62.dll \
	libpng16-16.dll \
	libstdc++-6.dll \
	libtiff-6.dll \
	libwinpthread-1.dll \
	wxbase30u_gcc_custom.dll \
	wxmsw30u_core_gcc_custom.dll \
	zlib1.dll \
	$(NULL)

maintainer-dll-links:
	for f in $(DLLS); do rm -f $$f ; $(LN_S) $(bindir)/$$f; done
