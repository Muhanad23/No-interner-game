;----------------------------------DRAW-------------------------------------
Draw    MACRO
      PUSHA
      MOV AX,1301H
      MOV CH,00H
      INT 10H
      POPA            
ENDM    Draw
;---------------------------------------------------------------------------
;---------------------------------DELAY-------------------------------------
Delay MACRO
       PUSHA
        Mov Ah,86H
        Mov Cx,0h
        Mov Dx,093e8H
        int 15h  
     POPA   
ENDM    Delay 
;---------------------------------------------------------------------------
;-------------------------------DrawPlayer----------------------------------------------
DrawPlayer MACRO LocationY,Color                                                    
      LOCAL PRINT
      LOCAL PRINT1
      LOCAL PRINT2
      LOCAL EXIT
      PushA    
      MOV DL,15
      MOV DH,LocationY
      MOV DI,0 ; DA 3SHAN ASHOF ARSM ANHY GOZ2
      MOV CL,2         ;L RGL
      PRINT: 
      INC DI       
      MOV BP,44H      
      MOV BX, Color  
      Draw
      CMP DI,1     ;L BODY 
      JNE PRINT1   
      SUB DL,2
      DEC DH
      MOV CL,4
      JMP PRINT      
      PRINT1:   
      CMP DI,2
      JNE PRINT2
      DEC DH
      MOV CL,1
      MOV DL,16 
      JMP PRINT
      PRINT2:
      CMP DI,3
      JNE EXIT
      MOV CL,2
      DEC DH
      JMP PRINT
      EXIT:
      POPA
ENDM DrawPlayer    
;---------------------------------------------------------------------------------------
;-------------------------------DrawOBJECT----------------------------------------------
DRAWOBJECT MACRO XBIG,XSMALL,Color                                                    
      LOCAL PRINT
      LOCAL PRINT1
      LOCAL PRINT2
      LOCAL EXIT
      PushA    
      MOV DL,XBIG        ;DRAW BIG TREE
      MOV DH,16H
      MOV DI,0 ; DA 3SHAN ASHOF ARSM ANHY GOZ2
      MOV CL,1         ;L RGL
      PRINT: 
      INC DI       
      MOV BP,44H      
      MOV BX, Color 
      MOV SI,3   
      Draw
      CMP DI,1     ;L BODY
      JNE PRINT1   
      DEC DL
      DEC DH
      MOV CL,3
      JMP PRINT      
      PRINT1:   
      CMP DI,2
      JNE PRINT2
      DEC DH
      DEC DL
      MOV CL,1
      DRAW
      DEC DH
      DRAW
      INC DH      
      ADD DL,2
      DRAW
      DEC DH
      DRAW
      DEC DH
      DRAW
      ADD DH,2
      ADD DL,2
      DRAW
      DEC DH 
      DRAW
      PRINT2:       ;DRAW SMALL TREE 
      MOV DH,16H
      MOV DL,XSMALL
      MOV CL,1
      DRAW
      DEC DH
      MOV CL,3
      DEC DL
      DRAW
      DEC DH
      MOV CL,1
      DRAW
      ADD DL,2
      DRAW
      EXIT:
      POPA
ENDM DRAWOBJECT    
;---------------------------------------------------------------------------------------
;------------------------------------CHECK----------------------------------
CHECK MACRO
      LOCAL CHECKSMALL
      LOCAL KML 
      LOCAL EXIT
      LOCAL EXIT1
      PUSHA
      MOV BL,lOCXBIG
      CMP BL,19
      JG CHECKSMALL
      CMP BL,11
      JL CHECKSMALL
      MOV BH,LocationY
      CMP BH,13H
      JL CHECKSMALL 
      MOV GAMEOVER,1
      CHECKSMALL:  
      CMP BL,10
      JNE KML
      INC SCORE
      KML:      
      MOV BL,lOCXSMALL
      CMP BL,18
      JG EXIT
      CMP BL,12
      JL EXIT
      MOV BH,LocationY
      CMP BH,14H
      JL EXIT
      MOV GAMEOVER,1
      EXIT:
      CMP BL,11
      JNE EXIT1
      INC SCORE
      EXIT1:
      POPA
ENDM CHECK
;---------------------------------------------------------------------------
;------------------------frame----------------------------------------------
FRAME MACRO 
    PUSHA    
    mov ax,0600h
    mov bh,07
    mov cx,0
    mov dx,184FH
    int 10h
    MOV BH,0
    mov ah,2         ;MOVE CURSOR
    mov dx,100h
    int 10h
    mov ah, 9
    mov dx, offset DRAW_LINE ;AWL 5T
    int 21h
    MOV AH,2
    MOV DX,200H
    INT 10H
    MOV AH,9
    mov dx, offset SCORE_LBL ;SCORE LBL
    int 21h
    MOV AH,2
    MOV DX,300H
    INT 10H
    mov ah, 9
    mov dx, offset DRAW_LINE ;TANI 5T
    int 21h
    MOV AH,2
    MOV DX,400H
    INT 10H
    MOV AH,9
    mov dx, offset HI_LBL ;HI SCORE LBL
    int 21h
    MOV AH,2
    MOV DX,500H
    INT 10H
    MOV AH,9
    mov dx, offset DRAW_LINE ;DISPLAY MSG    
    int 21h                        
    MOV AH,2
    MOV DX,1700H
    INT 10H
    MOV AH,9
    MOV DX,OFFSET DRAW_LINE
    INT 21H
    POPA
ENDM FRAME  
;-----------------------------------UPDATE SCORE----------------------------------
UPDATE_SCORE  MACRO
    LOCAL L1
    LOCAL L2
    LOCAL L3      
    PUSHA  
    mov ax,0600h
    mov bh,07
    mov cx,210H
    mov dx,220H
    int 10h
    MOV BH,SCORE
    MOV BL,BH
    SHR BL,4
    L1:
    MOV DI,BX
    SHL DI,4
    SHR DI,12
    CMP DI,0AH
    JC L2
    ADD BH,6
    L2:
    CMP BL,0
    JZ L3
    ADD BH,6
    DEC BL
    CMP BL,0
    JNZ L1    
    MOV DI,BX
    SHL DI,4
    SHR DI,12
    CMP DI,0AH
    JC L3
    ADD BH,6   
    L3:        
    SHR BX,4
    SHR BL,4
    ADD BH,30H
    ADD BL,30H  
    MOV PRINT_SCORE[0],BH
    MOV PRINT_SCORE[1],BL
    MOV BH,0
    mov ah,2         ;MOVE CURSOR
    mov dx,210h
    int 10h
    mov ah, 9
    mov dx, offset PRINT_SCORE ;PRINT SCORE
    int 21h
    POPA
ENDM UPDATE_SCORE 
;-----------------------------------------------------------------------------
;-----------------------------------UPDATE HIGH SCORE----------------------------------
UPDATE_HIGH  MACRO  
    LOCAL L1
    LOCAL L2
    LOCAL L3          
    PUSHA   
    mov ax,0600h
    mov bh,07
    mov cx,410H
    mov dx,420H
    int 10h
    MOV BH,HIGHSCORE
    MOV BL,BH
    SHR BL,4
    L1:
    MOV DI,BX
    SHL DI,4
    SHR DI,12
    CMP DI,0AH
    JC L2
    ADD BH,6
    L2:
    CMP BL,0
    JZ L3
    ADD BH,6
    DEC BL
    CMP BL,0
    JNZ L1    
    MOV DI,BX
    SHL DI,4
    SHR DI,12
    CMP DI,0AH
    JC L3
    ADD BH,6   
    L3:        
    SHR BX,4
    SHR BL,4
    ADD BH,30H
    ADD BL,30H  
    MOV PRINT_HIGH[0],BH
    MOV PRINT_HIGH[1],BL
    MOV BH,0
    mov ah,2         ;MOVE CURSOR
    mov dx,410h
    int 10h
    mov ah, 9
    mov dx, offset PRINT_HIGH ;PRINT SCORE
    int 21h
    POPA
 ENDM UPDATE_HIGH 