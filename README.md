# Concurrent-Hash-Map
Hash Map with chaining supports concurrent operations.

<b> Run benchmark with </b>  `g++ -std=c++17 -pthread benchmark.cpp` <br>

   Size of HashTable  |  #Threads:1 | #Threads:2 | #Threads:4 | #Threads:8 |
| ------------- | ------------- | ------------- | ------------- | ------------- |
| 10  | Content Cell  |Content Cell  |Content Cell  |Content Cell  |
| 100  | Content Cell  |Content Cell  |Content Cell  |Content Cell  |
| 1000  | Content Cell  |Content Cell  |Content Cell  |Content Cell  |
| 10000  | Content Cell  |Content Cell  |Content Cell  |Content Cell  |
