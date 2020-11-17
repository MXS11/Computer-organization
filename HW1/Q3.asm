# Q3.Assembly Language, Programming with Arrays in MIPS
# Definition: In this question, you are asked to implement an assembly code in MIPS which operates on arrays.
# Your application first asks an integer value for the number of elements in an array. Than, that many times it gets an integer value from the console for the elements of the array. Then it sorts the array and prints the sorted array to the screen.  
# Example: 
# Size of the array?: 5
# 1: 13
# 2: 25
# 3: 2
# 4: 17
# 5: 21
# Your sorted array is: 2 13 17 21 25

.data
	array: .space 40
	prompt: .asciiz "Please enter a number: "
	point: .asciiz "."
	colon: .asciiz " : "
	nextline: .asciiz "\n"
	spacing: .asciiz ", "
	Intput: .asciiz "Input  :"

.text
.globl main
main:
	addi $t0, $t0, 40 #Array size constant
	addi $t4, $t4, 90 #Loop counter
	addi $t9, $t9, 1 # Input counter
	addi $s5, $s5, 10 # Division
	
	li $v0, 4
	la $a0, prompt
	syscall
	
	li $v0, 4
	la $a0, nextline
	syscall

input:
	beq $t1, $t0, continue
	
	move $a0, $t9
	li $v0, 1
	syscall
	
	li $v0, 4
	la $a0, colon
	syscall
	
	li $v0, 5
	syscall 
	move $t2, $v0
	
	sw $t2, array($t1)
		addi $t1, $t1, 4
	addi $t9, $t9, 1
	
	j input

continue:
	move $t1, $zero
	move $t2, $zero
	addi $t2, $t2, 4
	move $s0, $zero
	addi $s0, $s0, 1
	
	
sort:
	beq $t3, $t4, calculation
	beq $t2, $t0, continue
	
	lw $t5, array($t1)
	lw $t6, array($t2)
	
	addi $t3, $t3, 1
	
	slt $t7, $t5, $t6
	beq $t7, $s0, swap
	
	addi $t1, $t1, 4
	addi $t2, $t2, 4
	
	j sort
	
	
calculation:
		move $t1, $zero
		move $t2, $zero
		move $t3, $zero
		move $t4, $zero
		addi $t4, $t4, 36
		move $t5, $zero
		move $t6, $zero
		move $t7, $zero
	
swap:
	sw $t5, array($t2)
	sw $t6, array($t1)
	
	addi $t1, $t1, 4
	addi $t0, $t0, 4
	
	j sort
	
	
output:
	li $v0, 4
	la $a0, nextline
	syscall
	
	lw $t5, array($t3)
	lw $t6, array($t4)
	
	li $v0, 4
	la $a0, Intput
	syscall
	
element:
	beq $t7, $t0, nextline
	lw $t8, array($t7)
	addi $t7, $t7, 4
	
	move $a0, $t8
	li $v0, 1
	syscall
	
	beq $t7, $t0, element
	
	li $v0, 4
	la $a0, spacing
	syscall
	
