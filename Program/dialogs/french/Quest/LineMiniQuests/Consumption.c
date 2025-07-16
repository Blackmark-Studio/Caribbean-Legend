// диалоги по квесту Цена чахотки
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Consumption == "final")
			{
				dialog.text = "Capitaine ! Tu es allé en mer, j'ai entendu dire ! Qu'est-ce qui s'est passé ? As-tu découvert quelque chose ? Je t'en prie, raconte, crache le morceau !";
				if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
				{//взял деньги
					link.l1 = "Non, ma beauté, ce raid a été effectué à la demande de Son Excellence le gouverneur. Je suis vraiment désolé, mais Angelo est mort dans les casemates du fort - il n'y a plus de doute là-dessus. Tiens bon !";
					link.l1.go = "Waitress";
				}
				else
				{//убил Хуана
					if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
					{
						link.l1 = "Tu avais raison. Ton frere a ete kidnappe. Le commandant vendait des prisonniers comme du bétail à un négrier surnommé Consommation. Mais j'ai rattrapé son navire, et maintenant il repose au fond, et ton frère Angelo va bientôt débarquer. Malheureusement, je n'ai pas autant de chaloupes qu'il faudrait pour amener tous les passagers à terre en une seule fois.";
						link.l1.go = "Waitress_2";
					}
					else
					{//отпустил Хуана
						link.l1 = "Tu avais raison. Ton frère a été enlevé. Le commandant vendait des prisonniers comme du bétail à un négrier surnommé Consommation. Mais j'ai rattrapé son navire, bien que j'aie échoué à tuer ce salaud, ton frère Angelo arrivera bientôt à terre. Malheureusement, je n'ai pas autant de chaloupes qu'il en faut pour débarquer tous les passagers en même temps.";
						link.l1.go = "Waitress_2";
					}
					sld = characterFromId("ConAndjelo");
					sld.lifeday = 0;
					RemovePassenger(Pchar, sld);
				}
			}
			else
			{
				dialog.text = "Avez-vous réussi à découvrir quoi que ce soit sur le sort d'Angelo, capitaine ?";
				link.l1 = "Pas encore. Mais je pense que j'aurai des nouvelles bientôt. Vous n'avez qu'à attendre. ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "without_moneysss": // лесник  если Гг нажрался..сволочь:D:D:D
		    dialog.text = "Señor, vous avez promis de retrouver mon frère... Pourquoi perdez-vous votre temps à boire ici ?";
			link.l1 = "Ohh..Ouais, c'est ça..hic... Détends-toi ma fille... Jésus a le contrôle..'gloups'... Jésus a le contrôle. Je suis déjà parti...hic..";
			link.l1.go = "exit";
		break;
		
		case "Servant":
			dialog.text = "Bon après-midi, señor. Quelle est votre affaire ici ?";
			link.l1 = "J'ai apporté une dépêche pour le seigneur commandant, mais je devrais la lui remettre personnellement.";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Alors tu vas le chercher dans le fort.";
			link.l1 = "Cette dépêche est trop importante et ne doit pas tomber sous les yeux et les oreilles des soldats. Peut-être suis-je arrivé trop tôt, mais je peux l'attendre ici. Croyez-moi, c'est très important !";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 40)
			{
				notification("Skill Check Failed (40)", SKILL_SNEAK);
				dialog.text = "Le señor commandant m'avertit généralement de toutes les affaires importantes qui nécessitent de changer la routine... Vous savez, en fait, il m'a averti de ce cas particulier.";
				link.l1 = "Et qu'a-t-il dit ?";
				link.l1.go = "Servant_3";
			}
			else
			{
				notification("Skill Check Passed", SKILL_SNEAK);
				dialog.text = "D'accord, je vous crois. Et je vous croirai encore plus quand le señor commandant arrivera pour confirmer vos paroles. Mais avant cela, je vous garderai constamment à l'œil.";
				link.l1 = "Tu peux me surveiller autant que tu veux...";
				link.l1.go = "Servant_4";
			}
		break;
		
		case "Servant_3":
			dialog.text = "Il m'a dit de faire appel aux gardes de la garnison dans de tels cas. Mais nous allons probablement nous débrouiller nous-mêmes. Les gars ! Éventrons-le !";
			link.l1 = "Putain !";
			link.l1.go = "Servant_fight";
		break;
		
		case "Servant_4":
			DialogExit();
			NextDiag.CurrentNode = "Servant_repeat";
			LAi_SetOwnerType(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Servant_repeat":
			dialog.text = "Que veux-tu d'autre ? As-tu décidé de me transmettre le message ?";
			link.l1 = "Non, j'attendrai le commandant...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Servant_repeat";
		break;
		
		case "Servant_fight":
			int iRank = sti(pchar.rank)+5;
			int iScl = 15 + 2*sti(pchar.rank);
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true;
			for (i=9; i<=11; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Conservant_"+i, "citiz_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//попытка залезть в сундук
		case "Man_FackYou":
			dialog.text = "Tu es un voleur ! Ou peut-être un espion ? Les gars, en bas, vite !";
			link.l1 = "Ah, diable !";
			link.l1.go = "Servant_fight";
		break;
		
		case "Sergio":
			dialog.text = "Excusez-moi, puis-je vous parler ?";
			link.l1 = "Pour être honnête, je suis pressé. Que voulez-vous ?";
			link.l1.go = "Sergio_1";
		break;
		
		case "Sergio_1":
			dialog.text = "J'ai entendu dire que vous vous renseignez sur un homme nommé Juan et une maladie dans notre prison...";
			link.l1 = "En effet, je l'ai fait... pourriez-vous vous expliquer.";
			link.l1.go = "Sergio_2";
		break;
		
		case "Sergio_2":
			dialog.text = "Doucement, doucement ! Calme-toi et ne touche pas à ton épée ! Nous sommes du même côté ici ! Je ne sais pas pourquoi tu te soucierais de nos problèmes, mais cela doit cesser ! Je ne peux plus garder le silence !";
			link.l1 = "Garder le silence? Sur quoi? Que sais-tu de la consommation?";
			link.l1.go = "Sergio_3";
		break;
		
		case "Sergio_3":
			dialog.text = "Je sais beaucoup, sinon tout, et je vais m'expliquer - mais pas ici. Rencontrons-nous le soir, quand les lumières sont éteintes, je suis assistant médical, donc j'ai la permission de quitter le fort. Nous nous retrouverons au-delà des portes de la ville, et je te dirai tout. Je t'en supplie - cesse de poser des questions, avant d'attirer leur attention, si ce n'est déjà fait... Je dois partir maintenant. Souviens-toi, la nuit au-delà des portes de la ville.";
			link.l1 = "D'accord, j'y serai. Hé! Attends...";
			link.l1.go = "Sergio_4";
		break;
		
		case "Sergio_4":
			DialogExit();
			AddQuestRecord("Consumption", "8");
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption3.win_condition.l1 = "location";
			pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
			pchar.quest.Consumption3.win_condition.l2 = "Hour";
			pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
			pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
			pchar.quest.Consumption3.function = "Consumption_MeetSergio";
			pchar.quest.Consumption4.win_condition.l1 = "Timer";
			pchar.quest.Consumption4.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Consumption4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Consumption4.function = "Consumption_FailSergio";
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);//офицеров не пускать
		break;
		
		case "Sergio_5":
			dialog.text = "Dieu merci, tu es là... J'espère que tu n'as pas été suivi ?";
			link.l1 = "Pourquoi ? Vous êtes trop suspicieux, peut-être même plus que le senor commandant, alors vous feriez mieux de passer aux affaires... Que savez-vous de Juan ?";
			link.l1.go = "Sergio_6";
		break;
		
		case "Sergio_6":
			dialog.text = "Mon nom est Sergio Saldo. Je sers comme assistant medical dans notre fort et...";
			link.l1 = "";
			link.l1.go = "Sergio_6_1";
		break;
		
		case "Sergio_6_1":
			dialog.text = "";
			link.l1 = "Attends ! As-tu entendu ça ?";
			link.l1.go = "Sergio_7";
			Play3DSound("lomanie_vetki", -33.25, 1.00, 3.73)
		break;
		
		case "Sergio_7":
			dialog.text = "Quoi?! Où?";
			link.l1 = "Merde, nous ne sommes pas seuls ici... Qui as-tu amené avec toi, raclure ?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;
		
		case "Bandit":
			dialog.text = "Ils nous ont remarqués ! Prends le doc, et je prends l'autre !";
			link.l1 = "...";
			link.l1.go = "Bandit_1";
		break;
		
		case "Bandit_1":
			DialogExit();
			sld = characterFromId("Sergio");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=3; i++)
			{	
				sld = characterFromId("Conbandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Sergio_8":
			dialog.text = "Range ton épée, c'est fini ! Tu as vu par toi-même maintenant qu'ils ont essayé de me tuer aussi !";
			link.l1 = "Eh bien, cela semble trop sophistiqué pour un mauvais coup - donc, vous n'êtes pas avec eux. Où en étions-nous ? Vous êtes médecin de prison, n'est-ce pas ?";
			link.l1.go = "Sergio_9";
		break;
		
		case "Sergio_9":
			dialog.text = "Oui. Je sers comme médecin de prison. J'étudiais la médecine quand j'étais jeune, et il n'y a pas beaucoup de gens instruits ici. C'est pourquoi je sais mieux que quiconque ce qui se passe dans la prison !";
			link.l1 = "Qu'est-ce qui se passe alors ? Et les prisonniers ? Sais-tu quelque chose à propos de leur soudaine disparition.";
			link.l1.go = "Sergio_10";
		break;
		
		case "Sergio_10":
			dialog.text = "Notre commandant les vend... les vend comme du bétail à un esclavagiste nommé Juan. Il choisit ceux qui ne seront pas recherchés - les indigents, les marins de navires au hasard. Et puis ils meurent soudainement de 'consomption' - vous pouvez deviner la suite...";
			link.l1 = "Ce Juan est un humain, après tout ! Que savez-vous de lui ?";
			link.l1.go = "Sergio_11";
		break;
		
		case "Sergio_11":
			dialog.text = "Un peu. Il avait l'habitude de faire ses sales affaires au Maroc avec les pirates berbères, il aime raconter des histoires sur cette époque quand il nous rend visite. C'est là qu'il a obtenu son surnom - Consomption. Je ne veux pas penser à ses origines\nIl vient ici tous les mois et emmène tous les prisonniers à bord.";
			link.l1 = "'Consommation !' Et ils m'ont accusé d'être cynique ! Alors c'est pour ça... Ce señor commandant à toi est un vrai imbécile !";
			link.l1.go = "Sergio_12";
		break;
		
		case "Sergio_12":
			dialog.text = "Si je comprends bien, vous avez besoin de quelqu'un parmi les prisonniers perdus, sinon comment sauriez-vous cette histoire, ai-je raison ? Si c'est le cas, vous devriez vous dépêcher : cette nuit est la dernière de ce mois. J'ai déjà signé les papiers déclarant la mort de trois autres personnes, et Juan lèvera l'ancre demain avant midi, lorsqu'il les recevra !";
			link.l1 = "Qu'as-tu signé ? Je ne te suis pas tout à fait...";
			link.l1.go = "Sergio_13";
		break;
		
		case "Sergio_13":
			dialog.text = "Je devais le faire - comme je le faisais déjà depuis plusieurs mois ! C'est pourquoi je suis venu ici pour arrêter cela. Savez-vous comment est mort le docteur Pinero ? Celui qui soignait les prisonniers avant moi ?";
			link.l1 = "Je crois qu'on m'a dit qu'il est mort de la consomption, n'est-ce pas ? Alors, vous y êtes contraint. Cela est logique - mais pourquoi personne n'a-t-il contacté les autorités à ce sujet ?";
			link.l1.go = "Sergio_14";
		break;
		
		case "Sergio_14":
			dialog.text = "Et qui va croire à ça ? Je n'ai aucune preuve et ces soldats censés garder les prisonniers sont grassement payés, donc ils s'en fichent même s'ils vendent des gens aux Caraïbes comme repas\nPersonne n'en a rien à foutre des prisonniers et c'est un atout dans la main du commandant. Mais tu peux arrêter cela, au moins pour un temps, en éliminant Juan !";
			link.l1 = "Autant que je comprenne, ces gars à terre étaient ses hommes, n'est-ce pas? Comment puis-je le trouver?";
			link.l1.go = "Sergio_15";
		break;
		
		case "Sergio_15":
			dialog.text = "Vous avez probablement attiré l'attention de quelqu'un avec vos questions... Je vous ai dit d'être plus prudent ! Mais cela n'a pas d'importance maintenant. Je ne sais rien du navire de Juan, mais les prisonniers sont toujours envoyés à Galera Point, qui se trouve dans la partie nord de l'île. Je suppose que le navire du négrier devrait être à proximité et vous pourriez le rattraper. Ses messagers ont mentionné aujourd'hui qu'il comptait partir demain à midi.";
			if (!CheckCharacterItem(pchar, "letter_consumption"))
			{
				link.l1 = "Merci, Sergio, tu es un véritable officier et un homme d'honneur. Je vais lever l'ancre sur-le-champ, et je trouverai ce navire infâme. Tu dois retourner au fort avant qu'ils ne commencent à te chercher.";
				link.l1.go = "Sergio_16";
			}
			else
			{
				link.l1 = "Eh bien, c'est tout ce que j'ai besoin de savoir. Je dois lever l'ancre immédiatement si je ne veux pas chercher ce 'Consumption' à travers tout le Nouveau Monde. En attendant, tu peux étudier ça.";
				link.l1.go = "Sergio_17";
			}
		break;
		
		case "Sergio_16":
			dialog.text = "Bonne chance, capitaine ! Ne vous inquiétez pas pour moi - l'essentiel est d'arrêter cela au moins pour un moment. Je vous souhaite bonne chance !";
			link.l1 = "Mes canons sont le meilleur remède contre la maladie et la méchanceté. Je jure que tous les prisonniers seront à terre avant l'aube - et le navire de Juan reposera au fond de la mer !";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_17":
			RemoveItems(PChar, "letter_consumption", 1);
			Log_Info("You have given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Qu'est-ce que c'est ? Voici le nom du colonel et un monogramme 'J' ? Incroyable ! Où l'avez-vous trouvé ?";
			link.l1 = "Tu ferais mieux de ne pas savoir cela, mais je pense que tu l'utiliseras de la meilleure manière possible.";
			link.l1.go = "Sergio_18";
		break;
		
		case "Sergio_18":
			dialog.text = "Je le ferai, je le jure par tout ce qui est sacré ! Le colonel ira à la potence avant la fin du mois ! Je m'en occuperai personnellement !";
			link.l1 = "Je crains que cela ne finisse par une punition disciplinaire, qui, à ce que je crois, ne sera pas la première de sa vie. Peut-être vaut-il mieux abattre ce gredin ? C'est un remède très efficace... Je dois y aller maintenant - je ne veux pas faire attendre 'Consumption'.";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_19":
			DialogExit();
			AddQuestRecord("Consumption", "11");
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption5.win_condition.l1 = "location";
			pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
			pchar.quest.Consumption5.function = "Consumption_CreateJuan";
			pchar.quest.Consumption6.win_condition.l1 = "HardHour";
			pchar.quest.Consumption6.win_condition.l1.hour = 13;
			pchar.quest.Consumption6.function = "Consumption_FailJuan";
			// Сержио теперь наш друг и будет торговать смолами
			SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // таймер
		break;
		
		// генератор торговли смолами
		case "Sergio_20":
			dialog.text = "Oh, quelle rencontre chanceuse ! Senor "+GetFullName(pchar)+" ! Je suis tellement heureux de te voir !";
			link.l1 = "Señor Sergio ! Je ne m'attendais pas à vous rencontrer ! Comment allez-vous ? Comment va le bon vieux commandant ?";
			link.l1.go = "Sergio_21";
		break;
		
		case "Sergio_21":
			dialog.text = "Je vais bien, et le senor commandant est allé aux mines de Los-Teques - ses sales machinations avec Juan Consumption ont été révélées.";
			link.l1 = "Des mines ?! Par mon âme ! Je n'aurais jamais cru que justice serait rendue dans son cas...";
			link.l1.go = "Sergio_22";
		break;
		
		case "Sergio_22":
			dialog.text = "Ah, si seulement c'était le cas, capitaine... Il a juste été transféré et rétrogradé. Il sert maintenant à la garnison, et il n'a même pas été déchu de son grade d'officier. Eh bien, au moins San Jose s'est débarrassé de cette vermine.";
			link.l1 = "Eh bien, jusqu'ici tout va bien. Mais je m'attendais à plus.";
			link.l1.go = "Sergio_23";
		break;
		
		case "Sergio_23":
			dialog.text = "Moi aussi... Mais oublions cette canaille - il ne mérite pas qu'on parle de lui. Señor, dès que j'ai su que votre navire allait entrer au port, je me suis précipité vers le quai avec toute la hâte possible. J'ai une affaire à vous proposer.";
			link.l1 = "Vraiment ? J'écoute.";
			link.l1.go = "Sergio_24";
		break;
		
		case "Sergio_24":
			if (startHeroType == 1) sStr = "French";
			if (startHeroType == 2) sStr = "Spanish";
			if (startHeroType == 3) sStr = "English";
			if (startHeroType == 4) sStr = "English";
			dialog.text = "Capitaine, vous semblez être un homme digne de confiance. Une autre chose très importante est que vous êtes "+sStr+" et vous avez votre propre navire. Je suggere que nous concluions un accord commercial.";
			link.l1 = "Ça semble prometteur ! Quel genre d'accord ?";
			link.l1.go = "Sergio_25";
		break;
		
		case "Sergio_25":
			dialog.text = "Nous ferions mieux de discuter de cela ailleurs - au phare, dans la cabane du gardien. C'est un vieil ami à moi, et j'ai confiance en lui. Venez au phare de San Jose aujourd'hui ou demain. Je vous y attendrai. Je suis sûr que vous trouverez ma proposition des plus intéressantes !";
			link.l1 = "Très bien, señor Sergio. Je vous y retrouverai !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;
		
		case "Sergio_26":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; //снять прерывание
			dialog.text = "Bienvenue encore, señor. Permettez-moi de vous expliquer cette affaire.";
			link.l1 = "Je suis tout ouïe. ";
			link.l1.go = "Sergio_27";
		break;
		
		case "Sergio_27":
			dialog.text = "Comme vous le savez peut-être déjà, je ne suis pas seulement un soldat, mais aussi un médecin. Pourquoi ? Parce que je suis un homme bien éduqué. Mon éducation m'a empêché de perdre mon temps ici avec les femmes et les boissons. Au lieu de cela, j'ai organisé plusieurs expéditions et réussi à trouver un gisement de résine non loin d'ici\nC'est une ressource d'importance stratégique, cette île est le seul endroit où vous pouvez trouver la résine spéciale utilisée pour construire des navires solides et durables\nUn gouverneur et un commandant m'ont ordonné de vendre toute la résine à la marine espagnole\nLe problème est qu'ils me paient la moitié de son prix de marché et je ne peux pas la vendre ailleurs. Par conséquent, je vous propose de l'acheter chez moi. C'est une marchandise très importante et très difficile à obtenir.";
			link.l1 = "Quelles sont les conditions de notre accord ? ";
			link.l1.go = "Sergio_28";
		break;
		
		case "Sergio_28":
			dialog.text = "Selon mes calculs, je pourrai récolter 60 barils par mois sans éveiller de soupçons. Faisons un marché - chaque cinquième jour du mois, je viendrai à ce phare pour boire un coup avec mon ami. Rejoins-nous si tu veux acheter la résine. Dix doublons d'or pour un baril\nTu paies pour tout le lot et tu prends tout d'un coup. Pas de pression, c'est comme tu veux. Alors, marché conclu ?";
			link.l1 = "Ça me semble être une sacrée bonne affaire ! Bien sûr, c'est un marché conclu !";
			link.l1.go = "Sergio_29";
		break;
		
		case "Sergio_29":
			dialog.text = "Magnifique. Alors, le cinq de chaque mois, je boirai une bouteille de vin des Canaries avec mon vieil ami, le gardien, et nous vous attendrons.";
			link.l1 = "Très bien. Faisons-le ainsi.";
			link.l1.go = "Sergio_30";
		break;
		
		case "Sergio_30":
			dialog.text = "Je suis heureux que nous soyons parvenus à un accord. À bientôt, capitaine !";
			link.l1 = "Bonne chance dans votre commerce de résine, señor !";
			link.l1.go = "Sergio_31";
		break;
		
		case "Sergio_31":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			pchar.questTemp.OilTrade = "true";
			pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
			pchar.quest.Oil_fail.function = "Oil_TradeFail";
			AddQuestRecordInfo("Unique_Goods", "4");
		break;
		
		case "oil_trade":
			dialog.text = "Bonjour, senor capitaine ! Vous êtes venu pour un lot de résine, je suppose.";
			link.l1 = "C'est exact, señor Sergio. Tout est-il prêt ?";
			link.l1.go = "oil_trade_1";
			link.l2 = "Señor Sergio, je ne suis pas d'humeur à marchander. Peut-être plus tard.";
			link.l2.go = "oil_trade_exit";
		break;
		
		case "oil_trade_exit":
			DialogExit();
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "oil_trade_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
			{
				dialog.text = "Oui. Avez-vous 2550 doublons avec vous ?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Bien sûr. Voici.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Mauvaise chance ! J'ai oublié l'argent sur mon navire. Je l'apporterai ici immédiatement !";
					link.l1.go = "oil_trade_exit";
				}
			}
			else
			{
				dialog.text = "Oui. As-tu six cents doublons avec toi ?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Bien sûr. Voici.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Pas de chance ! J'ai oublié l'argent sur mon navire. Je l'apporterai ici immédiatement !";
					link.l1.go = "oil_trade_exit";
				}
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && !CheckAttribute(pchar, "questTemp.SergioOilBlock")) // увеличить объём поставок смолами
			{
				link.l4 = "Señor Sergio, je souhaite acheter plus de résine. Pourriez-vous fournir des lots, disons, cinq fois plus importants ?";
				link.l4.go = "UpgradeOil";
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && CheckAttribute(pchar, "questTemp.SergioOilPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок смолами, если в первый раз не принесли
			{
				link.l4 = "Voici, comme promis, Señor Sergio, trois mille doublons, comme vous l'avez demandé. Je suis certain"+GetSexPhrase("","e")+" qu'avec votre prévoyance et mon investissement, cette entreprise nous apportera un profit considérable à tous les deux.";
				link.l4.go = "UpgradeOil_Agreed";
			}
		break;
		
		case "oil_trade_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) RemoveDublonsFromPCharTotal(2550);
			else RemoveDublonsFromPCharTotal(600);
			PlaySound("interface\important_item.wav");
			dialog.text = "C'est un plaisir de traiter avec vous, capitaine. Mes gens vous aideront à charger les barils sur votre navire.";
			link.l1 = "Merci!";
			link.l1.go = "oil_trade_3";
		break;
		
		case "oil_trade_3":
			dialog.text = "L'affaire tient toujours. Si tu as besoin d'un autre lot, reviens dans un mois.";
			link.l1 = "D'accord, Sergio. À bientôt.";
			link.l1.go = "oil_trade_4";
		break;
		
		case "oil_trade_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) AddCharacterGoods(pchar, GOOD_OIL, 300);
			else AddCharacterGoods(pchar, GOOD_OIL, 60);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.SergioOil = sti(pchar.questTemp.SergioOil) + 1; // счётчик покупок
		break;
		
		case "UpgradeOil":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Señor"+GetSexPhrase("","ita")+", votre désir d'acheter plus de résine témoigne sans doute de votre confiance dans notre entreprise. Cependant, une difficulté se présente : avec l'augmentation des volumes, le risque d'attirer l'attention des autorités de l'île grandit, et le contrôle de tels lots nécessite du personnel et des mesures de sécurité qui, je l'avoue, ne sont pas bon marché. Si vous êtes prêt"+GetSexPhrase("","e")+" à ajouter trois mille doublons au prix, en tant que paiement unique, j'embaucherai des personnes fiables, capables de protéger les cargaisons et d'empêcher les fuites d'informations. Notre itinéraire deviendra alors plus sûr, et je pourrai vous fournir trois cents barils de résine par mois. Pour compenser votre investissement, je vous offrirai, en tant qu'acheteur en gros, une remise de quinze pour cent sur tous les lots futurs.";
				link.l1 = "Trois mille doublons pour sécuriser les livraisons ? Señor Sergio, je ne vous cache pas que ce prix me semble incroyable - comme si vous me proposiez de monter une conspiration à l'Escorial plutôt que de simplement sécuriser la cargaison de résine !";
				link.l1.go = "UpgradeOil_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Señor"+GetSexPhrase(" ","ita")+", j'apprécie votre intérêt, mais de telles transactions importantes exigent de l'expérience et de la prudence. À vrai dire, votre niveau dans les affaires commerciales n'est pas encore assez élevé pour gérer un tel volume. Je vous conseille d'acquérir encore un peu d'expérience et de revenir me voir lorsque vous serez prêt"+GetSexPhrase("","e")+" pour des lots plus importants. Alors, peut-être, nous discuterons de l'affaire en profondeur.";
				link.l1 = "Très bien. Nous reviendrons sur cette question plus tard.";
				link.l1.go = "oil_trade_exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeOil_1":
			dialog.text = "Señor"+GetSexPhrase("","ita")+", je comprends votre inquiétude. Mais vous savez que la sécurité n'est jamais bon marché, surtout quand il s'agit d'une marchandise aussi rare. De plus, non seulement je vous garantis l'absence de fuites, mais je suis également prêt à vous offrir une remise qui compensera votre investissement avec le temps. N'est-ce pas un compromis raisonnable ?";
			link.l1 = "J'admets : dans notre domaine, la fiabilité et le secret coûtent cher, et la remise rend notre affaire potentielle un peu plus attrayante. Mais tout de même, trois mille doublons, c'est une somme excessive. Peut-être pourriez-vous la réduire un peu ?";
			link.l1.go = "UpgradeOil_2";
		break;
		
		case "UpgradeOil_2":
			dialog.text = "Je regrette, mais les demi-mesures sont inacceptables dans ce genre d'affaires. Soit nous assurons une protection complète, soit nous risquons tout. La somme reste la même, et c'est seulement ainsi que je peux garantir la fiabilité et la confidentialité. Vous ne voudriez pas que toute la flotte royale me pourchasse d'abord, puis vous ensuite, n'est-ce pas ?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Très bien, Señor Saldo, vous m'avez convaincu. La sécurité et la fiabilité valent leur prix. Trois mille doublons. Les voici.";
				link.l1.go = "UpgradeOil_Agreed";
			}
			link.l2 = "Señor Saldo, vous m'avez convaincu de la nécessité de ces mesures. Cependant, trois mille doublons est une somme considérable, et je ne l'ai pas pour le moment. Je devrai attendre un peu, jusqu'à ce que j'aie réuni la quantité nécessaire.";
			link.l2.go = "UpgradeOil_4";
			link.l3 = "Pour une telle somme, on pourrait soudoyer une flotte entière et tous les soldats du continent, sans parler de gardes pour une modeste cargaison de résine ! Je m'excuse, mais je ne peux pas accepter une telle offre. Laissons tout comme c'est, sans excès ni dépenses supplémentaires.";
			link.l3.go = "UpgradeOil_3";
		break;
		
		case "UpgradeOil_Agreed":
			dialog.text = "Eh bien, Señor"+GetSexPhrase("","ita")+", je vois que notre confiance est mutuelle. Soyez assuré"+GetSexPhrase("","e")+" : l'affaire sera organisée comme il se doit. Passons aux détails : 300 barils de résine, comme d'habitude, vous attendront ici, au phare de Trinidad, le 5 de chaque mois. Vous pourrez acquérir tout le lot pour 2550 doublons.";
			link.l1 = "Magnifique, Señor Sergio. Ne me décevez pas.";
			link.l1.go = "UpgradeOil_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "4_1");
			pchar.questTemp.UpgradeOil = true;
			pchar.questTemp.SergioOilBlock = true;
			DeleteAttribute(pchar, "questTemp.SergioOilPotom");
		break;
		
		case "UpgradeOil_Agreed_1":
			dialog.text = "N'ayez aucun doute, Señor"+GetSexPhrase("","ita")+". Tout sera organisé au plus haut niveau, et notre effort commun portera ses fruits.";
			link.l1 = "À bientôt.";
			link.l1.go = "oil_trade_exit";
		break;
		
		case "UpgradeOil_3":
			DialogExit();
			pchar.questTemp.SergioOilBlock = true;
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "UpgradeOil_4":
			dialog.text = "Revenez quand vous aurez la somme complète. Je serai heureux de conclure une nouvelle affaire avec vous.";
			link.l1 = "D'accord.";
			link.l1.go = "oil_trade_exit";
			pchar.questTemp.SergioOilBlock = true;
			pchar.questTemp.SergioOilPotom = true;
		break;
	// <-- генератор смол
		
		case "Juan_abordage":
			dialog.text = "Qui diable es-tu !?";
			link.l1 = "Mon nom est "+GetFullName(pchar)+", quant à toi, la Consomption, le diable t'attend - et il aura ton âme très bientôt !";
			link.l1.go = "Juan_abordage_1";
		break;
		
		case "Juan_abordage_1":
			if (CheckAttribute(pchar, "questTemp.Consumption.House"))
			{
				dialog.text = "Ce navire va exploser - une mèche brûle déjà dans la soute à poudre - pourquoi devrions-nous mourir tous les deux ? Baissons les épées. Tu auras le temps de sortir, et moi je sauterai du navire, Galera Point est à un jet de pierre d'ici. Si tu as besoin d'or, prends-le ! Cinq cents doublons, comptant sur le clou - et tu m'oublies, et je t'oublie ! Marché conclu ?";
				link.l1 = "L'or ? J'ai commencé tout cela non pas pour l'argent, Juan, mais pour tuer la vermine, et tu es la plus grande récompense en soi.";
				link.l1.go = "Juan_abordage_2";
				link.l2 = "Cinq cents doublons ? Tu te moques de moi, Consommation. Je pense que tu as empilé ici au moins deux fois plus... Donne-moi mille tout de suite et tu peux aller au diable, sinon...";
				link.l2.go = "Juan_abordage_3";
			}
			else
			{
				dialog.text = "Le navire est sur le point d'exploser, donc je vais avoir bonne compagnie, qu'en penses-tu?";
				link.l1 = "Tu parles trop, Consumption, passons aux choses sérieuses !";
				link.l1.go = "Juan_abordage_5";
			}
		break;
		
		case "Juan_abordage_2":
			dialog.text = "Nous aurions pu avoir un accord... Eh, peu importe!";
			link.l1 = "Tu as sorti ces pauvres gens de leurs cellules, et ils ne pouvaient ni résister ni s'enfuir. Tu es un lâche, Consumption, et tu mourras comme un lâche maintenant.";
			link.l1.go = "Juan_abordage_5";
		break;
		
		case "Juan_abordage_3":
			dialog.text = "Tu as le sens des affaires, ami... Tiens - c'est tout ce que j'ai. Pas grand-chose pour une vie, n'est-ce pas ?";
			link.l1 = "Ta vie ne vaut pas une balle, donc il semble que ce soit l'affaire la plus rentable de ma vie. Maintenant, dégage.";
			link.l1.go = "Juan_abordage_4";
			TakeNItems(pchar, "gold_dublon", 1000);
			Log_Info("You received 1000 doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			OfficersReaction("bad");
			pchar.questTemp.Consumption.TakeMoney = "true"; //атрибут для диалога
		break;
		
		case "Juan_abordage_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;
		
		case "Juan_abordage_5":
			dialog.text = "Il est dommage que tu n'auras pas le temps de sauver tout le monde et de me tuer, n'est-ce pas ? La mèche brûle, et le temps passe...";
			link.l1 = "Sacré bleu ! Je dois faire sortir les gens d'ici... Dégage, racaille - tu auras ce que tu mérites tôt ou tard !";
			link.l1.go = "Juan_abordage_4";
			link.l2 = "Je vais essayer quand même...";
			link.l2.go = "Juan_abordage_6";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
			sld.name = "Angelo";
			sld.lastname = "";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
		break;
		
		case "Juan_abordage_6":
			//LAi_SetCurHPMax(NPChar);
			//LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Consumption.KillJuan = "true"; //атрибут для диалога
		break;
		
		case "Waitress":
			dialog.text = "Ah... Je suis sans voix... Quel cauchemar !";
			link.l1 = "Hélas, je n'ai rien pu faire. Je suis désolé, ma fille. Adieu.";
			link.l1.go = "Waitress_1";
		break;
		
		case "Waitress_1":
			DialogExit();
			AddQuestRecord("Consumption", "16");
			AddQuestUserData("Consumption", "sSex", GetSexPhrase("",""));
			Consumption_Close();
		break;
		
		case "Waitress_2":
			dialog.text = "Inouï ! Vous... l'avez-vous vraiment sauvé ? Je n'ai aucune idée de comment vous remercier.";
			if (CheckAttribute(npchar, "quest.Consumption.sex"))
			{
				link.l1 = "Je peux l'imaginer, beauté. Mais ma part du marché est accomplie maintenant - il ne reste qu'une petite chose.";
				link.l1.go = "Waitress_3";
			}
			link.l2 = "Le devoir m'a appelé - et j'ai agi. C'est tout.";
			link.l2.go = "Waitress_5";
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan")) AddQuestRecord("Consumption", "18");
			else AddQuestRecord("Consumption", "17");
		break;
		
		case "Waitress_3":
			dialog.text = "Je... oh Dieu! Vous avez raison. Pour lui, comme je l'avais promis... Montez à l'étage dans la chambre - nous n'avons pas beaucoup de temps.";
			link.l1 = "Dépêchons-nous, alors !";
			link.l1.go = "Waitress_4";
		break;
		
		case "Waitress_4"://благодарность натурой
			DialogExit();
			LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
			pchar.questTemp.Consumption.Sex = "true";
		break;
		
		case "Waitress_sex":
			dialog.text = "Me voici, mon brave caballero! Et regarde ce que j'ai apporté avec moi.";
			link.l1 = "Eh bien, je suis impressionné, ouvrons ce vin de cerise ! Ensuite, nous ouvrirons autre chose... C'est ton jour de chance après tout... Ha-ha !";
			link.l1.go = "Waitress_sex_1";
		break;
		
		case "Waitress_sex_1":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;
		
		case "Waitress_5":
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			{
				dialog.text = "Vous êtes un vrai chevalier ! Caballero ! Prenez-le - ne le prenez pas comme une insulte, mais je veux que vous l'acceptiez. J'ai rassemblé cet argent pour libérer Angelo, mais maintenant cela n'a plus d'importance ! Je vous en prie, ne refusez pas - acceptez-le !";
				link.l1 = "Eh bien, je me souviendrai de vos yeux, señorita - ils sont tellement plus beaux lorsqu'ils brillent des larmes de bonheur et non de douleur. J'accepte votre cadeau. Adieu, et bonne chance à vous et à Angelo.";
				link.l1.go = "Waitress_6";
				AddMoneyToCharacter(pchar, 5000);
			}
			else
			{
				dialog.text = "Tu es un vrai chevalier ! Caballero ! Je le dirai à tout le monde ! Je me souviendrai toujours de toi !";
				link.l1 = "Eh bien, et je me souviendrai de vos yeux, señorita - ils sont tellement plus beaux quand ils brillent des larmes de bonheur et non de douleur. Puissiez-vous toujours être heureuse. Adieu !";
				link.l1.go = "Waitress_6";
			}
		break;
		
		case "Waitress_6":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			Consumption_Close();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
