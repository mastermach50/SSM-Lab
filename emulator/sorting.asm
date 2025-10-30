DATA SEGMENT
    MSG1 DB 10,13,"ENTER A NUMBER: $"
    MSG2 DB 10,13,"SORTING DONE. CHECK ARRAY AT 3000H$"
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA
START:
    MOV AX, DATA
    MOV DS, AX          ; Initialize data segment
    MOV CX, 5h           ; Number of elements
    MOV SI, 3000H       ; Store numbers starting from address 3000H

INPUT_LOOP:
    CALL INPUTNUM       ; Get number ? DX
    MOV [SI], DX        ; Store 16-bit number in memory
    ADD SI, 2h           ; Move to next word location
    LOOP INPUT_LOOP     ; Repeat until CX = 0
    MOV BX, 05H
    DEC BX
OUTER:
    MOV CX, 05H
    DEC CX
    MOV SI, 3000H
INNER:

    MOV AX, [SI]
    ADD SI, 02H
    CMP AX, [SI]
    JNA LOOPING
    
    XCHG AX,[SI]
    SUB SI, 02H
    MOV [SI], AX
    ADD SI, 02H
    
LOOPING:
    LOOP INNER
    
    DEC BX
    JNZ OUTER
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H   
    HLT            ; Exit to DOS

INPUTNUM PROC
    PUSH AX
    PUSH BX
    PUSH CX

    LEA DX, MSG1
    MOV AH, 09H
    INT 21H             ; Display prompt

    MOV DX, 0h           ; Clear DX (store result)
    MOV CX, 10h          ; Base 10 multiplier

READ_CHAR:
    MOV AH, 01H         ; Read character
    INT 21H
    CMP AL, 0DH         ; Enter pressed?
    JE DONE_INPUT

    SUB AL, 30H         ; Convert ASCII to number
    MOV BL, AL
    MOV BH, 0h
    MOV AX, DX
    MUL CX              ; DX = DX * 10
    ADD AX, BX
    MOV DX, AX
    JMP READ_CHAR

DONE_INPUT:
    POP CX
    POP BX
    POP AX
    RET
INPUTNUM ENDP

CODE ENDS
END START