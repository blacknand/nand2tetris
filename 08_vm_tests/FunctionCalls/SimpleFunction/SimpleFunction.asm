@7777
M=0
M=1

@7777
M=0
M=1

 // ------------------------- writeFunctionSimpleFunction.test2 ---------------------
(SimpleFunction.test)
@SP
A=M
M=0
@SP
M=M+1
@SP
A=M
M=0
@SP
M=M+1
 // ------------------------- writeFunction ---------------------

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

// push -------------------------LCL 1
@LCL
D=M
@1
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------LCL 1
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

// ------------------------------- pop R13, bitNot -------------------------------
@SP
M=M-1
A=M
D=M
     // pop
@R13
M=D
      // save to R13
@R13
D=!M

// ------------------------------- pop R13, bitNot -------------------------------
// push
@SP
A=M
M=D
@SP
M=M+1

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

// -------------------- writeReturn -------------------
@LCL
D=M
@R15
M=D
@5
A=D-A
D=M
@R14
M=D
@SP
AM=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@R15
D=M
A=D-1
D=M
@THAT
M=D
@2
D=A
@R15
A=M-D
D=M
@THIS
M=D
@3
D=A
@R15
A=M-D
D=M
@ARG
M=D
@4
D=A
@R15
A=M-D
D=M
@LCL
M=D
@R14
A=M
0;JMP
// -------------------- writeReturn -------------------

@END
(END)
@END
0;JMP

