#include <multiboot.h>
#include <printf.h>
#include <gdt.h>
#include <idt.h>

void dump_mmap(multiboot_memory_map_t *mmap) {
    printf("base_addr = 0x%x%x,"
    " length = 0x%x%x, type = 0x%x\n",
    mmap->addr >> 32,
    mmap->addr & 0xffffffff,
    mmap->len >> 32,
    mmap->len & 0xffffffff,
    (unsigned) mmap->type);
}

void dump_mboot(multiboot_info_t *mboot) {
    //if (mboot->flags & MULTIBOOT_INFO_CMDLINE)
    //    printf("Command Line: %s\n", mboot->cmdline);
    if (mboot->flags & MULTIBOOT_INFO_MEMORY) {
        printf("Low Memory: %uKb\n", mboot->mem_lower);
        printf("Upper Memory: %uKb\n", mboot->mem_upper);
    }

    if (mboot->flags & MULTIBOOT_INFO_MEM_MAP) {
        multiboot_memory_map_t *mmap = mboot->mmap_addr;
        printf("Memory Map: \n");
        while ((unsigned long) mmap < mboot->mmap_addr + mboot->mmap_length) {
            dump_mmap(mmap);
            mmap = (multiboot_memory_map_t *) ((unsigned long) mmap + mmap->size + sizeof (mmap->size));
        }
    }
}

void main(multiboot_info_t *mboot, int magic, void *esp) {
    monitor_clear();
    printf("Booting...\n");

    dump_mboot(mboot);

    printf("Initializing GDT\n");
    gdt_init();

    printf("Initializing IDT\n");
    idt_init();

    printf("Initializing IRQ\n");
    irq_init();

    printf("Initializing Timer\n");
    timer_init();

    interrupt_enable();

}
