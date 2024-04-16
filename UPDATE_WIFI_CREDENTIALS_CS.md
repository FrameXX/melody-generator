# Návod jak aktualizovat heslo či SSID ke kterému se má počítáč připojit.

## Co budete potřebovat
 - Počítač s Linux, Windows či MacOS (cokoliv kde lze nainstalovat drivery pro ovládání ESP8266 a tím pádem je schopné nahrávat kód na ESP8266)
 - [Editor který podporuje rozšíčení PlatformIO](https://docs.platformio.org/en/latest/integration/ide/index.html) (Doporučuji [VSCodium](https://vscodium.com/).)
  - V editoru nainstalované rozšíření [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) a v případě VSCodium i [officiální rozšíření pro kódování v C++ ](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) a [C++ rozšiřovací balíček](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)

## Postup
 - Stáhněte si kód z [repozitáře](https://github.com/FrameXX/melody-generator) do ZIPu (zelené tlačítko "Code" a potom "Download ZIP")
 - Rozbalte ZIP do samostatné složky
 - Otevřete složku v editoru
 - Ve složce `lib` vytvořte složku `WiFiCredentials`
 - V této složce vytvořte soubor `WiFiCredentials.h`
 - Do souboru zkopírujte následující kód příčemž přepište `název wifiny` a `heslo od wifiny` jejich reálnými hodnotami:
```c
#pragma once

#define WIFI_SSID "název wifiny"
#define WIFI_PASS "heslo of wifiny"
```
 - Nahrajte kód do připojeného ESP8266. V případě jiných potíží si zkuste poradit sami.
