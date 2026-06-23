// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions?","Que veux-tu, "+GetAddress_Form(NPChar)+"?"),"Vous avez déjà essayé de me poser une question "+GetAddress_Form(NPChar)+"...","Vous parlez de cette question pour la troisième fois aujourd'hui...","Ecoute, si tu n'as rien à me dire sur les affaires du port, alors ne me dérange pas avec tes questions.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis.","Je n'ai rien à dire."),"Peu importe.","En effet, déjà la troisième fois...","Désolé, mais je ne suis pas intéressé par les affaires du port pour le moment.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dis-moi, le nom 'Juan' te dit-il quelque chose?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Señor, il y avait une frégate ici sous le commandement de Miguel Dichoso en avril 1654. Il a disparu ensuite. Ne vous souvenez-vous de rien à ce sujet ? Peut-être que Dichoso était ici et a enregistré son navire...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Juan ? C'est tout ? Senor, êtes-vous ivre ou vous moquez-vous de moi ? Pouvez-vous vous souvenir d'un nom de famille ou au moins du nom de son navire ? C'est une colonie espagnole, bon sang. Savez-vous combien de Juan nous avons ici ? Je ne pourrai pas vous aider sans aucun détail.";
			link.l1 = "Je vois. Désolé de vous déranger...";
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
		
		case "guardoftruth":
			dialog.text = "Voyons mes notes... ah ha ! Oui, le Capitaine Miguel Dichoso était ici en avril 1654, à bord de la frégate 'Santa-Quiteria'. Il s'est enregistré comme venant de la colonie San-Andres, Providence. Il se dirigeait vers Cadix, Espagne. Il est parti le 14 avril 1654. C'est tout ce que j'ai.";
			link.l1 = "Naviguer vers l'Europe ? Je vois. Merci pour cela !";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "39");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
