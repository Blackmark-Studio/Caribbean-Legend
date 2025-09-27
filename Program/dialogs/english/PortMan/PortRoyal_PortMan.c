// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?","What do you want, "+GetAddress_Form(NPChar)+"?"),"You've already tried to ask me a question "+GetAddress_Form(NPChar)+"...","You've brought up this question for the third time today...","Look, if you have nothing to tell me about the port's affairs then don't bother me with your questions.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.","I've got nothing to talk about."),"Never mind.","Indeed, the third time already...","Sorry, but I'm not interested in the port's affairs for now.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Good day. Has Captain François Gontier registered here? He was sailing from Porto Bello on a corvette named '"+pchar.questTemp.Slavetrader.ShipName+"'.";
                link.l1.go = "Jamaica_ratPP_1";
            }
			
		break;
		
		case "Jamaica_ratPP_1":
			dialog.text = NPCStringReactionRepeat("No he hasn't. And the corvette '"+pchar.questTemp.Slavetrader.ShipName+"' hasn't been seen in Port Royal.","You have already asked about this and I've answered.","I told you that you have already asked about this Gontier fellow.","Please, don't distract me from my work!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thanks. I'll keep searching.","Hm, well...","Yes, I have really asked ...","Pardon, "+npchar.name+"...",npchar,Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
