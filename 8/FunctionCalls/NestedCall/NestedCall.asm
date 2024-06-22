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

// push -------------------------constant 4000
@4000
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 4000
@7777
M=0
M=1

// pop ------------------------- pointer 0
@THIS
D=A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

// pop ------------------------- pointer 0
@7777
M=0
M=1

// push -------------------------constant 5000
@5000
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 5000
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

// -------------------- writeCallSys.main0 -------------------
@Sys.main$ret.0
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
@Sys.main
// -------------------- writeCallSys.main0 -------------------
0;JMP
(Sys.main$ret.0)

@7777
M=0
M=1

// pop -------------------------temp 1
@SP
M=M-1
A=M
D=M
@6
M=D

// pop -------------------------temp 1
@7777
M=0
M=1

(Sys.init$LOOP)

@7777
M=0
M=1

 // ------------------------- writeGoto ---------------------
@Sys.init$LOOP
 // ------------------------- writeGoto ---------------------
0;JMP

@7777
M=0
M=1

 // ------------------------- writeFunctionSys.main5 ---------------------
(Sys.main)
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
@SP
A=M
M=0
@SP
M=M+1
 // ------------------------- writeFunction ---------------------

@7777
M=0
M=1

// push -------------------------constant 4001
@4001
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 4001
@7777
M=0
M=1

// pop ------------------------- pointer 0
@THIS
D=A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

// pop ------------------------- pointer 0
@7777
M=0
M=1

// push -------------------------constant 5001
@5001
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 5001
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

// push -------------------------constant 200
@200
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 200
@7777
M=0
M=1

// pop -------------------------LCL 1
@LCL
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

// pop -------------------------LCL 1
@7777
M=0
M=1

// push -------------------------constant 40
@40
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 40
@7777
M=0
M=1

// pop -------------------------LCL 2
@LCL
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

// pop -------------------------LCL 2
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

// pop -------------------------LCL 3
@LCL
D=M
@3
D=D+A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

// pop -------------------------LCL 3
@7777
M=0
M=1

// push -------------------------constant 123
@123
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 123
@7777
M=0
M=1

// -------------------- writeCallSys.add121 -------------------
@Sys.add12$ret.1
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
@Sys.add12
// -------------------- writeCallSys.add121 -------------------
0;JMP
(Sys.add12$ret.1)

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

// push -------------------------LCL 2
@LCL
D=M
@2
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------LCL 2
@7777
M=0
M=1

// push -------------------------LCL 3
@LCL
D=M
@3
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------LCL 3
@7777
M=0
M=1

// push -------------------------LCL 4
@LCL
D=M
@4
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------LCL 4
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

@7777
M=0
M=1

 // ------------------------- writeFunctionSys.add120 ---------------------
(Sys.add12)
 // ------------------------- writeFunction ---------------------

@7777
M=0
M=1

// push -------------------------constant 4002
@4002
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 4002
@7777
M=0
M=1

// pop ------------------------- pointer 0
@THIS
D=A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

// pop ------------------------- pointer 0
@7777
M=0
M=1

// push -------------------------constant 5002
@5002
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 5002
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

// push -------------------------constant 12
@12
D=A
@SP
A=M
M=D
@SP
M=M+1

// push -------------------------constant 12
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

