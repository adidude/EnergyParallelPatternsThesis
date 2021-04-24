import os.path
from os import path
import multiprocessing

numberOfCores = multiprocessing.cpu_count() - 1

fileName = "stiched.txt"
if path.exists(fileName):
    n = open(fileName,"w")
else:
    n = open(fileName,"x")

n.write("Serial Start (ms),Serial End (ms),Serial Duration (ms),Energy at Serial Start (mWh),Energy at Serial End (mWh),Serial Energy Consumed (mWh),Parallel Start (ms),Parallel End (ms),Parallel Duration (ms),Energy at Parallel Start (mWh),Energy at Parallel End (mWh),Parallel Energy Consumed (mWh),Cores,Speedup\n")

speedup = open("untitled")
drain = open("energy")

speedupData = speedup.readlines()
drainData = drain.readlines()
currLine = 1

finalOutput = []
serialEnergyVals = []

locks = [False,False,False,False]
lastEnergyVal = 0

for line in drainData:
    if line == "Time (ms),Energy (mWh),Power (mW)\n":
        continue
    drainLine = line.split(",")
    drainLine[2] = drainLine[2][0:len(drainLine[2])-1]
    if currLine < len(speedupData):
        speedupLine = speedupData[currLine].split(",")
    else:
        break
    speedupLine[7] = speedupLine[7][0:1]
    #if the energy reading at the start is not recorded
    if not locks[0]:
        #Add the serial algo data and the starting energy
        serialEnergyVals.append(drainLine[1])
        finalOutput = [speedupLine[0],speedupLine[1],speedupLine[2],drainLine[1]]
        #lock informing that the first energy value is recorded
        locks[0] = True
    
    if locks[3]:    
        if speedupLine[6] == "1":
            if int(drainLine[0]) < int(speedupLine[0]):
                lastEnergyVal = drainLine[1]
                continue
            else:
                finalOutput.append(speedupLine[0])
                finalOutput.append(speedupLine[1])
                finalOutput.append(speedupLine[2])
                finalOutput.append(lastEnergyVal)
                serialEnergyVals.append(lastEnergyVal)
                locks[3] = False
        else:
            finalOutput.append(speedupLine[0])
            finalOutput.append(speedupLine[1])
            finalOutput.append(speedupLine[2])
            finalOutput.append(serialEnergyVals[0])
            locks[3] = False
            
    
    if not locks[1]:
        # if the currently read time is less than the end of the serial end timestatement
        if int(drainLine[0]) < int(speedupLine[1]):
            lastEnergyVal = drainLine[1]
            continue
        else:
            #Add energy values and lock block
            if speedupLine[6] == "1":
                finalOutput.append(lastEnergyVal)
                serialEnergyVals.append(lastEnergyVal)
            else:
                finalOutput.append(serialEnergyVals[1])
            finalOutput.append(int(finalOutput[3])-int(finalOutput[4]))
            locks[1] = True

    if not locks[2]:
        if int(drainLine[0]) < int(speedupLine[3]):
            lastEnergyVal = drainLine[1]
            continue
        else:
            finalOutput.append(speedupLine[3])
            finalOutput.append(speedupLine[4])
            finalOutput.append(speedupLine[5])
            finalOutput.append(lastEnergyVal)
            locks[2] = True

    if int(drainLine[0]) < int(speedupLine[4]):
        lastEnergyVal = drainLine[1]
        continue
    else:
        finalOutput.append(lastEnergyVal)
        finalOutput.append(int(finalOutput[9]) - int(lastEnergyVal))
        finalOutput.append(speedupLine[6])
        finalOutput.append(speedupLine[7])
        n.write(finalOutput[0] + "," + finalOutput[1] + "," + finalOutput[2] + "," + finalOutput[3] + "," + finalOutput[4] + "," + str(finalOutput[5]) + "," + finalOutput[6] + "," + finalOutput[7] + "," + finalOutput[8] + "," + finalOutput[9] + "," + finalOutput[10] + "," + str(finalOutput[11]) + "," + finalOutput[12] + "," + finalOutput[13] + "\n" )
        currLine = currLine + 1
        finalOutput = []
        if speedupLine[6] == str(numberOfCores):
            serialEnergyVals = []
        locks[3] = True
        locks[1] = False
        locks[2] = False