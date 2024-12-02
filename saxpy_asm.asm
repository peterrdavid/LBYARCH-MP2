section .text
bits 64
default rel
global saxpy_asm

saxpy_asm:
    XOR r10, r10
    MOVSS xmm6, xmm0
    
L1:
    CMP r10, r9
    JGE .end
    MOV rax, rcx
    MOVSS xmm4, [rax + r10*4]
    MOV rax, rdx 
    MOVSS xmm5, [rax + r10*4] ; xmm5 = Y[i]
    MULSS xmm4, xmm6
    ADDSS xmm4, xmm5
    MOV rax, r8
    MOVSS [rax + r10*4], xmm4
    INC r10
    JMP L1

.end:
    MOVSS xmm0, xmm6 
    RET