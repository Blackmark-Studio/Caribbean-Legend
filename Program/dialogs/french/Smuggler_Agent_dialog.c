void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
    bool bOk2;
    
	int Sum, nRel, nDay, iChurchQuest2_Summ;
	ref sld;
	
	// Церковный квест № 2 -->
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra"))
	{
		iChurchQuest2_Summ = sti(PChar.rank)*100 + (rand(3)+1)*100;
		PChar.GenQuest.ChurchQuest_2.Summ_To_Contra = sti(iChurchQuest2_Summ);
	}
	// <-- Церковный квест № 2
	
	string sColony;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	// belamour legendary edition
	bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
	bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	//тереть нафиг аттрибут при прошествии дней (navy fix)
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Smuggling_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
			Pchar.quest.Contraband.active = true;
			pchar.GenQuest.Contraband.GuardNation = npchar.nation;
			pchar.GenQuest.Contraband.SmugglerId  = npchar.id;				
			SetAllContraGoods(&Stores[sti(Pchar.GenQuest.Contraband.StoreIdx)], npchar);
			ReOpenQuestHeader("Gen_Contraband");
            if (GetIslandByCityName(npchar.city) == "Mein")
            {
            	AddQuestRecord("Gen_Contraband", "t1_1");
            }
            else
            {
	            AddQuestRecord("Gen_Contraband", "t1");
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));
				
			DialogExit();
		break;
		
		case "First time":											
			//--> Jason если идёт первая часть квеста Шарля
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
            {
				dialog.text = "Monsieur, quittez cet endroit. Je doute que nous ayons quoi que ce soit à discuter.";
				link.l1 = "Oh, vraiment? Tu n'aimes pas mon visage? Très bien, je pars...";
				link.l1.go = "exit";
				break;
			}
			//<-- идёт первая часть квеста Шарля
			//--> Addon-2016 Jason блокировка контры во избежание конфликтов с квестами
			if (CheckAttribute(pchar, "GenQuest.SmugglersBlock") && pchar.GenQuest.SmugglersBlock == npchar.location)
            {
				dialog.text = "Pas d'affaires aujourd'hui.";
				link.l1 = "Je vois.";
				link.l1.go = "exit";
				break;
			}
			//--> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "Mes amis et moi sommes extrêmement occupés aujourd'hui.";
				link.l1 = "Mais j'ai besoin...";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<-- прибыла инспекция на Святом Милосердии
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.Consumption.Contra"))
            {
				dialog.text = "Que voulez-vous, capitaine?";
				link.l1 = "Pouvons-nous parler un peu?";
				link.l1.go = "Consumption";
				break;
			}
			//<-- Цена чахотки
			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Qu'est-ce que tu veux, capitaine? Je ne connais pas ton nom et je ne peux pas te dire le mien.";
				Link.l1 = "Je suis le capitaine "+GetFullName(pchar)+".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1"; 
			}
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 1)
				{
					if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
					{
						pchar.GenQuest.CaptainComission.SpeakContra = true;
						dialog.text = "Aucune affaire aujourd'hui. Il y a des patrouilles à chaque baie, notre gouverneur cherche une cargaison qui a été confisquée par un certain capitaine de"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" et il l'a caché quelque part.";
						link.l1 = "Et où est ce capitaine"+pchar.GenQuest.CaptainComission.Name+"?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "Aucune affaire aujourd'hui.";
						link.l1 = "Je vois.";
						link.l1.go = "exit";					
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "Aucun affaire aujourd'hui.";
					link.l1 = "Je vois.";
					link.l1.go = "exit";
					break;
				}
				
				if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
				{
					dialog.text = "Pas de commerce aujourd'hui.";
					link.l1 = "Je vois.";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "Que voulez-vous, capitaine?";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("Soyez rapide, "+GetSexPhrase("copain","fille")+", que voulez-vous? Ils te poursuivent!","Parlez de votre affaire et faites-le rapidement! Les soldats vous poursuivent et nous n'avons pas beaucoup de temps...");
				}
				// belamour legendary edition
				bOk2 = MCGovernon || MCAdmiral;
				if(FindContrabandGoods(PChar) != -1 && !bOk2)
				{
					Link.l1 = "Je voudrais acheter ou vendre quelque chose.";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "A propos du voyage...";
				else
					Link.l2 = "J'ai besoin d'aller à un endroit.";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "J'ai quelque chose de 'spécial' et je pense que cela pourrait t'intéresser. Jette un oeil !";
						link.l3.go = "SM_ShipLetters_1";
					}	
				}				

				//Jason --> мини-квест Бесчестный конкурент
				if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
				{
					Link.l8 = "J'ai une affaire inhabituelle pour toi.";
					Link.l8.go = "Shadowtrader_smugglers";
				}
				// <-- мини-квест Бесчестный конкурент
				
				//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "Écoute, mon ami, j’ai besoin d’un lot de vin et de rhum. Du gros, et vite.";
					Link.l8.go = "TPZ_smugglers_1";
				}
				// <-- Торговля по закону

				//Jason --> генератор сбыта бакаута
				if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
				{
					Link.l9 = "J'ai besoin de rencontrer Michael Rosenkraft. J'ai la cargaison qui sera intéressante pour lui.";
					Link.l9.go = "bakaut";
				}
				// <-- генератор сбыта бакаута
				
				// Церковный генератор №2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "J'ai besoin de découvrir quelque chose, mon pote.";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "Un collègue à vous et mon bon ami de  "+XI_ConvertString("Colonie"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gén")+" a dit que vous êtes au courant de certaines affaires.";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- Церковный генератор №2
				
				Link.l7 = "Rien. Au revoir.";
				Link.l7.go = "Exit";				
			}
		break;
		
		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "Dans le sous-sol du fort, où d'autre? Ce capitaine peut révéler la cachette aux autorités à tout moment et il ne nous restera rien. Ne pensez à aucune affaire tant que cette agitation n'est pas terminée.";
				link.l1 = "Écoute, tu connais chaque parcelle de cette île. Tu n'as vraiment aucune idée de où se trouve le capitaine "+pchar.GenQuest.CaptainComission.Name+"le dépôt est ?";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "Au paradis, je suppose. Il a été pendu avec son équipage. Mais ils n'ont pas mentionné dans la sentence de mort que c'était un bateau pirate.";
				link.l1 = "Et pourquoi êtes-vous si sûr que le navire était un pirate ?";
				link.l1.go = "CapComission_2";
			}	
		break;
		
		case "CapComission_2":
			dialog.text = "Nous avions regardé le combat depuis le rocher. Dans une longue-vue, nous avons vu le navire sous le Jolly Roger. Puis, comme cinq heures plus tard, nous avons vu un éclair dans l'obscurité, cela ressemblait à un coup de la salle de poudre. Assez de temps pour déplacer la cargaison vers le rivage.";
			link.l1 = "Ne savez-vous pas où est le capitaine "+pchar.GenQuest.CaptainComission.Name+"'s cache? Tu connais chaque coin de cette île.";
			link.l1.go = "CapComission_3";
		break;
		
		case "CapComission_3":
			dialog.text = "Non. Et nous le cherchons aussi, mais pas pour l'amusement du gouverneur...";
			link.l1 = "Je vois.... Passez une bonne journée.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
		break;
		
		case "CapComission_4":
			dialog.text = "Non. Et nous le cherchons aussi mais pas pour l'amusement du gouverneur... he-he";
			link.l1 = "Je vois... Passez une bonne journée.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;
				
		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Pourquoi avez-vous décidé ainsi? Je suis un caboteur honnête. Allez chercher un autre acheteur.";
				link.l1 = "Merci...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Pourquoi pas? Peut-être que je trouverai une utilité pour ton 'chargement'. Prends "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" pièces et oubliez ça.";
					link.l1 = "Non, merci.";
					link.l1.go = "SM_ShipLetters_2";	
					link.l2 = "Et tu as deviné correctement, je commence à oublier ça !";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Exactement! Je suis vraiment curieux maintenant. Je suppose que si je te paye "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" pièces et tu n'en auras rien à faire de ces documents.";
						link.l1 = "Non, merci.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Et vous avez raison. Je les ai déjà oubliés.";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Maintenant, c'est une chance de attraper ce insolent! Je suis vraiment, vraiment curieux. Ecoute, je te paierai "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" en or et tu oublieras complètement les documents sur la table ?";
						link.l1 = "Je ne le ferai pas.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "D'accord, marché conclu !";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;
		
		case "SM_ShipLetters_2":
			dialog.text = "D'accord, d'accord, mais arrête de te faire plus d'ennemis.";
			link.l1 = "Pareillement !";
			link.l1.go = "exit";
		break;
		
		case "SM_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "7");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Meeting":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 2)
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
				{
					pchar.GenQuest.CaptainComission.SpeakContra = true;
					dialog.text = "Aucune affaire aujourd'hui. Il y a des patrouilles à chaque baie, notre gouverneur recherche une cargaison qui a été confisquée par un certain capitaine de"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" et il l'a caché quelque part.";
					link.l1 = "Et où est ce capitaine"+pchar.GenQuest.CaptainComission.Name+"?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "Aucune affaire aujourd'hui.";
					link.l1 = "Je vois.";
					link.l1.go = "exit";					
					break;
				}
			}
			
			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "Aucun commerce aujourd'hui.";
				link.l1 = "Je vois.";
				link.l1.go = "exit";
				break;
			}
			
			if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
			{
				dialog.text = "Pas d'affaires aujourd'hui.";
				link.l1 = "Je vois.";
				link.l1.go = "exit";
				break;
			}
			
			Dialog.Text = "Comment puis-je vous aider, capitaine?";
			
			bOk2 = MCGovernon || MCAdmiral;
			if(FindContrabandGoods(PChar) != -1 && !bOk2)
			{
				Link.l1 = "Je veux acheter ou vendre des trucs.";
				Link.l1.go = "Meeting_1";
			}
			
			Link.l2 = "J'ai besoin d'aller à un endroit.";
			Link.l2.go = "Travel";				
			
			//Jason --> мини-квест Бесчестный конкурент
			if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
			{
				Link.l8 = "J'ai une affaire assez inhabituelle pour vous.";
				Link.l8.go = "Shadowtrader_smugglers";
			}
			// <-- мини-квест Бесчестный конкурент
			
			//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "Écoute, mon ami, j’ai besoin d’un lot de vin et de rhum. Du gros, et vite.";
					Link.l8.go = "TPZ_smugglers_1";
				}
			
			// <-- Торговля по закону
			//Jason --> генератор сбыта бакаута
			if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
			{
				Link.l9 = "J'ai besoin de rencontrer Michael Rosenkraft. J'ai la cargaison qui sera intéressante pour lui.";
				Link.l9.go = "bakaut";
			}
			// <-- генератор сбыта бакаута
			
			// Церковный генератор №2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "J'ai besoin de découvrir quelque chose, mon pote.";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "Un collègue à vous et mon bon ami de  "+XI_ConvertString("Colonie"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" a dit que vous êtes au courant de certaines affaires.";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			Link.l5 = "Rien. A bientôt.";
			Link.l5.go = "Exit";				
		break;

		// Церковный генератор №2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "Je ne suis pas un ami pour toi. Et cela peut te coûter cher.";
				link.l1 = "Hm. J'ai besoin de savoir quelque chose qui ne coûte pas plus de "+FindRussianMoneyString(iChurchQuest2_Summ)+".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;
			
		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "Donne-moi tes pièces. Et sache que tu n'obtiendras pas grand-chose pour une somme comme celle-ci.";
				link.l1 = "Voyez, j'ai manqué mes amis. J'étais en retard pour une réunion, et ils ne m'ont pas attendu...";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "Ha, tu n'as pas une pièce ! Viens quand tu auras de l'argent.";
				link.l1 = "En effet, je m'en occupe.";
				link.l1.go = "exit";
			}
			break;
			
		case "Contra_GenQuest_Church_2_3":
				dialog.text = "Et pourquoi avez-vous besoin de moi?";
				link.l1 = "Ils ne sont pas en ville et ils n'ont pas de navire. C'est pourquoi je me suis dit: peut-être que certains de vos partenaires commerciaux leur ont rendu service?";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;
			
		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "Je vois... J'ai rencontré quelques gars, ils ont dit qu'ils devaient s'éloigner de l'île et ils se fichaient de savoir où. Nous ne demandons pas les raisons dans un tel cas, seulement le paiement. Nous avions un voyage vers "+XI_ConvertString("Colonie"+sColony+"Acc")+" , "+XI_ConvertString(locations[FindLocation(sColony+"_Ville")].IslandID+"Cela")+" . Nous pouvons vous y emmener, si nous nous entendons sur l'argent.";
			link.l1 = "Merci, mais j'ai mon propre navire.";
			link.l1.go = "exit";
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "8");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + sColony + "Acc"));
			AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Voc"));
			PChar.GenQuest.ChurchQuest_2.AskContra_2 = true;
			PChar.GenQuest.ChurchQuest_2.Contra_Colony = sColony;
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_1":
			dialog.text = "Je n'ai jamais fait affaire avec vous.";
			link.l1 = "Nous pouvons le réparer. Vous avez amené mes amis ici il n'y a pas longtemps. J'ai raté une réunion avec "+GetSexPhrase("eux","eux")+".";
			link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "Hm, nous les avons débarqués à "+XI_ConvertString(sGenLocation+"Gen")+"... Vous savez, ils feraient mieux d'être vos amis, sinon je ne vous conseille pas de les déranger dans l'autre cas.";
			link.l1 = "Merci pour votre préoccupation, mais je suis bien armé et très charmant.";
			link.l1.go = "exit";
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "9");
			AddQuestUserData(sQuestTitle, "sShore", XI_ConvertString(sGenLocation + "Gen")); // belamour gen
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			SetFunctionTimerCondition("Church_GenQuest2_TimeIsLeft", 0, 0, 1, false);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2");
		break;
		// <-- Церковный генератор №2

		case "Meeting_1":
			Dialog.Text = "Hm... et en quoi cela me concerne-t-il? Vous vous êtes probablement perdu, capitaine. Allez à la boutique et vendez ou achetez là-bas ce que vous voulez.";
			Link.l1 = "Non, j'ai besoin de toi.";
			Link.l1.go = "Meeting_2";				
			Link.l2 = "Merci pour votre conseil. Bonne journée.";
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = "Pour quoi ?";
			Link.l1 = "Peut-être, vous serez intéressé par des marchandises spéciales ? Ou peut-être, avez-vous quelque chose à me proposer à la place ?"Link.l1.go ="Rencontre_3";				
		break;

		case "Meeting_3":
			int iTmp = false;
			int iChIdx, i;

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
				dialog.text = NPCStringReactionRepeat("Pourquoi ne prendriez-vous pas un homme de guerre royal la prochaine fois. Votre navire peut être repéré depuis le fort facilement. Nous ne risquerons pas nos têtes. Venez sur un seul petit navire la prochaine fois.","Dois-je me répéter? Trouve un navire plus petit et alors nous discuterons.","Es-tu vraiment si idiot? Trouve-toi une goélette ou une brigantine. Ce n'est que dans ce cas que nous aurons affaire.","Oh, quel idiot...","bloc",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("D'accord, je vous ai compris.","Je comprends, je voulais juste préciser quelque chose.","Non, pas un idiot, juste un avare. Pensais que quelque chose avait changé. J'aurais pris quelques pinnaces de plus...","Regarde dans le miroir...",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
				break;
			}
			bOk  = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
			bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
			bool bOk3 = CheckAttribute(Pchar, "questTemp.pirateStartQuest") && (Pchar.questTemp.pirateStartQuest == "3");
			if (bOk)
			{
			    if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
				{  // просрочка
					DeleteAttribute(PChar, "GenQuest.contraTravel");
					CloseQuestHeader("Gen_ContrabandTravel");
					bOk = false;
				}
			}

//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "Désolé, "+GetSexPhrase("pote","fille")+", nous sommes déjà occupés. Revenez dans quelques jours.";
				Link.l1 = "Dommage...";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "Que diriez-vous si nous finissions d'abord notre affaire en cours?";
				Link.l1 = "Je suppose que vous avez raison.";
				Link.l1.go = "Exit";				
			}
			else
			{
                if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;
                    
                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None")//boal fix
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "Je sais que nous pouvons faire des affaires avec vous. Nous vous attendrons à "+GetConvertStr(Pchar.quest.contraband.CurrentPlace,"LocLables.txt")+".";
                            }
                            else
                            {
            				    Dialog.Text = "Hm... Peut-être, nous pouvons vous trouver un acheteur. Nous vous attendrons à "+GetConvertStr(Pchar.quest.contraband.CurrentPlace,"LocLables.txt")+".";
            				}
            				Link.l1 = "D'accord. A bientôt là-bas.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            Dialog.Text = "Pas d'affaires aujourd'hui. Venez ici demain.";
            				Link.l1 = "D'accord.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "Croyez-vous vraiment que quelqu'un voudra travailler avec vous après tout cela? Vous feriez mieux d'être content que nous n'ayons pas envoyé les chasseurs de primes après vous.";
        				Link.l1 = "Dommage. Aucune chance pour moi de devenir un contrebandier.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    Dialog.Text = "Aucune affaire aujourd'hui. Venez ici demain.";
    				Link.l1 = "D'accord.";
    				Link.l1.go = "Exit";
				}
			}
		break;
////////////////////////////////////////////////////////////////////////////////
//	Корсарское метро
////////////////////////////////////////////////////////////////////////////////
		case "Travel":
//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "Désolé, "+GetSexPhrase("pote","fille")+", nous sommes déjà occupés. Revenez dans quelques jours.";
				Link.l1 = "Dommage.";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--
			//если нет корабля у ГГ и нет компаньонов все ок
			if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
			{
				//случай если уже была инфа
				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				{
					//платил уже
					if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
					{
						Dialog.Text = "Je pensais que nous avions déjà conclu l'accord ?";
						Link.l2 = "En effet !";
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "Avez-vous apporté l'argent?";
							Link.l1 = "Oui.";
							Link.l1.go = "Travel_pay";
							Link.l3 = "J'ai changé d'avis...";
							Link.l3.go = "Travel_abort";
							Link.l2 = "Pas encore.";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "Je vous ai déjà tout dit.";
								Link.l2 = "Exactement.";
								Link.l1 = "J'ai changé d'avis...";
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
							    Dialog.Text = "Je ne peux pas vous aider aujourd'hui. Revenez dans deux jours et peut-être aurons-nous quelque chose pour vous.";
								Link.l2 = "Dommage.";
								DeleteAttribute(PChar, "GenQuest.contraTravel");
								CloseQuestHeader("Gen_ContrabandTravel");
							}
						}
					}
				}
				//если не было договора, обговариваем условия
				else
				{
					nRel = ChangeContrabandRelation(pchar, 0);
					//если нормальные отношения и количество подстав меньше 20, работаем....
					if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
					{
						//бухта...
						pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
						aref arTmp; makearef(arTmp, pchar.GenQuest.contraTravel);
						SetSmugglersTravelDestination(arTmp);
						//за сколько доставят 
						pchar.GenQuest.contraTravel.price = (sti(PChar.rank)*250 + (100 - nRel)*10 + rand(30)*20) + sti(arTmp.destination.days)*100;
						
						//если метро активно, и нет пассажиров у ГГ, и ещё сегодня не виделись, есть доступная бухта, и ранд ...
						bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") && 
							Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
                        bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
						if (bOk && !bOk2)
						{
							nDay = 1 + rand(3);
							SetNPCQuestDate(npchar, "Travel_Talk");
							SaveCurrentQuestDateParam("contraTravel");

							Dialog.Text = "Eh bien, nous pouvons vous emmener à "+GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id,"LocLables.txt")+" près "+XI_ConvertString("Colonie"+pchar.GenQuest.contraTravel.destination+"Gen")+" pour "+pchar.GenQuest.contraTravel.price+" or. Apporte l'argent dans "+FindRussianDaysString(nDay)+". Le navire vous attendra à "+GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id,"LocLables.txt")+"exactement 24 heures.";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "Ça marche pour moi.";
							Link.l1.go = "Travel_agree";
							Link.l2 = "Non merci.";
						}
						else
						{
							Dialog.Text = "Je ne peux pas t'aider aujourd'hui. Reviens dans deux jours et peut-être aurons-nous quelque chose pour toi.";
							Link.l2 = "Dommage.";
						}
					}
					//нет, посылаем в сад
					else
					{
                        Dialog.Text = "Pensez-vous vraiment que quelqu'un voudra travailler avec vous après tout cela? Vous feriez bien d'être content que nous n'ayons pas envoyé les chasseurs de primes pour vous. Dégage!";
        				Link.l2 = "Hein, pas de chance encore une fois.";
					}

				}
			}
			//корабль есть, посылаем в сад...
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "Non, nous ne vous prendrons pas tous. Seulement l'un d'entre vous.";
					Link.l2 = RandSwear()+"Je n'en ai pas besoin de toute façon!";
				}
				else
				{
					Dialog.Text = "Pourquoi n'utilisez-vous pas votre propre navire? Non, nous ne vous emmènerons pas.";
					Link.l2 = "D'accord, comme tu veux.";
				}
			}
			Link.l2.go = "Exit";
			break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "Ce que vous voulez.";
			Link.l1 = "";
			Link.l1.go = "Exit";
			break;

		//ГГ согласен ехать
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetConvertStr(pchar.GenQuest.contraTravel.CurrentPlace, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
			AddQuestUserData("Gen_ContrabandTravel", "sDays", FindRussianDaysString(sti(pchar.GenQuest.contraTravel.days)));
			AddQuestUserData("Gen_ContrabandTravel", "sPrice", pchar.GenQuest.contraTravel.price);

			//активируем квест
			pchar.GenQuest.contraTravel.active = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;

		//ГГ согласен платить
		case "Travel_pay":
			//денег хватает?
			Sum = sti(pchar.GenQuest.contraTravel.price);
			if (sti(pchar.money) >= Sum)
			{
				AddMoneyToCharacter(pchar, -1*Sum);
				//ставим флаг оплаты
				pchar.GenQuest.contraTravel.payed = true;
				Dialog.Text = "C'est un plaisir de faire affaire avec vous. Ne soyez pas en retard sur le navire.";
				Link.l1 = "Je vais essayer.";
				AddQuestRecord("Gen_ContrabandTravel", "2");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
				
				//ставим контру.
				PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
				//корабль на волнах в бухте....
				Sum = sti(pchar.GenQuest.contraTravel.destination.days);
				sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "citiz_46", "man", "man", 5, PIRATE, Sum + 2, true, "hunter"));
				//воскресим...
				sld.nation = PIRATE;
				SetRandomNameToCharacter(sld);
				SetMerchantShip(sld, rand(GOOD_PAPRIKA));
				SetFantomParamHunter(sld);
				SetCaptanModelByEncType(sld, "pirate");
				SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

				SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
			}
			//нет, посылаем в сад...
			else
			{
				Dialog.Text = "Il semble que vous n'ayez pas assez d'argent."Link.l1 ="Quel dommage, je reviendrai plus tard.";
			}
			Link.l1.go = "Exit";
		break;  
////////////////////////////////////////////////////////////////////////////////
//	END OF Корсарское метро
////////////////////////////////////////////////////////////////////////////////
				
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_smugglers":
			dialog.text = "Très intéressant. Montre ce que tu as.";
			link.l1 = "J'ai entendu dire qu'il existe une boutique souterraine où vous pouvez échanger des marchandises très 'spéciales' à un prix tentant et vous avez aidé à démarrer cette boutique. J'aimerais parler avec son propriétaire.";
			link.l1.go = "Shadowtrader_fail";
			link.l2 = "J'ai entendu dire qu'il y a une boutique souterraine où tu peux échanger des marchandises très 'spéciales' à un prix alléchant. Je dois naviguer dans quelques jours et je n'ai pas assez d'argent pour acheter tout ce dont j'ai besoin au magasin local, alors j'ai besoin et envie d'économiser quelques pièces... certaines personnes m'ont dit que tu peux m'aider avec ça.";
			link.l2.go = "Shadowtrader_smugglers_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.seeksmugglers");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fail":
			dialog.text = "De quoi parles-tu? Je ne te comprends pas. Nous n'avons pas ouvert de boutique ici, c'est absurde, ha-ha! Si tu veux faire du commerce alors apporte-nous des marchandises et nous discuterons à notre manière habituelle... Une boutique, ha!";
			link.l1 = "Hm...";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			AddQuestRecord("Shadowtrader", "3");
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_smugglers_1":
			dialog.text = "Vous voulez un rabais? Facile. Venez à la porte du maître de port quand il fait noir. Notre homme vous rencontrera et vous emmènera au bon endroit.";
			link.l1 = "D'accord. Je serai là !";
			link.l1.go = "Shadowtrader_smugglers_2";		
		break;
		
		case "Shadowtrader_smugglers_2":
			pchar.questTemp.Shadowtrader.SeekTrader = "true";
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
			AddQuestRecord("Shadowtrader", "5");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			SetFunctionTimerCondition("ShadowtraderTimeSmugglers_Over", 0, 0, 2, false);
			int iNation = pchar.questTemp.Shadowtrader.nation;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
			sld = GetCharacter(NPC_GenerateCharacter("ShadowAgent_1", "citiz_"+(rand(9)+41), "man", "man", iRank, iNation, 2, true, "quest"));
			SetFantomParamFromRank(sld, iRank, true);
			GiveItem2Character(sld, "blade_04");
			EquipCharacterbyItem(sld, "blade_04");
			LAi_SetCitizenType(sld);
			sld.dialog.Filename = "Common_citizen.c";
			sld.dialog.currentnode = "First time";	
			sld.greeting = "cit_common"; 
			sld.city = pchar.questTemp.Shadowtrader.City;
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City +"_town", "goto", "goto1");
			pchar.quest.Shadowtrader_SMG.win_condition.l1 = "locator";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.location = pchar.questTemp.Shadowtrader.City + "_town";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator_group = "reload";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator = "reload10_back";
			pchar.quest.Shadowtrader_SMG.win_condition.l2 = "Night";
			pchar.quest.Shadowtrader_SMG.function = "ShadowAgent";
			DialogExit();
		break;
		// <-- Бесчестный конкурент
		//--> Торговля по закону
		case "TPZ_smugglers_1":
			dialog.text = "Ha, c’est ce filou derrière le comptoir qui t’envoie, hein?";
			link.l1 = "Et alors? Est-ce que c’est important? Tu peux fournir ou je dois chercher quelqu’un d’autre?";
			link.l1.go = "TPZ_smugglers_2";
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_smugglers_2":
			dialog.text = "Je peux tout trouver, tu vois? Suffit de payer correctement. Mais ce foutu gouverneur nous met la pression. Plus question de toucher à l’alcool – ça fait du bruit, on l’entend à un kilomètre, les marges sont minables, et le risque de finir pendu est immense. Alors désolé.";
			link.l1 = "Hmm... Et tu dis que tu peux tout trouver.";
			link.l1.go = "TPZ_smugglers_3";		
		break;
		
		case "TPZ_smugglers_3":
			dialog.text = "Je peux! Mais je ne veux pas. Y a un gars, juste à côté de la résidence du gouverneur, tu te rends compte? Ha-ha. Quel idiot... Qu’est-ce que je disais? Ah oui. Il vend un peu d’alcool discrètement. Juste sous la perruque du gouverneur, ha-ha. Va lui parler, peut-être qu’il pourra t’aider. Il bosse en petite quantité, mais c’est déjà ça.";
			link.l1 = "Pas vraiment utile, mais merci quand même.";
			link.l1.go = "TPZ_smugglers_4";		
		break;
		
		case "TPZ_smugglers_4":
			DialogExit();
			AddQuestRecord("TPZ", "3");
			DeleteAttribute(pchar, "questTemp.TPZ_ContraInfo");
			
			// проведаем дом Кристиана
			sld = GetCharacter(NPC_GenerateCharacter("TPZ_Kristian", "citiz_17", "man", "man", 1, FRANCE, -1, false, "quest"));
			sld.name = "Christian";
			sld.lastname = "Deluce";
			LAi_SetOwnerType(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			sld.City = "BasTer";
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Il y a beaucoup de fêtards ici et si vous n'avez pas d'affaires, monsieur, buvez ou parlez avec eux. Cet endroit est animé.";
			link.l1 = "Essayons encore. Je te paierai pour ton temps et ma curiosité. J'ai besoin de réponses.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			if (sti(pchar.money) >= 3002)
			{
				dialog.text = "Il paiera, ha ! Mon temps n'est pas bon marché, monsieur, il coûte 3000 pesos plus cette boisson dégoûtante qu'ils appellent par erreur du rhum.";
				link.l1 = "Marché conclu ! Maintenant, parle-moi de l'un des tiens qui a passé une demi-année en prison locale puis est passé de l'autre côté. Que lui est-il arrivé ?";
				link.l1.go = "Consumption_2";
			}
			else
			{
				dialog.text = "Tu ferais mieux de remplir tes poches d'argent ou d'or qui serait mieux. Ensuite viens parler, je n'ai pas de temps pour discuter avec toi gratuitement.";
				link.l1 = "Bonjour, monami.";
				link.l1.go = "exit";
			}
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3002);
			dialog.text = "Je me souviens de cela, bien que je ne comprenne pas pourquoi cela vous intéresse. Le gamin est vraiment devenu fou derrière ces barreaux. Il est devenu un ivrogne et parlait toujours de quelque absurdité à propos de la consommation qui emportait les gens et dont personne n'était à l'abri. Il disait que cette consommation avait un nom et n'ose même pas le dire à haute voix. Si vous le faites, il viendra aussi vous prendre.";
			link.l1 = "Et qu'est-ce qui lui est arrivé ensuite?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "L'histoire a une fin étrange, monsieur. Au début, les locaux et les marins aimaient son récit, mais finalement ils en avaient assez. C'est toujours le cas avec n'importe quelle fable. Alors ils l'ont provoqué pour qu'il dise le nom. Le gars se cabrait et résistait mais ne pouvait supporter les moqueries et l'a littéralement crié\nPersonne n'a ressenti quelque chose de spécial, les bougies ne se sont pas éteintes, mais le pauvre âme a été retrouvée morte le lendemain matin derrière la taverne avec la gorge tranchée.";
			link.l1 = "Je ne vois aucune magie ici. Dis-moi le nom.";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Je me souviens du nom, mais damn, je ne vais pas le dire à voix haute. Il y a quelque chose de sinistre dans tout ça. Ne le voyez-vous pas?";
			link.l1 = "Hey, l'ami, tu as reçu un portefeuille plein de pièces de ma part, tu te souviens? Alors, pourrais-tu gentiment me dire le nom?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Oh ça ne finira pas bien, senor, croyez-moi... (baissant la voix) Il a dit - Juan...";
			link.l1 = "Maudits soyez-vous! Juan? C'est juste un nom ordinaire et c'est assez populaire ici. Pourquoi est-ce si spécial?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Je ne sais pas, mais l'homme qui a prononcé ce nom a été tué. Faites confiance à mes instincts, quelque chose ne va pas avec ce nom. Est-ce tout ce que vous vouliez savoir?";
			link.l1 = "Je suppose que oui. Tu peux t'acheter un verre. A bientôt !";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Consumption.Contra");
			pchar.questTemp.Consumption.AskJuan = 0;
			pchar.questTemp.Consumption = "current";
			AddQuestRecord("Consumption", "6");
		break;
		//<-- Цена чахотки
		
		//Jason --> генератор сбыта бакаута
		case "bakaut":
			dialog.text = "C'est vrai ? Très bien. Mynheer Rosenkraft a besoin d'un lot de bois de fer, mais pas moins de "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+". Avez-vous assez de cargaison?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Je le fais. Où puis-je trouver monsieur Rosenkraft?";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hm. Je n'ai pas autant pour le moment.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			dialog.text = "Ne dérangez pas monsieur Rosenkraft alors. Venez quand vous aurez assez de cargaison.";
			link.l1 = "D'accord.";
			link.l1.go = "exit";
		break;
		
		case "bakaut_1":
			dialog.text = "Son galion naviguera près des côtes de "+XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gén")+" pendant plusieurs jours. Alors ne soyez pas en retard - il pourrait naviguer vers un autre endroit de l'archipel.";
			link.l1 = "D'accord, je vais accélérer. Merci !";
			link.l1.go = "bakaut_2";
		break;
		
		case "bakaut_2":
			DialogExit();
			sld = characterFromId("Rozencraft");
			sld.DeckDialogNode = "bakaut";
			DeleteAttribute(sld, "DontDeskTalk"); // можно выслать шлюпку
			pchar.GenQuest.Bakaut.Info = "true";
			ReOpenQuestHeader("Bakaut");
			AddQuestRecord("Bakaut", "1");
			AddQuestUserData("Bakaut", "sIsland", XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen"));
			AddQuestUserData("Bakaut", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Bakaut.DaysQty)));
			AddQuestUserData("Bakaut", "sQty", FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)));
			// таймер
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1 = "Timer";
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.function = "Bakaut_RozencraftRemove";
		break;
		// <-- генератор сбыта бакаута
		
		//--> прибыла инспекция на Святом Милосердии
		case "SantaMisericordia_1":
			dialog.text = "Et j'ai besoin de vivre jusqu'à demain. La maudite 'Miséricorde' est en ville. Partez.";
			link.l1 = "Quel drame...";
			link.l1.go = "exit";
		break;
		//<-- прибыла инспекция на Святом Милосердии
	}
}
