// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Go ahead, what do you want?","We were just talking about that. You must have forgotten...","This is the third time today you've brought up some question...","Listen, this is a store. People buy things here. Don't disturb me!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, "+NPChar.name+", maybe next time.","Right, I've forgotten for some reason...","Yes, it really is the third time...","Hm, I won't...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Tell me, does the name Juan mean anything to you?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "In April 1654, a frigate docked at your port under the command of Captain Miguel Dichoso, after which he disappeared. Does his name ring any bells? Perhaps he bought some merchandise from you or said something...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Oh, come off it, captain! I've just had two Juans in my store today, and another one yesterday. What, am I supposed to remember each one?";
			link.l1 = "Fine. Sorry for bothering you...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Oh, captain, I've seen so many frigates and galleons come and go in that time, Miguels and Carloses...";
			link.l1 = "I see. So, you can't be of any help...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
