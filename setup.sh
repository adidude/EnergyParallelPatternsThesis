#dependencies
#sudo apt -y install gdb &
#sudo apt -y install git &
#sudo apt -y install cmake &
echo "~gdb~"
sudo pacman --noconfirm -S gdb
echo "~gcc~"
sudo pacman --noconfirm -S gcc
echo "~cmake~"
sudo pacman --noconfirm -S cmake
echo "~make~"
sudo pacman --noconfirm -S make

#Fastflow
echo "~FastFlow~"
if [ ! -d "/home/$USER/Utility" ]; then
    sudo mkdir /home/$USER/Utility
    sudo mkdir /home/$USER/Utility/fastflow
    sudo git clone https://github.com/fastflow/fastflow.git /home/$USER/Utility/fastflow
elif [ ! -d "/home/$USER/Utility/fastflow" ]; then 
    sudo mkdir /home/$USER/Utility/fastflow
    sudo git clone https://github.com/fastflow/fastflow.git /home/$USER/Utility/fastflow
fi

export FF_ROOT=/home/$USER/Utility/fastflow
sudo echo "export FF_ROOT=/home/$USER/Utility/fastflow" >> ~/.bashrc

if [ ! -d "/home/$USER/Utility/fastflow/build" ]; then
    sudo mkdir /home/$USER/Utility/fastflow/build
fi
cd $FF_ROOT/build
sudo cmake /home/$USER/Utility/fastflow
sudo make
sudo make test
sudo make install DESTDIR=/
sudo cp -r /home/$USER/Utility/fastflow/ff /usr/local/include
