//
// Copyright (c) 2012 Christopher Baker <https://christopherbaker.net>
// https://github.com/bakercp/PacketSerial/blob/master/docs/BACKGROUND.md
// SPDX-License-Identifier: MIT
//

// RDF notes - Working this up for use with radio control using a Nano Every which has 2 serial ports

#include <PacketSerial.h>


// By default, PacketSerial automatically wraps the built-in `Serial` object.
// While it is still possible to use the Serial object directly, it is
// recommended that the user let the PacketSerial object manage all serial
// communication. Thus the user should not call Serial.write(), Serial.print(),
// etc. Additionally the user should not use the serialEvent() framework.
//
// By default, PacketSerial uses COBS encoding and has a 256 byte receive
// buffer. This can be adjusted by the user by replacing `PacketSerial` with
// a variation of the `PacketSerial_<COBS, 0, BufferSize>` template found in
// PacketSerial.h.
PacketSerial myPacketSerial;


void setup()
{
  // We begin communication with our PacketSerial object by setting the
  // communication speed in bits / second (baud).
  myPacketSerial.begin(9600);
  Serial.begin(9600);
  Serial1.begin(9600);
  myPacketSerial.setStream(&Serial1); // RDF set for Nano Every
  // If we want to receive packets, we must specify a packet handler function.
  // The packet handler is a custom function with a signature like the
  // onPacketReceived function below.
  myPacketSerial.setPacketHandler(&onPacketReceived);
}


void loop()
{
  // Do your program-specific loop() work here as usual.
  //  Serial.print("Test RDF ");

  // The PacketSerial::update() method attempts to read in any incoming serial
  // data and emits received and decoded packets via the packet handler
  // function specified by the user in the void setup() function.
  //
  // The PacketSerial::update() method should be called once per loop(). Failure
  // to call the PacketSerial::update() frequently enough may result in buffer
  // serial overflows.
  myPacketSerial.update();
  // Serial.print("Test RDF1 ");
  // Check for a receive buffer overflow (optional).
  // if (myPacketSerial.overflow())
  // {
  // Send an alert via a pin (e.g. make an overflow LED) or return a
  // user-defined packet to the sender.
  //
  // Ultimately you may need to just increase your recieve buffer via the
  // template parameters (see the README.md).
  // }
}

// This is our handler callback function.
// When an encoded packet is received and decoded, it will be delivered here.
// The `buffer` is a pointer to the decoded byte array. `size` is the number of
// bytes in the `buffer`.
void onPacketReceived(const uint8_t* buffer, size_t size)
{

  // Print stick outputs
  for (int i = 0; i < 6; i++)   //display all channels
  {
    Serial.print(buffer[i]);
    Serial.print("\t"); //tab
  }

}
