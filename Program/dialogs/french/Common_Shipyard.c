// boal 08/04/06 общий диалог верфи
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	string s2;
	
	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернет 7 (лодка)
	int iRank = sti(PChar.rank);
	int iSumm, iType;
	
	ref rRealShip;
	ref shTo;
	aref refShip;
	string attr;
	float fTmp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int Material, WorkPrice;
	int amount;
	int	iCannonDiff;
	
	// генератор парусов по кейсу -->
	string attrLoc   = Dialog.CurrentNode;
	int i;
  	if (findsubstr(attrLoc, "SailsColorIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (findsubstr(attrLoc, "SailsTypeChooseIDX_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
	if(!CheckAttribute(NPChar, "ExpMeeting"))
	{
		NPChar.ExpMeeting = true;
		notification("Первое посещение верфи " + XI_ConvertString("Colony" +NPChar.City + "Gen"), "Carpenter");
		AddCharacterExpToSkill(pchar, SKILL_REPAIR, 10.0);
	}
 	// генератор парусов по кейсу <--
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // аналог выхода, со старых времен, много переделывать.
            LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  // выход для тюнинга, нужно тут из-за LoadSegment
		break;
		
		case "ship_tunning_not_now_1":  
			LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("L'alarme a été donnée dans la ville, et tout le monde te cherche. Si j'étais toi, je ne resterais pas ici.","Tous les gardes de la ville ratissent la ville à ta recherche. Je ne suis pas un idiot et je ne parlerai pas avec toi !","Courez, "+GetSexPhrase("matelot","fillette")+", avant que les soldats ne te transforment en passoire..."),LinkRandPhrase("Que désirez-vous, "+GetSexPhrase("scélérat","puant")+"?! Les gardes de la ville ont déjà ton odeur, tu n'iras pas loin, sale pirate !","Assassin, quitte ma maison sur-le-champ ! Gardes !","Je n'ai pas peur de toi, "+GetSexPhrase("scélérat","rat")+"Bientôt tu seras pendu dans notre fort, tu n'iras pas loin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, une alarme n'est pas un problème pour moi...","Ils ne m'auront jamais."),RandPhraseSimple("Ferme ta gueule, "+GetWorkTypeOfMan(npchar,"")+", ou je t'arracherai la langue !","Heh, "+GetWorkTypeOfMan(npchar,"")+", et là aussi - pour attraper des pirates ! C'est ce que je te dis, camarade : sois tranquille et tu ne mourras pas !"));
				link.l1.go = "fight";
				break;
			}
			
//Jason ---------------------------------------Бремя гасконца------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_shipyard")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
				{
					dialog.text = "Voulez-vous quelque chose, Monsieur ?";
					Link.l1 = "Je suis venu jeter un œil à vos navires... Mais pour l'instant, je suis un peu occupé - j'ai encore une affaire inachevée. Je reviendrai plus tard, une fois que j'en aurai fini.";
					Link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
				{
					dialog.text = "Voulez-vous quelque chose, Monsieur ?";
					Link.l1 = "Écoutez, j'aimerais vous acheter un navire.";
					Link.l1.go = "Sharlie";
					break;
				}
				dialog.text = "Voulez-vous autre chose, Monsieur ?";
				Link.l1 = "Non, je suppose que non.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				NPChar.quest.meeting = "1";
				break;
			}
	//<-- Бремя гасконца
			// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
			if (CheckAttribute(pchar, "questTemp.FMQM.Oil") && pchar.location == "Fortfrance_shipyard")
			{
				if (pchar.questTemp.FMQM == "remove_oil")
				{
					dialog.text = "C'est fait, Capitaine. Le travail est terminé. Maintenant, la partie agréable - le son des pièces. Donnez-moi une seconde...";
					link.l1 = "... -> ";
					link.l1.go = "FMQM_oil_1";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil1")
				{
					dialog.text = "Officier, attendez ! S'il vous plaît ! Cela doit être une erreur. Monsieur, le capitaine n'a rien à voir avec cela, il est seulement accosté ici pour faire réparer son navire. Il était sur le point de partir. Et quels tonneaux ? De quoi parlez-vous ?";
					link.l1 = "";
					link.l1.go = "FMQM_oil_2";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil2")
				{
					dialog.text = "Officier, je le répète : le Capitaine est venu ici pour payer les réparations du navire. Ces tonneaux m'appartiennent et sont uniquement à des fins de production. Je suis un maître constructeur de navires et cette résine est pour les vaisseaux que je construis.";
					link.l1 = "";
					link.l1.go = "FMQM_oil_3";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil3")
				{
					dialog.text = "Oh, Monsieur Capitaine ! Vous n'avez pas idée de combien c'était terrible pour moi. Deux jours dans les cachots en compagnie de rats, de souris et de personnages misérables ! J'ai dû utiliser toutes mes relations pour me sortir de là. Ah, l'air frais !";
					link.l1 = "Vous avez ma sympathie, maître. Qu'en est-il de notre résine ? Et de mes pièces ?";
					link.l1.go = "FMQM_oil_4";
					DelLandQuestMark(npchar);
					break;
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_13" && pchar.location == "PortRoyal_shipyard")
			{
				dialog.text = "Oh, c'est encore vous ! Je vous reconnais, jeune homme ! C'était vous qui demandiez récemment... comment augmenter la vitesse de votre navire avec une voile en toile de soie, n'est-ce pas ?";
				link.l1 = "Votre mémoire vous fait honneur, maître."; 
				link.l1.go = "mtraxx_x";
				break;
			}
			
			if(NPChar.quest.meeting == "0") // первая встреча
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Ha ! Un vrai vieux loup de mer est venu dans mon humble atelier ! Êtes-vous nouveau dans ces eaux, Capitaine ?","Bienvenue, Monsieur ! Si vous n'êtes pas étranger à la mer et que vous avez un navire - vous êtes tombé pile au bon endroit !","Bonjour, Monsieur ! Vous avez de la chance - c'est le meilleur atelier naval de tout le Nouveau Monde britannique."),LinkRandPhrase("Monsieur, je suppose que vous êtes un capitaine fringant, n'est-ce pas ? Si c'est le cas, vous avez bien fait de visiter mon modeste chantier naval !","Première fois ici, Monsieur le Capitaine ? Entrez et rencontrez ce vieux charpentier de marine.","Faisons connaissance, Monsieur ! Un navire a besoin d'être cajolé, tout comme une femme - et nous, les Français, sommes des experts en la matière ! Croyez-moi, vous ne regretterez pas d'être venu ici !"),LinkRandPhrase("Je ne vous ai jamais vu ici auparavant, Señor. Enchanté de faire votre connaissance !","Je salue un vaillant conquérant des mers ! Vous êtes marin, n'est-ce pas ? Et moi, je suis le charpentier de navire local, nous devrions faire connaissance.","Bonjour, Caballero ! Je suis heureux de vous accueillir dans mon atelier !"),LinkRandPhrase("Bon après-midi, Monsieur. Je ne vous ai jamais rencontré auparavant, n'est-ce pas ? Avez-vous des affaires avec moi ?","Bonjour, Monsieur le Capitaine. Ne soyez pas surpris, j'ai rencontré pas mal de Capitaines, donc j'ai réalisé que vous êtes un Capitaine aussi, au premier coup d'œil.","Entrez, monsieur. Je suis le charpentier naval local. Enchanté de vous rencontrer."));
				Link.l1 = LinkRandPhrase("Je suis heureux de vous rencontrer également. Mon nom est "+GetFullName(pchar)+", et je suis nouveau dans ces parages. Alors, j'ai décidé de passer.","Je ne pouvais tout simplement pas passer à côté - vous savez, cette odeur de planches fraîchement rabotées... Je suis "+GetFullName(pchar)+", Capitaine du navire '"+pchar.ship.name+"'.","Permettez-moi de me présenter - "+GetFullName(pchar)+", Capitaine du navire '"+pchar.ship.name+"Enchanté de faire votre connaissance. Alors, vous construisez et réparez des navires ici, n'est-ce pas ?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_shipyard")
				{
					dialog.text = "Salutations, Capitaine MacArthur.";
					link.l1 = "Vous pouvez simplement m'appeler Hélène, Monsieur "+npchar.lastname+". "+TimeGreeting()+".";
					Link.l1.go = "Helen_meeting";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh! La terreur des eaux locales, Capitaine "+GetFullName(pchar)+"! Que puis-je faire pour vous ?","Passons directement aux affaires, "+GetAddress_Form(NPChar)+", je n'ai pas le temps de bavarder. Avez-vous besoin d'une réparation ou souhaitez-vous simplement remplacer votre rafiot ?","Oh, n'est-ce pas "+GetFullName(pchar)+"! Quoi de neuf, "+GetAddress_Form(NPChar)+"Quelque chose de fâcheux est arrivé à ta barcasse ?"),LinkRandPhrase("Que vous faut-il, Capitaine ? Pas une minute de paix - toujours tous ces vauriens, quelle journée maudite...","Bonjour, "+GetAddress_Form(NPChar)+".  Je dois dire que votre visite a fait fuir tous mes clients. J'espère que votre commande couvrira mes pertes ?","Pour affaires avec moi, "+GetAddress_Form(NPChar)+" ? Eh bien, va droit au but, et fais ça vite."),LinkRandPhrase("Qu'est-ce qui vous amène à moi, Monsieur "+GetFullName(pchar)+"? Je peux comprendre que votre navire puisse avoir des difficultés, compte tenu de votre mode de vie...","Je suis heureux de saluer un noble... oh, excusez-moi, "+GetAddress_Form(NPChar)+", je vous ai pris pour quelqu'un d'autre. Que vouliez-vous?","Je n'aime pas vraiment votre genre, Capitaine, mais je ne vais pas vous chasser, de toute façon. Que vouliez-vous ?")),LinkRandPhrase(LinkRandPhrase("Je suis très content de vous voir, Monsieur "+GetFullName(pchar)+"! Alors, comment elle se comporte ? Avez-vous besoin d'une réparation ou d'un carénage ?","Bienvenue, "+GetAddress_Form(NPChar)+" ! Capitaine "+GetFullName(pchar)+" est toujours un invité bienvenu dans mon atelier !","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"Ah ! Vous m'avez rendu visite à nouveau ! J'espère que votre beauté se porte bien, n'est-ce pas ?"),LinkRandPhrase(""+GetAddress_Form(NPChar)+", je suis si heureux de te revoir ! Comment va ton beau navire ? As-tu besoin d'aide ?","Oh, "+GetAddress_Form(NPChar)+", salutations ! Comment ça va ? Peut-être que les mâts grincent ou que vous avez besoin de vider la cale ? Mes gars feront de leur mieux pour vous !","Bon après-midi, Capitaine "+GetFullName(pchar)+"Je suis heureux que vous soyez revenu, et je suis toujours prêt à vous aider."),LinkRandPhrase("Je suis heureux de vous avoir ici, Capitaine ! Vous êtes un client très agréable, "+GetAddress_Form(NPChar)+", et je souhaite que vous restiez ainsi.","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Je suis vraiment heureux de vous avoir ici ! Que puis-je faire pour vous ?","Capitaine, encore une fois vous avez visité "+XI_ConvertString("Colony"+npchar.City+"Accord")+"Croyez-moi, nous serons ravis de vous aider.")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Prenez vos instruments, maître, et restez silencieux, d'accord ? Je ne suis pas d'humeur.","Arrête de bavarder, matelot ! J'ai besoin de ton aide, pas de tes balivernes."),RandPhraseSimple("Je paie - et vous travaillez. En silence. Est-ce clair ?","Hé, matelot, chasse-les tous - c'est moi, ton client préféré !")),RandPhraseSimple(RandPhraseSimple("Je suis heureux de vous voir aussi, maître. Hélas, je n'ai pas beaucoup de temps, alors passons aux affaires.","Et je suis heureux de te voir aussi, camarade. Tu veux aider ton client préféré ?"),RandPhraseSimple("Bon après-midi, l'ami. Passons directement aux affaires. Promis, la prochaine fois nous trinquerons certainement autour d'une bouteille.","Je suis heureux de vous voir, maître. Toujours un plaisir de vous voir, mais en ce moment j'ai besoin de votre aide.")));
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l11 = "J'ai besoin de canons pour mon navire.";
					link.l11.go = "Cannons";					
				}	
				
				if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "Charles" || NPChar.city == "PortoBello")
				{
					link.l22 = "Pouvez-vous m'offrir quelque chose de spécial, quelque chose qu'on ne trouve dans aucun autre chantier naval ?";
					link.l22.go = "ship_tunning";
				}
				
				link.l15 = "N'as-tu pas un travail nécessitant l'aide d'un étranger ?";
			    link.l15.go = "Tasks";
				// Jason Исла Мона 
				if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "tools" && !CheckAttribute(npchar, "quest.IslaMonaTools"))
				{
					link.l20 = "Je veux acheter un ensemble d'outils de construction, de forge et de mesure de qualité européenne. Pouvez-vous m'aider ?";
					link.l20.go = "IslaMona";
				}
				if (CheckAttribute(npchar, "quest.IslaMonaMoney"))
				{
					link.l20 = "J'ai apporté des doublons pour un ensemble d'outils de construction.";
					link.l20.go = "IslaMona_7";
				}
				//Jason --> генератор Призонер
				if (CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && NPChar.location == pchar.GenQuest.Findship.Shipyarder.City + "_shipyard")
				{
					ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
					if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
					{
						for(i = 1; i < COMPANION_MAX; i++)
						{
							int iTemp = GetCompanionIndex(PChar, i);
							if(iTemp > 0)
							{
								sld = GetCharacter(iTemp);
								if(GetRemovable(sld) && sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.GenQuest.Findship.Shipyarder.ShipType))
								{
									pchar.GenQuest.Findship.Shipyarder.CompanionIndex = sld.Index;
									pchar.GenQuest.Findship.Shipyarder.OK = 1;
									pchar.GenQuest.Findship.Shipyarder.ShipName = sld.Ship.Name;
									pchar.GenQuest.Findship.Shipyarder.Money = makeint(GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder"))*1.5);
								}
							}
						}
					}
					if (sti(pchar.GenQuest.Findship.Shipyarder.OK) == 1)
					{
						link.l16 = "Je vous ai livré "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+", comme vous l'avez demandé.";
						link.l16.go = "Findship_check";
					}// <-- генератор Призонер
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && CheckCharacterItem(pchar, "Tool") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_shipyard")
				{
					link.l17 = "J'ai réussi à débusquer le voleur et à obtenir "+pchar.GenQuest.Device.Shipyarder.Type+".";
					link.l17.go = "Device_complete";
				}
				// <-- генератор Неудачливый вор
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Je veux changer l'apparence de mes voiles.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Je voulais juste parler.";
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Je voudrais vous parler de questions financières.";
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Je suis ici à la demande d'un homme. Son nom est Gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" m'a envoyé vers vous. Je suis censé récupérer quelque chose...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "J'ai apporté le dessin du navire de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				} // patch-6
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = "Bonjour, je suis venu sur l'invitation de votre fils."; 
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = "C'est à propos de ta fille...";
							link.l8.go = "EncGirl_1";
						}
					}
				}								
				Link.l9 = "Je dois y aller.";
				Link.l9.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Meeting":
				dialog.Text = "Je suis très heureux de rencontrer un nouveau client. Mon chantier naval est à votre service.";
				Link.l1 = "Excellent, "+GetFullName(NPChar)+"Voyons voir ce que vous pouvez m'offrir.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "J'ai besoin de canons pour mon navire.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "N'avez-vous pas un travail nécessitant l'aide d'un étranger ?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Je veux changer l'apparence de mes voiles.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Je voulais juste parler.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Je voudrais vous parler de questions financières.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Je suis ici à la demande d'un homme. Il s'appelle Gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" m'a envoyé vers vous. Je suis censé récupérer quelque chose...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "J'ai livré le dessin du navire de la ville de "+XI_ConvertString("Colonie"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Bonjour, je viens sur l'invitation de votre fils."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "C'est à propos de ta fille...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "Que peux-tu me dire sur le proprietaire de ces documents ?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "Je dois partir, merci.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;
		
		case "Helen_Meeting":
				dialog.Text = "Bien sûr, Capitaine MacArthur, comme vous le souhaitez. Que désirez-vous aujourd'hui ?";
				Link.l1 = "Excellent, "+GetFullName(NPChar)+" Voyons voir ce que vous pouvez m'offrir.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "J'ai besoin de canons pour mon navire.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "N'as-tu pas un travail nécessitant l'aide d'un étranger ?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Je veux changer l'apparence de mes voiles.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Je voulais juste parler.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "J'aimerais vous parler de questions financières.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Je suis ici à la demande d'un homme. Son nom est Gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" m'a envoyé vers vous. Je suis censé récupérer quelque chose...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "J'ai livré le dessin du navire de la ville de "+XI_ConvertString("Colonie"+pchar.questTemp.WPU.Postcureer.StartCity+"Gén")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Bonjour, je suis venu sur l'invitation de votre fils."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "C'est au sujet de ta fille...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "Que pouvez-vous me dire sur le proprietaire de ces documents ?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "Je dois partir, merci.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;

		case "ship_tunning":
			dialog.text = "Notre chantier naval est réputé pour améliorer les navires. Cela vous intéresse, Capitaine ?";
			Link.l1 = LinkRandPhrase("Excellent ! Peut-être pourriez-vous jeter un œil à mon navire et me dire comment il pourrait être amélioré ?","C'est très intéressant, maître ! Et qu'est-ce que vous pouvez faire pour mon navire ?","Hmm... Vous savez, je me suis habitué à mon navire, mais si vous me proposez quelque chose de vraiment intéressant, je peux y réfléchir. Qu'en dites-vous?");
			Link.l1.go = "ship_tunning_start";
		break;
				
		case "ship_tunning_start" :		
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{				
				if (sti(RealShips[sti(pchar.Ship.Type)].Class) >= 7)
				{
					dialog.Text = "Euh... Je ne m'occupe pas des barques. Une vieille baignoire restera une vieille baignoire, peu importe les efforts que vous y mettez.";
					Link.l1 = "Je vois...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// belamour legendary edition -->
				if(!TuningAvailable())
				{
					dialog.Text = "Comme ci, comme ça... voyons voir ce que nous avons ici... Ouais - "+XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName)+"Votre navire a déjà le nombre maximum de caractéristiques améliorées, je crains que poursuivre les travaux dessus n'ait aucun sens et ne puisse même nuire.";
					Link.l1 = "Je vois...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// <-- legendary edition							
				if(GetHullPercent(pchar) < 100 || GetSailPercent(pchar) < 100)
				{
					dialog.Text = "Avant d'améliorer un navire, il doit être entièrement réparé. Cela aussi peut être fait ici à mon chantier naval.";
					Link.l1 = "Compris...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				
				s2 = "Alright, let's see what we've got here... Aha " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
				// belamour legendary edition -->
				if(NPChar.city == "PortRoyal")
				{
					s2 = s2 + " Our shipyard is famous for improving the ship's performance we can increase either the maximum speed or the angle to the wind.";
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					s2 = s2 + " At our shipyard we can increase the maximum number of cannons or the ship's carrying capacity.";
				}
				if(NPChar.city == "Villemstad")
				{
					s2 = s2 + " My guys can reinforce the hull of your ship or increase the maximum number of sailors in your crew.";
				}
				if(NPChar.city == "Charles")
				{
					s2 = s2 + " At this shipyard you can improve the maneurability or decrease the minimum number of sailors in the crew.";
				}	
				
				dialog.Text = s2;
				
				if(NPChar.city == "PortRoyal")
				{
					// belamour legendary edition -->
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"));
					if(ok)
					{
						Link.l1 = "Augmente la vitesse.";
						Link.l1.go = "ship_tunning_SpeedRate";
						Link.l2 = "Augmentez l'angle au vent.";
						Link.l2.go = "ship_tunning_WindAgainst";
						Link.l3 = "Attends! J'ai changé d'avis.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
						{
							Link.l1 = "Augmentez la vitesse.";
							Link.l1.go = "ship_tunning_SpeedRate";
							Link.l2 = "Attends! J'ai changé d'avis.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"))
						{
							Link.l1 = "Augmentez l'angle par rapport au vent.";
							Link.l1.go = "ship_tunning_WindAgainst";
							Link.l2 = "Attends ! J'ai changé d'avis.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("Oh! Mon navire est déjà amélioré de cette façon. Eh bien, merci pour votre temps !","Merci, maître, mais j'ai déjà une amélioration, et c'est exactement ce que vous m'avez mentionné. Bonne chance avec les autres navires et leurs Capitaines !","Heh ! Je suppose que mon navire a déjà été réaménagé par un précédent propriétaire - cela a dû être fait dans ce même chantier naval. Eh bien, je suppose que je dois le remercier pour sa prévoyance, et vous et vos gars pour leur excellent travail !");
						Link.l1.go = "ship_tunning_not_now_1";					
					}
						// <-- legendary edition
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"));
					if(ok)
					{	
						if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
						{	
							Link.l1 = "Augmentez le nombre maximum de canons.";
							Link.l1.go = "ship_c_quantity";
						}	
							Link.l2 = "Augmentez le port en lourd.";
							Link.l2.go = "ship_tunning_Capacity";
						Link.l3 = "Attends ! J'ai changé d'avis.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
						{
							if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
							{	
								Link.l1 = "Augmentez le nombre maximum de canons.";
								Link.l1.go = "ship_c_quantity";
								Link.l2 = "Attends ! J'ai changé d'avis.";
								Link.l2.go = "ship_tunning_not_now_1";	
								break;
							}	
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
						{
							Link.l1 = "Augmentez le port en lourd.";
							Link.l1.go = "ship_tunning_Capacity";
							Link.l2 = "Attendez ! J'ai changé d'avis.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("Oh! Mon navire est déjà amélioré de cette manière. Eh bien, merci pour votre temps !","Merci, maître, mais j'ai déjà une amélioration, et c'est exactement ce que vous m'avez mentionné. Bonne chance avec les autres navires et leurs Capitaines !","Heh ! Je suppose que mon navire avait déjà été réaménagé auparavant par un propriétaire précédent - cela a dû être fait dans ce chantier naval. Eh bien, je suppose que je dois le remercier pour sa prévoyance, et vous et vos gars pour leur excellent travail !");
						Link.l1.go = "ship_tunning_not_now_1";	
					// <-- legendary edition
					}						
				}
				if(NPChar.city == "Villemstad")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"));
					if(ok)
					{
						Link.l1 = "Augmentez la durabilité de la coque.";
						Link.l1.go = "ship_tunning_HP";
						Link.l2 = "Augmenter l'espace pour l'équipage.";
						Link.l2.go = "ship_tunning_MaxCrew";
						Link.l3 = "Attends ! J'ai changé d'avis.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
						{
							Link.l1 = "Augmenter la durabilité de la coque.";
							Link.l1.go = "ship_tunning_HP";
							Link.l2 = "Attends ! J'ai changé d'avis.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
						{
							Link.l1 = "Augmenter l'espace pour l'équipage.";
							Link.l1.go = "ship_tunning_MaxCrew";
							Link.l2 = "Attendez! J'ai changé d'avis.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;	
						}
						Link.l1 = LinkRandPhrase("Oh ! Mon navire est déjà amélioré de cette manière. Eh bien, merci pour votre temps !","Merci, maître, mais j'ai déjà une amélioration, et c'est exactement ce que vous m'avez mentionné. Bonne chance avec les autres navires et leurs capitaines !","Hein ! Je suppose que mon navire a déjà été réaménagé par un précédent propriétaire - cela doit avoir été fait dans ce chantier naval. Eh bien, je suppose que je dois le remercier pour sa prévoyance, et vous et vos gars pour leur excellent travail !");
						Link.l1.go = "ship_tunning_not_now_1";	
						// <-- legendary edition
					}
				}
				if(NPChar.city == "Charles")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"));
					if(ok)
					{		
						Link.l1 = "Augmenter la manœuvrabilité.";
						Link.l1.go = "ship_tunning_TurnRate";
						if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
						{
							Link.l2 = "Diminuez la taille minimale de l'équipage.";
							Link.l2.go = "ship_tunning_MinCrew";
						}	
						Link.l3 = "Attendez ! J'ai changé d'avis.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
						{
							Link.l1 = "Augmenter la manœuvrabilité.";
							Link.l1.go = "ship_tunning_TurnRate";
							Link.l2 = "Attends ! J'ai changé d'avis.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"))
						{
							if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
							{
								Link.l1 = "Réduire la taille minimale de l'équipage.";
								Link.l1.go = "ship_tunning_MinCrew";
								Link.l2 = "Attends ! J'ai changé d'avis.";
								Link.l2.go = "ship_tunning_not_now_1";
								break;
							}	
						}
						// <-- legendary edition				
					}
					Link.l1 = LinkRandPhrase("Oh ! Mon navire est déjà amélioré de cette manière. Eh bien, merci pour votre temps !","Merci, maître, mais j'ai déjà une amélioration, et c'est exactement ce que vous m'avez mentionné. Bonne chance avec d'autres navires et leurs Capitaines !","Heh ! Je parie que mon navire a déjà été remis en état par un propriétaire précédent - ce devait être dans ce même chantier naval. Eh bien, je suppose que je dois le remercier pour sa prévoyance, et vous et vos gars pour leur excellent travail !");
					Link.l1.go = "ship_tunning_not_now_1";	
				}								
			}
			else
			{
				dialog.Text = "Où est le navire ? Tu te moques de moi ou quoi ?";
			    Link.l1 = "Oh, ma foi, en effet... Je suis désolé.";
			    Link.l1.go = "ship_tunning_not_now_1";
			}			
		break;
		
		////////////////////////////////////////// Capacity ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Well, let's see what we can do. At the moment the deadweight of your vessel is " + sti(RealShips[sti(pchar.Ship.Type)].Capacity);			
			s2 = s2 + ". For lighter bulkheads I will require: ironwood - " + Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";			
            dialog.Text = s2;
			Link.l1 = "D'accord. J'accepte vos conditions. Je vous apporterai ce dont vous avez besoin.";
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = "Non. Cela ne me convient pas.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_Capacity_start":
		    amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;			    
				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.text = "Excellent. J'attendrai le materiel.";
			    link.l1 = LinkRandPhrase("Je vous assure que vous n'aurez pas à attendre longtemps. Je peux résoudre ces problèmes, d'accord ?","Considérez que vous les avez déjà et gardez le quai pour moi. Je serai aussi rapide que le vent.","Bien sûr. Je vais juste devoir rendre visite à quelques personnes qui ont les objets que vous avez demandés, ha-ha !");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the tonnage of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'"+
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Je ne vois pas l'acompte...";
				link.l1 = "Je passerai plus tard.";
				link.l1.go = "Exit";								
			}
		break;
				
		case "ship_tunning_Capacity_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "Le temps passe, et le navire attend. As-tu apporté tout ce que j'ai demandé ?";
			    Link.l1 = "Oui, j'ai réussi à trouver quelque chose.";
			    Link.l1.go = "ship_tunning_Capacity_again_2";
			    Link.l2 = "Non, je suis toujours dessus.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
			    dialog.Text = "Perdu"+GetSexPhrase("ter","s")+", avez-vous changé de navire depuis que nous avons conclu notre arrangement ? Vous n'auriez pas dû.";
			    Link.l1 = "Hélas, ce sont toutes les circonstances ! Dommage que l'acompte ait été perdu...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, maintenant j'ai tout ce dont j'ai besoin. Je vais commencer à travailler, alors.";
			    link.l1 = "J'attends.";
			    link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "J'ai encore besoin de : bois de fer - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "D'accord.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)* 0.65);
				}
				else
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
				}
			}
			else
			{
				
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.35 + sti(shTo.Bonus_Capacity));
				}
				else
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
				}
			}	
	        shTo.Tuning.Capacity = true;

	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = "...Cela semble être tout... Vous pouvez maintenant charger votre cale à pleine capacité, je garantis la qualité de mon travail.";
			Link.l1 = "Merci ! Je vais le tester.";
			Link.l1.go = "Exit";
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar,  1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar,  2 );
			s2 = "Let's see what we can do, then. At the moment the speed of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);	
			s2 = s2 + " knots. In order to replace the sails I will require: sail silk - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
            dialog.Text = s2;
			Link.l1 = "D'accord. J'accepte vos conditions. Je vous apporterai ce dont vous avez besoin.";
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = "Non. Cela ne me convient pas.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
			
		case "ship_tunning_SpeedRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType   	= Pchar.Ship.Type;
			    NPChar.Tuning.ShipName   	= RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.text = "Excellent. J'attendrai le matériel.";
				link.l1 = LinkRandPhrase("Je vous assure que vous n'aurez pas à attendre longtemps. Je peux résoudre de tels problèmes, d'accord ?","Considérez que vous les avez déjà et gardez le quai pour moi. Je serai aussi rapide que le vent.","Bien sûr. Je devrai juste rendre visite à quelques personnes qui ont les choses que vous avez demandées, ha-ha !");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the speed at " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". As the deposit was paid for " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Je ne vois pas le dépôt...";
				link.l1 = "Je passerai plus tard.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "Le temps passe, et le navire attend. Avez-vous apporté tout ce que j'ai demandé ?";
			    Link.l1 = "Oui, j'ai réussi à trouver quelque chose.";
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
			    Link.l2 = "Non, j'y travaille encore.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Raté"+GetSexPhrase("ter","s")+", avez-vous changé votre navire depuis que nous avons conclu notre accord ? Vous n'auriez pas dû.";
			    Link.l1 = "Hélas, ce sont toutes les circonstances ! Dommage que le dépôt ait été perdu...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, maintenant j'ai tout ce dont j'ai besoin. Je vais commencer à travailler, alors.";
			    link.l1 = "J'attends.";
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "J'ai encore besoin de : soie de navire - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "D'accord.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate) * 0.65);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.35 + stf(shTo.Bonus_SpeedRate);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
				}
			}
	        shTo.Tuning.SpeedRate = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Tout est prêt, Capitaine. Attrapez le vent à pleines voiles. Vérifiez-le si vous le souhaitez !";
			Link.l1 = "Merci ! Je vais le tester.";
			Link.l1.go = "Exit";			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			s2 = "Let's see what we can do, then. At the moment the maneurability of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);			
			s2 = s2 + " In order to add new sails to shake it up I shall require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";										
            dialog.Text = s2;
			Link.l1 = "D'accord. J'accepte vos conditions. Je vous apporterai tout ce dont vous avez besoin.";
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = "Non. Cela ne me convient pas.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_TurnRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.text = "Excellent. J'attendrai le matériel.";
				link.l1 = LinkRandPhrase("Je vous assure que vous n'aurez pas à attendre longtemps. Je peux résoudre de tels problèmes, d'accord ?","Considérez que vous les avez déjà et gardez le quai pour moi. Je serai aussi rapide que le vent.","Bien sûr. Je devrai juste rendre visite à quelques personnes qui ont les marchandises que vous avez demandées, ha-ha !");			    
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase agility by " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of  " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Je ne vois pas l'acompte...";
				link.l1 = "Je passerai plus tard.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "Le temps passe, et le navire attend. As-tu apporté tout ce que j'ai demandé ?";
			    Link.l1 = "Oui, j'ai réussi à livrer quelque chose.";
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
			    Link.l2 = "Non, je suis encore dessus.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Raté"+GetSexPhrase("ter","s")+", avez-vous changé de navire depuis que nous avons passé notre accord? Vous n'auriez pas dû.";
			    Link.l1 = "Hélas, ce sont toutes les circonstances ! Dommage que le dépôt ait été perdu...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, maintenant j'ai tout ce dont j'ai besoin. Je vais commencer à travailler, alors.";
			    link.l1 = "J'attends.";
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "J'ai encore besoin de : cordages - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Très bien.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
			}
			else
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}	

	        shTo.Tuning.TurnRate = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4") && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
			dialog.Text = "... Tout devrait être prêt maintenant... Vérifiez le gouvernail maintenant, Capitaine !";
			Link.l1 = "Merci ! Je vais l'essayer.";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the maximum number of sailors in your crew, including overloading, is " + sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew) + " men.";			
			s2 = s2 + " I will require: ironwood - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "D'accord. J'accepte vos conditions. Je vous apporterai tout ce dont vous avez besoin.";
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = "Non. Cela ne me convient pas.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MaxCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.text = "Excellent. J'attendrai le matériel.";
				link.l1 = LinkRandPhrase("Je vous assure que vous n'aurez pas à attendre longtemps. Je peux résoudre de tels problèmes, d'accord ?","Considérez que vous les avez déjà et gardez le quai pour moi. Je serai aussi rapide que le vent.","Bien sûr. Il me suffira de rendre visite à quelques personnes qui ont les objets que vous avez demandés, ha-ha !");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For their efforts to increase the crew of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Je ne vois pas l'acompte...";
				link.l1 = "Je passerai plus tard.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "Le temps passe, et le navire attend. Avez-vous apporté tout ce que j'ai demandé ?";
			    Link.l1 = "Oui, j'ai réussi à trouver quelque chose.";
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
			    Link.l2 = "Non, je suis toujours dessus.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Raté"+GetSexPhrase("ter","s")+", avez-vous changé de navire depuis que nous avons passé notre accord? Vous n'auriez pas dû.";
			    Link.l1 = "Hélas, ce sont toutes les circonstances ! Dommage que le dépôt ait été perdu...";				
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, maintenant j'ai tout ce qu'il me faut. Je vais commencer à travailler, alors.";
			    link.l1 = "J'attends.";
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "J'ai encore besoin de : bois d'iroko - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "D'accord.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    
	        shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
	        shTo.Tuning.MaxCrew = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... C'est fait, Capitaine. Vous pouvez maintenant engager plus de marins, il y aura assez de place pour tout le monde.";
			Link.l1 = "Merci ! Je vais le tester.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

		
		////////////////////////////////////////// MinCrew ////////////////////////////////////////////////////
		case "ship_tunning_MinCrew":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the minimum number of required sailors in your crew is " + sti(RealShips[sti(Pchar.Ship.Type)].MinCrew) + " men.";			
			s2 = s2 + " To improve the controllability of the ship and to reduce the required number of sailors in the crew I will require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Entendu. J'accepte vos conditions. Je vous apporterai tout ce dont vous avez besoin.";
			Link.l1.go = "ship_tunning_MinCrew_start";
			Link.l2 = "Non. Cela ne me convient pas.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MinCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
                dialog.text = "Excellent. J'attendrai le matériel.";
				link.l1 = LinkRandPhrase("Je vous assure que vous n'aurez pas à attendre longtemps. Je peux résoudre ces problèmes, d'accord ?","Considérez que vous les avez déjà et gardez le quai pour moi. Je serai aussi rapide que le vent.","Bien sûr. Il me suffira de rendre visite à quelques personnes qui ont les objets que vous avez demandés, ha-ha !");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to reduce the minimum required number of crew on " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Je ne vois pas l'acompte...";
				link.l1 = "Je passerai plus tard.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MinCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "Le temps passe, et le navire attend. As-tu apporté tout ce que j'ai demandé ?";
			    Link.l1 = "Oui, j'ai réussi à trouver quelque chose.";
			    Link.l1.go = "ship_tunning_MinCrew_again_2";
			    Link.l2 = "Non, je suis toujours dessus.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mal"+GetSexPhrase("ter","s")+", as-tu changé de navire depuis que nous avons conclu notre accord ? Tu n'aurais pas dû.";
			    Link.l1 = "Hélas, ce sont toutes les circonstances ! Dommage que l'acompte ait été perdu...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MinCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, maintenant j'ai tout ce dont j'ai besoin. Je vais commencer à travailler, alors.";
			    link.l1 = "J'attends.";
			    link.l1.go = "ship_tunning_MinCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "J'ai encore besoin de: cordages - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Très bien.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MinCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew) * 0.65);
			}
			else
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
			}
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
	        shTo.Tuning.MinCrew = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4")  && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Prêt, Capitaine ! Désormais, moins de marins peuvent gérer le navire avec le même résultat global.";
			Link.l1 = "Merci ! Je vais le tester.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what we can do, then. At the moment the ship's hull is " + sti(RealShips[sti(Pchar.Ship.Type)].HP);			
			s2 = s2 + ". To reinforce the hull, I will require: resin - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "D'accord. J'accepte vos conditions. Je vous apporterai tout ce dont vous avez besoin.";
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = "Non. Cela ne me convient pas.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_HP_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.text = "Excellent. J'attendrai le matériel.";
				link.l1 = LinkRandPhrase("Je vous assure que vous n'aurez pas à attendre longtemps. Je peux résoudre ces problèmes, d'accord ?","Considérez que vous les avez déjà et gardez le quai pour moi. Je serai aussi rapide que le vent.","Bien sûr. Je devrai juste rendre visite à quelques personnes qui ont les affaires que vous avez demandées, ha-ha !");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his efforts to increase the strength of the hull " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Je ne vois pas l'acompte...";
				link.l1 = "Je passerai plus tard.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "Le temps passe, et le navire attend. As-tu apporté tout ce que j'ai demandé ?";
			    Link.l1 = "Oui, j'ai réussi à trouver quelque chose.";
			    Link.l1.go = "ship_tunning_HP_again_2";
			    Link.l2 = "Non, je suis toujours dessus.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Erreur"+GetSexPhrase("ter","s")+" , avez-vous changé de navire depuis que nous avons conclu notre accord ? Vous n'auriez pas dû.";
			    Link.l1 = "Hélas, ce sont toutes les circonstances ! Dommage que l'acompte ait été perdu...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_OIL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, maintenant j'ai tout ce qu'il me faut. Je vais commencer à travailler, alors.";
			    link.l1 = "J'attends.";
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "J'ai encore besoin de : résine - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "D'accord.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_HP"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP) * 0.65);
				}
				else
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.35 + sti(shTo.Bonus_HP));
				}
				else
				{
					shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
				}
			}
	        shTo.Tuning.HP = true;
			shTo.BaseHP = sti(shTo.HP);

			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
			TuningAvailable();
            NextDiag.TempNode = "First time";
			
			dialog.Text = "... Cela devrait le faire... Je vous garantis qu'à partir de maintenant, vos ennemis auront beaucoup plus de mal à déchirer la coque de votre navire en morceaux !";
			Link.l1 = "Heh, je te croirai sur parole ! Merci, maître.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_REPAIR, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			fTmp = 180.0 - (acos(1 - stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed)) * 180.0/PI);
			s2 = "Let's see what we can do, then. At the moment the point of sail by the wind is " + makeint(fTmp) + " degrees.";
			// belamour legendary edition если спускать курс по ветру, то это даунгрейд
			s2 = s2 + " To accelerate the ship upwind, I will require: ship silk - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "D'accord. J'accepte vos conditions. Je vous apporterai tout ce dont vous avez besoin.";
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = "Non. Cela ne me convient pas.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;

		case "ship_tunning_WindAgainst_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial    	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.text = "Excellent. J'attendrai le matériel.";
				link.l1 = LinkRandPhrase("Je vous assure que vous n'aurez pas à attendre longtemps. Je peux résoudre ces problèmes, d'accord ?","Considérez que vous les avez déjà et tenez le quai pour moi. Je serai aussi rapide que le vent.","Bien sûr. Je vais juste devoir rendre visite à quelques personnes qui ont les marchandises que vous avez demandées, ha-ha !");
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work on changing the wind angle of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Je ne vois pas l'acompte...";
				link.l1 = "Je passerai plus tard.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			    dialog.Text = "Le temps passe, et le navire attend. As-tu apporté tout ce que j'ai demandé ?";
			    Link.l1 = "Oui, j'ai réussi à livrer quelque chose.";
			    Link.l1.go = "ship_tunning_WindAgainst_again_2";
			    Link.l2 = "Non, je suis encore dessus.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Raté"+GetSexPhrase("ter","s")+", avez-vous changé de navire depuis que nous avons conclu notre accord ? Vous n'auriez pas dû.";
			    Link.l1 = "Hélas, ce sont toutes les circonstances ! Dommage que le dépôt ait été perdu...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, maintenant j'ai tout ce dont j'ai besoin. Je vais commencer à travailler, alors.";
			    link.l1 = "J'attends.";
			    link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.Text = "J'ai encore besoin de : soie de navire - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "D'accord.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;

		case "ship_tunning_WindAgainst_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим			
			// belamour legendary edtion чем больше WindAgainstSpeed, тем круче к ветру
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.35 * stf(shTo.WindAgainstSpeed);	
			}
			else
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.20 * stf(shTo.WindAgainstSpeed);
			}
			if (stf(shTo.WindAgainstSpeed) > 1.985) shTo.WindAgainstSpeed = 1.985;
	        shTo.Tuning.WindAgainst = true;

			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Prêt, Capitaine !.. Votre navire naviguera bien plus rapidement au près désormais.";
			Link.l1 = "Merci ! Je vais le tester.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
						
		////////////////////////////////////////// только количество орудий  ////////////////////////////////////////////////////	
		case "ship_c_quantity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what can be done there. Right now, the number of cannons on your ship is " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity) + ", and the maximum possible number is - " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax) + ".";			
			s2 = s2 + " I can tell you right away that it's not going to be cheap. I will require: resin - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
			dialog.Text = s2;		
			Link.l1 = "D'accord. J'accepte vos conditions. Je vous apporterai tout ce dont vous avez besoin.";
			Link.l1.go = "ship_c_quantity_start";		
			Link.l2 = "Non. Cela ne me convient pas.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_c_quantity_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Cannon 		= true;				
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 				
				NPChar.Tuning.ShipType      = Pchar.Ship.Type;
				NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;											    
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.text = "Excellent. J'attendrai le matériel.";
				link.l1 = LinkRandPhrase("Je vous assure que vous n'aurez pas à attendre longtemps. Je peux résoudre ces problèmes, d'accord ?","Considérez que vous les avez déjà et gardez le quai pour moi. Je serai aussi rapide que le vent.","Bien sûr. Je devrai simplement rendre visite à quelques personnes qui ont les choses que vous avez demandées, ha-ha !");
				link.l1.go = "Exit";			    
				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the number of cannons on the " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +						
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");				
			}		
			else
			{ 
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "Je ne vois pas l'acompte...";
				link.l1 = "Je repasserai plus tard.";
				link.l1.go = "Exit";
			}
		break;		
		
		case "ship_c_quantity_again":	
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Le temps passe, et le navire attend. Avez-vous apporté tout ce que j'ai demandé ?";
				Link.l1 = "Oui, j'ai réussi à trouver quelque chose.";
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = "Non, je suis encore dessus.";
				Link.l2.go = "Exit";
			}		
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.Text = "Manque"+GetSexPhrase("ter","s")+", avez-vous changé de navire depuis que nous avons conclu notre arrangement? Vous n'auriez pas dû.";
			    Link.l1 = "Hélas, ce sont toutes les circonstances ! Dommage que le dépôt ait été perdu...";
				Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
				AddQuestRecord("ShipTuning", "Lose");
				CloseQuestHeader("ShipTuning");
			}		
		break;
		
		case "ship_c_quantity_again_2":		
			checkMatherial(Pchar, NPChar, GOOD_OIL);
			if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.text = "Excellent, maintenant j'ai tout ce dont j'ai besoin. Je vais commencer à travailler, alors.";
				link.l1 = "J'attends.";
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "J'ai encore besoin de : résine - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Très bien.";
				link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}		
		break;
		
		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");		
			makearef(refShip, pchar.Ship);
			
			iCannonDiff = sti(refShip.CannonDiff);
			iCannonDiff -= 1;
								
			for (i = 0; i < sti(shTo.cannonr); i++)
			{
				attr = "c" + i;										
					
				if(i < (sti(shTo.cannonr) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0; 
					}	
				}					
			}	
			for (i = 0; i < sti(shTo.cannonl); i++)
			{
				attr = "c" + i;
				if(i < (sti(shTo.cannonl) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0; 
					}	
				}										
			}	
			
			if(CheckAttribute(shTo,"CannonsQuantityMax")) 	shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
			else										    shTo.Cannons = sti(shTo.CannonsQuantity) - iCannonDiff * 2;
			
			shTo.CannonsQuantity = sti(shTo.Cannons);
		
			refShip.Cannons = sti(shTo.Cannons);
			refShip.CannonDiff = iCannonDiff;			

			shTo.Tuning.Cannon = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			NextDiag.TempNode = "First time";
			dialog.Text = "... C'est tout, Capitaine. Vous pouvez utiliser des canons supplémentaires - c'est-à-dire, si vous les avez, hé-hé.";
			Link.l1 = "Merci !";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_CANNONS, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		case "Tasks":
			//--> Jason генератор Поиск корабля
			if (hrand(4) == 2 && !CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && sti(pchar.rank) < 19)
			{
				if (!CheckAttribute(npchar, "Findship") || GetNpcQuestPastDayParam(npchar, "Findship") >= 60) 
				{
					SelectFindship_ShipType(); //выбор типа корабля
					pchar.GenQuest.Findship.Shipyarder.ShipBaseName =  GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Findship.Shipyarder.ShipType), "Name") + "Acc")); // new
					pchar.GenQuest.Findship.Shipyarder.City = npchar.city; //город квестодателя
					dialog.text = "J'ai un problème qui doit être résolu. J'ai une commande pour un navire - "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+" Cependant, dans mon chantier, il n'y a pas un tel navire maintenant et dans les deux mois, je n'ai également aucune possibilité d'en obtenir un.\nSi vous pouvez me fournir un tel navire - je vous en serai très reconnaissant, et je vous paierai une somme une fois et demie supérieure à son prix de vente.";
					link.l1 = "Une offre intéressante. J'accepte !";
					link.l1.go = "Findship";
					link.l2 = "Ça ne m'intéresse pas.";
					link.l2.go = "Findship_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Findship");
					break;
				}
				
			}//<-- генератор Поиск корабля
			//Jason --> генератор Неудачливый вор
			if (hrand(6) == 1 && !CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && sti(pchar.rank) < 10 && npchar.city != "Charles")
			{
				if (!CheckAttribute(npchar, "Device")) 
				{
					switch (hrand(4))
					{
						case 0:  
							pchar.GenQuest.Device.Shipyarder.Type = "inside gage";
							pchar.GenQuest.Device.Shipyarder.Describe = "two hammered strips, connected with a joint unriveted on both ends";
						break; 
						case 1:  
							pchar.GenQuest.Device.Shipyarder.Type = "Swedish broad axe";
							pchar.GenQuest.Device.Shipyarder.Describe = "an axe on a long straight handle with a thin semicircular blade";
						break; 
						case 2:  
							pchar.GenQuest.Device.Shipyarder.Type = "groover";
							pchar.GenQuest.Device.Shipyarder.Describe = "a small axe, looking like a farmer's mattock";
						break; 
						case 3:  
							pchar.GenQuest.Device.Shipyarder.Type = "stockpile level";
							pchar.GenQuest.Device.Shipyarder.Describe = "two wooden bars of equal length, linked by the same third one, which has in the middle a rotating liquid-filled plate with an air bubble";
						break;
						case 4:  
							pchar.GenQuest.Device.Shipyarder.Type = "barsik";
							pchar.GenQuest.Device.Shipyarder.Describe = "an ordinary flail, but the chain is rod-shaped and only moves in one direction";
						break; 
					}
					dialog.text = "Tu arrives à point nommé. Peut-être pourras-tu m'aider. On m'a volé un instrument très précieux hier - "+pchar.GenQuest.Device.Shipyarder.Type+"Je n'ai pas la possibilité d'en faire un autre et je ne peux pas me permettre le temps ou le coût de le commander d'Europe. Et sans cela, je ne peux pas construire de navires normalement, tu sais ?\nEt le plus agaçant, c'est que cette chose n'est utile à personne sauf aux constructeurs de navires, et je suis le seul constructeur de navires dans la colonie. Ce voleur ne le vendra à personne et le jettera simplement. Peut-être que tu pourrais essayer de retrouver le voleur, te renseigner dans la ville, mais je n'ai tout simplement pas le temps de m'éloigner du chantier naval - j'ai besoin de terminer des commandes spéciales de toute urgence.";
					link.l1 = "D'accord, je vais essayer. Dis-moi, à quoi ressemblait cet... engin à toi ?";
					link.l1.go = "Device";
					link.l2 = "   Cela ne m'intéresse pas.   ";
					link.l2.go = "Device_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Device");
					break;
				}//<-- генератор Неудачливый вор
			}
			dialog.text = "Je n'ai rien de ce genre.";
			link.l1 = "Comme vous le dites.";
			link.l1.go = "exit";
		break;
		
		case "Findship_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		
		case "Device_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		
		//--> Jason генератор Поиск корабля
		case "Findship":
			pchar.GenQuest.Findship.Shipyarder = "begin";
			pchar.GenQuest.Findship.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Findship.Shipyarder.City = npchar.city;
			ReOpenQuestHeader("Findship");
			AddQuestRecord("Findship", "1");
			AddQuestUserData("Findship", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Findship.Shipyarder.City+"Gen"));
			AddQuestUserData("Findship", "sName", pchar.GenQuest.Findship.Shipyarder.Name);
			AddQuestUserData("Findship", "sShip", pchar.GenQuest.Findship.Shipyarder.ShipBaseName);
			SetFunctionTimerCondition("Findship_Over", 0, 0, 60, false);
			DialogExit();
		break;
		
		case "Findship_check":
			dialog.text = "Excellent ! Je suis très heureux que vous ayez réussi si rapidement. Où est ce navire ?";
			link.l1 = "At the moment the vessel is at the roadstead; her name is '"+pchar.GenQuest.Findship.Shipyarder.ShipName+"'.";
				link.l1.go = "Findship_complete";
				break;
		
		case "Findship_complete":
			pchar.quest.Findship_Over.over = "yes";//снять прерывание
			sld = GetCharacter(sti(pchar.GenQuest.Findship.Shipyarder.CompanionIndex));
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			dialog.text = "Voici votre argent - "+FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money))+"Merci pour le travail. N'oubliez pas de revenir me voir. Adieu!";
			link.l1 = "Adieu, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Findship.Shipyarder.Money));
			AddQuestRecord("Findship", "3");
			AddQuestUserData("Findship", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)));
			CloseQuestHeader("Findship");
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		//<-- генератор Поиск корабля
		
		//Jason --> генератор Неудачливый вор
		case "Device":
			pchar.GenQuest.Device.Shipyarder.Chance1 = rand(6);
			pchar.GenQuest.Device.Shipyarder.Chance2 = rand(3);
			pchar.GenQuest.Device.Shipyarder.Chance3 = rand(2);
			pchar.GenQuest.Device.Shipyarder.Chance4 = rand(4);
			pchar.GenQuest.Device.Shipyarder.Money = 12000+rand(8000);
			//генерируем тип корабля для бонуса сейчас, чтобы не сливали
			if (sti(pchar.rank) < 5) iType = sti(RandPhraseSimple(its(SHIP_BARKENTINE), its(SHIP_SLOOP)));
			if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 11) iType = sti(RandPhraseSimple(its(SHIP_SHNYAVA), its(SHIP_BARQUE)));
			if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 16) iType = sti(RandPhraseSimple(its(SHIP_BRIG), its(SHIP_FLEUT)));
			if (sti(pchar.rank) >= 16) iType = sti(LinkRandPhrase(its(SHIP_CORVETTE), its(SHIP_POLACRE), its(SHIP_GALEON_L)));
			pchar.GenQuest.Device.Shipyarder.Bonus = iType;
			dialog.text = "Bien sûr, je vais essayer de l'expliquer en des mots simples. On dirait que "+pchar.GenQuest.Device.Shipyarder.Describe+". C'est un objet unique, donc vous le reconnaîtrez très facilement. Si vous m'apportez cet instrument, je vous paierai généreusement.";
			link.l1 = "Compris. Je vais commencer ma recherche immédiatement !";
			link.l1.go = "exit";
			pchar.GenQuest.Device.Shipyarder = "begin";
			pchar.GenQuest.Device.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Device.Shipyarder.City = npchar.city;
			pchar.GenQuest.Device.Shipyarder.Nation = npchar.Nation;
			ReOpenQuestHeader("Device");
			AddQuestRecord("Device", "1");
			AddQuestUserData("Device", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Device.Shipyarder.City+"Voc"));
			AddQuestUserData("Device", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			AddQuestUserData("Device", "sDesc", pchar.GenQuest.Device.Shipyarder.Describe);
			SetFunctionTimerCondition("Device_Over", 0, 0, 30, false);
		break;
		
		case "Device_complete":
			pchar.quest.Device_Over.over = "yes";//снять прерывание
			dialog.text = "Vous l'avez fait ! Vous n'avez pas idée à quel point je vous suis reconnaissant ! J'avais déjà perdu tout espoir de revoir mon instrument.";
			link.l1 = "Voici pour vous.";
			link.l1.go = "Device_complete_1";
		break;
		
		case "Device_complete_1":
			RemoveItems(PChar, "Tool", 1);
			dialog.text = "Pour vos efforts, je vous paierai "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money))+" J'espère que ce serait une récompense méritée.";
			link.l1 = "Merci !";
			link.l1.go = "Device_complete_2";
		break;
		
		case "Device_complete_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Device.Shipyarder.Money));
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddQuestRecord("Device", "10");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)));
			CloseQuestHeader("Device");
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance4) == 3)
			{
				dialog.text = "De plus, j'aimerais vous faire une offre, en guise de gratitude supplémentaire.";
				link.l1 = "C'est intéressant. Eh bien, allez-y - j'aime les agréables surprises.";
				link.l1.go = "Device_complete_3";
			}
			else
			{
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
		break;
		
		case "Device_complete_3":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			dialog.text = "Je viens de lancer un nouveau navire - "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(iType,"Nom")+"Acc"))+". Il y a déjà plusieurs clients pour ce navire, mais je vous donnerai la priorité. Si ce navire vous plaît, et que le prix ne vous effraie pas - vous pouvez l'acheter.";
			link.l1 = "Heh ! Bien sûr, jetons un coup d'œil !";
			link.l1.go = "Device_complete_4";
			link.l2 = "Merci, mais mon navire actuel me convient parfaitement, et je ne cherche pas à le remplacer.";
			link.l2.go = "Device_complete_5";
		break;
		
		case "Device_complete_4":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(iType, NPChar), "ship10");
			DialogExit();
			LaunchShipyard(npchar);
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // лесник , митрокоста		   
		break;
		
		case "Device_complete_5":
			dialog.text = "Eh bien, comme vous le souhaitez. Merci encore - et bonne chance !";
			link.l1 = "Bonne chance à vous aussi !";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		// <-- генератор Неудачливый вор
		
		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Laisse-moi jeter un oeil... Non, il n'y avait personne comme lui. Je suppose que tu devrais voir le maître du port à ce sujet.";
				link.l1 = "Bien sûr...";
				link.l1.go = "exit";
			}
			else
			{
				sTemp = "Let me take a look, Captain! A-ha! Those are the ship documents of a good friend of mine, my favorite customer! I am sure he will be extremely happy because of your find and will reward you deservedly.";
				sTemp = sTemp + "I guess I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " pesos on his behalf";
				dialog.text = sTemp;
				link.l1 = "Non, je ne pense pas...";
				link.l1.go = "exit";
				link.l2 = "Merci, "+GetFullName(NPChar)+"! Je vous prie de transmettre mes respects à votre ami.";
				link.l2.go = "ShipLetters_7";				
			}	
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "4");		
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "Je vous écoute attentivement.";
			link.l1 = "J'ai amené votre fugitif.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, Capitaine, merci beaucoup! Comment va-t-elle? Est-elle blessée? Pourquoi s'est-elle enfuie? Pourquoi?\nNe comprend-elle pas? Le fiancé est un homme riche et important! La jeunesse est naïve et insensée... cruelle même. Souvenez-vous-en!";
			link.l1 = "Eh bien, vous êtes son père et la décision finale vous appartient, mais je ne me presserais pas avec le mariage...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Que sais-tu ? As-tu tes propres enfants ? Non ? Quand tu en auras un, viens me voir et nous parlerons. \nJ'ai promis une récompense à quiconque la ramènerait à la famille.";
			link.l1 = "Merci. Tu devrais la surveiller. J'ai le pressentiment qu'elle ne s'arrêtera pas là.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;		
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, alors vous êtes ce capitaine qui a amené à mon fils prodigue une jeune épouse ?";
				link.l1 = "Oui, c'était moi.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, là "+GetSexPhrase("il est, notre bienfaiteur","elle est, notre bienfaitrice")+"Attendant une récompense, je suppose ?";
				link.l1 = "Eh bien, je m'en passe de récompense, votre bonne parole suffira amplement.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Je vous suis très reconnaissant de ne pas avoir abandonné mon enfant dans le besoin et de l'avoir aidé à trouver une issue à une situation délicate. Permettez-moi de vous remercier et, je vous en prie, acceptez cette modeste somme et un cadeau de ma part.";
			link.l1 = "Merci. Aider ce jeune couple fut un plaisir.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Merci? Quels mercis?! Cela fait six mois que cet imbécile traîne sans travail - et regarde-le, il a assez de temps pour des amourettes ! Quand j'avais son âge, je gérais déjà ma propre affaire ! Pff ! Un gouverneur a une fille à marier - et cet idiot a ramené une traînée sans famille chez moi et a osé demander ma bénédiction !";
			link.l1 = "Hmm... Apparemment, vous ne croyez pas aux sentiments sincères?";
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
			dialog.text = "Quels sentiments ? De quels sentiments parles-tu ? Sentiments... comment peut-on être aussi léger d'esprit à ton âge ?! Honte à toi de céder aux caprices des jeunes et d'agir comme un proxénète ! Non seulement tu as enlevé une fille de chez elle, mais tu as aussi ruiné la vie de mon novice. Il n'y aura pas de remerciements pour toi. Adieu.";
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
		
		case "shipyard":
			if(CheckAttribute(npchar, "TrialDelQuestMark"))
			{
				DeleteAttribute(npchar, "TrialDelQuestMark");
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("PortRoyal");
			}
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Vous vous moquez de moi ? Où est votre navire ? Je ne le vois pas dans le port !","Je jure par le diable, tu ne me tromperas pas ! Ton navire n'est pas dans le port !"),pcharrepphrase("Je ne vois pas votre navire dans le port, Capitaine "+GetFullName(pchar)+" J'espère qu'elle n'est pas le 'Hollandais Volant'?","Capitaine, c'est beaucoup plus facile de charger la cargaison depuis le quai. Amenez votre navire au port et revenez."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Quelle galère ! D'accord, vieux renard, à bientôt !","Je ne voulais pas te tromper, "+GetFullName(npchar)+"un navire de l'autre côté de l'île."),pcharrepphrase("Non. Mon navire s'appelle le 'Perle Noire' ! Qu'est-ce qui est arrivé à ton visage ? Il est pâle... Haha ! Blague !","Merci pour le conseil, je m'assurerai de le faire."));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Tu te moques de moi ? Où est ton navire ? Je ne le vois pas au port !","Je jure devant le diable, tu ne me tromperas pas ! Ton navire n'est pas au port !"),pcharrepphrase("Je ne vois pas votre navire dans le port, Capitaine "+GetFullName(pchar)+". J'espère qu'elle n'est pas le 'Hollandais Volant'?","Capitaine, c'est bien plus facile de charger la cargaison depuis le quai. Amenez votre navire au port et revenez."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Quel tracas ! D'accord, vieux renard, à bientôt !","Je ne voulais pas te tromper, "+GetFullName(npchar)+", un navire de l'autre côté de l'île."),pcharrepphrase("Non. Mon navire s'appelle le 'Perle Noire' ! Qu'est-ce qui est arrivé à ton visage ? Il est pâle... Haha ! Blague !","Merci pour le conseil, je m'assurerai de le faire."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsGerald":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    dialog.text = "Changer la couleur des voiles coûte "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSCOLOR_PRICE_RATE))+", changer les armoiries coûte "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSGERALD_PRICE_RATE))+", remplacer les voiles - cela dépend de votre navire.";
							  
			    link.l1 = "Choisissez une nouvelle couleur.";
			    link.l1.go = "SailsColorChoose";
			    link.l2 = "Représentez un nouveau blason.";
			    link.l2.go = "SailsGeraldChoose";
				link.l3 = "Installer des voiles uniques."; 
				link.l3.go = "SailsTypeChoose";
			    Link.l9 = "J'ai changé d'avis.";
				Link.l9.go = "exit";
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Tu te moques de moi ? Où est ton navire ? Je ne le vois pas dans le port !","Je jure par le diable, vous ne me tromperez pas ! Votre navire n'est pas dans le port !"),pcharrepphrase("Je ne vois pas votre navire dans le port, Capitaine "+GetFullName(pchar)+"J'espère qu'elle n'est pas le 'Hollandais Volant' ?","Capitaine, c'est bien plus facile de charger la cargaison depuis le quai. Amenez votre navire au port et revenez."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Quel ennui ! D'accord, vieux roublard, à bientôt !","Je ne voulais pas te tromper, "+GetFullName(npchar)+", un navire de l'autre côté de l'île."),pcharrepphrase("Non. Mon navire s'appelle le 'Black Pearl' ! Qu'est-il arrivé à ton visage ? Il est pâle... Haha ! Blague !","Merci pour le conseil, je m'assurerai de le faire."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsTypeChoose":
			dialog.text = "Quelles voiles voulez-vous installer ? Pour l'instant vous avez "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+".";
            Link.l6 = "Je veux installer "+GetSailsType(6)+".";
			Link.l6.go = "SailsTypeChooseIDX_6";
			Link.l7 = "Je veux installer "+GetSailsType(7)+".";
			Link.l7.go = "SailsTypeChooseIDX_7";
			Link.l8 = "Je veux installer "+GetSailsType(8)+".";
			Link.l8.go = "SailsTypeChooseIDX_8";
			Link.l9 = "Je veux installer "+GetSailsType(9)+".";
			Link.l9.go = "SailsTypeChooseIDX_9";
			Link.l10 = "Je veux installer "+GetSailsType(10)+".";
			Link.l10.go = "SailsTypeChooseIDX_10";
			Link.l11 = "Je veux installer "+GetSailsType(11)+".";
			Link.l11.go = "SailsTypeChooseIDX_11";
			attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
			DeleteAttribute(Link, attrLoc);
		    Link.l99 = "J'ai changé d'avis.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChoose2":
            NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
			                                          sti(NPChar.SailsTypeChooseIDX),
													  stf(NPChar.ShipCostRate),
													  sti(RealShips[sti(Pchar.Ship.Type)].Price));
													  
			dialog.text = "Pour le moment, vous avez "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+", vous avez sélectionné "+GetSailsType(sti(NPChar.SailsTypeChooseIDX))+"Le coût du remplacement est "+FindRussianMoneyString(sti(NPChar.SailsTypeMoney))+"Procéder ?";

			if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
			{
	            Link.l1 = "Oui.";
				Link.l1.go = "SailsTypeChooseDone";
			}
		    Link.l99 = "Non.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChooseDone":
			AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
			dialog.text = "Excellent ! Tout ira bien.";
		    Link.l9 = "Merci.";
			Link.l9.go = "exit";

			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsColorChoose":
			if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
			{
				dialog.text = "Quelle couleur allons-nous choisir ? Le prix est "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSCOLOR_PRICE_RATE))+".";
				for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
				{
					if (CheckSailsColor(Pchar, i))
					{
						attrLoc = "l" + i;
						Link.(attrLoc) = XI_ConvertString(SailsColors[i].name);
						Link.(attrLoc).go = "SailsColorIdx_" + i;
					}
				}
			    Link.l99 = "J'ai changé d'avis.";
				Link.l99.go = "exit";
			}
			else
			{
				dialog.text = "Revenez quand vous aurez l'argent.";
			    Link.l9 = "D'accord.";
				Link.l9.go = "exit";	
			}
		break;
		
		case "SailsColorDone":
			AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
			dialog.text = "Entendu. Nous peindrons les voiles en "+GetStrSmallRegister(XI_ConvertString(SailsColors[sti(NPChar.SailsColorIdx)].name))+" couleur.";
		    Link.l9 = "Merci.";
			Link.l9.go = "exit";
			
			SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsGeraldChoose":
			if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
			{
				if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchSailsGeraldScreen(npchar);
				}
				else
				{
				    dialog.text = "Malheureusement, votre navire ne peut pas arborer des armoiries.";
				    Link.l9 = "C'est dommage.";
					Link.l9.go = "exit";
				}
			}
			else
			{
				dialog.text = "Revenez quand vous aurez l'argent.";
			    Link.l9 = "Bien.";
				Link.l9.go = "exit";	
			}
		break;

//--> -------------------------------------------Бремя гасконца---------------------------------------------------
		case "Sharlie":
			dialog.text = "Je suis désolé de vous décevoir, Monsieur, mais en ce moment je n'ai aucun navire à vendre.";
			link.l1 = "C'est vraiment étrange, car on m'avait dit que vous aviez un tout nouveau lougre à votre chantier naval.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
			{
				dialog.text = "Vous savez, c'est probablement à propos du lougre, pour lequel une caution de trois mille pesos a été versée par Michel de Monper ? Eh bien, ce navire a déjà été vendu, car selon le contrat, le montant total devait être payé au plus tard une semaine après la mise à l'eau du navire.\nTous les délais sont passés, et je n'ai pas reçu l'argent, donc le lougre a été vendu. Je suis vraiment désolé, Monsieur.";
				link.l1 = "Oui, c'était vraiment pas de chance, en effet... Mais es-tu sûr que tu n'as pas d'autres navires à vendre ?";
				link.l1.go = "Sharlie_6";
			}
			else
			{
			dialog.text = "Hmm. Oui, en effet. Mais...";
			link.l1 = "Et il y a déjà un acompte dessus - cinq mille pesos. Michel de Monper, qui a déposé l'argent, m'a accordé tous les droits sur ce navire.";
			link.l1.go = "Sharlie_2";
			}
		break;
		
		case "Sharlie_2":
			int iDay = 3-sti(GetQuestPastDayParam("questTemp.Sharlie_ship"));
			sTemp = "You only have "+FindRussianDaysString(iDay)+"";
			if (iDay == 0) sTemp = "Today is the last day";
			dialog.text = "Eh bien, si c'est ainsi, continuons notre conversation, Monsieur. Comme vous l'avez justement souligné, j'ai reçu l'acompte de cinq mille pesos pour le navire. Mais je pense que la valeur totale du navire est de quinze mille pesos, y compris les munitions. Donc, payez-moi dix mille et le navire est à vous.\nSelon le contrat, vous devez payer l'argent au plus tard une semaine après la mise à l'eau du navire."+sTemp+", et ensuite je suis libre de vendre ce navire à un autre client. Et, je vous préviens, il y en a déjà un, alors vous feriez bien de vous dépêcher.";
			if (sti(Pchar.money) >= 10000)
			{
				link.l1 = "Il n'y aura pas besoin de se presser. J'ai la somme requise sur moi en ce moment. Tenez, la voilà.";
				link.l1.go = "Sharlie_4";
			}
			link.l2 = "Bien, bien. Vous aurez votre argent, Monsieur. Je ne vous ferai pas attendre longtemps.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
			{
				dialog.text = "Puis-je vous aider, Monsieur ?";
				Link.l1 = "Je suis juste passé pour jeter un œil aux navires que vous avez de disponibles... Mais en ce moment, je suis un peu occupé - j'ai une affaire inachevée à régler. Je reviendrai dès que j'en aurai terminé.";
				Link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
			{	
				if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
				{
					dialog.text = "Monsieur, je vous avais prévenu que vous n'aviez que trois jours à votre disposition. Ils sont écoulés, et vous ne m'avez toujours pas apporté l'argent, donc notre accord a expiré, et j'ai vendu le navire à un autre client. Sans rancune.";
					link.l1 = "Ouais, c'était vraiment pas de chance, en effet... Mais êtes-vous sûr de ne pas avoir d'autres navires à vendre ?";
					link.l1.go = "Sharlie_6";
				}
				else
				{
					dialog.text = "As-tu apporté dix mille, Monsieur ?";
					if (sti(Pchar.money) >= 10000)
					{
						link.l1 = "Bien sûr que j'en ai. Tenez.";
						link.l1.go = "Sharlie_4";
					}
					link.l2 = "Non, j'y travaille encore.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Sharlie_3";
				}
			}
		break;
		
		case "Sharlie_4":
			AddMoneyToCharacter(pchar, -10000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "Permettez-moi donc de vous féliciter pour cet achat réussi. Le navire est à vous. J'espère qu'il vous servira bien.";
			link.l1 = "Merci !";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "lugger";
			pchar.questTemp.Sharlie = "crew";
			//стартовый люггер
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_LUGGER, 6, 800, 40, 610, 16000, 15.2, 58.8, 1.42);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			//UpgradeShipParameter(pchar, "Cannons");
			pchar.ship.HP = 732; */
			//UpgradeShipFull(pchar);
			UpgradeShipParameter(pchar, "Capacity");
			RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull  = "q"; // belamour особый скин
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddCharacterGoods(pchar, GOOD_BALLS, 100);
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddCharacterGoods(pchar, GOOD_POWDER, 220);
			pchar.Ship.name = "Adeline";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_6":
			if (sti(Pchar.money) >= 15000)
				{
					dialog.text = "Hmm... Eh bien, j'en ai un, en fait, mais je ne suis pas sûr qu'il vous convienne.";
					link.l1 = "Eh bien, je ne peux pas me permettre d'être trop difficile maintenant. Montre-moi ce que tu as !";
					link.l1.go = "Sharlie_7";
				}
				else
				{
					dialog.text = "Écoutez, Monsieur, commencez par amasser une fortune et ensuite posez vos questions sur les navires, d'accord ? Personne ici ne vous donnera rien gratuitement. Ai-je été clair ?";
					link.l1 = "Parfaitement clair, bien qu'il n'était pas nécessaire d'être grossier. Très bien, je reviendrai quand j'aurai l'argent.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Sharlie_shipwait";
				}
		break;
		
		case "Sharlie_7":
			dialog.text = "Alors regarde. J'ai récemment acheté à un prix raisonnable une goélette. C'était un ancien navire pirate, ses anciens propriétaires sont déjà pendus pour de nombreux crimes. Le navire, franchement, n'est pas aussi bon qu'un lougre et a aussi de lourds dommages, mais peut encore prendre la mer.\nJe n'ai pas le temps de la réparer maintenant - tous mes hommes sont occupés à construire une brigantine qui a été commandée, donc tu peux l'acheter de moi dans l'état où elle est. Considérant cela, je la vendrai moins cher que d'habitude, tout en incluant le contenu de la cale - quinze mille pesos.";
			link.l1 = "Marché conclu. Elle est en état de naviguer, et c'est tout ce qui compte. La Guadeloupe est à un jet de pierre - je la ferai réparer là-bas si tu n'as pas une telle opportunité.";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			AddMoneyToCharacter(pchar, -15000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "Permettez-moi de vous féliciter pour cet achat réussi. Le navire est à vous. J'espère qu'il vous servira bien.";
			link.l1 = "Merci!";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "sloop";
			pchar.questTemp.Sharlie = "crew";
			//стартовый шлюп
			pchar.Ship.Type = GenerateShipHand(SHIP_SLOOP, 6, 700, 50, 790, 20000, 13.1, 50.1, 1.25);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			AddCharacterGoods(pchar, GOOD_BALLS, 51);
			AddCharacterGoods(pchar, GOOD_GRAPES, 39);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 54);
			AddCharacterGoods(pchar, GOOD_BOMBS, 36);
			AddCharacterGoods(pchar, GOOD_POWDER, 231);
			pchar.Ship.name = "Black Hound";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS3;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_shipwait":
			dialog.text = "Alors, Monsieur, êtes-vous revenu avec l'argent ?";
			if (sti(Pchar.money) >= 15000)
			{
				link.l1 = "Ouais, je pense que j'ai assez pour me permettre un navire délabré.";
				link.l1.go = "Sharlie_7";
			}
			else
			{
				link.l1 = "Je n'en ai pas encore assez. Je suis juste passé pour jeter un coup d'œil...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_shipwait";
			}
		break;
//<-- -----------------------------------------Бремя гасконца-----------------------------------------------------
		// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
		case "FMQM_oil_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto5", "FMQM_Looking", -1);
			pchar.questTemp.FMQM = "remove_oil1";
		break;
		
		case "FMQM_oil_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil2";
		break;
		
		case "FMQM_oil_3":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil3";
		break;
		
		case "FMQM_oil_4":
			dialog.text = "Hélas, mon ami, mais nous avons tous deux souffert ici. Ils ont confisqué la résine, et en plus j'ai gaspillé une énorme somme d'argent pour ma caution. Et comment diable ont-ils appris notre opération ? Ça doit être l'un de mes ouvriers... Je vais m'occuper de ça, que le Seigneur ait pitié de la partie coupable !";
			link.l1 = "Ce qui signifie que tous mes efforts ont été vains...";
			link.l1.go = "FMQM_oil_5";
		break;
		
		case "FMQM_oil_5":
			dialog.text = "Je suis vraiment désolé, Capitaine. Nous ne pouvons rien faire ici, le destin est parfois une garce.";
			link.l1 = "Je vois. Très bien, je vais prendre congé alors. Adieu !";
			link.l1.go = "FMQM_oil_6";
		break;
		
		case "FMQM_oil_6":
			DialogExit();
			AddQuestRecord("FMQ_Martinique", "12");
			pchar.questTemp.FMQM = "officer";
			pchar.quest.FMQM_advice.win_condition.l1 = "location";
			pchar.quest.FMQM_advice.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FMQM_advice.function = "FMQM_GuideAdvice";
			DeleteAttribute(pchar, "questTemp.FMQM.Oil");
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_x":
            dialog.text = "Je voudrais revenir à cette conversation. Je suis prêt à offrir une bonne réduction... une réduction très importante pour tout travail sur votre navire... si vous me fournissez un peu de soie supplémentaire...";
			link.l1 = "Maître, allons droit au but. Je vous promets que je ne suis pas un espion et encore moins un des hommes du colonel D'Oyley. De plus, je travaille avec Marcus Tyrex, un nom dont vous devriez être familier. Alors, mettons cartes sur table. Je sais que vous avez besoin d'un approvisionnement régulier de toile de voile en soie, et Marcus Tyrex est prêt à vous l'apporter. Régulièrement aussi. Cependant, seulement si nous nous mettons d'accord sur le prix. Alors, passons directement à cela, maître ?";
			link.l1.go = "mtraxx_x_1";
		break;
		
		case "mtraxx_x_1":
            dialog.text = "Très bien. Il semble que je n'ai pas le choix dans cette affaire - soit vous travaillez pour D'Oyley et vous m'enverrez en prison, soit je ferai faillite si je ne trouve pas d'urgence une cargaison importante de soie. Je suis prêt à payer 25 doublons par pièce, mais seulement pour les grandes cargaisons, pas moins de 100 rouleaux.";
			link.l1 = "Alors, nous avons un accord. Je suis sûr que Tyrex est capable de vous fournir 100 rouleaux chaque mois.";
			link.l1.go = "mtraxx_x_2";
		break;
		
		case "mtraxx_x_2":
            dialog.text = "Ce serait des plus excellents ! Je pourrais acheter le premier lot immédiatement.";
			link.l1 = "Je ne peux pas le faire tout de suite, mais cela ne prendra pas longtemps. Un navire avec la cargaison dont vous avez besoin est à Capsterville en ce moment, je m'y rends immédiatement et je vous l'enverrai. Où devrions-nous faire le déchargement ?";
			link.l1.go = "mtraxx_x_3";
		break;
		
		case "mtraxx_x_3":
            dialog.text = "Arrangons cela ainsi. Entre le 10 et le 15 de chaque mois, chaque nuit, mes hommes attendront vos visiteurs à la baie... non, attendez, mieux au Cap Negril. Ce sera certes un long trajet, mais il y a beaucoup moins de patrouilles... Le mot de passe sera : 'Un marchand de Lyon'.";
			link.l1 = "Marché conclu, maître. Je me rends à Capsterville immédiatement.";
			link.l1.go = "mtraxx_x_4";
		break;
		
		case "mtraxx_x_4":
            dialog.text = "J'espère que votre navire arrivera vite, j'ai un besoin urgent de nouvelle soie.";
			link.l1 = "Ne t'inquiète pas, tout ira bien. Bon vent !";
			link.l1.go = "mtraxx_x_5";
		break;
		
		case "mtraxx_x_5":
			DialogExit();
            AddQuestRecord("Roger_2", "21");
			pchar.questTemp.Mtraxx = "silk_10"; // покупатель найден
			sld = characterFromId("Jeffry");
			sld.DeckDialogNode = "Jeffry_9";
		break;
		// Jason Исла Мона
		case "IslaMona":
			if (CheckAttribute(pchar, "questTemp.IslaMona.Shipyarder") && pchar.questTemp.IslaMona.Shipyarder == npchar.id)
			{
				if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
				{
					dialog.text = "Non, "+pchar.name+". Je n'ai rien contre vous, mais résolvez d'abord vos problèmes avec mon pays. Vendre un stock aussi précieux à un ennemi de la Couronne pourrait être mal interprété.";
					link.l1 = "Oui, et quand tu fais entrer des marchandises de contrebande d'origine douteuse dans des navires, vous êtes les meilleurs amis ? Attends-moi pour résoudre ce malentendu.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Disons. Pourquoi ? Construis-tu quelque chose ?";
					link.l1 = "Non, je fais une mission très spéciale. Pour un directeur de plantation.";
					link.l1.go = "IslaMona_1";
				}
			}
			else
			{
				npchar.quest.IslaMonaTools = "true";
				dialog.text = "Je ne peux pas vous aider.";
				link.l1 = "C'est une honte !";
				link.l1.go = "exit";
			}
		break;
		
		case "IslaMona_1":
            dialog.text = "Je vois. J'espère que ce gérant vous a fourni suffisamment, car je demanderais une bonne somme pour un ensemble comme celui-ci. Vous avez beaucoup de chance d'avoir eu récemment une importation de la métropole.";
			link.l1 = "Combien?";
			link.l1.go = "IslaMona_2";
		break;
		
		case "IslaMona_2":
			pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
            dialog.text = "Mille doublons d'or.";
			link.l1 = "Tu as l'air de surchauffer. Moi, je vais bien. Je le prends.";
			link.l1.go = "IslaMona_7";
			link.l2 = "C'est trop cher. Je doute qu'il y ait un autre acheteur pour l'ensemble complet comme moi. Une partie sera vendue, une autre partie sera volée par les vagabonds locaux. Que diriez-vous d'une remise?";
			link.l2.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				notification("Skill Check Failed (60)", SKILL_COMMERCE);
				dialog.text = "Je te garantis qu'elle réapparaîtra. Pas de changement de prix. Qu'en dis-tu ? Je n'attendrai pas longtemps.";
				link.l1 = "Très bien, d'accord, d'accord. Je le prends.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 900;
				dialog.text = "Très bien, nous en prendrons cent. Neuf cents. Je ne descendrai pas plus bas. Ne me le demandez pas.";
				link.l1 = "Et je ne le ferai pas. Je suis d'accord.";
				link.l1.go = "IslaMona_7";
				link.l2 = "Pourquoi ne me donnes-tu pas un peu plus? Comme un grossiste. Et ensuite je commanderai des réparations et des peintures chez toi, et la figure de proue la plus juteuse.";
				link.l2.go = "IslaMona_4";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
		break;
		
		case "IslaMona_4":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 85)
			{
				notification("Skill Check Failed (85)", SKILL_COMMERCE);
				dialog.text = "Je me fiche que tu commandes une gourgandine vivante. Neuf cents.";
				link.l1 = "D'accord, très bien, très bien. Je le prends.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 800;
				dialog.text = "Tu es sûr? Tu n'oublieras pas? Très bien, coupons une autre centaine. Mais c'est tout!";
				link.l1 = "Je n'oublierai pas. C'est un marché !";
				link.l1.go = "IslaMona_7";
				link.l2 = "Eh bien, comment puis-je dire cela...";
				link.l2.go = "IslaMona_5";
				AddCharacterExpToSkill(pchar, "Fortune", 200);
			}
		break;
		
		case "IslaMona_5":
            dialog.text = "Impensable ! "+pchar.name+", ils ont oublié d'enlever le plomb de ton crâne ? Aussi avide qu'un scorpion ! On a tous entendu parler de tes récentes escapades ! Tu as déjà amassé ton tas d'or, alors n'empêche pas les autres de gagner le leur. Un mot de plus et je ne vendrai pas à moins de mille.";
			link.l1 = "D'accord, d'accord ! Du calme. J'accepte.";
			link.l1.go = "IslaMona_7";
			link.l2 = "Mais, "+npchar.name+", j'ai des petits enfants ! Je dois aussi penser à eux ! On ne te paie pas assez pour le fret honnête, tu le sais !";
			link.l2.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 100)
			{
				notification("Skill Check Failed (100)", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
				dialog.text = "Les enfants des filles de bordel ne comptent pas, "+pchar.name+". J'en ai marre de toi. Mille doublons sur le tonneau, ou nous disons adieu.";
				link.l1 = "Que voulez-vous dire, ils ne le sont pas ? Hein. Je suis d'accord, vous êtes un escroc.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 800);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 700;
				dialog.text = "Je ne savais pas que tu avais des enfants. Et que les choses allaient si mal. D'accord, ne te plains pas. Sept cents. C'est presque une perte.";
				link.l1 = "Je n'oublierai pas. C'est un marché!";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Fortune", 400);
				Achievment_SetStat(106, 1);
			}
		break;
		
		case "IslaMona_7":
            dialog.text = "Alors, tu me dois "+sti(pchar.questTemp.IslaMona.Shipyarder.Money)+" doublons.";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.questTemp.IslaMona.Shipyarder.Money))
			{
				link.l1 = "Tiens, je te donne le dernier, je n'ai plus rien.";
				link.l1.go = "IslaMona_8";
			}
			else
			{
				if (GetCharacterItem(pchar, "gold_dublon") < 1)
				{
					link.l1 = "Attends, je vais chez l'usurier pour m'endetter.";
					link.l1.go = "IslaMona_money_exit";
				}
				else
				{
					link.l1 = "Tout ce que j'ai sur moi "+FindRussianDublonString(GetCharacterItem(pchar,"gold_dublon"))+"Prends ça, et je vais voir les usuriers.";
					link.l1.go = "IslaMona_money";
				}
			}
		break;
		
		case "IslaMona_money":
			pchar.questTemp.IslaMona.Shipyarder.Money = sti(pchar.questTemp.IslaMona.Shipyarder.Money)-GetCharacterItem(pchar, "gold_dublon");
			Log_Info("You gave "+FindRussianDublonString(GetCharacterItem(pchar, "gold_dublon"))+"");
			RemoveItems(pchar, "gold_dublon", GetCharacterItem(pchar, "gold_dublon"));
			PlaySound("interface\important_item.wav");
            dialog.text = "Ne t'inquiète pas pour moi, tu as un coffre de cabine rempli d'or. Tu me devras "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+".";
			link.l1 = "";
			link.l1.go = "IslaMona_money_exit";
		break;
		
		case "IslaMona_money_exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			npchar.quest.IslaMonaMoney = "true";
			pchar.questTemp.IslaMona = "dublon";
		break;
		
		case "IslaMona_8":
			Log_Info("You gave "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+"");
			RemoveItems(pchar, "gold_dublon", sti(pchar.questTemp.IslaMona.Shipyarder.Money));
			PlaySound("interface\important_item.wav");
            dialog.text = "C'est formidable. Le montant total est en place. Les outils seront livrés à votre navire. Ce sont des caisses lourdes.";
			link.l1 = "Merci, "+npchar.name+" !";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			GiveItem2Character(pchar, "islamona_toolbox");
			DeleteAttribute(pchar, "questTemp.IslaMona.Shipyarder");
			DeleteAttribute(npchar, "quest.IslaMonaMoney");
			AddQuestRecord("IslaMona", "2");
			pchar.questTemp.IslaMona = "get_tools";
		break;
	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}

// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	string sSail;
	
	switch (_type)
	{
	    case 1 : sSail = ""+XI_ConvertString("sails_1")+""; break;
	    case 2 : sSail = ""+XI_ConvertString("sails_2")+""; break;
	    case 3 : sSail = ""+XI_ConvertString("sails_3")+""; break;
		case 4 : sSail = ""+XI_ConvertString("sails_4")+""; break;
		case 5 : sSail = ""+XI_ConvertString("sails_5")+""; break;
		case 6 : sSail = ""+XI_ConvertString("sails_6")+""; break;
		case 7 : sSail = ""+XI_ConvertString("sails_7")+""; break;
		case 8 : sSail = ""+XI_ConvertString("sails_8")+""; break;
		case 9 : sSail = ""+XI_ConvertString("sails_9")+""; break;
		case 10 : sSail = ""+XI_ConvertString("sails_10")+""; break;
		case 11 : sSail = ""+XI_ConvertString("sails_11")+""; break;
	}
	return sSail;
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

void SelectFindship_ShipType()
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) <= 27) iRank = 3;
	
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
	}
	
	pchar.GenQuest.Findship.Shipyarder.ShipType = iShip;
}

// проверка количества материалов для корабельного тюнинга
void checkMatherial(ref Pchar, ref NPChar, int good)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Tuning.Matherial);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial);
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Tuning.Matherial = sti(NPChar.Tuning.Matherial) - amount;
}

/*
  _chr 		- ГГ
  NPChar 	- верфист
  MaterialNum -  номер материала для апгрейда 
	 1 - товар	 
	 2 - цена в дублонах(сундуки)
  Функция возвращает кол-во материала необходимого для данного типа апгрейда	  
*/

int GetMaterialQtyUpgrade( ref _chr, ref _nchar, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	float fQuestShip 	= 1.0;
	float LEcoeff       = 1.0; // legendary edition
		
	int   	shipClass     		= sti(RealShips[sti(_chr.Ship.Type)].Class);	
	int   	shipMinCrew   		= sti(RealShips[sti(_chr.Ship.Type)].MinCrew);	
	int 	shipPrice			= sti(RealShips[sti(_chr.Ship.Type)].Price);	
		
    if(shipClass == 4) LEcoeff = 0.38;
    if(shipClass > 4) LEcoeff = 0.25;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 	fQuestShip = 1.3;	

	if(MaterialNum == 1) 
	{
	int Material 	= makeint((40 * (8 - shipClass) + 25 * MOD_SKILL_ENEMY_RATE + hrand(shipMinCrew)) * fQuestShip * LEcoeff);
	if(Material < 1) 		Material 	= 1;
		return Material;
	}
	if(MaterialNum == 2)
	{
		int WorkPrice 	= 1;
		switch (shipClass)
		{
			case 1: 
				WorkPrice = 10;
			break;
			case 2: 
				WorkPrice = 7;
			break;
			case 3: 
				WorkPrice = 5;
			break;
			case 4: 
				WorkPrice = 3;
			break;
			case 5: 
				WorkPrice = 2;
			break;
			case 6: 
				WorkPrice = 1;
			break;
		}
		return WorkPrice;
	}
	
	return 0;
}
// belamour legendary edition тюнинг - проверка на сделанное
bool TuningAvailable()
{
	int num = 0;
    ref shTo = &RealShips[sti(Pchar.Ship.Type)];

	if(CheckAttribute(shTo, "Tuning.SpeedRate"))    num++;
	if(CheckAttribute(shTo, "Tuning.WindAgainst"))  num++;
	if(CheckAttribute(shTo, "Tuning.Cannon"))       num++;
	if(CheckAttribute(shTo, "Tuning.Capacity"))     num++;
	if(CheckAttribute(shTo, "Tuning.HP"))           num++;
	if(CheckAttribute(shTo, "Tuning.MaxCrew"))      num++;
	if(CheckAttribute(shTo, "Tuning.TurnRate"))     num++;
	if(CheckAttribute(shTo, "Tuning.MinCrew"))      num++;
	
	if(sti(shTo.Class) > 4 && num == 7 && !CheckAttribute(shTo, "Tuning.MinCrew"))
	{
		if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
	}
	
	if(num < 8) return true;
	else
    {
        if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
    }
}