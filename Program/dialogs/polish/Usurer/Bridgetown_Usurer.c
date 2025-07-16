// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi to pytanie niedawno...","Tak, pozwól, że zgadnę... Znowu kręcisz się w kółko?","Słuchaj, ja tu zajmuję się finansami, nie odpowiadam na pytania...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam w tej chwili nic do omówienia."),"Ach, gdzież to znikła moja pamięć...","Domyśliłeś się, przykro mi...","Rozumiem...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Zmierzam do Blueweld z ładunkiem wina. Ale dowiedziałem się od jednego kapitana, że w Blueweld zwiększyło się zapotrzebowanie na kawę i nie wiem, co to powoduje. Myślę o sprzedaniu wina i zakupie kawy zamiast tego, ale nie mam wystarczająco pieniędzy, aby wypełnić cały ładownię. Czy mógłbym pożyczyć od ciebie trochę pieniędzy z odsetkami?";
                link.l1.go = "UsurerDone";
            }
		break;
		
		case "UsurerDone":
			dialog.text = "Kredyt dla szanowanego kupca, nie ma problemu. Jakiej kwoty potrzebujesz? Porozmawiajmy o tym.";
			link.l1 = "Dobrze. Załaduję ładownię i sprawdzę, ile miejsca zostało. Potem obliczę, ile mi brakuje, i wrócę do ciebie, jeśli zajdzie taka potrzeba.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-13");
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
