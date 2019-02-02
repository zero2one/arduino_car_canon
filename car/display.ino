/**
 * Display related code.
 * 
 * Use following methods to update the display values:
 * 
 * - displayDirection(int) : Update the direction (degrees) the car is pointing to.
 * 
 * - displayDistance(int)  : Update the currently measured distance.
 * - displayDistanceX(int) : Update the currently X-distance.
 * - displayDistanceY(int) : Update the currently Y-distance.
 * - displayTargetX(int)   : Update the wanted X-distance.
 * - displayTargetY(int)   : Update the wanted Y-distance. 
 */

// Display configuration.
#define DISPLAY_WIDTH 128 // OLED display width, in pixels
#define DISPLAY_HEIGHT 32 // OLED display height, in pixels
#define DISPLAY_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)

#define DISPLAY_LINE_1 0
#define DISPLAY_LINE_2 14
#define DISPLAY_LINE_3 24

#define DISPLAY_ON 0

// Create the display object.
Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, DISPLAY_RESET);



/**
 * Setup the display.
 * 
 * This will:
 * - Check if we can communicate with the display.
 * - Run the displayInit method.
 */
void displaySetup() {
  if (!DISPLAY_ON) {
    return;
  }
  
  debugStep("Display Setup");
  
  // Check if the display library works
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    debugError("! SSD1306 allocation failed... Check your wiring!");
    debugError("  Script halted.");
    for (;;); // Don't proceed, loop forever.
  }
  
  // Initialise display
  displayInit();
}

/**
 * Init the display with the fixed text parts.
 */
void displayInit() {
  if (!DISPLAY_ON) {
    return;
  }
  
  debugStep("Display Init");

  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text

  // Measured distance.
  display.setCursor(0, DISPLAY_LINE_2);
  display.println("Dist");
  display.setCursor(30, DISPLAY_LINE_2);
  display.println("X");
  display.setCursor(78, DISPLAY_LINE_2);
  display.println("Y");

  // Target.
  display.setCursor(0, DISPLAY_LINE_3);
  display.println("Targ");
  display.setCursor(30, DISPLAY_LINE_3);
  display.println("X");
  display.setCursor(78, DISPLAY_LINE_3);
  display.println("Y");

  // Distance.
  display.setCursor(0, DISPLAY_LINE_1);
  display.println("Dist");

  // Heading
  display.setCursor(66, DISPLAY_LINE_1);
  display.println("Dir");

  display.display();
}

/**
 * Update a value on the given location.
 * 
 * @param int x
 *   The x-position of the value.
 * @param int y
 *   The y-position of the value.
 * @param String value
 *   The value to write to the display.
 */
void displayValue(int x, int y, String value) {
  if (!DISPLAY_ON) {
    return;
  }
  
  // Clear first the existing text.
  display.fillRect(x, y, 30, 7, BLACK); // (x, y, w, h)

  // Print the new text.
  display.setCursor(x, y);
  display.println(value);
  display.display();
}

/**
 * Display the measured distance in cm.
 * 
 * @param int distance
 *   The distance to put on the display.
 */
void displayDistance(int distance) {
  debugValue("Distance", distance);
  displayValue(30, DISPLAY_LINE_1, String(distance));
}

/**
 * Update the current direction in degrees (0-360).
 * 
 * @param int dir
 *   The direction the car is pointing to.
 */
void displayDirection(int direction) {
  //debugValue("Direction", direction);
  String dir = String(direction);
  displayValue(90, DISPLAY_LINE_1, dir);
}

/**
 * Update the X-distance to the screen.
 * 
 * @param int x
 *   The distance in cm.
 */
void displayDistanceX(int x) {
  debugValue("Distance X", x);
  displayValue(42, DISPLAY_LINE_2, String(x));
}

/**
 * Update the Y-distance to the screen.
 * 
 * @param int y
 *   The distance in cm.
 */
void displayDistanceY(int y) {
  debugValue("Distance Y", y);
  displayValue(90, DISPLAY_LINE_2, String(y));
}

/**
 * Display the X-target value.
 * 
 * @param int x
 *   The target X-distance in cm.
  */
void displayTargetX(int x) {
  debugValue("Target X", x);
  displayValue(42, DISPLAY_LINE_3, String(x));
}

/**
 * Display the Y-target value.
 * 
 * @param int y
 *   The target Y-distance in cm.
  */
void displayTargetY(int y) {
  debugValue("Target Y", y);
  displayValue(90, DISPLAY_LINE_3, String(y));
}

/**
 * Test the display by printing out dummy values.
 */
void displayDummy() {
  displayDirection(185);
  
  displayDistance(101);
  displayDistanceX(201);
  displayDistanceY(202);
  displayTargetX(301);
  displayTargetY(302);
}
