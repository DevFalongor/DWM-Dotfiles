echo "Installing git, wget, kitty, dmenu, unzip"
sudo pacman -Sy git wget kitty dmenu unzip

unzip dwm.zip
cd dwm
sudo make clean install
