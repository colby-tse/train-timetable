# train-timetable
A program that finds the next earliest train departure after arrival at a station, written in C. This project was developed as part of a university project.

## Program Structure
### Timetable Data
The train network timetable will be presented in a double colon separated format. The format will specify the source, destination and leaving time from the source station. The source and destination component may contain spaces and will be sub-strings of the line entry. Each entry in the timetable is separated by a new line. Following the `<time>` , a new line character is expected. Each entry will not exceed the maximum number of characters (4096).

The data is formatted in the following form:
```
<source>::<destination>::<time>
```

### Command Line Arguments
The command line arguments are given in the format and order:
```
./timetable <source> <destination> <time>
```
The following is an example of program execution with command line arguments:
```
./timetable Sydney Melbourne "11:59:59" < timetable.list
The next train to Melbourne from Sydney departs at 12:05:40
```
The time format must be supplied in 24-hour format `<hh>:<mm>:<ss>`, where `hh` represents the hour, `mm` represents the minutes and `ss` represents the seconds.

### Testing
The `make test` command will execute the test cases and provide human readable output. The file `testinfo.txt` contains a brief description of each test case.
