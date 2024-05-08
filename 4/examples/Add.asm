// Computes RAM[2] = RAM[0] + RAM[1] + 17
// Usage: put values in RAM[0] and in RAM[1]

    // D = RAM[0]
    @RO
    D=M

    // D = D + RAM[1]
    @R1
    D=D+M

    // D = D + 17
    @17
    D=D+A   // Reason for not using M is because M is for a selected data memory register,
            // while A is just a value that can be either a RAM or ROM

    // RAM[2] = D
    @R2
    M=D

(END)

    @END
    0;JMP