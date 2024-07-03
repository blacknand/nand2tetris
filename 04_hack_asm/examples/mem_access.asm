// Figure 4.3 in Machine Language chapter


// D = 17
@17
D=A

// RAM[100] = 17
@17     // A <- 17
D=A     // D <- A
@100    // A <- 100
M=D     // M <- D

// RAM[100] = RAM[200]
@200
D=M
@100
M=D
