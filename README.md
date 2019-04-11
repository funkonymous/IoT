# IoT
Code-Sharing



+-------------------- Read Kit --------------------------------------------------------+

 * getData.py <- diavazei times apo to IoT kit. Sthn grammh 
   18 grafeis thn address tou kit

 * sudo python getData.py  (apo ubuntu)

 * Oti diavazei to grafei sto data.txt, grammh 44 orizeis to arxeio
 
 +-------------------------------------------------------------------------------------+
 
 +------------------- Parser ----------------------------------------------------------+
 
  * Ta arxeia main.cpp / logparsing.h / logparsing.cpp kanoun to parsing. Sthn main
    dialegeis ti arxeia diavazeis kai grafeis (f1, f2) kai thn usterhsh.
    
  * Gia na kaneis build ena binary
  
    gcc main.cpp logparsing.cpp -o MainLoop -std=c++11 -lstdc++
    
    mporei kapoia flags na mhn xreiazontai!
    
  * ./MainLoop trexei to binary
  
+---------------------------------------------------------------------------------------+

+------------------- Upload sthn Amazon ------------------------------------------------+

 * To connect_and_publish.py anevazei ston server ths amazon

+---------------------------------------------------------------------------------------+

Genika h seira ekteleshs gia na mhn varane polla exceptions einai

1) build thn C++
2) getData.py
3) MainLoop
4) connect_and_publish.py

Ta 2 - 4 trexoun parallhla se ksexwristo terminal
