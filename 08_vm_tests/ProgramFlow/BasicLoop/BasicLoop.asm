@7777
M=0
M=1

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

// pop -------------------------LCL 0
@LCL
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

// pop -------------------------LCL 0
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

// push -------------------------LCL 0
@LCL
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------LCL 0
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

// pop -------------------------LCL 0
@LCL
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

// pop -------------------------LCL 0
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
@NULL$LOOP
 // ------------------------- writeIf ---------------------
D;JNE

@7777
M=0
M=1

// push -------------------------LCL 0
@LCL
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------LCL 0
@END
(END)
@END
0;JMP

