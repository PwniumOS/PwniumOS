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

.PHONY: qemu-test
qemu-test: kernel
	$(QEMU) -kernel $(BUILD_DIR)/kernel
