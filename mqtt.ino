void callback(char* topic, byte* payload, unsigned int length) {
  print("Message arrived [");
  print(topic);
  print("] ");
  for (int i=0;i<length;i++) {
    print((char)payload[i]);
  }
  println();
}

void reconnect() {
  while(!client.connected()) {
    if (client.connect("arduinoClient")) {
      println("Connected to mqtt brocker!");
    } else {
      println("Client not connected!");
      print("[ State ]: "); println(client.state());
    }
    delay(5000);
  }
}
