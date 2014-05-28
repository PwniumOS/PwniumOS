#include <monitor.h>
#include <vga.h>
#include <multiboot.h>


dump_mmap(multiboot_memory_map_t *mmap)
{
    mprintf ("base_addr = 0x%x%x,"
    " length = 0x%x%x, type = 0x%x\n",
    mmap->addr >> 32,
    mmap->addr & 0xffffffff,
    mmap->len >> 32,
    mmap->len & 0xffffffff,
    (unsigned) mmap->type);
}
void dump_mboot(multiboot_info_t *mboot)
{
    if (mboot->flags & MULTIBOOT_INFO_CMDLINE)
        mprintf("Command Line: %s\n", mboot->cmdline); // not used yet
    if (mboot->flags & MULTIBOOT_INFO_MEMORY)
    {
        mprintf("Low Memory: %uKb\n", mboot->mem_lower);
        mprintf("Upper Memory: %uKb\n", mboot->mem_upper);
    }

    if (mboot->flags & MULTIBOOT_INFO_MEM_MAP)
    {
        multiboot_memory_map_t *mmap = mboot->mmap_addr;
        mprintf("Memory Map: \n");
        while ((unsigned long) mmap < mboot->mmap_addr + mboot->mmap_length) {
            dump_mmap(mmap);
            mmap = (multiboot_memory_map_t *) ((unsigned long) mmap + mmap->size + sizeof (mmap->size));
        }
    }
}

int main(multiboot_info_t *mboot, int magic) // remember interrupt are disabled 
{
    monitor_clear();
    monitor_set_color(VGA_COLOR(COLOR_RED, COLOR_BLACK));
    monitor_put_string("PwniumOS\n");
    monitor_set_color(VGA_GREY_ON_BLACK);
    monitor_put_string("Booting...\n");
    dump_mboot(mboot);
    return 0;
}
