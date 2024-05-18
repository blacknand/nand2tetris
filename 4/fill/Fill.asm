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

    // Initalise counter to 0
    @counter
    M=0

    @var
    M=0
    D=M

    // var = 24576 - 16384 
    // if var == 0 then stop
    @KBD
    D=A
    @var
    D=D+M
    @SCREEN
    D=D-A
    @var
    M=D

    // if counter - var == -1
    // stop

    // or if counter - var == 0
    // stop

    // or if counter - var == 1
    // stop

(LOOP)

// (FILL_SCREEN)

    // if counter - var == 1 stop to prevent from touching illegal memory
    @counter
    D=M
    @var
    D=D-M
    @LOOP
    D;JGT

    @var
    D=M
    @END
    D;JEQ

    // *(SCREEN + counter) = -1
    @SCREEN
    D=A
    @counter
    A=D+M
    M=-1

// (CLEAR_SCREEN)

    // *(SCREEN + counter) = 0
    // @SCREEN
    // D=A
    // @counter
    // A=D+M
    // M=0

    @counter
    M=M+1

    @LOOP
    0;JMP

(END)

    @END
    0;JMP