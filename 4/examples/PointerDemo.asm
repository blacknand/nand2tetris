// Starting at base address RO, sets the first
// R1 words to - 1

    // n = 0
    @n
    M=0

(LOOP)

    // if (n == R1) goto END
    @n
    D=M
    @R1
    D=D-M
    @END
    D;JEQ

    // *(R0 + n) = -1
    @RO
    D=M
    @n
    A=D+M
    M=-1

    // n = n + 1
    @n
    M=M+1

    // goto LOOP
    @LOOP
    0;JMP

(END)

    @END
    0;JMP