// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.","I am listening to you, what's your question?"),"It is the second time you are trying to ask...","It is the third time you are trying to ask again...","When will this end?! I am a busy man, working on the colony's affairs, and you're still trying to ask something!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...","Not now. Wrong place and time."),"True... But later, not now...","I'll ask... But a bit later...","I am sorry, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "I had a profitable deal on Martinique and now I am planning to sail to Blueweld. I want to buy redwood and coffee in your colony. Besides, my brig can't hold as much cargo as I wish to purchase, so I need to buy a fluyt here at your shipyard. Could I have your assistance in these matters?";
                link.l1.go = "MayorDone";
            }
		break;
		
		case "MayorDone":
			dialog.text = "My assistance? Our trader is a very honest man, so I doubt he would attempt to fool you. Speak to the shipmaster about the flute, he will help you with this matter. And if you have any trouble anyway, then you should come see me. I am interested in advancing trade connections with our colony and I will give you my full support.\nAlso, I'm organizing a banquet tonight, all of Bridgetown's brightest will attend. You should come too, captain.";
			link.l1 = "Thank you for your invitation, but unfortunately I am too busy. Goodbye, and thank you for your assistance!";
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
