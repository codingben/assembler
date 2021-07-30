; File: test_2.as (page 37-38)
; .entry - directive
; K: - label
; add - command
; $0 - register
; ".entry" and ".extern" should create binary file

MAIN: add   $3,$5,$9
LOOP: ori   $9,-5,$2
      la    vall
      jmp   Next
Next: move  $20,$4
      bgt   $4,$2,END
      la    K
      sw    $0,4,$10
      bne   $31,$9,LOOP
      call  vall
      jmp   $4
END:  stop
STR:  .asciz "aBed"
LIST: .db    6,-9
      .dh    27056
.entry K
K:     .dw   31,-12
.extern vall
