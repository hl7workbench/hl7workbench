# HL7 Workbench

## Table of Contents

* [Description](README.md#description)
* [Installation](README.md#installation)
  * [Linux](README.md#linux)

## Description

Early stage development of an open-source workbench to edit, send and
receive Health Level 7 (HL7) messages.

## Installation

### Linux

* Install build dependencies
    ```
    sudo apt install build-essentials git qtbase5-dev
    ```

* Download HL7 Workbench source
    ```
    git clone https://github.com/hl7workbench/hl7workbench.git
    cd hl7workbench
    ```

* Build and install HL7 Workbench
    ```
    mkdir build && cd build
    qmake ..
    make
    sudo make install
    ```

* Run HL7 Workbench
    ```
    hl7workbench
    ```
