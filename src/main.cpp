#include "asm.h"

int main(int argc, char** argv)
{
    if (argc!=2)
    {
        cout<<"asm.exe asm_source_file\n";
        return 1;
    }
    Asm a;
    if (a.ReadSrc(argv[1]))
    {
       a.RunCode();
       cout << "\nprogram end normally.\n";
    }
    return 0;
}
