.syntax unified
.cpu cortex-m4
.text

// Returns b^2 - 4ac
.global Discriminant
.thumb_func
.align
Discriminant:
	VMUL.F32 	S1, S1, S1
	VMOV		S3, 4.0
	VMUL.F32	S0, S0, S3
	VMLS.F32 	S1, S2, S0
	VMOV		S0, S1
	BX LR


// Gives the positive root
.global Root1
.thumb_func
.align
Root1:
	PUSH 		{LR}
	VPUSH 		{S16, S17}
	VNEG.F32	S17, S1
	VMOV		S16, 2.0
	VMUL.F32	S16, S0, S16
	BL 			Discriminant
	VSQRT.F32	S0, S0
	VADD.F32	S0, S17, S0
	VDIV.F32 	S0, S0, S16
	VPOP 		{S16, S17}
	POP			{PC}

// Gives the negative root
.global Root2
.thumb_func
.align
Root2:
	PUSH 		{LR}
	VPUSH 		{S16, S17}
	VNEG.F32	S17, S1
	VMOV		S16, 2.0
	VMUL.F32	S16, S0, S16
	BL 			Discriminant
	VSQRT.F32	S0, S0
	VSUB.F32	S0, S17, S0
	VDIV.F32 	S0, S0, S16
	VPOP 		{S16, S17}
	POP			{PC}


// Returns ax^2 + bx + c
.global Quadratic
.thumb_func
.align
Quadratic:
	VMOV		S4, S0
	VMUL.F32 	S0, S4, S4		// x^2
	VMLA.F32	S3, S1, S0 	// ax^2 + c
	VMLA.F32	S3, S2, S4	// ax^2 + bx + c
	VMOV		S0, S3
	BX 		LR

.end