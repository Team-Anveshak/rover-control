#export ROS_MASTER_URI=http://aniket-HP-Pavilion-Notebook:11311
#export ROS_MASTER_URI=http://akshitk:11311
#export ROS_MASTER_URI=http://niyas-Satellite-L50-B:11311
sudo chmod a+rw /dev/ttyACM0
sudo chmod a+rw /dev/ttyACM1
roslaunch main_control rover_erdt.launch