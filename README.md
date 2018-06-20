https://github.com/pantaluna/support_esp_espidf

# 1. Environment
- MCU: Adafruit HUZZAH32 ESP32 development board.
- ESP-IDF Github master branch of Jun 20, 2018.

# 2. Setup
```
cd ~
git clone --recursive https://github.com/pantaluna/support_esp_espidf.git
cd  support_esp_espidf
make flash monitor
```

SERIAL UART:

```
...
...
```

#.
# APPENDICES
#.


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
git commit -m "Testing 123"

git push --set-upstream origin master

git status
```
