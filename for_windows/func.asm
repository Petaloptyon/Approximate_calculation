section .text
; ############## f1(x) = 0.35*x^2 - 0.95*x + 2.7
_f1:
    finit
    push    ebp
    mov     ebp, esp
    fld     qword [ebp + 8]      ; ST0 = x (double)
    fld     st0                  ; ST0 = x, ST1 = x
    fmul    st0, st0             ; ST0 = x^2, ST1 = x
    fmul    qword [const_0_35]   ; ST0 = 0.35*x^2, ST1 = x
    fxch    st1                  ; ST0 = x, ST1 = 0.35*x^2
    fmul    qword [const_0_95]   ; ST0 = 0.95*x, ST1 = 0.35*x^2
    fsubp   st1, st0             ; ST0 = 0.35*x^2 - 0.95*x
    fadd    qword [const_2_7]    ; ST0 = 0.35*x^2 - 0.95*x + 2.7
    pop     ebp
    ret

; f1'(x) = 0.7*x - 0.95
_df1:
    finit
    push    ebp
    mov     ebp, esp
    fld     qword [ebp + 8]      ; ST0 = x
    fmul    qword [const_0_7]    ; ST0 = 0.7*x
    fsub    qword [const_0_95]   ; ST0 = 0.7*x - 0.95
    pop     ebp
    ret

; f1''(x) = 0.7
_d2f1:
    finit
    push    ebp
    mov     ebp, esp
    fld     qword [const_0_7]    ; ST0 = 0.7
    pop     ebp
    ret

; ############## f2(x) = 3*x + 1
_f2:
    finit
    push    ebp
    mov     ebp, esp
    fld     qword [ebp + 8]      ; ST0 = x
    fmul    qword [const_3]      ; ST0 = 3.0*x
    fadd    qword [const_1]      ; ST0 = 3.0*x + 1.0
    pop     ebp
    ret

; f2'(x) = 3
_df2:
    finit
    push    ebp
    mov     ebp, esp
    fld     qword [const_3]      ; ST0 = 3.0
    pop     ebp
    ret

; f2''(x) = 0
_d2f2:
    finit
    push    ebp
    mov     ebp, esp
    fldz                        ; ST0 = 0.0
    pop     ebp
    ret

; ############## f3(x) = 1/(x + 2)
_f3:
    finit
    push    ebp
    mov     ebp, esp
    fld     qword [ebp + 8]      ; ST0 = x
    fadd    qword [const_2]      ; ST0 = x + 2
    fld1                        ; ST0 = 1.0, ST1 = x + 2
    fdivrp  st1, st0             ; ST0 = 1/(x+2)
    pop     ebp
    ret

; f3'(x) = -1/(x + 2)^2
_df3:
    finit
    push    ebp
    mov     ebp, esp
    fld     qword [ebp + 8]      ; ST0 = x
    fadd    qword [const_2]      ; ST0 = x + 2
    fld     st0                  ; ST0 = x+2, ST1 = x+2
    fmulp   st1, st0             ; ST0 = (x+2)^2
    fld1                        ; ST0 = 1.0, ST1 = (x+2)^2
    fdivrp  st1, st0             ; ST0 = 1/(x+2)^2
    fchs                         ; ST0 = -1/(x+2)^2
    pop     ebp
    ret

; f3''(x) = 2/(x + 2)^3
_d2f3:
    finit
    push    ebp
    mov     ebp, esp
    fld     qword [ebp + 8]      ; ST0 = x
    fadd    qword [const_2]      ; ST0 = x + 2
    fld     st0                  ; ST0 = x+2, ST1 = x+2
    fmul    st0, st0             ; ST0 = (x+2)^2, ST1 = x+2
    fmul    st1, st0             ; ST0 = (x+2)^2, ST1 = (x+2)^3
    fld1                        ; ST0 = 1.0, ST1 = (x+2)^2, ST2 = (x+2)^3
    fdivrp  st1, st0             ; ST0 = 1/(x+2)^3
    fadd    st0, st0             ; ST0 = 2/(x+2)^3
    pop     ebp
    ret
    
;extern printf
;main:
;    push ebp
;    mov  ebp, esp
;    and  esp, 0xfffffff0
;    sub  esp, 16
;    
;    ; Загружаем аргумент 2.0 (double)
;    fld     qword [const_for_func]; ST0 = 2.0
;    fstp    qword [esp]          ; Сохраняем в стеке (64 бита)
;    
;    ; Вызываем _f2(2.0)
;    call _d2f3                    ; Результат в ST0
;    
;    ; Печатаем результат через printf
;    fstp    qword [esp]          ; Сохраняем double в стек
;    push    fmt_float            ; Форматная строка
;    call    printf
;    add     esp, 12              ; Чистим стек
;    leave
;    ret

global _f1, _f2, _f3
global _df1, _df2, _df3
global _d2f1, _d2f2, _d2f3
;global main
        
section .data
    const_for_func dq -1.9
    const_0_35   dq 0.35
    const_0_95   dq 0.95
    const_2_7    dq 2.7
    const_0_7    dq 0.7
    const_2      dq 2.0
    const_1      dq 1.0
    const_neg_1  dq -1.0
    const_3      dq 3.0

;section .rodata
;    fmt_float db "%.6f", 10, 0   ; Формат вывода (6 знаков после запятой)