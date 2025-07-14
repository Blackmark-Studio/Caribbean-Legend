// Бесчестный конкурент
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "C'est un bug. Informez les développeurs.";
			link.l1 = "Bien sûr !";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShadowGuarder":
			dialog.text = "Que veux-tu ?";
			link.l1 = "Es-tu "+pchar.questTemp.Shadowtrader.Guardername+" ? Le marchand local m'a envoyé. Il attend impatiemment votre présence en ce moment même.";
			link.l1.go = "ShadowGuarder_1";
			DelLandQuestMark(npchar);
		break;
	
		case "ShadowGuarder_1":
			dialog.text = "A-ah, mais je l'attendais ici ! On m'a dit qu'il viendrait à une taverne ! Désolé, je suis en route immédiatement.";
			link.l1 = "Très bien !";
			link.l1.go = "ShadowGuarder_2";
		break;
	
		case "ShadowGuarder_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("ShadowGuarder");	
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", pchar.questTemp.Shadowtrader.City +"_store", "goto", "goto2", "OpenTheDoors", 6);
			pchar.questTemp.Shadowtrader = "begin";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowAgent":
			dialog.text = "Bonsoir, capitaine. Vous voulez des marchandises bon marché, hein ? Suivez-moi !";
			link.l1 = "Guide-moi.";
			link.l1.go = "ShadowAgent_1";
		break;
	
		case "ShadowAgent_1":
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS4", "CommonFlamHouse", "barmen", "stay", "Shadow_inRoom", 40);
		break;
	
		case "ShadowTrader":
			dialog.text = "Bonsoir, monsieur. C'est un plaisir de rencontrer un nouveau client, ha ! Permettez-moi de me présenter : je suis "+GetFullName(npchar)+"J'ai les marchandises les moins chères de cette ville, je vous l'assure.";
			link.l1 = "Enfin, nous nous sommes rencontrés..."+npchar.name+". Je suppose que je vais vous décevoir : je vous cherchais non pas pour commercer mais pour mettre fin à votre sale trafic. Vous avez été une grande douleur dans le cul d'un homme important. Cette douleur est devenue si grande qu'il est prêt à vous faire taire... par tous les moyens nécessaires.";
			link.l1.go = "ShadowTrader_1";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "Arrêtez-vous là, canaille ! Ne saviez-vous pas que vous devez payer des taxes pour exploiter une entreprise commerciale ? Personne ne transgresse la loi sous ma surveillance ! "+GetFullName(npchar)+", vous avez enfreint la loi et vos marchandises volées sont maintenant confisquées ! Il y a des soldats armés juste derrière moi, dehors, alors ne faites même pas semblant d'être innocent !";
				link.l2.go = "ShadowTrader_2";
			}
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowTrader_1":
			dialog.text = "Vraiment? Je ne m'attendais pas... Qui diable es-tu?! C'est un coup monté! Je crois savoir qui est responsable de cela! Par tous les moyens nécessaires... les gars, tuez-le!";
			link.l1 = "Dansons, canaille !";
			link.l1.go = "ShadowTrader_fight";
			NextDiag.currentnode = "ShadowTrader_6";
		break;
	
	case "ShadowTrader_2":
		dialog.text = "Oh Dieu... officier, écoutez ! Faisons un marché. Vous êtes un homme sage et miséricordieux ! Je vous paierai 5000 pièces de huit et vous nous laisserez fuir par le deuxième étage. Vous prendrez aussi les marchandises, vous en avez besoin, n'est-ce pas ? Pourquoi auriez-vous besoin de moi ? Je quitterai la ville immédiatement et personne ne nous reverra jamais. Et vous aurez votre argent. Qu'en pensez-vous, officier ?";
		link.l1 = "Penses-tu vraiment, racaille, que je déshonorerai mon devoir pour une somme si dérisoire ?";
		link.l1.go = "ShadowTrader_3";
		break;
	
	case "ShadowTrader_3":
		dialog.text = "D'accord, d'accord, officier, prenez tout ce que j'ai - 10 000 pesos. C'est tout ce que j'ai, je le jure !";
		link.l1 = "Hm... Si je t'arrête, tout ton argent sera confisqué... Très bien ! Ce poste de contrebande est fermé et toutes les marchandises sont confisquées... Donne-moi la monnaie et dégage. Ne montre plus ta tête ici !";
		link.l1.go = "ShadowTrader_4";
		break;
		
	case "ShadowTrader_4":
			dialog.text = "Merci, merci, merci monsieur l'officier ! Voici votre argent, et vous ne me verrez plus ici. Allons-y !";
			link.l1 = "Sors d'ici ou je devrai t'arrêter !";
			link.l1.go = "ShadowTrader_escape";
		break;
	
		case "ShadowTrader_fight":
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.nation = PIRATE;
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ShadowTrader_afterfight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	
		case "ShadowTrader_escape"://напугали
			AddMoneyToCharacter(pchar, 10000);
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			}
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 9.0);
			pchar.questTemp.Shadowtrader.End.Escape = "true";
			AddQuestRecord("Shadowtrader", "8");
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 250);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
	
		case "ShadowTrader_6":
			dialog.text = "Ah! Pitié, ne me tue pas ! Je te donnerai tout ce que j'ai !";
			link.l1 = "Tous vos biens seront confisqués par les autorités. Penses-tu vraiment que j'ai pitié de toi après ce qui vient de se passer ici ?";
			link.l1.go = "ShadowTrader_7";
		break;
	
		case "ShadowTrader_7":
			dialog.text = "Je... Je te donnerai tout mon argent et mes biens ! Laisse-moi partir ! Je quitterai l'île aujourd'hui et tu ne me reverras plus ici !";
			link.l1 = "Très bien. Donne-moi tout ce que tu as sur toi et dégage. Et n'essaie plus jamais de faire des affaires ici - la prochaine fois, je n'épargnerai pas ta misérable vie, vaurien.";
			link.l1.go = "ShadowTrader_free";
			link.l2 = "Pas moyen, salaud, tu ne m'achèteras pas. La seule façon de traiter avec ton genre, c'est l'acier froid et le plomb brûlant !";
			link.l2.go = "ShadowTrader_killed";
		break;
		
		case "ShadowTrader_free"://отпустили
			AddMoneyToCharacter(pchar, 20550);
			TakeNItems(pchar, "jewelry1", rand(5));
			TakeNItems(pchar, "jewelry2", rand(20));
			TakeNItems(pchar, "jewelry5", rand(20));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received items");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 7.0);
			pchar.questTemp.Shadowtrader.End.Free = "true";
			AddQuestRecord("Shadowtrader", "9");
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
	
		case "ShadowTrader_killed":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(pchar);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "Shot", "ShadowTrader_killed_end", 1.3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
