// пещерные энкаунтеры
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Voulez-vous quelque chose?";
			link.l1 = "Non, rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (hrand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("Ho-ho, regarde qui est là ! Eh bien, c'est ton jour de chance, mon pote. Nous sommes de bons gars, vois-tu, en train de cuisiner et tout... Je ne t'invite pas à notre dîner, mais tu devrais te perdre pendant que tu le peux encore.","Dégage maintenant et ne nous dérange pas. Reviens demain - et n'oublie pas d'apporter ta bourse avec toi, ha-ha-ha!","Ne me rends pas fou, marin! Te souviens-tu encore où se trouve l'entrée de la grotte? Tu devrais y aller maintenant, très, très vite...","Eh bien, maintenant tu as franchi la ligne, mon pote ! Je suppose que je vais devoir me détourner de mes affaires et m'occuper de toi, enfoiré !","bloc",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("C'est très gentil de ta part, camarade...","Je vois que tu es tout un farceur...","D'accord, continue à frire tes crêpes plates, alors...","Maintenant, on parle, ha-ha!",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Ho, parbleu! Pas besoin d'aller chasser la proie - elle est déjà ici... Hé, les gars - on secoue ce dandy, non?","Personne ne t'a invite ici, mon pote... Mais c'est tellement bien que tu sois ici, de toute façon. Voyons maintenant, à quel point ta bourse est lourde !","Personne ne t'a trainé ici de force, he-he... Mais puisque tu es déjà là, je suppose que nous allons te chatouiller un peu pour voir ce qui tombe de tes poches...");
				link.l1 = LinkRandPhrase("Maintenant, je vais raccourcir un peu ta langue...","J'espère que tes compétences à l'épée correspondent à ton esprit, moulin à paroles !","Eh bien, il semble qu'il soit temps de faire quelques trous de plus dans ton corps périssable...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("Oh la la, bon sang ! Pas besoin de chasser la proie - elle est déjà ici... Hé, les gars - on secoue ce fringant, n'est-ce pas ?","Personne ne t'a invité ici, mon pote... Mais c'est si bon que tu sois là, de toute façon. Voyons voir maintenant, à quel point ton sac est lourd !","Personne ne t'a trainé ici de force, he-he... Mais puisque tu es déjà là, je suppose qu'on va te chatouiller un peu pour voir ce qui tombe de tes poches...");
			link.l1 = LinkRandPhrase("Maintenant, je vais raccourcir un peu ta langue...","J'espère que tes compétences à l'épée sont à la hauteur de ton esprit, moulin à paroles!","Eh bien, il semble que c'est l'heure de faire quelques trous de plus dans ton corps périssable...");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("Dégage, mon pote. Il n'y a rien à faire pour toi ici !","Hé, je demande d'une manière amicale : dégage. On ne sait jamais ce qui peut arriver...","Dernier avertissement: si tu ne te perds pas tout de suite, tu regretteras d'être venu ici.","C'est ça, mon pote, tu as cherché des ennuis.","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ne me dis pas quoi faire, d'accord?","Et qu'est-ce qui est si spécial là-bas? Juste une grotte, rien de plus...","Oh, allez maintenant...","Ha ! Voyons voir qui est le meilleur, asticot !",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (hrand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat("Visage pâle s'en va. Il est heureux que "+npchar.name+"  gentil. Les dieux ont pitié de toi aujourd'hui.","Sors de ma grotte, avant que moi et mes frères ne nous mettions en colère!","Va-t'en, chien visage pale!","Ton chance et ta vie sont finies, chien blanc!","bloc",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Eh bien, merci, mon pote, très gentil de ta part...","Cette grotte n'est pas la tienne, et je vais où je veux.","Baisse d'un cran, rejeton du marais.","Maintenant, je vais te faire ravaler tes paroles, animal...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Le visage pâle maudit est venu à notre feu de camp! Wheppee! Tu es fini!","Visage pâle idiot est venu dans la tanière du jaguar. Je vais frire ton foie!","Insolent visage pale ose venir dans ma grotte ? Alors il n'en sort jamais vivant !");
				link.l1 = LinkRandPhrase("Maintenant, je vais arracher ta langue...","Maintenant, le monde aura plusieurs cannibales de moins...","Eh bien, il semble qu'il soit temps de faire quelques trous de plus dans ton corps périssable, toi, le singe au visage rouge.");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("Sale visage pâle est venu à notre grotte ! Whe-hee ! Je vais te couper la langue et la faire frire !","Stupide visage pâle est venu à la tanière du jaguar. Frères, coupez ce maudit chien blanc!","Un visage pâle insolent ose venir à ma grotte? Alors il n'en sortira jamais vivant!");
			link.l1 = LinkRandPhrase("Je vais te couper cette foutue tête...","Maintenant, le monde aura plusieurs cannibales de moins...","Eh bien, prépare-toi à rencontrer tes ancêtres, peau-rouge. Au diable avec toi!");
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
