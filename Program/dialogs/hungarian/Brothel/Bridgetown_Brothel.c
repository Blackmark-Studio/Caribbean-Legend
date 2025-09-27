// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdés, "+ GetSexPhrase("fiatalember","fiatal hölgy") +"?", "Mire van szükséged, "+ GetSexPhrase("jóképû","csinos") +"? Kérdezz csak!"), "Már megint kérdés?", "Tee-hee, ha neked mindegy - kérdések...",
                          ""+ GetSexPhrase("Hm, miért nem választasz magadnak egy szépséget? Kezdek gyanakodni rád...","Hm, miért nem választasz magadnak egy szépséget? Attól tartok, itt nincsenek fiúk, te-hee...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam, elnézést.", "Igazából, nem számít..."), "Én... elnézést, egyelôre nincs kérdésem.",
                      "Igazad van, már harmadszorra. Bocsásson meg.", "Talán legközelebb, asszonyom.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Vettem egy rakomány mahagónit cserébe, és Blueweld felé tartok. Hosszú még az út, és az embereim kevesen vannak, és nyugtalanok... Mennyibe kerülne, ha ötven matróz itt töltené az éjszakát?";
                link.l1.go = "BrothelDone";
            }
		break;
		
		case "BrothelDone":
			dialog.text = "Ötven matróz - tizenötezer.";
			link.l1 = "Nagy összeg... Át kell gondolnom.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-7");
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
