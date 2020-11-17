#Q1.Assembly Language Programming in MIPS
#Definition: In this question, you are asked to implement an assembly application in MIPS ISA. Your application first asks a positive integer value; N, from the console. Then, it prints a NxN square to the screen by using * s. For input 7, your output should be as in the example:
#     * * * * * * * * 
#     * * * * * * * * 
#     * * * * * * * * 
#     * * * * * * * * 
#     * * * * * * * * 
#     * * * * * * * * 
#     * * * * * * * *   


.data 
	prompt: .asciiz "Enter a number: "
	char: .asciiz  "*"
	space: .asciiz "\n"

.text
.globl main

main:
	# Ask the user to enter a value
	li $v0, 4
	la $a0, prompt
	syscall

	# get the user's value
	li $v0, 5
	syscall
	li $s4, 0
	li $s3, 0
	# store the result in t0
	move $s0, $v0
	j for3

for2:	addi $s4, $s4, 1 # j++
	bge $s4, $s0, Exit # for loop
	li $v0, 4 # display \n
	la $a0, space
	syscall
	li $s3, 0
	j for3

for3: 
	bge $s3, $s0, for2 # for(i = 0; i < prompt; i++)
	addi $s3, $s3, 1 #i++
	li $v0, 4 # display *
	la $a0, char
	syscall
	j for3

Exit:
	li $v0, 10 #load exit
	syscall # execute exit
