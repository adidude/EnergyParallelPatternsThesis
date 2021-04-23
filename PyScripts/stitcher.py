import os.path
from os import path
fileName = "PyScripts/Output/stiched.txt"
if path.exists(fileName):
    n = open(fileName,"w")
else:
    n = open(fileName,"x")

n.write("Serial Start (ms),Serial End (ms),Serial Duration (ms),Energy at Serial Start (mWh),Energy at Serial End (mWh),Serial Energy Consumed (mWh),Parallel Start (ms),Parallel End (ms),Parallel Duration (ms),Energy at Serial Start (mWh),Energy at Serial End (mWh),Parallel Energy Consumed (mWh),Cores,Speedup")

speedup = open("PyScripts/Output/matrixSpeedup.txt")
drain = open("PyScripts/Output/matrixMultEnerDrain.txt")

speedupData = speedup.readlines()
drainData = drain.readlines()
currLine = 1

finalOutput = []

locks = [False,False]
lastEnergyVal = 0

for line in drainData:
    if line == "Time (ms),Energy (mWh),Power (mW)\n":
        continue
    drainLine = line.split(",")
    drainLine[2] = drainLine[2][0:len(drainLine[2])-1]
    speedupLine = speedupData[currLine].split(",")
    speedupLine[7] = speedupLine[7][0:1]
    #if the energy reading at the start is not recorded
    if not locks[0]:
        #Add the serial algo data and the starting energy
        finalOutput = [speedupLine[0],speedupLine[1],speedupLine[2],drainLine[1]]
        #lock informing that the first energy value is recorded
        locks[0] = True
    
    
    if not locks[1]:    
        # if the currently read time is less than the end of the serial end timestatement
        if drainLine[0] < speedupLine[1]:
            lastEnergyVal = drainLine[1]
            continue
        else:
            #Add energy values and lock block
            finalOutput.append(lastEnergyVal)
            finalOutput.append(finalOutput[3]-lastEnergyVal)
            locks[1] = True

    if locks[0] and locks[1]:
        if drainLine[0] < speedupLine[3]:
            lastEnergyVal = drainLine[1]
            continue
        else:
            finalOutput.append(lastEnergyVal)
            finalOutput.append(finalOutput[3]-lastEnergyVal)
            locks[1] = True

    

