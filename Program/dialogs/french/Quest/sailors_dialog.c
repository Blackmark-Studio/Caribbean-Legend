// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
        case "First time":
			dialog.text = "Parle avec notre capitaine. Je n'ai rien à te dire.";
			Link.l1 = "D'accord.";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = "Parlez avec notre capitaine. Je n'ai rien à vous dire.";
			Link.l1 = "D'accord.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// Первый церковный генератор
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "Monsieur, cherchez-vous quelqu'un ?";
					Link.l1 = "Oui, l'ami. Puis-je voir le capitaine ?";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "Si vous cherchez notre capitaine. Il a récemment débarqué.";
					Link.l1 = "Très bien";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("Oh, tu es venu ici seul. Ha ! Dans ce cas, va voir notre capitaine. Parle-lui de tes tristes exploits...","Eh bien, on dirait que tu es fou, l'ami. Va voir notre capitaine et il te parlera.");
				Link.l1 = "Tant pis...";
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "Tu ferais mieux de le chercher au port.";
			Link.l1 = "Merci, mon ami.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
		break;
*/		
        //  на палубе <--
				
		// ugeen --> разговор с боцманом по генератору "Повод для спешки"
		case "On_MyShip_Deck":
			dialog.text = "Eh bien, c'était un sacré bazar, cap ! Nous étions à la taverne, en train de boire comme d'habitude quand nous avons entendu des cris. Nous avons couru hors de la taverne et avons vu qu'ils essayaient de vous arrêter. Qu'ils aillent se faire voir ! Alors nous avons décidé de quitter ce port inhospitalier.";
			link.l1 = "Oui, certains ont certainement une perception un peu étrange de la justice.";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// карты не было
				dialog.text = "Capitaine ! Ne vous inquiétez pas ainsi ! Il était évident qu'il n'y avait aucun moyen de fuir en paix, alors nous avons décidé de rendre visite au banquier local pour vérifier ses coffres. Voici votre part - "+int(pchar.questTemp.ReasonToFast.p9)+" pesos...";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "Capitaine ! Ne vous inquiétez pas ainsi ! Il était évident qu'il n'y avait aucun moyen de fuir en paix, alors nous avons décidé de rendre visite au banquier local et de vérifier ses coffres. Il y avait aussi une belle épée dans la boîte de prêt. Voici votre part - "+int(pchar.questTemp.ReasonToFast.p9)+" pesos et une épée...";
			}		
			link.l1 = "Bien joué les gars ! Bien joué ! Je suis fier de vous.";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, int(pchar.questTemp.ReasonToFast.p9));
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("ReasonToFast", "17");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;
		
		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		// разговор с боцманом по генератору 'Операция Галеон'
		case "CapComission_OnShipDeck":
			dialog.text = "Capitaine, votre ami s'est échappé.";
			link.l1 = "Quel ami ?";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "Eh bien, l'ami que vous avez sorti des cachots.";
			link.l1 = "Comment diable as-tu réussi à le perdre?!";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "Ce n'était pas notre faute, capitaine. Il s'est échappé par la latrine dans la mer... Nous avons essayé de lui tirer dessus, mais il faisait trop sombre là-bas...";
			link.l1 = "Merde! Vous avez vraiment perdu le sens des mesures ! Vous serez tous débarqués et envoyés travailler avec la canne à sucre ! Perdre un tel gros bonnet précieux ! Incroyable !";
			link.l1.go = "CapComission_OnShipDeck3";
		break;
		
		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("CaptainComission2", "25");	
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));			
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputationABS(pchar, "authority", 1);
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();		
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// <-- ugeen
		
		// разговор с боцманом по ситуациям в трюме
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "Capitaine, pardonnez-nous, c'était notre faute - le prisonnier s'est échappé.";
			link.l1 = "Quel prisonnier ? Qui s'est échappé ?";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "Eh bien, oh, oublié son nom, "+pchar.GenQuest.Hold_GenQuest.CapName+", n'est-ce pas ?";
			link.l1 = "Merde! Où regardais-tu?";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "Il est sorti de la cale et a sauté du bastingage. Nous ne lui avons pas tiré dessus pour éviter le bruit et pendant que nous préparions une chaloupe, il a été sauvé par ces putains de pêcheurs.";
			link.l1 = "Et pourquoi est-ce que je te paie! Fouettez la tête de la garde et privez-le de rhum pendant une semaine. A vos postes! Nous levons l'ancre...";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);			
			CloseQuestHeader("HoldQuest");	
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();					
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = "Salutations, capitaine. Il n'y a eu aucun accident pendant votre...";
			link.l1 = "Très bien, très bien, j'ai compris.... Il y a le prisonnier dans notre cale. Son nom est "+pchar.GenQuest.Hold_GenQuest.CapName+"Prends quelques hommes et emmène-le au port. Il est libre maintenant.";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "Il est vraiment libre ? Devons-nous le livrer sur une chaloupe ?";
			link.l1 = "Non sur une putain de tortue... Je pensais avoir été assez clair. Et dépêche-toi ! Nous devons lever l'ancre au début de la marée descendante.";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "Capitaine, il n'y a personne du tout sur le navire ! Quelque chose ne tourne pas rond ici... Tommy a dit qu'il avait vu un chat dans le poste de pilotage et c'était la seule âme vivante...";
			Link.l1 = "Idiot, les chats n'ont pas d'âme. On dirait qu'il n'a pas mis les pieds dans une église depuis longtemps ou qu'il n'y est jamais allé. As-tu été dans la cabine du capitaine ? J'ai besoin d'un journal de bord.";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "Non, ils ont bien des âmes. Il n'y avait pas de journal de bord et pas un seul instrument de navigation. Pas même une seule chaloupe...";
			Link.l1 = "Ils ne le font pas. A-t-il été arraché par une tempête ?";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "Ils en ont, capitaine. Les chats ont une âme. Capitaine, la chaloupe a été coupée et nous avons trouvé une épée sur le sol du cockpit. Elle est rouillée et ensanglantée. Tenez, regardez...";
			Link.l1 = "Arrête de me raconter ces conneries, jette ça, et arrête de parler de chats, bon sang ! Allons vérifier la cale et partons... Oh, quelque chose ne va vraiment pas ici et ça ne me plaît pas du tout...";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил
			
			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = int(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернем манёвренность, для интерфейса
			
			chrDisableReloadToLocation = false; // Откроем выход
			
			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;
		
		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
					Dialog.text = "Capitaine, j'ai un mauvais pressentiment à propos de cet endroit... Peut-être est-il temps pour nous de partir ?";
					Link.l1 = "Oui... Va à la chaloupe.";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "Capitaine, je ne resterai pas sur ce navire étrange si vous êtes prêt à l'emmener au port. Je ferais mieux de sauter moi-même à la mer.";
					Link.l1 = "Je ne suis pas disposé à faire cela... Je suis aussi un peu effrayé...";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "Peut-être devrions-nous le couler, capitaine ?";
					Link.l1 = "Pour laisser les ames des marins morts qui vivent ici nous visiter dans nos cauchemars ?";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "Bon Dieu, non ! Capitaine... pourquoi dites-vous cela ?";
			Link.l1 = "Ne deviens pas blême, je plaisantais... Va à l'embarcation du navire. Et je suppose que tu as raison après tout, peut-être que les chats ont vraiment une âme...";
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест
		
        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("Parle au patron. Je n'ai rien à te dire.","Je suis à mon poste. Toutes les questions vont au commandant du fort.");
			Link.l1 = "Très bien.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("Je suis vraiment occupé maintenant. Laisse-moi tranquille.","Ne me distrait pas de mon travail. Il n'y a rien à dire.");
			Link.l1 = "Pitié...";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;
		
		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple("Morgan voulait te dire 'une chose ou deux'... Il est quelque part ici, sur le pont.","Héhé, trouve Morgan. De mauvaises nouvelles t'attendent...");
			Link.l1 = "Bien.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
