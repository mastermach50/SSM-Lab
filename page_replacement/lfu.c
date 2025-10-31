#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3

typedef struct
{
    int page;
    int frequency;

} Frame;

Frame frames[MAX_FRAMES];

// Initialize all frames as empty
void initialize()
{
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        frames[i].page = -1;
        frames[i].frequency = -1;
    }
}

void displayFrames()
{
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        printf("%d ", frames[i].page);
    }
    printf("\n");
}

int getExistingPage(int page)
{
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        if (frames[i].page == page)
        {
            return i;
        }
    }
    return -1;
}

int getReplacablePage()
{
    int least_frequent_page_idx = 0;
    int least_frequent_page_frequency = frames[0].frequency;
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        if (frames[i].page == -1)
        {
            return i;
        }

        if (frames[i].frequency < least_frequent_page_frequency)
        {
            least_frequent_page_idx = i;
            least_frequent_page_frequency = frames[i].frequency;
        }
    }

    return least_frequent_page_idx;
}

int LFU(int *pages, int pn)
{
    int page_faults = 0;

    for (int i = 0; i < pn; i++)
    {
        // incAllRecency();
        if (getExistingPage(pages[i]) > -1)
        {
            int idx = getExistingPage(pages[i]);
            frames[idx].frequency++;
            printf("page %d already exists\n", pages[i]);
        }
        else
        {
            int idx = getReplacablePage();
            frames[idx].page = pages[i];
            frames[idx].frequency = 1;
            page_faults++;
            printf("page fault due to %d\n", pages[i]);
        }

        displayFrames();
    }

    return page_faults;
}

void main()
{
    int pages[] = {1, 3, 0, 3, 5, 6, 3};
    int pn = sizeof(pages) / sizeof(pages[0]);

    initialize();
    int page_faults = LFU(pages, pn);
    printf("There were %d page faults", page_faults);
}