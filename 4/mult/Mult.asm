// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

// Pseudocode
// For i in R1
    // if (counter > R1)
        // goto STOP
    // R2 = R1 + R0
    // counter = counter + 1
    // if (counter < R1)
        // GOTO beginning of for loop

(LOOP)

    // TODO: if counter > R0 goto END

    // TODO: implement counter for each iteration in LOOP
    @counter
    M=M+1

    // TODO: assign R2 = R1 + R0
    @R1
    D=M
    @R0
    D=D+M
    @R2
    M=D

    // TODO: if counter < R0 goto LOOP

(END)

    // Terminate program
    // by intentionally getting stuck in infinite loop
    @END
    0;JMP
