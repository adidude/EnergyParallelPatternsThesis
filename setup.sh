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

#pip
#sudo apt install -y python-pip &
#sudo apt -y install snapd
echo "~pip~"
sudo pacman --noconfirm -S python-pip
#echo "~snapd~"
#sudo pacman --noconfirm -S snapd
wait
#visual studio code
echo "~visual studio code~"
#sudo snap install code --classic &
sudo pacman --noconfirm -S code
#s-tui
echo "~s-tui~"
sudo pip install s-tui &

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

#Wait for background jobs to finish
wait
#~~~~~~IntelTBB - now Intel OneAPI Thread Building Blocks ~WIP~~~~~~
#sudo apt-get install -y gpg-agent
#wget -qO - https://repositories.intel.com/graphics/intel-graphics.key | sudo apt-key add -
#sudo apt-add-repository \ 'deb [arch=amd64] https://repositories.intel.com/graphics/ubuntu bionic main'

#sudo apt-get update
#sudo apt-get install \
#  intel-opencl \
#  intel-level-zero-gpu level-zero

#sudo apt-get install \
#  intel-igc-opencl-devel \
#  level-zero-devel

#stat -c "%G" /dev/dri/render*
#groups ${USER}

#cd /tmp
#wget https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB
#sudo apt-key add GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB
#rm GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB

#sudo apt -y install intel-basekit
