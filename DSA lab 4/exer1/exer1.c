#include<stdio.h>

int glob;
void p();
void g();
void h();
void d();

int main(int argc, char *argv[])
{
    p();
    return 0;
}

void p() {
    int pilani;
    // printf("inside p. pilani is at: %p\n", &pilani);
    g();
    h();
    d();
}
void g() {
    int goa;
    // printf("inside g. goa is at: %p\n", &goa);
    p();
    h();
    d();
}
void h() {
    int hyd;
    printf("inside h. hyd is at: %p\n", &hyd);
    p();
    g();
    d();
}
void d() {
    int dub;
    printf("inside d. dub is at: %p\n", &dub);
    p();
    g();
    h();
}