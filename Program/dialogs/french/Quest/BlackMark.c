void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Que voulez-vous ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;
		
		case "BM_Contra_1":
			dialog.text = "Qui es-tu, et que diable fais-tu à traîner ici?!";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Tranquille, l'ami. Je ne fais que passer. Je ne vais pas m'immiscer dans votre... quoi que ce soit.";
			}
			else
			{
				link.l1 = "Eh? Ce phare est à toi? La prochaine fois, mets une pancarte avec ton nom sur un des palmiers ou construis une fichue clôture.";
			}
			link.l1.go = "BM_Contra_2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Contra_2":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Sors d'ici ! Si tu fais foirer l'affaire en effrayant un client, je...";
			}
			else
			{
				dialog.text = "Ecoute, gamin, ne nous oblige pas, moi et mes gars, à te défier pour voir si ta lame est aussi aiguisée que ta langue. Disparais juste et...";
			}
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosPatrolPribegaet");
		break;
		
		case "BM_Contra_3":
			dialog.text = "Eh bien, Frankie, lequel est-ce ?";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_3_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay12", "1", 1.9);
		break;
		case "BM_Contra_3_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_4", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_4":
			dialog.text = "Non... Que le diable m'emporte, mais je ne reconnais aucune de ces trognes.";
			link.l1 = "I'm sorry, but there is no text provided to translate. Could you please provide the text you would like translated?";
			link.l1.go = "BM_Contra_4_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay15", "1", 1.9);
		break;
		case "BM_Contra_4_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_5", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_5":
			dialog.text = "Quoi ?! Es-tu sûr ?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_5_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolZhitel"));
		break;
		case "BM_Contra_5_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_6", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_6":
			dialog.text = "Tu penses que je suis aveugle ?! Je te dis, que...";
			link.l1 = "... ";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			CharacterTurnByChr(CharacterFromID("BM_PatrolOff"), CharacterFromID("BM_PatrolZhitel"));
			AddDialogExitQuest("BM_BarbadosMayakVystrel");
		break;
		
		case "BM_Contra_7":
			dialog.text = "Que diable?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay9", "1", 1.9);
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_7_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_8", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_8":
			dialog.text = "Qui a tiré ?!";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_8_1";
			locCameraFromToPos(-84.11, 6.33, -62.68, true, -78.07, 3.20, -66.67);
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 1.9);
		break;
		
		case "BM_Contra_8_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_9", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_9":
			dialog.text = "Nous prends-tu pour des imbéciles, racaille? Posez vos armes à terre, tous autant que vous êtes! Et toi aussi!";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_9_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_9_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_10", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_10":
			dialog.text = "Tiens-toi tranquille, officier. Ce n'est pas nous, tu ne vois pas ? Nos armes sont là où elles étaient. Et ne touche pas aux tiennes !";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_10_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		case "BM_Contra_10_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_11", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_11":
			dialog.text = "Tu me donnes des ordres, espèce de salaud ?! Arrêtez-les tous, maintenant !";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_11_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_11_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_12", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_12":
			dialog.text = "Va te faire foutre ! Ça n'arrivera pas. Les gars, aux armes !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosMayakBoinya");
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		
		case "BM_Irons_1":
			dialog.text = "Eh, eh, fais attention ! Quelqu'un pourrait se faire tuer si tu continues à agiter ce sabre si sauvagement.";
			link.l1 = "Ha, qui ?";
			link.l1.go = "BM_Irons_2";
			LAi_SetCurHPMax(npchar);
			SetOfficerToMushketer(npchar, "mushket1", true);
		break;
		
		case "BM_Irons_2":
			dialog.text = "Moi, bien sûr.";
			link.l1 = "Quoi...? Qui diable es-tu ?";
			link.l1.go = "BM_Irons_4";
			link.l2 = "C'est exactement ce que j'essaie de faire. Allons-y ?";
			link.l2.go = "BM_Irons_3";
		break;
		
		case "BM_Irons_3":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			npchar.MusketerDistance = 10;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "BM_Irons_4":
			if (startHeroType == 4)
			{
				dialog.text = "Je suis Tommy ! Tommy Irons. Je suppose. Qui es-tu ? T'es une femme courageuse, je te le dis, à te promener comme ça, héhé.";
				link.l1 = "Brave, en effet. Et je n'ai pas peur de te faire taire si je dois. Il fait chaud ici, alors je m'habille légèrement - pas pour te plaire à toi ou à tes semblables. Je m'appelle Helen MacArthur. Mes amis pourraient m'appeler Rumba, mais tu n'es certainement pas l'un d'eux. Et que voulait dire ce 'je suppose' ?";
				link.l1.go = "BM_Irons_5";
			}
			else
			{
				dialog.text = "Je suis Tommy ! Tommy Irons. J'imagine. Et toi ?";
				link.l1 = ""+GetFullName(pchar)+". Et que signifie exactement ce 'je suppose' ?";
				link.l1.go = "BM_Irons_5";
			}
			LAi_SetCurHPMax(pchar);
		break;
		
		case "BM_Irons_5":
			dialog.text = "Cela signifie exactement ce que cela signifie. J'ai perdu la mémoire - j'ai été salement amoché au combat. Vous savez, parfois vous perdez tout. Mais j'ai de la chance, cependant. Je n'ai oublié que mon nom. Heureusement pour moi, j'ai ce pendentif autour du cou qui dit 'Thomas'. Mais je préfère Tommy. Et Irons. J'ai combattu dans les Ironsides pour Cromwell, souvenez-vous de cela. Mais 'Ironsides' est trop imposant. Irons est bien meilleur.";
			link.l1 = "Je vois ce qui ne va pas chez toi, Tommy. Alors, dis-moi - qu'est-ce que c'était ? Visais-tu quelqu'un en particulier ? As-tu atteint ta cible ? Ou tirais-tu juste pour t'amuser ? Ça ne me surprendrait pas.";
			link.l1.go = "BM_Irons_6";
		break;
		
		case "BM_Irons_6":
			dialog.text = "Je l'ai frappé, et je l'ai frappé fort ! Dans tous les sens. Tu te souviens de ce godelureau ? Il a suivi ma piste et a amené des soldats avec lui. Tout un escadron, juste parce que j'ai couché avec sa femme.";
			link.l1 = "Tu l'as bien touché, hein. Je suppose qu'il vous a surpris tous les deux sur le fait ?";
			link.l1.go = "BM_Irons_7";
		break;
		
		case "BM_Irons_7":
			dialog.text = "Ha ! Tu ne le croirais pas - non. La garce l'a avoué plus tard. Mauvaise conscience, ou peut-être qu'elle n'a pas autant apprécié que moi, héhé. Qui sait ce qui se passe dans la tête des femmes ? Je m'en moque bien, ha-ha-ha !";
			link.l1 = ""+GetSexPhrase("Hmm, c'est une drôle de fille.","Les hommes... Un instant, vous essayez de comprendre ce qui se passe dans nos têtes, le suivant vous dites que cela ne vous intéresse pas. Mais vous avez raison sur un point - ce qu'elle a fait était étrange. Elle aurait dû simplement partir et l'oublier comme un mauvais rêve. C'est exactement ce que je ferais si cela arrivait.")+"";
			link.l1.go = "BM_Irons_8";
		break;
		
		case "BM_Irons_8":
			dialog.text = "Exactement! Les gens disent qu'il y a quelque chose qui cloche chez moi. Je plains les soldats qui sont morts. Je le sais, j'étais moi-même un simple troufion autrefois. Ne te l'ai-je pas dit ?";
			link.l1 = "Oui, tu l'as fait. Des Ironsides. Cromwell.";
			link.l1.go = "BM_Irons_9";
		break;
		
		case "BM_Irons_9":
			dialog.text = "Oh, ouais? Je ne me souviens pas si je l'ai fait ou non. Sais-tu comment j'ai fini dans le Nouveau Monde? Veux-tu que je te raconte?";
			link.l1 = "Non, et cela ne m'intéresserait pas, Tommy.";
			link.l1.go = "BM_Irons_10";
		break;
		
		case "BM_Irons_10":
			dialog.text = "Ce serait, ce serait. Je te le dirai.";
			link.l1 = "D'accord, au diable, tire simplement. Je veux dire, vas-y.";
			link.l1.go = "BM_Irons_11";
		break;
		
		case "BM_Irons_11":
			dialog.text = "Ne m'interromps pas, alors ! Où en étais-je ? Ah, oui, j'étais blessé, tu vois ? J'ai reçu ma démission officielle parce que j'étais du côté des vainqueurs. Mais tu aurais dû voir la tête de ces rats de bureau ! Ils pensaient que je faisais semblant, prétendant avoir perdu la mémoire. Ils n'arrêtaient pas de demander des nouvelles de ma famille.";
			link.l1 = "Eh bien, qu'est-ce que tu leur as dit ?";
			link.l1.go = "BM_Irons_12";
		break;
		
		case "BM_Irons_12":
			dialog.text = "Que leur ai-je dit ? Je leur ai dit que je ne me souvenais pas. Et je ne mentais pas - je ne les ai jamais connus mes parents. J'ai été élevé par les rues, par les ouvriers et les domestiques dans les taudis. J'ai rejoint la Révolution pour eux. Bien que l'ingratitude des gens soit stupéfiante - si j'avais perdu un bras ou une jambe, ils auraient été forcés de donner à un héros comme moi une retraite immédiate. Et d'ailleurs, j'ai failli perdre la tête, littéralement !";
			link.l1 = "Eh bien, comment es-tu arrivé au Nouveau Monde, héros de guerre ?";
			link.l1.go = "BM_Irons_13";
		break;
		
		case "BM_Irons_13":
			dialog.text = "En doutes-tu ? Se battre pour le commun des mortels - qu'est-ce qui n'est pas héroïque là-dedans ? J'espère qu'un jour des mauviettes comme toi connaîtront ce qu'est la vraie liberté !";
			link.l1 = "Bien que la liberté soit une bonne chose, d'une certaine façon, tu l'as fait sonner comme une menace. D'accord, Tommy, continue.";
			link.l1.go = "BM_Irons_14";
		break;
		
		case "BM_Irons_14":
			dialog.text = "Aye. J'ai obtenu ma démission après que la Révolution ait été gagnée, et puis j'ai réalisé que je ne pouvais rien faire d'autre que tirer et donner des coups de poing au visage des gens. Et on ne peut pas réintégrer l'armée - ils se moqueraient de toi, surtout après que j'ai lutté si fort pour ma démission. Heh, il me semble que même si j'avais vraiment perdu un bras ou une jambe, les rats de bureau auraient quand même pensé que je les cachais quelque part pour les recoudre plus tard une fois que j'aurais obtenu mes papiers de sortie, ha-ha-ha!";
			link.l1 = "C'est drôle. Mais tu ne m'as toujours pas dit comment tu t'es retrouvé ici.";
			link.l1.go = "BM_Irons_15";
		break;
		
		case "BM_Irons_15":
			dialog.text = "Oh, tu es tellement ennuyeux. Ne t'ont-ils pas appris la patience, "+GetSexPhrase("jeune gaillard","ma fille")+"? Je n'avais rien à faire chez moi à part tirer sur des canards et des cerfs, alors je suis allé dans le Nouveau Monde. J'ai navigué avec des pirates pendant un certain temps pour m'amuser, et quand je me suis lassé de l'anarchie, je suis devenu mercenaire.";
			link.l1 = "Pas une histoire très originale.";
			link.l1.go = "BM_Irons_16";
		break;
		
		case "BM_Irons_16":
			dialog.text = "Peut-être en avez-vous un meilleur ? Vous n'avez pas besoin d'un garde du corps, par hasard ? Parce que vous avez l'air... faible. Je suis inquiet que vous n'alliez pas loin, héhé. Souvenez-vous, c'est l'entourage qui fait les rois. Et une mauvaise suite peut les faire tomber.";
			link.l1 = "Et quel genre de "+GetSexPhrase("roi","reine")+" serais-je avec une suite comme toi? "+GetSexPhrase("Roi","Reine")+" du tas de fumier ?";
			link.l1.go = "BM_Irons_17";
		break;
		
		case "BM_Irons_17":
			dialog.text = "Non, non ! Je te fais une offre sincère, et tu...";
			link.l1 = "Je n'ai pas encore reçu d'offre. Combien demandes-tu pour tes services, Tommy ?";
			link.l1.go = "BM_Irons_18";
		break;
		
		case "BM_Irons_18":
			dialog.text = "Deux cent cinquante doublons d'avance ! Pour m'assurer que vous êtes sérieux et pas juste un bon à rien. Et une redevance mensuelle après cela. Je pense que nous pouvons conclure un marché.";
			link.l1 = "Et tu ne...";
			link.l1.go = "BM_Irons_19";
		break;
		
		case "BM_Irons_19":
			dialog.text = "... tu penses avoir le cran ? Heh, je ne vais même pas discuter avec toi - as-tu vu comment j'ai abattu ce cocu du phare ? Premier tir ! Pas de marchandage non plus, si c'est ce que tu penses. Tu dois montrer que tu peux te permettre un professionnel comme moi.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Oui, je peux ! Deux cent cinquante pieces d'or. Voici pour toi.";
				link.l1.go = "BM_Irons_Hire1";
			}
			link.l2 = "Tu as eu de la chance avec ce tir. Et maintenant tu essaies de gonfler ta valeur avec des vantardises. Je peux me passer d'un professionnel comme toi. C'est trop d'honneur et trop d'argent.";
			link.l2.go = "BM_Irons_NoHire1";
			link.l3 = "Je ne peux pas me le permettre pour l'instant, car je n'ai pas autant sur moi. Restez ici et ne partez pas - je vais chercher l'or sur le navire et je reviendrai.";
			link.l3.go = "BM_Irons_Wait1";
		break;
		
		case "BM_Irons_Hire1":
			RemoveDublonsFromPCharTotal(250);
			
			dialog.text = "Tu n'es pas aussi mauvais que je le pensais ! Mais tu ferais mieux de t'assurer que je ne m'ennuie pas. Ce serait un gâchis de mon talent, n'est-ce pas ? Tommy et "+pchar.name+" ! Bousculons les Caraïbes !";
			link.l1 = "Apprends à respecter la chaîne de commandement, Tommy. Et deuxièmement, je suis le capitaine pour toi. Compris ?";
			link.l1.go = "BM_Irons_Hire2";
		break;
		
		case "BM_Irons_Hire2":
			dialog.text = "Eh bien, moi oui, Capitaine Ennuyeux, "+GetSexPhrase("monsieur","mademoiselle")+".";
			link.l1 = "Oh, je commence déjà à le regretter...";
			link.l1.go = "Irons_hire";
		break;
		
		case "Irons_Hire":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = 15000;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			pchar.questTemp.IronsItemsBlock = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Irons_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_SetHP(npchar, 170.0, 170.0);
			
			// Костыли, нужно украсить интерфейс офицера ==>
			//RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			//TakeItemFromCharacter(npchar, "unarmed");
			//GiveItem2Character(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "mushket1");
			//EquipCharacterByItem(npchar, "indian_2");
			// <== Костыли, нужно украсить интерфейс офицера
			
			if (CheckAttribute(pchar, "questTemp.BM_hireInGrot"))
			{
				AddQuestRecord("BlackMark", "4");
			}
			else
			{
				AddQuestRecord("BlackMark", "1");
			}
			
			// Продолжение через неделю в джунглях
			SetTimerCondition("BM_FirstJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_Irons_NoHire1":
			dialog.text = "Eh bien, tu es un idiot, jeune "+GetSexPhrase("homme","femme")+" ! Et complètement dépourvu de jugement. Je te suggère de corriger cela ou tu ne feras pas long feu. Surtout dans l'Archipel.";
			link.l1 = "Je me débrouillerai sans toi, Tommy. Adieu.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsGoodbye");
		break;
		
		case "BM_Irons_Wait1":
			dialog.text = "Tu es sérieux ? Une bande de soldats vient de mourir ici, génie ! Ils vont probablement envoyer une autre escouade bientôt. Non, je pourrais fermer la porte du phare et organiser une défense, mais est-ce que j'en ai envie ? Non.";
			link.l1 = "Alors, que suggérez-vous ?";
			link.l1.go = "BM_Irons_Wait2";
		break;
		
		case "BM_Irons_Wait2":
			dialog.text = "Retrouve-moi dans une grotte dans la jungle. Je te donnerai quelques jours pour gagner assez pour payer mes services - tu sais manier une lame, peut-être y parviendras-tu.";
			link.l1 = "Es-tu sérieux ? Tu seras comme un rat acculé là-bas.";
			link.l1.go = "BM_Irons_Wait3";
		break;
		
		case "BM_Irons_Wait3":
			dialog.text = "Seulement s'ils me cherchent spécifiquement, avec un grand détachement. Alors je pense que ça ira. Et maintenant je dois partir - ils seront bientôt là. À plus tard.";
			link.l1 = "Oui, je dois y aller aussi, juste au cas où.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsToCave");
		break;
		
		case "BM_Irons_WaitInCave1":
			dialog.text = "Aye, te voilà ! Je commençais à penser que tu n'avais pas ce qu'il faut pour gagner de l'argent. Parfois, je crois que des gens comme toi naissent avec. Et s'ils ne l'ont pas, ils meurent dans la misère sans avoir travaillé un jour comme des gens honnêtes.";
			link.l1 = "Eh bien, eh bien, Tommy. Si tu ne veux pas rejoindre mon equipage, alors ne le fais pas. Je vois que tu aimes nicher dans ce trou.";
			link.l1.go = "BM_Irons_WaitInCave2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Irons_WaitInCave2":
			dialog.text = "Il est évident que vous ne vous êtes jamais caché dans des fosses pendant la saison des pluies en Irlande, "+GetSexPhrase("jeune freluquet","ma fille")+" ! Mais te suivre est mieux que de se cacher ici. Maintenant, à propos de cet or...";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Voici ton or.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Je ne l'ai pas encore. Je pensais vérifier si tu étais parti ailleurs.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_Irons_HireInCave1":
			RemoveDublonsFromPCharTotal(250);
			pchar.quest.BM_IronsTimeOver.over = "yes";
			pchar.questTemp.BM_hireInGrot = true;
			
			dialog.text = "Maintenant nous parlons! Que faisons-nous ensuite... Capitaine?";
			link.l1 = "D'abord, sortons de cet endroit humide, ou je vais commencer à éternuer.";
			link.l1.go = "BM_Irons_HireInCave2";
		break;
		
		case "BM_Irons_HireInCave2":
			dialog.text = "Oh, tu devrais essayer la guerre. Je me sens presque chez moi dans des endroits comme celui-ci.";
			link.l1 = "Je vois, tu as donc reçu ta démission et oublié le respect et la subordination, hein, Tommy ? Ne t'inquiète pas, je n'hésiterai pas à t'enseigner à nouveau si je dois le faire. Maintenant, allons-y.";
			link.l1.go = "Irons_hire";
		break;
		
		case "BM_Irons_NoHireInCave1":
			NextDiag.TempNode = "BM_Irons_WaitInCave3";
			
			dialog.text = "Heh, Tommy Irons ne s'enfuit jamais ! Il tient sa parole. Tiendras-tu la tienne ?";
			link.l1 = "Je travaille dessus.";
			link.l1.go = "Exit";
		break;
		
		case "BM_Irons_WaitInCave3":
			dialog.text = "As-tu apporté l'or ?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Voici ton or.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Je ne l'ai pas encore. Je pensais vérifier si tu t'étais enfui ailleurs.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_IronsJungleUhodit":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			GiveItem2Character(sld, "blade_42");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			//LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			AddQuestRecord("BlackMark", "5");
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsFirstJungle_1":
			dialog.text = "Ecoutez, Capitaine...";
			link.l1 = "Qu'est-ce que c'est, Tommy ?";
			link.l1.go = "BM_IronsFirstJungle_2";
		break;
		
		case "BM_IronsFirstJungle_2":
			dialog.text = "N'aurais-tu pas une cartouche de plus sur toi ? Pas juste une balle, mais une cartouche complète, enveloppée de papier.";
			link.l1 = "Est-ce encore une de tes blagues ? Je te donne des balles et des cartouches régulièrement, tout ce dont tu as besoin. Et pourquoi exactement une cartouche, pas une poignée ?";
			link.l1.go = "BM_IronsFirstJungle_3";
		break;
		
		case "BM_IronsFirstJungle_3":
			dialog.text = "Pourquoi prends-tu si mal ma demande ? Je ne demande pas des foutues perles, juste une cartouche. J'ai même attendu que nous soyons dans la jungle pour ne pas te distraire des affaires en ville. Alors, t'as une cartouche ?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Ouais, j'ai un tour. Tiens. Ne me fais pas une mauvaise blague avec cette balle. Compris, Tommy ?";
				link.l1.go = "BM_IronsFirstJungle_7";
			}
			link.l2 = "Pas pour l'instant, je n'en ai pas. Ce n'est pas comme si je portais une seule cartouche dans ma poche, me demandant et si Tommy la demandait...?";
			link.l2.go = "BM_IronsFirstJungle_4";
		break;
		
		case "BM_IronsFirstJungle_4":
			dialog.text = "Eh bien, c'est un bon point, et tu es vif d'esprit, hehe. Mais j'ai bien peur que ce soit là que nos chemins se séparent, alors.";
			link.l1 = "Es-tu sérieux ? Tu es vexé pour une balle ? Allons, allons au navire et prenons-en une là-bas. Si tu en as besoin si urgemment, je t'en obtiendrai une, dix, tout ce dont tu as besoin.";
			link.l1.go = "BM_IronsFirstJungle_5";
		break;
		
		case "BM_IronsFirstJungle_5":
			dialog.text = "Non. Il n'y a rien de spécial chez toi, après tout. Un bon capitaine peut toujours fournir à son équipage tout ce dont il a besoin. Alors je m'en vais.";
			link.l1 = "Et si nous étions en mer, que nous manquions de rhum, et que tu en voulais plus ? Détacherais-tu le canot et voguerais-tu au loin ? Ou sauterais-tu à l'eau ?";
			link.l1.go = "BM_IronsFirstJungle_6";
		break;
		
		case "BM_IronsFirstJungle_6":
			dialog.text = "Ha-ha-ha ! J'ai ri, mais en ce triste moment, même une bonne blague n'aidera pas. Adieu, Capitaine Ennuyeux.";
			link.l1 = "Eh bien, va au diable, Tommy. Adieu.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsFirstJungle_7":
			dialog.text = "Je ne peux rien promettre, héhé. Une bonne blague détend l'atmosphère. Mais merci, bien sûr.";
			link.l1 = "D'accord, allons-y, espèce de bouffon.";
			link.l1.go = "BM_IronsFirstJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsFirstJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_SecondJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_IronsSecondJungle_1":
			dialog.text = "Hey, Capitaine!";
			link.l1 = "Oui, Tommy ?";
			link.l1.go = "BM_IronsSecondJungle_2";
		break;
		
		case "BM_IronsSecondJungle_2":
			dialog.text = "Encore une cartouche en papier?";
			link.l1 = "Qu'est-il arrivé au dernier ? Et c'était quoi cette blague sur la cartouche ? Ça fait deux semaines que j'attends une foutue blague de ta part, mais rien.";
			link.l1.go = "BM_IronsSecondJungle_3";
		break;
		
		case "BM_IronsSecondJungle_3":
			dialog.text = "Oh, ça va être une blague mortelle, fais-moi confiance. Tu vas l'adorer, hehe. Je n'ai juste pas encore tout assemblé. Alors, qu'en est-il de la cartouche ?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Tiens. J'espère vraiment que je vais apprécier ta prochaine farce. Et où as-tu mis la dernière tournée ? Je t'en ai donné plein. Ou gardes-tu les munitions pour te battre à un endroit et les plaisanteries à un autre ?";
				link.l1.go = "BM_IronsSecondJungle_7";
			}
			link.l2 = "Je n'ai pas de munitions pour tes blagues stupides, Tommy ! Tu aurais pu demander tout un lot au lieu d'une seule cartouche il y a deux semaines !";
			link.l2.go = "BM_IronsSecondJungle_4";
		break;
		
		case "BM_IronsSecondJungle_4":
			dialog.text = "Je l'ai fait ! Je pensais que quiconque prétend être mon capitaine garde toujours ce dont son équipage a besoin.";
			link.l1 = "Je ne prétends rien être, Tommy. J'ai choisi d'être moi-même il y a longtemps. Ceux qui sont à l'aise avec moi, tant mieux. Sinon, tant pis.";
			link.l1.go = "BM_IronsSecondJungle_5";
		break;
		
		case "BM_IronsSecondJungle_5":
			dialog.text = "Eh bien, toi et moi sommes semblables à cet égard. Mais j'ai certaines exigences pour mon capitaine. Et tu ne les remplis plus, jeune homme. C'est là que nous nous séparons.";
			link.l1 = "Es-tu sérieux ? Parce que je n'avais pas une foutue cartouche de papier ?";
			link.l1.go = "BM_IronsSecondJungle_6";
		break;
		
		case "BM_IronsSecondJungle_6":
			dialog.text = "C'est hors de question. D'habitude, je conseille aux gens de faire ce qu'ils aiment et de prendre ce qu'ils veulent de la vie. Je vous conseillerais de penser davantage à vos gens à l'avenir. Adieu.";
			link.l1 = "Et je te conseille de prendre soin de ta tête - ils lui ont fait plus de mal que tu ne le penses. Adieu, Tommy.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsSecondJungle_7":
			dialog.text = "Vous le saurez. Tout en temps voulu, hehe.";
			link.l1 = "Oh, j'ai un mauvais pressentiment à ce sujet, Tommy...";
			link.l1.go = "BM_IronsSecondJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsSecondJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_ThirdJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_IronsThirdJungle_1":
			dialog.text = "J'ai une question pour vous, Capitaine.";
			link.l1 = "Oui, Tommy, qu'est-ce que c'est ?";
			link.l1.go = "BM_IronsThirdJungle_2";
		break;
		
		case "BM_IronsThirdJungle_2":
			dialog.text = "Tu n'as pas deviné ? Deviner est une compétence utile, héhé. Toi, moi, la jungle... Il y a environ deux semaines, nous avons eu cette conversation. J'ai besoin d'une autre cartouche en papier.";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Cela devient une drôle de tradition, n'est-ce pas ? Ça fait deux semaines - Tommy demande une cartouche. Voilà. Combien d'autres te faut-il pour ta blague ?";
				link.l1.go = "BM_IronsThirdJungle_5";
			}
			link.l2 = "Combien de temps encore, Tommy ?! Combien de temps cela va-t-il durer ? Est-ce que vous, les Ironsides, ne recevez qu'une cartouche avant chaque bataille ?! Je n'ai pas besoin de garder une balle sur moi à tout moment pour vos lubies, tu le sais bien !";
			link.l2.go = "BM_IronsThirdJungle_3";
		break;
		
		case "BM_IronsThirdJungle_3":
			dialog.text = "En fait, en tant que mon capitaine, c'est votre devoir de me fournir tout ce dont j'ai besoin pour les batailles et plus encore.";
			link.l1 = "Tu es confus, Tommy. C'est ton devoir d'obéir aux ordres de ton capitaine. Je vous fournis toujours tout - médicaments, munitions, rhum. Le fait que tu ne prennes pas ce dont tu as besoin à temps et que tu agisses ensuite comme un mendiant est ta seule faute !";
			link.l1.go = "BM_IronsThirdJungle_4";
		break;
		
		case "BM_IronsThirdJungle_4":
			dialog.text = "Tu es si intelligent - pourquoi n'as-tu rien accompli de notable ici jusqu'à présent ? Je vais te dire pourquoi. Parce que tu ne penses pas à l'avance, et tu n'es jamais prêt pour quoi que ce soit. Tu ne sais pas ce que tu fais, espèce d'ennuyeux. Je ne reconnaîtrai pas une telle personne comme mon commandant, alors adieu.";
			link.l1 = "Et tu n'utilises pas du tout ta tête ! Bon débarras, espèce d'imbécile !";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsThirdJungle_5":
			dialog.text = "Celui-ci fera l'affaire, hehe.";
			link.l1 = "Tu as enfin rassemblé tes esprits, alors ? Mais pour quoi faire ?";
			link.l1.go = "BM_IronsThirdJungle_6";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsThirdJungle_6":
			dialog.text = "Je te faisais juste une farce, pour voir si tu redeviendrais ton moi grincheux. Hehe. Mais merci pour la cartouche.";
			link.l1 = "Tes blagues sont étranges, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_7";
		break;
		
		case "BM_IronsThirdJungle_7":
			dialog.text = "That was a joke too. I wasn't collecting them; I was selecting them. Needed a cartridge that was close to perfect. This one will do. Yeah, with this round, the bullet will go far and true. Just like when I blew old Reasley's head off, ha-ha-ha!";
			link.l1 = "Vieux Reasley, tu as dit... Frankie le Cocu, n'est-ce pas? Celui que tu as tiré au phare? Alors, vous vous connaissez depuis longtemps, hein?";
			link.l1.go = "BM_IronsThirdJungle_8";
		break;
		
		case "BM_IronsThirdJungle_8":
			dialog.text = "Quoi? Oh, diable, ça m'a échappé. Mais je m'en fiche - je n'ai jamais été bon pour mentir ou garder des secrets.";
			link.l1 = "Je suppose que la seconde balle était destinée à quelqu'un en particulier, n'est-ce pas, Tommy ?";
			link.l1.go = "BM_IronsThirdJungle_9";
		break;
		
		case "BM_IronsThirdJungle_9":
			dialog.text = "Bien, génie. Eh bien, je me connais et mes objectifs, et je n'en ai pas honte. C'est pourquoi je me fiche de ce que tu penses - je vais te raconter toute l'histoire, pourquoi diable pas.";
			link.l1 = "Eh bien, dis-moi alors. Cela ne fera pas de mal de savoir ce que tu mijotes.";
			link.l1.go = "BM_IronsThirdJungle_10";
		break;
		
		case "BM_IronsThirdJungle_10":
			dialog.text = "Eh bien, ne m'interromps pas, comme tu le fais habituellement. Il y avait deux salauds dans la compagnie avec moi - Francis Reasley et Gabriel Callow. De vraies canailles ! Même pire que ces rats de bureau qui ne voulaient pas me donner ma démission, ce qui, tu sais, n'était pas facile à obtenir.";
			link.l1 = "Et qu'ont-ils fait ? Surtout le deuxième, Callow. As-tu aussi couché avec sa femme ? Et il t'a aussi envoyé des soldats ?";
			link.l1.go = "BM_IronsThirdJungle_11";
		break;
		
		case "BM_IronsThirdJungle_11":
			dialog.text = "Garde ta bouche fermée, n'est-ce pas ? Bien que... ça ne me dérangerait pas, héhé. Mais non. Les Royalistes nous ont attaqués ce jour-là. La cavalerie aussi. Ils étaient bien plus nombreux. Gabe et Frankie ont couru comme des lapins effrayés. Mais je suis resté avec les gars. J'étais le seul à survivre. J'ai oublié beaucoup de choses de mon enfance et de ma jeunesse, mais pas ça.";
			link.l1 = "Et tu veux te venger parce qu'ils ont fui ? Tout le monde ne se bat pas pour une idée. Chacun veut survivre. Ou presque tout le monde. Même si quelqu'un se bat pour la Révolution, il se peut qu'il ait rejoint par accident et qu'il le regrette.";
			link.l1.go = "BM_IronsThirdJungle_12";
		break;
		
		case "BM_IronsThirdJungle_12":
			dialog.text = "Ha, si je chassais chaque lâche, je devrais tirer sur le monde entier. Les lâches, au diable avec eux. Mais ils m'ont trahi. Ils ont dit à tout le monde que j'avais trahi la Révolution et massacré toute notre compagnie sur les ordres des partisans du Roi. Je t'ai menti sur quelque chose, Capitaine.";
			link.l1 = "Qu'est-ce que c'est ? En plus du fait que tu as menti sur le fait que Frankie ne te chasse que pour ce que tu as fait avec sa femme ?";
			link.l1.go = "BM_IronsThirdJungle_13";
		break;
		
		case "BM_IronsThirdJungle_13":
			dialog.text = "Non, non ! Je ne t'ai pas menti, je ne t'ai juste pas tout dit. Il y a une différence. Ce sur quoi j'ai menti, c'était la démission. Il n'y a pas eu de démission. Il y a eu un tribunal. Et le vieux Tommy chanceux - ils ont décidé de ne pas le pendre mais de l'envoyer aux carrières dans les colonies du sud. Barbade, pour être précis.";
			link.l1 = "Ouais, c'était une chance. Combien d'années as-tu travaillé là-bas ?";
			link.l1.go = "BM_IronsThirdJungle_14";
		break;
		
		case "BM_IronsThirdJungle_14":
			dialog.text = "Aucun. Puisque le tribunal terrestre m'a condamné à cause de ces rats, celui céleste là-haut a décidé de me sauver. Dès que nous avons franchi l'Archipel, nous avons ressenti son atmosphère - notre navire a été abordé par des pirates.";
			link.l1 = "Alors, au lieu des carrières et plantations de la Barbade, tu as été vendu en esclavage par des pirates ? Mais tu as dit que tu n'avais jamais travaillé dans les carrières.";
			link.l1.go = "BM_IronsThirdJungle_15";
		break;
		
		case "BM_IronsThirdJungle_15":
			dialog.text = "C'est ce que j'ai dit - quelqu'un là-haut a décidé de me sauver. Quel sauvetage c'était, héhé ! Tu as raison - les pirates ont triomphé de ceux qui aiment abuser des hommes liés et enchaînés. Mais c'était quand même un combat chaud, aussi brûlant que le soleil ici. Et nos sauveurs ont subi quelques pertes. Alors ils ont proposé à tous ceux qui le souhaitaient de les rejoindre.";
			link.l1 = "Et les as-tu rejoints ? Tu as dit que tu naviguais avec des pirates.";
			link.l1.go = "BM_IronsThirdJungle_16";
		break;
		
		case "BM_IronsThirdJungle_16":
			dialog.text = "En enfer, oui ! Les meilleures années de ma vie. Jack Mills était un capitaine avec un grand C - J'espère que tu seras comme lui un jour. J'ai navigué sur son 'Grue' pendant environ deux ans jusqu'à ce que...";
			link.l1 = "... jusqu'à ce que tu te lasses de l'anarchie, comme tu l'as dit ? Pourquoi dis-tu que c'étaient les meilleures années de ta vie ?";
			link.l1.go = "BM_IronsThirdJungle_17";
		break;
		
		case "BM_IronsThirdJungle_17":
			dialog.text = "Eh... jusqu'à ce que j'entende parler de ces deux traîtres finissant aussi dans l'Archipel. Oui, je sais, je t'ai dit que j'en avais assez de la piraterie en haute mer et tout ça. Et je t'ai déjà dit que je me fiche de ce que tu penses. C'est toujours vrai, mais je ne te connaissais pas bien quand nous nous sommes rencontrés. Je ne savais pas comment tu réagirais. C'est pourquoi j'ai dit des choses différentes.";
			link.l1 = "Tu es un menteur, Tommy ! Mais soit, pourquoi as-tu quitté le 'Crane' ?";
			link.l1.go = "BM_IronsThirdJungle_18";
		break;
		
		case "BM_IronsThirdJungle_18":
			dialog.text = "Parce que Jack était un vrai chef, alors il a dit qu'il ne ferait pas de détour pour un seul homme, qu'il ne l'attendrait pas, ne se vengerait pas, et ne s'en prendrait pas aux officiers éminents de la Marine britannique au lieu d'attaquer les gros navires marchands.";
			link.l1 = "Des officiers en vue ? Frank était un civil, je crois.";
			link.l1.go = "BM_IronsThirdJungle_19";
		break;
		
		case "BM_IronsThirdJungle_19":
			dialog.text = "Eh, il n'en a pas toujours été un. Il a toujours été un peu, tu sais, louche. Et quand il a essayé de piéger quelqu'un, il a été expulsé en disgrâce. Il a essayé de naviguer sur un marchand, mais le travail honnête n'était pas son truc. Il a fini par s'établir ici.";
			link.l1 = "Je ne l'appellerais toujours pas un officier éminent.";
			link.l1.go = "BM_IronsThirdJungle_20";
		break;
		
		case "BM_IronsThirdJungle_20":
			dialog.text = "N'oublie pas Gabe. Il est devenu lieutenant chez nous. Et il a obtenu sa commission ici à Port Royal comme capitaine du navire, le 'Principio'.";
			link.l1 = "N'a pas l'air très anglais.";
			link.l1.go = "BM_IronsThirdJungle_21";
		break;
		
		case "BM_IronsThirdJungle_21":
			dialog.text = "Bon argument ! Le navire a changé de mains comme une demoiselle de port, il a donc vu toutes sortes de choses. Mais elle est encore en bon état de navigabilité. Et Gabe est un capitaine compétent, que le diable l'emporte.";
			link.l1 = "Et Jack avait peur de traiter avec lui? Est-il aussi bon que tu le dis?";
			link.l1.go = "BM_IronsThirdJungle_22";
		break;
		
		case "BM_IronsThirdJungle_22":
			dialog.text = "D'accord, d'accord ! Plutôt qu'il ne voulait pas perdre de temps à cause de moi. En parlant de Jack, j'ai apprécié quelques traditions que j'ai vues pour la première fois chez lui - la mise au pilori et la distribution de marques noires. Cela m'a donné une idée amusante à l'époque.";
			link.l1 = "Noires... marques ? Tu veux dire un point noir, n'est-ce pas ? Et qu'est-ce que c'était, Tommy ? Je ne pense pas qu'il saurait quoi faire si tu lui avais remis un point noir. Est-ce que c'est ce qui s'est passé ? Tu voulais le lui remettre, et il t'a attaqué dès qu'il t'a vu, alors tu as couru vers le phare, et il a emmené avec lui une escouade de soldats, leur disant que tu étais un pirate ?";
			link.l1.go = "BM_IronsThirdJungle_23";
		break;
		
		case "BM_IronsThirdJungle_23":
			dialog.text = "Je préfère appeler cela une marque noire. Cela sonne simplement mieux. Une simple marque noire n'aurait rien fait comprendre à cet homme. Mais une marque noire faite avec notre mouchoir en soie, qui était une caractéristique distinctive de notre compagnie - ça, il comprendrait. Je l'ai glissée discrètement dans sa poche. Puis je me suis assuré qu'il me voyait me diriger vers le phare. Vous connaissez la suite.";
			link.l1 = "Et les contrebandiers ?";
			link.l1.go = "BM_IronsThirdJungle_24";
		break;
		
		case "BM_IronsThirdJungle_24":
			dialog.text = "Mauvais endroit, mauvais moment. J'ai même ressenti un peu de pitié pour eux. Mais juste un peu, héhé.";
			link.l1 = "Et pour Frankie ?";
			link.l1.go = "BM_IronsThirdJungle_25";
		break;
		
		case "BM_IronsThirdJungle_25":
			dialog.text = "Qui s'en soucie maintenant ? Nous avons des poissons plus gros à frire. Cela laisse Gabe. Cela va être délicat. Nous devons...";
			link.l1 = "Nous ?";
			link.l1.go = "BM_IronsThirdJungle_26";
		break;
		
		case "BM_IronsThirdJungle_26":
			dialog.text = "Eh bien, c'est une chose d'apprendre une histoire intéressante, et une autre d'en créer une soi-même ! Voici donc le plan. Nous devrons laisser à Gabe une autre marque noire spéciale - j'en ai déjà préparé une. Ensuite, nous suivrons sa piste jusqu'à Portland Cove, où nous nous occuperons de lui sans laisser de trace.";
			link.l1 = "Où allons-nous le planter ?";
			link.l1.go = "BM_IronsThirdJungle_27";
		break;
		
		case "BM_IronsThirdJungle_27":
			dialog.text = "Ha ha ha, c'est ce que je voulais dire quand j'ai dit que je souhaitais que tu sois plus comme Jack, Capitaine. Allez, ne sois pas ennuyeux, je vois tes yeux brûler !";
			link.l1 = "En fait, j'étais plutôt intéressé par votre histoire.";
			link.l1.go = "BM_IronsThirdJungle_28";
		break;
		
		case "BM_IronsThirdJungle_28":
			dialog.text = "Chez lui, bien sûr ! Quelle sorte de question est-ce là ? Il s'est installé à Port Royal. Donc toi et moi allons accoster dans la crique, pour pouvoir quitter l'île si quelque chose tourne mal.";
			link.l1 = "Sais-tu où se trouve sa maison ?";
			link.l1.go = "BM_IronsThirdJungle_29";
		break;
		
		case "BM_IronsThirdJungle_29":
			dialog.text = "Non. Mais ce n'est pas difficile à découvrir. Nous demanderons aux ivrognes - ils vendraient leur mère si vous leur offriez un verre ou deux. Eh bien, que penses-tu de mon plan ?";
			if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) > 24 && GetSummonSkillFromName(pchar, SKILL_GRAPPLING) > 24 && GetSummonSkillFromName(pchar, SKILL_SAILING) > 24)
			{
				link.l1 = "Si c'est le capitaine d'un navire à destination de la Jamaïque, il patrouille tout le temps dans les eaux de l'île. Attaquer sous un faux pavillon est mieux que d'essayer quoi que ce soit dans la ville.";
				link.l1.go = "BM_IronsThirdJungle_Sea1";	// Морской вариант
				notification("Skill Check Passed", SKILL_SAILING);
				notification("Skill Check Passed", SKILL_ACCURACY);
				notification("Skill Check Passed", SKILL_GRAPPLING);
			}
			else
			{
				if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 25) notification("Skill Check Failed (25)", SKILL_SAILING);
				if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) < 25) notification("Skill Check Failed (25)", SKILL_ACCURACY);
				if (GetSummonSkillFromName(pchar, SKILL_GRAPPLING) < 25) notification("Skill Check Failed (25)", SKILL_GRAPPLING);
			}
			link.l2 = "C'est pas sans défauts, et tu laisses beaucoup au hasard. Mais dans l'ensemble, c'est faisable. Je suis avec toi, Tommy. T'as éliminé l'un, tu peux pas laisser l'autre partir, n'est-ce pas ?";
			link.l2.go = "BM_IronsThirdJungle_Land1";	// Сухопутный вариант
			link.l3 = "Je ne m'impliquerai pas dans ta vengeance et ne risquerai pas ma relation avec l'Angleterre pour cette aventure où tant de choses dépendent du hasard, Tommy.";
			link.l3.go = "BM_IronsThirdJungle_Otkaz1";	// Отказ
		break;
		
		case "BM_IronsThirdJungle_Sea1":
			dialog.text = "Vous êtes un risque-tout, Capitaine ! Je commence à vous apprécier. Mais Gabe sur le vieux 'Principio' n'est pas une proie facile - il est bien plus dangereux que d'autres capitaines sur un navire comme celui-là.";
			link.l1 = "Que crois-tu que je sois, un lâche, Tommy ? Nous l'aborderons nous-mêmes, et tu pourras avoir une franche discussion avec lui. Donne-lui la tache noire juste avant qu'il ne soit destitué.";
			link.l1.go = "BM_IronsThirdJungle_Sea2";
		break;
		
		case "BM_IronsThirdJungle_Sea2":
			dialog.text = "Eh bien, tu n'es peut-être pas un lâche, mais lui, il l'est, bien qu'il soit malin. Il n'attaquera pas un soldat ni même un pirate plus gros que son navire. S'il voit quelque chose comme ça à l'horizon, il se cachera sous l'aile du fort.";
			link.l1 = "Hmm, que dirais-tu des navires marchands ?";
			link.l1.go = "BM_IronsThirdJungle_Sea3";
		break;
		
		case "BM_IronsThirdJungle_Sea3":
			dialog.text = "Oui, cela pourrait fonctionner ! Mais encore une fois, rien de plus grand qu'une barque ou barkentin ! Gabe n'est pas seulement un lâche - il n'a jamais été assez avide pour que cela l'emporte sur sa prudence.";
			link.l1 = "Espérons que ça marche, Tommy. Donc, une barque ou barkentin de cinquième ordre battant pavillon espagnol ou néerlandais. Prépare-toi à rencontrer ton ancien camarade de guerre !";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SeaVariant");
		break;
		
		case "BM_IronsThirdJungle_Land1":
			dialog.text = "Je savais que je pouvais compter sur toi ! Un jour, tu pourrais même être un meilleur capitaine que Jack. Quant à ma chance... Elle m'a bien servi jusqu'à présent, alors je vais à nouveau m'y fier. Allons-y, alors ?";
			link.l1 = "Ouais, ne tirons pas ça en longueur trop longtemps. Plus tôt ce sera fini, mieux ce sera.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_LandVariant");
		break;
		
		case "BM_IronsThirdJungle_Otkaz1":
			dialog.text = "Eh bien, j'espérais autrement, mais je m'y attendais - tu n'as pas les tripes pour ce genre de chose, "+GetSexPhrase("jeune mousse","ma fille")+". Tout vrai capitaine a eu au moins quelques occasions comme celle-là où il s'est discrètement occupé des rats. Parfois même de ses propres rats.";
			link.l1 = "Je suppose que je suis censé tomber dans cette provocation et dire que j'ai changé d'avis et que je vais prouver que je suis un vrai capitaine, hein, Tommy ? Mais je comprends ton désir de vengeance. Je ne vais pas te forcer à quitter l'équipage comme Jack l'a fait. Combien de temps te faut-il pour cela ? J'arriverai en Jamaïque d'ici là.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz2";
		break;
		
		case "BM_IronsThirdJungle_Otkaz2":
			dialog.text = "Ha ha ha, tu grandis. Je te respecte presque pour ne pas être tombé dans le panneau. Mais tu n'as pas à attendre et venir me chercher après - je finirai ça moi-même. Après tout, tout ce que j'ai toujours voulu, c'est quelqu'un prêt à faire quelque chose pour moi en tant que capitaine. Alors adieu. Prends soin de l'Angleterre, ha-ha.";
			link.l1 = "Tu es vraiment étrange. Mais comme tu veux. Adieu ! Et bonne chance avec ta vengeance, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz3";
		break;
		
		case "BM_IronsThirdJungle_Otkaz3":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			AddQuestRecord("BlackMark", "6");
			AddQuestUserData("BlackMark", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("к","чка"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsJamaicaShore1":
			dialog.text = "Parfait, nous pouvons nous retirer rapidement d'ici si le besoin s'en fait sentir. Prends ceci - donne à Gabe la note et une marque noire une fois que tu auras découvert où il habite et quand il est chez lui.";
			link.l1 = "Oh, alors maintenant c'est toi qui commandes, Tommy. Mais souviens-toi, je suis toujours ton capitaine. Qu'as-tu l'intention de faire pendant que je suis en ville ?";
			link.l1.go = "BM_IronsJamaicaShore2";
		break;
		
		case "BM_IronsJamaicaShore2":
			dialog.text = "Heh, comment pourrais-je oublier ça, Capitaine Ennui? Si Gabe me repère dans les rues, il va soit donner l'alarme, soit filer de l'île, ce fichu lâche. Ne t'inquiète pas, je vais tendre une embuscade juste ici, hehehe.";
			link.l1 = "Une embuscade, dis-tu. Très bien, Tommy. Offrons à ton vieux camarade de guerre des retrouvailles dignes de ce nom, ha ha ha ha!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsJamaicaGo");
		break;
		
		case "BM_Pyanitsa_0":
			dialog.text = "Hic ! C'est du rhum formidable ! Hic... Santé !";
				link.l1 = "Ecoute, camarade, quelles sont les nouvelles en ville à propos du Capitaine Gabriel Callow ?";
			link.l1.go = "BM_Pyanitsa_1";
			DelLandQuestMark(npchar);	//Удаляем квестмарку
		break;
		
		case "BM_Pyanitsa_1":
			dialog.text = "Vieux Gabe ?! Que des bonnes choses ! Pourquoi, hic, qu'est-ce que c'est ?";
			link.l1 = "Oh, vraiment ? Heureux de l'entendre. Eh bien, il y a des ennuis avec un pirate. Le Commandant s'occupe principalement des affaires terrestres, et je ne veux pas déranger Sa Seigneurie.";
			link.l1.go = "BM_Pyanitsa_2";
		break;
		
		case "BM_Pyanitsa_2":
			dialog.text = "Alors va directement voir Gabe, je te dis ! Il n'y a pas de capitaine plus honnête ou courageux en ville que Gabe. Même le colonel Doyley le tient en haute estime. Il navigue sur un navire qui appartenait autrefois à Nicolas Sharp lui-même, peux-tu le croire ?";
			link.l1 = " Je ne suis pas encore assez ivre pour y croire, camarade.";
			link.l1.go = "BM_Pyanitsa_3";
		break;
		
		case "BM_Pyanitsa_3":
			dialog.text = "A-Aye, mais vous l'êtes ! C'est le Principio ! Ça vous dit quelque chose, hein ?";
			link.l1 = "Un navire trophée espagnol, hein ? Pourquoi ?";
			link.l1.go = "BM_Pyanitsa_4";
		break;
		
		case "BM_Pyanitsa_4":
			dialog.text = "Quand as-tu vu un rose de tes propres yeux pour la dernière fois, hein ? Je sais ce que je dis, ouah !";
			link.l1 = "Eh bien, je ne sais pas si le design du navire est si inhabituel.";
			link.l1.go = "BM_Pyanitsa_5";
		break;
		
		case "BM_Pyanitsa_5":
			dialog.text = "Mais c'est vrai ! Personne ne commanderait une telle épave maintenant, avec tous les nouveaux modèles autour ! Ils ont cessé de les construire dans les chantiers navals il y a presque t-trente ans ! Nic l'a naviguée lui-même, je te dis.";
			link.l1 = "D'accord, je l'achèterai. Alors, c'est elle le navire. Comment cet épave ne s'est-elle pas encore désintégrée ?";
			link.l1.go = "BM_Pyanitsa_6";
		break;
		
		case "BM_Pyanitsa_6":
			if (sti(pchar.basenation) == ENGLAND) sStr = "our";
			else sStr = "your";
			dialog.text = "Eh bien, elle n'est plus aussi rapide qu'à ses plus belles années - comme moi après un autre verre, ha-ha-ha ! Mais un bon capitaine peut encore tirer quelque chose de cette vieille dame. Gabe essaie de ne pas la mettre en ligne de mire non plus.";
			link.l1 = "Alors pourquoi le navire n'a-t-il pas été renommé ? Peut-être le Navire de Sa Majesté Écrasant, sous "+sStr+" ancien regime?";
			link.l1.go = "BM_Pyanitsa_7";
		break;
		
		case "BM_Pyanitsa_7":
			dialog.text = "Trad... trad-trad-tradition, ouille ! Nic lui-même ne lui a jamais donné un autre nom après avoir fui d'une plantation espagnole à Cuba. Il n'a jamais voulu oublier cette expérience - et les Espagnols non plus ! Laisse-moi te raconter, cette bataille près de la côte de Tendales...";
			if (startHeroType == 4)
			{
				link.l1 = "Tendales, hein ? Eh bien, la derniere fois que j'ai entendu ce nom, c'etait quand j'etais gamin. Je ne pensais pas que quiconque connaissait encore et se souvenait de ces cailloux maintenant abandonnes.";
				link.l1.go = "BM_Pyanitsa_8";
			}
			else
			{
				link.l1 = "Où se trouve Tendales ?";
				link.l1.go = "BM_Pyanitsa_8";
			}
		break;
		
		case "BM_Pyanitsa_8":
			dialog.text = "Ou était-ce, ouille, Highrock ? N-non, sûrement pas là... Peu importe ! Nic a combattu et remporté la victoire dans ce rose, une victoire incroyable contre la brigantine Seiche, envoyée après lui par Desmond Ray Beltrop, Baron Pirate. Ils se sont saignés mutuellement pendant longtemps jusqu'à ce que Nic abatte Desmond lui-même.";
			if (startHeroType == 4)
			{
				link.l1 = "Wow, c'est impressionnant ! Bien que, tu ne t'attendrais à rien d'autre de la part de Nicholas. Eh, les Sharps et les Beltrops sont toujours ensemble, puis séparés - apparemment, l'histoire se répète vraiment de temps en temps.";
				link.l1.go = "BM_Pyanitsa_9";
			}
			else
			{
				link.l1 = "Impressionnant. Alors, comment Sharp s'est-il séparé du navire? L'a-t-il vendue à l'arsenal?";
				link.l1.go = "BM_Pyanitsa_9";
			}
		break;
		
		case "BM_Pyanitsa_9":
			dialog.text = "Nah. Apres cet abordage, elle a commence a fuir, alors Nic l'a abandonnee. Puis avec la grande maree, la pink a ete amenee a terre, juste pres de la ville.";
			link.l1 = "Comme si quelqu'un s'intéressait à cette épave.";
			link.l1.go = "BM_Pyanitsa_10";
		break;
		
		case "BM_Pyanitsa_10":
			dialog.text = "Oh, mais la Marine était intéressée ! Des gars pratiques. Ils ont vu un navire sous pavillon anglais mais avec un nom espagnol et se sont intéressés. Nic est mort quelques années plus tard, mais son navire a continué, changeant de mains, toujours de manière sanglante.";
			link.l1 = "C'est juste une autre histoire de navire fantôme, tandis que le capitaine Gabe est bien réel. Alors, je pense que je vais aller le voir. Sais-tu où il habite ?";
			link.l1.go = "BM_Pyanitsa_11";
		break;
		
		case "BM_Pyanitsa_11":
			dialog.text = "Ha-ha ! Bien sûr, hic, je sais ! Tout le monde le sait ! Le vieux Gabe habite près du vieux moulin à vent. Il suffit de contourner la taverne et de lever la tête... hic !";
			link.l1 = "Quand est-il chez lui ? On dirait que c'est un homme occupé.";
			link.l1.go = "BM_Pyanitsa_12";
		break;
		
		case "BM_Pyanitsa_12":
			dialog.text = "C'est vrai, mate! Il a beaucoup à faire. Il est à la maison seulement le soir, à partir de dix heures. Et il se lève à six heures précises, chaque jour, tout seul. Une discipline de fer!";
			link.l1 = "Merci beaucoup ! J'en ai assez de ces contes de pirates pour l'instant.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SearchGabeHouse");
		break;
		
		case "BM_Callow1":
			if (startHeroType == 4) 
			{
				dialog.text = "Es-tu vraiment... Rumba ? J'ai entendu parler de toi... mais tu ne t'es jamais retourné contre les tiens auparavant !";
				link.l1 = "Et je ne l'ai pas fait. Ma querelle n'est pas avec mon pays. C'est avec toi, Gabe.";
				link.l1.go = "BM_Callow_Helena1";
			}
			else
			{
				dialog.text = "Tu n'es pas un marchand...";
				link.l1 = "Surprise, Gabe! On m'a dit que tu étais prudent et même lâche. L'avidité a obscurci ton jugement, n'est-ce pas? Aucun marchand ne chercherait à aborder comme je l'ai fait.";
				link.l1.go = "BM_Callow2";
			}
		break;
		
		case "BM_Callow_Helena1":
			dialog.text = " Avec moi? Quel est le problème? Nous pourrions avoir une discussion appropriée chez moi, ou même chez vous. Comme des capitaines, et... Que faites-VOUS ici?!";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_Callow2":
			dialog.text = "En effet. Alors, qui es-tu ? Non, au diable avec toi, pourtant. Qui est-ce...";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_IronsClone1":
			dialog.text = "Thomas, est-ce toi...?";
			link.l1 = "Oh oui, Gabe. Et je suis venu te punir pour ce que tu m'as fait ce jour-là.";
			link.l1.go = "BM_IronsClone2";
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			CharacterTurnByChr(sld, CharacterFromID("IronsClone"));
			sld = CharacterFromID("IronsClone");
			CharacterTurnByChr(sld, &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]);
		break;
		
		case "BM_IronsClone2":
			dialog.text = "Me punir ?! Surveille ton langage, Thomas ! Si l'un de nous mérite une punition, c'est bien toi ! Tu avais dit que tu apporterais des renforts ! Et nous avons attendu, mourant sous les balles et les épées de la cavalerie du Roi !";
			link.l1 = "J'ai couru sacrément vite pour amener de l'aide ! Mais j'ai été dépassé par une autre foutue force ! Les maudits partisans de Charles étaient partout ! Ils m'ont immobilisé, j'ai failli mourir ! Heureusement, ils ont pensé que j'étais mort. Mais tu sais ce que j'ai vu, Gabe ?!";
			link.l1.go = "BM_IronsClone3";
		break;
		
		case "BM_IronsClone3":
			dialog.text = "Qu'est-ce que c'est, Tom ? Tu es prêt à inventer n'importe quelle histoire pour que cet homme te croie ?!";
			link.l1 = "Eh bien, cet homme-là ne me trahira pas de toute façon. Ce n'est pas un rat comme certaines personnes.";
			link.l1.go = "BM_IronsClone4";
		break;
		
		case "BM_IronsClone4":
			dialog.text = "Il n'a pas le choix ! Attaquer un navire de la marine anglaise !";
			link.l1 = "Oh, il avait un choix depuis le début. Et il a choisi de m'aider. Toi et Frankie aviez un choix aussi. Vous avez choisi de fuir pour ne pas mourir. Et puis vous êtes revenus et m'avez trouvé, à moitié mort. Et vous avez raconté vos vilains mensonges au tribunal. Vous saviez que personne ne m'écouterait parce que j'avais été frappé à la tête et que j'avais perdu la mémoire !";
			link.l1.go = "BM_IronsClone5";
		break;
		
		case "BM_IronsClone5":
			dialog.text = "Personne ne t'aurait écouté de toute façon. Tu as toujours été un... dévergondé, Thomas.";
			link.l1 = "Oh, donc tu ne caches pas ce que tu as fait ce jour-là. J'ai quelque chose pour toi, Gabe. Une marque noire. Mais à quoi bon te la donner maintenant que le navire a été réquisitionné et que nous sommes sur le point de répandre tes tripes, hi hi hi hi hi hi...";
			link.l1.go = "BM_IronsClone6"; // здесь переход на кейс с боёвкой
		break;
		
		case "BM_IronsClone6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			locCameraTarget(PChar);
			locCameraFollow();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			
			sld = CharacterFromID("IronsClone");
			LAi_SetCheckMinHP(sld, 1, true, "");
			LAi_SetCurHPMax(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "reload", "reload1", "BM_IronsCloneMushket", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "BM_CabinDialog4");
		break;
		
		case "BM_IronsClone8":
			dialog.text = "Eh bien, Gabe est destitué, héhé. Ça fait longtemps que je voulais dire ça. Dommage que tu ne puisses plus l'entendre, l'ami. Oh, attends ! Tu pourrais - depuis l'enfer.";
			link.l1 = "Allons, Tommy. Même s'il ne l'a pas entendu, il a vu et su que c'était exactement ton stratagème et ta vengeance. Et il ne pouvait rien y faire.";
			link.l1.go = "BM_IronsClone9";
		break;
		
		case "BM_IronsClone9":
			if (startHeroType == 4) 
			{
				dialog.text = "Heh, tu as raison ! Sacrebleu, tu as raison ! Merci de m'avoir aidé sur ce coup-là. Tu sais, je pensais que tu n'étais qu'une fille gâtée dans une tenue voyante qui avait obtenu un navire pour s'amuser. Mais tu es un sacré bon capitaine ! Je parie que tu donnerais du fil à retordre à Jack.";
			}
			else
			{
				dialog.text = "Eh, tu as raison ! Sacrebleu, c'est vrai ! Merci de m'avoir aidé sur ce coup-là. Tu sais, je pense que tu es aussi bon capitaine que Jack. Ou même meilleur !";
			}
			link.l1 = "Oh, maintenant tu me flattes. Merci. Je suppose.";
			link.l1.go = "BM_IronsClone10";
		break;
		
		case "BM_IronsClone10":
			dialog.text = "Pas du tout. Pas de flatterie, vraiment. Comme vous l'avez peut-être remarqué, je ne loue presque jamais personne de cette façon. Alors ferme-la et sois content que je te tienne en si haute estime.";
			link.l1 = "Je ne dirais pas que j'apprécie la façon dont tu le présentes, même si je suis content que tu me considères généralement comme un bon capitaine. Mais... la chaîne de commandement, Tommy, la chaîne de commandement.";
			link.l1.go = "BM_IronsClone11";
		break;
		
		case "BM_IronsClone11":
			if (startHeroType == 4) 
			{
				dialog.text = "Oh, allez! J'ai l'impression que tout ce que nous avons traversé nous a rapprochés, Ellie. Nous pourrions être plus que simplement capitaine et officier. Admets-le - même si ce n'est que pour toi-même tu le ressens aussi.";
				link.l1 = "Seulement dans tes rêves les plus fous, Tommy. Et c'est Helen, pas Ellie. Mais je suppose que tu peux m'appeler Rumba maintenant.";
				link.l1.go = "BM_IronsClone12";
			}
			else
			{
				dialog.text = "Oh, allez, espèce de rabat-joie ! Il me semble que nous ne sommes plus seulement un capitaine et son officier, mais les plus vrais des amis. Ne penses-tu pas ?!";
				link.l1 = "Heh. Peut-être. Il vaut mieux être ton ami que ton ennemi. Et puisque l'étiquette n'est clairement pas ton fort, je suppose que je devrai m'y habituer.";
				link.l1.go = "BM_IronsClone12";
			}
		break;
		
		case "BM_IronsClone12":
			dialog.text = "J'ai un... cadeau pour vous, Capitaine.";
			link.l1 = "Whoa, regarde ça ! Une tache noire ? Tu veux que je sois destitué aussi, hein, Tommy ? Tu veux être capitaine toi-même ? Ha-ha-ha-ha ! Je pensais que tu disais que nous étions camarades.";
			link.l1.go = "BM_IronsClone13";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_IronsClone13":
			dialog.text = " C'est une marque noire, espèce de crétin. Tu sais, je commence à penser que dès que j'ai brodé le crâne et les os croisés sur ce foulard, il a commencé à me porter chance. Je ne peux pas l'expliquer. Prends-le. Aussi... si tu veux, tu peux toujours emprunter mon épée et mon armure fidèles... ce qu'il en reste, ha-ha ! Ça te sera utile ! Tu iras loin. Et je veux en être témoin. Je ne veux pas que tu te fasses tuer par une balle perdue. ";
			link.l1 = "Merci, camarade ! Je ferai de mon mieux. Et toi - regarde et admire, ha-ha-ha !";
			link.l1.go = "BM_IronsClone14";
		break;
		
		case "BM_IronsClone14":
			dialog.text = "Admirer, bien sûr, ha-ha-ha. Aye. Alors, qu'as-tu décidé de faire de ce navire ? D'un côté, il n'est plus vraiment utile. De l'autre, il n'y en a pas d'autres comme lui. Je ne pense pas qu'il y en aura jamais d'autres.";
			if (startHeroType == 4) 
			{
				link.l1 = "Je n'ai pas encore décidé... Tu sais, Tommy, je ressens une sorte de lien avec ce navire. Je ne peux pas l'expliquer. Alors, débarrassons-nous d'abord de ce cadavre puant. S'il n'y a pas de fuites dans la cale, je prendrai probablement cette fille pour moi.";
			}
			else
			{
				link.l1 = "Je ne sais pas, Tommy. Je n'ai pas encore décidé. En attendant, débarrassons-nous du corps de Gabe. Au cas où nous garderions le navire.";
			}
			link.l1.go = "BM_IronsClone15";
		break;
		
		case "BM_IronsClone15":
			DialogExit();
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		case "BM_IronsPinkPotopil1":
			dialog.text = "Eh bien, vous avez fait du bon boulot sur ce vieux rafiot, Capitaine ! Et bien que je voulais en finir avec Gabe de mes propres mains, je ne mettrai pas en colère le Créateur en minimisant cette victoire.";
			link.l1 = "Ce ne serait pas nécessaire, Tommy. J'espère que ton âme est en paix maintenant.";
			link.l1.go = "BM_IronsPinkPotopil2";
		break;
		
		case "BM_IronsPinkPotopil2":
			if (startHeroType == 4) 
			{
				dialog.text = "Je sens que tout ce que nous avons traversé nous a rapprochés, Ellie. Nous pourrions être plus que simplement capitaine et officier. Admets-le - même si ce n'est qu'à toi-même, tu le ressens aussi.";
				link.l1 = "Seulement dans tes rêves les plus fous, Tommy. Et c'est Helen, pas Ellie. Mais je suppose que tu peux m'appeler Rumba maintenant si tu arrêtes avec ces flatteries.";
			}
			else
			{
				dialog.text = "Je n'ai jamais été aussi heureux de ma vie ! Merci de m'avoir aidé à traverser cela. Tu sais, je pense que tu es aussi bon que Jack en tant que capitaine. Ou même meilleur !";
				link.l1 = "Oh, vous me flattez. Merci aussi pour la comparaison, je suppose.";
			}
			link.l1.go = "BM_IronsPinkPotopil3";
		break;
		
		case "BM_IronsPinkPotopil3":
			if (startHeroType == 4) 
			{
				dialog.text = "Pas du tout. Aucun compliment. Comme vous l'avez peut-être remarqué, je fais rarement des éloges de ce genre. Alors ferme-la et sois heureux que je te tienne en si haute estime.";
				link.l1 = "Je ne dirais pas que j'aime la manière dont tu l'as formulé, mais je suis content que tu me considères généralement comme un bon capitaine. Mais... la chaîne de commandement, Tommy, la chaîne de commandement.";
			}
			else
			{
				dialog.text = "Pas du tout. Aucune flatterie quelle qu'elle soit. Comme vous l'avez peut-être remarqué maintenant, je loue rarement quelqu'un de cette manière. Alors tais-toi et sois heureux que je te juge si hautement.";
				link.l1 = "Je ne dirais pas que j'aime ta manière de le dire, mais je suis content que tu me considères généralement comme un bon capitaine. Mais... la hierarchie, Tommy, la hierarchie.";
			}
			link.l1.go = "BM_IronsPinkPotopil4";
		break;
		
		case "BM_IronsPinkPotopil4":
			if (startHeroType == 4) 
			{
				dialog.text = "Oh, allez, vieux barbon ! Il me semble que toi et moi ne sommes plus simplement un capitaine et son officier, mais les plus vrais amis. Ne penses-tu pas ?!";
				link.l1 = "Heh. Peut-être. Il vaut mieux être ton ami que ton ennemi. Et puisque l'étiquette n'est manifestement pas ton fort, je suppose que je devrai m'y habituer.";
			}
			else
			{
				dialog.text = "Oh, allez, espèce d'ennuyeux ! Il me semble que toi et moi ne sommes plus simplement un capitaine et son officier, mais les plus vrais des amis. Ne penses-tu pas ainsi ?!";
				link.l1 = "Heh. Peut-être. Il vaut mieux être ton ami que ton ennemi. Et puisque l'étiquette n'est visiblement pas ton fort, je suppose que je devrai m'y habituer.";
			}
			link.l1.go = "BM_IronsPinkPotopil5";
		break;
		
		case "BM_IronsPinkPotopil5":
			if (startHeroType == 4) 
			{
				dialog.text = "J'ai un... cadeau pour vous, Capitaine.";
			}
			else
			{
				dialog.text = "J'ai un... cadeau pour vous, Capitaine.";
			}
			link.l1 = "Whoa, regarde ça ! Une tache noire ? Tu veux que je sois destitué aussi, hein, Tommy ? Tu veux devenir capitaine toi-même ? Ha-ha-ha-ha ! Je pensais que tu disais qu'on était camarades.";
			link.l1.go = "BM_IronsPinkPotopil6";
		break;
		
		case "BM_IronsPinkPotopil6":
			dialog.text = "C'est une MARQUE noire, espèce de crétin. Tu sais, je commence à penser que dès que j'ai brodé le crâne et les os croisés sur ce foulard, ça a commencé à me porter chance. Je ne peux pas l'expliquer. Prends-le. Aussi... si tu veux, tu peux toujours emprunter ma fidèle épée et mon armure... ce qu'il en reste, ha-ha ! Ça te sera utile ! Tu iras loin. Et je veux en être témoin. Je ne veux pas que tu te fasses tuer par une balle perdue.";
			link.l1 = "Merci, l'ami ! Je ferai de mon mieux. Et toi - regarde et admire, ha-ha-ha !";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_PinkPotopil_4");
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabeHouseGood1":
			notification("Reputation Check Passed", "None");
			if (startHeroType == 4)
			{
				dialog.text = "Qui a besoin de croire en une telle chose... Je suis désolé, mademoiselle. "+TimeGreeting()+". Comment puis-je vous aider? Vous avez l'air très inquiet.";
			}
			else
			{
				dialog.text = "Quoi ? Qui vient à cette heure tardive ? Vous avez l'air plutôt préoccupé, monsieur. Que puis-je faire pour vous ?";
			}
			link.l1 = "Je m'excuse de troubler votre repos, Capitaine Callow. Je m'appelle "+GetFullName(pchar)+", et je viens de la part de l'un de vos anciens compagnons d'armes.";
			link.l1.go = "BM_GabeHouseGood2";
		break;
		
		case "BM_GabeHouseGood2":
			dialog.text = "Quel camarade ? J'en avais beaucoup, tant dans le Vieux Monde que dans le Nouveau.";
			link.l1 = "Au début, je comptais seulement laisser quelque chose dans l'un de vos coffres. Ou peut-être sur la table, pour que vous le remarquiez plus vite. Cela concerne un homme de votre passé. Tenez, jetez un œil et lisez-le vous-même.";
			link.l1.go = "BM_GabeHouseGood3";
		break;
		
		case "BM_GabeHouseGood3":
			dialog.text = "Une tache noire ? Je ne me souviens pas de pirates parmi mes camarades. Ou bien certains gars sont-ils tombés dans cette vie ? De la soie noire ? Vraiment... Oh, Thomas. Je suis étonné qu'un homme comme toi ait des affaires avec ce vaurien.";
			link.l1 = "Je m'excuse, mais ce n'est pas à vous de le traiter de vaurien. Vous avez fui le champ de bataille et calomnié Tom. Peut-être vous êtes-vous repenti plus tard et devenu un officier exemplaire ici dans l'Archipel, mais cela ne change pas le passé.";
			link.l1.go = "BM_GabeHouseGood4";
		break;
		
		case "BM_GabeHouseGood4":
			dialog.text = "Il te l'a dit ? Pas étonnant - il a toujours su trouver l'homme qu'il fallait pour raconter ses histoires. Thomas avait une langue d'argent. Tu ne le connais pas, ni la vraie histoire, ni dans quoi tu t'embarques. Je peux te le dire - puisque je ne dormirai de toute façon pas maintenant.";
			link.l1 = "C'est jamais une mauvaise idee d'ecouter. Continuez, Capitaine Callow.";
			link.l1.go = "BM_GabeHouseGood5";
		break;
		
		case "BM_GabeHouseGood5":
			dialog.text = "Alors, Thomas prétend que je me suis enfui et que je l'ai calomnié ? Eh bien, tu devrais savoir que c'était le contraire ! Quand la cavalerie du Roi s'est approchée, Tom a dit qu'il allait chercher des renforts. Donc nous ne nous sommes pas retirés - nous avons attendu. Toute notre compagnie a été massacrée ! Si nous n'avions pas attendu les renforts qu'il avait promis, nous aurions pu nous replier et survivre ! Au final, il n'y avait que moi, Frankie, et ce maudit Thomas qui avons survécu.";
			link.l1 = "Donc ce que tu dis, c'est...";
			link.l1.go = "BM_GabeHouseGood6";
		break;
		
		case "BM_GabeHouseGood6":
			dialog.text = "Je dis que le sang de nos garçons est autant sur les mains de Tom que sur celles des royalistes. Il a de la chance d'avoir été condamné aux travaux forcés et non à la pendaison ! Et maintenant, il a le culot de me tenir rancune et de me défier en duel ! Il n'en est pas digne !";
			link.l1 = "Donc tu ne partiras pas ? Tu réalises ce que cela signifie. Les lois de l'honneur sont écrites pour tout le monde.";
			link.l1.go = "BM_GabeHouseGood7";
		break;
		
		case "BM_GabeHouseGood7":
			dialog.text = "Bien sûr que oui. Et c'est pourquoi j'irai. Nous devons terminer ce que notre cour républicaine n'a pas pu à cause des honneurs militaires passés de Tom. Et toi... tu sembles être une personne décente. Je te conseillerais de choisir tes fréquentations plus judicieusement. Ne te mêle pas de Tom et de son genre.";
			link.l1 = "Mais Thomas est maintenant mon subordonne, un officier sur mon navire. "+GetSexPhrase("Je garderai un oeil sur lui et ne le laisserai pas se déshonorer davantage s'il survit à sa rencontre avec toi.","")+"";
			link.l1.go = "BM_GabeHouseGood_Tommi1";
			link.l2 = "Et que feriez-vous à ma place, Capitaine Callow ?";
			link.l2.go = "BM_GabeHouseGood_Gabe1";
		break;
		
		case "BM_GabeHouseGood_Tommi1":
			dialog.text = "Eh, si Tom pouvait te convaincre de son histoire, il n'aura aucun mal à le faire à nouveau.";
			link.l1 = ""+GetSexPhrase("Mais par les lois de l'honneur, je ne peux pas le trahir. Je suis","Je suis")+" responsable de mes hommes.. Je ne serai pas comme lui. Et je serai plus prudent et critique envers lui dorénavant s'il survit.";
			link.l1.go = "BM_GabeHouseGood_Tommi2";
		break;
		
		case "BM_GabeHouseGood_Tommi2":
			dialog.text = "C'est une decision difficile. Mais je n'essaierai pas de te faire changer d'avis. Eh bien, adieu, "+GetSexPhrase("monsieur","mademoiselle")+" - Je dois encore me préparer à rencontrer Tom.";
			link.l1 = "Adieu, Capitaine Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_GabeHouseGood_Gabe1":
			dialog.text = "A que justice soit faite ! Aidez-moi à abattre Thomas, "+pchar.lastname+" . C'est un rare vaurien et un lâche, mais un excellent tireur - ce ne sera pas facile. Mais ensemble...";
			link.l1 = "Hmm, t'aider a vaincre Thomas? Y a-t-il beaucoup d'honneur dans un tel duel? Vous pouvez le régler vous-mêmes, et je resterai à l'écart.";
			link.l1.go = "BM_GabeHouseGood_Gabe2";
		break;
		
		case "BM_GabeHouseGood_Gabe2":
			dialog.text = "Le connaissant, je doute d'obtenir un duel équitable. En restant neutre, tu ne fais que cautionner l'injustice. Ai-je raison ?";
			link.l1 = "Il semble que tu connaisses Tom mieux que moi, et comment il est vraiment. Tu as raison - il prépare déjà une embuscade dans la baie de Portland, et il compte sur mon aide - tout comme toi maintenant.";
			link.l1.go = "BM_GabeHouseGood_Gabe3";
		break;
		
		case "BM_GabeHouseGood_Gabe3":
			dialog.text = "Alors ce n'est pas un duel, mais une bagarre. Mais je ne propose pas que nous tuions Thomas nous-mêmes. Nous l'arrêterons ! J'amènerai des soldats, et nous finirons ce que nous ne pouvions pas dans le Vieux Monde. S'ils essaient de l'innocenter à nouveau, j'écrirai au Colonel ou même je l'amènerai ici pour le procès. Si Thomas ne dépose pas les armes, c'est de sa faute.";
			link.l1 = "Cela semble bien mieux.";
			link.l1.go = "BM_GabeHouseGood_Gabe4";
		break;
		
		case "BM_GabeHouseGood_Gabe4":
			dialog.text = "Heureux de l'entendre, "+pchar.lastname+" ! Je me rends compte qu'il ne vous est peut-etre pas facile de prendre une telle decision, mais je vous assure que vous avez fait le bon choix. Et pour m'en assurer, je vais vous aider avec autre chose.";
			link.l1 = "Qu'est-ce que c'est, Capitaine Callow ?";
			link.l1.go = "BM_GabeHouseGood_Gabe5";
		break;
		
		case "BM_GabeHouseGood_Gabe5":
			dialog.text = "Tiens, prends ça. Ce n'est pas un cadeau, mais un prêt - Thomas, comme je l'ai dit, est un très bon combattant, et il vaut mieux l'affronter avec une arme convenable, pas un morceau de fer rouillé. Le colonel Doyley lui-même m'a donné cette beauté, mais pour un vrai combat, je choisirais toujours une épée large.";
			link.l1 = "En effet, c'est une rapière splendide. Merci.";
			link.l1.go = "BM_GabeHouseGood_Gabe6";
			GiveItem2Character(PChar, "blade_40");
		break;
		
		case "BM_GabeHouseGood_Gabe6":
			dialog.text = "N'me remerciez pas - je vous le prête, je ne vous le donne pas, souvenez-vous ? Maintenant, rendez-vous à l'anse et jouez votre rôle avec notre cher Tom, pendant que je rassemble des renforts. A bientôt là-bas.";
			link.l1 = "À plus tard, Capitaine Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_GabePlan");
		break;
		
		case "BM_GabeHouseNeutral1":
			notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			if (startHeroType == 4)
			{
				dialog.text = "Qui êtes-vous, mademoiselle ? Vous devez avoir la mauvaise adresse. Je, euh, n'ai pas commandé de services de nuit.";
				link.l1 = "Helen MacArthur. Et gardez vos désirs en échec, M. Callow. Je suis une fille honnête. Notre climat me fait sentir chaude, même la nuit. N'avez-vous pas eu honte de dire cela à une fille inconnue ? On m'a parlé de vous comme d'un officier exemplaire.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
			else
			{
				dialog.text = "Qui êtes-vous, et que voulez-vous? Je n'aime pas votre sourire en coin, monsieur.";
				link.l1 = ""+GetFullName(pchar)+". Et vous n'etes pas tres hospitalier, Monsieur Callow.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
		break;
		
		case "BM_GabeHouseNeutral2":
			dialog.text = "Accueilles-tu les étrangers à cette heure différemment ?";
			link.l1 = "On m'a dit que tu n'es pas chez toi à d'autres moments.";
			link.l1.go = "BM_GabeHouseNeutral3";
		break;
		
		case "BM_GabeHouseNeutral3":
			dialog.text = "Bien sûr que non - j'ai le service, le devoir et le travail honnête, des mots qui semblent inconnus pour vous, à en juger par votre apparence.";
			link.l1 = "Quelle confiance en soi ! Mais alors, tu n'aurais pas convaincu le colonel Doyley et les autres de ton honnêteté autrement. Je n'ai besoin de rien de toi, Gabe, mais une vieille connaissance à toi, oui. Voilà pour toi.";
			link.l1.go = "BM_GabeHouseNeutral4";
		break;
		
		case "BM_GabeHouseNeutral4":
			dialog.text = "Convaincu? Gabe? Je dis! Une tache noire? Alors tu es un pirate? Attends une minute... soie noire... cela pourrait-il être... Oh, je vois. Thomas, sale bâtard, toujours en colère contre moi et Frank pour t'avoir dénoncé, ha ha ha ha!";
			link.l1 = "Je dis ! Tom est un officier sur mon navire et mérite le respect. C'est l'un des meilleurs tireurs de l'Archipel.";
			link.l1.go = "BM_GabeHouseNeutral5";
		break;
		
		case "BM_GabeHouseNeutral5":
			dialog.text = "Je n'ai pas dit qu'il était un mauvais tireur. Mais tu ne connais pas très bien Thomas, je vois. C'est lui qui nous a tous trahis. Mais je vois qu'il est inutile de discuter avec toi - vous êtes manifestement faits l'un pour l'autre.";
			link.l1 = "Je m'en moque. Garde tes histoires pour Doyley et tous ces simples d'esprit naifs. Si tu es aussi courageux et honorable qu'on le dit, tu accepteras le defi et tu viendras maintenant. Alors, l'acceptes-tu?";
			link.l1.go = "BM_GabeHouseNeutral6";
		break;
		
		case "BM_GabeHouseNeutral6":
			dialog.text = "Je le fais, je le fais. Maintenant, sortez de chez moi avant que j'appelle les gardes.";
			link.l1 = "Ce sera mon plaisir, Gabe.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_IronsJamaicaJungle1":
			if (CheckAttribute(pchar, "questTemp.BM_GabePlan"))
			{
				dialog.text = "Pourquoi es-tu si nerveux ? As-tu peur, ou quoi ?";
				link.l1 = "Tout le monde serait nerveux en voyant un homme avec un mousquet courir vers eux - je ne t'ai pas reconnu au début. Que fais-tu ici, Tommy ?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_2";
			}
			else
			{
				dialog.text = "Comment ça s'est passé ? Hé, hé, pourquoi me regardes-tu comme ça ? Tu m'as fait peur, héhé.";
				link.l1 = "Qui fait peur à qui ! Qui s'enfuit comme ça ?! Nous avons convenu de rencontrer les invités dans la crique !";
				link.l1.go = "BM_IronsJamaicaJungle2";
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_2":
			dialog.text = "Heh, eh bien, peut-être. J'en avais marre d'attendre - nos chers invités et toi. Et j'ai décidé que cet endroit était mieux adapté pour une bonne embuscade. Après tout, je suis un chasseur, pas un duelliste.";
			link.l1 = "Je vois.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_3";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_3":
			dialog.text = "Aye. Alors, as-tu laissé mon cadeau chez Gabe ? Tu as pris ton temps. Je serais bien plus rapide si je pouvais entrer en ville. Qu'est-ce qui te tracasse, Capitaine ? Qu'est-ce qui ne va pas ?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Digne de confiance) Je suis nerveux. Gabe est un lâche, mais il n'est pas stupide. Et si un peloton entier de soldats venait ici à sa place ? Ou s'ils s'approchaient de la crique et coulaient notre navire en premier ?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD1";
				notification("Trustworthy", "Trustworthy");
			}
			else
			{
				link.l2 = "Gabe m'a vu. Je devais courir.";
				link.l2.go = "BM_IronsJamaicaJungle_GabePlan_4";
				notification("Perk Check Failed", "Trustworthy");
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD1":
			dialog.text = "Heh, je comprends - je ne suis pas tout à fait sûr que ça marchera moi-même. C'est la première fois qu'il se passe quelque chose d'aussi gros pour toi, hein ? Ça va, ça arrive. J'ai tout prévu. Si les soldats viennent sans Gabe, on s'en va simplement. S'ils viennent avec Gabe, je lui mettrai une balle entre les yeux, et encore une fois, on s'en va simplement. Et si un navire arrive dans la baie, on file à Maroon Town - ils n'oseront pas y aller, et ensuite on décidera de la suite.";
			link.l1 = "Je vois que tu as vraiment pensé à tout, Tommy.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD2";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD2":
			dialog.text = "Bien sûr que je l'ai. Maintenant, attendons notre invité...";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe");
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_4":
			dialog.text = "Ha ha, tu es aussi bon voleur que je suis royaliste. Mais pourquoi ne me regardes-tu pas dans les yeux... Capitaine ? Tu parlais à Gabe, n'est-ce pas ?";
			link.l1 = "Non, de quoi parles-tu ? Pourquoi lui parlerais-je même ?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_5";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_5":
			dialog.text = "Parce que vous êtes tous de grands bavards. Tout ce que vous faites, c'est parler. Alors, qu'est-ce que notre cher Gabe vous a dit ?";
			link.l1 = "Est-ce important, Tommy ?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_6";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_6":
			dialog.text = "Franchement, non. Ça le fait si tu ne me poignardes pas dans le dos. Mais on dirait que tu l'as déjà fait. Il t'a persuadé de prendre son parti, n'est-ce pas ?";
			link.l1 = "Non. Pas exactement. Baisse le pistolet, Tommy. Je te promets que rien d'irréparable ne doit arriver. Tu pourrais travailler dans les carrières, peut-être. Je demanderai à Gabe de faire preuve de clémence. Je demanderai même au Colonel Doyley si je dois le faire.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_7";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_7":
			dialog.text = "Quel bon Samaritain tu es. Me montrer de la clémence pour que je puisse cracher mes poumons après des années dans la carrière ? Je ne retourne pas aux bateaux-prisons. Plus jamais. Et toi... J'aurais dû savoir que tu n'étais qu'un autre rat. Il y a quelque chose dans ta façon de regarder. Je vais m'occuper de toi d'abord, pour que Gabe soit plus facile ensuite.";
			link.l1 = "Tu ne nous laisses pas le choix !";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaSTommi");
		break;
		
		case "BM_GabePlan_TommiMertv":
			dialog.text = "Eh bien, je vois que vous l'avez déjà fait, "+GetSexPhrase("monsieur","mademoiselle")+". Et je rassemblais une escouade, pensant que l'avantage numérique ferait réfléchir Tom à deux fois et qu'il déposerait les armes.";
			link.l1 = "Et tu as pris ton temps, Capitaine Callow.";
			link.l1.go = "BM_GabePlan_TommiMertv2";
		break;
		
		case "BM_GabePlan_TommiMertv2":
			dialog.text = "Je t'ai dit, je rassemblais des hommes. Les meilleurs de notre garnison. Tom est un soldat vétéran après tout. Mais à qui est-ce que je raconte cela ? Bien joué, "+GetSexPhrase("Monsieur.","mademoiselle")+" "+pchar.lastname+". "+GetSexPhrase("Je suis fier de toi, jeune homme","Je dois admettre, mademoiselle, que vous possédez autant de beauté, d'intelligence, que de talent.")+"Comme je te l'ai dit lors de notre première rencontre, tu as pris la bonne décision. Maintenant, justice a été rendue.";
			link.l1 = "Ça a si bien marché pour toi. Fier de toi ?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict";
			link.l2 = "Eh bien, je ne suis pas un soldat vétéran, mais je sais me battre, comme vous l'avez peut-être remarqué. Mais je vous remercie, monsieur. La justice n'est pas un mot vide pour moi.";
			link.l2.go = "BM_GabePlan_TommiMertv_Mir";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir":
			dialog.text = "Et cela est louable, "+GetSexPhrase("jeune homme","jeune demoiselle")+" Cependant, il reste encore une chose à faire pour parfaire cette belle journée.";
			link.l1 = "Hmm, et qu'est-ce que c'est? Tom est déjà vaincu, après tout.";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir2":
			dialog.text = "Tu as quelque chose qui m'appartient. Rends-moi mon beau rapière italien s'il te plaît. Ce n'est pas qu'un cure-dent, après tout, mais un souvenir - un cadeau du Colonel Doyley lui-même.";
			if (!CheckCharacterItem(PChar, "blade_40"))
			{
				link.l1 = "Eh... Voilà le problème, Capitaine Callow... le rapière est parti. Je l'ai perdu. Je suis désolé.";
				link.l1.go = "BM_GabePlan_TommiMertv_Poteryal";			//Потеряли Рапиру
				break;
			}
			if (CheckCharacterItem(PChar, "blade_40"))
			{
				link.l2 = "Ah, bien sûr. Je vous en prie. Je n'avais pas l'intention de le voler. Je ne vais pas mentir - j'aimerais le garder. Mais le voici, Capitaine Callow.";
				link.l2.go = "BM_GabePlan_TommiMertv_Soglasen";			//Согласен
			}
			if (CheckCharacterItem(PChar, "blade_42"))
			{
				link.l3 = "J'ai une meilleure offre pour vous, Capitaine.";
				link.l3.go = "BM_GabePlan_TommiMertv_Obmen";			//Обмен
			}
			link.l4 = "Mais tu viens de l'appeler un cure-dent. De plus, tu as dit que tu n'aimes même pas les rapières. Moi, en revanche, je mérite une récompense.";
			link.l4.go = "BM_GabePlan_TommiMertv_Otkaz";				//Отказ
		break;
		
		case "BM_GabePlan_TommiMertv_Soglasen":
			dialog.text = "Tout le monde aurait voulu garder cette beauté ! Merci de me l'avoir rendue. Beaucoup de gens auraient été têtus à votre place.";
			link.l1 = "C'est à toi. Je suppose que nous avons fini ici ?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_40");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen":
			dialog.text = "Je ne suis pas intéressé. Rends simplement la rapière, et nous partirons en bons termes, "+GetSexPhrase("Monsieur.","mademoiselle")+" "+pchar.lastname+".";
			link.l1 = "Je suppose que ce rapière vous est cher parce que vous aimez les armes avec de l'histoire, ai-je raison ? J'en ai un pareil, et celui-ci est ce que vous aimeriez porter au lieu de le garder dans un tiroir.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen2";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen2":
			dialog.text = "Vraiment ? Eh bien, je ne peux pas promettre que nous parviendrons à un accord, mais je vous écoute. Je suis en effet intéressé par les armes avec une histoire. Mais cette rapière était un cadeau du Colonel. C'est pourquoi elle m'est si précieuse.";
			link.l1 = "Vous avez mentionné que vous aimez les épées larges. Tenez. Elle appartenait à notre cher Tommy. Imaginez ce que cette arme a traversé au fil des ans. Et ce qu'elle continuera à traverser avec vous.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen3";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen3":
			dialog.text = "Tu es très persuasif, jeune homme ! Brandir l'épée de Thomas... quelle ironie. Eh bien, prends la rapière. Je ne m'en sépare pas à la légère, sache-le.";
			link.l1 = "Je suis heureux que nous ayons pu parvenir à un accord. Je pense que c'est un adieu, Capitaine Callow ?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_42");
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Commerce", 500);
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal":
			dialog.text = "QUOI?! Comment as-tu pu... Comment as-tu pu perdre tout un putain de rapière?! T'es un idiot!";
			link.l1 = "Calme-toi ! Ce n'est qu'une rapière. Tu ne l'aurais jamais utilisée de toute façon. Tom est mort - n'est-ce pas la seule chose qui compte maintenant ?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal2";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal2":
			dialog.text = "Juste une rapière ?! C'était mon trésor ! Un cadeau du colonel Doyley lui-même ! Je m'en fiche si je ne l'utilisais pas !";
			link.l1 = "Alors tu n'aurais pas dû me le donner, n'est-ce pas ?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal3";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal3":
			dialog.text = "Tu ferais mieux de la fermer maintenant, "+GetSexPhrase("Monsieur.","mademoiselle")+" "+pchar.lastname+". Nous aurions pu nous séparer pacifiquement. Mais maintenant... maintenant j'aimerais te donner une leçon, "+GetSexPhrase("jeune homme","jeune demoiselle")+".";
			link.l1 = "Les cimetières sont remplis de professeurs comme toi.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz":
			dialog.text = "Bien sûr que oui. Mais tu ne peux pas simplement prendre l'arme personnelle d'un officier parce que tu lui as donné un coup de main, n'est-ce pas ?";
			link.l1 = "Je serais d'accord, mais tu ne l'utilises de toute façon pas. Ça ne fera que pendre à un clou dans ta cabine. Tandis qu'avec moi, ça trouvera un usage digne. Le colonel Doyley ne va pas vérifier si tu l'as égaré, n'est-ce pas ?";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz2";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz2":
			dialog.text = "Ce n'est pas sujet à discussion, jeune homme. Je t'ai dit dès le début, ce n'est pas un cadeau. Donne-moi la rapière. Maintenant.";
			link.l1 = ""+GetSexPhrase("Je ne suis pas un de tes soldats de plomb","Je ne suis pas une de vos putains de port")+", à recevoir des ordres de vous. Je suis capitaine de navire, tout comme vous. La rapière reste avec moi, que cela vous plaise ou non.";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz3";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz3":
			dialog.text = "On dirait que Thomas a eu un sacre effet sur toi. Alors meurs pour cela, si tu y tiens tant.";
			link.l1 = "Mes pensées exactement!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Platok":
			dialog.text = "Tiens, prends ça. Je n'en ai pas du tout besoin. Ce sera ton souvenir de la journée. Essaie d'être un peu moins crédule à partir de maintenant. Et ne laisse pas des vauriens comme Thomas t'impliquer dans leurs sales affaires.";
			link.l1 = "Eh bien, tu me donnes une tache noire, Capitaine Callow ?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok2";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabePlan_TommiMertv_Platok2":
			dialog.text = "Eh bien, aucun de nous n'est pirate, n'est-ce pas, "+pchar.name+"? Que cela serve de rappel. Prends soin de toi, l'Archipel a besoin d'hommes comme toi. "+GetSexPhrase("Peut-être devrais-je te conseiller de rejoindre la Marine et d'écrire une recommandation au Colonel Doyley...","")+"";
			link.l1 = "Je regrette de ne pouvoir accepter votre offre, Capitaine.";
			if (startHeroType == 3)
			{
				link.l1 = "Hum. Je vais y réfléchir. Sérieusement.";
			}
			if (startHeroType == 4)
			{
				link.l1 = "Adieu, monsieur.";
				link.l1.go = "exit";
				AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
				break;
			}
			link.l1.go = "BM_GabePlan_TommiMertv_Platok3";
		break;
		
		case "BM_GabePlan_TommiMertv_Platok3":
			dialog.text = "Comme tu veux. Eh bien, adieu, "+GetSexPhrase("Monsieur.","mademoiselle")+" "+pchar.lastname+"  Vous méritez de porter ce qui reste des Ironsides. Adieu. ";
			link.l1 = "Adieu, monsieur.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict":
			dialog.text = "Je n'aime pas ton ton, "+GetSexPhrase("monsieur","mademoiselle")+". Quel est ton point?";
			link.l1 = "Vous avez délibérément temporisé, rassemblant vos 'meilleurs hommes'. Pour quoi faire ? Pour appréhender un seul homme ? Vous auriez dû prendre quelques soldats patrouillant la ville et venir à mon secours immédiatement !";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict2";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict2":
			dialog.text = "Apporter de la chair à canon ?! Tom n'était pas juste un garde de ville comme eux. Il avait une formation et une expérience complètement différentes - c'est un foutu Ironclad, tout comme moi ! Comment ne le réalises-tu pas ?";
			link.l1 = "Oh, au contraire, je le réalise bien. C'est pourquoi toi et moi étions ici - pour croiser le fer avec Tom, permettant aux gars de le capturer vivant. En plus, tu es aussi de la compagnie Ironclad. La même compagnie même. Avais-tu si peur de l'affronter en personne ?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict3";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict3":
			dialog.text = "Comment osez-vous m'accuser de lachete, jeune "+GetSexPhrase("homme","mademoiselle")+" ! Demandez à n'importe qui, et ils vous diront en détail quels exploits j'ai accomplis pour cette ville.";
			link.l1 = "Je n'ai pas encore fini. Je commence à me demander si ces 'exploits' ont été réalisés de tes propres mains. Tu voulais que Tom et moi nous entre-tuyions afin que tu puisses prendre toute la gloire. Tu as déjà fait cela, n'est-ce pas ?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict4";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict4":
			dialog.text = "J'en ai assez de tes accusations, "+GetSexPhrase("Monsieur.","mademoiselle")+" "+pchar.lastname+"Tu veux du conflit ? Tu l'auras. Tout de suite.";
			link.l1 = "La vérité fait mal, n'est-ce pas, Gabe ?";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Conflict = true;
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_1":
			dialog.text = "";
			link.l1 = "Gabe ! Cela fait si longtemps, tant d'hivers moroses ! Et regarde-toi - tu as toujours ce même air suffisant, maudit sois-tu !";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_2":
			dialog.text = "Thomas ! Je devrais être ravi, car aujourd'hui je vais enfin terminer de mes propres mains ce que notre système de justice n'a pas réussi à faire pendant des années. Et puisque je suis de bonne humeur, je te permets de déposer les armes et de nous suivre. Tu pourrais même être renvoyé aux travaux forcés. Dans ce cas, je t'y conduirai personnellement.";
			link.l1 = "Heh, fais-moi donc! Tu penses qu'une paire de gars à côté de toi va m'arrêter!!!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_3";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_3":
			dialog.text = "Qui dit qu'ils sont les seuls avec moi ? Je parle de la personne debout à côté de toi en ce moment.";
			link.l1 = "Quoi ?";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_4";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_4":
			dialog.text = "Thomas, Thomas, Thomas... tu es, comme toujours, seul dans ce monde. J'ai presque pitié de toi !";
			link.l1 = "Satanes de rats ! Bâtards !";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_5";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_5":
			StartInstantDialog("Irons", "BM_GabePlan_GazgovorTommiAndGabe_6", "Quest\BlackMark.c");
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_6":
			dialog.text = "Qu'est-ce que cela signifie ?! Que voulait-il dire par là ?!";
			link.l1 = "Tommy, écoute...";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_7";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_7":
			dialog.text = "C'est exactement ce que je fais ! Dis-moi qu'il ment !";
			link.l1 = "Malheureusement, il a raison. Déposez vos armes. Et personne n'a besoin de mourir aujourd'hui. Je mettrai un bon mot pour vous moi-même afin que vous ne soyez pas pendu. Vous pourrez même revenir à une vie honnête un jour.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_8";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_8":
			dialog.text = "Cela ne vous regarde pas de decider ! Et certainement pas vous ! Qui a besoin d'ennemis avec un commandant comme ça ! Un autre foutu rat.";
			link.l1 = "Allons, Tommy. Il n'y a pas de fuites propres pour les gens comme toi.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_9";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_9":
			dialog.text = " Une place dans votre équipage, sur votre navire serait un début, si seulement vous étiez prêt à défendre vos hommes ! Mais cela n'a plus d'importance. Que le diable vous emporte, vous tous ! Je vais vous éventrer, espèce de petit rat. Et toi, Gabe, j'essaierai de t'emporter avec moi...";
			link.l1 = "Attends, Tommy, non !";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe_Fight");
		break;
		
		case "BM_GabePlan_GabeWin_1":
			dialog.text = "Félicitations, "+GetSexPhrase("jeune homme","jeune demoiselle")+" ! Je suis impressionné que tu aies réussi à faire croire à Thomas que tout se déroulait selon son plan - il avait le flair pour la trahison.";
			link.l1 = "Ah, merci, bien sûr, Capitaine Callow.";
			link.l1.go = "BM_GabePlan_GabeWin_2";
		break;
		
		case "BM_GabePlan_GabeWin_2":
			dialog.text = "Quelque chose vous tracasse, "+GetSexPhrase("Monsieur.","mademoiselle")+" "+pchar.lastname+"?";
			link.l1 = "Tom... il n'était pas seulement en colère que je sois de ton côté. Il y avait un vrai désespoir et de l'incompréhension dans sa voix, comme si...";
			link.l1.go = "BM_GabePlan_GabeWin_3";
		break;
		
		case "BM_GabePlan_GabeWin_3":
			dialog.text = "...comme s'il était la partie lésée ici. C'était à prévoir. Souviens-toi, Charles, un monstre peut ressentir de la douleur. Mais cela ne l'empêche pas d'être un monstre. Beaucoup de criminels sont souvent sincèrement convaincus de leur droiture et de leur innocence.";
			link.l1 = "Je vais essayer de m'en souvenir. Je pense que nous avons terminé ici, n'est-ce pas, Capitaine ?";
			link.l1.go = "BM_GabePlan_GabeWin_4";
		break;
		
		case "BM_GabePlan_GabeWin_4":
			dialog.text = "En général, oui, mais il reste encore une chose à faire pour compléter cette belle journée.";
			link.l1 = "Ah bon ? Qu'est-ce que c'est ?";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_IronsJamaicaJungle2":
			dialog.text = "Vous avez mis le temps. Alors je me suis dit que je ferais un peu de reconnaissance. Quoi qu'il en soit, je pense qu'il vaut mieux leur tendre une embuscade ici plutôt que de jouer les duellistes raffinés sur la plage. J'espère que vous avez pu trouver la maison de Gabe et laisser tout en évidence ?";
			link.l1 = "Bien sûr que je l'ai fait, pour qui me prenez-vous, un idiot ? Je suis en fait votre capitaine, Tommy. Que seriez-vous si vous serviez un idiot ?";
			link.l1.go = "BM_IronsJamaicaJungle3";
		break;
		
		case "BM_IronsJamaicaJungle3":
			dialog.text = "Ha-ha-ha-ha, tu ne croirais pas à quelle fréquence j'ai dû gérer ce genre de conneries dans le service ! Mais dans notre cas, heureusement, ce n'est pas le cas. Très bien, alors. Nous attendons de la compagnie. Prêt ?";
			link.l1 = "Eh bien, à moins que toute la flotte ou la garnison de Port Royal ne se pointe ici, je suis prêt.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CreateGabeInJungle");
		break;
		
		case "BM_GabeJungle1":
			dialog.text = "Thomas ? C'est bien toi après tout...";
			link.l1 = "Bien sûr que c'est vraiment moi, ou tu attendais quelqu'un d'autre, Gabe ? Hé, tu as l'air pâle, comme si tu avais vu un fantôme. Tu es aussi plus gros que tu ne l'étais en Vieille Angleterre.";
			link.l1.go = "BM_GabeJungle2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabeJungle2":
			dialog.text = "Maintenant je suis enfin convaincu que c'est vraiment toi. Impoli comme toujours. Mais ça va, je vais bientôt te clouer le bec pour de bon, salaud.";
			link.l1 = "Ha-ha-ha, maintenant nous y voilà! Tu sais, tu m'as vraiment déçu, Gabe. Encore une fois! Tu aurais clairement dû amener plus d'hommes avec toi rien que pour me gérer seul. Et nous sommes deux! Ou bien c'était tout ce qu'ils pouvaient te donner, lâche?";
			link.l1.go = "BM_GabeJungle3";
		break;
		
		case "BM_GabeJungle3":
			dialog.text = "Assez ! Je ne vois plus l'intérêt de continuer à parler.";
			link.l1 = "D'accord avec toi là-dessus ! "+pchar.name+"À la bataille, Capitaine !";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GabeJungleFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BM_IronsJamaicaJungle4":
			dialog.text = "Eh bien, voilà ! Repose en paix, salopard.";
			link.l1 = "Eh bien, es-tu satisfait, Tommy ? Tu sais, beaucoup de gens ne font qu'empirer après avoir obtenu leur vengeance.";
			link.l1.go = "BM_IronsJamaicaJungle5";
		break;
		
		case "BM_IronsJamaicaJungle5":
			dialog.text = "Ha, as-tu lu ça quelque part ? Je n'ai jamais compris ces mauviettes. Bah ! Suis-je satisfait ? Je suis si heureux que je suis sur le point de me pisser dessus ! Ces salauds étaient à la racine de mes plus grands malheurs !";
			link.l1 = "Je suis heureux pour toi. N'y a-t-il personne d'autre sur qui tu dois te venger ? Dois-je m'attendre à d'autres plaisanteries sur les cartouches en papier de ta part ?";
			link.l1.go = "BM_IronsJamaicaJungle6";
		break;
		
		case "BM_IronsJamaicaJungle6":
			dialog.text = "Calme-toi, Gabe était le dernier. Et pour les blagues - ne t'inquiète pas, il n'y en aura plus, du moins pas en ce qui te concerne.";
			link.l1 = "Devons-nous retourner au navire alors ?";
			link.l1.go = "BM_IronsJamaicaJungle7";
		break;
		
		case "BM_IronsJamaicaJungle7":
			dialog.text = "Nous serions de toute façon de retour à son bord, que j'aie encore quelqu'un à qui me venger ou non. Attends une minute, cependant...";
			link.l1 = "Oh, alors ce n'est pas encore fini...";
			link.l1.go = "BM_IronsJamaicaJungle8";
		break;
		
		case "BM_IronsJamaicaJungle8":
			dialog.text = "En effet, en effet. Il y a quelque chose que je veux te dire. C'est quelque chose que je dis à très peu de gens. Et je ne le dirai pas de nouveau. Si tu te moques de moi, je serai très fâché contre toi.";
			link.l1 = "Je promets de ne pas rire. De toute façon, je trouve tes blagues plus tendues que drôles.";
			link.l1.go = "BM_IronsJamaicaJungle9";
		break;
		
		case "BM_IronsJamaicaJungle9":
			dialog.text = "Bien. Alors. Je suis très reconnaissant que tu aies décidé de m'aider au lieu de faire ce que Jack a fait. Tu es un véritable ami, Capitaine. Merci. Aussi... si tu veux, tu peux emprunter mon fidèle sabre, et mon armure... Ce qu'il en reste, ha-ha !";
			link.l1 = "Eh bien, merci de dire cela. Ce n'est pas tous les jours que l'on entend quelque chose comme ça de la part de ses officiers. Allez, camarade.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_FinalInJungleWithTommy");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Irons_officer":
			dialog.text = "Oui, oui, Capitaine ?";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Alors, Rumba, sur quels os allons-nous danser ce soir ?";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Oui, Ellie ?";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Je suis tout ouïe, capitaine.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = ""+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = "Tommy, j'aimerais te demander quelque chose de très sérieux. Il y a une... une idole en pierre des Peaux-Rouges. Et je vais avoir besoin d'aide. Je ne peux demander cela qu'à mes amis les plus proches, comme toi. Les novices ou ceux en qui je n'ai pas encore trop confiance ne conviennent pas.";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tommy, arrête de compter les mouettes. As-tu fait le décompte de toute la cargaison ? Donne-moi un rapport complet avec des prévisions.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Tommy, à partir d'aujourd'hui, j'ai besoin que tu achètes certaines marchandises dans les ports.";
				Link.l12.go = "QMASTER_2";
				
				if (startHeroType == 4)
				{
					Link.l11 = "Tommy, pourrais-tu faire un rapport complet sur le navire, s'il te plaît?";
					Link.l12 = "Tommy, je commence à être bien las. Pourrais-tu faire des provisions de certains biens à chaque port ?";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "Prepare-moi un rapport sur l'état du navire et tout ce qui s'y trouve, Tommy.";
					Link.l12 = "Pourrais-tu faire le plein de certaines marchandises lors de nos escales au port ?";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "Compte tout ce que j'ai sur le navire et fais un rapport sur son etat general.";
					Link.l12 = "J'ai besoin que tu achètes ces marchandises lors de nos escales à chaque port.";
				}
			}
			//////
			Link.l1 = "Ecoutez attentivement mon ordre !";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Quelqu'un, c'est sûr. Mais pour l'instant, écoute mes ordres.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Ecoute mon ordre... Tommy. ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "C'est bien, car j'ai un nouvel ordre pour toi, Tommy.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Ecoute mon ordre, Tom.";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "Rien, Tommy. Repos.";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Nous verrons comment ça se passe, Tommy.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Non, Tom, rien.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Non, rien.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Rien, tout va bien.";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Je n'ai même pas encore commencé l'inventaire. Tu devrais être reconnaissant que je compte nos profits et pertes, sans parler de marchander avec ces marchands avides. L'inventaire, ce n'est pas mon affaire, je n'ai jamais eu à le faire dans l'armée, et je ne vais pas commencer maintenant.";
			Link.l1 = "Ce n'est pas l'armée, Tommy. Mais d'accord, je comprends, je ne te forcerai pas.";
			if (startHeroType == 4)
			{
				dialog.Text = "Je ne suis pas un scribe, Ellie. J'ai connu un gars, Daniel Crimson, qui prétendait toujours être scribe, mais il avait à peine vu le champ de bataille. Pourtant, cet homme était une bête au combat. Ce n'est pas mon cas, et je ne mentirai pas à ce sujet. L'inventaire, ce n'est tout simplement pas mon truc. Je fais déjà nos comptes pour te faire plaisir. N'insiste pas.";
				Link.l1 = "D'accord, Tommy, je ne le ferai pas.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Ecoutez, je ne suis pas un scribe. Personne n'a jamais exigé cela de simples soldats comme moi, même dans l'armée. Ne changeons pas cette règle.";
				Link.l1 = "D'accord, n'en parlons plus.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = " La seule chose que je peux compter, c'est combien de nos ennemis j'ai abattus, ha-ha-ha. Et même là, je perdrai le compte. Je suis un simple soldat, tu sais. Qui diable sait quelque chose sur le navire - j'ai été un terrien la plupart de ma vie.";
				Link.l1 = "On dirait que je vais devoir le faire moi-même.";
			}
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "Pour qui me prends-tu, un quartier-maître de bas étage ? Nous n'avions que du mépris pour ces lâches sans couilles restés au pays. Je ne suis peut-être pas de la noblesse, mais j'ai encore ma fierté.";
			link.l1 = "D'accord, d'accord, si tu ne veux pas, alors tu ne veux pas.";
			link.l1.go = "exit";
			if (startHeroType == 4)
			{
				dialog.Text = "Écoute, j'étais un simple et honnête soldat, pas un officier d'approvisionnement, ma fille. Je n'en sais pas beaucoup à ce sujet et je ne veux pas commencer à apprendre. C'est comme te demander de monter et démonter un mousquet dans les délais.";
				Link.l1 = "Eh bien, je pourrais nommer par coeur chaque partie des agrès fixes et courants de ce navire. Mais comme tu veux, Tom. L'affaire est close.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Non, je ne pouvais pas. Peut-être avez-vous oublié ou vous ne le savez pas du tout, alors je vais expliquer. Pour vous, ce serait une tâche de routine, mais dans notre armée, nous ne traitons pas très bien les services de ravitaillement et de l'arrière. Ne me comptez pas parmi eux, je vous prie.";
				Link.l1 = "Ha-ha, bien, bien.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Écoute, je te respecte, bien sûr, mais je ne vais pas me faire violence et faire quelque chose que je ne peux pas faire et que je ne supporte pas. J'ai à peine appris à compter à l'époque, et tu veux que je sois un véritable fournisseur. D'ailleurs, nous ne les aimions pas - ils économisent sur les munitions, l'eau, la nourriture et sa fraîcheur.";
				Link.l1 = "D'accord, oublions cela.";
			}
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("Oh, un ordre, hein ? Vous aimez la routine et toutes ces choses de l'armée, n'est-ce pas ? Je préférerais que vous me disiez simplement ce qu'il faut faire.","Vous êtes comme un sergent ou quelque chose comme ça. Ça ne vous va pas - vous êtes trop belle pour ça. Vous n'auriez pas survécu un jour dans l'armée. Mais je vous écoute.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Apparemment, tu es vraiment un grand fan des uniformes, des exercices et tout ça. Mais bon, continue.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Lequel ?";
			}
			
            Link.l1 = ""+GetSexPhrase("Ne va nulle part et ne fais rien - observe simplement, compris ? Je te connais.","Restez là où vous êtes, vous me comprenez ?")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Reste ici, ne va nulle part, et ne touche à rien.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Reste ici et ne laisse passer personne.";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("Suis-moi et ne te laisse distraire par rien - les femmes égarées ou les vieux camarades de guerre surgissant soudainement inclus.","Reste près, d'accord ? J'aimerais avoir mon dos couvert.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Suis-moi. Je vois que tu es perdu dans tes pensées.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Suivez-moi, sinon vous vous êtes arrêté pour une raison quelconque.";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "J'ai besoin que tu tires sur quelque chose de différent cette fois.";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "J'ai besoin que tu tires des munitions différentes dans le prochain combat.";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "Tu utiliseras des munitions differentes dans la prochaine bataille.";
					}
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Change le type de munitions pour ton mousquet.";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "Changez votre arme prioritaire pour le combat.";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "Je voudrais que vous gardiez une certaine distance entre vous et vos ennemis.";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "Je voudrais que tu gardes une certaine distance de l'ennemi, Tommy.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "Garde une certaine distance entre toi et l'ennemi, Tommy.";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("Quel genre de projectiles ? J'espère que tu as soigneusement fabriqué chacun d'eux, car qui sait où ils vont atterrir, héhé.","Je tirerai sur n'importe quoi pour vous. Quoi que ce soit, mais jamais à blanc, héhé. ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Je sens que quelque chose d'intéressant se prépare ! D'accord, quel genre ?";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Se battre à nouveau... D'accord, quel genre ?";
			}
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

		case "SetMusketBullets":
			Dialog.Text = "Sélectionnez le type de munitions :";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Au début du combat, vous utiliserez : ";
			Link.l1 = "Lame";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Fusil";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = ""+GetSexPhrase("  Même si tu te fais tabasser là-bas, hehe ? Compris, je vais juste regarder. ","Essayer de me transformer en garde ? Et si vous vous faisiez tabasser ou quelque chose ?")+"";
            Link.l1 = ""+GetSexPhrase("Hé, fais attention ! On trouvera une solution si ça en arrive là.","Eh bien, tu ne vas pas te contenter de regarder, n'est-ce pas ? Si tu penses que ton capitaine est aussi merveilleux que tu le dis, tu ferais bien de faire quelque chose à ce sujet.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "  Même pour viser la tête ? D'accord, d'accord, ne me regarde pas comme ça, je comprends.  ";
				Link.l1 = "J'espère que oui.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "N'aie pas peur, personne ne passera.";
				Link.l1 = "Si tu ne manques à personne, bien sûr. Mais bien.";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("Très drôle. Mais je comprends ton point.","Oh, ne t'inquiète pas, ton dos est toujours sous mon oeil vigilant, hehe.")+"";
            Link.l1 = ""+GetSexPhrase("Bon.","Dieu, tu es insupportable, Tom.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Eh bien, j'essaie de me souvenir de quelque chose de très important. Et puis je réalise que je ne sais même pas ce que c'est, puisque j'ai perdu la mémoire à l'époque, donc rien n'en sortira. D'accord, allons-y.";
				Link.l1 = "Spirituel, je dois dire.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Eh bien, je suis là parce que vous m'avez vous-même ordonné de le faire plus tôt. J'arrive, j'arrive.";
				Link.l1 = "D'accord, d'accord.";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("Quelle sorte de distance ? N'oubliez pas qu'au-delà de vingt yards, je ne pourrai pas viser avec précision. Sauf, bien sûr, si vous n'avez pas besoin que je touche réellement quelque chose, hehe.","Comme si j'avais envie de m'approcher d'hommes puants après avoir été près de toi. Alors, quelle est la distance ? Mais souviens-toi, je ne peux vraiment viser mon tir au-delà de vingt yards, personne ne le peut.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "D'accord, quelle distance ? Mais permettez-moi de vous rappeler que je ne pourrai pas tirer avec précision et lentement à plus de vingt mètres dans le feu de l'action.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "D'accord. Quoi ? Souviens-toi que plus loin que... eh bien, nous ne sommes plus des enfants, toi et moi le savons.";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("Tu ne devrais pas tenter l'humour.","Tu as encore beaucoup à apprendre de moi sur l'humour, ma fille. Mais tu fais des progrès!")+"";
				link.l1 = ""+GetSexPhrase("That's odd; I've always been told the opposite.","Very funny, Tommy.")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Pas ta pire blague. Peut-être qu'un jour tu cesseras même d'être un grincheux, heh-heh.";
					Link.l1 = "Eh bien.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Ha-ha-ha, bonne blague.";
					Link.l1 = "En fait, je viens de... d'accord.";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Eh bien, alors je resterai immobile et tiendrai ma position. Si tu les combats de trop loin, c'est ton cul qui est en jeu, hehe.";
				link.l1 = "Don't be sarcastic; holding your ground is exactly what I want you to do from now.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Heh, vous auriez pu simplement me dire de tenir la ligne, et ne pas parler de distances et de chiffres.";
					Link.l1 = "Eh bien, l'essentiel est que tu m'as compris.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Compris, je tiendrai la ligne ici. Puis amenez-les plus près de moi pour que je puisse tirer.";
					Link.l1 = "Certainement.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Ecoute, je sais que tu voudrais que chaque tir que je fais soit comme celui au phare, mais ça ne va pas arriver. C'était une bonne position là-bas. Calme et stable. Tu ne peux pas reproduire ça en pleine bataille.";
				link.l1 = "Hmm.  Alors, garde vingt yards de distance.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Je sais que tu aimerais ça, tous les gars aimeraient ça, mais comme cette fois-là, au phare, ça ne marchera plus. J'aurai besoin d'un bon argument, et que personne ne m'approche, sinon mes nerfs lâcheront.";
					Link.l1 = "Hm-m, d'accord.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "J'ai certainement aiguisé mes compétences depuis, mais l'impossible restera impossible - dans la chaleur de la bataille, je ne pourrais jamais répéter ce tir depuis le phare. Même avec un mousquet à rouet.";
					Link.l1 = "Et l'impossible est possible, Tommy. Mais d'accord, non c'est non.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("Très bien. Je maintiendrai exactement cette distance, mais si nous nous battons à l'intérieur d'une taverne ou d'une caverne, je sortirai pour la garder, héhé.","Je vais essayer. Mais les ponts et les espaces confinés peuvent dicter leurs propres conditions.");
			link.l1 = ""+GetSexPhrase("Pas drôle, Tommy. Agis selon la situation, mais pas de blagues ou de tes stupides farces.","Je sais cela, Thomas, je ne suis pas idiot.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Je vais essayer de m'en souvenir.";
				Link.l1 = "D'accord, je compte sur toi.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Oui, capitaine.";
				Link.l1 = "Repos, Tommy.";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "Aider à quoi, le voler ? Mais pourquoi ? Je suis flatté, bien sûr, mais vous auriez pu tout dire il y a longtemps. Allez-y, crachez.";
			link.l1 = "Surveille ton langage, hein? Eh bien, bon sang - cela m'est égal comment tu t'exprimes, tant que tu es de mon côté. Alors, cet idole. Grâce à elle, tu peux... te rendre magiquement ailleurs. Ne me regarde pas comme ça - je sais comment ça sonne. Mais j'ai déjà traversé ça et j'ai tout vu de mes propres yeux. C'est... sûr si tu bois un élixir.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Je vois que tu as déjà bu quelques verres. Quoique non, tu sembles sobre. Et on dit de moi que je dis toujours des bêtises...";
			link.l1 = "Viens-tu avec moi ou pas ? L'idole est censée nous emmener à une ancienne cité maya, et qui sait ce qui nous y attend ? Tu es de ceux sur qui je crois pouvoir compter en un moment difficile. Et maintenant, un tel moment vient juste d'arriver.";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "J'ai un mauvais pressentiment à propos de tout ça. Si tu n'étais pas mon capitaine, je dirais que tu devrais être dans un asile de fous. Ensuite tu me diras que Dieu existe.";
			link.l1 = "Il le fait, Tommy. Et, comme je l'ai découvert à ma grande surprise dans cet Archipel, pas seulement le nôtre. Tu pourrais voir toi-même toutes les diableries qui se passent ici. Et tu as probablement remarqué l'influence des breloques bénies ou maudites.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Le diable existe aussi chez nous. Et il a toujours eu une explication normale. Désolé, capitaine, mais je ne danserai pas autour des idoles de pierre avec vous. Tirer sur les ennemis - à votre service. J'ai peut-être perdu la mémoire, mais je n'ai pas perdu la raison. Du moins, je le pense.";
			link.l1 = "Eh bien, je ne peux pas te forcer. Alors... comme tu veux, Tommy.";
			link.l1.go = "tieyasal_5";
			link.l2 = "Je doute que tu aies les tripes de leur tirer dessus, toi l'audacieux, si tu as peur de t'approcher de l'idole.";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "Eh bien-bien, ne fais pas la moue. D'accord, si tu reviens après avoir dansé autour de cette idole, alors j'y réfléchirai la prochaine fois.";
			link.l1 = "Il se peut qu'il n'y ait pas de prochaine fois. Retourne au navire, Tom.";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "Je n'ai pas peur, ne te méprends pas. Mais j'ai l'habitude d'écouter mon instinct, il ne m'a jamais trahi au fil des ans. Et maintenant, il me dit que rien de bon ne sortira de cela. Et de toute façon... Bon, tu vas te vexer.";
			link.l1 = "Allez-y et dites-moi.";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Eh bien, si c'est le cas ! J'ai accepté de me battre à tes côtés. Mais que se passe-t-il si, imaginons, ce truc fonctionne vraiment ? Et s'il est maudit ? Je ne vais pas mourir pour qui que ce soit, désolé.";
			link.l1 = "Maintenant que tu as fait tes preuves, Tommy. J'avais besoin des gens les plus loyaux maintenant. Et maintenant, je vois que tu n'es pas l'un d'eux. J'y vais. Et toi... fais ce que tu veux.";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Regarde-le. Il est offensé après tout.";
			link.l1 = "Ferme ta gueule. Si tu nous trouves si dégoûtants, tu n'as pas besoin de revenir sur le navire.";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Ouah ! Tu es sérieux ? Eh bien, peut-être que c'est pour le mieux. Je ne veux pas être avec des rabat-joie qui ne comprennent même pas les blagues. Dans ce cas... adieu, Votre Excellence.";
			link.l1 = "Adieu, Tommy. Et va en enfer.";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			DialogExit();
			RemovePassenger(pchar, npchar);
			DeleteAttribute(npchar, "OfficerImmortal");
			npchar.lifeday = 0;
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
	}
} 