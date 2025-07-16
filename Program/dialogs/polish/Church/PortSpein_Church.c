// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakiego rodzaju pytania, "+GetSexPhrase("mój synu","moja córko")+"?","Pytaj, słucham..."),"Słucham, mów teraz, "+GetSexPhrase("mój synu","moja córko")+"... ","Po raz trzeci, "+GetSexPhrase("mój synu","moja córko")+"Proś o to, czego potrzebujesz.","Duchowny ma od groma pracy, "+GetSexPhrase("mój synu","moja córko")+" a ty mnie ewidentnie rozpraszasz...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie teraz, ojcze..."),"Nie mam nic do powiedzenia, przepraszam.","Zapytam, ale później. Wybacz mi, ojcze.","Przepraszam, święty ojcze...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Powiedz mi, święty ojcze, czy imię 'Juan' brzmi znajomo?";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Tak, mój synu. W tym mieście jest wielu parafian, którzy nazywają się Juan.";
			link.l1 = "Rozumiem. Przepraszam, że niepokoję, ojcze...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
