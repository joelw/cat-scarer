# cat-scarer
Keep cat off kitchen bench

A simple Arduino program that attempts to keep cats off a kitchen bench by blasting them with compressed air.
Inspired by Ssscat, but with 100 psi and virtually free refills.

Requires:

- Air compressor (with tank)
- Solenoid valve
- Random air fittings
- Relay
- PIR sensors
- Microview

The aim is to attempt to detect and track the cat's movement using multiple PIR sensors and a servo to
direct the air nozzle, but this may not be necessary because the cat gets out of there pretty damn fast.

To do:

- Decide if motion tracking is worthwhile. Either remove or buy a much bigger servo
- Make the Microview stuff optional. Once I'm happy with the way it's working, use a cheapy Arduino clone
- Support for tweeting about it via an ESP8266


Licence: MIT
