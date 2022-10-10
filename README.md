# Compile and run egos-2000

You can use MacOS, Linux or Windows. 
For MacOS on the Apple M1 chip, just download and run the `x86-64` version of the toolchain and MacOS will transparently translate the binary with Rosetta.
For Windows users, use WSL (Windows Subsystem for Linux) in step1-3.

Here are the tutorial videos for [MacOS](https://youtu.be/v8PW2N5edCc), [Linux](https://youtu.be/JDApdvnnz4A) and [Windows](https://youtu.be/VTTynr9MZRg).

## Step1: Setup the compiler and compile egos-2000

Setup your working directory and name it as `$EGOS`.

```shell
> export EGOS=/home/yunhao/egos
> cd $EGOS
> git clone https://github.com/yhzhang0128/egos-2000.git
# now the code repository is at $EGOS/egos-2000
```

Download the [SiFive riscv-gcc compiler](https://github.com/sifive/freedom-tools/releases/tag/v2020.04.0-Toolchain.Only) to the working directory `$EGOS`.

```shell
> cd $EGOS
> tar -zxvf riscv64-unknown-elf-gcc-8.3.0-2020.04.1-x86_64-xxx-xxx.tar.gz
> export PATH=$PATH:$EGOS/riscv64-unknown...../bin
> cd $EGOS/egos-2000
> make
mkdir -p build/debug build/release
-------- Compile the Apps Layer --------
......
-------- Compile the Grass Layer --------
......
-------- Compile the Earth Layer --------
......
```


`build/release` holds the ELF format binary executables and `build/debug` holds the human readable assembly files.

## Step2: Create the disk and bootROM images

Make sure you have a C compiler (i.e., the `cc` command) in your shell environment.

```shell
> cd $EGOS/egos-2000
> make install
-------- Create the Disk Image --------
......
[INFO] Finish making the disk image
-------- Create the BootROM Image --------
......
[INFO] Finish making the bootROM binary
[INFO] Finish making the bootROM mcs image
```

This will create `disk.img`, `bootROM.bin` and `bootROM.mcs` in the `tools` directory.
To program `disk.img` to a microSD card:

```shell
# Find your microSD card in /dev
> sudo fdisk -l
......
Disk /dev/sdb: 117.8 GiB, 126437294080 bytes, 246947840 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
...
# Say it is /dev/sdb as shown above
> sudo dd if=$EGOS/egos-2000/tools/disk.img of=/dev/sdb
8192+0 records in
8192+0 records out
4194304 bytes (4.2 MB, 4.0 MiB) copied, 0.377515 s, 11.1 MB/s
```

Instead of `dd`, you can also use GUI softwares like [balena Etcher](https://www.balena.io/etcher/) to program `disk.img` to your microSD card.

## Step3: Run egos-2000 on the QEMU emulator

Download the [QEMU emulator for egos-2000](https://github.com/yhzhang0128/freedom-tools/releases/tag/v2022.10.6) to the working directory `$EGOS`.

```shell
> cd $EGOS
> tar -zxvf riscv-qemu-xxx.tar.gz
> export PATH=$PATH:$EGOS/riscv-qemu-5.2.0-...../bin
> cd $EGOS/egos-2000
> make qemu
-------- Simulate on QEMU-RISCV --------
cp build/release/earth.elf tools/qemu/qemu.elf
riscv64-unknown-elf-objcopy --update-section .image=tools/disk.img tools/qemu/qemu.elf
qemu-system-riscv32 -readconfig tools/qemu/sifive-e31.cfg -kernel tools/qemu/qemu.elf -nographic
[INFO] -----------------------------------
[INFO] Start to initialize the earth layer
......
```


## Step4: Run egos-2000 on the Arty board

### Step4.1 Program the Arty on-board ROM

#### MacOS or Linux

Download [OpenOCD v0.11.0-1](https://github.com/xpack-dev-tools/openocd-xpack/releases/tag/v0.11.0-1) to the working directory `$EGOS`.

```shell
> cd $EGOS
> tar -zxvf xpack-openocd-0.11.0-1-xxx-xxx.tar.gz
> export PATH=$PATH:$EGOS/xpack-openocd-0.11.0-1-xxx-xxx/bin
> cd $EGOS/egos-2000
> make program
-------- Program the on-board ROM --------
cd tools/openocd; time openocd -f 7series.txt
......
Info : sector 188 took 223 ms
Info : sector 189 took 223 ms
Info : sector 190 took 229 ms
Info : sector 191 took 243 ms  # It will pause at this point for a while
Info : Found flash device 'micron n25q128' (ID 0x0018ba20)

real    2m51.019s
user    0m11.540s
sys     0m37.338s

```

#### Windows or Linux
Install Vivado Lab Edition which can be downloaded [here](https://www.xilinx.com/support/download.html).
You may need to register a Xilinx account, but the software is free.

1. Open Vivado Lab Edition and click "Open Hardware Manager"
2. Click "Open target" and "Auto Connect"; the Arty board should appear in the "Hardware" window
3. In the "Hardware" window, right click `xc7a35t` and click "Add Configuration Memory Device"
4. Choose memory device "mt25ql128-spi-x1_x2_x4" and click "Program Configuration Memory Device"
5. In the "Configuration file" field, choose the `bootROM.mcs` file compiled in step 2
6. Click "OK" and wait for the program to finish

In **4**, new versions of Arty may use "s25fl128sxxxxxx0" as memory device. 
If you choose the wrong one, **6** will tell you.

In **2**, if the Arty board doesn't appear, try to install [Digilent Adept](https://digilent.com/reference/software/adept/start) or reinstall the USB cable drivers following [these instructions](https://support.xilinx.com/s/article/59128?language=en_US). If it still doesn't work, it may be an issue with Vivado and please [contact Xilinx](https://support.xilinx.com/s/topic/0TO2E000000YKXgWAO/programmable-logic-io-bootconfiguration?language=en_US).

![This is an image](screenshots/vivado.png)

### Step4.2: Connect with egos-2000

1. Press the `program` red button on the left-top corner of the Arty board
2. To restart, press the `reset` red button on the right-top corner 
3. For Linux users, type in your shell
```shell
> sudo chmod 666 /dev/ttyUSB1
> screen /dev/ttyUSB1 115200
[INFO] -----------------------------------
[INFO] Start to initialize the earth layer
[SUCCESS] Finished initializing the tty device
[CRITICAL] Choose a disk:
  Enter 0: use the microSD card
  Enter 1: use the on-board flash ROM @0x20800000
......
```
4. For Mac users, use the same commands but check your `/dev` directory for the  device name (e.g., `/dev/tty.usbserial-xxxxxx`)
5. For Windows users, find the board in your "Device Manager" (e.g., COM4) and use `PuTTY` to connect with the board:

![This is an image](screenshots/putty.png)



## A Minimal Operating System on a RISC-V Board and the QEMU Emulator

With only **2000** lines of code, **egos-2000** implements every component of a functional operating system.
It can run on a RISC-V board or a software emulator called QEMU.
The vision of this project is to help **every** college student read **all** the code of an operating system within **one** semester.

![This is an image](references/screenshots/egos-2000.jpg)
Note: `cloc` is used to [count lines of code](https://github.com/AlDanial/cloc) above. Try `cloc egos-2000 --exclude-ext=md` which excludes the markdown documents in the count.

## Earth and Grass Operating System 2000

We use **egos-2000** as our teaching operating system at Cornell. It adopts a 3-layer architecture.

* The **earth layer** implements hardware-specific abstractions.
    * tty and disk device interfaces
    * cpu interrupt and memory management interfaces
* The **grass layer** implements hardware-independent abstractions.
    * processes, system calls and inter-process communication
* The **application layer** implements file system, shell and user commands.

The definitions of `struct earth` and `struct grass` in [**egos.h**](library/egos.h) specify the interfaces of these layers.

### Hardware Requirements
* an Artix-7 35T [Arty FPGA development board](https://www.xilinx.com/products/boards-and-kits/arty.html)
* a microUSB cable (e.g., [microUSB-to-USB-C](https://www.amazon.com/dp/B0744BKDRD?psc=1&ref=ppx_yo2_dt_b_product_details))
* [optional] a [microSD Pmod](https://digilent.com/reference/pmod/pmodmicrosd/start?redirect=1), a [microSD reader](https://www.amazon.com/dp/B07G5JV2B5?psc=1&ref=ppx_yo2_dt_b_product_details) and a microSD card (e.g., [Sandisk](https://www.amazon.com/dp/B073K14CVB?ref=ppx_yo2_dt_b_product_details&th=1))

Don't worry if the hardware is not available to you. You can also use the software emulator QEMU.

### Usages and Documentation

For compiling and running egos-2000, please read [USAGES.md](references/USAGES.md) or watch the tutorial videos ([MacOS](https://youtu.be/v8PW2N5edCc), [Linux](https://youtu.be/JDApdvnnz4A) or [Windows](https://youtu.be/VTTynr9MZRg)).
[This document](references/README.md) further introduces the teaching plans, architecture and development history.

The [RISC-V instruction set manual](references/riscv-privileged-v1.10.pdf) introduces the privileged registers used by egos-2000.
The [SiFive FE310 manual](references/sifive-fe310-v19p04.pdf) introduces the memory map, especially the GPIO, UART and SPI bus controllers.

For any questions, please contact [Yunhao Zhang](https://dolobyte.net/).

## Acknowledgements

Many thanks to [Robbert van Renesse](https://www.cs.cornell.edu/home/rvr/) and [Lorenzo Alvisi](https://www.cs.cornell.edu/lorenzo/) for their support.
Many thanks to [Meta](https://about.facebook.com/meta/) for supporting me with a [fellowship](https://research.facebook.com/fellows/zhang-yunhao/).
Many thanks to all CS4411 students at Cornell over the years for helping improve this course.
