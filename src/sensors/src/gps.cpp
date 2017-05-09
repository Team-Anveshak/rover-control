#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/MagneticField.h>
#include <rover_msgs/WheelVelocity.h>
#include <cstdlib>
#include <cmath>

#define PI 3.14159
#define R 6371

double lat_init = 12.99178849*PI/180,logg_init = 80.2310192*PI/180, dist_init;
double lat_dest=11.993511*PI/180,logg_dest=80.272439*PI/180;
double lat,logg,dist,brng,brng_cur,decl=-4.88*PI/180;
int service,status;
double theta; 
double x,y;

void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg)
{
	lat = (msg->latitude)*PI/180;
	logg = (msg->longitude)*PI/180;
	//service = msg->status.service;
	//status = msg->status.status;
	
	brng = atan2((sin(logg_dest - logg))*(cos(lat_dest)),(cos(lat))*(sin(lat_dest))-(sin(lat))*(cos(lat_dest)*(cos(logg_dest-logg))));
	
	float a = (sin((lat_dest-lat)/2))*(sin((lat_dest-lat)/2)) + (cos(lat))*(cos(lat_dest))*(sin((logg_dest-logg)/2))*(sin((logg_dest-logg)/2));
	float c = 2 * atan2(sqrt(a),sqrt(1-a));
	dist= R*c;

	//ROS_INFO("%lf\t%lf\t%lf\t%lf\t%f\t%f",lat_dest,logg_dest,lat,logg,brng,dist_init);
}

void ortnCallback(const sensor_msgs::MagneticField::ConstPtr& msg)
{
	x = (msg->magnetic_field.x)*1000000;
	y = (msg->magnetic_field.y)*1000000;
	
	theta = fabs(atan2( y, x ));
	if(y<0)		theta = PI - theta;

	if( decl > 0 ){
		if(y>0 && (theta+decl-PI)<0 )		brng_cur = theta + decl;
		if(y>0 && (theta+decl-PI)>0 )	 brng_cur = theta + decl - 2*PI;
		if(y<0)		brng_cur = theta + decl -PI;	
	}
	else {
		if(y<0 && (theta-fabs(decl))<0 )		brng_cur = theta + PI - decl;
		if(y<0 && (theta-fabs(decl))>0 )	 brng_cur = theta - decl - PI;
		if(y>0)		brng_cur = theta - decl;	
	
	/*ROS_INFO("%lf\t%lf\t",x,y);*/
	}

}

int main(int argc,char **argv)
{
	ros::init(argc,argv,"gps");
	ros::NodeHandle n;

	ros::Subscriber gps_sub = n.subscribe("/phone1/android/fix",100,gpsCallback);
	ros::Subscriber ortn_sub = n.subscribe("/phone1/android/magnetic_field",100,ortnCallback);
	//ros::Publisher vel_pub = n.advertise<rover_msgs::WheelVelocity>("/rover1/wheel_vel",10);
	ros::Rate loop_rate(5);	

	float a = (sin((lat_dest-lat_init)/2))*(sin((lat_dest-lat_init)/2)) + (cos (lat_init))*(cos (lat_dest))*(sin((logg_dest-logg_init)/2))*(sin((logg_dest-logg_init)/2));
	float c = 2 * atan2(sqrt(a),sqrt(1-a));
	dist_init= R*c;

	while(ros::ok()){
	ros::spinOnce();
	//ROS_INFO("%lf\t%lf\t%lf\t%lf",lat_dest,logg_dest,brng,theta);
	//ROS_INFO("%lf\t%lf\t%lf\t%lf",decl,theta,brng,brng_cur);
	ROS_INFO("%lf\t%lf\t",x,y);
	loop_rate.sleep();
	}

/*	while(ros::ok())
	{
	ros::spinOnce();
	rover_msgs::WheelVelocity vel;
	if(fabs(dist_init-dist)>0.002){
		if(fabs(brng-brng_cur)>=30*PI/180 ){
			if (brng-brng_cur<=0){
				vel.left_front_vel = 70;
    	 	   	vel.right_front_vel = -70;
        		vel.left_middle_vel = 70;
        		vel.right_middle_vel = -70;
        		vel.left_back_vel = 70;
        		vel.right_back_vel = -70;	
			}
			else{
				vel.left_front_vel = -70;
        		vel.right_front_vel = 70;
        		vel.left_middle_vel = -70;
        		vel.right_middle_vel = 70;
        		vel.left_back_vel = -70;
        		vel.right_back_vel = 70;
			}
		
		}
		else if(fabs(brng-brng_cur)<=30*PI/180 && fabs(brng-brng_cur)>15*PI/180){
			
			if (brng-brng_cur<=0){

			vel.left_front_vel = 50;
    	 	   	vel.right_front_vel = -50;
        		vel.left_middle_vel = 50;
        		vel.right_middle_vel = -50;
        		vel.left_back_vel = 50;
        		vel.right_back_vel = -50;	

			}
			else{
				vel.left_front_vel = -50;
        		vel.right_front_vel = 50;
        		vel.left_middle_vel = -50;
        		vel.right_middle_vel = 50;
        		vel.left_back_vel = -50;
        		vel.right_back_vel = 50;
			}

		}
		else{
			vel.left_front_vel = 70;
    	 	vel.right_front_vel = 70;
        	vel.left_middle_vel = 70;
        	vel.right_middle_vel = 70;
        	vel.left_back_vel = 70;
        	vel.right_back_vel = 70;
			}	
			


	}
	else{
		vel.left_front_vel = 0;
        vel.right_front_vel = 0;
        vel.left_middle_vel = 0;
        vel.right_middle_vel = 0;
        vel.left_back_vel = 0;
        vel.right_back_vel = 0;
	}
	vel_pub.publish(vel);
	loop_rate.sleep();
	
}
*/	ros::spin();
	return 0 ;
}
