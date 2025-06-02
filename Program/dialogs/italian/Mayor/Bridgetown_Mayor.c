// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa desideri? Chiedi pure.","Ti sto ascoltando, qual è la domanda?"),"È la seconda volta che provi a chiedere...","È la terza volta che stai cercando di chiedere di nuovo...","Quando finirà?! Sono un uomo impegnato, lavoro sulle questioni della colonia e tu stai ancora cercando di chiedere qualcosa!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ora. Luogo e momento sbagliati."),"Vero... Ma più tardi, non ora...","Chiederò... Ma un po' più tardi...","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Ho fatto un affare proficuo a Martinica e ora sto pianificando di navigare verso Blueweld. Voglio comprare palissandro e caffè nella vostra colonia. Inoltre, la mia brigata non può contenere tutto il carico che sono disposto a comprare, quindi ho bisogno di comprare un flauto qui nel vostro cantiere navale. Potrei avere il vostro aiuto in queste questioni?";
                link.l1.go = "MayorDone";
            }
		break;
		
		case "MayorDone":
			dialog.text = "Il mio aiuto? Il nostro mercante è un uomo molto onesto, quindi dubito che cercherà di ingannarti. Parla con il capitano della nave riguardo al flauto, lui ti aiuterà in questa questione. E se dovessi avere comunque problemi, dovresti venire da me. Sono interessato a promuovere i collegamenti commerciali con la nostra colonia e ti mostrerò tutto il mio sostegno.\nInoltre, sto organizzando un banchetto stasera, parteciperanno i più brillanti di Bridgetown. Dovresti venire anche tu, capitano.";
			link.l1 = "Grazie per il vostro invito, ma purtroppo sono troppo occupato. Arrivederci e grazie per la vostra agenzia!";
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
