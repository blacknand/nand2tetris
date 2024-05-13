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

    // If (count > R1)
    @END
    R1;JGT

    // Counter for i in R1
    @count
    M=M+1

    // R2 = R1 + R2
    @R2
    M=R1+R2

    // If (count < R1)
    @LOOP
    R1;JLT

(END)

    // Terminate program
    // by intentionally getting stuck in infinite loop
    @END
    0;JMP
