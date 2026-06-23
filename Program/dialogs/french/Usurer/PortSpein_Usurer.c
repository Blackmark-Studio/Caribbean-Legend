// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous ?","Comment puis-je vous aider ?"),"Vous avez essayé de me poser cette question il n'y a pas longtemps...","Oui, laissez-moi deviner... Encore une fois en train de tourner en rond ?","Ecoutez, je m'occupe des finances ici, je ne reponds pas aux questions...","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Oumph, où est donc passée ma mémoire...","Vous avez deviné, je suis désolé...","Je comprends...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dis-moi, est-ce que le nom 'Juan' te dit quelque chose ?";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Je ne sais pas. Et je ne veux pas savoir. Je ne vous recommande pas de le savoir non plus. Et maintenant, vous devrez m'excuser, mais j'ai des affaires auxquelles je dois retourner. Je suppose que vous avez probablement aussi des affaires dont vous devez vous occuper ? Alors, partez et occupez-vous en.";
			link.l1 = "D'accord, très bien. Désolé de vous déranger...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = int(pchar.questTemp.Consumption.AskJuan)+1;
			if(int(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
