void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
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

		case "OS_Matros_sluh":
			if (!CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe" && sti(pchar.rank) >= 5)
			{
				dialog.text = RandPhraseSimple("Hé, "+GetSexPhrase("l'ami","l'amie")+", t'as pas vu ma botte quelque part ? Un fichu voleur est parti avec pendant que j'étais évanoui sous la table de la taverne.",
									 "Il paraît qu'il y a eu une bagarre à la taverne hier... Bien que qui se battait soit difficile à dire. Mon visage semble intact. Je crois.", "Par tous les diables des profondeurs, j'avais une bourse pleine d'or hier ! Où diable est-elle maintenant ?");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "OS_Matros_sluh";

				SetQuestHeader("OS");
				AddQuestRecord("OS", "1");
				pchar.questTemp.OS_Start = true;
				pchar.questTemp.OS_Tavern_1 = true;
				AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
			}
			else
			{
				switch (rand(2))
				{
					case 0:
						dialog.text = "Hé, "+GetSexPhrase("l'ami","l'amie")+", t'as pas vu ma botte quelque part ? Un fichu voleur est parti avec pendant que j'étais évanoui sous la table de la taverne.";
						link.l1 = "Garde un œil plus vigilant, ou l'autre suivra le même chemin.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 1:
						dialog.text = "Il paraît qu'il y a eu une bagarre à la taverne hier... Bien que qui se battait soit difficile à dire. Mon visage semble intact. Je crois.";
						link.l1 = "Peut-être ont-ils estimé que ton visage avait déjà subi assez de dégâts.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 2:
						dialog.text = "Par tous les diables des profondeurs, j'avais une bourse pleine d'or hier ! Où diable est-elle maintenant ?";
						link.l1 = "Pour un vrai pirate, l'or n'est pas le prix qui importe le plus. La liberté a bien plus de valeur.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
				}
			}
		break;

		case "OS_Matros_again":
			switch (rand(2))
			{
				case 0:
					dialog.text = "Que veux-tu encore ? Tu ne vois pas que mon crâne est sur le point d'exploser ? Dégage.";
					link.l1 = "Peut-être qu'en buvant moins, tu pourrais passer pour un homme respectable plutôt qu'une épave détrempée.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Laisse-moi tranquille... Ma tête est sur le point d'exploser !";
					link.l1 = "Remarquable qu'elle soit encore attachée à tes épaules.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 2:
					dialog.text = "Maudit sois-tu... Laisse-moi en paix, ne vois-tu pas que je ne suis pas d'humeur à converser maintenant !";
					link.l1 = "...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
		break;
		
		case "OS_Matros":
			dialog.text = "Laisse-moi tranquille ! Tu ne vois pas que je suis à bout ? Mes poings me démangent d'en coller une à quelqu'un.";
			link.l1 = "Du calme, camarade. Je veux juste savoir ce qui s’est passé hier dans la taverne.";
			link.l1.go = "OS_Matros_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Matros_2":
			dialog.text = "Caramba ! T’es "+GetSexPhrase("un autre soupirant","une parente")+" de cette serveuse folle ? Qu’est-ce que tu veux, te faire balayer par la tempête ? Tu veux me provoquer en duel ? Ou tirer ta lame sur-le-champ ?";
			if (pchar.sex == "woman")
			{
				link.l1 = "Parente ? Peu probable. Mais on dirait que tu ne la tiens pas en très haute estime, hein ?";
				link.l1.go = "OS_Matros_3_scrit";
			}
			else
			{
				link.l1 = "Soupirant ? Peu probable. La fille semble préférer la quantité à la qualité, n’est-ce pas ?";
				link.l1.go = "OS_Matros_3_scrit";
				link.l2 = "Ses aventures ne m'intéressent pas. Dis-moi simplement ce qui s'est passé, et je te laisse en paix. C’est toi qui l’as poussée à bout, non ?";
				link.l2.go = "OS_Matros_3_fortuna";
			}
		break;

		case "OS_Matros_3_scrit":
			dialog.text = "Cette furie a le discernement d’un marin affamé – elle saute sur le premier venu ! Elle me lançait des œillades toute la soirée et minaudait comme un chat affamé au galion. Mais dès que j’ai voulu accoster un peu trop près – elle a crié si fort que les poissons du port ont plongé !";
			link.l1 = "Peut-être que tu avais trop bu et que tu t’es montré un peu trop insistant ?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "OS_Matros_3_fortuna":
			dialog.text = "Cette furie a le discernement d’un marin affamé – elle saute sur le premier venu ! Elle me lançait des œillades toute la soirée et minaudait comme un chat affamé au galion. Mais dès que j’ai voulu accoster un peu trop près – elle a crié si fort que les poissons du port ont plongé !";
			link.l1 = "Peut-être que tu avais trop bu et que tu t’es montré un peu trop insistant ?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "OS_Matros_4":
			dialog.text = "J'étais peut-être ivre, mais je me souviens clairement de tout ce qui s'est passé. Ce n’est pas moi qui la chassais – c’est elle qui s’accrochait à moi comme un requin sur une carcasse. Elle tournait autour de moi toute la journée !";
			if (pchar.sex == "woman")
			{
				link.l1 = "Et à cause de cette broutille tu veux frapper le premier venu ? Il s’est passé autre chose ce soir-là ?";
			}
			else
			{
				link.l1 = "Tu as dit 'un autre soupirant'. Tu en sais quelque chose sur ses aventures ?";
			}
			link.l1.go = "OS_Matros_5";
		break;

		case "OS_Matros_5":
			dialog.text = "Après que ses cris aient cessé, les gars de mon équipage m'ont dit que j'aurais mieux fait de ne pas jeter l'ancre dans sa crique. Il paraît qu’elle a un prétendant en ville qui est copain avec notre capitaine.";
			link.l1 = "Intéressant. Tu n’as rien remarqué d’autre d’étrange ? Quelqu’un s’est-il approché du comptoir pendant la dispute ?";
			link.l1.go = "OS_Matros_6";
		break;

		case "OS_Matros_6":
			dialog.text = "Par le diable... J’ai la tête qui éclate, et maintenant toi avec tes questions. J’ai rien vu et rien entendu. Tu ferais mieux de me donner quelques pesos au lieu de harceler un vieux loup de mer.";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Tiens, cent pesos. Mais ne te saoule pas encore au point de retomber sous le charme de la serveuse, héhé.";
				link.l1.go = "OS_Matros_7_harizma";
			}
			link.l2 = "Tu t’en passeras. Sinon tu vas encore t’enivrer et courir après la serveuse.";
			link.l2.go = "OS_Matros_7_fortuna";
		break;
		
		case "OS_Matros_7_harizma":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddQuestRecord("OS", "3");
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Matros_7_fortuna":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddQuestRecord("OS", "3");
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Dialog_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Hé, Jack ! Tu as une putain des quais dans tes quartiers ! Ha-ha ! Régale-toi les yeux – quelle jolie petite diablesse ! Je me demande, a-t-elle fouillé tous nos coffres, ou l'avons-nous interrompue au moment le plus intéressant ?";
				link.l1 = "...";
			}
			else
			{
				dialog.text = "Hé, Jack ! Regarde ce qu'on a là – un rat voleur ! Ha-ha ! Regarde-moi ce gredin ! Il a déjà fouillé dans nos coffres de marin, ce chien sournois, hein ?";
				link.l1 = "...";
			}
			link.l1.go = "OS_Dialog_2";
		break;

		case "OS_Dialog_2":
			StartInstantDialog("OS_Jack", "OS_Dialog_3", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Une petite poule audacieuse. S'introduire dans l'antre de Jack Veils – peu auraient le cran. Alors, qu'est-ce qui t'amène ici, ma jolie ? Tu as pensé nous divertir, n'est-ce pas ?";
				link.l1 = "Vous divertir ? Ha ! Vous êtes de sacrés rêveurs, messieurs. Je suis ici pour récupérer ce que vous avez volé. Pensiez-vous honnêtement que votre pathétique petite représentation passerait inaperçue ?";
			}
			else
			{
				dialog.text = "Un ver bien audacieux, en effet. S'introduire dans la maison de Jack Veils n'est pas quelque chose que beaucoup oseraient tenter. Alors, quelle affaire as-tu ici ?";
				link.l1 = "Disons que je récupère des biens volés. Ou pensiez-vous vraiment, messieurs, que votre pitoyable petite mascarade passerait inaperçue ?";
			}
			link.l1.go = "OS_Dialog_4";
		break;

		case "OS_Dialog_4":
			StartInstantDialog("OS_capWolf", "OS_Dialog_5", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_5":
			if (pchar.sex == "woman")
			{
				dialog.text = "Pathétique représentation ?! Que le diable me rôtisse, je vais t'écorcher vive et utiliser ta peau pour les voiles ! Ha-ha ! Quoique, peut-être devrions-nous d'abord... nous amuser un peu avec toi ?";
				link.l1 = "Je vois que vous êtes impatients de rencontrer votre créateur ? Très bien, je ne vous ferai pas attendre – en garde, sales bâtards !";
			}
			else
			{
				dialog.text = "Pitoyable mascarade ? Que le diable m'emporte, je vais t'arracher la peau du dos et m'en servir comme toile de voile ! Assez parlé – ton heure est venue, misérable chien !";
				link.l1 = "Si c'est ainsi que vous le voulez, alors en garde, scélérats !";
			}
			link.l1.go = "OS_Dialog_bitva";
		break;
		
		case "OS_Dialog_bitva":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("OS_Jack");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("OS_capWolf");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "OS_VernuliBochonok");
		break;
		
		case "Zaharia_1":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = ""+sld.name+", où est mon gin ?! Si tu ne l'as pas, je t'enverrai personnellement nourrir les poissons au fond du port !";
			link.l1 = "...";
			link.l1.go = "Zaharia_2";
			CharacterTurnByChr(npchar, sld);
			//locCameraFromToPos(-2.53, 2.00, 1.26, false, 0.03, 0.00, -1.11);
		break;

		case "Zaharia_2":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "...";
			link.l1 = "Je viens de le livrer moi-même"+GetSexPhrase("","e")+". Le voici.";
			link.l1.go = "Zaharia_3";
			CharacterTurnByChr(npchar, pchar);
			TakeItemFromCharacter(pchar, "cask_gin");
			Log_Info("Vous avez remis le tonneau de gin");
		break;

		case "Zaharia_3":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "Heureusement que ma confiance en toi n'était pas mal placée, "+sld.name+". Passe à mes quartiers demain pour tes doublons.";
			link.l1 = "...";
			link.l1.go = "Zaharia_4";
			CharacterTurnByChr(npchar, sld);
		break;

		case "Zaharia_4":
			DialogExit();

			//ChangeShowIntarface();
			LAi_SetStayType(pchar);

			sld = CharacterFromID("OS_Zaharia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.lifeday = 0;
			sld.location = "None";

			DoQuestFunctionDelay("OS_RazgovorTavern", 1.5);
		break;

		case "Tavern_1":
			dialog.text = "Capitaine, à propos de cette plaque...";
			link.l1 = "Quelle plaque ? Ah, celle-là... Je pense pouvoir me passer de tels honneurs. Ne vous donnez pas cette peine.";
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = "Je peux vous offrir quelque chose de bien meilleur ! À partir de ce jour, vous aurez toujours un logement gratuit et des boissons offertes par la maison dans ma taverne ! Une personne de votre trempe mérite certainement autant !";
			link.l1 = "Voilà qui me convient davantage ! De tels privilèges, je peux les apprécier de tout cœur ! À la prochaine, "+npchar.name+".";
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			AddQuestRecord("OS", "5");
			AddQuestUserData("OS", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.OS_Tavern_FreeBuhlo = true;
			ChangeShowIntarface();
			
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			sld.dialog.filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First Time";
			LAi_SetBarmanType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			
			PChar.quest.OS_AttackSea.win_condition.l1 = "location";
			PChar.quest.OS_AttackSea.win_condition.l1.location = "Cuba1";
			PChar.quest.OS_AttackSea.function = "OS_AttackSea";
			
			// вражеский корабль атакует в море
			sld = CharacterFromID("OS_Pirate");
			DeleteAttribute(sld, "AlwaysFriend");
			DeleteAttribute(sld, "ShipEnemyDisable");
			sld.AlwaysEnemy = true;
			LAi_SetImmortal(sld, false);
			
			PChar.quest.TPZ_Potopil.win_condition.l1 = "NPC_Death";
			PChar.quest.TPZ_Potopil.win_condition.l1.character = "OS_Pirate";
			PChar.quest.TPZ_Potopil.function = "OS_Pobeda";
		break;
		
		
		
		
		
		
		
	}
}