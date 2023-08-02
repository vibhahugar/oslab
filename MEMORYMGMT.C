#include <stdio.h>
#include <conio.h>

#define max 25

void readInput(int *nb, int *nf, int b[], int f[]);
void bestFit(int nb, int nf, int b[], int f[], int bf[], int ff[], int frag[]);
void worstFit(int nb, int nf, int b[], int f[], int bf[], int ff[], int frag[]);
void firstFit(int nb, int nf, int b[], int f[], int bf[], int ff[], int frag[]);
void displayResults(int nf, int f[], int ff[], int b[], int frag[]);

int main()
{
    int nb, nf;
    int b[max], f[max], bf[max] = {0}, ff[max] = {0}, frag[max] = {0};

    clrscr();

    readInput(&nb, &nf, b, f);
    bestFit(nb, nf, b, f, bf, ff, frag);
    displayResults(nf, f, ff, b, frag);

    // You can uncomment and use the other fit functions as well.
    // worstFit(nb, nf, b, f, bf, ff, frag);
    // firstFit(nb, nf, b, f, bf, ff, frag);

    getch();
    return 0;
}

void readInput(int *nb, int *nf, int b[], int f[])
{
    int i;
    printf("Enter the number of blocks:");
    scanf("%d", nb);

    printf("Enter the number of files:");
    scanf("%d", nf);

    printf("\nEnter the size of the blocks:\n");
    for (i = 1; i <= *nb; i++)
    {
        printf("Block %d:", i);
        scanf("%d", &b[i]);
    }

    printf("Enter the size of the files:\n");
    for (i = 1; i <= *nf; i++)
    {
        printf("File %d:", i);
        scanf("%d", &f[i]);
    }
}

void bestFit(int nb, int nf, int b[], int f[], int bf[], int ff[], int frag[])
{
    int i, j, temp, highest = 0;

    for (i = 1; i <= nf; i++)
    {
        for (j = 1; j <= nb; j++)
        {
            if (bf[j] != 1) //if bf[j] is not allocated
            {
                temp = b[j] - f[i];
                if (temp >= 0)
                {
                    if (highest == 0 || temp < highest)
                    {
                        ff[i] = j;
                        highest = temp;
                    }
                }
            }
        }
        frag[i] = highest;
        bf[ff[i]] = 1;
        highest = 0;
    }
}

void worstFit(int nb, int nf, int b[], int f[], int bf[], int ff[], int frag[])
{
    int i, j, temp, lowest = 10000;

    for (i = 1; i <= nf; i++)
    {
        for (j = 1; j <= nb; j++)
        {
            if (bf[j] != 1)
            {
                temp = b[j] - f[i];
                if (temp >= 0)
                {
                    if (lowest == 10000 || temp > lowest)
                    {
                        ff[i] = j;
                        lowest = temp;
                    }
                }
            }
        }
        frag[i] = lowest;
        bf[ff[i]] = 1;
        lowest = 10000;
    }
}

void firstFit(int nb, int nf, int b[], int f[], int bf[], int ff[], int frag[])
{
    int i, j, temp;

    for (i = 1; i <= nf; i++)
    {
        for (j = 1; j <= nb; j++)
        {
            if (bf[j] != 1)
            {
                temp = b[j] - f[i];
                if (temp >= 0)
                {
                    ff[i] = j;
                    break;
                }
            }
        }
        frag[i] = temp;
        bf[ff[i]] = 1;
    }
}

void displayResults(int nf, int f[], int ff[], int b[], int frag[])
{
    int i;

    printf("\nFile_no\t\tFile_size\tBlock_no\tBlock_size\tFragment");
    for (i = 1; i <= nf; i++)
    {
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
    }
}
