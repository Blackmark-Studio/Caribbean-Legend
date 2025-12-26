int iClockSP4PseudoGlobal = SOUND_INVALID_ID;

void ProcessDialogEvent()
{
	ref NPChar, sld, realShip;
	aref Link, NextDiag, arTmp;
	int i, n, NextMonth, idx;
	string sTemp, sStr, Month, NationName, shipType;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (HasSubStr(Dialog.CurrentNode, "chosenIdx/"))
	{
		Dialog.tmpIdx = FindStringAfterChar(Dialog.CurrentNode, "/");
		Dialog.CurrentNode = FindStringBeforeChar(Dialog.CurrentNode, "/");
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		// Диалог с Йоханом
		case "ClockTower_Johan_1":
			dialog.text = "Halt, "+GetTitle(NPChar, true)+". Weiter geht's nicht.";
			link.l1 = "Warum nicht?";
			link.l1.go = "ClockTower_Johan_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_2":
			dialog.text = "Den Turm seht Ihr? Büro der Niederländischen Westindien-Kompanie. Schiffsregisterabteilung und Archiv. Zutritt nur mit Termin.";
			link.l1 = "Und wie bekommt man einen Termin?";
			link.l1.go = "ClockTower_Johan_3";
		break;

		case "ClockTower_Johan_3":
			dialog.text = "Wer es wissen muss, weiß es. Der Mynheer Direktor arbeitet nicht mit jedem x-beliebigen.";
			link.l1 = "'Mynheer Direktor?' Wer ist das?";
			link.l1.go = "ClockTower_Johan_4";
		break;

		case "ClockTower_Johan_4":
			dialog.text = "Verwalter van Doorn. Vielleicht ist er nicht genau ein Direktor, aber alle nennen ihn so. Arbeitet hier seit zehn Jahren — hat Ordnung geschaffen. Jetzt läuft jedes Schiff in der Karibik über sein Büro.";
			link.l1 = "Jedes Schiff? Auch Kriegsschiffe?";
			link.l1.go = "ClockTower_Johan_5";
		break;

		case "ClockTower_Johan_5":
			dialog.text = "Nur die besten Schiffe und die reichsten Kapitäne. Ein Kunde unseres Büros zu sein ist eine große Ehre!";
			link.l1 = "Was für Dienste bietet ihr an?";
			link.l1.go = "ClockTower_Johan_6";
		break;

		case "ClockTower_Johan_6":
			dialog.text = "Mir sind die Einzelheiten nicht bekannt — ich bewache nur den Eingang. Aber ich habe gehört, die Leute gehen zufrieden.";
			link.l1 = "Beeindruckend.";
			link.l1.go = "ClockTower_Johan_7";
		break;

		case "ClockTower_Johan_7":
			dialog.text = "Und ich sage Euch noch etwas. Seht Ihr die Uhr? Ein europäisches Wunderwerk — so etwas findet man nirgends in unserer Wildnis. Der Mynheer Direktor kümmert sich persönlich darum.";
			link.l1 = "Vielleicht können wir uns einigen?";
			link.l1.go = "ClockTower_Johan_8_1";
			link.l2 = "Gibt es denn gar nichts, was ich tun kann, um reinzukommen?";
			link.l2.go = "ClockTower_Johan_8_2";
		break;

		case "ClockTower_Johan_8_1":
			dialog.text = "Ich nehme keine Bestechungsgelder!";
			link.l1 = "Entschuldigung. Du bist ein guter Kerl. Wie heißt du?";
			link.l1.go = "ClockTower_Johan_9";
		break;

		case "ClockTower_Johan_9":
			dialog.text = "Johan... Hört zu... Ich verstehe, Ihr seid nicht von hier. Aber hier herrscht Ordnung. Der Mynheer Direktor sagt immer: Einmal Schwäche zeigen — und unser Turm stürzt ein. Wollt Ihr rein? Helft der Stadt — dann wird man Euch bemerken.";
			link.l1 = "Verstehe. Pass auf dich auf, Soldat.";
			link.l1.go = "ClockTower_Johan_11";
		break;

		case "ClockTower_Johan_8_2":
			dialog.text = "Tja, ich weiß nicht. Der Mynheer Direktor belohnt Freunde von Willemstad. Helft der Stadt — und man wird Euch bemerken. Ich verstehe, Ihr seid nicht von hier. Aber hier herrscht Ordnung. Der Mynheer Direktor sagt immer: Einmal Schwäche zeigen — und unser Turm stürzt ein.";
			link.l1 = "Verstehe. Und wie heißt du eigentlich?";
			link.l1.go = "ClockTower_Johan_10";
		break;

		case "ClockTower_Johan_10":
			dialog.text = "Johan, Mynheer Kapitän.";
			link.l1 = "Und ich bin "+GetTitle(NPChar, false)+" "+GetFullName(pchar)+". Pass auf dich auf, Soldat.";
			link.l1.go = "ClockTower_Johan_11";
		break;
		
		case "ClockTower_Johan_11":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_1");
		break;
		
		case "ClockTower_Johan_repeat":
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) >= 51)
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
				link.l1 = "Ist etwas passiert?";
				link.l1.go = "ClockTower_Johan_22";
				Notification_ReputationNation(true, 51, HOLLAND);
			}
			else 
			{
				dialog.text = ""+Greeting(true)+", "+GetTitle(NPChar, true)+". Kann ich Ihnen irgendwie helfen?";
				link.l1 = "Nein, "+npchar.name+". Mach weiter.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_repeat";
				Notification_ReputationNation(false, 51, HOLLAND);
			}
		break;

		case "ClockTower_Johan_21":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
			link.l1 = "Ist etwas passiert?";
			link.l1.go = "ClockTower_Johan_22";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_22":
			dialog.text = "Glückwunsch. Sie haben einen Termin.";
			link.l1 = "Termin? Mit wem?";
			link.l1.go = "ClockTower_Johan_23";
		break;

		case "ClockTower_Johan_23":
			dialog.text = "Mit dem Stellvertreter des Mynheer Direktors. Er hat von Eurer Hilfe für die Stadt gehört und mir befohlen, Euch einzuladen.";
			link.l1 = "Was ist mit dem Direktor selbst?";
			link.l1.go = "ClockTower_Johan_24";
		break;

		case "ClockTower_Johan_24":
			dialog.text = "Äh... Ich bin nicht befugt, Euch darüber etwas zu erzählen. Viel Glück da drin, "+GetTitle(NPChar, true)+".";
			link.l1 = "Danke.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower");
		break;
		
		// Диалог с Маартеном Виссером, заместителем директора
		case "ClockTower_Visser_1":
			dialog.text = "Willkommen in der Schiffsregisterabteilung der NWIK. "+UpperFirst(GetTitle(NPChar, false))+"?..";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_2":
			dialog.text = ""+GetFullName(NPChar)+", stellvertretender Direktor.\n"+
						 "Ich habe gehört, dass Ihr Willemstad gute Dienste geleistet habt. Vielleicht kann unser Büro auch Euch von Nutzen sein.";
			link.l1 = "Deshalb bin ich hier.";
			link.l1.go = "ClockTower_Visser_3_1";
			link.l2 = "Ich bin froh, dass ich der Hauptstadt von Curaçao helfen konnte.";
			link.l2.go = "ClockTower_Visser_3_2";
		break;
			
		case "ClockTower_Visser_3_1":
			dialog.text = "Jeder Kapitän — französisch, spanisch, niederländisch — kann bei uns ein Schiffsaudit beauftragen. Wir prüfen Takelung, Kanonen, Takelage. Finden Schwachstellen, geben Empfehlungen.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
		break;

		case "ClockTower_Visser_3_2":
			dialog.text = "Jeder Kapitän — französisch, spanisch, niederländisch — kann bei uns ein Schiffsaudit beauftragen. Wir prüfen Takelung, Kanonen, Takelage. Finden Schwachstellen, geben Empfehlungen.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "ClockTower_Visser_4":
			dialog.text = "Und wenn ein Audit nicht genug ist, können wir auch neue Schiffsdokumente besorgen. Mit anderen Worten, die Arbeit unseres Büros wird Euer Schiff verbessern — ohne wertvolles Mahagoni und Seide zu verschwenden.";
			link.l1 = "Wie ist das möglich?";
			link.l1.go = "ClockTower_Visser_4_1";
		break;

		case "ClockTower_Visser_4_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"? Ihr habt keine Ahnung, wie mächtig der Ort ist, den Ihr betreten habt, und wie viel ein einfacher Federstrich bewirken kann.";
			link.l1 = "Für Dublonen, nehme ich an?";
			link.l1.go = "ClockTower_Visser_5";
		break;

		case "ClockTower_Visser_5":
			dialog.text = "Selbstverständlich. Unsere Dienste sind nicht billig und hängen von der Größe Eures Schiffes ab. Aber sie zahlen sich immer aus. Ein Kapitän, der durch uns gegangen ist, scheitert selten\n"+
						 "Allerdings nehmen wir nicht nur Euer Gold — wir geben Euch auch Gelegenheit, welches zu verdienen. Piraten haben sich so vermehrt, dass selbst in den Kleinen Antillen Kapitäne Geschwader ausrüsten müssen, um diese Plage abzuschrecken. Bringt Beweise für die Vernichtung — und Ihr erhaltet Bezahlung in denselben Dublonen.";
			link.l1 = "Was für Beweise?";
			link.l1.go = "ClockTower_Visser_6";
		break;

		case "ClockTower_Visser_6":
			dialog.text = "Schiffstagebücher. Selbst dieses Gesindel muss irgendwelche Aufzeichnungen führen — sonst kann man nicht mal einen Lugger richtig befehligen. Abgesehen davon, dass Tagebücher ein eindeutiger Beweis für Schandtaten sind, finden sie auch immer einen Platz in unseren Archiven. Nützlich bei Versicherungsstreitigkeiten\n"+
						 "Wenn euch unsere Dienste interessieren, dann ist ein Platz in unserer Kundendatei frei geworden — ein anderer Kapitän hat vor kurzem seine Zusammenarbeit beendet. Führt die Arbeit aus — und der Platz ist euer.";
			link.l1 = "Warum solche Komplexität? Reichen meine Dublonen nicht?";
			link.l1.go = "ClockTower_Visser_7";
		break;

		case "ClockTower_Visser_7":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+", wir arbeiten nach Qualität, nicht nach Quantität. Jeder Kunde unseres Büros erhält den besten Service und die persönliche Aufmerksamkeit des Mynheer Direktors selbst. Und Letzteres kostet, glauben Sie mir, beträchtliches Geld selbst für unsere keineswegs arme Gesellschaft. Da ein Monat nur dreißig Tage hat, können wir uns auch nur dreißig Kunden leisten.";
			link.l1 = "Was muss ich tun?";
			link.l1.go = "ClockTower_Visser_8";
		break;

		case "ClockTower_Visser_8":
			dialog.text = "Bringt fünf Piraten-Schiffstagebücher — das wird Eure Effizienz beweisen. Die Belohnung hängt davon ab, wie gefährlich ihre Besitzer waren.";
			link.l1 = "Gut. Ich werde es tun.";
			link.l1.go = "ClockTower_Visser_9_1";
			link.l2 = "Ich muss darüber nachdenken.";
			link.l2.go = "ClockTower_Visser_9_2";
			link.l3 = "Wo ist der Direktor selbst?";
			link.l3.go = "ClockTower_Visser_9_3";
		break;

		case "ClockTower_Visser_9_1":
			dialog.text = "Ausgezeichnet. Ich erwarte Ergebnisse und hoffe auf Zusammenarbeit.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_2":
			dialog.text = "Wie Ihr wünscht. Das Angebot bleibt bestehen. Aber Euer Platz könnte schneller vergeben werden, als Ihr denkt.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_3":
			dialog.text = "Auf See. Mynheer van Doorn vereint die Leitung des Büros mit dem Kommando über das Flaggschiff.";
			link.l1 = "Wie schafft er das?";
			link.l1.go = "ClockTower_Visser_10";
		break;

		case "ClockTower_Visser_10":
			dialog.text = "Er arbeitet achtzehn Stunden am Tag. Schläft hier, im Büro oben. Sagt, Schlaf sei Zeitverschwendung. Vier Stunden reichen ihm.";
			link.l1 = "Was ist mit dem Lärm dieser riesigen Uhrwerke? Wie kann man hier überhaupt schlafen?";
			link.l1.go = "ClockTower_Visser_11";
		break;

		case "ClockTower_Visser_11":
			dialog.text = "Ihr könnt ihn selbst fragen und vielleicht etwas lernen. Er redet immer gerne mit Kunden. Verstehen wir uns?";
			link.l1 = "Durchaus.";
			link.l1.go = "ClockTower_Visser_12";
			link.l2 = "Nicht ganz...";
			link.l2.go = "ClockTower_Visser_12";
		break;

		case "ClockTower_Visser_12":
			dialog.text = "Einen guten Tag, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;
		   
		case "ClockTower_Visser_13_exit":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_2");
		break;
		
		// Йохан спрашивает про журналы
		case "ClockTower_Johan_31":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! Haben Sie die Logbücher dabei?";
			link.l1 = "Wie ich sehe, bist du gut informiert, Johan.";
			link.l1.go = "ClockTower_Johan_32";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_32":
			if (!CheckAttribute(npchar, "questTemp.ClockTower_Johan_journal"))
			{
				dialog.text = "Ha! Das ist weder der Pier noch das Stadttor, und ich bin nicht irgendein Wachposten, sondern ein Angestellter der Kompanie.";
				npchar.questTemp.ClockTower_Johan_journal = true;
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! Haben Sie die Logbücher dabei?";
			}
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Ich habe die Logbücher gebracht. Lässt du mich durch?";
				link.l1.go = "ClockTower_Johan_33";
			}
			link.l2 = "Ein andermal.";
			link.l2.go = "ClockTower_Johan_34";
		break;

		case "ClockTower_Johan_33":
			dialog.text = "Schön, dass es geklappt hat! Gehen Sie rein, man erwartet Sie.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower_2");
		break;

		case "ClockTower_Johan_34":
			dialog.text = "Einen schönen Tag noch, Mynheer Kapitän.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Johan_32";
		break;
		
		case "ClockTower_Visser_21":
			dialog.text = "Kapitän! Ihr seid zurück. Habt Ihr die Tagebücher?";
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Ja. Alle fünf.";
				link.l1.go = "ClockTower_Visser_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Ein andermal.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Visser_21";
			}
		break;

		case "ClockTower_Visser_22":
			dialog.text = "Ausgezeichnet. Zeigt her.\n"+
						"Ja, alles in Ordnung. Das sind echte Piratenschiffe. Gute Arbeit. Euch stehen #количество_дублонов Dublonen zu.\n"+
						"Bitte, nehmt sie. Und unterschreibt noch hier, bitte.";
			link.l1 = "Also bin ich auf der Liste?";
			link.l1.go = "ClockTower_Visser_23";
			//RemoveItemsFromPCharTotal("ClockTower_PirateJournal", 5);    
		break;

		case "ClockTower_Visser_23":
			dialog.text = "Fast. Zuerst müssen wir die Unterlagen ausfüllen. Das dauert ein paar Minuten.\n"+
						"Vollständiger Name?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_24";
		break;

		case "ClockTower_Visser_24":
			dialog.text = "Staatsangehörigkeit?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_25";
		break;

		case "ClockTower_Visser_25":
			dialog.text = "Name Eures Schiffes?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_26";
		break;

		case "ClockTower_Visser_26":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Schiffstyp?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_27";
		break;

		case "ClockTower_Visser_27":
			dialog.text = "Anzahl der Geschütze?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_28";
		break;

		case "ClockTower_Visser_28":
			dialog.text = "Größe der Besatzung?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_29";
		break;

		case "ClockTower_Visser_29":
			dialog.text = "Gut. Jetzt unterschreibt hier. Und hier. Und hier auch.";
			link.l1 = "Das war's?";
			link.l1.go = "ClockTower_Visser_30";
		break;

		case "ClockTower_Visser_30":
			dialog.text = "Fast. Bleibt nur noch, Euch ins Register einzutragen. Natürlich sollte der Mynheer Direktor Euch zuerst persönlich kennenlernen... Aber das ist eine Formalität — ich bin befugt, neue Kunden anzunehmen.\n"+
					"...Aber ich schweife ab. Erlaubt mir, Euch erneut mit unserer Dienstleistungsliste vertraut zu machen.\n"+
					"Versicherung. Teuer, aber kein Kriegsgeschwader wird Schiffe anrühren, die von der Gesellschaft versichert sind. Ihr könnt so viele Schiffe in Hafenlagern halten, wie Ihr mögt, ohne Angst, sie während einer Koloniebelagerung zu verlieren.\n"+
					"Schiffsaudit — erhöht alle Charakteristiken leicht, ohne strategische Güter auszugeben. Wir überprüfen alles: Takelung, Laderaum, Mannschaftsquartiere. Geben Empfehlungen. Der Preis hängt von der Schiffsgröße ab.\n"+
					"Eintragung in unser Register. Steigert die Sicherheit des Schiffes in der Karibikregion, so dass Kopfgeldjäger, Piraten und Militärs zweimal überlegen, bevor sie Euch angreifen.\n"+
					"Audit und Registereintrag können für ein bestimmtes Schiff nur einmal durchgeführt werden. Also wenn Ihr schon Geld ausgegeben habt, passt auf Euer Schiff auf. Ihr habt keine Ahnung, wie sehr es meine Vorgesetzten irritiert, wenn Kapitäne ihre Schiffe nachlässig behandeln und sie wie Handschuhe wechseln!\n"+
					"Aber ich schweife wieder ab. Nun zu den wiederholbaren Dienstleistungen...\n"+
					"Dokumentenwechsel. Ihr wisst, dass Schiffe unterschiedliche Spezialisierungen haben können. Aber Ihr ahnt nicht einmal, dass dies in erster Linie davon abhängt, wie das Schiff dokumentiert ist. Wenn es Euch nicht gefällt, dass Euer Kriegsschiff für Festungsbelagerungen dokumentiert ist, wisst Ihr, an wen Ihr Euch wenden müsst.\n"+
					"Nun, von den Belohnungen für die Abgabe von Piraten-Schiffstagebüchern habt Ihr schon gehört... Je gefährlicher der Pirat, desto mehr zahlen wir für sein Tagebuch.";
			link.l1 = "Beeindruckend. Ich muss sagen, Mynheer Visser, Euer Büro ist wirklich...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor");
		break;

		case "ClockTower_Visser_31":
			dialog.text = "'"+GetShipName("Amsterdam")+"' im Hafen! Der Mynheer Direktor ist zurück!";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_31_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
			ClockTower_AmsterdamInTheHarbor_2();
		break;

		case "ClockTower_Visser_31_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_32", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_32":
			dialog.text = "Was?! Schon?! Aber er sollte erst in drei Tagen zurückkommen!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_32_add";
		break;

		case "ClockTower_Visser_32_add":
			StartInstantDialog("ClockTower_Johan_clone", "ClockTower_Visser_33", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_33":
			dialog.text = "Der Mynheer Direktor ist bereits an Land! Er kommt direkt hierher!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_33_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
		break;

		case "ClockTower_Visser_33_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_34", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_34":
			dialog.text = "Mein Gott... Wenn er Euch sieht...";
			link.l1 = "Welches Problem gibt es denn? Habt Ihr doch gerade gesagt, dass Ihr befugt seid, neue Kunden anzunehmen.";
			link.l1.go = "ClockTower_Visser_35";
		break;

		case "ClockTower_Visser_35":
			dialog.text = "Habe ich! Aber er mag es nicht, wenn... Egal. Kapitän, wartet draußen. Am Eingang. Der Mynheer Direktor wird mit Euch sprechen wollen.";
			link.l1 = "Mit mir?";
			link.l1.go = "ClockTower_Visser_36";
		break;

		case "ClockTower_Visser_36":
			dialog.text = "Er überprüft persönlich jeden neuen Kunden. Immer. Geht, schnell!";
			link.l1 = "Die Dublonen für die Tagebücher gebe ich nicht zurück!";
			link.l1.go = "ClockTower_Visser_36_1";
			link.l2 = "Schade, ich wäre gerne geblieben und hätte zugehört.";
			link.l2.go = "ClockTower_Visser_36_2";
		break;

		case "ClockTower_Visser_36_1":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;

		case "ClockTower_Visser_36_2":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		// диалог с Йоханом, после того как мы вышли из башни
		case "ClockTower_Johan_41":
			dialog.text = "...";
			link.l1 = "Was war das, Johan?";
			link.l1.go = "ClockTower_Johan_42";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_42":
			dialog.text = "Der Mynheer Direktor ist zurück.";
			link.l1 = "Was ist daran so schrecklich?";
			link.l1.go = "ClockTower_Johan_43";
		break;

		case "ClockTower_Johan_43":
			dialog.text = "Gar nichts Schreckliches! Nur... Der Mynheer Direktor mag keine Überraschungen. Alles muss nach Plan laufen. Und hier ist ein neuer Kunde, den er noch nicht überprüft hat.";
			link.l1 = "Maarten sagte, er habe die Befugnis, mich ins Register einzutragen.";
			link.l1.go = "ClockTower_Johan_44";
		break;

		case "ClockTower_Johan_44":
			dialog.text = "Nein, darum geht's nicht. Der Mynheer Direktor will einfach... nun, er will alles selbst kontrollieren. Jede Kleinigkeit. Sagt, sonst fällt alles auseinander. Ihr werdet sehen, jetzt fängt er wieder an, sich um seine Uhr zu sorgen.";
			link.l1 = "Was?";
			link.l1.go = "ClockTower_Johan_45";
		break;

		case "ClockTower_Johan_45":
			dialog.text = "Mynheer van Doorn hält, wenn er gereizt ist, die Uhr an und fängt an, daran herumzubasteln. Manchmal bleibt die Stadt einen halben Tag ohne Zeit. Und das passiert...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_45_1";
		break;

		case "ClockTower_Johan_45_1":
			dialog.text = "Oh... Hört Ihr das? Es hat angefangen.";
			link.l1 = "Der Chef ist zurück. Alles wie immer.";
			link.l1.go = "ClockTower_Johan_46_1";
			link.l2 = "Und wie ich das höre. Sie machen Maarten gerade zur Schnecke.";
			link.l2.go = "ClockTower_Johan_46_2";
			iClockSP4PseudoGlobal = ClockTower_PlaySound_rh2("Location/SP4_quest2");
		break;

		case "ClockTower_Johan_46_1":
			dialog.text = "Leider ist es inzwischen üblich geworden.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_46_2":
			dialog.text = "Das solltet Ihr nicht sagen. Das ist alles ungerecht, wenn Ihr mich fragt.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";	
			ChangeCharacterComplexReputation(pchar, "nobility", -2);

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_47":
			dialog.text = "Scheint sich beruhigt zu haben. Sie werden Euch gleich reinbitten.";
			link.l1 = "Bekomme ich Ärger?";
			link.l1.go = "ClockTower_Johan_48";
		break;

		case "ClockTower_Johan_48":
			dialog.text = "Keine Sorge. Ihr habt doch nichts Schlimmes getan.";
			link.l1 = "Das beruhigt mich.";
			link.l1.go = "ClockTower_Johan_49";
		break;

		case "ClockTower_Johan_49":
			dialog.text = "Ach kommt! Der Mynheer Direktor kann manchmal übermäßig streng sein... Aber er ist großzügig und höflich... Oh, hab ich's nicht gesagt!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_50";
		break;

		case "ClockTower_Johan_50":
			dialog.text = "Oh, hab ich's nicht gesagt!";
			link.l1 = "...";
			link.l1.go = "exit";
			ClockTower_VisserComingTowardsUs();
		break;

		case "ClockTower_Visser_37":
			dialog.text = "Der Mynheer Direktor wartet drinnen auf Euch.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VisserComingTowardsUs_2");
			DelLandQuestMark(npchar);
		break;
		
		// Первое знакомство с ван Дорном
		case "ClockTower_VanDoorn_1":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". Euer Schiff — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" Geschütze und "+GetMaxCrewQuantity(pchar)+" Besatzung.";
			link.l1 = "Alles korrekt.";
			link.l1.go = "ClockTower_VanDoorn_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_VanDoorn_2":
			shipType = XI_ConvertString(GetShipTypeName(npchar));
			dialog.text = "Es ist ungerecht, dass ich alles über Euch weiß, während Ihr nichts über mich wisst außer Johans Klatsch. Hendrik van Doorn. Leiter der Registerabteilung der Niederländischen Westindien-Kompanie in der Karibik. Kommandant der Fregatte Amsterdam. "+shipType+". "+GetCannonQuantity(npchar)+" Geschütze und "+GetMaxCrewQuantity(npchar)+" Besatzung.";
			link.l1 = "Angenehm, Euch kennenzulernen.";
			link.l1.go = "ClockTower_VanDoorn_3";
		break;

		case "ClockTower_VanDoorn_3":
			dialog.text = "Ihr habt fünf Piraten-Schiffstagebücher besorgt. Mein Stellvertreter schätzte Euch hoch ein, trug Euch ins Kundenregister ein und machte Euch mit den Diensten meines Büros vertraut\n"+
						"Aber die endgültige Entscheidung über die Zulassung treffe immer ich. Persönlich. Nach einem Gespräch. Maarten konnte einen Kandidaten vorschlagen — nicht mehr.";
			link.l1 = "Dann lasst uns beginnen.";
			link.l1.go = "ClockTower_VanDoorn_4";
		break;

		case "ClockTower_VanDoorn_4":
			if (!CheckAttribute(npchar, "ClockTower_option"))
			{
				dialog.text = "Ich brauche Kapitäne, die Piraten effektiv bekämpfen und dabei kommerziell erfolgreich genug sind, um sich unsere Dienste leisten zu können. Entsprecht Ihr diesen Kriterien?";
			}
			else dialog.text = "";
			if (!CheckAttribute(npchar, "ClockTower_option_1") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				link.l1 = "Ich habe Mortimer Grimm vernichtet. Kapitän der Brigg Memento.";
				link.l1.go = "ClockTower_VanDoorn_option_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_2") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				link.l2 = "Ich glaube, Eure Gesellschaft hat meinen Sieg über Albert Blackwood hoch geschätzt. Die Schaluppe Lady Beth war ein ernsthafter Gegner.";
				link.l2.go = "ClockTower_VanDoorn_option_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_3") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				link.l3 = "Fernando de Alamida war kein Pirat, aber...";
				link.l3.go = "ClockTower_VanDoorn_option_3";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_4") && CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l4 = "Ich habe den Schrecken aller Segelfahrer besiegt. Das müsst Ihr wissen.";
				link.l4.go = "ClockTower_VanDoorn_option_4";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_5") && GetCharacterShipClass(PChar) <= 3)
			{
				link.l5 = "Ihr habt gerade mein Schiff ins Register eingetragen. Glaubt Ihr, ein inkompetenter Kapitän könnte es unterhalten?";
				link.l5.go = "ClockTower_VanDoorn_option_5";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_6") && sti(pchar.Money) >= 1000000)
			{
				link.l6 = "Ich komme gut zurecht, und Geld wächst in der Karibik auf Bäumen.";
				link.l6.go = "ClockTower_VanDoorn_option_6";
			}
			link.l7 = "Mynheer Visser hat bereits meine Kompetenz überprüft. Reicht Euch die Einschätzung Eures eigenen Stellvertreters nicht?";
			link.l7.go = "ClockTower_VanDoorn_5";
			npchar.ClockTower_option = true;
		break;

		case "ClockTower_VanDoorn_option_1":
			dialog.text = "Grimm? Unsere Organisation hatte nie Beschwerden über Grimm, ganz im Gegenteil. Aber derjenige, der seinen Platz einnahm... Ich weiß, wer er war und zu welchem Zweck er ursprünglich in die Karibik kam. Solche Schandtaten verjähren nicht, und ich bin froh, dass Ihr den Verbrecher und wahren Feind meines Landes bestraft habt.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_1 = true;
		break;

		case "ClockTower_VanDoorn_option_2":
			dialog.text = "Wenn ich mich an den Bericht über den Vorfall auf den Kaimanen richtig erinnere, hattet Ihr keine Gelegenheit, das zu überprüfen. Meiner Ansicht nach ist die Situation nicht ganz eindeutig, aber Euer Sieg war zweifellos kompetent.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_2 = true;
		break;

		case "ClockTower_VanDoorn_option_3":
			dialog.text = "Aber er hätte etwas viel Schlimmeres werden können, ja. Ein würdiger Feind, obwohl er nicht gegen Euch verlor, sondern gegen seine undankbaren Vorgesetzten. Ich bin Holländer, also weiß ich, wovon ich rede, wenn es um den Krieg mit Kastilien geht.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_3 = true;
		break;

		case "ClockTower_VanDoorn_option_4":
			dialog.text = "'"+GetShipName("Flying Heart")+"'. Es erstaunt mich immer noch, dass ehrliche Leute nicht davonlaufen, wenn sie dieses Ungetüm in den Hafen einlaufen sehen. Vieles an dieser Geschichte überrascht mich, Kapitän. Aber eines Tages wird sie ihren Platz in unseren Büchern finden und all ihren Charme verlieren. Und Ihr... Ihr habt Euch unsterblich gemacht.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_4 = true;
		break;

		case "ClockTower_VanDoorn_option_5":
			dialog.text = "Ihr würdet Euch wundern. Aber in Eurem Fall gibt es keine Zweifel, das stimmt.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_5 = true;
		break;

		case "ClockTower_VanDoorn_option_6":
			dialog.text = "Und deshalb nichts wert sind. Es sei denn, es sind Dublonen, natürlich.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_6 = true;
		break;

		case "ClockTower_VanDoorn_5":
			dialog.text = "\nIhr seid zu den Diensten des Büros zugelassen. Willkommen im Kundenregister der angesehenen Niederländischen Westindien-Kompanie.";
			link.l1 = "Danke.";
			link.l1.go = "ClockTower_VanDoorn_6";
		break;

		case "ClockTower_VanDoorn_6":
			dialog.text = "Das ist eine für beide Seiten vorteilhafte Zusammenarbeit. Ihr erhaltet Zugang zu den besten Diensten in der Karibik. Wir bekommen einen zuverlässigen Partner.";
			link.l1 = "Gut.";
			link.l1.go = "ClockTower_VanDoorn_7";
		break;

		case "ClockTower_VanDoorn_7":
			dialog.text = "Wartet! Hört Ihr das?";
			link.l1 = "Ich höre nichts.";
			link.l1.go = "ClockTower_VanDoorn_8";
			// sound stops
			i = FindSoundEventId("Location/clocks_mechanism_inside");
			SetSoundEventPauseState(i, true);
			DelEventHandler("NextHour", "Villemstad_BigClock_Above");
		break;

		case "ClockTower_VanDoorn_8":
			dialog.text = "Genau das ist der Punkt! Kaum war ich eine Woche weg...";
			link.l1 = "Stimmt etwas nicht?";
			link.l1.go = "ClockTower_VanDoorn_9";
		break;

		case "ClockTower_VanDoorn_9":
			dialog.text = "Mit der Uhr. Muss den Mechanismus überprüfen. Entschuldigung. Das... ist wichtig.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
		break;

		case "ClockTower_VanDoorn_10":
			if (!CheckAttribute(npchar, "ClockTower_question"))
			{
				dialog.text = "Scheint alles in Ordnung zu sein. Nochmals meine Entschuldigung. Habt Ihr Fragen?";
				LAi_Fade("", "");
				// sound returns
				i = FindSoundEventId("Location/clocks_mechanism_inside");
				SetSoundEventPauseState(i, false);
				SetEventHandler("NextHour", "Villemstad_BigClock_Above", 0);
			}
			else dialog.text = "Noch Fragen?";
			if (!CheckAttribute(npchar, "ClockTower_question_1"))
			{
				link.l1 = "Euer Stellvertreter hat die Dienste des Büros ausführlich erklärt. Wie ist das alles überhaupt möglich?";
				link.l1.go = "ClockTower_VanDoorn_question_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_2"))
			{
				link.l2 = "Wie vereint Ihr zwei Positionen? Kapitän und Direktor?";
				link.l2.go = "ClockTower_VanDoorn_question_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_3"))
			{
				link.l3 = "Wie arbeitet Ihr unter solchen Bedingungen? Der Lärm der Uhrwerke, die Dunkelheit und die mit schweren Vorhängen verhängten Fenster.";
				link.l3.go = "ClockTower_VanDoorn_question_3";
			}
			link.l4 = "Nein, danke für Eure Zeit. Was ist mit den Diensten des Büros?";
			link.l4.go = "ClockTower_VanDoorn_11";
			npchar.ClockTower_question = true;
		break;

		case "ClockTower_VanDoorn_question_1":
			dialog.text = "Hier gibt es keine Hexerei, "+GetTitle(NPChar, false)+". Feder und Tinte regieren die Welt. Die Kirche verzeichnet Geburt, Taufe, Heirat und Tod eines Menschen. Ändere auch nur eine Zeile — und sein Schicksal ändert sich. Ein Schiff ist etwas komplexer, aber auch in seinem Fall ändert ein Federstrich vieles. Ich verhehle nicht, dass ich stolz bin auf das, was ich erreicht habe. Und dennoch weiß ich, dass es besser sein könnte. Was wäre, wenn wir in die Bücher nicht nur Schiffe und Menschen eintragen würden, sondern eine ganze Welt?";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_1 = true;
		break;

		case "ClockTower_VanDoorn_question_2":
			dialog.text = "Weil es jemand tun muss. Der vorherige Kapitän der Amsterdam starb im Kampf gegen eine Gruppe von Antigua. Die Gesellschaft fand keinen würdigen Ersatz. Ich bot mich an. Absolvierte die Ausbildung. Bestand die Prüfungen. Erhielt ein Patent\n"+
			"Ja, ich bin ein schlechter Kapitän. Viel schlechter als Ihr — das ist sicher. Aber ein guter Manager kann alles leiten, nicht nur ein Schiff. Es ist schwierig zu lernen, drei Menschen zu befehligen. Aber wenn man es gelernt hat, kann man auch dreitausend befehligen. Ein Büro, ein Schiff, eine Stadt oder sogar eine riesige Gesellschaft — es gibt keine Grenzen, solange man talentierte Leute findet und ihnen vertraut, einen zu vertreten... Letzteres ist das Schwierigste. Ein wahrer Fluch.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_2 = true;
		break;

		case "ClockTower_VanDoorn_question_3":
			dialog.text = "Und es gibt kaum Luft zum Atmen. "+UpperFirst(GetTitle(NPChar, false))+", der Mensch formt seine eigene Umgebung. Hier lenkt mich nichts und niemand ab, alles ist griffbereit und nur mir und der Zeit unterworfen. Wenn ich könnte, würde ich mit der Außenwelt nur über Papier kommunizieren. Leider ist das unmöglich. Und nehmt es nicht persönlich, "+GetTitle(NPChar, false)+". Besser allein zu sein, aber nicht einsam. Wenn Ihr versteht, was ich meine.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_3 = true;
		break;

		case "ClockTower_VanDoorn_11":
			// pchar.quest.ClockTower.date = rand(27)+1;
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Wir empfangen nur nach Terminvereinbarung. Ihr seid für... "+pchar.quest.ClockTower.date+" "+month+" vorgemerkt. Wenn Ihr am vorgesehenen Tag nicht kommt, ist das kein Problem. Wendet Euch an Johan, und er wird Euch den nächsten verfügbaren Termin mitteilen.";
			link.l1 = "Warum diese Umstände?";
			link.l1.go = "ClockTower_VanDoorn_12";
		break;

		case "ClockTower_VanDoorn_12":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Unsere Arbeit ist teuer, weil wir wahre Wunder vollbringen und unseren Kunden großen Nutzen bringen. Interessenkonflikte sind unmöglich, daher widmen wir einen ganzen Arbeitstag den Bedürfnissen einer bestimmten Person. Euer nächster verfügbarer Tag: "+pchar.quest.ClockTower.date+" "+month+"\n"+
			"Wenn Ihr Visser seht... Maarten handelte richtig, als er Eure Kandidatur vorschlug. Sagt ihm das. Er ist ein guter Stellvertreter. Er soll nicht zweifeln.";
			link.l1 = "Gut.";
			link.l1.go = "ClockTower_VanDoorn_13";
		break;

		case "ClockTower_VanDoorn_13":
			dialog.text = "Einen guten Tag noch, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VanDoornInCabinet_3");
		break;
		
		case "ClockTower_Visser_41":
			dialog.text = "Wie ist es gelaufen?";
			link.l1 = "Es war ein langer Tag, aber van Doorn hat Ihre Entscheidung bestätigt.";
			link.l1.go = "ClockTower_Visser_42";
		break;

		case "ClockTower_Visser_42":
			dialog.text = "Gott sei Dank. Also habe ich alles richtig gemacht.";
			link.l1 = "Er ließ mir ausrichten, dass Sie ein guter Stellvertreter sind.";
			link.l1.go = "ClockTower_Visser_43";
		break;

		case "ClockTower_Visser_43":
			dialog.text = "Wirklich? Er... hat das gesagt?";
			link.l1 = "Ja. Das hat er gesagt.";
			link.l1.go = "ClockTower_Visser_44";
		break;

		case "ClockTower_Visser_44":
			dialog.text = "Verdammt. Das hätte er besser nicht sagen sollen. Jetzt werde ich mich wie ein undankbares Schwein fühlen. Oder hat er das vorausgesehen und alles eingeplant?";
			link.l1 = "Mynheer Stellvertreter, Sie haben plötzlich aufgehört, Sie selbst zu sein.";
			link.l1.go = "ClockTower_Visser_45";
		break;

		case "ClockTower_Visser_45":
			dialog.text = "Kapitän, ich bin ein Geschäftsmann, und Sie auch, also werde ich nicht um den heißen Brei herumreden.\n"+
						 "Der Mynheer Direktor arbeitet schon lange nicht mehr für uns.";
			link.l1 = "Was, pardon?!";
			link.l1.go = "ClockTower_Visser_46";
		break;

		case "ClockTower_Visser_46":
			dialog.text = "Er kam mit einem Vertrag hierher, der ein einziges Ziel hatte — die Arbeit der Schiffsregistrierungsabteilung aufzubauen. Er hat es brillant gemeistert, seinen Nachfolger ausgebildet, mich befördert... und das war's.";
			link.l1 = "Was, das war's?";
			link.l1.go = "ClockTower_Visser_47";
		break;

		case "ClockTower_Visser_47":
			dialog.text = "Sein Vertrag ist schon lange abgelaufen. Wir wissen nicht genau wann, aber wir sind absolut sicher, dass dieser Mann kein Recht mehr hat, seine Position zu behalten.";
			link.l1 = "Verstanden. Die hohen Tiere im Zentralflügel dieses Gebäudes werden nervös.";
			link.l1.go = "ClockTower_Visser_48_1";
			link.l2 = "Verstanden. Sie sind es leid zu warten, bis er seinen Sessel für Sie räumt.";
			link.l2.go = "ClockTower_Visser_48_2";
		break;

		case "ClockTower_Visser_48_1":
			dialog.text = "Genau! Und sie können nichts dagegen tun!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_48_2":
			dialog.text = "Ich will nicht lügen. Ich bin wirklich müde. Verdammt noch mal, van Doorn beförderte mich speziell dazu, ihn zu ersetzen, wenn der Vertrag abläuft!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_49":
			dialog.text = "Dennoch würde ich niemals an diesem verdammten Sessel rütteln, nur weil ich mich betrogen fühle! Gott weiß, ich bin dankbar und bewundere diesen Mann!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_50";
		break;

		case "ClockTower_Visser_50":
			dialog.text = "Nein, Mynheer. Van Doorn möchte unsere gemeinsamen Vorgesetzten loswerden. Diejenigen, die hinter der Turmmauer sitzen — im Zentralflügel dieses Gebäudes! Doch selbst sie können ihn nicht unter Kontrolle bringen!";
			link.l1 = "Was ist daran so schwierig? Van Doorn ist kaum wichtiger als Stuyvesant.";
			link.l1.go = "ClockTower_Visser_51";
		break;

		case "ClockTower_Visser_51":
			dialog.text = "Dies ist weder ein Schiff noch ein Königshof, Kapitän. Unsere Kompanie ist eine völlig neue Art von Organisation. Man kann nicht einfach mit dem Finger auf jemanden zeigen und einen so wertvollen Menschen entlassen.\n"+
						 "Erstens weiß niemand, wo das Original von van Doorns Vertrag ist. Ergo gibt es keine Grundlage für eine Entlassung. Versuchten wir das, würde er eine Horde Rechtsanwälte losschicken, und wir würden ihm am Ende noch etwas schulden.\n"+
						 "Zweitens hat die Führung einen Fehler gemacht, als sie van Doorn das Patent für die Amsterdam erteilte. Er mag ein schwacher Kapitän sein, aber die Mannschaft, die er zusammenstellte, ist die beste der ganzen Region. Ein einziger Befehl, und die Elite-Soldaten der Kompanie würden dieses Gebäude ohne mit der Wimper zu zucken besetzen.\n"+
						 "Drittens vergöttert ihn seine Frau. Es ist egal, dass er sie seit Jahren nicht gesehen hat. De Witts eigene Tochter ist zu vielem bereit für ihren geliebten Ehemann. Und der Rat der Siebzehn muss sich damit abfinden.\n"+
						 "In Kurzfassung: Für Ihre Hilfe wird das Direktorat sehr großzügig zahlen. Und Ihre Privilegien bei der Schiffsregistrierungsstelle bleiben erhalten.";
			link.l1 = "Beeindruckend. Sie sind wirklich ein Geschäftsmann, Maarten. Sie verkaufen mir Verrat mit der gleichen Professionalität, mit der Sie kürzlich die Dienstleistungen Ihrer Stelle verkauften.";
			link.l1.go = "ClockTower_Visser_57";
		break;

		case "ClockTower_Visser_57":
			dialog.text = "Es ist nicht schwer, wenn van Doorn dir selbst die Kunst der Verhandlung beigebracht hat und du aufrichtig an das glaubst, was du sagst.";
			link.l1 = "Also, was wollen Sie von mir?";
			link.l1.go = "ClockTower_Visser_58";
		break;

		case "ClockTower_Visser_58":
			dialog.text = "Etwas, das nur ein Außenstehender tun kann. Dringen Sie nachts in die Stelle ein und finden Sie dort das Original von van Doorns Vertrag. Ich werde dafür sorgen, dass die Türen offen sind.";
			link.l1 = "Warum machen Sie es nicht selbst? Und was hindert mich daran, jetzt sofort zu gehen und Ihrem Vorgesetzten alles zu erzählen?";
			link.l1.go = "ClockTower_Visser_59";
		break;

		case "ClockTower_Visser_59":
			dialog.text = "Weil van Doorn die Gewohnheit hat, nachts jeden zu empfangen außer Angestellten der Kompanie. Niemand wird sich wundern, wenn er Sie zu ungewöhnlicher Stunde aus diesem Turm kommen sieht.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_60";
		break;

		case "ClockTower_Visser_60":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Was Ihre Drohung betrifft... Sie kommen jetzt nicht zum Direktor, da Sie einen anderen Tag vereinbart haben. "+pchar.quest.ClockTower.date+" "+month+", richtig? Bis dahin wird die Dringlichkeit der Neuigkeiten etwas nachgelassen haben. Darüber hinaus belohnt der Direktor niemals Denunzianten. Und schützt immer seine Mitarbeiter.";
			link.l1 = "Bequem für Sie.";
			link.l1.go = "ClockTower_Visser_61";
		break;

		case "ClockTower_Visser_61":
			dialog.text = "Das ist kein Verrat, Kapitän. Wir möchten einfach den Vertrag einhalten und die Kompanie schützen. Auch Willemstad, dem Sie übrigens so sehr geholfen haben.";
			link.l1 = "Ich werde darüber nachdenken. Aber ich verspreche nichts.";
			link.l1.go = "ClockTower_Visser_62";
		break;

		case "ClockTower_Visser_62":
			dialog.text = "Mehr verlange ich nicht von Ihnen, Kapitän. In erster Linie sind Sie unser Kunde. Wie es auch ausgehen mag, ich bin sehr stolz darauf, dass gerade ich Sie gefunden und in das Register der Stelle eingetragen habe.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_63";
		break;

		case "ClockTower_Visser_63":
			dialog.text = "Sie können mich jederzeit im Zentralflügel finden. Einen guten Tag noch.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Quest_3");
		break;
		
		case "ClockTower_Visser_64":
			dialog.text = "Guten Tag, "+GetTitle(NPChar, false)+". Gibt es Neuigkeiten?";
			link.l1 = "Noch nichts.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_64";
		break;
		
		case "ClockTower_Johan_51":
			if (GetHour() >= 6 && GetHour() < 24)
			{
				if (pchar.quest.ClockTower.date <= GetDataDay())
				{
					NextMonth = GetDataMonth() + 1;
					if (NextMonth == 13) NextMonth = 1;
				}
				else NextMonth = GetDataMonth();
				Month = XI_ConvertString("MonthGen_" + NextMonth);
				if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", heute ist Ihr Tag. Bitte, gehen Sie rein.";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
						
						ClockTower_RightDay();
					}
					else
					{
						dialog.text = "Guten Tag, "+GetTitle(NPChar, false)+"!";
					}
				}
				else
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", man erwartet Sie an einem anderen Tag. Wir freuen uns, Sie zu sehen: "+pchar.quest.ClockTower.date+" "+month+".";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					}
					else
					{
						dialog.text = "Guten Tag, "+GetTitle(NPChar, false)+"!";
					}
				}
				link.l1 = "Danke, Johan.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_51";
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeatnight"))
				{	// первая ночная встреча с Йоханом
					dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", Sie kommen etwas spät. Die Stelle ist geschlossen.";
					link.l1 = "Hallo, "+npchar.name+". Ich habe gehört, sie arbeitet auch nachts.";
					link.l1.go = "ClockTower_Johan_52";
					npchar.ClockTower_repeatnight = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = ""+TimeGreeting()+", "+GetTitle(NPChar, false)+"!";
					link.l1 = "";
					link.l1.go = "ClockTower_Johan_53";
				}
			}
		break;
		
		case "ClockTower_Johan_52":
			dialog.text = "Das stimmt. Alle möglichen Leute kommen vorbei. Sogar Priester schauen manchmal rein, hehe. Aber sie alle müssen erst an mir vorbei. Und bezüglich Ihnen habe ich keine Anweisungen erhalten.";
			link.l1 = "Warte mal, stehst du hier rund um die Uhr auf Posten? Wie ist das möglich?";
			link.l1.go = "ClockTower_Johan_53";
		break;

		case "ClockTower_Johan_53":
			if (!CheckAttribute(npchar, "ClockTower_repeatnight_2"))
			{
				dialog.text = "Ja. Der Mynheer Direktor hat es gerade so angeordnet. Wie er das schafft, weiß ich nicht, aber ich habe trotzdem genug Zeit für Ruhe und Dienst. Und sie haben meinen Sold erhöht — da kann man nicht meckern!";
				npchar.ClockTower_repeatnight_2 = true;
			}
			else
			{
				dialog.text = "Noch etwas?";
			}
			if (!CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
			{
				link.l1 = "Du solltest mich durchlassen. Ich arbeite für die oberste Führung der Kompanie.";
				link.l1.go = "ClockTower_Johan_54";
				link.l2 = "(Ihn töten)";
				link.l2.go = "ClockTower_Johan_KillHim";
			}
			link.l3 = "Weiter so, Soldat.";
			link.l3.go = "ClockTower_Johan_NightExit";
		break;

		case "ClockTower_Johan_KillHim":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_KillToJohan");
		break;

		case "ClockTower_Johan_NightExit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_Johan_51";
		break;

		case "ClockTower_Johan_54":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				dialog.text = "Äh. Was wollen Sie von mir, Mynheer Kapitän? Ich bin nur ein einfacher Soldat, ich weiß nichts.";
				link.l1 = "Du weißt alles, Johan. Sei nicht so bescheiden. Die Herren in den hohen Büros müssen dir vielleicht keine Rechenschaft ablegen, aber von der schwarzen Katze zwischen ihnen hast du sicher gehört.";
				link.l1.go = "ClockTower_Johan_55";
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
			}
			else
			{
				dialog.text = "Ich bin ein kleiner Mann, aber über den Kopf meines direkten Vorgesetzten hinweg werde ich nicht springen. Entschuldigen Sie, Mynheer Kapitän.";
				link.l1 = "Wir werden auf dieses Gespräch zurückkommen.";
				link.l1.go = "ClockTower_Johan_NightExit";
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
			}
		break;

		case "ClockTower_Johan_55":
			Achievment_Set("ach_CL_197");
			dialog.text = "Das stimmt, Mynheer Kapitän. Der Mynheer Direktor hat zu lange gesessen. Ein Sturm zieht auf.";
			link.l1 = "Was hast du gehört?";
			link.l1.go = "ClockTower_Johan_56";
		break;

		case "ClockTower_Johan_56":
			dialog.text = "Alle fürchten, dass er wenn nicht heute, dann morgen die Macht ergreift. Er ist zu groß für unser Provinznest. Er erstickt alle mit seinen Kontrollen, lässt jede Unterschrift durch sich laufen.\nIch sag's Ihnen ehrlich, und Sie haben es selbst gesehen: Jedes Mal, wenn die Amsterdam in den Hafen einläuft — steigt sofort eine böse Unruhe auf.";
			link.l1 = "Ich kann das lösen, aber dafür musst du mich durchlassen.";
			link.l1.go = "ClockTower_Johan_57";
		break;

		case "ClockTower_Johan_57":
			dialog.text = "Gehen Sie rein, Mynheer Kapitän. Nur bitte ich Sie, richten Sie mich nicht zugrunde: Wenn der Mynheer Direktor davon erfährt, kostet es mich den Kopf, und ich muss eine Familie ernähren.";
			link.l1 = "Ich werde mein Bestes tun.";
			link.l1.go = "ClockTower_Johan_58_hint";
		break;

		case "ClockTower_Johan_58_hint":
			ClockTower_AddBook();
			dialog.text = "Sie sind ein guter Mann, Mynheer Kapitän. Vielleicht kann ich Ihnen helfen: Ich weiß, dass der Mynheer Direktor in einem der Bücher einen Schlüssel aufbewahrt. Wofür er ist — weiß ich nicht, aber vielleicht ist er nützlich.";
			link.l1 = "Danke, Johan.";
			link.l1.go = "ClockTower_Johan_NightSuccess";
		break;
		
		case "ClockTower_Johan_NightSuccess":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_NightFree");
			NextDiag.CurrentNode = "ClockTower_Johan_51";
			// if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
		break;
		
		case "ClockTower_Peter_50":
			dialog.text = "Halt. Sie befinden sich auf dem Gelände der Niederländischen Westindien-Kompanie. Abteilung für Schiffsregistrierung und Archiv. Eintritt nur mit Termin.";
			link.l1 = "Ich bin "+GetTitle(NPChar, false)+" "+pchar.name+".";
			link.l1.go = "ClockTower_Peter_51";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_51":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Sie haben einen Termin? Gehen Sie rein.";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					
					ClockTower_RightDay();
				}
				else
				{
					dialog.text = "...";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Ihr Termin ist für einen anderen Tag angesetzt: "+pchar.quest.ClockTower.date+" "+month+".";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = "...";
				}
			}
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Peter_51";
		break;
		
		case "ClockTower_Visser_71":
			dialog.text = "Guten Tag, "+GetTitle(NPChar, false)+". Gibt es Neuigkeiten?";
			link.l1 = "Ja. Hier ist der Vertrag.";
			link.l1.go = "ClockTower_Visser_72";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_72":
			dialog.text = "Unglaublich... Er ist vor sieben Jahren abgelaufen!";
			link.l1 = "Also ist das, was Sie brauchten?";
			link.l1.go = "ClockTower_Visser_73";
		break;

		case "ClockTower_Visser_73":
			dialog.text = "Genau! Mit diesem Dokument kann die Kompanie ihn rechtmäßig abberufen. Keine Schlupflöcher. Keine Ausreden. Die Zeit ist abgelaufen — Punkt.";
			link.l1 = "Was kommt als Nächstes?";
			link.l1.go = "ClockTower_Visser_74";
		break;

		case "ClockTower_Visser_74":
			dialog.text = "Ich schicke den Vertrag nach Amsterdam. Der Rat der Siebzehn wird eine Entscheidung treffen. Doorn wird befohlen, zurückzukehren. Er wird nicht ablehnen können.";
			link.l1 = "Was, wenn er es doch tut?";
			link.l1.go = "ClockTower_Visser_75";
		break;

		case "ClockTower_Visser_75":
			dialog.text = "Er kann nicht. Seine Frau mag die Tochter eines Anteilseigners sein, des Großen Ratspensionärs, aber selbst ihr Vater wird sich nicht gegen den Rat stellen. Und Catharina selbst... Sie wartet seit zehn Jahren. Wenn sie erfährt, dass er zurückkehren kann, aber ablehnt — wird es sie umbringen.";
			link.l1 = "Grausam.";
			link.l1.go = "ClockTower_Visser_76";
		break;

		case "ClockTower_Visser_76":
			dialog.text = "Ja. Aber das ist der einzige Weg. Danke, Kapitän. Sie haben wichtige Arbeit geleistet.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_77";
		break;

		case "ClockTower_Visser_77":
			if (CharacterIsAlive("ClockTower_Johan"))
			{
				dialog.text = "Ihre Belohnung — fünfhundert Dublonen. Und ich gebe Ihnen mein Wort: In zwei bis drei Monaten, wenn ich den Stuhl des Direktors übernehme, erhalten Sie unbegrenzten Zugang zu den Dienstleistungen der Stelle. Keine Warteschlangen. Keine Termine. Jederzeit.";
				AddItems(pchar, "gold_dublon", 500);
			}
			else
			{
				dialog.text = "Und Sie haben Johan getötet. Ich habe bereits einen Mann verraten, den ich bewundere und dem ich alles verdanke. Nun auch noch das.\n"+
							 "Vielleicht sind Menschen auf Ihrem Schiff wie Brennholz, aber die Kompanie schätzt ihre Mitarbeiter. Und es ekelt mich, Komplize eines Mordes zu sein.\n"+
							 "Ihre Dublonen gehen an Johans Familie, aber den zweiten Teil des Deals werde ich erfüllen.\n"+
							 "Ich gebe Ihnen mein Wort: In zwei bis drei Monaten, wenn ich den Stuhl des Direktors übernehme, erhalten Sie unbegrenzten Zugang zu den Dienstleistungen der Stelle.";
			}
			link.l1 = "Ich verlasse mich auf Ihr Wort. Einen guten Tag noch.";
			link.l1.go = "ClockTower_Visser_78";
		break;

		case "ClockTower_Visser_78":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_WaitFewMonths");
		break;

		case "ClockTower_Visser_79":
			dialog.text = "Guten Tag, "+GetTitle(NPChar, false)+". Noch keine Neuigkeiten. Machen Sie sich keine Sorgen, ich erinnere mich an unsere Abmachung.";
			link.l1 = "Hoffentlich.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_79";
		break;

		case "ClockTower_Visser_81":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"! Kommen Sie rein, kommen Sie rein. Ich freue mich, Sie zu sehen.";
			link.l1 = "Glückwunsch zu Ihrer Ernennung.";
			link.l1.go = "ClockTower_Visser_82";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_82":
			dialog.text = "Danke. Der Rat der Siebzehn hat seine Entscheidung schneller getroffen, als ich erwartet hatte. Der Vertrag erwies sich als ausreichender Beweis. Mynheer van Doorn wurde von der Leitung der Stelle entfernt.";
			link.l1 = "Und wie hat er es aufgenommen?";
			link.l1.go = "ClockTower_Visser_83";
		break;

		case "ClockTower_Visser_83":
			dialog.text = "Er weiß, wie man verliert. Hat einfach seine persönlichen Sachen aus dem Büro geholt und ist gegangen. Obwohl, hat er wirklich verloren?\n"+
						 "Sein Kommando über die Amsterdam haben sie ihm gelassen. In dieser Hinsicht hat die Kompanie sicherlich einen Fehler gemacht. Sie hätten ihm das Schiff damals nicht geben sollen.\n"+
						 "Wir haben ihn unterschätzt. Hoffentlich wird am Ende nicht alles noch schlimmer.";
			link.l1 = "Wie könnte es noch schlimmer sein?";
			link.l1.go = "ClockTower_Visser_84";
		break;

		case "ClockTower_Visser_84":
			dialog.text = "Mynheer van Doorn weiß, wer den Vertrag aus seinem Büro geholt hat.";
			link.l1 = "Woher?!";
			link.l1.go = "ClockTower_Visser_85";
		break;

		case "ClockTower_Visser_85":
			dialog.text = "Schauen Sie mich nicht so an! Ich habe ihm nichts gesagt. Er hat es selbst herausgefunden.";
			link.l1 = "Und was jetzt?";
			link.l1.go = "ClockTower_Visser_86";
		break;

		case "ClockTower_Visser_86":
			dialog.text = "Jetzt betrachtet er Sie als Feind. Aber solange Sie keine Bedrohung für die Republik der Sieben Vereinigten Provinzen darstellen — wird er Sie nicht anrühren.\n"+
						 "Van Doorn wusste immer, wie man Persönliches von Beruflichem trennt. Die Frage ist, können Sie das?";
			link.l1 = "Was, wenn ich es nicht kann?";
			link.l1.go = "ClockTower_Visser_87";
		break;

		case "ClockTower_Visser_87":
			dialog.text = "Dann wird er Sie finden. Und seine Arbeit tun. Geben Sie ihm keinen Grund.";
			link.l1 = "Ich werde es versuchen.";
			link.l1.go = "ClockTower_Visser_88";
		break;

		case "ClockTower_Visser_88":
			dialog.text = "Einen guten Tag wünsche ich Ihnen, Kapitän. Nutzen Sie jederzeit die Dienste unserer... meiner Stelle.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VillemstadStreet");
		break;
		
		case "ClockTower_Johan_61":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", man erwartet Sie. Mynheer Visser hat angeordnet, alle Kunden frei hereinzulassen. Er sagt, die alten Regeln waren zu streng.";
			link.l1 = "Danke, Johan.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_61":
			dialog.text = "Gehen Sie rein zu jeder Geschäftszeit. Termine wurden abgeschafft.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Helena_1":
			dialog.text = "Hast du eine Minute?";
			link.l1 = "Für dich — immer.";
			link.l1.go = "ClockTower_Helena_2";
		break;

		case "ClockTower_Helena_2":
			dialog.text = "Ach, wenn das nur so wäre, mein Kapitän. Du hast auch andere Leidenschaften im Leben. Gerade jetzt zum Beispiel ist dein hübscher Kopf mit ganz anderen Dingen beschäftigt als mit mir, nicht wahr?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Helena_3";
		break;

		case "ClockTower_Helena_3":
			dialog.text = "Dachte ich's mir doch. Ich kenne meinen Mann gut. Und die Leidenschaft eines Seemanns — die kenne ich noch besser. Also sag es mir geradeheraus, Liebling...\n"+
						 "Was wird es uns kosten, das Flaggschiff der angesehenen Niederländischen Westindien-Handelskompanie zu kapern?";
			link.l1 = "Damit van Doorn selbst nach uns kommt, muss ich zum Feind von Willemstad werden.";
			link.l1.go = "ClockTower_Helena_4";
		break;

		case "ClockTower_Helena_4":
			dialog.text = "Oh, mein Kapitän... Also wird es so sein. Nicht das erste Mal, oder?";
			link.l1 = "Als ob du es nicht billigen würdest.";
			link.l1.go = "ClockTower_Helena_5";
		break;

		case "ClockTower_Helena_5":
			dialog.text = "Ich habe mich in dich verliebt, so wie du bist. Und ich werde immer auf deiner Seite sein. Denk nur an die Last der Verantwortung, die wir... das heißt, die du gegenüber deinen Leuten trägst.";
			link.l1 = "Aber dafür haben wir ja unseren Alonso. Der wird dich daran erinnern.";
			link.l1.go = "ClockTower_Helena_6";
		break;

		case "ClockTower_Helena_6":
			dialog.text = "Sobald wir in See stechen, mein Kapitän.";
			link.l1 = "Dann wollen wir nicht zögern, Liebste.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Mary_1":
			dialog.text = "Charles? Ich möchte dich etwas fragen.";
			link.l1 = "Natürlich, Mary. Was ist passiert?";
			link.l1.go = "ClockTower_Mary_2";
		break;

		case "ClockTower_Mary_2":
			dialog.text = "Ich... ich mache mir Sorgen um dich, ja. Ich kenne diesen Blick. Du denkst an etwas Schlimmes.";
			link.l1 = "Unsinn. Ich erinnere mich nicht mal daran, worüber ich gerade nachgedacht habe. Woher willst du das wissen?";
			link.l1.go = "ClockTower_Mary_3";
		break;

		case "ClockTower_Mary_3":
			dialog.text = "Ich weiß es einfach! Ich habe diese Amsterdam gesehen, ja. Ein schönes Schiff. Sehr schön. Aber...\n"+
						 "Du hast bereits alles entschieden... Wie früher, nicht wahr?";
			link.l1 = "Van Doorn wird selbst nach uns kommen, aber dafür muss ich zum Feind von Willemstad werden.";
			link.l1.go = "ClockTower_Mary_4";
		break;

		case "ClockTower_Mary_4":
			dialog.text = "Ist es das wert, Charles?";
			link.l1 = "Ich weiß es nicht, Mary.";
			link.l1.go = "ClockTower_Mary_5";
		break;

		case "ClockTower_Mary_5":
			dialog.text = "Ich möchte, dass du glücklich bist, ja. Aber trotzdem werde ich Alonso bitten, dich davon abzubringen, ja!";
			link.l1 = "Das sieht ihm ähnlich. Komm, Liebste.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Girl_End":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Girl_DlgExit");
		break;
		
		case "ClockTower_Alonso_1":
			dialog.text = "Cap, wir müssen reden.";
			link.l1 = "Ich höre.";
			link.l1.go = "ClockTower_Alonso_2";
			link.l2 = "Nicht jetzt, Alonso.";
			link.l2.go = "ClockTower_Alonso_2";
		break;

		case "ClockTower_Alonso_2":
			dialog.text = "Es ist so, Cap, aber Sie müssen mir zuhören. Es ist, äh, wie sagt man...\n"+
						 "Eine dringende Angelegenheit — genau!\n"+
						 "Also, ein Vögelchen hat mir gezwitschert, dass Sie persönlich einen der Direktoren der Kompanie von seinem bequemen Platz vertrieben haben, und der hegt nun einen Groll und jagt uns jetzt mit seiner prächtigen Fregatte.";
			link.l1 = "Das ist eine grobe Übertreibung.";
			link.l1.go = "ClockTower_Alonso_3";
		break;

		case "ClockTower_Alonso_3":
			dialog.text = "Sie wissen doch, wie die Leute gerne tratschen, Cap. Lassen Sie ein Gerücht eine Woche gären — und Sie werden hören, dass van Doorn von der Tochter eines Plantagenbesitzers verführt wurde, dass die Amsterdam eine Crew aus lebenden Toten hat und im Laderaum die Schätze von Cortés höchstpersönlich liegen.\n"+
						 "Aber mich interessiert mehr die wahre Sachlage. Also, Cap, wird es eine Prügelei geben oder nicht?";
			link.l1 = "...";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Tommy
			{
				link.l1.go = "ClockTower_Alonso_4_1";
			}
			else
			{
				link.l1.go = "ClockTower_Alonso_4_5";
			}
		break;

		case "ClockTower_Alonso_4_1":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin");
		break;

		case "ClockTower_Alonso_4_2":
			dialog.text = "Das, nebenbei bemerkt, wäre verdammt lustig, da widerspreche ich nicht! Niederländisches Flaggschiff! Ha! Ich stelle mir die Gesichter dieser Käsefresser vor, wenn wir...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_3";
		break;

		case "ClockTower_Alonso_4_3":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin_2");
		break;

		case "ClockTower_Alonso_4_4":
			dialog.text = "Tommy, halt die Klappe.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_5";
		break;

		case "ClockTower_Alonso_4_5":
			dialog.text = "...";
			link.l1 = "Wenn es zu einer Prügelei kommt, dann nicht so bald. Van Doorn wird sich nicht rächen, er ist nicht so ein Mensch. Zuerst müssen wir die Holländer ordentlich verärgern.";
			link.l1.go = "ClockTower_Alonso_4_6";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "ClockTower_Alonso_4_6":
			dialog.text = "Danke, Cap, das wird die Crew beruhigen.";
			link.l1 = "Und dich?";
			link.l1.go = "ClockTower_Alonso_5";
		break;

		case "ClockTower_Alonso_5":
			dialog.text = "Meine Sorge ist es, die Crew zu schützen. Vor sich selbst und... vor Ihnen, wenn es mir gelingt. Sie werden sowieso tun, was Sie vorhaben.";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Tommy
			{
				link.l1 = "...";
				link.l1.go = "ClockTower_Alonso_5_add";
			}
			else
			{
				link.l1 = "Weiter so, Alonso.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
			}
		break;

		case "ClockTower_Alonso_5_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_6", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_6":
			dialog.text = "Stur wie ein spanischer Maulesel!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_6_add";
		break;

		case "ClockTower_Alonso_6_add":
			StartInstantDialogTurnToNPC("ClockTower_Alonso", "ClockTower_Alonso_7", "Quest\ShipsPack\ClockTower_dialog.c", "Irons");
		break;

		case "ClockTower_Alonso_7":
			dialog.text = "Herr, warum ich.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_7_add";
		break;

		case "ClockTower_Alonso_7_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_8", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_8":
			dialog.text = "Du verkomplizierst alles! Cap will ein schönes Schiff — wir besorgen ihm ein schönes Schiff! Wir sind eine Mannschaft!";
			link.l1 = "Weiter so, Alonso. Tommy, raus.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
		break;
		
		// Абордаж Амстердама, перед боем с Ван Дормом
		case "ClockTower_VanDoorn_21":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". Euer Schiff — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" Geschütze und "+GetMaxCrewQuantity(pchar)+" Besatzung.";
			link.l1 = "Sie sind wie immer präzise, Mynheer Direktor.";
			link.l1.go = "ClockTower_VanDoorn_22";
		break;

		case "ClockTower_VanDoorn_22":
			dialog.text = "Dieser Titel gehört mir nicht mehr — dank Ihrer Bemühungen. Aber denken Sie nicht einmal daran, dass ich Sie aus kleinlicher Rache angegriffen habe. Ich habe meine Arbeit getan.\n"+
						 "Und offensichtlich habe ich versagt. Ich hätte auch nicht gewinnen können: Ich sagte Ihnen einmal, dass Sie ein viel besserer Kapitän sind als ich.";
			link.l1 = "Sie haben sich diese Last selbst aufgeladen! Ihr Vertrag ist vor sieben Jahren abgelaufen. Was hat Sie davon abgehalten, einfach nach Hause zurückzukehren?";
			link.l1.go = "ClockTower_VanDoorn_23";
		break;

		case "ClockTower_VanDoorn_23":
			dialog.text = "Was hält Sie davon ab, dasselbe zu tun? Sie kennen die Antwort, Kapitän. Sie haben einen Traum. Sie haben kein anderes Leben. Und sobald Sie die Kontrolle loslassen — bricht alles zusammen.\n"+
						 "Ich hätte Ordnung in diese Gegend bringen können. Den endlosen Kreislauf der Gewalt stoppen. Wenn ich die Kontrolle nicht gelockert hätte. Wenn ich meine Angst überwunden und getan hätte, was längst getan werden musste.\n"+
						 "Aber genug Pathos. Als Kämpfer tauge ich genauso wenig wie als Kapitän, aber ich verstehe es, meine Leute auszuwählen. Sie haben sich selbst zu meiner letzten Aufgabe gemacht, Kapitän. Heute wird das Register der Stelle um zwei Kapitäne ärmer sein!";
			if (CheckCharacterItem(PChar, "CatharinaLetter"))
			{
				link.l1 = "Sie sprachen da etwas von Angst. Also lesen Sie diesen Brief.";
				link.l1.go = "ClockTower_VanDoorn_24";
			}
			link.l2 = "Nur um einen. Zum Kampf!";
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_24":
			dialog.text = "Von Catharina?! Wie können Sie es wagen, Persönliches mit Geschäftlichem zu vermischen?!";
			link.l1 = "Wie Sie sehen, ist der Brief noch versiegelt. Ich warte.";
			link.l1.go = "ClockTower_VanDoorn_25";
			TakeItemFromCharacter(pchar, "CatharinaLetter");
			pchar.questTemp.ClockTower_GaveCatharinaLetter = true;
		break;

		case "ClockTower_VanDoorn_25":
			dialog.text = "...sie kann nicht mehr warten... wird zu einem anderen gehen... wenn ich nicht zurückkehre?!";
			link.l1 = "Die Stelle haben Sie bereits verloren. Ihre Mannschaft stirbt gerade. Sind Sie bereit, auch noch Ihre Familie zu verlieren?";
			link.l1.go = "ClockTower_VanDoorn_26";
		break;

		case "ClockTower_VanDoorn_26":
			dialog.text = "Nicht so. Kapitän, akzeptieren Sie meine Kapitulation?";
			link.l1 = "Ja. Verschwinden Sie von meinem Schiff.";
			link.l1.go = "ClockTower_VanDoorn_27";
			link.l2 = "Nein. Das war die letzte Gunst für einen Verurteilten. Zum Kampf!";
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_27":
			dialog.text = "Dann gratuliere ich Ihnen zum Sieg, Kapitän "+GetFullName(pchar)+". Heute wird das Register nur um einen Kapitän ärmer sein. Leb wohl.";
			link.l1 = "...";
			link.l1.go = "ClockTower_cabinPeace";
			GiveItem2Character(PChar, "pistol15");
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			TakeItemFromCharacter(npchar, "pistol15");
		break;
		
		// Финальный диалог с Маартеном
		case "ClockTower_Visser_101":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+". Ich hätte nicht gedacht, dass Sie es wagen würden, hierher zu kommen.";
			link.l1 = "Warum nicht? Ich bin immer noch Ihr Kunde, und ich brauche die Dienste der Stelle.";
			link.l1.go = "ClockTower_Visser_102";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_102":
			dialog.text = "Dienste? DIENSTE?! Nach dem, was Sie getan haben? Sie sind ein Feind der angesehenen Niederländischen Westindien-Kompanie! Ein anderer Kapitän wird Ihren Platz als Kunde einnehmen!";
			link.l1 = "Unwahrscheinlich. Sehen Sie, was ich in van Doorns Papieren gefunden habe.";
			link.l1.go = "ClockTower_Visser_103";
		break;

		case "ClockTower_Visser_103":
			dialog.text = "...";
			link.l1 = "Ihr Vorgänger hielt es für unter seiner Würde, dieses Dokument zu benutzen — selbst als sein Stuhl zu wackeln begann.";
			link.l1.go = "ClockTower_Visser_104";
			TakeItemFromCharacter(pchar, "Visser_Key");
		break;

		case "ClockTower_Visser_104":
			dialog.text = "...";
			link.l1 = "Sie haben Glück, dass Sie einen solchen Vorgesetzten hatten. Für solche Machenschaften hätte Sie ein Prozess erwartet — im besten Fall.";
			link.l1.go = "ClockTower_Visser_105";
		break;

		case "ClockTower_Visser_105":
			dialog.text = "...";
			link.l1 = "Sie sind ein Geschäftsmann. Sie wissen, worauf ich hinaus will.";
			link.l1.go = "ClockTower_Visser_106";
		break;

		case "ClockTower_Visser_106":
			dialog.text = "Sie... Ihr Platz im Register ist wiederhergestellt.";
			link.l1 = "Ach, Maarten. Sie wollten den Platz des Direktors einnehmen, obwohl er Ihnen alles gegeben hat. Er hat Sie vor einem Prozess bewahrt und hielt es nicht einmal für nötig, Sie darüber zu informieren.";
			link.l1.go = "ClockTower_Visser_107";
		break;

		case "ClockTower_Visser_107":
			dialog.text = "...";
			link.l1 = "Dieser kleine Sündenfall wird Sie niemals weiter hinaufsteigen lassen und Sie in ständiger Angst leben lassen.";
			link.l1.go = "ClockTower_Visser_108";
		break;

		case "ClockTower_Visser_108":
			dialog.text = "...";
			link.l1 = "Jetzt sind Sie an der Reihe, an diesen Ort gekettet zu sein. Aber einen solchen Stellvertreter wie van Doorn hatte, werden Sie sicher nicht haben.";
			link.l1.go = "ClockTower_Visser_109";
		break;

		case "ClockTower_Visser_109":
			dialog.text = "Genug. Wollen Sie mich vollends erledigen?!";
			link.l1 = "Nicht ganz. Ich möchte, dass Sie mein neues Schiff ins Register eintragen. Ich will keine Missverständnisse.";
			link.l1.go = "ClockTower_Visser_110";
		break;

		case "ClockTower_Visser_110":
			dialog.text = "Ihr Schiff ist die Amsterdam. Flaggschiff der NWIK. Es kann nicht einfach... neu registriert werden.";
			link.l1 = "Warum nicht? Papier erträgt alles. Funktioniert Ihr System nicht so?";
			link.l1.go = "ClockTower_Visser_111";
		break;

		case "ClockTower_Visser_111":
			dialog.text = "Großer Gott, aber alles hat Grenzen!";
			link.l1 = "Ich glaube an die Macht dieses Ortes. Das sollten Sie auch.";
			link.l1.go = "ClockTower_Visser_112";
		break;

		case "ClockTower_Visser_112":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_113";
		break;

		case "ClockTower_Visser_113":
			dialog.text = "Vollständiger Name?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_114";
		break;

		case "ClockTower_Visser_114":
			dialog.text = "Staatsangehörigkeit?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_115";
		break;

		case "ClockTower_Visser_115":
			dialog.text = "Name Ihres Schiffs?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_116";
		break

		case "ClockTower_Visser_116":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Schiffstyp?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_117";
		break;

		case "ClockTower_Visser_117":
			dialog.text = "Anzahl der Kanonen?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_118";
		break;

		case "ClockTower_Visser_118":
			dialog.text = "Besatzungsgröße?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_119";
		break;

		case "ClockTower_Visser_119":
			dialog.text = "Gut. Jetzt unterschreiben Sie hier. Und hier. Und hier auch.";
			link.l1 = "Das war's?";
			link.l1.go = "ClockTower_Visser_120";
		break;

		case "ClockTower_Visser_120":
			dialog.text = "Das war's.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Visser_pausa_1");
		break;

		case "ClockTower_Visser_121":
			dialog.text = "...";
			link.l1 = "Sie haben vergessen, etwas zu sagen.";
			link.l1.go = "ClockTower_Visser_122";
		break;

		case "ClockTower_Visser_122":
			dialog.text = "\nWillkommen im Kundenregister der angesehenen Niederländischen Westindien-Kompanie.";
			link.l1 = "Bis zum nächsten Mal, Mynheer Direktor.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FINAL");
		break;
		

		//------------------Услуги конторы------------------//
		case "ClockTower_OfficeServices":
			if (npchar.id == "ClockTower_VanDoorn")
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.name+". Wie können ich und meine Stelle Ihnen heute helfen?";
			}
			if (npchar.id == "ClockTower_Visser")
			{
				if (CharacterIsAlive("ClockTower_VanDoorn"))
				{
					dialog.text = "Schön, Sie zu sehen, "+GetTitle(NPChar, false)+"! Immer zu Ihren Diensten. Was interessiert Sie heute?";
				}
				else
				{
					dialog.text = "Nun? Was interessiert Sie heute?";
				}
			}
			link.l1 = "Werden Sie ein Audit meines Schiffes durchführen? Ich möchte seine Eigenschaften verbessern.";
			link.l1.go = "ClockTower_OfficeServices_audit"; // Аудит
			link.l2 = "Ich bin mit der Spezialisierung meines Schiffes nicht zufrieden. Können Sie neue Dokumente fertigen?";
			link.l2.go = "ClockTower_OfficeServices_changeTrait"; // Смена документов
			link.l3 = "Werden Sie mein Schiff im Register der Kompanie eintragen? Damit Piraten und Kopfgeldjäger zweimal überlegen.";
			link.l3.go = "ClockTower_OfficeServices_buffSpec"; // Занесение в реестр
			if (!CheckAttribute(pchar, "questTemp.ShipInsurance"))
			{
				link.l4 = "Ich möchte meine Schiffe in den Hafenhallen versichern. Aktuelle und zukünftige.";
				link.l4.go = "ClockTower_OfficeServices_Insurance"; // Страховка (пропадает после оплаты)
			}
			if(!CheckAttributeEqualTo(npchar, "last_logbook_date", LastSpeakDate()) && ClockTower_JournalsQty() > 0)
			{
				link.l5 = "Sie nehmen doch die Schiffstagebücher von Piratenkapitänen an?";
				link.l5.go = "ClockTower_OfficeServices_logbook"; // Награда за пиратов (раз в сутки)
			}
			link.l6 = "Vielleicht ein andermal. Guten Tag.";
			link.l6.go = "ClockTower_OfficeServices_exit"; // Отказ
		break;

		// Аудит
		case "ClockTower_OfficeServices_audit":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Die Kosten hängen von der Größe des Schiffes ab. Um welches Schiff geht es?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.Audit")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Leider ist das Audit eine einmalige Dienstleistung für jedes einzelne Schiff. Noch etwas?";
				link.l1 = "Dann ein andermal.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "Audit"))
			{
				n = GetAuditShipCost(sld);
				dialog.text = "Mal sehen... Das wird " + n + " Dublonen kosten.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Fahren Sie fort.";
					link.l1.go = "ClockTower_OfficeServices_audit_upgradeShip";
				}
				link.l2 = "Obwohl... machen wir es ein andermal.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Ich muss Ihnen leider eine Absage erteilen. Laut Register ist Ihr Schiff vor vielen Jahren dem Meeresteufel anheimgefallen, und einen solchen Geist der Vergangenheit kann man nicht mit einem Federstrich auslöschen. Bevor wir zusammenarbeiten können, sollten Sie es restaurieren lassen. Man sagt, auf Isla Tesoro gebe es einen Meister, der sich einer solchen Arbeit annimmt.";
				link.l1 = "Verstanden, danke.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$Das Schiff ist bereits optimiert worden.";
				link.l1 = "Verstanden, danke.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetAuditShipCost(sld));
			UpgradeShipAudit(sld);
			dialog.text = "Fertig.";
			link.l1 = "Danke.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;

		// Улучшение специализации
		case "ClockTower_OfficeServices_buffSpec":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Die Kosten hängen von der Größe des Schiffes ab. Um welches Schiff geht es?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Leider ist die Eintragung ins Register eine einmalige Dienstleistung für jedes einzelne Schiff. Noch etwas?";
				link.l1 = "Dann ein andermal.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "SpecialityUpgrade"))
			{
				n = GetSpecialityUpgradeShipCost(sld);
				dialog.text = "Mal sehen... Das wird " + n + " Dublonen kosten.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Fahren Sie fort.";
					link.l1.go = "ClockTower_OfficeServices_buffSpec_upgradeShip";
				}
				link.l2 = "Obwohl... machen wir es ein andermal.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Ich muss Ihnen leider eine Absage erteilen. Laut Register ist Ihr Schiff vor vielen Jahren dem Meeresteufel anheimgefallen, und einen solchen Geist der Vergangenheit kann man nicht mit einem Federstrich auslöschen. Bevor wir zusammenarbeiten können, sollten Sie es restaurieren lassen. Man sagt, auf Isla Tesoro gebe es einen Meister, der sich einer solchen Arbeit annimmt.";
				link.l1 = "Verstanden, danke.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$Das Schiff ist bereits optimiert worden.";
				link.l1 = "Verstanden, danke.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetSpecialityUpgradeShipCost(sld));
			UpgradeShipSpeciality(sld);
			dialog.text = "Fertig.";
			link.l1 = "Danke.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;

		// Смена трейта корабля
		case "ClockTower_OfficeServices_changeTrait":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Die Kosten hängen von der Größe des Schiffes ab. Um welches Schiff geht es?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				sTemp = "";
				ShipTraitCanBeChanged(sld, &sTemp);
				if (sTemp == "EmptyShip" || sTemp == "QuestCompanion") continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Hm. Ich sehe keins Ihrer Schiffe im Hafen.";
				link.l1 = "Dann ein andermal.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";

			if (ShipTraitCanBeChanged(sld, &sTemp))
			{
				n = GetChangeShipTraitCost(sld);
				dialog.text = "Mal sehen... Das wird " + n + " Dublonen kosten.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Fahren Sie fort.";
					link.l1.go = "ClockTower_OfficeServices_changeTrait_upgradeShip";
				}
				link.l2 = "Obwohl... machen wir es ein andermal.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "QuestSP")
			{
				dialog.text = "Leider ist das unmöglich. Ihr Schiff ist ein einmaliges Exemplar, umgeben von Legenden. Mit einem Federstrich lässt sich das nicht ändern.";
				link.l1 = "Verstanden, danke.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else
			{
				dialog.text = "Über welche Spezialisierung sprechen Sie? Ihr Schiff ist universal, ohne spezielle Merkmale.";
				link.l1 = "Angenehm zu erfahren, danke.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_upgradeShip":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
			DialogExit();
			LaunchChangeShipTraitScreen(sld);
		break;

		// Страховка
		case "ClockTower_OfficeServices_Insurance":
			n = GetInsuranceCost();
			dialog.text = "Mal sehen... Das wird " + n + " Dublonen kosten.";
			if (PCharDublonsTotal() > n)
			{
				link.l1 = "Fahren Sie fort.";
				link.l1.go = "ClockTower_OfficeServices_Insurance_done";
			}
			link.l2 = "Obwohl... machen wir es ein andermal.";
			link.l2.go = "ClockTower_OfficeServices_exit";
		break;

		case "ClockTower_OfficeServices_Insurance_done":
			pchar.questTemp.ShipInsurance = true;
			RemoveDublonsFromPCharTotal(GetInsuranceCost());
			dialog.text = "Fertig.";
			link.l1 = "Danke.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			Achievment_Set("ach_CL_199");
		break;

		// Награда за пиратов
		case "ClockTower_OfficeServices_logbook":
			dialog.text = "Absolut korrekt. Die Belohnung hängt von der Anzahl der Logbücher und der relativen Gefährlichkeit ihrer Besitzer ab.\n" +
						  "Wie viele Logbücher haben Sie mitgebracht?";
			link.l1 = "" + ClockTower_JournalsQty();
			link.l1.go = "ClockTower_OfficeServices_logbook_1";
		break;

		case "ClockTower_OfficeServices_logbook_1":
			dialog.text = "Die Kompanie dankt Ihnen für Ihre Arbeit. Ihnen stehen " + JournalsCost() + " Dublonen zu. Bitte, nehmen Sie sie und unterschreiben Sie hier.";
			link.l1 = "Danke.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			npchar.last_logbook_date = LastSpeakDate();
			Achievment_Set("ach_CL_199");
		break;

		case "ClockTower_OfficeServices_exit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
		break;

		case "ClockTower_cabinFight":
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			ClockTower_CabinFight2();
		break;
		
		case "ClockTower_cabinPeace":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_cabinPeace");
		break;
	}
}

void ClockTower_NoShipInPort(ref link)
{
	dialog.text = "Ich sehe Ihr Schiff nicht im Hafen.";
	link.l1 = "Dann ein andermal.";
	link.l1.go = "ClockTower_OfficeServices_exit";
}

int ClockTower_PlaySound_rh2(string name)
{
    float x = stf(loadedLocation.locators.reload.houseO2.x);
    float y = stf(loadedLocation.locators.reload.houseO2.y);
    float z = stf(loadedLocation.locators.reload.houseO2.z);
    return SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, name, 0, x, y, z);
}
