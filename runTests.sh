sudo nohup ./batReader.sh &
PROC=$!
sudo ./a.out > PyScripts/Output/testOutput
sudo kill -9 $PROC
sudo kill $(ps aux | grep '[.]/batReader.sh' | awk '{print $2}')
sudo rm nohup.out
curl -X POST https://maker.ifttt.com/trigger/task_complete/with/key/eBm552XQq4pOPLH5ncoBSwDKECuQjM1EujlATzOOUM2