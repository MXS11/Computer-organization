# Q2.Assembly Language, Programming a Recursive Method in MIPS
# Definition: In this question, you are asked to implement a recursive code assembly in MIPS ISA. 
# Your application should ask an X value from the console. Then it calculates the sum of all integer values between zero and x recursively.  


.data
	promptMsg: .asciiz "Enter a number: "
	resultMsg: .ascii "\nProssessing... \nThe factorial number is: "
	# Define the integers
	Num:	.word 0
	Result:	.word 0
	
.text 
	.globl main
	main:
	     # Read the values given by the user
	     li $v0, 4
	     la $a0, promptMsg
	     syscall
	     
	     # The value given by the user will be stored in $v0
	     li $v0, 5
	     syscall
	     
	     # Store the value given by the user in the int Num
	     sw $v0, Num
	     
	     # call factorial function and store the value after it's facotrized in Result
	     lw $a0, Num
	     jal FactorialFunc
	     sw $v0, Result
	     
	     # Show the results
	     li $v0, 4
	     la $a0, resultMsg
	     syscall
	     
	     li $v0, 1
	     lw $a0, Result
	     syscall
	     
	     # End the program
	     li $v0, 10
	     syscall
	     
# Create FactorialFunc

.globl FactorialFunc
FactorialFunc:
		# Store the value of the address into the stack
		subu $sp, $sp, 8
		sw $ra, ($sp)
		sw $s0, 4($sp) 
		
		# Base case
		li $v0, 1
		beq $a0, 0, factorialFinished # if the int is 0 go to factorialFinished
		
		# FactorialFun(Num - 1)
		move $s0, $a0
		sub $a0, $a0, 1
		jal FactorialFunc
		
		# Execute when the recursion is rewinding
		# it'll calculate the previous value($v0) multiplied by the local values and it'll be stored in ($v0) 
		mul $v0, $s0, $v0
		
		
		factorialFinished:
				  lw $ra, ($sp) # restore the value of the reutrning address from the stack
				  lw $s0, 4($sp) # load the value of the local veriable to the register
				  addu $sp, $sp, 8 # in order to restore the stack we add the value 8 which was subtracted at the beginning of the code
				  jr $ra # jump to the previous address
				  
				  
				  
		
