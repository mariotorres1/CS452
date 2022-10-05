#include <linux/slab.h>

#include "infiniti.h"
#include "fault.h"

/* segv signal error code, defined in /usr/include/asm-generic/siginfo.h */
#define SEGV_MAPERR 1 // segv signal, error code 1: address not mapped to object
#define SEGV_ACCERR 2 // segv signal, error code 2: invalid permissions for mapped object

int is_valid_address(struct infiniti_vm_area_struct *infiniti_vma, uintptr_t user_addr){
	struct list_head *pos, *next;
 	struct infiniti_vm_area_struct *node;
	/* traverse the list of nodes, and see if there is one which is reserved, and its range includes this address. */
	list_for_each_safe(pos, next, &(infiniti_vma->list)) {
		node = list_entry(pos, struct infiniti_vm_area_struct, list);
        if(node->status == RESERVED && user_addr >= node->start && user_addr < (node->start + 4096 * node->num_pages)){
            return 1;
        }
	}
    return 0;
}

int is_entire_table_free(unsigned long table){
	int i = 0;
	/* all four tables have 512 entries, each has 8 bytes, and thus 4KB per entry.. */
	for(i = 0; i < 512; i++){
		int offset = i * 8;
		unsigned long * entry = (unsigned long *)(table + offset);
		/* as long as one of them is one, then we can't free them or invalidate the tlb entries. */
		if(*entry & 0x1){
			/* not entirely free */
			return 0;
		}
	}
	/* table entirely free */
	return 1;
}

/*
 * error_code:
 * 1 == not present
 * 2 == permissions error
 * return 0 if handled successful; otherwise return -1.
 * */

int infiniti_do_page_fault(struct infiniti_vm_area_struct *infiniti_vma, uintptr_t fault_addr, u32 error_code) {
	// Variables 
	unsigned long pm14_table, pdp_table, pd_table, pt_table;
	unsigned long *pm14e, *pdpte, *pde, *pte;
	unsigned long cr3;

	// Verifying address is valid
	if (is_valid_address(infiniti_vma, fault_addr) == 0 ) {
		return -1;
	}

	// Verifying error code
	if (error_code == SEGV_ACCERR) {
		return -1;
	}

	// Updating cr3, pm14_table and pm143 variables
	cr3 = get_cr3();
	pm14_table = (unsigned long)__va(cr3 & 0x000FFFFFFFFFF000);
	pm14e = (unsigned long *)(pm14_table + (unsigned long)(((fault_addr >> 39) & 0x01ff) << 3));
}

/* this function takes a user VA and free its PA as well as its kernel va. */
void infiniti_free_pa(uintptr_t user_addr){
	return;
}

/* vim: set ts=4: */
