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

}

void loop()
{
  // Do your program-specific loop() work here as usual.
  Serial.print("Test RDF ");
  // Serial1.print("1234");

  // Make an array to represent stick values.
  uint8_t myPacket[6] = { 3, 7, 22, 33, 44, 55 };

  // Send the array.
  myPacketSerial.send(myPacket, 6);
}
