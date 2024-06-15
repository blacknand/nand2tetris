// push constant 3030
@3030
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop pointer 0
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

// push constant 3040
@3040
D=A
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

// push constant 32
@32
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop THIS 2
@THIS
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

// push constant 46
@46
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop THAT 6
@THAT
D=M
@6
D=D+A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

// push pointer 0
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1

// push pointer 1
@THAT
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

// push THIS 2
@THIS
D=M
@2
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

// push THAT 6
@THAT
D=M
@6
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

