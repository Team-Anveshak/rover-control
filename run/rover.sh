#ssh Anveshak@192.168.1.100
#ssh vaibhav@10.21.66.68
ssh ganga@10.21.65.155
#export ROS_MASTER_URI=http://aniket-HP-Pavilion-Notebook:11311
export ROS_MASTER_URI=http://Capt-Rammer:11311
sudo su
sudo chmod a+rw /dev/ttyACM0
sudo chmod a+rw /dev/ttyACM1
roslaunch main_control rover.launch
