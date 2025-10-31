// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tous les rumeurs de "+GetCityName(npchar.city)+"à votre service. Que souhaitez-vous savoir ?","Nous parlions justement de cela. Vous devez avoir oublié...","C'est la troisième fois aujourd'hui que tu parles d'une question...","Tu répètes tout comme un perroquet...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tu sais, "+NPChar.name+", peut-être la prochaine fois.","D'accord, j'ai oublié pour une raison quelconque...","Oui, c'est vraiment la troisième fois...","Oui...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga") // работорговец
            {
                link.l1 = "Écoutez, où puis-je trouver François Gontier ? Il était censé être déjà arrivé à Tortuga.";
                link.l1.go = "Tortuga_ratT_1";
            }
			// суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Je cherche Henri Thibaut. Où puis-je le trouver ?";
				link.l1.go = "terrapin";
			}
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Je cherche Henri Thibaut. Où puis-je le trouver ?";
				link.l1.go = "terrapin_2";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
			{
				link.l1 = "Dis-moi, un galion du nom de 'Santa Margarita' s'est-il arrêté récemment dans ta colonie ? Peut-être comme prise de corsaire ?";
                link.l1.go = "guardoftruth";
			}
			// Addon 2016-1 Jason Пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
			{
				link.l1 = "Ecoute mon vieux, je cherche Gaspard Parmentier. Où puis-je le trouver ?";
                link.l1.go = "mtraxx_jew";
			}
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(npchar, "quest.PZ.Ask.Block"))
			{
				link.l1 = "Peux-tu m'aider un peu, camarade? Je cherche un homme qui s'appelle Joep van der Vink. Le connais-tu?";
				link.l1.go = "PZ_1";
			}
        break;
        
		case "Tortuga_ratT_1":
			dialog.text = "Francois Gontier ? Qui est-ce ? Je ne connais aucun homme de ce nom.";
			link.l1 = "Il est capitaine de la corvette '"+pchar.questTemp.Slavetrader.ShipName+".";
			link.l1.go = "Tortuga_ratT_2";
        break;
		
		case "Tortuga_ratT_2":
			dialog.text = "Je n'en ai pas la moindre idée, matelot. Et aucune corvette de ce nom n'a accosté à notre port, ça je peux te l'assurer.";
			link.l1 = "Très bien, avez-vous vu des étrangers en ville dernièrement ?";
			link.l1.go = "Tortuga_ratT_3";
        break;
		
		case "Tortuga_ratT_3":
			dialog.text = "Bonne question ! C'est une ville portuaire, pas un village. Des étrangers passent chaque jour. Bien que j'aie entendu parler de cinq gars bizarres, ils restent toujours ensemble et gardent leurs lames prêtes.\nMême la patrouille a posé des questions à leur sujet sans résultat. Mais je suis sûr qu'ils ne sont pas arrivés ici sur une corvette, aucun tel navire n'a été vu dans les parages, compris ?";
			link.l1 = "Hm... D'accord alors, je vois. Merci, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//затычка
        break;
		
		// суп из черепахи
		case "terrapin":
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Monsieur Thibaut est un homme célèbre à Tortuga. Sa demeure est située près de l'administration portuaire. En quittant la taverne, allez tout droit vers le port. Approchez l'arche menant au port, tournez à gauche au carrefour et descendez jusqu'au bout de la rue où vous tomberez sur un bâtiment en pierre à deux étages avec un toit rouge. C'est le manoir de Monsieur Thibaut.";
			link.l1 = "Merci! Je vais aller lui rendre visite...";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			DialogExit();
			pchar.questTemp.Terrapin = "house";
			sld = characterFromId("Tibo");
			ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
			LAi_SetOwnerType(sld);
		break;
		
		case "terrapin_2":
			dialog.text = "Monsieur Thibaut est très demandé aujourd'hui, un messager du gouverneur vient juste de passer ici. Il était également intéressé. Est-ce si difficile de le trouver ? Il loue une chambre chez moi au deuxième étage depuis un bon moment, bien qu'il ait un manoir tout entier où vivre. Je ne sais pas à quoi cela lui sert, mais il entre beaucoup plus souvent qu'il ne sort. Et il n'est là que le soir.";
			link.l1 = "Peut-être qu'il est ici en ce moment.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
			{
				dialog.text = "Non. Il a dit qu'il ne reviendrait pas avant huit heures du soir aujourd'hui. Vous pouvez essayer de le chercher chez lui dans son manoir, mais je ne pense pas que vous le trouverez là-bas. Je l'ai vu naviguer sur une chaloupe de patrouille en mer.";
				link.l1 = "Merci! Je passerai le voir plus tard.";
				link.l1.go = "terrapin_4";
			}
			else
			{
				dialog.text = "Oui. Si tu veux, tu peux monter.";
				link.l1 = "Merci ! Je vais aller le voir...";
				link.l1.go = "terrapin_4";
			}
		break;
		
		case "terrapin_4":
			DialogExit();
			pchar.questTemp.Terrapin = "tavern";
			sld = characterFromId("Tibo");
			sld.dialog.currentnode = "tibo_9";
			LAi_SetLoginTime(sld, 20.0, 8.0);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // откроем комнату
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);//запретить драться
			LAi_SetStayType(sld);
			// Addon 2016-1 Jason Пиратская линейка
			if (GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			if (GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Aucune idée du nom du navire, était-ce 'Santa Margarita' ou 'Putain Castillane', mais ils ont amené ici un galion espagnol capturé. Capturé par un sloop, rien de moins ! Voilà de la navigation comme il se doit ! Gaius Marchais, son capitaine, se vante depuis deux jours dans une taverne - son premier voyage et un tel prix !\nOui, très héroïque acte, d'aborder un galion rempli de rats d'église sans soldats pour les garder. Il semble que ces bâtards papistes ont oublié ce qu'ils disent sur ceux qui se servent eux-mêmes...";
			link.l1 = "Oui, Dieu aide celui qui s'aide lui-même, c'est sûrement un dicton huguenot. Comment puis-je avoir un aperçu de ce capitaine chanceux ? Est-il ici, à Tortuga ?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ah, qui diable sait. Je ne l'ai pas vu dans ma taverne depuis longtemps. Dès qu'il a dégrisé, il a acheté un navire flambant neuf avec l'argent du prix et a couru sur son pont comme un forcené. Je n'ai aucune idée d'où se trouve Marchais maintenant. Peut-être qu'il est à la Tortue ou peut-être en mer.";
			link.l1 = "D'accord. Eh bien, merci pour l'histoire, mon pote!";
			link.l1.go = "guardoftruth_2";			
		break;
		
		case "guardoftruth_2":
			dialog.text = "À tout moment, Monsieur. Je suis toujours heureux d'aider notre bien-aimé Capitaine "+pchar.name+", sauveur de St. Pierre ! Passez plus tard !";
			link.l1 = "... ";
			link.l1.go = "exit";	
			AddQuestRecord("Guardoftruth", "8");
			pchar.questTemp.Guardoftruth = "tortuga1";
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_jew":
            dialog.text = "On dirait que Gaspard devient de plus en plus populaire parmi les vôtres. Sa maison est près du mur. Tournez à gauche en sortant de la taverne et dirigez-vous vers le port, mais n'y allez pas, tournez à nouveau à gauche, allez tout droit puis tournez à droite. Une maison à deux étages.";
			link.l1 = "Merci !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
		break;
		
		case "PZ_1":
			dialog.text = "Jamais entendu parler de lui.";
			link.l1 = "Peut-être qu'il se fait appeler autrement. Peut-être avez-vous entendu parler de lui comme du capitaine du brigantin 'Banten' ?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Jamais entendu parler de ce brick non plus.";
			link.l1 = "J'ai entendu dire qu'il était ici récemment. Peut-être qu'un peu d'argent rafraîchira ta mémoire ?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			npchar.quest.PZ.Ask.Block = true;
			
			dialog.text = "Eh bien, demandez d'où vous avez entendu ça. Cela dit, je ne suis pas contre l'idée de prendre votre argent.";
			link.l1 = "Pas d'argent cette fois, alors. Adieu.";
			link.l1.go = "Exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
