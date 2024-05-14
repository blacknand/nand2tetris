// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

// Pseudocode
// for i in R0
    // if (counter > R0)
        // Terminate program
    // R2 = R2 + R1
    // counter = counter + 1
    // if (counter < R0)
        // Go back to beginning of for loop

    // Initalise counter, R0, R1, R2 to 0
    @counter
    M=0

    @R0
    M=0

    @R1
    M=0

    @R2
    M=0

(LOOP)

    // if (counter > R0)
    @counter
    D=M
    @R0
    D=D-M                                   // Difference between counter and R0; counter - R0
    @TERMINATE
    D;JGT

    // R2 = R2 + R1
    @R2
    D=M
    @R1
    D=D+M
    @R2
    M=D

    // counter++
    @counter
    M=M+1

    // if (counter < R0)
    @R0
    D=M
    @counter
    D=D-M                                   // Difference between R0 and counter; R0 - counter
    @LOOP
    D;JGT


(TERMINATE)

    @TERMINATE
    0;JMP