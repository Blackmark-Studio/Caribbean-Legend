#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
string sProf;		//  без оффа hasert	
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd()*0.1);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    int i, cn, iTemp;
    ref chref, compref; // без оффа hasert
	ref rRealShip;
    string attrL, sTitle, sCapitainId, s1;
	string sColony;
    
	String sLastSpeakDate = LastSpeakDate();
	
	// Warship 25.07.09 Генер "Сгоревшее судно". Даты отказа ГГ - если отказал, то предложит снова только на след сутки
	if(CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate") && NPChar.Quest.BurntShip.LastQuestDate != sLastSpeakDate)
	{
		DeleteAttribute(NPChar, "Quest.BurntShip");
	}
    
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
    string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //для списка кэпов

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}
	
	attrL = Dialog.CurrentNode;
	// hasert блок для сторожа ==>
	if(HasSubStr(attrL, "ShipStockManBack11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}
	
	if(HasSubStr(attrL, "ShipStockManBack22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}

	if(HasSubStr(attrL, "ShipStockManBack2_"))
	{
		i = findsubstr(attrL, "_" , 0);
		AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));

		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));//сторож

		////DownCrewExp(chref,GetNpcQuestPastDayParam(chref, "ShipInStockMan.Date"));

        int iChar = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); //выбранный пассажир
		compref = GetCharacter(iChar);

		DeleteAttribute(compref,"ship");//зачем-то стираем корабль офицера, хотя его там и не должно быть
		compref.ship = "";

		aref    arTo, arFrom;

		makearef(arTo, compref.ship);
		makearef(arFrom, chref.Ship);
		CopyAttributes(arTo, arFrom);

		// снимем пассажира -->
		CheckForReleaseOfficer(iChar);//увольнение офицера с должностей, если он не просто пассажир
		RemovePassenger(pchar, compref);
		// снимем пассажира <--
		SetCompanionIndex(pchar, -1, iChar);
		DelBakSkill(compref);
		DeleteAttribute(chref, "ShipInStockMan");
		chref.id = "ShipInStockMan";//сбрасываем индекс к стандартному, чтобы этот номер массива в следующий раз можно было занять
		DeleteAttribute(chref,"ship");//затираем данные корабля у сторожа
		chref.ship = "";
		LAi_SetCurHP(chref, 0.0);//ещё и убивать непися, чтоб точно очистился из массива?

		NPChar.Portman	= sti(NPChar.Portman) - 1;
		pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		Dialog.CurrentNode = "exit";//закрываем диалог, ещё одно подтверждение уже не справшиваем
	}
	
	if(HasSubStr(attrL, "ShipStockMan11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}

	if(HasSubStr(attrL, "ShipStockMan22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}
    //  <=== hasert
    
	if(HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_" , 0);
	 	NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
 	    Dialog.CurrentNode = "BurntShip19";
	}
    
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("L'alarme a été donnée dans la ville et tout le monde te cherche maintenant. Si j'étais toi, je ne resterais pas là.","Tous les gardes de la ville fouillent la ville à votre recherche. Je ne suis pas un imbécile pour vous parler !","Courez, "+GetSexPhrase("matelot","fillette")+", avant que les soldats ne te criblent de trous..."),LinkRandPhrase("Que désirez-vous, "+GetSexPhrase("scélérat","puant")+"?! Les gardes de la ville ont déjà flairé votre piste, vous n'irez pas loin, sale pirate !","Assassin, quittez ma maison sur-le-champ ! Gardes !","Je n'ai pas peur de toi, "+GetSexPhrase("vaurien","rat")+"! Bientôt ils te pendront dans notre fort, tu n'iras pas loin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, une alarme n'est jamais un problème pour moi...","Ils ne m'attraperont jamais."),RandPhraseSimple("Tais-toi, "+GetWorkTypeOfMan(npchar,"Understood. Please provide the text for translation.")+", et peut-être que je ne t'arracherai pas ta langue immonde!","Hein, "+GetWorkTypeOfMan(npchar,"")+", et tout le monde là-bas - attrapez les pirates ! C'est ce que je te dis, l'ami : reste tranquille et tu vivras..."));
				link.l1.go = "fight";
				break;
			}
			//Jason, фрахт
			if (CheckAttribute(pchar, "questTemp.WPU"))
			{
				if (pchar.questTemp.WPU.Fraht == "fail" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					dialog.text = "Oh, je sais qui vous êtes. Vous deviez livrer la cargaison mais vous l'avez volée à la place ! Gardes, gardes !";
					Link.l1 = "Aaargh !";
					Link.l1.go = "exit";
					LAi_group_Attack(NPChar, Pchar);
					break;
				}
			}
			//фрахт
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				dialog.text = "Que puis-je faire pour vous, monsieur ?";
				Link.l1 = "J'ai affaire avec vous...";
				Link.l1.go = "quests";
				Link.l2 = "Je suis désolé mais je dois y aller.";
				Link.l2.go = "exit";
				NPChar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			if(NPChar.quest.meeting == "0")
			{
				
				dialog.text = "Salutations, "+GetAddress_Form(NPChar)+". Je ne pense pas que nous nous soyons déjà rencontrés. Je suis "+GetFullName(npchar)+" - le maître du port.";
				Link.l1 = "Bonjour, "+GetFullName(NPChar)+". Je suis "+GetFullName(PChar)+", capitaine du '"+PChar.ship.name+"'.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice")
				{
					dialog.text = "Capitaine MacArthur, comme je vous le rappelle toujours - il n'est pas nécessaire de me consulter à chaque fois. Ne vous inquiétez pas.";
					link.l1 = "Arrêtez ça, Monsieur "+npchar.lastname+" Je suis comme tout le monde.";
					Link.l1.go = "node_2";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Salutations, "+GetAddress_Form(NPChar)+" . Avez-vous affaire avec moi ?","Bonjour, "+GetFullName(Pchar)+". J'ai vu ton navire entrer dans notre port et j'étais sûr que tu viendrais me voir.","Oh, capitaine "+GetFullName(Pchar)+" Qu'est-ce qui vous amène à moi ?");
				Link.l1 = "Bonjour, "+GetFullName(NPChar)+"Je voulais te parler.";
			}
			Link.l1.go = "node_2";
		break;
		
		case "node_2":
			// Церковный генератор 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// Получаем полную инфу
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "Alors, qu'en est-il de l'argent ? As-tu au moins mille pesos pour moi ?";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "Oui, j'ai"+GetSexPhrase("Bonjour, mon ami.","")+"C'est exactement mille pesos. Maintenant, l'information !";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("Non, pas encore...","Pas encore...","Pas encore, mais je l'apporterai bientôt...");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "S'il vous plaît, permettez-moi d'expliquer le coeur du problème. Moi et mon vieil ami, capitaine "+PChar.GenQuest.ChurchQuest_1.CapFullName+", nous nous sommes manqués de quelques heures seulement, et j'ai une affaire urgente à régler avec lui. Maintenant, je vais devoir le rattraper, mais je n'ai aucune connaissance"+GetSexPhrase("Bonjour, ami.","Bonjour, mon ami.")+"de son emplacement.";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// Полная инфа уже есть
				{
					link.l1 = "Maître de port, monsieur, j'ai besoin de quelques informations sur le navire nommé '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"appartenant au capitaine "+PChar.GenQuest.ChurchQuest_1.CapFullName+".";
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NextColonyIsLast")) // Он здесь, в этой колонии!		
						link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_1";
					else // Отправляет в рандомную колонию
						link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_1";
				}				
				break;
			}		
//-------------------------------------------//Jason, фрахт---------------------------------------------------
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && CheckAttribute(PChar, "questTemp.WPU.Fraht.LevelUp") && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
					Link.l1 = "La cargaison pour votre colonie est dans la cale de mon navire.";
					Link.l1.go = "Fraht_completeLevelUp";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht != "lost" && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
					Link.l1 = "La cargaison pour votre colonie est dans la cale de mon navire.";
					Link.l1.go = "Fraht_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht == "lost" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					if (pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
					{
						dialog.text = "Oh, enfin vous êtes venu. Franchement, je ne m'attendais pas à votre retour. Nous avons déjà demandé aux autorités de vous marquer comme personne recherchée. Alors, qu'avez-vous à dire ?";
						Link.l1 = "J'ai échoué à livrer la cargaison à temps en raison de circonstances imprévues. Mais je veux régler ce conflit de manière pacifique. J'ai apporté votre cargaison et j'espère que nous pourrons trouver un accord.";
						Link.l1.go = "Fraht_complete_bad";
					}
					else
					{
						dialog.text = "Oh, je sais qui tu es. Tu étais engagé pour livrer la cargaison mais tu l'as volée à la place ! Gardes, gardes !";
						Link.l1 = "Aaargh !";
						Link.l1.go = "exit";
						LAi_group_Attack(NPChar, Pchar);
					}
				}
// <-- фрахт
//-------------------------------------------//Jason, почта---------------------------------------------------	
		
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer != "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
					Link.l1 = "J'ai livré du courrier pour votre colonie.";
					Link.l1.go = "Postcureer_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer == "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Ah, enfin te voilà. Franchement, on te croyait déjà mort... Eh bien, je suppose que c'est mieux que tu sois juste un imbécile et non un cadavre.";
					Link.l1 = "Je n'ai pas pu livrer le courrier à temps en raison de circonstances imprévues. Mais le voici.";
					Link.l1.go = "Postcureer_complete_bad";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.fail") && pchar.questTemp.WPU.Postcureer.StartCity == npchar.city)
				{
					dialog.text = "Que s'est-il passé ? Vous avez l'air d'un cadavre ambulant.";
					Link.l1 = "Bonjour, mon ami."+GetAddress_FormToNPC(NPChar)+", tu avais raison quand tu m'as averti du danger. Deux hommes en noir m'ont attaqué juste à la sortie du bureau de l'autorité portuaire et... eh bien, ils m'ont pris le paquet.";
					Link.l1.go = "Postcureer_complete_fail";
					break;
				}
// <-- почта
//-------------------------------------------//Jason, эскорт---------------------------------------------------	
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
					Link.l1 = "J'ai été envoyé ici par le maître du port "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". On m'a demandé d'escorter un navire transportant une cargaison d'armes et de munitions. Voici mes papiers.";
					Link.l1.go = "Escort_LUGo_0";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0") && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
					Link.l1 = "J'ai escorté le navire avec les armes, comme nous l'avions convenu.";
					Link.l1.go = "Escort_LUGo_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "current" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
					Link.l1 = "J'ai retrouvé le navire disparu et l'ai amené à votre port. Le capitaine du navire a dû déjà se présenter à vous.";
					Link.l1.go = "Escort_LU1WM_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
					Link.l1 = "J'ai trouvé le navire disparu et l'ai amené à votre port. Le capitaine du navire devrait déjà vous avoir fait son rapport.";
					Link.l1.go = "Escort_LU1VSP_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "sink" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
					Link.l1 = "J'ai trouvé le navire disparu sur les rivages de l'île de "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+"Son capitaine était engagé dans un combat inégal contre les forces pirates accablantes. J'ai aidé de toutes les manières possibles, hélas, en vain : ces sacrés salauds ont coulé le navire. Tout ce que je pouvais faire à ce moment-là, c'était la venger.";
					Link.l1.go = "Escort_LU1VSP_completeSink";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
					Link.l1 = "J'ai trouvé le navire disparu sur les rivages de l'île de "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Eh bien, pas le navire, en fait, mais plutôt une cinquantaine d'hommes de son équipage et le capitaine. Ils sont en sécurité maintenant - l'équipage est monté à bord de mon navire, et le capitaine est dans votre ville maintenant - je suppose qu'il vous a déjà rendu visite.";
					Link.l1.go = "Escort_LU1S_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
					Link.l1 = "J'ai accompli votre mission. L'escadre pirate qui a attaqué le convoi marchand a été détruite.";
					Link.l1.go = "Escort_LU2_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus != "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
					Link.l1 = "Je suis le capitaine du navire d'escorte. Je suis venu signaler que j'ai amené les navires marchands au port.";
					Link.l1.go = "Escort_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus == "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
					Link.l1 = "Je suis le capitaine du navire d'escorte. J'ai été envoyé pour amener deux navires marchands et leur cargaison au port, mais, malheureusement, les deux navires escortés ont coulé lors d'une bataille avec un convoi ennemi. J'ai tout de même réussi à livrer la cargaison.";
					Link.l1.go = "Escort_fail";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id && !CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp"))
				{
					dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
					Link.l1 = "Je suis le capitaine du navire d'escorte. Je suis venu signaler que j'ai amené les navires marchands au port.";
					Link.l1.go = "Escort_complete";
					break;
				}
// <-- эскорт
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice" && NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "Quel plaisir de vous entendre dire cela. Beaucoup seraient devenus vaniteux à votre place. Alors, comment puis-je et mes registres vous aider?";
			}
			else dialog.text = "Excellent. Je suis à votre service, "+GetFullName(PChar)+".";
			if (npchar.city != "Panama") // Captain Beltrop, 24.12.2020, запрет брать задания и ставить корабли в ПУ Панамы
			{
				Link.l2 = "Avez-vous des travaux que je pourrais prendre ? Ou peut-être un contrat ?";
				Link.l2.go = "Work_check"; //квесты
				Link.l3 = "Puis-je amarrer l'un de mes navires ici pour un certain temps ?";
				Link.l3.go = "ShipStock_1";
			}
			if (sti(NPChar.Portman) > 0)
			{
                Link.l4 = "Je veux récupérer mon navire.";
    			Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "Je suis venu discuter d'affaires financières.";
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)	
			}
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Je suis ici à la demande d'un certain homme. Son nom est gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" m'a envoyé à vous. Je suis censé récupérer quelque chose...");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "Je voudrais en savoir plus sur les capitaines qui se sont enregistrés auprès de votre autorité portuaire.";
			link.l6.go = "CapitainList";
			link.l61 = "Pourriez-vous partager des informations sur les navires uniques, faits sur mesure, et leurs capitaines légendaires ?";
			link.l61.go = "UniqueShips";
			
			link.l8 = "Je suis sur une autre affaire.";
			// Warship 26.07.09 Генер "Сгоревшее судно"
			if(CheckAttribute(NPChar, "Quest.BurntShip") && !CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate"))
			{
				if(CheckAttribute(NPChar, "Quest.BurntShip.TimeIsOver")) // Просрочено
				{
					link.l8.go = "BurntShip10";
				}
				else
				{
					if(CheckAttribute(NPChar, "Quest.BurntShip.TwoDaysWait"))
					{
						if(GetNpcQuestPastDayParam(NPChar, "Quest.BurntShip.TwoDaysWait") >= 2)
						{
							link.l8.go = "BurntShip17";
						}
						else
						{
							link.l8.go = "quests";
						}
					}
					else
					{
						link.l8.go = "BurntShip12";
					}
				}
			}
			else
			{
				link.l8.go = "quests";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "portman_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Bonjour, je suis venu sur l'invitation de votre fils."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "C'est au sujet de votre fille...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "Je suis tombé par hasard sur ce paquet de documents de navire.";
					link.l10.go = "ShipLetters_out1";				
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "Je suis tombé par hasard sur ce paquet de documents de navire, quelqu'un a dû les perdre.";
						if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakPortman"))
						{
							link.l10.go = "ShipLetters_Portman1_1";						
						}
						else
						{
							link.l10.go = "ShipLetters_Portman2";
						}
					}
				}		
			}												
			Link.l15 = "Merci. Au revoir.";
			Link.l15.go = "exit";
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "Votre problème peut être facilement résolu. Allez voir l'officier du service de navigation et il pourra vous fournir toutes les informations concernant l'itinéraire du navire de votre ami.";
			link.l1 = "Malheureusement, ce n'est pas si simple. Mon ami a renommé son navire dans votre port... pour des raisons religieuses.";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "Je vois. Cela complique un peu les choses. Je dois fouiller dans les registres du navire, et cela prendra du temps. Et le temps, c'est de l'argent, comme vous le savez probablement.";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "Je comprends parfaitement cela, monsieur "+GetFullName(NPChar)+", et je suis suffisamment préparé pour évaluer votre temps ... à hauteur de, disons, mille pesos.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // Можно будет спросить.
				link.l1 = "C'est bien dommage, car je n'ai pas un sou sur moi en ce moment... Je reviendrai plus tard...";
				link.l1.go = "exit";
			}
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "Parfait ! Voyons voir maintenant... juste une minute... ici... bien. Le renommage du navire a été enregistré, et le navire, qui désormais sera connu sous le nom de '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"commandée par le capitaine "+PChar.GenQuest.ChurchQuest_1.CapFullName+"a mis les voiles aujourd'hui vers "+XI_ConvertString("Colony"+sColony+"Gen")+".";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "Oh ! Vous comprenez vraiment que je suis un homme très occupé, et je suis heureux que vous l'appréciiez ! Voyons maintenant... juste une minute... ici... bien. Le changement de nom du navire a été enregistré, et le navire, qui désormais sera connu sous le nom de '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"commandé par le capitaine "+PChar.GenQuest.ChurchQuest_1.CapFullName+"a mis les voiles aujourd'hui vers "+XI_ConvertString("Colonie"+sColony+"Gen")+".";			
				link.l1 = "Merci, monsieur, vous m'avez rendu un grand service.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_4";
				AddMoneyToCharacter(pchar, -1000);
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Gen"));
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);	
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true;
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_1":
			dialog.text = "Que voulez-vous savoir exactement ?";
			link.l1 = "Peux-tu me dire si le navire appartenant à ce capitaine a visité ton port ?";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;
						
		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "Hmm... Et puis-je savoir pourquoi vous demandez ?";
			link.l1 = "J'ai affaire avec lui. Mais s'il n'a pas accosté à votre port ou si vous ne savez pas...";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "Il l'a fait. Mais louez tous les Saints, ce matin même, il nous a débarrassés de sa présence et s'est dirigé vers "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapGoToColony+"Acc")+". Et je plains sincèrement quiconque doit avoir affaire à lui.";
			link.l1 = "Dans ce cas, souhaitez-moi bonne chance - et merci pour votre aide.";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_4";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "5");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Voc")); // belamour gen
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony; // Спрашиваем портмана в колонии, куда отправился кэп.
			if(rand(2) == 1) 
			{
				Log_TestInfo("The next colony is the last");
				PChar.GenQuest.ChurchQuest_1.NextColonyIsLast = true; // Флаг - следующая колония будет последней
			}
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_1":
			dialog.text = "Que voulez-vous savoir, "+GetSexPhrase("monsieur","mademoiselle")+" "+GetFullName(PChar)+"?";
			link.l1 = "Pourriez-vous me dire si ce capitaine a fait escale dans votre port ou non ?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "Hmm, il l'a bien fait. Et je dois dire que j'attends avec impatience ce moment béni où il quittera enfin ce port tant éprouvé.";
			link.l1 = "Vous voulez dire que son navire est encore ici ?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "Oui, gracieux "+GetSexPhrase("monsieur","dame")+"Tout le port, à commencer par les plus humbles débardeurs et en terminant par le chef du service des pilotes, prie pour son départ rapide. Son navire vient de quitter le bassin de radoub où il a été rapidement réparé, mais d'ici là, son vaillant capitaine s'était déjà chamaillé avec tous les charpentiers et avait rejeté trois lots de planches sélectionnées pour la coque du navire. Mais demain, notre Seigneur très gracieux et omniscient nous débarrassera de cette... de cette peste, de cette épine dans le flanc d'un homme !";
			link.l1 = "Maintenant, calmez-vous, monsieur "+NPChar.Name+", et sachez que quelqu'un d'autre va avoir encore plus de mal. Vous avez déjà passé cette épreuve, tandis que moi, je n'ai pas encore rencontré ce capitaine dont vous parlez. Et maintenant, si vous voulez bien m'excuser...";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_4";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "6");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
//			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithSailors = true; // Спрашиваем моряков
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithCap = true; // Говорим с капитаном
//			SetFunctionLocationCondition("Church_GenQuest1_ChangeCapitanLocation", "Deck_Near_Ship", true);
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = NPChar.city;
			Group_SetAddress("ChurchGenQuest1_CapGroup", colonies[FindColony(NPChar.City)].Island, "IslandShips1", "Ship_1"); // Ставим кэпа в порту колонии
			Characters[GetCharacterIndex("ChurchGenQuest1_Cap")].Nation = sti(NPChar.Nation); // Сменим нацию, чтоб вражды не было
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan"); // Больше не спрашиваем
//			if(rand(1) == 0) PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			sld = CharacterFromID("ChurchGenQuest1_Cap");
			sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		break;
						
		case "ShipLetters_out1":
			dialog.text = "Laissez-moi jeter un œil ! Oui, en effet, dans mes documents cet ensemble est marqué comme nul. C'est très aimable à vous d'avoir trouvé un moment pour venir me voir et me remettre ces papiers. Bon vent, capitaine !";
			link.l1 = "Merci !";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "CaptainBook"); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "10");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
				
		case "ShipLetters_Portman1_1":
			pchar.questTemp.different.GiveShipLetters.speakPortman = true;
			s1 = "Let me take a look! Yes, this vessel and its captain are both registered in my documents. ";
			s1 = s1 + "Your conscientiousness, captain, reflects credit upon yourself! Of course, your efforts must not go unrewarded.  ";
			dialog.text = s1+"Dis-moi, accepterais-tu une somme de "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" pesos une récompense convenable ?";
			link.l1 = "Bien sûr que non !";
			link.l1.go = "exit";
			link.l2 = "Eh bien, une somme modeste, mais ce n'était pas une grande affaire non plus. Oui, j'accepte votre offre, "+npchar.name+".";
			link.l2.go = "ShipLetters_Portman1_2";
		break;
		
		case "ShipLetters_Portman1_2" :
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "5");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "ShipLetters_Portman2":
			dialog.text = "Accepteras-tu mon offre ?";
			link.l1 = "Bien sûr que non !";
			link.l1.go = "exit";
			link.l2 = "Peut-être. Bien que je sois sûr que ces documents valent bien plus.";
			link.l2.go = "ShipLetters_Portman2_1";
		break;
		
		case "ShipLetters_Portman2_1":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "6");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 		
		break;

		case "EncGirl_1":
			dialog.text = "Je suis tout ouïe.";
			link.l1 = "J'ai amené votre fugitif.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, capitaine, merci beaucoup ! Comment va-t-elle ? Est-elle blessée ? Pourquoi s'est-elle enfuie ? Pourquoi ?\nNe comprend-elle pas ? Le fiancé est un homme riche et important ! La jeunesse est naïve et insensée... cruelle même. Souvenez-vous-en !";
			link.l1 = "Eh bien, vous êtes son père et la décision finale vous revient, mais je ne me précipiterais pas avec le mariage...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Que sais-tu ? As-tu tes propres enfants ? Non ? Quand tu en auras un, viens me voir et nous en parlerons. \nJ'ai promis une récompense à quiconque la ramènerait à sa famille.";
			link.l1 = "Merci. Tu devrais garder un oeil sur elle. J'ai l'impression qu'elle ne s'arrêtera pas là.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, vous êtes ce "+GetSexPhrase("capitaine qui a apporté","jeune demoiselle qui a apporté")+" mon fils prodigue avec une jeune mariée ?";
				link.l1 = "Oui, j'ai aidé à leur évasion.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, viens, bienfaiteur. Probablement en attente d'une récompense ?";
				link.l1 = "Eh bien, je me passe de récompense, votre gratitude suffira amplement.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Je vous suis très reconnaissant de ne pas avoir abandonné mon enfant dans une situation désespérée et de l'avoir aidé à trouver une issue à cette délicate situation. Permettez-moi de vous remercier et acceptez cette modeste somme ainsi qu'un cadeau personnel de ma part.";
			link.l1 = "Merci. Aider ce jeune couple fut un plaisir.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Merci ? Quels remerciements ?! Cela fait déjà un demi-an que cet imbécile traîne sans travail - et regardez-le, il a assez de temps pour des affaires amoureuses ! Quand j'avais son âge, je dirigeais déjà ma propre affaire ! Pff ! Un gouverneur a une fille à marier - et cet idiot a amené une traînée sans foi ni loi dans ma maison et a osé demander ma bénédiction !";
			link.l1 = "Hmm... Apparemment, vous ne croyez pas aux sentiments sincères ?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Quels sentiments ? De quels sentiments parles-tu ? Sentiments... comment peut-on être si léger d'esprit à ton âge ?! Honte à toi de céder aux caprices des jeunes et de te comporter en proxénète ! Non seulement tu as pris une fille de chez elle, mais tu as aussi ruiné la vie de mon novice. Il n'y aura pas de remerciements pour toi. Adieu.";
			link.l1 = "D'accord, et pareillement pour vous...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		case "node_4":
			//--> дача миниквестов начальника порта. 
			if (rand(2) < 2 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = LinkRandPhrase("Oui, bon sang ! J'ai un travail pour toi !","Ha ! Vous arrivez juste à temps ! J'ai un problème à résoudre.","Mais bien sûr ! Bien sûr que j'ai du travail pour vous ! Vous savez, je suis simplement submergé de problèmes ces derniers temps...");
				link.l1 = "Alors, veuillez en venir au fait, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}
			
			// Warship 25.07.09 Генер "Сгоревшее судно"
			if(hrand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "Dieu ! Capitaine "+GetFullName(PChar)+", tu arrives juste à temps ! Quel malheur s'est abattu, quelle calamité... Le navire a brûlé dans la rade sous la garde de l'autorité portuaire ! Par la négligence de la sécurité, le navire a brûlé... brûlé jusqu'à la ligne de flottaison...\n"+"Seigneur, qu'ai-je fait pour mériter un tel châtiment ? J'ai été un serviteur fidèle pendant tant d'années...";
				link.l1 = "Alors, c'est quoi le problème? Un navire a brûlé? Et à quoi servent les contrats d'assurance? Ou vous avez décidé de ne pas l'assurer pour économiser votre argent et maintenant vous vous rongez les sangs?";
				link.l1.go = "BurntShip4";
				link.l2 = "Le chantier naval vous assistera mieux que moi pour cela. Dans quelques mois, ils restaureront l'ancien ou même en construiront un nouveau. Désolé, je ne suis pas constructeur de navires...";
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- дача миниквестов начальника порта.

			dialog.text = "Le gouverneur prend soin du bien-être de ses citoyens, ainsi il a toujours des tâches à proposer. Il peut y avoir des marchands à la taverne intéressés à recevoir de l'aide, et la boutique a besoin de capitaines pour le transport maritime également.";
			Link.l1 = "J'ai une question de plus.";
			Link.l1.go = "node_2";
			Link.l2 = "Merci. Au revoir.";
			Link.l2.go = "exit";
		break;

///Jason-----------------------новые генераторы накопительного типа для портмана----------------------------
		int iTime, idaysQty, iGoods, iGoodsQty, amount;
		case "Work_check"://фейс-контроль - общая проверка профпригодности ГГ и выбор задания
			//--> проверка миниквестов начальника порта. 
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = "Tu étais censé localiser le capitaine "+npchar.quest.PortmansJornal.capName+" et lui rendre le journal de bord de son navire. Avez-vous réussi ?";
				link.l1 = "Non, pas encore...";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = "Vous vous êtes engagé à rechercher un bien volé "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" '"+npchar.quest.PortmansSeekShip.shipName+"'. Il n'y aura pas d'autres missions pour vous tant que vous n'aurez pas terminé celle-là.";
				link.l1 = "Je vais continuer mes recherches, attends juste.";
				link.l1.go = "exit";
				link.l2 = "Je veux abandonner la mission.";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = "Tu m'as promis de chercher ce qui a été volé "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" '"+npchar.quest.PortmansSeekShip.shipName+"Avez-vous accompli cela ?";
				bool bOk = false;
				for (i=0; i<=COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if(cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName && 
							RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
							RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{	//если нужный корабль - у ГГ
								sld.Ship.Type = GenerateShip(SHIP_TARTANE, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}				
				if (bOk)
				{
					link.l1 = "Oui, je l'ai trouvé, il est maintenant au port. Vous pouvez le prendre.";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "Je continuerai ma recherche, attendez juste.";
					link.l1.go = "exit";
				}
				link.l2 = "Je veux abandonner la mission.";
				link.l2.go = "SeekShip_break";
				break;
			}
			//<-- проверка миниквестов начальника порта. 
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2)//проверка повтора
				{
					if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
					{
						dialog.text = RandPhraseSimple("Il n'y a pas de travail pour ceux qui naviguent sous le pavillon de "+NationNameGenitive(sti(pchar.nation))+"Quittez mon bureau sur-le-champ !","Je ne collaborerai pas avec "+NationNameAblative(sti(pchar.nation))+"Va-t'en !");
						link.l1 = RandPhraseSimple("Eh bien, comme vous le souhaitez...","Eh bien, comme vous voulez...");
						link.l1.go = "exit";
						break;
					}
					if (isBadReputation(pchar,40)) // проверка репутации ГГ с вызывающим доверие belamour legendary edition
					{
						dialog.text = "Votre réputation ne m'inspire guère confiance. Je ne vais pas collaborer avec vous. Adieu.";
						link.l1 = "Quoi ! Ce ne sont que des mensonges.";
						link.l1.go = "exit";
						break;
					}
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
					{
						dialog.text = "Je ne veux pas vous insulter, capitaine, mais... J'ai bien peur que vous ne soyez pas en mesure de remplir ma mission - vous manquez simplement d'expérience. Je ne peux pas signer de contrat avec vous.";
						link.l1 = "Je vois. Eh bien, comme vous dites.";
						link.l1.go = "exit";
						break;
					}
					dialog.Text = "Hmm... Eh bien, cela dépend du travail qui vous intéresse.";
					link.l1 = "Je pourrais vous proposer d'affréter mon navire pour transporter des marchandises.";
					Link.l1.go = "Fraht_begin";		//фрахты
					link.l2 = "Je veux gagner de l'argent supplémentaire en escortant des marchands ou en livrant du courrier.";
					Link.l2.go = "Check_other";		//доставка почты, эскорт
					Link.l3 = "Eh bien, peut-être pourriez-vous proposer quelque chose ?";
					Link.l3.go = "node_4"; 			//судовой журнан, угнанное судно, сгоревшее судно
				}
				else
				{
					dialog.Text = "Il n'y a plus rien pour aujourd'hui. Reviens un autre jour.";
					link.l1 = "D'accord.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Je ne vois pas votre navire dans le port. Allez mouiller au large puis revenez me voir - nous essaierons de trouver quelque chose pour vous.";
				link.l1 = "D'accord, je vais faire juste cela.";
				link.l1.go = "exit";
			}
		break;
	
		case "Check_other"://выбор между почтовым курьером, эскортом и ничем
		SaveCurrentNpcQuestDateParam(npchar, "work_date"); // mitrokosta безусловно сохраняем
		int nTask = 0;
		string tasks[10]; // mitrokosta сделал выбор задания расширяемым на тот случай если задания добавятся
		if (sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER) {
			tasks[nTask] = "cureer";
			nTask++;
		}
		if (GetCompanionQuantity(pchar) < 3 && sti(RealShips[sti(pchar.Ship.Type)].Class) >= 4 && or(sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_WAR, sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER)) {
			tasks[nTask] = "escort";
			nTask++;
		}
		if (nTask > 0 && hrand(5) > 1) {
			string sTask = tasks[hrand(nTask - 1)];
			switch (sTask) {
				case "cureer":
					if (pchar.questTemp.WPU.Postcureer == "begin" || pchar.questTemp.WPU.Postcureer == "late" || pchar.questTemp.WPU.Postcureer == "lost" || pchar.questTemp.WPU.Postcureer == "fail" || CheckAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp")) { // если заняты
						dialog.text = "Malheureusement, je ne peux rien vous offrir de ce genre. Repassez dans quelques jours.";
						link.l1 = "Très bien, je ferai juste cela.";
						link.l1.go = "exit";
					} else { // если не заняты
						if (sti(pchar.questTemp.WPU.Postcureer.count) > 3 && hrand(1) == 1) { //если 2 уровень
							dialog.text = "Alors... Vous avez déjà pris plusieurs emplois en tant que courrier et vous y avez bien réussi, à ma connaissance. Vous pouvez probablement gérer la tâche que je m'apprête à vous confier.";
							link.l1 = "Je suis tout ouïe, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "Postcureer_LevelUp";
						} else { // первый уровень
							dialog.text = "Je vois que vous avez un navire rapide. Je peux vous offrir un travail de courrier - livrer du courrier et des papiers commerciaux.";
							link.l1 = "C'est intéressant. J'accepte. Où dois-je aller ?";
							link.l1.go = "Postcureer";
							link.l2 = "Je vous remercie, mais ce n'est tout simplement pas mon genre de travail.";
							link.l2.go = "exit";
						}
					}
				break;

				case "escort":
					if (pchar.questTemp.WPU.Escort == "begin" || pchar.questTemp.WPU.Escort == "late" || pchar.questTemp.WPU.Escort == "win" || CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp")) { // если заняты
						dialog.text = "Malheureusement, je ne peux rien vous offrir de ce genre. Revenez dans quelques jours.";
						link.l1 = "D'accord, je ferai juste cela.";
						link.l1.go = "exit";
					} else { // если не заняты
						if (sti(pchar.questTemp.WPU.Escort.count) > 3 && hrand(1) == 1) { // 2 уровень
							dialog.text = "Vous avez déjà escorté des navires marchands avec succès plusieurs fois. Je suppose que j'ai une mission qui vous conviendrait.";
							link.l1 = "Je suis tout ouïe.";
							link.l1.go = "Escort_LevelUp";
						} else { // 1 уровень
							if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_GALEON_H && 2500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) < 0 && !CheckAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID")) { // если на ТГ
								dialog.text = "J'ai un travail rien que pour vous. Il y a deux navires marchands dans le port qui auraient déjà dû prendre la mer. Le fait est que leur navire d'escorte a été endommagé et attend encore les réparations nécessaires, il ne pourra donc pas partir de sitôt.\nIl se trouve que votre navire est idéal pour le travail - de plus, je dois encore déposer une cargaison supplémentaire dans votre cale. Bien entendu, le paiement sera doublé - pour le fret et l'escorte.";
								link.l1 = "Quelle offre intéressante ! Je l'accepte !";
								link.l1.go = "escort_bonus";
								link.l2 = "Merci, mais ce n'est tout simplement pas mon genre de travail.";
								link.l2.go = "exit";
							} else { // просто эскорт
								dialog.text = "J'ai un travail rien que pour vous. Deux navires marchands se trouvent dans notre port en ce moment - ils ont besoin d'une escorte. Je vous propose d'escorter ces navires jusqu'à leur destination. Allez-vous le faire ?";
								link.l1 = "Une offre intéressante ! Je l'accepte !";
								link.l1.go = "escort";
								link.l2 = "Merci, mais ce n'est tout simplement pas mon genre de travail.";
								link.l2.go = "exit";
							}
						}
					}
				break;
			}
			break;
		}
		//ничего не подошло
		dialog.text = "Malheureusement, je ne peux rien vous proposer de ce genre. Repassez dans quelques jours.";
		link.l1 = "D'accord, je ferai justement cela.";
		link.l1.go = "exit";
		break;

///--> ------фрахт со свободным выбором пункта назначения, оплаты и вида груза из предложенного списка---------

		case "Fraht_begin":
			if (hrand(4) < 4)
			{
				if (pchar.questTemp.WPU.Fraht == "begin" || pchar.questTemp.WPU.Fraht == "late" || pchar.questTemp.WPU.Fraht == "lost" || CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))//проверка на занятость
				{
					dialog.Text = "Mais j'ai entendu dire que votre navire était déjà affrété. Je ne peux pas vous donner d'autres cargaisons. Honorez les engagements que vous avez déjà pris.";
					link.l1 = "Oui, vous avez probablement raison.";
					Link.l1.go = "exit";
					break;
				}
				if (1500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) > 0)//мало места - не даем
				{
					dialog.text = "Vous avez trop peu de place dans votre cale. J'ai besoin d'un navire plus spacieux pour un fret. Je vous suggère de vérifier au magasin - le marchand local affrète souvent des navires pour livrer de petites cargaisons.";
					link.l1 = "Je vois. Eh bien, comme vous dites.";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.WPU.Fraht.count > 3 && rand(1) == 0)
				{
					dialog.text = "Je n'ai rien de convenable pour le moment. Mais vous avez déjà effectué plusieurs livraisons réussies. J'ai un certain travail que j'aimerais vous confier spécifiquement.";
					link.l1 = "Je vous écoute. Quel genre de travail?";
					link.l1.go = "Fraht_LevelUp";
					break;
				}
				dialog.Text = "Eh bien, je peux vous offrir plusieurs opportunités de charter.";
				link.l1 = "Voyons voir, alors...";
				Link.l1.go = "Fraht_choise";
			}
			else
			{
				dialog.Text = "Il n'y a plus de cargaisons disponibles pour aujourd'hui. Revenez un autre jour.";
				link.l1 = "Oh bien.";
				Link.l1.go = "exit";
			}
		break;
	
		int iFrahtGoods1, iFrahtGoods2, iFrahtGoods3, iFrahtGoods;
		int iFrahtGoodsQty1, iFrahtGoodsQty2, iFrahtGoodsQty3;
		case "Fraht_choise":
			//выбираем города
			pchar.questTemp.WPU.Fraht.City1 = findCurrentCity1(npchar);
			pchar.questTemp.WPU.Fraht.City2 = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Fraht.City3 = findCurrentCity3(npchar);
			//выбираем товары
			iFrahtGoods1 = hrand(GOOD_PAPRIKA);
			iFrahtGoods2 = hrand(GOOD_PAPRIKA-3);
			iFrahtGoods3 = hrand(GOOD_PAPRIKA-7);
			pchar.questTemp.WPU.Fraht.Goods1 = iFrahtGoods1;
			pchar.questTemp.WPU.Fraht.Goods2 = iFrahtGoods2;
			pchar.questTemp.WPU.Fraht.Goods3 = iFrahtGoods3;
			//определим количество
			iFrahtGoodsQty1 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods1))/(1+frand(0.5));
			iFrahtGoodsQty2 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods2))/(1+frand(0.5));
			iFrahtGoodsQty3 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods3))/(1+frand(0.5));
			if (sti(iFrahtGoodsQty1) > 10000) iFrahtGoodsQty1 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty2) > 10000) iFrahtGoodsQty2 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty3) > 10000) iFrahtGoodsQty3 = 10000 + rand(500);
			pchar.questTemp.WPU.Fraht.GoodsQty1 = iFrahtGoodsQty1;
			pchar.questTemp.WPU.Fraht.GoodsQty2 = iFrahtGoodsQty2;
			pchar.questTemp.WPU.Fraht.GoodsQty3 = iFrahtGoodsQty3;
			pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Fraht.Chance = rand(4);//форс-мажор
			//определим сроки с учётом рандома
			int daysQty1 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City1));
			int daysQty2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City2));
			int daysQty3 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City3));
			pchar.questTemp.WPU.Fraht.DaysQty1 = makeint(sti(daysQty1)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty2 = makeint(sti(daysQty2)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty3 = makeint(sti(daysQty3)*(frand(1.3)+0.7));
			//установим цену исходя из объёма груза, дальности и сроков
			pchar.questTemp.WPU.Fraht.Money1 = (makeint((sti(iFrahtGoodsQty1) * sti(Goods[iFrahtGoods1].Weight) / sti(Goods[iFrahtGoods1].Units))))*(sti(daysQty1)*2)*sti(daysQty1)/sti(pchar.questTemp.WPU.Fraht.DaysQty1);
			pchar.questTemp.WPU.Fraht.Money2 = (makeint((sti(iFrahtGoodsQty2) * sti(Goods[iFrahtGoods2].Weight) / sti(Goods[iFrahtGoods2].Units))))*(sti(daysQty2)*2)*sti(daysQty2)/sti(pchar.questTemp.WPU.Fraht.DaysQty2);
			pchar.questTemp.WPU.Fraht.Money3 = (makeint((sti(iFrahtGoodsQty3) * sti(Goods[iFrahtGoods3].Weight) / sti(Goods[iFrahtGoods3].Units))))*(sti(daysQty3)*2)*sti(daysQty3)/sti(pchar.questTemp.WPU.Fraht.DaysQty3);
			if (hrand(5) < 4)//три варианта
			{
				dialog.text = "Les variantes suivantes sont disponibles :\n"+"cargaison "+GetGoodsNameAlt(iFrahtGoods1)+" en quantité de "+FindRussianQtyString(iFrahtGoodsQty1)+" à la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+", dans "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+". Paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\ncargo "+GetGoodsNameAlt(iFrahtGoods2)+" en montant de "+FindRussianQtyString(iFrahtGoodsQty2)+" à la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+", dans "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+". Paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+"\ncargaison "+GetGoodsNameAlt(iFrahtGoods3)+" en montant de "+FindRussianQtyString(iFrahtGoodsQty3)+" à la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3)+", à "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty3)+". Paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3))+" \nQuel est votre choix ?";
				Link.l1 = "Je choisirai la deuxième option - affréter vers la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+" chargé de "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "Je choisirai la troisième option - charte vers la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" chargé de "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
				Link.l3 = "Je choisirai la troisième variante - affréter vers la ville de "+XI_ConvertString("Colonie"+pchar.questTemp.WPU.Fraht.City3)+" chargé de "+GetGoodsNameAlt(iFrahtGoods3)+".";
				Link.l3.go = "Fraht_Choise_3";
			}
			else //два варианта
			{
				dialog.text = "Il y a les variantes suivantes disponibles:\n"+"cargaison "+GetGoodsNameAlt(iFrahtGoods1)+" à hauteur de "+FindRussianQtyString(iFrahtGoodsQty1)+" à la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+", dans "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+". Paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\ncargo "+GetGoodsNameAlt(iFrahtGoods2)+" en quantité de "+FindRussianQtyString(iFrahtGoodsQty2)+"  à la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+", dans "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+". Paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+" \nQuel est votre choix ?";
				Link.l1 = "Je choisirai la première option - affréter vers la ville de "+XI_ConvertString("Colonie"+pchar.questTemp.WPU.Fraht.City1)+" chargé de "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "Je choisirai la deuxième option - affréter vers la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" chargé de "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
			}
			Link.l4 = "Malheureusement, il n'y a rien qui me convienne.";
			Link.l4.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
		break;
	
		case "Fraht_Choise_1":
			dialog.text = "Eh bien, formidable ! Je vais traiter les documents nécessaires, et vous pourrez préparer votre navire pour le chargement.";
			link.l1 = "Je ferai de mon mieux !";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods1), sti(pchar.questTemp.WPU.Fraht.GoodsQty1));
			iFrahtGoods1 = pchar.questTemp.WPU.Fraht.Goods1;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods1));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty1)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty1)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty1), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City1+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods1].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods1].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty1);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods1);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty1);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money1);
		break;
	
		case "Fraht_Choise_2":
			dialog.text = "Eh bien, formidable ! Je vais traiter les documents nécessaires, et vous pouvez préparer votre navire pour le chargement.";
			link.l1 = "Je ferai de mon mieux !";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods2), sti(pchar.questTemp.WPU.Fraht.GoodsQty2));
			iFrahtGoods2 = pchar.questTemp.WPU.Fraht.Goods2;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods2));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty2)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty2)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty2), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City2+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods2].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods2].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty2);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods2);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty2);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money2);
		break;
	
		case "Fraht_Choise_3":
			dialog.text = "Eh bien, formidable ! Je vais traiter les documents nécessaires, et vous pouvez préparer votre navire pour le chargement.";
			link.l1 = "Je ferai de mon mieux !";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods3), sti(pchar.questTemp.WPU.Fraht.GoodsQty3));
			iFrahtGoods3 = pchar.questTemp.WPU.Fraht.Goods3;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods3));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty3)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty3)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty3), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City3+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods3].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods3].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty3);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods3);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty3);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money3);
		break;
	
		case "Fraht_Forcemajor":
			pchar.questTemp.WPU.Fraht = "begin";
			sld = characterFromId(pchar.questTemp.WPU.Fraht.TargetPortmanID);
			pchar.questTemp.WPU.Fraht.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Fraht.TargetCity = FindTownOnIsland(pchar.questTemp.WPU.Current.TargetIslandID);
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Fraht.Chance > 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Fraht.Chance == 2) FrahtHunterOnSea();//создание ДУ в акватории
			DialogExit();
		break;
	
		case "Fraht_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			iFrahtGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
			amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
			if (amount > 0)
			{
				dialog.text = "Voyons voir, alors. Vous étiez censé livrer une cargaison de "+GetGoodsNameAlt(iFrahtGoods)+" en montant de "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Mais comme je peux le voir, vous n'avez pas livré l'ensemble de la cargaison - vous êtes "+FindRussianQtyString(sti(amount))+" court.";
				link.l1 = "Par mille requins ! Ce doit être ces satanés rats ! Mais ne t'inquiète pas, "+GetAddress_FormToNPC(NPChar)+", j'achèterai la quantité manquante et remettrai le lot entier.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Voyons voir, alors. Vous deviez livrer une cargaison de "+GetGoodsNameAlt(iFrahtGoods)+" en montant de "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Correct?";
			link.l1 = "Absolument correct, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "Fraht_complete_1";
		}
		else
		{
			dialog.text = "Je ne vois pas votre navire dans le port. Jetez l'ancre au large puis revenez me voir - alors nous discuterons.";
			link.l1 = "D'accord, je ferai juste cela.";
			link.l1.go = "exit";
		}
		break;
	
		case "Fraht_complete_1":
			if (pchar.questTemp.WPU.Fraht == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Fraht.Late"))+1;
				pchar.questTemp.WPU.Fraht.DayLate = iTime;
				pchar.questTemp.WPU.Fraht.PercentLate = iTime/0.2;
				pchar.questTemp.WPU.Fraht.Money = makeint(sti(pchar.questTemp.WPU.Fraht.Money) - sti(pchar.questTemp.WPU.Fraht.Money)*sti(pchar.questTemp.WPU.Fraht.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... Mais vous étiez "+FindRussianDaysString(iTime)+" en retard. Par conséquent, je dois réduire votre paiement pour le fret. Selon le contrat, votre amende est de cinq pour cent du montant total pour chaque jour de retard. Maintenant, s'il vous plaît, prenez votre "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+", et essayez de respecter le contrat à l'avenir.";
				link.l1 = "Eh bien, c'est déjà quelque chose.";
				link.l1.go = "Fraht_complete_2";
				break;
			}
			dialog.text = "Merci pour votre travail. Je vous prie de prendre votre paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "Merci !";
			link.l1.go = "Fraht_complete_2";
		break;
	
		case "Fraht_complete_2":
			if (pchar.questTemp.WPU.Fraht == "begin")
			{
				pchar.quest.FrahtTime_Over.over = "yes";
				AddQuestRecord("Fraht", "2");
			}
			else
			{
				pchar.quest.FrahtTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Fraht", "4");
				AddQuestUserData("Fraht", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Fraht.DayLate));
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
			}
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
			CloseQuestHeader("Fraht");
			DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "Fraht_complete_bad":
			dialog.text = "As-tu livré la cargaison ? Joli. En fait, nous avons dû l'acheter nous-mêmes pour la remettre au destinataire ! Et cela nous a coûté cher, je te prie de le croire. Donc, si tu veux rétablir ta bonne réputation, tu devras compenser nos dépenses et payer l'amende. Quant à la cargaison, tu peux la garder - nous n'en avons plus besoin.";
			link.l1 = "Oui, bien sûr. Combien?";
			link.l1.go = "Fraht_complete_bad_1";
		break;
	
		case "Fraht_complete_bad_1":
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)*3;
			dialog.text = "Trois fois le coût des marchandises. Cela s'élève à "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+".";
			if (sti(Pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
			{
				link.l1 = "C'est pas mal. Mais les affaires sont les affaires. Très bien, voici votre argent.";
				link.l1.go = "Fraht_complete_pay";
			}
			link.l2 = "Es-tu fou ? Exiger une somme si scandaleuse est le comble de la cupidité ! Tu n'auras rien de moi !";
			link.l2.go = "Fraht_complete_fail";
		break;
	
		case "Fraht_complete_pay":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			dialog.text = "Une sage décision. Maintenant je vois que vous êtes véritablement une personne sérieuse. Je suppose que nous pourrons encore travailler ensemble à l'avenir.";
			link.l1 = "Merci, et maintenant je dois y aller.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 12);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 30);
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "8");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "6");
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Fraht");
				pchar.questTemp.WPU.Fraht = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 70);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
		break;
	
		case "Fraht_complete_fail":
			dialog.text = "Oh, je vois... Eh bien, dans ce cas, tu ne devrais plus jamais montrer ta frimousse à aucune autorité portuaire de "+NationNameGenitive(sti(pchar.questTemp.WPU.Fraht.Nation))+"! Va-t'en !";
			link.l1 = "Je n'ai sûrement pas manqué grand-chose...";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "9");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "7");
				CloseQuestHeader("Fraht");
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
		break;
	
		case "Fraht_complete_3":
			dialog.text = "Dépêchez-vous, le destinataire sait déjà que votre navire est arrivé et il s'inquiète pour sa cargaison.";
			link.l1 = "Dans ce cas, je ne vais pas perdre plus de temps !";
			link.l1.go = "exit";
		break;
	//фрахт <--
	
/// -------------------------------работа курьером по доставке почты-------------------------------------

		case "Postcureer":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.7)); 
			if (sti(pchar.questTemp.WPU.Postcureer.DaysQty) == 1) pchar.questTemp.WPU.Postcureer.DaysQty = 2;
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*1000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));
			dialog.text = "Ce paquet doit être livré à l'autorité portuaire de la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)+", pour "+FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DaysQty)+", et dès que possible. Paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))".";
			link.l1 = "Je suis d'accord !";
			link.l1.go = "Postcureer_1";
			link.l2 = "Hmm... Mais je ne vais pas par là. Désolé, mais je dois refuser.";
			link.l2.go = "exit";
		break;
	
		case "Postcureer_1":
			dialog.text = "Excellent ! Je compte sur vous. Voici le paquet.";
			link.l1 = "Je mettrai les voiles sur-le-champ !";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "PostLetters");
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)+1;//считаем сделанные доставки
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			if (pchar.questTemp.WPU.Postcureer.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Postcureer.Chance == 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "1");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_complete":
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.DayLate = iTime;
				pchar.questTemp.WPU.Postcureer.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money) - sti(pchar.questTemp.WPU.Postcureer.Money)*sti(pchar.questTemp.WPU.Postcureer.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... Mais vous étiez "+FindRussianDaysString(iTime)+" en retard. Par conséquent, je dois réduire votre paiement pour le travail. Selon le contrat, votre pénalité est de cinq pour cent du montant total pour chaque jour de retard. Maintenant, s'il vous plaît, prenez votre "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+", et essayez de vous en tenir au contrat à l'avenir.";
				link.l1 = "Eh bien, c'est déjà quelque chose.";
				link.l1.go = "Postcureer_complete_1";
				break;
			}
			dialog.text = "Merci pour votre travail. Veuillez prendre votre paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
			link.l1 = "Merci !";
			link.l1.go = "Postcureer_complete_1";
		break;
	
		case "Postcureer_complete_1":
			if (pchar.questTemp.WPU.Postcureer == "begin")
			{
				pchar.quest.PostcureerTime_Over.over = "yes";
				AddQuestRecord("Postcureer", "2");
			}
			else
			{
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "4");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DayLate));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			}
			RemoveItems(PChar, "PostLetters", 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Achievment_Set("ach_CL_118");
			DialogExit();
		break;
	
		case "Postcureer_complete_bad":
			dialog.text = "Et qu'allons-nous en faire maintenant ? Les gens l'attendaient depuis que Dieu sait combien de temps, et tu viens de l'apporter aujourd'hui. D'accord, donne-le-moi - peut-être qu'il y aura encore quelque utilité à en tirer. Et j'espère que tu comprends qu'aucun paiement n'est dû maintenant.";
			link.l1 = "Bien sûr, je le fais. Prends ton paquet. Adieu.";
			link.l1.go = "exit";
			RemoveItems(PChar, "PostLetters", 1);
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			Group_DeleteGroup("Fraht_Attack");
			pchar.questTemp.WPU.Postcureer = "fail";
		break;
	
/// ---------------------------работа в качестве эскорта для торговых кораблей----------------------------

		case "escort":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods1 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.Goods2 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1)); 
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));
			dialog.text = "Alors, tu devras escorter des navires '"+pchar.questTemp.WPU.Escort.ShipName1+"' et '"+pchar.questTemp.WPU.Escort.ShipName2+" à la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+", pour "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+". Paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))"Les deux navires doivent atteindre leur destination sains et saufs. Vous remettrez les navires au fonctionnaire de l'autorité portuaire locale. C'est lui qui vous paiera également pour le travail.";
			link.l1 = "Tout semble clair. Dois-je procéder ?";
			link.l1.go = "escort_1";
			link.l2 = "Hmm... Mais je ne vais pas par là. Désolé, mais je dois refuser.";
			link.l2.go = "exit";
		break;
	
		case "escort_1":
			dialog.text = "Allez-y. Ces navires sont sous votre commandement à partir de maintenant.";
			link.l1 = "Je mets les voiles, alors !";
			link.l1.go = "escort_add_ships";
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "1");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)); // belamour gen
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "escort_add_ships":
			int iGoods1, iGoods2, iSpace1, iSpace2, ShipType, Rank;
			int iNation = pchar.questTemp.WPU.Escort.ShipNation;
			int iLifeday = sti(pchar.questTemp.WPU.Escort.DaysQty)+10;
			string sTemp;
	        for (i=1; i<=2; i++)
	        {
				ShipType = GetRandomShipType(GetClassFlag(sti(RealShips[sti(pchar.Ship.Type)].Class)), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
				Rank = 5 * (6 - sti(RealShips[sti(pchar.Ship.Type)].Class)) + rand(5);
				if (i == 1) sTemp = pchar.questTemp.WPU.Escort.ShipName1;
				if (i == 2) sTemp = pchar.questTemp.WPU.Escort.ShipName2;
				if (i == 2) ShipType = SHIP_FLEUT;//один всегда флейт
	            sld = GetCharacter(NPC_GenerateCharacter("EscortCaptain_"+i, "trader_"+(rand(15)+1), "man", "man", Rank, iNation, iLifeday, true, "citizen"));
				FantomMakeSmallSailor(sld, ShipType, sTemp, CANNON_TYPE_CANNON_LBS16, 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10));
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				SetCharacterGoods(sld, GOOD_FOOD, 400+rand(200));
				SetCharacterGoods(sld, GOOD_MEDICAMENT, 60+rand(30));
	            iGoods1 = sti(pchar.questTemp.WPU.Escort.Goods1);
				iSpace1 = GetCharacterFreeSpace(sld, iGoods1);
				iSpace1 = makeint(iSpace1/2 + rand(iSpace1/2));
				iGoods2 = sti(pchar.questTemp.WPU.Escort.Goods2);
				iSpace2 = GetCharacterFreeSpace(sld, iGoods2);
				iSpace2 = makeint(iSpace2/2 + rand(iSpace2/2));
				if (i == 1) SetCharacterGoods(sld, iGoods1, iSpace1);
				if (i == 2) SetCharacterGoods(sld, iGoods2, iSpace2);
				sld.CompanionEnemyEnable = false; //всегда друзья
	            SetCompanionIndex(pchar, -1, sti(sld.index));
				sld.loyality = MAX_LOYALITY;
				SetCharacterRemovable(sld, false);
				sld.Dialog.Filename = "Common_portman.c";
				sld.dialog.currentnode = "Escort_companion";
				pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l1.character = "EscortCaptain_1";
				pchar.quest.Escort_fail.win_condition.l2 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l2.character = "EscortCaptain_2";
				pchar.quest.Escort_fail.function = "Escort_failed";
	        }
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			DialogExit();
		break;
	
		case "Escort_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//проверяем, все ли корабли
			if (GetCharacterIndex("EscortCaptain_1") == -1 || GetCharacterIndex("EscortCaptain_2") == -1)
			{
				dialog.text = "Hmm... Je ne vois qu'un seul navire dans votre escorte. Est-ce correct ?";
				link.l1 = "Oui, "+GetAddress_FormToNPC(NPChar)+". Un autre a été coulé lors d'une bataille avec un escadron ennemi.";
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
				{
					link.l1.go = "EscortBonus_complete_fail";
				}
				else
				{
					link.l1.go = "Escort_complete_fail";
				}
				break;
			}
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				//pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney);
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.TotalMoney);
				amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
				if (amount > 0)
				{
					dialog.text = "D'accord, alors. Vous étiez censé escorter des navires et livrer la cargaison de "+GetGoodsNameAlt(iGoods)+" en montant de "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+" . Mais je vois que vous n'avez pas livré toute la cargaison - vous êtes "+FindRussianQtyString(sti(amount))+" court.";
					link.l1 = "Mille requins ! Ce doit être ces maudits rats ! Mais ne t'inquiète pas, "+GetAddress_FormToNPC(NPChar)+", j'achèterai la quantité manquante et remettrai le lot entier.";
					link.l1.go = "Fraht_complete_3";
					break;
				}
			}
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... Mais vous étiez "+FindRussianDaysString(iTime)+" en retard. Par conséquent, je dois réduire votre paiement pour le travail. Selon le contrat, votre amende est de cinq pour cent du montant total pour chaque jour de retard. Maintenant, s'il vous plaît, prenez votre "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+", et essayez de respecter le contrat à l'avenir.";
				link.l1 = "Eh bien, c'est déjà quelque chose.";
				link.l1.go = "Escort_complete_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				dialog.text = "D'accord, alors. Vous deviez escorter des navires et livrer la cargaison de "+GetGoodsNameAlt(iGoods)+" en quantité de "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+". Merci pour votre travail. Prenez votre paiement, je vous prie - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			else
			{
				dialog.text = "Merci pour votre travail. S'il vous plaît, prenez votre paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			link.l1 = "Merci !";
			link.l1.go = "Escort_complete_1";
		}
		else
		{
			dialog.text = "Je ne vois pas votre navire dans le port. Mouillez au large puis venez me voir à nouveau - alors nous discuterons.";
			link.l1 = "D'accord, je ferai juste cela.";
			link.l1.go = "exit";
		}
		break;
	
		case "Escort_complete_1":
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				AddQuestRecord("Escort", "2");
			}
			else
			{
				pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//опоздавший рейс не засчитываем
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
				{
					pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				}
				AddQuestRecord("Escort", "4");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_1"));//удалим компаньонов
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_2"));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 100);//защита
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "escort_bonus":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods = 	hrand(GOOD_PAPRIKA);//для ГГ
			pchar.questTemp.WPU.Escort.Goods1 = hrand(GOOD_PAPRIKA-3);
			pchar.questTemp.WPU.Escort.Goods2 = hrand(GOOD_PAPRIKA-5);
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			iGoodsQty = makeint(GetCharacterFreeSpace(pchar, iGoods))-(50+rand(100));//количество груза
			pchar.questTemp.WPU.Escort.GoodsQty = iGoodsQty;
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1));//дни
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));//оплата за сопровождение
			pchar.questTemp.WPU.Escort.BonusMoney = (makeint((sti(iGoodsQty) * sti(Goods[iGoods].Weight) / sti(Goods[iGoods].Units))))*(sti(idaysQty)*2)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty);//оплата за фрахт
			pchar.questTemp.WPU.Escort.TotalMoney = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney); // общая сумма
			dialog.text = "Alors, vous aurez besoin d'escorter des navires '"+pchar.questTemp.WPU.Escort.ShipName1+"' et '"+pchar.questTemp.WPU.Escort.ShipName2+" à la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+", pour "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+". Paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+"Aussi sur votre navire, je place la cargaison de "+GetGoodsNameAlt(iGoods)+" en quantité de "+FindRussianQtyString(iGoodsQty)+". Paiement pour la livraison - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+".";
			link.l1 = "Tout semble clair. Dois-je procéder ?";
			link.l1.go = "escort_bonus_1";
			link.l2 = "Hmm... Mais je ne vais pas dans cette direction. Désolé, mais je dois refuser.";
			link.l2.go = "exit";
		break;
	
		case "escort_bonus_1":
			dialog.text = "Excellent ! Prenez le commandement de l'escadron.";
			link.l1 = "Je mets les voiles, alors !";
			link.l1.go = "escort_add_ships";
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.Bonus = "true";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 3) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "6");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
			AddQuestUserData("Escort", "sGoods", GetGoodsNameAlt(iGoods));
			AddQuestUserData("Escort", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)));
			AddQuestUserData("Escort", "sMoney1", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Escort.GoodsQty);//средняя стоимость товара
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "Escort_complete_fail":
			dialog.text = "Inconcevable ! Et pourquoi avions-nous besoin de vous ? Comment avez-vous pu laisser cela arriver ?! J'espère que vous comprenez qu'une récompense est maintenant hors de question.";
			link.l1 = "Bien sûr, je le fais... Eh bien, salutations distinguées.";
			link.l1.go = "exit";
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			pchar.quest.EscortTime_Over.over = "yes";//снять прерывание // patch-2
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));
			AddQuestRecord("Escort", "11");
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "EscortBonus_complete_fail":
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));//удалим компаньона
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			pchar.questTemp.WPU.Escort.GoodsQty = GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				pchar.questTemp.WPU.Escort.MinusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)*sti(amount));
				if (sti(pchar.questTemp.WPU.Escort.MinusMoney) < 0) amount = 101;
				if (amount > 0 && amount <= 100)
				{
					pchar.questTemp.WPU.Escort.BonusMoney = sti(pchar.questTemp.WPU.Escort.MinusMoney);
					dialog.text = "Incroyable ! Et pourquoi avions-nous besoin de vous ? Comment avez-vous pu laisser cela arriver ?! J'espère que vous comprenez que toute récompense pour l'escorte est maintenant hors de question... Non seulement cela, mais vous êtes également à court de cargaison - "+FindRussianQtyString(sti(amount))+"\nEn général, je ne vous paierai que pour le fret des marchandises livrées en bon état, moins la valeur des articles manquants. Vaquer à vos occupations "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" et vous pouvez aller où bon vous semble.";
					link.l1 = "Eh bien, c'est déjà quelque chose.";
					link.l1.go = "EscortBonus_complete_fail_1";
					break;
				}
				if (amount > 100)
				{
					dialog.text = "Incroyable ! Et pourquoi avions-nous besoin de vous ? Comment avez-vous pu permettre que cela se produise ?! J'espère que vous comprenez que toute récompense pour l'escorte est désormais hors de question... Non seulement cela, mais vous avez également une énorme pénurie de cargaison. \nJe n'ai pas le temps d'attendre que vous acquériez les marchandises manquantes. Donc vous devez compenser le coût en totalité - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+"Quant à la cargaison, vous pouvez la garder.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "D'accord, ne t'emporte pas trop. Voici ton argent.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Avez-vous tous perdu la tête ? C'est du racket pur et simple ! Je ne vous donnerai rien !";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Incroyable ! Et pourquoi avions-nous besoin de vous ? Comment avez-vous pu laisser cela se produire ?! J'espère que vous comprenez que toute récompense pour l'escorte est maintenant hors de question.\nEn général, je ne paierai que pour le fret des marchandises que vous avez prises. Obtenez votre "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" et vous pouvez aller où bon vous semble.";
				link.l1 = "Eh bien, c'est déjà quelque chose.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
			if (pchar.questTemp.WPU.Escort == "late")
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.BonusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Escort.BonusMoney)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				if (amount > 0)
				{
					dialog.text = "Inimaginable ! Et pourquoi avions-nous besoin de toi ? Comment as-tu pu laisser cela se produire ?! J'espère que tu comprends qu'il n'est plus question de récompense pour l'escorte maintenant... Tu as perdu un navire, tu es arrivé "+FindRussianDaysString(iTime)+"en retard, et en plus de cela, il te manque aussi de la cargaison - "+FindRussianQtyString(sti(amount))+"\nJe n'ai pas le temps d'attendre que vous acquériez les marchandises manquantes. Donc, vous devez compenser le coût en entier "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+"Quant à la cargaison, vous pouvez la garder.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "D'accord, ne vous échauffez pas trop. Voici votre argent.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Avez-vous tous perdu la tête ? C'est du racket pur et simple ! Je ne vous donnerai rien !";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Inouï ! Et pourquoi avions-nous besoin de vous ? Comment avez-vous pu laisser cela arriver ?! J'espère que vous comprenez que toute récompense pour l'escorte est maintenant hors de question... De plus, vous êtes arrivé "+FindRussianDaysString(iTime)+" tard.\nDonc j'ai dû réduire le paiement pour le fret. Selon l'accord, la pénalité est de 10 pour cent du montant initial pour chaque jour de retard. Maintenant, prends ton "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+", et vous pouvez partir.";
				link.l1 = "Eh bien, c'est déjà ça.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
		break;
	
		case "EscortBonus_complete_fail_1"://потеряли корабль, время и груз в норме или частично
			AddQuestRecord("Escort", "12");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.BonusMoney));
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_2"://потеряли корабль и груз, время норма или нет, мир
			AddQuestRecord("Escort", "13");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_3"://потеряли корабль и груз, время норма или нет, война
			dialog.text = "Oh, je vois... Eh bien, dans ce cas, tu ne devrais jamais montrer ta frimousse à aucune autorité portuaire de "+NationNameGenitive(sti(pchar.questTemp.WPU.Escort.Nation))+"Va-t'en !";
			link.l1 = "Je n'ai sûrement pas manqué grand-chose...";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "14");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.WPU.Escort.Nation)) + "hunter", 30);
			pchar.questTemp.WPU.Fraht.Nation = pchar.questTemp.WPU.Escort.Nation;
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "Escort_fail"://потеряли 2 корабля
			dialog.text = "C'est très, très mauvais ! Pour quoi vous avons-nous engagé, pouvez-vous me le dire ? Pour garder les navires ? Ou simplement pour traîner ?";
			link.l1 = "Je comprends. L'ennemi était tout simplement trop fort, et... mais à quoi bon discuter - ce qui s'est passé, s'est déjà passé. Mais la cargaison - la cargaison est toujours intacte ! Alors, réglons cela.";
			link.l1.go = "Escort_fail_complete";
		break;
	
		case "Escort_fail_complete":
			iFrahtGoods = makeint(pchar.questTemp.WPU.Escort.Goods);
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (amount > 0)
			{
				dialog.text = "Voyons voir, alors. Vous deviez livrer une cargaison de "+GetGoodsNameAlt(iFrahtGoods)+" en montant de "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+"Mais je vois que vous n'avez pas livré l'ensemble de la cargaison - vous êtes "+FindRussianQtyString(sti(amount))+" court.";
				link.l1 = "Mille requins! Ce doit être ces maudits rats! Mais ne vous inquiétez pas, "+GetAddress_FormToNPC(NPChar)+", je vais acheter la quantité manquante et livrer le lot entier.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Voyons voir, alors. Vous étiez censé livrer une cargaison de "+GetGoodsNameAlt(iFrahtGoods)+" en quantité de "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+". Correct?";
			link.l1 = "Absolument correct, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "Escort_fail_complete_1";
		break;
	
		case "Escort_fail_complete_1":
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney)/2);
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hmm... Non seulement vous avez perdu les navires qui vous ont été confiés, mais en plus vous êtes arrivé en retard de "+FindRussianDaysString(iTime)+". Donc, j'ai dû réduire le paiement pour le fret. Puisque vous n'avez pas pu sauver les navires, j'ai réduit de moitié le paiement pour le fret, et c'est le maximum que je peux vous offrir.\nDe plus, selon le contrat, l'amende est de 10 pour cent du montant initial pour chaque jour de retard. Maintenant, prenez votre "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+", et en avant.";
				link.l1 = "Eh bien, c'est déjà quelque chose.";
				link.l1.go = "Escort_fail_complete_2";
				break;
			}
			dialog.text = "Eh bien, bien que je sois extrêmement contrarié que vous n'ayez pas pu protéger les navires qui vous ont été confiés, au moins vous avez livré les marchandises. Puisque vous n'avez pas pu sauver les navires, j'ai réduit de moitié le paiement pour le fret, et c'est le maximum que je puisse vous offrir. Maintenant, prenez votre paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+" et vous pouvez aller où bon vous semble.";
			link.l1 = "Eh bien, c'est déjà quelque chose.";
			link.l1.go = "Escort_fail_complete_2";
		break;
	
		case "Escort_fail_complete_2":
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";
				AddQuestRecord("Escort", "17");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			else
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				AddQuestRecord("Escort", "18");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//фейловый рейс не засчитываем
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
//-------------------------------------задания 2 уровня для курьера---------------------------------------------
		case "Postcureer_LevelUp":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);//целевой город
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.6));//дни
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*3000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));//оплата
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			pchar.questTemp.WPU.Postcureer.StartNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}

			switch (rand(3))
			{
				case 0:
					dialog.text = "Vous devrez livrer une dépêche officielle urgente au gouverneur de la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" pas plus tard que "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Soyez très prudent - nos ennemis pourraient également être à la recherche de ce message. Paiement pour la livraison - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Je suis d'accord !";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Non, je suppose que je vais laisser passer.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_Mayor";//ИД губера
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == "Villemstad_Mayor") pchar.questTemp.WPU.Postcureer.TargetPortmanID = "hol_guber"; // фикс Матиаса Бека #717
					pchar.questTemp.WPU.Current.Add = "a dispatch for the governor";
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp1";//описание
				break;
			
				case 1:
					dialog.text = "Vous devrez livrer ces papiers au propriétaire du magasin de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gén")+"au plus tard que"+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+" . Voici le dernier résumé des prix dans les magasins de tout l'archipel - un document commercial précieux. Il faut être prudent - les concurrents pourraient organiser une chasse. Paiement pour la livraison - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Je suis d'accord !";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Non, je suppose que je vais passer.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_trader";//ИД торговца
//					pchar.questTemp.WPU.Current.Add = "сводку цен для хозяина магазина";
					pchar.questTemp.WPU.Current.Add = "a price list for the store owner";     // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp2";//описание
				break;
			
				case 2:
					dialog.text = "Vous devrez livrer ce paquet de documents à l'usurier dans la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" pas plus tard que "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". C'est une information très importante sur les taux de change et les cours des actions. Soyez très prudent - quelques personnages louches sont déjà intéressés par ce colis. Paiement pour la livraison - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Je suis d'accord !";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Non, je suppose que je vais passer.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_usurer";//ИД ростовщика
					pchar.questTemp.WPU.Current.Add = "a packet of information for the moneylender";   // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp3";//описание
				break;
			
				case 3:
					dialog.text = "Vous devriez livrer ce paquet au maître de quai dans la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gén")+" pas plus tard que "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Il contient les plans pour le nouveau "+RandPhraseSimple(LinkRandPhrase("brigantin","corvette","frégate"),LinkRandPhrase("flûte","pinace","galion"))+", employant des conceptions technologiques uniques. J'espère que vous comprenez qu'il y a d'autres... parties intéressées, donc vous devrez agir discrètement. Paiement pour la livraison - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Je suis d'accord !";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Non, je suppose que je vais passer.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_shipyarder";//ИД верфиста
					pchar.questTemp.WPU.Current.Add = "the draft of a new ship for the owner of the shipyard";
					pchar.questTemp.WPU.Current.Item = "ShipyardsMap";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_ShipyardsMap_PortmanLevelUp4";//описание
				break;
			}
		break;
	
		case "Postcureer_LevelUp_Go":
			dialog.text = "Alors prenez les documents et mettez les voiles. Bonne chance... et que le Tout-Puissant veille sur vous.";
			link.l1 = "Merci !";
			link.l1.go = "Forsmajor_choose";
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.LevelUp = "true";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) + 1;
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			ChangeItemDescribe(pchar.questTemp.WPU.Current.Item, pchar.questTemp.WPU.Current.Itemdescr);
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "6");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sText", pchar.questTemp.WPU.Current.Add);
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_LevelDown":
			dialog.text = "Dommage, en effet... En fait, des offres de ce genre ne se présentent pas souvent. Mais c'est votre décision, de toute façon.";
			link.l1 = "Oui, c'est mon appel, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) - 1;//за отказ от спецзадания счетчик скрутим
		break;
	
		case "Forsmajor_choose":
			switch (sti(pchar.questTemp.WPU.Postcureer.Chance))
			{
				case 0://охотники в городе прибытия + ДУ
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.City + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerGopHuntersOnLand";
					TraderHunterOnMap();
				break;
		
				case 1://создание скоростного перехватчика на глобалке
					EnemyNationHunterOnMap(true);
				break;
		
				case 2://запуск ДУ на глобалке и в порту прибытия
					TraderHunterOnMap();
					FrahtHunterOnSea();
				break;
		
				case 3://наёмники в стартовом городе
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerProfHuntersOnLand";
				break;
		
				case 4://агент
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerAgent";
				break;
			}
			DialogExit();
		break;

		case "Postcureer_complete_fail":
			dialog.text = "Sacré bleu ! Alors ils t'ont repéré, après tout. Dommage que tu ne sois pas un soldat, capitaine - dans ce cas, les choses auraient pu tourner différemment... À quoi ressemblaient-ils ?";
			link.l1 = "Deux hommes robustes en noir avec des demi-masques sur le visage, armés de haches d'armes et de fusils à double canon...";
			link.l1.go = "Postcureer_complete_fail_1";
		break;

		case "Postcureer_complete_fail_1":
			dialog.text = "Je notifierai immédiatement le gouverneur pour qu'il commence à les chercher. D'accord, à bientôt, "+GetAddress_Form(NPChar)+"Encore, c'est dommage que vous ne soyez pas un soldat...";
			link.l1 = "Je suis vraiment désolé, "+GetAddress_FormToNPC(NPChar)+", pour ce qui s'est passé. Eh bien, adieu.";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.fail");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
	
//----------------------------------------задания 2 уровня фрахт------------------------------------------

	case "Fraht_LevelUp":
		rColony = GetColonyByIndex(FindColony(npchar.city));
		pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Fraht.Nation = npchar.nation;//нация получателя
		switch (rand(4))//для тестов
		{
			case 0:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_CHOCOLATE + hrand(makeint(GOOD_TOBACCO - GOOD_CHOCOLATE));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 3000 + sti(pchar.rank)*30*(hrand(9)+1);
				iGoodsQty = 1000+sti(pchar.rank)*10*(hrand(9)+1); // min 1100 max 5000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "Une demande pour une certaine marchandise a récemment augmenté de manière spectaculaire dans notre colonie. Les magasins locaux n'en ont plus en stock. Par conséquent, je voudrais que vous me fournissiez "+GetGoodsNameAlt(iGoods)+" en montant de "+FindRussianQtyString(iGoodsQty)+", et je suis prêt à payer le double - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" par article. Cela se montera à "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+" Oh, et essayez de respecter le délai d'un mois - je ne pourrai pas attendre les marchandises plus longtemps.";
				link.l1 = "D'accord, j'accepte cette mission.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Je suis désolé de vous décevoir mais je ne peux pas le faire en ce moment.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 1:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_EBONY + hrand(makeint(GOOD_CINNAMON - GOOD_EBONY));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 1500 + sti(pchar.rank)*20*(hrand(9)+1);
				iGoodsQty = 600+sti(pchar.rank)*5*(hrand(6)+1); // min 630 max 2000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "Une demande pour une certaine marchandise a récemment augmenté de manière spectaculaire dans notre colonie. Les magasins locaux n'en ont plus en stock. Par conséquent, je voudrais que vous me fournissiez "+GetGoodsNameAlt(iGoods)+" d'un montant de "+FindRussianQtyString(iGoodsQty)+", et je suis prêt à payer le double - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" par article. Cela s'élèvera à "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Oh, et essayez de respecter le délai d'un mois - je ne pourrai pas attendre les marchandises plus longtemps.";
				link.l1 = "D'accord, j'accepte cette mission.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Je suis désolé de vous décevoir, mais je ne peux pas le faire en ce moment.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 2:
				//pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS + hrand(makeint(GOOD_POWDER - GOOD_BOMBS));
				pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				iGoodsQty = 5000+sti(pchar.rank)*10*(hrand(9)+1); // min 5100 max 9000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/20);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "L'arsenal de notre colonie manque cruellement "+GetGoodsNameAlt(iGoods)+". Les magasins locaux n'en ont plus en stock. Par conséquent, j'aimerais que vous me fournissiez "+GetGoodsNameAlt(iGoods)+" en montant de "+FindRussianQtyString(iGoodsQty)+", et je suis prêt à payer triple - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" par article. Cela s'élèvera à "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Oh, et essayez de respecter le délai d'un mois - je ne pourrai pas attendre les marchandises plus longtemps.";
				link.l1 = "D'accord, j'accepte cette mission.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Je suis désolé de vous décevoir mais je ne peux pas le faire en ce moment.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 3:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_MEDICAMENT;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 7000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/30);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "Après la récente épidémie de fièvre dans notre colonie, nous manquons de fournitures médicales - et il ne reste rien dans les magasins. Le gouverneur craint pour la sécurité des habitants. Par conséquent, j'aimerais que vous me fournissiez "+GetGoodsNameAlt(iGoods)+" en montant de "+FindRussianQtyString(iGoodsQty)+", et je suis prêt à payer le triple - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" par paquet. Cela s'élèvera à "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Oh, et essayez de respecter le délai d'un mois - je ne pourrai pas attendre les marchandises plus longtemps.";
				link.l1 = "D'accord, j'accepte cette mission.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Je suis désolé de vous décevoir, mais je ne peux pas le faire en ce moment.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 4:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_FOOD;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2)/10);//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "Apres une mauvaise récolte, notre colonie a constamment besoin de nourriture importée. En ce moment, notre stock est presque vide, et tout a été balayé des étagères des magasins depuis un bon moment. Je voudrais vous demander de me livrer "+GetGoodsNameAlt(iGoods)+" en quantité de "+FindRussianQtyString(iGoodsQty)+", et je suis prêt à payer le double - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+"par paquet. Cela s'élèvera à "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+"Ah, et essayez de respecter le délai d'un mois - je ne pourrai pas attendre la marchandise plus longtemps.";
				link.l1 = "D'accord, j'accepte cette mission.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Je suis désolé de vous décevoir, mais je ne peux pas le faire pour le moment.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		}
	break;
		
	case "Fraht_LevelDown":
		DialogExit();
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//скрутим счетчик
	break;
		
	case "Fraht_LevelUp_Go":
		dialog.text = "Excellent ! Je suis très heureux que vous ayez accepté. J'espère vous revoir bientôt.";
		link.l1 = "Bien sûr, "+GetAddress_FormToNPC(NPChar)+".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Fraht = "begin";
		pchar.questTemp.WPU.Fraht.LevelUp = "true";
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count) + 1;
		pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.StartCity +"_portman";//ИД портмана
		iGoods = pchar.questTemp.WPU.Fraht.Goods;
		ReOpenQuestHeader("Fraht");
		AddQuestRecord("Fraht", "8");
		AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
		AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
		AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iGoods));
		AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty)));
		AddQuestUserData("Fraht", "sText", pchar.questTemp.WPU.Current1.Add);
		SetFunctionTimerCondition("FrahtTimeLevelUp_Over", 0, 0, 30, false);
	break;
	
	case "Fraht_completeLevelUp":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		iGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
		amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
		if (amount > 0)
		{
			dialog.text = "Tu te moques de moi ? Tu n'as pas la quantité de marchandises que j'ai commandée !";
			link.l1 = "Je suis désolé, ma faute...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "D'accord, vous deviez livrer une cargaison de "+GetGoodsNameAlt(iGoods)+" en quantité de "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+"Excellent, merci beaucoup. Voici votre paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "C'est un plaisir de faire affaire avec vous, "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "Fraht_completeLevelUp_1";
		}
	}
	else
	{
		dialog.text = "Je ne vois pas votre navire dans le port. Allez mouiller au large, puis revenez me voir - alors nous parlerons.";
		link.l1 = "D'accord, je ferai juste cela.";
		link.l1.go = "exit";
	}
	break;
	
	case "Fraht_completeLevelUp_1":
		pchar.quest.FrahtTimeLevelUp_Over.over = "yes";//снять таймер
		AddQuestRecord("Fraht", "2");
		CloseQuestHeader("Fraht");
		RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current1"); // лесник  Current1 вместо Current
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.LevelUp");
		pchar.questTemp.WPU.Fraht = "complete";
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
		DialogExit();
	break;
	
//----------------------------------------задания 2 уровня эскорт ------------------------------------------

	case "Escort_LevelUp":
		pchar.questTemp.WPU.Escort.LevelUp = "true";//установим атрибут
		pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Escort.Nation = npchar.nation;//нация квестодателя
		pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
		i = 0;
		while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
		{
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
			i++;
			if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
		}
		switch (hrand(2))
		{
			case 0://приключения на необитаемых островах
				pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();//выбор необитайки
				while (!isLocationFreeForQuests(pchar.questTemp.WPU.Current.TargetIslandID)) pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();//выбор корабля
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));//имя корабля
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				pchar.questTemp.WPU.Escort.ShipBaseName = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.WPU.Escort.ShipType), "Name") + "Gen"));
				dialog.text = "Cette calamité est survenue il y a dix jours... une caravane de navires marchands à destination de notre colonie a été attaquée par des pirates. Une tempête a forcé les pirates à battre en retraite, mais les navires marchands se sont dispersés et ont perdu de vue l'un l'autre. Finalement, tous les navires sont arrivés dans différents ports, sauf un. \n"+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+" a disparu et son destin reste inconnu. On présume qu'elle peut être trouvée près de l'île inhabitée de "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Je vous demande d'y aller, de découvrir ce qui est arrivé au navire perdu et, si elle a survécu, de l'amener à notre port. Nous déciderons de votre compensation une fois le travail accompli, mais je vous assure que cela en vaudra la peine.";
				link.l1 = "Bien sûr, j'accepte !";
				link.l1.go = "Escort_LevelUp_1";
				link.l2 = "Je suis désolé, mais ce travail ne me convient pas. J'ai bien peur de devoir refuser.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 1://защитить конвой вблизи текущего острова от пиратов
				pchar.questTemp.WPU.Current.TargetIslandID = Islands[GetCharacterCurrentIsland(PChar)].id;//текущий остров
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				dialog.text = "Une caravane commerciale était censée arriver à notre colonie, mais juste avant d'entrer dans le port, elle a été attaquée par les pirates. La bataille se déroule à l'instant même. Elle est hors de portée des canons du fort et je n'ai aucun navire d'escorte disponible pour le moment, donc je ne peux fournir aucune aide aux pauvres marchands. Vous êtes un capitaine vaillant, c'est pourquoi je vous demande d'intervenir et d'aider les marchands à repousser l'attaque ! Accepterez-vous ?";
				link.l1 = "Bien sûr ! C'est une question d'honneur !";
				link.l1.go = "Escort_LevelUp_2";
				link.l2 = "Je suis désolé mais ce travail ne me convient pas. J'ai bien peur de devoir décliner.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 2://встретить и довести
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();
				pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//город, откуда забрать
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
				sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
				pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
				pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(npchar);//ИД целевого ареала
				pchar.questTemp.WPU.Escort.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));//расстояние в днях
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.DaysQty)*2000+20000;
				pchar.questTemp.WPU.Escort.Chance = rand(1);
				dialog.text = "Un navire avec des armes et des munitions que notre colonie a commandées est récemment arrivé à la colonie "+XI_ConvertString(pchar.questTemp.WPU.Escort.City)+"Son navire d'escorte a heurté le récif, a été gravement endommagé et ne pourra pas quitter le port de sitôt. Nous ne pouvons pas prendre le risque d'envoyer un navire marchand avec une telle cargaison seul.\nAccepteriez-vous de l'escorter jusqu'à notre colonie ? Le paiement pour le travail est fixé à "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
				link.l1 = "Bien sûr, j'accepte !";
				link.l1.go = "Escort_LevelUp_0";
				link.l2 = "Je suis désolé mais ce travail ne me convient pas. J'ai bien peur de devoir refuser.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
		}
	break;
	
	case "Escort_LevelUp_exit":
		dialog.text = "Quel dommage, vraiment. Je comptais sur vous...";
		link.l1 = "Je suis désolé aussi. Eh bien, jusqu'à ce que nous nous rencontrions à nouveau, "+GetAddress_FormToNPC(NPChar)+".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//скрутим счетчик
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	break;
	
	case "Escort_LevelUp_0":
		dialog.text = "Excellent ! Je savais que je pouvais compter sur vous. Veuillez essayer d'être aussi rapide que possible. Je pense "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+" suffira pour arriver à "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City+"Gén")+". Tenez, prenez ces papiers qui confirmeront votre identité. Vent arrière, capitaine !";
		link.l1 = "Ne vous inquiétez pas, je ne vous laisserai pas tomber.";
		link.l1.go = "Escort_LevelUp_0_go";
	break;
	
	case "Escort_LevelUp_0_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "19");
		AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty));
		SetFunctionTimerCondition("EscortArsenalShip_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+1, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.LevelUp_0 = "true";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LUGo_0":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.EscortArsenalShip_Over.over = "yes";
		dialog.text = "Enfin ! Ce navire a été une horreur pour les yeux bien trop longtemps. Prenez le commandement, alors. Le nom du navire est "+pchar.questTemp.WPU.Escort.ShipName+", et son capitaine sera immédiatement informé de votre arrivée.";
		link.l1 = "Dites-lui de préparer son navire à appareiller - je vais partir dès que possible.";
		link.l1.go = "Escort_LUGo_01";
	}
	else
	{
		dialog.text = "Je ne vois pas votre navire dans le port. Mouillez au large pour le moment et revenez me voir plus tard - alors nous parlerons.";
		link.l1 = "Je ferai exactement cela.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_01"://добавляем компаньона
		int iShipType = sti(pchar.questTemp.WPU.Escort.ShipType);
		sTemp = pchar.questTemp.WPU.Escort.ShipName;
		sld = GetCharacter(NPC_GenerateCharacter("ArsenalShipCaptain", "citiz_41", "man", "man", 15, sti(pchar.nation), -1, true, "quest"));
		FantomMakeSmallSailor(sld, iShipType, sTemp, CANNON_TYPE_CANNON_LBS16, 65, 22, 24, 35, 33);
		SetFantomParamFromRank(sld, 15, true); 
		SetCaptanModelByEncType(sld, "war");
		SetCharacterGoods(sld, GOOD_FOOD, 500);
		SetCharacterGoods(sld, GOOD_BALLS, 5000);
		SetCharacterGoods(sld, GOOD_GRAPES, 3000);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 3000);
		SetCharacterGoods(sld, GOOD_BOMBS, 5000);
		SetCharacterGoods(sld, GOOD_POWDER, 10000);
		SetCharacterGoods(sld, GOOD_WEAPON, 3000);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		SetCharacterRemovable(sld, false);
		sld.loyality = MAX_LOYALITY;
		sld.Dialog.Filename = "Common_portman.c";
		sld.dialog.currentnode = "Escort_companion";
		DialogExit();
		AddQuestRecord("Escort", "20");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
		pchar.quest.Escort_fail.win_condition.l1.character = "ArsenalShipCaptain";
		pchar.quest.Escort_fail.function = "EscortArsenalShip_failed";
		SetFunctionTimerCondition("EscortArsenalShipGo_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+6, false);
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0");
		pchar.questTemp.WPU.Escort.LevelUpGo_0 = "true";
		if (sti(pchar.questTemp.WPU.Escort.Chance) == 0) EnemyNationHunterOnMap(true);//скоростной перехватчик
		else FrahtHunterOnSea();
	break;
	
	case "Escort_LUGo_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.Escort_fail.over = "yes";
		pchar.quest.EscortArsenalShipGo_Over.over = "yes";
		dialog.text = "Excellent ! Encore une fois, vous avez prouvé que l'on peut compter sur vous. Merci pour ce travail bien fait. Veuillez accepter votre paiement - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+"  Et n'oublie pas de me rendre visite de temps en temps - il y a toujours une ou deux missions pour un capitaine comme toi.";
		link.l1 = "Ravi de l'entendre, "+GetAddress_FormToNPC(NPChar)+" ! Bien sûr, notre collaboration se poursuivra. Meilleures salutations !";
		link.l1.go = "Escort_LUGo_complete_1";
	}
	else
	{
		dialog.text = "Je ne vois pas votre navire dans le port. Mettez-vous en attente pour l'instant et revenez me voir plus tard - alors nous parlerons.";
		link.l1 = "D'accord, je ferai juste cela.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_complete_1":
		RemoveCharacterCompanion(Pchar, characterFromID("ArsenalShipCaptain"));
		sld = characterFromId("ArsenalShipCaptain");
		sld.lifeday = 0;//на всякий случай
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
		AddQuestRecord("Escort", "24");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		CloseQuestHeader("Escort");
		DialogExit();
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 100, 100, 0, 100, 0, 0);
		AddComplexSelfExpToScill(30, 30, 30, 30);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_1":
		dialog.text = "Alors, je vous souhaite bon voyage. Et je vous en prie, ne tardez pas dans vos recherches ! L'équipage de ce navire pourrait avoir besoin d'une aide immédiate.";
		link.l1 = "Compris. Je vais mettre les voiles aujourd'hui !";
		link.l1.go = "Escort_LevelUp_1_select";
	break;
	
	case "Escort_LevelUp_1_select"://выберем приключение
		switch (rand(2))
		{
			case 0://весь побитый и остался без мачты
				pchar.quest.DisasterShip_WM.win_condition.l1 = "location";
				pchar.quest.DisasterShip_WM.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_WM.function = "CreateDisasterShip_WithoutMasts";
				pchar.questTemp.WPU.Escort.LevelUp_1WM = "true";
			break;
			case 1://ведет бой с пиратусами в шторме
				pchar.quest.DisasterShip_VSP.win_condition.l1 = "location";
				pchar.quest.DisasterShip_VSP.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_VSP.function = "CreateDisasterShip_VSPirate";
				for (i=0; i<MAX_ISLANDS; i++)//устроим шторм
				{				
					if (Islands[i].id == pchar.questTemp.WPU.Current.TargetIslandID)
					{
					Islands[i].alwaysStorm = true; 
					Islands[i].storm = true;
					Islands[i].tornado = true; 
					}
				}
				pchar.questTemp.WPU.Escort.LevelUp_1VSP = "true";
			break;
			case 2://потонул
				pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
				pchar.quest.DisasterShip_S.win_condition.l1 = "location";
				pchar.quest.DisasterShip_S.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
				pchar.quest.DisasterShip_S.function = "CreateDisasterShip_Crew";
				pchar.questTemp.WPU.Escort.LevelUp_1S = "true";
			break;
		}
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "25");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		SetFunctionTimerCondition("DesIsland_Over", 0, 0, 15, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LU1WM_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Oui, j'ai déjà été informé. Excellent travail, "+GetAddress_Form(NPChar)+"! Vous avez une fois de plus prouvé que vous êtes celui sur qui je peux compter. Recevez votre récompense - 30 000 pesos.\nN'oubliez pas de me rendre visite de temps en temps - des gens comme vous sont inestimables et je trouverai toujours un travail approprié pour vous.";
		link.l1 = "Content de l'entendre, "+GetAddress_FormToNPC(NPChar)+"! Bien sûr, nous coopérerons davantage. Tout le meilleur !";
		link.l1.go = "Escort_LU1WM_complete_1";
	}
	else
	{
		dialog.text = "Je ne vois pas votre navire dans le port. Faites escale pour le moment et revenez me voir plus tard - alors nous parlerons.";
		link.l1 = "D'accord, je ferai exactement cela.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1WM_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 30000);
		ChangeCharacterComplexReputation(pchar,"nobility", 5);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 5);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 30000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Repair", 300);//починка
		AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Oui, il m'a déjà parlé de la bataille avec les pirates et de combien vous avez été héroïque en défendant son navire. Excellent travail, "+GetAddress_Form(NPChar)+"! Vous avez encore une fois prouvé que vous êtes quelqu'un sur qui je peux compter. Recevez votre récompense - 50 000 pesos.\nN'oubliez pas de me rendre visite de temps en temps - des gens comme vous sont inestimables et je trouverai toujours un travail adéquat pour vous.";
		link.l1 = "Content d'entendre ça, "+GetAddress_FormToNPC(NPChar)+" ! Bien sûr, notre collaboration se poursuivra. Cordiales salutations !";
		link.l1.go = "Escort_LU1VSP_complete_1";
	}
	else
	{
		dialog.text = "Je ne vois pas votre navire dans le port. Mettez-vous au large pour l'instant et revenez me voir plus tard - alors nous parlerons.";
		link.l1 = "D'accord, je ferai juste cela.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1VSP_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 50000);
		ChangeCharacterComplexReputation(pchar,"nobility", 10);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 6);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 50000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_completeSink":
		dialog.text = "Quelle fin tragique... Que Dieu repose leurs âmes.";
		link.l1 = "J'ai fait tout ce que je pouvais, "+GetAddress_FormToNPC(NPChar)+"La tempête a encore aggravé la situation.";
		link.l1.go = "Escort_LU1VSP_completeSink_1";
	break;
	
	case "Escort_LU1VSP_completeSink_1":
		dialog.text = "Je crois bien, "+GetAddress_Form(NPChar)+", que vous aviez entrepris tout ce que vous pouviez pour sauver le navire et ces pauvres marins. Mais hélas... Eh bien, s'il vous plaît, acceptez votre récompense - 10000 pesos - et merci pour votre service.";
		link.l1 = "Rien à me remercier pour, "+GetAddress_FormToNPC(NPChar)+"Je suis vraiment désolé. Eh bien, adieu.";
		link.l1.go = "Escort_LU1VSP_completeSink_2";
	break;
	
	case "Escort_LU1VSP_completeSink_2":
		DialogExit();
		AddMoneyToCharacter(pchar, 10000);
		ChangeCharacterComplexReputation(pchar,"nobility", 1);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 10000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(50, 50, 50, 50, 0, 0, 0);
		AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1S_complete":
		dialog.text = "Oui, il m'a déjà parlé de toi, combattant les païens à la peau rouge puis un navire pirate - comme un vrai héros. Excellent travail, "+GetAddress_Form(NPChar)+"! Vous avez encore prouvé être celui sur qui je peux compter.\nRecevez votre récompense - 40 000 pesos. N'oubliez pas de me rendre visite de temps en temps - les gens comme vous sont inestimables et je trouverai toujours un travail approprié pour vous.";
		link.l1 = "Content d'entendre cela, "+GetAddress_FormToNPC(NPChar)+" ! Bien sûr, notre collaboration se poursuivra. Meilleures salutations !";
		link.l1.go = "Escort_LU1S_complete_1";
	break;
	
	case "Escort_LU1S_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 40000);
		ChangeCharacterComplexReputation(pchar,"nobility", 8);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 3);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 40000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_2":
		dialog.text = "Je savais que je pouvais compter sur vous. Bonne chance à vous, capitaine ! Toute la colonie vous souhaite la victoire !";
		link.l1 = "Je vais essayer de répondre à vos attentes. Je vais maintenant mettre les voiles, et que Dieu nous vienne en aide!";
		link.l1.go = "Escort_LevelUp_2_go";
	break;
	
	case "Escort_LevelUp_2_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "41");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		SetFunctionTimerCondition("CaravanNearIsland_Over", 0, 0, 2, false);
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
		pchar.quest.CaravanNearIsland_Start.win_condition.l1 = "location";
		pchar.quest.CaravanNearIsland_Start.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
		pchar.quest.CaravanNearIsland_Start.function = "CreateCaravanNearIsland";
		pchar.questTemp.WPU.Escort.LevelUp_2 = "true";
		pchar.questTemp.WPU.Escort = "begin";
		DialogExit();
	break;
	
	case "Escort_LU2_complete":
		switch (sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty))
		{
			case 1:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 10000;
				dialog.text = "Oui, toute la ville a observé votre bataille. Pauvres marchands, je les plains. Eh bien, au moins vous avez réussi à sauver un navire, donc votre récompense de 10000 pesos est bien méritée. Je vous en prie, acceptez-la - et merci pour votre aide.";
				link.l1 = "Rien à me remercier... Il est regrettable que je n'aie pas remporté ce combat de manière décisive, mais j'ai fait tout ce que je pouvais. Adieu, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 2:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 25000;
				dialog.text = "Oui, toute la ville a assisté à la bataille que vous avez menée - et vous l'avez fait avec beaucoup d'habileté, je dois dire. Ce pauvre marchand, je le plains vraiment... Mais sans vous, aucun d'eux n'aurait échappé vivant, alors votre récompense de 25000 pesos est bien méritée. Veuillez l'accepter - et merci pour votre aide.";
				link.l1 = "Eh bien, merci pour cet éloge de mes actions, mais je ne pense pas que ce fût ma meilleure bataille - j'ai tout de même perdu un navire. Eh bien, la destinée est la destinée, et il n'y a rien à y faire. Adieu, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 3:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 50000;
				dialog.text = "Oui, toute la ville observait la bataille que vous meniez - vous étiez absolument magnifique ! Vous avez complètement démoli toute l'escadre de ces sales pirates ! Maintenant, ils ont appris leur leçon - dommage que ça ne leur serve plus à rien. Votre récompense s'élève à 50000 pesos - je vous prie de l'accepter.";
				link.l1 = "Merci pour cette évaluation flatteuse de mes actions ! Toujours un plaisir d'aider. Et maintenant, "+GetAddress_FormToNPC(NPChar)+"Je vous prie de bien vouloir me laisser prendre congé.";
				link.l1.go = "Escort_LU2_complete_1";
			break;
		}
	break;
	
	case "Escort_LU2_complete_1":
		iTemp = sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty);
		DialogExit();
		Group_DeleteGroup("CaravanShip");
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", iTemp*2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), iTemp);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		CloseQuestHeader("Escort");
		AddCharacterExpToSkill(pchar, "Sailing", iTemp*35);//навигация
		AddCharacterExpToSkill(pchar, "Accuracy", iTemp*50);//меткость
		AddCharacterExpToSkill(pchar, "Cannons", iTemp*50);//орудия
		AddCharacterExpToSkill(pchar, "Grappling", iTemp*35);//абордаж
		AddCharacterExpToSkill(pchar, "Leadership", iTemp*40);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", iTemp*35);//везение
		AddCharacterExpToSkill(pchar, "FencingL", iTemp*35);//лёгкое оружие
		AddCharacterExpToSkill(pchar, "FencingS", iTemp*35);//среднее оружие
		AddCharacterExpToSkill(pchar, "FencingH", iTemp*35);//тяжелое оружие
		AddCharacterExpToSkill(pchar, "Pistol", iTemp*35); //пистоли
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
		case "PortmanQuest_NF":
			dialog.text = "Hmm, c'est fâcheux. Dans ce cas, votre travail futur pour moi est hors de question.";
			link.l1 = "Compris. Voici ce que je voulais dire...";
			link.l1.go = "node_2";
		break;
		
		//сгоревшее судно
		case "BurntShip2":
			dialog.text = "Quel dommage, capitaine... C'est dommage que vous ne soyez pas disposé à m'aider.";
			link.l1 = "Ce n'est pas une question de ma volonté, mon bonhomme. Vous devez comprendre. Adieu.";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;
		
		case "BurntShip4":
			dialog.text = "Qu'est-ce qui te prend, capitaine ?! N'as-tu pas honte ?! Comment as-tu pu ?! Je connais mon affaire, je suis en service depuis de nombreuses années. Il y a des contrats d'assurance, et la compagnie d'assurance est prête à payer, et je t'assure que la somme assurée est assez convenable.";
			link.l1 = "Quel est votre problème, monsieur? Une pièce à poudre a explosé, il y a eu des victimes, et maintenant vous devez être jugé pour votre négligence?";
			link.l1.go = "BurntShip5";
		break;
		
		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");
			
			dialog.text = "Non ! Bien sûr que non ! Que le Seigneur sauve mon âme, sinon je perdrais la tête. La cale était absolument vide, merci Seigneur, la Sainte Vierge Marie !\n"+"Et le problème est que le navire appartient à... ou plutôt, appartenait à M. "+sCapitainId+", bien connue de tous les Caraïbes. Et elle a été construite en Europe sur commande spéciale, avec des caractéristiques extraordinaires. "+"Et ce propriétaire de navire était bien trop fier et se vantait à tout-va, une sorte de tête de pioche, que Dieu me pardonne... Que vais-je lui dire maintenant ? Je ferais mieux de me tuer, je le jure...";
			link.l1 = "Oh, maintenant je vois quel est le problème, en effet. Et qu'est-ce qui était si spécial à propos du navire ? Quelles caractéristiques inhabituelles avait-elle pour que son propriétaire en soit si fier ?";
			link.l1.go = "BurntShip6";
			
			NPChar.Quest.BurntShip.ShipOwnerName = sCapitainId;
		break;
		
		case "BurntShip6":
			BurntShipQuest_FillStartParams(NPChar);
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s wind speed was more than " + NPChar.Quest.BurntShip.ShipNeededValue + " knots. That was the privateer's pride... And now he'd just tell his boys to hang me in the yard. What devil has brought him to our harbor together with that pirate tub...";
				break;
				
				case "turnrate":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s maneuverability was more than " + NPChar.Quest.BurntShip.ShipNeededValue + " units. That was the soldier's pride... And now he'd just have me flogged to death. What devil advised him to leave his tub there...";
				break;
				
				case "capacity":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "' had a deadweight of over " + NPChar.Quest.BurntShip.ShipNeededValue + " units. Greed is bad, I'll tell ya. And now he'd just have me quartered in court. What devil advised him to leave his tub there...";
				break;
			}
			
			dialog.text = attrL;
			link.l1 = "Et que disent les gens au quai ? Est-il vraiment impossible d'en construire un autre ici ?";
			link.l1.go = "BurntShip7";
		break;
		
		case "BurntShip7":
			dialog.text = "Personne ne le peut. Je suis même allé sur l'île voisine pour demander aux habitants. Ils ont dit qu'il y a un maître réputé sur l'Isla Tesoro capable de réaliser presque tout en construction navale. Mais l'Isla Tesoro est sacrément loin. Tout ce qui me reste, c'est de compter sur l'aide de capitaines libres comme vous. Peut-être que vous arriverez à trouver un tel navire pour moi. Et je m'occuperai du reste\n"+"Je vous remercierai généreusement, et la compagnie d'assurance fera de même, également. L'affaire est inhabituelle, vous savez. Qui voudrait jamais contrarier un homme aussi puissant ?";
			link.l1 = "Oui, cela ne va pas être facile. Et combien de temps ai-je?";
			link.l1.go = "BurntShip8";
			link.l2 = "Non, l'ami, je ne peux pas être impliqué dans une telle affaire. Sans parler du fait qu'il n'y a aucune garantie qu'un navire avec de tels paramètres existe réellement. Je suis désolé...";
			link.l2.go = "BurntShip2";
		break;
		
		case "BurntShip8":
			dialog.text = "Dieu merci, il y a encore du temps. Le propriétaire est parti pour l'Europe et ne reviendra pas avant au moins six mois.";
			link.l1 = "Eh bien, je suppose que je vais m'en occuper. Je vous apporterai un navire similaire. Mais gardez cela à l'esprit - si vous choisissez d'être trop avare, je le brûlerai juste devant vos yeux !";
			link.l1.go = "BurntShip9";
		break;
		
		case "BurntShip9":
			dialog.text = "Que sous-entendez-vous, capitaine ? Certes, je comprends que vous ayez besoin de temps - il ne s'agit pas de trouver une barcasse quelconque dans la flaque la plus proche... Apportez-nous simplement le navire et nous ferons de notre mieux, vous pouvez compter là-dessus...";
			link.l1 = "J'espère bien... Eh bien, attends-moi et de bonnes nouvelles. Adieu.";
			link.l1.go = "BurntShip9_exit";
		break;
		
		case "BurntShip9_exit":
			attrL = "BurntShipQuest_TimeIsOver_" + NPChar.Id;
			PChar.Quest.(attrL).win_condition.l1 = "Timer";
			PChar.Quest.(attrL).win_condition.l1.date.day = GetAddingDataDay(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.month = GetAddingDataMonth(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.year = GetAddingDataYear(0, 6, 0);
			PChar.Quest.(attrL).function = "BurntShipQuest_TimeIsOver";
			PChar.Quest.(attrL).PortmanId = NPChar.id;
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "speed. The wind speed of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " must be at least " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "turnrate":
					attrL = "manoeuvrability. Manoeuvrability of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " must be no less than " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "capacity":
					attrL = "hold. Hold of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " has to be no less than " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
			}
			
			sTitle = "BurntShipQuest" + NPChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "BurntShipQuest", "1");
			AddQuestUserDataForTitle(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Dat"));
			AddQuestUserData(sTitle, "portmanName", GetFullName(NPChar));
			AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Gen"));
			AddQuestUserData(sTitle, "text", attrL);
			
			NPChar.Quest.BurntShip.LastPortmanName = GetFullName(NPChar); // Запомнм имя
			
			DialogExit();
		break;
		
		// Вариант, когда не уложились в сроки
		case "BurntShip10":
			dialog.text = "De quoi vouliez-vous parler ?";
			link.l1 = "Et où se trouve l'ancien maître de port, monsieur "+NPChar.Quest.BurntShip.LastPortmanName+" ? J'ai affaire avec lui.";
			link.l1.go = "BurntShip11";
		break;
		
		case "BurntShip11":
			dialog.text = "Il n'est plus dans les parages. Imaginez - il a incendié un navire appartenant à une personne bien connue et a empoché l'argent de l'assurance. Pendant que les autorités démêlaient tout cela, il a démissionné et s'est éclipsé en Europe. Quel filou, n'est-ce pas ?";
			link.l1 = "Oui, j'ai entendu cette histoire. Je suis désolé, mais je dois y aller.";
			link.l1.go = "BurntShip11_exit";
		break;
		
		case "BurntShip11_exit":
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "2");
			AddQuestUserData(sTitle, "portmanName", NPChar.Quest.BurntShip.LastPortmanName);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		// Не просрочено - проверяем корабль
		case "BurntShip12":
			dialog.text = "De quoi voulais-tu parler ?";
			link.l1 = "Je t'ai amené un navire inhabituel, exactement comme tu l'avais demandé. J'attends maintenant ma récompense.";
			link.l1.go = "BurntShip14";
			link.l2 = "Tu sais, "+GetFullName(NPChar)+", je n'ai toujours pas trouvé un seul navire correspondant à ce dont vous avez besoin. Je suppose que je vais abandonner ce travail. Désolé si je vous ai laissé tomber...";
			link.l2.go = "BurntShip13";
		break;
		
		case "BurntShip13":
			dialog.text = "Quel dommage, capitaine... C'est dommage que vous ne soyez pas disposé à m'aider.";
			link.l1 = "Ce n'est pas une question de volonté, mon brave. Je vous en prie, comprenez. Adieu.";
			link.l1.go = "BurntShip13_exit";
		break;
		
		case "BurntShip13_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip14":
			dialog.text = "Oh, vraiment ! Et quel est le nom de notre nouveau navire ?";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip15";
						}
					}
				}
			}
			
			link.l99 = "Excusez-moi, je reviendrai plus tard.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Oh, capitaine, je suis si heureux que vous ne m'ayez pas laissé tomber ! Quel "+GetSexPhrase("jeune homme de bien","jeune dame de qualité")+" vous êtes là, vous m'avez littéralement sauvé la vie... S'il vous plaît, pourriez-vous venir récupérer votre argent dans quelques jours ? Vous savez, je dois régler les formalités avec l'assurance... En attendant, vous pourriez faire quelques réparations mineures au navire - vous savez, renouveler les voiles, boucher les trous, un carénage ne ferait pas de mal non plus...";
			link.l99 = "J'ai promis de faire quelque chose de méchant au navire si tu essaies de me duper. As-tu oublié ?";
			link.l99.go = "BurntShip16";
		break;
		
		case "BurntShip16":
			dialog.text = "Non, non, bien sûr que non ! Je resterai fidèle à ma parole, ne vous inquiétez pas. Vous voyez, sachant qu'il y aura plus de dépenses pour, disons, déguiser le nouveau navire, j'ai prêté l'argent de l'assurance que j'ai reçu pour l'ancien navire avec intérêt. J'espère que vous comprenez...";
			link.l1 = "Je comprendrai bien mieux quand l'argent arrivera dans mon coffre. Jusqu'à notre prochaine rencontre.";
			link.l1.go = "BurntShip16_exit";
		break;
		
		case "BurntShip16_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "3");
			
			NPChar.Quest.BurntShip.TwoDaysWait = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Quest.BurntShip.TwoDaysWait"); // Запомним дату
			
			sTitle = "BurntShipQuest" + NPChar.Id;
			PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время
			
			DialogExit();
		break;
		
		case "BurntShip17":
			dialog.text = "De quoi vouliez-vous parler ?";
			link.l1 = "Je suis venu chercher ma récompense. J'ai toujours le navire dont vous avez besoin.";
			link.l1.go = "BurntShip18";
		break;
		
		case "BurntShip18":
			dialog.text = "Pourriez-vous me rappeler son nom, s'il vous plaît ? Ma mémoire n'est plus ce qu'elle était - vous savez, avec tout ce tracas...";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip19_" + i;
						}
					}
				}
			}
			
			link.l99 = "Excusez-moi, je reviendrai plus tard.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 3;
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3;
			
			dialog.text = "Oui, parfait. Je suis prêt à vous remettre votre récompense, "+FindRussianMoneyString(cn)+"Voilà comment la compagnie d'assurance a évalué la valeur du navire brûlé. La somme d'assurance est payée en coffres de crédit - pas de liquide, désolé.";
			link.l1 = "Oh non, ce montant ne me convient pas. Je suis sûr que ce navire vaut bien plus cher.";
			link.l1.go = "BurntShip21";
			link.l2 = "C'est exact. Je suis content d'avoir pu vous aider. À bientôt.";
			link.l2.go = "BurntShip20_exit";
			NPChar.Quest.BurntShip.Money = cn;
		break;
		
		case "BurntShip20_exit":
			TakeNItems(pchar, "chest", makeint(sti(NPChar.Quest.BurntShip.Money)/12000));
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip21":
			dialog.text = "Que dites-vous, capitaine ?! Croyez-moi, je sais de quoi je parle. Cet argent vous permettrait d'acheter deux navires comme celui-là !";
			link.l1 = "Je suppose que je vais le garder. Vous savez, je m'y suis attaché... Adieu.";
			link.l1.go = "BurntShip21_exit";
		break;
		
		case "BurntShip21_exit":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "5");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		//--> миниквесты портмана
		case "PortmanQuest":
			if (hRand(5) == 2)
			{	//квест догнать и передать судовой журнал
				dialog.text = "Un des capitaines a oublié son journal de bord dans mon bureau. Quel écervelé ! J'ai besoin que tu le rattrapes et que tu le lui rendes.";
				link.l1 = "Oh, ça va être facile... Je prends ça !";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "Non, je ne m'occuperai pas de cela. C'est son propre problème, en fait.";
				link.l2.go = "node_2";
			}
			else
			{	//квест разыскать украденный корабль
				dialog.text = "Un navire a été volé à l'amarrage là-bas. Je veux que vous retrouviez le vaisseau volé et que vous le rameniez.";
				link.l1 = "Hmm, eh bien, je suis prêt à me lancer dans l'enquête.";
				link.l1.go = "SeekShip_1";
				link.l2 = "Je suis désolé mais je ne m'engage pas à rechercher des navires volés.";
				link.l2.go = "node_2";
			}
		break;
//-------------------------------- квест доставки судового журнала до рассеяного кэпа ---------------------
		case "PortmanQuest_1":
			dialog.text = "Excellent, voici son journal de bord... Tu m'as vraiment enlevé un poids de l'esprit ! La perte d'un journal de bord est une chose très désagréable. J'ai toujours eu pitié de ces capitaines...";
			link.l1 = "Eh bien, c'est vraiment quelque chose qui doit nous inquiéter ! Maintenant, parlez-moi davantage de ce capitaine distrait.";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "Oui, bien sûr ! Son nom est "+npchar.quest.PortmansJornal.capName+", c'est un capitaine de "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName+"Gén"))+" nommé '"+npchar.quest.PortmansJornal.shipName+"'. Il a mis les voiles il n'y a pas longtemps et s'est dirigé vers "+XI_ConvertString("Colony"+npchar.quest.PortmansJornal.city+"Acc")+".";
			link.l1 = "Je vois. D'accord, je vais le trouver. Maintenant, qu'en est-il du paiement ?";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName+" lui-même vous paiera, c'est dans son intérêt. Concentrez-vous simplement sur le fait de l'atteindre dès que possible et tout ira bien.";
			link.l1 = "Je vois. Eh bien, je vais y aller, alors...";
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandByCityName(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(npchar.quest.PortmansJornal.city) + "Dat"));
			}			
		break;
		// -------------------------------- квест розыска украденного корабля ----------------------------------
		case "SeekShip_1":
			dialog.text = "Excellent ! Vous savez, le navire volé appartient à une personne influente, donc c'est très important pour moi. Je vous paierai généreusement pour ce travail...";
			link.l1 = "Je vois. Parlez-moi davantage du navire et des circonstances dans lesquelles il a été volé.";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)+" du nom de '"+npchar.quest.PortmansSeekShip.shipName+"' a été volé pendant la nuit "+FindRussianDaysString(rand(5)+10)+" il y a. Le guet a été tué.";
			link.l1 = "Hmm... Ils doivent être loin maintenant. La piste n'est plus fraîche et c'est là le problème.";
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = "Vrai, mais je n'ai toujours pas vu l'intérêt de donner l'alarme immédiatement. Le navire militaire aurait pu les rattraper, mais il aurait juste réduit le navire en pièces - et ce n'est pas exactement ce dont j'ai besoin.";
			link.l1 = "Je vois. Eh bien, je vais commencer mes recherches. J'espère avoir de la chance.";
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName+"Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;

		case "SeekShip_break":
			dialog.text = "Quel dommage - mais nous ne pouvions guère compter sur le succès.";
			link.l1 = "Oui, cela fait trop longtemps que le navire a été volé.";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "Eh bien, merci pour votre aide de toute façon, même si vos efforts n'ont pas été aussi fructueux que nous l'espérions.";
			link.l1 = "J'ai fait tout ce que je pouvais...";
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//если кэп-вор еще жив - убираем его
			if (cn > 0)
			{
				characters[cn].LifeDay = 0; 
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
			ChangeCharacterComplexReputation(pchar,"nobility", -7);
		break;	

		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				dialog.text = "Excellent ! Bien que je soupçonne que ce n'est pas exactement le navire qui a été volé... Oh, peu importe ! Je le prends.";
				link.l1 = "Oui, en effet...";
				//npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //снижаем оплату
				ChangeCharacterComplexReputation(pchar,"nobility", 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
                AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				dialog.text = "Excellent ! Vous m'avez beaucoup aidé. Je n'imagine pas à quel point cela a dû être difficile.";
				link.l1 = "Oui, en effet...";
				ChangeCharacterComplexReputation(pchar,"nobility", 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
                AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "Je suis prêt à vous payer votre récompense. Elle se compose de "+FindRussianMoneyString(makeint(sti(npchar.quest.chest)*15000))+"  dans des coffres. Malheureusement, je ne peux pas te payer plus que ça.";
			link.l1 = "Eh bien, cela suffit. Merci et chaleureuses salutations.";
			link.l1.go = "exit";
			TakeNItems(pchar, "chest", sti(npchar.quest.chest));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		break;

		//------------------------------> инфа по базе квествых кэпов
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery  #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		//ПРИМЕР: в конце метода  void SetCapitainFromCityToSea(string qName)
		case "CapitainList":
			if (sti(npchar.quest.qty) > 0)
			{
				dialog.text = "Il y a plusieurs capitaines enregistrés. Vous intéressez-vous à quelqu'un en particulier ?";
				makearef(arCapBase, npchar.quest.capitainsList); 
				for (i=0; i<sti(npchar.quest.qty); i++)
				{
    				arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = GetFullName(sld) + ", captain of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Gen")) + " '" + sld.Ship.name + "'.";
					link.(attrL).go = "CapList_"+attrL;
				}
			}
			else
			{
				dialog.text = "Je n'ai aucun capitaine sur ma liste qui pourrait vous intéresser.";
				link.l1 = "Je vois. Eh bien, merci pour l'information.";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Eh bien, voyons voir... A-ha! Là! ","Ah-ha... A-ha! Là! ","D'accord, alors. ")+"Capitaine "+GetFullName(sld)+" "+arCapLocal.date+"année a quitté notre port et a navigué vers "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Merci. Je voudrais revoir la liste encore une fois...";
			link.l1.go = "CapitainList";
			link.l2 = "Très bien, c'est tout. Je ne suis pas intéressé par un autre capitaine.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l1":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  1);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Eh bien, voyons voir... Ah-ha ! Là !","Ah-ha... A-ha! Là! ","D'accord, alors. ")+"Capitaine "+GetFullName(sld)+" "+arCapLocal.date+" annee a quitté notre port et a navigué vers "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Merci. J'aimerais revoir la liste à nouveau...";
			link.l1.go = "CapitainList";
			link.l2 = "D'accord, c'est tout. Je ne suis pas intéressé par d'autres capitaines.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l2":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  2);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Eh bien, voyons voir... A-ha! Là! ","Ah-ha... A-ha! Là! ","D'accord, alors. ")+"Capitaine "+GetFullName(sld)+" "+arCapLocal.date+"année a quitté notre port et a navigué vers "+XI_ConvertString("Colonie"+arCapLocal+"Accord")+".";
			link.l1 = "Merci. J'aimerais revoir la liste encore une fois...";
			link.l1.go = "CapitainList";
			link.l2 = "Très bien, c'est tout. Je ne suis pas intéressé par d'autres capitaines.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l3":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  3);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Eh bien, voyons voir... Ah-ha ! Là !","Ah-ha... A-ha! Là ! ","D'accord, alors. ")+"Capitaine "+GetFullName(sld)+" "+arCapLocal.date+" année a quitté notre port et a navigué vers "+XI_ConvertString("Colonie"+arCapLocal+"Acc")+".";
			link.l1 = "Merci. J'aimerais revoir la liste à nouveau...";
			link.l1.go = "CapitainList";
			link.l2 = "Bien, c'est tout. Je ne suis pas intéressé par d'autres capitaines.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l4":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  4);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Eh bien, voyons voir... Ah-ha ! Là !","Ah-ha... A-ha ! Là ! ","Très bien, alors. ")+"Capitaine "+GetFullName(sld)+" "+arCapLocal.date+" annee a quitte notre port et a navigue vers "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Merci. Je voudrais revoir la liste encore une fois...";
			link.l1.go = "CapitainList";
			link.l2 = "D'accord, c'est tout. Je ne suis pas intéressé par un autre capitaine.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobTakeShip" && !CheckAttribute(npchar, "quest.HWICHoll"))
			{
			dialog.text = "Je vous écoute - quel navire, pour quelle durée ?";
    		Link.l1 = "Lucas Rodenburg m'a envoyé. Il a dit que je peux amarrer mon navire ici gratuitement.";
    		Link.l1.go = "ShipStock_HWICHoll";
			DelLandQuestMark(npchar);
			break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoPortoffice" && !CheckAttribute(npchar, "quest.HWICEng"))
			{
			dialog.text = "Je vous écoute - quel navire, pour quelle durée ?";
    		Link.l1 = "Richard Fleetwood m'a envoyé. Il a dit que je peux amarrer mon navire amiral ici pour 10000 pesos.";
    		Link.l1.go = "ShipStock_HWICEng";
			break;
			}
            if (sti(NPChar.Portman) >= 3 || CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip"))
			{
                dialog.text = "Eh bien, c'est exact. Mais malheureusement, je ne peux pas accepter votre navire pour l'instant. Pas de place au quai disponible.";
    			Link.l1 = "C'est dommage.";
    			Link.l1.go = "exit";
			}
            else
            {
    			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "Et quel navire en particulier allez-vous laisser ici ?";
	    			for(i=1; i<COMPANION_MAX; i++)
					{
						cn = GetCompanionIndex(PChar, i);
						if(cn > 0)
						{ // hasert со сторожем.
							chref = GetCharacter(cn);
							if (!GetRemovable(chref)) continue;							
							attrL = "l"+i+COMPANION_MAX;
							Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockMan22_" + i;

						}
					}
	    			Link.l17 = "Peu importe, merci.";
	    			Link.l17.go = "exit";
    			}
    			else
    			{
					dialog.text = "Hmm... Je ne vois aucun de vos navires.";
	    			Link.l1 = "Je voulais juste savoir s'il était possible d'accoster.";
	    			Link.l1.go = "exit";
				}
			}
		break;

/*  //////////   hasert уже не надо но пусть висит ////////////////////////////////////
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Jetons un oeil à ce navire.";
			Link.l1 = "D'accord.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Non, j'ai changé d'avis.";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Jetons un oeil à ce navire.";
			Link.l1 = "Très bien.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Non, j'ai changé d'avis.";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Jetons un oeil à ce navire.";
			Link.l1 = "Très bien.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Non, j'ai changé d'avis.";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Jetons un oeil à ce navire.";
			Link.l1 = "D'accord.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Non, j'ai changé d'avis.";
			Link.l2.go = "exit";
		break;
*/		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if (MOD_SKILL_ENEMY_RATE >= 6) NPChar.MoneyForShip = 5*GetPortManPriceExt(NPChar, chref); // для высокой сложности - 5x цена
			else NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
			dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName)+" ' "+chref.Ship.Name+", classe "+RealShips[sti(chref.Ship.Type)].Class+", le coût d'amarrage est "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+" par mois, paiement d'un mois à l'avance.";
			Link.l1 = "Oui, cela me convient.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			{
			    Link.l1.go = "ShipStock_3";
			}
			else
			{
                Link.l1.go = "ShipStock_NoMoney";
			}
			Link.l2 = "Non, j'ai changé d'avis.";
			Link.l2.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "Et cela me conviendra aussi, dès que vous aurez réuni le montant requis.";
			Link.l1 = "Zut... Je reviendrai plus tard.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3": // hasert новый кейс выбора для оффов
			//AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
			if (sti(NPChar.StoreWithOff))
			{
				AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.ShipInStockMan = NPChar.id;
			// Warship 22.03.09 fix Не перенеслось с КВЛ 1.2.3
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
			chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
			SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчёта
			chref.Ship.Crew.Quantity  = 0;
			RemoveCharacterCompanion(pchar, chref);
			}
			else
			{
				AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
			chref = GetCharacter(NPC_GenerateCharacter("ShipInStockMan_", "citiz_"+(rand(9)+31), "man", "man", 1, NPChar.nation, -1, false, "quest"));
			chref.id = "ShipInStockMan_" + chref.index; //меняем ID на оригинальный
			chref.loyality = MAX_LOYALITY; 
			chref.name = "";
			chref.lastname = "";
			 chref.Ship.Crew.Quantity  = 0;
			DeleteAttribute(chref,"ship");
			chref.ship = "";
			
			chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
			chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
			SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчёта
			//  chref.Ship.Crew.Quantity  = 0;
			compref = GetCharacter(sti(NPChar.ShipToStoreIdx));//компаньон, у которого надо забрать корабль
			compref.Ship.Crew.Quantity  = 0;
            RemoveCharacterCompanion(pchar, compref);
			makearef(arTo, chref.ship);
			makearef(arFrom, compref.Ship);
			CopyAttributes(arTo, arFrom);

			compref.ship.type = SHIP_NOTUSED;
			RemoveCharacterCompanion(pchar, compref);
			AddPassenger(pchar, compref, false);
			DelBakSkill(compref);
			}

			chref.location = "";
			chref.location.group = "";
			chref.location.locator = "";
			NPChar.Portman	= sti(NPChar.Portman) + 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) + 1;

			dialog.text = "D'accord. Vous pouvez reprendre votre navire quand vous le souhaitez.";
			Link.l1 = "Merci.";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
            ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	            {
	                dialog.text = "Laquelle de ces navires allez-vous prendre ?";
	                cn = 1;
	                for(i=1; i<MAX_CHARACTERS; i++)
					{
						makeref(chref, Characters[i]);
						if (CheckAttribute(chref, "ShipInStockMan"))
						{    
							if (chref.ShipInStockMan == NPChar.id)
							{
								attrL = "l"+cn;
								if(HasSubStr(chref.id, "ShipInStockMan_"))											  
								{ 
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
								Link.(attrL).go = "ShipStockManBack22_" + i; 
								}
								else
								{  
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "' and my officer " + GetFullName(chref) + ".";
								Link.(attrL).go = "ShipStockManBack11_" + i;
								}
								cn++;
							}
						}
					}
	
	    			Link.l99 = "Non, j'ai changé d'avis.";
	    			Link.l99.go = "exit";
				}
				else
				{
	                dialog.text = "Avez-vous de la place pour un autre navire ?";
	    			Link.l1 = "Oh, d'accord. Merci.";
	    			Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm. Je ne vois pas votre navire amiral dans le port. Et vous ne pouvez reprendre vos navires qu'ici.";
    			Link.l1 = "D'accord, je viendrai les chercher plus tard.";
    			Link.l1.go = "exit";
			}
		break;

        case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
			if (CheckAttribute(chref, "quest.Mutiny.date")) {
				dialog.text = "Voyons voir... Ce navire a quitté le port à "+chref.quest.Mutiny.date+".";
				link.l1 = "Comment ça 'partie'? Elle doit être ici, sur les quais !";
				link.l1.go = "ShipStockManMutiny";
				break;
			}
			// <--
            NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);
			if (sti(NPChar.MoneyForShip) > 0)
			{
			    dialog.Text = "Tu veux récupérer ton navire ? Pour l'amarrage, tu dois encore "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+".";
			}
			else
			{
				dialog.Text = "Vous venez chercher?";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "Oui.";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "Non, j'ai changé d'avis.";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockManBack2": // hasert новый кейс для сторожа.
			if (sti(NPChar.StoreWithOff))
			{   
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));

			NPChar.Portman	= sti(NPChar.Portman) - 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			}
			else
			{   
			dialog.Text = "Lequel de vos officiers devrais-je remettre ceci?";
			int _curCharIdx;
			int q = 0;
			int nListSize = GetPassengersQuantity(pchar);
			for(i=0; i<nListSize; i++)
				{
				_curCharIdx = GetPassenger(pchar,i);
				sld = GetCharacter(_curCharIdx);
					if (_curCharIdx!=-1)
					{
						ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;

						if (!CheckAttribute(sld, "CompanionDisable"))
					    {
							if (!ok && GetRemovable(&characters[_curCharIdx]))
							{
								attrL = "l"+i;
								sProf = "";
								if (IsOfficer(sld)) sProf += " (vanguard)";
								if (sti(pchar.Fellows.Passengers.navigator) == sti(sld.index)) sProf += " (navigator)";
								if (sti(pchar.Fellows.Passengers.boatswain) == sti(sld.index)) sProf += " (boatswain)";
								if (sti(pchar.Fellows.Passengers.cannoner) == sti(sld.index)) sProf += " (cannoneer)";
								if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index)) sProf += " (surgeon)";
								if (sti(pchar.Fellows.Passengers.carpenter) == sti(sld.index)) sProf += " (carpenter)";
							    if (sti(pchar.Fellows.Passengers.treasurer) == sti(sld.index)) sProf += " (purser)";
								Link.(attrL)	= GetFullName(&characters[_curCharIdx]) + sProf;
								Link.(attrL).go = "ShipStockManBack2_" + i;
								q++;
							}
						}
					}
				}
			attrL = "l"+nListSize;
			if (q == 0)
				{
				Link.(attrL) = RandSwear() + "I forgot to bring an officer with me for this ship.";
				Link.(attrL).go = "exit";
				}
			else
				{
				Link.(attrL) = "No, I've changed my mind..";
				Link.(attrL).go = "exit";
				}
			}
		break;
		
		//--> Jason Голландский гамбит
		case "ShipStock_HWICHoll":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Oui, oui, je sais. Mais je ne peux accepter qu'un seul navire pour l'amarrage gratuit. Alors, je vous prie, réglez les choses avec votre escadre et revenez ensuite.";
				link.l1 = "D'accord, je n'apporterai que le navire amiral.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Oui, oui, je sais. Par ordre de monsieur Rodenburg, nous acceptons votre navire pour l'entreposage et nous fournirons un officier de garde pendant toute la durée de votre séjour ici. Veuillez signer ici... et ici...";
				link.l1 = "D'accord... Je comprends que toutes les formalités sont maintenant réglées ?";
				link.l1.go = "ShipStock_HWICHoll_1";	
			}
		break;
		
		case "ShipStock_HWICHoll_1":
			dialog.text = "Oui. Vous n'avez plus à vous inquiéter pour votre navire - nous allons nous en occuper. Vous pouvez retourner chez mynheer Rodenburg.";
			link.l1 = "Merci. Au revoir.";
			link.l1.go = "exit";	
			npchar.quest.HWICHoll = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "ShipStock_HWICEng":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Oui, oui, je sais. Mais je ne peux accepter qu'un seul navire pour l'amarrage gratuit. Alors, je vous prie, réglez les affaires avec votre escadron puis revenez.";
				link.l1 = "D'accord, je n'apporterai que le navire amiral.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Oui, bien sûr. Avez-vous l'argent sur vous ?";
				if(makeint(Pchar.money) >= 10000)
				{
					link.l1 = "Bien sûr. Voilà.";
					link.l1.go = "ShipStock_HWICEng_1";	
				}
				else
				{
					link.l1 = "Non. Je reviendrai dans un instant.";
					link.l1.go = "exit";	
				}
			}
		break;
		
		case "ShipStock_HWICEng_1":
			dialog.text = "D'accord. Nous prendrons soin de votre navire et fournirons un officier de quart durant tout le temps que votre bateau restera ici.";
			link.l1 = "Merci !";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -10000);
			npchar.quest.HWICEng = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Fleetwood"), "questmarkmain");
		break;
		//<-- Голландский гамбит
		case "Escort_companion":
			dialog.text = "Vouliez-vous quelque chose, capitaine ?";
			link.l1 = "Non, rien.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Escort_companion";
		break;
		
		// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
		case "ShipStockManMutiny":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			dialog.text = "Votre officier "+GetFullName(chref)+"informé"+NPCharSexPhrase(chref,"I understand. Please provide the text you would like translated."," ")+" moi cela "+NPCharSexPhrase(chref,"il","elle")+" a dû prendre la mer sur votre ordre. Je ne me suis pas opposé "+NPCharSexPhrase(chref,"lui","elle")+".";
			link.l1 = "Merde! Il n'y avait pas un tel ordre! Je n'aurais pas dû confier mon navire à ce salaud! Eh, peu importe, je ne peux rien faire pour ma perte de toute façon.";
			link.l1.go = "ShipStockManMutiny1";
			// вот тут можно микроквестик сделать
			//link.l2 = "Quelle surprise... Avez-vous "+NPCharSexPhrase(chref,"il","elle")+" te dire, où ils sont allés, par hasard ?";
			//link.l2.go = "ShipStockManMutiny2";
		break;
		
		case "ShipStockManMutiny1":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.lifeday = 0;

			dialog.text = "Je suis désolé, "+GetAddress_Form(NPChar)+" . Vous devriez être plus prudent avec vos subordonnés.";
			link.l1 = "Je sais, je suis un idiot. Adieu, "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
		break;
		// <--
		
		// уникальные корабли и легендарные капитаны -->
		case "UniqueShips":
			dialog.text = "Les navires uniques et les individus qui leur sont confiés ne peuvent passer inaperçus dans l'archipel. Cependant, cette information a une valeur considérable et n'est pas donnée à la légère.";
			if (sti(pchar.Money) >= 25000)
			{
				link.l1 = "Je comprends. La somme de 25000 pesos suffirait-elle à démontrer mes intentions sincères ?";
				link.l1.go = "UniqueShips_2";
			}
			else
			{
				link.l1 = "D'accord, alors une autre fois.";
				link.l1.go = "node_2";
			}
		break;
		
		case "UniqueShips_2":
			dialog.text = "En effet, cela serait acceptable. Quel navire précis vous intéresse-t-il?";
			if (GetDLCenabled(DLC_APPID_4) && !CheckAttribute(pchar, "questTemp.SantaMisericordia_InfoPU") && CharacterIsAlive("SantaMisericordia_cap"))
			{
				link.l1 = "Galion 'Sainte Miséricorde'.";
				link.l1.go = "UniqueShips_SantaMisericordia";
			}
			if (GetDLCenabled(DLC_APPID_5) && !CheckAttribute(pchar, "questTemp.LadyBeth_InfoPU") && CharacterIsAlive("LadyBeth_cap"))
			{
				link.l2 = "Senau de patrouille 'Lady Beth'.";
				link.l2.go = "UniqueShips_LadyBeth";
			}
			link.l99 = "Je pense que j'en sais assez.";
			link.l99.go = "node_2";
		break;
		
		case "UniqueShips_SantaMisericordia":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "1");
			pchar.questTemp.SantaMisericordia_InfoPU = true;
			dialog.text = "Sainte Miséricorde a été envoyée par l'Escorial d'Europe pour superviser les colonies espagnoles. Son capitaine, Don Alamida, est un serviteur renommé de la couronne espagnole, un combattant impitoyable contre la corruption et le crime, et un zélote de la foi catholique. Sainte Miséricorde navigue entre les colonies, commençant et terminant son voyage à La Havane, se concentrant uniquement sur sa mission.\nDans chaque port, Alamida passe plusieurs jours, parfois plus. On dit que pendant ces périodes, il peut même être rencontré dans la rue, mais les habitants ne sont pas particulièrement désireux de telles rencontres - en Espagnols, le señor inspire seulement peur et révérence.\nSainte Miséricorde a un équipage expérimenté et loyal, personnellement sélectionné par Alamida. Chaque marin est prêt à défendre leur Patrie et capitaine avec leur vie. On dit que Don Fernando a ordonné que Sainte Miséricorde ne doit jamais être capturée, et il se murmure que si l'équipage devait faire face à des chances insurmontables lors d'un abordage, ils préfèreraient envoyer le navire par le fond plutôt que de la voir abordée.";
			link.l1 = "Merci beaucoup.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_LadyBeth":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "2");
			pchar.questTemp.LadyBeth_InfoPU = true;
			dialog.text = "'Lady Beth' est une vraie beauté. Un chef-d'oeuvre du génie naval britannique, sous le commandement d'Albert Blackwood, ancien officier de la Royal Navy. Peu de gens réussissent une telle désertion avec autant d'éclat ! Il a quitté le service, ruiné une brillante carrière et volé un navire de guerre - tout ça pour chasser des trésors !\nEt il a eu raison. Il en a déjà trouvé assez pour acheter la moitié de la Barbade, mais cela ne lui suffit jamais. Si vous le croisez en mer - n'essayez même pas de l'intercepter. Son navire est excellent, et le capitaine est expérimenté et prudent. Dernièrement, Blackwood fréquente souvent les Caïmans - il y creuse jour et nuit, épuisant ses hommes jusqu'à la mort\nSi vous décidez d'enquêter - prenez au moins 60 hommes et de bonnes armes à feu... Cela pourrait ne pas suffire.J'espère que vous savez tirer, car une compagnie d'anciens marines du colonel Fox a déserté avec lui. Des professionnels, bien supérieurs aux simples bandits. Et ne l'attaquez jamais dans les ports français - il y a des protections et des mécènes qui partagent ses découvertes.";
			link.l1 = "Merci beaucoup.";
			link.l1.go = "node_2";
		break;
		
		// уникальные корабли и легендарные капитаны <--
	}
}

float BurntShipQuest_GetMaxNeededValue(int iShipType, string _param)
{
	float NeededValue = makefloat(GetBaseShipParamFromType(iShipType, _param));
	switch (_param)
	{
		case "speedrate":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/10.0)); 
		break;
		case "turnrate":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/10.0)); 
		break;
		case "capacity":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/8.0)); 
		break;
	}
	return NeededValue;
}

// Warship 25.07.09 Генер "A burnt vessel". Начальные иниты для портмана - тип разыскиваемого судна, выдающаяся характеристика и т.д.
void BurntShipQuest_FillStartParams(ref _npchar)
{
	int rank = sti(PChar.rank);
	int shipType, temp;
	float neededValue;
	String shipAttribute;
	
	// TODO Пересмотреть зависимость от ранга
	if(rank <= 5)
	{
		shipType = SHIP_LUGGER + rand(1);
		
		switch(shipType)
		{
			case SHIP_LUGGER:
				shipAttribute = "speedrate";
			break;
			
			case SHIP_SLOOP:
				temp = rand(2);
				
				if(temp == 2)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
		}
	}
	
	if(rank > 5 && rank <= 15)
	{
		shipType = SHIP_SCHOONER + rand(2);
		
		switch(shipType)
		{
			case SHIP_SCHOONER:
				if(rand(1) == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_BARKENTINE:
				shipAttribute = "capacity";
			break;
			
			case SHIP_SHNYAVA:
				shipAttribute = "capacity";
			break;
		}
	}
	
	if(rank > 15 && rank <= 25)
	{
		shipType = SHIP_FLEUT + rand(3);
		
		switch(shipType)
		{
			case SHIP_FLEUT:
				shipAttribute = "turnrate";
			break;
			
			case SHIP_CARAVEL:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_PINNACE:
				shipAttribute = "capacity";
			break;
			
			case SHIP_BRIGANTINE:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
		}
	}
	
	if(rank > 25 && rank <= 35)
	{
		shipType = SHIP_SCHOONER_W + rand(2);
		
		switch(shipType)
		{
			case SHIP_SCHOONER_W:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_GALEON_L:
				shipAttribute = "capacity";
			break;
			
			case SHIP_CORVETTE:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
		}
	}
	
	if(rank > 35)
	{
		shipType = SHIP_GALEON_H + rand(1);
		
		switch(shipType)
		{
			case SHIP_GALEON_H:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
			
			case SHIP_FRIGATE:
				shipAttribute = "turnrate";
			break;
		}
	}
	
	neededValue = BurntShipQuest_GetMaxNeededValue(shipType, shipAttribute);
	
	Log_TestInfo("shipType == " + shipType);
	Log_TestInfo("ShipAttribute == " + shipAttribute);
	Log_TestInfo("ShipNeededValue == " + neededValue);
	
	_npchar.Quest.BurntShip.ShipType = shipType;
	_npchar.Quest.BurntShip.ShipAttribute = shipAttribute;
	
	if(shipAttribute != "capacity") // Чтобы трюм с десятичными не писался
	{
		_npchar.Quest.BurntShip.ShipNeededValue = FloatToString(neededValue, 2);
	}
	else
	{
		_npchar.Quest.BurntShip.ShipNeededValue = MakeInt(neededValue);
	}
}

void SetJornalCapParam(ref npchar)
{
	//созадем рассеянного кэпа
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true, "citizen"));
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	SetCaptanModelByEncType(sld, "trade");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//в морскую группу кэпа
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansJornal"; //личный флаг квеста для портмана
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //имя кэпа
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //имя корабля
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название корабля
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //определим колонию, куда ушел кэп
	sld.quest = "InMap"; //личный флаг рассеянного кэпа
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //продублируем колонию-цель в структуру кэпа
	sld.quest.firstCity = npchar.city; //капитану знать откуда вышел в самом начале
	sld.quest.stepsQty = 1; //количество выходов в море
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 150) + (sti(pchar.rank)*150); //вознаграждение
	Log_TestInfo("The absent-minded cap " + sld.id + " went to: " + sld.quest.targetCity);
	//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " '" + npchar.quest.PortmansJornal.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
//проверить список отметившихся квестовых кэпов
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
    makearef(arCapBase, npchar.quest.capitainsList);
    int	Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId; 
	for (int i=0; i<Qty; i++)
    {
    	arCapLocal = GetAttributeN(arCapBase, i);
        sCapitainId = GetAttributeName(arCapLocal);
    	if (GetCharacterIndex(sCapitainId) > 0) //если еще жив
    	{
			bResult++;			
    	}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
    }
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//создаем кэпа-вора
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true, "soldier"));
	SetSeekCapShip(sld);
	sld.Ship.Mode = "pirate";
	SetCaptanModelByEncType(sld, "pirate");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansSeekShip"; //личный флаг квеста для портмана
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //имя кэпа-вора
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //тип украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //вознаграждение
	npchar.quest.chest = 12-sti(RealShips[sti(sld.Ship.Type)].Class); //в сундуках
	sld.quest = "InMap"; //личный флаг кэпа-вора
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Thieving cap " + sld.id + " sailed out of: " + sld.city + " and went to: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, откуда кэп-вор спер корабль
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " '" + npchar.quest.PortmansSeekShip.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на абордаж
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на потопление без абордажа
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestPortman_GenerateGem() // камни
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";	
		break;
		case 1:
			itemID = "jewelry2"; 
		break;
		case 2:
			itemID = "jewelry3"; 
		break;
		case 3:
			itemID = "jewelry3"; 
		break;
		case 4:
			itemID = "jewelry5"; 
		break;
		case 5:
			itemID = "jewelry6"; 
		break;
	}
	return itemID;
}

// --> Jason, новые мини-квесты
string findCurrentCity1(ref NPChar)//выбираем целевой город 1
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}

string findCurrentCity2(ref NPChar)//выбираем целевой город 2
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-3)];
	return colonies[nation].id;
}

string findCurrentCity3(ref NPChar)//выбираем целевой город 3
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-7)];
	return colonies[nation].id;
}

int Escort_ShipType()
{
	int iShipType;
	switch (rand(2))
	{
		case 0: iShipType = SHIP_FLEUT; 	break;
		case 1: iShipType = SHIP_GALEON_L; 	break;
		case 2: iShipType = SHIP_PINNACE;	break;
	}
	return iShipType;
}
//<-- новые мини-квесты

void DelBakSkill(ref _compref) // hasert
{
	DelBakSkillAttr(pchar);
	ClearCharacterExpRate(pchar);
	RefreshCharacterSkillExpRate(pchar);
	SetEnergyToCharacter(pchar);

	DelBakSkillAttr(_compref);
	ClearCharacterExpRate(_compref);
	RefreshCharacterSkillExpRate(_compref);
	SetEnergyToCharacter(_compref);
}

void SetSeekCapShip(ref _chr)
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) < 27) iRank = 3;
	if (sti(pchar.rank) >= 27) iRank = 4;
	
	int iShip = SHIP_WAR_TARTANE;
	switch (iRank)
	{
		case 0:
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 1:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break; 
		case 2:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 3:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 4:  
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	_chr.Ship.Type = GenerateShipExt(iShip, true, _chr);
	SetRandomNameToShip(_chr);
    SetBaseShipData(_chr);
    SetCrewQuantityFull(_chr);
    Fantom_SetCannons(_chr, "pirate");
    Fantom_SetBalls(_chr, "pirate");
	Fantom_SetUpgrade(_chr, "pirate");
	Fantom_SetGoods(_chr, "pirate");
}
