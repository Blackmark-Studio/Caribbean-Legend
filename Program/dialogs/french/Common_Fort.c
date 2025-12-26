// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
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
				dialog.text = RandPhraseSimple("Un espion! Rends ton arme et suis-moi!","Un agent ennemi! Saisissez "+GetSexPhrase("lui","elle")+"!");
				link.l1 = RandPhraseSimple("Tais-toi, mauviette!","Va te faire foutre !");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("Qui êtes-vous et que faites-vous ici?","Tenez-vous tranquille ! Qui êtes-vous ? Pour quelle raison essayez-vous d'entrer dans le fort ?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Officier, j'ai "+GetRusNameNationLicence(sti(npchar.nation))+", donc je suis ici en toute légalité. Ici, jetez un coup d'oeil...";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Un pirate est dans le fort ? Capturez-le"+GetSexPhrase("lui","elle")+"!","C'est un pirate, flairant quelque chose dans notre fort ! A la geôle !!!");
							link.l1 = RandPhraseSimple("Oui, je suis un pirate, et alors ?","Heh, attrape-moi si tu peux...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Ne voyez-vous pas le drapeau de "+NationNameGenitive(sti(pchar.nation))+" sur le mât de mon navire?!";
						}
						else //если причалил не в городе
						{
							link.l1 = "J'ai jeté l'ancre près de "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" sous le drapeau de"+NationNameGenitive(sti(pchar.nation))+"! Avez-vous besoin de quelque chose d'autre?";
						}
						// belamour legendary edition вызываюий доверие даёт возможность обмануть стражу
						if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
						{
							Notification_Perk(true, "Trustworthy");
							link.l1.go = "NotPegYou";
						}
						else
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
							{
								notification("Skill Check Failed", SKILL_SNEAK);
								link.l1.go = "PegYou";
							}
							else
							{
								link.l1.go = "NotPegYou";
							}
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Oh, capitaine, nous avons passé de si bons moments avec vous en mer! Tant de navires que nous avons coulé ensemble sous votre commandement! Et voici...";
									link.l1 = "Et ici, mon ami, tu peux régaler tes yeux de dames charmantes, tu ne les verras pas en mer.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Capitaine, qu'avons-nous fait pour mériter cela ?! Nous ne sommes pas des rats terrestres, n'est-ce pas?";
									link.l1 = "Silence, marin! Ton poste est très important et honorable, alors arrête de te plaindre.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "Qu'est-ce qui se passe en mer, capitaine? Le reverrons-nous jamais?";
									link.l1 = "Mais bien sûr, marin! Une fois que vous êtes relevé de votre devoir, vous pouvez vous diriger vers le quai et profiter de la mer autant que vous le souhaitez.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Je veux me plaindre, capitaine: chacun de nous manque la mer. Nous en avons tous totalement marre de ce service terrestre!";
									link.l1 = "Je suis fatigué de ces plaintes ! Vous avez aussi assez de rhum ici ! Servez là où le capitaine vous a placé, sinon quelqu'un sera pendu comme exemple pour les autres.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Je vais vous le dire en toute confiance, capitaine, le nouveau gouverneur est un corrupteur et un détournement de fonds. Mais ça ne me regarde vraiment pas...";
									link.l1 = "Exactement, corsaire. Ton affaire c'est de rester à ton poste et de maintenir l'ordre. Et pendre le gouverneur à la vergue, c'est mon affaire. Bon travail !";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Merci de ne pas nous avoir oubliés, capitaine ! Nous vous suivrions à travers le feu et l'eau !";
									link.l1 = "Je connais ton genre, escrocs ! Tout ce que vous aimez vraiment, c'est l'or. Il y a une fête à la taverne ce soir, les boissons sont pour moi. N'oubliez pas de vous présenter.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Heh, capitaine! Pensez-y, un corsaire peut-il vraiment être un gardien de l'ordre?! Cela fait si longtemps que nous n'avons pas été dans le vrai commerce!";
									link.l1 = "Pas de temps pour se détendre, corsaire! Les armadas ennemies ratissent les eaux près de nos îles, et nous devons être prêts pour un bain de sang à tout moment.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Capitaine, j'ai entendu dire que la Couronne avait envoyé un autre escadron dans notre direction ?";
									link.l1 = "Bien sûr, corsaire. Tant que nous vivrons, il n'y aura pas de paix pour nous. Et même en Enfer nous combattrons les diables!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! Sacrebleu, c'etait vraiment une forte gnole hier, capitaine! C'est dommage que tu n'y etais pas.";
									link.l1 = "Ce n'est pas grave, je me rattraperai. Et je ne vous envie pas, les gars.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Je vais vous le dire en confidence, capitaine, car vous nous avez toujours bien traités, nous avons passé du bon temps avec une vraie belle poulette hier...";
									link.l1 = "Heh, corsaire, un noeud coulant est vraiment ce dont tu as besoin !";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Cap! S'il vous plaît, délivrez-moi de ce devoir maudit! Je ne peux tout simplement plus jouer le rôle de gardien de l'ordre.";
									link.l1 = "La garde de nuit sur un navire n'est pas facile non plus. Mon ami, le devoir est le devoir, quoi qu'il soit et où qu'il soit.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("Il y a une affaire importante !","J'ai une affaire avec toi.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
					}
					
					//Jason --> мини-квест Дефицитный товар
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
					{// Addon 2016-1 Jason пиратская линейка
						string wineCity = "FortFrance";
						if(SandboxMode)
						{
							if(CheckAttribute(pchar,"HeroParam.ToCityId"))
							{
								wineCity = pchar.HeroParam.ToCityId;	
							}
						}
						if(GetCityNameByIsland(LoadedLocation.islandId) ==  wineCity && npchar.location.locator == "protector1")
						{
							dialog.text = "Hey, camarade ! Peux-tu me rendre un petit service ?";
							link.l1 = "Cela dépend de ce qui doit être fait.";
							link.l1.go = "Wine_soldier";
							link.l2 = "Je n'ai pas de temps pour ça.";
							link.l2.go = "exit";
							pchar.questTemp.Wine = "true";
							DelLandQuestMark(npchar);
							break;
						}
						if(StartHeroType == 2)
						{
							if(LoadedLocation.id == "Santiago_fort")
							{
								dialog.text = "Hé, l'ami! Peux-tu me rendre un petit service?";
								link.l1 = "Cela dépend de ce qui doit être fait.";
								link.l1.go = "Wine_soldier";
								link.l2 = "Je n'ai pas de temps pour ça.";
								link.l2.go = "exit";
								pchar.questTemp.Wine = "true";
								DelLandQuestMark(npchar);
								break;
							}
						}
					}
					// <-- мини-квест Дефицитный товар
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Votre Excellence, Gouverneur Général ! Que puis-je vous servir ?";
							link.l1 = "Je n'ai besoin de rien, merci.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "C'est un grand honneur pour moi, M. le Gouverneur Général ! Comment puis-je vous aider ?";
								link.l1 = "Effectuez votre service consciencieusement - je n'exige rien de plus de vous.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Heureux de vous voir, Votre Excellence! Que peut faire un humble soldat pour le gouverneur général de nos colonies?";
								link.l1 = "Personnellement, je n'ai besoin de rien de vous. Continuez à servir.";
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
							link.l1 = "Calmez-vous, soldat, je n'ai pas besoin de votre rapport. Rapportez-vous à votre supérieur.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Heureux de vous voir, Vice-amiral! Puis-je vous aider avec quelque chose?";
								link.l1 = "Non, je vérifiais juste à quel point vous êtes attentif. Je suis content que vous m'ayez reconnu.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Vice-amiral, c'est un honneur pour moi ! Que puis-je faire pour vous ?";
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
							dialog.text = "Salutations, capitaine! Si vous avez des instructions pour moi, alors je vous demande pardon: bien que je sois à votre service "+NationNameGenitive(sti(npchar.nation))+", Je ne réponds qu'au commandant et au gouverneur."; 
							link.l1 = "J'ai mes officiers et mon équipage qui répondent à ma direction. Fais ton devoir, soldat.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Capitaine, pouvez-vous me prendre pour servir sur votre navire? Le même service pour "+NationNameGenitive(sti(npchar.nation))+", mais je préfère la mer."; 
								link.l1 = "Vous êtes nécessaire là où on vous a assigné, alors accomplissez votre service avec honneur. Vous fermez vos yeux pendant une seconde, et ils l'emmèneront à la mer.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Oh, vous avez de la chance: vous êtes le capitaine du navire au service de "+NationNameGenitive(sti(npchar.nation))+"... Et je suis coincé ici toute la journée."; 
								link.l1 = "Pensez-vous que je suis arrivé dans les Caraïbes et suis devenu capitaine une semaine plus tard? C'est toutes des années de dur labeur...";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Ne vois-tu pas? Je suis en service. Arrête de me déranger.";
							link.l1 = "D'accord, d'accord...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Allez-vous me parler de quelque activité suspecte?";
							link.l1 = "Non, pas du tout, et je suis un capitaine, d'ailleurs. Je vois que vous n'écoutez plus ? Au revoir.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "C'est une installation militaire, alors ne faites pas trop de bruit ici.";
							link.l1 = "D'accord, je vais garder ça à l'esprit.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Un temps si clair, et je suis contraint de rester ici. En ville, il y a au moins des filles, et qu'avons-nous ici? Seulement des rats autour.";
							link.l1 = ""+GetSexPhrase("Je sympathise, mais il n'y a rien que je puisse faire pour aider - c'est votre devoir après tout.","Hé! Qu'est-ce qui ne va pas avec moi? Ne suis-je pas une fille?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Si tu aimes parler, trouve quelqu'un d'autre. Je dois maintenir l'ordre ici, et je n'ai pas de temps pour des bavardages bon marché.";
							link.l1 = "Oh, non, je vérifie seulement si tu es toujours en vie. Tu te tenais comme une statue.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Vous pensez probablement que les jours de travail de la garnison sont une promenade de santé ? Absolument pas ! C'est un travail dur et important. Je me souviens d'une fois...";
							link.l1 = "Vous me raconterez cette histoire une autre fois. Je suis un peu pressé maintenant.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Faites attention ici, vous êtes dans un fort ! Soyez aussi silencieux qu'une souris !";
							link.l1 = "Comme vous dites, soldat.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Hey ! Avez-vous de l'eau, par hasard ? Je meurs de soif.";
							link.l1 = "Non, mon pote, garde ton calme...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "Comme la vie en garnison est ennuyeuse, seuls des péquenauds comme toi sont autour ! Maintenant, la garnison de la ville a sûrement de meilleurs moments...";
							link.l1 = "Et tu appelles ça 'être de service'? De cette façon, tu laisseras sûrement un espion te glisser entre les doigts!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("Tu as l'air d'un gars costaud, n'est-ce pas? Aimerais-tu t'engager pour le service dans la garnison du fort? Nous avons des casernes spacieuses, deux repas par jour et de l'alcool gratuit.","Oh, jeune dame, vous n'avez aucune idée, combien il est agréable de rencontrer une si jolie demoiselle dans ce trou perdu!")+"";
							link.l1 = ""+GetSexPhrase("C'est certainement tentant, mais je dois encore refuser. Tout ce drill de caserne n'est tout simplement pas pour moi.","Merci pour le compliment, soldat.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Cette maudite chaleur... Je donnerais volontiers la moitié de ma vie pour retourner en Europe.";
							link.l1 = "Oui, je peux voir que votre santé n'est pas adaptée au climat local.";
							link.l1.go = "exit";
						break;
					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Eh bien... je comprends. Voici ce que "+GetSexPhrase("voulait","voulait")+" demander...";
					link.l3.go = "quests";//(перессылка в файл города) */
				}
			}
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_soldier":
			dialog.text = "Voyez-vous, je veux vraiment du vin... Mais pas le tord-boyaux local fait de fruits pourris, qui se vend deux pesos le baril - je veux une bouteille de vrai vin européen. Vous pouvez l'obtenir dans la ville auprès des marchands. C'est assez cher, mais je paierai en totalité et j'ajouterai même trois cents pesos par-dessus. Alors, m'en apporterez-vous ?";
			link.l1 = "Et pourquoi ne pouvez-vous pas l'obtenir par vous-même? Vous n'aurez pas besoin de trop payer, attendez simplement d'être relevé de votre poste et allez-y. Quel est le problème?";
			link.l1.go = "Wine_soldier_1";
		break;
		
		case "Wine_soldier_1":
			dialog.text = "Il n'y a pas de piege. Je ne peux tout simplement pas quitter le fort pour aller en ville jusqu'a ce que j'obtienne mon conge, ce qui n'arrivera pas de sitot. De plus, notre commandant a strictement interdit toute boisson dans le fort, maudit soit-il! Alors, vas-tu aider un soldat?";
			link.l1 = "Eh bien, pourquoi pas ? Je vous apporterai ce vin, j'ai du temps libre de toute façon.";
			link.l1.go = "Wine_soldier_2";
			link.l2 = "Je suis désolé, mon pote, mais je ne peux pas faire ça. Cherche quelqu'un d'autre pour t'aider.";
			link.l2.go = "exit";
		break;
		
		case "Wine_soldier_2":
			dialog.text = "Génial ! Merci beaucoup ! Aujourd'hui je suis de garde, alors venez demain. Vous me trouverez en haut du fort, là vous pouvez me glisser la bouteille, pour que personne ne remarque...";
			link.l1 = "D'accord. Attends-moi, je viendrai te voir demain.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.id = npchar.ID;
			pchar.questTemp.Wine.SName = GetFullName(npchar);
			pchar.questTemp.Wine.bottle = "true";
			npchar.lifeday = 5;
			SetFunctionTimerCondition("Wine_Exchange", 0, 0, 1, false);
			pchar.questTemp.Wine.City = GetCityNameByIsland(LoadedLocation.islandId);
			if(StartHeroType == 2) pchar.questTemp.Wine.City = "Santiago";
			Log_TestInfo(pchar.questTemp.Wine.City);
			SaveCurrentQuestDateParam("questTemp.Wine_bottle");
			AddQuestRecord("Wine", "0");
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
		// <-- мини-квест Дефицитный товар
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Il me semble que c'est une sorte de tromperie. Parlons avec le commandant, "+GetSexPhrase("camarade","mon chéri")+", et comprendre tout cela...","Hmm... Quelque chose me dit que tu n'es pas celui que tu prétends être... Rends ton arme "+GetAddress_Form(npchar)+", et suivez-moi pour une enquête plus approfondie!");
			link.l1 = RandPhraseSimple("Va te faire foutre !","Quand deux dimanches viennent en une semaine...");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Oh, je vois... Tout semble en ordre, vous êtes libre de partir, "+GetAddress_Form(pchar)+".","Je dois être un peu fatigué de monter la garde... Tout semble aller bien, "+GetAddress_Form(pchar)+", je suis désolé.");
			link.l1 = "Aucun problème !";
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Viens juste d'y penser ! Quelle insolence ! Venir ici sous le guise d'un marchand ! Tes portraits sont affichés dans chaque caserne, espèce de salaud ! Tu ne t'en sortiras pas cette fois ! Attrapez-le !";
				link.l1 = RandPhraseSimple("Arrgh!..","Eh bien, tu l'as demandé...");
				link.l1.go = "fight";	
				break;
			}
			if (findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе
			{
				dialog.text = "Vous êtes venu faire du commerce ici? Puis-je demander comment? Où est votre navire? Vous savez, tout cela semble très suspect, et je suis obligé de vous retenir jusqu'à ce que nous ayons tout compris. Rendez votre arme et suivez-moi!";
				link.l1 = RandPhraseSimple("Va te faire foutre !","Quand deux dimanches viennent en une semaine...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Votre licence doit être révoquée car elle est expirée et n'est donc pas valable. Rendez votre arme et suivez-moi pour une enquête plus approfondie!";
				link.l1 = RandPhraseSimple("Va te faire foutre !","Quand deux dimanches viennent en une semaine...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Tout semble en ordre. Cependant, je dois noter que votre licence expire aujourd'hui. Je vais vous laisser passer cette fois, mais vous devrez toujours obtenir une nouvelle licence.";
				link.l1 = "Merci, je le ferai à ma première commodité.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Tout semble en ordre. Cependant, je dois noter que votre licence expirera bientôt. Elle n'est toujours valable que pour "+FindRussianDaysString(iTemp)+". Alors garde ça à l'esprit, "+GetAddress_Form(npchar)+".";
				link.l1 = "Merci, j'en obtiendrai une nouvelle dès que possible.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Eh bien, tout semble correct. Votre licence est valide pour "+FindRussianDaysString(iTemp)+". Vous pouvez passer.","Tout est clair, "+GetAddress_Form(npchar)+". Vous pouvez entrer et sortir librement de la ville, votre licence est valide pour  "+FindRussianDaysString(iTemp)+". Désolé de vous déranger.","Tout a l'air bien, "+GetAddress_Form(npchar)+", je ne te retiens plus ici.");
				link.l1 = RandPhraseSimple("Excellent. Meilleures salutations.","Merci, officier.");
				link.l1.go = "exit";
			}
		break;

		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
				dialog.text = "Capitaine, je vous demande de ranger vos armes : il est interdit de les dégainer dans notre ville.";
				link.l1 = LinkRandPhrase("D'accord, je le range...","Déjà fait.","Comme vous dites...");
				link.l1.go = "exit";
				link.l2 = LinkRandPhrase("Va te faire foutre !","Je suppose que je vais l'utiliser !","Je le rangerai quand le moment sera venu.");
				link.l2.go = "fight";
				npchar.greeting = "soldier_common";
				NextDiag.TempNode = "First Time";
				break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("Pourquoi diable te promènes-tu avec une lame non gainée? Range ton arme immédiatement!","Je vous ordonne de ranger votre arme immédiatement!","Hey, "+GetSexPhrase("camarade","fillette")+", arrête de faire peur aux gens! Fourre ton arme.");
			link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme vous dites...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Va te faire foutre!","Il n'y a pas de mal à rêver...","Quand deux dimanches viennent en une semaine.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}
