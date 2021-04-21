#Reads the battery's energy level,power and time since start and outputs data to file
filePath="PyScripts/Output/energyDrain.txt"
timerDuration=600
calcDuration=0
#Print Legend
echo "Time (ms),Energy (mWh),Power (mW)" > $filePath
start=$(date +%s%N)
#infinite run or run for certain number of seconds
while true;do
#while [ $((calcDuration / 1000)) -lt $timerDuration ];do
    #calculate duration since start
    calcDuration=$((($(date +%s%N) - $start)/1000000))
    concat=$(cat /sys/class/power_supply/BAT0/energy_now)
    concat=$((concat / 1000))
    power=$(cat /sys/class/power_supply/BAT0/power_now)
    power=$((power / 1000))
    concat="${calcDuration},${concat},${power}"
    echo $concat >> $filePath
    sleep 1
done;