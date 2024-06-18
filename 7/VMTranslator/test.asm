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

// pop pointer 1
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

// push constant 0
@0
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop THAT 0
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

// push constant 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop THAT 1
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

// push constant 2
@2
D=A
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

// pop ARG 0
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

(test.NULL$LOOP)

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

@SP
M=M-1
A=M
D=M
@test.NULL$COMPUTE_ELEMENT
D;JNE

@test.NULL$END
0;JMP

(test.NULL$COMPUTE_ELEMENT)

// push THAT 0
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

// push THAT 1
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

// pop THAT 2
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

// push pointer 1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1

// push constant 1
@1
D=A
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

// pop pointer 1
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

// push constant 1
@1
D=A
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

// pop ARG 0
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

@test.NULL$LOOP
0;JMP

(test.NULL$END)

@END
(END)
@END
0;JMP

