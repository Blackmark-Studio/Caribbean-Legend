// boal 25/04/04 общий диалог мэры
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // фортовый командер
	ref arItem;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

    ref offref;
    int i, cn, iRank, iDay;
    int qty;
    string attrLoc, QuestName, sTemp;
	bool bOk, bOk1, bOk2;
	
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10)+1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// генератор ИДХ по кейсу -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// генератор ИДХ по кейсу <--
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Tu oses montrer ton visage dans ma demeure ?! Très courageux de ta part, ou bien insensé...","Comment mes gardes idiots ont-ils laissé un ennemi pénétrer dans mon palais ? Je ferai rouler des têtes pour cela.","Apparemment, mes gardes ne valent pas un sou, si quelque vaurien se balade dans ma résidence et fouille dans mes affaires..."),LinkRandPhrase("Que désirez-vous, "+GetSexPhrase("canaille","diable")+"?! Mes soldats sont déjà sur tes traces"+GetSexPhrase(", sale pirate","")+" !",+"Meurtrier, quittez ma résidence sur-le-champ ! Gardes !","Je n'ai pas peur de vous, "+GetSexPhrase("canaille","rat")+" Bientôt, tu seras pendu dans notre fort !"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Vos soldats ne valent rien.","Essaie de m'attraper."),RandPhraseSimple("Tais-toi, "+GetWorkTypeOfMan(npchar,"")+", ou je te la fermerai !","Sois tranquille, l'ami, et tu resteras en vie."));
				link.l1.go = "fight";
				break;
			} 
			if (sti(NPChar.nation) == PIRATE)
            {
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = "Que voulez-vous ?";
					link.l1 = "Je voulais vous parler d'un travail important.";
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
				{
					dialog.text = "Que désirez-vous?";
					link.l1 = "Je voulais vous parler d'un travail important.";
					link.l1.go = "quests";
					break;
				}
					dialog.text = "Il n'y a rien à dire, mouche. Je suis occupé.";
					link.l1 = "Je vous prie de m'excuser.";
					link.l1.go = "Exit";
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
            {
				iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
                dialog.text = "Oh, regarde qui voilà ! C'est"+GetSexPhrase("","Bonjour, mon ami.")+" "+GetFullName(pchar)+"Vous savez, je viens tout juste d'envoyer des chasseurs de pirates pour vous ramener ici. Si j'avais su que vous entreriez en dansant par ma porte, j'aurais économisé mon argent.";
                if (sti(pchar.Money) >= iTotalTemp*6000)
                {
                    link.l1 = "J'étais justement sur le point de régler nos comptes.";
				    link.l1.go = "arestFree_1";
                }
				link.l2 = "Il est temps pour moi de prendre la poudre d'escampette.";
				link.l2.go = "arest_1";
				break;
            }
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			dialog.text = "Une effraction ! Gardes ! Alerte ! Meurtre !";
				link.l1 = "Merde !";
				link.l1.go = "fight"; 
				break;
			}
			//--> Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
			{
    			dialog.text = "Qu'est-ce que vous désirez, monsieur ?";
				link.l1 = "Bonjour, Votre Grâce. Je suis Charles de Maure, tout juste arrivé de Paris. Je cherche Michel de Monper.";
                link.l1.go = "Sharlie";
				npchar.quest.meeting = "1"; // patch-6
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
				{
					dialog.text = "Oh, c'est vous, monsieur... Je dois m'excuser pour mon impolitesse. Mes excuses, nous sommes loin des mondanités de Paris ici dans les colonies.";
					link.l1 = "Bien sûr, Votre Grâce.";
					link.l1.go = "Sharlie_2";
				}
				else
				{
					dialog.text = "Vouliez-vous quelque chose, Charles?";
					link.l1 = "J'ai une question...";
					link.l1.go = "quests";
					link.l2 = "Non, rien.";
					link.l2.go = "exit";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
				{
					link.l3 = "Monsieur, j'ai trouvé un cadavre de bandit dans la jungle. Il a été tué par les Indiens. Il y avait des boucles d'oreilles sur son corps, on dirait qu'elles ont été apportées d'Europe. Peut-être appartenaient-elles à l'un des nobles de votre ville ?";
					link.l3.go = "Sharlie_junglejew";
				}
				npchar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_TravlyaKrys") && npchar.city == "FortFrance")
			{
    			dialog.text = "Bienvenue dans les Caraïbes, Capitaine de Maure. Cette fois, pour de bon.";
				link.l1 = "Merci, Votre Excellence.";
                link.l1.go = "TK_TravlyaKrys";
				DelLandQuestMark(npchar);
				break;
			}
			// Jason НСО
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && IsUniformEquip())
			{
    			dialog.text = "C'est bon de vous voir, Gouverneur ! Comment allez-vous ? Tout est sous contrôle à Saint-Martin.";
				link.l1 = "Je n'ai pas le temps de rester. Continuez votre bon travail.";
				link.l1.go = "exit";
				link.l2 = "Je voulais parler de travail.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Que diriez-vous d'une partie de hasard ?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && IsUniformEquip())
			{
    			dialog.text = "Mon Dieu, ravi de vous voir, Gouverneur-Général ! Tout va bien ici dans notre humble petite colonie ! Asseyez-vous, je vais ordonner aux serviteurs de dresser la table...";
				link.l1 = "Il n'est pas nécessaire de le faire. Je ne suis pas venu pour longtemps. Continuez votre bon travail.";
				link.l1.go = "exit"; 
				link.l2 = "Je voulais parler du travail.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Que diriez-vous d'un jeu de hasard ?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") &&  IsUniformEquip())
			{
    			dialog.text = "Qui avons-nous ici ! Monsieur le Gouverneur-Général des Colonies Françaises ! Que désirez-vous, votre Grâce ? Asseyez-vous, je vais ordonner à mes serviteurs d'apporter du vin et des fruits frais.";
				link.l1 = "Ne t'inquiète pas, je suis venu ici seulement parce que je visitais l'île, et je ne pouvais pas simplement passer sans te saluer.";
				link.l1.go = "exit"; 
				link.l2 = "Je voulais parler de travail.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Que diriez-vous d'un jeu de hasard ?";
				link.l8.go = "Play_Game";
				break;
			}		
			//--> Jason, Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
			{
    			dialog.text = "Oh, vous voilà, capitaine ! Je dois dire que vous avez pris votre temps.";
				link.l1 = "Je suis arrivé à la première occasion, Votre Excellence. On m'a dit que vous aviez des affaires urgentes ?";
				link.l1.go = "Portugal"; 
				break;
			}			
			//<-- Португалец
            
            if (npchar.quest.meeting == "0")
			{
				dialog.text = "Mes hommes m'ont dit que vous étiez très insistant pour demander une audience. Mon nom est "+GetFullName(npchar)+". Je suis le gouverneur de la ville de "+GetCityName(NPChar.city)+", sujet de "+NationKingsName(npchar)+". Et maintenant, s'il vous plaît, que désirez-vous "+GetAddress_Form(NPChar)+"?";
				link.l1 = "Mon nom est "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_townhall")
				{
					dialog.text = TimeGreeting()+", Mademoiselle MacArthur.";
					link.l1 = TimeGreeting()+", Votre Excellence.";
					link.l1.go = "Helen_node_1"
				}
			}
			else
			{
               	//ОСАДЫ homo
				if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
                {

                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = "Est-ce tout ?";
                        link.l1 = "Oui, monsieur. Je ne vous retarde pas davantage.";
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = "Je suis désolé de vous contrarier, mais je n'ai pas le temps de vous parler en ce moment. Comme vous le savez sûrement, notre colonie a été attaquée par "+NationNamePeople(sti(aData.nation))+". Je m'occupe encore de nos défenses.";
                        link.l1 = "Je veux offrir mon assistance pour la défense du fort.";
                        link.l1.go = "siege_task";
                        link.l2 = "Alors je ne vous retiendrai pas plus longtemps.";
            			link.l2.go = "exit";
                    }
                }
                else
                {//->
                    makearef(aData, NullCharacter.Siege);
                    if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                    && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                        ChangeCharacterComplexReputation(pchar,"nobility", 10);
                        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                        AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                        //--> слухи
                        SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and to defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<-- слухи
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = "Oh, c'est vous, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", je suis heureux de vous voir. De bonnes nouvelles pour notre colonie - nous avons réussi à repousser le "+NationNameSK(sti(aData.nation))+"  envahisseurs. Vous avez également un rôle à jouer dans cette affaire, alors voici votre récompense - "+(sti(aData.iSquadronPower)*1500)+"pièces de huit. Tenez, les voilà.";
                        link.l1 = "Merci, "+GetAddress_FormToNPC(NPChar)+", plaisir de faire affaire avec vous !";
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> дача квеста найти кольцо в борделе
						if (rand(4) == 4 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 365 && sti(pchar.questTemp.HorseQty) > 10)
						{// Addon-2016 Jason
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = "J'ai une tâche pour vous, mais elle est quelque peu inhabituelle.";
								link.l1 = "Ce sont les tâches dans lesquelles j'excelle.";
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- дача квеста найти кольцо в борделе    				
						dialog.text = RandPhraseSimple("Oh, c'est encore vous ? Que voulez-vous de moi cette fois-ci ?","Vous me distraiez des affaires de ma ville. Que voulez-vous, "+GetAddress_Form(NPChar)+"?");
						if (npchar.city != "Panama") // Addon-2016 Jason
						{
							link.l1 = "Je veux vous parler de travailler pour "+NationNameGenitive(sti(NPChar.nation))+".";
							link.l1.go = "work";
						}
						// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
						if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen")+" J'ai trouvé des pirates. Tous "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" sont à bord pour le moment. Je veux les remettre aux autorités.";
							link.l11.go = "PiratesOnUninhabited_1";
						}
						
        				link.l2 = "J'allais vous parler d'un sujet important.";
						if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
						{
							link.l2.go = "ReasonToFast_Mayor1";
						}
						else
						{
							link.l2.go = "quests";   //(перессылка в файл города)
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
						{
							if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
							{
								link.l12 = "Il y a un capitaine à la tête de la patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Accord"))+" nommé "+pchar.GenQuest.CaptainComission.Name+", comment puis-je le voir ?";
								link.l12.go = "CapComission_Mayor1";
							}	
							if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = "Ancien capitaine en commandement de la patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"a accepté de révéler sa cachette aux autorités.";
								link.l12.go = "CapComission_Mayor9";
							}
							if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = "Ancien capitaine à la tête de la patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"a révélé sa cachette à moi.";
								link.l12.go = "CapComission_Mayor13";
							}
						}
						if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25  && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
						{
							if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
							{
								iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
								if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" J'ai rencontré le capitaine "+pchar.GenQuest.ShipWreck.Name+" et ses marins qui ont été débarqués par un pirate "+pchar.GenQuest.ShipWreck.BadName+". "+"Malheureusement, j'avais déjà trop d'hommes à bord de mon navire et je ne pouvais pas les prendre à bord. Mais je leur ai laissé des provisions et des armes. Si un navire de sauvetage ne les récupère pas dans "+(30 - iDay)+" jours, alors je ne sais pas si je les trouverai vivants ou non.";
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Gén"))+" J'ai rencontré des marins du navire naufragé '"+pchar.GenQuest.ShipWreck.ShipTypeName+"' avec leur capitaine. "+"Malheureusement, j'avais déjà trop d'hommes sur mon navire et je ne pouvais pas les embarquer. Mais je les ai laissés avec des provisions et des armes. Si un navire de secours ne les récupère pas d'ici là "+(30 - iDay)+"jours, alors je ne sais pas si je les trouverai vivants ou non.";
									link.l13.go = "ShipWreck1";							
								}
							}	
						}
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = "Je souhaite livrer un prisonnier.";
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // если не в тюрьме
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = "Je dois régler quelques problèmes financiers avec vous.";
        						link.l4.go = "LoanForAll";//(перессылка в кредитный генератор)
        					}
        				}
						//-->> сдача найденного в борделе кольца
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = "J'ai réussi à retrouver votre bague. La voilà.";
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = "J'ai votre alliance. L'une des... filles de joie du bordel l'avait.";
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- сдача найденного в борделе кольца 
						
						//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Je porte un message de la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
						//<-- генер почтового курьера 2 уровня
						
						// Warship, 16.05.11. Квест "Правосудие на продажу" -->
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", j'ai localisé une bande de contrebandiers dont le meneur avait été récemment capturé par les gardes. Maintenant, ils complotent son évasion. Leur navire '"+PChar.GenQuest.JusticeOnSale.ShipName+"' est amarré à "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+".";
							link.l15.go = "JusticeOnSale_1";
						}
						
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", la bande de contrebandiers n'existe plus !";
							link.l15.go = "JusticeOnSale_7";
						}
						// <--Правосудие на продажу
						//Jason --> Регата
						if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
						{
							link.l16 = "Je suis ici pour la régate. Voici mon invitation.";
							link.l16.go = "Regata";
						}
        				//link.l7 = "Je souhaiterais savoir où se trouve le Gouverneur Général de "+NationNameGenitive(sti(NPChar.nation))+"est.";
        				link.l8 = "Peut-être voulez-vous faire une pause en jouant à un jeu de hasard ?";
        			    link.l8.go = "Play_Game";
        				link.l10 = "Je vous prie de m'excuser, mais le devoir m'appelle.";
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;
		
		// Warship Генер "Пираты на необитайке"
		case "PiratesOnUninhabited_1":
			offref = CharacterFromID("PirateOnUninhabited_0");
			qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);
			
			PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;
			
			dialog.text = "Très bien. Nous devons combattre ce fléau commun avec nos efforts concertés. J'enverrai immédiatement un navire pour les récupérer. Sois assuré qu'ils seront pendus à la potence en moins d'une semaine. Oh, et une récompense est due, bien sûr -"+FindRussianMoneyString(qty)+".";
			link.l1 = "Merci, Votre Grâce. Toujours un plaisir. ";
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = "Non. En y réfléchissant bien, cela ne convient pas.";
			link.l2.go = "exit";
		break;
		
		case "PiratesOnUninhabited_2":
			offref = CharacterFromID("PirateOnUninhabited_0");
			
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));
			
			RemovePassenger(PChar, offref);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
			AddQuestUserData(sTemp, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
			CloseQuestHeader(sTemp);
			
			PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
			PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";
			
			if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
			{
				PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
				
				PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
				Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
			}
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Mayor1":
			dialog.text = "Je suis tout ouïe, capitaine.";
			link.l1 = "Je voulais vous parler d'une collusion criminelle entre un officier de votre garnison et des pirates... (explique l'affaire).";
			if(sti(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_BMayor";			
			}
			else
			{
				link.l1.go = "ReasonToFast_GMayor";	
			}
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_GMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Merci, "+GetSexPhrase("monsieur","mademoiselle")+"Je vais immédiatement donner l'ordre d'arrêter ce traître.\nTu as dû dépenser beaucoup d'argent, hélas, notre trésor est vide...";
				link.l1 = "Je ne l'ai pas fait pour l'argent, votre Excellence.";
				link.l1.go = "ReasonToFast_GMayor_11";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Je vous remercie ! Je ferai arrêter ce vaurien. Imaginez-vous ! J'étais sur le point de le récompenser avec un sabre à poignée dorée pour ses dix années de service ! Vous m'avez épargné une sérieuse humiliation !";
				link.l2 = "La justice est une récompense en soi.";
				link.l2.go = "ReasonToFast_GMayor_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Raté"+GetSexPhrase("ter","s")+"de Maure, vous ne pouvez pas simplement tuer un suspect sans aucun témoin ! Maintenant, nous ne pouvons même pas prouver ses crimes ! Je fais tout mon possible pour éviter que vous ne soyez arrêté pour homicide involontaire.";
				link.l3 = "Avast, c'était en légitime défense, Votre Excellence.";
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}			
		break;
		
		case "ReasonToFast_BMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 				
				dialog.text = "Capitaine, réalisez-vous ce que diable vous avez fait ?!! Je prépare ce piège depuis plus d'un mois ! Et maintenant, juste pour votre propre divertissement, vous avez saboté la rencontre de notre patrouille avec "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" et maintenant tu viens ici te vanter de cela ?!! Peut-être pourrais-tu me dire maintenant comment vais-je justifier toutes les dépenses et les coûts de cette opération ?!";
				link.l1 = "Votre Grâce, je viens de résoudre votre problème, si vous y regardez de près, vous auriez dû me payer tout ce temps !";
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Laissez-moi voir cette carte\nÊtes-vous sérieux en ce moment ? Ce bout de papier en lambeaux est une preuve ?";
				link.l2 = "Allons, Votre Grâce, soyez raisonnable.";
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");				
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Eh bien, eh bien, maintenant nous savons ce qui est arrivé à ma patrouille. Au moins, en venant ici, vous nous avez épargné la peine de chercher le meurtrier.";
				link.l3 = "Votre Grâce ! Vous refusez simplement de voir le problème...";
				link.l3.go = "ReasonToFast_BMayor_1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_GMayor_11":
			dialog.text = "You may be an idiot but you are at least a useful idiot. Here - take this map; found it on a pirate who we hanged last week. God willing, perhaps you will find his treasure, although I find it quite unlikely...";
			link.l1 = "Merci, c'est très généreux de votre part !";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		
		case "ReasonToFast_GMayor_21":
			dialog.text = "Votre zèle est louable. Veuillez accepter cette épée en récompense - c'est le moins que je puisse faire. Oh, et vous pouvez garder la carte pour vous. Je suis certain qu'il y a beaucoup de telles contrefaçons dans les Caraïbes.";
			link.l1 = "Merci, c'est très généreux de votre part !";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = "Peut-être, peut-être... Eh bien, disons simplement que cet accord a été décidé par la justice divine et par la volonté de notre Seigneur.";
			link.l1 = "Merci, c'est très généreux de votre part !";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;
		
		case "ReasonToFast_BMayor_1":
			dialog.text = "Tiens ta langue, garçon ! Tu es soit fou, soit de mèche avec nos ennemis ! Gardes, saisissez cet imbécile !";
			link.l1 = "Touche-moi et tu la perdras !";
			link.l1.go = "fight";
		
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";						
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		
		// --------------------------Операция 'Галеон'-----------------------------
		case "CapComission_Mayor1":
			dialog.text = "Pour le moment, c'est impossible. Il est en état d'arrestation en attendant son procès.";
			link.l1 = "Ah bon? Et de quoi est-il soupçonné?";			
			link.l1.go = "CapComission_Mayor2";
		break;
		
		case "CapComission_Mayor2":
			dialog.text = "Malheureusement, ce n'est pas une suspicion, mais un fait avéré. Nous avons des informations selon lesquelles il attaquait des navires sous prétexte de patrouiller. Il confisquait des marchandises aux marchands pour ensuite les vendre à des contrebandiers et des pirates. C'est dommage... de penser qu'il était autrefois considéré comme l'un des meilleurs capitaines que la Couronne ait eus...";
			link.l1 = "Et qui vous a fourni les preuves ?";
			link.l1.go = "CapComission_Mayor3";				
		break;
		
		case "CapComission_Mayor3":
			dialog.text = "Une de ses victimes a rédigé un rapport, où il a décrit l'incident en détail, y compris la date, le nom du navire pillé et les quantités de marchandises confisquées. "+"Croyez-moi, les chiffres sont assez impressionnants. Ce jour-là, la patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")))+" capitaine "+pchar.GenQuest.CaptainComission.Name+"était en service en effet. Le capitaine a décrit cet incident comme une rencontre avec un navire pirate dans son rapport, mais n'a pas mentionné de cargaison du tout.";
			link.l1 = "Mais y avait-il une cargaison, au moins ?";
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;
		
		case "CapComission_Mayor4":
			dialog.text = "Il n'y a aucun doute là-dessus. La partie lésée est un homme très connu et il ne s'abaisserait pas à la calomnie et à la diffamation. En ce moment, nos patrouilles recherchent la cachette du capitaine."+"Une fois trouvé, le capitaine peut se présenter à la cour\nSi vous nous apportez votre aide dans cette affaire, nous vous en serons très reconnaissants.";
			link.l1 = "Probablement pas. Je ne connais pas assez bien la région pour chercher une cachette. Excusez-moi, je dois partir.";
			link.l1.go = "CapComission_Mayor5";
			link.l2 = "Peut-être... Combien de temps ai-je ?";
			link.l2.go = "CapComission_Mayor6";	
		break;
		
		case "CapComission_Mayor5":
			AddQuestRecord("CaptainComission2", "49");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.GenQuest.CaptainComission = "MayorTalkBad";
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor6":
			dialog.text = "Je crois qu'en deux jours les patrouilles peuvent localiser la cachette sans votre aide, alors vous devriez vous dépêcher."; 
			link.l1 = "Oui, j'y suis. Mais je devrai rendre visite au capitaine "+pchar.GenQuest.CaptainComission.Name+"Peut-on arranger cela ?";
			link.l1.go = "CapComission_Mayor7";
		break;
		
		case "CapComission_Mayor7":
			dialog.text = "Ce ne sera pas un problème. J'informerai le commandant du fort de votre visite.";
			link.l1 = "Merci. Maintenant, veuillez m'excuser.";
			link.l1.go = "CapComission_Mayor8";
		break;
		
		case "CapComission_Mayor8":
			AddQuestRecord("CaptainComission2", "50");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);			
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			OfficersReaction("good");
			pchar.GenQuest.CaptainComission.MayorTalkGood = true;
			pchar.GenQuest.CaptainComission = "MayorTalkGood";
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor9":
			dialog.text = "Excellent ! Où est le trésor ?";
			link.l1 = "Je n'ai aucune idée pour l'instant. Il ne m'a pas indiqué l'emplacement exact.";
			link.l1.go = "CapComission_Mayor10";
		break;
		
		case "CapComission_Mayor10":
			dialog.text = "Hmm, quelle coïncidence ! Vous savez, il ne m'a pas non plus 'indiqué' l'emplacement exact...";
			link.l1 = "Je m'en occupe.";
			link.l1.go = "CapComission_Mayor11";
		break;
		
		case "CapComission_Mayor11":
			dialog.text = "Plus maintenant\nGardes ! Ramenez le prisonnier aux cellules\nVous êtes libre de partir, "+GetFullName(pchar)+".";
			link.l1 = "Mais gouverneur...";
			link.l1.go = "CapComission_Mayor12";
		break;
		
		case "CapComission_Mayor12":
			sld = CharacterFromID("CapComission_1");
			sld.lifeDay = 0;
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);			
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";									
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);			
			AddQuestRecord("CaptainComission2", "23");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CapComission_Mayor13":
			pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
			dialog.text = "Excellent ! Et où allons-nous chercher son trésor ?";
			link.l1 = "Dans le "+RandPhraseSimple(RandPhraseSimple("nord","occidental"),RandPhraseSimple("oriental","du sud"))+" fin de "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+" au pied de la falaise, il y a une grande niche, dont l'entrée est jonchée de pierres. C'est la cachette.";
			link.l1.go = "CapComission_Mayor14";
		break;
		
		case "CapComission_Mayor14":
			dialog.text = "Excellent travail ! Et où est "+pchar.GenQuest.CaptainComission.Name+" lui-même ? On m'a dit que vous l'avez pris des cachots du fort.";
			link.l1 = "Malheureusement, il a péri lors d'une escarmouche avec les contrebandiers.";
			link.l1.go = "CapComission_Mayor15";
		break;
		
		case "CapComission_Mayor15":
			dialog.text = "C'est mauvais... C'est très mauvais, "+GetSexPhrase("monsieur","mademoiselle")+" "+GetFullName(pchar)+". J'allais l'exécuter en public, 'pour encourager les autres.'"+"Quoi qu'il en soit, il n'aurait pas évité la potence\nAlors, comme vous avez techniquement enfreint la loi en libérant illégalement un prisonnier, mais que vous ne l'avez tout de même pas sauvé, je ne peux pas inscrire cela dans le rapport. Par conséquent, vous ne recevez pas de récompense... Mais j'aimerais personnellement vous remercier. Acceptez mon cadeau - une chose très utile pour un capitaine combattant.";
			link.l1 = "Merci. Toujours heureux de servir.";	
			link.l1.go = "CapComission_Mayor16";
		break;
		
		case "CapComission_Mayor16":
			AddQuestRecord("CaptainComission2", "30");
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			CloseQuestHeader("CaptainComission2");
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			OfficersReaction("good");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// --------------------------Операция 'Галеон'-----------------------------
		
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		case "ShipWreck1":
			if(iDay > 15)
			{
				dialog.text = RandPhraseSimple("Comment fais-tu cela ? Il faut au moins quinze jours pour atteindre cet endroit, même en naviguant avec le vent !","Capitaine "+GetFullName(pchar)+", ton irresponsabilité me stupéfie ! Pourquoi ne m'en as-tu pas parlé plus tôt ?");
				link.l1 = "Eh bien, je ne sais même pas quoi dire...";
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = "C'est une excellente nouvelle ! Nous avions déjà perdu espoir de voir "+pchar.GenQuest.ShipWreck.Name+"  vivant à nouveau. Je vais envoyer une équipe de secours immédiatement. Oh, et veuillez accepter cette récompense pour votre efficacité et votre participation à leur sauvetage.";
				link.l1 = "Merci, Votre Grâce. Je suis heureux d'avoir pu aider. Je suis sûr que l'expédition arrivera à temps.";
				link.l1.go = "ShipWreck3";	
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen таймер на 30 дней тоже нужно снять
		break;
		
		case "ShipWreck2":
			dialog.text = "Houlà....Que puis-je dire ? Va étudier le Droit de la Mer, garçon ! Quoi qu'il en soit, je ferai de mon mieux pour sauver ces gens.";
			link.l1 = "Votre Grâce, mais je leur ai laissé assez de provisions. Vous avez du temps, je vous assure ...";
			link.l1.go = "ShipWreck4";
		break;
		
		case "ShipWreck3":
			addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			AddQuestRecord("ShipWrecked", "14");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;		
		
		case "ShipWreck4":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("ShipWrecked", "13");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		
		// ---------------------- найти кольцо в борделе ----------------------------
		case "TakeRing_1":
			dialog.text = "Je sais que vous, comment dire... "+GetSexPhrase("sont un habitué des bordels","aimer aller aux bordels de temps en temps")+". Et par conséquent, j'ai décidé de m'adresser à vous pour de l'aide\n"+"Tu sais, j'ai honte de l'admettre, mais j'y étais récemment...";
			link.l1 = "Et qu'y a-t-il de mal à cela ? Le sexe est une chose parfaitement naturelle, vous savez...";
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = "Oh, non, je ne prêche pas, non. Le fait est que j'avais trop bu à une occasion et j'ai perdu mon alliance...";
			link.l1 = "Voilà un problème. Je suis désolé.";
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = "Je n'ai pas besoin que l'on soit désolé pour moi. J'ai besoin de récupérer ma bague. Si tu parviens à la récupérer avant minuit, je serai très généreux. Si tu échoues, ma femme me tuera.";
			link.l1 = "Je vois... Et où exactement pourriez-vous l'avoir perdu ? Vous souvenez-vous de quelque chose en particulier ?";
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = "Malheureusement, non. Pas une chose.";
			link.l1 = "Je vois. Eh bien, cherchons-le, alors.";
			link.l1.go = "TakeRing_5";
			link.l2 = "Tu sais, "+GetAddress_FormToNPC(NPChar)+", je pense que je vais passer mon tour pour celui-ci. Je vous prie de m'excuser...";
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = "Excellent! Mais rappelez-vous - vous devez le trouver avant minuit.";
			link.l1 = "Je m'en souviens. Je reviendrai bientôt.";
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;	
			pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank)*100+1000;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//ложим кольцо в итем
			if (rand(3) != 2)
			{				
				switch (rand(2))
				{
					case 0: sTemp = "_Brothel_room";  break;
					case 1: sTemp = "_Brothel";  break;
					case 2: sTemp = "_SecBrRoom";  break;
				}
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
				sld.startLocator = "item" + (rand(4)+1);
				pchar.questTemp.different.TakeMayorsRing.item = true; //флаг кольцо валяется в итемах
				Log_QuestInfo("The ring is at " + sld.startLocation + ", in locator " + sld.startLocator);
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;	
		case "TakeRing_6":
			dialog.text = "Oh? Eh bien, c'était vraiment inattendu... Eh bien, bonne chance à vous alors, capitaine.";
			link.l1 = "Adieu.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
		break;

		case "TakeRing_S1":
			dialog.text = "C'est ma bague ! Vous m'avez sauvé la vie !";
			link.l1 = "Ce n'est rien, monsieur.";
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = "Voici votre argent pour un travail bien fait ! Je vous suis très reconnaissant !";
			link.l1 = "Ravi de vous aider, monsieur, faites plus attention la prochaine fois.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = "Seigneur, ayez pitié ! Je devrais vraiment arrêter de boire autant...";
			link.l1 = "Ça, c'est sûr ! Voici votre anneau.";
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = "Oui, oui, merci beaucoup. Je vous suis redevable ! Voici votre argent pour un travail bien fait !";
			link.l1 = "Merci "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 3);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- найти кольцо в борделе ----------------------------

		case "node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "Nous avons déjà tout discuté, n'est-ce pas ?";
                    link.l1 = "D'accord. Je ne vous retarde pas davantage.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Je suis désolé de vous contrarier, mais je n'ai pas le temps de vous parler en ce moment. Comme vous le savez sans doute, notre colonie a été attaquée par "+NationNamePeople(sti(aData.nation))+"Je dois veiller à nos défenses.";
                    link.l1 = "Eh bien, je voulais juste offrir mon assistance pour la défense du fort.";
                    link.l1.go = "siege_task";
                    link.l2 = "Alors je ne vous retiendrai pas plus longtemps.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Oh, c'est vous, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", je suis heureux de vous voir. Bonne nouvelle - nous avons réussi à repousser le "+NationNameSK(sti(aData.nation))+" envahisseurs. Vous avez également fait votre part dans cela, et voici votre récompense - "+(sti(aData.iSquadronPower)*1500)+"pièces de huit. Voici pour vous.";
                    link.l1 = "Merci, "+GetAddress_FormToNPC(NPChar)+", un plaisir de faire affaire avec vous !";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "Alors, quelle était la raison de ta venue ici pour me distraire des affaires d'État importantes ?";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "Je voulais travailler pour "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Ca")+" J'ai rencontré des pirates. Tous "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" sont à bord pour le moment. Je veux les livrer aux autorités.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "Je voulais vous parler d'une affaire importante.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "Il y a un capitaine à la tête de la patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Acc"))+" nommé "+pchar.GenQuest.CaptainComission.Name+", comment puis-je le rencontrer ?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Ancien capitaine en charge de la patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"a accepté de révéler sa cachette aux autorités.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Ancien capitaine commandant de patrouille  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"a révélé sa cachette à moi.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Ce"))+" J'ai rencontré un capitaine "+pchar.GenQuest.ShipWreck.Name+" et ses marins qui furent débarqués par un pirate "+pchar.GenQuest.ShipWreck.BadName+". "+"Malheureusement, j'avais déjà trop d'hommes sur mon navire et je ne pouvais donc pas les embarquer. Mais je leur ai laissé de la nourriture et des armes. Si le navire de secours ne les récupère pas d'ici là "+(30 - iDay)+" jours, alors je ne sais pas si je les trouverai encore vivants ou non.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" J'ai rencontré des marins d'un naufrage de navire '"+pchar.GenQuest.ShipWreck.ShipTypeName+"avec leur capitaine. "+"Malheureusement, j'avais déjà trop d'hommes sur mon navire et ne pouvais donc pas les prendre à bord. Mais je leur ai laissé de la nourriture et des armes. Si le navire de sauvetage ne les récupère pas d'ici "+(30 - iDay)+" jours, alors je ne sais pas si je les trouverai encore vivants ou non.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "J'ai un message de la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gouverneur")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Milord, j'ai localisé une bande de contrebandiers dont le chef a été récemment capturé par les gardes. Maintenant, ils complotent son évasion. Leur navire '"+PChar.GenQuest.JusticeOnSale.ShipName+" est amarré à "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Je dois remettre le capitaine captif aux autorités.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "Je suis ici pour la régate. Voici mon invitation.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Peut-être aimeriez-vous faire une pause ?";
        			link.l5.go = "Play_Game";
        			link.l10 = "C'était juste une visite de courtoisie, "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Helen_node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "Nous avons déjà tout discuté, n'est-ce pas ?";
                    link.l1 = "Correct. Je ne vous retarde pas davantage.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Je suis désolé de vous contrarier, mais je n'ai pas le temps de vous parler pour le moment. Comme vous devez le savoir, notre colonie a été attaquée par "+NationNamePeople(sti(aData.nation))+"Je dois veiller à nos défenses.";
                    link.l1 = "Eh bien, je voulais juste offrir mon assistance pour la défense du fort.";
                    link.l1.go = "siege_task";
                    link.l2 = "Alors je ne vous retarderai pas davantage.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Oh, c'est vous, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", je suis heureux de vous voir. Bonne nouvelle - nous avons réussi à repousser le "+NationNameSK(sti(aData.nation))+"envahisseurs. Vous avez également fait votre part dans cela, et voici votre récompense - "+(sti(aData.iSquadronPower)*1500)+"pièces de huit. Tenez, les voilà.";
                    link.l1 = "Merci, "+GetAddress_FormToNPC(NPChar)+", plaisir de faire affaire avec vous !";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "Qu'est-ce qui vous amène à moi ? Je pensais que vous régliez toutes vos affaires avec votre... mécène. Mais parlez, je suis toujours ravi de vous écouter.";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "Je voulais travailler pour "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Ce jour-là")+" J'ai rencontré des pirates. Tous "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" sont à bord pour le moment. Je veux les livrer aux autorités.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "J'allais vous parler d'une affaire importante.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "Il y a un capitaine à la tête de la patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Acc"))+" nommé "+pchar.GenQuest.CaptainComission.Name+", comment puis-je le rencontrer?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Ancien capitaine en charge de la patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"a accepté de révéler sa cachette aux autorités.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Ancien capitaine en charge de la patrouille  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" m'a révélé sa cachette.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" J'ai rencontré un capitaine "+pchar.GenQuest.ShipWreck.Name+" et ses marins qui ont été débarqués par des pirates "+pchar.GenQuest.ShipWreck.BadName+". "+"Malheureusement, j'avais déjà trop d'hommes à bord de mon navire et je ne pouvais donc pas les embarquer. Mais je leur ai laissé de la nourriture et des armes. Si le navire de secours ne les récupère pas dans les "+(30 - iDay)+" jours, alors je ne sais pas si je les trouverai encore en vie ou non.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" J'ai rencontré des marins d'une épave de navire victime du naufrage '"+pchar.GenQuest.ShipWreck.ShipTypeName+"avec leur capitaine. "+"Malheureusement, j'avais déjà trop d'hommes sur mon navire et je ne pouvais donc pas les prendre à bord. Mais je leur ai laissé de la nourriture et des armes. Si le navire de secours ne les récupère pas dans "+(30 - iDay)+" jours, alors je ne sais pas si je les trouverai encore vivants ou non.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "J'ai un message de la ville de "+XI_ConvertString("Colonie"+pchar.questTemp.WPU.Postcureer.StartCity+"Gouverneur")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Milord, j'ai localisé une bande de contrebandiers dont le chef a été récemment arrêté par les gardes. Maintenant, ils complotent son évasion. Leur navire '"+PChar.GenQuest.JusticeOnSale.ShipName+"' est amarré à "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Je dois livrer le capitaine captif aux autorités.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "Je suis ici pour la régate. Voici mon invitation.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Peut-être que vous aimeriez faire une pause ?";
        			link.l5.go = "Play_Game";
        			link.l10 = "C'était juste une visite de courtoisie, "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Pas maintenant ! Nous avons une inspection, don de Alamida est en ville. Oh, chaque année la même chose, qu'ai-je fait pour mériter cela...";
				link.l1 = "Comme vous dites. Je ne vous distrairai pas.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			dialog.text = "Hmm, et quel genre de jeux préférez-vous ?";
			link.l1 = "Veux-tu jouer une partie de cartes pour de l'argent sérieux ?";
			link.l1.go = "Card_Game";
   			link.l2 = "Que dirais-tu de lancer quelques dés au poker-joker ?";
			link.l2.go = "Dice_Game";
			link.l10 = "Veuillez m'excuser, mais le devoir m'appelle.";
			link.l10.go = "exit";
		break;
		
		//  карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "Je vous prie de m'excuser, monseigneur, mais je n'ai pas le temps pour cela en ce moment. Peut-être une autre fois."; // Jason НСО
                else dialog.text = "Je ne joue pas avec les pirates !";
    			link.l1 = "Comme vous le souhaitez.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = "Pourquoi pas ! Se détendre est bon pour le cœur, mais pas pour la bourse...";
	    			link.l1 = "Excellent.";
	    			link.l1.go = "Cards_begin";
	    			link.l2 = "Quelles sont les règles de notre jeu ?";
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = "Non, j'en ai fini pour aujourd'hui. J'ai des choses à faire.";
	    			link.l1 = "Comme vous le souhaitez.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Eh bien, commençons alors !";
			link.l1.go = "Cards_begin";
			link.l3 = "Non, ce n'est pas pour moi...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = "Mettons-nous d'accord sur le pari, d'abord.";
			link.l1 = "Jouons pour 1000 pièces de huit.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Jouons pour 5000 piastres.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Je suppose que je dois y aller.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "Vous êtes un tricheur notoire. Je ne jouerai pas avec vous.";
                link.l1 = "C'est que des mensonges !";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Te moques-tu, "+GetAddress_Form(NPChar)+"? Vous n'avez pas d'argent !";
                link.l1 = "Ça arrive.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "C'est fini ! J'en ai assez des cartes - avant qu'ils ne me traitent de prodigue et ne me forcent à quitter mon poste.";
                link.l1 = "Pitié.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Très bien, jouons pour 1000 pièces de huit.";
			link.l1 = "Commençons !";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "Tu es un tricheur notoire. Je ne jouerai pas avec toi.";
                link.l1 = "Tout n'est que mensonges ! Eh bien, peu importe.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "On dit que vous êtes un très bon joueur. Je ne jouerai pas pour de grosses mises avec vous.";
                link.l1 = "Devons-nous baisser la mise, peut-être?";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "Je suis désolé, mais je dois y aller.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Te moques-tu, "+GetAddress_Form(npchar)+" ? Vous n'avez pas 15000 pièces de huit !";
                link.l1 = "Je les élèverai!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Non, ces paris videront le trésor de la ville.";
                link.l1 = "Comme vous le souhaitez.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Très bien, jouons pour 5000 pièces de huit.";
			link.l1 = "Commençons !";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 5000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--

	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "Je vous prie de m'excuser, monseigneur, mais je n'ai pas le temps pour cela en ce moment. Peut-être une autre fois."; // Jason НСО
                else dialog.text = "Je ne jouerai pas avec des pirates !";
    			link.l1 = "Comme vous le souhaitez.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Pourquoi pas ! Se détendre est bon pour le coeur... mais pas pour la bourse...";
	    			link.l1 = "Excellent.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "Quelles sont les règles de notre jeu ?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "Non, j'en ai fini pour aujourd'hui. J'ai des affaires à régler.";
	    			link.l1 = "Comme vous le souhaitez.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Eh bien, commençons alors !";
			link.l1.go = "Dice_begin";
			link.l3 = "Non, ce n'est pas pour moi...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = "Mettons-nous d'accord sur le pari, d'abord.";
			link.l1 = "Jouons pour 500 pièces de huit par dé.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Jouons pour 2000 pièces de huit par dé.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Je suppose que je dois y aller.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Tu es un tricheur notoire. Je ne jouerai pas avec toi.";
                link.l1 = "C'est tout des mensonges ! Eh bien, peu importe.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Tu plaisantes, "+GetAddress_Form(NPChar)+"? Vous n'avez pas d'argent !";
                link.l1 = "Ça arrive.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "C'est tout! J'en ai fini avec le jeu - avant qu'ils ne me traitent de dépensier et ne me forcent à quitter mon poste...";
                link.l1 = "Pitié.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "D'accord, jouons pour 500 pièces de huit.";
			link.l1 = "Commençons !";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 500;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Tu es un tricheur notoire. Je ne jouerai pas avec toi.";
                link.l1 = "Tout n'est que mensonges ! Bon, peu importe.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Ils disent que vous êtes un très bon joueur. Je ne jouerai pas de grosses mises avec vous.";
                link.l1 = "Devons-nous peut-être abaisser le pari ?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Je suis désolé, mais je dois y aller.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Tu plaisantes, "+GetAddress_Form(NPChar)+" ? Vous n'avez pas 15000 pièces de huit !";
                link.l1 = "Je les lèverai !";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Non, ces paris videront certainement le trésor de la ville.";
                link.l1 = "Comme vous voulez.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "D'accord, jouons pour 2000 pièces de huit par dé.";
			link.l1 = "Commençons !";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 2000;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
		case "node_2":
			dialog.text = "Dans ce cas, je vous demanderais de quitter mon cabinet et d'arrêter de me distraire de mon travail";
			link.l1 = "Oui, oui, bien sûr. Désolé de vous déranger.";
			link.l1.go = "exit";
		break;

		//---------------------------- генератор квестов мэра -------------------------------
		case "work": 
            dialog.text = "C'est un bug. Informez les développeurs à ce sujet.";
        	link.l1 = "Merci, c'est un excellent jeu !";
        	link.l1.go = "exit";
			
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Pas maintenant ! Nous avons une inspection, don de Alamida est en ville. Oh, chaque année la même chose, qu'ai-je fait pour mériter cela...";
				link.l1 = "Comme vous dites. Je ne vous distrairai pas.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			//==> взят ли какой-либо квест
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{		 				
				//--> Федот, да не тот
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id) 
				{					
					dialog.text = RandPhraseSimple("Autant que je puisse dire, vous avez déjà une mission donnée par le gouverneur de "+XI_ConvertString("Colonie"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Gen")+"Terminez le travail que vous avez déjà et nous parlerons.","Hmm, n'étiez-vous pas en "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Voc")+" où vous avez reçu des ordres du gouverneur local ? Oui, c'est exact. Terminez d'abord cette mission.");
					link.l1 = RandPhraseSimple("Je vois...","Compris..."+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".");
					link.l1.go = "exit";					
					break;
				}
				//<--Федот, да не тот
				//-------- взят квест уничтожения банды ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = LinkRandPhrase("Une mission pour localiser le bandit "+GetFullName(arName)+"  vous a déjà été accordée. Maintenant, accomplissez-la !","Vous avez déjà une mission pour localiser un bandit du nom de "+GetFullName(arName)+"J'attends les résultats !","Pendant que vous perdez votre temps dans ma résidence, "+GetFullName(arName)+"pille nos colons ! Au travail !");
							link.l1 = RandPhraseSimple("Très bien, "+GetAddress_FormToNPC(NPChar)+".","Je suis occupé avec ça, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Le temps qui vous était imparti pour localiser et éliminer ce bandit est écoulé. Et quels genres de rapports je reçois, à votre avis ? Et je vais vous le dire - "+GetFullName(arName)+" est toujours vivant et bien portant ! Maintenant, expliquez-vous, "+GetAddress_Form(NPChar)+".","Le temps qui vous est imparti pour éliminer ce scélérat du nom de "+GetFullName(arName)+", est épuisé. Pourtant, on me dit qu'aucun progrès n'a été fait. Que se passe-t-il ?");
							link.l1 = "Je n'ai pas pu accomplir votre tâche dans le temps imparti, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Alors, que dites-vous ? Avez-vous réussi à éliminer le bandit mentionné ? "+GetFullName(arName)+"est enfin mort ?","Dis-moi juste une chose - est-ce "+GetFullName(arName)+"mort ou vif ?");
							link.l1 = "Malheureusement, toujours en vie, "+GetAddress_FormToNPC(NPChar)+". J'ai réussi à le trouver, mais j'étais surpassé et j'ai été forcé de battre en retraite. Ce bandit est un vrai salaud coriace. Je suis désolé.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Alors, qu'en dites-vous ? Avez-vous réussi à éliminer le bandit mentionné ? "+GetFullName(arName)+"est enfin mort ?","Dis-moi juste une chose - est-ce que "+GetFullName(arName)+"mort ou vif ?");
							link.l1 = "Il est mort, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 180);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контркурьер ---------->>
				if (QuestName == "TakePostcureer")
				{
					switch (pchar.GenQuest.TakePostcureer)
					{
						case "":
							dialog.text = LinkRandPhrase("Une mission pour capturer un navire courrier vous a déjà été confiée. Maintenant, accomplissez-la !","Vous avez déjà une mission pour capturer un navire courrier ! J'attends les résultats !","Tandis que vous perdez votre temps dans ma résidence, les documents dont j'ai besoin tombent directement entre les mains de notre ennemi ! Au travail !");
							link.l1 = RandPhraseSimple("D'accord, "+GetAddress_FormToNPC(NPChar)+".","Je suis occupé avec ça, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Le temps qui vous était imparti pour localiser et capturer ce navire de courrier est écoulé. Et quel genre de rapports est-ce que je reçois, à votre avis ? Eh bien, je vais vous le dire - les documents que j'attendais sont tombés directement entre les mains de notre ennemi ! Maintenant, daignez vous expliquer, "+GetAddress_Form(NPChar)+".","Tous les délais qui vous ont été accordés pour capturer les documents du navire du courrier sont écoulés. Pourtant, aucun progrès n'a été fait. Qu'est-ce que c'est que cela ?");
							link.l1 = "Je n'ai pas pu accomplir la tâche à temps, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Alors, qu'en dites-vous ? Avez-vous réussi à capturer les documents ?","Dis-moi une seule chose - as-tu réussi à sécuriser la correspondance ?");
							link.l1 = "Malheureusement, non, "+GetAddress_FormToNPC(NPChar)+". J'ai localisé le navire, mais les documents m'ont échappé.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Alors, que dis-tu ? As-tu réussi à capturer les documents ?","Dis-moi juste une chose - as-tu réussi à sécuriser la correspondance ?");
							link.l1 = "Oui, "+GetAddress_FormToNPC(NPChar)+"Je les ai. Voilà.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							RemoveItems(pchar, "ContraPostLetters", 1);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контрфрахт - арсенал ---------->>
				if (QuestName == "TakeArsenalship")
				{
					switch (pchar.GenQuest.TakeArsenalship)
					{
						case "":
							dialog.text = LinkRandPhrase("Une mission pour détruire un transport militaire vous a déjà été confiée. Maintenant, accomplissez-la !","Vous avez déjà une mission pour détruire un transport militaire ! J'attends les résultats !","Tandis que vous perdez votre temps dans ma résidence, la poudre à canon et les munitions sont livrées directement aux canons ennemis ! Au travail !");
							link.l1 = RandPhraseSimple("D'accord, "+GetAddress_FormToNPC(NPChar)+".","Je suis occupé avec ça, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Le temps qui vous a été accordé pour localiser et détruire ce transport militaire est écoulé. Et quel genre de rapports je reçois, comment pensez-vous ? Eh bien, je vais vous le dire - le convoi ennemi a atteint sa destination avec succès ! Maintenant, daignez vous expliquer, "+GetAddress_Form(NPChar)+".","Tous les délais qui vous ont été donnés pour détruire le transport militaire ennemi sont écoulés. Pourtant, aucun progrès n'a été réalisé. Que se passe-t-il ?");
							link.l1 = "Je n'ai pas pu exécuter votre tâche dans le temps imparti, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Alors, que dites-vous ? Avez-vous réussi à détruire le transport ennemi ?","Dis-moi juste une chose - cet inventaire ennemi repose-t-il au fond de la mer ?");
							link.l1 = "Malheureusement, non, "+GetAddress_FormToNPC(NPChar)+". J'ai localisé le convoi, mais je n'ai pas réussi à couler le navire requis.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Alors, que dites-vous ? Avez-vous réussi à détruire ce transport ennemi ?","Dis-moi juste une chose - l'arsenal ennemi repose-t-il au fond de la mer ?");
							link.l1 = "Oui, "+GetAddress_FormToNPC(NPChar)+". Notre ennemi ne recevra pas cette poudre à canon et ces munitions.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 220);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- ОЗГ - пират ---------->>
				if (QuestName == "TakePirateship")
				{
					switch (pchar.GenQuest.TakePirateship)
					{
						case "":
							dialog.text = LinkRandPhrase("Une mission pour éliminer un pirate vous a déjà été confiée. Maintenant, accomplissez-la !","Vous avez déjà une mission pour détruire un navire pirate ! J'attends les résultats !","Alors que vous perdez votre temps dans ma résidence, ce pirate immonde dépouille une autre victime ! Allez travailler !");
							link.l1 = RandPhraseSimple("Très bien, "+GetAddress_FormToNPC(NPChar)+".","Je suis occupé avec ça, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Le temps qui vous était imparti pour localiser et éliminer le pirate est écoulé. Et quel genre de rapports je reçois, à votre avis ? Et je vais vous le dire - ce sale pirate continue de piller nos navires ! Maintenant, daignez vous expliquer, "+GetAddress_Form(NPChar)+".","Tous les délais qui vous ont été donnés pour détruire le navire pirate sont écoulés. Pourtant, aucun progrès n'a été réalisé. Que se passe-t-il?");
							link.l1 = "Je n'ai pas pu accomplir votre tâche à temps, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Alors, que dites-vous ? Avez-vous réussi à détruire le navire pirate ?","Dis-moi juste une chose - ce maudit pirate repose-t-il enfin au fond de la mer ?");
							link.l1 = "Malheureusement, non, "+GetAddress_FormToNPC(NPChar)+"J'ai réussi à débusquer ce vaurien, mais je n'ai pas réussi à couler son navire.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Alors, que dis-tu? As-tu réussi à détruire le navire pirate?","Dis-moi juste une chose - est-ce que ce sale pirate repose enfin au fond de la mer ?");
							link.l1 = "Oui, "+GetAddress_FormToNPC(NPChar)+"Ce vaurien ne troublera plus nos navires marchands.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
					//-------- ОЗГ - пассажир ---------->>
				if (QuestName == "TakePassenger")
				{
					switch (pchar.GenQuest.TakePassenger)
					{
						case "":
							dialog.text = LinkRandPhrase("Une mission pour traquer un criminel vous a déjà été confiée. Maintenant, accomplissez-la !","Vous avez déjà une mission pour traquer un criminel ! J'attends les résultats !","Tandis que vous perdez votre temps dans ma résidence, ce scélérat immonde continue à naviguer ! Procédez immédiatement avec la mission qui vous a été confiée !");
							link.l1 = RandPhraseSimple("D'accord, "+GetAddress_FormToNPC(NPChar)+".","Je suis occupé avec ça, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Le temps qui t'était imparti pour localiser ce vaurien est écoulé. Et quels types de rapports reçois-je, à ton avis ? Et je vais te le dire - il est arrivé à bon port et puis s'est évaporé dans la nature ! Maintenant, daigne t'expliquer, "+GetAddress_Form(NPChar)+".","Tous les délais qui vous ont été accordés pour retrouver le criminel sont écoulés. Pourtant, aucun progrès n'a été réalisé. Qu'est-ce qui se passe ?");
							link.l1 = "Je n'ai pas pu accomplir votre tâche dans le délai imparti, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Alors, que dis-tu ? As-tu capturé le scélérat ?","Dis-moi juste une chose - est-ce que ce vil scélérat est dans ta cale, bâillonné et enchaîné ?");
							link.l1 = "Malheureusement, non, "+GetAddress_FormToNPC(NPChar)+". J'ai échoué à capturer le scélérat. Il a coulé avec le navire sur lequel il était.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Alors, qu'en dites-vous? Avez-vous capturé le scélérat?","Dis-moi juste une chose - cet infâme scélérat est-il dans ta cale, bâillonné et enchaîné ?");
							link.l1 = "Oui, "+GetAddress_FormToNPC(NPChar)+". Veuillez envoyer vos soldats au quai, et je vous le remettrai.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.TakePassenger.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							sld.lifeday = 0;
						break;
					}
				}
				//-------- таможенный патруль ---------->>
				if (QuestName == "CustomPatrol")
				{
					switch (pchar.GenQuest.CustomPatrol)
					{
						case "":
							dialog.text = LinkRandPhrase("Une mission pour rechercher les contrebandiers vous a déjà été confiée. Maintenant, accomplissez-la!","Vous avez déjà une mission pour traquer les contrebandiers ! J'attends les résultats !","Pendant que vous perdez votre temps dans ma résidence, ces contrebandiers se préparent à conclure une autre affaire ! Allez immédiatement accomplir la mission qui vous a été confiée !");
							link.l1 = RandPhraseSimple("D'accord, "+GetAddress_FormToNPC(NPChar)+".","Je suis occupé avec cela, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Le temps qui vous était donné pour localiser les contrebandiers est écoulé. Et quel genre de rapports je reçois, à votre avis ? Et je vais vous le dire - ils ont joyeusement vendu toutes leurs marchandises ! Maintenant, daignez vous expliquer, "+GetAddress_Form(NPChar)+".","Tous les délais qui vous ont été donnés pour trouver les contrebandiers sont écoulés. Pourtant, aucun progrès n'a été réalisé. Que se passe-t-il ?");
							link.l1 = "Je n'ai pas pu accomplir votre tâche à temps, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Alors, que dites-vous ? Avez-vous réglé le compte des contrebandiers ?","Dis-moi une seule chose - as-tu fait échouer l'affaire de ces contrebandiers ?");
							link.l1 = "Malheureusement, non, "+GetAddress_FormToNPC(NPChar)+". J'ai échoué à déjouer les plans de ces scélérats.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Alors, qu'en dis-tu ? As-tu réglé le compte des contrebandiers ?","Dis-moi juste une chose - as-tu fait échouer le marché de ces contrebandiers ?");
							link.l1 = "Oui, "+GetAddress_FormToNPC(NPChar)+"Je les ai rattrapés et j'ai éliminé les navires des deux parties, acheteur et vendeur.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 300);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- Дезертир ---------->>
				if (QuestName == "FindFugitive")
				{
					switch (pchar.GenQuest.FindFugitive)
					{
						case "":
							dialog.text = LinkRandPhrase("Une mission pour retrouver le déserteur vous a déjà été confiée. Maintenant, accomplissez-la !","Vous avez déjà pour mission de retrouver le déserteur ! J'attends les résultats !","Alors que tu perds ton temps dans ma résidence, ce déserteur pourrait trahir nos secrets d'État ! Va immédiatement remplir la mission qui t'a été confiée !");
							link.l1 = RandPhraseSimple("D'accord, "+GetAddress_FormToNPC(NPChar)+".","Je suis occupé avec ça, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Le temps qui vous était accordé pour localiser le déserteur est écoulé. Et quels types de rapports je reçois, à votre avis ? Et je vais vous le dire - aucun résultat, aucun du tout ! Maintenant, daignez vous expliquer, "+GetAddress_Form(NPChar)+".","Tous les délais qui vous ont été accordés pour trouver le déserteur sont expirés. Pourtant, aucun progrès n'a été réalisé. Que se passe-t-il ?");
							link.l1 = "Je n'ai pas pu accomplir votre tâche à temps, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Alors, que dis-tu? As-tu capturé le déserteur?","Dis-moi juste une chose - est-ce que ce déserteur est dans ta cale, bâillonné et menotté?");
							link.l1 = "Malheureusement, non, "+GetAddress_FormToNPC(NPChar)+". J'ai échoué à capturer ce vaurien. J'ai trouvé sa piste dans la colonie de "+XI_ConvertString("Colonie"+pchar.GenQuest.FindFugitive.City)+", mais juste la veille de mon arrivée, il est parti vers le sud sur un navire pirate. Je suppose qu'il est maintenant avec ces gentilshommes de fortune.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Eh bien... Voici notre "+pchar.GenQuest.FindFugitive.Name+"... Excellent travail, capitaine ! Avez-vous eu du mal à chercher ?","Oh, quels invités avons-nous là ! Bonjour, "+pchar.GenQuest.FindFugitive.Name+"! Excellent travail, capitaine ! Avez-vous fourni beaucoup d'efforts dans votre recherche ?");
							link.l1 = "Comment dire, "+GetAddress_FormToNPC(NPChar)+". Quoi que ce soit - votre mission a été accomplie.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 300);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar, "authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							LAi_SetActorType(sld);
							sld.lifeday = 0;
							pchar.quest.FindFugitive_Over.over = "yes"; //снимаем таймер
							chrDisableReloadToLocation = false;//открыть локацию
						break;
					}
				}
				//------ проникновение во враждебный город ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								dialog.text = RandPhraseSimple("Le temps qui vous était imparti pour livrer la lettre est écoulé. Et je suppose que vous avez échoué.","Le temps est écoulé. Pourtant, aucun progrès n'a été fait. Que se passe-t-il ?");
								link.l1 = "Je n'ai pas pu accomplir votre tâche, "+GetAddress_FormToNPC(NPChar)+".";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase("Une mission pour me livrer une lettre vous a déjà été confiée. Maintenant, accomplissez-la !","Vous avez déjà une mission pour me livrer une lettre directement! J'attends les résultats, j'ai besoin de cette lettre dès que possible!","Alors que vous perdez votre temps dans ma résidence, les informations dont j'ai cruellement besoin sont encore entre les mains de la personne censée me les envoyer ! Allez immédiatement mener à bien la mission qui vous a été confiée !");
								link.l1 = RandPhraseSimple("D'accord, "+GetAddress_FormToNPC(NPChar)+".","Je m'y attelle immédiatement, "+GetAddress_FormToNPC(NPChar)+".");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("As-tu livré la lettre que j'attends?","Dis-moi maintenant - l'as-tu?!");
							link.l1 = "Oui, je le fais. Comme convenu - livré à vous, personnellement.";
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								link.l1.go = "Intelligence_ExecuteLate";
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							else
							{
								link.l1.go = "All_Execute";		
								AddCharacterExpToSkill(PChar, "Leadership", 100);
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							TakeItemFromCharacter(pchar, "sicretLetter");
							DeleteAttribute(ItemsFromID("sicretLetter"), "City");
							DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
						break;
					}
				}
				break;
			}
			sTemp = npchar.city;
			//занят ПГГ
			i = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONMAYOR);
			if (i != -1)
			{
				dialog.text = "Hélas, aujourd'hui je n'ai pas de travail pour toi. Le dernier a été fait par "+GetFullName(&Characters[i])+" Reviens demain, peut-être que quelque chose apparaîtra.";
				link.l1 = "Oh, diable ! Pas de chance...";
				link.l1.go = "exit";
				break;
			}
//navy <--
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") > 2 || bBettaTestMode)
    		{	
				SaveCurrentNpcQuestDateParam(npchar, "work_date");
				if(CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)
				{
					dialog.text = "Vous arrivez juste à temps, capitaine. Je dois résoudre un problème urgent lié à la contrebande de marchandises vers notre colonie. Je suppose que votre navire est en état de naviguer et prêt au combat.";
					link.l1 = "Mon navire est toujours prêt pour la mer et apte au combat. Je vous en prie, dites-m'en plus sur la mission à venir, votre grâce.";
					link.l1.go = "CustomPatrol";
					break;
				}
				if (rand(5) > 4 && !bBettaTestMode && pchar.location == "Panama_townhall") // patch-5
				{
					dialog.text = LinkRandPhrase("Pour l'instant, je n'ai pas de travail pour vous. Revenez demain, je suppose...","Hélas, je n'ai pas de travail pour vous aujourd'hui. Revenez dans un jour ou deux, s'il vous plaît.","Aujourd'hui, je n'ai rien à vous proposer. Je serai ravi de vous voir un autre jour.");
					link.l1 = "Je comprends, "+GetAddress_FormToNPC(NPChar)+".";
					link.l1.go = "exit";
				}
				else
				{
					sTemp = GetSpyColony(npchar);
					// не даём задание пробраться во вражеский город, если у нации ГГ нет врагов
					if (sTemp == "none")
						i = 1 + hrand(6);
					else
						i = hrand(7);
					switch (i)
					{
						//========== пробраться во вражеский город ============//Jason: оставляем, как годный
						case 0:
							pchar.GenQuest.Intelligence.Terms = hrand(10) + (42 - MOD_SKILL_ENEMY_RATE); //сроки выполнения задания
							pchar.GenQuest.Intelligence.Money = ((hrand(4) + 6) * 2000) + (sti(pchar.rank) * 1000 + 10000); //вознаграждение
							pchar.GenQuest.Intelligence.City = sTemp; //враждебная колония
                            sTemp = ", which is on " + XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat");                         
							dialog.text = "J'ai une mission pour vous, qui comporte des risques sérieux. J'ai besoin que vous vous infiltriez dans "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc")+sTemp+", rencontre une certaine personne là-bas, puis remets-moi ce qu'il te donnerait.";
							link.l1 = "Hmm, je ne pense pas que dans "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" Je serai un invité bienvenu...";
							link.l1.go = "Intelligence";
						break;
						//========== квест уничтожения банды ============ //Jason: оставляем, как классику
						case 1:
							pchar.GenQuest.DestroyGang.Terms = hrand(2) + 2; //сроки выполнения задания
							pchar.GenQuest.DestroyGang.Money = ((hrand(6)+4)*500)+(sti(pchar.rank)*300+2000); //вознаграждение
							makearef(arName, pchar.GenQuest.DestroyGang);
							arName.nation = PIRATE;
							arName.sex = "man";
							SetRandomNameToCharacter(arName); //имя бандита в структуру квеста	
							dialog.text = "Je viens d'avoir une mission pour vous. Dans la jungle près de "+XI_ConvertString("Colony"+npchar.city+"Gen")+" une bande de brigands est apparue, et je sais que le chef de cette bande se nomme "+GetFullName(arName)+". Localisez et éliminez cette bande de vauriens.";
							link.l1 = "Suis-je d'une manière ou d'une autre limité dans les termes ?";
							link.l1.go = "DestroyGang";
						break;
						
						//========== контркурьер - отобрать почту ============
						case 2:
							dialog.text = "Oui, j'ai une mission pour vous. Pour l'accomplir, vous devrez faire preuve de rapidité et aussi d'une certaine habileté au combat naval. Êtes-vous prêt à prouver votre valeur ?";
							link.l1 = "Votre Grâce, pouvez-vous révéler plus de détails sur la mission ?";
							link.l1.go = "TakePostcureer";
						break;
						
						//========== контрфрахт - потопить корабль с боеприпасами ============
						case 3:
							dialog.text = "Oui, j'ai une mission pour vous. Pour l'accomplir, vous devrez faire preuve d'une galanterie exceptionnelle et aussi d'une certaine compétence en combat naval. Êtes-vous prêt à prouver votre valeur ?";
							link.l1 = "Votre Grâce, pouvez-vous révéler plus de détails sur la mission à venir ?";
							link.l1.go = "TakeArsenalship";
						break;
						//========== ОЗГ - охотник на пирата ============
						case 4:
							dialog.text = "Oui, j'ai une mission importante pour vous. Pour l'accomplir, vous devrez utiliser toutes vos compétences. Cela implique des pirates...";
							link.l1 = "Des pirates ? Pouvez-vous me dire plus en détail ce qui est attendu de moi, alors ?";
							link.l1.go = "TakePirateship";
						break;
						//========== ОЗГ - охотник на пассажира ============
						case 5:
							dialog.text = "Vous arrivez à point nommé, monsieur. J'ai une mission urgente qui vous conviendra parfaitement. Elle implique de traquer et capturer une certaine personne...";
							link.l1 = "Une chasse à l'homme ? Pouvez-vous me dire plus en détail ce qu'on attend de moi ?";
							link.l1.go = "TakePassenger";
						break;
						//========== Патруль - таможенник ============
						case 6:
							dialog.text = "Vous arrivez à temps, capitaine. Je dois régler un problème urgent lié à la contrebande de marchandises vers notre colonie. Je suppose que votre navire est en bon état et prêt pour le combat ?";
							link.l1 = "Mon navire est toujours prêt pour la mer et prêt pour la bataille. Je vous prie, parlez-moi davantage de la mission à venir, votre grâce.";
							link.l1.go = "CustomPatrol";
						break;
							//========== Найти дезертира ============
						case 7:
							dialog.text = "J'ai une mission pour vous qui implique de visiter plusieurs colonies dans les Caraïbes. Êtes-vous prêt pour un long voyage ?";
							link.l1 = "Oui, mes hommes et moi sommes prêts à partir sur-le-champ. Que devrai-je faire exactement ?";
							link.l1.go = "FindFugitive";
						break;
					}
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Aujourd'hui, je ne peux vous proposer aucun travail.","Aujourd'hui, il n'y a plus de travail pour vous.","Plus de travail pour aujourd'hui, désolé. Revenez demain, et nous verrons...");
				link.l1 = RandPhraseSimple("Pitié...","Ah, quel dommage, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
			}
		//---------------------------- генератор квестов мэра -------------------------------
		break;

		case "sell_prisoner":
            dialog.text = "Qui souhaitez-vous rançonner ?";

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                            attrLoc = "l"+qty;
                            link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = "Personne.";
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  "So, this is captain " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // цена зависит от губернатора
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
			if(HasShipTrait(pchar, "trait14")) qty = makeint(qty * 1.35);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + " I am ready to pay the ransom for my compatriot in the amount of  " + FindRussianMoneyString(qty) + ".";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + " I can give " + FindRussianMoneyString(qty) + "  for this gallowsbird. And then we'll execute the scoundrel at once.";

                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + " " + FindRussianMoneyString(qty) + "for that man, not a peso more.";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = "Marché conclu. Il est tout à vous, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = "Non. Cela ne fera pas l'affaire.";
			link.l3.go = "exit";
		break;


		case "sell_prisoner_3":
			dialog.text = "C'est bien.";
			link.l1 = "Tout le meilleur.";
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
            {
                AddCharacterExpToSkill(pchar, "Commerce", 25);
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    ChangeCharacterComplexReputation(pchar,"nobility", -2);
                }
                else
                {
                    AddCharacterExpToSkill(pchar, "Commerce", 5);
                }
            }

        	offref.location = "";
        	ReleasePrisoner(offref); // освободили пленника
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // всё, все свободны
			
			// --> Левассер
			if (pchar.location == "Tortuga_townhall" && CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga"))
			{
                dialog.Text = "Arrgh ! Qu'est-ce que c'est que cette indignation, de Maure ? Depuis quand les Français attaquent-ils leurs propres compatriotes ?!";
                Link.l1 = "Par l'ordre du Gouverneur-Général Francois Longvillier de Poincy, vous, Monsieur Levasseur, êtes démis de votre poste de gouverneur de Tortuga et condamné à mort ! Et c'est moi qui exécuterai cette sentence !";
                Link.l1.go = "levasser";
				break;
			}
			// <-- Левассер
            // fix от грабежа 5 раз на дню -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = "Vous avez déjà tout pris. Que vous faut-il d'autre ?";
                Link.l1 = "Oui, d'accord, mauvaise ville.";
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

            	ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
                // вернём диалог после разговора и спрячем
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix от грабежа 5 раз на дню <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
            { // а форт-то ЖИВ, значит с суши прошли
                dialog.Text = "Insolence sans précédent ! Les renforts du fort arriveront bientôt et tu paieras pour cela !";
                Link.l2 = "Je ne vais pas attendre ici jusqu'à leur arrivée. Payez-moi, et nous quitterons cette ville.";
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // токо половина денег
            }
            else
            {
				dialog.Text = "Vous avez gagné cette fois, mais sachez qu'une escouade de nos chasseurs de pirates vous traquera et arrachera chaque peso de votre chair de pirate immonde !";
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = "Silence! This town belongs to me from now on; as for your piratehunters - I'll send them straight to Davy Jones' Locker. Hey lads, grab this pig and put it behind bars.";
	    				}
	    				else
	    				{
	    					Link.l1 = "Cette ville m'appartient désormais. Les gars, escortez l'ex-gouverneur dans ses nouveaux 'quartiers', heh heh.";
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = "Des renforts du fort ? Payez-moi une belle rançon, et nous quitterons votre ville.";
				}
				else
				{
	            	Link.l2 = "Une escadre de chasseurs de pirates ? Hmm... Payez-moi simplement et nous quitterons votre ville.";
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
	            {
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = "Insolence sans précédent ! Comment osez-vous attaquer la colonie appartenant à "+NationNameGenitive(sti(NPChar.nation))+"? ! Vous paierez cher pour le sang que vous avez versé et pour les dégâts que vous avez infligés à notre état.";
	                Link.l1 = "Desormais, cette colonie m'appartient. Quiconque ose contester mon autorite ira droit en enfer.";
	                Link.l1.go = "City_patent";
	                Link.l2 = "Abaissez vos armes. J'agis au nom de "+NationNameGenitive(sti(PChar.nation))+". A partir de maintenant cette colonie appartient à "+NationKingsCrown(PChar)+" !";
	                Link.l2.go = "City_nation";
	                Link.l3 = "Charmante ville que vous avez ici. Ce serait vraiment tragique si elle était réduite en cendres et son gouverneur pendu sur la place de la ville. Nous devrions discuter de la taille de la rançon que vous êtes prêt à payer pour éviter cette tragédie.";
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
		
		// --> Левассер
		case "levasser":
            dialog.Text = "Poincy ?! Maudit soit ce bâtard papiste ! Je vais m'occuper de lui... et toi, tu es fini, scélérat ! Tu ne sortiras pas d'ici vivant - je vais personnellement t'achever !";
			Link.l1 = "Épargne-moi ton prêche, hérétique. Quand j'enverrai ton âme huguenote en Enfer, donne mes meilleures salutations à Lucifer et Jean Calvin. En garde !";
			Link.l1.go = "levasser_1";
        break;
		
		case "levasser_1":
			chrDisableReloadToLocation = true;//закрыть локацию
            DialogExit();
			LAi_SetImmortal(npchar, false);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto6");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LevasserDiedResidence");
			AddDialogExitQuest("MainHeroFightModeOn");	
        break;
		// <-- Левассер
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 400);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            // ремонт
            RepairAllShips();
            Log_Info("All ships have been repaired.");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
        break;

        case "City_patent":
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -20); // пираты мы, но у нас патент
            dialog.Text = "Tu as gagné cette fois, mais sache que notre escadre arrivera bientôt et qu'elle ne laissera rien de toi !";
			Link.l1 = "Shut your mouth. This town belongs to me from now on; as for your squadron - I'll send it straight to Hell. Boys, escort the ex-governor to his new 'quarters', heh heh.";
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = "Que voulez-vous d'autre de moi ?";
            Link.l1 = "Je vérifie juste si j'ai raté quelque chose...";
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
		    NextDiag.CurrentNode = "Exit_for_pay";
		    Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		    if (sti(NPChar.NoGiveMoney) == false) // себе берем
		    {
				// вернём диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
            dialog.Text = "Je n'ai pas d'autre choix que d'accepter vos conditions. Prenez votre fichu argent et quittez notre colonie sur-le-champ.";
            Link.l1 = "Un plaisir de faire affaire avec vous.";
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
            AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 300);
            AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 300);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
        break;

        case "Summ_patent":
            dialog.Text = "Très bien, énoncez vos conditions...";
            Link.l1 = "Oui, vae victis ! Commence à compter ton argent.";
            Link.l1.go = "Summ";
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -10); // не на службе
        break;

        case "City_nation":
			dialog.Text = "D'accord, nous nous rendons à votre merci.";
			Link.l1 = "Je vous conseille de quitter la ville dès que possible - les changements à venir pourraient être très mauvais pour votre santé. Adieu.";
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 600);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 400);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

            PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
            //  СЖ -->
	    	sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  СЖ <--
			AddTitleNextRate(sti(PChar.nation), 1);  // счетчик звания
            SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// нечего не даёт, тк работает OtherChar - а это губер, но он и так друг
            UpdateRelations();

            // 22.03.05  fix вернём диалог после разговора и спрячем
            //  внутри диалога не работало
            SetReturn_Gover_Dialog_Exit(NPChar);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
	    break;
	    
	    case "Prison":
			dialog.Text = "Que voulez-vous de plus de ma part, gredin ?";
            Link.l3 = "Comment Votre Excellence se plaît-elle dans sa nouvelle chambre ? Assez spacieuse ? Eh bien, je dois y aller maintenant !";
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = "S'installer ? Et comment imaginez-vous cela ?";
            link.l1 = "Je pense qu'une somme de "+iTotalTemp*6000+" pesos peuvent encore me sauver, n'est-ce pas ?";
			link.l1.go = "arestFree_2";
			link.l2 = "Non. Et il est temps pour moi de partir. Mes salutations distinguées.";
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= hrand(7) && iTotalTemp < 21)
            {
    			dialog.text = "Je suppose que nous pourrions régler notre incident de cette manière. Vous n'avez pas encore poussé la situation à un point irréparable.";
    		    link.l1 = "Excellent. Je suis très content. S'il vous plaît, acceptez mon don.";
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -iTotalTemp*6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
    		    AddCharacterExpToSkill(pchar, "Fortune", 100);
            }
            else
            {
    			dialog.text = "Me proposes-tu un pot-de-vin ? Oh non ! Tes actes maléfiques ne peuvent être expiés que d'une seule manière... Gardes ! Mettez "+GetSexPhrase("lui","elle")+"en fers !";
    		    link.l1 = "Attendez !";
    		    link.l1.go = "arest_2";
    		    AddCharacterExpToSkill(pchar, "Fortune", 10);
            }
		break;

		case "arest_1":
			dialog.text = "Bien sûr, il est temps. Nous vous raccompagnerons. Gardes ! Saisissez "+GetSexPhrase("lui","elle")+" !";
		    link.l1 = "Aucune chance !";
		    link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = "Tu as eu tout le temps de réfléchir ! Gardes !";
			link.l1 = "Vous ne m'aurez pas facilement !";
		    link.l1.go = "fight";
		break;    
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение банды
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			dialog.text = "Bien sûr. Pour accomplir cette mission, je vous donne "+FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms))+", et ta récompense en cas de succès sera "+FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money))+".";
			link.l1 = "Oui, j'accepte cette tâche.";
		    link.l1.go = "DestroyGang_agree";
			link.l2 = "Hmm... Non, je pense que je vais passer.";
		    link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //тип квеста
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			if (pchar.GenQuest.DestroyGang.Location == "none") //на всякий случай
			{
				dialog.text = "Attends, j'ai juste oublié le rapport d'hier. Le fait est que cette bande a déjà quitté notre île. Donc je dois annuler la mission.";
				link.l1 = "Je vois. Quel dommage.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = "Eh bien, formidable ! Je vous attendrai à ma résidence avec vos rapports.";
				link.l1 = "Je ne vous ferai pas attendre longtemps, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //тупо дожидаться своего часа бандиты не будут
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> энкаунтеров в квестовой локации не будет 
				locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "1");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				makearef(arName, pchar.GenQuest.DestroyGang);
				AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контркурьер
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePostcureer":
			//установка параметров
			pchar.GenQuest.questName = "TakePostcureer"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index)); //вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Aujourd'hui, je ne peux vous offrir aucun emploi.","Aujourd'hui, il n'y a plus de travail pour vous.","Pas d'autres travaux pour aujourd'hui, désolé. Revenez demain, et nous verrons...");
				link.l1 = RandPhraseSimple("Pitié...","Ah, quel dommage, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePostcureer.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakePostcureer.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakePostcureer.Island = GetArealByCityName(pchar.GenQuest.TakePostcureer.City);
			pchar.GenQuest.TakePostcureer.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePostcureer.Island)+5;
			pchar.GenQuest.TakePostcureer.LoginDay = sti(pchar.GenQuest.TakePostcureer.Terms)-1;
			pchar.GenQuest.TakePostcureer.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePostcureer.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePostcureer.Nation));
			pchar.GenQuest.TakePostcureer.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePostcureer.ShipType));
			pchar.GenQuest.TakePostcureer.Money = ((hrand(5)+hrand(6)+4)*2000)+(sti(pchar.rank)*500);
			dialog.text = "Bien sûr. Vous devrez localiser un navire courrier de "+NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation))+" du nom de '"+pchar.GenQuest.TakePostcureer.ShipName+", aborde-le et apporte-moi les papiers, que tu devrais pouvoir trouver dans la cabine du capitaine. Ce navire passera près de "+XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen")+" approximativement dans "+FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms)+".";
			link.l1 = "Très bien, j'accepte cette mission. Et quels types de documents dois-je chercher ?";
		    link.l1.go = "TakePostcureer_agree";
			link.l2 = "Hmm... Non, je pense que je vais passer.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePostcureer_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePostcureer.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Courrier. Il y a des papiers très importants pour moi. Mais il n'est pas nécessaire que vous cherchiez parmi les documents, apportez-moi simplement le paquet entier. Je vous paierai "+FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money))+"Donc, je vous attendrai ainsi que le résultat de votre travail à ma résidence.";
			link.l1 = "Je ne vous ferai pas attendre longtemps, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.quest.TakePostcureer.win_condition.l1 = "location";
			pchar.quest.TakePostcureer.win_condition.l1.location = pchar.GenQuest.TakePostcureer.Island;
			pchar.quest.TakePostcureer.win_condition.l2 = "Timer";
			pchar.quest.TakePostcureer.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakePostcureer.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.function = "TakePostcureer_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePostcureer.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "3");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePostcureer.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePostcureer.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контрфрахт - уничтожить корабль с арсеналом
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakeArsenalship":
			//установка параметров
			pchar.GenQuest.questName = "TakeArsenalship"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Aujourd'hui, je ne peux vous offrir aucun travail.","Aujourd'hui, il n'y a plus de travail pour vous.","Plus de travail pour aujourd'hui, désolé. Revenez demain, et nous verrons...");
				link.l1 = RandPhraseSimple("Quel dommage...","Ah, quel dommage, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakeArsenalship.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakeArsenalship.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakeArsenalship.Island = GetArealByCityName(pchar.GenQuest.TakeArsenalship.City);
			pchar.GenQuest.TakeArsenalship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakeArsenalship.Island)+5;
			pchar.GenQuest.TakeArsenalship.LoginDay = sti(pchar.GenQuest.TakeArsenalship.Terms)-1;
			pchar.GenQuest.TakeArsenalship.ShipType = SelectArsenalShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.TakeArsenalship.ShipTypeA = SelectArsenalShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.TakeArsenalship.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakeArsenalship.Nation));
			pchar.GenQuest.TakeArsenalship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipType));
			pchar.GenQuest.TakeArsenalship.CannonA = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipTypeA)); // Addon 2016-1 Jason пиратская линейка
			pchar.GenQuest.TakeArsenalship.Money = ((hrand(5)+hrand(6)+4)*1800)+(sti(pchar.rank)*500);
			dialog.text = "Bien sûr. Vous devrez localiser un transport militaire de "+NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation))+", with gunpowder and ammunition on board; the name of the vessel is '"+pchar.GenQuest.TakeArsenalship.ShipName+"', find and destroy it. We'll weaken our enemy by doing that\nThe transport will sail with an escort to the colony "+XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City)+", and will be approximately in "+FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms)+", so you should hurry.";
			link.l1 = "D'accord, j'accepte. Dois-je couler le navire arsenal ou devrais-je tenter de le capturer ?";
		    link.l1.go = "TakeArsenalship_agree";
			link.l2 = "Hmm... Non, je pense que je vais m'abstenir.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakeArsenalship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakeArsenalship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Je m'en moque, cela dépend de vous. L'important est que cette cargaison ne doit pas atteindre sa destination. Si vous réussissez, je vous paierai "+FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money))+"... Je ne vous retarde plus, capitaine.";
			link.l1 = "Je ne vous ferai pas attendre longtemps, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.quest.TakeArsenalship.win_condition.l1 = "location";
			pchar.quest.TakeArsenalship.win_condition.l1.location = pchar.GenQuest.TakeArsenalship.Island;
			pchar.quest.TakeArsenalship.win_condition.l2 = "Timer";
			pchar.quest.TakeArsenalship.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakeArsenalship.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.function = "TakeArsenalship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakeArsenalship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "8");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakeArsenalship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakeArsenalship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - уничтожить корабль пиратов
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePirateship":
			//установка параметров
			pchar.GenQuest.questName = "TakePirateship"; //тип квеста
			pchar.GenQuest.TakePirateship.City = FindQuestCity(npchar, "all", -1, true, true); // belamour legendary edition 
			pchar.GenQuest.TakePirateship.Island = GetArealByCityName(pchar.GenQuest.TakePirateship.City);
			pchar.GenQuest.TakePirateship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePirateship.Island)+5;
			pchar.GenQuest.TakePirateship.ShipType = SelectPirateShipType();
			pchar.GenQuest.TakePirateship.ShipName = GenerateRandomNameToShip(PIRATE);
			pchar.GenQuest.TakePirateship.Name = GenerateRandomName(PIRATE, "man");
			pchar.GenQuest.TakePirateship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePirateship.ShipType));
			pchar.GenQuest.TakePirateship.Money = ((hrand(5)+hrand(6)+4)*2400)+(sti(pchar.rank)*500);
			dialog.text = "Bien sûr. Je suis vraiment furieux des agissements d'un capitaine pirate, dont le nom est "+pchar.GenQuest.TakePirateship.Name+". Ce gredin a pris l'habitude de piller nos marchands, ce qui nuit énormément au commerce entre les colonies. C'est maintenant le moment idéal pour se débarrasser de ce bâtard, car je viens juste de découvrir où il se cache en ce moment. Es-tu prêt à envoyer ce fils de pute sur le Siège du Jugement de Dieu ?";
			link.l1 = "Je serais honoré ! Où puis-je trouver ce pirate ?";
		    link.l1.go = "TakePirateship_agree";
			link.l2 = "Hmm... Non, je pense que je vais passer.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePirateship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePirateship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Dans le plus proche "+FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms)+" son navire du nom de '"+pchar.GenQuest.TakePirateship.ShipName+" sera en croisière près des côtes de "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". Trouvez-le et tuez-le. Envoyez-le nourrir les poissons avec le navire, abordez le navire - cela m'importe peu. Ce qui m'importe, c'est que ce maudit pirate cesse de souiller nos mers de sa présence\nPour cette tâche, je suis prêt à vous payer "+FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money))+"Ne perdez pas de temps, capitaine : ce vaurien ne vous attendra pas à "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+"Allez, et que Dieu vous aide !";
			link.l1 = "Levez l'ancre déjà, "+GetAddress_FormToNPC(NPChar)+" ! Vous n'attendrez pas longtemps.";
			link.l1.go = "exit";
			pchar.quest.TakePirateship.win_condition.l1 = "location";
			pchar.quest.TakePirateship.win_condition.l1.location = pchar.GenQuest.TakePirateship.Island;
			pchar.quest.TakePirateship.function = "TakePirateship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePirateship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "9");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePirateship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePirateship.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePirateship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - захватить пассажира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePassenger":
			//установка параметров
			pchar.GenQuest.questName = "TakePassenger"; //тип квеста
			pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));//вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Aujourd'hui je n'ai point de travail à vous proposer.","Aujourd'hui, il n'y a plus de travail pour vous.","Plus de travail pour aujourd'hui, désolé. Revenez demain, et nous verrons...");
				link.l1 = RandPhraseSimple("Quel dommage...","Ah, quel dommage, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePassenger.City = FindQuestCity(npchar, "enemy", sti(pchar.GenQuest.TakePassenger.Nation), false, false); // belamour legendary edition
			pchar.GenQuest.TakePassenger.CityA = SelectAnyColony(pchar.GenQuest.TakePassenger.City);
			pchar.GenQuest.TakePassenger.Terms1 = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, GetArealByCityName(pchar.GenQuest.TakePassenger.City));
			pchar.GenQuest.TakePassenger.Terms2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.TakePassenger.City), GetArealByCityName(pchar.GenQuest.TakePassenger.CityA))+1;
			pchar.GenQuest.TakePassenger.Terms = sti(pchar.GenQuest.TakePassenger.Terms1)+sti(pchar.GenQuest.TakePassenger.Terms2);
			pchar.GenQuest.TakePassenger.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePassenger.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePassenger.Nation));
			pchar.GenQuest.TakePassenger.Name = GenerateRandomName(sti(pchar.GenQuest.TakePassenger.Nation), "man");
			pchar.GenQuest.TakePassenger.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePassenger.ShipType));
			pchar.GenQuest.TakePassenger.Money = ((hrand(5)+hrand(6)+4)*2200)+(sti(pchar.rank)*500);
			string sText = SelectPassText();
			dialog.text = "Bien sûr. Je parle d'un gredin du nom de "+pchar.GenQuest.TakePassenger.Name+". "+sText+" Je le cherchais depuis pas mal de temps, et maintenant j'ai enfin obtenu des informations fiables sur l'endroit où il se trouve. J'ai besoin que tu m'amènes cet homme, coûte que coûte vivant. Je veux le pendre en public sur la place de notre ville. Es-tu prêt à entreprendre cette mission ?";
			link.l1 = "Je suis prêt, "+GetAddress_FormToNPC(NPChar)+"Où puis-je trouver ce vaurien ?";
		    link.l1.go = "TakePassenger_agree";
			link.l2 = "Hmm... Non, je pense que je vais passer.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePassenger_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePassenger.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Juste à "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1)+", il, en tant que passager sur un navire du nom de '"+pchar.GenQuest.TakePassenger.ShipName+", naviguera hors de "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen")+" et allez à "+XI_ConvertString("Colonie"+pchar.GenQuest.TakePassenger.CityA+"Acc")+". Tu as "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms)+" pour trouver ce navire sur le segment de route spécifié, aborder et saisir ce salaud. Si vous suivez cette instruction, je vous paierai "+FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money))+"Bonne chance à vous, capitaine !";
			link.l1 = "Je ne perdrai pas plus de temps, "+GetAddress_FormToNPC(NPChar)+"! Je vais mettre les voiles immédiatement.";
			link.l1.go = "exit";
			SetFunctionTimerCondition("TakePassenger_CreateShip", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms1), false);
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sCityA", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc"));
			AddQuestUserData("MayorsQuestsList", "sDay1", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms1)));
			AddQuestUserData("MayorsQuestsList", "sDay2", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePassenger.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePassenger.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Таможенный патруль
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "CustomPatrol":
			//установка параметров
			pchar.GenQuest.questName = "CustomPatrol"; //тип квеста
			pchar.GenQuest.CustomPatrol.Nation = sti(npchar.nation);//нация
			pchar.GenQuest.CustomPatrol.Island = Islands[GetCharacterCurrentIsland(PChar)].id;
			pchar.GenQuest.CustomPatrol.LoginDay = rand(4)+1;
			pchar.GenQuest.CustomPatrol.Loginlocator = rand(3)+4;
			pchar.GenQuest.CustomPatrol.ShipType = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.CustomPatrol.ShipTypeA = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.CustomPatrol.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.CustomPatrol.ShipType));
			pchar.GenQuest.CustomPatrol.Money = ((hrand(5)+hrand(6)+4)*1400)+(sti(pchar.rank)*300);
			dialog.text = "J'ai des informations fiables qu'un certain capitaine a arrangé une transaction avec des contrebandiers concernant la vente de quelques esclaves. Comme vous devez le savoir, de telles transactions par des particuliers dans nos colonies sont caractérisées comme des marchandises de contrebande\nLe problème est que je ne connais ni l'heure exacte, ni la date, ni l'endroit où les contrebandiers se rencontreront. On sait seulement qu'une transaction criminelle sera réalisée dans les cinq prochains jours sur notre île. Pour aggraver les choses, tous mes navires de patrouille sont soit en réparation, soit impliqués dans d'autres tâches et ne peuvent pas trouver ces vauriens\nJe vous suggère de vous occuper de cette tâche - traquez les contrebandiers et traitez-les avec les méthodes les plus radicales, faites-en un exemple. Êtes-vous prêt à accomplir cette mission ?";
			link.l1 = "Je suis prêt, "+GetAddress_FormToNPC(NPChar)+"Dis-moi, as-tu des informations supplémentaires ? Comme le nom du capitaine, le nom ou le type de son navire ?";
		    link.l1.go = "CustomPatrol_agree";
			link.l2 = "Hmm... Non, je crois que je vais passer.";
		    link.l2.go = "All_disagree";
		break;
		
		case "CustomPatrol_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.CustomPatrol.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Ma source vient de me dire qu'une transaction est en cours de préparation et sera bientôt conclue. C'est tout. Alors, gardez un œil vigilant sur tous les navires suspects dans nos eaux. Si vous réussissez, je vous paierai une somme de "+FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money))+"\nDe plus, compte tenu des circonstances, je vous autorise à récupérer toute la cargaison de contrebande, que vous pourrez trouver. Officieusement, bien sûr, à condition que vous ne la vendiez pas dans notre ville.";
			link.l1 = "Assez généreux. Très bien, je vais commencer à patrouiller les eaux de votre colonie, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 6, false);
			pchar.quest.CustomPatrol.win_condition.l1 = "location";
			pchar.quest.CustomPatrol.win_condition.l1.location = pchar.GenQuest.CustomPatrol.Island;
			pchar.quest.CustomPatrol.win_condition.l2 = "Timer";
			pchar.quest.CustomPatrol.win_condition.l2.date.hour  = sti(GetTime()+rand(8));
			pchar.quest.CustomPatrol.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.function = "CustomPatrol_CreateShip";
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "11");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)));
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Найти дезертира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "FindFugitive":
			//установка параметров
			pchar.GenQuest.questName = "FindFugitive"; //тип квеста
			pchar.GenQuest.FindFugitive.Startcity = npchar.city;
			pchar.GenQuest.FindFugitive.City = SelectFugitiveCity();
			pchar.GenQuest.FindFugitive.Chance = rand(2);
			pchar.GenQuest.FindFugitive.Name = GenerateRandomName(sti(npchar.Nation), "man");
			pchar.GenQuest.FindFugitive.Money = ((hrand(5)+hrand(6)+4)*2600)+(sti(pchar.rank)*600);
			sText = SelectFugitiveText();
			log_testinfo(pchar.GenQuest.FindFugitive.City);
			log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
			dialog.text = "Je vais tout vous raconter en détail. Une histoire très laide s'est produite - "+sText+"En interrogeant ses collègues et amis, nous croyons, non sans raison, que le déserteur s'est réfugié parmi les pirates dans l'un de leurs repaires\nJe vous suggère de visiter le nid des pirates, de trouver le fugitif, de l'arrêter et de le livrer ici. La désertion est une infraction grave, et ne peut rester impunie. Êtes-vous prêt à accepter cette mission ?";
			link.l1 = "Je suis prêt, "+GetAddress_FormToNPC(NPChar)+"Pouvez-vous me dire le nom du déserteur ?";
		    link.l1.go = "FindFugitive_agree";
			link.l2 = "Hmm... Non, je pense que je vais passer.";
		    link.l2.go = "All_disagree";
		break;
		
		case "FindFugitive_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.FindFugitive.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Oui, bien sûr. Son nom est "+pchar.GenQuest.FindFugitive.Name+". Je doute fort qu'il porte son uniforme, alors examinez de plus près toutes sortes de canailles. Je vous donne un mois pour la recherche, car, j'ai bien peur, il ne servirait à rien de le chercher après cela. Si vous réussissez, je vous paierai une somme de "+FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money))+".";
			link.l1 = "Je ne perdrai pas plus de temps, "+GetAddress_FormToNPC(NPChar)+" ! Je mettrai les voiles immédiatement.";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 30, false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.FindFugitive.Name);
			//создаем дезертира
			sld = GetCharacter(NPC_GenerateCharacter("Fugitive", "citiz_"+(21+rand(9)), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, sti(npchar.nation), 30, true, "soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			sld.name = pchar.GenQuest.FindFugitive.Name;
			sld.lastname = "";
			sld.dialog.FileName = "MayorQuests_dialog.c";
			sld.greeting = "marginal";
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Проникновение во враждебный город
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			dialog.text = "Je vois. Peut-être, une récompense de "+FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money))+" sera une bonne incitation pour vous.";
			link.l1 = "Oui, c'est une somme correcte... J'accepte cette mission.";
		    link.l1.go = "Intelligence_agree";
			link.l2 = "Hmm... Non, je pense que je vais refuser. C'est trop dangereux.";
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //на всякий случай
			{
				dialog.text = "Bien que je ne puisse pas dire que je vous fais entièrement confiance... Je pense que je ne vais pas vous confier cette mission.";
				link.l1 = "Eh bien... C'est dommage, mais je n'y peux rien.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //тип квеста
				sTemp = pchar.GenQuest.Intelligence.City;
				switch (rand(4))
				{
					case 0:	sTemp += "_Priest";		break;
					case 1:	sTemp += "_trader";		break;
					case 2:	sTemp += "_shipyarder"; break;
					case 3:	sTemp += "_usurer";	    break;
					case 4:	sTemp += "_PortMan";	break;
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //Id нашего шпиона в городе
				dialog.text = "Superbe ! Passons maintenant aux affaires. Dans "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" tu dois trouver un local "+GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)],"Gen")+", son nom est "+GetFullName(&characters[GetCharacterIndex(sTemp)])+" . Vous lui direz mon nom et il vous remettra un paquet de documents. Pour avoir livré ce paquet entre mes mains, je vous accorde "+FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms))+"Et n'oubliez pas que tout doit être fait secrètement. Si votre couverture est compromise, l'agent ne prendra pas le risque de tenter le contact. Est-ce clair ?";
				link.l1 = "Oui, je l'ai, "+GetAddress_FormToNPC(NPChar)+"Je commencerai immédiatement.";
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получения квеста
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat"));
				AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
				AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));			
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
				AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			}
		break;
		case "Intelligence_ExecuteLate":
			QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / 2);
			dialog.text = RandPhraseSimple("Pas mal. Mais tu n'as pas respecté le délai, et donc je dois réduire un peu ta récompense. Désormais, ta paie sera "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+"  Voilà.","C'est bien. Mais vous n'avez pas respecté le délai, et j'ai attendu ces lettres. Vous avez gâché mes plans, et par conséquent, je suis contraint de réduire un peu votre récompense. Néanmoins, je suis heureux de vous remettre votre dû - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+"Voilà.");
			link.l1 = "Je ne dirais pas que cela me plaît, mais en fin de compte, les délais ont effectivement été violés. Donc je n'ai aucune plainte, "+GetAddress_FormToNPC(NPChar)+".";
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(RandPhraseSimple("You know, governor " + GetFullName(npchar) + " are not very pleased with the quickness of a captain " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is not very pleased with captain " + GetMainCharacterNameDat() + ", "+ GetSexPhrase("who","who") +" complied with his orders, but did not in due time..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		
		// -------------- общий набор для всех квестов мэра ------------------
		case "All_disagree":
			dialog.text = "Tu me déçois !";
			link.l1 = "Je suis désolé, "+GetAddress_FormToNPC(NPChar)+", mais je ne peux pas accepter ce travail.";
		    link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Eh bien, très mauvais - que puis-je dire d'autre. Je comptais sur vous - et il s'avère que j'ai simplement perdu mon temps. Je suis déçu.","Eh bien, je dois dire que je suis totalement déçu de vous... Il y a beaucoup de gens dans ma résidence toujours prêts à accomplir de telles tâches pour moi - et j'ai perdu mon temps avec vous. Oh là là...");
			link.l1 = "Je suis désolé, "+GetAddress_FormToNPC(NPChar)+"J'ai fait tout ce que je pouvais.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Just imagine - he failed to fulfill his assignment in time!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " put his shoulder to the wheel, but fail to fulfill his assignment in time. That's too bad...", 
				"I heard that governor " + GetFullName(npchar) + " is very displeased with you, captain " + GetFullName(pchar) + ", since you failed to meet the deadline while trying to fulfill his assignment."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Je suis tout simplement choqué ! Vous avez réussi à localiser votre cible mais vous ne vous êtes guère soucié des moyens d'assurer votre supériorité - c'est une imprudence extrême. Je suis déçu !","Eh bien, je dois dire que je suis déçu de vous... Trouver votre cible ne suffit pas - vous devez avoir les moyens de la détruire. Il y a beaucoup de coupe-jarrets à ma résidence toujours prêts à exécuter de telles courses pour moi. Que pensais-je donc en me tournant vers vous ?");
			link.l1 = "Je suis désolé, "+GetAddress_FormToNPC(NPChar)+", mais je ne suis tout simplement pas prêt à risquer imprudemment ma propre vie.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Imagine, "+ GetSexPhrase("he turned out to be a downright coward","she turned out to be a downright coward") +"!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " took the job, but failed to carry it out because of their own indecision. Hee-hee, what wilt captains!", 
				"I heard that Governor " + GetFullName(npchar) + " very displeased with you, Captain " + GetFullName(pchar) + ". They say you're nothing but a coward"+ GetSexPhrase("","") +"..."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Excellente nouvelle ! Eh bien, il est temps de faire le bilan. Votre rémunération sera "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+"  Voici pour vous. ","Excellent ! Cette voie est la meilleure pour tout le monde... Eh bien, je suis heureux de vous remettre votre récompense due - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+"Voilà, pour vous.");
			link.l1 = "Merci, "+GetAddress_FormToNPC(NPChar)+", "+RandPhraseSimple("C'est un plaisir de faire affaire avec vous !","Je suis agréablement surpris par la clarté des colonies.");
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + "  was praising for diligence"+ GetSexPhrase("a captain","a young lady") +" " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is praising captain " + GetMainCharacterNameGen() + ", "+ GetSexPhrase("he","she") +" is always a flawless performer when it comes to governor's assignments. An irreplaceable person for the governor, I say...", 
				"I heard that governor " + GetFullName(npchar) + " is very much pleased with you, captain " + GetFullName(pchar) + ". He defines you as a very careful and thorough officer. That's very nice to hear, captain..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Très bien. Vous pouvez revenir me voir - peut-être que je trouverai un autre travail pour vous.","Eh bien, formidable ! Je suppose que je vous proposerai à nouveau de tels travaux.");
			link.l1 = RandPhraseSimple("Génial.","D'accord.");
		    link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(PChar, "Leadership", 180);
			OfficersReaction("good"); // dlc
			
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			// инкремент в базу заданий мэров
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<-- осады homo
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = "En ces temps difficiles, toute aide serait la bienvenue. Nous acceptons votre aide - aidez-nous à défendre notre colonie, et vous serez récompensé.";
			link.l1 = "Alors ne perdons pas de temps.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> Бремя гасконца
		case "Sharlie":
			dialog.text = "Vous cherchez Michel de Monper ? Intéressant... Et pourquoi avez-vous besoin de lui ?";
			link.l1 = "Je suis son frère. Mon père m'a dit que Michel est en difficulté et a besoin d'aide, alors je...";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
			DelLandQuestMark(sld);
			dialog.text = "Êtes-vous? Je ne me souviens pas que Monsieur de Monper ait des frères... Vous savez, monsieur, vous me paraissez très suspect... donc je vous arrête pour une enquête plus approfondie. Lieutenant ! Arrêtez cet homme !";
			link.l1 = "Mais Votre Seigneurie !";
			link.l1.go = "exit";
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}	
			AddDialogExitQuestFunction("Sharlie_enterSoldiers");
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Sharlie_2":
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload3_back");
			dialog.text = "Et pourtant, je voudrais me racheter. Tenez - veuillez accepter cette épée, ce pistolet et cette armure légère - c'est mon cadeau pour vous. Je crois que vous trouverez ces objets fort utiles.";
			link.l1 = "Merci, monsieur. Étant donné que vos gardes ont pris tout ce que je possède, cela sera très utile.";
			// belamour legendary edition -->
			link.l1.go = "Sharlie_5";		
			link.l2 = "Je vous remercie, monsieur. Y a-t-il une autre manière dont vous pourriez m'aider ? D'homme à homme ? Vous pouvez voir par vous-même dans quelle situation terrible je me trouve !";
			link.l2.go = "Sharlie_3";	
		break;
		
		case "Sharlie_3":
			dialog.text = "Eh bien, Charles... (fouillant dans le bureau) Tiens, garde cet amulette sacrée pour la bonne fortune. Je ne peux plus t'aider, désolé. Ici, dans les colonies, tu devras compter uniquement sur toi-même.";
			link.l1 = "Eh bien, c'est déjà ça. Merci pour le cadeau, monsieur.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Commerce", 10);
			Log_Info("You'have received equipment");
			Log_Info("You have received the 'Holy Water' amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Sharlie_5":
			// <-- legendary edition
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 10);
			Log_Info("You'have received equipment");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		//<-- Бремя гасконца
		
		//Sinistra --> Травля крысы		
		case "TK_TravlyaKrys":
			dialog.text = "Quelle ironie du sort, Charles... Ce n'est pas souvent que nous voyons quelqu'un s'élever si rapidement dans notre monde. J'ai le sentiment que vous et moi nous entendrons très bien.";
			link.l1 = "Je serais honoré. Peut-être avez-vous une tâche pour moi ?";
			link.l1.go = "TK_TravlyaKrys_2";
			DeleteAttribute(pchar, "questTemp.TK_TravlyaKrys");
			PChar.quest.TK_Timer.over = "yes";
		break;
		
		case "TK_TravlyaKrys_2":
			dialog.text = "Absolument ! Surtout après votre engagement victorieux avec l'un des pirates de Barbazon près de Le Francois...";
			link.l1 = "Je ne peux pas dire que j'ai de bons souvenirs de cette rencontre. Qui est exactement Barbazon ?";
			link.l1.go = "TK_TravlyaKrys_3";
		break;
		
		case "TK_TravlyaKrys_3":
			dialog.text = "Jacques Barbazon, également connu sous le nom de Jacques le Bonhomme, dirige le nid de bandits à Le Françcois. C'est l'un des soi-disant barons pirates, semant le trouble avec la piraterie et la contrebande dans les Petites Antilles. C'est un criminel notoire, et croyez-moi, il finira un jour sur la potence à St. Pierre !";
			link.l1 = "Excusez-moi, mais n'êtes-vous pas la véritable autorité en Martinique ? Ne pouvez-vous pas simplement éliminer ce nid ? J'y suis allé, et croyez-moi, ce n'est pas grand-chose à voir.";
			link.l1.go = "TK_TravlyaKrys_4";
		break;
		
		case "TK_TravlyaKrys_4":
			dialog.text = "Je te conseillerais de ne pas te vanter de ta connaissance des endroits peu recommandables de mon île, Charles. Ce n'est pas digne d'un noble. Quant à ta question\nTout dans notre monde ne peut être résolu par la force brute. Il y a des intérêts politiques et commerciaux en jeu. Mais ne nous attardons pas sur des détails inutiles : j'ai une tâche spécifique qui nécessite un peu de force brute.";
			link.l1 = "Je vous en prie, continuez.";
			link.l1.go = "TK_TravlyaKrys_5";
		break;
		
		case "TK_TravlyaKrys_5":
			dialog.text = "Barbazon attire des équipages de petites frappes, avides d'or facile. Parfois, il leur jette un os juste pour les voir se battre pour celui-ci. De temps en temps, il met le survivant au travail, mais le plus souvent, il les rejette, et croyez-moi, il n'y a rien de plus dangereux qu'un pirate désespéré errant dans les parages.";
			link.l1 = "Je pense comprendre, mais je ne suis pas sûr d'être prêt pour cela. Je viens tout juste de prendre le commandement de mon navire, et j'apprends encore les ficelles du métier, pour ainsi dire...";
			link.l1.go = "TK_TravlyaKrys_6";
		break;
		
		case "TK_TravlyaKrys_6":
			dialog.text = "Balivernes ! Vous avez déjà goûté à la victoire - plus que la plupart des fainéants parmi mes officiers ! La ville vous récompensera avec cinq mille pesos pour avoir coulé un autre des rats de Barbazon, sans impôts. Huit mille si vous ramenez le pirate vivant - pour une exécution en bonne et due forme, bien sûr.";
			link.l1 = "Je pourrais certainement utiliser cet argent. Où puis-je trouver ce pirate ?";
			link.l1.go = "TK_TravlyaKrys_7";
			link.l2 = "Je suis désolé, mais je ne pense pas être prêt pour ce genre de tâche pour l'instant.";
			link.l2.go = "TK_TravlyaKrys_Otkaz";
		break;
		
		case "TK_TravlyaKrys_Otkaz":
			dialog.text = "C'est bien dommage, Charles. Dans ce cas, je ne te retiendrai pas plus longtemps.";
			link.l1 = "Adieu, Votre Excellence.";
			link.l1.go = "exit";
		break;
		
		case "TK_TravlyaKrys_7":
			dialog.text = "Je suis heureux que tu sois à bord, Charles. Nos rapports de renseignements indiquent que le Hater, une chaloupe, se prépare actuellement à partir de Le François. Nous ne pouvons pas nous permettre de retarder, alors mettez les voiles et engagez. Ne t'inquiète pas, mon ami, tu réussiras.";
			link.l1 = "Avec la grâce de Dieu, Votre Excellence.";
			link.l1.go = "TK_TravlyaKrys_8";			
		break;
		
		case "TK_TravlyaKrys_8":
			DialogExit();
			SetQuestHeader("TravlyaKrys");
			AddQuestRecord("TravlyaKrys", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, true, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			FantomMakeSmallSailor(sld, SHIP_LUGGER, "Hater", CANNON_TYPE_CANNON_LBS3, 20, 40, 20, 25, 35);
			SetCharacterGoods(sld, GOOD_GOLD, 1);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("HeiterAttack");
			Group_SetType("HeiterAttack", "pirate");
			Group_AddCharacter("HeiterAttack", "TK_Heiter");

			Group_SetGroupCommander("HeiterAttack", "TK_Heiter");
			Group_SetTaskAttack("HeiterAttack", PLAYER_GROUP);
			Group_SetAddress("HeiterAttack", "Martinique", "Quest_Ships", "Quest_Ship_6");
			Group_LockTask("HeiterAttack");
			
			PChar.quest.TK_Potopil.win_condition.l1 = "Character_sink";
			PChar.quest.TK_Potopil.win_condition.l1.character = "TK_Heiter";
			PChar.quest.TK_Potopil.win_condition = "TK_Potopil";
		break;
		//<-- Травля крысы
		
		//Jason --> Португалец
		case "Portugal":
			dialog.text = "Bien sûr que vous pouvez, capitaine ! C'est pour cela que je vous ai dérangé.";
			link.l1 = "Je suis tout ouïe.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Des pêcheurs locaux ont aperçu un étrange navire près de l'île la nuit dernière. Selon eux, c'était un énorme vaisseau de guerre, comme un vaisseau de ligne, sans aucun drapeau ni lanterne de signalisation. Je ne pense pas que ce navire puisse réellement être plus grand qu'une frégate, mais même cela serait déjà trop!";
			link.l1 = "La peur transforme les taupinières en montagnes, c'est certain... mais à quoi bon ?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Je m'adresse à vous, capitaine. Mes partenaires commerciaux sont effrayés par ces rumeurs - ils pensent qu'il s'agit de pirates ou de corsaires espagnols, et cela nuit au commerce. Pire que tout - il n'y a actuellement pas de navires de guerre dans la colonie, seulement quelques sloops pour la protection et une vieille goélette, adaptée à la chasse aux contrebandiers\nJe ne peux pas laisser cela sans surveillance... Quoi qu'il en soit, maintenant que la rumeur sur le navire mystérieux est connue de la moitié de la ville ! S'il vous plaît, rejoignez-nous avec votre navire pour nous aider à le trouver - je vous connais comme un capitaine respectable, et même s'il s'agit vraiment d'une simple frégate, vos canons peuvent la convaincre de chercher une proie ailleurs !";
			link.l1 = "Monsieur... En fait, j'avais d'autres plans...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "S'il vous plaît, capitaine ! Juste pour quelques jours, jusqu'à ce que ces rumeurs troublantes se calment ! Et vous serez payé pour votre temps, bien sûr. Dix mille pièces de huit vous conviendraient-elles ?";
			link.l1 = "Hmm... mais, votre Excellence, je...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "Et nous doublerons la récompense si vous engagez le combat avec ce navire, et la triplerons si vous le coulez ! Alors, qu'en dites-vous ?";
			link.l1 = "D'accord, je comptais de toute façon rester ici quelques jours.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Excellent, je n'ai jamais vraiment douté de vous, monsieur capitaine ! N'oubliez pas - juste deux jours dans nos eaux - et l'argent est à vous. Et si vous êtes forcé d'entrer en bataille, vous serez payé en fonction du résultat.";
			link.l1 = "Je l'ai compris, Votre Excellence. Nous avons un accord, et je retourne à mon navire maintenant.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Je vous attendrai à votre retour, capitaine !";
			link.l1 = "Permettez-moi de prendre congé.";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			DialogExit();
			AddQuestRecord("Portugal", "10");
			NextDiag.CurrentNode = "Portugal_8";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", false);//открыть выходы из города
			bDisableFastReload = true;//закрыть быстрый переход
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.Portugal_Seapatrol.win_condition.l1 = "location";
			pchar.quest.Portugal_Seapatrol.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_Seapatrol.function = "PortugalSeapatrolGo";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1 = "location";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Portugal_SeapatrolAvendel.function = "AvendelSpeach";
		break;
		
		case "Portugal_8":
			dialog.text = "Capitaine, je crois que nous avions un accord pour que vous patrouilliez nos eaux côtières pendant deux jours !";
			link.l1 = "Oui, bien sûr. Je me souviens de cela.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Portugal_8";
		break;
		
		case "Portugal_9":
			dialog.text = "Eh bien, vous avez tenu votre part du marché. Voici votre récompense - 10 000 pesos, comme convenu.";
			link.l1 = "Merci ! Comme vous pouvez le voir, vos appréhensions étaient sans raison. Bonne chance à vous !";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			DialogExit();
			AddMoneyToCharacter(pchar, 10000);
			NextDiag.CurrentNode = "First time";
			pchar.quest.MartiniqueGovernorOver.over = "yes"; //снять таймер
		break;
		//<-- Португалец
		
		// Warship, 16.05.11. Генер "Правосудие на продажу".
		case "JusticeOnSale_1":
			dialog.text = "Oh "+GetAddress_Form(NPChar)+", vous m'avez surpris ! Ces vauriens sont-ils vraiment devenus si impudents ? Je dois en informer le commandant immédiatement et envoyer une patrouille côtière là-bas !";
			link.l1 = "J'étais heureux d'aider. Puis-je prendre congé maintenant ?";
			link.l1.go = "JusticeOnSale_2";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
			
			DeleteQuestCondition("JusticeOnSale_MapEnter");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Bien sûr, capitaine. Tenez - s'il vous plaît, acceptez cette modeste récompense personnellement de ma part.";
			link.l1 = "Merci.";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_3":
			AddQuestRecord("JusticeOnSale", "5");
			CloseQuestHeader("JusticeOnSale");
			
			AddMoneyToCharacter(PChar, 1000 + sti(PChar.rank) * 30 * hrand(10));
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			
			DialogExit();
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Vous avez raison, capitaine ! Nous ne pouvons pas laisser cela ainsi ! Je vous demanderais de vous rendre à "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Ce")+", trouvez leur navire et mettez toute leur bande en état d'arrestation ! S'ils résistent - usez de la force et n'hésitez pas !";
			link.l1 = "Permettez-moi de prendre congé.";
			link.l1.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Maintenant, va. Navigue là-bas et assure-toi que personne n'échappera à la justice. Je pense que d'abord tu devras débarquer sur la côte, puis tu pourras t'occuper du navire.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_6";
		break;
		
		case "JusticeOnSale_6":
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShipPirate", "", "man", "man", sti(PChar.rank) + 5, PIRATE, -1, true, "quest"));
			sld.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.JusticeOnSale.ShipType), true, sld);
			sld.Ship.Name = PChar.GenQuest.JusticeOnSale.ShipName;
			SetBaseShipData(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetCannons(sld, "pirate");
			Fantom_SetBalls(sld, "pirate");
			Fantom_SetUpgrade(sld, "pirate");
			SetCaptanModelByEncType(sld, "pirate");
			SetRandGeraldSail(sld, PIRATE);
			
			Character_SetAbordageEnable(sld, false);
			
			Group_FindOrCreateGroup("JusticeOnSaleGroup");
			Group_AddCharacter("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetGroupCommander("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetAddress("JusticeOnSaleGroup", PChar.curislandid, "reload", Island_GetLocationReloadLocator(PChar.curislandid, PChar.GenQuest.JusticeOnSale.ShoreId));
			Group_SetTaskNone("JusticeOnSaleGroup");
			Group_LockTask("JusticeOnSaleGroup");
			
			sld.AlwaysFriend = true;
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
			
			SetCharacterShipLocation(sld, PChar.GenQuest.JusticeOnSale.ShoreId);

			DeleteAttribute(sld, "SinkTenPercent");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			DeleteAttribute(sld, "AboardToFinalDeck");
			
			sld.AlwaysSandbankManeuver = true;
			sld.AnalizeShips = true;
			sld.DontRansackCaptain = true;
			
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.function = "JusticeOnSale_ShoreEnterFromMayor";
			
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1 = "Character_sink";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1.character = "JusticeOnSale_ShipPirate";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.function = "JusticeOnSale_PirateShip_Sink";
			
			DialogExit();
		break;
		
		case "JusticeOnSale_7":
			dialog.text = "Merci pour votre aide. Ces vauriens ont eu ce qu'ils méritaient. Permettez-moi de vous offrir cette modeste récompense de ma part. J'apprécie grandement l'ordre et la paix dans ma ville.";
			link.l1 = "... ";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + hrand(1000));
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			DialogExit();
		break;
		//<-- Правосудие на продажу
		
			//--> Jason регата
		case "Regata":
			// belamour legendary edition -->
			if(sti(pchar.rank) < 20)
			{
				notification("Level 20 required", "None");
				dialog.text = "Ah, merveilleux, heureux de vous voir, capitaine ! J'ai entendu parler de vos talents, mais venez quand vous serez vraiment prêt.";
				link.l1 = "Oui, bien sûr. Comme vous le souhaitez.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Oh, formidable, heureux de vous voir, capitaine ! Vous arrivez juste à temps - la régate va commencer dans quelques jours. Avez-vous lu les règles de la régate, qui ont dû vous être remises par un officier ?";
				link.l1 = "Oui, monsieur, je l'ai fait.";
				link.l1.go = "Regata_1";
				RemoveItems(PChar, "letter_open", 1);//уберем письмо
				DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
			}
		break;
		
		case "Regata_1":
			dialog.text = "Et avez-vous préparé 50000 pesos - votre droit d'entrée, qui contribuera à la cagnotte ?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Oui, bien sûr. Veuillez accepter mon honoraire.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "Je manque un peu d'argent en ce moment. Mais je vais certainement réunir la somme requise.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Très bien. Si vous gagnez - vous récupérerez votre argent quintuple. Maintenant, vous devez mieux vous familiariser avec les règles de la régate\nTous les détails vous pouvez les apprendre de Sir Henry Stivenson, il devrait être dans une chambre de la résidence. Allez le voir - il vous expliquera tout.";
			link.l1 = "D'accord. Je ferai exactement cela.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Très bien, mais s'il vous plaît, ne tardez pas trop, capitaine. La régate commence très bientôt.";
			link.l1 = "Je vois. J'essaierai de vous apporter l'argent dès que possible.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "Aha! Et voici le vainqueur de la régate! Bonne journée Capitaine "+GetFullName(pchar)+"Permettez-moi de vous féliciter pour ce succès bien mérité ! Les vainqueurs de la régate ont toujours été populaires dans les colonies anglaises - et à juste titre.";
			link.l1 = "Merci, monsieur !";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Passons maintenant à la partie la plus agréable - la cérémonie de récompense. Le premier prix est de 250 000 pesos. Félicitations !";
			link.l1 = "Merci !";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			// belamour legendary edition в регате только один приз -->
			GiveItem2Character(pchar, "blade_26");
			GiveItem2Character(pchar, "cirass4");
			GiveItem2Character(pchar, "bussol");
			
			dialog.text = "Ainsi, vous recevrez un ensemble de prix précieux : la légendaire rapière en acier de Tolède 'Asoleda', une armure milanaise et une belle boussole. Tout est à vous.";
			// <-- legendary edition
			link.l1 = "Je suis très heureux, monsieur. Vraiment, je n'aurais pu espérer une telle largesse.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "Au nom de tous les sujets des colonies anglaises, je vous remercie pour votre participation à la régate et vous félicite encore une fois pour votre victoire ! Si vous avez parié, allez voir Sir Henry Stevenson et récupérez vos gains si vous ne l'avez pas encore fait. Bonne chance à vous, capitaine !";
			link.l1 = "Merci pour vos aimables paroles, monsieur ! À mon tour, permettez-moi de vous remercier de m'avoir offert l'opportunité de participer à un événement si grandiose. Maintenant, veuillez me permettre de prendre congé.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}

string GetGangLocation(ref npchar)
{
    int n;
	string island = GetArealByCityName(npchar.city);
	string LocationId, sAreal;
	int storeArray[2];
	SetArraySize(&storeArray, MAX_LOCATIONS);  
    int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if (GiveArealByLocation(&locations[n]) == island)
		{			
			//==> на всякий случай
			if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if (findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[hrand(howStore-1)];
	return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //если взят квест по доставке малявы
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GetSpyColony(ref NPChar)
{
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		// Rebbebion, чуть изменил функцию, чтобы условно испанцы не просили пробраться к испанцам, французы к французам и т.д
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].id != npchar.City && colonies[n].nation != npchar.nation)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[Rand(howStore-1)]].id;
}

int SelectCureerShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL + FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
}

int SelectCustomPatrolShipType(int iFlagType)
{
	if(CheckAttribute(pchar, "questTemp.StatusCity"))
	{
		return SHIP_CAREERLUGGER;
	}
	
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

int SelectArsenalShipType(int iFlagType)
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

string SelectPassText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "That Judas, using his position, sold an important state secret to an enemy power."; break;
		case 1: sText = "That foul scoundrel killed his relative, a well-known and noble man, in order to inherit his fortune."; break;
		case 2: sText = "That foul scoundrel insulted my family and me personally."; break;
		case 3: sText = "This thieving rogue stole a decent sum of money from our city's treasury."; break;
		case 4: sText = "That villain is guilty of deaths of nearly a dozen of our citizens."; break;
		case 5: sText = "That rogue used his connection to take possession of a merchant vessel, and then he stole it and sold at the neighboring shipyard."; break;
	}
	return sText;
}

string SelectFugitiveCity()
{
	string sCity;
	switch (rand(3))
	{
		case 0: sCity = "LaVega"; break;
		case 1: sCity = "PuertoPrincipe"; break;
		case 2: sCity = "LeFransua"; break;
		case 3: sCity = "FortOrange"; break;
	}
	return sCity;
}

string SelectFugitiveText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "one of the junior officers in our garrison has deserted and left the colony on board of a merchant ship."; break;
		case 1: sText = "one of our officers deserted right on duty and escaped on board of a smuggler ship."; break;
		case 2: sText = "one of our naval officers serving on a patrol brig deserted for unknown reason, hijacked a long boat and disappeared on it."; break;
		case 3: sText = "one of our prison guards threw up his service for  unknown reason and left our colony aboard a private vessel."; break;
		case 4: sText = "one of the soldiers in our garrison abandoned his post while keeping guard, went to the cove and left this place aboard an unknown vessel."; break;
		case 5: sText = "one of our military officers, captain of a patrol lugger, abandoned his ship in the open sea and went south on a fishing long boat."; break;
	}
	return sText;
}
