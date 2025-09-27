// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the rumours of "+GetCityName(npchar.city)+" at your service. What would you like to know?","We were just talking about that. You must have forgotten...","This is the third time today you've brought up this question...","You're repeating the same thing like a parrot...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, "+NPChar.name+", maybe next time.","Right, I've forgotten for some reason...","Yes, it really is the third time...","Yup...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "I hear you've got a privateer by the name of François Gontier in your town. Would you happen to know where to find him?";
                link.l1.go = "Panama_rat_1";
            }
			// Addon-2016 Jason ”ЊЉ-ѓваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_panama")
            {
                link.l1 = "Look, I am searching for a man named Bertrand Pinette, have you heard of him? He arrived in Panama not long ago. An imposing gentleman in a periwig. He might have been here...";
                link.l1.go = "FMQG";
            }
		break;

		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat("Yes, we've had a fellow like that in town. He was lurking around dark places... Then some of his mates came and paid him a visit, looked like a band of cutthroats. He left town with them.","You've already asked about that and I've answered you.","I told you, you've already asked about that Gontier.","Listen, walk away and stop bothering me! Have you completely lost your mind?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("And where did he go, do you know?","Hm, I suppose so...","Yes, that's right, I've asked that...","Sorry, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;
		
		case "Panama_rat_2":
			dialog.text = "Well, there is only one way out of here on foot - Portobello. And he legged it. So look for him there.";
			link.l1 = "Thank you, you've been a great help!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--работорговец
		
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		case "FMQG":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("panama");
			dialog.text = "Bertrand Pinette? French? Never heard of him. No, mate, we haven't seen any French folk around here in a while.";
			link.l1 = "What a pity... Are you sure? He is a friend of an important hidalgo named Don Carlos de Milyar. They were supposed to arrive here together.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Señor de Milyar? That gentleman visited Panama a year ago. Actually, Don Carlos de Milyar lives in Portobello. He is a close friend of the local governor.";
			link.l1 = "I see. There was no need to waste time and breath in the jungle. Thank you, mate.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			pchar.questTemp.FMQG = "headhunter_portobello";
			AddQuestRecord("FMQ_Guadeloupe", "8");
			AddMapQuestMarkCity("PortoBello", true);
			AddLandQuestMark(characterFromId("PortoBello_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
