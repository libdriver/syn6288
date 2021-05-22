<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver SYN6288

[English](/README.md) | [ 简体中文](/README_CN.md)

SYN6288 Chinese speech synthesis chip is a middle and high-end speech synthesis chip with higher cost performance and more natural effect launched by Beijing Yuyintianxia Technology Co., Ltd. in early 2010. SYN6288 receives the text to be synthesized through the asynchronous serial port to realize the text to sound (TTS) conversion. The latest SYN6288 speech synthesis chip inherits the excellent features of OSYNO6188 : the smallest SSOP28L chip package, simple hardware interface and high cost performance; In addition, SYN6288 text recognition is more intelligent, speech synthesis is more natural, and speech synthesis effect and intelligent recognition effect are greatly improved. It is a speech synthesis chip for high-end applications.

LibDriver SYN6288 is the full function driver of SYN6288 launched by LibDriver.It provides text synthesis, music synthesis, alarm sound synthesis and other functions.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example advance](#example-advance)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver SYN6288 source files.

/interface includes LibDriver SYN6288 UART platform independent template。

/test includes LibDriver SYN6288 driver test code and this code can test the chip necessary function simply。

/example includes LibDriver SYN6288 sample code.

/doc includes LibDriver SYN6288 offline document.

/datasheet includes SYN6288 datasheet。

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

### Install

Reference /interface UART platform independent template and finish your platform UART driver.

Add /src, /interface and /example to your project.

### Usage

#### example basic

```C
uint8_t res;

res = syn6288_basic_init();
if (res)
{
    return 1;
}

...

res = syn6288_basic_synthesis("你好");
if (res)
{
    syn6288_basic_deinit();

    return 1;
}
syn6288_basic_sync();

...

syn6288_basic_deinit();

return 0;
```

#### example advance

```C
uint8_t res;

res = syn6288_advance_init();
if (res)
{
    return 1;
}

...

res = syn6288_advance_synthesis("你好");
if (res)
{
    syn6288_advance_deinit();

    return 1;
}
syn6288_advance_sync();

...

res = syn6288_advance_sound(SYN6288_SOUND_A);
if (res)
{
    syn6288_advance_deinit();

    return 1;
}
syn6288_advance_sync()    

...
    
res = syn6288_advance_message(SYN6288_MESSAGE_A);
if (res)
{
    syn6288_advance_deinit();

    return 1;
}
syn6288_advance_sync();

...

res = syn6288_advance_ring(SYN6288_RING_A);
if (res)
{
    syn6288_advance_deinit();

    return 1;
}
syn6288_advance_sync();

...
    
syn6288_advance_deinit();

return 0;
```

### Document

Online documents: https://www.libdriver.com/docs/syn6288/index.html

Offline documents: /doc/html/index.html

### Contributing

Please sent an e-mail to lishifenging@outlook.com

### License

Copyright (C) LibDriver 2015-2021 All rights reserved 



The MIT License (MIT) 



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

### Contact Us

Please sent an e-mail to lishifenging@outlook.com