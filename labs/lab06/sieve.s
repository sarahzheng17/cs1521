# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

    # PUT YOUR CODE


  .data           # the data segment to store global data
space:  .asciiz " "     # whitespace to separate prime numbers

    .text           # the text segment to store instructions
    .globl  main        # define main to be a global label
main:   li  $s0, 0x00000000 # initialize $s0 with zeros
    nor $s1, $s0, $s0   # saves one ALU count over using li $s1, 0x11111111
    li  $t9, 200    # find prime numbers from 2 to $t9

    add $s2, $sp, 0 # backup bottom of stack address in $s2

    li  $t0, 2      # set counter variable to 2

init:   sw  $s1, ($sp)  # write ones to the stackpointer's address
    add $t0, $t0, 1 # increment counter variable
    sub $sp, $sp, 4 # subtract 4 bytes from stackpointer (push)
    bne     $t0, $t9, init  # take loop if $t0 != $t9, changed ble to bne
    addi    $t8, $t0, 15    # approximate square root of 200
    li  $t0, 1      # reset counter variable to 1

outer:  add     $t0, $t0, 2 # increment counter variable (start at 2)
    mul $t1, $t0, $t0   # squaring $t0 and save it to $t1
    bgt $t1, $t8, print # start printing prime numbers when $t1 > $t8, changed so only bgt if $t1 > square root

check:  add $t2, $s2, 0 # save the bottom of stack address to $t2
    sll $t3, $t0, 2 # calculate the number of bytes to jump over
    sub $t2, $t2, $t3   # subtract them from bottom of stack address
    add $t2, $t2, 8 # add 2 words - we started counting at 2!

    lw  $t3, ($t2)  # load the content into $t3

    beq $t3, $s0, outer # only 0's? go back to the outer loop

inner:  add $t2, $s2, 0 # save the bottom of stack address to $t2
    sll $t3, $t1, 2 # calculate the number of bytes to jump over

    add     $t4, $t1, 2 # save $t1 + 2 into $t4, added
    sll     $t5, $t4, 2 # mul by 4, added

    sub $t2, $t2, $t3   

    add $t2, $t2, 8 # add 2 words - we started counting at 2!

    sw  $s0, ($t2) 

    add $t1, $t1, $t0   # do this for every multiple of $t0

    add $t1, $t1, $t0   # adding $t0 to $t1, added
    sub $t2, $t2, $t5   # save $t2 - $t5 into $t2, added
    add $t2, $t2, 8 # adding 8 to $t2, added
    sw  $s0, ($t2)  
    add $t4, $t4, $t0   # adding $t0 to $t4, added

    blt $t1, $t9, inner 

    j   outer       # some multiples left? go back to inner loop, changed to branching to outer

print:  li  $t0, 1      # reset counter variable to 1

  


count:  add $t0, $t0, 2 # increment counter variable (start at 2), skipping even numbers

    bgt $t0, $t9, exit  # make sure to exit when all numbers are done (branch to exit if $t0 > $t9)
    
    add $t2, $s2, 0 # save the bottom of stack address to $t2
    sll $t3, $t0, 2 # calculate the number of bytes to jump over
    sub $t2, $t2, $t3   # subtract them from bottom of stack address
    add $t2, $t2, 8 # add 2 words - we started counting at 2!

    lw  $t3, ($t2)  # load the content into $t3
    beq $t3, $s0, count # only 0's? go back to count loop

    add $t3, $s2, 0 # save the bottom of stack address to $t3

    sub $t3, $t3, $t2   # substract higher from lower address (= bytes)
    srl $t3, $t3, 2 # changed div to srl
    add $t3, $t3, 2 # add 2 (words) = the final prime number!

    li  $v0, 1      # system code to print integer
    add $a0, $t3, 0 # the argument will be our prime number in $t3
    syscall         # print it!

    li  $v0, 4      # system code to print string
    la  $a0, space  # the argument will be a whitespace
    syscall         # print it!
        li $a0, '\n'
    li $v0, 11    # print_character
    syscall
    bne $t0, $t9, count # take loop when $t0 != $t9, changed ble to bne

exit:   li  $v0, 10     # set up system call 10 (exit)
    syscall 

