void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;	
	int Shit, i;
	ref refStore;
	ref sld;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
        case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

        case "First time":
			Diag.TempNode = "first time";
			if(CheckAttribute(PChar, "quest.Contraband.active"))
			{
				int iTmp = false;
				int iChIdx;

				// поиск мин.  те старшего класса
				for (i=0; i<COMPANION_MAX; i++)
				{
					iChIdx = GetCompanionIndex(GetMainCharacter(), i);
					if (iChIdx>=0)
					{
						sld = GetCharacter(iChIdx);
            			if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
					}
				}
				
				if (iTmp)
				{
					dialog.text = NPCStringReactionRepeat("On ne vous a pas dit de ne pas venir ici sur un navire si remarquable ! Pourquoi n'apportez-vous pas une paire de navires de guerre ? Allez-vous en et revenez sur un navire plus petit.","Sors! Ou nous te livrerons nous-mêmes à la patrouille.","Allez à votre bateau et partez.","Tellement fatigué de toi...","bloc",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("D'accord, d'accord je vais changer mon navire.","Calmez-vous, je suis en chemin.","Zut, je pensais que ça marcherait...","Oui, je suis vraiment têtu!",npchar,Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
					break;
				}
			
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("Eh, qu'est-ce que tu fais ici, "+GetSexPhrase("copain","fille")+"?",RandSwear()+"Quelle est votre affaire ici?!");
				Link.l1 = "Détends-toi, camarade, faisons du commerce !";
				Pchar.quest.Contraband.Counter = 0; // не торговали
				if(Pchar.Location == Pchar.location.from_sea)
				{
					Link.l1.go = "Exchange";
				}
				else
				{
					Link.l1.go = "No_Ship";
				}
				//по заданию губернатора, истребление контры, только эта ветка.
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))				
				{
					Link.l2 = "Je suis ici sur ordre du gouverneur de "+XI_ConvertString("Colonie"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gén")+"! Déposez vos armes et suivez-moi, vous êtes arrêté!";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				//если заплатил, то разговаривают, иначе посылают
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
                    dialog.Text = RandPhraseSimple("Ah, enfin! Nous vous attendions. Allons-y, il est temps de mettre les voiles.","Faisons-le vite. Il y a des patrouilles partout. Nous devons nous éloigner d'ici!");
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "Je suis ici sur les ordres du gouverneur de "+XI_ConvertString("Colonie"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"! Baissez vos armes et suivez-moi, vous êtes arrêté !";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "Et qui êtes-vous ? Nous parlions d'un seul passager !";
						Link.l1 = "Oups..";
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже :), в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("Qui êtes-vous ? Nous attendions un passager, pas un capitaine.","Va-t'en ! Ne reviens pas tant que tu n'as pas débarrassé de ton navire.");
						Link.l1 = "Merde!";
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбиться, свой парень... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // ещё бой идёт
						{
						    dialog.Text = "Merde, patrouille! Nous ne vous connaissons pas et vous ne nous connaissez pas.";
							Link.l1 = "D'accord...";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("Merci pour votre aide. Nous n'oublierons pas cela. Naviguons maintenant.","Bien joué! Bon combat. Allons-y.");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//тут все ок, отправляемся.
					Link.l2 = "Je suis en chemin.";
					Link.l2.go = "Exit";
					//а это патруль... 
					if (GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < frandSmall(13.0*(1.0 - pow(0.9, sti(PChar.rank)))) && !CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
					{
						AddDialogExitQuest("Rand_ContrabandInterruption");
						PChar.GenQuest.contraTravel.PatrolFight = true;
					}
					else 
					{
						//поместим Грея в локацию.
						refStore = CharacterFromID("Abracham_Gray");
						ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
						refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
                        refStore.dialog.CurrentNode = "Travel_talkStart";
						//поплыл, иначе RemoveTravelSmugglers грохнет всю ветку
						PChar.GenQuest.contraTravel.ship = true;
						PChar.quest.Munity = "";  // признак выхода с палубы
						
						SetLaunchFrameFormParam(".. " + sti(Pchar.GenQuest.contraTravel.destination.days) + " days passed." + NewStr() + "Smuggler's ship deck.",
						                        "Reload_To_Location", 0.1, 5.0);
                        bQuestCheckProcessFreeze = true;
						WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
						bQuestCheckProcessFreeze = false;
						MakeCloneShipDeck(refStore, true); // подмена палубы
						SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
						AddDialogExitQuest("LaunchFrameForm");
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
//================ METRO ====================
				}
				else
				{
                    // если таможня уже бежит
					if (CheckAttribute(NPChar, "ContrabandInterruption"))
					{
					    dialog.Text = RandSwear()+"Patrouille! Nous ne vous connaissons pas et vous ne nous connaissez pas.";
						Link.l1 = "D'accord!";
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = "Dégage! Nous t'éventrerons si tu gâches notre affaire.";
						Link.l1 = RandPhraseSimple("Oses-tu me menacer, chien galeux!?","Tu t'étoufferas avec tes mots!");
						Link.l1.go = "Exit_fight";
						Link.l2 = "Ne t'inquiète pas, je sais ce qu'est le commerce. Au revoir.";
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "Le portes-tu sur ton dos? Où est ton navire?";
			Link.l1 = RandPhraseSimple("D'abord, j'aimerais voir s'il y a un piège dedans.","Je ne voulais pas risquer le navire. Je préfère voir tout de mes propres yeux.");
			Link.l1.go = "No_ship_1";
			Link.l2 = "L'affaire est terminée!";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "Nous sommes des hommes honnêtes et nous ne vous tromperons pas. Amenez votre navire ici, ne faites juste pas suivre les patrouilles.";
			Link.l1 = "D'accord. Attends-moi ici.";
			Link.l1.go = "Exit";
		break;

		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
    			dialog.Text = "Terminé ? Tu te moques de moi, sans doute !";
    			Link.l1 = "Je suis sérieux.";
    			Link.l1.go = "Cancellation_1";
			}
			else
            {
    			dialog.Text = "D'accord alors. Nous avons eu de bons échanges aujourd'hui de toute façon.";
    			Link.l1 = "C'est correct !";
    			Link.l1.go = "Finish_exit";
			}
		break;

		case "Cancellation_1":
			if( makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5 )
			{
				if(Rand(1) == 1)
				{
					ChangeContrabandRelation(pchar, -30);
					Dialog.snd = "voice\SMSH\SMSH006";
					dialog.Text = "Espèce de salaud! Tu ne peux pas nous tromper comme ça! Tu paieras pour cela avec ta propre tête!";
					Link.l1 = "J'en doute !";
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "Vous ne vous en tirerez pas comme ça !";
					Link.l1 = "Allez aboyer ailleurs, chiens !";
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "Tu le regretteras!";
				Link.l1 = "Tu parles trop.";
				Link.l1.go = "Exit_cancel";			
			}	
		break;

		case "GenQuestKillContraband_1":
			//счетчик подстав по "метро"...
			if(CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
			{
				Statistic_AddValue(PChar, "contr_TravelKill", 1);
				ChangeContrabandRelation(pchar, -20); //репу контры вниз
			}
			dialog.Text = "Tu répondras de cela !";
			Link.l1 = "Alors vous êtes tous morts. J'ai reçu un ordre clair - éliminer tous ceux qui résistent.";
			Link.l1.go = "Exit_fight";
		break;
		
		case "Exit_Cancel":
            DeleteAttribute(Pchar, "quest.Contraband");
            CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;
		
		case "Exit_fight":
            DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");			

			AddSimpleRumourCity("Heard the latest news? The local smugglers were rounded up by a patrol not long ago. And you know what? Captain who had a deal with them escaped!" +
				"He had dashing lads in his crew and the whole patrol was killed. And our local smugglers just vanished. There was nothing found on the shore. No goods, no stash and smugglers. See, how they do their business here!", Pchar.quest.contraband.City, 3, 5, "");	

			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			LAi_SetFightMode(Pchar, true);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Finish_exit":
            // таможня на суше
            if(GetSummonSkillFromName(pchar, "Sneak") < Rand(120))
			{
				AddDialogExitQuest("Rand_ContrabandInterruption");
				for (i=1; i<=3; i++)
				{
					characters[GetCharacterIndex("Rand_Smug0"+i)].ContrabandInterruption = true;
				}
			}
			AddCharacterExpToSkill(Pchar, "Sneak", 100);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			ChangeContrabandRelation(pchar, 15);
            OfficersReaction("bad");
            ChangeCharacterComplexReputation(pchar,"nobility", -1);
            
            CloseQuestHeader("Gen_Contraband");
            
			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
	
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
		break;

		case "Exchange":
			// сама торговля -->
            if(FindContrabandGoods(Pchar) == -1 && sti(Pchar.quest.Contraband.Counter) == 0)
            {
				dialog.Text = "Et que faites-vous ici? Vous n'avez rien à vendre! Chaque bien dans votre cargaison peut être vendu en ville!";
				Link.l1 = "Pas de chance cette fois.";
				Link.l1.go = "NoGoods";
			}
			else
			{
                // установим окружение -->
                if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали ещё
                {
                    if(hrand(11) == 3)
                    {
        				dialog.Text = "Je vois.. Tu sais, nous prendrons tes biens gratuitement. Je doute que tu seras capable de te plaindre de toute façon.";
        				Link.l1 = "Essaie, raclure !";
        				Link.l1.go = "Exit_fight";
                        break;
        			}
        			// море и солдаты на суше НЕЗАВИСИМЫ!!!
        			if(GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < Rand(12))
        			{
                        SetCoastalGuardPursuit();
        			}
        			// при убегании от патруля на карту - корабли трем
        			SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 2, false);// если в порту сидим, спим, то 2 день
        			
                    Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
        			Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";
    			}
    			// установим окружение <--
				dialog.text = "D'accord, voyons ce que tu as.";										  
				Link.l1 = "Montre-nous ce que tu as.";
				Link.l1.go = "Exchange1"; 
				if (sti(Pchar.quest.Contraband.Counter) == 0)
    			{
        			Link.l99 = "J'ai changé d'avis.";
    				Link.l99.go = "Cancellation";
				}				
            }
		break;
		
		case "Exchange1":
			NPChar.quest.meeting = NPC_Meeting;
			Diag.CurrentNode = Diag.TempNode;		 
			DialogExit();
			// belamour legendary edition опасный груз
			pchar.GenQuest.Smugglerzpq = npchar.id;
			
			LaunchContrabandTrade(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId),  sti(pchar.FindContrabandGoods.StoreIdx));	
		break;				
		// belamour legendary edition опасный груз -->
		case "SmugglerZPQ":
			dialog.text = "Bonne affaire, capitaine ! Si il y a d'autres produits intéressants - contactez-nous !";										  
			Link.l1 = "Je suis d'accord, je suis également satisfait de notre commerce. Oh, si seulement je pouvais acheter toutes les marchandises à un si bon prix...";
			Link.l1.go = "SmugglerZPQ_1"; 
		break;

		case "SmugglerZPQ_1":
			dialog.text = "Pourquoi devons-nous acheter des biens ordinaires à de tels prix, s'ils peuvent être légalement achetés dans un magasin? Mais ne vous découragez pas: en réalité, n'importe quel produit peut être vendu, même de la poudre à canon ordinaire! Vous pourriez vendre à un prix exorbitant, il suffit de connaître l'endroit.";										  
			Link.l1 = "Allez. Qui achètera de la poudre à canon à un prix exorbitant?";
			Link.l1.go = "SmugglerZPQ_2"; 
		break;
		
		case "SmugglerZPQ_2":
			dialog.text = "Eh bien, c'est ce que je t'ai dit, hehe ... Quoique ... Tu sais, il y a vraiment une telle opportunité de vendre de la poudre à canon pour une fortune, mais cette affaire ne brille toujours pas pour nous, pour cela tu dois avoir une assez bonne réputation, et nous, comme tu comprends, ne sommes pas des nobles.";										  
			Link.l1 = "Eh bien, peut-être que je peux y jeter un oeil. Je peux être bon et gentil quand c'est nécessaire. Pouvez-vous me parler de l'affaire?";
			Link.l1.go = "SmugglerZPQ_3"; 
		break;
		
		case "SmugglerZPQ_3":
			dialog.text = "Tout coûte de l'argent dans ce monde, capitaine, même l'information. Je dirais même, surtout l'information. Je propose ceci : je vous donnerai ce tuyau pour une somme symbolique de ... disons cinq mille pesos. Cela vous convient-il ?";										  
			Link.l1 = "Payer cinq mille pesos pour des informations douteuses sur l'endroit où vous pouvez vendre de la poudre à canon à un prix élevé? Non, je pense que je peux vivre sans ce tuyau.";
			Link.l1.go = "SmugglerZPQ_NM"; 
			if(sti(pchar.money) > 4999)
			{
				Link.l2 = "Je pense que je peux faire plus que juste cinq mille sur ce marché. D'accord alors, je suis d'accord.";
				Link.l2.go = "SmugglerZPQ_4";
			}
		break;	
		
		case "SmugglerZPQ_NM":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "C'est à toi de décider, capitaine. Dans tous les cas, nous avons conclu une bonne affaire. Bonne chance... et ne tombe pas sur une patrouille!";										  
			Link.l1 = "Toi aussi. Au revoir.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_4":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Excellent, capitaine! Vous êtes un client incroyable, vous savez. Alors écoutez. On a murmuré à mon oreille que dans certaines des villes espagnoles du Maine, il y avait un problème avec la poudre à canon. Que ce soient des averses tropicales, ou autre chose - en général, dans le fort qui garde la colonie, il y a très peu de réserves. Et le commandant de ce fort cherche quelqu'un qui pourrait l'aider dans cette situation difficile.\nIl n'y a que deux problèmes: d'abord, c'est une affaire délicate, et le commandant ne parlera pas de cela avec n'importe quels fripons, et deuxièmement, on parle d'un très grand lot - pas chaque navire ne pourra contenir autant de poudre à canon, donc vous pourriez avoir besoin d'une flotte. De plus, pas chaque capitaine acceptera de transformer son navire en une bombe flottante qui peut facilement détruire une île entière si elle est touchée par un boulet de canon égaré.";
			if(CheckAttribute(pchar,"questTemp.zpq"))
			{
				Link.l1 = "Désolé, mais je suis déjà au courant de cet accord. De toute façon, l'accord vaut plus que de l'argent, donc tu mérites cinq mille.";
				Link.l1.go = "SmugglerZPQ_5"; 
			}
			else
			{
				Link.l1 = "Informations précieuses, merci. Si je suis sur Maine, je demanderai aux commandants locaux des forts à propos de leurs malheurs. Et d'une manière ou d'une autre, j'espère que je m'occuperai de ces problèmes ou en abuserai, he-he.";
				Link.l1.go = "SmugglerZPQ_6"; 
			}
		break;
		
		case "SmugglerZPQ_5":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "C'est comme ça que ça se passe. Dans tous les cas, nous avons conclu une bonne affaire. Bonne chance... et ne tombez pas sur une patrouille!";										  
			Link.l1 = "Toi aussi. Au revoir.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_6":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			AddQuestRecord("zpq", "0");
			dialog.text = "C'est comme ça que ça se passe. De toute façon, nous avons fait une bonne affaire. Bonne chance... et ne tombez pas sur une patrouille !";										  
			Link.l1 = "Vous aussi. Au revoir.";
			Link.l1.go = "exit"; 
		break;
		// <-- legendary edition опасный груз
	}
}
