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

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;
		
		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase("Va à ta propre voie, "+GetSexPhrase("camarade","lass")+". Elle nous remerciera à la fin, tu sais.","Dégage! Laisse les messieurs passer un bon moment.","Cela ne vous regarde pas, "+GetSexPhrase("étranger","demoiselle")+". Nous allons juste nous amuser, et c'est tout!");
				link.l1 = LinkRandPhrase("Je ne le permettrai pas !","Abandonnez vos plans maléfiques sur-le-champ !","Je ne tolérerai aucune violence!");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("Je l'ai compris, je m'en vais. Désolé de déranger.","Je n'oserai plus vous déranger. Désolé de vous avoir importuné.");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
					dialog.text = LinkRandPhrase("Va à ta propre voie, "+GetSexPhrase("camarade","fillette")+". Elle nous remerciera à la fin, tu sais.","Dégage! Laisse les messieurs passer du bon temps.","Ceci ne vous concerne pas, "+GetSexPhrase("étranger","fillette")+". Nous allons juste nous amuser, et c'est tout!!");
					link.l1 = LinkRandPhrase("Je ne permettrai pas cela !","Abandonne tes mauvais desseins sur-le-champ !","Je ne tolérerai aucune violence !");
					link.l1.go = "Node_Fight";
					link.l2 = RandPhraseSimple("J'ai compris, je pars. Désolé de déranger.","Je n'oserai plus vous déranger. Désolé de vous avoir importuné.");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple("Hey, "+GetSexPhrase("étranger","jeune dame")+", pourquoi cherchez-vous des ennuis? Cette fille est une 'bien connue', individuelle, dans notre colonie. Nous l'avons déjà payée, mais elle vous a remarqué et a décidé de fuir avec notre argent.","Salut, "+GetSexPhrase("compagnon","fillette")+", allez votre propre chemin et ne vous mêlez pas de nos affaires. Nous avons gagné cette fille à un jeu de dés, mais elle était un peu trop rapide, alors elle s'est enfuie, nous la poursuivons depuis une heure dans cette jungle.");
					link.l1 = "Je m'en fiche, je ne te laisserai pas lui faire du mal!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Oh, je vois! Et j'ai presque cru en elle! Une telle garce...","Ah, eh bien, c'est une autre affaire alors. Amusez-vous bien, les gars!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{	
					dialog.text = "Va à ton propre chemin, "+GetSexPhrase("bon homme","jeune dame")+". Nous nous débrouillerons sans vous.";
					link.l1 = "Je ne tolérerai aucune violence!";
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple("Eh, "+GetSexPhrase("étranger","jeune dame")+", pourquoi cherchez-vous des ennuis ? Cette fille est une 'personne connue' dans notre établissement. Nous l'avons déjà payée, mais elle vous a remarqué et a décidé de fuir avec notre argent.","Hey, "+GetSexPhrase("camarade","lass")+", va-t'en et ne te mêle pas de nos affaires. Nous avons gagné cette demoiselle dans un jeu de dés, mais elle a été un peu trop rapide pour s'échapper, nous la poursuivons depuis une heure.");
					link.l1 = "Je m'en fiche - Je ne te laisserai pas lui faire du mal!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Oh, je vois! Et j'ai presque cru en elle! Quelle garce...","Eh bien, c'est une autre affaire alors. Amusez-vous bien, les gars !");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Eh bien, vous avez certainement choisi le bon moment pour une promenade...","Alors, tu as décidé d'être un héros?")+"Traite avec h"+GetSexPhrase("suis","hein")+", les gars !","Vous "+GetSexPhrase("vermine","ordure")+"! Tu oses te mettre en travers de notre chemin?! Coupe h"+GetSexPhrase("suis","hein")+"!");
			link.l1 = "J'ai vu des gens plus menaçants !";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = "Vous devriez savoir qu'elle nous a coûté pas mal! Et si vous êtes si noble, vous pouvez la prendre pour "+sti(pchar.GenQuest.EncGirl.price)+" pesos."+GetSexPhrase(" Tu passeras un bon moment avec elle, he-he...","")+"";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple("Voici votre argent. Je l'emporte avec moi.","Arrête de sourire comme ça. Je prends la fille avec moi. Voici ton argent.");
				link.l1.go = "Node_4";
			}	
			link.l2 = LinkRandPhrase("Alors, c'est de l'argent que tu veux ? Que dirais-tu d'un acier froid ?","C'est censé être drôle, regarde la fille, espèce d'imbécile ! Elle a peur !","A qui essayes-tu de duper, toi, le dégénéré!");
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": // бандюки уходят, девица остаётся - ГГ ее выкупил у бандюков
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price))); 
			ChangeCharacterComplexReputation(pchar,"nobility", 7);
			//pchar.quest.LandEnc_RapersBadExit.over = "yes";
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = "Pourquoi la crois-tu en premier lieu? Quelle violence? Elle a fui la maison, et nous avons été envoyés par notre patron pour la retrouver.";
			link.l1 = RandPhraseSimple("Eh bien, c'est une autre histoire, alors. Vas-y, poursuis ton fugitif.","Oh, je vois. Et bien, continue de la poursuivre alors... et j'ai des affaires à faire.");
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple("Raconte ces contes de fées à tes petits-fils, si tu vis assez longtemps pour les avoir!","A qui essayes-tu de faire croire ça, espèce de salaud?!");
			link.l2.go = "Node_6";
			link.l3 = "Je la ramènerai chez elle moi-même, pour éviter quelque chose de mauvais. Qui sont ses parents?";
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = "Tu veux mourir ? C'est ton choix...";
			link.l1 = "Regarde qui parle.";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = hrand(2);
			else	i = hrand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = "is a store owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a store owner";
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = "serves in the port office";
					pchar.GenQuest.EncGirl.FatherGen = "who serves in the port office";
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = "serves as the prison's commandant";
					pchar.GenQuest.EncGirl.FatherGen = "of a prison's commandant";
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = "is a shipyard owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a shipyard owner";
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dialog.text = "Son père "+pchar.GenQuest.EncGirl.FatherNom+", dans la colonie de "+XI_ConvertString("Colonie"+pchar.GenQuest.EncGirl.city)+". Mais s'il vous plaît, ne nous laissez pas tomber, car il n'est pas quelqu'un avec qui il faut plaisanter, il nous écorchera tous vifs...";
			link.l1 = "Ne t'inquiète pas. Je la lui livrerai.";
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = "Et donc nous nous rencontrons à nouveau. Où est votre compagne? Oh, en fait, je n'ai pas besoin d'elle, si vous êtes ici.";
			link.l1 = "Messieurs, je pense vraiment que vous avez déjà reçu assez d'argent pour laisser la demoiselle tranquille.";
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(hrand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(hrand(4))
			{
				case 0:
					sTemp = "a leg";
				break;
				case 1:
					sTemp = "an arm";
				break;
				case 2:
					sTemp = "an ear";
				break;
				case 3:
					sTemp = "a nose";
				break;
				case 4:
					sTemp = "an eye";
				break;
			}
			dialog.text = "Qu'est-ce que votre argent comparé aux trésors de "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_GEN)+"? "+"Il était si avare qu'il ne voulait pas marier sa propre fille parce qu'il voulait éviter des dépenses supplémentaires...\nMais il a notre part dans ses coffres ! "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.PirateName2,NAME_NOM)+" a perdu lors de l'abordage "+sTemp+"! Alors qu'avez-vous à la place ? "+"Pitoyable poignée d'argent ? "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_NOM)+" a toujours pris tout le butin pour sa cachette. Mais maintenant, nous ne renoncerons pas! Montrez-nous où sont ses coffres!";
			link.l1 = "Eh bien, je n'ai certainement pas postulé pour garder les trésors de votre capitaine, mais je ne peux pas vous montrer l'endroit... Parce que je ne sais pas où se trouve cet endroit.";
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = "Tu mens!!! Je peux sentir l'odeur de l'or qui sort de cette grotte! Montre-moi l'endroit si tu ne veux pas mourir!";
			link.l1 = "Je vois que mes mots n'ont pas réussi à vous convaincre. Peut-être, mon épée sera plus expressive ?";
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = "Vous "+GetSexPhrase("chien","ordure")+"! Sors de mon chemin !";
			link.l1 = "Argh!";
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = "Bonjour, bon "+GetSexPhrase("homme","demoiselle")+". Nous avons des plaintes à votre sujet.";
			link.l1 = "Des plaintes de qui? De cette pute?";
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = "Garde ta langue, d'accord? Je ne te permettrai pas d'insulter ma soeur! D'abord tu l'as molestée dans la jungle, puis tu l'as amenée ici "+GetSexPhrase("pour plus d'indécence","et m'a volé")+".";
			link.l1 = "Hey mon pote, dois-je vraiment écouter tout ça ?";
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = "Non. Une somme modeste de seulement "+sti(pchar.GenQuest.EncGirl.BerglarSum)+" pesos vous sauveront de tous les ennuis.";
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = "Eh bien, les nobles actions sont sûrement un peu coûteuses ces jours-ci. D'accord, prenez-le...";
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = "Je pense qu'il serait moins cher de faire un trou dans ton ventre pour que tu ne te mettes pas en travers de ma route vers la sortie.";
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = "Non. Mais tu vas aussi vider tes poches, sinon je vais te poignarder!";
				link.l1 = "D'accord, prends-le, espèce de coquin ! Mais tu ne t'en tireras pas comme ça...";
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = "Je pense qu'il serait plus facile de faire un trou dans ton ventre pour que tu ne te tiennes pas sur mon chemin vers la sortie.";
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = "Très bien. Bon débarras.";
			link.l1 = "Bonne chance.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = "Bien sûr que non, bien sûr... Eh bien, au revoir à toi, "+GetSexPhrase("camarade","demoiselle")+"."+GetSexPhrase(" Et garde à l'esprit, tu n'es pas si beau que n'importe quelle fille serait tombée pour toi l'instant où elle t'a vu. Ce serait ma leçon pour toi.","")+"";
			link.l1 = ""+GetSexPhrase("C'est sûr et certain !..","Dégage déjà !")+"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = "Tu as l'air "+GetSexPhrase("un homme si noble","une dame si bien élevée")+", pourquoi ce langage grossier?";
			link.l1 = "Cela me convient le mieux...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = "Eh bien, tu l'as demandé ! Devrions-nous te chatouiller h"+GetSexPhrase("je suis","hein")+" avec de l'acier, les garçons?";
			Link.l1 = "Prie avant de mourir !";
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = "Alors, tu veux te joindre à nous ou quoi ? "+GetSexPhrase("Dégage, il n'y en a pas assez pour nous tous","Dégage pendant que tu le peux, une donzelle nous suffit")+"!";
			Link.l1 = "Eh bien, je ne vous dérangerai pas alors.";
			Link.l1.go = "Exit_NoFight";
			Link.l2 = "Je ne permettrai aucune violence !";
			Link.l2.go = "Node_2";
		break;				
	}
}
