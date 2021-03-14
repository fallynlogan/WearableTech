import processing.serial.*;

Serial myPort;  // Create object from Serial class
String val;      // Data received from the serial port
float t;
float n = 30;
float side;
float radius = 150;
String x_accel;
String y_accel;
String[] values;
int numFrames = 360;
int x_int = 1;
int y_int = 1;
int r; 
int g;
int b;
boolean recording = true;
float noiseRadius = 2;

void setup() 
{
  size(500, 500);
  noFill();
  side = width/n*2;
  String portName = Serial.list()[2];
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  t = map(frameCount-1, 0, numFrames, 0, 1);
  if ( myPort.available() > 0) {  // If data is available,
    val = myPort.readString();       // read it and store it in val
    values = val.split(",");
    if(values.length == 2) {
      x_accel = values[0].trim();
      y_accel = values[1].trim();
      try{
        x_int = Integer.parseInt(x_accel);
        y_int = Integer.parseInt(y_accel);
        radius = 200*(float)(noise((x_int)*side*cos(TWO_PI), (y_int)*side*sin(TWO_PI)));
        //radius = 100*(float)noise(x_int*side*0.01, y_int*side*0.01, noiseRadius*cos(TWO_PI*t), noiseRadius*sin(TWO_PI*t))+100;
        println("radius", radius);
        //change background color based on x pos
        if(x_int <= 50) {
          //green
          background(173,237,34);
        } else if (50 < x_int && x_int<= 100){
          //pink
          background(255,20,147);
        } else if (100 < x_int && x_int<= 200){
          //cyan
          background(51, 255, 226);
        }
        else if (300 < x_int && x_int<= 400){
          //orange
          background(255, 156, 51);
        }
        else if (400 < x_int && x_int<= 500){
          //yellow
          background(255, 254, 51);
        }
        else if (500 < x_int && x_int<= 600){
          //purple
          background(182, 51, 255);
        }
        else if (600 < x_int && x_int<= 700){
          //red
          background(255, 51, 82);
        }
        else if (x_int < 700){
          //red
          background(129, 27, 249);
        }
        
        //change stroke color of circle based on y pos
        if(y_int <= 50) {
          //dark purple
          r = 95;
          g = 7;
          b = 148;
        } else if (50 < y_int && y_int<= 100){
          //dark blue
          r = 25;
          g = 21;
          b = 126;
        } else if (100 < y_int && y_int<= 200){
          //dark orange
          r = 202;
          g = 116;
          b = 0;
        }
        else if (200 < y_int && y_int<= 300){
          //dark pink
          r = 179;
          g = 10;
          b = 120;
        }
        else if (300 < y_int && y_int<= 400){
          //dark red
          r = 217;
          g = 21;
          b = 21;
        }
        else if (400 < y_int && y_int<= 500){
          //dark yellow
          r = 182;
          g = 172;
          b = 31;
        }
        else if (500 < y_int && y_int<= 600){
          //dark cyan
          r = 8;
          g = 147;
          b = 104;
        }
        else if (600 < y_int && y_int<= 700){
          //dark red
          r = 37;
          g = 114;
          b = 72;
        }
      } catch(NumberFormatException ex){ // handle your exception
        x_int = 1;
        y_int = 1;
      }
      println("x: ", x_accel);
      println("y: ", y_accel);
    } //else {
    //  background(0);
    //}
  }

  for(int y=0;y<n;y++) {
    for(int x=0;x<n;x++) {
      stroke(255);
      
       if(dist(x*side, y*side, width/2, height/2) < radius) {
        stroke(r,g,b);
        line(x*side, y*side, (x+1)*side, (y+1)*side);
      } else {
        line((x+1)*side, y*side, x*side, (y+1)*side);
      }
    }
  }
  
  if(recording) {
    saveFrame("###.png");
    
    if(frameCount==numFrames)
      exit();
  }
}
