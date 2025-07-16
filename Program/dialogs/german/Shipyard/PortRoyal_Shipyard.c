// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen?"),"Du hast versucht, mir vor einer Weile eine Frage zu stellen...","Ich habe noch nie Menschen mit solcher Neugier in meiner Werft oder sonstwo in dieser Stadt getroffen.","Was ist mit all den Fragen? Meine Aufgabe ist es, Schiffe zu bauen. Kümmern wir uns darum.","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Ich habe im Moment nichts zu besprechen."),"Umph, wo ist mein Gedächtnis hin...","Hm, nun ja...","Mach weiter...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx"))
            {
				if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
				{
					link.l1 = "Ich habe gehört, dass diese Werft sich mit der Verbesserung der Segelgeschwindigkeit des Schiffes befasst. Dafür wird ein Seidensegelstoff benötigt, der sehr selten ist. Möchten Sie... darüber sprechen?";
					link.l1.go = "mtraxx";
				}
			}
			if (CheckAttribute(npchar, "quest.upgradeship")) {
				link.l2 = "Ich komme von Miss MacArthur, bezüglich...";
				link.l2.go = "helen_upgradeship";
			}
			
			if (CheckAttribute(npchar, "quest.upgradeship.money") && HelenCanUpgrade()) {
				link.l2 = "Beginnen Sie die Überholung des Schiffes!";
				link.l2.go = "helen_upgradeship_money";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Könnten Sie etwas deutlicher sein, junger Mann? Was genau hat Sie hierher gebracht? Wenn Sie Ihr Schiff verbessern wollen - dann lassen Sie uns sofort zum Geschäft kommen.";
			link.l1 = "Nicht ganz. Die Art von Dienstleistungen, die Sie erbringen, erfordert Waren, die im Laden nicht frei verfügbar sind. Ich möchte Ihnen die gleiche Art von Materialien anbieten, die Sie benötigen könnten.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Nun, nun... Hmm... Sind Sie sich bewusst, dass nur die Behörden dieser Kolonie befugt sind, mit solchen strategischen Gütern zu handeln? Sie können mir gerne Ihre eigene Seide zur Verfügung stellen, damit ich an der Verbesserung Ihres Schiffes arbeiten kann, aber der Verkauf ist strengstens verboten. Ebenso der Kauf von mir - solche Aktivitäten werden ziemlich schwer bestraft.";
			link.l1 = "Nun, das hier ist weder ein Laden, noch ist es ein Zollamt...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Ich beziehe all die Seegeltuch direkt von meinen Kunden, oder kaufe begrenzte Mengen mit einer speziellen Erlaubnis des Gouverneurs. Wenn Sie keine weiteren Fragen haben, dann lassen Sie mich bitte zurück zu meiner Arbeit.";
			link.l1 = "Hmm... Sehr gut. Einen schönen Tag noch, Meister.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            DialogExit();
			AddQuestRecord("Roger_2", "5");
			pchar.questTemp.Mtraxx = "silk_4";
		break;
		
		case "helen_upgradeship":
			dialog.text = "Oh, I know! Lucky you, Captain. Is it about a complete overhaul of the ship? We'll take care of everything; our shipyard is on par with those in Plymouth!";
			link.l1 = "Ich nehme an, dieser Dienst wird nicht kostenlos sein?";
			link.l1.go = "helen_upgradeship_1";
		break;
		
		case "helen_upgradeship_1":
			dialog.text = "Natürlich, Kapitän, solche Dienste können nicht kostenlos sein, selbst für Cromwell! Jedoch, ich halte mein Wort und werde nur Geld nehmen - Sie müssen keine Schmuggelware schmuggeln.";
			link.l1 = "Verständlich. Wie viel?";
			link.l1.go = "helen_upgradeship_2";
		break;
		
		case "helen_upgradeship_2":
			dialog.text = "Es hängt von der Größe Ihres Flaggschiffs ab, Kapitän. Ein Schiff erster Rang kostet Sie fünftausend Dublonen, und ein fünfter Rang - nur tausend.";
			link.l1 = "In Ordnung, ich komme zu dir, sobald ich eine Entscheidung getroffen habe.";
			link.l1.go = "exit";
			
			npchar.quest.upgradeship.money = true;
		break;
		
		case "helen_upgradeship_money":
			dialog.text = "Ausgezeichnet, jetzt habe ich alles, was ich brauche. Dann fange ich an zu arbeiten.";
			link.l1 = "Ich warte.";
			link.l1.go = "helen_upgradeship_money_1";
			
			iTemp = GetCharacterShipType(pchar);
			sld = GetRealShip(iTemp);
			iTemp = (7 - sti(sld.class)) * 1000;
			RemoveDublonsFromPCharTotal(iTemp);
		break;
		
		case "helen_upgradeship_money_1":
			AddTimeToCurrent(6, 30);
			dialog.text = "... Ich denke, das wäre es... Qualität ist garantiert.";
			link.l1 = "Danke! Ich werde es überprüfen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenUpgradeShip2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

bool HelenCanUpgrade() {
	int shipIndex = GetCharacterShipType(pchar);
	if (shipIndex == SHIP_NOTUSED) {
		return false;
	}
	
	sld = GetRealShip(shipIndex);
	if (sti(sld.class) == 7) {
		return false;
	}
	
	int cost = (7 - sti(sld.class)) * 1000;
	return (PCharDublonsTotal() >= cost);
}
