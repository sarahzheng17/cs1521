# Read a number and print positive multiples of 7 or 11 < n

main:                    # int main(void) {

    la $a0, prompt       # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5            # scanf("%d", number);
    syscall
    
    move $t1, $v0       # Moved result into temp
    
    li $t0, 1            # int i = 0;

loop: 
    bge $t0, $t1, end    # while (i < number){
    
    rem $t2, $t0, 7      # if(i % 7 == 0){
    rem $t3, $t0, 11     # if(i % 11 == 0){
    
    beqz $t2, print      # branch to print                   
    beqz $t3, print     
    
after_if:
    
    addi $t0, $t0, 1     # i = i + 1;
    
    j loop 
    
print: 
    move $a0, $t0        # printf("%d", i);
    li $v0, 1
    syscall
    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall
    
    j after_if           # jump back to loop
    
end:
    jr   $ra             # return

    .data
prompt:
    .asciiz "Enter a number: "
