// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

// Pseudocode
// for i in R0 (sequence of 1s)
    // if (counter > R0)
        // Terminate program
    // R2 = R2 + R1
    // counter = counter + 1
    // goto beginning of for loop

    // Initalise counter and R2 to 0
    @counter
    M=0

    @R2
    M=0

(LOOP)

    // if (counter >= R0) goto TERMINATE
    @counter
    D=M
    @R0
    D=D-M                                   // Difference between counter and R0; counter - R0
    @TERMINATE
    D;JGE

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

    // if (R0 != 0) goto LOOP
    @LOOP
    0;JMP


(TERMINATE)

    // Terminate program by getting
    // intentionally stuck in an infinite loop
    // and letting the assembler deal with it
    @TERMINATE
    0;JMP
