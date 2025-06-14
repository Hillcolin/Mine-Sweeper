
This is how to run it (specifically on the cs3307 gaul):

1. start the xming server
2. open terminal or whatever you are running it on
3. set DISPLAY=localhost:0.0 (you may not have to do this but I had to)
4. ssh -X chill232@cs3307.gaul.csd.uwo.ca ssh in using the -X prefix, to use the Xming server
5. cd over to the assignment
6. qmake6 mineSweeper.pro
7. make
8. ./mineSweeper


NOTE:
If you are not running it on the cs3307 gaul, I was able to get away with not using Xming when running it locally
just had to ssh in, qmake, make, ./mineSweeper

![alt text][logo]
[logo]: MineSweeper.png
