import random
linesToGen = 25
#first 3 values determine the dimensions of both matrices to be multiplied.
count = 0
file = open("matrixDataset","x")
while count < linesToGen:
    sentence = ""
    count2 = 0
    matrixDimensions = []
    while count2 < 3:
        randint = random.randint(1,10)
        matrixDimensions.append(randint)
        sentence += str(randint) + ","
        count2 += 1
    count3 = 0
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
    #TEST
    noOfNumbers = matrixDimensions[0] * matrixDimensions[1] + matrixDimensions[1] * matrixDimensions[2] + 3
    values = sentence.split(",")
    #if test pass write line
    if len(values) == noOfNumbers:
        sentence += "\n"
        file.write(sentence)
    count += 1
file.close()