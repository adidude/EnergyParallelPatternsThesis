#PowerTop dependancies
#sudo apt install -y libpci-dev libnl-3-dev libnl-genl-3-dev gettext \
#libgettextpo-dev autopoint gettext libncurses5-dev libncursesw5-dev libtool-bin \
#dh-autoreconf autoconf-archive pkg-config

#mkdir ~/Utility/powertop
cd ~/Utility
#wget https://github.com/fenrus75/powertop/archive/v2.13.zip
#unzip v2.13.zip
cd ./powertop-2.13

#Gettext powertop dependancy
#wget https://ftp.gnu.org/gnu/gettext/gettext-0.21.tar.gz
#tar xvzf gettext-0.21.tar.gz
#cd ./gettext-0.21
#sudo ./autogen.sh
#sudo ./configure --prefix=/usr    \
#            --disable-static \
#            --docdir=/usr/share/doc/gettext-0.20.1
#make
#make install
#sudo chmod -v 0755 /usr/lib/preloadable_libintl.so
#cd ..
#sudo rm gettext-0.21.tar.gz

#POWERTOP MAIN
#sudo ~/Utility/powertop/autogen.sh
#sudo ~/Utility/powertop/configure
#make
#mkdir powertopMain
#sudo ./install-sh