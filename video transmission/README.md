+ PREREQUISITES:

sudo add-apt-repository ppa:mc3man/trusty-media
sudo apt-get update
sudo apt-get dist-upgrade
sudo apt-get install ffmpeg

sudo apt-get install build-essential autoconf libjpeg-dev libavformat-dev libavcodec-dev libswscale-dev  subversion git

sudo install libv4l-devel

+ link for motion-3.2.12.tar.gz
https://sourceforge.net/projects/motion/files/motion%20-%203.2/3.2.12/

+ UNPACKING AND INSTALLATION:(provide path to the downloaded motion .tar file)

tar -xvzf /path/to/motion-3.2.12.tar.gz 
cd motion-3.2.12/

+ INCLUDE in track.h -- <code>#include</usr/include/linux/videodev.h></code>
+ INCLUDE in track.c -- <code>#include<linux/videodev2.h></code>
<code>
sudo ln -s /usr/include/libv4l1-videodev.h /usr/include/linux/videodev.h 
./configure
sudo make
sudo make install
sudo mkdir /var/run/motion
sudo chmod a+rwxt /var/run/motion
</code> 
+ REPLACE /usr/local/etc/motion-dist.conf with motion.conf file in the .tar file attached also copy all thread.conf files in that folder.  
+ RENAME motion-dist.conf to motion.conf

sudo mv /usr/local/etc/motion-dist.conf /usr/local/etc/motion.conf

+ to start daemon

sudo motion

now you can configure the motion library by editing motion.conf (common edits - change the device name from /dev/video0 to /dev/video0 for usb cameras for webcam it's default 0)
