.data
_Prompt: .asciiz "Enter an integer:  "
_ret: .asciiz "\n"
.globl main
.text
#FUN_PUBLIC BEGIN
addi $sp,$sp,-12
sw $ra,8($sp)
lw $t1,($fp)
sw $t1,4($sp)
add $fp,$sp,$zero
addi $sp,$sp,-8
#FUN_PUBLIC END
  jal main
  li $v0,10
syscall
read:
  li $v0,4
  la $a0,_Prompt
  syscall
  li $v0,5
  syscall
  sw $v0,12($fp)
add $t0,$ra,$zero
lw $ra,8($fp)
addi $sp,$fp,8
lw $fp,4($fp)
jr $t0
write:
  lw $a0,4($sp)
  addi $sp,$sp,4
  li $v0,1
  syscall
  li $v0,4
  la $a0,_ret
  syscall
add $t0,$ra,$zero
lw $ra,8($fp)
addi $sp,$fp,8
lw $fp,4($fp)
jr $t0
##LABEL
f:
lw $t0,-0($fp) #ID_NO BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #ID_NO END
addi $t0,$zero,1 #INT BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #INT END
lw $t1,8($sp) #EQ BEGIN
lw $t2,4($sp)
addi $sp,$sp,8
addi $t3,$zero,0
addi $t4,$zero,1
beq $t1,$t2,LABEL6
sw $t3,($sp)
j LABEL7
LABEL6:
sw $t4,($sp)
LABEL7:
addi $sp,$sp,-4 #EQ END
lw $t0,-0($fp) #ID_NO BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #ID_NO END
addi $t0,$zero,2 #INT BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #INT END
lw $t1,8($sp) #EQ BEGIN
lw $t2,4($sp)
addi $sp,$sp,8
addi $t3,$zero,0
addi $t4,$zero,1
beq $t1,$t2,LABEL8
sw $t3,($sp)
j LABEL9
LABEL8:
sw $t4,($sp)
LABEL9:
addi $sp,$sp,-4 #EQ END
lw $t1,8($sp) #OR BEGIN
lw $t2,4($sp)
addi $sp,$sp,8
or $t0,$t1,$t2
sw $t0,($sp)
addi $sp,$sp,-4 #OR END
lw $t0,4($sp) #JUDGE BEGIN
addi $sp,$sp,4
beqz $t0,LABEL1 #JUDGE END
addi $t0,$zero,1 #INT BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #INT END
lw $t0,4($sp) #RETURN BEGIN
sw $t0,12($fp)
add $t0,$ra,$zero
lw $ra,8($fp)
addi $sp,$fp,8
lw $fp,4($fp)
jr $t0 #RETURN FINISHED
#GOTO_BREAK BEGIN

j LABEL2
#GOTO_BREAK END

##LABEL
LABEL1:
addi $sp,$sp,-12 #FUN_PUBLIC BEGIN
sw $ra,8($sp)
sw $fp,4($sp) #FUN_PUBLIC END
lw $t0,-0($fp) #ID_NO BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #ID_NO END
addi $t0,$zero,1 #INT BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #INT END
lw $t1,8($sp) #MINUS BEGIN
lw $t2,4($sp)
addi $sp,$sp,8
sub $t0,$t1,$t2
sw $t0,($sp)
addi $sp,$sp,-4 #MINUS END
addi $fp,$sp,4 #FUN_CALL BEGIN
addi $sp,$fp,-8
jal f #FUN_CALL END
addi $sp,$sp,-12 #FUN_PUBLIC BEGIN
sw $ra,8($sp)
sw $fp,4($sp) #FUN_PUBLIC END
lw $t0,-0($fp) #ID_NO BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #ID_NO END
addi $t0,$zero,2 #INT BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #INT END
lw $t1,8($sp) #MINUS BEGIN
lw $t2,4($sp)
addi $sp,$sp,8
sub $t0,$t1,$t2
sw $t0,($sp)
addi $sp,$sp,-4 #MINUS END
addi $fp,$sp,4 #FUN_CALL BEGIN
addi $sp,$fp,-8
jal f #FUN_CALL END
lw $t1,8($sp) #ADD BEGIN
lw $t2,4($sp)
addi $sp,$sp,8
add $t0,$t1,$t2
sw $t0,($sp)
addi $sp,$sp,-4 #ADD END
lw $t0,4($sp) #RETURN BEGIN
sw $t0,12($fp)
add $t0,$ra,$zero
lw $ra,8($fp)
addi $sp,$fp,8
lw $fp,4($fp)
jr $t0 #RETURN FINISHED
##LABEL
LABEL2:
##LABEL
main:
addi $sp,$sp,-12 #FUN_PUBLIC BEGIN
sw $ra,8($sp)
sw $fp,4($sp) #FUN_PUBLIC END
addi $fp,$sp,0 #FUN_CALL BEGIN
addi $sp,$fp,-0
jal read #FUN_CALL END
lw $t0,-4($fp) #ID_NO BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #ID_NO END
lw $t0,8($sp) #ASSIGN_OP BEGIN
addi $sp,$sp,8
sw $t0,-4($fp) #ASSIGN_OP END
addi $t0,$zero,1 #INT BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #INT END
lw $t0,-0($fp) #ID_NO BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #ID_NO END
lw $t0,8($sp) #ASSIGN_OP BEGIN
addi $sp,$sp,8
sw $t0,-0($fp) #ASSIGN_OP END
##LABEL
LABEL3:
lw $t0,-0($fp) #ID_NO BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #ID_NO END
lw $t0,-4($fp) #ID_NO BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #ID_NO END
lw $t1,8($sp) #LE BEGIN
lw $t2,4($sp)
addi $sp,$sp,8
addi $t3,$zero,0
addi $t4,$zero,1
sub $t0,$t1,$t2
blez $t0,LABEL10
sw $t3,($sp)
j LABEL11
LABEL10:
sw $t4,($sp)
LABEL11:
addi $sp,$sp,-4 #LE END
lw $t0,4($sp) #JUDGE BEGIN
addi $sp,$sp,4
beqz $t0,LABEL4 #JUDGE END
addi $sp,$sp,-12 #FUN_PUBLIC BEGIN
sw $ra,8($sp)
sw $fp,4($sp) #FUN_PUBLIC END
addi $sp,$sp,-12 #FUN_PUBLIC BEGIN
sw $ra,8($sp)
sw $fp,4($sp) #FUN_PUBLIC END
lw $t0,-0($fp) #ID_NO BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #ID_NO END
addi $fp,$sp,4 #FUN_CALL BEGIN
addi $sp,$fp,-8
jal f #FUN_CALL END
addi $fp,$sp,4 #FUN_CALL BEGIN
addi $sp,$fp,-4
jal write #FUN_CALL END
##LABEL
LABEL5:
lw $t0,-0($fp) #ID_NO BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #ID_NO END
addi $t0,$zero,1 #INT BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #INT END
lw $t1,8($sp) #ADD BEGIN
lw $t2,4($sp)
addi $sp,$sp,8
add $t0,$t1,$t2
sw $t0,($sp)
addi $sp,$sp,-4 #ADD END
lw $t0,-0($fp) #ID_NO BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #ID_NO END
lw $t0,8($sp) #ASSIGN_OP BEGIN
addi $sp,$sp,8
sw $t0,-0($fp) #ASSIGN_OP END
j LABEL3 #GOTO_JUDGE BEGIN
##LABEL
LABEL4:
addi $t0,$zero,0 #INT BEGIN
sw $t0,($sp)
addi $sp,$sp,-4 #INT END
lw $t0,4($sp) #RETURN BEGIN
sw $t0,12($fp)
add $t0,$ra,$zero
lw $ra,8($fp)
addi $sp,$fp,8
lw $fp,4($fp)
jr $t0 #RETURN FINISHED
