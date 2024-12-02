nasm -f win64 saxpy_asm.asm
gcc -c saxpy_c.c -o saxpy_c.obj -m64
gcc saxpy_c.obj saxpy_asm.obj -o saxpy.exe -m64
"./saxpy.exe"