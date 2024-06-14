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
