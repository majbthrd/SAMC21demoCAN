CAN and CAN-FD demonstration code for SAMC21-XPRO (Atmel SAMC21)
================================================================

Existing example CAN code for the Atmel SAMC21 was limited to the [AT6493 app note](http://www.atmel.com/Images/Atmel-42464-SAMC21-CAN-BUS-Firmware_ApplicationNote_AT6493.pdf).

In the author's opinion, said app note isn't particularly helpful (and is based on the infernal Atmel Software Framework (ASF) to boot).

What is bemusing is that Atmel has some excellent open-source CAN demonstration code in its [Atmel SAMA5 Software Package](https://github.com/atmelcorp/atmel-software-package).

Although that code was written for the SAMA5D2, the same [Bosch M_CAN](http://www.bosch-semiconductors.de/en/automotive_electronics/ip_modules/can_ip_modules/in_vehicle_communication.html) is used in both the SAMA5D2 and the SAMC21.

I can only assume that those working on documenting the SAMC21 Atmel didn't realize that they already had this excellent resource at their disposal.

This is my quick and dirty adaptation of said code to run on the SAMC21-XPRO evaluation board.

## Requirements

[Rowley Crossworks for ARM](http://www.rowley.co.uk/arm/) is needed to compile this code.  The source code is written to compile with gcc/clang, but you must adapt the code yourself (adding all the startup code that tends to not be available as freely-distributable open-source) if you wish to adopt a different tool chain.

[SAM C21 Xplained Pro Evaluation Kit](http://www.atmel.com/tools/atsamc21-xpro.aspx)

## Usage

The SAMC21-XPRO provides a USB serial port to the SAMC21 target.  Using terminal emulator, open the port at 115200,n,8,1.  An 'h' keystroke provides a help menu, and this explains operation.

