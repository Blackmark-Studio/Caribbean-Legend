// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;
    
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
		//--> Jason, Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace.Prisoner") && GetFullName(npchar) == pchar.questTemp.FalseTrace.CapName)
		{
			dialog.text = "Que voulez-vous, capitaine? Discuter de ma rançon? Je tiens à vous faire savoir que je me soucie du sort de la fille...";
			link.l1 = "Vous parlez de Katerine Rayner ? Je suis déjà informé à ce sujet, "+pchar.questTemp.FalseTrace.CapName+". Elle m'a demandé de parler avec vous.";
			link.l1.go = "FalseTrace_Prisoner";
			break;	
		}
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "Voyez maintenant, don Juan, la trahison c'est mal...";
			link.l1.go = "FMQG";
			break;	
		}
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear()+"Je suis votre prisonnier, "+GetAddress_Form(NPChar)+". Mais je veux que tu saches que "+NationNameNominative(sti(NPChar.nation))+" ne paie jamais pour ses gens. Nous sommes tous pour nous-mêmes.";
				link.l1 = "Eh bien... Je vois que je ne ferai aucun profit sur toi. Au moins, je peux te rançonner comme un criminel dans n'importe quelle colonie.";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "Regarde, tu es un combattant doué et j'ai besoin de gens comme toi. Aimerais-tu servir sous mes ordres?";
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear()+"Je suis votre prisonnier, "+GetAddress_Form(NPChar)+". "+NationNameNominative(sti(NPChar.nation))+" paiera un bon prix pour ma liberté.";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "Regarde, tu es un marin compétent et j'ai besoin de gens comme toi. Aimerais-tu servir sous mon commandement?";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = "Nous ne sommes pas loin de "+GetConvertStr(attrLoc+" Ville","LocLables.txt")+". Et je pourrais te laisser partir d'ici.";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "Va voir le bosco, dis-lui de te donner une armoire. Tu peux débarquer au prochain port.";
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = "Je suppose que je ferai de toi un excellent esclave - fort et dévoué.";
			link.l4.go = "Slave_1";
			link.l5 = "Vous avez ignoré un ordre de baisser vos voiles et résisté avec force. Vous serez pendu pour cela. Le bosco a déjà reçu mes ordres.";
			link.l5.go = "PunishmentAction";
			link.l99 = "Je sais.";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "tip-off"
						dialog.text = RandPhraseSimple("Capitaine, aimeriez-vous entendre ma proposition sur une variante plus rentable de ma rançon?","Je comprends qu'il n'y a pas de place pour le marchandage chez moi, mais aimeriez-vous entendre ma proposition?");
						link.l1 = "Je vous écoute.";	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = "Capitaine, pourquoi ne me libérez-vous pas simplement? Je n'ai aucune valeur pour vous. Si vous me vendez à des esclavagistes, vous n'obtiendrez que quelques pièces et une mauvaise réputation.";
						link.l1 = "Et si je te libère simplement, je n'obtiendrai rien ...";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = "Vous avez ignoré un ordre de baisser vos voiles et résisté avec force. Vous serez pendu pour cela. Le bosco a déjà reçu mes ordres.";
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = "Vous êtes vraiment insistant alors je pense que je peux vous donner ce que vous voulez. Vous êtes un homme libre maintenant. Quittez mon navire.";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("Ne testez pas ma patience. Vous êtes déjà un homme chanceux de rester en vie.","J'ai mes propres plans pour toi.","Je suppose que tu peux encore être utile pour moi à l'avenir.");
						link.l3.go = "exit";	
					break;
					
					case 2: // "ransom"
						dialog.text = "Capitaine, cette incertitude me tue. Puis-je savoir ce que vous prévoyez de faire de moi?";
						link.l1 = "Avez-vous quelque chose à me proposer?";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple("Je n'ai encore aucune idée à votre sujet.",RandPhraseSimple("Des plans? Une boulet de canon sur ton cou? Je plaisante, ha!","Tu es mon prisonnier et j'ai tous les droits de faire ce que je veux avec toi. Ton propre avis n'a aucune valeur ici."));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "Capitaine, pourquoi ne me laissez-vous pas simplement partir? Vous n'avez pas besoin de moi. Choisir d'être un pirate était la seule option pour moi parce que je n'ai aucune compétence précieuse ou éducation. Mon souhait était de gagner quelques pièces et de prendre ma retraite.";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "Regarde, tu es un combattant doué et j'ai besoin de gorges-coupées comme toi. Voudrais-tu être mon officier?";
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase("Aucune pitié pour toi. Il y a beaucoup de voyous en mer. Il y en aura au moins un de moins qui naviguera maintenant.","Des problèmes, 'loup de mer'? Reste ici et reste tranquille.","La potence attend tous les vôtres. Je te vendrai aux autorités et ce sera une grande leçon pour tout pirate.");	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "Capitaine, je vous en supplie... Libérez-moi. J'ai une famille et des enfants et ils ne s'en sortiront pas sans moi.";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "Regarde, tu es un marin habile et j'ai besoin de gens comme toi. Aimerais-tu servir sous mon commandement?";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("J'ai mes propres plans sur toi.","Je suppose que tu peux encore être utile pour moi à l'avenir.","Tu es mon prisonnier et j'ai tous les droits de faire ce que je veux de toi.");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("Capitaine, j'ai perdu un combat et je vous implore de votre clémence.","Capitaine, je supplie votre générosité. Je comprends qu'il n'y a aucune raison pour que vous me traitiez comme un prisonnier de guerre alors je vous demande de me pardonner. Je vous donne ma parole que j'éviterai de vous rencontrer en mer.");
						link.l2 = LinkRandPhrase("Ne teste pas ma patience. Tu es déjà un homme chanceux de rester en vie.",RandPhraseSimple("J'ai mes propres plans pour toi.","Je suppose que tu peux encore être utile pour moi à l'avenir."),RandPhraseSimple("Tu es mon prisonnier et j'ai tous les droits de faire ce que je veux de toi. Ton propre avis n'a aucune valeur ici.","Vous êtes... enfin vous étiez un capitaine de navire de guerre et vous étiez conscient des risques. N'essayez pas de vous représenter comme un saint ici."));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "Regarde, tu es un combattant habile et j'ai besoin de gueules d'acier comme toi. Aimerais-tu être mon officier?";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = "Nous ne sommes pas loin de "+GetConvertStr(attrLoc+" Ville","LocLables.txt")+". Et je pourrais te laisser partir ici.";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "Allez voir le bosco, dites-lui de vous donner un casier. Vous pouvez accoster au prochain port.";
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = "Maudite soit ta vie! Va voir le bosco, dis-lui de te donner un casier. Tu peux débarquer au prochain port. Et rappelle-toi que notre prochaine rencontre sera la dernière.";
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = "Vous avez ignoré un ordre de baisser vos voiles et résisté avec force. Vous serez pendu pour cela. Le bosco a déjà reçu mes ordres.";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = "Criminel? Tu te moques de moi,"+GetAddress_Form(NPChar)+"!";
			link.l1 = "Sans blague. Tu es un pirate.";
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "Servir sous vos ordres ? Je préférerais nourrir les requins !";
				link.l1 = "Garde ta langue ou tu les nourriras.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Pour être votre officier, "+GetAddress_Form(NPChar)+"? Je suis d'accord. Je connais mon travail et je n'ai rien à perdre.";
				link.l1 = "Marché conclu ! Vas et fais ton travail.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Attends un peu, j'ai changé d'avis.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("C'est une offre tentante... mais je dois la rejeter. Par principe.","Désolé, mais après ce que vous avez fait à mes amis... C'est impossible.","Non, capitaine. Après toute cette terreur, je ne peux plus faire ce travail. J'ai fait un vœu que si la Sainte Vierge entend mes prières et me donne la liberté, je ne naviguerai plus.");
				link.l1 = "C'est votre choix. Je ne serai pas insistant.";	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Pourquoi pas? Je suis un mauvais capitaine, j'ai perdu mon navire et il ne me reste rien sur le rivage. Sauf des factures et des dettes...";
				link.l1 = "Marché conclu! Allez voir le maître d'équipage et récupérez vos allocations. Je vous donnerai une position sur mon navire un peu plus tard.";	
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Attends un peu, j'ai changé d'avis.";
				link.l2.go = "exit";
			}
		break;
		
		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // освободили пленника
            DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";
            
			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;
				
		case "Slave_1":
			dialog.text = "Mais "+GetAddress_Form(NPChar)+", vous ne pouvez pas faire ça ! Je me suis rendu.";
            link.l1 = "Ferme ta gueule ! ... Attachez-le.";
			link.l1.go = "Slave_2";
			link.l99 = "D'accord. Reste ici jusqu'à ce que je décide...";
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
            if (rand(5) == 1)
            {
    			dialog.text = "Jamais! Je préférerais me tuer que devenir esclave!";
                link.l1 = "Arrête ça! C'est un ordre!... Contremaître! Nettoyez la cargaison...";
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "Boucher! Les gars, rejoignez-moi, nous n'avons rien à perdre!";
                        link.l1 = "Mauvais choix, mesdames. Je gère les mutineries moi-même et de manière très rapide...";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "En aucune façon ! J'aimerais mieux mourir au combat !";
						link.l1 = "Comme vous voulez...";
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
					dialog.text = "Oh, je suis d'accord. Je n'ai pas le choix.";
                    link.l1 = "Splendide. Il vaut mieux être un esclave qui respire qu'un héros mort.";
        			link.l1.go = "Slave_3";				
    			}			
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  пленника в рабы
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", êtes-vous vraiment si gentil, et vous me libérez sans rançon?";
            link.l1 = "Oui, je le suis. Tu es libre maintenant,"+GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "Hm... Vous avez un point! J'ai besoin de plus de temps pour décider.";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "Merci, "+GetFullName(PChar)+"! Je prierai pour toi.";
            link.l1 = "Va maintenant, et essaie de rester en vie, sinon ma générosité sera vaine.";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;
		
		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", 2);
        	DialogExit();
        break;	

		case "free_withoutFee_4":	
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("Merci, capitaine. Je n'oublierai jamais votre gentillesse. Je vais quitter ce travail et réparer de petits bateaux dans des ports paisibles. Je peux le faire.","Merci, capitaine! Je jure, j'abandonnerai cette occupation ingrate et deviendrai un pêcheur.");
					link.l1 = "Si tu es honnête alors je te souhaite bonne chance, et si ce n'est pas le cas alors prie pour ne jamais me revoir...";	
				break;
				case "trade":
					dialog.text = "Je ne sais même pas comment vous remercier, capitaine. J'avais déjà perdu tout espoir. Je vais raconter à tout le monde votre gentillesse. Je vous donne ma parole que j'allumerai une bougie pour vous ! Laissez-moi juste arriver à une église.";
					link.l1 = "Adieu. Et la prochaine fois, n'essaie même pas de résister. Tire sur moi et ce sera une sentence de mort pour toi et ton équipage.";
				break;
				case "war":
					dialog.text = "Mes remerciements, capitaine. Je prierai pour vous.";
					link.l1 = "Bonne chance, et souviens-toi, si tu décides de me chasser, ce sera ta fin.";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;
		
		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // освободили пленника        	
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;		

		case "free_in_sea_battle_all":
			//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                        	ReleasePrisoner(offref); // освободили пленника
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;
		
		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "Mais "+GetAddress_Form(NPChar)+", tu ne peux pas faire ça! J'ai capitulé.";
			link.l1 = "Seulement après que vos hommes aient disparu. Vous les avez trahis... Bosco! Emmenez-le.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Eh bien... J'ai besoin de temps pour y réfléchir. Reste ici.";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "Boucher! Les gars, nous n'avons rien à perdre!";
                    link.l1 = "Mauvais choix, mesdames. Je gère les mutineries moi-même et de manière très rapide...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "Pas question! Je préfère mourir en combat!";
					link.l1 = "Comme vous voulez...";
					link.l1.go = "free_in_sea_battle_1";
				}	
    		}
			else
    		{
				dialog.text = "Au moins donnez-moi un peu de temps pour prier...";
                link.l1 = "Prie, si tu veux.";
        		link.l1.go = "PunishmentAction2";				
    		}						
		break;
		
		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";		
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;
		
		case "free_tip_off":
			dialog.text = "J'ai une information intéressante qui pourrait être utile à un homme comme toi. Mais j'ai besoin de tes garanties que j'obtiendrai ma liberté en échange.";
			link.l1 = "Comment puis-je vous donner mes garanties si je ne connais même pas votre proposition? Je doute que vos informations me donnent quoi que ce soit.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Je ne peux que vous donner ma parole.";
			link.l2.go = "free_tip_off_1";
		break;
		
		case "free_tip_off_0":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;
		
		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "He proposed me a freight but this guy was too greedy and I rejected the offer.";  
				break;
				case "war":
					sTmp = "I have escorted him a few times as a commander of a convoy.";
				break;
				case "pirate":
					sTmp = "I had an idea to rob him once but I have never had a single chance to do that.";
				break;
			}
			dialog.text = "D'accord. C'est suffisant pour moi. Maintenant, directement aux affaires, dans "+XI_ConvertString("Colonie"+NPChar.Hold_GenQuest.City+"Voc")+" vit un marchand riche "+NPChar.Hold_GenQuest.Name+". "+"Il a fait sa fortune sur son navire '"+NPChar.Hold_GenQuest.ShipName+" vendant "+GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name+"Acc"))+" avec l'itinéraire : "+XI_ConvertString("Colonie"+NPChar.Hold_GenQuest.FromCity)+" - "+XI_ConvertString("Colonie"+NPChar.Hold_GenQuest.ToCity)+". "+"Quand il a trop de cargaison, il paye pour une escorte."+sTmp+"Je suis sûr que cette information est plus précieuse pour vous que la vie d'un seul homme.";
			link.l1 = "Doute que cette information puisse m'être utile. Je ne chasserai pas les marchands pacifiques.";	
			link.l1.go = "free_tip_off_0";
			link.l2 = "Je ne suis pas sûr que cette information me sera utile, mais je vous ai donné ma parole. Le bosco vous placera avec mon équipage et vous laissera partir dans le port le plus proche.";
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = "Mes remerciements, capitaine! Je n'avais aucun doute sur votre honnêteté!";
			link.l1 = RandPhraseSimple(RandPhraseSimple("J'aimerais pouvoir en dire autant de toi","Désolé, mais je ne peux pas dire la même chose de vous."),RandPhraseSimple("Va et souviens-toi que la prochaine fois je ne serai pas aussi généreux.","Va-t'en et reste loin de ma route. La prochaine fois, je ne te croirai pas si facilement."));
			link.l1.go = "free_tip_off_3";
		break;
		
		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;			
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation; 
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity; 
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;				
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City); 
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc"))); 
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
			
			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();			
		break;
	
		case "free_buyout":
			dialog.text = "Et j'ai une proposition pour vous. Dans "+XI_ConvertString("Colonie"+NPChar.Hold_GenQuest.City+"Voc")+" vit mon ami, "+NPChar.Hold_GenQuest.Name+" est son nom. Nous avons eu une affaire ensemble une fois."+"Trouve-le là-bas. Je suis sûr qu'il te paiera une grande somme. Il me doit et je m'occuperai de lui moi-même.";
			link.l1 = "Ton ami, hein? Faisons-le voir.";	
			link.l1.go = "free_buyout1";
			link.l2 = "Pourquoi devrais-je chercher votre ami si je peux obtenir une rançon dans le tout premier port?";
			link.l2.go = "free_tip_off_0";
		break;
	
		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);
			
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "En fait, je connais un homme qui a un beau trésor mais il n'a pas les couilles pour l'utiliser.";
			link.l1 = "Que voulez-vous dire?";
			link.l1.go = "free_by_hoard1";
			link.l2 = "Épargnez-moi vos histoires. Vous feriez mieux de vous soucier de votre âme.";
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = "Je vous raconte l'histoire qui mène à de grands trésors. J'ai besoin de votre parole en retour que vous me laisserez partir au prochain port.";
			link.l1 = "Je déciderai moi-même quand et quoi faire de toi. Tes 'histoires' ne feront aucune différence.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Je vous écoute. Vous avez ma parole.";
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = "Je fais confiance à un tel honorable "+GetSexPhrase("homme","femme")+". Les gens comme vous tiennent toujours parole ! Peu importe si le monde entier brûle, vous tiendrez votre parole ! Ai-je raison, capitaine?";
			link.l1 = "Raconte-moi ton histoire ou je te laisse partir tout de suite... par-dessus bord et sans tête.";
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = "Ha-ha, bonne blague... Maintenant ecoute. Il y a un pote dans "+XI_ConvertString("Colonie"+NPChar.Hold_GenQuest.City+"Voc")+" nommé "+NPChar.Hold_GenQuest.Name+", c'était un vrai casse-cou dans sa jeunesse. Il avait beaucoup d'affaires à cette époque..."+"Alors une fois dans la taverne, il m'a dit qu'il était membre de "+GetName(NAMETYPE_VIP,NPChar.Hold_GenQuest.PirateName,NAME_ACC)+" bande et il a vu comment ces pirates enterraient un trésor."+" Il a eu cinq de ses copains tués pour ce trésor... Il y avait des rumeurs qu'il a été pris et pendu, mais la vérité est qu'il s'est retiré des affaires, et donc il a fondé une famille. Il se souvient de l'emplacement du trésor, il a même dessiné une carte. Il m'a proposé de l'accompagner pour trouver le trésor. C'est un homme superstitieux, le trésor était couvert de sang, il a donc peur d'y aller seul. Je l'avoue, je n'ai pas non plus tenté l'aventure pour la même raison. "+"Il était prêt à vendre la carte, mais pourquoi en aurais-je besoin si je n'y vais jamais de toute façon...\nC'est mon histoire... Je pense qu'un homme courageux comme toi la trouvera utile, et la carte est assez bon marché d'ailleurs.";
			link.l1 = "Et tu me suggères vraiment d'acheter ça? Ton histoire n'est pas réelle alors je romps notre accord.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Histoire intéressante, bien que je n'y crois pas vraiment. Mais vous avez ma parole, allez dire au bosco de vous donner un casier. Vous êtes libre.";
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = "Mes remerciements, capitaine ! Maintenant, je vois le prix de la parole de quelqu'un "+GetSexPhrase("monsieur!","madame!");
			link.l1 = "Va-t'en et reste hors de mon chemin. La prochaine fois, je ne te laisserai pas partir si facilement.");
			link.l1.go = "free_by_hoard6";
		break;
		
		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();					
		break;
		
		case "free_in_sea":
			dialog.text = "Mais, "+GetAddress_Form(NPChar)+", nous sommes en pleine mer! C'est comme si vous m'exécutiez!";
			link.l1 = "C'est ce que vous vouliez. Adieu. Le bosco exécutera mon ordre.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "D'accord, je n'ai pas encore décidé.";
			link.l2.go = "exit";
		break;		
		
		//--> Jason, Ложный след
		case "FalseTrace_Prisoner":
			dialog.text = "Katerine ! Elle t'a vraiment demandé de venir ici ? Quelle fille merveilleuse...";
			link.l1 = "Restons loin de la poésie capitaine, et parlons de choses plus sérieuses. Je vais vous parler de la situation actuelle et j'attends une réponse de votre part. Votre réponse déterminera votre sort et celui de Katerine.";
			link.l1.go = "FalseTrace_Prisoner_1";
		break;
		
		case "FalseTrace_Prisoner_1":
			dialog.text = "Je vous écoute, capitaine.";
			link.l1 = "J'ai abordé votre flûte parce qu'Adam Rayner, le mari de Katerin, m'a dit qu'il y avait beaucoup d'argent sur votre navire. Cette ruse lui a permis de reprendre une femme qui lui appartenait autrefois, et qui s'est échappée de lui pour vous.";
			link.l1.go = "FalseTrace_Prisoner_2";
		break;
		
		case "FalseTrace_Prisoner_2":
			dialog.text = "Adam? Ce salaud? C'était tout son plan! Maintenant je vois... Oui, j'ai aidé Katrine à s'échapper il y a trois mois. Une telle pauvre fille, tu n'as aucune idée de comment il la traitait...";
			link.l1 = "Elle était sa femme et je me fichais de ce qui s'est passé, ce n'est pas mes affaires. J'ai fait une erreur en montant à bord de votre galion mais il est trop tard pour en parler. Adam m'a promis de me payer pour mon aide.";
			link.l1.go = "FalseTrace_Prisoner_3";
		break;
		
		case "FalseTrace_Prisoner_3":
			dialog.text = "Adam a fait une promesse? Ha-ha! Et vous lui avez fait confiance? Capitaine, savez-vous même quel genre de personne il est? Il...";
			link.l1 = "Katerine m'a déjà beaucoup parlé de lui et a fait beaucoup d'efforts pour cela. Mais sa proposition a du sens et bien que je n'ai aucune raison de faire confiance à ce salaud, peut-être que cette fois il dit la vérité. Alors allons droit au but...";
			link.l1.go = "FalseTrace_Prisoner_4";
		break;
		
		case "FalseTrace_Prisoner_4":
			dialog.text = "";
			link.l1 = "J'allais te rançonner aux autorités et livrer Adam avec Katerine à "+XI_ConvertString("Colonie"+pchar.questTemp.FalseTrace.QuestCity+"Acc")+", puis obtiens d'Adam les informations sur l'or de Solly aux yeux bridés et navigue vers cela. Mais Katerine m'a persuadé de parler avec toi d'abord, elle a dit que tu pourrais me proposer quelque chose de mieux et de plus fiable que ce qu'Adam a fait, en échange de vos vies et liberté.";
			link.l1.go = "FalseTrace_Prisoner_5";
		break;
		
		case "FalseTrace_Prisoner_5":
			dialog.text = "";
			link.l1 = "C'est pourquoi je suis ici et je vous parle. J'ai fini. Maintenant c'est à votre tour. Réfléchissez à mes paroles et aux paroles de Katerine, et donnez-moi vos idées. Vous n'avez pas beaucoup de temps.";
			link.l1.go = "FalseTrace_Prisoner_6";
		break;
		
		case "FalseTrace_Prisoner_6":
			dialog.text = "Capitaine! Bien que je ne pense pas que vous soyez un bon homme, vous avez écouté les supplications d'une pauvre fille et vous êtes venu ici. Cela me montre que vous pouvez être honorable et ressentir de la pitié. Je n'ai pas besoin de temps, je suis prête à vous faire ma proposition.";
			link.l1 = "Vraiment? Excellent! Eh bien, je vous écoute.";
			link.l1.go = "FalseTrace_Prisoner_7";
		break;
		
		case "FalseTrace_Prisoner_7":
			dialog.text = "Vous allez arrêter Adam Rayner et le mettre en chaînes. Ensuite, vous nous emmènerez, Katerine et moi à "+XI_ConvertString("Colonie"+pchar.questTemp.FalseTrace.TargetCity)+". Ne débarquez pas dans la ville, après tout, c'était vous qui avez coulé mon galion, déposez-nous tous les trois à "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+"\nJe vous demanderais aussi une arme. Nous irons à la ville à travers les jungles et je m'assurerai que cette crapule paie non seulement pour ses crimes mais aussi pour les vôtres. Il le mérite\nVous avez ma parole que votre nom ne sera pas mentionné. En retour, je vous donnerai des informations véridiques concernant un navire avec de l'or d'un état ennemi\nCe ne sera pas un grand défi pour vous mais il a des dents, vous obtiendrez un beau butin. Bien mieux que ma rançon et les trésors du 'soi-disant' Solly aux yeux louches. Avons-nous un accord?";
			link.l1 = "Je n'aime pas ton plan. Je pense que les autorités locales organiseront une chasse à l'homme dès que je quitterai les rivages de "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gén")+". Non, capitaine, je ne vais pas risquer ma tête. Notre conversation est terminée.";
			link.l1.go = "FalseTrace_Prisoner_8";
			link.l2 = "Eh bien, il semble que Katerine avait raison. J'aime votre proposition. Adam Rayner sera arrêté. Je vais le faire tout de suite. Vous serez libéré après l'arrestation d'Adam. À bientôt, capitaine!";
			link.l2.go = "FalseTrace_Prisoner_9";
		break;
		
		case "FalseTrace_Prisoner_8":
			DialogExit();
			AddQuestRecord("FalseTrace", "9");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			bQuestDisableMapEnter = false;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_Prisoner_9":
			DialogExit();
			AddQuestRecord("FalseTrace", "10");
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			AddDialogExitQuestFunction("SetCheckForGoldShip");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FalseTrace.PrisonerID = npchar.id;
			Pchar.questTemp.FalseTrace.PrisonerIDX = GetCharacterIndex(npchar.id);
		break;
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Vous êtes ici pour prêcher ou pour faire des affaires?";
			link.l1 = "Pour faire des affaires. J'ai besoin de votre complice - Bertrand Pinette. Je suis dans une merde profonde à cause de lui. Où puis-je le trouver, hein?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Pourquoi pensez-vous que je vais vous dire cela?";
			link.l1 = "C'est ton cul sur la ligne. Je te mènerai à Basse-Terre, te livrerai au gouverneur et recevrai une récompense pour avoir capturé un déserteur qui a organisé l'évasion de Carlos de Milyar. C'est ton choix. Soit tu me dis où se trouve Pinette, soit nous nous dirigeons tous les deux vers la Guadeloupe.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "Alors vous savez tout... Bien, je vous dirai tout ce que je sais sur Bertrand Pinette mais en retour, vous me libérerez.";
			link.l1 = "Allez, dis-moi alors. Je te débarquerai dans la baie des Moustiques, comme la dernière fois. Mais si tu me mens, je reviendrai et mettrai le feu à cette plantation que don Carlos t'a offerte, j'informerai aussi Basse-Terre de ta présence, donc je ne serai pas le seul à te chasser.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "D'abord, dépose-moi là. Cela me fera me sentir plus en sécurité et je jure que je te dirai tout.";
			link.l1 = "D'accord. Ce n'est pas comme si tu allais quelque part.";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "16");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FMQG.PrisonerID = npchar.id;
			Pchar.questTemp.FMQG.PrisonerIDX = GetCharacterIndex(npchar.id);
			pchar.quest.FMQG_SailMoskitos.win_condition.l1 = "location";
			pchar.quest.FMQG_SailMoskitos.win_condition.l1.location = "Shore47";
			pchar.quest.FMQG_SailMoskitos.function = "FMQG_ArriveMoskitos";
			pchar.questTemp.FMQG = "to_moskitos";
			AddMapQuestMarkShore("Shore47", true);
			bDisableMapEnter = false; // Rebbebion, теперь можно
		break;
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
	}
}
