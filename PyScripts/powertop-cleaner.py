import os.path
from os import path
fileName = "Output/cleanpower.txt"
if path.exists(fileName):
    n = open(fileName,"w")
else:
    n = open(fileName,"x")

f = open("../powertop.csv")

lines = f.readlines()
watts = 0.0
count = 0
end = False
for line in lines:
    if count > 155 and count < 264:
        arr = line.split(";")

        if not end and len(arr) > 1 and " a.out" in arr[6]:
            n.write(arr[5] + "," + arr[6] + "," + arr[7])
            val = arr[7].split()
            if "u" in arr[7]:
                watts = watts + float(val[0]) * 0.000001
            else:
                watts = watts + float(val[0]) * 0.001

        if arr[0] == "\n":
            end = True
        elif end:
            n.write(arr[0] + "\n")
    elif count > 264:
        n.write("Total discharge for a.out in Watts: " + str(watts) + " W\nTotal discharge for a.out in milli-Watts: " + str(watts*1000) + " mW")
        break
    count = count + 1