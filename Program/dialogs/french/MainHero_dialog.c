void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, sld, rShip, rItm, rItem;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr, sGun, sBullet, attrL;
	aref rType;
    
	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индекс в конце
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
	
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	if (findsubstr(sAttr, "tonzag_jail_" , 0) != -1) {
	 	pchar.questTemp.Tonzag.JailDialog.ID = strcut(sAttr, strlen("tonzag_jail_"), strlen(sAttr) - 1);
		DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog." + pchar.questTemp.Tonzag.JailDialog.ID);
		AddDialogExitQuestFunction("Tonzag_InJailDialog");
 	    Dialog.CurrentNode = "exit";
 	}
 	// генератор ИДХ по кейсу <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "Si vous lisez cette ligne, c'est un bug dans le code";
			Link.l1 = "Sortie";
			Link.l1.go = "exit";
			
			//--> Вступительный туториал на палубе корабля за Шарля
		if (CheckAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1"))
		{
			dialog.text = "Excitant, nom d’un chien ! Un vrai combat naval !\nDommage que je ne puisse pas voir la bataille d’ici... Tant pis. Je pense être assez calé en navigation pour imaginer fidèlement le déroulement des événements\nProbablement cinq pirates... Un grand navire, deux moyens et quelques petites embarcations. Parfait pour notre pinasse. Ce sera un récit formidable — Lulu va adorer !";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1");
			pchar.wind.speed = 18.0;
			fWeatherSpeed = stf(18.0);
			//AddDialogExitQuestFunction("SharlieTutorial_StartShip");
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_3");
		}
		//<-- Вступительный туториал на палубе корабля за Шарля

			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC_FindIsland"))
    		{
    		    dialog.text = "Alors, nous avons trouvé cet endroit sur la carte. Je devrais le marquer, et nous sommes prêts à partir à la recherche.";
    			link.l1 = "Bonjour, monami.";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("SearchingForIslandOnMap");
    		}
			if (CheckAttribute(pchar, "questTemp.HWICMC") && pchar.questTemp.HWICMC == "Fleetwood")
    		{
    		    dialog.text = "D'accord, nous sommes ici. Je devrais cacher mon navire dans la baie du Sud, puis revenir à pied à travers la jungle et préparer une vilaine surprise pour Fleetwood.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1.location = pchar.location;
				pchar.quest.Fleetwood_repeatShore.function = "Fleetwood_repeatShore";
    		}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabinWoman" && PChar.location == Get_My_Cabin()) 
	        {
				dialog.text = "Hm... Faire confiance à ce coquin est dangereux, bien que son histoire semble authentique. Peut-être, il ne ment pas cette fois. Mais, de toute façon, je devrais parler à sa femme... Bosco! Amène-moi cette femme capturée !";
    			link.l1 = "Aye Aye, capitaine!";
	    		Link.l1.go = "exit";
				chr = characterFromId("FalseTraceWife");
				chr.dialog.currentnode = "FalseTrace_wife_6";
				pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
				AddDialogExitQuest("SetFalseTraceCharToCabin");
	    	}
			//<-- Ложный след
			
			//--> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "DigGems")
    		{
    		    dialog.text = "Cela semble être l'endroit. C'est le seul arbre sans sève aux alentours. Je devrais creuser ici.";
    			link.l1 = "(creuse le trésor)";
    			link.l1.go = "exit";
				AddDialogExitQuest("FindPortugalGems");
    		}
			//<-- Португалец
			// Сага
			if (CheckAttribute(pchar, "questTemp.Saga.JessSoul"))
    		{
    		    dialog.text = "Qu'est-ce qui se passe? Où suis-je?! Quel genre d'endroit est-ce?";
    			link.l1 = "Bonjour, monami.";
    			link.l1.go = "exit";
				AddDialogExitQuest("Saga_JessikaSoul_2");
    		}
            //--> приколы со стуком в дверь Диффиндура, LSC
			if (CheckAttribute(pchar, "questTemp.LSC.DiffIndoor"))
    		{
    		    dialog.text = "C'est la porte qui mène aux locaux intérieurs du navire. Elle est fermée à clé... Hawk doit être ici. Que mentionnait encore Ole? Je dois utiliser un coup secret.";
    			link.l1 = "Frappe deux fois.";
    			link.l1.go = "knock_2";
				link.l2 = "Frappez trois fois.";
    			link.l2.go = "knock_3";
				link.l3 = "Frappe une fois, fais une pause, frappe trois fois.";
    			link.l3.go = "knock_1_3";
				link.l4 = "Frappe deux fois, fais une pause, frappe deux fois.";
    			link.l4.go = "knock_2_2";
				link.l5 = "Frappez trois fois, faites une pause, frappez une fois.";
    			link.l5.go = "knock_3_1";
    		}
			//<-- приколы со стуком в дверь Диффиндура, LSC
			
			//--> напялили водолазный скафандр, для перехода в режим шага
			if (pchar.model == "protocusto")
    		{
    		    dialog.text = "Sacrebleu! Cette chose est vraiment lourde!";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			//<-- водолазный скафандр
			// отказ от телепортации
			if (IsCharacterInLocator(pchar, "item", "dolly1") || IsCharacterInLocator(pchar, "item", "dolly2") || IsCharacterInLocator(pchar, "item", "dolly3"))
    		{
    		    dialog.text = "Non-non-non! Pas question! Trois fois étaient plus que suffisantes!";
    			link.l1 = "...";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "roof")
    		{
    		    dialog.text = "C'est fait. Levasseur est mort. Cela s'est avéré beaucoup plus facile que je ne le pensais... Mais quelque chose ne va pas. Thibaut n'a même pas parlé à Martene ! Cela signifie que soit Robert m'a trahi, soit il y a eu un accident\nMais où ce salaud de Thibaut pourrait-il se cacher ? Il doit être à la recherche de Catherine. Je dois agir rapidement si je veux prendre la fille vivante sous son nez...";
    			link.l1 = "";
    			link.l1.go = "terrapin";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
    		{
    		    dialog.text = "Trésors, trésors... une ville indienne... Je ne crois pas à de telles coïncidences... Je parie que mon frère a eu quelque chose à voir avec la disparition de la frégate de Dichoso. Il a probablement fait en sorte que Dichoso ne puisse jamais ouvrir à nouveau sa bouche\nOu, peut-être qu'il travaillait avec lui, les Espagnols devaient avoir des raisons de penser que Dichoso est quelque part par ici. Cela n'a aucun sens. Mais je suis sûr que l'or indien que Michel livrait à de Poincy, ainsi que l'or de Miguel Dichoso, c'est le même or. L'histoire du prisonnier correspond à ce que l'officier m'a dit sur les aventures de mon frère\nC'est drôle, Michel n'a pas réussi à livrer l'or et Miguel non plus ! Et où sont les trésors maintenant alors ? Peut-être, étaient-ils la raison pour laquelle mon frère se dépêche autant\nErgo, trouver l'or signifiera faire d'une pierre deux coups : je regarderai à nouveau dans les yeux insolents de mon frère et... oui, l'or est toujours bon. Mais comment diable vais-je le trouver ? Il semble, qu'il est temps de devenir vraiment proche des Espagnols\nDon Ramona Mendoza est hors de question, je doute que je serai capable de m'occuper de lui, mais le saint père Vincento, pire ennemi d'un baron... il fera l'affaire. Son genre n'est pas scrupuleux mais aime l'argent et les moyens malhonnêtes\nDichoso, Dichoso... J'ai déjà entendu ce nom de famille... ou pas ? Quoi qu'il en soit, au diable. Je devrais aller voir l'officier et revendiquer le prisonnier espagnol. Ensuite, je peux me diriger vers Santiago à tout moment.";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore")
    		{
    		    dialog.text = "La vanille a été chargée sur la caraque et ses voiles ont depuis longtemps disparu à l'horizon - et ce maudit galion est revenu au port au lieu de prendre le large. Je ne dois pas me montrer avec mon navire au port - il vaut mieux qu'ils pensent que j'ai quitté la Guadeloupe... Je suppose que je vais marcher jusqu'à la ville à travers la jungle et me renseigner sur mon cher Marchais...";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "galeon")
    		{
    		    dialog.text = "Il n'y a que quelques gardes sur le pont superieur, tous assez somnolents. Je suppose que je peux tous les eliminer un par un, si je viens silencieusement par derriere et les frappe avec un coup-de-poing americain a l'arriere de la tete...";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth_room"))
    		{
    		    dialog.text = "Une maison vide déverrouillée avec une chambre confortable au deuxième étage, et à proximité des appartements de Calhoun... C'est juste une réponse à la prière d'une jeune fille... Si je sors par la fenêtre et marche sur l'abat-jour du toit, je me faufilerai facilement dans la chambre d'Archie. Mais cela doit être fait la nuit pour que je ne me fasse pas prendre...";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("GuardOT_FindWayToRoom");
    		}
			// Поиски Ксочитэма
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_pearl")
    		{
    		    dialog.text = "Enfin! J'ai localisé l'endroit, indiqué par la 'manifestation': c'est une idole indienne. Quand on est près, la 'Flèche de la Voie' arrête d'osciller et pointe dans une direction. Eh bien, cela semble logique - la magie indienne et une idole indienne. Maintenant, je dois marquer l'emplacement indiqué par la 'Flèche de la Voie' sur la carte, et ensuite je vais à la Dominique.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFirstWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_dominica")
    		{
    		    dialog.text = "Enfin! J'ai trouvé l'endroit indiqué par la 'manifestation' : c'est une idole indienne. Quand je suis proche, la 'Flèche de la Voie' cesse d'osciller et pointe dans une direction. Eh bien, cela semble logique - magie indienne et une idole indienne. Maintenant, je devrais marquer l'emplacement indiqué par la 'Flèche de la Voie' sur la carte, et puis je vais aller à Main.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindSecondWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "full")
    		{
    		    dialog.text = "Les deux manifestations ont été trouvées! Maintenant, je dois marquer la deuxième direction sur la carte. L'intersection de ces deux directions me montrera l'emplacement de l'île de Ksocheatem.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFullWay");
    		}
			// рассуждения по Тайясалю
			if (CheckAttribute(pchar, "questTemp.Tieyasal_CabinTalk"))
    		{
				if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
				{
					dialog.text = "Alonso de Maldonado a dit qu'il y a un chemin vers Tayasal qui commence au nord du Yucatan. Cela signifie que je dois aller profondément dans la selva de la région. Mais Gino a dit que les statues de téléportation étaient à l'origine censées déplacer les gens à Tayasal\nEt le shaman Miskito Snake Eye m'a dit que les idoles étaient conçues pour envoyer les 'mangés' à l'endroit. Mais pourquoi alors, ces portails sont-ils cassés? Hm. De plus, la carte des Deux Manifestations montre un cercle étrange près de la statue de Miskito\nQue diable cela signifie-t-il? Un autre endroit magique? Ou cela montre-t-il que la statue là-bas a des fonctions supplémentaires? Je suppose, je devrais rendre visite au shaman. Ou je peux aller au nord-ouest de Main et chercher le chemin là-bas, dans l'une des baies locales.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Alonso de Maldonado a dit qu'il y avait un autre moyen d'arriver à Tayasal depuis la partie nord de la péninsule du Yucatan. Cela signifie que je dois chercher un chemin dans les profondeurs de la selva. Il est probable que le chemin dont j'ai besoin commence à l'une des criques dans le nord-ouest principal.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				AddDialogExitQuest("Tieyasal_AfterCabinTalk");
    		}
			// решаем - титры или фриплей 010912
			if (CheckAttribute(pchar, "questTemp.Tieyasal_final"))
    		{
				dialog.text = "C'est fait. La fin de mon long voyage. Je ne pouvais pas imaginer que sauver mon frère de prison signifiait me préparer pour le combat final contre lui ! Que j'avais presque condamné notre monde. Grâce à Dieu, c'est fini \nRien ne me retient plus dans les Caraïbes. Il est temps de rentrer chez moi, en France. Mais... Est-ce que je le veux vraiment ?";
				link.l1 = "Oui, je retourne en Europe.";
				link.l1.go = "final_1";
				link.l2 = "Non, je reste ici dans les Caraïbes.";
				link.l2.go = "final_2";
    		}
			// фэйловый финал 040912
			if (CheckAttribute(pchar, "questTemp.Europe"))
    		{
				PlaySound("Voice\English\military02.wav");
				dialog.text = "Avez-vous entendu le colonel? Les rebelles se cachent là-bas! Fouillez tout, retournez la maison et arrêtez tout le monde que vous y trouvez! Allez-y!";
				link.l1 = "Bonjour, monami.";
				link.l1.go = "exit";
				AddDialogExitQuest("Europe_SharlieFinal_2");
    		}
			// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
			/*if (CheckAttribute(pchar, "questTemp.FMQG.Info") && pchar.location == "Bridgetown_Plantation")
    		{
    		    dialog.text = "C'est le meilleur endroit pour une embuscade. Je devrais attendre ici l'arrivée de Pinette.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("FMQG_KidnappingInfo");
    		}*/
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN.Choose") && pchar.location == "shore40")
    		{
				dialog.text = "Hm. Cette histoire ne semble pas correcte. Je crois que ce lougre de St. Jones n'était jamais censé exister. Le lieutenant m'entraîne dans son opération militaire. Pourquoi aurais-je besoin de cela? Je ne suis pas en guerre avec les Hollandais... Que devrais-je faire? Devrais-je partir et laisser les Britanniques s'amuser seuls? Ou devrais-je rester?";
				link.l1 = "Partez.";
				link.l1.go = "FMQN_1";
				link.l2 = "Reste.";
				link.l2.go = "FMQN_2";
    		}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Chest") && pchar.location == "shore37")
    		{
    		    dialog.text = "Alors, le coffre est prêt. Je pourrais essayer de trouver tout le matériel nécessaire moi-même, mais je préfère aller voir Fadey. Il me semble être un homme qui peut se procurer n'importe quoi.";
    			link.l1 = "*UTILISE UNE OPTION DE PARLER A HAUTE VOIX POUR FINIR DE RAMASSER LES MUNITIONS*";
    			link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_PlantChestReadyExit");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Boats") && pchar.location == "Maracaibo_river")
    		{
    		    dialog.text = "Alors, nous devons construire six longboats. Pour cela, j'ai besoin d'un charpentier, de 20 planches et de 10 paquets de cuir";
    			link.l1 = "*UTILISEZ UNE OPTION DE PENSÉE À VOIX HAUTE POUR COMMENCER À CONSTRUIRE DES DRAGONS LONGS*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Boats");
				AddQuestRecord("Roger_5", "11");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder") && pchar.location == "shore10")
    		{
    		    dialog.text = "Alors, je compte simplement faire sauter ce tas de vieux arbres en l'air. Tout ce dont j'ai besoin pour cela, c'est de 300 unités de poudre à canon, juste pour être sûr.";
    			link.l1 = "*utilise une option Pensée à Voix Haute pour ordonner un placement de poudre à canon*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder");
				pchar.questTemp.Mtraxx.Retribution = "powder";
				chrDisableReloadToLocation = false;
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed") && pchar.location == "Judgement_dungeon_01")
    		{
    		    dialog.text = RandSwear()+" La sortie est scellée ! Il semble qu'ils aient bloqué la porte avec quelque chose de lourd ! "+RandSwear()+"\nChut... Qu'est-ce que le diable?";
    			link.l1 = "";
    			link.l1.go = "mtraxx_dungeon";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead") && pchar.location == "Judgement_church")
    		{
    		    dialog.text = "C'est ça... Fin de ligne\n On dirait que don Enrico était sérieux : il n'y a pas d'issue à ces donjons. J'ai eu un moment d'espoir quand j'ai trouvé une seconde porte au niveau de l'eau mais maintenant... J'ai perdu le compte du temps - combien de temps ai-je passé à rôder dans ces tunnels sombres ? Une demi-journée, toute la journée ? Cet endroit est aussi silencieux et effrayant qu'un cercueil\nIls avaient une église ici autrefois, juste ici. Quel endroit parfait pour dire mes prières. J'ai beaucoup péché, trop... Je prierai et dormirai ici, mes blessures et mon épuisement me tuent. Si j'ai de la chance, je ne me lèverai jamais...";
    			link.l1 = "";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead");
				AddDialogExitQuestFunction("Mtraxx_RetributionBead");
    		}
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice") && pchar.questTemp.Mtraxx.Retribution.Choice == "to_choice")
			{
				dialog.text = "";
    			link.l1 = "Moi, Charles de Maure, capitaine français et noble, je jure à moi-même et à ma conscience que j'en ai fini avec mon passé de pirate pour de bon!";
    			link.l1.go = "Good_Choice";
				link.l2 = "Ouais! Ouais! Ah ha ha!! Je l'ai fait, j'ai survécu! Mange ça, Zorro! Va en enfer, Marcus! Maintenant, je suis seul! Charlie Prince est peut-être mort, mais personne ne tuera jamais Charles de Maure!";
    			link.l2.go = "Bad_Choice";
			}
			// <-- legendary edition
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog")) {
				dialog.text = "Que devrions-nous faire ?";
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime")) {
					DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime");
					dialog.text = "... bien sûr, Levasseur n'est pas un imbécile. Sinon, pourquoi auraient-ils besoin de nous arrêter à ce moment précis?\nEt ils n'ont pas dit un mot!\n"+dialog.text;
				}
				
				DeleteAttribute(link, "l1");
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Helena")) {
					link.l1 = "Helen, pourquoi es-tu si silencieuse ?";
					link.l1.go = "tonzag_jail_helena";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Mary")) {
					link.l2 = "Marie, pourquoi as-tu l'air si heureuse?!";
					link.l2.go = "tonzag_jail_mary";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tichingitu")) {
					link.l3 = "Tichingitu? Dis quelque chose d'adéquat pour la situation.";
					link.l3.go = "tonzag_jail_tichingitu";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tonzag")) {
					link.l4 = "Hercule, peux-tu m'entendre? Que allons-nous faire?";
					link.l4.go = "tonzag_jail_tonzag";
				}
				
				link.l5 = "Rien à faire. Je suppose que je porterai les chaussures de Michel pendant un moment.";
				link.l5.go = "tonzag_exit";
			}
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailPanic")) {
				dialog.text = "";
				link.l1 = "Oh mon Dieu, ils ont tué Hercule!";
				link.l1.go = "exit";
				link.l2 = "Vous salauds!";
				link.l2.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.TonzagQuest.JailPanic");
				AddDialogExitQuestFunction("Tonzag_GFAfterShot");
			}
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.RefusedGame")) {
				dialog.text = "Quelle soirée ! Pourquoi ai-je écouté sa parole ? Mon frère avait raison - les filles d'ici sont complètement différentes. Peut-être qu'elles ajoutent quelque chose au rhum ?";
				link.l1 = "Temps de dormir, et ensuite - à Cartagena!";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.RefusedGame");

				AddDialogExitQuestFunction("HelenDrinking_LightsOut1");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk")) {
				dialog.text = "Pas une seule chose n'a été volée, bien que tout soit éparpillé. Même les objets de valeur n'ont pas été touchés. ";
				link.l1 = "Ils n'essayaient pas de me voler - ils cherchaient quelque chose de spécifique. Mais quoi? Et plus important encore, qui...?";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk");

				AddDialogExitQuest("PZ_OsmatrivaemSunduk_3");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_GotovimShlupki")) {
				dialog.text = "Attendons la nuit et attaquons !";
				link.l1 = "Nous commencerons à préparer les longues barques pendant ce temps.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_GotovimShlupki");

				AddDialogExitQuest("PZ_ShturmZvezdy");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_TiboUkralDevu")) {
				dialog.text = "Oh mon Dieu... Non, non, non... ";
				link.l1 = "";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_TiboUkralDevu");
				
				LAi_SetActorType(pchar);
				LAi_ActorAnimation(pchar, "kneeling", "1", 7.5);
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_DevaMertva")) {
				dialog.text = "Oh mon Dieu, oh mon Dieu, oh mon Dieu... Pourquoi? Oh mon Dieu, pourquoi... mais j'ai fait tout ce que je pouvais...";
				link.l1 = "C'est entièrement ma faute, seulement la mienne. Je ne suis pas arrivé ici à temps. Je suis tellement désolé... S'il te plaît, pardonne-moi.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_DevaMertva");

				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva8");
			}
		break;
		
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("C'était un sacré combat... Maintenant, nous pouvons appeler ces lâches qui ont pris la fuite...","Ha ! C'était facile. Et ces terriens se sont juste dispersés !");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("Hmm... Alors, que devrais-je faire maintenant?","Que faire maintenant?");
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "Appelle un compagnon.";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
			else 
			{   //исп.линейка, квест №6, возможность переночевать в оплаченной комнате
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "Reposez-vous jusqu'au matin.";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "Repose-toi jusqu'à la nuit.";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "Reposez-vous jusqu'à demain matin.";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        if (!bDisableMapEnter)//боя в море нет
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "Incorporez les esclaves dans l'équipage.";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // захват города
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && !CheckAttribute(Pchar, "questTemp.Sharlie.DefendSP"))
	        {
	            Link.l6 = "Commencez à capturer la ville la plus proche.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
	        
			bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
	        if(!bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait") && !CheckAttribute(loadedLocation, "CannotWait")) 
	        {
	        	Link.l7 = "Je devrais me reposer...";
	    		Link.l7.go = "TalkSelf_StartWait";
	    	}
			
			if(CheckAttribute(pchar, "equip.gun"))
			{
				if(CheckAttribute(pchar, "chr_ai.gun.bulletNum") && sti(pchar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l8 = "Je veux changer les munitions pour les armes à feu.";
					Link.l8.go = "SetGunBullets";
				}	
			}
			
			if(CheckAttribute(pchar, "equip.musket"))
			{
				if(CheckAttribute(pchar, "chr_ai.musket.bulletNum") && sti(pchar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l9 = "Je veux changer les munitions pour le mousquet.";
					Link.l9.go = "SetMusketBullets";
				}
					Link.l10 = "Je veux choisir une arme prioritaire pour le combat.";
					Link.l10.go = "SetPriorityMode";
			}
			
			Link.l19 = "Je veux choisir une potion pour une utilisation constante.";
			Link.l19.go = "ChoosePotion";
			
			//--> Голландский гамбит
			if(CheckAttribute(pchar, "questTemp.HWIC_Coordinates") && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l11 = "Essayez de trouver l'île par les coordonnées sur la carte.";
	    		Link.l11.go = "Seek_AbyIsland";
	    	}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabin" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Appelez Adam Rayner.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "CatchAdam" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Arrête Adam Rayner.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			//<-- Ложный след
			// Addon 2016-1 Jason Пиратская линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Ammo") && PChar.location == "Shore37") // прогон 3
	        {
	        	Link.l17 = "Comptez le contenu de la poitrine et décidez de terminer la collecte de munitions pour Picard.";
	    		Link.l17.go = "mtraxx_ammo";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Mutiny") && pchar.location == "Maracaibo_Plantation" && stf(environment.time) >= 3.00 && stf(environment.time) < 4.00) 
	        {
	        	Link.l17 = "Donnez l'ordre d'attaquer la plantation de Maracaibo.";
	    		Link.l17.go = "mtraxx_mutiny";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_boats" && pchar.location == "Maracaibo_river") 
	        {
	        	Link.l17 = "Donnez l'ordre de construire des chaloupes.";
	    		Link.l17.go = "mtraxx_boats";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "powder" && pchar.location == "shore10") 
	        {
	        	Link.l17 = "Ordre de livrer la poudre à canon à l'abatis mort.";
	    		Link.l17.go = "mtraxx_powder";
	    	}
			// Jason Долго и счастливо
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "letter") 
	        {
	        	Link.l18 = "Pensez à un mariage.";
	    		Link.l18.go = "LH_marry";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "marry_offer" && LongHappy_CheckShore()) // 28-03-20
	        {
	        	Link.l18 = "Faites une proposition de mariage.";
	    		Link.l18.go = "LH_marry_3";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "toIslaTesoro" && pchar.location == "Pirates_town") 
	        {
	        	Link.l18 = "Préparez la célébration.";
	    		Link.l18.go = "LH_marry_4";
	    	}
			// -->Авторемонт			
			if(Pchar.Location == Pchar.location.from_sea && CheckOfficersPerk(pchar, "SelfRepair") && CheckSelfRepairConditions()) 
			{
				Link.l14 = "Commencez à réparer les navires";
				Link.l14.go = "StartSelfRepair";
			}			
			// <--Авторемонт
			//--> завершение игры
			if(CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) // patch-9
	        {
	        	Link.l15 = "Termine les affaires dans les Caraïbes et navigue vers l'Europe.";
	    		Link.l15.go = "final_1";
	    	}
			//<-- завершение игры
			Link.l20 = RandPhraseSimple("Pas maintenant. Il n'y a pas de temps.","Pas de temps pour ça, trop à faire.");
			Link.l20.go = "exit";
		break;
		
		case "tonzag_exit":
			DialogExit_Self();
			AddDialogExitQuestFunction("Tonzag_CreateKiller");
		break;
		
		case "StartSelfRepair":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchRepair(pchar);
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Sélectionnez le type de munitions:";
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;
		
		case "SetGunBullets2":
			i = sti(PChar.GenQuest.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(pchar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetGunBullets");
			DialogExit_Self();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Sélectionnez le type de munition:";
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;
		
		case "SetMusketBullets2":
			i = sti(PChar.GenQuest.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, "musket", sBullet);
			LAi_GunSetUnload(pchar, "musket");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetMusketBullets");
			DialogExit_Self();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Au début du combat, j'utiliserai :";
			Link.l1 = "Lame";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Mousquet";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			pchar.PriorityMode = 1;
			DialogExit_Self();
		break;
		
		case "MusketPriorityMode":
			pchar.PriorityMode = 2;
			DialogExit_Self();
		break;
		
		case "ChoosePotion":
			Dialog.Text = "Sélectionnez la potion :";
	    	Link.l1 = "Potion de guérison.";
	    	Link.l1.go = "ChoosePotion1";
			Link.l2 = "Élixir.";
	    	Link.l2.go = "ChoosePotion2";
			Link.l3 = "Mélange.";
	    	Link.l3.go = "ChoosePotion3";
			Link.l4 = "Racine de gingembre.";
	    	Link.l4.go = "ChoosePotion4";
			Link.l5 = "Rhum.";
	    	Link.l5.go = "ChoosePotion5";
			Link.l6 = "Vin.";
	    	Link.l6.go = "ChoosePotion6";
			if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
			{
				Link.l7 = "Je veux sélectionner des potions automatiquement.";
				Link.l7.go = "ChoosePotion7";
			}
			Link.l8 = "Attends, j'ai changé d'avis..";
	    	Link.l8.go = "ChoosePotion8";
		break;
		
		case "ChoosePotion1":
			log_info("A healing essence will be used by default.");
			pchar.GenQuest.Potion_choice = "potion1";
			DialogExit_Self();
		break;
		
		case "ChoosePotion2":
			log_info("An elixir will be used by default.");
			pchar.GenQuest.Potion_choice = "potion2";
			DialogExit_Self();
		break;
		
		case "ChoosePotion3":
			log_info("A mixture will be used by default.");
			pchar.GenQuest.Potion_choice = "potion4";
			DialogExit_Self();
		break;
		
		case "ChoosePotion4":
			log_info("A ginger root will be used by default.");
			pchar.GenQuest.Potion_choice = "potion5";
			DialogExit_Self();
		break;
		
		case "ChoosePotion5":
			log_info("Rum will be used by default.");
			pchar.GenQuest.Potion_choice = "potionrum";
			DialogExit_Self();
		break;
		
		case "ChoosePotion6":
			log_info("Wine will be used by default.");
			pchar.GenQuest.Potion_choice = "potionwine";
			DialogExit_Self();
		break;
		
		case "ChoosePotion7":
			log_info("Potions will be selected automatically.");
			DeleteAttribute(pchar, "GenQuest.Potion_choice");
			DialogExit_Self();
		break;
		
		case "ChoosePotion8":
			DialogExit_Self();
		break;
		
		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  захват города
		case "TalkSelf_TownAttack":
            int needCrew = 500;
			if(CheckOfficersPerk(pchar, "Troopers")) needCrew = 300;
            bOk = (GetPartyCrewQuantity(Pchar, true) >= needCrew) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "Nous pourrions commencer à capturer la ville, mais le navire ne supporterait pas longtemps les salves des canons du fort, et nous ne pourrions pas envoyer un groupe d'abordage.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
					if (pchar.location == "Panama_ExitTown" || pchar.location == "Tortuga_ExitTown" || pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_ExitTown") // patch-5
					{
						Dialog.Text = "Non, je ne suis pas encore si fou..";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						if (pchar.location == "LosTeques_ExitTown")
						{
							Dialog.Text = "Il n'y a aucun intérêt à attaquer cette mine sans d'abord rassembler des informations sur l'or et l'argent qui y sont extraits. Sinon, j'envoie mes hommes mourir en vain.";
							Link.l1 = "...";
							Link.l1.go = "exit";
						}
						else
						{
							Dialog.Text = "Attaque "+GetCityName(chr.City)+".";
							if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && pchar.location == "PortSpein_ExitTown") // Jason НСО
							{
								Link.l1 = "Arrête de faire l'idiot! Halte!";
								Link.l1.go = "exit";
								break;
							}
							if (CheckAttribute(pchar, "questTemp.Patria")) // Jason НСО
							{
								if (pchar.questTemp.Patria != "fail" || pchar.questTemp.Patria != "complete")
								{
									if (pchar.location == "Marigo_ExitTown" || pchar.location == "Villemstad_ExitTown")
									{
										Link.l1 = "Arrête de faire l'idiot ! Halte !";
										Link.l1.go = "exit";
										break;
									}
								}
							}
							Link.l1 = "Aux armes!";
							Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "Arrête !";
							Link.l2.go = "exit";
						}
	    		}
	        }
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "Heh! There aren't enough people in the crew; we need at least "+needCrew+" men.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "Ne vous dispersez pas! Continuez l'attaque!";
					Link.l2 = "Bonjour, monami.";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // для сухопутных
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "Aucun des esclaves ne veut rejoindre l'équipage.";
	            Link.l1 = "Au diable avec eux !";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "Il n'y a pas d'espace libre sur le navire pour de nouveaux marins.";
	                Link.l1 = "Heh! Je devrai transférer une partie de l'équipage à un autre navire.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "Votre équipage peut être reconstitué avec "+pchar.GenQuest.SlavesToCrew+" des esclaves qui veulent servir sous vos ordres. Voulez-vous accepter?";
	                Link.l1 = "Oui";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "Non";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
			// belamour legendary edition перк получил время работы, старый метод не подходит
	        if (GetOfficersPerkUsing(pchar, "IronWill"))
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
	        }
	        else
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
	        }
			ChangeCharacterComplexReputation(pchar,"authority", -0.5);
	        // падение опыта -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "Ce doux navire est à moi maintenant, et je suis le capitaine ici ! C'est dommage que j'ai dû tuer tout l'équipage, cependant.";
			Link.l1 = "C'est l'heure de venir à terre...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "Quel compagnon appeler?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "Une autre fois.";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		//--> Голландский гамбит
		case "Seek_AbyIsland":
			bOk = CheckCharacterItem(pchar, "bussol") && CheckCharacterItem(pchar, "clock2");
			bool bOk1 = CheckCharacterItem(pchar, "sextant2");
			if (bOk || bOk1)
			{
				DialogExit();
				DeleteAttribute(pchar, "questTemp.HWIC_Coordinates");
				pchar.questTemp.HWIC_FindIsland = "true";
				AddDialogExitQuestFunction("PrepareSearchingFor");
			}
			else
			{
				dialog.text = "Dommage que je n'aie pas les instruments de navigation nécessaires pour déterminer la latitude et la longitude. Je devrai chercher l'île une autre fois. ";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		//<-- Голландский гамбит
		
		//--> Ложный след
		case "FalseTrace_Cabin":
			dialog.text = "Maître d'équipage! Amenez-moi Adam Rayner immédiatement!";
			link.l1 = "Aye aye, capitaine!";
			link.l1.go = "exit";
			chr = characterFromId("Mugger");
			if (pchar.questTemp.FalseTrace == "CatchAdam") chr.dialog.currentnode = "FalseTrace_17";
			else chr.dialog.currentnode = "FalseTrace_7";
			pchar.questTemp.FalseTrace.CharID = "Mugger";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		
		case "FalseTrace_Woman":
			DialogExit();
			chr = characterFromId("FalseTraceWife");
			chr.dialog.currentnode = "FalseTrace_wife_6";
			pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		//<-- Ложный след
		
		//--> LSC, приколы со стуком в дверь
		case "knock_2":
			PlaySound("interface\knock_2.wav");
			dialog.text = "Alors, j'ai frappé, maintenant attendons la réponse...";
			link.l1 = "(attends)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3":
			PlaySound("interface\knock.wav");
			dialog.text = "Alors, j'ai frappé, maintenant attendons la réponse...";
			link.l1 = "(attends)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3_1":
			PlaySound("interface\knock_3_1.wav");
			dialog.text = "Alors, j'ai frappé, attendons maintenant la réponse...";
			link.l1 = "(attends)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_1_3":
			PlaySound("interface\knock_1_3.wav");
			dialog.text = "Alors, j'ai frappé, attendons maintenant la réponse...";
			link.l1 = "(attends)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_2_2":
			PlaySound("interface\knock_2_2.wav");
			dialog.text = "Alors, j'ai frappé, maintenant attendons la réponse...";
			link.l1 = "(attends)";
			link.l1.go = "knock_right";
		break;
		
		case "knock_wrong":
			dialog.text = "Il n'ouvre pas la porte... Je suppose que j'ai utilisé le mauvais coup secret. D'accord, je reviendrai demain et j'essaierai à nouveau. Aujourd'hui, il n'ouvrira sûrement pas la porte.";
			link.l1 = "(partir)";
			link.l1.go = "exit";
		break;
		
		case "knock_right":
			PlaySound("interface\key.wav");
			PlaySound("Voice\English\YouFace.wav");
			dialog.text = "Wouah ! Il a répondu et ouvert la porte ! Je peux entrer maintenant...";
			link.l1 = "(entrer)";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.DiffIndoor");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
		break;
		//<-- LSC, приколы со стуком в дверь
		
		// суп из черепахи
		case "terrapin":
			PlaySound("Interface\Door_Kick.wav");
			PlaySound("Voice\English\EvilPirates02.wav");
			dialog.text = "Caramba! Alors c'est le renfort retardé pour Levasseur... Impossible de partir par la porte... D'accord, je suivrai les pas de Thibaut - par la fenêtre! Après tout, ce coquin a réussi à s'échapper d'une manière ou d'une autre!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Terrapin_GoWindow");
		break;
		
		// защита Сен-Пьера
		case "SP_defend":
			PlaySound("Voice\English\military02.wav");
			dialog.text = "Alors, notre mission est de repousser une attaque des maudits Espagnols et de sauver Saint Pierre. Le fort est capturé, et une bataille se déroule dans les rues. Il y a une puissante escadre dans la baie de Saint Pierre et ils ont un navire de ligne comme navire amiral. L'attaquer maintenant est inutile, le fort et la ville sont sous le contrôle de l'ennemi, donc ils ne nous laisseront pas débarquer au port\nPar conséquent, j'ai décidé de passer par les jungles et de les frapper par derrière par les portes de la ville. Une fois que le fort et la ville sont débarrassés des Espagnols, nous nous occuperons de l'escadre. Elle deviendra beaucoup plus vulnérable sans le soutien au feu du fort\nCe ne sera pas facile, alors j'ai donné l'ordre de payer cent mille pesos supplémentaires à répartir parmi l'équipage en plus du salaire normal. En avant!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("DefendSP_GoJungle");
		break;
		
		// финал игры
		case "final_1": // Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) // генерал-губернатор никуда не уедет
			{
				dialog.text = "Attendez, où est-ce que je vais ? Je ne peux pas quitter le poste de Gouverneur Général sans la permission de Paris ! Sinon, je serai très certainement arrêté pour l'abandon non autorisé des colonies confiées quand je reviendrai en France. Paris, tu vas me manquer ...";
				link.l1 = "";
				link.l1.go = "exit";
				EndQuestMovie();
			}
			else
			{
				dialog.text = "Alors ne perdons plus de temps! Les champs de ma chère Gascogne me manquent tellement! Mettons les voiles!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("Final_ReturnToEurope");
			}
		break;
		
		case "final_2":
			dialog.text = "Je crois que c'est la bonne décision! Qu'est-ce qui m'attend dans la bonne vieille Europe, quand je me suis trouvé ici? De plus, je peux retourner en France quand je le veux, de toute façon!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Final_StayInCarribean"); // 010912
			DeleteAttribute(pchar, "questTemp.Tieyasal_final");
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN_1":
			dialog.text = "C'est la meilleure façon. Je devrais monter à bord et partir d'ici.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseExit");
		break;
		
		case "FMQN_2":
			dialog.text = "Non, pas question, je reste. Mais bon sang, je ne vais pas rester ici à attendre Dieu sait quoi. Je devrais naviguer vers le port de Philipsburg et enquêter sur la situation. L'idée d'être un outil entre les mains d'un maudit Anglais menteur ne me plaît pas.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseContinue");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_ammo":
			Mtraxx_PlantCheckShoreBox(); // анализируем содержимое сундука
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && !CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade")) // собрали 30 сабель
			{
				dialog.text = "Trente morceaux d'acier froid sont dans le coffre! Devrais-je m'arrêter maintenant, ou devrais-je rassembler plus d'armes à feu, de charges et de potions?";
				link.l1 = "C'est suffisant!";
				link.l1.go = "mtraxx_ammo_1";
				link.l2 = "Non, je devrais continuer à remplir ce coffre.";
				link.l2.go = "exit";
				// belamour legendary edition
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Full")
				{
					link.l3 = "Remplis avec le contenu du coffre de Fadey, et prends l'excédent."; 
					link.l3.go = "mtraxx_ammo_1";
				}
			}
			else
			{
				dialog.text = "Trente morceaux d'acier froid ne sont pas encore rassemblés ! Je devrais en apporter plus.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_ammo_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Verrouiller le coffre et faire un plan pour le faufiler à la plantation.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantShoreBoxComplete");
		break;
		
		case "mtraxx_mutiny":
            dialog.text = "Allez, chargez ! Hourra !";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantMutiny");
		break;
		
		case "mtraxx_boats":
            if (GetSquadronGoods(pchar, GOOD_PLANKS) >= 20 && GetSquadronGoods(pchar, GOOD_LEATHER) >= 10) // наличие материалов
			{
				if (Mtraxx_MeridaCheckCarpenter()) // наличие плотника
				{
					dialog.text = "Tous les matériaux nécessaires sont préparés, nous devrions commencer à construire les longs bateaux tout de suite.";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_MeridaBuildBoats");
				}
				else
				{
					dialog.text = "Je n'ai pas de charpentier expérimenté capable de faire le travail. Je devrais nommer un officier à ce poste.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Pas assez de matériaux, nous avons besoin d'au moins 20 paquets de planches et 10 balles de cuir.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_powder":
            if (GetSquadronGoods(pchar, GOOD_POWDER) >= 300) // наличие пороха
			{
				if (GetCrewQuantity(pchar) >= 20) // наличие команды
				{
					dialog.text = "Tout est prêt pour une explosion !";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_RetributionBarrels");
				}
				else
				{
					dialog.text = "J'ai besoin d'au moins 20 hommes pour livrer la poudre à canon.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Pas assez de poudre à canon, au moins 300 est nécessaire.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_dungeon":
			PlaySound("ambient\jail\jail_door2.wav");
            dialog.text = "Etait-ce une porte?";
			link.l1 = "";
			link.l1.go = "mtraxx_dungeon_1";
		break;
		
		case "mtraxx_dungeon_1":
			PlaySound("ambient\jail\jail_door1.wav");
            dialog.text = "D'accord ! Nous avons des visiteurs... Jan ?..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionRunToEnrico");
		break;
		// belamour legendary edition -->
		case "Good_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "good";
			DoQuestCheckDelay("Mtraxx_RetributionFreedom", 0.5); 
			DialogExit_Self();
		break;
		
		case "Bad_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "bad";
			Achievment_Set("ach_CL_97");
			bNoEatNoRats = false;
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Roger_10", "18");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
			DialogExit_Self();
		break;
		// <-- legendary edition
		
		// Jason Долго и счастливо
		case "LH_marry":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			string sTemp = sld.name;
			dialog.text = "Moi et "+sTemp+" nous sommes ensemble depuis longtemps, et nos liens sont plus forts que tous les vœux d'église, mais je veux que nous nous souvenions tous les deux de ce moment. Par conséquent, je dois décider où je vais la demander en mariage:";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Isla Tessoro - cette île signifie beaucoup dans notre histoire. Je suppose, il n'y a pas de meilleur endroit - La baie de Sabu Matila est charmante au coucher du soleil !";
				link.l1.go = "LH_marry_1_1";
			}
			link.l2 = "Tortuga - un symbole de la liberté de notre époque, et la vue depuis le phare sur le détroit de Tortu est digne du pinceau de n'importe quel peintre!";
			link.l2.go = "LH_marry_1_2";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l3 = "La Jamaïque - il y a tant à découvrir ! Et admirer l'aube à Portland Cove, c'est comme ça que j'imagine le Paradis sur terre.";
				link.l3.go = "LH_marry_1_3";
			}
		break;
		
		case "LH_marry_1_1":
			pchar.questTemp.LongHappy.Shore = "Shore_ship1";
			AddQuestRecord("LongHappy", "2_1");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Mais nous ne pouvons pas faire cela sans la solennité de l'église - tout devrait être selon tous les canons afin que mon père soit forcé d'accepter mon choix. Donc, j'aurai besoin d'un prêtre, et je ne vois personne digne de ce poste à part l'Abbé Benoit. Il est un vieil ami de mon père et c'est de lui que mes aventures dans le Nouveau Monde ont commencé. Je pense qu'il consentira à me faire cet honneur.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_2":
			pchar.questTemp.LongHappy.Shore = "Mayak6";
			AddQuestRecord("LongHappy", "2_2");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Mais nous ne pouvons pas faire cela sans la solennité de l'église - tout devrait être selon tous les canons afin que mon père soit forcé d'accepter mon choix. Donc, j'aurai besoin d'un prêtre, et je ne vois personne digne de ce poste à part l'abbé Benoit. C'est un vieil ami de mon père et c'est de lui que mes aventures dans le Nouveau Monde ont commencé. Je pense qu'il acceptera de me faire l'honneur.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_3":
			pchar.questTemp.LongHappy.Shore = "Shore36";
			AddQuestRecord("LongHappy", "2_3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Mais nous ne pouvons pas faire cela sans la solennité de l'église - tout doit être selon tous les canons pour que mon père soit obligé d'accepter mon choix. Donc, j'aurai besoin d'un prêtre, et je ne vois personne digne de cette position à part l'Abbé Benoit. Il est un vieil ami de mon père et c'est de lui que mes aventures dans le Nouveau Monde ont commencé. Je pense qu'il acceptera de me faire l'honneur.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_2":
			AddQuestRecord("LongHappy", "3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Eh bien, cela peut se produire sans la solennité de l'homme. Bien que je préférerais en discuter avec "+sTemp+" un peu plus tard.";
			link.l1 = "";
			link.l1.go = "exit";
			pchar.questTemp.LongHappy = "choose";
		break;
		
		case "LH_marry_3":
			dialog.text = "Eh bien, je suis prêt !";
			link.l1 = "";
			link.l1.go = "exit";
			LongHappy_MarryOffer();
		break;
		
		case "LH_marry_4":
			if (LongHappy_CheckGoods())
			{
				dialog.text = "Tout est préparé!";
				link.l1 = "";
				link.l1.go = "exit";
				LongHappy_OnIslaTesoro();
			}
			else
			{
				dialog.text = "Les marchandises nécessaires et la monnaie n'ont pas encore été collectées !";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
	}
}

void  DialogExit_Self()
{
    DialogExit();
	locCameraSleep(false); //boal
}
