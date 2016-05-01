# SQLitencrypt
A lightweight SQLite3 C++ wrapper for Android, iOS, Unix and Unix-like operating system(including SQLite3 encryption extension)

- [Instroduction](#introduction)
- [Getting Started](#getting-started)
- [Examples](#examples)
- [License](#license)

## Introduction

SQLitencrypt is base on native C APIs of sqlite3 and use the the encryption extension of wxsqlite3.

## Getting Started

### Requirements

#### Unix
1. cmake
2. c++ compiler support for c++11

#### Android
1. android-sdk
2. android-ndk

#### iOS
TODO

### Get source
`git clone --recursive git@github.com:robchou/sqlitencrypt.git`

### Comiple

#### Unix
```bash
cd sqlitencrypt
mkdir build && cd build
cmake ..
make
```

### Android
```bash
cd android
ndk-build
```

### iOS
TODO

## Examples

### Unix
```bash
cd build
./examples/company
```

### Android
TODO

### iOS
TODO

## License
SQLitencrypt is licensed under the [Apache License, Version 2.0.](./LICENSE)
