#include <linux/mm.h>       // 内核内存管理头文件
#include <linux/mm_types.h> // 内核内存类型头文件
#include <linux/init.h>     // 初始化头文件
#include <linux/module.h>   // 内核模块头文件
#include <linux/mmzone.h>
#include <linux/kernel.h>
#include <linux/slab.h>

static int my_paging_init(void) {
        struct mm_struct *mm = current->mm; // 当前进程的内存描述符
    struct vm_area_struct *vma = mm->mmap; // 虚拟内存区域描述符
    pgd_t *pgd;
    p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;
    unsigned long address;

    printk(KERN_INFO "Process ID: %d\n", current->pid);

    for (; vma; vma = vma->vm_next) {
        printk(KERN_INFO "VMA: start = 0x%lx, end = 0x%lx\n", vma->vm_start, vma->vm_end);

        for (address = vma->vm_start; address < vma->vm_end; address += PAGE_SIZE) {
            pgd = pgd_offset(mm, address);
            if (pgd_none(*pgd) || pgd_bad(*pgd)) {
                printk(KERN_INFO "  No PGD for address 0x%lx\n", address);
                continue;
            }

            p4d = p4d_offset(pgd, address);
            if (p4d_none(*p4d) || p4d_bad(*p4d)) {
                printk(KERN_INFO "  No P4D for address 0x%lx\n", address);
                continue;
            }

            pud = pud_offset(p4d, address);
            if (pud_none(*pud) || pud_bad(*pud)) {
                printk(KERN_INFO "  No PUD for address 0x%lx\n", address);
                continue;
            }

            pmd = pmd_offset(pud, address);
            if (pmd_none(*pmd) || pmd_bad(*pmd)) {
                printk(KERN_INFO "  No PMD for address 0x%lx\n", address);
                continue;
            }

            if (pmd_present(*pmd) && pmd_large(*pmd)) {
                printk(KERN_INFO "  PMD Large Page: address = 0x%lx\n", address);
                continue;
            }

            pte = pte_offset_map(pmd, address);
            if (!pte) {
                printk(KERN_INFO "  No PTE for address 0x%lx\n", address);
                continue;
            }

            if (!pte_present(*pte)) {
                printk(KERN_INFO "  Page not present for address 0x%lx\n", address);
            } else {
                unsigned long pfn = pte_pfn(*pte);
                unsigned long phys_addr = pfn << PAGE_SHIFT;
                printk(KERN_INFO "  Virtual Address: 0x%lx -> Physical Address: 0x%lx\n", address, phys_addr);
            }

            pte_unmap(pte);
        }
    }

    return 0;
}

static int buddy_system_init(void) {
    struct zone *zone;
    unsigned long free_pages;

    zone = &NODE_DATA(0)->node_zones[ZONE_NORMAL];
    free_pages = zone_page_state(zone, NR_FREE_PAGES);

    printk(KERN_INFO "Free pages in ZONE_NORMAL: %lu\n", free_pages);
    return 0;
}

static int kmalloc_example_init(void) {
    char *buffer;

    buffer = kmalloc(1024, GFP_KERNEL); // 分配1KB内存
    if (!buffer) {
        printk(KERN_ERR "kmalloc failed\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "kmalloc succeeded: buffer = %p\n", buffer);

    kfree(buffer); // 释放内存
    return 0;
}

static int __init demo_init(void) {
    my_paging_init();
    buddy_system_init();
    kmalloc_example_init();

    return 0;
}

static void __exit demo_exit(void) {
    printk(KERN_INFO "Module exit.\n");
}

module_init(demo_init);
module_exit(demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xiaowan-tiger");
MODULE_DESCRIPTION("A simple example of paging/phy-mem/kmalloc in Linux kernel.");



