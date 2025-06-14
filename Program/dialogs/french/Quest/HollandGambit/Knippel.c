// Чарли Книппель - старый артиллерист
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		//ветка на взятие 2 варианта прохождения - за Англию
		if(CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "Ahoy, l'ami, enchaîne-moi le cul! Qu'est-ce qui t'amène ici?";
			link.l1 = "Tire à chaîne votre... quoi ? Oh peu importe, je voulais juste dire bonjour.";
			link.l1.go = "exit";
			link.l2 = "Salutations, Monsieur Knippel. Ha, je vois pourquoi on vous appelle Knippel. Quoi qu'il en soit, il y a des rumeurs selon lesquelles vous auriez servi dans la marine anglaise. J'ai un excellent navire et un équipage compétent. Je voudrais offrir mes services et ceux de mon navire à la Couronne anglaise... euh... au Commonwealth. Pouvez-vous me donner des conseils ou me recommander à quelqu'un ou, peut-être, m'aider dans cette affaire ?";
			link.l2.go = "Knippel_check";
			break;
		}
		//за Голландию
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "Ahoymatelot, chaînede boulets mon cul ! Qu'est-ce qui t'amène ici ?";
				link.l1 = "Salutations, M. Knippel. Ha, je vois pourquoi on vous appelle Knippel. Il y a des rumeurs selon lesquelles vous avez servi dans la Marine anglaise, c'est pour cela que je souhaite vous demander de l'aide...";
				link.l1.go = "Dominica";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Chaîne de fer, mon cul ! Que veux-tu, camarade ?";
			link.l1 = "Non, ce n'est rien. Je m'en vais.";
			link.l1.go = "exit";
			break;
		}
		//за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "Ahoy capitaine, j'ai entendu des rumeurs sur un convoi d'argent intercepté...";
				link.l1 = "Vous êtes bien informé, M. Knippel.";
				link.l1.go = "HollConvoy_Check";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Wait")
			{
				dialog.text = "Des questions, capitaine ?";
				link.l1 = "Non, ce n'est rien. Je m'en vais.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main")
			{
				dialog.text = "Je suis heureux de vous voir, cap'tain ! Mon commandant Richard Fleetwood allait venir ici pour vous rencontrer lui-même, mais un accident s'est produit hier soir... Quelqu'un a essayé de le tuer en plein milieu de la rue, boulet enchainé mon cul !";
				link.l1 = "Impossible ! Que faisaient les gardes ?";
				link.l1.go = "Fleetwood_house";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Des questions, capitaine ?";
			link.l1 = "Non, ce n'est rien. Je m'en vais.";
			link.l1.go = "exit";
		break;
		}
			dialog.text = "Ahoy matelot, chain shot mon cul ! Qu'est-ce qui t'amène ici ?";
			link.l1 = "Bonjour, juste de passage.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------за Голландию--------------------------------------------------	
		case "Dominica":
			dialog.text = "Ahoy, vraiment ? Et comment un vieux loup de mer retiré depuis longtemps peut-il t'aider, matelot ?";
			link.l1 = "Voyez... Je ne suis qu'un capitaine ordinaire et je fais des voyages réguliers entre la Martinique et Curaçao. Donc, j'ai été attaqué deux fois par le navire fantôme non loin de la Martinique... Mais voilà, elle n'est ni Fata Morgana ni le Hollandais volant. J'ai pu déchirer ses voiles avec de simples boulets de canon !";
			link.l1.go = "Dominica_1";			
		break;
		
		case "Dominica_1":
			dialog.text = "Vraiment ? Ce n'est certainement pas dans les habitudes d'un vaisseau fantôme de perdre sa toile à cause d'un coup solide, sacrebleu...";
			link.l1 = "Nous avons survécu uniquement parce que mon navire pouvait le distancer en naviguant au plus près du vent. La dernière fois, j'ai dû jeter toute ma cargaison par-dessus bord pour alléger ma coque et m'enfuir... peux-tu imaginer la perte ? C'est déchirant !";
			link.l1.go = "Dominica_2";			
		break;
		
		case "Dominica_2":
			dialog.text = "Par tous les diables, capitaine...";
			link.l1 = "Mathias Beck, le gouverneur de Curaçao, a simplement écarté mes plaintes. Il a dit que les histoires du navire fantôme sont des balivernes et que mes guetteurs étaient ivres de grog. Le gouverneur de la Martinique a promis d'envoyer une patrouille là-bas, mais ses yeux m'ont dit qu'il ne se soucie pas de faire quoi que ce soit. Je ne peux pas retourner en Martinique tant que ce maudit pirate 'fantôme' rôde dans les parages. Mon navire est petit tout comme mon équipage, il est probable que nous ne survivrons pas à la troisième rencontre avec lui...";
			link.l1.go = "Dominica_3";			
		break;
		
		case "Dominica_3":
			dialog.text = "C'est une honte criante, matelot. Mais comment puis-je t'aider?";
			link.l1 = "J'ai entendu dire par les marins d'ici qu'il y avait un capitaine ici à St. John's du nom de Richard Fleetwood qui a chassé ce même vaisseau fantôme. Je ne le connais pas personnellement, c'est pourquoi je te raconte cette histoire, peut-être pourrais-tu lui transmettre le récit de mes malheurs ? Je suis sûr que le sale pirate se cache quelque part près des côtes sauvages de la Dominique et fait des raids entre la Barbade et la Martinique.";
			link.l1.go = "Dominica_4";			
		break;
		
		case "Dominica_4":
			dialog.text = "Entre la Barbade et la Martinique ? Ya har ! Une route commerciale grasse et riche. Ça ressemble bien à quelque chose que ce rat de cale ferait.";
			link.l1 = "Je ne suis ni riche ni gros, et je n'ai pas d'argent pour soudoyer un capitaine naval pour une escorte militaire. Mais, si Sir Fleetwood traque déjà ce rat de fond de cale, pourriez-vous lui dire où il pourrait trouver ce 'Hollandais Volant'?";
			link.l1.go = "Dominica_5";			
		break;
		
		case "Dominica_5":
			dialog.text = "Tu as bien fait de venir ici, camarade. Je raconterai ton histoire aux bonnes personnes, par le foie de ma chaîne ! Bientôt, tu pourras commercer à nouveau avec la Martinique.";
			link.l1 = "J'espère que Dieu entendra vos paroles ! Merci de m'écouter, Charlie. Je souhaite que tout se passe pour le mieux. Adieu et esquive les boulets ramés !";
			link.l1.go = "Dominica_6";			
		break;
		
		case "Dominica_6":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toDominica";
			AddQuestRecord("Holl_Gambit", "1-17");
			pchar.quest.toDominica.win_condition.l1 = "location";
			pchar.quest.toDominica.win_condition.l1.location = "Dominica";
			pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
			DelMapQuestMarkShore("Shore1");
			DelMapQuestMarkShore("Shore2");
			AddMapQuestMarkIsland("Dominica", true);
		break;

//----------------------------------------------за Англию--------------------------------------------------	
		case "Knippel_check"://начинаем проверять нашего ГГ по всем статьям
			if(makeint(PChar.reputation.nobility) < 48)//низкая репа
			{
				// belamour legendary edition покажем критерии
				notification("Reputation Too Low! (Adventurer)", "None");
				PlaySound("Voice\English\hambit\Charlie Knippel-04.wav");
				dialog.text = "Le joyeux vieux Angleterre n'a pas besoin de services de vauriens, boulet ramé mon cul ! Respectueusement, vous pouvez aller vous faire foutre.";
				link.l1 = "Hey hey mate, surveille ton langage ou je te le coudrai fermé !";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Reputation Check Passed", "None");
			}
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 30)//низкая навигация
			{
				dialog.text = "Capitaine, je vais être franc. Vous ne pourriez pas naviguer hors d'un sac mouillé. Revenez quand vous aurez plus de compétences en navigation, compris?";
				// belamour legendary edition покажем критерии  -->
				notification("Skill Check Failed (30)", SKILL_SAILING);
				//<--
				dialog.text = "Cap'taine, notre flotte a besoin de capitaines expérimentés, pas de marins d'eau douce. Reviens quand tu auras maîtrisé l'art de la navigation.";							 
				link.l1 = "Je vois... Alors je vous verrai plus tard.";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Skill Check Passed", SKILL_SAILING);
			}
			dialog.text = "Aho, tu arrives juste à temps, cap'taine, bordée de chain shot à mon cul! Richard ne savait pas sur qui il pouvait compter pour cette affaire risquée, il envisageait même de la décliner... Alors les petits oiseaux de l'opportunité chantent doucement à tes oreilles aujourd'hui. Si tu te montres à la hauteur de nos attentes, je te recommanderai à un homme très important. As-tu assez de plomb dans ta braguette pour t'en charger?";
			link.l1 = "Je suis chargé à la mitraille, Monsieur Knippel.";
			link.l1.go = "Knippel_task";
		break;
		
		case "Knippel_task"://первое задание
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Lucas"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Ar har ! Je vois que ton coq est dressé, cap'taine ! Bientôt le feu jaillira ! Maintenant, écoute attentivement. La flotte d'argent de la Compagnie néerlandaise des Indes occidentales a quitté Willemstad à Curaçao il y a un ou deux jours. Elle se dirige vers Philipsburg. Cette fois-ci, il n'y a que quelques navires dans la flotte. Un seul Galion avec l'argent dans sa cale, accompagné de deux escortes. Intercepte la flotte d'argent, capture l'Galion avec la cargaison d'argent et amène-le à Antigua. Tu peux couler les escortes, elles sont sacrifiables. Vise leurs tripes avec des boulets ramés, yar !";
			link.l1 = "Leurs jours sont comptés.";
			link.l1.go = "Knippel_task_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_task_1":
			dialog.text = "Un conseil, capitaine. La route commerciale de Curaçao à Saint-Martin ne se trouve pas loin des côtes de Saint-Christophe. Je vous conseillerais de préparer une embuscade là-bas. Préparez-vous, ainsi que votre navire, bien pour cette rencontre. Se frotter à la Compagnie des Indes occidentales n'est pas une promenade dans le parc avec une jolie fille.";
			link.l1 = "Je sais dans quoi je m'engage, mais j'apprécie votre franchise, Monsieur Knippel. Je reviendrai avec l'argent hollandais.";
			link.l1.go = "Knippel_task_2";			
		break;
		
		case "Knippel_task_2":
			DialogExit();
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Eng = "true";//признак, что английка уже бралась
			HWICSilverConvoyInWorld();
			AddQuestRecord("Holl_Gambit", "2-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила ,чтобы вышел из архива. 																				   
			pchar.questTemp.HWIC.Eng = "begin";
			SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;
		
		case "HollConvoy_Check"://начинаем проверять
			int iHal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_GALEON_L) iHal++;
				}
			}//признак наличия ТГ в компаньонах
			if (iHal > 0)
			{
				amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
				if (amount <= 0)
				{
					dialog.text = "Aucun besoin de me raconter ce qui s'est passé, cap'taine. J'ai été informé de tout pendant que l'agent des douanes inspectait votre navire... Vous avez fait du bon travail, cap'taine. Vraiment excellent ! Ça n'avait pas l'air facile, boulets ramés mon cul !";
					link.l1 = "C'est agréable d'être apprécié.";
					link.l1.go = "HollConvoy_complete";
				}
				else
				{
					dialog.text = "Pas besoin de me dire ce qui s'est passé, l'ami. J'ai été informé de tout pendant que l'agent des douanes inspectait ton navire... Tu n'as pas ramené tout l'argent, à d'autres mes salades de boulets ramés ! Je sais exactement combien d'argent il y avait sur ce navire de l'Inde Orientale au peso près. Cette mission avait pour but non seulement de tester tes compétences de combat, mais aussi de tester ton honnêteté. Tu as échoué sur ce dernier point. Sors de ma maison, moussaillon !";
					link.l1 = "Au diable avec toi alors, simplet!";
					link.l1.go = "HollConvoy_fail";
				}
			}
			else
			{
				dialog.text = "Halte-là, matelot. Je ne vois pas le navire hollandais des Indes orientales dans ton escadron. Je t'avais dit de l'amener ici comme prise. Tu l'as vendue et as essayé de garder l'argent pour toi, hein ?";
				link.l1 = "Attends, je devais amener le navire ? Je pensais que tu voulais seulement l'argent.";
				link.l1.go = "HollConvoy_noShip";
			}
		break;
		
		case "HollConvoy_noShip":
			dialog.text = "Personne ne prend Charlie Knippel pour un imbécile, l'ami ! Je me souviens clairement de ce que je t'ai dit et de ce que je ne t'ai pas dit. Tu as rompu les termes de notre accord et aucun Anglais honnête ne travaillera avec toi, il n'y a pas de place pour les vauriens ici. Sors de chez moi, matelot !";
			link.l1 = "Au diable avec toi alors, simplet !";
			link.l1.go = "HollConvoy_fail";
		break;
		
		case "HollConvoy_fail":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-3");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Eng");//зачищаем для возможности отката к голландскому варианту
			pchar.questTemp.HWIC.Fail2 = "true";
		break;
		
		case "HollConvoy_complete":
			dialog.text = "Rendez-moi visite demain et je vous présenterai à mon patron. Il vous proposera du travail à la hauteur de vos compétences. De plus, il s'occupera de votre...incitation financière. Levez l'ancre !";
			link.l1 = "Très bien, Monsieur Knippel. Je serai ici demain.";
			link.l1.go = "exit";
			npchar.greeting = "knippel_2";
			AddDialogExitQuestFunction("HollConvoy_Remove");
			AddQuestRecord("Holl_Gambit", "2-4");
			SetTimerFunction("EnglandGambit_2_ZadanieStart", 0, 0, 1);
			pchar.questTemp.HWIC.Eng = "Wait";
			AddSimpleRumourCity("They say that you captured a Dutch ship filled with silver. Well done! You are a valiant sailor, captain! Godspeed!", "SentJons", 10, 3, "");
		break;
		
		case "Fleetwood_house":
			dialog.text = "Je me suis posé la même question... Un salaud a jeté du poivre dans les yeux du capitaine Fleetwood et l'a poignardé dans la poitrine avant que Richard ne puisse même saisir sa lame. L'assassin espérait en finir avec le capitaine d'un seul coup, puisqu'il n'avait pas le temps pour un autre, mais il a échoué. Le capitaine Fleetwood porte toujours une cuirasse sous son manteau\nLa vermine immonde, balle à chaîne dans son foie, a réussi à fuir et à disparaître. Il semble qu'il ait des amis en ville. Le seul détail dont le capitaine se souvient est que l'assassin n'a qu'un œil. Ça ne nous aidera pas beaucoup, cependant, il y a beaucoup de Cyclopes comme lui qui rôdent sur les quais de nos jours\nRichard a perdu beaucoup de sang et le poivre a horriblement irrité ses yeux si bien qu'il est presque aveugle maintenant...";
			link.l1 = "Poivre moulu ? C'est une façon coûteuse d'aveugler quelqu'un. Fleetwood a dû vraiment mettre quelqu'un en colère. Je suis désolé pour votre capitaine. La recherche de l'attaquant a-t-elle donné quelque chose ?";
			link.l1.go = "Fleetwood_house_1";
		break;
		
		case "Fleetwood_house_1":
			dialog.text = "Les marins du Capitaine Fleetwood ont fouillé toute la ville et les baies locales, mais ils n'ont rien trouvé, que leurs cous soient enchaînés ! Si nous avons échoué à le trouver juste après l'attaque, il n'y a aucune chance de trouver ce salaud maintenant. Le Capitaine Fleetwood a beaucoup d'ennemis... Mais, capitaine, mon commandant veut vous voir de toute façon malgré l'accident. Il se repose maintenant chez lui, alors allons-y. Suivez-moi !";
			link.l1 = " Conduisez, Monsieur Knippel.";
			link.l1.go = "Fleetwood_house_2";
		break;
		
		case "Fleetwood_house_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			bDisableFastReload = true;//закроем быстрый переход
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
			pchar.quest.Knippel_Outside.win_condition.l1 = "location";
			pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
			pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			sld = characterFromId("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			AddLandQuestMark(sld, "questmarkmain");
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;
		
		case "InFleetwoodHouse":
			dialog.text = "Capitaine Fleetwood est à l'étage dans sa chambre. Va le voir, il t'attend. Je resterai ici.";
			link.l1 = "Compris, Monsieur Knippel. Je suis en route.";
			link.l1.go = "exit";	
		break;
		
		case "Knippel_ToOfficer":
			dialog.text = "Ecoutez cap... Le cap'taine Fleetwood est en sécurité et entre de bonnes mains maintenant. Je veux vous aider à vous venger du salaud qui l'a attaqué. Je vous offre mes services en tant qu'officier d'artillerie. Je ne suis pas très bon à l'épée, trop vieux pour ça, mais je peux abattre les cacatois d'un marchand à mille pas.";
			link.l1 = "Maintenant, ça, j'aimerais bien voir. Bienvenue à bord, M. Knippel !";
			link.l1.go = "Knippel_ToOfficer_1";	
		break;
		
		case "Knippel_ToOfficer_1":
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);//откроем локаторы
			//Книппеля - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 20;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false);//на все дела - 1 месяц
			AddSimpleRumourCity("They say that Sir Richard Fleetwood himself is indebted in you. You are a very important man in our town, sir", "SentJons", 10, 3, "");
		break;
		
		case "hired":
			dialog.text = "Ahoy capitaine ! Besoin de quelque chose ?";
			link.l1 = "Non, rien.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			if (pchar.questTemp.HWIC.Eng == "MirageFail")
			{
				dialog.text = "Tu es un véritable imbécile, matelot, un boulet ramé à mon cul! Tu as échoué à accomplir une tâche élémentaire - capturer le 'Mirage' sans perdre le 'Valkyrie'\nNotre équipage ne servira plus sous ton commandement. Nous sommes sûrs que Sir Fleetwood approuvera notre décision, il aime les idiots aussi peu que nous.";
				link.l1 = "Va te faire foutre, toi et ton maître !";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
			{
				dialog.text = "Tu es un parfait imbécile, matelot, à m'parler de tir à chaîne ! Nous avons perdu trop de temps à résoudre tes problèmes personnels\nNotre équipage ne te servira plus. Nous sommes sûrs que Sir Fleetwood approuvera notre décision, il aime les idiots aussi peu que nous.";
				link.l1 = "Va te faire foutre, toi et ton maître !";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
			{
				dialog.text = "Tu es un parfait imbécile, mon gaillard, tir de chaînette mon cul ! On t'avait dit de jouer au marchand solitaire sur le 'Valkyrie', et qu'as-tu fait ? Tu as fait fuir le pirate avec ta flottille !\nNous sommes certains que Sir Fleetwood approuvera notre décision, il apprécie les idiots autant que nous.";
				link.l1 = "Va te faire foutre, toi et ton maître !";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake")
			{
				dialog.text = "Tu es un parfait idiot, compagnon, tirer à la chaîne mon cul ! As-tu décidé de gaspiller notre temps à faire autre chose que capturer le 'Mirage' et naviguer vers Antigua ?\nNotre équipage ne te servira plus. Nous sommes sûrs que Sir Fleetwood approuvera notre décision, il aime les idiots aussi peu que nous.";
			link.l1 = "Va te faire foutre, toi et ton maître !";
			link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)//если сам на Валькирии
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
						{
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "OnCuracao":
			pchar.quest.HWICEng_toBarbadosOver.over = "yes";//снять прерывание
			dialog.text = "Salutations, capitaine. Heureux de vous voir!";
			link.l1 = "Salutations, M. Knippel. Avez-vous l'argent ? Donnez-le-moi et allons à Willemstad chercher Abigail. Voulez-vous m'accompagner ?";
			link.l1.go = "OnCuracao_1";	
		break;
		
		case "OnCuracao_1":
			dialog.text = "Capitaine, écoutez... Il n'y a plus besoin d'aller nulle part maintenant.";
			link.l1 = "De quoi parlez-vous? C'est du n'importe quoi!";
			link.l1.go = "OnCuracao_2";	
		break;
		
		case "OnCuracao_2":
			dialog.text = "J'ai une lettre du Capitaine Fleetwood pour vous. Et l'argent. Mais cet argent n'est pas pour le père d'Abigail, mais pour vous. Deux cent mille pesos. Lisez la lettre et essayez de ne pas le juger trop sévèrement...";
			link.l1 = "Que diable se passe-t-il ces jours-ci ?! Encore une mauvaise surprise ? Donne-moi la lettre !";
			link.l1.go = "OnCuracao_3";	
		break;
		
		case "OnCuracao_3":
			DialogExit();
			NextDiag.CurrentNode = "OnCuracao_4";
			AddMoneyToCharacter(pchar, 200000);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 1;//еще денек пусть погуляет по пляжу
			pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
			pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol";//патруль в прибрежных водах
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//открыть подземелье
			pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
			AddQuestRecordInfo("LetterFromFleetwood", "1");
			AddQuestRecord("Holl_Gambit", "2-23");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "OnCuracao_4":
			dialog.text = "Tu l'as lu, cap'taine ? Je vais être franc. J'ai honte du Cap'taine Fleetwood et de ce qu'il a fait, tirer à mitraille son... ah, merde à ça. Rodenburg était furieux quand il a appris la romance d'Abigail avec Richard. Des patrouilles à pied fouillent Curaçao et il y a des navires militaires de la Compagnie qui croisent dans les eaux locales. Nous devons foutre le camp d'ici.\n Capitaine, as-tu besoin d'un canonnier ? Je n'ai pas besoin de luxe - juste une ration de mer normale régulièrement. Je ne suis pas très bon à l'escrime, trop vieux pour ça, mais je peux faire tomber les perroquets d'un marchand à mille pas.";
			link.l1 = "Eh bien, diantre, j'aimerais voir comment vous allez vous y prendre, Monsieur Knippel. Bienvenue à l'équipage !";
			link.l1.go = "Knippel_hire";
			link.l2 = "Je regrette d'avoir aidé ces vauriens anglais dès le départ. Je ne sais pas maintenant comment sortir de ce pétrin. Tracez votre propre chemin, j'en ai assez des surprises.";
			link.l2.go = "Knippel_exit";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*200;
			npchar.OfficerWantToGo.DontGo = true;
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 120, 120);
			LAi_SetOfficerType(npchar);
			npchar.greeting = "knippel_hire";
			NextDiag.CurrentNode = "Knippel_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			
			//Sinistra - через 2 месяца стартует личный квест Чарли Книппеля "Длинные тени старых грехов"
			SetTimerCondition("DTSG_Start", 0, 0, 60, false);
		break;
		
		case "Knippel_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;
		
//------------------------------------------------против всех-----------------------------------------------
		case "Knippel_abordage":
			dialog.text = "Ah, maudit rat d'eau ! Pourquoi as-tu attaqué ce paisible navire hollandais ? Je n'ai ni marchandises précieuses ni or, que des boulets ramés pour mon derrière !";
			link.l1 = "Navire hollandais ? Haha ! Ne me fais pas rire, 'Hollandais'. J'ai attaqué ta brigantine pour te capturer, cher Charlie. Bienvenue dans ma soute à cargaison. Nous allons discuter de ta destination et de la raison de ton voyage...";
			link.l1.go = "Knippel_abordage_1";	
		break;
		
		case "Knippel_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-20");
            pchar.quest.Knippel_DieHard.over = "yes";
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "KnippelPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Knippel_prisoner":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			dialog.text = "Tu es un démon, pirate... Tu brûleras en enfer pour tous tes péchés ! Hurle...";
			link.l1 = "Calme-toi, sermonneur. Tu prêches comme un puritain. Tu ferais mieux de t'occuper d'abord de l'état de ton âme.";
			link.l1.go = "Knippel_prisoner_1";
		break;
		
		case "Knippel_prisoner_1":
			dialog.text = "Que complotes-tu, vaurien ? Que veux-tu de mon commandant et de la pauvre fille hollandaise ?";
			link.l1 = "Ce n'est pas ton affaire, Charlie. Je n'ai plus besoin de toi. Lève-toi.";
			link.l1.go = "Knippel_prisoner_2";	
		break;
		
		case "Knippel_prisoner_2":
			dialog.text = "Tu veux me tuer ? Digne d'un salaud comme toi. *crache* Va te faire foutre !";
			link.l1 = "Lève-toi, Charlie. Dis tes dernières prières.";
			link.l1.go = "Knippel_prisoner_3";	
		break;
		
		case "Knippel_prisoner_3":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
			pchar.quest.RemoveKnippelOver.over = "yes";//снять таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Knippel_officer":
			dialog.text = "Ahoy capitaine, enchaîne mon cul !";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Monsieur Knippel, je vais à l'ancienne ville indienne perdue de Tayasal. Je vais être clair, ce sera un voyage vraiment dangereux et aussi inhabituel - nous devons y parvenir à travers cette...idole magique. Voulez-vous m'accompagner ?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Monsieur Knippel, donnez-moi un rapport complet du navire.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Je veux que tu achètes certaines marchandises chaque fois que nous sommes à quai.";
				Link.l12.go = "QMASTER_2";
			}
			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Je suis arrivé sur vos ordres, capitaine.";
				Link.l2 = "Je dois vous donner plusieurs ordres.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Knippel_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Ecoutez mes ordres !";
            Link.l1.go = "stay_follow";
			link.l2 = "Ce n'est rien. Rompez!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Que le diable m'emporte... Les canons vont bien, on remplace ceux qui explosent et on garde notre poudre sèche et en sécurité. Quel genre de rapport attendiez-vous, Capitaine ? Je suis un vieux canonnier, pas un commissaire. Chaîne ma fesse, je suis le meilleur canonnier des Caraïbes cependant, prenez note !";
			Link.l1 = "Aucune dispute ici, M. Knippel, vous connaissez bien votre métier. Je trouverai un intendant moi-même, ne vous inquiétez pas.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Tu veux que le vieux Charlie échange son pont-batterie pour le gaillard d'arrière ? Capitaine, je coule des navires, je ne me bats pas pour chaque peso. Et je suis sûr qu'ils vont m'arnaquer dans la toute première colonie où nous essayerons ça.";
			link.l1 = "Mais bien sûr, Monsieur Knippel. Je devrais commencer à chercher un intendant convenable.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Je vous écoute.";
			Link.l1 = "C'est à propos de l'abordage.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "C'est à propos de ton navire.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "Je veux que tu quittes mon escadre pour un temps et cherches fortune par toi-même.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Rien jusqu'à présent.";
			Link.l8.go = "exit";
			break;

		case "Companion_TaskBoarding":
			dialog.Text = "Alors quel est ton souhait.";
			Link.l1 = "N'embarquez pas sur les navires ennemis. Prenez soin de vous et de l'équipage.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Je veux que tu abordes les navires ennemis.";
			Link.l2.go = "Companion_TaskBoardingYes";
			break;

		case "Companion_TaskChange":
			dialog.Text = "Alors, quel est ton souhait.";
			Link.l1 = "Je voudrais que tu ne changes pas ton navire pour un autre après l'abordage. Ton navire est trop précieux.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Lorsque tu abordes des navires ennemis, tu peux les prendre pour toi, s'ils sont convenables.";
			Link.l2.go = "Companion_TaskChangeYes";
			break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Oui, oui!";
			Link.l1 = "Repos.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
			break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Ce sera fait.";
			Link.l1 = "Repos.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
			break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Oui, oui !";
			Link.l1 = "Ce sera fait.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
			break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Ce sera fait.";
			Link.l1 = "Reposez-vous.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
			break;
			//	<========////////////////////////////////////////

		case "stay_follow":
            dialog.Text = "Ordres ?";
            Link.l1 = "Tiens-toi là !";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Suis-moi et ne traîne pas !";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Changez le type de munitions pour vos armes à feu.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choisir le type de munition :";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Il y a un changement de disposition !";
            Link.l1 = "Congédié.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Il y a un changement de disposition !";
            Link.l1 = "Congédié.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Je me suis vraiment attaché à vous durant mon service, "+pchar.name+", et je n'abandonne pas mon capitaine dans le pétrin. Je vous suivrais en enfer si nécessaire. Je suis avec vous !";
			link.l1 = "Merci, Monsieur Knippel ! Je suis heureux d'avoir eu raison à votre sujet.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Quand commencerons-nous, que le mitraille me crève les yeux ?";
			link.l1 = "Un peu plus tard. Nous devons nous y préparer.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "22");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Vous êtes un "+GetSexPhrase("voleur, monsieur ! Gardes, attrapez-le","voleuse, fille! Gardes, attrapez-la")+"!!!","Regardez-moi ça ! Dès que j'ai eu le dos tourné, vous avez décidé de fouiller dans mon coffre ! Attrapez le voleur !!!","Gardes ! Vol ! Attrapez le voleur !!!");
			link.l1 = "Sacrebleu !";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
