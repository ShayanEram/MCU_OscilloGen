/*
 * asmFunc.s
 * author: Shayan Eram
 */
.syntax unified
.text
.global firFilterASM
.thumb_func

firFilterASM:
    PUSH    {r4-r7, lr}          // Save registers
    MOV     r3, #0               // Initialize result (r3 = output)

loop:
    LDRSH   r4, [r0], #2         // Load signal[i], advance r0 (signed load)
    LDRSH   r5, [r1], #2         // Load coeffs[i], advance r1 (signed load)
    MLA     r3, r4, r5, r3       // Multiply + Accumulate: result += signal[i] * coeffs[i]

    SUBS    r2, r2, #1           // Decrement loop counter
    BNE     loop                 // Continue looping if r2 != 0

    MOV     r0, r3               // Store result in r0 (return value)
    POP     {r4-r7, lr}          // Restore registers
    BX      lr                   // Return

