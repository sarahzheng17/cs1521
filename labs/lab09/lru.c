// Simulate LRU replacement of page frames

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

// represent an entry in a simple inverted page table

typedef struct ipt_entry {
    int virtual_page;        // == -1 if physical page free
    int last_access_time;
} ipt_entry_t;


void lru(int n_physical_pages, int n_virtual_pages);
void access_page(int virtual_page, int access_time, int n_physical_pages, struct ipt_entry *ipt);

int least_recently_used(int n_physical_pages, struct ipt_entry *ipt);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n-physical-pages> <n-virtual-pages>\n", argv[0]);
        return 1;
    }
    lru(atoi(argv[1]), atoi(argv[2]));
    return 0;
}


void lru(int n_physical_pages, int n_virtual_pages) {
    printf("Simulating %d pages of physical memory, %d pages of virtual memory\n",
          n_physical_pages, n_virtual_pages);
    struct ipt_entry *ipt = malloc(n_physical_pages * sizeof *ipt);
    assert(ipt);

    for (int i = 0; i < n_physical_pages; i++) {
        ipt[i].virtual_page = -1;
        ipt[i].last_access_time = -1;
    }

    int virtual_page;
    for (int access_time = 0; scanf("%d", &virtual_page) == 1; access_time++) {
        assert(virtual_page >= 0 && virtual_page < n_virtual_pages);
        access_page(virtual_page, access_time, n_physical_pages, ipt);
    }
}


// if virtual_page is not in ipt, the first free page is used
// if there is no free page, the least-recently-used page is evicted
//
// a single line of output describing the page access is always printed
// the last_access_time in ipt is always updated

void access_page(int virtual_page, int access_time, int n_physical_pages, struct ipt_entry *ipt) {
    // Note: ipt are structs representing physical pages i.e. frames
    // ipt[i].virtual_page is the virtual page that "physical page i" is holding

    // PUT YOUR CODE HERE TO HANDLE THE 3 cases
    //
    int page_accessed = FALSE;
    for (int i = 0; i < n_physical_pages; i++) {
    // 1) The virtual page is already in a physical page
        if (ipt[i].virtual_page == virtual_page) {  // There is a physical page that holds the virtual page
            ipt[i].last_access_time = access_time;
            printf("Time %d: virtual page %d -> physical page %d\n", access_time, virtual_page, i);
            page_accessed = TRUE;
            break;
        } else if (ipt[i].virtual_page == -1) {     // There is free space
    // 2) The virtual page is not in a physical page,
    //    and there is free physical page
            ipt[i].virtual_page = virtual_page;
            ipt[i].last_access_time = access_time;
            printf("Time %d: virtual page %d loaded to physical page %d\n", access_time, virtual_page, i);
            page_accessed = TRUE;
            break;
        }
    }
    // 3) The virtual page is not in a physical page,
    //    and there is no free physical page
    if (page_accessed == FALSE) {
        int evicted_physical_page = least_recently_used(n_physical_pages, ipt);
        int old_virtual_page = ipt[evicted_physical_page].virtual_page;

        ipt[evicted_physical_page].virtual_page = virtual_page;
        ipt[evicted_physical_page].last_access_time = access_time;

        printf("Time %d: virtual page %d  - virtual page %d evicted - loaded to physical page %d\n", access_time, virtual_page, old_virtual_page, evicted_physical_page);

        page_accessed = TRUE;
    }

    // don't forgot to update the last_access_time of the virtual_page

   // printf("Time %d: virtual page %d accessed\n", access_time, virtual_page);
}

// Function returns the physical page that holds the least-recently-used virtual page
int least_recently_used(int n_physical_pages, struct ipt_entry *ipt) {
    int time = ipt[0].last_access_time;
    int physical_page = 0;
    for (int i = 1; i < n_physical_pages; i++) {    // i = 1 since ipt[0] is already loaded
        if (ipt[i].last_access_time < time) {       // Least-recently-used means smaller last_access_time
            time = ipt[i].last_access_time;
            physical_page = i;
        }
    }

    return physical_page;
}

