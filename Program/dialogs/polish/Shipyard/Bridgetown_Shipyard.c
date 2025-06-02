// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę Ci pomóc?"),"Próbowałeś zadać mi pytanie chwilę temu...","Nie spotkałem ludzi o takiej ciekawości ani w mojej stoczni, ani nigdzie indziej w tym mieście.","Co z tymi wszystkimi pytaniami? Moim zadaniem jest budować statki. Zajmijmy się tym.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam teraz nic do powiedzenia."),"Gdzież to podziała się moja pamięć...","Hm, cóż...","Śmiało...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Jestem w drodze do Blueweld z ładunkiem kawy i chciałbym kupić trochę więcej towaru, ale jest problem: na tej brygantynie, którą kupiłem od psa wojennego, jest obrzydliwa ilość ciężkich dział, w sumie 24. Nie wybieram się na wojnę, wiesz. Chciałbym sprzedać ci je wszystkie i kupić 12 sześciu-funtowych, więcej niż wystarczająco, by przestraszyć niektórych piratów. A resztę przestrzeni, którą mam, wypełnię towarem.";
                link.l1.go = "ShipyardDone";
			}
		break;
		
		case "ShipyardDone":
			dialog.text = "Tak, śmiało sprzedawaj je. Zawsze mam dość sześcio-funtówek, ale zawsze mam problem z ciężkimi armatami, ponieważ wszyscy je ciągle kupują i nikt nie chce ich sprzedawać, chyba że są całkowicie zepsute, więc zapłacę ci za nie przyzwoitą cenę, jeśli oczywiście są jeszcze w stanie roboczym.";
			link.l1 = "Wow, wspaniale! Od razu wydam rozkazy.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-10");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
