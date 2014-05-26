include Makefile.inc

.PHONY: all
all: kernel

.PHONY: clean
clean:
	-$(MAKE) -C kernel clean
	-rm $(BUILD_DIR)/kernel

.PHONY: kernel
kernel:
	$(MAKE) -C kernel
	mv kernel/kernel $(BUILD_DIR)


qemu-test: kernel
	$(QEMU) -kernel $(BUILD_DIR)/kernel
