# Styring og regulering af et Pan og Tilt system
Semesterprojekt F16


Indledning:
I forbindelse med overvågningssystemer af f.eks. mennesker eller objekter der bevæger sig, kan
der benyttes et kamera tracking system, der kan følge personen eller objektet. Tracking systemer
kan også bruges indenfor tracking af lydkilder eller afstandsmåling. Fælles for disse systemer er at
de grundlæggende er styret at et Pan og Tilt system.


Projektbeskrivelse:
Formålet med projektarbejdet er at opbygge et Pan og Tilt system således, at det er muligt at
kunne styre systemet fra en eller flere bruger inputs f.eks. et joystick, et keyboard, knapper eller
via kommandoer fra en computer. Derudover skal systemet også giver brugeren mulighed for
feedback af væsentlige systemparametre, se figur 1.


Det prioriteres fra projektstillernes side at løsningen indeholder:  
 - En systemanalyse og modellering af systemets enkelte elementer
 - Analyse og design af reguleringssløjferne i Matlab og Simulink  
 - Dokumentation for FPGA design og implementering
 - Dokumentation for microprocessorprogrammets design og implementering, herunder opdeling i Task’s og valg af skedulering
 - Test og verifikation af systemet
Det er optil projektgruppen selv at vælge regulatortyper og kravene til reguleringssløjfernes
egenskaber.

Det er følgende krav til systemet:
-  Regulatorerne skal implementeres på én microprocessoren.
-  Der skal benyttes SPI kommunikationen imellem microprocessoren og FPGA’en.  
-  FPGA’en skal styre PWM signalerne til motorerne.
-  FPGA’en skal benyttes til at bestemmes motorernes position via encoderne.   
Følgende stilles til rådighed for projektet:
-  4 stk. Pan og Tilt opstillinger, som skal deles mellem projektgrupperne.
-  Motor med indbygget encoder til hver projektgruppe.  
-  Print med dobbelt H‐bro til hver projektgruppe.
Derudover kan der på Blackboard findes datablade på komponenter og tegninger over
opstillingerne.  

Rapporten:
Rapporten skal indeholde dokumentation for den udførte del af arbejdet, såvel analyse som
begrundelse for de beslutninger, der er truffet undervejs, beskrivelse af de implementerede
løsninger herunder afprøvnings‐ og måleresultater. Rapporten må maksimalt være på ca. 60 A4‐
sider, inkl. bilag, men ekskl. kode, som evt. kan vedlægges på en CD. Eksaminationen tager
udgangspunkt i rapporten.
Rapporten afleveres i 2 eksemplarer i Ø26‐608‐3, senest den 25. maj 2015 kl. 12.00.
