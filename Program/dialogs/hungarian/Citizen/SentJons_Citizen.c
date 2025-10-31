// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Milyen kérdések?", "Mit akarsz?");
			link.l1 = RandPhraseSimple("Meggondoltam magam.'", "Most már nincs mit mondanom.");
		    link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
			{
				link.l1 = "Mister Jones-t keresem. Ismeri ôt?";
				link.l1.go = "terrapin";
			}
		break;
		
		case "terrapin":
			if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% или числом
			{
				dialog.text = "Sok Jones' van itt. A leghíresebb, akirôl én tudok, Benjamin Jones, Fox ezredes segédtisztje. Ô általában az ezred fôhadiszállásán fogadja a látogatókat.";
				link.l1 = "Van neki egy Molly nevû húga?";
				link.l1.go = "terrapin_yes";
			}
			else
			{
				dialog.text = LinkRandPhrase("Melyik Jonesra van szüksége? Legalább két tucatot ismerek belôlük...","Túl sok Jones' van itt. Konkrétabbnak kell lenned.","Rengeteg Jones' van itt, akárcsak Johnsonok vagy Jacksonok. Konkrétabbnak kell lenned, ugye?");
				link.l1 = "Van egy Molly nevû felnôtt húga. Azt mondták, hogy ô egy ritka szépség?";
				link.l1.go = "terrapin_no";
			}
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_no":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Hm, attól tartok, ebben nem tudok segíteni.","Nem, nem ismerem ôt.","Phah! Ha az általam ismert Molly Jones egy ritka szépség, akkor Fox ezredes egy plébános."), LinkRandPhrase("Ismerek néhány Molly Jonest'. Az egyiknek van testvére, de... nem ô az, akit keres. Csak egy ember, aki majmokkal élt együtt, nevezné ôt 'egy ritka szépségnek'.","Sajnálom, de az összes Jones' , akit ismerek, nem rendelkezik testvérrel.","Sajnálom, nem tudok segíteni. Kérdezzen meg valaki mást."));
			link.l1 = "Értem. Elnézést a fáradságért.";
			link.l1.go = "exit";
			pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count)+1;
		break;
		
		case "terrapin_yes":
			dialog.text = "Igen, de jobban járna, ha a testvére lenne. Ez a sztrapacska valószínûleg nem fog vôlegényt találni magának a ronda pofája miatt.";
			link.l1 = "Köszönöm.";
			link.l1.go = "terrapin_yes_1";
		break;
		
		case "terrapin_yes_1":
			DialogExit();
			AddQuestRecord("Terrapin", "2");
			pchar.questTemp.Terrapin.Benjamin = true;
			DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Azt hiszi, hogy a "+NationNameGenitive(sti(NPChar.nation))+"titkosszolgálatának dolgozom?";
			link.l1 = "Nos... nem. Akkor viszlát.";
			link.l1.go = "exit";
			link.l2 = "Van még kérdésed?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Úgy nézek ki, mint a nyomozóiroda? Nem tudom, nem tudok semmit.";

            link.l1 = "Maga olyan zavarosfejû! Távozz.";
			link.l1.go = "exit";
			link.l2 = "Van még kérdésed?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
