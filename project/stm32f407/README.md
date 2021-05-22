### 1. chip

#### 1.1 chip info

chip name : STM32F407ZGT6.

extern oscillator : 8MHz.

uart pin: TX/RX PA9/PA10.

uart2 pin: TX/RX PA2/PA3.

### 2. shell

#### 2.1 shell parameter

baud rate: 115200.

data bits : 8.

stop bits: 1.

parity: none.

flow control: none.

### 3. syn6288

#### 3.1 command Instruction

​          syn6288 is a basic command which can test all syn6288 driver function:

​           -i        show syn6288 chip and driver information.

​           -h       show syn6288 help.

​           -p       show syn6288 pin connections of the current board.

​           -t (reg | syn)

​           -t reg        run syn6288 register test.

​           -t syn        run syn6288 synthesis test.

​           -c (syn <text>| advance (-syn <text>| -sound <soundtype>| -message <messagetype>|  -ring <ringtype>))

​           -c syn <text>        run syn6288 synthesis text function. text format is gb2312.

​           -c advance -syn <text>        run syn6288 advance synthesis text function. text format is gb2312.

​           -c advance -sound <soundtype>        run syn6288 advance synthesis sound function. soundtype can be "A" - "Y".

​           -c advance -message <messagetype>        run syn6288 advance synthesis message function. messagetype can be "A" - "H".

​           -c advance -ring <ringtype>        run syn6288 advance synthesis ring function. ringtype can be "A" - "O".

#### 3.2 command example

```shell
syn6288 -i

syn6288: chip is YuToneWorld SYN6288.
syn6288: manufacturer is YuToneWorld.
syn6288: interface is UART.
syn6288: driver version is 2.0.
syn6288: min supply voltage is 2.4V.
syn6288: max supply voltage is 5.1V.
syn6288: max current is 280.00mA.
syn6288: max temperature is 85.0C.
syn6288: min temperature is -35.0C.
```

```shell
syn6288 -p

syn6288: TX connected to GPIOA PIN3.
syn6288: RX connected to GPIOA PIN2.
```

```shell
syn6288 -t reg

syn6288: chip is YuToneWorld SYN6288.
syn6288: manufacturer is YuToneWorld.
syn6288: interface is UART.
syn6288: driver version is 2.0.
syn6288: min supply voltage is 2.4V.
syn6288: max supply voltage is 5.1V.
syn6288: max current is 280.00mA.
syn6288: max temperature is 85.0C.
syn6288: min temperature is -35.0C.
syn6288: start register test.
syn6288: syn6288_set_baud_rate/syn6288_get_baud_rate test.
syn6288: set 9600 bps.
syn6288: check baud rate ok.
syn6288: syn6288_set_mode/syn6288_get_mode test.
syn6288: set background_15 mode.
syn6288: check mode ok.
syn6288: syn6288_set_text_type/syn6288_get_text_type test.
syn6288: set gb2312 text type.
syn6288: check text type ok.
syn6288: set gbk text type.
syn6288: check text type ok.
syn6288: set big5 text type.
syn6288: check text type ok.
syn6288: set unicode text type.
syn6288: check text type ok.
syn6288: syn6288_set_synthesis_volume/syn6288_get_synthesis_volume test.
syn6288: set synthesis volume 6.
syn6288: check synthesis volume ok.
syn6288: syn6288_set_background_volume/syn6288_get_background_volume test.
syn6288: set background volume 8.
syn6288: check background volume ok.
syn6288: syn6288_set_synthesis_speed/syn6288_get_synthesis_speed test.
syn6288: set synthesis speed 3.
syn6288: check synthesis speed ok.
syn6288: syn6288_set_command test.
syn6288: check command ok.
syn6288: finish register test.
```

```shell
syn6288 -t syn

syn6288: chip is YuToneWorld SYN6288.
syn6288: manufacturer is YuToneWorld.
syn6288: interface is UART.
syn6288: driver version is 2.0.
syn6288: min supply voltage is 2.4V.
syn6288: max supply voltage is 5.1V.
syn6288: max current is 280.00mA.
syn6288: max temperature is 85.0C.
syn6288: min temperature is -35.0C.
syn6288: start synthesis test.
syn6288: synthesis text test.
syn6288: gb2312 synthesis text.
syn6288: gbk synthesis text.
syn6288: big5 synthesis text.
syn6288: unicode synthesis text.
syn6288: synthesis sound test.
syn6288: synthesis message test.
syn6288: synthesis ring test.
syn6288: synthesis control test.
syn6288: synthesis control pause.
syn6288: synthesis control resume.
syn6288: synthesis control stop.
syn6288: synthesis volume test.
syn6288: set synthesis volume 5.
syn6288: synthesis speed test.
syn6288: set synthesis speed 0.
syn6288: synthesis mode test.
syn6288: background mode on.
syn6288: command test.
syn6288: set command 0.
syn6288: set command 1.
syn6288: finish synthesis test.
```

```shell
syn6288 -c syn 你好

syn6288: synthesis 你好.
```

```shell
syn6288 -c advance syn 你好

syn6288: synthesis 你好.
```

```shell
syn6288 -c advance sound A

syn6288: synthesis sound A.
```

```shell
syn6288 -c advance message A

syn6288: synthesis message A.
```

```shell
syn6288 -c advance ring A

syn6288: synthesis ring A.
```

```shell
syn6288 -h

syn6288 -i
	show syn6288 chip and driver information.
syn6288 -h
	show syn6288 help.
syn6288 -p
	show syn6288 pin connections of the current board.
syn6288 -t reg
	run syn6288 register test.
syn6288 -t syn
	run syn6288 synthesis test.
syn6288 -c syn <text>
	run syn6288 synthesis text function.text format is gb2312.
syn6288 -c advance -syn <text>
	run syn6288 advance synthesis text function.text format is gb2312.
syn6288 -c advance -sound <soundtype>
	run syn6288 advance synthesis sound function.soundtype can be "A" - "Y".
syn6288 -c advance -message <messagetype>
	run syn6288 advance synthesis message function.messagetype can be "A" - "H".
syn6288 -c advance -ring <ringtype>
	run syn6288 advance synthesis ring function.ringtype can be "A" - "O".
```

