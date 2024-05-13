// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

// Pseudocode
// For i in R0
    // if (counter > R0)
        // goto STOP
    // R2 = R1 + R0
    // counter = counter + 1
    // if (counter < R0)
        // GOTO beginning of for loop

(LOOP)

    // If (counter > R0) goto END
    @counter
    D=M
    @R0
    D=D-M           // R0 = counter - R0
    @END
    D;JGT

    // counter++ for i in R0
    @counter
    M=M+1

    // R2 = R1 + R0
    @R1
    D=M
    @R0
    D=D+M
    @R2
    M=D
 
    // if (counter < R0) goto LOOP
    @R0
    D=M
    @counter
    D=D+M
    @LOOP
    D;JLT

(END)

    // Terminate program
    // by intentionally getting stuck in infinite loop
    @END
    0;JMP
