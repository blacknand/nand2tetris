// File: Sum1ToN.asm
// Computes RAM[i] = 1 + 2 + 3 + ... + RAM[0]
// Usage: put a value >= 1 in RAM[0]

// Pseudocode for Sum1ToN
    // i = 1
    // sum = 0
// LOOP:
    // if (i > RO) goto STOP
    // sum = sum + i
    // i = i + 1
    // goto LOOP
// STOP:
    // R1 = SUM

// Notes
	// In Hack assembly, every operation involving a memory location entails two instructions
	// The first instruction @addr is used to select a target memory address;
	// the subsequent instruction specifies what to do with this address
	// The language features 2 generic instructions: an address instruction (@N)
	// and a compute instruction (C-instruction)
	// Each instruction has a symbolic representation, a binary representation and a effect on the computer

// Figure 4.4 in Machine Language chapter

    // i= 1
    @i
    M=1

    // sum = 0
    @sum
    M=0

(LOOP)

    // if (i > R0) goto STOP
    @i
    D=M
    @R0
    D=D-M
    @STOP
    D;JGT

    // sum = sum + i
    @sum
    D=M
    @i
    D=D+M
    @sum
    M=D

    // i = i + 1
    @i
    M=M+1

    // goto LOOP
    @LOOP
    0;JMP

(STOP)

    // R1 = sum
    @sum
    D=M
    @R1
    M=D

(END)

    @END
    0;JMP
