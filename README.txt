Autoři: Adam František Čapka (xcapka06)
	Filip Janoušek (xjanou24)

Simulátor robotů.

Testováno v QT Creatoru a v Ubuntu.

Uživatel má možnost editovat simulaci - přidání překážek a robotu. 
uživatel může kliknout na robota a ovládat ho. Po klikuntí se robot označí zeleně a je možné kliknout na tlačítka, které budou měnit jeho stavy. Dokud se neklikne na žádné z těchto tlačítek, tak se robot hýbe jako by nebyl ovladaný manuálně. Opětovným klinutím na robota se tento robot odoznačí.

Uživatel může importovat a exportovat rozložení simulace.
Tlačítko export uloží momentální stav do souboru "scene.json". Tlačítko import potom otevře tento soubor v GUI v režimu editace pro manuální úpravy. Následně je potřeba kliknout na tlačítko save. Tlačítko load načtě scénu ze souboru "scene.json"

Uživatel může simulaci pozastavit a následně znovu spustit.

Při načtení ze souboru se překážky i roboti umístí správně.