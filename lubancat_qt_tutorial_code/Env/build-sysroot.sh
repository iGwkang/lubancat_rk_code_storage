#!/bin/sh

sudo symlinks -rc /usr/lib

sudo mkdir -p ./sysroot
sudo rsync -avz /usr/lib ./sysroot/usr
sudo rsync -avz /usr/include ./sysroot/usr
sudo rsync -avz /lib ./sysroot/

cd ./sysroot/usr/lib
ln -s aarch64-linux-gnu/crt* .

# host
#rsync -avz --rsync-path="sudo rsync" --delete cat@10.0.0.21:~/sysroot .
#find -type l -lname '/*' -exec sh -c 'ln -sf "$(pwd)/sysroot$(readlink "$0")" "$0"' {} \;
