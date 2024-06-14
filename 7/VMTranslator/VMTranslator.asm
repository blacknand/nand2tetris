// push constant 10
@10
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop LCL 0
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

// push constant 21
@21
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 22
@22
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop ARG 2
@ARG
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

// pop ARG 1
@ARG
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

// push constant 36
@36
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop THIS 6
@THIS
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

// push constant 42
@42
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 45
@45
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop THAT 5
@THAT
D=M
@5
D=D+A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

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

// push constant 510
@510
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop temp 11
@R5
D=M
@11
D=D+A
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

// push LCL 0
@LCL
D=M
@0
A=D+M
D+M
@SP
A=M
M=D
@SP
M=M+1

// push THAT 5
@THAT
D=M
@5
A=D+M
D+M
@SP
A=M
M=D
@SP
M=M+1

// pop, popR13
@SP
M=M-1
A=M
D=M
@R13
M=D
// pop, popR14, add
@SP
M=M-1
A=M
D=M
@R14
M=D
@R13
D=M
@R14
M=D+M
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
A=D+M
D+M
@SP
A=M
M=D
@SP
M=M+1

// pop, popR13
@SP
M=M-1
A=M
D=M
@R13
M=D
// pop, popR14, sub
@SP
M=M-1
A=M
D=M
@R14
M=D
@R13
D=M
@R14
D=D-M
// push
@SP
A=M
M=D
@SP
M=M+1
// push THIS 6
@THIS
D=M
@6
A=D+M
D+M
@SP
A=M
M=D
@SP
M=M+1

// push THIS 6
@THIS
D=M
@6
A=D+M
D+M
@SP
A=M
M=D
@SP
M=M+1

// pop, popR13
@SP
M=M-1
A=M
D=M
@R13
M=D
// pop, popR14, add
@SP
M=M-1
A=M
D=M
@R14
M=D
@R13
D=M
@R14
M=D+M
// push
@SP
A=M
M=D
@SP
M=M+1
// pop, popR13
@SP
M=M-1
A=M
D=M
@R13
M=D
// pop, popR14, sub
@SP
M=M-1
A=M
D=M
@R14
M=D
@R13
D=M
@R14
D=D-M
// push
@SP
A=M
M=D
@SP
M=M+1
// push temp 11
@R5
D=M
@11
A=D+M
D+M
@SP
A=M
M=D
@SP
M=M+1

// pop, popR13
@SP
M=M-1
A=M
D=M
@R13
M=D
// pop, popR14, add
@SP
M=M-1
A=M
D=M
@R14
M=D
@R13
D=M
@R14
M=D+M
// push
@SP
A=M
M=D
@SP
M=M+1
