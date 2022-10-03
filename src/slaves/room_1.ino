int sensor1[] = {4, 5};
int sensor2[] = {6, 7};

int sensor1Initial = 0;
int sensor2Initial = 0;

bool hist_sensor1[5];
bool hist_sensor2[5];
int hist_counter;

int prev_des = 0; // previous decision 0 if entry or leave or initial (not to be considerd) || hold + out 1 || hold + in 2 || hold+ hold 3 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400); // Default communication rate of the Bluetooth module
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor1Val = 0;
  int sensor2Val = 0;
  bool sensor_1_det = false;
  bool sensor_2_det = false;
  bool entry =false;
  bool leave = false;
  bool hold =false;
  
  sensor1Val = measureDistance(sensor1);
  sensor2Val = measureDistance(sensor2);
  if (sensor1Initial == 0 && sensor2Initial == 0){
    sensor1Initial = sensor1Val;
    sensor2Initial = sensor2Val;
    Serial.println("sensor 1");
    Serial.println(sensor1Initial);
    Serial.println("sensor 2");
    Serial.println(sensor2Initial);
  }else{
    if(sensor1Val < sensor1Initial - 60){
      sensor_1_det = true;
      Serial.println("Sensor 1 Detected !!");
      
    }else{
      sensor_1_det = false;
      
    }
    if(sensor2Val < sensor2Initial - 60){
      sensor_2_det = true;
      Serial.println("Sensor 2 Detected !!");
            
    }else{
      sensor_2_det = false;
    }
    if (hist_counter < 5 && (sensor_1_det == true || sensor_2_det == true || hist_sensor1[0] == true || hist_sensor2[0] == true )){
      hist_sensor1[hist_counter] = sensor_1_det;
      hist_sensor2[hist_counter++] = sensor_2_det;
    }else{
      hist_counter = 0;
      int last_true_1 = -1;
      int last_true_2 = -1; //Check where lost true in historical arrays the highest + not equal 5 determines leave or entry if last true is at 5 then decision is hold plus direction 
    }
  }
  
  

  
}
  //Returns the distance of the ultrasonic sensor that is passed in
  //a[0] = echo, a[1] = trig
  int measureDistance(int a[]) {
  pinMode(a[1], OUTPUT);
  digitalWrite(a[1], LOW);
  delayMicroseconds(2);
  digitalWrite(a[1], HIGH);
  delayMicroseconds(10);
  digitalWrite(a[1], LOW);
  pinMode(a[0], INPUT);
  long duration = pulseIn(a[0], HIGH, 100000);
  return duration / 29 / 2;
}
