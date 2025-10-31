// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?","How can I help you, "+GetAddress_Form(NPChar)+"?"),"You tried to ask me a question not long ago, "+GetAddress_Form(NPChar)+"...","Over the course of this day, this is the third time you've brought up that question...",
			"More questions, I presume?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","I've got nothing to talk about at the moment."),"Umph, where has my memory gone...","Yes, it really is the third time...",
			"No, what questions?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";			
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Listen, have you seen a privateer by the name of Francois Gontier? He's been here in your town recently.";
                link.l1.go = "Portobello_rat_1";
            }			
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "Listen, could you tell me where to find a merchant named Jaime Silicio? He was supposed to come and see you...";
                link.l1.go = "trial";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "Look, I am searching for a man named Bertrand Pinette, have you heard of him? He arrived in Portobello not long ago. An imposing gentleman in a curled wig. A trader. He might have been here...";
                link.l1.go = "FMQG";
            }
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Tavern_1"))
            {
                link.l1 = "Can you tell me where I can find Marisa Caldera?";
                link.l1.go = "LFD_Tavern_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("No, I don't know. He didn't stop by the tavern and I didn't see him in town either.","You've already asked about that and I've answered you.","I told you, 'you've already asked about that Gontier.'","Listen, walk away and stop bothering me! Have you completely lost your mind?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Well then, I'll keep looking.","Hm, I suppose so...","Yes, that's right, I've asked that...","Sorry, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			DelLandQuestMark(npchar);
			npchar.quest.trial = true;
			
			dialog.text = "Forgive me, señor, but only a traitor or a drunkard would discuss such matters with a stranger. I don't want any trouble.";
			link.l1 = "A drunkard, you say? See you around, pal.";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Never heard of him, mate.";
			link.l1 = "He is an acquaintance of Don Carlos de Milyar. You sure you never heard of him?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "I am. If he is a friend of de Milyar - go to the governor and ask for señor Carlos. He will tell you about this trader of yours.";
			link.l1 = "I'll do that. Thanks for the advice!";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
		
		//--> Письмо от покойника
		case "LFD_Tavern_1_1":
			dialog.text = "Marisa? Hm... Haven’t seen her in a while. Ever since she was informed of her husband’s death, she’s stopped showing up around town.";
			link.l1 = "So she’s a widow?";
			link.l1.go = "LFD_Tavern_1_2";
			DelLandQuestMark(npchar);
		break;

		case "LFD_Tavern_1_2":
			dialog.text = "Yes. Her husband was captain of the trading pinnace 'Wavereaver'. Thanks to a license from the Dutch West India Company, nearly all ports in the archipelago were open to him. Rumor has it he didn’t survive a pirate attack on the way from Belize to Capsterville. Such things aren’t rare around here, but for her, it was a real blow.";
			link.l1 = "So she just disappeared?";
			link.l1.go = "LFD_Tavern_1_3";
		break;

		case "LFD_Tavern_1_3":
			dialog.text = "Well, 'disappeared' might be too strong a word. But she’s rarely seen in town since. Odd thing is... from time to time, different men ask about her. Like you, Captain. If she weren’t so devout, I’d think she... went into hiding and is earning her way as she can. But Marisa, before her husband’s death, never missed a Holy Mass – she practically lived at the church – so I doubt that’s the case.";
			link.l1 = "That’s it? You don’t know anything else?";
			link.l1.go = "LFD_Tavern_1_4";
		break;

		case "LFD_Tavern_1_4":
			dialog.text = "Everything I know, Captain, I’ve already told you.";
			link.l1 = "...";
			link.l1.go = "LFD_Tavern_1_5";
		break;

		case "LFD_Tavern_1_5":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Tavern_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}