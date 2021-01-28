#include "storage.h"

// compare according to execution time.
// returns: 0 == LESSER if j1 < j2
//          1 == GREATER if j1 > j2
//          2 == EQUAL if j1 == j2
ORDER compare (Job j1 , Job j2)
{
    if (j1.et < j2.et) return LESSER;
    else if (j1.et > j2.et) return GREATER;
    else if (j1.et == j2.et) return EQUAL;
}

