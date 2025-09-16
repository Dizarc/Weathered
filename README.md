# Weathered ⛅

**Weathered** is a smart mirror application that turns your Raspberry Pi into a device which combines real-time weather forecasts with a touch of motivation and style advice;

* ⛅ **Weather at a glance** - Displays temperature, humidity, wind peed all with a multi-day forecast with an intuitive design.

* 🌟 **Daily inspiration** - A Small Language Model provides uplifting quotes to start your day on a happy note!

* 👒**Clothing suggestions** - Get outfit recommendations based on the weather.

* 🪞**Smart mirror ready** - Designed to run on a raspberry Pi with minimal setup making it an easy implementation with a step-by-step tutorial on the setup!

## Prerequisites
* Llama.cpp with a model of your choice(Qwen3 used in development)
* Git 
* Docker and Docker Compose
* Internet connection
* For Yocto builds: good computer

## How to build the embedded OS (Not finished)

1. **Clone this repository:**
```bash
    git clone https://github.com/Dizarc/Weathered.git
    cd Weathered/yocto-build
```

2. **Launch the Yocto Build environment:**
```bash
    docker compose -f docker-compose.yml up -d --build
    docker compose exec yocto-build-shell bash
```

3. **Inside the container, clone the required Yocto layers:**
```bash
    cd /home/builder/yocto
    git clone git://git.yoctoproject.org/poky -b scarthgap
    cd poky
    git clone git://git.yoctoproject.org/meta-raspberrypi -b scarthgap
    git clone https://github.com/openembedded/meta-openembedded.git -b scarthgap
    git clone git://code.qt.io/yocto/meta-qt6.git -b 6.9.2
```

4. **Initialize the build environment and build the image:**
```bash
    oe-init-build-env
    bitbake-layers add-layer ../meta-raspberrypi
    bitbake-layers add-layer ../meta-qt6
    bitbake-layers create-layer ../meta-weathered
    bitbake-layers add-layer ../meta-weathered
```
5. **Add openembedded stuff to bblayers.conf because add-layer in bitbake does not work:**
Your BBLAYERS inside poky/build/conf/bblayers.conf should look like this:
```bash
    BBLAYERS ?= " \
  /home/builder/yocto/poky/meta \
  /home/builder/yocto/poky/meta-poky \
  /home/builder/yocto/poky/meta-yocto-bsp \
  /home/builder/yocto/poky/meta-raspberrypi \
  /home/builder/yocto/poky/meta-openembedded/meta-oe \
  /home/builder/yocto/poky/meta-openembedded/meta-python \
  /home/builder/yocto/poky/meta-openembedded/meta-networking \
  /home/builder/yocto/poky/meta-openembedded/meta-multimedia \
  /home/builder/yocto/poky/meta-qt6 \
  /home/builder/yocto/poky/meta-weathered \
  /home/builder/yocto/poky/build/workspace \
  "
```

6. **Configure local.conf by adding:**
```bash
    MACHINE = "raspberrypi5"
    INIT_MANAGER = "systemd"
    LICENSE_FLAGS_ACCEPTED = "synaptics-killswitch"
    DL_DIR = "${TOPDIR}/../downloads"
    SSTATE_DIR = "${TOPDIR}/../sstate-cache"
    EXTRA_IMAGE_FEATURES += "ssh-server-openssh allow-empty-password empty-root-password allow-root-login" 
```

7. **Configure llamacpp & Weathered recipes:**

8. **Build the final image:**

## Saving and restoring layers setup
Configuration file creation for replication
```bash
    bitbake-layers create-layers-setup [DESTINATION]
    # This creates setup-layers and setup-layers.json
```

## Application development with the SDK
For rapid application development without rebuilding the entire OS use an sdk.

1. **Build the SDK:**

2. **Install SDK on host:**