void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("Argent sur le tonneau "+GetSexPhrase("camarade","fillette")+"! Mon nom est "+GetFullName(npchar)+", et je ne suis pas habitué aux objections...","Maintenant montre-moi ta bourse, "+GetSexPhrase("camarade","fillette")+", et soyez rapide à ce sujet! Mon nom est  "+GetFullName(npchar)+", et j'espère que vous avez entendu parler de moi...","Donne-moi tout ce que tu as de valeur, je réquisitionne aussi le contenu de ton sac. Et dépêche-toi, la patience n'est pas ma plus grande vertu. Je ne peux pas en dire autant de ma soif de sang !");
			Link.l1 = LinkRandPhrase("Heh, alors tu es ce fameux bandit "+GetFullName(npchar)+", à propos de qui le gouverneur local "+sTemp+"ne cesse jamais de parler?","Oh, donc tu es ce bandit pourchassé par le gouverneur local "+sTemp+"?! ","Heureux"+GetSexPhrase("","")+" de vous voir, "+GetFullName(npchar)+". Le gouverneur local, "+sTemp+" ne parle que de vous.");
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("Oui, je suis bien connu dans ces terres, he-he... Attends, n'es-tu pas un autre "+GetSexPhrase("chien sale","salope crasseuse")+" du gouverneur qu'il a envoyé pour me traquer?","Le gouverneur est mon bon ami, c'est vrai. Et n'es-tu pas, par hasard, "+GetSexPhrase("un autre héros, envoyé","une autre héroïne, envoyée")+" par lui pour ma tête?","Le gouverneur est mon meilleur ami, ce n'est pas un secret, he-he. Mais comment savez-vous cela? Peut-etre, il vous a envoyé après moi?");
			Link.l1 = LinkRandPhrase("Exactement, fripouille. Prépare-toi à mourir !","N'es-tu pas un rapide d'esprit! Très bien, il est temps de procéder à ta liquidation. Assez parlé.","Ouais, c'est moi. Sors ton arme, camarade ! Voyons de quelle couleur est ton sang.");
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase("Oh, laisse tomber! Je n'ai pas du tout besoin de tels problèmes...","Non, non, je ne suis pas un héros, en aucun cas...","Non, non, jamais! Je n'ai pas besoin de problèmes...");
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("C'est mieux, "+GetSexPhrase("camarade","fillette")+"...Et maintenant perds-toi!","Et c'est une décision correcte. J'aimerais que tu saches combien de héros j'ai envoyés dans l'autre monde... Bien, moins de mots. Dégage, "+GetSexPhrase("morceau de merde","salope")+"!","Bien "+GetSexPhrase("garçon","fille")+"! Une décision très sage - de ne pas se mêler des affaires des autres... Bon, dégage déjà, "+GetSexPhrase("camarade","lass")+".");
			Link.l1 = "Adieu et bonne chance à toi...";
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашёл, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// ОЗГ - пассажир
		case "ContraPass_abordage":
			dialog.text = "Arghh, espèce de scélérat! Comment as-tu osé attaquer mon navire ?! Tu vas payer pour ça!";
			link.l1 = "Au contraire, je suis en réalité payé pour cela. Vous avez un certain homme à bord, nommé "+pchar.GenQuest.TakePassenger.Name+". C'est lui dont j'ai besoin.";
			link.l1.go = "ContraPass_abordage_1";
		break;
		
		case "ContraPass_abordage_1":
			dialog.text = "Je savais que ce gredin nous attirerait des ennuis... Mais tu ne m'auras pas si facilement ! Défends-toi, sale pirate !";
			link.l1 = "C'est toi qui doit penser à la défense, gueux.";
			link.l1.go = "ContraPass_abordage_2";
		break;
		
		case "ContraPass_abordage_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Tempsailor":
			dialog.text = "Capitaine, nous avons fouillé les cabines et la cale, comme vous l'avez ordonné. Ce scélérat a essayé de se cacher, mais nous l'avons trouvé.";
			link.l1 = "Excellent! Où est-il maintenant?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Il est dans la cale, comme vous nous l'avez ordonné.";
			link.l1 = "Excellent! Maintenant, sortons de cette vieille coquille. Il est temps de rentrer.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Tout de suite, capitaine!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
			sld.name = pchar.GenQuest.TakePassenger.Name;
			sld.lastname = "";
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;
		
		case "Fugitive_city": // ходит по городу
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Que voulez-vous, monsieur?";
			link.l1 = "Eh bien, eh bien... Donc tu es "+pchar.GenQuest.FindFugitive.Name+", n'est-ce pas? Je suis tres heureux de vous voir...";
			link.l1.go = "Fugitive_city_1";
		break;
		
		case "Fugitive_city_1":
			dialog.text = "Eh bien, c'est moi, en effet, bien que je me demande pourquoi tu es content de me voir? Cela me semble étrange, car je ne t'ai jamais vu auparavant... Tu voudrais bien t'expliquer?";
			link.l1 = "Mais bien sûr. Je viens de "+XI_ConvertString("Colonie"+pchar.GenQuest.FindFugitive.Startcity+"Gén")+", par ordres du gouverneur local. Vous êtes arrêté et je dois vous livrer à la même ville... Oh, et éloignez les mains de votre sabre ! Ne tentez rien de stupide monsieur, ou ça se passera mal pour vous !";
			link.l1.go = "Fugitive_city_2";
		break;
		
		case "Fugitive_city_2":
			dialog.text = "Alors, vous m'avez trouvé après tout... Monsieur, écoutez-moi et, peut-être, vous changerez d'avis. Oui, j'ai déserté de la garnison. Mais je ne pouvais pas regarder la dégradation de notre armée!\nJe voulais une vie paisible et j'ai trouvé une telle vie ici, dans ce village... Laissez-moi tranquille, dites-leur que vous n'avez pas réussi à me trouver ou que j'ai fui avec des pirates en haute mer. En retour, je vous donnerai cette bourse d'ambre. Un objet très précieux, je dois dire...";
			link.l1 = "Ne pensez même pas à me corrompre, monsieur ! Rendez votre arme et suivez-moi !";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Degradation? Une vie tranquille et paisible? D'accord, je suppose que je peux réaliser votre souhait. Où est votre ambre?";
			link.l2.go = "Fugitive_city_gift";
		break;
		
		case "Fugitive_city_fight":
			dialog.text = "Alors dégaine ton épée, mercenaire! Tu ne m'auras pas aussi facilement!";
			link.l1 = "D'accord, voyons ta valeur!";
			link.l1.go = "Fugitive_fight_1";
		break;
		
		case "Fugitive_city_gift":
			TakeNItems(pchar, "jewelry8", 50+hrand(25));
			TakeNItems(pchar, "jewelry7", 2+hrand(5));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received amber");
			dialog.text = "Ici... Et j'espère bien que je ne verrai jamais ni toi ni d'autres 'envoyés' à nouveau.";
			link.l1 = "Je vous assure que vous ne le regretterez pas. Au revoir, monsieur !";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_gift_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.FindFugitive = "Found"; //флаг провалил
			AddQuestRecord("MayorsQuestsList", "12-4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity));
		break;
		
		case "Fugitive_fight_1":// в городе и бухте
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Fugitive_afterfight":
			dialog.text = "Arrgh! Tu as gagné, va te faire foutre! Je me rends...";
			link.l1 = "Surveillez votre langue, monsieur ! Et maintenant, donnez-moi votre sabre, s'il vous plaît... Suivez-moi, et sans stupidités !";
			link.l1.go = "Fugitive_afterfight_1";
		break;
		
		case "Fugitive_afterfight_1":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			//DeleteAttribute(npchar, "LifeDay");
			npchar.lifeday = 0;
			LAi_SetImmortal(npchar, true);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			pchar.GenQuest.FindFugitive = "Execute"; //флаг выполнил успешно
			pchar.quest.FindFugitive1.win_condition.l1 = "location";
			pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity+"_townhall";
			pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
			SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;
		
		case "Fugitive_shore": // в бухте
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Monsieur, je ne suis pas d'humeur à discuter avec vous, alors...";
			link.l1 = "Néanmoins, vous devrez parler avec moi. Vous êtes "+pchar.GenQuest.FindFugitive.Name+", n'est-ce pas? Je pense que vous ne devriez pas le nier.";
			link.l1.go = "Fugitive_shore_1";
		break;
		
		case "Fugitive_shore_1":
			dialog.text = "Et je ne vais pas le nier, c'est moi. Mais que voulez-vous ?";
			link.l1 = "J'ai besoin de vous emmener à "+XI_ConvertString("Colonie"+pchar.GenQuest.FindFugitive.Startcity)+", le gouverneur local meurt d'envie de vous voir. Pas de betises, s'il vous plait! Rendez votre arme et suivez-moi!";
			link.l1.go = "Fugitive_shore_2";
		break;
		
		case "Fugitive_shore_2":
			dialog.text = "Je vois... Monsieur, avant que vous ne tiriez à bout portant, laissez-moi vous dire quelque chose. Oui, j'ai déserté de la garnison. Mais j'avais des raisons de le faire. Je ne peux pas rester dans le service, c'est plus que je peux supporter! Vous me comprenez? Je ne peux pas!\nJe veux une vie paisible et j'ai trouvé une telle vie ici, dans ce village... Laissez-moi tranquille, dites-leur que vous avez échoué à me trouver ou que j'ai fui avec des pirates en haute mer. En retour, je vous donnerai ma capture hebdomadaire de perles. C'est tout ce que j'ai.";
			link.l1 = "Ne pensez même pas à me soudoyer, monsieur ! Rendez votre arme et suivez-moi !";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Vous en avez marre du service militaire ? Vous voulez une vie paisible ? D'accord, je suppose que je peux réaliser votre souhait. Où sont vos perles?";
			link.l2.go = "Fugitive_shore_gift";
		break;
		
		case "Fugitive_shore_gift":
			TakeNItems(pchar, "jewelry52", 100+hrand(40));
			TakeNItems(pchar, "jewelry53", 400+hrand(100));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received pearls");
			dialog.text = "Ici... Et j'espère bien que je ne verrai plus jamais ni vous ni d'autres 'envoyés'.";
			link.l1 = "Je vous assure que vous ne le ferez pas. Adieu, monsieur!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern": // в таверне
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Ehhh... hic! Monsieur, je ne cherche pas de compagnie - surtout la vôtre. Dégagez!";
			link.l1 = "Mais je CHERCHE votre compagnie, "+pchar.GenQuest.FindFugitive.Name+"! Et tu toléreras ma compagnie dans la cale de mon navire. Nous allons à  "+XI_ConvertString("Colonie"+pchar.GenQuest.FindFugitive.Startcity)+", au gouverneur de la ville. Il est presque mourant de vous voir.";
			link.l1.go = "Fugitive_tavern_1";
		break;
		
		case "Fugitive_tavern_1":
			dialog.text = "H-Hic!"+RandSwear()+" Alors il m'a finalement traqué ! Écoute, camarade, tu ne sais pas ce qui s'est passé, tu n'étais pas là ! Je ne pouvais pas rester au service, je ne pouvais tout simplement pas ! Je me saoule encore chaque soir pour oublier ça\nRegarde, faisons un marché. Dis-lui que tu as échoué à me trouver ou que j'ai fui avec des pirates en haute mer. En retour, je te donnerai tous les pépites que j'ai trouvées dans la grotte locale. C'est tout ce que j'ai, vois-tu, je te donne tout, juste pour ne plus jamais voir "+XI_ConvertString("Colonie"+pchar.GenQuest.FindFugitive.Startcity)+"...";
			link.l1 = "Ne pensez même pas à me corrompre, monsieur! Rendez votre arme et suivez-moi!";
			link.l1.go = "Fugitive_tavern_fight";
			link.l2 = "Hmm... Une histoire désagréable ? Êtes-vous tourmenté par des cauchemars ou la conscience coupable ? D'accord, je suppose que je peux vous laisser avec ça tout seul. Où sont vos pépites ?";
			link.l2.go = "Fugitive_tavern_gift";
		break;
		
		case "Fugitive_tavern_gift":
			TakeNItems(pchar, "jewelry5", 50+hrand(30));
			TakeNItems(pchar, "jewelry6", 100+hrand(50));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received nuggets");
			dialog.text = "Voici... Et j'espère que je ne verrai plus jamais ni vous ni d'autres 'envoyés'.";
			link.l1 = "Je vous assure que vous ne le ferez pas. Adieu, monsieur!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern_fight":
			dialog.text = "Alors dégaine ton épée, mercenaire ! Tu ne m'auras pas si facilement !";
			link.l1 = "D'accord, voyons ta valeur!";
			link.l1.go = "Fugitive_fight_2";
		break;
		
		case "Fugitive_fight_2":// в таверне
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetImmortal(npchar, false);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
