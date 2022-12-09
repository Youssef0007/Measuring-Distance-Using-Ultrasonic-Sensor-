# Measuring Distance Using Ultrasonic Sensor 
 
1. Use ATmega16 Microcontroller with frequency 8Mhz.
2. Measure the distance using the Ultrasonic sensor HC-SR04. Check the “HC-SR04 
Ultrasonic MT Student Tutorial” pdf file to understand how to interface with this 
sensor.
3. The LCD should display the distance value like that:
4. The project should be design and implemented based on the layered architecture 
model as follow:
GPIO Driver Requirements
1. Use the Same GPIO driver implemented in the course.
ICU Driver Requirements
1. Use the Same ICU driver implemented in the course.
2. The ICU should be configured with frequency F_CPU/8 and to detect the raising 
edge as the first edge.
3. ICU_init and ICU_setCallBack functions should be called inside the Ultrasonic_init
function.
LCD Driver Requirements
1. Use 4x16 LCD.
2. Use the Same LCD driver implemented in the course with 8-bits data mode.
3. Connect the LCD control pins and 8-bits data pins as follow:
• RS → PB0
• RW → PB1
• E → PB2
• Data Bus → all PORTA pins.
Ultrasonic Driver Requirements
1. Implement a full ultrasonic Driver using ATmega16 ICU driver.
2. The ultrasonic driver has 4 functions:
a. void Ultrasonic_init(void)
b. void Ultrasonic_Trigger(void)
c. uint16 Ultrasonic_readDistance(void)
d. void Ultrasonic_edgeProcessing(void)
