# read 10 numbers into an array
# swap any pairs of of number which are out of order
# then print the 10 numbers

# i in register $t0,
# registers $t1 - $t4 used to hold temporary results
# $t6 = x, $t7 = y

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

    # $t0 = i,
    # $t1 = index i, $t2 = index i-1,
    # $t3 = &numbers[0] = numbers
    # $t4 = &numbers[i], $t5 = &numbers[i-1]
    # $t6 = x, $t7 = y
    
    li $t0, 1           # i = 1;
loop:
    bge $t0, 10, end    # while (i < 10)
    
    # int x = numbers[i];
    # int y = numbers[i - 1];
    mul $t1, $t0, 4     # $t1 = (i)th index
    addi $t2, $t0, -1   # $t2 = i - 1
    mul $t2, $t2, 4     # $t2 = (i - 1)th index
    
    la $t3, numbers
    
    add $t4, $t3, $t1
    lw $t6, ($t4)       # x = numbers[i]
    add $t5, $t3, $t2   
    lw $t7, ($t5)       # y = numbers[i - 1]
    
    bge $t6, $t7, no_swap   # if (x < y)

    sw $t7, ($t4)       # numbers[i] = y
    sw $t6, ($t5)       # numbers[i - 1] = x;    

no_swap:
    addi $t0, $t0, 1    # i++;

    b loop
end:

    li $t0, 0           # i = 0
loop1:
    bge $t0, 10, end1   # while (i < 10) {

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    lw $a0, ($t3)       #   load numbers[i] into $a0
    li $v0, 1           #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t0, $t0, 1     #   i++
    b loop1             # }
end1:

    jr $31              # return

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

