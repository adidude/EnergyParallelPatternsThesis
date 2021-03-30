#dependencies and powertop
sudo apt -y install snapd gdb git cmake powertop
#visual studio code
sudo snap install code --classic
#pip
sudo apt install -y python-pip
#s-tui
sudo apt install s-tui

#Fastflow
if [ ! -d "/home/adi/Utility" ]; then
    sudo mkdir /home/adi/Utility
    sudo mkdir /home/adi/Utility/fastflow
    git clone https://github.com/fastflow/fastflow.git /home/adi/Utility/fastflow
elif [ ! -d "/home/adi/Utility/fastflow" ]; then 
    sudo mkdir /home/adi/Utility/fastflow
    git clone https://github.com/fastflow/fastflow.git /home/adi/Utility/fastflow
fi

export FF_ROOT=/home/adi/Utility/fastflow
sudo echo "export FF_ROOT=/home/adi/Utility/fastflow" >> ~/.bashrc

if [ ! -d "/home/adi/Utility/fastflow/build" ]; then
    sudo mkdir /home/adi/Utility/fastflow/build
fi
cd $FF_ROOT/build
cmake /home/adi/Utility/fastflow
make
make test
sudo make install DESTDIR=/
sudo cp -r /home/adi/Utility/fastflow/ff /usr/local/include

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
