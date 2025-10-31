// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések?", "Mit akarsz, " + GetAddress_Form(NPChar) + "?"), "Már próbáltál kérdezni " + GetAddress_Form(NPChar) + "...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Nézze, ha nincs mondanivalója a kikötô ügyeirôl, akkor ne zavarjon a kérdéseivel.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam.", "Nincs mirôl beszélnem."), "Nevermind.", "Valóban, már harmadszor...", "Sajnálom, de egyelôre nem érdekelnek a kikötô ügyei.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
            {
    			link.l1 = "Szeretném megtudni a bárkáról, ami a rabszolgalázadás után eltûnt.";
    			link.l1.go = "EscapeSlave_Villemstad_P1";
            }
			//Голландский гамбит, против всех
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "SeekFleut")
            {
    			link.l1 = "Meg akarok találni egy Toff Keller nevû kapitányt. Neki van egy flottája, a neve 'Leiden'. Azt mondták, hogy gyakran jár Willemstadban, így nem lesz nehéz, ha segít nekem.";
    			link.l1.go = "SeekTradeFleut";
            }
		break;

		//работорговец
		case "EscapeSlave_Villemstad_P1":
				dialog.text = "Hm... És miért érdekli? Negros a specialitása?";
				link.l1 = "Mathias Beck, a kormányzó megbízásából vagyok itt. Minden okom megvan arra, hogy azt gyanítsam, hogy a szökött négerek ellopták a hajót és megléptek vele. Ezért arra kérem, hogy minden lehetséges módon segítsen nekem a keresésben.";
				link.l1.go = "EscapeSlave_Villemstad_P2";
		break;
		
		case "EscapeSlave_Villemstad_P2":
				dialog.text = "Értem. Nos, nem tudok segíteni. A bárka '" + pchar.questTemp.Slavetrader.ShipName + "' reggelre eltûnt, senki sem látott semmit. Otthon aludtam. A dokkôr is eltûnt, és nem hagyott nyomot.\nA kormányzó egy sloopot küldött, hogy megpróbálja levadászni, amíg még forró volt a nyom, de üres kézzel jöttek vissza. Sem a négerek, sem a '" + pchar.questTemp.Slavetrader.ShipName + "'nyoma sem volt. Hogy ôszinte legyek, a sloop nem is kereste ôket túlságosan közelrôl, mindenki még mindig pánikban volt, és azt hitték, hogy a dzsungelbôl vasvillákkal és machetékkel forronganak majd a kafírok - fehér vérre éhesen.";
				link.l1 = "Ez nem volt túl hasznos, de azért köszönöm. Viszontlátásra.";
				link.l1.go = "exit";
				AddQuestRecord("Slavetrader", "22_3");
				AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
				pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
		break;				
		//Голландский гамбит
		case "SeekTradeFleut":
			DelLandQuestMark(npchar);
			dialog.text = "Toff Keller? Persze, hogy ismerem! Rendszeresen hajózik San Joséba, ami a Trinidadon van, és Cumanába. Nemrégiben Trinidadra hajózott. Gondolom, ott is megtalálják.";
			link.l1 = "Köszönjük!";
			link.l1.go = "SeekTradeFleut_1";
		break;
		
		case "SeekTradeFleut_1":
			DialogExit();
			AddMapQuestMarkIsland("Trinidad", true);
			pchar.questTemp.HWIC.Self = "FleutOnTrinidad";
			AddQuestRecord("Holl_Gambit", "3-59");
			pchar.quest.Seek_Fleut.win_condition.l1 = "location";
			pchar.quest.Seek_Fleut.win_condition.l1.location = "Trinidad";
			pchar.quest.Seek_Fleut.function = "CreateTradeFleut";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
