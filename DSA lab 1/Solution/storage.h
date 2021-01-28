#define MAX 10
#define MAX_SEQ_LIST 3

typedef enum {PRI_0, PRI_1, PRI_2} PRIORITY;
typedef enum {LESSER , GREATER , EQUAL} ORDER;
typedef int JOB_ID;
typedef int EXECUTION_TIME;
typedef int ARRIVAL_TIME;

typedef struct
{
    JOB_ID id;
    PRIORITY pri;
    EXECUTION_TIME et;
    ARRIVAL_TIME at;
} Job;

//joblist: array of Jobs. size = MAX
typedef Job joblist[MAX];

typedef struct
{
    // ele: a Job
    Job ele;
    // next: index of next Job in SeqList
    int next;
} LOCATION;

typedef LOCATION STORE[MAX];

// structure to hold different buckets of jobs acc to priority.
typedef struct
{
    // total size of this seqlist
    int size;
    // = index of first element of this seqlist in st IF present.
    // = -1 otherwise.
    int head;
} seqlist;

// seqarr: array of seqlists
typedef seqlist seqarr[MAX_SEQ_LIST];

// STORE = array of LOCATIONS
// st contains all the jobs
STORE st;
