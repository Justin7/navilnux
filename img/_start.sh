dd if=/dev/zero of=flash.bin bs=4096 count=4096
dd if=u-boot.bin of=flash.bin bs=4096 conv=notrunc

./mkimage -A arm -O linux -T kernel -C none -a a0008000 -e a0008000 -n 'test' -d navilnux_gum_img uImage
cp uImage img/boot
mkfs.jffs2 -e 0x20000 -d img -p -o os.jffs2
dd of=bootimg bs=1k conv=notrunc if=flash.bin
dd of=bootimg bs=1k conv=notrunc seek=180 if=os.jffs2
#qemu-system-arm -M connex -pflash bootimg -serial stdio
qemu-system-arm -machine connex -pflash bootimg -nographic