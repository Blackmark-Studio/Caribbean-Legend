// гид
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Tu veux quelque chose ?";
			link.l1 = "Non, rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guide_0":
			PlaySound("Voice\English\LE\Greguar\Greguar_01.wav");
			dialog.text = "Plaisir de vous accueillir dans les colonies, monsieur ! Permettez-moi de me présenter : "+GetFullName(npchar)+". Venez-vous d'Europe ? C'est votre première fois ici ?";
			link.l1 = "Bonjour, monsieur. Mon nom est "+GetFullName(pchar)+". Oui, je viens tout juste de débarquer.";
			link.l1.go = "guide_1";
		break;
		
		case "guide_1":
			DelLandQuestMark(npchar);
			dialog.text = "En voyant un gentilhomme, j'ai cru de mon devoir d'offrir mon aide. Ici, dans le Nouveau Monde, il y a ses propres règles — et les ignorer peut coûter cher. Les gens de qualité comme nous doivent s'entraider. Vous ne croiriez pas combien de racaille s'est rassemblée ici, prête à trahir son prochain pour une poignée de pièces.\n"+
			"Puis-je vous faire visiter la ville et vous mettre brièvement au courant ?";
			link.l1 = "C'est très noble de votre part, monsieur ! J'accepte volontiers votre proposition.";
			link.l1.go = "guide_2";
			link.l2 = "Merci pour votre sollicitude, monsieur, je vous en suis vraiment reconnaissant, mais je pense que je me débrouillerai sans peine tout seul.";
			link.l2.go = "guide_exit";
		break;
		
		case "guide_exit":
			dialog.text = "Comme il vous plaira, monsieur. En tout cas, j'ai été ravi de faire votre connaissance. Les gens nobles sont si rares dans cette contrée sauvage. Tout le bien possible et bonne chance !";
			link.l1 = "Et à vous aussi, "+GetFullName(npchar)+" !";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_2":
			dialog.text = "Magnifique ! La vie aux Caraïbes est simple, et chaque établissement est construit selon les mêmes règles. Si vous vous familiarisez avec Saint-Pierre, vous vous familiariserez avec n'importe quelle autre ville.";
			link.l1 = "";
			link.l1.go = "guide_tavern";			
		break;
		
		case "guide_tavern":
			dialog.text = "Taverne — le cœur du port. Ici vous trouverez un gîte, du rhum, des rumeurs et pourrez engager des marins et des officiers. Et aussi — jouer aux cartes, trouver du travail ou utiliser les services de contrebandiers et de marchands de cartes au trésor.";
			link.l1 = "";
			link.l1.go = "guide_market";
			locCameraFromToPos(-2.08, 5.32, 68.88, true, -15.00, 0.90, 55.00);
		break;
		
		case "guide_market":
			dialog.text = "Marché. Les marchandises pour usage personnel peuvent toujours s'acheter au marché. Chez l'armurier — armes, armures et munitions, chez l'herboriste — potions de guérison. Les bohémiennes et les moines commercent en amulettes, et le brocanteur vend toutes sortes de bric-à-brac utile à ceux qui ne dédaignent pas bricoler de leurs mains.";
			link.l1 = "";
			link.l1.go = "guide_brothel";
			locCameraFromToPos(-13.58, 4.11, 69.06, true, -45.00, -6.00, 52.00);
		break;
		
		case "guide_brothel":
			dialog.text = "Bordel. Il n'y a pas de meilleur remède pour le corps que les plaisirs de l'amour dans les bras d'une femme habile. Si la santé chancelle — passez donc ici, divertissez-vous, recevez votre dose de caresses et vous vous sentirez un autre homme.";
			link.l1 = "";
			link.l1.go = "guide_bank";
			locCameraFromToPos(-2.75, 7.07, 61.10, true, 60.00, -6.60, 42.65);
		break;
		
		case "guide_bank":
			dialog.text = "Banque. Maison de l'usurier. On peut emprunter ou placer de l'argent, échanger des pesos contre des doublons. Et aussi — c'est le meilleur endroit pour vendre des bijoux.";
			link.l1 = "";
			link.l1.go = "guide_prison";
			locCameraFromToPos(3.07, 7.64, 51.99, true, 45.00, -8.30, 4.50);
		break;
		
		case "guide_prison":
			dialog.text = "Prison. Il y a peu de vrais criminels ici — surtout toutes sortes de racailles. Si vous voulez trouver du travail parmi les rebuts de la société — parlez au commandant. Pour un petit pot-de-vin il peut vous laisser passer aux cellules.";
			link.l1 = "";
			link.l1.go = "guide_townhall";
			locCameraFromToPos(-50.52, 5.79, 38.60, true, -47.65, 3.95, 33.52);
		break;
		
		case "guide_townhall":
			dialog.text = "Palais. Le palais de la personne la plus importante de la colonie — le gouverneur. Les hommes d'affaires et les capitaines viennent ici pour du travail sérieux. Être en bons termes avec le gouverneur — c'est une grande affaire, car de lui dépend en grande partie comment toute sa nation vous traitera.";
			link.l1 = "";
			link.l1.go = "guide_12";
			locCameraFromToPos(3.14, 7.39, 37.55, true, 1.06, 8.45, 14.14);
		break;
		
		case "guide_12":
			dialog.text = "Vous vous dépêchez quelque part, et je vous dérange ?";
			link.l1 = "Eh bien... je suppose que oui. Monsieur, je suis venu ici pour retrouver mon frère. On dit qu'il est quelque part à Saint-Pierre. C'est un homme important et certainement connu du gouverneur...";
			link.l1.go = "guide_13";
			SetCameraDialogMode(npchar);
		break;
		
		case "guide_13":
			dialog.text = "Ah, je comprends. Notre gouverneur s'appelle Jacques Dyel du Parquet. Je suis sûr qu'il vous recevra sans délai.";
			link.l1 = "Qui d'autre pourrait-je interroger à propos de mon frère ? Peut-être ne devrais-je pas déranger Son Excellence tout de suite ?";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "Si votre frère est vraiment connu à la Martinique — demandez aux passants. Peut-être que quelqu'un pourra vous renseigner. Au fait, comment s'appelle-t-il ?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "J'ai entendu ce nom, mais, hélas, je n'ai pas eu l'honneur d'être présenté personnellement. Essayez de demander en ville — ou allez directement chez le gouverneur. Bonne chance, monsieur. Nous nous reverrons certainement et bavarderons ensemble !";
			link.l1 = "Merci, "+GetFullName(npchar)+" !";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_21":
			dialog.text = "Oh, c'est encore vous, mon ami ! Je vois qu'on vous a admis dans le saint des saints de Saint-Pierre — la forteresse des Chevaliers de Malte. Tout indique que vous êtes un grand personnage. Avez-vous trouvé votre frère ?";
			link.l1 = "Eh bien oui, je l'ai trouvé...";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "Pardonnez mon insistance, monsieur, mais il m'a semblé que je n'entends pas de joie dans votre voix...";
			link.l1 = "C'est vrai, monsieur. J'espérais retourner en France par le prochain navire, mais le destin semble avoir décidé de se moquer de moi : je reste ici pour longtemps... non, bon sang — pour une durée indéterminée ! Et, imaginez-vous, par-dessus le marché je dois devenir marin, peuh !";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "Pour une raison quelconque, je ne suis pas surpris. J'ai déjà entendu parler de votre aventure sur la pinasse 'Ulysse'. Ne vous découragez pas — être propriétaire de son propre navire et capitaine est très honorable. Vous comptez acheter un navire, n'est-ce pas ?";
			link.l1 = "Oui, bon sang, c'est exactement ce que je dois faire... Il ne reste plus qu'à trouver un chantier naval et à réunir de l'argent d'une manière ou d'une autre. Mais je ne sais ni où est le chantier naval, ni comment piloter un navire, ni où trouver de l'argent — rien !";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "Pour l'argent, hélas, je ne peux pas aider — je suis moi-même à court en ce moment. Mais pour le reste — je suis à votre service. Êtes-vous prêt à continuer la visite ?";
			link.l1 = "Oui, sans doute, car ce n'est pas pour rien qu'on dit : le savoir, c'est le pouvoir.";
			link.l1.go = "guide_25";
			link.l2 = "Merci du fond du cœur, monsieur, mais je me débrouillerai seul pour la suite.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_exit_11":
			dialog.text = "J’ai été ravi de faire votre connaissance. Et pour l’argent du navire — parlez aux personnes influentes de la ville. Par exemple, au marchand du magasin.\n"+
			"Bonne chance, "+pchar.name+" — osez, et tout vous réussira.";
			link.l1 = "";
			link.l1.go = "guide_exit_12";			
		break;
		
		case "guide_exit_12":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_25":
			dialog.text = "Alors suivez-moi ! Commençons par le plus fondamental — les navires.";
			link.l1 = "";
			link.l1.go = "guide_shipyard";
		break;
		
		case "guide_shipyard":
			dialog.text = "Chantier naval. Ici on achète et répare les navires. Le choix est limité — principalement des petites embarcations, mais parfois on trouve des vaisseaux sérieux. On peut aussi y acheter des canons et décorer les voiles.";
			link.l1 = "";
			link.l1.go = "guide_port";
			locCameraFromToPos(-23.25, 7.74, 77.79, true, -27.85, 5.36, 73.65);
		break;
		
		case "guide_port":
			dialog.text = "Quai — la porte vers la mer. Dès que vous aurez un navire — une chaloupe vous attendra ici. En attendant, je vous recommande d'engager un navigateur, un trésorier et un canonnier — avec eux, vous vous sentirez plus confiant en mer.";
			link.l1 = "";
			link.l1.go = "guide_portoffice";
			locCameraFromToPos(-8.55, 4.06, 91.31, true, 40.00, -8.00, 0.00);
		break;
		
		case "guide_portoffice":
			dialog.text = "Bureau du port. Ici, vous pouvez laisser votre navire et trouver du travail honnête : fret, escorte, livraison de courrier. Plus vous accomplissez de missions, plus elles deviennent lucratives.";
			link.l1 = "";
			link.l1.go = "guide_store";
			locCameraFromToPos(48.38, 9.48, 43.95, true, 43.69, 5.47, 48.13);
		break;
		
		case "guide_store":
			dialog.text = "Magasin. Les capitaines viennent ici pour les vivres, le rhum, les remèdes, la poudre et les munitions. Si un article manque, cherchez des contrebandiers à la taverne. Sans un bon trésorier, le commerce n’est qu’une perte de temps et d’argent.";
			link.l1 = "";
			link.l1.go = "guide_gate";
			locCameraFromToPos(-21.10, 6.60, 45.21, true, -30.00, 3.70, 45.00);
		break;
		
		case "guide_gate":
			dialog.text = "Porte. Si le quai est la porte vers la mer, ici c’est l’accès à la nature sauvage. Dangereux, mais indispensable pour atteindre un fort, chercher des trésors ou rejoindre une autre colonie par voie terrestre.";
			link.l1 = "";
			link.l1.go = "guide_45";
			locCameraFromToPos(50.58, 5.74, 23.21, true, 100.00, 0.00, 20.00);
			//AddQuestRecordInfo("Guide_OnLand", "1");
		break;
		
		case "guide_45":
			dialog.text = "Toutes les colonies n’accueillent pas les étrangers. Si vous ne voulez pas attendre la nuit, hissez un autre pavillon en mer, puis comptez sur la discrétion – ou achetez une licence commerciale.";
			link.l1 = "";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "Vous êtes un excellent auditeur, mon ami. Envie de vous amuser un peu ? Je propose un duel d’entraînement derrière la porte.";
			link.l1 = "Bien sûr ! Cela tombe à pic.";
			link.l1.go = "guide_47";
			link.l2 = "Merci du fond du cœur, monsieur, mais je me débrouillerai seul pour la suite.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_47": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "Mon ami, je suppose que vous n’êtes pas novice en escrime ?";
			link.l1 = "Ha ! J’ai déjà survécu à un abordage et même...";
			link.l1.go = "guide_50";
			if (FindCharacterItemByGroupWithout_knife_03(pchar, BLADE_ITEM_TYPE) == "")
			{
				GiveItem2Character(pchar, "blade_05");
				EquipCharacterByItem(Pchar, "blade_05");
			}
		break;
		
		case "guide_50":
			dialog.text = "Parfait. On commence ?";
			link.l1 = "¡Bailemos!";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			if (MOD_SKILL_ENEMY_RATE <= 6)	// На первых трёх сложностях Валинье будет ослаблен
			{
				LAi_SetHP(npchar, LAi_GetCharacterMaxHP(npchar) * 0.7, LAi_GetCharacterMaxHP(npchar) * 0.7);
				npchar.rank = 1;
				SetSelfSkill(npchar, 1, 1, 1, 1, 1);
			}
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//DoQuestCheckDelay("GuideFight_tutorial", 1.0);
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = "Vous... vous êtes un homme qui sait comment tenir son épée. Bien joué, Monsieur. Vous avez besoin de plus de pratique, mais vous avez le potentiel pour devenir un véritable maître d'épée.";
			link.l1 = "Merci beaucoup. Et maintenant ?";
			link.l1.go = "guide_62"; // нода на выход
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				link.l2 = "Plus de pratique, dites-vous ? Vous êtes sérieux ? J'en ai assez de ce ton condescendant depuis que j'ai mis les pieds dans cet endroit misérable !";				//Пасхалка Корсары 2 для сложности СФ и выше
				link.l2.go = "guide_64";
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "Beaucoup mieux ! Tu vois, il te suffit de te concentrer. Il te faut plus de pratique, un jour tu deviendras un escrimeur décent.";
			link.l1 = "Merci beaucoup. Que faire maintenant ?";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = "J'ai gagné, Monsieur. Bougez plus vite, parez mes coups, sautez en arrière. Un autre duel ?";
			link.l1 = "Oui! Pas de quartier, Monsieur!";
			link.l1.go = "guide_56";
			link.l2 = "Non, j'en ai assez. Finissons la leçon. Que maintenant ?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = "J'ai encore gagné, "+pchar.name+" ! Ne perds pas ton initiative. Attrape mes coups, feins-les. Si tu vois que je vais frapper fort - esquive ou pare, ne te contente pas de te défendre. Encore !";
			link.l1 = "Venez, Monsieur, je vais vous rosser cette fois-ci !";
			link.l1.go = "guide_56";
			link.l2 = "Non, j'en ai assez. Finissons la leçon. Et maintenant ?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = "Tu as beaucoup à apprendre, "+pchar.name+"Ne t'inquiète pas, tu as encore beaucoup de temps pour maîtriser l'art de l'escrime. Mais fais attention, ne prends pas de risques tant que tu ne sais pas comment tenir une arme.";
			link.l1 = "Je vais y réfléchir, Monsieur, mais je dois dire que vous avez eu une sacrée chance ! Cette maudite chaleur... la seule raison pour laquelle je ne vous ai pas rossé. Merde, terminons notre leçon d'escrime. Que faire maintenant ?";
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = "Maintenant, il est temps de dire adieu, Monsieur. Ce fut un plaisir. J'espère que ma présentation et ma formation vous ont été bénéfiques et vous seront utiles à l'avenir. Peut-être nous reverrons-nous un jour. \nEt à propos de l'argent dont vous avez besoin - parlez aux personnes importantes de notre ville. Visitez tous les endroits que je vous ai montrés aujourd'hui et parlez à leurs propriétaires. Renseignez-vous. Faites une promenade dans la jungle et jusqu'au fort. Trouvez un emploi ou... eh bien, je ne suis ni prêtre ni juge, fouillez dans les maisons des gens et voyez quels bibelots vous pouvez trouver dans leurs coffres déverrouillés. Faites-le simplement quand ils ont le dos tourné ou les gardes vous attraperont. \nBonne chance, "+pchar.name+", J'ai le fort sentiment que tu as l'étincelle de la vraie grandeur en toi. Fais de ton mieux pour l'attiser en un feu ardent !";
			link.l1 = "Merci, Monsieur. Le plaisir était pour moi. Bon vent !";
			link.l1.go = "guide_63";
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "guide_64": // решили убить Валинье
			dialog.text = "Tiens ta langue, Monsieur ! Je ne tolérerai plus une telle insolence. Cependant, je comprends ta réaction face à un nouvel environnement, donc je pardonne ton éclat cette fois-ci. Mais fais attention à tes paroles dorénavant. Adieu, Monsieur de Maure.";
			link.l1 = "Sans vouloir vous offenser, Monsieur Valinnie. Si nous étions au Louvre en ce moment, vous surveilleriez votre ton ! Il est temps de donner une leçon finale à cette province. Défendez-vous !";
			link.l1.go = "guide_65";
		break;
		
		case "guide_65":
			DialogExit();
			
			npchar.rank = 25;
			int iHp = MOD_SKILL_ENEMY_RATE*10+300;
			LAi_SetHP(npchar, iHp, iHp);
			SetSelfSkill(npchar, 80, 80, 80, 80, 50);
			SetShipSkill(npchar, 50, 80, 35, 30, 50, 20, 30, 20, 80);
			SetSPECIAL(npchar, 9, 5, 8, 6, 5, 10, 8);
			SetCharacterPerk(npchar, "Energaiser");
			SetCharacterPerk(npchar, "BasicDefense");
			SetCharacterPerk(npchar, "AdvancedDefense");
			SetCharacterPerk(npchar, "CriticalHit");
			SetCharacterPerk(npchar, "Tireless");
			SetCharacterPerk(npchar, "HardHitter");
			SetCharacterPerk(npchar, "Sliding");
			SetCharacterPerk(npchar, "BladeDancer");
			SetCharacterPerk(npchar, "SwordplayProfessional");
			SetCharacterPerk(npchar, "Gunman");
			SetCharacterPerk(npchar, "GunProfessional");
			GiveItem2Character(npchar, "blade_30");
			EquipCharacterbyItem(npchar, "blade_30");
			GiveItem2Character(npchar, "cirass7");
			GiveItem2Character(npchar, "obereg_7");
			GiveItem2Character(npchar, "talisman11");
			AddMoneyToCharacter(npchar, 10000);
			AddItems(npchar, "gold_dublon", 25);
			AddItems(npchar, "bullet", 5);
			AddItems(npchar, "grapeshot", 5);
			AddItems(npchar, "GunPowder", 10);
			TakeItemFromCharacter(npchar, "blade_12");
			npchar.cirassId = Items_FindItemIdx("cirass4");
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Guide_HeroKill");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string FindCharacterItemByGroupWithout_knife_03(ref chref, string groupID)
{
	ref refItm;
    string resultItemId;

	resultItemId  = "";
	for(i=TOTAL_ITEMS-1; i>=0; i--)
	{
		refItm = &Items[i];
		if( !CheckAttribute(refItm,"groupID") ) continue;
		if(refItm.groupID!=groupID) continue;
		if( !CheckAttribute(chref,"items."+refItm.id) ) continue;
		if(refItm.id == "knife_03") continue;
		if (groupID == BLADE_ITEM_TYPE)
		{
			resultItemId  = refItm.id;
		}
	}
	
	if (resultItemId != "")
	{
        return resultItemId;
	}

	return "";
}