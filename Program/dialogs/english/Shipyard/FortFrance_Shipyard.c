// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?","How can I help you?"),"You tried to ask me a question a little while ago...","I have never met people with such curiosity in my shipyard or anywhere else in this town.","What's with all the questions? My job is to build ships. Let's take care of that.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","I've got nothing to talk about at the moment."),"Umph, where has my memory gone...","Hm, well...","Go ahead...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ”ЊЉ-Њартиника
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "begin")
            {
                link.l1 = "Your man told me you wanted to see me. I'm all ears.";
                link.l1.go = "FMQM";
            }
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "oil" && GetSquadronGoods(pchar, GOOD_OIL) >= 50)
            {
                link.l1 = "I've done the job. "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_OIL))+" barrels of resin are in my cargo holds.";
                link.l1.go = "FMQM_9";
            }
		break;
		
		// Addon-2016 Jason ”ЊЉ-Њартиника
		case "FMQM":
			pchar.quest.FMQM_Denial.over = "yes";
			dialog.text = "Yes, yes, captain "+GetFullName(pchar)+". I saw your vessel entering our port and immediately sent my servant to you. Straight to business then: you are a newcomer, but they say you have already become a seasoned sailor and fortune is on your side. That is why I have a business proposal for you.";
			link.l1 = "Interesting! Go on, tell me.";
			link.l1.go = "FMQM_1";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_1":
			dialog.text = "Have you ever heard of a special resin the Spaniards produce on the island of Trinidad? It is a rare resource of strategic value, used to fortify the hulls of ships. Every barrel costs a hefty sum because the Spanish direct all the resin to the needs of their Navy. Every colonial authority keeps trade in this good under strict control; to put it simply, it's pure contraband.   I need this resin for a special order. Of course, our store doesn't have it, and the same can be said about our local military warehouses—or perhaps they simply didn't want to sell it. It's irrelevant, really. What matters is that I need the resin, and I know where to get some. All I need is a captain who is comfortable with boardings.";
			link.l1 = "I think I'm starting to see your point...";
			link.l1.go = "FMQM_2";
		break;
		
		case "FMQM_2":
			dialog.text = "Splendid. Now listen, a small trade convoy was spotted near Trinidad, or to be more precise, in the harbour of San Jose. One ship is carrying a fine batch of resin, the very resin I am in dire need of. I will tell you more if you like the idea of plundering the enemies of our nation. What's your call?";
			link.l1 = "I like your proposal. I am ready to give it a try.";
			link.l1.go = "FMQM_3";
			link.l2 = "I'll pass, monsieur. My ship and my crew are not in their best state at the moment.";
			link.l2.go = "FMQM_exit";
		break;
		
		case "FMQM_exit":
			dialog.text = "Fine, it's your right to do as you wish. Sorry for taking your time, captain.";
			link.l1 = "Goodbye.";
			link.l1.go = "FMQM_exit_1";
		break;
		
		case "FMQM_exit_1":
			DialogExit();
			pchar.questTemp.FMQM = "fail";
			AddQuestRecord("FMQ_Martinique", "3");
			CloseQuestHeader("FMQ_Martinique");
		break;
		
		case "FMQM_3":
			string sTemp = "barquentine";
			if (MOD_SKILL_ENEMY_RATE < 7) sTemp = "barque";// Addon 2016-1 Jason пиратскаЯ линейка
			dialog.text = "Then listen: the convoy consists of three ships, the resin will be among other goods on a "+sTemp+" called the 'Bensecho'. This is your main target. As I've said before, the Spanish are sailing from San Jose - Trinidad to San Juan - Puerto Rico. They will set sail tomorrow, so you are free to choose where to attack them.";
			link.l1 = "Got it. What about a reward?";
			link.l1.go = "FMQM_4";
		break;
		
		case "FMQM_4":
			dialog.text = "All I am interested in is the resin. I will pay fifteen golden doubloons for every barrel of the stuff. According to my information, the 'Bensecho' carries around a hundred barrels.";
			link.l1 = "Good heavens! That's a hefty sum!";
			link.l1.go = "FMQM_5";
		break;
		
		case "FMQM_5":
			dialog.text = "Yes. I already told you that this particular merchandise is very expensive and rare.";
			link.l1 = "You also told me that this is contraband.";
			link.l1.go = "FMQM_6";
		break;
		
		case "FMQM_6":
			dialog.text = "Don't worry, there will be no need for you to bring it to the store or to smugglers. Come see me when the job's done, we'll dock your vessel in my shipyard for repairs and then unload all the cargo secretly at night. No one will suspect a thing.";
			link.l1 = "You think ahead of me, master. Very well. No wasting time then. I am on my way to set sail.";
			link.l1.go = "FMQM_7";
		break;
		
		case "FMQM_7":
			dialog.text = "Godspeed, captain.";
			link.l1 = "...";
			link.l1.go = "FMQM_8";
		break;
		
		case "FMQM_8":
			DialogExit();
			pchar.questTemp.FMQM = "convoy";
			AddQuestRecord("FMQ_Martinique", "4");
			SetFunctionTimerCondition("FMQM_ConvoyStart", 0, 0, 1, false);
		break;
		
		case "FMQM_9":
			dialog.text = "Excellent! Let's put your ship in dock as we agreed before. We'll unload her there tonight. Go back to your ship and let me prepare the money for you.";
			link.l1 = "Let's do this.";
			link.l1.go = "FMQM_10";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_10":
			pchar.quest.FMQM_Late.over = "yes";
			DialogExit();
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
			pchar.GenQuest.FrameLockEsc = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.questTemp.FMQM = "remove_oil";
			pchar.questTemp.FMQM.Oil = "true";
			pchar.questTemp.FMQM.Qty = GetSquadronGoods(pchar, GOOD_OIL);
			DoQuestFunctionDelay("FMQM_WaitTime", 1.0);
			RemoveCharacterGoods(pchar, GOOD_OIL, GetSquadronGoods(pchar, GOOD_OIL));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
