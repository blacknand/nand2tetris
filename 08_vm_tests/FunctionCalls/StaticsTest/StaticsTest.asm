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

// push -------------------------constant 6
@6
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 6
@7777
M=0
M=1

// push -------------------------constant 8
@8
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 8
@7777
M=0
M=1

// -------------------- writeCallClass1.set2 -------------------
@Class1.set$ret.0
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
@7
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Class1.set
// -------------------- writeCallClass1.set2 -------------------
0;JMP
(Class1.set$ret.0)

@7777
M=0
M=1

// pop -------------------------temp 0
@SP
M=M-1
A=M
D=M
@5
M=D

// pop -------------------------temp 0
@7777
M=0
M=1

// push -------------------------constant 23
@23
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 23
@7777
M=0
M=1

// push -------------------------constant 15
@15
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 15
@7777
M=0
M=1

// -------------------- writeCallClass2.set2 -------------------
@Class2.set$ret.1
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
@7
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Class2.set
// -------------------- writeCallClass2.set2 -------------------
0;JMP
(Class2.set$ret.1)

@7777
M=0
M=1

// pop -------------------------temp 0
@SP
M=M-1
A=M
D=M
@5
M=D

// pop -------------------------temp 0
@7777
M=0
M=1

// -------------------- writeCallClass1.get0 -------------------
@Class1.get$ret.2
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
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Class1.get
// -------------------- writeCallClass1.get0 -------------------
0;JMP
(Class1.get$ret.2)

@7777
M=0
M=1

// -------------------- writeCallClass2.get0 -------------------
@Class2.get$ret.3
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
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Class2.get
// -------------------- writeCallClass2.get0 -------------------
0;JMP
(Class2.get$ret.3)

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

 // ------------------------- writeFunctionClass1.set0 ---------------------
(Class1.set)
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

// pop -------------------------static 0
@SP
AM=M-1
D=M
@Class1.0
M=D

// pop -------------------------static 0
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

// pop -------------------------static 1
@SP
AM=M-1
D=M
@Class1.1
M=D

// pop -------------------------static 1
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

 // ------------------------- writeFunctionClass1.get0 ---------------------
(Class1.get)
 // ------------------------- writeFunction ---------------------

@7777
M=0
M=1

// push -------------------------static 0
@Class1.0
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------static 0
@7777
M=0
M=1

// push -------------------------static 1
@Class1.1
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------static 1
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

@7777
M=0
M=1

 // ------------------------- writeFunctionClass2.set0 ---------------------
(Class2.set)
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

// pop -------------------------static 0
@SP
AM=M-1
D=M
@Class2.0
M=D

// pop -------------------------static 0
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

// pop -------------------------static 1
@SP
AM=M-1
D=M
@Class2.1
M=D

// pop -------------------------static 1
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

 // ------------------------- writeFunctionClass2.get0 ---------------------
(Class2.get)
 // ------------------------- writeFunction ---------------------

@7777
M=0
M=1

// push -------------------------static 0
@Class2.0
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------static 0
@7777
M=0
M=1

// push -------------------------static 1
@Class2.1
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------static 1
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

