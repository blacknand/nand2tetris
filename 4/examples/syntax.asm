// The Hack computer is designed to maniplaute 3, 16 bit registers

// The three register types are:
    // - A data register, denoted D
    // - A address register, denoted A
    // - A selected data memory register, denoted M

// The address register, A, serves both as an address and a data register
// The syntax @N will set the address register, A, to the value of N
// The @N register will make the RAM register whose value is N the selected memory register,
// M and it will make the ROM register whose value is N the selected instruction


// Example from page 67
load A,17  
load M,1                     

load R1,17     // R1 <- 17
load R2,4      // R2 <- 4
add R1,R1,R2   // R1 <- R1 + R2

load R1,true    // R1 <- true
load R2, false  // R2 <- false
add R1,R1,R2    // R1 <- R1 + R2