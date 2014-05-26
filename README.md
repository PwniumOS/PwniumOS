# PwniumOS

**PwniumOS** aims to be a complete, free and fast operating system.

A short list of things possible with **PwniumOS** :
- 32-bits protected mode.
- Pre-emptive multitasking & multi-threading
- Memory management
- FAT32 file system and large disk support (LBA)
- Long file names support.
- Easy multiboot with other operating systems (Windows,Linux...)
- Responsive GUI with resolutions up to 1280x1024, 16 million colors
- Network functionality(TCP/IP)
- etc.

**PwniumOS** is developed by hackers for educational purpose

### Test it
Install [qemu](http://qemu.org) or [Bochs](http://bochs.sourceforge.net)

1. ```git clone https://github.com/PwniumOS/PwniumOS.git```
2. ```cd PwniumOS```
3. ```make qemu-test``` _// test using qemu_
3. ```make bochs-test``` _// test using bochs_ (not supported yet)
