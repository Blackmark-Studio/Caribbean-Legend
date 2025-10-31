// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+GetSexPhrase("young man","young lady")+"?","What is it you need, "+GetSexPhrase("handsome","pretty one")+"? Ask away."),"Questions again?","Tee-hee, if it's all the same to you - questions...",""+GetSexPhrase("Hm, why don't you pick a beauty for yourself? I'm starting to get suspicious about you...","Hm, why don't you pick a beauty for yourself? We don't have any boys here, I'm afraid, tee-hee...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind, excuse me.","Actually, never mind..."),"I... apologies, I have no questions for now.","You're right, it's the third time already. Pardon me.","Maybe next time, Madam.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "I've bought a cargo of mahogany for trade and I'm headed to Blueweld. It's still a long way, and my men are few and anxious ... What would it cost to let fifty sailors rest here for the night?";
                link.l1.go = "BrothelDone";
            }
		break;
		
		case "BrothelDone":
			dialog.text = "Fifty sailors - fifteen thousand.";
			link.l1 = "A large sum... I need to think about it.";
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
