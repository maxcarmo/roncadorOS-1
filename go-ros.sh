# Executa o RoS no Linux com uma versão mais recente do Qemu (compilada pelo SiFive)
# https://www.sifive.com/software
QEMU=/home/vagrant/riscv-qemu-4.2.0-2020.04.0-x86_64-linux-ubuntu14/bin/qemu-system-riscv64
$QEMU -append 'console=ttyS0'  -nographic -serial mon:stdio -smp 4 -machine virt -bios none -kernel kernel
