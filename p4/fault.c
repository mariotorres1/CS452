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
	unsigned long pml4_table, pdp_table, pd_table, pt_table;
	unsigned long *pml4e, *pdpte, *pde, *pte;
	unsigned long cr3;

	// Verifying address is valid
	if (is_valid_address(infiniti_vma, fault_addr) == 0 ) {
		return -1;
	}

	// Verifying error code
	if (error_code == SEGV_ACCERR) {
		return -1;
	}

	// Updating cr3, pml4_table and pml4e variables
	cr3 = get_cr3();
	pml4_table = (unsigned long)__va(cr3 & 0x000FFFFFFFFFF000);
	pml4e = (unsigned long *)(pml4_table + (unsigned long)(((fault_addr >> 39) & 0x01ff) << 3));

	// Checking the present bit of pml4e
	if (*pml4e & 0x1) {
		// If it's 1, do nothing
	} else {
		/* If not 1, allocate table and update pm14e to show that */
		uintptr_t kernel_addr = 0;
		kernel_addr = (uintptr_t)get_zeroed_page(GFP_KERNEL);
		
		if (!kernel_addr) {
			return -ENOMEM;
		}
		
		*pml4e = (unsigned long)((unsigned long)*pml4e | 0x7);
		*pml4e = (unsigned long)(*pml4e | ((unsigned long)__pa(kernel_addr) & (unsigned long)0xffffffffff000));
	}

	// Updating pdp_table pdpte variables
	pdp_table = (unsigned long)__va(*pml4e & 0x000FFFFFFFFFF000);
    	pdpte = (unsigned long *)(pdp_table + (unsigned long)(((fault_addr >> 30) & 0x01ff) << 3));

	// Checking the present bit of pdpte
	    if (*pdpte & 0x1) {
		    // If it's 1, do nothing
	    } else {
		    /* If not 1, allocate table and update pdpte to show that */
		uintptr_t kernel_addr = 0;
		kernel_addr = (uintptr_t)get_zeroed_page(GFP_KERNEL);

		if (!kernel_addr) {
		    return -ENOMEM;
		}

		*pdpte = (unsigned long)((unsigned long)*pdpte | 0x7);
		*pdpte = (unsigned long)(*pdpte | ((unsigned long)__pa(kernel_addr) & (unsigned long)0xffffffffff000));
	    }

	// Updating pd_table and pde variables
    pd_table = (unsigned long)__va(*pdpte & 0x000FFFFFFFFFF000);
    pde = (unsigned long *)(pd_table + (unsigned long)(((fault_addr >> 21) & 0x01ff) << 3));

	// Checking the present bit of pde
    if (*pde & 0x1) {
	    // If it's 1, do nothing
    } else {
	    /* If not 1, allocate table and update pde to show that */
        uintptr_t kernel_addr = 0;
        kernel_addr = (uintptr_t)get_zeroed_page(GFP_KERNEL);

        if (!kernel_addr) {
            return -ENOMEM;
        }

		*pde = (unsigned long)((unsigned long)*pde | 0x7);
		*pde = (unsigned long)(*pde | ((unsigned long)__pa(kernel_addr) & (unsigned long)0xffffffffff000));
	    }

	// Updating pt_table and pte variables
	    pt_table = (unsigned long)__va(*pde & 0x000FFFFFFFFFF000);
	    pte = (unsigned long *)(pt_table + (unsigned long)(((fault_addr >> 12) & 0x01ff) << 3));

	// Checking the present bit of pte
	    if (*pte & 0x1) 
		    // If it's 1, do nothing
	    } else {
		/* If not 1, allocate table and update pte to show that */
		uintptr_t kernel_addr = 0;
		kernel_addr = (uintptr_t)get_zeroed_page(GFP_KERNEL);

		if (!kernel_addr) {
		    return -ENOMEM;
		}

		*pte = (unsigned long)((unsigned long)*pte | 0x7);
		*pte = (unsigned long)(*pte | ((unsigned long)__pa(kernel_addr) & (unsigned long)0xffffffffff000));
	    }

		return 0;

	}

/* this function takes a user VA and free its PA as well as its kernel va. */
void infiniti_free_pa(uintptr_t user_addr){
	// Variables
	unsigned long pml4_table, pdp_table, pd_table, pt_table;
	unsigned long *pml4e, *pdpte, *pde, *pte;
	unsigned long cr3;
	unsigned long kernel_addr;

	// Updating cr3, pml4_table, and plm4e variables
	cr3 = get_cr3();
	pml4_table = (unsigned long)__va(cr3 & 0x000FFFFFFFFFF000);
	pml4e = (unsigned long *)(pml4_table + (unsigned long)(((user_addr >> 39) & 0x01ff) << 3));

	// Checking present bit of pml4e
	if (*pml4e & 0x1) {
		// If it's 1, do nothing
	} else {
		// Return if it's not 1
		return;
	}

	// Updating pdp_table and pdpte variables
	pdp_table = (unsigned long)__va(*pml4e & 0x000FFFFFFFFFF000);
	pdpte = (unsigned long *)(pdp_table + (unsigned long)(((user_addr >> 30)&0x01ff) << 3));

	// Checking present bit of pdpte
	if (*pdpte & 0x1) {
		// If it's 1, do nothing
	} else {
		// If it's not 1, return
		return;
	}

	// Updating pd_table and pde variables
	pd_table = (unsigned long)__va(*pdpte & 0x000FFFFFFFFFF000);
	pde = (unsigned long *)(pd_table + (unsigned long)(((user_addr >> 21)&0x01ff) << 3));

	// Checking present bit of pde
	if (*pde & 0x1) {
		// If it's 1, do nothing
	} else {
		// If it's not 1, return
		return;
	}

	// Updating pt_table and pte variables
	pt_table = (unsigned long)__va(*pde & 0x000FFFFFFFFFF000);
	pte = (unsigned long *)(pt_table + (unsigned long)(((user_addr >> 12)&0x01ff) << 3));

	// Checking present bit of pte
	if (*pte & 0x1) {
		// If it's 1, do nothing
	} else {
		// If it's not 1, return
		return;
	}

	// Update kernel_addr and free it's page
	kernel_addr = (unsigned long)__va(*pte & 0x000ffffffffff000) + (user_addr & 0xfff);
	free_page(kernel_addr);

	// Setting pte to 0
	*pte = 0;
	// Checking if the pt_table is free
	if (is_entire_table_free(pt_table)) {
		// If it is, free the page
		free_page(pt_table);
	} else {
		// If it's not free, return
		return;
	}

	// Setting pde to 0
	*pde = 0;
	// Checking if the pd_table is free
	if (is_entire_table_free(pd_table)) {
		// If it is, free the page
		free_page(pd_table);
	} else {
		// If it's not free, return
		return;
	}

	// Setting pdpte to 0
	*pdpte = 0;
	// Checking if the pdp_table is free
	if (is_entire_table_free(pdp_table)) {
		// If it is, free the page
		free_page(pdp_table);
	} else {
		// If it's not free, return
		return;
	}

	// Settting pml4e to 0
	*pml4e = 0;
	// Checking if the pml4_table is free
	if (is_entire_table_free(pml4_table)) {
		// If it is, free the page
		free_page(pml4_table);
	} else {
		// If it's not free, return
		return;
	}
}

/* vim: set ts=4: */
