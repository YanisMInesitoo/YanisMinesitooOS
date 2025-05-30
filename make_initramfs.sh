# Este script crea un initramfs personalizado con un mensaje de bienvenida para YanisMinesitoo OS
mkdir -p initramfs/bin
cp ../init initramfs/init
chmod +x initramfs/init
cp ../busybox initramfs/bin/busybox
chmod +x initramfs/bin/busybox
# Crear enlaces simbólicos para los comandos más comunes
cd initramfs/bin
for i in sh ls cat echo uname dmesg mount ps; do ln -sf busybox $i; done
cd ../..
cd initramfs
find . | cpio -H newc -o | gzip > ../initramfs.img
cd ..
cp ../nano initramfs/bin/nano
cp ../wget initramfs/bin/wget
cp ../curl initramfs/bin/curl
cp ../tar initramfs/bin/tar
cp ../gzip initramfs/bin/gzip
cp ../dpkg initramfs/bin/dpkg
chmod +x initramfs/bin/nano initramfs/bin/wget initramfs/bin/curl initramfs/bin/tar initramfs/bin/gzip initramfs/bin/dpkg
