#!/bin/sh
UBOOT=/root/workspace/my_navilnux/gumstix_uboot
KERNEL=/root/workspace/my_navilnux/navilnux
IMG=$(pwd)

# clean old files
rm u-boot.bin -f
rm flash.bin -f
rm navilnux_gum_img -f
rm navilnuximg -f
rm navilnux.jffs2 -f

# copy images
cp $UBOOT/tools/mkimage .
cp $KERNEL/navilnux_gum_img .
cp $UBOOT/u-boot.bin .

# u-boot 이미지 재조합. 젤 첨에 /dev/zero 넣어줘야 함
dd if=/dev/zero of=flash.bin bs=4096 count=4096
dd if=u-boot.bin of=flash.bin bs=4096 conv=notrunc

# navlinux의 커널 이미지를 uImage 형식으로 변환 (부트로더에서 읽을 수 있는 형태)
# -A [architecture]
# -O [os]
# -T [image type]
# -C [compression type]
# -a [load address]
# -e [entry point]
# -n [image name]
./mkimage -A arm -O linux -T kernel -C none -a a0008000 -e a0008000 -n 'Navilnux 0.0.0.1' -d navilnux_gum_img uImage
mkdir -p image/boot
mv uImage image/boot/

# ramdisk 만들기. 원래는 util들이 포함되지만 우리는 커널(부트이미지)이미지만 넣기로 하자. boot에 넣어야 부트 이미지로 인식됨.
# -e, --eraseblock=SIZE : raw flash device에서 삭제 단위(블록)의 크기를 지정
# -r, -d, --root=DIR : Build file system from directory DIR
# -P, --squash-perms : Squash permissions, removing write permission for ´group´ and ´other´.
# -o, --output=FILE
mkfs.jffs2 -e 0x20000 -d image -p -o navilnux.jffs2

#파일을 블록 단위로 복사하는 dd 명령어로 '부트로더+커널램디스크이미지'를 하나의 이미지로 합치기
dd of=navilnuximg bs=1k conv=notrunc if=flash.bin
dd of=navilnuximg bs=1k conv=notrunc seek=180 if=navilnux.jffs2

#에뮬레이터 실행
qemu-system-arm -machine connex -pflash navilnuximg -nographic