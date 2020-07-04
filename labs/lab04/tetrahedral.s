# Read a number n and print the first n tetrahedral numbers
# https://en.wikipedia.org/wiki/Tetrahedral_number

main:                       # int main(void) {

    la $a0, prompt          # printf("Enter how many: ");
    li $v0, 4
    syscall

    li $v0, 5               # scanf("%d", number);
    syscall
    
    move $t0, $v0           # move result into temp

    li $t1, 1               # int n = 1;
loop1: 
    bgt $t1, $t0, end       # while (n <= how_many)
    li $t3, 1              # int j = 1;    
    li $t4, 0               # int total = 0; 
loop2:
    bgt $t3, $t1, print     # while (j <= n){
    li $t2, 1               # int i = 1;
    
loop3:
    bgt $t2, $t3, j_increment# while (i <= j){
    add $t4, $t4, $t2       # total = total + i;
    add $t2, $t2, 1        # i = i + 1;
    j loop3       
j_increment:  
    add $t3, $t3, 1        # j = j + 1;
    j loop2
print:
    move $a0, $t4           # printf("%d\n", total);
    li   $v0, 1
    syscall

    li   $a0, '\n'          # printf("%c", '\n');
    li   $v0, 11
    syscall
    add $t1, $t1, 1        # n = n + 1;
        
    j loop1
   
end:
    jr   $ra                # return

    .data
prompt:
    .asciiz "Enter how many: "
