// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham cię, jakie jest pytanie?"),"To drugi raz, kiedy próbujesz zapytać...","To już trzeci raz, gdy próbujesz znowu zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, pracuję nad sprawami kolonii, a ty wciąż próbujesz o coś pytać!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie teraz. Nieodpowiednie miejsce i czas."),"Prawda... Ale później, nie teraz...","Zapytałem... Ale trochę później...","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"... ",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Miałem dochodowy interes na Martynice i teraz planuję żeglować do Blueweld. Chcę kupić czerwone drewno i kawę w waszej kolonii. Poza tym, mój bryg nie może pomieścić tyle ładunku, ile chcę kupić, więc muszę kupić flautę tutaj w waszej stoczni. Czy mogę liczyć na waszą pomoc w tych sprawach?";
                link.l1.go = "MayorDone";
            }
		break;
		
		case "MayorDone":
			dialog.text = "Moja pomoc? Nasz handlarz to bardzo uczciwy człowiek, więc wątpię, by próbował cię oszukać. Porozmawiaj z kapitanem statku o flecie, on ci pomoże w tej sprawie. A jeśli mimo wszystko będziesz miał kłopoty, powinieneś przyjść do mnie. Jestem zainteresowany rozwijaniem naszych handlowych połączeń z kolonią i okażę ci wszelkie moje wsparcie.\nRównież organizuję dziś wieczorem bankiet, na który przybędzie cała elita Bridgetown. Powinieneś również przyjść, kapitanie.";
			link.l1 = "Dziękuję za zaproszenie, lecz niestety jestem zbyt zajęty. Żegnaj i dziękuję za twoją pomoc!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-8");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
