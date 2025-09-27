// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?","What do you want, "+GetAddress_Form(NPChar)+"?"),"Questions again, "+GetAddress_Form(NPChar)+"...","Questions, questions... How about we trade, "+GetAddress_Form(NPChar)+"huh?","Listen, how long do you plan to talk?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("No questions for now...","Sorry, I have nothing to say right now..."),"Once again, sorry...","Maybe it really is time to trade...","I'm sorry, let's trade...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Listen, does the name 'Juan' ring any bells?";
				link.l1.go = "Consumption";
			}			
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "No, it doesn't... Now, please don't bother me, I am quite busy... What an idiotic question...";
			link.l1 = "I see. Sorry for wasting your time...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
