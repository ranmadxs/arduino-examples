Platformio
==========

## Install

### 1° Install platformio

```bash
 pip install -U platformio
```

### 2° Link simbólicos

```bash
ln -s ~/.platformio/penv/bin/platformio /usr/local/bin/platformio
ln -s ~/.platformio/penv/bin/pio /usr/local/bin/pio
ln -s ~/.platformio/penv/bin/piodebuggdb /usr/local/bin/piodebuggdb
```

## Uninstall

```bash
pip uninstall platformio
```

## Errors

On error 
*** [upload] could not open port /dev/ttyUSB0: [Errno 13] Permission denied: '/dev/ttyUSB0'

```bash
sudo usermod -a -G tty <user>
sudo usermod -a -G dialout <user>
sudo chown ranmadxs:ranmadxs /dev/ttyUSB0
```

## Run

### Run 01SerialPrint

```bash
# Change directory to example
cd 01SerialPrint/

# Compile
platformio run

# Compile and upload
platformio run --target upload

# if msg error 
# [Errno 13] Permission denied: '/dev/ttyUSB0'

sudo chown esanchez:esanchez /dev/ttyUSB0
```

## Other commands

```bash
# List USB Devices connected
pio device list

# see serial device monitor send to file out
pio device monitor -f log2file -f default

# list enviorments boards
pio run --list-targets

# Install boards 

pio init --board uno --board nodemcuv2 --board pro16MHzatmega328

# Instalar Libs

platformio lib search thread
platformio lib install 440

# upload 

# platformio run -t upload -e <board> --upload-port <USB>

platformio run -t upload -e uno
platformio run -t upload -e nodemcuv2 --upload-port COM7 

```




