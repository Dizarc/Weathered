# Weathered ⛅

**Weathered** is a smart mirror application that turns your Raspberry Pi into a device which combines real-time weather forecasts with a touch of motivation and style advice;

* ⛅ **Weather at a glance** - Displays temperature, humidity, wind peed all with a multi-day forecast with an intuitive design.

* 🌟 **Daily inspiration** - A Small Language Model provides uplifting quotes to start your day on a happy note!

* 👒**Clothing suggestions** - Get outfit recommendations based on the weather.

* 📰**News** - See current news around the world.

* 🪞**Smart mirror ready** - Designed to run on a raspberry Pi with minimal setup making it an easy implementation with a step-by-step tutorial on the setup!

## Prerequisites
* Llama.cpp with a model of your choice(Qwen3 used in development)
* Git 
* Docker and Docker Compose
* Internet connection
* VcXsrv (For windows users) or an X11 server (for linux users) to enable GUI display in the Docker Development Environment
* Yocto builds need a capable computer

## 🐳Setting up the Docker Development Environment

This section explains how to build and run the app inside a Docker-based development environment. The environment includes both the Qt build system and the Llama.cpp API server for running the language model.

### Display configuration (Windows vs Linux)

The Docker Compose file already includes environment variables for display configuration.

Depending on your host OS, **comment/uncomment** the appropriate lines inside docker-compose.yml:

For Windows (using VcXsrv):
```yml
    #- DISPLAY=${DISPLAY:-:0} 
    - DISPLAY=host.docker.internal:0.0 
```

For Linux (using local X11):
```yml
    - DISPLAY=${DISPLAY:-:0} 
    #- DISPLAY=host.docker.internal:0.0 
```

Also ensure you have the X11 socket shared:
```yml
    volumes:
      - /tmp/.X11-unix:/tmp/.X11-unix:rw
```

And finally for linux if available you can give GPU access:
```yml
    devices:
      - "/dev/dri:/dev/dri" 
```

### Step 1: Build and start the Containers

To build and start the containers you first need to create an .env file in the same folder as the docker-compose file.

It should have these environmental variables: 
* **WEATHER_API_KEY**: Your API key from OpenWeatherMap
* **WEATHER_API_CITY_COUNTRY**: Your City, Country codes as per OpenWeatherMap docs
* **NEWS_API_KEY**: Your API key from TheNewsApi
* **MODEL_PATH**: A path pointing to your .gguf model file

With that file created you are ready to build and start the containers:
```bash
    docker compose up -d --build
```
This command:
* Builds the docker images and
* Starts the development container in detached mode

### Step 2: Enter the dev Container

Once the containers are running, open a shell inside the Qt development container with:
```bash
    docker exec -it weathered-app-dev /bin/bash
```
This places you inside the /app directory where your project files are mounted.

### Step 3: Build and Run the app

Inside the container build and run the app using CMake and Ninja:
```bash
    cmake -G Ninja -S . -B build/docker/ && ninja -C build/docker/ && build/docker/./appWeathered
```
This will:
* Configure the build with CMake
* Compile the project using Ninja
* Launch the app

If everything goes well the GUI should appear on your host display

### Step 4: Stopping and Cleaning up

To stop all running containers:
```bash
    docker compose down
```

To rebuild from scratch:
```bash
    docker compose down -v
    docker compose up -d --build
```

## 🖥️How to build the embedded OS (Not finished)
The build process is currently on hold due to computer restraints

### 1. **Launch the Yocto Build environment inside yocto-build folder:**
```bash
    docker compose -d --build
    docker compose exec yocto-build-shell bash
```

### 2. **Inside the container, clone the required Yocto layers:**
```bash
    cd /home/builder/yocto
    git clone git://git.yoctoproject.org/poky -b scarthgap
    cd poky
    git clone git://git.yoctoproject.org/meta-raspberrypi -b scarthgap
    git clone https://github.com/openembedded/meta-openembedded.git -b scarthgap
    git clone git://code.qt.io/yocto/meta-qt6.git -b 6.9.2
```

### 3. **Initialize the build environment and build the image:**
```bash
    oe-init-build-env
    bitbake-layers add-layer ../meta-raspberrypi
    bitbake-layers add-layer ../meta-qt6
    bitbake-layers create-layer ../meta-weathered
    bitbake-layers add-layer ../meta-weathered
```
### 4. **Add openembedded stuff to bblayers.conf because add-layer in bitbake does not work:**

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

### 5. **Configure local.conf by adding:**
```bash
    MACHINE = "raspberrypi5"
    INIT_MANAGER = "systemd"
    LICENSE_FLAGS_ACCEPTED = "synaptics-killswitch"
    DL_DIR = "${TOPDIR}/../downloads"
    SSTATE_DIR = "${TOPDIR}/../sstate-cache"
    EXTRA_IMAGE_FEATURES += "ssh-server-openssh allow-empty-password empty-root-password allow-root-login" 
```

### 6. **Configure llamacpp & Weathered recipes:**

### 7. **Build the final image:**

### Saving and restoring layers setup
Configuration file creation for replication
```bash
    bitbake-layers create-layers-setup [DESTINATION]
```

This creates setup-layers and setup-layers.json

### Application development with the SDK
For rapid application development without rebuilding the entire OS use an sdk.