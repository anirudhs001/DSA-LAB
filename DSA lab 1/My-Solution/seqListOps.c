#include <stdio.h>
#include "compare.h"
//nextfreeloc: next free location in st. Can store new job here.
int nextfreeloc = 0;

seqlist insert (Job , seqlist);

seqlist createlist()
{
    seqlist sl;
    sl.head = nextfreeloc++;
    sl.size = 0;
    st[sl.head].next = -1;
    return (sl);
}


//insertelements: inserts all elements in joblist in corresponding seqarr, according to priority
// joblist: array of all jobs
// seqarr: array of seqlists
// returns: nothing
void insertelements (joblist ele ,seqarr s)
{
    // insert all jobs of same priority together
    for (int p=0;p<3;p++) {
        printf("\n pri=%d, head=%d\n", p, s[p].head);
        for (int j=0;j<MAX;j++) {
            if (ele[j].pri == p) {
                s[p] = insert(ele[j], s[p]);
                for (int k = 0; k < MAX; k++) {
                    printf("[id=%d, pri=%d, next=%d]", st[k].ele.id, st[k].ele.pri, st[k].next);
                }
                printf("\n");
            }
        }
        // move heads by size of current sl
        for (int k=p+1; k<3; k++) {
            s[k].head += s[p].size;
        }
    }
}

seqlist insert(Job j , seqlist sl)
{
    int i, temp;
    i = sl.head;

    // add the new job in list
    while (st[i].next != -1)
    {
        if (compare(st[st[i].next].ele , j) == GREATER) // i+1th job is greater than current job
            break;
        i=st[i].next;
    }
    // move all jobs after ith job one block right
    for (int k=MAX-1;k>i+1;k++) {
        st[k].ele = st[k-1].ele;
        if (st[k-1].next == -1) {
            st[k].next = -1;
        }
        else {
            st[k].next++;
        }
    }

    temp = nextfreeloc++;
    st[temp].next = st[i].next;
    st[temp].ele = j;
    st[i].next = temp;
    sl.size++;
    return sl;
}

void printjob (Job j)
{
    printf ("JOB ID = %d, Priority = %d, Execution time = %d, Arrival time = %d \n",j.id,j.pri,j.et,j.at);
}


void printseqlist(seqlist sl)
{
    int i;
    printf ("size of list = %d\n",sl.size);
    for (i=st[sl.head].next ; st[i].next != -1 ; i=st[i].next)
    {
        printjob (st[i].ele);
    }
}

void printjoblist (joblist j)
{
    int i;
    for (i=0;i<MAX;i++)
    {
        printjob (j[i]);
    }
}

// initialize_elements: initialises a list of Jobs(ele)
// returns: no. of elements added in ele
// ele is a joblist(defined in storage.h) which is an array of Jobs with size MAX.
int initialize_elements (joblist ele)
{
    int i,size;
    /*
    printf ("No of Jobs");
    scanf ("%d",&size);
    for (i=0;i<10;i++)
    {
        printf ("Enter job ID");
        scanf ("%d",ele[i].id);
        printf ("Enter Priority (from 0 - 2)");
        scanf ("%d",ele[i].pri);
        printf ("Execution Time");
        scanf ("%d",ele[i].et);
        printf ("Arrival Time");
        scanf ("%d",ele[i].at);
    }
    */
    i=0;
    size = 10;
    ele[0].id=1;
    ele[0].pri=0;
    ele[0].at=4;
    ele[0].et=5;
    ele[1].id=2;
    ele[1].pri=1;
    ele[1].at=9;
    ele[1].et=3;
    ele[2].id=3;
    ele[2].pri=2;
    ele[2].at=11;
    ele[2].et=12;
    ele[3].id=4;
    ele[3].pri=0;
    ele[3].at=1;
    ele[3].et=7;
    ele[4].id=5;
    ele[4].pri=1;
    ele[4].at=8;
    ele[4].et=2;
    ele[5].id=6;
    ele[5].pri=2;
    ele[5].at=12;
    ele[5].et=11;
    ele[6].id=7;
    ele[6].pri=0;
    ele[6].at=3;
    ele[6].et=9;
    ele[7].id=8;
    ele[7].pri=1;
    ele[7].at=7;
    ele[7].et=4;
    ele[8].id=9;
    ele[8].pri=2;
    ele[8].at=13;
    ele[8].et=10;
    ele[9].id=10;
    ele[9].pri=0;
    ele[9].at=2;
    ele[9].et=15;

    /* ele[0].pri = ele[3].pri = ele[6].pri = PRI_0;
       ele[1].pri = ele[4].pri = ele[7].pri = PRI_1;
       ele[2].pri = ele[5].pri = ele[8].pri = ele[9].pri = PRI_2;
       for (i=0;i<MAX;i++)
       {
       ele[i].id = i+1;
       ele[i].et = i+2;
       ele[i].at = i;
       }
       ele[2].at = 10;
       ele[5].at = 1;
       ele[6].at = 5;*/
    return size;
}

void copy_sorted_ele(seqarr s , joblist ele)
{
    int i,j;
    int index = 0;
    printf ("\n \n");
    for (i=2 ; i>=0 ; i--)
    {
        for (j=st[s[i].head].next ; st[j].next != -1; j = st[j].next)
        {
            ele[index] = st[j].ele;
            //printjob(ele[index]);
            index++;
        }  
        ele[index] = st[j].ele; 
        index++;
    }
}

