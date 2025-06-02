// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande, "+GetSexPhrase("giovane uomo","giovane signora")+"?","Di cosa hai bisogno, "+GetSexPhrase("affascinante","bella")+"? Chiedi pure."),"Di nuovo domande?","Hi-hi, se non ti dispiace - domande...",""+GetSexPhrase("Mh, perché non scegli una bellezza per te? Sto cominciando ad avere sospetti su di te...","Eh, perché non scegli una bellezza per te? Mi dispiace, ma qui non abbiamo ragazzi, hi-hi...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto, mi scusi.","Effettivamente, lascia stare..."),"Mi... scuso, non ho domande, per ora.","Hai ragione, è già la terza volta. Perdonami.","Forse la prossima volta, Signora.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Ho acquistato un carico di mogano per commercio e sto andando a Blueweld. È ancora una lunga strada, e i miei uomini sono pochi e ansiosi ... Quanto costerebbe far riposare qui cinquanta marinai per la notte?";
                link.l1.go = "BrothelDone";
            }
		break;
		
		case "BrothelDone":
			dialog.text = "Cinquanta marinai - quindicimila.";
			link.l1 = "Una somma considerevole... Devo pensarci su.";
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
