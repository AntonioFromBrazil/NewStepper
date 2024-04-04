<html>

<head>
<meta charset="utf-8">
</head>

<body>

<table border="0" width="100%" id="table1" cellspacing="0" cellpadding="0">
	<tr>
		<td align="center">
		<p align="left"><font size="4" face="Courier">
        <hr align="left">
		</font>
		<p align="left"><b><font face="Courier" size="5"><br>
		This is an ESP-32 nonblocking 
		step motor library based on interrupts for Nema17 and 28byj-48</font></b><font size="4" face="Courier">
		<br>
		By Antonio Testa, April/2024<br>
		<br>
		Special thanks to @gfvalvo from https://forum.arduino.cc who fixed the 
		error: invalid-use-of-non-static-member-function and gave all tricks to 
		use hardware timers inside the library<br>
		<br>
		https://forum.arduino.cc/t/error-invalid-use-of-non-static-member-function/1240240<br>
		<br>
        </p>
        <hr align="left">
		<p align="left"><br>
		In the main program is mandatory to define the following:<br>
		<br>
		#include &lt;NewStepper.h&gt;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;//include the NewStepper.h library <br>
		<br>
		NewStepper name(5,17,16,4);&nbsp; //constructor for driver motor pins 
		in1,in2,in3,in4<br>
		<br>
		name.begin(mode);&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; //At setup(), issue begin() command to init the 
		library timer and set stepmotor mode operation<br>
		<br>
        </p>
        <hr align="left">
		<p align="left">
		<br>
		</font><b><font face="Courier" size="5">CONSTRUCTOR:</font></b><font size="4" face="Courier"><br>
		<br>
		<b>NewStepper name(pin1, pin2, pin3, pin4);</b> <br>
		name is any name for instance stepmotor<br>
		uint8_t pin1,2,3,4 reffers to ESP-32 pins connected to in1,2,3,4 of 
		motor driver<br>
		<br>
		<br>
		</font><font face="Courier" size="5"><b>METHODS:</b></font><font size="4" face="Courier"><br>
		<br>
		<b>name.begin(uint8_t mode);</b><br>
		at setup() section, to init the library timer and step motor model and 
		mode of operation<br>
		uint8_t mode should be:<br>
		0 = For Nema17, 200 steps per turn<br>
		1 = For 28byj-48 full step, 2048 steps per turn, low torque, low consumption<br>
		2 = For 28byj-48 full step, 2048 steps per turn, high torque, high consumption<br>
		3 = For 28byj-48 half step, 4096 steps per turn, middle torque, middle 
		consumption<br>
		<br>
		<b>name.run(steps,vel,cw);</b><br>
		uint32_t steps is the number of steps to travel<br>
		uint8_t vel is the speed (from 2 to ...) higher values lower speed<br>
		boolean cw define direction of turn (true for right, clockwise; false 
		for left, counterclockwise)<br>
		IMPORTANT: the name.run can only be called if the name.where()==0 <br>
		<br>
		<b>name.where();</b><br>
		retun in an uint32_t value the number of steps remainding to motor 
		arrives to destination<br>
		if name.where()==0 means the motor is already in the last destination 
		and is stopped at this moment<br>
		<br>
		<b>name.setms(uint32_t ms);</b><br>
		set the ms counter down (nonblock to be used in substitution of delay 
		function).<br>
		As soon as initiated this ms counter is decremented each millisecond<br>
		<br>
		<b>name.getms();</b><br>
		return the ms counter at moment (initial ms value setted by previously 
		name.setms)<br><br>
        </p>
        <hr align="left"></font><br>
&nbsp;</td>
	</tr>
	<tr>
		<td align="center">
		<b><font face="Courier" size="4"><br>
		correct way to wire step motors to it's driver:<br>
&nbsp;</font></b></td>
	</tr>
	<tr>
		<td align="center">
		<img border="0" src="/NewStepper/images/Nema17.jpg" width="300" height="224" align="middle">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		<img border="0" src="/NewStepper/images/28byj-48.jpg" width="300" height="224" align="middle"></td>
	</tr>
	<tr>
		<td align="center">
		<b><font size="4" face="Courier"><br>
		popular drivers for Nema17 and 28byj-48 step motors:<br>
&nbsp;</font></b></td>
	</tr>
	<tr>
		<td align="center">
		<img border="0" src="/NewStepper/images/D_L298.jpg" width="240" height="240" align="middle">&nbsp;&nbsp;&nbsp;&nbsp;
		<img border="0" src="/NewStepper/images/D_ULN2003.jpg" width="240" height="240" align="middle">&nbsp;&nbsp;&nbsp;&nbsp;
		<img border="0" src="/NewStepper/images/D_L293.jpg" width="240" height="240" align="middle"></td>
	</tr>
</table>
    <br><hr align="left">
</body>

</html>
