import random
import os.path
from os import path
#sets the number of lines to generate.
linesToGen = 1000
count = 0
if path.exists("matrixDataset"):
    file = open("Output/matrixDataset","w")
else:
    file = open("Output/matrixDataset","x")
while count < linesToGen:
    #Can comment out to generate matrices of varying lenght between 1-10 or set custom dimensions 
    sentence = ""
    matrixDimensions = []
    #first 3 values determine the dimensions of both matrices to be multiplied.
    sentence = "400,400,400,"
    matrixDimensions = [400,400,400]
    
    count2 = 0
    #Determines matrix dimensions if they were not specified.
    if len(matrixDimensions) == 0:
        while count2 < 3:
            randint = random.randint(1,10)
            matrixDimensions.append(randint)
            sentence += str(randint) + ","
            count2 += 1
    count3 = 0
    #Generating the matrix values
    #Y
    while count3 < matrixDimensions[0]:
        count4 = 0
        #X
        while count4 < matrixDimensions[1]:
            sentence += str(random.randint(1,100)) + ","
            count4 += 1
        count3 += 1
    count3 = 0
    #Y
    while count3 < matrixDimensions[1]:
        count4 = 0
        #X
        while count4 < matrixDimensions[2]:
            if count3 == matrixDimensions[1]-1 and count4 == matrixDimensions[2]-1:
                sentence += str(random.randint(1,100))
            else:
                sentence += str(random.randint(1,100)) + ","
            count4 += 1
        count3 += 1
    #TEST to see if the number of values in the file comply with valid matrix multiplication sizes
    noOfNumbers = matrixDimensions[0] * matrixDimensions[1] + matrixDimensions[1] * matrixDimensions[2] + 3
    values = sentence.split(",")
    #if test pass write line
    if len(values) == noOfNumbers:
        sentence += "\n"
        file.write(sentence)
    count += 1
file.close()