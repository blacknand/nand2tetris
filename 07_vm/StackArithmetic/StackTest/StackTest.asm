// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// popR14 and popR13, eq
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
@EQ1
D;JEQ
@NO.eq1
0;JMP
(EQ1)
D=-1
@EQ.skip1
0;JMP
(NO.eq1)
D=0
(EQ.skip1)

// push
@SP
A=M
M=D
@SP
M=M+1

// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 16
@16
D=A
@SP
A=M
M=D
@SP
M=M+1

// popR14 and popR13, eq
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
@EQ2
D;JEQ
@NO.eq2
0;JMP
(EQ2)
D=-1
@EQ.skip2
0;JMP
(NO.eq2)
D=0
(EQ.skip2)

// push
@SP
A=M
M=D
@SP
M=M+1

// push constant 16
@16
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// popR14 and popR13, eq
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
@EQ3
D;JEQ
@NO.eq3
0;JMP
(EQ3)
D=-1
@EQ.skip3
0;JMP
(NO.eq3)
D=0
(EQ.skip3)

// push
@SP
A=M
M=D
@SP
M=M+1

// push constant 892
@892
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop14 and popR13, lt
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
@LT4
D;JLT
@NO.lt4
0;JMP
(LT4)
D=-1
@LT.skip4
0;JMP
(NO.lt4)
D=0
(LT.skip4)

// push
@SP
A=M
M=D
@SP
M=M+1

// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 892
@892
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop14 and popR13, lt
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
@LT5
D;JLT
@NO.lt5
0;JMP
(LT5)
D=-1
@LT.skip5
0;JMP
(NO.lt5)
D=0
(LT.skip5)

// push
@SP
A=M
M=D
@SP
M=M+1

// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop14 and popR13, lt
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
@LT6
D;JLT
@NO.lt6
0;JMP
(LT6)
D=-1
@LT.skip6
0;JMP
(NO.lt6)
D=0
(LT.skip6)

// push
@SP
A=M
M=D
@SP
M=M+1

// push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

// popR14 and popR13, gt
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
@GT7
D;JGT
@NO.gt7
0;JMP
(GT7)
D=-1
@GT.skip7
0;JMP
(NO.gt7)
D=0
(GT.skip7)

// push
@SP
A=M
M=D
@SP
M=M+1

// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1

// popR14 and popR13, gt
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
@GT8
D;JGT
@NO.gt8
0;JMP
(GT8)
D=-1
@GT.skip8
0;JMP
(NO.gt8)
D=0
(GT.skip8)

// push
@SP
A=M
M=D
@SP
M=M+1

// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

// popR14 and popR13, gt
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
@GT9
D;JGT
@NO.gt9
0;JMP
(GT9)
D=-1
@GT.skip9
0;JMP
(NO.gt9)
D=0
(GT.skip9)

// push
@SP
A=M
M=D
@SP
M=M+1

// push constant 57
@57
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 31
@31
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 53
@53
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

// push constant 112
@112
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

// popR13, neg
@SP
M=M-1
A=M
D=M
     // pop
@R13
M=D
      // save to R13
@R13
D=-M

// push
@SP
A=M
M=D
@SP
M=M+1

// popR14 and popR13, bitAnd
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
D=D&M

// push
@SP
A=M
M=D
@SP
M=M+1

// push constant 82
@82
D=A
@SP
A=M
M=D
@SP
M=M+1

// popR14 and popR13, bitOr
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
D=D|M

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

@END
(END)
@END
0;JMP

