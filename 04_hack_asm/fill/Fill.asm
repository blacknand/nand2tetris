// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

// evaluate if KBD is > 0 then a key has been pressed, 
// then loop to FILL_SCREEN and increment a pointer to the adresses starting from SCREEN 
// else if KBD == 0 then loop to CLEAR_SCREEN
// and increment a pointer to the adresses starting from SCREEN. 

    // Initialise
    @counter
    M=0
    @limit
    M=0

    // limit = 24576 - 16384 
    // 24576 == address of KBD
    // 16384 == address of SCREEN
    @limit
    D=M
    @KBD
    D=A
    @limit
    D=D+M
    @SCREEN
    D=D-A
    @limit
    M=D

(LOOP)

    // if (counter > limit) goto RESET 
    @counter
    D=M
    @limit
    D=D-M
    @RESET
    D;JGT

    @KBD
    D=M
    // If any key is being pressed
    @FILL_SCREEN
    D;JGT
    // If no key is being pressed
    @CLEAR_SCREEN
    D;JEQ

// Make every pixel 1 (black)
(FILL_SCREEN)
    // *(SCREEN + counter) = -1
    @SCREEN
    D=A
    @counter
    A=D+M
    M=-1
    // counter++
    @counter
    M=M+1
    // goto LOOP
    @LOOP
    0;JMP

// Make every pixel 0 (white)
(CLEAR_SCREEN)
    // *(SCREEN + counter) = 0
    @SCREEN
    D=A
    @counter
    A=D+M
    M=0
    // counter++
    @counter
    M=M+1
    // goto LOOP 
    @LOOP
    0;JMP

// Reset so every pixel is white
(RESET)
    @counter
    M=0
    // goto LOOP
    @LOOP
    0;JMP