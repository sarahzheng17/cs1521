# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

# i in register $t0
# $t1 = "offset", $t2 = "address of numbers", $t3 = "address of numbers[i]"
# used for calcultaing numbers[i]
# swapped = $t4, x = $t5, y = $t6

main:

    li $t0, 0           # i = 0
loop0:
    bge $t0, 10, end0   # while (i < 10) {

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    sw $v0, ($t3)       #   store entered number in array

    add $t0, $t0, 1     #   i++;
    b loop0             # }
end0:

    # PUT YOUR CODE HERE
    
    li $t4, 0           # int swapped = 0;
    li $t0, 1           # i = 1;

loop:
    bge $t0, 10, end    # while (i < 10)
    
    mul $t1, $t0, 4     # int x = numbers[i];
    la $t2, numbers
    add $t3, $t2, $t1
    lw $t5, ($t3)

    addi $t1, $t0, -1   # index the (i-1)th index
    mul $t1, $t1, 4     # int y = numbers[i - 1];  
    la $t2, numbers
    add $t3, $t2, $t1
    lw $t6, ($t3)

    bge $t5, $t6, no_swap   # if (x < y)
    li $t4, 1           # swapped = 1;

no_swap:
    addi $t0, $t0, 1    # i++;

    b loop

end:
    move $a0, $t4         # printf("%d", swapped)
    li $v0, 1           #
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr $31

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};
#    .word 1 2 3 5 4 6 7 8 9 10   

