.syntax unified
.cpu cortex-m4
.text

.global Ten32
.thumb_func
.align
Ten32:
	// Load the constant, 10, into the R0
	MOV R0,10
	BX LR


.global Ten64
.thumb_func
.align
Ten64:
	// Store leading zeros in the MSB register, 10 goes in the LSB reg
	LDR R0,=10
	LDR R1,=0
	BX LR

.global Incr
.thumb_func
.align
Incr:
	// Add 1 and R0 and store to R0
	ADD R0,R0,1
	BX LR


.global Nested1
.thumb_func
.align
Nested1:
	// Add the rand return to 1 and store in R0 for return
	PUSH {LR}
	BL rand
	ADD R0,R0,1
	POP {PC}

.global Nested2
.thumb_func
.align
Nested2:
	// Finds rand then stores in R4 to find another rand
	PUSH {LR}
	BL rand
	MOV R4,R0
	BL rand
	ADD R0,R0,R4
	POP {PC}

.global PrintTwo
.thumb_func
.align
PrintTwo:
	// Pushs the parameters to the stack since manipulation only needs to be done twice
	PUSH {LR,R0,R1}
	BL printf
	// Prints and then pops those params for one more print
	POP {R0,R1}
	ADD R1,R1,1
	BL printf
	POP {PC}

.end