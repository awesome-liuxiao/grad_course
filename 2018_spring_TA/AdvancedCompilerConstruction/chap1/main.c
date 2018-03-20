#include "prog1.h"
#include <stdio.h>
int main(){
        A_stm a = prog();

        int n = maxargs(a);
        interp(a);
        printf("\nmaxargs of print:%d\n",n);
        return 0;
        return 0;
}
