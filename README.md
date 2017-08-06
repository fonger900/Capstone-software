# Capstone-software
program that create DoS detection rules for Snort

## About
This program detects DoS attack from inspecting Bro IDS's logs, then generates DoS detection rule for Snort.

## Prequisites
* Python 2.7
  * sklearn library
* GNU/Make
* GNU/gcc
* libconfig library
* Bro IDS

## Configuration
Program use libconfig library run configuration file.
Specify two variables in src/getdosrule.cfg to point to Snort's rule directory and Bro's log directory.

## Compile & run
```sh
$ make
$ ./getdosrule
```
