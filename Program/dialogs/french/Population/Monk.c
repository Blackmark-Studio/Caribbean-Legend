//Jason общий диалог уличных монахов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

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
	
	iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = "Bonjour à vous, mon fils. Je vous demande de faire preuve de clémence et de donner quelques pièces d'argent pour le bien des pauvres, de votre âme et de la Sainte Mère Église.";
					link.l1 = "Eh bien, père, je suppose que nous devons tous nous entraider comme le Christ et Son Église nous l'enseignent. Pouvez-vous me dire où ira l'argent ?";
					link.l1.go = "donation";
					link.l2 = "Pardonnez-moi, père, mais je suis aussi pauvre qu'un rat d'église en ce moment.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)//монах-пассажир
				{
					dialog.text = "Bonjour à vous, mon fils. J'aimerais vous demander de me rendre un service. Je paierai bien sûr.";
					link.l1 = "Je vous écoute, mon père. Que désirez-vous ?";
					link.l1.go = "passenger";
					link.l2 = "Je suis tellement désolé, mon père, mais je dois partir.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))//корабельный капеллан
				{
					dialog.text = "Salutations, mon fils. Je suppose que vous êtes capitaine. J'ai donc une proposition pour vous.";
					link.l1 = "Je vous écoute, mon père.";
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(LinkRandPhrase("Salutations, mon fils. Qu'est-ce qui te tourmente?","Salutations, mon fils. Consultez le pasteur si vous voulez vous confesser.","Salutations, mon fils. 'Souviens-toi de ton Créateur aux jours de ta jeunesse.'"),LinkRandPhrase("Salutations, mon fils. Qu'est-ce qui te tracasse ?","Bonne journée à vous, mon fils, que Dieu vous bénisse !","Bonne journée à vous, mon fils, que le visage de Dieu brille sur vous !"));
				link.l1 = LinkRandPhrase("De même pour vous, père. Comment allez-vous?","Bonne journée à vous, père. Comment va votre paroisse ?","Comment allez-vous, mon père ?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("J'ai une question pour vous, mon père.","J'ai besoin d'informations.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
				{
					link.l3 = "Mon Père, j'ai des gens sur mon navire. Ce sont des esclaves, à la fois chrétiens et païens non baptisés. Je veux que vous baptisiez les païens et que vous administriez la communion aux chrétiens. Ensuite, je les libérerai tous pour la gloire de Dieu et de notre Église.";
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Mon père, je veux que vous bénissiez mon navire et offriez une messe pour mon équipage. Combien cela coûterait-il ?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Pardonnez-moi, mon père, mais je dois partir.","Désolé de vous déranger, mon père.","Je dois retourner à mon navire, mon père. Adieu !");
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = LinkRandPhrase("Encore toi, mon fils ? Que veux-tu ?","As-tu encore quelque chose à me raconter, mon fils?","Il est bon de te revoir, mon fils.");
				link.l1 = LinkRandPhrase("De même, père. Comment allez-vous?","Bonjour à vous, mon père. Comment va votre paroisse ?","Comment allez-vous, père ?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("J'ai une question pour vous, mon père.","J'ai besoin d'informations.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
					{
						link.l3 = "Mon père, j'ai des gens à bord de mon navire. Ce sont des esclaves, à la fois chrétiens et païens non baptisés. Je veux que vous baptisiez les païens et que vous administriez la communion aux chrétiens. Ensuite, je les libérerai tous pour la gloire de Dieu et de notre Église.";
						link.l3.go = "slaves";
					}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Père, je veux que vous bénissiez mon navire et offriez une messe pour mon équipage. Combien cela coûterait-il ?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Pardonnez-moi, mon père, mais je dois y aller.","Je suis désolé de vous déranger, mon père.","Je dois retourner à mon navire, père. Adieu !");
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "check":
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = "J'ai une affaire urgente pour toi, mon fils. Je dois livrer ces documents au pasteur de "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+". Naviguez-vous dans cette direction ? Les documents doivent être livrés dans deux semaines...";
				link.l1 = "Assez facile, père. Donnez-moi ces papiers et je les livrerai à "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+".";
				link.l1.go = "Monkletter";
				link.l2 = "Je serais heureux de le faire, mon père, mais je navigue dans une autre direction.";
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city;//город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = "Mon fils, accepteriez-vous de m'aider dans une affaire urgente ? Notre église manque de Bibles et de livres de prières que nous donnons à tous ceux qui en ont besoin\nPourriez-vous naviguer jusqu'à la colonie la plus proche "+NationNameGenitive(sti(npchar.nation))+", pour ramasser quelques bibles et livres de prières à l'église locale et les apporter ici ? Et essayez de le faire en un mois, il ne nous en reste plus beaucoup.";
				link.l1 = "J'aiderai votre église avec plaisir. Puis-je obtenir ces livres auprès de n'importe quel pasteur ?";
				link.l1.go = "Churchbooks";
				link.l2 = "Je serais ravi de le faire, père, mais je ne peux pas le faire maintenant.";
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}
			
			dialog.text = RandPhraseSimple("C'est bon, mon fils. Merci pour vos aimables paroles.","Notre paroisse va bien, mon fils. Merci de vos préoccupations.");
			link.l1 = "Je dois y aller alors, père.";
			link.l1.go = "exit";
		break;
		
//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = "Bien sûr, mon fils. "+sTemp+"Bonjour, monami.";
			link.l1 = "Quelle donation serait considérée comme suffisante ?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			dialog.text = "Tout dépend de votre bourse et de votre désir personnel, mon fils. 'Dieu aime celui qui donne avec joie.' Nous sommes profondément reconnaissants pour tout don.";
			link.l1 = "100 pesos";
			link.l1.go = "donation_rate_1";
			link.l2 = "1000 pesos";
			link.l2.go = "donation_rate_2";
			link.l3 = "5000 pesos";
			link.l3.go = "donation_rate_3";
			link.l4 = "10000 pesos";
			link.l4.go = "donation_rate_4";
		break;
		
		case "donation_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Merci pour les pieces, mon fils ! Elles serviront une bonne cause !";
				link.l1 = "Vous êtes le bienvenu, saint père.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "'Ne vous y trompez pas, Dieu ne se laisse pas railler. Car ce qu'un homme sème, cela aussi il le moissonnera. Celui qui sème dans sa chair moissonnera de la chair la corruption. Mais celui qui sème dans l'esprit moissonnera de l'esprit la vie éternelle.'";
				link.l1 = "Ha-ha ! Garde ton sermon pour toi, je ne fais pas de charité. Dégage !";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_2":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Je vous remercie, mon fils. Cette somme aidera vraiment notre mission paroissiale. Que Dieu vous bénisse !";
				link.l1 = "Bonne chance, père !";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCrewMorale(pchar, 2);
			}
			else
			{
				dialog.text = "La vengeance de Dieu vous attend, gredin ! Se moquer d'un serviteur de la sainte église du Christ est un blasphème !";
				link.l1 = "Ha-ha ! Je ne fais pas de charité. Déguerpis !";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_3":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Je n'aurais jamais imaginé que tu serais si généreux, mon fils ! Je te mentionnerai dans ma prochaine lettre à notre évêque et nous prierons pour toi chaque jour ! Je te bénis et accepte ton argent avec gratitude !";
				link.l1 = "L'argent ne vaut rien à moins qu'il ne soit utilisé pour les desseins de Dieu ! Bonne chance, père !";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCrewMorale(pchar, 3);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			}
			else
			{
				dialog.text = "La rétribution divine vous attend, maraud! Se moquer d'un serviteur de la sainte église du Christ est un blasphème!";
				link.l1 = "Ha-ha ! Je ne fais pas de charité. Fiche le camp !";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_4":
			if (sti(pchar.money) >= 10000)
			{
				AddMoneyToCharacter(pchar, -10000);
				dialog.text = "Quoi... Ai-je bien entendu ? Allez-vous vraiment donner dix mille pesos !? Je vous bénis et accepte votre argent avec gratitude. Je vous mentionnerai dans ma prochaine lettre à notre évêque et nous prierons pour vous chaque jour ! C'est une aide immense pour l'Église !";
				link.l1 = "'A qui on a beaucoup donné, on demandera beaucoup,' n'est-ce pas? Bonne chance, saint père.";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 10);
				AddCharacterExpToSkill(pchar, "Leadership", 60);
				AddCrewMorale(pchar, 5);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
				ChangeCrewExp(pchar, "Sailors", 5);
				ChangeCrewExp(pchar, "Cannoners", 5);
				ChangeCrewExp(pchar, "Soldiers", 5);
			}
			else
			{
				dialog.text = "Le châtiment de Dieu vous attend, coquin ! Se moquer d'un serviteur de la sainte église du Christ est un blasphème !";
				link.l1 = "Ha-ha! Je ne fais pas de charité. Dégage !";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterHealth(pchar, -5);
			LAi_CharacterDisableDialog(npchar);
		break;
		
//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = "Bien sûr, mon fils. C'est notre devoir sacré d'aider ces pauvres misérables. Je ferai ce que vous demandez.";
			link.l1 = "Merci, mon père. Je donnerai dix pièces de huit pour chaque prisonnier baptisé et administré.";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES)*10);
			dialog.text = "Bien que cela ne soit pas nécessaire, j'accepte avec gratitude votre frais de vol. Votre argent sera consacré à diverses missions de notre paroisse. Pourriez-vous me conduire à votre navire ?";
			link.l1 = "Oui, père. Suivez-moi.";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam("Two hours later"+ NewStr() +"Slaves were freed", "Monk_RemoveSlaves", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
//<-- отпустить рабов

//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
			//поиск старшего класса
			iTemp = 7;
			for (i=0; i<COMPANION_MAX; i++)
			{
				int iIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iIdx >= 0)
				{
					sld = GetCharacter(iIdx);
					if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
				}
			}
			switch (GetCompanionQuantity(pchar))
			{
				case 1: 
					sTemp = "I have only one ship in my squadron and it's "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = 5000*(7-iTemp);
				break;
				case 2:
					sTemp = "I have two ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(1.8*(5000*(7-iTemp)));
				break;
				case 3:
					sTemp = "I have three ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(2.6*(5000*(7-iTemp)));
				break;
				case 4:
					sTemp = "I have four ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(3.4*(5000*(7-iTemp)));
				break;
				case 5:
					sTemp = "I have five ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(7-iTemp)));
				break;
			}
			dialog.text = "Tout dépend du nombre total de navires dans votre escadre et de leur taille.";
			link.l1 = " "+sTemp+"";
			link.l1.go = "shipshine_1";
		break;
		
		case "shipshine_1":
			dialog.text = "Ca te coutera "+FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money))+", mon fils.";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = "Je peux vous payer cette somme, mon père. Prenez l'argent.";
				link.l1.go = "shipshine_2";
			}
			link.l2 = "Malheureusement, je n'ai pas autant d'argent sur moi.";
			link.l2.go = "shipshine_exit";
		break;
		
		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = "Très bien, mon fils. Laisse-moi rassembler les vases sacrés et nous irons au port.";
			link.l1 = "Suis-moi, père.";
			link.l1.go = "shipshine_3";
		break;
		
		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam("Several hours later"+ NewStr() +"The priest has held mass aboard your ship and blessed it", "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
//<-- освятить корабль

//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = "Bonjour capitaine, permettez-moi de me présenter. Je suis un prêtre et j'ai une certaine expérience en tant qu'aumônier à bord des navires de guerre. J'ai quitté mon dernier navire car le capitaine et moi avons eu quelques... désaccords moraux. Voulez-vous m'accueillir dans votre équipage ?";
			link.l1 = "Un pretre a bord ? Dites-moi, mon pere, que fait l'aumonier d'un navire ?";
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;
		
		case "capellan_1":
			dialog.text = "Eh bien, c'est tout à fait évident. Je prie Dieu pour vous et votre équipage, je célèbre la messe quotidiennement, je bénis vos hommes et j'écoute leurs confessions avant la bataille. La parole de Dieu accorde force aux mains et aux esprits de votre équipage. Votre équipage aura l'occasion de recevoir la communion et de se confesser régulièrement. Croyez-moi, un marin en état de grâce tiendra bon dans des situations où un impie tremblera. \nJe ne demande pas grand-chose pour moi-même : un paiement unique de cinquante mille pesos pour ma paroisse d'origine, une couchette simple dans une cabine et une table comme celle de vos officiers. Ce serait tout.";
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = "Intéressant... Vous avez raison, un bon capitaine doit veiller non seulement sur les corps de son équipage mais aussi sur leurs âmes. Bienvenue à bord, père !";
				link.l1.go = "capellan_2";
			}
			link.l2 = "Non, père. Je suis désolé, mais je ne peux pas me permettre vos services.";
			link.l2.go = "capellan_exit";
		break;
		
		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Merci de ta confiance, mon fils. Tu as dépensé ton argent judicieusement. Mais je te préviens, je ne sers que des capitaines dignes, qu'ils soient commerçants ou corsaires, cela n'a pas d'importance. Mais je ne prêcherai jamais à bord d'un navire pirate !\nDonc, si jamais tu hisses le pavillon noir du diable, je quitterai immédiatement ton navire au tout premier port.";
			link.l1 = "Je vais y réfléchir, mon père, et j'essaierai de ne pas vous décevoir. Veuillez monter à bord et vous présenter à l'équipage !";
			link.l1.go = "capellan_3";
		break;
		
		case "capellan_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "loc1", "Monk_Capellan", -1);
			pchar.questTemp.ShipCapellan.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.ShipCapellan.Yes = "true";//капеллан в команде
			Achievment_Set("ach_69");
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			npchar.reputation = 60;
		break;
		
		case "capellan_4":
			dialog.text = "As-tu besoin de quelque chose, mon fils ?";
			link.l1 = "Non, ce n'est rien, père.";
			link.l1.go = "exit";
			link.l2 = "Mon père, je voudrais que vous quittiez le navire au prochain port. Je ne m'expliquerai pas davantage.";
			link.l2.go = "capellan_5";
			NextDiag.TempNode = "capellan_4";
		break;
		
		case "capellan_5":
			dialog.text = "Très bien, mon fils. Vous êtes responsable ici. Je quitterai votre navire au prochain établissement.";
			link.l1 = "Merci pour votre compréhension, mon père.";
			link.l1.go = "capellan_6";
		break;
		
		case "capellan_6":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			ShipCapellan_Remove();
		break;
		
		case "capellan_7":
			dialog.text = "Fi, capitaine ! Je vous ai averti que je vous quitterais si vous hissiez le pavillon pirate ! Je quitte votre navire au prochain port. Je prierai pour votre repentir immédiat et votre retour au giron de la Sainte Mère Église.";
			link.l1 = "Eh bien, zut...";
			link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;
//<-- капеллан
	
//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				dialog.text = "Mon "+GetSexPhrase("fils","fille")+", je dois me rendre à "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+"C'est en cours "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Çà")+", pour "+FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty))+"Je te paierai "+FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money))+" pour cela. Que dis-tu?";
			}
			else
			{
				dialog.text = "Mon "+GetSexPhrase("fils","fille")+", le Seigneur agit de façon mystérieuse, et ainsi je cherche un capitaine fiable. Pouvez-vous m'aider à me rendre à "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+", qui est sur "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Ça")+"? Je comprends que c'est comme un voyage en Géhenne ardente, puisque nos ennemis ne dorment jamais. Et je comprends que tu n'es pas Jésus-Christ, mais je ne suis pas non plus un apôtre, et donc j'ai quelques économies. Veux-tu "+FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money))+" cela te suffit-il ?";
			}
			link.l1 = "Je suis d'accord, père.";
			link.l1.go = "passenger_1";
			link.l2 = "Je suis désolé, mon père, mais je navigue dans une autre direction. Je ne peux pas vous aider.";
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;
		
		case "passenger_exit":
			dialog.text = "C'est la volonté de Dieu pour tous, mon fils. J'attendrai un autre navire. Que la paix soit avec vous !";
			link.l1 = "Adieu, mon père.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Que Dieu vous bénisse ! Vous recevrez votre paiement lorsque nous arriverons à notre destination.";
			link.l1 = "Dirigez-vous vers mon navire, père. Nous partons bientôt.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "monk");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Monkpassenger.City+"Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City+"_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Merci, mon "+GetSexPhrase("fils","fille")+"Vous avez tenu votre promesse et c'est maintenant mon tour. Prenez votre argent comme je l'avais promis.";
			link.l1 = "Merci. Bonne chance, mon père.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Monkpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
//<-- монах-пассажир
		
//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter":
			dialog.text = "Tiens. Prends ce paquet, mon fils. Souviens-toi que tu n'as que deux semaines pour le livrer. Le pasteur l'attend. Va, et que Dieu soit avec toi !";
			link.l1 = "Je ne te décevrai pas, père. Adieu.";
			link.l1.go = "Monkletter_1";
		break;
		
		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
//<-- Церковная депеша
		
//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = "Oui. Vous pouvez les obtenir dans n'importe quelle colonie "+NationNameGenitive(sti(npchar.nation))+". Apportez tous les livres que vous trouverez à notre pasteur dans l'église. Que Dieu vous bénisse !";
			link.l1 = "Merci ! Vous recevrez vos livres bientôt.";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(4))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
				case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
				case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
				case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
				case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
			}
			OfficersReaction("good");
		break;
//<-- доставить молитвенники
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (hrand(9))
	{
		case 0: sText = "I am gathering money for building "+LinkRandPhrase("a chapel","an almshouse","a hospital")+". The local citizens give little in alms so I must ask prosperous men like you." break;
		case 1: sText = "I am gathering donations for our church. Sailors don't usually have much time to visit the house of God, but everyone must do his best in saving his own soul." break;
		case 2: sText = "I am gathering money to buy food and medicines for our poorhouse for the sick, widows, orphans, and infirm. Please donate sir, because there but for the grace of God go all of us." break;
		case 3: sText = "I am gathering money for new sacred vessels, the ones which we brought from Europe are battered with continual use. It's a duty for every Christian to take care of our Church." break;
		case 4: sText = "I am gathering money for our church's renovation, the roof is leaking terribly and the pews have to be repaired too. It's a duty for every Christian to take care of our Church." break;
		case 5: sText = "I am gathering money to pay the good artist who is able to paint the walls of our church and draw scenes from the Bible on them for those of our parish who cannot read. It's a duty for every Christian to take care about his Church." break;
		case 6: sText = "I am gathering money for a new high altar for our church. Our parish is poor and we would like a noble seat for the Blessed Sacrament. I do hope for your help." break;
		case 7: sText = "There are a lot of wounded sailors from pirate raids in our hospital. They need medicines and bandages. Pray help them, for you can really understand sufferings of the common sailors." break;
		case 8: sText = "I am trying to get money for clothes and food for our poorest citizens. The only hope they have is our holy church. Please help them." break;
		case 9: sText = "I am going to go deep in our island for missionary work to bring the light of Christ's Gospel to the lost souls of the pagan Indians. I am gathering funds for this expedition. Please help our good deed!" break;
	}
	return sText;
}
