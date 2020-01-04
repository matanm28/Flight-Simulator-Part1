# Flight Gear Interpreter

"Flight-Gear: Interpreter"- First Mile-Stone main achievements:

    1) Establishing a TCP/IP connection with the simulator.
  
    2) Writing commands for the plane flight.

## Extra Details
This is a UAV control code interpreter.
Our plane is flying in the virtual space of FlightGear instructed by a pre-written code that is lexed and parsed using our interpreter.
Our interpreter works in two directions:  
1. Receives data from _FlightGear_ as a **server** and uses said data while flying the plane.
2. Sends data as a **client** to _FlightGear_ to correctly maneuver the plane according to the commands listed in _fly.txt_.
3. More on the syntax for the interpreted language later.
  
## Installation
  1.	We use the “Flight-Gear” installation ( Flight-Gear site- https://www.flightgear.org/download/).
  2.	The incitement is - Linux.
  3.	TCP protocol- “Generic Small.xml” is needed (you need to add it to /data/Protocol directory), this file is provided inside this repository.
  4.	Lastly, you will need the define the connection inside of FlightGear setting before flying:
  5.	specification of TCP/IP and other protocols is needed. Here is what you need to fill:

    --telnet=socket,in,10,127.0.0.1,5402,tcp
        
    --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
        
And this is where:

![](flight-gear%20menu.png)

## Compiling
You should compile this program using the added makefile in this repository with the following command:
> make all

Alternatively, you can download source.txt from this repository and use the following command:
> make compile

## Running
The interpreter receives a single argument which is the path of a text file containing the code you'll want to run.
Notice that if the text file resides in the same folder as _a.out_ you only need to add its name.

After compiling you can run the interpreter with our provided _makefile_ using the following commands:
1. To run the provided _fly.txt_ file use:
>make run
2. To run the provided _fly_with_func.txt_ file use: 
>make runFunc

## Syntax
The syntax is quite intuitive with some restrictions:
1. Conditions can only contain a single boolean expression.
2. Conditions cannot be used within the while loop.

