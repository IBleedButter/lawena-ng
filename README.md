# lawena-ng

> [!IMPORTANT]  
> This is still early in development, don't use it outside of testing yet, and make sure you backup your `tf/` folder!

lawena-ng is a C++ port of Java [Lawena](https://github.com/quanticc/lawena-recording-tool). It greatly enhances your TF2 and other Source games image quality for recording purposes, with little performance loss compared to other alternatives. Records using in-game Source Recorder, with key bindings to ease the process.

Easy to install and use. Does not interfere with your regular configs, HUD or launch options.

## 1. Installing

Not available until I set up GitHub Actions or whatever, so you'll have to build it yourself

## 2. Building

### CMake options

> [!NOTE]  
> You can ignore this section if you're not a developer or a power user

- `-G Ninja` - Use a custom generator, e.g. Ninja

- `-DCMAKE_CXX_COMPILER=clang++` - Use a custom C++ compiler, e.g. Clang

- `-DWITH_LTO=ON` - Enables Link-Time Optimization
    - *Only makes sense with `-DCMAKE_BUILD_TYPE=Release`*

- `-DWITH_UPX=ON` - Packs the executable after compilation to reduce disk space
    - *Only makes sense with `-DCMAKE_BUILD_TYPE=Release`*

- `-DWITH_ASAN=ON` - Enables [AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html)
    - *Only makes sense with `-DCMAKE_BUILD_TYPE=Debug`*
    - NOTE: ASan's memory leak detector gives false positives? Valgrind reported nothing, so could run with `ASAN_OPTIONS=detect_leaks=0`

- `-DWITH_UBSAN=ON` - Enables [UndefinedBehaviorSanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html)
    - *Only makes sense with `-DCMAKE_BUILD_TYPE=Debug`*


### 2.1. Windows

...

### 2.2. Linux

Required dependencies:

- `git`
- `cmake`
- `make` or `ninja`
- `g++` or `clang++`
- `qt6` development headers and libraries

On Ubuntu you can install this with:

```Shell
sudo apt update

sudo apt install git cmake make g++ qt6-base-dev
```

Then:

```Shell
git clone https://github.com/IBleedButter/lawena-ng.git

cd lawena-ng

mkdir build ; cd build

cmake -DCMAKE_BUILD_TYPE=Release -DWITH_LTO=ON ..

cmake --build .

sudo cmake --install .
```

## 3. Contributing

You can help out even if you're not a developer. Issues with old Lawena or ideas for lawena-ng would be much appreciated!

- Open a [GitHub issue](https://github.com/IBleedButter/lawena-ng/issues/new)
- Reply in the [TFTV thread](https://www.teamfortress.tv/64527/lawena-2-0)
- Send me a Discord message: `ibleedbutter`

## 4. Developing

### 4.1. clangd

For clangd to be able to do its job you might need to generate `compile_commands.json`:

```Shell
mkdir build ; cd build

cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang++ -DWITH_ASAN=ON -DWITH_UBSAN=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

cp -v compile_commands.json ..
```

If you run into include errors in your IDE you might also have to create the `.clangd` file with:

```Text
CompileFlags:
  Add:
    - "-I/usr/include/qt6"
```

^ replace `/usr/include/qt6` with whatever directory has the Qt6 headers

### 4.2. Static analysis

```Shell
analyze-build --cdb compile_commands.json --analyze-headers --maxloop 8
```

### 4.3. Coding style

Slightly modified version of [LLVM's coding standard](https://llvm.org/docs/CodingStandards.html) as defined in `.clang-format`

You don't have to learn this, just make sure your IDE supports [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html). CLion does this out-of-the-box, but for Visual Studio Code you have to install the [clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd) extension

### 4.4. Before opening a pull request

Please properly test your code before opening a pull request!

This means building and running it with both ASan and UBsan, using a static analyzer, and writing unit tests

## 5. TO-DO

List of changes / improvements from old Lawena I'll eventually implement:

- Add [CastingEssentialsNext](https://github.com/drunderscore/CastingEssentialsNext)
- Add support for generating VDM files based off of an _events.txt file (*thanks [blakeplusplus](https://www.teamfortress.tv/user/blakeplusplus)*)
- Add a previewer for skyboxes (*see [vtf2png](https://github.com/eXeC64/vtf2png)*)
- Add a previewer for custom particle effects
- Add an in-line renderer to remove dependencies on external tools like VirtualDub, AviRecorder or FFmpeg (*see [libav*](https://trac.ffmpeg.org/wiki/Using%20libav*)*)
- Add [SourceRes](https://github.com/MattMcNam/source-res) for rendering beyond your native resolution (*thanks [maraudeR](https://www.teamfortress.tv/user/maraudeR)*)
    - This hasn't been updated since way before the 64-bit update, it probably doesn't work anymore...
- Rewrite the custom HUDs
- Fix medic speech bubbles appearing for the first few seconds when jumping ticks (*thanks [pajaro](https://www.teamfortress.tv/user/pajaro)*)
- Fix `snd_soundmixer` changing when jumping ticks (*thanks [pajaro](https://www.teamfortress.tv/user/pajaro)*)
- Look into using a [custom tf2 install](https://www.youtube.com/watch?v=lH4scK3uB_s) with gameinfo.txt (*thanks [Hold_on](https://www.teamfortress.tv/user/Hold_on)*)
- Better HUD checking: old Lawena thinks some custom assets like CE are HUDs
    - This can be done by checking `resource/ui/*`
- Output recordings outside the `tf` folder
    - TF2 doesn't let you do this for security reasons, but an easy workaround is to have Lawena move them around as they appear on disk
- Replace Chris Max's maxquality cfgs with mastercomfig ultra preset

## 6. Credits

- Original project created by Montz
- Original developer: [Quantic](https://steamcommunity.com/profiles/76561198012092861) since June 2013 to December 2018
- Current developer: [IBleedButter](https://steamcommunity.com/profiles/76561198130814770) since May 2024
- Graphic configs based on [mastercoms](https://docs.comfig.app/latest/support_me/)' ultra preset
- Built-in Killnotices only and Medic HUD made by [mih](https://github.com/parinpu/recordinghuds)
- Skyboxes included made by [komaokc](https://gamebanana.com/members/289553) from GameBanana
- Valve - Source engine, Team Fortress and the Team Fortress logo