@7777
M=0
M=1

@7777
M=0
M=1

// push -------------------------ARG 1
@ARG
D=M
@1
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------ARG 1
@7777
M=0
M=1

// pop ------------------------- pointer 1
@THAT
D=A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

// pop ------------------------- pointer 1
@7777
M=0
M=1

// push -------------------------constant 0
@0
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 0
@7777
M=0
M=1

// pop -------------------------THAT 0
@THAT
D=M
@0
D=D+A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

// pop -------------------------THAT 0
@7777
M=0
M=1

// push -------------------------constant 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 1
@7777
M=0
M=1

// pop -------------------------THAT 1
@THAT
D=M
@1
D=D+A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

// pop -------------------------THAT 1
@7777
M=0
M=1

// push -------------------------ARG 0
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------ARG 0
@7777
M=0
M=1

// push -------------------------constant 2
@2
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 2
@7777
M=0
M=1

// ---------------- pop R14 and R13, sub -----------------
@SP
M=M-1
A=M
D=M
     // pop
@R14
M=D
      // save to R14
@SP
M=M-1
A=M
D=M
     // pop
@R13
M=D
      // save to R13
@R13
D=M
@R14
D=D-M
     // sub
// ---------------- pop R14 and R13, sub -----------------
// push
@SP
A=M
M=D
@SP
M=M+1

@7777
M=0
M=1

// pop -------------------------ARG 0
@ARG
D=M
@0
D=D+A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

// pop -------------------------ARG 0
@7777
M=0
M=1

(NULL$LOOP)

@7777
M=0
M=1

// push -------------------------ARG 0
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------ARG 0
@7777
M=0
M=1

 // ------------------------- writeIf ---------------------
@SP
M=M-1
A=M
D=M
@NULL$COMPUTE_ELEMENT
 // ------------------------- writeIf ---------------------
D;JNE

@7777
M=0
M=1

 // ------------------------- writeGoto ---------------------
@NULL$END
 // ------------------------- writeGoto ---------------------
0;JMP

@7777
M=0
M=1

(NULL$COMPUTE_ELEMENT)

@7777
M=0
M=1

// push -------------------------THAT 0
@THAT
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------THAT 0
@7777
M=0
M=1

// push -------------------------THAT 1
@THAT
D=M
@1
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------THAT 1
@7777
M=0
M=1

// -------------- pop R13 and R14, add ------------------
@SP
M=M-1
A=M
D=M
     // pop
@R13
M=D
      // save to R13
@SP
M=M-1
A=M
D=M
     // pop
@R14
M=D
      // save to R14
@R13
D=M
@R14
D=D+M
     // add
// -------------- pop R13 and R14, add ------------------
// push
@SP
A=M
M=D
@SP
M=M+1

@7777
M=0
M=1

// pop -------------------------THAT 2
@THAT
D=M
@2
D=D+A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

// pop -------------------------THAT 2
@7777
M=0
M=1

// push ------------------------- pointer 1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1

// push ------------------------- pointer 1
@7777
M=0
M=1

// push -------------------------constant 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 1
@7777
M=0
M=1

// -------------- pop R13 and R14, add ------------------
@SP
M=M-1
A=M
D=M
     // pop
@R13
M=D
      // save to R13
@SP
M=M-1
A=M
D=M
     // pop
@R14
M=D
      // save to R14
@R13
D=M
@R14
D=D+M
     // add
// -------------- pop R13 and R14, add ------------------
// push
@SP
A=M
M=D
@SP
M=M+1

@7777
M=0
M=1

// pop ------------------------- pointer 1
@THAT
D=A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

// pop ------------------------- pointer 1
@7777
M=0
M=1

// push -------------------------ARG 0
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------ARG 0
@7777
M=0
M=1

// push -------------------------constant 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 1
@7777
M=0
M=1

// ---------------- pop R14 and R13, sub -----------------
@SP
M=M-1
A=M
D=M
     // pop
@R14
M=D
      // save to R14
@SP
M=M-1
A=M
D=M
     // pop
@R13
M=D
      // save to R13
@R13
D=M
@R14
D=D-M
     // sub
// ---------------- pop R14 and R13, sub -----------------
// push
@SP
A=M
M=D
@SP
M=M+1

@7777
M=0
M=1

// pop -------------------------ARG 0
@ARG
D=M
@0
D=D+A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

// pop -------------------------ARG 0
@7777
M=0
M=1

 // ------------------------- writeGoto ---------------------
@NULL$LOOP
 // ------------------------- writeGoto ---------------------
0;JMP

@7777
M=0
M=1

(NULL$END)

@END
(END)
@END
0;JMP

