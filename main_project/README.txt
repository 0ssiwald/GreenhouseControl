%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Willkommen zur Cannabis Gewächshaussteuerungssoftware "greenhousecontrol"
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Bedienung und Funktionen:
-	Beim Start des Programms ist links die Top Down Ansicht des Gewächshauses zu sehen. 
	Dabei sind die Pflanzen (symbolisiert als grüne Vierecke) in Pflanzengruppen aufgeteilt.
-	Durch Klicken auf eine dieser Gruppen können Details zu dieser Gruppe angesehen werden. 
	Dabei können in der horizontalen Leiste oben ein Pflanzenprofil ausgewählt werden. 
	Zusätzlich können in der vertikalen Leiste Details zu den einzelnen Lebenswochen der Pflanze eingesehen werden. 
	Rechts daneben können Notizen zu der Gruppe durch den Button "Notiz erstellen" erstellt werden. 
	Durch Doppelklick auf eine Notiz können diese geändert und durch das Kreuz neben der Notiz auch gelöscht werden.
-	Im Hauptfenster sind Benachrichtigungen zu den Gruppen zu finden, welche gerade zu erledigen sind. 
	Diese werden periodisch aktualisiert damit aus den ganzen Benachrichtigungen, 
	welche beim Hinzufügen einer neuen Pflanzengruppe erstellt werden, nur die relevanten angezeigt werden. 
	(Wenn eine Pflanze der Gruppe in Lebenswoche 2 ist, werden nur Benachrichtigungen aus den ersten 2 Lebenswochen angezeigt 
	und nicht Benachrichtigungen aus den späteren Lebenswochen) 
	Durch klicken auf das Kreuz können die Benachrichtigungen als erledigt markiert (gelöscht) werden.
-	Der Knopf Systemlog unten rechts führt zu einer Übersicht aller Logeinträge. 
	Jeden Tag wird ein neues Logfile erstellt und alle Logeinträge dieses Tags mit Zeitstempel in dieser Datei gespeichert.
-	Durch den Knopf unten links kann das Hauptventil geöffnet und geschlossen werden. 
	Dieses Ventil ist eine Sicherheitsmaßname und bei geschlossenem Ventil können die Pflanzen nicht bewässert werden. 
	Wenn eine Pflanze bewässert werden soll aber durch das geschlossene Hauptventil nicht kann färbt sie sich rot.
-	Der Slider daneben zeigt die Messung des Flusssensors an. Dieser dient zum Detektieren von Leaks im Bewässerungssystem. 
	Der Slider kann auch mit der Maus manipuliert werden. 
	Wenn gerade keine Pflanze gegossen wird und der Slider nach rechts bewegt wird 
	(was zu einem Detektieren eines unerwünschten Wasserflusses führt), erschein eine Warnung 
	auf dem Bildschirm und das Hauptventil schließt sich automatisch und muss manuell wieder geöffnet werden. 
-	Mit dem Knopf mit der Flamme kann ein Feueralarm simuliert werden. 
	Es erschein eine Warnung und das Feuer wird durch eine große Flamme im Hintergrund symbolisiert. 
	Durch erneutes Drücken des Knopfes kann die Flamme entfernt werden. 

Informationen zu den Tests:
-	Für die Integrationstest wurde einmal das Zusammenspiel der Sensoren mit SensorControl und der Aktoren (Wasserventile) mit WaterControl getestet.
-	Der Systemtest testet einmal den Standard Anwendungsfall im Gewächshaus bei dem die Sensoren ausgelesen und Pflanzen gegossen werden.
-	Äquivalenzklassenbilung wurde im Unittest der Klasse Greenhouse mit der Methode addPlantGroupToGrid() implementiert. 
- 	Die Tests zum Kontrollfluss sind im Unittest der Klasse WaterControl mit der Methode controlMoistureLevels() implementiert.
