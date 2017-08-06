![louis](http://paoru.fr/wp-content/uploads/2011/11/images.jpg)

# Capstone-software
Applying Machine Learning to create DoS detection rules for Snort.

## About
This software is a part of capstone project of Information Assurance department of FPT University.

### How it work.
This program applys Machine Learning's algorithm to detects DoS attack in Bro IDS's logs. Then generates DoS detection rule for Snort.
1. Get logs from Bro's log directory, preprocessing logs to the form of KDDCup99 dataset format.
2. Fetch logs to ML's model to label connections to 'attack' or 'normal'.
3. Generates a 'threshold' by calculating average of 'count' attribute's values with 'normal' label.
4. Generates rule in format: 
```sh
alert tcp any any -> $(HOME_NET) any (msg:"TCP SYN flood attack detected"; flags:S; threshold: type threshold, track by_dst, count 0 , seconds 2; sid: 5000001; rev:1;)
```

## Prequisites
* Python 2.7
  * sklearn library
* GNU/Make
* GNU/gcc
* libconfig library
* Bro IDS

## Configuration
Program use [libconfig](https://github.com/hyperrealm/libconfig) library to parse and run configuration file.
Modify two variables in src/getdosrule.cfg to point to Snort's rule directory and Bro's log directory.
```sh
log_dir  = "/Bro/log/dir/"
rule_dir = "/Snort/rule/dir/"
```

## Compile & run
```sh
$ make
$ ./getdosrule
```
