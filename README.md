To build and run application:
   In the /cpuzzle/src directory, run 'make all' to compile. Executable outfile rk
   will be created after compilation and can be ran using ./rk ~/path/to/input.txt.
   If no input file path argument is provided, a default one is generated. 

   Satisfied requirements 1-6

                              Understood Requirements                             
                                                                                  
  - C Puzzle Description provided by ICS:                                         
 Write a computer program in C to run on a Linux computer using the GNU compiler. 
 A comma delimited file has two columns: timeA and timeB. Both columns are times  
 in hh:mm [a|p] or ISO YYYY-MM-DD hh24:mm format. Times can be in either format,  
 but for any given row the times will be in the same format. Write a program to   
 read the file:                                                                   
   1. For each line report the time that is earlier.                           
      Assume the same day for each line and time zone.                         
   2. The records should be displayed in the order they are in the file        
   3. After the initial print, print for each row, all the times that are later
     without reading the file again.                                          
   4. The records should be displayed in reverse order of the file order         
   5. The program should include linked lists                                    
   6. Include necessary instructions to build your program.                      


C Puzzle "record keeper" written by Diego Arriaga intended as part of the ICS
interview process only.
