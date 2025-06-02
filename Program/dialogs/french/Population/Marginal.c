//Jason общий диалог уличных контриков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Que veux-tu ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("J'ai une question pour vous.","J'ai besoin d'informations.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//захват пассажира
				{
					dialog.text = "Hé, capitaine ! Oui, toi. Viens ici, j'ai une affaire pour toi...";
					link.l1 = "Et quel est le marché ?";
					link.l1.go = "passenger";
					link.l2 = "Je suis pressé, ami. Peut-être la prochaine fois.";
					link.l2.go = "exit_quest";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Hé, capitaine, je suis occupé en ce moment. Que voulez-vous?","Que voulez-vous, capitaine ?","Capitaine, je ne suis pas d'humeur à parler. Que voulez-vous ?");
				link.l1 = "Salutation, "+GetAddress_FormToNPC(NPChar)+". Attendez une minute, je veux que vous me disiez quelque chose.";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("J'ai une question pour vous.","J'ai besoin d'informations.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "C'est rien, je suis en route pour la taverne...";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

//----------------------------------------захват пассажиров для выкупа------------------------------------------
			case "passenger":
				DeleteAttribute(npchar, "talker");
				dialog.text = "Hm. Vous êtes capitaine d'un navire mais vous n'avez pas l'air d'un marchand. On dirait que vous avez quelques pièces dans votre poche... Que diriez-vous d'obtenir des informations intéressantes en échange d'une poignée de doublons ?";
				link.l1 = "D'abord, prouve que tes informations valent une seule pièce de huit.";
				link.l1.go = "passenger_1";
			break;
		
			case "passenger_1":
				dialog.text = "C'est vrai, capitaine, c'est vrai. Cela coûte bien plus que ce que je demande. Donnez-moi l'or et je vous dirai quand et sur quel navire une personne très importante naviguera. Vous pourrez rançonner celle-ci pour un très bon prix... Je vous dirai même le nom de l'acheteur. Marché conclu ?";
				link.l1 = "Pas question ! Je ne suis pas un kidnappeur. Va-t'en !";
				link.l1.go = "exit_quest";
				link.l2 = "Et comment puis-je savoir que tu dis la vérité ?";
				link.l2.go = "passenger_2";
			break;
		
			case "passenger_2":
				pchar.GenQuest.Marginpassenger.Dublon = 70+hrand(5)*10;
				dialog.text = "Ce serait fort imprudent de vous duper, vieux loup de mer. Je vis dans cette ville et je n'ai pas besoin d'ennuis. Pour seulement "+sti(pchar.GenQuest.Marginpassenger.Dublon)+" doubloons Je fournirai des informations complètes. Vous gagnerez beaucoup plus.";
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Vous avez raison. Prenez l'or et commencez à parler.";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Je n'ai pas assez de pièces sur moi maintenant.";
				link.l2.go = "passenger_3";
				link.l3 = "Tu te moques de moi ? Payer de l'or véritable pour des promesses en l'air ? Va-t'en...";
				link.l3.go = "exit_quest";
			break;
		
			case "passenger_3":
				dialog.text = "Pas toi ? Très bien, cap'. Je peux attendre quelques jours de plus et cette information aussi. Trouve-moi quand tu auras ton or. Ce ne sera pas difficile de me trouver... aujourd'hui, ha-ha-ha !";
				link.l1 = "Ne montre pas tes dents comme ça. Très bien, je t'apporterai l'or... si je ne change pas d'avis. ";
				link.l1.go = "passenger_wait";
			break;
			
			case "passenger_wait":
			DialogExit();
				SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
				npchar.dialog.currentnode = "passenger_repeat";
			break;

			case "passenger_repeat":
				dialog.text = "As-tu apporté mon or ?";
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Oui. Prends-le. N'essaie même pas de mentir maintenant...";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Pas encore. Peut-être plus tard...";
				link.l2.go = "exit";
				Nextdiag.Tempnode = "passenger_repeat";
			break;
			
			case "passenger_4"://установка параметров
				pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
				RemoveItems(pchar, "gold_dublon", sti(pchar.GenQuest.Marginpassenger.Dublon));
				pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
				pchar.GenQuest.Marginpassenger.City = npchar.city;
				pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city); 
				pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
				pchar.GenQuest.Marginpassenger.Days = 10+hrand(5);
				pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
				pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
				pchar.GenQuest.Marginpassenger.Chance = 0.8+frand(0.4);
				SelectMarginpassengerParameter();
				log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
				dialog.text = "Garde ta poudre sèche, tu en auras bientôt besoin, cap. Maintenant écoute, dans "+FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days))+" un navire s'éloignera de notre colonie, le navire est "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Nom")))+" nommé '"+pchar.GenQuest.Marginpassenger.ShipName+"' et il se dirigera vers "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity+"Gen")+" . Il y aura un passager -  "+pchar.GenQuest.Marginpassenger.Text+", nommé "+pchar.GenQuest.Marginpassenger.q1Name+"\nLe capitaine "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Nom")+"Gen"))+" est un lâche comme tous les marchands, ha-ha-ha ! Peut-être que tu éviteras même de te battre. Fais-lui juste peur avec le diable et il te remettra la cible lui-même, hé-hé\nComme tu le comprends, "+pchar.GenQuest.Marginpassenger.Text1+", vous obtiendrez probablement vos pièces, oui, mais les autorités locales vous traqueront jusqu'à la mort après cela. Vous feriez mieux d'apporter votre proie à "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+"Vous y trouverez un homme nommé "+pchar.GenQuest.Marginpassenger.q2Name+"\n"+pchar.GenQuest.Marginpassenger.Text2+"et tu n'auras même pas besoin de dire ton nom. C'est à toi de décider où rançonner ton homme, mais ne mords pas plus que tu ne peux mâcher... Mais "+sti(pchar.GenQuest.Marginpassenger.Dublon)*4+"des doublons que vous pouvez demander à coup sûr. Compris ?";
				link.l1 = "Oui. Je vais retourner sur mon navire et l'écrire dans le journal de bord.";
				link.l1.go = "passenger_5";
			break;
		
			case "passenger_5":
				dialog.text = "Exactement ! Bon choix. Bien, cap', bonne chance dans cette tâche aisée. Ah oui, j'ai presque oublié : "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Nom")))+" ne naviguera pas du port mais d'une des baies voisines. Alors fais attention. Bonne chance et merci pour l'or !";
				link.l1 = "Je vous en prie. Ne dépensez pas tout en une seule nuit.";
				link.l1.go = "exit_quest";
				npchar.lifeday = 0;
				ReOpenQuestHeader("Marginpassenger");
				AddQuestRecord("Marginpassenger", "1");
				AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
				AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity));
				AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
				AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
				AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
				AddQuestUserData("Marginpassenger", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
				AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Voc")));
				AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
				AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
				pchar.GenQuest.Marginpassenger = "begin";
				SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
			break;
			
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Écoute, matelot, calme-toi et rengaine ton arme.","Écoute, camarade, calme-toi et rengaine ton arme.");
			link.l1 = LinkRandPhrase("Bien.","Bien.","Comme vous voulez.");
			link.l1.go = "exit";
		break;
		
		case "question":
			dialog.text = LinkRandPhrase("Ne tourne pas autour du pot, capitaine. Dis ce que tu veux !","Oh, très bien. Que voulez-vous ?","Des questions ? Bien, marin, je t'écoute.");
			link.l1 = LinkRandPhrase("Peux-tu me raconter les derniers potins ?","Est-ce qu'il s'est passé quelque chose d'intéressant ici récemment ?","Que se passe-t-il dans les Caraïbes ?");
			link.l1.go = "rumours_marginal";
		break;
		
		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void SelectMarginpassengerParameter()
{
	if (hrand(1) == 0)
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
		pchar.GenQuest.Marginpassenger.model = "women_"+(rand(5)+11);
		pchar.GenQuest.Marginpassenger.sex = "woman";
		pchar.GenQuest.Marginpassenger.ani = "towngirl";
		pchar.GenQuest.Marginpassenger.Text2 = "He wants to marry her and will pay a significant sum for the girl.";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "store keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the store keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	else
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
		pchar.GenQuest.Marginpassenger.model = "citiz_"+(rand(9)+11);
		pchar.GenQuest.Marginpassenger.sex = "man";
		pchar.GenQuest.Marginpassenger.ani = "man";
		pchar.GenQuest.Marginpassenger.Text2 = "He has been planning to ingratiate himself with this family and he will pay a lot for the prisoner ";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "trader's relative, shipmaster's";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipmaster";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	if (sti(pchar.rank) < 5) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 10) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 10 && sti(pchar.rank) < 17) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 17 && sti(pchar.rank) < 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
