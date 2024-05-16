// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

(LOOP)

    @KBD
    D=M
    @BLACK
    D;JGT
  
(BLACK)

    @SCREEN
    M=-1

(WHITE)

    @SCREEN
    M=0

    @LOOP
    0;JMP