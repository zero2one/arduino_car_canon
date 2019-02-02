/**
  Debugging related functionality.

  Available functions:

  - debugStep(String) : Print a step title prefixed by "> ".
  - debugText(String) : Print text prefixed by "  ".
  - debugValue(String, mixed) : Print any value prefixed by given text.
  - debugError(String) : Print out an error, prefixed with "[ERROR] ".
*/

#define DEBUG_ENABLED 1
#define DEBUG_VALUE_TYPE 0

/**
   Print an error.
*/
void debugError(String text) {
  Serial.println("");
  Serial.print("[ERROR] ");
  Serial.println(text);
  Serial.println("");
}

/**
  Print a simple text value.

  @param String text
    The text to print.
*/
void debugText(String text) {
  if (DEBUG_ENABLED) {
    Serial.print("  ");
    Serial.println(text);
  }
}

/**
  Print a simple step title.

  @param String text
    The text to print.
*/
void debugStep(String text) {
  if (DEBUG_ENABLED) {
    Serial.print("> ");
    Serial.println(text);
  }
}

/**
  Debug a string value.

  @param String text
    The value name.
  @param String value
    The value to print.
*/
void debugValue(String text, String value) {
  if (DEBUG_ENABLED) {
    debugValuePrefix(text);
    Serial.print(value);
    debugValueType("String");
  }
}

/**
  Debug an integer value.

  @param String text
    The value name.
  @param int value
    The value to print.
*/
void debugValue(String text, int value) {
  if (DEBUG_ENABLED) {
    debugValuePrefix(text);
    Serial.print(value);
    debugValueType("int");
  }
}

/**
  Debug a float value.

  @param String text
    The value name.
  @param float value
    The value to print.
*/
void debugValue(String text, float value) {
  if (DEBUG_ENABLED) {
    debugValuePrefix(text);
    Serial.print(value);
    debugValueType("float");
  }
}

/**
  Debug a double value.

  @param String text
    The value name.
  @param double value
    The value to print.
*/
void debugValue(String text, double value) {
  if (DEBUG_ENABLED) {
    debugValuePrefix(text);
    Serial.print(value);
    debugValueType("double");
  }
}

/**
  Debug a boolean value.

  @param String text
    The value name.
  @param double value
    The value to print.
*/
void debugValue(String text, bool value) {
  if (DEBUG_ENABLED) {
    debugValuePrefix(text);
    Serial.print(value);
    debugValueType("boolean");
  }
}

/**
  Print value prefix.

  @param String text
    The text to print.
*/
void debugValuePrefix(String text) {
  Serial.print("  $ ");
  Serial.print(text);
  Serial.print(" : ");
}

/**
  Print value type suffix.

  @param String type
    The value type.
*/
void debugValueType(String type) {
  if (DEBUG_VALUE_TYPE) {
    Serial.print(" (");
    Serial.print(type);
    Serial.print(")");  
  }
  Serial.println();
}
