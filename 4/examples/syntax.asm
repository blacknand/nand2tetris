// Data registers are designed to hold data values
// Address registers can hold either data values or addresses

// Address register: A, the address register
// Memory register: M, the selected register
load A,17                       // A <- 17 (memory address A is set 17)
load M,1                        // The memory register whose address is selected by A (17 <- 1 or A <- 1)

load R1,17     // R1 <- 17
load R2,4      // R2 <- 4
add R1,R1,R2   // R1 <- R1 + R2

load R1,true    // R1 <- true
load R2, false  // R2 <- false
add R1,R1,R2    // R1 <- R1 + R2