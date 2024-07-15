# lawena-ng

lawena-ng is a C++ port of Java [Lawena](https://github.com/quanticc/lawena-recording-tool). It greatly enhances your TF2 and other Source games image quality for recording purposes, with little performance loss compared to other alternatives. Records using in-game Source Recorder, with key bindings to ease the process.

Easy to install and use. Does not interfere with your regular configs, HUD or launch options.

## Features

- Working settings manager, compatible with old Lawena's setting file
	- it reads from and saves to `lawena.lwf` in current directory by default, but this can be overwritten by passing a runtime argument (e.g. `./lawena-ng /path/to/my/lawena.lwf`)

## Installing

. . .

## Building

### Windows

*Required Visual Studio workloads*:
- Desktop development with C++

Visual Studio -> Clone a repository -> URL: `https://github.com/ibleedbutter/lawena-ng.git`

Build -> Build all (or `Ctrl+Shift+B`)

### Linux

*Required dependencies*:
- `git`
- `cmake`
- `make`
- `g++` or `clang++`

```Bash
git clone https://github.com/ibleedbutter/lawena-ng.git
cd lawena-ng
mkdir build && cd build
cmake ..
make
```

## Contributing

You can help out even if you're not a developer. Issues with old Lawena or ideas for lawena-ng would be much appreciated!

- Open a [GitHub issue](https://github.com/IBleedButter/lawena-ng/issues/new)
- Reply in the [TFTV thread](https://www.teamfortress.tv/64527/lawena-2-0)
- Send me an email: `119887590+IBleedButter@users.noreply.github.com`
- Send me a Discord message: `ibleedbutter`

## TO-DO

Port Java codebase to C++. Use [Qt6](https://www.qt.io/product/qt6) as cross-platform GUI framework. 

- Add 64-bit TF2 support and enable it by default
- Add CastingEssentials by default
- Add support for generating VDM files based off of an _events.txt file (*thanks [blakeplusplus](https://www.teamfortress.tv/user/blakeplusplus)*)
- Add a previewer for custom particle effects
- Add an in-line renderer to remove dependencies on external tools like VirtualDub, AviRecorder or FFmpeg
- Add SourceRes for rendering beyond your native resolution (*thanks [maraudeR](https://www.teamfortress.tv/user/maraudeR)*)
- Fix the skybox previewer (*only seems to be dysfunctional on Linux?*)
- Fix 'kill notices only' and 'medic' HUDs not working (*only seems to be dysfunctional when using CE?*)
- Fix 'medic' HUD: include HP (*thanks [Blu2th1000](https://www.teamfortress.tv/user/Blu2th1000)*)
- Fix medic speech bubbles appearing for the first few seconds when jumping ticks (*thanks [pajaro](https://www.teamfortress.tv/user/pajaro)*)
- Fix `snd_soundmixer` changing when jumping ticks (*thanks [pajaro](https://www.teamfortress.tv/user/pajaro)*)
- Look into using a [custom tf2 install](https://www.youtube.com/watch?v=lH4scK3uB_s) with gameinfo.txt (*thanks [Hold_on](https://www.teamfortress.tv/user/Hold_on)*)
- Remove dependence on admin privs under Windows ([CLWindows.java:125](https://github.com/quanticc/lawena-recording-tool/blob/d3bf73e540d927be23e09516a4569162dcd3b700/src/main/java/lwrt/CLWindows.java#L125)?)
- Better HUD checking: old Lawena thinks some custom assets like CE are HUDs
- Output recordings outside the `tf` folder: TF2 doesn't let you do this, but an easy workaround is to have Lawena move them around as they appear on disk
- Better config:
	- graphics: use mastercomfig ultra preset instead of Chris Max's maxquality cfgs (*they've been unmaintained since 2012*)
	- `tf_use_min_viewmodels 0`
	- `gameui_preventescapetoshow`
	- `cl_jiggle_bone_framerate_cutoff 0`: fixes botkiller shaking (*thanks phnx8*)
	- `r_portalsopenall 1`: fixes doorway flash glitch (*thanks phnx8*)
	- `violence_*gibs` & `violence_*blood`: enables gibs in case someone disables them in their class cfg (*thanks phnx8*)
	- `hud_saytext_time 0`: keeps chat disabled (*thanks phnx8*)
- Better default settings
	- Change resolution from 1280x720 to 1920x1080
	- Change viewmodelf FOV from 70 to 90
	- Disable motion blur
	- Enable default crosshair
	- Enable combat text (dmg numbers)
	- Enable hitsounds
	- Add `-insecure` launch option

## Credits

- Original project created by Montz
- Original developer: [Quantic](steamcommunity.com/profiles/76561198012092861/) since June 2013 to December 2018
- Current developer: [IBleedButter](https://steamcommunity.com/profiles/76561198130814770) since May 2024
- Graphic .cfg files based on [mastercoms'](https://docs.comfig.app/latest/support_me/) ultra preset
- Built-in Killnotices only and Medic HUD made by [mih](https://github.com/parinpu/recordinghuds)
- Skyboxes included made by [komaokc](gamebanana.com/members/submissions/textures/289553) from GameBanana
- Includes some content used in PLDX recording tool
- Valve - Source engine, Team Fortress and the Team Fortress logo
