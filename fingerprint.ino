void fingerprintSensor() {
  if (finger.verifyPassword()) {
      println("Found fingerprint sensor!");
    } else {
      println("Did not find fingerprint sensor :(");
      while (1) { delay(1); }
  }
}

void detectFingerPrint() {  
  // check if fingerprint is found.
  while (!Serial);
  delay(100);
  println("\n\nAdafruit finger detect test");
}


int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  return finger.fingerID; 
}
