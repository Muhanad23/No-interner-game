;Muhanad Atef
;Sec 2
;Bn 25
INCLUDE MACROO.INC
.model small
.386
.stack 64
.data
ORG 100
LocationY DB 16H
lOCXBIG DB 40
lOCXSMALL DB 77
UPDOWN DB 2 
SCORE DB 0
HIGHSCORE DB 0
GAMEOVER DB 0
MSG DB '- Game Over press any key to RESTART $'
draw_line DB 80 DUP('_'),'$'
SCORE_LBL DB 'SCORE:$'
HI_LBL DB 'HIGHSCORE:$'
MSG1 DB '- PRESS ANY KEY TO START GAME$'
PRINT_SCORE DB 3 DUP('$')
PRINT_HIGH DB 3 DUP('$')
.code
main proc far
  
     mov ax,@data
     mov ds,ax
     mov es,ax 

     mov ah,0        ;OPEN TEXT MODE 
     mov al,3h
     int 10h
     mov ch, 32    ;HIDE CURSOR
     mov ah, 1
     int 10h     
     FRAME
     MOV BH,0
     MOV AH,2
     MOV DX,1800H    ;BKTB RESTART
     INT 10H
     MOV AH,9
     MOV DX,OFFSET MSG1
     INT 21H
     DrawPlayer LocationY,044H
     DRAWOBJECT lOCXBIG,lOCXSMALL,0FFH
     ll:
     mov ah,1
     int 16h
     jz ll
     mov ah,0
     int 16h
     L:  
     UPDATE_SCORE 
     DrawPlayer LocationY,044H 
     DELAY     
     MOV DH,lOCXSMALL
     CMP DH,2
     JG GO2   
     DRAWOBJECT lOCXBIG,lOCXSMALL,0H
     MOV lOCXSMALL,77
     GO2:
     MOV DH,lOCXBIG
     CMP DH,2
     JG GO21  
     DRAWOBJECT lOCXBIG,lOCXSMALL,0H
     MOV lOCXBIG,77
     GO21:
     DRAWOBJECT lOCXBIG,lOCXSMALL,0H    
     DEC lOCXBIG
     DEC lOCXSMALL 
     DRAWOBJECT lOCXBIG,lOCXSMALL,0FFH
     MOV BL,0AH
     CMP LocationY,BL 
     JG KML
     DrawPlayer LocationY,0
     MOV UPDOWN,0
     KML:
     MOV BL,16H
     CMP LocationY,BL
     JL KML1
     MOV BL,UPDOWN
     CMP BL,0
     JNZ KML1
     MOV LocationY,16H
     MOV UPDOWN,2
     KML1:
     MOV BL,UPDOWN
     CMP BL,0
     JNZ UP
     DrawPlayer LocationY,0H
     INC LocationY
     UP:
     CMP BL,1
     JNZ GETKEY
     DrawPlayer LocationY,0H
     DEC LocationY
     GETKEY:
     MOV BL,LocationY
     CMP BL,16H
     JNZ KKKMMMLLL
     mov ah,1                                     ;TAKE A KEY FROM THE USER
     int 16h
     CMP AH,1
     JZ KKKMMMLLL     
     CMP AH,48H
     JNZ NOTUP
     MOV UPDOWN,1
     NOTUP:
     mov ah,0                                     
     int 16h
     KKKMMMLLL:
     CHECK
     MOV BL,GAMEOVER
     CMP BL,0
     JZ CNT    
     DrawPlayer LocationY,044H 
     MOV BH,0
     MOV AH,2
     MOV DX,1800H    ;BKTB RESTART
     INT 10H
     MOV AH,9
     MOV DX,OFFSET MSG
     INT 21H
     UU:     
     MOV AH,1
     INT 16H
     JZ UU
     mov ah,0                                     
     int 16h    
     MOV BH,SCORE
     CMP HIGHSCORE,BH
     JA ENZL
     MOV HIGHSCORE,BH
     ENZL:
     FRAME
     MOV LocationY,16H
     MOV lOCXBIG,40
     MOV lOCXSMALL,77
     MOV UPDOWN,2 
     MOV SCORE,0
     MOV GAMEOVER,0
     UPDATE_HIGH
     CNT:
     JMP L
HLT
MAIN ENDP
END MAIN  
     