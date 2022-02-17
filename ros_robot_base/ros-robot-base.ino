#include <ros.h>
#include <Sabertooth.h>
#include <geometry_msgs/Twist.h>
#include <SoftwareSerial.h>
#define USE_USBCON

SoftwareSerial STSerial(NOT_A_PIN,11);
Sabertooth ST(128, STSerial);

ros::NodeHandle  nh;

void moveRobot(const float x, const float z) {
  ST.drive(x);
  ST.turn(z);
  digitalWrite(LED_BUILTIN, LOW);
}

void cmd_vel_cb(const geometry_msgs::Twist & msg) {
  const float x = msg.linear.x;
  const float z_rotation = msg.angular.z;
  moveRobot(x,z_rotation);

}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", cmd_vel_cb);

void setup() {
  STSerial.begin(57600); // 9600 is the default baud rate for Sabertooth packet serial.
  //ST.autobaud();        
  ST.drive(0); // The Sabertooth won't act on mixed mode packet serial commands until
  ST.turn(0);
  nh.initNode();
  nh.subscribe(sub);
 }

int currentTime = millis();

void loop() {
if (millis() - currentTime > 500) {  
nh.spinOnce();
currentTime = millis();
}
}
