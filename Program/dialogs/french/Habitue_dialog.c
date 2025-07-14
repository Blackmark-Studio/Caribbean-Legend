#include "DIALOGS\%language%\Common_Duel.c" //navy
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
    ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2, sQuestTitle, sStr;
	int DonationSize;
    	
	// Warship 18.05.08
	int iLa_Puesta; // La puesta - это ставка по-испански
    	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
    ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 25/06/06
    ProcessDuelDialog(NPChar, Link, Diag); //navy

	int iEnemyDice, iPCDice;
	int d1,d2,d3,d4;
	bool ok;
    ref sld;
    
	if (npchar.quest.Meeting != LastSpeakDate())
	{
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
		if (sti(npchar.money) < 150) npchar.money = 150;
        if (bBettaTestMode)
        {
            Dialog.CurrentNode = "Beta_test";
        }
	}
	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "Beta_test":
            dialog.text = "Sélection du type d'ivrogne (bêta)";
			link.l1 = "Ivrogne";
			link.l1.go = "Beta_test_alc";
            link.l2 = "Joueur de cartes";
			link.l2.go = "Beta_test_card";
			link.l3 = "Joueur de dés";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "Ivrogne sélectionné";
			link.l1 = "Continuez";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "Joueur de cartes (30% de ressentiment immédiat)";
			link.l1 = "Continuer";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "Dé joueur (30% de ressentir du ressentiment tout de suite)";
			link.l1 = "Continuez";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("Je pourrais être ivre mais je ne suis pas un idiot. Si je bois avec toi maintenant, le lendemain les soldats me prendront. Pas question !","Je ne suis pas un ennemi de ma propre ville. Je ne bois pas avec toi!",""+GetSexPhrase("camarade","lass")+", tu ferais mieux de quitter cet endroit pendant que tu le peux encore...");
				link.l1 = RandPhraseSimple("Eh bien, comme vous voulez...","Heh, tu sais, je n'ai pas besoin de me saouler autant. Ce n'est pas le bon moment pour ça."); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "Ha, raté"+GetSexPhrase("ter","s")+", certainement, j'ai entendu parler de toi, he-he. Les gens dans les tavernes disent que tu es un provocateur et un duelliste. Je dis que notre peuple n'est pas facilement effrayé, mais personne ne veut mourir pour une coupe de rhum. Je trouve effrayant de m'asseoir près de toi, donc je ferais mieux de passer mon chemin.";
				link.l1 = LinkRandPhrase("Bon débarras, alors!","Dégage, pendant que je suis encore de bonne humeur...","Va, va ! Perds-toi, nourriture pour poissons !");
				link.l1.go = "exit";
				link.l2 = "Attendez, je voulais poser une question....";
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = "Ne te tiens pas dans ma lumière, je ne peux pas voir les mouches dans la chope!";
            link.l1 = "Je ne reste pas debout...";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = "Hic! Oh, "+GetSexPhrase("camarade, tu as vraiment l'air d'un vieux loup de mer aguerri","mademoiselle, vous ressemblez certainement à un vieux loup de mer expérimenté")+"! Peut-être, voudriez-vous me payer un verre de rhum ?";
						link.l1 = "Je pourrais être un vieux loup de mer, mais cela ne signifie pas que j'achète de l'alcool pour la racaille...";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = "Je rejoindrais volontiers votre compagnie.";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "Et pourquoi cela ?";
							link.l2.go = "talk_with_alchogol_song";
						}
					break;

					case "1":
	                    if (rand(3) != 1 && ok)
	                    {
							switch (sti(npchar.quest.last_theme_game))
							{
							    case 0 :
									// Игра в карты boal 20/05/05 -->
	                                if (CheckNPCQuestDate(npchar, "Card_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Une partie de cartes, peut-être? Un jeu très intéressant!","Je propose de jouer à un jeu de cartes. Que diras-tu?");
										link.l1 = "Et pourquoi pas? D'accord, jouons.";
										link.l1.go = "Cards_begin";
										link.l2 = "Et quelles sont les règles de votre jeu?";
										link.l2.go = "Cards_Rule";
										link.l3 = "Pas maintenant.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Non, je ne joue plus aux cartes avec toi.";
						    			link.l1 = "Comme vous dites.";
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Une partie de dés, peut-être ? Un jeu très intéressant !","Je propose de lancer quelques dés. Que diras-tu?");
										link.l1 = "Et pourquoi pas? D'accord, jouons.";
										link.l1.go = "Dice_begin";
										link.l2 = "Et quelles sont les règles de votre jeu?";
										link.l2.go = "Dice_Rule";
										link.l3 = "Pas maintenant.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Non, je ne joue plus aux dés avec toi.";
					    				link.l1 = "Comme vous dites.";
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear()+" Tu trichais !!!";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("Éloigne-toi de ma table! Maintenant!"," Oh? Quoi? Qui est-ce? Hic... Va-t'en!");
	                        link.l1 = RandPhraseSimple("Boire condamne votre âme pécheresse ! Revenez à la raison !","Ne sois pas impoli avec moi.");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("Surveille ta langue, espèce de gueux ! Ou je vais t'apprendre les bonnes manières.","Et si je te frappe à la tête maintenant, je suppose que ça t'aidera à te dessouler.");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = "Je ne te dis rien, gredin"+GetSexPhrase("ter","s")+"! Et je ne pense pas que quelqu'un d'autre te parlera, cela signifie toujours des ennuis. Mais tu sais, les gens ont tendance à avoir la mémoire courte, donc dans un mois ou deux ils pourraient oublier ton aventure, si tu ne leur rappelles pas encore une fois, bien sûr, he-he! Adieu, mis"+GetSexPhrase("ter","s")+". ";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
		break;
		
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Eh bien, commençons alors...";
			link.l1.go = "Cards_begin";
			link.l3 = "Non, ce n'est pas pour moi...";
			link.l3.go = "exit";
		break;
		
		case "Cards_begin":
			Diag.tempnode = "Cards_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Cards_Node":
			Diag.tempNode = "first time";

			Dialog.text = "Définissons d'abord le pari alors (entrer le pari).";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "Je suppose que je dois y aller.";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "Tu es un tricheur notoire. Je ne vais pas jouer avec toi.";
                link.l1 = "C'est tous des mensonges! Enfin, peu importe.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Je vois que tu es fauché, "+GetSexPhrase("ami","cherie")+". Reviens quand tu seras riche.";
                link.l1 = "D'accord.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "J'ai déjà tout perdu ce que j'avais. Aujourd'hui n'est pas mon jour de chance.";
                link.l1 = "D'accord.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Tu te moques de moi ou quoi?! Jouant pour "+iLa_Puesta+" pesos?! Jouons pour des mises raisonnables, sinon je me retire !";
				link.l1 = "Ouais, tu as raison. Nous devons augmenter un peu le pari.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "J'ai changé d'avis, je ne joue pas.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Jouer pour une telle somme d'argent? Non, je vais passer, à moins que nous ne changions la mise.";
				link.l1 = "Ouais, tu as raison. Nous devons réduire un peu le pari.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "En fait, j'ai décidé de ne pas jouer du tout.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "D'accord, jouons pour "+iLa_Puesta+" pièces.";
			link.l1 = "Distribuez les cartes !";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = "Alors, quel est le pari? (Entrez le pari)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "Je pense que je ne jouerai pas, après tout...";
			link.l2.go = "exit_sit";
		break;
							
		case "Cards_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Card_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    // КОСТИ -->
	    case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Eh bien, commençons alors...";
			link.l1.go = "Dice_begin";
			link.l3 = "Non, ce n'est pas pour moi...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Diag.tempnode = "Dice_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Dice_Node":
		    Diag.tempNode = "first time";		    
			Dialog.text = "Définissons le pari (entre pari).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = "Je suppose que je dois y aller.";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "Tu es un tricheur notoire. Je ne jouerai pas aux dés avec toi.";
                link.l1 = "C'est tous des mensonges! Eh bien, peu importe.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Je vois que tu es fauche, "+GetSexPhrase("ami","chéri")+". Reviens quand tu seras riche.";
                link.l1 = "D'accord.";
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "J'ai déjà perdu tout ce que j'avais. Aujourd'hui n'est pas mon jour de chance.";
                link.l1 = "D'accord.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Tu te moques de moi ou quoi?! Jouer pour "+iLa_Puesta+" pesos par jour?! Jouons pour des mises raisonnables, ou je suis hors de ça!";
				link.l1 = "Ouais, tu as raison. Nous devons augmenter un peu le pari.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "J'ai changé d'avis, je ne joue pas.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Jouer aux dés pour tant d'argent? Non, je passe, à moins que nous ne changions la mise.";
				link.l1 = "Ouais, tu as raison. Nous devons réduire un peu le pari.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "En fait, j'ai décidé de ne pas jouer du tout.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "D'accord, jouons pour "+iLa_Puesta+" pièces par dé.";
			link.l1 = "Allons-y!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			dialog.text = "Alors, quel est le pari? (Entrez pari)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "Je pense que je ne jouerai pas, après tout...";
			link.l2.go = "exit_sit";
			break;

		case "Dice_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // КОСТИ <--

		/////////////////////////////////////////////
        case "talk_with_alchogol_song":
			dialog.text = "Eh bien, h-hic ! Les choses sont bonnes. Hic ! Tu ne le vois pas venir. Hi-ic ! Ce rhum est bon. Du rhum noir de la Jamaïque. hic !\nIci, mets et verse !";
			link.l1 = "D'accord, pourquoi pas.";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "Désolé mon ami, je dois partir.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "Les chope et les visages viennent et vont... Hic... Jusqu'à ce que je frappe le sol. Je bois tout le temps... Hic! Où est le tord-boyaux... Et quelle est la rime...";
			link.l1 = "Le rhum est ici et les filles sont jolies, toutes veulent un flibustier, mais seul le rhum semble être le mien.";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "Je n'ai pas de temps pour ça.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "Quand tu es triste, n'essaie pas de penser, viens ici, et laisse-nous boire ! Tout ira certainement bien, je suis ton ami, et tu es le mien !";
			link.l1 = "Avoir un ami, c'est bien sûr formidable, quand tu es parti il attendra, avec un ami il n'y a pas de haine, mais quand le rhum est parti il n'y a qu'un débat. Alors buvons, mon pote, avant que je ne parte et sois en retard...";
			link.l1.go = "exit";
		break;
		
		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.snd = "Voice\HADI\HADI028";
			dialog.text = LinkRandPhrase("Hic ! Maintenant c'est mieux ! C'est sûrement mieux ! Alors ? Tu vas me payer du rhum ou quoi ?","Asseyez-vous, "+GetAddress_Form(npchar)+", allons déguster une tasse de bon vieux rhum jamaïcain. Cela ne fait jamais de mal à la santé. Et si vous êtes intéressé par ce qui se passe - vous ne trouverez jamais un meilleur endroit que cette taverne, je vous l'assure. Un peu d'argent, quelques tasses de bon rhum - et vous saurez tout ce que vous aviez besoin de savoir, et même plus, faites confiance à un vieux client...","Heh, s'il vous plaît, asseyez-vous, "+GetSexPhrase("mon bon ami","mademoiselle")+", allons prendre un verre... Pourquoi ne pas boire en bonne compagnie ? Vous pouvez entendre beaucoup de choses intéressantes si vous êtes patient et buvez lentement, à petites gorgées... Il y a des capitaines qui se vantent de leurs aventures, il y a beaucoup d'autres qui révèlent des choses importantes, quand ils ne se contrôlent plus... Beaucoup de gens passent leur temps là-bas, et beaucoup ont quelque chose à raconter, croyez-moi, "+GetSexPhrase("mon bon ami","Mademoiselle")+".");
			link.l1 = "Et pourquoi pas ! Barman ! Du rhum, pour nous deux !";
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "Certainement ! Avez-vous entendu... les bandits pillent même les églises !";
				link.l1 = "Eh bien, cela ressemble à des pirates, qui d'autre...";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "Quels pirates ? Juste vos terriens ordinaires, et bien sûr les maudits locaux... S'ils étaient des visiteurs, ils n'auraient pas su quand les coffres de l'église étaient pleins. Et ils auraient à peine réussi à entrer dans ce gâchis, de toute façon.";
				link.l1 = "Des gars audacieux, c'est sûr. Ils ont si galamment ouvert une barre de porte fragile...";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "A-ha. Et des astucieux aussi. Qui se dévoilerait de telle manière?";
				link.l1 = "C'est vrai. Toute la paroisse économisait de l'argent pour le donner à l'église, et maintenant ces malins ont fait fortune avec ? Ils seront sûrement attrapés. Tout le monde les cherche maintenant.";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "A peine. Qui va chercher ça? Ils ont simplement volé l'église et quitté la ville, disparus comme le vent. La jungle est grande, très grande, tu les chercherais là-dedans jusqu'au jour du jugement dernier. Et après quelques mois, les gens vont simplement tout oublier, marque mes mots!";
				link.l1 = "Je ne pense pas. De telles choses ne peuvent pas être pardonnées.";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "La mémoire d'un homme est comme une barque qui fuit. Les gens oublieront et pardonneront. Mais Dieu?! Il voit tout. C'est lui que tu dois craindre. Je te dis, il y a dix ans, quelque chose de terrible est arrivé à un vieux camarade à moi. Lui aussi, manquait de respect pour le Créateur, et a presque été directement au diable de mer...";
				link.l1 = "Désolé mon ami, je dois partir. Nous parlerons de ton pote une autre fois. À bientôt.";
				link.l1.go = "Alcogol_GenQuest_Church_2_6";
			break;
			
		case "Alcogol_GenQuest_Church_2_6":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");			
			string sGenLocation = QuestGetGangLocation(PChar.GenQuest.ChurchQuest_2.QuestTown);
			PChar.GenQuest.ChurchQuest_2.QuestGangJungle = sGenLocation;
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			PChar.GenQuest.ChurchQuest_2.WayOfShortVariant = true; // Нужно для проверки при убийстве банды
			SetFunctionTimerConditionParam("Church_GenQuest2_TimeIsLeft", 0, 0, 1, MakeInt(24 - GetHour()), false);
			Log_TestInfo("The bandits who raided the church shall be in location - " + sGenLocation + " Time to search for them - 1 day");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
			break;
		// <-- Церковный генератор. Квест №2
		//--> работорговец
			case "Jamaica_ratH_1":
				dialog.text = "Oh Francois! Bien sûr, je me souviens de ce gars... Non, je ne sais pas. Mais, tu sais, tu peux demander à notre serveuse à propos de lui. Pendant tout le temps qu'il a vécu ici, elle passait chaque nuit avec lui. Une garce elle est, c'est sûr. Peut-être qu'il a bavardé quelque chose à elle.";
				link.l1 = "Merci pour le conseil, mon pote. J'irai lui parler.";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = "Ouais, des choses très étranges peuvent arriver en pleine mer parfois. Lors de mon dernier voyage, j'ai vu quelque chose de vra-iment...";
				link.l1 = "Vas-y, raconte-moi, juste ne l'exagère pas trop. Je vais te chercher plus de rhum pendant ce temps.";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = "Je jure devant Dieu, noble"+GetSexPhrase("monsieur","madame")+" - Je l'ai vu de mes propres yeux... Un navire naviguait, mais au lieu de marins, il y avait des singes geants... ou des macaques... des singes, vous savez.";
				link.l1 = "Quoi?! Dis-moi, ami, tu bois aussi pendant la garde?";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = "Frappez-moi aveugle si je mens ! N'avez-vous jamais entendu parler de la crevette singe ? Baise-moi, crevette ha-ha ! ... Le navire singe.";
				link.l1 = "Quel navire de singe?";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = "Ohé, je dis que je l'ai vu de mes propres yeux. Il y avait une tempête. On ne voyait rien, et puis le navire est apparu de nulle part. Voiles déchirées. Son foc était cassé tout comme sa grand-voile, et pot et mille sabords tout était cassé! Et pourtant, elle filait à contre-vent! \nEt il y avait des singes sur son pont ... beaucoup d'entre eux comme ... une colonie de phoques! Et un gorille pur se tenait à la barre! Neuf pieds, chemise rouge et des dents de requin à la place de la croix sur sa poitrine... Les yeux sont rouges, les crocs clignotent, il nous a vus et a crié quelque chose...";
				link.l1 = "Tu mens comme un arracheur de dents, mon ami. Tu sais, on peut voir des choses quand on est saoul. Ensuite, tu vas me dire qu'elle était le Hollandais Volant.";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = "Non, ce n'était pas un Hollandais. Je te dis la vérité ! C'était une barque, et sur la poupe il y avait une inscription - "+pchar.questTemp.Slavetrader.ShipName+".";
				link.l1 = "Sacrebleu! Je crois que je sais de quels 'singes' tu parles. En effet, le rhum peut délier les langues - il suffit d'écouter...";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = "Vois - Je te le disais! Et tu ne me croyais pas!.. D'accord, buvons une dernière tasse, et je suis prêt à partir.";
				link.l1 = "D'accord, merci pour une histoire intéressante. Je dois y aller. Bonne chance à toi, mon pote.";
				link.l1.go = "exit_sit";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1 = "location";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1.location = pchar.questTemp.Slavetrader.Island.Shore;
				Pchar.quest.Slavetrader_EscapeSlave.function = "Slavetrader_EscapeSlaveInShore";
				AddQuestRecord("Slavetrader", "22_4");
				AddQuestUserData("Slavetrader", "sAreal", pchar.questTemp.SlavetraderAreal.add);
				pchar.questTemp.Slavetrader = "FindMayak";
			break;
		
		//Голландский Гамбит, против всех
		case "Lucas_Tavern":
			DelMarkInTavernHWIC();
			dialog.text = "Non, capitaine. La vie de marin n'est pas pour moi. Tu sais, j'avais aussi un navire autrefois, mais... j'ai eu une sacrée malchance.";
			link.l1 = "Ecoutez - j'ai vu un navire inhabituel au large - 'Meifeng' est son nom. Je n'ai jamais vu un navire comme celui-ci auparavant. Qui est le propriétaire? Peut-être, est-il à vendre? J'aimerais y jeter un coup d'oeil.";
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = "Ha ! À peine, capitaine. Je ne pense pas que le gars chinois vous vendra, ou à quiconque d'autre, son navire.";
			link.l1 = "Un Chinois ? Il y a des Chinois à Curacao ? Et même un capitaine de son propre navire ?";
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = "Il y a, comme vous pouvez le voir. Mais ce n'est pas son navire, en fait - il appartient à la Compagnie de Commerce. Ils disent, monsieur Rodenburg, le vice-directeur et maintenant gouverneur par intérim, le possède.";
			link.l1 = "Alors, Matthias Beck a pris sa retraite?";
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = "Ha ! Mynheer, vous devriez vraiment visiter la terre plus souvent - ou au moins vous soucier des nouvelles. Matthias Beck a été déchargé et mis derrière les barreaux jusqu'à ce que toutes les circonstances soient éclaircies.";
			link.l1 = "Tu ne dis pas! En effet, je passe trop de temps en mer. Et quand cela s'est-il passé?";
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = "En fait, il y a juste quelques jours. Une brigantine de courrier est arrivée au port. Elle n'était pas en meilleur état, clairement elle a participé à un combat féroce. Le capitaine est allé directement chez monsieur Rodenburg avec son rapport, et en seulement quelques heures Matthias Beck a été arrêté par monsieur Rodenburg et le commandant sur des soupçons de collaboration avec le renseignement anglais.";
			link.l1 = "Vous dites des choses terribles. Comment un gouverneur de Curaçao peut-il être un espion anglais?";
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = "Honnêtement, j'ai du mal à le croire, moi aussi. J'ai entendu dire que bientôt le directeur de la Compagnie, Peter Stuyvesant lui-même, arrivera ici. Apparemment, il va mener personnellement l'enquête.";
			link.l1 = "Alors vous avez raison. Il peut être risqué de déranger monsieur Rodenburg à cette heure.";
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = "Bonne réflexion, capitaine! D'autant plus que 'Meifeng' est actuellement en cours de chargement. Elle vient de revenir de voyage de la côte sud du Main, et elle va bientôt reprendre la mer. Et, je vous le dis, des choses étranges se passent là-bas. Les marins hollandais et les gardes de la Compagnie ont été relevés de leur poste, et un autre équipage est en train d'être formé. Et je jure par toutes les coupes de rhum que j'ai bu dans ma vie, ces nouveaux volontaires sont tout à fait différents, tous pirates, bandits et coupe-gorges!";
			link.l1 = "Un miracle, en effet! Eh bien, c'est dommage! Un si beau navire... Eh bien, le sort en a décidé autrement... Merci pour cette histoire intéressante et pour les nouvelles! C'était un plaisir de vous parler!";
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = "Eh bien, merci pour la compagnie et le rhum, capitaine! Repassez un de ces jours!";
			link.l1 = "Bien sûr que je le ferai !";
			link.l1.go = "exit_sit";
			AddQuestRecord("Holl_Gambit", "3-44");
			pchar.questTemp.HWIC.Self = "AttackMeifeng";
			//ставим прерывание на выход в море Мейфенг
			pchar.quest.HWIC_Meifeng.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Meifeng.function = "CreateMeifengOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 12, false); // таймер
			pchar.quest.Meifeng_fail.over = "yes"; //снять прерывание
			Group_DelCharacter("Meifeng_Empty", "Longway");
			Group_DeleteGroup("Meifeng_Empty");//удалить Мейфенг из порта
		break;
		
			//Jason --> поиск дезертира
		case "FindFugitiveHb":
			npchar.quest.fugitive = "true";
			if (npchar.location == pchar.GenQuest.FindFugitive.City+"_tavern" && sti(pchar.GenQuest.FindFugitive.Chance) == 2)
			{
				pchar.GenQuest.FindFugitive.Shore = SelectQuestShoreLocation();
				dialog.text = "Ha ! "+pchar.GenQuest.FindFugitive.Name+"? Je sais, je sais... Il est très peu sociable, ce collègue à toi. Un loup solitaire, pour ainsi dire. Il navigue sur son long bateau le long de la côte de l'île toute la journée jusqu'à la nuit. Les gens pensent qu'il est un pêcheur, mais en réalité, il est un pêcheur de perles... He-he ! Je le sais pour sûr, sacré nom d'un chien !";
				link.l1 = "Heh ! Alors... pouvez-vous me dire où le trouver ?";
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+"? Non, je jure que je n'ai jamais entendu parler de lui... Mais toi - Hic ! Tu peux demander à notre barman - il doit sûrement savoir !";
				link.l1 = "Hmm... D'accord, je vais me renseigner un peu plus. Eh bien, mon pote, merci pour la compagnie. A bientôt !";
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = "Bien sûr, je peux! Chaque matin, il peut être trouvé sur la rive, à "+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gén")+". Venez aussi tôt que possible sinon il mettra les voiles et vous devrez attendre le lendemain matin.";
			link.l1 = "Merci ! Tu m'as beaucoup aidé, mon ami ! À bientôt !";
			link.l1.go = "exit_sit";
			pchar.GenQuest.FindFugitive.Chance = 3; // чтобы никто больше не говорил
			AddQuestRecord("MayorsQuestsList", "12-3");
			AddQuestUserData("MayorsQuestsList", "sShore", XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen"));
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_shore";
			LAi_SetLoginTime(sld, 4.0, 6.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.Shore, "goto", "goto1");
		break;
		//<-- поиск дезертира
		
		// Карибские нравы
		case "trial_spy":
			dialog.text = "Il traînait dans notre chantier naval, posant des questions aux charpentiers de marine sur ceci et cela. Et c'est ce qui lui a joué un vilain tour. Certaines personnes ont alerté le commandant sur des personnes suspectes qui traînaient en ville, alors il l'a détenu, et ensuite on a découvert qu'il n'était pas du tout marchand.";
			link.l1 = "Je présume, il allait voler un projet secret de votre charpentier naval?";
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = "Qui sait ? Mais je suis tout à fait sûr qu'il s'intéressait en premier lieu au galion 'Alacantara' ! Hic ! Je peux le jurer ! Ce navire est équipé par le gouverneur lui-même, donc je parie que ce scélérat a essayé de découvrir quelque chose à son sujet.";
			link.l1 = "Ha ! C'est fort probable. Assurément, le gouverneur la chargera avec quelque chose de précieux...";
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = "Cela va sans dire ! Cela devrait vraiment valoir la peine, je vous le dis ! Oh, et les gens disaient que les pêcheurs ont vu un navire militaire étranger dans ces eaux... une frégate très probablement. Peut-être, c'est de là que vient cet espion ?";
			link.l1 = "Ouais, ça peut l'être... D'accord, mon pote, merci pour la compagnie, mais je dois y aller !";
			link.l1.go = "exit_sit";
			pchar.questTemp.Trial = "spy_drink";
			
			if(CheckAttribute(pchar,"questTemp.trialHabitueId"))
			{
				if (GetCharacterIndex(pchar.questTemp.trialHabitueId) != -1)
				{
					sld = characterFromId(pchar.questTemp.trialHabitueId);
					sld.lifeday = 0;
					DeleteAttribute(pchar,"questTemp.trialHabitueId");
					LAi_CharacterDisableDialog(sld);
					DelLandQuestMark(sld);
				}
			}
			// belamour legendary edtion -->
			if (GetCharacterIndex("PortoBello_Poorman") < 0)
			{
				// новый нищий
				sld = GetCharacter(NPC_GenerateCharacter("PortoBello_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false, "slave"));
				sld.city = "PortoBello";
				sld.location	= "PortoBello_town";
				sld.location.group = "goto";
				sld.location.locator = "goto15";
				sld.forStay.locator = "goto15"; //где генеримся в случае стояния
				sld.forSit.locator0 = "goto3";
				sld.forSit.locator1 = "goto25"; //три локатора, где генеримся в случае сидения
				sld.forSit.locator2 = "goto12";
				LAi_SetLoginTime(sld, 9.0, 21.99);
				sld.Dialog.Filename = "Common_poorman.c";
				LAi_SetPoorType(sld);
				LAi_SetHP(sld, 50.0, 50.0);
				sld.greeting = "poorman_male";
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			}
			sld = characterFromId("PortoBello_Poorman");
			LAi_RemoveLoginTime(sld);
			ChangeCharacterAddressGroup(sld, "Portobello_town", "goto", "goto15");
			AddLandQuestMark(sld, "questmarkmain");
			DelLandQuestMark(characterFromId("portobello_tavernkeeper"));
			// <-- legendary edtion
			AddQuestRecord("Trial", "14");
		break;
		
		case "sit_2":
			Statistic_AddValue(pchar, "TavernDrink", 1);
			AddMoneyToCharacter(pchar, -2);
			//navy --> Alcohol - rum count;
			if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
			{
				if (CheckAttribute(pchar, "questTemp.Rum"))
				{
					pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
				}
				else pchar.questTemp.Rum = 1;
			}
			else 
			{
				if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
			}				
			//<-- navy
			if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("",0,0,0, 0, 30);
			
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
			
			// Sinistra - Квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerAlkash") && npchar.city == "baster")
			{
				dialog.text = "A votre santé et à votre générosité !";
				link.l1 = "Mon pote, as-tu vu un gars chinois en ville?";
				link.l1.go = "PZ_BasTerAlkash_1";
				break;
			}
			// <== Квест "Путеводная звезда" - Sinistra
			
			dialog.text = LinkRandPhrase("Tu es un "+GetSexPhrase("vrai ami","superbe demoiselle")+"! Enchanté de vous rencontrer ! Santé !","Hic! C'est un excellent rhum! Hic... Santé!","A votre santé et à votre générosité !");
			link.l1 = "Heh, c'est du rhum fort en effet. Bon, je dois y aller. Passez un bon moment !";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "Une autre tasse, ça vous dérange?";
				link.l2.go = "sit_3";
			}

			link.l4 = LinkRandPhrase("On dirait que j'ai passé une éternité en mer. Des nouvelles?","Que disent les gens ? Assurément, je vais vous acheter des boissons.","Dites-moi, mon pote, quelles sont les histoires populaires dans les tavernes maintenant?");
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "Oh! Une excellente idée!";
					link.l1 = "Barman! Plus de rhum!";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "A toi! Oh, diable! Qui est-ce?";
					link.l1 = "Hein? Quoi? Ou? Je dois voir des choses.";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = "Buvons, alors ! Encore un ?";
					link.l1 = "Allez-y !";
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple("Eh, toi, "+GetAddress_Form(NPChar)+", vous pensez sûrement que tout le monde vous admire, n'est-ce pas? Eh bien, si vous me demandez, vous n'êtes qu'un brigand ordinaire!.. Et un meurtrier! 'Pirate noble'! Ha! Un bandit est un bandit... Hic... Que ce soit sur terre ou en mer..","Hic ! "+GetSexPhrase("Fri... Fripon","Fi... Immondice")+"! Tu veux que je boive jusqu'à ce que je m'évanouisse - hic - et ensuite tu voleras tout mon argent!");
						link.l1 = "Je vois que tu as déjà bu assez... Va dormir... Et je dois partir...";
						link.l1.go = "exit_sit";						
						link.l2 = "Je n'aime pas ton ton, matelot. Tiens ta langue, d'accord?";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "Qui viens-tu de traiter de bandit, toi qui ne connais que la terre?! Voyons ce que tu vas dire avec un trou dans le ventre!";
						link.l3.go = "sit_case_2_enemy2";
					link.l4 = "Calme-toi ! As-tu oublié ? Je suis ton seul véritable ami !";
					link.l4.go = "sit_case_2_friend";		
					}
					else
					{
						// Captain Beltrop, 27.06.21, новый вариант
						/* if (rand(1) == 0)
						{
							Diag.CurrentNode = Diag.TempNode;
							AddDialogExitQuestFunction("Tavern_SetBadHabitue");
							DialogExit();
						}
						else
						{ */
							dialog.text = RandPhraseSimple("Pourquoi tu me regardes ainsi? Tu attendras que je m'évanouisse - hic - et ensuite tu voleras tout mon argent! D'où vient toute cette racaille?! Hic... Pas de place pour une personne décente dans cette taverne?","Tu me respectes ?.. Ouais, toi ! Tu me respectes ?! Tu ferais mieux de faire attention... Je ne suis pas celui avec qui on joue... Un coup entre les yeux... Et tu es aussi bon que mort...");
							link.l1 = "Mate, tu es saoul comme un cochon. Rentre chez toi et dors-le... Et je dois aussi y aller...";	
							link.l1.go = "exit_sit";
							link.l2 = "Tiens tes chevaux, mon pote. Attention à qui tu parles.";
							link.l2.go = "sit_case_2_enemy1";
							link.l3 = "Qu'est-ce que tu viens de dire ?! Je vais te donner une leçon !";
							link.l3.go = "sit_case_2_enemy2";
							link.l4 = "Calmez-vous! M'avez-vous oublié? Je suis votre seul véritable ami!";
							link.l4.go = "sit_case_2_friend";	
						//}
					}
				break;

				case 4:
					dialog.text = "Ecoutez! Vous êtes un bon homme! Peut-être, vous m'aiderez... avec une affaire?";
					link.l1 = "Non, je pense que je dois partir maintenant.";
					link.l1.go = "exit_sit";
					link.l2 = "Bien sûr ! Hic ! Nous sommes amis... n'est-ce pas ? Hic !";
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) || CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
					{
						dialog.text = "...Et alors j-j'ai attrapé son sabre par la l-lame...";
						link.l1 = "...et puis elle a dit...";
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = "...Et puis j-j'ai attrapé son sabre par la l-lame...";
						link.l1 = "...hic! ...et puis elle a dit...";
						link.l1.go = "sit_case_4_exit";
					}
				break;
			}
		break;

		case "sit_case_5_exit": // дуэль
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("fighting");
		break;

		case "sit_case_4_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			dialog.snd = "Voice\HADI\HADI037";
			dialog.text = "Le p-point, c'est qu'un des s-soldats m'a insulté. C-C'est ça!";
			link.l1 = "Un s-soldat? N-Non, je pense que je vais passer mon tour.";
			link.l1.go = "exit_sit";
			link.l2 = "Calmez-vous! M'avez-vous oublié? Je suis votre seul véritable ami!";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "Vous ? Quel genre d'ami êtes-vous ? N-non ! Vous... vous voulez me tuer ! C-C'est ça !";
			link.l1 = "Eh bien, certainement que tu as déjà assez bu. Adieu.";
			link.l1.go = "exit_sit";
			link.l2 = "Quoi? Je vais te prouver que je ne vais p-pas te tuer! Je... Je vais te couper la main!... Sanssss... elle tu ne peux pas être tué!... Hic!";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "Aaaah! Prends "+GetSexPhrase("lui","elle")+" éloigne-toi de moi!";
			link.l1 = "Calme-toi... hic... Ça ne va pas faire mal !... C'est moins douloureux qu'un rasage !";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Ne tentez pas de m'intimider ! Hic ! Je ne suis pas si facilement effrayé !.. Et vous - vous devriez être pendu à la potence... Avec tous les vôtres - hic ! Vous pouvez bien gonfler vos plumes autant que vous le voulez - mais vous sentez toujours le poisson pourri ! Et je ne vais pas tenir ma langue quand - hic ! - je parle à des gens comme vous ! Vous me dégoûtez tous !";
			link.l1 = "Argh, pourquoi je parle à un tel ivrogne de toute façon... Je suppose que je vais prendre une bouffée d'air frais...";
			link.l1.go = "exit_sit1";
			link.l2 = "Tu es trop audacieux, mon pote. Je vais te faire ravaler tes paroles!";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Quoi ?! Je vais t'étrangler de mes propres mains ! Hic... Personne ne m'a échappé - hic! - jusqu'à présent !";
			link.l1 = "N'es-tu pas un cochon ivre? Pour gâcher une si belle soirée... Très bien, va attraper tes cafards - et je me tire d'ici.";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear()+"Je vois que tu ne vas pas te taire. Eh bien, alors une leçon de bonnes manières est due.";
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Approche, espèce de coquin ! Tu recevras ce que tu mérites !",RandSwear()+"Je te donnerai ce que tu mérites!","Ha ! Bien, chien de mer - voyons comment tu te débrouilles sur la terre ferme !");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Je jure que tu le regretteras!","Je vais raccourcir ta sale langue jusqu'aux oreilles !"),RandPhraseSimple("Je vais t'éventrer comme un cochon, de ton cul vers ton trou à merde que certains appellent bouche!","Je jure que je vais te faire taire !"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Hey, les garçons ! Balayons ces ordures hors de notre ville !";
				link.l1 = RandPhraseSimple(RandSwear()+"Dites vos prières, salauds !","Oh, donc tu n'es pas seul?! Eh bien, tant mieux pour toi - tu auras de la compagnie en enfer!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Approche, toi, vaurien ! Tu obtiendras ce que tu mérites !",RandSwear()+"Je te donnerai ce que tu mérites !","Ha ! D'accord, chien de mer - voyons comment tu te débrouilles sur la terre ferme !");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Je te jure que tu le regretteras !","Je raccourcirai ta langue vile jusqu'aux oreilles !"),RandPhraseSimple("Je vais t'éventrer comme un porc, de ton cul vers ton trou à merde que certains appellent bouche!","Je jure que je vais te faire taire !"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Eh, les garçons! Balayons ces déchets hors de notre ville!";
				link.l1 = RandPhraseSimple(RandSwear()+"Dites vos prières, salauds!","Oh, alors tu n'es pas seul?! Eh bien, tant mieux pour toi - tu auras de la compagnie en enfer!");
				link.l1.go = "fight_right_now_1";
			}
		break;		
		
		case "exit_sit":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "exit_sit1":
			ChangeCharacterComplexReputationToNeutral(pchar,"nobility", 2.0);			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
				
		case "tavern_keeper":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
		
		// Captain Beltrop, 27.06.21, новый вариант
		case "bad_habitue":
			dialog.text = "Eh, je n'ai pas compris quelque chose ! Dès que je suis allé au coin, un nouveau bleu a atterri à ma place. Dégage d'ici !";
			link.l1 = "C'est toujours comme ça : tu t'assois juste à la table et il s'avère qu'elle est déjà prise... Garde ta place, j'allais partir de toute façon.";
			link.l1.go = "bad_habitue1";
			link.l2 = "Encore une phrase comme celle-là de ta bouche sale et ce sera la dernière chose que tu diras de ta vie, comprends-tu?";
			link.l2.go = "bad_habitue2";
			link.l3 = "Je ne sais pas si c'est vraiment ta place, mais je ne te laisserai pas me parler ainsi. Surveille tes paroles.";
			link.l3.go = "bad_habitue3";
		break;
		
		case "bad_habitue1":
			DialogExit();
			pchar.questTemp.BadHabitueSit = true; // атрибут усаживания
			AddDialogExitQuest("exit_sit");
		break;
		
		case "bad_habitue2":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Allons-y, canailles ! Vous allez avoir votre compte !",RandSwear()+"Maintenant, je vais te dépouiller correctement !","Ha ! Allez, marin - voyons ce que tu peux faire sur terre !");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Je jure que tu le regretteras !","Je vais couper ta putain de langue court !"),RandPhraseSimple("Je vais t'éventrer comme un cochon, de ton postérieur à ce trou à merde qu'on appelle ta bouche!","Je jure que je vais te faire taire!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Allons-y les gars ! Débarrassons notre ville de cette écaille !";
				link.l1 = RandPhraseSimple(RandSwear()+"Priez, vous salauds!","Oh, tu n'es pas seul ! Eh bien, tu auras de la compagnie en enfer !");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "bad_habitue3":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Allons-y, coquins! Vous allez avoir votre compte!",RandSwear()+"Maintenant, je vais te dépouiller comme il faut !","Ha ! Allez, marin - voyons ce que tu peux faire sur terre !");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Je jure que tu le regretteras!","Je vais te couper cette putain de langue!"),RandPhraseSimple("Je vais t'éventrer comme un cochon, de ton cul vers ton trou à merde que certains appellent bouche !","Je te jure que je vais te faire taire !"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Allons-y les gars! Débarrassons notre ville de cette vermine!";
				link.l1 = RandPhraseSimple(RandSwear()+"Priez, vous enfoirés!","Oh, tu n'es pas seul! Bien, tu auras de la compagnie en enfer!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		//--> Sinistra Длинные тени старых грехов
		case "DTSG_NightIskat":
			dialog.text = "B-bien sûr, nous nous connaissons tous ! Pourquoi demandes-tu ?";
            link.l1 = "Je voulais rendre visite au prêteur sur gages et j'ai découvert qu'il avait vendu sa vieille maison. Savez-vous où il vit maintenant?";
            link.l1.go = "DTSG_NightIskat_2";
		break;
		
		case "DTSG_NightIskat_2":
			dialog.text = "Pourquoi avez-vous besoin de lui à cette heure, hic ? Visitez simplement la banque le matin !";
            link.l1 = "J'ai besoin d'argent de toute urgence. Laissez le riche travailler pour cela pour changer! Leur genre nous appelle toujours des parasites qui ne font que mendier, se plaindre et ne jamais rendre ce que nous devons.";
            link.l1.go = "DTSG_NightIskat_3";
		break;
		
		case "DTSG_NightIskat_3":
			dialog.text = "Ha-ha-ha, hic, oui, laissez-le travailler! Savez-vous où vivait notre glorieux capitaine Fleetwood?";
            link.l1 = "Bien sûr, qui ne connaissait pas Richard. Maintenant, c'est le banquier qui y vit?";
            link.l1.go = "DTSG_NightIskat_4";
		break;
		
		case "DTSG_NightIskat_4":
			dialog.text = "Tu as raison. Quand tu seras là, mon ami - dis-lui qu'il est devenu trop suffisant.";
            link.l1 = "Heh-heh, je vais certainement faire ça. Adieu.";
            link.l1.go = "DTSG_NightIskat_5";
		break;
		
		case "DTSG_NightIskat_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_NightIskat");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("Knippel");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Knippel_SluhSmertFleetWood";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//<-- Длинные тени старых грехов
		
		//--> Путеводная звезда
		case "PZ_BasTerAlkash_1":
			dialog.text = "Ha-ha-ha, ai-je vu un Chinois? Nous l'avons tous vu!";
			link.l1 = "Qu'est-ce qui est si drôle? Je ne parle pas d'un cirque ambulant, si c'est ce que vous voulez dire. Je parle d'un combattant, d'un officier de marine.";
			link.l1.go = "PZ_BasTerAlkash_2";
		break;
		
		case "PZ_BasTerAlkash_2":
			dialog.text = "Ah, je vois ce que tu veux dire ! Oui, je l'ai vu. Même après avoir dégrisé, je ne pouvais pas arrêter de le voir... Je ne peux pas l'oublier !";
			link.l1 = "C'est intéressant. Continue. Prenons un autre verre - tu bois probablement maintenant pour tout oublier. Dis-moi ce que tu as vu avant de le faire.";
			link.l1.go = "PZ_BasTerAlkash_3";
		break;
		
		case "PZ_BasTerAlkash_3":
			dialog.text = "Un cirque ambulant, mon cul ! Il sautait, tournait, et faisait tournoyer ce sabre - Je n'ai jamais vu personne aussi doué et terrifiant avec une arme.";
			link.l1 = "Cela ressemble à lui. Contre qui se battait-il? Vous souvenez-vous?";
			link.l1.go = "PZ_BasTerAlkash_4";
		break;
		
		case "PZ_BasTerAlkash_4":
			dialog.text = "Les gardes, mon pote! Il les regarde avec des yeux étroits aussi! Bien que, je pense qu'il a toujours cette expression. Qu'en pensez-vous?";
			link.l1 = "Je ne sais pas, mon pote. Continue. Pensait-on qu'il était un espion? Pourquoi les gardes l'ont-ils attaqué?";
			link.l1.go = "PZ_BasTerAlkash_5";
		break;
		
		case "PZ_BasTerAlkash_5":
			dialog.text = "Qui sait? Ils essayaient de comprendre ce qu'il faisait en ville...";
			link.l1 = "Alors, l'ont-ils arrêté? Ou...";
			link.l1.go = "PZ_BasTerAlkash_6";
		break;
		
		case "PZ_BasTerAlkash_6":
			dialog.text = "Ha, une chance mince! Ils n'ont pas pu l'attraper. Il a abattu les gardes en ville et s'est enfui dans la jungle. Ils ont envoyé plusieurs groupes après lui, mais aucun n'est revenu. Pouvez-vous imaginer? Il a transformé cette grotte en une vraie forteresse!";
			link.l1 = "C'est quelque chose. Repose-toi et essaie de l'oublier. Je pense que je vais partir maintenant - ma tête tourne.";
			link.l1.go = "PZ_BasTerAlkash_7";
		break;
		
		case "PZ_BasTerAlkash_7":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerAlkash2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			pchar.questTemp.PZ_BasTerTurma = true;
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
			DelMapQuestMarkIsland("Guadeloupe");
			AddQuestRecord("PZ", "3");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			PChar.quest.PZ_BasTerPeshera.win_condition.l1 = "location";
			PChar.quest.PZ_BasTerPeshera.win_condition.l1.location = "Guadeloupe_CaveEntrance";
			PChar.quest.PZ_BasTerPeshera.win_condition = "PZ_BasTerPeshera";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
		break;
		
		case "Sotta1":
			dialog.text = "Je ne l'ai pas vu moi-même - il a traîné autour du bureau du gouverneur, hein ! Mais son équipage a fait une grande fête ici.";
			link.l1 = "Est-ce ainsi?";
			link.l1.go = "Sotta2";
		break;
		
		case "Sotta2":
			dialog.text = "Tout le monde dit qu'il est marchand. Mais son équipage ne ressemblait pas à des déchets de taverne, je te le dis ! Leur allure était comme si... comme si... quel est le mot...?";
			link.l1 = "Je comprends. Merci pour la compagnie, camarade. Prends soin de toi.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Je fête ! Et qui dit que je suis seul ? Tu es là, matelot ! Et quant à Matt, cela devait arriver tôt ou tard.";
			link.l1 = "Pourquoi dis-tu cela? J'ai entendu dire qu'il était un pirate incroyablement chanceux, favorisé par la Fortune pendant des années!";
			link.l1.go = "Lutter2";
		break;
		
		case "Lutter2":
			dialog.text = "Heh, ce n'était pas seulement la Fortune, hein! C'était un pirate solitaire, pas un membre de la Confrérie ! Et ceux-là ne durent pas longtemps... Bien que, j'ai entendu des gens raconter qu'il était autrefois sous l'aile de Levasseur.";
			link.l1 = "C'est vrai, les solitaires ne durent pas longtemps. Eh bien, fêtez. Je dois y aller, mon pote.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sepp1":
			dialog.text = "Ah, ouais n-non, je ne l'ai jamais vu. Qui est-il?";
			link.l1 = "Il est le capitaine de l'un des navires les plus rapides de l'Archipel, la brigantine 'Banten'. Vous en avez entendu parler?";
			link.l1.go = "Sepp2";
		break;
		
		case "Sepp2":
			pchar.questTemp.PZ.TortugaHabitueBlock = true;
			
			dialog.text = "Euh, non, les navires ne m'intéressent pas, camarade, eek! On prend une autre tasse?";
			link.l1 = "Pas pour moi. Je n'ai pas obtenu ce que je voulais ici de toute façon.";
			link.l1.go = "exit_sit";
		break;
		//<-- Путеводная звезда
		
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter; //ищем
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}
