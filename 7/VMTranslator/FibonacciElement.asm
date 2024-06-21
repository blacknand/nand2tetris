@7777
M=0
M=1

 // ------------------------- writeFunction ---------------------
(Sys.Sys.init)
 // ------------------------- writeFunction ---------------------

@7777
M=0
M=1

// push -------------------------constant 4
@4
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 4
@7777
M=0
M=1

// -------------------- writeCall -------------------
@Sys.Main.fibonacci$ret.0
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@6
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.Main.fibonacci
// -------------------- writeCall -------------------
0;JMP
(Sys.Main.fibonacci$ret.0)

@7777
M=0
M=1

(Sys.Sys.init$END)

@7777
M=0
M=1

 // ------------------------- writeGoto ---------------------
@Sys.Sys.init$END
 // ------------------------- writeGoto ---------------------
0;JMP

@7777
M=0
M=1

 // ------------------------- writeFunction ---------------------
(Main.Main.fibonacci)
 // ------------------------- writeFunction ---------------------

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

// ------------------------- pop14 and popR13, lt --------------------------
@SP
M=M-1
A=M
D=M

@R14
M=D

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
@LT1
D;JLT
@NO.lt1
0;JMP
(LT1)
D=-1
@LT.skip1
0;JMP
(NO.lt1)
D=0
(LT.skip1)

// ------------------------- pop14 and popR13, lt --------------------------
// push
@SP
A=M
M=D
@SP
M=M+1

@7777
M=0
M=1

 // ------------------------- writeIf ---------------------
@SP
M=M-1
A=M
D=M
@Main.Main.fibonacci$N_LT_2
 // ------------------------- writeIf ---------------------
D;JNE

@7777
M=0
M=1

 // ------------------------- writeGoto ---------------------
@Main.Main.fibonacci$N_GE_2
 // ------------------------- writeGoto ---------------------
0;JMP

@7777
M=0
M=1

(Main.Main.fibonacci$N_LT_2)

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
@1
A=D-A
D=M
@THAT
M=D
@R15
D=M
@2
A=D-A
D=M
@THIS
M=D
@R15
D=M
@3
A=D-A
D=M
@ARG
M=D
@R15
D=M
@4
A=D-A
D=M
@LCL
M=D
@R14
A=M
0;JMP
// -------------------- writeReturn -------------------

@7777
M=0
M=1

(Main.Main.fibonacci$N_GE_2)

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

// -------------------- writeCall -------------------
@Main.Main.fibonacci$ret.1
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@6
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.Main.fibonacci
// -------------------- writeCall -------------------
0;JMP
(Main.Main.fibonacci$ret.1)

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

// -------------------- writeCall -------------------
@Main.Main.fibonacci$ret.2
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@6
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.Main.fibonacci
// -------------------- writeCall -------------------
0;JMP
(Main.Main.fibonacci$ret.2)

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
@1
A=D-A
D=M
@THAT
M=D
@R15
D=M
@2
A=D-A
D=M
@THIS
M=D
@R15
D=M
@3
A=D-A
D=M
@ARG
M=D
@R15
D=M
@4
A=D-A
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

