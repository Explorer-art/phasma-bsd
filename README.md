# Phasma BSD
Phasma BSD - simple operating system for x86

### Install tools
For build:
```
sudo apt install gcc nasm make mtools qemu-system grub-pc
```

For debug (Bochs):
```
sudo apt install bochs bochs-x bochs-sdl bochsbios vgabios
```

### Build
```
sudo make
```

### Run
```
make run
```
or
```
qemu-system-x86_64 -drive format=raw,file=phasma.img,if=ide,index=0
```