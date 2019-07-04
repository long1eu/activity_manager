sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) main universe"
sudo apt-get update
sudo apt-get install libncurses5-dev libncursesw5-dev
mkdir build
cd build
cmake ..