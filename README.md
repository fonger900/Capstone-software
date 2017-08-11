# Capstone-software
Applying Machine Learning to create DoS detection rules for [Snort](https://www.snort.org/).

![louis](http://www2.siit.tu.ac.th/crd/wp-content/uploads/2014/04/LogoFUNew.png)

## About
This software is a part of capstone project of Information Assurance department of FPT University.

### How it work.
This program applies Machine Learning's algorithm to detects DoS attack in [Bro IDS](https://www.bro.org/)'s logs. Then generates DoS detection rule for Snort.
1. Get logs from Bro's log directory, preprocessing logs to the form of KDDCup99 dataset format.
2. Fetch logs to ML's model to label connections to 'attack' or 'normal'.
3. Generates a `threshold` by calculating average of 'count' attribute's values with 'normal' label.
4. Generates rule in Sort's .rules file format. Rule format: 
```sh
alert tcp any any -> $(HOME_NET) any (msg:"TCP SYN flood attack detected"; flags:S; threshold: type threshold, track by_dst, count 0 , seconds 2; sid: 5000001; rev:1;)
```
5. Store new rule in directory pointed by `rule_dir` variable in `getdosrule.cfg`
## Installation

### Prequisites
* Python 2.7
  * [scikit-learn](http://scikit-learn.org/stable/index.html) library
* GNU/Make
* GNU/gcc
* libconfig
* Bro IDS

### Configuration
Program use [libconfig](https://github.com/hyperrealm/libconfig) library to parse and run configuration file.
Modify two variables in `src/getdosrule.cfg` to point to Snort's rule directory and Bro's log directory.
```sh
# getdosrule.cfg

log_dir  = "/Bro/log/dir/"
rule_dir = "/Snort/rule/dir/"
```

### Compile & Run
```sh
$ make
$ ./getdosrule
```
### Clean
```sh
$ make clean
```

