//writeFuncASM
(SimpleFunction.test)
   @2
   D=A
   @SimpleFunction.test$end_func
   D;JEQ
(SimpleFunction.test$main_loop)
   @SP
   A=M
   M=0
   @SP
   M=M+1
   D=D-1
   @SimpleFunction.test$main_loop
   D;JGT
(SimpleFunction.test$end_func)

// push LCL 0
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

// push LCL 1
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

// pop R13 and R14, add
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
// push
@SP
A=M
M=D
@SP
M=M+1

// pop R13, bitNot
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

// push
@SP
A=M
M=D
@SP
M=M+1

// push ARG 0
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

// pop R13 and R14, add
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
// push
@SP
A=M
M=D
@SP
M=M+1

// push ARG 1
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

// pop R14 and R13, sub
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
// push
@SP
A=M
M=D
@SP
M=M+1

// frame = LCL
   @LCL
   D=M
   @SimpleFunction.test$frame
   M=D
// retAddr(R15) = *(LCL - 5)
   @LCL
   D=M
   A=D
   D=M
   @5
   D=D-A
   M=D
   @R15
   M=D
// *ARG = pop()
   @SP
   AM=M-1
   D=M
   @ARG
   A=M
   M=D
// SP = ARG++
   @ARG
   D=M
   D=D+1
   @SP
   M=D
// THAT = *(frame--)
   @SimpleFunction.test$frame
   M=M-1
   D=M
   A=D
   D=M
   @THAT
   M=D
// THIS = *(frame - 2)
   @SimpleFunction.test$frame
   M=M-1
   D=M
   A=D
   D=M
   @THIS
   M=D
 // ARG = *(frame - 3)
   @SimpleFunction.test$frame
   M=M-1
   D=M
   A=D
   D=M
   @ARG
   M=D
// LCL = *(frame - 4)
   @SimpleFunction.test$frame
   M=M-1
   D=M
   A=D
   D=M
   @LCL
   M=D
// goto retAddr
   @R15
   0;JMP

@END
(END)
@END
0;JMP

