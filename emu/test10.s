    la $t2, numbers     #
    add $t1, $t1, $t2   #
    sw $v0, ($t1)       #   store entered number in array

    add $t0, $t0, 1     #   count++;
    j read              # }

print:
    la $a0, string1     # printf("Reverse order:\n");
    li $v0, 4
    syscall
    li $t0, 9           # count = 9;
next:
    bltz $t0, end1    # while (count >= 0) {

    mul $t1, $t0, 4     #   printf("%d", numbers[count])
    la $t2, numbers     #   calculate &numbers[count]
    add $t1, $t1, $t2   #
    lw $a0, ($t1)       #   load numbers[count] into $a0
    li $v0, 1
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    sub $t0, $t0,1      #   count--;
    j next              # }
end1:

    jr $31              # return

.data

numbers:
    .space 40           # int numbers[10];

string0:
    .asciiz "Enter a number: "
string1:
    .asciiz "Reverse order:\n"
