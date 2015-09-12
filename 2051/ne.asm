  ORG 0000H
    LJMP START
    ORG 001BH
    LJMP Timer1Interrupt

START:
    
    MOV SP,#60H
    LCALL InitTimer1
    MOV R1,#00H
    mov r0,#00h
LOOP:
         ;add your code here!
    clr P3.0
    CJNE r1,#20,$
    ljmp display
    LJMP LOOP

InitTimer1:
    MOV TMOD,#10H
    MOV TH1,#3CH
    MOV TL1,#0B0H
    SETB EA
    SETB ET1
    SETB TR1
    RET

Timer1Interrupt:
    PUSH DPH
    PUSH DPL
    PUSH ACC
    MOV TH1,#3CH
    MOV TL1,#0B0H
    ;========================
         ;add your code here!
    ;========================
    mov a,r1
    add a,#01h
    mov r1,a
    ;setb p3.0
    POP ACC
    POP DPL
    POP DPH
    RETI

;œ‘ æ≥Ã–Ú
display:
PUSH DPH
PUSH DPL
PUSH ACC

mov a,#01h
mov dptr,#table

movc a,@a+dptr

mov p1,a

mov r1,0
add a,#01h
mov r0,a

POP ACC
POP DPL
POP DPH
ljmp loop



ret
table:
db 01h,4Fh,12h,06h,4ch,24h,10h,0fh,00h,04h
END

