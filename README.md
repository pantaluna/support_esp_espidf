https://github.com/pantaluna/support_esp_espidf

## Environment
- Development Kit:      [Adafruit HUZZAH32]
- Core (if using chip or module): [ESP-WROOM32]
- IDF version (commit id): 4b91c82c Jun19,2018
- Development Env:      [Eclipse]
- Operating System:     [Windows]
- Power Supply:         [USB]

## Problem Description
ledc_set_fade_with_time() does not fade from duty 0..255 when it is executed immediately after setting and updating the duty cycle to 0 using ledc_set_duty() and ledc_update_duty().

### Expected Behavior
ledc_set_fade_with_time() does fade from duty 0..255 in 5 seconds.

### Actual Behavior
ledc_set_fade_with_time() does not fade and ends immediately.

### Workaround
Adding a delay of 1 second after setting and updating the duty cycle to 0 using ledc_set_duty() and ledc_update_duty(), and before ledc_set_fade_with_time().

### Steps to repropduce
No wiring needed.

```
cd ~
git clone --recursive https://github.com/pantaluna/support_esp_espidf.git
cd  support_esp_espidf
make flash monitor
```

### Code to reproduce this issue
https://github.com/pantaluna/support_esp_espidf


## Debug Logs
Note that the first two ledc_set_fade_with_time() section does nothing (it ends immediately).

```
D (424) myapp: app_main()
I (424) myapp: === LEDC: ledc_timer_config(LEDC_TIMER_8_BIT) ledc_channel_config() freq=60 | duty = 255
D (434) ledc: LEDC_PWM CHANNEL 0|GPIO 14|Duty 0255|Time 0
V (444) intr_alloc: esp_intr_alloc_intrstatus (cpu 0): checking args
V (444) intr_alloc: esp_intr_alloc_intrstatus (cpu 0): Args okay. Resulting flags 0x40E
D (444) intr_alloc: Connected src 43 to int 13 (cpu 0)
I (464) myapp: === freq=60 | vary duty 0..255 using ledc_set_fade_with_time(5 seconds)
I (474) myapp:   Set duty := 0
I (474) myapp:   ***PROBLEM ledc_set_fade_with_time() does not fade. It starts at duty 255 instead of duty 0 and so e
nds right away
D (484) ledc: Set to target duty: 255
I (504) myapp: === freq=60 | vary duty 0..255 using ledc_set_fade_with_time(5 seconds)
I (504) myapp:   Set duty := 0
I (504) myapp:   ***PROBLEM ledc_set_fade_with_time() does not fade. It starts at duty 255 instead of duty 0 and so e
nds right away
D (514) ledc: Set to target duty: 255
I (534) myapp: === freq=60 | vary duty 0..255 using ledc_set_fade_with_time(5 seconds)
I (534) myapp:   Set duty := 0
I (534) myapp:   ***OK when using a delay of 1 second after updating duty...***
I (544) myapp:    FIX: wait 1 second after updating duty...
D (1554) ledc: cur duty: 0; target: 255, step: 255, cycle: 1; scale: 1; dir: 1

I (5804) myapp: === freq=60 | vary duty 0..255 using ledc_set_fade_with_time(5 seconds)
I (5804) myapp:   Set duty := 0
I (5804) myapp:   ***OK when using a delay of 1 second after updating duty...***
I (5814) myapp:    FIX: wait 1 second after updating duty...
D (6814) ledc: cur duty: 0; target: 255, step: 255, cycle: 1; scale: 1; dir: 1
```


##################################################################################################
# APPENDICES

# 1. SOP for upload to GITHUB
https://github.com/pantaluna/support_esp_espidf

## 1.a: BROWSER: create github public repo support_esp_espidf of pantaluna at Github.com

## 1.b: MSYS2 git
```
git config --system --unset credential.helper
git config credential.helper store
git config --list

cd  /c/myiot/esp/support_esp_espidf
git init
git add .
git commit -m "First commit"
git remote add origin https://github.com/pantaluna/support_esp_espidf.git

git push --set-upstream origin master

git remote show origin
git status

git tag --annotate v1.0 --message "First release"
git push origin --tags

```

# 2. SOP for source updates
```
cd  /c/myiot/esp/support_esp_espidf
git add .
git commit -m "Updated xyz"

git push --set-upstream origin master

git status
```
