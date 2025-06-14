void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Que veux-tu ?";
			link.l1 = "Rien pour le moment.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//Найти помощника в магазин
		case "Storehelper":
			DelLandQuestMark(npchar);
			dialog.text = "Y a-t-il quelque chose dont vous avez besoin, monsieur ?";
			link.l1 = "Vous êtes Gralam Lavoie, n'est-ce pas ?";
			link.l1.go = "Storehelper_1";
		break;
		
		case "Storehelper_1":
			dialog.text = "Qui demande ? Ne me dérangez pas pendant que je bois du rhum, monsieur. Je n'ai pas envie de bavarder.";
			link.l1 = "Je ne prendrai pas beaucoup de votre temps. Un marchand de Saint-Pierre m'a envoyé ici. Vous étiez son ancien employé. Il vous cherche et...";
			link.l1.go = "Storehelper_2";
		break;
		
		case "Storehelper_2":
			dialog.text = "Ha, il me cherche, hein!? C'est bien de la part de ce foutu radin ! Pensait-il vraiment que je passerais toute ma vie à travailler pour des salaires aussi dérisoires ? C'est le plus avare des grippe-sous des Caraïbes ! J'ai trimé pour lui pendant cinq ans et il ne m'a jamais payé un sou de plus qu'il ne pouvait s'en tirer ! Bah, même pas assez pour m'acheter un verre !\nIl peut compter ses propres marchandises maintenant, je démissionne. Personne à Saint-Pierre ne travaillera pour ce pingre, c'est sûr. Il n'a qu'une seule préoccupation - gagner plus pour lui-même et payer ses gens moins.";
			link.l1 = "Je suppose que tu ne retournes pas travailler pour lui ?";
			link.l1.go = "Storehelper_3";
		break;
		
		case "Storehelper_3":
			dialog.text = "Non, que Dieu me foudroie si je l'ai fait ! Je vais juste attendre ici à Le Francois qu'un navire arrive et je m'engagerai comme intendant s'ils veulent bien de moi. Et si cela ne fonctionne pas, alors je vivrai comme un simple matelot. Je ne peux même pas supporter de poser les yeux sur ce grippe-sou. Si je dois être pauvre, autant être un homme libre...";
			link.l1 = "Je comprends, c'est tout ce que j'avais besoin de savoir. Bonne chance, Gralam !";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_4":
			DelLandQuestMark(npchar);
			dialog.text = "Messire, écartez-vous. Vous êtes sur mon chemin !";
			link.l1 = "Juste une question, monsieur. Êtes-vous Gralam Lavoie ?";
			link.l1.go = "Storehelper_5";
		break;
		
		case "Storehelper_5":
			dialog.text = "Ha ! Oui, c'est moi. Que veux-tu ?";
			link.l1 = "Un marchand de Saint-Pierre te cherche. Tu travaillais pour lui, n'est-ce pas ?";
			link.l1.go = "Storehelper_6";
		break;
		
		case "Storehelper_6":
			dialog.text = "Ha-ha ! Quelle plaisanterie ! Et que veut sa majesté royale de moi ? A-t-il décidé de me payer mon salaire manquant pour mes deux dernières semaines de travail ? Ou a-t-il des difficultés à compter ses tonneaux tout en dupant ses clients, hein ? Ha-ha-ha !";
			link.l1 = "Il m'a demandé de te chercher et de clarifier pourquoi tu ne viens plus travailler dans sa boutique.";
			link.l1.go = "Storehelper_7";
		break;
		
		case "Storehelper_7":
			dialog.text = "Pourquoi ? Parce que c'est un foutu avare et un patron épouvantable ! Je fais maintenant partie des Frères de la Côte, un homme libre et plus un esclave ! Regardez autour de vous, je m'amuse vraiment !\nBientôt, je mettrai les voiles et je compterai des pesos et des doublons pris aux Espagnols au lieu de caisses de bananes ! Et pour ce radin - je doute qu'il trouve quelqu'un pour me remplacer. Personne à Saint-Pierre n'est assez stupide pour travailler pour lui, nous avons répandu la nouvelle de sa réputation à tous les apprentis de l'île, ha-ha !";
			link.l1 = "Je comprends. C'est tout ce que j'avais besoin de savoir. Bonne chance, Gralam !";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_8":
			DelLandQuestMark(npchar);
			dialog.text = "Comment puis-je vous aider ?";
			link.l1 = "Bon après-midi. Gralam Lavoie, je présume ?";
			link.l1.go = "Storehelper_9";
		break;
		
		case "Storehelper_9":
			dialog.text = "Oui. Que voulez-vous, monsieur ?";
			link.l1 = "Un marchand de Saint-Pierre est à ta recherche. Tu travaillais pour lui, n'est-ce pas ?";
			link.l1.go = "Storehelper_10";
		break;
		
		case "Storehelper_10":
			dialog.text = "Eh bien, qu'il continue de chercher. Je ne lui dois rien. Il me doit encore deux semaines de salaire, mais je ne vais même pas me donner la peine de récupérer mon argent. J'espère qu'il s'étouffe avec ses propres sous.";
			link.l1 = "Hum. Alors tu l'as quitté pour de bon, je suppose ?";
			link.l1.go = "Storehelper_11";
		break;
		
		case "Storehelper_11":
			dialog.text = "Tu as tout compris, sire. Mon ancien employeur est un rare spécimen d'avare, véritablement biblique en échelle. Je suis maintenant un Frère de la Côte et mes talents sont bien estimés par mes nouveaux compagnons. Je gagne deux fois plus, avec des primes en plus\nJe doute que notre cher ami trouve quelqu'un pour me remplacer. Son avidité est bien connue des gens de Saint-Pierre, personne là-bas n'est assez stupide pour travailler pour lui.";
			link.l1 = "J'ai compris. C'est tout ce que je devais savoir. Bonne chance, Gralam !";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_12":
			DialogExit();
			npchar.lifeday = 0;
			AddQuestRecord("SharlieA", "2");
			pchar.questTemp.Sharlie.Storehelper = "return";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.StorehelperOver.over = "yes"; //снять таймер
			
			pchar.quest.Sharlie_JungleBandos.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleBandos.win_condition.l1.location = "Martinique_Jungle_01";
			pchar.quest.Sharlie_JungleBandos.function = "SharlieJungleBandos";
			
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Newstorehelper_1":
			dialog.text = "Bonjour, monsieur. Je ne veux pas être trop audacieux, mais je crois que ma candidature conviendra parfaitement au poste que vous proposez.";
			link.l1 = "Bon après-midi. Et pourquoi pensez-vous cela ?";
			link.l1.go = "Newstorehelper_1_1";
		break;
		
		case "Newstorehelper_2":
			dialog.text = "Salutations, monsieur ! Permettez-moi de vous parler un peu de moi.";
			link.l1 = "Je suis tout ouïe.";
			link.l1.go = "Newstorehelper_2_1";
		break;
		
		case "Newstorehelper_3":
			dialog.text = "Bonne santé à vous, cher monsieur. Offrez-vous un poste de marchand ?";
			link.l1 = "Oui, je le suis. Que pouvez-vous me dire sur vous?";
			link.l1.go = "Newstorehelper_3_1";
		break;
		
		case "Newstorehelper_1_1":
			dialog.text = "J'ai servi comme quartier-maître sous le commandement du capitaine Francis Dubois lui-même. Il était très satisfait de mes compétences, mais j'ai été blessé au combat et j'ai dû prendre congé pour être soigné. Je suis bien maintenant, complètement sain de corps, mais l'idée des vagues roulantes me rend malade. Non, mon seul désir maintenant est de rester sur la terre ferme\n(chuchotant) Et si vous me choisissez, je paierai cinq cents pesos et vingt-cinq doublons d'or en extra.";
			link.l1 = "Je vois. Je vais y réfléchir.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_1":
			dialog.text = "J'étais marchand ambulant, mais j'ai dû fuir certains créanciers et prendre la mer comme intendant sur un navire marchand. Le destin m'a conduit dans ce village. De toute façon, je n'aimais pas beaucoup la vie de marin, et je serais ravi d'accepter votre offre\n(en chuchotant) Et si vous me choisissez, je vous donnerai non seulement cinq cents pesos, mais aussi ce lourd paquet d'ambre.";
			link.l1 = "Je vois. Je vais y réfléchir.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_1":
			dialog.text = "J'étais commis dans l'un des entrepôts portuaires de Glasgow. Je suis venu aux Caraïbes à la recherche de richesse et j'ai réussi à gagner assez d'argent pour vivre ma vieillesse avec dignité. Mais je suis fatigué des voyages en mer et j'aimerais vivre une vie paisible à terre\n(chuchotant) Et si tu me choisis, je te donnerai cinq cents pesos plus deux mille cinq cents pesos supplémentaires en prime.";
			link.l1 = "Je vois. J'y réfléchirai.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_2":
			dialog.text = "Monsieur, faites le bon choix. Et n'oubliez pas les doublons...";
			link.l1 = "J'ai décidé en ta faveur. Ressaisis-toi. Nous allons à Saint-Pierre.";
			link.l1.go = "Newstorehelper_1_3";
			link.l2 = "Je n'ai pas encore décidé...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_2":
			dialog.text = "J'espère que vous me choisirez, monsieur. Et l'ambre est aussi une chose assez précieuse et utile...";
			link.l1 = "J'ai décidé en ta faveur. Ressaisis-toi. Nous allons à Saint-Pierre.";
			link.l1.go = "Newstorehelper_2_3";
			link.l2 = "Je n'ai pas encore décidé...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_2":
			dialog.text = "Le marchand ne sera pas déçu par mon travail. Et n'oublie pas ton bonus.";
			link.l1 = "J'ai décidé en ta faveur. Ressaisis-toi. Nous allons à Saint-Pierre.";
			link.l1.go = "Newstorehelper_3_3";
			link.l2 = "Je n'ai pas encore décidé...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_3":
			dialog.text = " Laissez-moi juste rassembler mes affaires ! Je vous attendrai à l'entrée de la taverne. ";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;
		
		case "Newstorehelper_2_3":
			dialog.text = "J'arrive dans un instant, monsieur ! Je vous attendrai à l'entrée de la taverne.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;
		
		case "Newstorehelper_3_3":
			dialog.text = "Je vais prendre ma vieille valise et je vous attendrai à l'entrée de la taverne, monsieur !";
			link.l1 = "... ";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;
		
		case "Newstorehelper_exit":
			DialogExit();
			pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay")
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			pchar.quest.storehelper4.win_condition.l1 = "location";
			pchar.quest.storehelper4.win_condition.l1.location = "FortFrance_store";
			pchar.quest.storehelper4.function = "NewstorehelperRegard";
			AddQuestRecord("SharlieA", "4");
			pchar.questTemp.Sharlie.Storehelper = "choise";
			pchar.quest.storehelper.over = "yes"; //снять прерывание
			
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			
			SetLaunchFrameFormParam("Retour à Saint-Pierre...", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("FortFrance_store", "reload", "reload1", "");
			LaunchFrameForm();
		break;
		
		case "Newstorehelper_regard":
			dialog.text = "Eh bien, je suppose que c'est ici que je travaille désormais ? Merci, monsieur, de m'avoir choisi. Voici vos cinq cents pesos et le bonus promis en plus.";
			link.l1 = "Ma gratitude... Permettez-moi de vous présenter votre employeur.";
			link.l1.go = "Newstorehelper_regard_1";
		break;
		
		case "Newstorehelper_regard_1":
			DialogExit();
			npchar.lifeday = 0;
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "gold_dublon", 25);
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "jewelry8", 10);
					TakeNItems(pchar, "jewelry7", 1);
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 3000);
				break;
			}
		break;
		
		//контрабанда рома
		case "Rum_Cap_Over":
			dialog.text = "Monsieur, je dois vous demander de quitter mon navire immédiatement. Nous levons l'ancre et larguons les amarres !";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rum_Cap_Over";
			chrDisableReloadToLocation = false;
			npchar.DontDeskTalk = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;
		
		case "Rum_Cap":
			pchar.quest.Sharlie_rum2.over = "yes"; //снять таймер
			chrDisableReloadToLocation = false; // patch-4
			dialog.text = "Eh bien ? Qui es-tu, camarade ?";
			//link.l1.edit = 1;			
			link.l1 = "Bonjour, mon ami."+pchar.questTemp.Sharlie.Rum.Pass+" !";
			link.l1.go = "Rum_Cap_1";
		break;
		
		case "Rum_Cap_1":
			dialog.text = "Prends un coup de rhum, matelot! Ha-ha! Bienvenue à bord de mon lougre. Tu es venu pour la marchandise?";
			link.l1 = "Oui. Pour quelle autre raison serais-je ici ?";
			link.l1.go = "Rum_Cap_2";
			/* if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Prends un coup de rhum, matelot ! Ha-ha ! Bienvenue à bord de mon lougre. Tu es venu pour la marchandise ?";
				link.l1 = "Oui. Pourquoi d'autre serais-je ici?";
				link.l1.go = "Rum_Cap_2";
			}
			else
			{
				dialog.text = "Ma foi, quel fils de catin tout frais éclos ! Les gars, celui-là ressemble à une recrue toute crue ! Jetons-le par-dessus bord !";
				link.l1 = "Hep !";
				link.l1.go = "Rum_Cap_getout";
			} */
		break;
		
		case "Rum_Cap_getout":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
		break;
		
		case "Rum_Cap_2":
			dialog.text = "Les gars ! Chargez les caisses sur la chaloupe !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;
		
		case "Rum_Cap_3":
			dialog.text = "Tous les caisses de rhum sont sur votre chaloupe. Port Le Francois se trouve droit au sud d'ici. Faites vite, il est temps pour moi de lever l'ancre aussi !";
			link.l1 = "Ne perdons pas de temps, messieurs ! Bonne chance !";
			link.l1.go = "Rum_Cap_4";
		break;
		
		case "Rum_Cap_4":
			dialog.text = "Toi aussi, matelot...";
			link.l1 = "...";
			link.l1.go = "Rum_Cap_5";
		break;
		
		case "Rum_Cap_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			npchar.DontDeskTalk = true;
			NextDiag.CurrentNode = "Rum_Cap_Over";
			pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
			pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
			AddQuestRecord("SharlieB", "4");
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 3000;
			
			DoQuestFunctionDelay("MessageRum1", 1.0);
			//NewGameTip("Transport the rum to Le Francois. Keep sailing around the island.");
			pchar.questTemp.Rum.Tip2.Reload = "l4";
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
			
			Weather.Wind.Angle = PId2;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
			pchar.quest.MessageRum2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.MessageRum2.win_condition.l1.location = pchar.location;
			pchar.quest.MessageRum2.function = "MessageRum2";
		break;
		
		case "Rum_Carrier":
			dialog.text = "Nous vous attendions, monsieur. Comment cela s'est-il passé? Avez-vous les caisses?";
			link.l1 = "Tout s'est déroulé de façon spectaculaire. Les caisses de rhum sont sur la chaloupe.";
			link.l1.go = "Rum_Carrier_1";
		break;
		
		case "Rum_Carrier_1":
			dialog.text = "Parfait. Nous nous occupons du reste. Filez à Saint-Pierre à la taverne pour le paiement. Soyez attentif et prudent dans les jungles nocturnes.";
			link.l1 = "Tout le meilleur, messieurs.";
			link.l1.go = "Rum_Carrier_2";
		break;
		
		case "Rum_Carrier_2":
			DialogExit();
			for (i=1; i<=3; i++)
			{
				
				sld = characterFromId("Rum_Carrier2_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.questTemp.Sharlie.Rum = "regard";
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Gigolo")) QuestPointerToLocTime("fortfrance_town", "reload", "reload9_back", 23.0, 24.0);
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		//доставить девочку из борделя
		case "GigoloMan":
			DelLandQuestMark(npchar);
			dialog.text = "Bon après-midi, monsieur ! Ma foi, vous n'avez pas l'air des vauriens en haillons qui traînent habituellement dans notre colonie. À en juger par vos vêtements, vous avez dû venir de loin... Arrivé d'Europe, n'est-ce pas ?";
			link.l1 = "Exactement, monsieur. "+GetFullName(pchar)+", à votre service. Que voulez-vous?";
			link.l1.go = "GigoloMan_1";
		break;
		
		case "GigoloMan_1":
			dialog.text = "Permettez-moi de me présenter - "+GetFullName(npchar)+"Je suis arrivé dans ce lieu effroyable de France il y a quelques années. Mais cela n'a pas d'importance. J'ai une affaire très délicate pour vous.\nVeuillez comprendre que si je n'étais pas sûr que vous étiez un gentilhomme, je ne vous demanderais jamais une telle faveur.";
			link.l1 = "Veuillez, énoncer votre demande, monsieur. Si cela est dans mes capacités, alors bien sûr, j'essaierai d'aider.";
			link.l1.go = "GigoloMan_2";
		break;
		
		case "GigoloMan_2":
			dialog.text = "Je suis heureux d'entendre ces mots de votre part, monsieur de Mor. Voilà le fait. Dans notre bled, il y a un bordel. Une jeune fille y est arrivée récemment, apparemment d’Europe — blanche, blonde, toute juvénile. Cela fait plusieurs semaines que je l’observe et… j’ai un désir fou de rester seul avec elle.\nCependant, ma position dans la société et mon rang m’interdisent de m’aventurer dans ce lieu de péché. Non, comme vous l’avez deviné, mon ami, je n’y vois pas d’objection — mais ma réputation a un prix très élevé.\nC’est pourquoi je me tourne vers vous. Vous êtes un homme nouveau ici, personne ne vous connaît, et personne ne s’intéresse à vous… pour l’instant. Vous me rendriez un immense service, monsieur…";
			link.l1 = "Et comment puis‑je vous aider, monsieur ?";
			link.l1.go = "GigoloMan_3";
		break;
		
		case "GigoloMan_3":
			dialog.text = "Je vous remercie pour votre discrétion, monsieur. Je ne peux pas aller à la fille, donc la fille doit venir à moi. Chez moi. Je vous demande d'aller au bordel et d'arranger un accord avec la madame pour qu'elle vous permette d'organiser une 'visite à domicile' de la fille blonde pour une nuit\nAurora ne refusera pas, elle est bien connue pour fournir de tels services de livraison, bien que cela coûte toujours un peu plus. Après cela, vous devrez amener la fille chez moi. Pour paiement, je vous donnerai six mille pesos. Aurora prend généralement trois mille ou trois mille cinq cents pour une nuit avec la fille à domicile. Vous pouvez garder le surplus en guise de compensation pour vos ennuis.";
			link.l1 = "Ça ne semble pas trop compliqué. Je peux le faire.";
			link.l1.go = "GigoloMan_4";
			link.l2 = "Monsieur, je prends ma réputation de gentilhomme aussi au sérieux que vous. Je vous prie de me pardonner, mais je ne peux pas satisfaire votre demande. Je dois refuser. Je devrais probablement aller à la taverne et vérifier si l'aubergiste a du travail pour moi.";
			link.l2.go = "GigoloMan_exit";
		break;
		
		case "GigoloMan_exit":
			DialogExit();
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload9", false);// бордель
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false);// таверна
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
		break;
		
		case "GigoloMan_4":
			dialog.text = "Je suis très heureux. Écoutez bien: la jeune fille que je veux s'appelle Lucile. Je vous demande de la conduire chez moi lorsqu’il fera nuit, pas avant onze heures du soir, pour que personne ne vous voie. Frappez à la porte et je vous ouvrirai\nMa maison se trouve à gauche de la résidence du gouverneur, si vous lui tournez le dos — un manoir à deux étages au toit rouge. Vous le trouverez facilement, il y a aussi un magasin juste à côté. En fait, je suis en route chez moi maintenant, vous pouvez me suivre pour voir à quoi elle ressemble et où elle est exactement, afin de ne pas vous tromper la nuit\nVoici, prenez six mille pesos. Et je vous attends à l’heure convenue !";
			link.l1 = "Très bien, monsieur, c’est entendu. D’ici la nuit, votre blonde sera devant votre porte.";
			link.l1.go = "GigoloMan_5";
		break;
		
		case "GigoloMan_5":
			DialogExit();
			AddMoneyToCharacter(pchar, 6000);
			AddQuestRecord("SharlieC", "1");
			AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie.Gigolo = "start";
			pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
			pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", false);// бордель
			AddLandQuestMark(characterFromId("Fortfrance_hostess"), "questmarkmain");
			QuestPointerToLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerToLoc("fortfrance_brothel", "reload", "reload3");
			chrDisableReloadToLocation = false;
		break;
		
		case "GigoloGirl":
			if (npchar.quest.meeting == "0")
			{
				DelLandQuestMark(npchar);
				QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
				dialog.text = "Bonne journée, monsieur. Eh bien, êtes-vous l'homme qui m'a engagée ce soir ? Oh là là, je dois dire que j'ai bien de la chance de tomber sur un gentleman si beau et bien soigné, rien à voir avec les brutes qui débarquent du port en puant le goudron et la sueur...";
				link.l1 = "Mes excuses, mais pas ce soir, Lucille. Je suis ici au nom de mon bon ami, qui, pour une multitude de raisons très compliquées, ne peut pas quitter sa maison, alors je vais vous amener à lui. Maintenant, ne soyez pas contrariée, c'est un homme doux et il vous apprécie beaucoup. Je pense que vous serez heureuse à la fin.";
				link.l1.go = "GigoloGirl_1";
				// belamour legendary edition -->
				link.l2 = "Euh... Tu as tout à fait raison, ma chère. On y va?";
				link.l2.go = "GigoloGirl_1a";
				// <-- legendary edition
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Monsieur, j'espère que vous comprenez que je ne peux pas simplement me promener avec vous la nuit. Vous devez m'emmener rapidement chez votre ami ou je retournerai directement chez Madame et vous allez gâcher votre argent.";
				link.l1 = "Très bien, je comprends. Suivez-moi !";
				link.l1.go = "GigoloGirl_2";
			}
		break;
		// belamour legendary edition -->
		case "GigoloGirl_1a":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			chrDisableReloadToLocation = true; //закрыть локацию
			DoQuestReloadToLocation(pchar.location+"_room", "goto", "goto2", "GigoloGirl_Sex");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_room", "goto", "goto1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		case "GigoloGirl_1":
			AddCharacterExpToSkill(pchar, "Fortune", 40);
		// <-- legendary edition
			dialog.text = "C'est bien dommage... Je t'ai tout de suite apprécié, monsieur. J'aurais adoré passer la nuit avec toi... peut-être une autre fois. Allons-y?";
			link.l1 = "Oui. Suis-moi !";
			link.l1.go = "GigoloGirl_2";
		break;
		
		case "GigoloGirl_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
			pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
			QuestPointerToLoc("fortfrance_town", "reload", "houseSp1");
		break;
		
		case "GigoloGirl_3":
			dialog.text = "Quelle grande maison. Est-ce l'endroit ?";
			link.l1 = "Oui. Entrez. N'ayez pas peur, mon ami est un homme bon.";
			link.l1.go = "GigoloGirl_4";
		break;
		
		case "GigoloGirl_4":
			dialog.text = "Vous me sous-estimez, je n'ai pas peur, monsieur. Je sais comment me débrouiller. Maintenant, peut-être qu'un peu plus tard, vous pourrez payer Madame pour une nuit avec moi ? Je promets que ce sera la meilleure nuit de votre vie !";
			link.l1 = "Tout est possible, Lucille. Peut-être nous reverrons-nous. Adieu !";
			link.l1.go = "GigoloGirl_5";
		break;
		
		case "GigoloGirl_5":
			pchar.quest.Sharlie_Gigolo1.over = "yes";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
			QuestPointerDelLoc("fortfrance_town", "reload", "houseSp1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		//пираты с пленным испанцем
		case "CaptivePirate":
			pchar.quest.Captive_CreatePiratesOver.over = "yes";//снять таймер
			pchar.quest.Captive_CreatePiratesOver2.over = "yes";//снять таймер
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			dialog.text = "Qu'est-ce que c'est!? Qui êtes-vous? Que voulez-vous ici? Allez, foutez le camp d'ici!";
			link.l1 = "Tu n'es pas très poli, monsieur.";
			link.l1.go = "CaptivePirate_1";
		break;
		
		case "CaptivePirate_1":
			dialog.text = "Ecoute, garçon, je n'ai pas été élevé pour être poli, tout comme je n'ai pas appris à lire et écrire, mais fendre ton crâne avec un coutelas m'est aussi aisé qu'une catin tombant à la renverse. Et je jure sur mes yeux de mort que si tu ne sors pas d'ici à l'instant, tu seras porté dehors. T'as compris ?";
			link.l1 = "Non, c'est toi qui m'écoutes, gredin. Ton complot est à découvert. J'ai besoin de cet homme vivant, alors jette tes armes et cours. Il y a une escouade de soldats français dans la jungle juste derrière moi. Si tu cours assez vite, alors peut-être que tu parviendras à sauver vos vies pitoyables.";
			link.l1.go = "CaptivePirate_3";
			link.l2 = "D'accord, d'accord, calme-toi. Je m'en vais.";
			link.l2.go = "CaptivePirate_2";
		break;
		
		case "CaptivePirate_2":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
				sld.lifeday = 0;
			}
			sld = characterFromId("CaptiveSpain");
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";//снять прерывание
			AddQuestRecord("SharlieD", "5");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "CaptivePirate_3":
			dialog.text = "Quoi-i ? Tu bluffes, mate ! Descendez-le les gars, aux armes !";
			link.l1 = "Alors, que cela retombe sur ta tête, en garde !";
			link.l1.go = "CaptivePirate_4";
		break;
		
		case "CaptivePirate_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			int n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
			sld = characterFromId("CaptiveSpain");
			LAi_SetCitizenType(sld);
			DoQuestFunctionDelay("Ngt_CaptiveEng", 0.5);
		break;
		
		//пленный испанец
		case "CaptiveSpain":
			dialog.text = "Gracias a Dios! Ah, vous êtes Français? Merde, vous avez repoussé ces brigands avec panache. Mais ne pensez pas que je vais simplement me rendre, je vais vous montrer comment un Espagnol se bat! Santiago!";
			link.l1 = "Non, attends, s'il te plaît !";
			link.l1.go = "CaptiveSpain_1";
		break;
		
		case "CaptiveSpain_1":
			dialog.text = "Je préfèrerais mourir plutôt que d'être pris par les Français. J'ai pris un sabre sur l'un des cadavres pendant que tu te battais... maintenant je vais te faire danser une quadrille espagnole !";
			link.l1 = "Vous, Espagnols, êtes aussi têtus que des mules !";
			link.l1.go = "CaptiveSpain_2";
		break;
		
		case "CaptiveSpain_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			NextDiag.currentnode = "CaptiveSpain_3";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "CaptiveSpain_3":
			dialog.text = "Maldito... Tu as gagné. J'abandonne, maudit Français. Je suis à ta merci.";
			link.l1 = "Range ton épée et laisse-moi parler, toi, Castillan obstiné ! Je ne veux pas que tu meures, et je ne t'envoie pas non plus en prison !";
			link.l1.go = "CaptiveSpain_4";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;
		
		case "CaptiveSpain_4":
			dialog.text = "Alors que fais-tu ? Pourquoi as-tu tué les pirates ? Et où sont tes soldats ?";
			link.l1 = "Il n'y a pas de soldats. J'ai essayé de duper les vauriens, mais comme vous pouvez le voir autour de nous, cela n'a pas fonctionné. Je suis ici seul, selon la demande de votre vieil ami. Son nom est "+pchar.questTemp.Sharlie.Captive.Name+", il est banquier à St. Pierre.";
			link.l1.go = "CaptiveSpain_5";
		break;
		
		case "CaptiveSpain_5":
			dialog.text = "Bonjour, mon ami."+pchar.questTemp.Sharlie.Captive.Name+" ? Je ne connais personne de ce nom...";
			link.l1 = "Je ne savais rien de vous ni de votre captivité. C'est par lui que j'ai appris votre transfert sur un navire anglais. Ma tâche est de vous livrer à lui et j'ai juré de le faire ! Maintenant, venez avec moi si vous voulez vivre.";
			link.l1.go = "CaptiveSpain_6";
		break;
		
		case "CaptiveSpain_6":
			dialog.text = "De toute façon, je n'ai pas le choix... Ton banquier ne peut pas être pire que les Anglais et leur cuisine atroce...";
			link.l1 = "Tu prends enfin une sage décision. Assez parlé pour l'instant, nous mettons le cap sur St. Pierre. Reste près de moi et ne t'éloigne pas. Si tu t'enfuis, je te rattraperai et je te battrai à nouveau jusqu'à ce que tu sois à deux doigts de la mort.";
			link.l1.go = "CaptiveSpain_7";
		break;
		
		case "CaptiveSpain_7":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
			DialogExit();
			AddQuestRecord("SharlieD", "6");
			LAi_group_Register("TempFriends");
			LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "TempFriends");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
			pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
			pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
			pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
			pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
			pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
			pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload";//вход ночью
			pchar.questTemp.Sharlie = "bankskipercaptive";
			SetFunctionLocationCondition("CaptiveSpain_removeGuard", "fortfrance_town", 0);
			SetFunctionLocationCondition("CaptiveSpain_saveTip", "fortfrance_exittown", 0);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			// Rebbebion, новые марки до места назначения. belamour поправил - были не в ту сторону
			QuestPointerToLoc("shore39", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload8_back");
			AddLandQuestMark(characterFromId("FortFrance_Usurer"), "questmarkmain");
		break;
		
		//горожанин с пропавшей дочерью
		case "Prosper":
			DelLandQuestMark(npchar);
			pchar.quest.Sharlie_RescueDaughter.over = "yes"; //снять прерывание
			dialog.text = "Que désirez-vous, monsieur ? Je n'ai point de temps pour discuter, alors soyez bref.";
			link.l1 = "Vous êtes Prosper Trubal, n'est-ce pas ?";
			link.l1.go = "Prosper_1";
		break;
		
		case "Prosper_1":
			dialog.text = "Oui, c'est moi. Mais vous avez l'avantage sur moi. Veuillez m'informer de qui vous êtes et ce que diable vous voulez.";
			link.l1 = "Mon nom est "+GetFullName(pchar)+"J'ai été envoyé à vous par "+GetFullName(characterFromId("Fortfrance_portman"))+", le maître de port. Il a dit que vous aviez besoin d'une aide urgente...";
			link.l1.go = "Prosper_2";
		break;
		
		case "Prosper_2":
			dialog.text = "Mon Dieu oui ! Ce sacripant de commandant n'a même pas écouté ma plainte ! Il est soit trop paresseux, soit trop lâche pour aider. Es-tu vraiment venu ici pour m'aider ? Si c'est le cas, je ne te laisserai pas sans récompense !";
			link.l1 = "Oui Prosper. Dis-moi ce qui s'est passé et ce que je dois faire pour aider. J'ai entendu dire que ta fille a disparu...";
			link.l1.go = "Prosper_3";
		break;
		
		case "Prosper_3":
			dialog.text = "Oui, ma chère fille Célène a disparu depuis deux jours. Elle est partie se promener jusqu'au fort non loin d'ici. Mais elle n'est jamais revenue, alors je suis allé au fort moi-même et les soldats m'ont dit qu'elle n'y avait jamais été !\nMais à mon retour, j'ai été attaqué par deux sauvages Indiens ! Ils ont sauté sur moi avec des massues et ont essayé de me battre.\nMais je ne suis pas un chaton, alors j'ai frappé l'un d'eux au visage, ce qui m'a donné assez de temps pour dégainer mon pistolet et tirer. J'ai raté mais je les ai effrayés. J'ai réussi à atteindre les portes de la ville et j'ai raconté l'attaque aux gardes. Ils ont couru vers la jungle, mais les sauvages étaient déjà partis depuis longtemps.\nJe suis sûr qu'ils sont responsables de la disparition de Célène. En plus de cela, deux autres personnes ont disparu la semaine dernière - César Blanchet et Gilbert Courcy ! L'un se dirigeait vers la baie et l'autre vers Le François. Ils ne sont jamais revenus.";
			link.l1 = "Alors, les Indiens ont attaqué les citadins juste aux portes de la ville ? C'est d'une audace incroyable...";
			link.l1.go = "Prosper_4";
		break;
		
		case "Prosper_4":
			dialog.text = "Entre-temps, je suis allé moi-même dans la jungle pour la chercher et j'ai trouvé une grotte au nord de la ville. J'ai découvert que ces salauds s'y terrent. J'ai vu plusieurs Indiens à l'entrée, mais certains doivent être à l'intérieur aussi\nJ'ai entendu une fille crier... C'était ma Célène, j'en suis sûr, c'était sa voix ! Il m'a fallu tout mon contrôle pour ne pas me précipiter là-dedans sur le champ - les chances n'étaient pas de mon côté et ils m'auraient massacré. Je ne lui sers à rien mort.";
			link.l1 = "Mais pourquoi diable attaquent-ils et prennent-ils les habitants en otage ?";
			link.l1.go = "Prosper_5";
		break;
		
		case "Prosper_5":
			dialog.text = "Je ne sais pas... Peut-être pour les vendre à des pirates ou des esclavagistes ? Peut-être qu'ils les mangeront vivants, ce sont des sauvages après tout.";
			link.l1 = "Mon Dieu au ciel, sont-ils des cannibales ? Je pensais que ce n'étaient que des histoires pour effrayer les enfants en Europe...";
			link.l1.go = "Prosper_6";
		break;
		
		case "Prosper_6":
			dialog.text = "Des histoires ? Eh bien, certains hommes comme vous pensaient la même chose jusqu'à ce que les Caraïbes les aient fait cuire sur un feu et dévorés... Alors, j'ai immédiatement adressé une requête au commandant pour une expédition punitive afin de sauver ma Célène. Il a refusé ! Il a dit que lorsque des filles disparaissent, elles sont probablement parties avec un garçon, pas des Indiens. Il m'a suggéré de la chercher dans les granges locales\nEt quant aux deux autres disparus... il a dit que l'un d'eux était soupçonné de contrebande, et que l'autre est probablement en train de boire à mort dans la taverne de Le François. En résumé, je n'ai rien accompli et j'ai décidé d'agir par moi-même.";
			link.l1 = "Que comptes-tu faire ?";
			link.l1.go = "Prosper_7";
		break;
		
		case "Prosper_7":
			dialog.text = "Je vais y aller et tuer jusqu'au dernier de ces foutus rouges. J'espère seulement que Celene est encore en vie. Comme tu peux le voir, j'ai acheté un mousquet - et je sais comment m'en servir. J'ai payé une fortune pour ça mais je m'en fiche\nMa mission sera beaucoup plus facile si tu m'accompagnes. Ensemble, nous pourrons finir ces sauvages sans trop de problèmes si tu peux couvrir mes arrières pendant que je recharge. Viendras-tu avec moi pour sauver ma fille ?";
			link.l1 = "Bien sûr ! C'est une question d'honneur ! Je ne peux pas simplement laisser une fille mourir sous le couteau d'un sauvage.";
			link.l1.go = "Prosper_8";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1.go = "Prosper_noweapon";
			}
			link.l2 = "Hm. Tu sais, je pense que les paroles du commandant ont du sens. Peut-être devrions-nous quand même suivre son conseil en premier ?";
			link.l2.go = "Prosper_exit";
		break;
		
		case "Prosper_noweapon":
			dialog.text = "Monsieur, où est votre lame ?";
			link.l1 = "Il semble que je l'ai égaré.";
			link.l1.go = "Prosper_noweapon_1";
		break;
		
		case "Prosper_noweapon_1":
			dialog.text = "Ça ne fera tout simplement pas l'affaire. Je vous attendrai jusqu'au soir, je vous conseille de vous prosterner aux pieds de notre gouverneur et de supplier son aide.";
			link.l1 = "Rampe à ses pieds, hein? Eh bien, comme tu veux...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prosper_getweapon";
			SetFunctionTimerConditionParam("RescueDaughter_Over", 0, 0, 0, 22, false);
		break;
		
		case "Prosper_getweapon":
			dialog.text = "Eh bien, monsieur ? Vous êtes-vous procuré une arme ?";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1 = "Pas encore, veuillez patienter un peu plus longtemps...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Prosper_getweapon";
			} else {
				link.l1 = "Compris. Je suis prêt à t'aider !";
				link.l1.go = "Prosper_8";
				DeleteQuestCondition("RescueDaughter_Over");
			}
		break;

		case "Prosper_exit":
			dialog.text = "Mon Dieu, tu fuis? Non! Fous le camp d'ici! Lâche!";
			link.l1 = "Hé-hé, doucement là, espèce de simplet ! Je ferais mieux de sortir et voir si des nobles dans les rues de Saint-Pierre ont besoin d'aide.";
			link.l1.go = "Prosper_exit_1";
			pchar.questTemp.Sharlie.GigoloMan.SamPodbezhit = true;
		break;
		
		case "Prosper_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			//AddTimeToCurrent(2,0);
			SetCurrentTime(17,30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
			CloseQuestHeader("SharlieF");
			chrDisableReloadToLocation = true;
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Prosper_8":
			dialog.text = "Je suis heureux qu'il y ait au moins un homme courageux dans cette ville. Tenez, prenez ces trois fioles. Ce sont des herbes médicinales, je les ai achetées à notre herboriste. Cela peut vous être d'une grande aide au combat.";
			link.l1 = "Et toi ?";
			link.l1.go = "Prosper_9";
		break;
		
		case "Prosper_9":
			TakeNItems(pchar, "potion1", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ne t'inquiète pas, j'en ai encore. Es-tu prêt?";
			link.l1 = "Oui, ne perdons pas de temps. En avant !";
			link.l1.go = "Prosper_10";
		break;
		
		case "Prosper_10":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "fortfrance_exittown", "reload", "reload3", "OpenTheDoors", 10.0);
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1 = "location";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1.location = "FortFrance_ExitTown";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition = "RescueDaughter_ProsperGateOutReload";
			AddQuestRecord("SharlieF", "3");
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
			pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour  = sti(GetTime()+2);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
			NextDiag.CurrentNode = "Prosper_11";
			pchar.questTemp.Sharlie.RescueDaughter = "true";
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", true);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", true);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", true);//джунгли
		break;
		
		case "Prosper_11":
			dialog.text = "Nous sommes presque en position, "+pchar.name+"Au-delà de ce virage se trouve l'entrée de la grotte. Approche et je te dirai notre plan.";
			link.l1 = "Je suis tout ouïe, Prosper.";
			link.l1.go = "Prosper_12";
		break;
		
		case "Prosper_12":
			dialog.text = "Je dois ajuster mon tir avec ce lourd mousquet, mais si tu peux me gagner du temps, je ne manquerai pas ma cible. Si je dois engager un combat rapproché, oublie tout soutien de feu, je ne pourrai que repousser les gens avec mon canon comme massue. Ce combat va dépendre de ton habileté à l'escrime.";
			link.l1 = "Que cherches-tu à dire ?";
			link.l1.go = "Prosper_13";
		break;
		
		case "Prosper_13":
			dialog.text = "Tout ce que tu dois faire, c'est détourner leur attention pour que je puisse tous les abattre. Je ne peux pas me déplacer et tirer, donc je resterai à un endroit fixe. Il y a trois salauds près de l'entrée de la grotte. Tu devrais les charger aussi vite que possible avec ta lame à la main\nFrappe l'un d'eux et fais-les te poursuivre. Attire-les loin de moi. Si les trois se concentrent sur toi, je peux les descendre comme des oiseaux pendant que tu pares et esquives. Mais si ces sauvages fondent sur moi, nous sommes fichus. Es-tu prêt ?";
			link.l1 = "Ce ne sera pas la première fois que je manie une épée, ces sauvages ne sont pas une menace.";
			link.l1.go = "Prosper_14";
			// belamour legendary edition -->
			link.l2 = "Ha ! Ne t'inquiète pas pour moi. C'est comme chasser au Mans ! Ne me tire pas dans le dos par erreur !";
			link.l2.go = "Prosper_14a";
		break;
		
		case "Prosper_14a":
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			dialog.text = "Passe devant, je te suis. Souviens-toi : tu ne dois pas les laisser s'approcher de moi !";
			link.l1 = "Je me souviens, allons-y. En avant !";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_14":
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			// <-- legendary edition
			dialog.text = "Alors prépare-toi pour l'action. Va en premier, je te suivrai. Souviens-toi : tu ne peux pas les laisser s'approcher trop près de moi !";
			link.l1 = "Je me souviens. Je ferai tout ce que je peux. En avant !";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_15":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
			NextDiag.CurrentNode = "Prosper_16";
			NewGameTip("A challenging fight awaits ahead. (F6) for quick save.");
		break;
		
		case "Prosper_16":
			dialog.text = "Bien joué, "+pchar.name+" ! Ces païens sauvages n'assassineront plus. Maintenant pour l'événement principal - la caverne. Je crois qu'il y en a trois ou quatre à l'intérieur, mais je ne peux en être sûr. Écoute maintenant\nJ'y suis allé il y a dix ans. Il y a un tunnel étroit à l'intérieur de la caverne. Il mène à une petite grotte, divisée par un mur avec un trou au milieu. Répétons notre plan d'avant. Je reste immobile près de l'entrée et tu te précipites à l'intérieur\nProvoque-les, ne cherche pas à tous les combattre à la fois, empêche-les simplement de m'attaquer. Prends position au tunnel dont j'ai parlé, il est étroit, donc seulement un ou deux d'entre eux pourront te combattre en même temps\nJe tirerai sur eux par-dessus ton épaule. Prêt ?";
			link.l1 = "En avant ! Finissons-en avec ce nid de sauvages !";
			link.l1.go = "Prosper_17";
		break;
		
		case "Prosper_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			NextDiag.CurrentNode = "Prosper_18";
		break;
		
		case "Prosper_18":
			dialog.text = "Ma fille est vivante ! Dieu merci ! Nous sommes arrivés à temps, "+pchar.name+"Je vous suis redevable, monsieur. Vous êtes un homme courageux et un bon combattant !";
			link.l1 = "Je suis heureux qu'il y ait une fin heureuse, Prosper. C'était un sacré boulot sanglant d'éliminer tous ces Indiens.";
			link.l1.go = "Prosper_19";
		break;
		
		case "Prosper_19":
			DialogExit();
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Prosper_20":
			dialog.text = "Mes plus sincères remerciements encore une fois, "+pchar.name+" ! Maintenant, retournons en ville. La vie de ma fille est inestimable, au-delà de toute somme d'argent, mais je veux vous remercier en vous donnant ce qui reste de mes économies. Dès que nous arriverons à Saint-Pierre, je vous les donnerai avec plaisir. Et ne pensez même pas à refuser !";
			link.l1 = "Je ne refuserai pas, Prosper. Bien que l'argent n'était pas mon objectif en vous aidant.";
			link.l1.go = "Prosper_21";
		break;
		
		case "Prosper_21":
			dialog.text = "Vous êtes un véritable chevalier chrétien, "+pchar.name+" ! Maintenant, ne traînons pas ici. Rentrons chez nous sans tarder !";
			link.l1 = "...";
			link.l1.go = "Prosper_22";
		break;
		
		case "Prosper_22":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Tutorial_Amulet.over = "yes";
			SetLaunchFrameFormParam("Back to the town...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("FortFrance_town", "reload", "gate_back", "");
			LaunchFrameForm();
		break;
		
		case "Prosper_23":
			SelectPresentAmulet();
			dialog.text = "Nous y voilà, Charles. Je te remercie encore une fois pour ton aide et j'attache cette modeste somme de pesos et de doublons d'or à mes paroles. Je te conseille de ne pas gaspiller les doublons et de les garder pour des occasions spéciales. Je sais, ce n'est pas beaucoup d'argent pour un tel service que tu m'as rendu, mais c'est du fond du cœur. Prends aussi cet amulette, "+pchar.questTemp.SMQ.Text+" ";
			link.l1 = "Merci ! Adieu Prosper, je souhaite bonheur à toi et à ta chère fille !";
			link.l1.go = "Prosper_24";
		break;
		
		case "Prosper_24":
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", false);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", false);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", false);//джунгли
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "gold_dublon", 15);
			TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
			Log_Info("You've received 15 doubloons");
			Log_Info("You've received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ah, un mari comme toi lui ferait du bien. Tout ce qu'elle fait, c'est être poursuivie en ville par une bande de freluquets aux jambes maigres et sans menton. Quel sacré dommage que chacun d'eux ait disparu quelque part... bon débarras. Bonne chance, Charles !";
			link.l1 = "... ";
			link.l1.go = "Prosper_25";
		break;
		
		case "Prosper_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 120);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 70);//скрытность
			AddQuestRecord("SharlieF", "7");
			CloseQuestHeader("SharlieF");
			DeleteAttribute(pchar, "questTemp.SMQ");
			pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			pchar.quest.Sharlie_JungleNative.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleNative.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Sharlie_JungleNative.function = "SharlieJungleNative";
			SetCurrentTime(17,30);
			//AddTimeToCurrent(2,0);
			//QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Selina":
			dialog.text = "Ah ! Que Dieu me vienne en aide ! (pleurant) Tu... tu ne peux même pas imaginer l'horreur qui se passe ici ! Ces... ces Indiens nous ont traînés ici pour nous tuer et nous manger ! Cesar Blanchet était ici... Les sauvages l'ont pris... Ils ont exécuté un rituel diabolique horrible et ensuite... Seigneur, je ne peux même pas en parler ! J'étais censé être le suivant ! Ils allaient m'égorger... demain !";
			link.l1 = "Calme-toi, Céline. Tout est fini. Ces salauds ont eu ce qu'ils méritaient et ils ne feront plus de mal à personne.";
			link.l1.go = "Selina_1";
		break;
		
		case "Selina_1":
			dialog.text = "Gilbert Coursie est ici aussi. Là-bas... il euh... il ne s'est toujours pas remis. Parle-lui... Puis dépêchons-nous de sortir d'ici !";
			link.l1 = "Là, là. Tout va bien, ma fille. Assez de larmes. Tout va bien. Tu as un père merveilleux. Il ne laisserait personne te faire du mal... Va dehors, je vais aider... euh... Gilbert à sortir d'ici et je te rejoindrai plus tard.";
			link.l1.go = "Selina_2";
		break;
		
		case "Selina_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			sld = characterFromId("RD_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
			AddQuestRecord("SharlieF", "5");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
		break;
		
		case "Selina_3":
			dialog.text = "Dieu et la Sainte Mère ont entendu mes prières ! Es-tu venu pour nous sauver ?";
			link.l1 = "Toi... Ton nom est Celine, n'est-ce pas ?";
			link.l1.go = "Selina_4";
		break;
		
		case "Selina_4":
			dialog.text = "Oui... (en pleurant) Vous... vous ne pouvez même pas imaginer l'horreur qui se passe ici ! Ces... ces Indiens nous ont traînés ici pour nous tuer et nous manger ! Cesar Blanchet était ici... Ils l'ont pris... Ils ont exécuté un rituel diabolique et puis... Seigneur, je ne peux même pas en parler ! Je suis censé être le prochain ! Ils allaient m'égorger... demain !";
			link.l1 = "Calme-toi, petite fille... Je suis désolé mais je t'apporte de mauvaises nouvelles. Je suis venu ici avec ton père. Il a été tué juste à l'extérieur par ces sauvages à peau rouge alors que nous luttions pour te rejoindre. Il a donné sa vie pour te sauver.";
			link.l1.go = "Selina_5";
		break;
		
		case "Selina_5":
			dialog.text = "Quoi ?! Mon père... Oh Dieu ! Je... Je...(sanglotant)";
			link.l1 = "Mes condoléances, Céline. Il y a quelqu'un d'autre ici avec vous, ai-je raison ?";
			link.l1.go = "Selina_6";
		break;
		
		case "Selina_6":
			dialog.text = "(en pleurant) Oui... Gilbert Coursie. Il est là-dedans... Il ne s'est pas encore remis. Allez lui parler... Puis dépêchons-nous de sortir d'ici !";
			link.l1 = "Oui, bien sûr. Nous ne pouvons pas perdre une minute à rester ici.";
			link.l1.go = "Selina_7";
		break;
		
		case "Selina_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			AddQuestRecord("SharlieF", "6");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Selina_8":
			dialog.text = "Mon père... Mon pauvre, cher père ! Ah, monsieur, je ne vous ai même pas remercié de m'avoir sauvé...";
			link.l1 = "Sélina Je suis simplement heureux que toi et Gilbert soyez sortis vivants de cette grotte. La mort héroïque de ton père n'a pas été vaine.";
			link.l1.go = "Selina_9";
		break;
		
		case "Selina_9":
			dialog.text = "(pleurant) S'il vous plaît, monsieur, emmenez-nous avec vous en ville. Nous devons envoyer chercher les soldats pour qu'ils viennent chercher le corps de mon père, afin qu'il ait un enterrement chrétien digne...";
			link.l1 = "Bien sûr, Céline. Suis-moi !";
			link.l1.go = "Selina_10";
		break;
		
		case "Selina_10":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Selina_11":
			dialog.text = "Merci, monsieur, d'accompagner mon pauvre père... Merci de m'avoir sauvé d'une mort certaine. Je... Je... Tenez, prenez ce sac de doublons. Je l'ai trouvé chez moi dans le coffre de mon père. Je vous en prie, n'osez même pas penser à refuser !";
			link.l1 = "Merci, Celine. Je suis heureux que nous ayons réussi à te sauver. Et mes sincères condoléances pour la perte de ton père.";
			link.l1.go = "Selina_12";
		break;
		
		case "Selina_12":
			TakeNItems(pchar, "gold_dublon", 15);
			PlaySound("interface\important_item.wav");
			dialog.text = "Vous êtes un homme noble, monsieur. Je ne vous oublierai jamais. Adieu !";
			link.l1 = "Adieu, Céline.";
			link.l1.go = "Selina_13";
		break;
		
		case "Selina_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			AddQuestRecord("SharlieF", "8");
			CloseQuestHeader("SharlieF");
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Jilberte":
			PlaySound("Voice\English\other\robinzons-08.wav");
			dialog.text = "Mon Dieu, est-ce vraiment tout derrière nous ? Je n'arrive même pas à y croire... Tu nous as sauvés, moi et Céline. Sans toi, le même sort qui a frappé le malheureux César l'aurait appelée demain et le même m'aurait été réservé dans quelques jours.";
			link.l1 = "Ces Indiens, sont-ils vraiment des cannibales ?!";
			link.l1.go = "Jilberte_1";
		break;
		
		case "Jilberte_1":
			dialog.text = "Vous en doutez ? Si vous avez l'estomac bien accroché, jetez un œil dans les cendres de leur feu de camp. Vous y trouverez le pauvre vieux Cesar. Maintenant, ce ne sont plus que des os rongés...";
			link.l1 = "Sacrement béni... Non, je vais passer. Je viens d'arriver ici d'Europe et je n'aurais jamais pu imaginer que de telles choses diaboliques et infâmes se produisent encore sur Terre.";
			link.l1.go = "Jilberte_2";
		break;
		
		case "Jilberte_2":
			dialog.text = "«Beaucoup de choses étranges se passent aux Caraïbes, des choses dont tu as entendu des murmures dans le Vieux Monde... Hommes-médecine indiens, magie, shamans et rituels secrets. Reste ici plus longtemps et tu seras témoin de toutes sortes de diableries. Mais pardonne-moi, je ne t'ai pas remercié de m'avoir sauvé - je suis encore sous le choc\nTu m'as sauvé la vie et je vais exprimer ma gratitude non seulement en paroles, mais aussi en or. Escorte Céline et moi jusqu'à la ville. Là, je pourrai te remercier comme tu le mérites, monsieur.»";
			link.l1 = "D'accord. Sortez. Je vais d'abord jeter un coup d'œil ici.";
			link.l1.go = "Jilberte_3";
		break;
		
		case "Jilberte_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
			pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;
		
		case "Jilberte_4":
			dialog.text = "Permettez-moi de vous exprimer une fois de plus ma profonde gratitude pour m'avoir sauvé, monsieur ! Comme promis, j'ajoute à ma gratitude verbale une gratitude matérielle sous forme de pesos d'argent et de doublons d'or.";
			link.l1 = "Je suis heureux que tout se soit bien terminé, Gilbert.";
			link.l1.go = "Jilberte_5";
		break;
		
		case "Jilberte_5":
			AddMoneyToCharacter(pchar, 3000);
			TakeNItems(pchar, "gold_dublon", 20);
			Log_Info("You've received 20 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Vous ne pouvez même pas imaginer à quel point je suis heureux de cela ! Merci encore et permettez-moi de prendre congé, monsieur.";
			link.l1 = "Bonne chance, Gilbert ! Au fait, sauriez-vous si quelqu'un d'autre à Saint-Pierre a besoin d'aide ?";
			link.l1.go = "Jilberte_6a";
		break;
		
		case "Jilberte_6a":
			dialog.text = "Je ne sais pas, mais... Vous pouvez demander aux citoyens dans les rues, Monsieur. Les habitants ordinaires, et même ceux qui sont aisés, ne sont guère susceptibles d'offrir quelque chose de digne, mais les nobles riches... ils pourraient avoir un emploi pour vous.";
			link.l1 = "Compris, Gilbert, merci. À bientôt !";
			link.l1.go = "Jilberte_6";
		break;
		
		case "Jilberte_6":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			sld.talker = 9;
			LAi_SetCitizenType(sld);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ecoutez, vous, je suis un citoyen respectueux des lois de cette ville. Je dois vous demander de ne pas vous promener avec votre lame dégainée comme un brigand.","Messire, je vous en prie, la loi est claire : les hommes ne peuvent se promener avec des armes dégainées à l'intérieur des murs de la ville.");
			link.l1 = LinkRandPhrase("D'accord.","Très bien.","Comme vous le souhaitez...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1":
			pchar.questTemp.SMQ.Amulet = "indian_7";
			pchar.questTemp.SMQ.Text = "it adds endurance and gives a second wind.";
		break;
		
		case "HeroType_2":
			pchar.questTemp.SMQ.Amulet = "amulet_7";
			pchar.questTemp.SMQ.Text = "it heightens resilience to battle wounds.";
		break;
		
		case "HeroType_3":
			pchar.questTemp.SMQ.Amulet = "indian_4";
			pchar.questTemp.SMQ.Text = "it raises the attack strength of your weapons.";
		break;
		
		case "HeroType_4":
			pchar.questTemp.SMQ.Amulet = "indian_1";
			pchar.questTemp.SMQ.Text = "it makes fire weaponry much more lethal.";
		break;
	}
}
