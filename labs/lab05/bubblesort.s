# read 10 numbers into an array
# bubblesort them
# then print the 10 numbers

# i in register $t0
# registers $t1 - $t4 used to hold temporary results
# Also, $t1 = index i, $t2 = index i - 1
# $t3 = &numbers[i], $t4 = &numbers[i - 1]
# $t5 = &numbers[0] = numbers, $t6 = x, $t7 = y

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
    # i in register $t0
    # $t1 = index i, $t2 = index i - 1
    # $t3 = &numbers[i], $t4 = &numbers[i - 1]
    # $t5 = numbers, $t6 = swapped, $t7 = x, $t8 = y

    li $t6, 1           # int swapped = 1;
outer:
    beq $t6, 0, end_outer   # while (swapped)

    li $t6, 0           # swapped = 0;
    li $t0, 1           # i = 1;

inner:
    bge $t0, 10, end_inner  # while (i < 10)

    # int x = numbers[i];
    # int y = numbers[i - 1];
    mul $t1, $t0, 4
    addi $t2, $t0, -1
    mul $t2, $t2, 4

    la $t5, numbers

    add $t3, $t5, $t1
    add $t4, $t5, $t2

    lw $t7, ($t3)
    lw $t8, ($t4)

    bge $t7, $t8, no_swap   # if (x < y)
    sw $t8, ($t3)           # numbers[i] = y;
    sw $t7, ($t4)           # numbers[i - 1] = x;
    li $t6, 1               # swapped = 1;

no_swap:
    addi $t0, $t0, 1        # i++;

    b inner
end_inner:

    b outer
end_outer:

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

