@7777
M=0
M=1

// -------------------- bootstrapASM --------------------
@261
D=A
@SP
M=D
@Sys.init
// -------------------- bootstrapASM --------------------
0;JMP
(Sys.init$ret.0)

@7777
M=0
M=1

 // ------------------------- writeFunctionSys.init0 ---------------------
(Sys.init)
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

// -------------------- writeCallMain.fibonacci1 -------------------
@Main.fibonacci$ret.0
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
@Main.fibonacci
// -------------------- writeCallMain.fibonacci1 -------------------
0;JMP
(Main.fibonacci$ret.0)

@7777
M=0
M=1

(Sys.init$END)

@7777
M=0
M=1

 // ------------------------- writeGoto ---------------------
@Sys.init$END
 // ------------------------- writeGoto ---------------------
0;JMP

@7777
M=0
M=1

 // ------------------------- writeFunctionMain.fibonacci0 ---------------------
(Main.fibonacci)
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
@Main.fibonacci$N_LT_2
 // ------------------------- writeIf ---------------------
D;JNE

@7777
M=0
M=1

 // ------------------------- writeGoto ---------------------
@Main.fibonacci$N_GE_2
 // ------------------------- writeGoto ---------------------
0;JMP

@7777
M=0
M=1

(Main.fibonacci$N_LT_2)

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

@7777
M=0
M=1

(Main.fibonacci$N_GE_2)

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

// -------------------- writeCallMain.fibonacci1 -------------------
@Main.fibonacci$ret.1
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
@Main.fibonacci
// -------------------- writeCallMain.fibonacci1 -------------------
0;JMP
(Main.fibonacci$ret.1)

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

// -------------------- writeCallMain.fibonacci1 -------------------
@Main.fibonacci$ret.2
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
@Main.fibonacci
// -------------------- writeCallMain.fibonacci1 -------------------
0;JMP
(Main.fibonacci$ret.2)

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

