include Makefile.inc

.PHONY: all
all: kernel

.PHONY: clean
clean:
	-$(MAKE) -C kernel clean
	-rm $(BUILD_DIR)/kernel

.PHONY: kernel
kernel:
	cd kernel && $(MAKE) && cd ..
	mv kernel/kernel $(BUILD_DIR)

.PHONY: qemu-run
qemu-run: kernel
	$(QEMU) -kernel $(BUILD_DIR)/kernel

.PHONY: bochs-run
bochs-run: image-update
	$(BOCHS) -q

.PHONY: image-update
image-update: kernel
	-sudo umount $(TMP_MOUNT_POINT) # Umount everything if it's already mounted ;)
	-sudo losetup -d /dev/loop1     #
	sudo losetup /dev/loop1 $(DISK_IMAGE)
	sudo mount -o loop /dev/loop1 $(TMP_MOUNT_POINT)
	sudo cp $(BUILD_DIR)/kernel $(TMP_MOUNT_POINT)
	sudo umount $(TMP_MOUNT_POINT)
	sudo losetup -d /dev/loop1
