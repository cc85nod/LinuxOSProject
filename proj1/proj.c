#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/string.h>
#include <linux/mm_types.h>
#include <asm/pgtable.h>
#include <asm/io.h>
#include <asm/pgtable_64.h>

unsigned long virToPhy(struct mm_struct *mm, unsigned long addr)
{
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	struct page *page;
	unsigned long phys;

	pgd = pgd_offset(mm, addr);
	if(pgd_none(*pgd) || pgd_bad(*pgd)) return 0;
	pud = pud_offset(p4d, addr);
	if(pud_none(*pud) || pud_bad(*pud)) return 0;
	pmd = pmd_offset(pud, addr);
	if(pmd_none(*pmd) || pmd_bad(*pmd)) return 0;
	pte = pte_offset_map(pmd, addr);
	if(!pte) return 0;
	page = pte_page(*pte);
	if(!page) return 0;
	phys = page_to_phys(page);
	pte_unmap(pte);

	return phys;
}									

SYSCALL_DEFINE1(linux_survey_TT, char *, rr)
{
	// get current process's task_struct
	struct task_struct *p = current;
	// get memory management
	struct mm_struct *mm = p->mm;
	// get virtual memory area
	struct vm_area_struct *vma = mm->mmap;
	
	char buffer[300];
	char *process_name = p->comm;
	char *path_name;
	int pid = p->pid;
	unsigned long inode;
	unsigned long start_addr;
	unsigned long end_addr;
	unsigned long offset;
	unsigned long phy;
	unsigned long vpage;
	unsigned long total_page = 0;
	unsigned long used_page = 0;

	sprintf(buffer, "@@@@@@@@@@@@@@@\n\nProcess name: %s, PID: %d\n\n@@@@@@@@@@@@@@@\n", process_name, pid);
	strcpy(rr, buffer);

	while(vma) {
		start_addr = vma->vm_start;
		end_addr = vma->vm_end;
		offset = end_addr - start_addr;

		if(start_addr <= vma->vm_mm->start_stack && end_addr >= vma->vm_mm->start_stack) {
			path_name = "[ stack ]";
		} else if(start_addr <= mm->brk && end_addr >= mm->start_brk) {
			path_name = "[ heap ]";
		} else if(vma->vm_file != NULL && vma->vm_file->f_path.dentry != NULL) {
			path_name = vma->vm_file->f_path.dentry->d_iname;
		} else {
			path_name = "unknown";
		}

		if(vma->vm_file != NULL && vma->vm_file->f_inode != NULL) {
			inode = vma->vm_file->f_inode->i_ino;
		} else {
			inode = 0;
		}

		sprintf(buffer, "---------------\n\npath_name: %s, inode: %lu\nvirtual_area: 0x%012lx-0x%012lx, offset: 0x%012lx\n\n", path_name, inode, start_addr, end_addr, offset);
		strcat(rr, buffer);
		for(vpage = start_addr; vpage < end_addr; vpage += PAGE_SIZE) {
			total_page++;
			phy = virToPhy(mm, vpage);
			if(phy) {
				used_page++;
			}
			sprintf(buffer, "0x%012lx ==> 0x%012lx\n", vpage, phy);
			strcat(rr, buffer);
		}
		sprintf(buffer, "\n---------------\n");
		strcat(rr, buffer);
		vma = vma->vm_next;
	}
	used_page = used_page*100;
	sprintf(buffer, "used page percentage: %lu%%\n", used_page/total_page);
	strcat(rr, buffer);

	return 0;
}

























