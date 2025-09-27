// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég megpróbált feltenni nekem egy kérdést...", "Ilyen kíváncsi emberekkel még nem találkoztam sem a hajógyáramban, sem máshol ebben a városban.",
                          "Mi ez a sok kérdés? Az én munkám az, hogy hajókat építsek. Gondoskodjunk errôl.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Hm, nos...", "Folytasd csak...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Úton vagyok Blueweldbe egy rakás kávéval, és szeretnék még egy kis árut venni, de itt a probléma: ezen a briggen, amit egy harci kutyától vettem, irtózatos mennyiségû nehézágyú van, összesen 24. Tudod, én nem háborúba tartok. Szeretném mindet eladni neked, és vennék 12 hatfontos ágyút, ami több mint elég néhány kalóz elijesztésére. A maradék helyet pedig áruval töltöm meg.";
                link.l1.go = "ShipyardDone";
			}
		break;
		
		case "ShipyardDone":
			dialog.text = "Igen, csak rajta, adja el ôket. Mindig van elég hatfontosom, de a nehézágyúkkal mindig gondban vagyok, mivel mindenki állandóan veszi ôket, és senki sem akarja eladni ôket, hacsak nem teljesen elromlottak, úgyhogy tisztességes árat fizetek értük, ha persze még mûködôképes állapotban vannak.";
			link.l1 = "Hû, nagyszerû! Azonnal leadom a rendeléseket.";
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
