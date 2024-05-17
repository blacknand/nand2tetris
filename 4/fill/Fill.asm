// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

    @counter
    M=0

(LOOP)

    @KBD
    D=M
    // If key is pressed
    @FILL_SCREEN
    D;JGT
    // If no key is pressed
    @CLEAR_SCREEN
    D;JEQ

(FILL_SCREEN)

    // *(SCREEN + counter) = -1
    @SCREEN
    D=M
    @counter
    A=D+M
    @LOOP
    M=-1

(CLEAR_SCREEN)

    // *(SCREEN + counter) = 0
    @SCREEN
    A=M+1
    M=0

    // TODO: find some way to limit the accessible ram
    @LOOP
    0;JMP


