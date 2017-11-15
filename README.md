# Buffalo-3SE-on-board-firmware

On-Board Firmware for the Twisted Pear Audio - Buffalo 3-SE-Pro DACs

AVR - ATTiny85
Fuse bytes:
- Low:	0xE2
- High:	0xF5
- Ext:	0xFF

[![Build Status](https://travis-ci.org/russwyte/B3SEPro-OnBoard-Firmware.svg?branch=master)](https://travis-ci.org/russwyte/B3SEPro-OnBoard-Firmware)

[Latest Release](https://github.com/russwyte/B3SEPro-OnBoard-Firmware/releases/latest "latest release")

The switches are connected to the Port Expander GPIO pins with weak pull-ups enabled. The other end of the switch is connected to GND - thus "Off" is open and results in logic 1 and "On" is closed and results in logic 0.

# Switch Assignments

## Switch 1

<table>
	<tr>
		<th>Position(s)</th>
		<th>Name</th>
		<th>On</th>
		<th>Off</th>
	</tr>
	<tr>
		<td>1</td>
		<td>Input Select</td>
		<td>SPDIF</td>
		<td>SERIAL(PCM/DSD)</td>
	</tr>
	<tr>
		<td>2-3</td>
		<td>PCM Format</td>
		<td colspan="2">
			<table>
				<tr>
					<th>2</th>
					<th>3</th>
					<th>Format</th>	
				</tr>
				<tr>
					<td>on</td>				
					<td>on</td>				
					<td>I2S</td>	
				</tr>
				<tr>
					<td>off</td>				
					<td>on</td>				
					<td>LJ</td>	
				</tr>
				<tr>
					<td>on</td>				
					<td>off</td>				
					<td>RJ</td>	
				</tr>
				<tr>
					<td>off</td>				
					<td>off</td>				
					<td>I2S</td>	
				</tr>
			</table>
		</td>
	</tr>
	<tr>
		<td>4-5</td>
		<td>PCM Word Length</td>
		<td colspan="2">
			<table>
				<tr>
					<th>4</th>
					<th>5</th>
					<th>Length</th>	
				</tr>
				<tr>
					<td>on</td>				
					<td>on</td>				
					<td>32-bit</td>	
				</tr>
				<tr>
					<td>off</td>				
					<td>on</td>				
					<td>24-bit</td>	
				</tr>
				<tr>
					<td>on</td>				
					<td>off</td>				
					<td>16-bit</td>	
				</tr>
				<tr>
					<td>off</td>				
					<td>off</td>				
					<td>32-bit</td>	
				</tr>
			</table>
		</td>
	</tr>
		<tr>
		<td>6-8</td>
		<td>Filter Selection</td>
		<td colspan="2">
			<table>
				<tr>
					<th>6</th>
					<th>7</th>
					<th>8</th>
					<th>Filter</th>	
				</tr>
				<tr>
					<td>on</td>				
					<td>on</td>				
					<td>on</td>				
					<td>Fast roll-off, linear phase</td>	
				</tr>
				<tr>
					<td>off</td>				
					<td>on</td>				
					<td>on</td>				
					<td>Slow roll-off, linear phase</td>	
				</tr>
				<tr>
					<td>on</td>				
					<td>off</td>				
					<td>on</td>				
					<td>Fast roll-off, minimum phase</td>	
				</tr>
				<tr>
					<td>off</td>				
					<td>off</td>				
					<td>on</td>				
					<td>Slow roll-off, minimum phase</td>	
				</tr>
				<tr>
					<td>on</td>				
					<td>on</td>				
					<td>off</td>				
					<td>Apodizing fast roll-off, liniear phase</td>	
				</tr>
				<tr>
					<td>off</td>				
					<td>on</td>				
					<td>off</td>				
					<td>Reserved</td>	
				</tr>
				<tr>
					<td>on</td>				
					<td>off</td>				
					<td>off</td>				
					<td>Hybrid fast roll-off, minimum phase</td>	
				</tr>
				<tr>
					<td>off</td>				
					<td>off</td>				
					<td>off</td>				
					<td>Brickwall</td>	
				</tr>
			</table>
		</td>
	</tr>
</table>

## Switch 2

<table>
	<tr>
		<th>Position(s)</th>
		<th>Name</th>
		<th>On</th>
		<th>Off</th>
	</tr>
	<tr>
		<td>1</td>
		<td>Automute</td>
		<td>DISABLE</td>
		<td>ENABLE</td>
	</tr>
	<tr>
		<td>2</td>
		<td>OSF</td>
		<td>ENABLED</td>
		<td>DISABLED</td>
	</tr>
	<tr>
		<td>3-4</td>
		<td>IIR Filter Bandwidth</td>
		<td colspan="2">
			<table>
				<tr>
					<th>3</th>
					<th>4</th>
					<th>Bandwidth @ 44.1khz</th>	
				</tr>
				<tr>
					<td>on</td>				
					<td>on</td>				
					<td>47.44K</td>	
				</tr>
				<tr>
					<td>off</td>				
					<td>on</td>				
					<td>50K</td>	
				</tr>
				<tr>
					<td>on</td>				
					<td>off</td>				
					<td>60K</td>	
				</tr>
				<tr>
					<td>off</td>				
					<td>off</td>				
					<td>70K</td>	
				</tr>
			</table>
		</td>
	</tr>
	<tr>
		<td>5-8</td>
		<td>4bit DPLL Bandwidth (switch 5 is the low bit)</td>
		<td colspan="2">on = 0 off = 1 - 0b0000=default 0b0001=lowest 0b1111=highest</td>
	</tr>
</table>


The MIT License (MIT)

Copyright (c) 2017 Russ White

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
