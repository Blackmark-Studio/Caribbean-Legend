// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai cercato di farmi una domanda un po' di tempo fa...","Non ho mai incontrato persone con tanta curiosità nel mio cantiere navale o in qualsiasi altro posto di questa città.","Perché tutte queste domande? Il mio lavoro è costruire navi. Occupiamoci di questo.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Umph, dove se n'è andata la mia memoria...","Mh, beh...","Avanti...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Sono in viaggio verso Blueweld con un carico di caffè e vorrei comprare altra merce, ma ecco il problema: su questa brigata, che ho comprato da un cane da guerra, c'è un numero abominevole di cannoni pesanti, un totale di 24. Non sto andando in guerra, lo sai. Vorrei venderli tutti a te e comprare 12 cannoni da sei libbre, più che sufficienti per spaventare alcuni pirati. E il resto dello spazio che ho lo riempirò con la merce.";
                link.l1.go = "ShipyardDone";
			}
		break;
		
		case "ShipyardDone":
			dialog.text = "Sì, vai avanti e vendili. Ho sempre abbastanza cannoni da sei libbre, ma ho sempre un problema con i cannoni pesanti, dato che tutti li comprano sempre e nessuno vuole venderli, a meno che non siano completamente rotti, quindi ti pagherò un prezzo decente per loro se ovviamente sono ancora in condizioni di funzionamento.";
			link.l1 = "Wow, fantastico! Darò gli ordini subito.";
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
