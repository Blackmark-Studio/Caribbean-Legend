//Jason общий диалог уличных матросов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//найм в команду
				{
					dialog.text = "Bonne journée, "+GetAddress_Form(NPChar)+". Je sais que vous êtes capitaine de votre propre navire. J'ai une affaire à vous proposer.";
					link.l1 = "Je vous écoute, "+GetAddress_FormToNPC(NPChar)+"Quel genre d'accord ?";
					link.l1.go = "crew";
					link.l2 = "Désolé, "+GetAddress_FormToNPC(NPChar)+", mais je suis pressé.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Eh, capitaine ! Que voulez-vous d'un simple marin ?","Bonne journée, monsieur. Comment puis-je vous aider ?","Bonjour, monsieur. Désirez-vous quelque chose?");
				link.l1 = "Ravi de vous rencontrer, camarade ! Mon nom est "+GetFullName(pchar)+"Tu as une minute pour parler ?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("J'ai une question pour vous.","J'ai besoin de quelques informations sur cette colonie.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Je voulais juste dire bonjour. À bientôt !";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Vous encore, monsieur ? Que voulez-vous d'autre ?";
				link.l1 = "As-tu une minute pour parler ?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("J'ai une question pour toi.","J'ai besoin d'informations sur cette colonie.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Non, l'ami, c'est rien. Bonne chance !";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat("Bonjour, mon ami."+GetFullName(npchar)+" à votre service, bon monsieur ! Que voulez-vous savoir ?","Ravi de parler avec vous, capitaine !","Eh bien... Je suppose que j'ai encore un peu de temps pour discuter...","Malheureusement, je dois partir maintenant. Adieu !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("As-tu quelque chose d'intéressant à me raconter ?","As-tu quelque chose d'intéressant à me raconter?","As-tu quelque chose d'intéressant à me raconter ?","Bien sûr. Bonne chance !",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

		case "crew":
			switch (hrand(2))
			{
				case 0: sTemp = "Me and my messmates were put shoreside from our last ship due to various sickness and injuries. But we are all healthy now and want to get back to work as sailors again. Do you want to hire us?"; break;
				case 1: sTemp = "Me and a few of my boys were paid off from a merchantman due to the end of its contract. We have been without a single piece of eight for a long time already so we want to get back to work again. Do you need some skillful sailors for your crew?"; break;
				case 2: sTemp = "Me and my mates just got back from a voyage two weeks ago. The ship's master has dismissed us and we've been having some great fun. But our pockets are empty now so it's time to set sail again. Do you want to hire us, captain?"; break;
			}
			dialog.text = sTemp;
			link.l1 = "Eh bien, je suis prêt à discuter de votre proposition. Combien êtes-vous et quelles sont vos compétences?";
			link.l1.go = "crew_1";
			link.l2 = "Je suis désolé, marin, mais j'ai déjà assez d'hommes. Tu devrais te trouver un autre capitaine.";
			link.l2.go = "exit";
		break;
		
		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "We are the best in working with sails and tackles. Not being overly modest, I'd say that we are professionals at ship handling, so don't worry, we won't let you down even in the strongest storms."; break;
				case 1: sTemp = "Most of all we like to be on the gun deck. Few of us even served on real warships. We can load and fire cannons in the way no one in your crew can. You can count on us in every hard fight!"; break;
				case 2: sTemp = "We're proper good boarders captain, did a few runs on privateers before this. We know the glitter of cutlasses and the smell of gunpowder and blood. That's our calling. It's not easy to defeat us in a hand-to-hand fight so you can always count on our blades, captain!"; break;
			}
			dialog.text = "Il y a "+sti(npchar.quest.crew.qty)+"de nous et nous n'engagerons que tous ensemble. Nous pouvons accomplir toutes les tâches de base des marins."+sTemp+"";
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "On dirait les hommes que je cherche. Et votre avance ?";
				link.l1.go = "crew_2";
				link.l2 = "Désolé, matelot, mais j'ai besoin d'autres compétences en ce moment. Tu devrais te trouver un autre capitaine.";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "Désolé, marin, mais je n'ai pas assez de place sur mon navire. Tu devrais te trouver un autre capitaine.";
				link.l1.go = "exit";
			}
		break;
		
		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" pour chaque. Et puis le salaire du marin ordinaire par mois. Nous ne demanderons rien d'excessif, capitaine.";
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "Tu es engagé ! Prends tes pièces. Maintenant, va à mon navire, il s'appelle '"+pchar.ship.name+",   juste  dans le port. Le maître d'équipage vous assignera tous des hamacs dans le quartier de l'équipage et s'occupera de vos repas.";
				link.l1.go = "crew_3";
			}
			link.l2 = "Malheureusement, je ne peux pas me permettre de payer pour vous tous. Vous devriez vous trouver un autre capitaine.";
			link.l2.go = "exit";
		break;
		
		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "Oui, oui, capitaine ! Je rassemblerai les gars et nous partirons immédiatement.";
			link.l1 = "Sois rapide, nous levons l'ancre à tout moment.";
			link.l1.go = "crew_4";
		break;
		
		case "crew_4":
			DialogExit();
			AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(pchar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(pchar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(pchar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(pchar, "Soldiers", iTemp); break;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(pchar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Hé, rengaine ton épée, capitaine. Aucun de nous n'a besoin de problèmes, n'est-ce pas ?","Eh, rengaine ton épée, capitaine. Aucun de nous n'a besoin de problèmes, n'est-ce pas ?");
			link.l1 = LinkRandPhrase("Très bien.","Comme vous voulez.","Comme vous dites.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
