import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;

Serial myPort;
String data = "";

// Variables for roll, pitch, and yaw for two objects
float roll1, pitch1, yaw1;
float roll2, pitch2, yaw2;

void setup() {
  size(2560, 1440, P3D); // Create a 3D canvas
  myPort = new Serial(this, "COM3", 19200); // Start serial communication
  myPort.bufferUntil('\n'); // Read data until newline character
}

void draw() {
  background(233); // Clear the background

  // Render text in 2D space
  camera(); // Reset the camera for text rendering
  textSize(22);
  fill(0);
  text("Object 1 - Roll: " + int(roll1) + " Pitch: " + int(pitch1) + " Yaw: " + int(yaw1), 20, 30);
  text("Object 2 - Roll: " + int(roll2) + " Pitch: " + int(pitch2) + " Yaw: " + int(yaw2), 20, 60);

  // Render the first box in 3D space
  pushMatrix();
  translate(width / 3, height / 2, 0);
  rotateX(radians(-pitch1));
  rotateZ(radians(roll1));
  rotateY(radians(yaw1));
  fill(0, 76, 153);
  box(200, 100, 50); // Draw 3D box for Object 1 with height
  popMatrix();

  // Render the second box in 3D space
  pushMatrix();
  translate(2 * width / 3, height / 2, 0);
  rotateX(radians(-pitch2));
  rotateZ(radians(roll2));
  rotateY(radians(yaw2));
  fill(153, 76, 0);
  box(200, 100, 50); // Draw 3D box for Object 2 with height
  popMatrix();
}

// Read data from the Serial Port
void serialEvent(Serial myPort) {
  // Read the data from the serial port until newline
  data = myPort.readStringUntil('\n');
  
  if (data != null) {
    data = trim(data); // Trim any whitespace
    
    // Split the string by spaces or slashes (adjust based on data format)
    String items[] = split(data, '/');

    if (items.length >= 1) {
      // Parse roll, pitch, and yaw for both objects
      roll1 = float(items[0]);
      pitch1 = float(items[1]);
      yaw1 = float(items[2]);

      roll2 = float(items[3]);
      pitch2 = float(items[4]);
      yaw2 = float(items[5]);
    }
  }
}
