// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int DeceptionChance  = 0;
	int DeceptionPenalty  = 0;
	if(CheckAttribute(pchar,"StealtDeceptionPenalty")) DeceptionPenalty = sti(pchar.StealtDeceptionPenalty);
	
	DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/110);
	if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE) 
	{
		DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/310);
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
	{
		DeceptionChance = 100;
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(DeceptionChance > 90) DeceptionChance = 90;
	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <-- */
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				// заглушка на пирата
				if (sti(pchar.nation) == PIRATE)
				{
    				dialog.text = RandPhraseSimple("Des pirates en ville?! Je n'y crois pas... Saisissez "+GetSexPhrase("lui","elle")+"!!","C'est un pirate ! Saisissez "+GetSexPhrase("lui","elle")+"!!!");
					link.l1 = RandPhraseSimple("Je suis un pirate et alors ?","Heh, tu peux essayer...");
					link.l1.go = "fight"; 
					break;
				}
				else
				{
					if (DeceptionChance > (10+rand(150)+rand(150)))
					{
						dialog.text = RandPhraseSimple("Qui êtes-vous et que faites-vous ici?","Arretez-vous là! Qui etes-vous et de quel droit essayez-vous d'entrer dans la ville?");
						link.l2 = "J'ai jeté l'ancre près de "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" sous le drapeau de "+NationNameGenitive(sti(npchar.nation))+". Qu'est-ce que tu ne comprends pas ? (Probabilité de tromperie "+DeceptionChance+"%%)";
						link.l1.go = "NotPegYou";
					}
					else
					{
						dialog.text = RandPhraseSimple("Un espion ! Rends ton arme et suis-moi !","Un agent ennemi ! Saisissez "+GetSexPhrase("lui","elle")+"!");
						link.l1 = RandPhraseSimple("Tais-toi, mauviette!","Va te faire foutre !");
						link.l1.go = "fight"; 
					}
				}
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					// грамота Винсенто
					if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
					{
						dialog.text = RandPhraseSimple("Qui êtes-vous et que faites-vous ici?","Arrêtez-vous là ! Qui êtes-vous, et par quel droit essayez-vous d'entrer en ville ?");
						link.l1 = "Regardez ce papier, soldat. Je suis ici avec la permission de l'Inquisiteur, Père Vincento.";
						link.l1.go = "vincento"; 
						break;
					}
					if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
					{
						dialog.text = RandPhraseSimple("Qui êtes-vous et que faites-vous ici?","Arrêtez-vous là ! Qui êtes-vous et quel est votre droit d'essayer d'entrer dans la ville ?");
						link.l1 = "Regarde ce papier, soldat. Je suis ici avec la permission de l'Inquisiteur, Père Vincento.";
						link.l1.go = "vincento"; 
						break;
					}
					if (PChar.location == "Maracaibo_Plantation")
					{
						dialog.text = LinkRandPhrase("Comporte-toi bien et ne dérange pas les esclaves.","Allez, avancez !","Ah, c'est toi. Vas-y, nous avons déjà été informés à ton sujet.");
						link.l1 = "...";
						link.l1.go = "exit";
						break;
					}
					dialog.text = RandPhraseSimple("Qui êtes-vous et que faites-vous ici?","Arrêtez-vous là ! Qui êtes-vous et en vertu de quel droit essayez-vous d'entrer dans la ville ?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Officier, j'ai "+GetRusNameNationLicence(HOLLAND)+", alors je suis ici en toute légalité. Regardez, s'il vous plaît...";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = "Ne voyez-vous pas le drapeau de "+NationNameGenitive(sti(pchar.nation))+"sur le mât de mon navire?! (Probabilité de tromperie "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l2 = "J'ai jeté l'ancre près de "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" sous le drapeau de "+NationNameGenitive(sti(pchar.nation))+". Que ne comprenez-vous pas ? (Probabilité de tromperie "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Des pirates en ville ?! Je n'arrive pas à le croire... Arrêtez-le !","C'est un pirate! Attrapez-le!");
							link.l1 = RandPhraseSimple("Oui, je suis un pirate - et alors?","Heh, attrape-moi si tu peux...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Ne vois-tu pas le drapeau de "+NationNameGenitive(sti(pchar.nation))+" sur mon navire?! (Probabilité de tromperie "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l1 = "J'ai jeté l'ancre près de "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gén")+" sous le drapeau "+NationNameGenitive(sti(pchar.nation))+". Qu'est-ce que tu ne comprends pas? (Probabilité de tromperie "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Oh, capitaine, nous avons passé un si bon moment avec vous en mer! Tant de navires que nous avons coulés ensemble sous votre commandement! Et voici...";
									link.l1 = "Et ici, mon ami, tu peux régaler tes yeux de dames charmantes, tu ne les verras pas en mer.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Capitaine, qu'avons-nous fait pour mériter ça?! Nous ne sommes pas des rats de terre, n'est-ce pas?";
									link.l1 = "Silence, marin! Ton poste est très important et honorable, alors arrête de te plaindre.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "Qu'est-ce qui se passe en mer, capitaine ? Le reverrons-nous un jour ?";
									link.l1 = "Mais bien sûr, marin! Une fois que tu es relevé de ton devoir, tu peux te diriger vers le quai et profiter de la mer autant que tu le souhaites.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Je veux me plaindre, capitaine : chacun de nous manque la mer. Nous en avons tous marre de ce service terrestre !";
									link.l1 = "Je suis fatigué de ces jérémiades! Il y a assez de rhum ici aussi! Sers où le capitaine t'a placé, sinon quelqu'un sera pendu en exemple pour les autres.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Je vais vous le dire en toute confiance, capitaine, le nouveau gouverneur est un preneur de pots-de-vin et un détournement de fonds. Mais ce n'est vraiment pas mon affaire...";
									link.l1 = "Exactement, corsaire. Ton affaire, c'est de rester à ton poste et de maintenir l'ordre. Et pendre le gouverneur à la vergue, c'est mon affaire. Bon travail !";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Merci de ne pas nous avoir oublies, capitaine! Nous vous suivrions a travers le feu et l'eau!";
									link.l1 = "Je connais ton genre, les escrocs ! Tout ce que vous aimez vraiment, c'est l'or. Il y a une fête à la taverne ce soir, les boissons sont pour moi. N'oubliez pas de vous montrer.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Heh, capitaine ! Pensez-y, un corsaire peut-il vraiment être un gardien de l'ordre ?! Cela fait si longtemps que nous n'avons pas été sur le véritable affaire !";
									link.l1 = "Pas de temps pour se détendre, corsaire ! Les armadas ennemies ratisseront les eaux près de nos îles, et nous devons être prêts pour un bain de sang à tout moment.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Capitaine, j'ai entendu dire que la Couronne avait envoyé une autre escadre dans notre direction ?";
									link.l1 = "Bien sûr, corsaire. Tant que nous vivons, il n'y aura pas de paix pour nous. Et même en Enfer, nous combattrons les démons !";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! Sacrebleu, c'était vraiment une sacrée gnôle hier, capitaine! C'est dommage que vous n'y étiez pas.";
									link.l1 = "Ce n'est pas un gros problème, je me rattraperai. Et je ne vous envie pas, les gars.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Je vais vous le dire en toute confiance, capitaine, parce que vous nous avez toujours bien traités, nous avons passé un bon moment avec une très jolie fille hier...";
									link.l1 = "Heh, corsaire, une potence est vraiment ce dont tu as besoin!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Capitaine ! Je vous en prie, libérez-moi de ce devoir maudit ! Je ne peux simplement plus jouer le rôle du gardien de l'ordre.";
									link.l1 = "La garde de nuit sur un navire n'est pas facile non plus. Mon ami, le devoir est le devoir, quoi qu'il soit et où qu'il soit.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("Il y a une affaire importante!","J'ai une affaire avec toi.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
						else
						{ // пираты, не наши
							if (sti(pchar.GenQuest.Piratekill) > 20)
							{
								dialog.text = RandPhraseSimple("Alerte! Un fou armé et malade est ici!","Aux armes, aux armes! Un fou furieux est ici!");
								link.l1 = RandPhraseSimple("Hein? Quoi?","Euh, pourquoi fais-tu cela?");
								link.l1.go = "pirate_fight";
							}
							else
							{
							    /* dialog.text = LinkRandPhrase(RandPhraseSimple("Vous avez affaire à moi, capitaine ?","Je suis ici pour affaires, si vous avez besoin de quelque chose, demandez, ne tardez pas."),RandPhraseSimple("Capitaine, je suis très occupé, alors cherchez d'autres interlocuteurs.","Quelque chose ne va pas, capitaine? Si vous n'avez pas de questions, permettez-moi de passer."),"Passez le chemin, capitaine, je suis pressé.");
							link.l1 = LinkRandPhrase("Désolé, mon ami, je "+GetSexPhrase("s'est perdu","Je suis perdue")+" ","D'accord, vaque à tes affaires.","Non, rien.");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("J'ai quelques questions pour toi.","J'ai une affaire avec toi."),RandPhraseSimple("Je vois que tu es pressé. Une question et tu seras libre.","Je "+GetSexPhrase("voulait","voulait")+"demander quelque chose."),"Tes affaires peuvent attendre. Voilà ce que je veux demander "+GetSexPhrase("voulait","voulait")+".");
							    link.l2.go = "quests";//(перессылка в файл города) */
								
								//Экку Korsar - что-то они больно вежливые для пиратов были...
								dialog.text = RandPhraseSimple("Que voulez-vous ? Passez votre chemin.","Arrête de bloquer la route, recule.");
					            link.l1 = RandPhraseSimple("Tu sais? Ne jappe pas!","Réduisez votre ardeur. Je ne vais pas la refroidir rapidement !");
					            link.l1.go = "exit";
						    	/* link.l2 = LinkRandPhrase(RandPhraseSimple("J'ai quelques questions pour toi.","J'ai une affaire avec toi."),RandPhraseSimple("Je vois que tu es pressé. Une question et tu seras libre.","Je "+GetSexPhrase("voulait","voulait")+"demander quelque chose."),"Tes affaires peuvent attendre. Voici ce que je veux demander "+GetSexPhrase("voulait","voulait")+".");
							link.l2.go = "quests";//(перессылка в файл города) */
							}
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("Juste regarde  "+GetSexPhrase("à ce scélérat! Il a osé montrer son visage","à ce coquin! Elle a osé montrer son visage")+" dans "+XI_ConvertString("Colonie"+npchar.city)+". Seize "+GetSexPhrase("lui","elle")+"!!!","Ha, je vous ai reconnu, "+GetSexPhrase("canaille","coquin")+"! Saisir "+GetSexPhrase("lui","elle")+"!!!");
							link.l1 = RandPhraseSimple("Argh!..","Eh bien, tu l'as demandé...");
							link.l1.go = "fight";
							break;						
						}
					}

					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)	
						{
							dialog.text = "Oh, regarde qui est là ! Dame "+pchar.GenQuest.EncGirl.name+" elle-même nous a honorés de sa présence ! Je me demande comment vous avez osé ? Nous vous cherchions ! Veuillez vous diriger vers le donjon - votre cellule est prête et vous attend. ";
							link.l1 = "Quelles absurdités racontes-tu!? Moi et mon "+GetSexPhrase("chevalier","compagnon")+" se promenaient dans la jungle, cueillant des fleurs. Laissez-moi tranquille ! Où sont les manières de ces martinets ?! Dès qu'ils voient une jolie fille, ils commencent à la harceler ! "+GetSexPhrase("Ma chère, dis à ces imbéciles de se perdre et de laisser une femme honnête tranquille !","Chéri, s'il te plaît, dis-le à ces imbéciles...")+"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)	
						{
							dialog.text = "Oh, voilà que tu es, belle! Ton père a mis toute la garnison debout pour te trouver et te ramener à la maison.";
							link.l1 = "Dégage ! Je sais où je vais et je n'ai pas besoin de ton aide ! Capitaine, dis-leur de me lâcher.";
							link.l1.go = "GirlEnc_2";						
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях
					
					// --> Sinistra Длинные тени старых грехов
					if(CheckAttribute(pchar, "questTemp.Knippel.Soldiers_1"))
					{
						switch(0)
						{
							case 0: 
							dialog.text = "Écoute, Charlie, nous avons de nouvelles recrues au fort. Vert comme de l'herbe... Pourrais-tu passer et leur montrer comment viser?";
							link.l1 = "Si le capitaine Fleetwood et moi ne prenons pas la mer dans les prochains jours - avec plaisir.";
							link.l1.go = "Knippel_Soldiers_1";
							break;
						}
						break;
					}
					
					if(CheckAttribute(pchar, "questTemp.Knippel.Soldiers_2"))
					{
						switch(0)
						{
							case 0: 
							dialog.text = "Charlie, mon quart est presque fini, tu veux boire quelque chose?";
							link.l1 = "Avec plaisir, mon pote ! Laisse-moi juste voir ce que le capitaine veut.";
							link.l1.go = "Knippel_Soldiers_2";
							break;
						}
						break;
					}
					
					if(CheckAttribute(pchar, "questTemp.Knippel.Soldiers_3"))
					{
						switch(0)
						{
							case 0: 
							dialog.text = "Bonne nuit, Charlie ! Tu n'as pas l'air si bien. Tout va bien ?";
							link.l1 = "Ils m'ont réveillé au milieu de la nuit, qu'en pensez-vous ? Impossible de trouver un moment de repos.";
							link.l1.go = "Knippel_Soldiers_3";
							break;
						}
						break;
					}
					// <-- Длинные тени старых грехов

					// --> belamour ночной приключенец
					if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum") && npchar.index == pchar.GenQuest.NightAdventureSolNum)
					{
						dialog.text = "La vie d'un soldat est programmée - monter la garde, patrouiller ... Que voulez-vous, "+GetAddress_Form(NPChar)+"?";
						link.l1 = "Écoutez, c'était avec vous qu'un ivrogne s'est battu ici récemment? Eh bien, bien que, apparemment, oui, avec vous...";
						link.l1.go = "NightAdventure_CitizenHomieSolder";
						break;
					}
					// <-- ночной приключенец
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Votre Excellence, Gouverneur Général ! Comment puis-je servir ?";
							link.l1 = "Je n'ai besoin de rien, merci.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "C'est un grand honneur pour moi, Monsieur le Gouverneur Général ! Comment puis-je vous aider ?";
								link.l1 = "Accomplissez votre service consciencieusement - je ne requiers rien de plus de vous.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Heureux de vous voir, Votre Excellence! Que peut un humble soldat faire pour le gouverneur général de nos colonies?";
								link.l1 = "Personnellement, je n'ai besoin de rien de toi. Continue à servir.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Вице-адмирал на службе нации узнается без мундира
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Vice-Amiral, Votre Excellence! Permettez-moi de rapporter: pendant ma garde...";
							link.l1 = "Calme-toi, soldat, je n'ai pas besoin de ton rapport. Rends-toi à ton officier.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Heureux de vous voir, Vice-Amiral ! Puis-je vous aider avec quelque chose ?";
								link.l1 = "Non, je vérifiais simplement à quel point vous êtes attentif. Je suis content que vous m'ayez reconnu.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Vice-amiral, c'est un honneur pour moi! Que puis-je faire pour vous?";
								link.l1 = "Servir "+NationNameGenitive(sti(npchar.nation))+", soldat! C'est la meilleure chose que tu puisses faire.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Офицер с патентом
					if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Salutations, capitaine ! Si vous avez des instructions pour moi, alors je vous demande pardon : bien que je sois à votre service "+NationNameGenitive(sti(npchar.nation))+", je réponds seulement au commandant et au gouverneur."; 
							link.l1 = "J'ai mes officiers et mon équipage qui répondent à mes directives. Fais ton devoir, soldat.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Capitaine, pouvez-vous me prendre pour servir sur votre navire? Le même service pour "+NationNameGenitive(sti(npchar.nation))+", mais je préfère la mer."; 
								link.l1 = "Vous êtes nécessaire là où vous avez été affecté, alors exécutez votre service avec honneur. Vous fermez les yeux pour une seconde, et ils l'emporteront à la mer.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Oh, vous avez de la chance: vous êtes le capitaine du navire au service de "+NationNameGenitive(sti(npchar.nation))+"... Et je suis coincé ici toute la journée."; 
								link.l1 = "Penses-tu que je suis arrivé aux Caraïbes et que je suis devenu capitaine une semaine plus tard ? C'est toutes des années de dur labeur...";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Ne voyez-vous pas ? Je suis en service. Arrêtez de me déranger.";
							link.l1 = "D'accord, d'accord...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Allez-vous me parler de certaines activités suspectes?";
							link.l1 = "Non, pas du tout, et je suis un capitaine, au fait. Je vois que tu n'écoutes plus? Au revoir.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "C'est une installation militaire, alors ne faites pas trop de bruit ici.";
							link.l1 = "D'accord, je garderai cela à l'esprit.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Un temps si clair, et je suis obligé de rester ici. En ville, il y a au moins des filles, et qu'avons-nous ici? Que des rats partout.";
							link.l1 = ""+GetSexPhrase("Je sympathise, mais il n'y a rien que je puisse faire pour aider - c'est ton devoir après tout.","Hey ! Qu'est-ce qui ne va pas avec moi ? Ne suis-je pas une fille ?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Si vous aimez parler, trouvez quelqu'un d'autre. Je dois maintenir l'ordre ici, et je n'ai pas de temps pour des bavardages bon marché.";
							link.l1 = "Oh, non, je vérifie juste si tu es toujours en vie. Tu te tenais là comme une statue.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Vous pensez probablement que les jours de travail en garnison sont une promenade de sante? Absolument pas! C'est un travail difficile et important. Je me souviens une fois...";
							link.l1 = "Tu me raconteras cette histoire une autre fois. Je suis un peu pressé maintenant.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Faites attention ici, vous êtes dans un fort ! Soyez aussi silencieux qu'une souris !";
							link.l1 = "Comme vous dites, soldat.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Hey! Avez-vous de l'eau, par hasard? Je meurs de soif.";
							link.l1 = "Non, mon ami, sois patient...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "Quelle vie ennuyeuse dans la garnison, il n'y a que des ploucs comme toi! Maintenant, la garnison de la ville doit sûrement connaître des jours meilleurs...";
							link.l1 = "Et vous appelez ça 'être en service' ? De cette façon, vous laisserez sûrement un espion vous échapper !";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("Tu as l'air d'un gars fort, n'est-ce pas? Voudrais-tu t'engager au service de la garnison du fort? Nous avons des casernes spacieuses, deux repas par jour et de l'alcool gratuit.","Oh, jeune dame, vous n'avez aucune idée, combien il est agréable de rencontrer une si gentille demoiselle dans ce trou perdu!")+"";
							link.l1 = ""+GetSexPhrase("C'est certainement tentant, mais je dois encore refuser. Toute cette drill de caserne n'est tout simplement pas pour moi.","Merci pour le compliment, soldat.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Cette maudite chaleur... Je donnerais volontiers la moitié de ma vie pour retourner en Europe.";
							link.l1 = "Ouais, je peux voir que votre santé n'est pas adaptée au climat local.";
							link.l1.go = "exit";
						break;

					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Attendez une minute. Je voulais demander quelque chose "+GetSexPhrase("voulait","voulait")+"...";
					link.l3.go = "quests";//(перессылка в файл города) */				
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Il me semble que c'est une ruse. Parlons avec le commandant, "+GetSexPhrase("camarade","chéri")+", et comprendre tout ça...","Hmm... Quelque chose me dit que vous n'êtes pas qui vous prétendez être... Rendez votre arme "+GetAddress_Form(npchar)+", et suivez-moi pour une enquête plus approfondie!");
			link.l1 = RandPhraseSimple("Va te faire foutre !","Quand deux dimanches viennent en une semaine...");
			link.l1.go = "fight";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Oh, je vois... Tout semble en ordre, tu es libre de partir, "+GetAddress_Form(pchar)+".","Je dois être un peu fatigué d'être en veille... Tout semble aller bien, "+GetAddress_Form(pchar)+", Je suis désolé.");
			link.l1 = "Pas de problème!";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "vincento":
			dialog.text = RandPhraseSimple("Oh, je vois... Tout semble être en ordre, vous êtes libre de partir, "+GetAddress_Form(pchar)+".","Voyons voir maintenant... Eh bien, tout semble en ordre, "+GetAddress_Form(pchar)+", je suis désolé.");
			link.l1 = "Ça t'apprendra !";
			link.l1.go = "exit";
		break;
		
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Juste à y penser ! Quelle insolence ! Venir ici sous le déguisement d'un marchand ! Vos portraits sont affichés dans chaque caserne, espèce de salaud ! Vous ne vous en sortirez pas cette fois-ci ! Saisissez-le !";
				link.l1 = RandPhraseSimple("Arrgh !..","Eh bien, vous l'avez demandé ...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (pchar.location != "LosTeques_town" && findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе 300912
			{
				dialog.text = "Vous êtes venu pour faire du commerce ici ? Puis-je demander comment ? Où est votre navire ? Vous savez, tout cela a l'air très suspect, et je suis obligé de vous détenir jusqu'à ce que nous ayons tout éclairci. Rendez votre arme et suivez-moi !";
				link.l1 = RandPhraseSimple("Va te faire foutre !","Quand deux dimanches viennent en une semaine...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Votre licence doit être révoquée car elle est expirée et n'est donc pas valide. Rendez votre arme et suivez-moi pour une enquête plus approfondie!";
				link.l1 = RandPhraseSimple("Va te faire foutre !","Quand deux dimanches viennent en une semaine...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Tout semble en ordre. Cependant, je dois noter que votre licence expire aujourd'hui. Je vous laisserai passer cette fois, mais vous devrez toujours obtenir une nouvelle licence.";
				link.l1 = "Merci, je m'en procurerai un nouveau dès que possible.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Tout semble correct. Cependant, je dois noter que votre licence expirera bientôt. Elle n'est encore valide que pour "+FindRussianDaysString(iTemp)+". Alors gardez cela à l'esprit, "+GetAddress_Form(npchar)+".";
				link.l1 = "Merci, je m'en procurerai un nouveau dès que possible.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Eh bien, tout semble en ordre. Votre licence est valable pour encore "+FindRussianDaysString(iTemp)+". Vous pouvez passer.","Tout est clair, "+GetAddress_Form(npchar)+". Vous pouvez aller et venir librement en ville, votre licence est valable pour un autre "+FindRussianDaysString(iTemp)+". Désolé de vous déranger.","Tout semble bien, "+GetAddress_Form(npchar)+", je ne te retiens plus ici.");
				link.l1 = RandPhraseSimple("Excellent. Meilleures salutations.","Merci, officier.");
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("Eh, camarade, ne casse rien dans le phare.","Ce phare est un objet de ville très important. Soyez prudent!");
			link.l1 = RandPhraseSimple("D'accord, ne t'inquiète pas.","D'accord, ne t'inquiète pas.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("Ne marchez pas près des canons - c'est une installation militaire!","Les étrangers ne sont pas autorisés près des canons!","Si je te vois traîner près des canons, tu es fini !");
			link.l1 = RandPhraseSimple("Je l'ai eu.","D'accord, j'ai compris.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;

		// --> генератор "A damsel in the jungle"
		case "GirlEnc_1":
			dialog.text = "Et qui êtes-vous, capitaine ? N'êtes-vous pas, par hasard, un complice du voleur le plus notoire de cette colonie ?";
			link.l1 = "Qui as-tu appelé un complice ?! Es-tu frappé par le soleil ou quoi ?! Hé, retire tes pattes de la fille !";
			link.l1.go = "GirlEnc_11";
			link.l2 = "En fait, j'ai "+GetSexPhrase("connu elle","l'ai connue")+" récemment...";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+", nous avons l'ordre de la détenir et de l'emmener au donjon. Et si vous pensez que vous pouvez nous arrêter, vous vous trompez.";
			link.l1 = "Voyons voir, alors...";
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "GirlEnc_12":
			dialog.text = "Oh, vraiment? Dans ce cas, je vous conseillerais de vérifier vos poches. Cette dame est une professionnelle, vous savez";
			link.l1 = "Merci, je ferai cela. Comment ai-je pu me faire si bête...";
			link.l1.go = "GirlEnc_12End";		
		break;		
		
		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "GirlEnc_2":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+", nous avons un ordre de trouver cette dame et de la ramener à son père.";
			link.l1 = "Eh bien, un ordre est un ordre - vas-y, alors.";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "Trop tard pour ça, parce que je parle déjà à son père.";
			link.l2.go = "GirlEnc_21";
		break;
		
		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("JungleGirl", "11");	
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));	
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "GirlEnc_21":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = "Capitaine, nous avons un ordre, et si vous pensez que vous pouvez nous arrêter, vous vous trompez.";
				link.l1 = "Voyons, alors...";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "Heh, "+GetSexPhrase("tu es un homme chanceux","tu es une fille chanceuse")+". Son père a promis une généreuse récompense à celui qui la ramènera chez lui.";
				link.l1 = "Ne désespérez pas - vous avez encore de nombreuses récompenses à venir.";
				link.l1.go = "exit";			 
			}
		break;
		
		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;
		// <-- генератор "A damsel in the jungle"
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomieSolder":
			dialog.text = "Oui, avec moi. Qu'il reste derrière les barreaux, à réfléchir à son comportement. Et si vous êtes venu me menacer pour lui, alors croyez-moi : je peux même atteindre le commandant du fort.";
			link.l1 = "Oui, je ne suis pas venu pour menacer, mais pour vous demander de retirer vos accusations contre lui. Vous voyez, c'est un vieux connaissant à moi, il a juste trop bu, mais pour un ivrogne, vous savez, la mer est à hauteur de genoux ...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_1";
		break;
		
		case "NightAdventure_CitizenHomieSolder_1":
			dialog.text = "C'est-à-dire, il m'a donné un cocard pendant que j'étais en service, et maintenant il devrait être libéré ? Pourquoi cela arriverait-il ?";
			link.l1 = "Que diriez-vous de cinq cents pesos en guise d'excuse pour son comportement?";
			link.l1.go = "NightAdventure_CitizenHomieSolder_2";
		break;
		
		case "NightAdventure_CitizenHomieSolder_2":
			dialog.text = "Pensez-vous cela? Il a fait une insulte à mon honneur, et vous pensez que cela peut être pardonné pour cinq cents pesos? Pensez-vous que mon honneur peut être acheté?";
			link.l1 = "...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_3";
		break;
			
		case "NightAdventure_CitizenHomieSolder_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM")
			{
				DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
				pchar.quest.NightAdventure_SeaExit.over = "yes";
				pchar.quest.NightAdventure_JungleExit.over = "yes";
				SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
				dialog.text = "Non, Capitaine, c'est tout à fait juste. Il l'a mérité. Et je vous demande de ne plus me distraire de mon service.";
				link.l1 = "Eh bien, tu as raison.";
				link.l1.go = "exit";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM")
			{
				dialog.text = "Mille. Et pas un peso de moins.";
				link.l1 = "Non, peut-être que je ne suis pas prêt à payer autant pour un seul coup.";
				link.l1.go = "NightAdventure_CitizenHomieSolder_3NM";
				if (sti(pchar.money) >= 1000)
				{
					link.l2 = "Oh... D'accord, attends. Voici un stylo et du parchemin tout de suite. Écris que tu renonces à toutes les revendications contre mon ami.";
					link.l2.go = "NightAdventure_CitizenHomieSolder_3GM";
				}
			}
		break;
		
		case "NightAdventure_CitizenHomieSolder_3NM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			dialog.text = "Alors je vous demande de ne plus me distraire de mon service.";
			link.l1 = "Je ne le ferai pas.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieSolder_3GM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.GenQuest.NightAdventureToPrisoner = true;
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Voici que tu es là.";
			link.l1 = "Bonne chance pour le travail.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Длинные тени старых грехов
		case "Knippel_Soldiers_1":
			dialog.text = "Et peut-être leur enseigner certains de vos secrets aussi, afin qu'ils ne les emportent pas dans la tombe avec vous?";
			link.l1 = "Heh-heh, euh, non, mon pote, mes secrets sont à moi seul, et quels genres de secrets seraient-ils alors?";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_1");
			pchar.questTemp.Knippel.Soldiers_2 = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Knippel_Soldiers_2":
			dialog.text = "Compris, tu vas encore te défiler, comme toujours.";
			link.l1 = "Eh bien, si le poisson glisse - c'est un mauvais pêcheur. C'est comme avec les boulets de canon - un bon ne vous fait jamais défaut, il suffit de bien viser...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_2");
			pchar.questTemp.Knippel.Soldiers_3 = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Knippel_Soldiers_3":
			dialog.text = "Au moins tu ne te lèves pas toutes les nuits. Et tu passes plus de temps sur le navire qu'à terre. A qui parles-tu ?";
			link.l1 = "Ah, que sais-tu des difficultés du service, mon pote! Ce que c'était dans la Marine Royale!.. Tu ne peux même pas imaginer.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_3");
			LAi_CharacterDisableDialog(npchar);
		break;
		// <-- Длинные тени старых грехов
		
		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
			dialog.text = "Capitaine, je vous demande de ranger vos armes : il est interdit de les dégainer dans notre ville.";
			link.l1 = LinkRandPhrase("D'accord, je vais le ranger...","Déjà fait.","Comme vous dites...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Va te faire foutre !","Je suppose que je vais l'utiliser !","Je le rangerai quand le moment sera venu.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("Eh, quel est le probleme avec tout ce maniement d'armes?! Range-le a cet instant!","Je vous ordonne de ranger votre arme tout de suite!","Salut, "+GetAddress_Form(NPChar)+", arrête de faire peur aux gens! Range ton arme.");
			link.l1 = LinkRandPhrase("D'accord, je vais le ranger...","Déjà fait.","Comme vous dites...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Va te faire foutre !","Je suppose que je vais l'utiliser !","Je le rangerai quand le moment sera venu.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;
	}
}
