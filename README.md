# Virt-v2v / QEMU preconversion assistant

https://github.com/libguestfs/preconversion-assistant

[Virt-v2v](https://github.com/libguestfs/virt-v2v) is a program that
converts a single guest from a foreign hypervisor to run on KVM.  It
can read Linux and Windows guests running on VMware, Xen, Hyper-V and
some other hypervisors, and convert them to KVM.  It can modify the
guest to make it bootable on KVM and install virtio drivers so it will
run quickly.

The virt-v2v / QEMU preconversion assistant (**PCA**) is an
**optional** tool that can be run inside the guest before conversion.
It has several functions (all optional):

* Preinstall virtio drivers.  For Windows, install [virtio-win
  drivers](https://github.com/virtio-win).  For Linux, rebuild the
  initramfs so it contains virtio drivers.  If this is successful,
  virt-v2v will notice and skip this step during conversion.

* Replace device names in Linux `/etc` (configuration files) with
  UUIDs.

* Collect information on network configuration which is hard or
  impossible to collect during conversion.  This allows a more
  faithful network configuration on the target.

* Recover UEFI variables and TPM state to allow conversion of
  encrypted and secure boot guests.

* Warn if the guest cannot be converted by virt-v2v.

The state of preconversion by PCA is written into the filesystem, and
may cause virt-v2v to skip or modify conversion steps.

Note PCA is not a replacement for virt-v2v.  It is intended that
virt-v2v is run in the normal way afterwards.  See [the virt-v2v
documentation](https://libguestfs.org/virt-v2v.1.html).

## Building

### Building PCA for Linux

Requirements:

* GCC, G++

* WxWidgets for GTK, version 3 (Fedora: `wxGTK-devel`)

Build:

 autoreconf -fi
 ./configure
 make

### Building PCA for Windows (cross-compilation from Linux)

Requirements:

* [GCC and G++ from the mingw-w64
  toolchain](https://www.mingw-w64.org).  The developers use the
  [Fedora MinGW tools](https://fedoraproject.org/wiki/MinGW/Tutorial)

* WxWidgets, version 3 (Fedora: `mingw32-wxWidgets3` or
  `mingw64-wxWidgets3`)

* [virtio-win guest tools installer](https://github.com/virtio-win/virtio-win-guest-tools-installer)
  MSI

Build:

 autoreconf -fi
 mkdir build-win
 pushd build-win
 mingw32-configure
 make
 popd

Notes:

* You can build either 32- or 64-bit binaries, but the 32-bit binaries
  are more compatible with older versions of Windows.

* You can share a git clone with Linux native builds, but you have to
  build the Linux and Windows versions in separate build directories.

### Building PCA for Windows (native build)

*Instructions to follow*
