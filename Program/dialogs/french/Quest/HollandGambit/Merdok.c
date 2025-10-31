// Джон Мердок, он же Йохан ван Мерден, соратник Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = "Monsieur, vous avez choisi un sacré mauvais moment pour bavarder. Toute la garnison est à votre recherche. Vous feriez mieux de déguerpir fissa...";
			link.l1 = "Ne t'inquiète pas. Je ne resterai pas longtemps.";
			link.l1.go = "exit";
			break;
		}
		// продажа алхимического набора, если провалил гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail" , 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = "Bienvenue, capitaine. Seriez-vous intéressé par une offre intrigante ? ";
				link.l1 = "Toutes sortes de gens ici semblent avoir de telles propositions, et je suis un homme curieux. Qu'est-ce que c'est ? ";
				link.l1.go = "alchemy";
				break;
			}
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = "Bonjour. Bienvenue dans mon apothicaire. J'ai des remèdes pour traiter la plupart des maladies et infirmités. Que puis-je vous offrir ?";
			link.l1 = "Écoute, John, il y a des rumeurs selon lesquelles quelqu'un vivrait chez toi au deuxième étage...";
			link.l1.go = "guardoftruth";
			break;
		}
//-----------------------------------------за Голландию------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Bonne journée. Je suis heureux de vous voir dans mon apothicairerie. J'ai des remèdes pour traiter la plupart des maladies et infirmités. Que puis-je vous offrir?";
				link.l1 = "Bonjour Monsieur Murdock. Je suis ici de la part de Lucas Rodenburg. Il m'a envoyé pour discuter d'une affaire concernant Richard Fleetwood.";
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Bon après-midi. Quel genre de problème avez-vous ? J'ai à la fois un mélange pour la toux et une poudre pour la diarrhée !";
				link.l1 = "Bonjour, Monsieur Murdock. Je suis ici de la part de Lucas Rodenburg. Il m'a envoyé vous voir pour discuter d'une affaire concernant Richard Fleetwood.";
				link.l1.go = "Knippel";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = "Ahhh, voici le chien de Rodenburg... Hercule, Longway - pourriez-vous venir ici?\nTuez cet homme!";
				link.l1 = "Attendez, j'ai une ordonnance !";
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = "Bon après-midi. Je suis heureux de vous voir dans ma pharmacie. J'ai des remèdes pour traiter la plupart des maladies et infirmités. Que puis-je vous offrir ?";
			link.l1 = "Rien pour le moment, merci. Je me sens assez bien.";
			link.l1.go = "exit";
			break;
		}
//----------------------------------------------за Англию---------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
			{
			dialog.text = "Bonjour, invité inopportun. Vous ne cachez pas votre visage avec un masque et ne ressemblez pas à un brigand. Par conséquent, j'en conclus que vous avez besoin d'autre chose d'un pauvre apothicaire. Peut-être quelque chose pour la diarrhée ?";
			link.l1 = "Bonjour à toi aussi, Johan van Merden. Je t'apporte les salutations d'Hercule Tonzag. Je vois que tu connais ce nom.";
			link.l1.go = "Merdok_talk";
			DelLandQuestMark(npchar);
			break;
			}
//--------------------------------------------против всех--------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
				{
					dialog.text = "Ah, te voilà. Eh bien, as-tu rencontré Hercule ? ";
					link.l1 = "Oui. Nous sommes parvenus à un accord. John, je vais aider Hercule, et j'ai plusieurs questions à te poser concernant Richard Fleetwood.";
					link.l1.go = "About_Fleetwood";
					break;
				}
				if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
				{
					dialog.text = "Bonjour ! Je suis ravi de te voir, "+pchar.name+" !";
					link.l1 = "Bonjour, John. As-tu découvert quelque chose sur Fleetwood ?";
					link.l1.go = "About_Fleetwood_9";
					pchar.quest.Wait_FleetwoodOver.over = "yes"; //снять таймер
					break;
				}
				if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
				{
					dialog.text = "Tu es en retard. L'oiseau s'est envolé. Charlie Knippel a visité Willemstad et a ramené une fille de là-bas pour Richard. Maintenant, ils voguent vers l'Angleterre avec un escadron militaire d'ici un jour ou deux. Fleetwood est parti, tu ne le reverras jamais dans cette vie.";
					link.l1 = "Bon sang. J'avais complètement oublié Richard et perdu la notion du temps. À plus tard.";
					link.l1.go = "About_Fleetwood_17";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
				{
					dialog.text = "Bienvenue, "+pchar.name+"! Rien pour toi pour l'instant. Il n'y a pas de nouvelles de Fleetwood, et Charlie Knippel n'est pas encore revenu de Curacao...";
					link.l1 = "Et il ne le fera jamais. Ni lui, ni son brigantin.";
					link.l1.go = "Abigile";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
				{
					dialog.text = "Ah, nous avons des invités ! Bonjour, Charlie ! Bonjour, Mademoiselle !";
					link.l1 = "Bon après-midi, John ! Permets-moi de te présenter ma compagne, la fiancée de Richard, la charmante Abigail Shneur.";
					link.l1.go = "Abigile_7_1";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
				{
					dialog.text = "Parle plus bas... Que comptes-tu faire ensuite ?";
					link.l1 = "Ensuite? Je préférerais dormir un peu, mais malheureusement, je n'ai pas le temps pour ça. Je vais dénicher Fleetwood du trou où il se cache et terminer le travail d'Hercule.";
					link.l1.go = "Abigile_9";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
				{
					dialog.text = "Tu as fini d'écrire ? Laisse-moi voir... Mon Dieu Charlie, tu es un vrai fou ! Ne penses-tu pas que tu as rendu cela un peu trop détaillé ? Je veux dire, la partie sur les doigts, les oreilles et le visage de Mademoiselle Shneur ? Tu as un talent malsain, c'est certain. Bon sang, je vais perdre mon déjeuner !";
					link.l1 = "Je bluffe, John. Je ne tuerai pas la fille. Je pourrais lui faire perdre un doigt... Mais rien de plus. Elle en a encore neuf après tout.";
					link.l1.go = "Abigile_15";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
				{
					dialog.text = "Est-ce que ça s'est bien passé ? Je le vois dans tes yeux - tu l'as fait !";
					link.l1 = "Oui. Fleetwood a accepté mes conditions. Les mâchoires du piège se referment. Maintenant, nous attendons.";
					link.l1.go = "Abigile_23";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
				{
					dialog.text = "Ah,   bienvenue de retour, mon ami !   Que peux-tu me raconter ?";
					link.l1 = "Fleetwood est mort. Tout s'est déroulé selon le plan. Il est arrivé sur l'île, où j'avais organisé une embuscade sur la plage. Il s'est bien défendu, mais cela ne lui a servi à rien. Un seul d'entre nous a quitté cette plage.";
					link.l1.go = "Abigile_27";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "MeetTonzag")
				{
					dialog.text = "D'accord "+pchar.name+", j'ai une offre sérieuse pour vous. L'affaire dont je vais parler est très dangereuse, mais, compte tenu de la façon dont vous vous êtes débarrassé de Fleetwood, je suis sûr que vous pouvez la gérer. Vous avez un... don rare pour résoudre des problèmes difficiles.";
					link.l1 = "Je suis flatté. Continuez à parler.";
					link.l1.go = "Lucas";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Bon retour, "+pchar.name+"Des bonnes nouvelles pour moi ?";
					link.l1 = "Jean, désormais tu peux dormir sans couteau sous l'oreiller. Lucas ne te menace plus. Il est arrêté et enfermé, et il sera bientôt envoyé en Hollande, où il sera jugé pour insurrection, tentative de meurtre, et autres méfaits.";
					link.l1.go = "Lucas_10";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Ravi de te voir, "+pchar.name+"! Tu es vivant - et c'est une bonne chose. Des nouvelles?";
					link.l1 = "Oui. Van Berg est parti pour de bon. Comme tu l'avais dit, il m'a traqué et attaqué au moment le plus inopportun. Van Berg était un dur à cuire, mais à la fin, je l'ai brisé.";
					link.l1.go = "Final";
					break;
				}
			dialog.text = "Vous avez besoin de quelque chose d'autre ?";
			link.l1 = "Non, John, rien. Je m'en vais.";
			link.l1.go = "exit";
			break;
			}
			dialog.text = "Bonjour. Je suis heureux de vous voir dans ma droguerie. J'ai des remèdes pour traiter la plupart des maladies et infirmités. Que puis-je vous offrir ?";
			link.l1 = "Rien pour le moment, merci. Je me sens assez bien.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------за Голландию-----------------------------------------------------
		case "Knippel_exit":
			dialog.text = "Je n'ai aucune idée de ce dont vous parlez, monsieur. Quel Lucas Rodenburg ? Je n'ai aucun commerce avec les Hollandais. Vous devez faire erreur.";
			link.l1 = "Quoi? Mynheer Rodenburg m'a envoyé vers vous!";
			link.l1.go = "Knippel_exit_1";
		break;
		
		case "Knippel_exit_1":
			dialog.text = "Permettez-moi de vous dire encore une fois - je ne connais aucun homme nommé Mynheer Rodenburg. Quant aux Hollandais, je ne traite pas avec eux. Il n'y a que deux choses que je ne supporte pas dans ce monde : les gens qui sont intolérants envers les cultures des autres, et les Hollandais. Alors si vous n'avez pas besoin de médicaments, s'il vous plaît, laissez-moi faire mon travail.";
			link.l1 = "De plus en plus curieux...";
			link.l1.go = "exit";
		break;

		case "Knippel":
			dialog.text = "Eh bien, eh bien... Êtes-vous de la part de Monsieur Rodenburg ? Très bien. Je vous écoute.";
			link.l1 = "Je dois organiser une rencontre avec le capitaine Fleetwood dans un endroit isolé. J'ai emprunté le 'Mirage' à Jacob van Berg, le corsaire hollandais que M. Fleetwood veut capturer à tout prix. Je voudrais l'informer que le 'Mirage' sera commodément à l'arrêt au large des côtes de la Dominique dans un avenir proche.";
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			dialog.text = "A-t-il donné son navire à Jacob ? Hum, alors maintenant vous avez besoin de quelqu'un pour dire à Monsieur Fleetwood que le 'Mirage' sera bientôt au large de la Dominique, puisque vous ne pouvez pas en parler vous-même à Richard pour des raisons particulières...";
			link.l1 = "Exactement. Mynheer Rodenburg m'a recommandé de m'adresser à vous pour cette affaire.";
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			dialog.text = "Dans ce cas, Charlie Knippel est l'homme qu'il vous faut. Un ami loyal de Fleetwood... et son espion. Parlez-lui et mentionnez tout ce que vous voulez que Richard sache. Soyez prudent, Knippel peut sembler assez simple, mais il n'est pas idiot.\nVous pouvez le trouver dans une petite cabane, non loin du rivage. Il doit être là.";
			link.l1 = "Je vois. Merci, Monsieur Murdock. Adieu!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "toKnippel";
			AddQuestRecord("Holl_Gambit", "1-16");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		break;
		
		case "Merdok_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			sld = characterFromId("Tonzag");
			PlaySound("Voice\English\hambit\Ercule Tongzag-04.wav");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//а вот и китаец нарисовался
			sld = characterFromId("Longway");
			LAi_SetWarriorType(sld);
			FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy"))//враг
			{
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend"))//друг
			{
				LAi_warrior_DialogEnable(sld, true);
				sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				sld.dialog.currentnode = "Longway_hire";
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral")) sld.lifeday = 0;//нейтрал - просто нет
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------------------за Англию-----------------------------------------------------
		case "Merdok_talk":
			dialog.text = "Vraiment ? Je pensais que ce pauvre Gaston brûlait en enfer depuis un bon moment déjà.";
			link.l1 = "Peut-être bien, mais il n'y a clairement personne comme Gaston. J'ai trouvé sa tête dans le trésor d'un vieux juif sur l'île secrète. Mais il a quand même réussi à t'envoyer ses salutations. Il a également mentionné que nous avons un ennemi commun : M. Rodenburg. Tonzag a dit que tu pourrais avoir des papiers importants pour Lucas qui pourraient le faire sortir de sa cachette à Curaçao.";
			link.l1.go = "Merdok_talk_1";			
		break;
		
		case "Merdok_talk_1":
			dialog.text = "Il avait raison. C'est mon archive qui empêche Rodenburg de dormir la nuit. Il semble qu'il traîne encore ici uniquement à cause d'elle. Le fait est qu'on lui a promis un poste tranquille au Comité des Directeurs de la Compagnie dans les Provinces-Unies. Si les informations contenues dans cette archive, qui renferme beaucoup de choses intéressantes sur le passé et le présent de Lucas, deviennent largement connues, ses aspirations de carrière seront anéanties. Dans ce cas, le mieux qu'il puisse espérer est d'être décapité au lieu d'être pendu.";
			link.l1 = "Donne-moi les archives, et je m'occuperai de notre ennemi.";
			link.l1.go = "Merdok_talk_2";			
		break;
		
		case "Merdok_talk_2":
			dialog.text = "Tu dois me prendre pour un idiot. Je suis encore en vie seulement parce que je l'ai toujours avec moi. Comment savoir que tu ne travailles pas pour Lucas maintenant ?";
			link.l1 = "Vous devrez me croire sur parole - ou mourir.";
			link.l1.go = "Merdok_talk_3";			
		break;
		
		case "Merdok_talk_3":
			PlaySound("Voice\English\hambit\John Mardock-07.wav");
			dialog.text = "Mauvaise réponse, tu vas mourir ici et maintenant ! Longway, gongji !";
			link.l1 = "Oh ho, le Chinois sort de l'ombre ! Pas de soucis, je vais vous transformer tous les deux en chop suey !";
			link.l1.go = "Merdok_fightEng";			
		break;
		
		case "Merdok_fightEng":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");	
			sld = characterFromId("Longway");
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			PlaySound("Voice\English\hambit\Longway-02.wav");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//----------------------------------------против всех-------------------------------------------------------
		case "MC_InHouse":
			PlaySound("Voice\English\hambit\John Mardock-02.wav");
			dialog.text = "Enfin, te voilà sur pied. J'avais peur que tu ne te réveilles pas.";
			link.l1 = "Quoi...? Qui êtes-vous ? Où diable suis-je ? Comment suis-je arrivé là ?";
			link.l1.go = "MC_InHouse_1";	
		break;
		
		case "MC_InHouse_1":
			dialog.text = "Calmez-vous, ne posez pas autant de questions à la fois, cela ne vous fait pas de bien de vous exciter ainsi. Je m'appelle John Murdock, je suis apothicaire ici à St. John's. Vous aviez perdu connaissance lors d'une rixe avec les hommes de Fleetwood. Je dois dire qu'ils vous ont bien amoché... C'est Hercule qui vous a amené ici dans ma pharmacie, et, eh bien, j'ai soigné vos blessures avec mes potions et remèdes.";
			link.l1 = "Hercule? Qui? L'homme qui est venu m'aider dans la rue? ";
			link.l1.go = "MC_InHouse_2";			
		break;
		
		case "MC_InHouse_2":
			dialog.text = "Oui. C'est lui. Au fait, il aimerait vous parler. Vous devez le rencontrer en ville. Pouvez-vous encore marcher ? Bien. Sortez la nuit - utilisez le tunnel secret qui commence derrière la porte au rez-de-chaussée de ma maison. Ne sortez pas avant la tombée de la nuit - les hommes de Fleetwood vous cherchent.";
			link.l1 = "Oui... Où est mon navire ?";
			link.l1.go = "MC_InHouse_3";			
		break;
		
		case "MC_InHouse_3":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Votre navire a été saisi et votre équipage dispersé par crainte d'être tué par les hommes de Fleetwood. Je suis désolé.";
				link.l1 = "Merde...";
			}
			else
			{
				dialog.text = "Elle est au port, à sa place habituelle.";
				link.l1 = "Ouf... c'est bon d'entendre ça. Je pensais que je l'avais perdue.";
			}
			link.l1.go = "MC_InHouse_4";			
		break;
		
		case "MC_InHouse_4":
			dialog.text = "Vous devriez rencontrer Hercule. Allez en ville la nuit par le tunnel secret. Il vous abordera. Maintenant reposez-vous, et je dois retourner à mon travail.";
			link.l1 = "D'accord, John. Et... merci pour ton aide et tes soins !";
			link.l1.go = "MC_InHouse_5";
		break;
		
		case "MC_InHouse_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			npchar.greeting = "merdok_2";
			AddQuestRecord("Holl_Gambit", "3-12");
			pchar.questTemp.HWIC.Self = "MainBegin";//новый флаг квеста
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.greeting = "barmen_1";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);//закрыть выход из аптеки через дверь
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//открыть подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//открыть дом из подземелья
			pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
			pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
			pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
			pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);	
		break;
		
		case "About_Fleetwood":
			DelLandQuestMark(npchar);
			dialog.text = "Fleetwood ? Que veux-tu savoir à son sujet ?";
			link.l1 = "Tout. Dis-moi tout ce que tu sais. Il me semble que ce n'est pas un secret pour toi pourquoi Hercule est venu à Antigua. Je suis de son côté.";
			link.l1.go = "About_Fleetwood_1";
		break;
		
		case "About_Fleetwood_1":
			dialog.text = "Très bien. Capitaine Richard Fleetwood de la Marine Royale- je veux dire la Marine du Commonwealth... bon sang, j'oublie toujours que ce fanatique de Cromwell est aux commandes et a changé le nom. Quoi qu'il en soit, Fleetwood est un bon combattant et un marin chevronné. Il commande une brigantine appelée 'Valkyrie' - un navire excellent, je voudrais mentionner, avec un équipage de marins et de soldats d'élite. Il mène une guerre privée contre les Provinces-Unies en général et contre la Compagnie néerlandaise des Indes occidentales en particulier. Il a pillé d'innombrables navires marchands néerlandais et a fait grimper le coût de l'assurance en flèche. Le gouverneur de Curaçao a mis une prime record sur sa tête.";
			link.l1 = "Hmm... Cela semble un peu inhabituel pour un officier de la 'Marine du Commonwealth' de se lancer dans la piraterie...";
			link.l1.go = "About_Fleetwood_2";
		break;
		
		case "About_Fleetwood_2":
			dialog.text = "Oui, en effet. Il marche sur une corde raide. Les Anglais ne reconnaissent pas officiellement ses actions et refusent d'y être mêlés, mais ils l'encouragent en coulisses. J'ai des raisons de supposer qu'il est d'une manière ou d'une autre lié au réseau d'espions anglais dans les Caraïbes, et ces vauriens ne sont pas à prendre à la légère.";
			link.l1 = "Un homme sérieux... C'est tout ? Hercule m'a parlé d'un de ses assistants... un autre Charlie... comment s'appelle-t-il... Canister ? Boulet de canon ?";
			link.l1.go = "About_Fleetwood_3";
		break;
		
		case "About_Fleetwood_3":
			dialog.text = "Knippel ? Oui, il y a bien un type comme ça. Charlie Knippel était autrefois maître canonnier dans la marine anglaise, maintenant à la retraite. Il mène maintenant une vie tranquille sur la côte. Il est les yeux et les oreilles de Fleetwood à St. John's, alors soyez prudent avec lui et n'envisagez même pas de le questionner sur Richard - vous finirez en prison ou pire.";
			link.l1 = "Je vois. Peux-tu me dire autre chose qui vaille la peine d'être mentionné à propos de Fleetwood ?";
			link.l1.go = "About_Fleetwood_4";
		break;
		
		case "About_Fleetwood_4":
			dialog.text = "Un idole pour toutes les femmes d'Antigua de seize à soixante ans. On dirait que c'est tout ce qu'il y a à savoir sur lui. Eh bien, je pense que vous savez ce qui lui est arrivé maintenant. Il reste au lit et lèche ses plaies.";
			link.l1 = "Il doit bien avoir quelques points faibles ou vices...";
			link.l1.go = "About_Fleetwood_5";
		break;
		
		case "About_Fleetwood_5":
			dialog.text = "Que veux-tu dire ?";
			link.l1 = "Eh bien, peut-être qu'il aime jouer ou qu'il boit beaucoup ou qu'il ne peut pas résister au beau sexe - quelque chose dans ce genre. Est-il marié ?";
			link.l1.go = "About_Fleetwood_6";
		break;
		
		case "About_Fleetwood_6":
			dialog.text = "Non, un célibataire. Quant aux choses que vous avez mentionnées - il n'est connu pour aucune d'elles.";
			link.l1 = "Je vois. Mais peut-être y a-t-il encore quelque chose de spécial chez lui ? Même une personne comme lui doit avoir quelques points faibles !";
			link.l1.go = "About_Fleetwood_7";
		break;
		
		case "About_Fleetwood_7":
			dialog.text = "Je ne sais pas. Écoute, faisons ainsi. Reviens me voir dans une semaine, et j'enquêterai sur la vie privée de Fleetwood. D'accord ?";
			link.l1 = "Marché conclu. Merci, John ! Je serai ici dans une semaine.";
			link.l1.go = "About_Fleetwood_8";
		break;
		
		case "About_Fleetwood_8":
			DialogExit();
			pchar.questTemp.HWIC.Self = "WaitFleetwood";
			SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
			SetFunctionTimerCondition("Wait_FleetwoodQM", 0, 0, 7, false);
			SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);//чтобы не опаздывал
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);//открыть выход из аптеки
			AddQuestRecord("Holl_Gambit", "3-14");
		break;
		
		case "About_Fleetwood_9":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Oui, mais pas beaucoup, malheureusement. Et j'ai bien peur que cela ne serve pas à grand-chose, de toute façon.";
			link.l1 = "Crache le morceau ! Chaque petit détail est très important s'il a un rapport avec Fleetwood.";
			link.l1.go = "About_Fleetwood_10";
		break;
		
		case "About_Fleetwood_10":
			dialog.text = "Il n'y a pas si longtemps, Richard a recueilli deux réfugiés juifs d'une île inconnue - un vieil homme et sa fille, naviguant vers Willemstad. Le navire sur lequel ils naviguaient a été coulé par des pirates. Fleetwood les a secrètement amenés à Curaçao, risquant son propre cou. Cela fait plusieurs mois depuis lors. Maintenant, il a envoyé son fidèle chien Charlie Knippel à Willemstad...";
			link.l1 = "Hmm... Comment est-ce relié ?";
			link.l1.go = "About_Fleetwood_11";
		break;
		
		case "About_Fleetwood_11":
			dialog.text = "J'ai réussi à apprendre que Charlie a reçu l'ordre de livrer ici une fille de Willemstad, une juive appelée Abigail Shneur. Oui, la même fille de l'île. On dirait que Richard est tombé amoureux d'elle, puisqu'il envoie son meilleur agent pour elle.\nVoilà. Je ne sais pas si cela aide du tout.";
			link.l1 = "Oh ho ho ! Hahaha ! Il semble que notre célibataire endurci soit tombé sous le charme rusé de la Juive. C'est un excellent travail, John, merci ! Maintenant, quand notre ami Knippel partira-t-il pour Curaçao ?";
			link.l1.go = "About_Fleetwood_12";
		break;
		
		case "About_Fleetwood_12":
			dialog.text = "Il est parti hier.";
			link.l1 = "Et sur quel navire ?";
			link.l1.go = "About_Fleetwood_13";
		break;
		
		case "About_Fleetwood_13":
			dialog.text = "Je savais que tu demanderais ça. Il est sur une brigantine commandée par le Commonwealth-oh au diable, la 'Royal Navy'. Son nom est 'Zeekalf'.";
			link.l1 = "'Zeekalf'? C'est un sacré nom hollandais pour un navire anglais...ohhh je comprends.";
			link.l1.go = "About_Fleetwood_14";
		break;
		
		case "About_Fleetwood_14":
			dialog.text = "Tu as l'esprit vif... Son ancien nom était 'Royal Mary', mais pour ce voyage, elle a été rebaptisée 'Zeekalf'. Et elle arbore le pavillon néerlandais.";
			link.l1 = "Ton aide a été inestimable, John. Je pars maintenant. Je reviendrai bientôt et j'aurai besoin de ta chambre au deuxième étage, où tu m'as logé pendant que je récupérais.";
			link.l1.go = "About_Fleetwood_15";
		break;
		
		case "About_Fleetwood_15":
			dialog.text = "Que mijotes-tu ?";
			link.l1 = "Je te dirai tout à mon retour. Souhaite-moi bonne chance, John ! Adieu.";
			link.l1.go = "About_Fleetwood_16";
		break;
		
		case "About_Fleetwood_16":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-16");
			pchar.questTemp.HWIC.Self = "HuntKnippel";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
			pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
			pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
			pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
			LocatorReloadEnterDisable("SentJons_town", "houseH1", true);//закрыть хижину Чарли
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		case "About_Fleetwood_17":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-15");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "Abigile":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Vraiment ? Pourquoi en es-tu si sûr ?";
			link.l1 = "Parce que Charlie est au fond de la mer à nourrir les poissons. J'ai abordé le 'Zeekalf' et envoyé Knippel en enfer. Bien sûr, je l'ai questionné avant cela... Il avait une lettre sur lui, ce qui m'a permis de me faire passer pour Knippel quand j'ai parlé à notre Juive Abigail, la chérie de notre brave Richard.";
			link.l1.go = "Abigile_1";
		break;
		
		case "Abigile_1":
			dialog.text = "Hmm...C'est astucieux. Alors, tu dis que...";
			link.l1 = "Oui. J'ai amené la Juive à Antigua. Elle est à bord de mon navire. Maintenant, j'ai un atout dans mon jeu de cartes avec Fleetwood ! Il fera n'importe quoi pour elle...";
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = "Es-tu sûr ? Il se pourrait que tout ne soit pas aussi simple que tu le laisses entendre...";
			link.l1 = "Oh oui, j'en suis absolument sûr. D'après la lettre, j'ai compris que le père d'Abigail était contre son mariage avec Richard à cause de l'argent. Je sais, un beau-père juif typique. Alors Fleetwood a décidé de payer une dot à son père - 200000 pesos ! Dis-moi maintenant, combien de filles dans le monde valent autant d'argent ?";
			link.l1.go = "Abigile_3";
		break;
		
		case "Abigile_3":
			dialog.text = "Hein ! Certainement pas une Juive ! Je n'ai jamais rencontré de chrétienne qui vaille ça dans ma vie, ça c'est sûr. "+pchar.name+", tu es un scélérat rusé. Que feras-tu d'elle ?";
			link.l1 = "Je vais amener la Juive ici et nous la garderons dans ta chambre. Je lui dirai que Richard est parti en mer et n'est pas encore revenu, donc elle sera notre invitée pendant une semaine. Elle pense que je suis Charlie Knippel.";
			link.l1.go = "Abigile_4";
		break;
		
		case "Abigile_4":
			dialog.text = "C'est intéressant. Alors tu as décidé de garder la fille dans ma maison ? Hmm...";
			link.l1 = "John, elle est juive. Une vagabonde apatride venue d'une colonie hollandaise. Elle n'est personne ici à St. John's et personne ne la connaît. Rassure-toi, nous pouvons faire ce que bon nous semble et elle n'osera pas dire un mot. Elle n'a ni un sou ni un ami. Et de toute façon, elle ne sera pas notre invitée longtemps. J'attirerai Fleetwood en l'utilisant comme appât, et après cela, nous n'aurons plus besoin d'elle.";
			link.l1.go = "Abigile_5";
		break;
		
		case "Abigile_5":
			dialog.text = "Tu commences à me faire peur, Charles. Tu ne vas pas profiter de cette fille, n'est-ce pas ? Ou la mener au même sort que Knippel ?";
			link.l1 = "Non, bien sûr que non. 'Fripouille rusée' je suis peut-être, mais je ne suis point ennemi des belles jeunes filles - juives ou chrétiennes. Ni même des laides, d'ailleurs. Si elle se conduit bien, je la ramènerai à son père à Willemstad une fois que tout cela sera terminé. Le vieux avare tombera probablement à mes pieds et me remerciera de l'avoir sauvée de ce perfide anglais.";
			link.l1.go = "Abigile_6";
			// belamour legendary edition -->
			link.l2 = "Elle a un rôle à jouer dans cette comédie. Quand la pièce sera terminée, je n'aurai plus besoin d'elle.";
			link.l2.go = "Abigile_6a";
		break;
		
		case "Abigile_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 60);
			dialog.text = "Je vois, donc pour l'instant je dois veiller sur elle.";
			link.l1 = "Je n'insisterai pas, l'ami. Si tu es complètement contre cela, elle peut rester à bord de mon navire. Mais alors je devrai la mettre aux fers pour la sécurité et la garder dans la cale avec les rats pour la protéger de mon équipage. C'est une nouveauté pour eux d'avoir des femmes à bord, tu sais. Ce serait dommage de traiter une si jolie fille de cette façon.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_6":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			// <-- legendary edition
			dialog.text = "Je vois, pour l'instant je dois m'occuper d'elle.";
			link.l1 = "Je n'insisterai pas, camarade. Si tu es totalement contre cela, elle peut rester à bord de mon navire. Mais alors je devrai la mettre aux fers pour sa sécurité et la garder dans la cale avec les rats pour la protéger de mon équipage. C'est une nouveauté pour eux d'avoir des femmes à bord, tu sais. Ce serait dommage de traiter une si jolie fille ainsi.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_7":
			dialog.text = "Je comprends. Très bien, amenez-la ici. C'est mon devoir de vous aider dans votre lutte contre Fleetwood. Amenez-la ici et je préparerai sa 'chambre d'hôte'.";
			link.l1 = "Merci John. Je savais que je pouvais compter sur toi.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Self = "AbigileInCabin";
			DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
			AddQuestRecord("Holl_Gambit", "3-24");
			//поставим табурет
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "SentJons_HouseF3";
			sld.startLocator = "goto2";
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abigile_7_1":
			DelLandQuestMark(npchar);
			dialog.text = "Oh ! Mon plaisir. Je suis heureux d'accueillir une femme si importante et... élégante. Mademoiselle, pourriez-vous monter au deuxième étage, s'il vous plaît. Un souper vous attend et le lit est fait. Je suis sûr que vous voudrez avoir une bonne nuit de sommeil après un si long voyage.";
			link.l1 = "Oui. Abigail est sûrement fatiguée après un si long voyage depuis Willemstad.";
			link.l1.go = "Abigile_8";
		break;
		
		case "Abigile_8":
			DialogExit();
			sld = characterFromId("Abigile");
			sld.dialog.currentnode = "Abigile_kidnapping_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_9":
			dialog.text = "As-tu déjà un plan?";
			link.l1 = "Oui. Nous devons rédiger une lettre à Richard avec une demande de rançon pour Abigail. Arrangez une rencontre quelque part sur une île inhabitée - comme les Turks. Et s'il ne se soumet pas, alors, nous enverrons, comment dire, sa tendre Hébraïque en morceaux.";
			link.l1.go = "Abigile_10";
		break;
		
		case "Abigile_10":
			dialog.text = "Pourquoi tant de complications avec une île déserte ?";
			link.l1 = "Terrain neutre. C'est plus sûr. Je n'emmènerai pas Abigail de toute façon. J'ai besoin de Fleetwood. Il préparera certainement une embuscade à Antigua, mais aux Turks, il n'aura pas cet avantage.";
			link.l1.go = "Abigile_11";
		break;
		
		case "Abigile_11":
			dialog.text = "Assez juste. Qui remettra la lettre? C'est très dangereux.";
			link.l1 = "Un étranger. Choisis un ivrogne de la taverne, un qui semble fiable. Ils sont prêts à faire tout ce que tu leur demandes pour un peu d'argent pour du rhum. Si Richard le tue dans un accès de rage, nous en enverrons un autre. Et nous joindrons un des doigts d'Abi dans la lettre. Cela le rendra bien plus docile.";
			link.l1.go = "Abigile_12";
		break;
		
		case "Abigile_12":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Ne t'inquiète pas, John. Je suis sûr que nous n'en arriverons pas là. Il te suffit de trouver un coursier et je rédigerai la lettre immédiatement. As-tu du papier et de l'encre ?";
			link.l1.go = "Abigile_13";
		break;
		
		case "Abigile_13":
			dialog.text = "Oui, en effet. Et il se trouve que je connais aussi un ivrogne qui convient. Je recommande Jack Harrison. Il passe chaque soir à la taverne à s'enivrer de rhum. Vous le trouverez facilement.";
			link.l1 = "Bien, apporte-moi plume et encre et je rédigerai la lettre de rançon pour Richard.";
			link.l1.go = "Abigile_14";
		break;
		
		case "Abigile_14":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.07, 2.57, -2.46, true, -0.08, -0.38, 1.35);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;
		
		case "Abigile_15":
			dialog.text = "Quand vas-tu lui remettre la lettre ? Vas-tu observer la livraison en cours ?";
			link.l1 = "Bien sûr. Richard n'est pas un imbécile, mais je doute qu'il prenne des risques. Du moins, je l'espère. Je ne veux pas faire de mal à la fille, mais je le ferai si nécessaire. Eh bien, il est temps de trouver le soûlard dont tu as parlé. Jack... quel était son nom complet ?";
			link.l1.go = "Abigile_20";
		break;
		
		case "Abigile_20":
			dialog.text = "Il s'appelle Jack Harrison. Il rend généralement visite à la taverne le soir. Sois prudent !";
			link.l1 = "Tout ira bien. Attends-moi.";
			link.l1.go = "Abigile_22";
		break;
		
		case "Abigile_22":
			DialogExit();
			LAi_SetOwnerType(npchar);
			pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
			AddDialogExitQuestFunction("CreateDrunckardInTavern");
			AddQuestRecord("Holl_Gambit", "3-25");
		break;
		
		case "Abigile_23":
			DelLandQuestMark(npchar);
			dialog.text = "Eh bien, je ne dirais pas ça. Fleetwood est rusé et dangereux. En plus de cela, c'est un maître d'épée et un marin aguerri. Il ne sera pas une proie facile.";
			link.l1 = "J'ai cessé de prendre la voie facile en arrivant aux Caraïbes. Eh bien, John, il est temps pour moi de partir. Au fait, tu as mentionné que notre brave Fleetwood a un bon navire, n'est-ce pas ?";
			link.l1.go = "Abigile_24";
		break;
		
		case "Abigile_24":
			dialog.text = "Il a la plus belle brigantin que j'aie jamais vue. Et j'en ai vu pas mal.";
			link.l1 = "C'est bien. J'aime les beaux navires. Il est temps de lever l'ancre !";
			link.l1.go = "Abigile_26";
		break;
		
		case "Abigile_26":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
			pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
			AddQuestRecord("Holl_Gambit", "3-28");
			AddMapQuestMarkShore("Shore57", false);
		break;
		
		case "Abigile_27":
			int iVal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
				}
			}//установили признак наличия Валькирии в эскадре.
			if (iVal != 0)
			{
				dialog.text = "Je suis sans voix! Une combinaison excellente, une idée géniale et une mise en œuvre magistrale! Mes félicitations, "+pchar.name+"! Et tu as aussi réussi à prendre sa goélette comme prise!";
				link.l1 = "Merci ! Et où est Hercule ? J'aimerais le voir. Lors de notre dernière rencontre, il m'a dit que je pourrais le trouver avec votre aide.";
				link.l1.go = "Abigile_28";
			}
			else
			{
				dialog.text = "Une combinaison excellente, une idée formidable et une mise en œuvre magistrale ! Mes félicitations, "+pchar.name+" !";
				link.l1 = "Merci ! Et où est Hercule ? J'aimerais le voir. La dernière fois que nous nous sommes rencontrés, il m'a dit que je pourrais le trouver avec votre aide.";
				link.l1.go = "Abigile_28";
			}
		break;
		
		case "Abigile_28":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Je l'attends d'une minute à l'autre. Il devrait arriver ici par le tunnel secret. Et tu devrais t'expliquer à Abigail. Elle a commencé à s'inquiéter de l'absence de Richard.";
			link.l1 = "D'accord, mais ne devrions-nous pas la renvoyer chez elle ?";
			link.l1.go = "Abigile_29";
		break;
		
		case "Abigile_29":
			dialog.text = "Pas encore... Je dois d'abord te parler. Mais attends d'abord l'arrivée d'Hercule. Va et réconforte Abigail. Raconte-lui une histoire, invente quelque chose. Puis viens à la cave. D'accord ?";
			link.l1 = "Oui, oui, John.";
			link.l1.go = "Abigile_30";
		break;
		
		case "Abigile_30":
			DialogExit();
			npchar.greeting = "merdok_4";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
			pchar.questTemp.HWIC.Self = "AbigileLie";
			sld = characterFromId("Abigile");
			LAi_SetCitizenType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddQuestRecord("Holl_Gambit", "3-34");
		break;
		
		case "Lucas":
			DelLandQuestMark(npchar);
			dialog.text = "Eh bien, il est temps de dévoiler les cartes. Comme tu l'as déjà deviné, je ne suis pas qu'un simple apothicaire. Mon vrai nom est Johan van Merden et jusqu'à récemment, j'étais un agent pour la Compagnie néerlandaise des Indes occidentales et la main droite de son vice-président Lucas Rodenburg.";
			link.l1 = "Vraiment ! C'est intéressant...";
			link.l1.go = "Lucas_1";
		break;
		
		case "Lucas_1":
			dialog.text = "C'est différent maintenant. Lucas veut quitter le jeu et retourner aux Pays-Bas, donc il a besoin d'enterrer tout et tout le monde lié à son passé\nJe pense que je respire encore seulement à cause de mes archives qui contiennent toutes les informations sur les crimes de Lucas... comme l'histoire du 'navire fantôme' qui n'est qu'un simple vaisseau pirate sous le commandement de la canaille téméraire et sans principes Jacob van Berg. Rodenburg a engagé cet homme pour piller et couler les navires marchands anglais\nVan Berg est également responsable du naufrage du flûte avec Abigail et son père à bord. Abigail est une figure importante dans ce jeu, Rodenburg voulait aussi sa main et son cœur, tout comme Fleetwood, donc j'ai été assez surpris quand vous l'avez amenée ici...";
			link.l1 = "Rodenburg... c'est le gendre dont le père excentrique d'Abigail parlait !";
			link.l1.go = "Lucas_2";
		break;
		
		case "Lucas_2":
			dialog.text = "Oui, c'est pourquoi je veux qu'elle reste ici un moment. Elle pourrait être mon dernier atout dans le jeu contre Rodenburg, bien que je préfère ne pas l'utiliser davantage, c'est une bonne fille, je ne veux pas qu'elle souffre. Je pense que Lucas choisirait mes archives à sa place, si le choix lui était proposé.\nDonc, je te propose d'être mon allié dans le jeu contre Lucas... débarrasse-toi de lui, par tous les moyens nécessaires. La récompense sera conséquente.";
			link.l1 = "Hmm... Je ne pense pas que ce sera plus difficile qu'avec Fleetwood. ";
			link.l1.go = "Lucas_3";
		break;
		
		case "Lucas_3":
			dialog.text = "Non, tu te trompes. En fin de compte, Fleetwood était un loup solitaire, agissant de son propre chef. Rodenburg est vice-président de la Compagnie. C'est un homme très influent, seul le gouverneur de Curaçao a plus de pouvoir. Jacob van Berg est son agent, un homme très dangereux. Lucas reste assis sur son cul à Willemstad sous la protection des gardes de la Compagnie, ils valent bien les hommes de Fleetwood.\nCela ne va pas être facile.";
			link.l1 = "Les règles du jeu sont les mêmes - attirer un tigre hors de sa tanière... J'ai déjà un plan. Que peux-tu me dire d'autre sur Lucas ?";
			link.l1.go = "Lucas_4";
		break;
		
		case "Lucas_4":
			dialog.text = "Eh bien, je vous ai presque tout dit. Il possède un navire rapide appelé 'Meifeng' - Beau Vent. Son capitaine est un Chinois nommé Longway - l'homme juré de Rodenburg. Lui aussi est un ennemi que vous ne voudriez pas affronter. Il n'y a pas d'amateurs dans l'équipage de Lucas.";
			link.l1 = "Nous avions déjà un atout dès le début - ton archive. S'il accorde plus de valeur à sa vie qu'à la Juive, alors il fera tout pour garder les informations de l'archive confidentielles... Mais... est-ce que l'archive existe vraiment, John ? Bluffes-tu ?";
			link.l1.go = "Lucas_5";
		break;
		
		case "Lucas_5":
			dialog.text = "L'archive existe bel et bien. Et Lucas le sait. As-tu trouvé quelque chose ?";
			link.l1 = "Je l'ai fait. John, si tu étais vraiment l'agent de la compagnie, tu devrais savoir quelque chose.";
			link.l1.go = "Lucas_6";
		break;
		
		case "Lucas_6":
			dialog.text = "Quoi exactement ? Demandez-moi.";
			link.l1 = "Je dois intercepter un navire de la compagnie. De préférence, un navire non escorté - un courrier ou quelque chose de ce genre. Peux-tu me dire quelque chose à ce sujet ?";
			link.l1.go = "Lucas_7";
		break;
		
		case "Lucas_7":
			dialog.text = "Hm... Je ne possède pas une telle information. Attends ! Je sais avec certitude que la Compagnie a un navire de courrier sur les routes maritimes entre Philipsburg et Willemstad une fois par mois. Elle livre des documents commerciaux. C'est une brigantine nommée 'Hoop'.\nElle quittera Philipsburg aujourd'hui ou demain.";
			link.l1 = "Oui, c'est ça ! Tout ce qu'il me faut pour aller aux côtes de Saint-Christophe. La route maritime vers Curacao passe juste à côté.";
			link.l1.go = "Lucas_8";
		break;
		
		case "Lucas_8":
			dialog.text = "Bonne chance, "+pchar.name+"Je ne te demanderai pas les détails de ton plan. Je t'attendrai au retour !";
			link.l1 = "Tout ira bien, John. Prends soin de la Juive et traite-la bien !";
			link.l1.go = "Lucas_9";
		break;
		
		case "Lucas_9":
			DialogExit();
			RemoveItems(PChar, "MC_Letter", 1);
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
			AddQuestRecordInfo("LetterToLucas", "1");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
			pchar.questTemp.HWIC.Self = "LetterToLucas";
			sld = characterFromId("Tonzag");
			sld.dialog.currentnode = "Tonzag_hired";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddQuestRecord("Holl_Gambit", "3-36");
			//установим таймер на генерацию энкаунтера
			pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Cureer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Cureer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false);//таймер
		break;
		
		case "Lucas_10":
			dialog.text = "Incroyable ! Je ne puis en croire mes oreilles ! Comment cela est-il arrivé ?";
			link.l1 = "J'ai capturé le bateau postal et envoyé une lettre à Lucas de la part de Fleetwood, dans laquelle j'ai déclaré que j'avais pris possession d'une certaine archive appartenant à un apothicaire de St. John's, et que bientôt les preuves de tous ses méfaits seraient connues d'ici à Amsterdam et Londres. Je m'attendais à ce qu'il commence à me traquer, mais il s'est avéré que c'était le contraire.";
			link.l1.go = "Lucas_11";
		break;
		
		case "Lucas_11":
			dialog.text = "";
			link.l1 = "Lucas a accusé Matthias Beck de trahison et de transactions avec les Anglais, l'a mis derrière les barreaux et a pris résidence dans le palais du gouverneur. Il a très probablement éliminé le capitaine de la brigantine. Puis il a ordonné à son fidèle Chinois du Meifeng de couler le navire avec le directeur de la Compagnie, Peter Stuyvesant, à bord !";
			link.l1.go = "Lucas_12";
		break;
		
		case "Lucas_12":
			dialog.text = "Rodenburg est un homme impitoyable. Mais même moi, je n'aurais jamais pensé qu'il irait aussi loin...";
			link.l1 = "J'ai capturé le Meifeng et interrogé Longway. Il m'a tout raconté. J'ai trouvé Stuyvesant et l'ai averti des intentions de Rodenburg, et nous avons navigué ensemble vers Willemstad. Stuyvesant a libéré Beck et arrêté Lucas. Il est en prison maintenant.";
			link.l1.go = "Lucas_13";
		break;
		
		case "Lucas_13":
			dialog.text = "Heh! Tu as un vrai talent, mon ami... Tu devrais faire carrière dans la Marine de la Compagnie ou comme politicien dans les Provinces-Unies - tu as toutes les chances de devenir gouverneur ! Et qu'as-tu fait à Longway ?";
			link.l1 = "Je l'ai laissé partir. Il s'est rendu honorablement donc je ne lui ai fait aucun mal.";
			link.l1.go = "Lucas_14";
		break;
		
		case "Lucas_14":
			dialog.text = "C'est bien. Longway est un bon homme, contrairement à son ancien patron. Eh bien, "+pchar.name+", tu as fait un excellent travail ! Je vais préparer ta récompense, mais il me faudra un peu de temps... En attendant...";
			link.l1 = "John, à vrai dire, il y a un hic. Longway puis Rodenburg m'ont tous deux dit que Jacob van Berg me traque. Quelle est la gravité de la situation ?";
			link.l1.go = "Lucas_15";
		break;
		
		case "Lucas_15":
			dialog.text = "Jacob van Berg ? Charlie, c'est sérieux. C'est un pirate impitoyable, un marin habile et un combattant qui fait passer Fleetwood pour un gentil minet. Un chasseur professionnel. C'est lui qui détruisait les navires sur ordre de Rodenburg.\nIl te retrouvera, alors tu dois te préparer. Je devrais prendre des précautions pour moi-même.";
			link.l1 = "Comment puis-je trouver ce van Berg ?";
			link.l1.go = "Lucas_16";
		break;
		
		case "Lucas_16":
			dialog.text = "Je ne sais pas. Lucas et Longway étaient les seuls à savoir où le trouver. Alors sois juste prudent et prêt\nJe ferme cet endroit. Passe par le tunnel secret si tu veux me voir. Et emmène la Juive, c'est trop dangereux pour elle de rester ici.";
			link.l1 = "Ne t'inquiète pas John. Qu'il se montre et je m'en occuperai. Où est Abigail ?";
			link.l1.go = "Lucas_17";
		break;
		
		case "Lucas_17":
			dialog.text = "Elle est allée à l'église. Je suis désolé pour elle. Elle a été très bouleversée récemment.";
			link.l1 = "Eh bien... C'est une agréable surprise. Peut-être réalise-t-elle que le Christ est le Messie que son peuple attend depuis longtemps. Eh bien, il est temps de la ramener à son père.";
			link.l1.go = "Lucas_18";
		break;
		
		case "Lucas_18":
			dialog.text = "Elle voulait te voir. Je suis sûr qu'elle te demandera de la ramener chez elle.";
			link.l1 = "Abi, hein ?";
			link.l1.go = "Lucas_19";
		break;
		
		case "Lucas_19":
			dialog.text = "Eh bien, je dois admettre que nous sommes devenus amis. Je ne regrette pas qu'elle ait vécu chez moi, et Dieu merci, elle ne saura jamais pourquoi elle a été amenée ici.";
			link.l1 = "D'accord, John, j'irai à l'église pour rencontrer Abigail. Ensuite, je me dirigerai vers Willemstad.";
			link.l1.go = "Lucas_20";
		break;
		
		case "Lucas_20":
			DialogExit();
			sld = characterFromId("Abigile");
			AddLandQuestMark(sld, "questmarkmain");
			ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1");//Аби - в церковь
			AddQuestRecord("Holl_Gambit", "3-56");
			pchar.questTemp.HWIC.Self = "AbiReturnHome";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
		break;
		
		case "Final":
			dialog.text = "Tu... lui as écrasé les noix ? Oh - une métaphore. Eh bien, noix ou pas noix, tu l'as fait ! Félicitations !";
			link.l1 = "Je ne te mentirais pas, hé. Maintenant tu peux respirer librement, John.";
			link.l1.go = "Final_1";
		break;
		
		case "Final_1":
			dialog.text = "Enfin ! Je pense qu'il vaut mieux renoncer à tous ces jeux politiques et intrigues. Il est maintenant temps de parler de votre récompense pour le travail accompli.";
			link.l1 = "Eh bien, j'apprécierais certainement cela.";
			link.l1.go = "Final_2";
		break;
		
		case "Final_2":
			dialog.text = "Je vais quitter les Caraïbes pour toujours. En guise de remerciement pour ton aide et pour m'avoir sauvé de Rodenburg, je te cède l'acte de propriété de cette maison et ma pharmacie. Elles sont à toi maintenant. Prends les clés.";
			link.l1 = "C'est formidable ! Je suis très content. Vous avez une maison très confortable et une cave douillette...";
			link.l1.go = "Final_3";
		break;
		
		case "Final_3":
			GiveItem2Character(pchar, "Drugstore_keys");//ключ
			dialog.text = "Et acceptez également cette modeste somme de 100 000 pesos et ce mousquet. Il m'a fidèlement servi jadis, et il vous servira bien aussi.";
			link.l1 = "Je ne rejette pas de tels cadeaux !";
			link.l1.go = "Final_4";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//открыть аптеку
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
			pchar.quest.Jino_Door.win_condition.l1 = "locator";
			pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
			pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
			pchar.quest.Jino_Door.function = "OpenRoomDoor";//на локатор комнаты Джино
			Achievment_Set("ach_10");
		break;
		
		case "Final_4":
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "mushket2");
			dialog.text = "Dans la chambre à l'étage, vous trouverez un jeune philosophe naturel. C'est le meilleur apothicaire que je connaisse. C'est lui qui a préparé ces mixtures, qui vous ont aidé à vous rétablir en quelques jours. Prenez soin de sa solde et son savoir compensera tous vos frais avec intérêt.";
			link.l1 = "Mon propre rat de bibliothèque personnel ? Très bien, je m'occuperai de lui.";
			link.l1.go = "Final_5";
		break;
		
		case "Final_5":
			dialog.text = "Je dois te dire adieu maintenant. Je vais à la cave pour empaqueter mes affaires. Demain, je ne serai plus ici - je mets les voiles pour quitter Antigua. Je suis heureux de t'avoir rencontré et je suis heureux que tu étais de mon côté et non avec mes ennemis.";
			link.l1 = "Je suis également heureux de vous rencontrer, John. Peut-être nous reverrons-nous...";
			link.l1.go = "Final_6";
		break;
		
		case "Final_6":
			dialog.text = "Pas dans cette vie mon ami. Je vais faire mes bagages. Adieu, "+pchar.name+" !";
			link.l1 = "Adieu, John ! Bonne chance à toi !";
			link.l1.go = "Final_7";
		break;
		
		case "Final_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			npchar.lifeday = 0;
			pchar.questTemp.HWIC.Self = "final";
			AddQuestRecord("Holl_Gambit", "3-64");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "self_win";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Ah, bon monsieur, n'écoutez pas ces bavardages insensés. Il n'y a personne là-bas. C'est mon laboratoire, des mélanges y sont préparés, vous savez...";
			link.l1 = "Sans plaisanter, John. Est-ce que le nom de Gino Gvineili te dit quelque chose ?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hmm...";
			link.l1 = "Ahah ! Je le vois dans tes yeux - j'ai raison... C'est là qu'il vit et pour qui il prépare ses herbes !";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Monsieur, je vous le répète - il n'y a personne ici.";
			link.l1 = "Mettons de côté les excuses, John. Je ne ferai pas de mal à ton alchimiste - mais si le Père Vincento de Santiago le trouve, je ne peux pas en être sûr. L'Inquisiteur prévoit déjà d'envoyer ses 'Domini Canes' à Antigua...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Que veux-tu de lui ?";
			link.l1 = "Juste pour parler. Il a des informations assez importantes pour moi. Je promets que je ne le livrerai pas à l'Inquisition et ne lui ferai aucun mal.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Gino est un bon gars. Ne crois rien de ce que le Père Vincento t'a raconté sur lui. Et souviens-toi - je défendrai mon alchimiste.";
			link.l1 = "Je t'ai donné ma parole. Cela ne te suffit-il pas ?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Monte à l'étage, alors. La porte est ouverte. Et espère rester fidèle à ta parole.";
			link.l1 = "Sois assuré, je le ferai.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "jino1";
			AddQuestRecord("Guardoftruth", "36");
			LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;
		
		// алхимический набор
		case "alchemy":
			dialog.text = "Capitaine, ne voudriez-vous pas vous familiariser avec les arts hermétiques ? Cela pourrait vous être très utile.";
			link.l1 = "Je suis désolé, mais mon occupation est quelque peu différente. J'ai l'habitude de tenir la poignée d'une épée dans ma main, pas des flacons ou des éprouvettes.";
			link.l1.go = "alchemy_exit";
			link.l2 = "'Il y a plus de choses dans le ciel et sur la terre que dans vos rêves de philosophie.' Bien sûr, j'adorerais. Que faut-il ?";
			link.l2.go = "alchemy_1";
			npchar.quest.alchemy = true;
		break;
		
		case "alchemy_exit":
			dialog.text = "Comme vous voulez. Je viens juste de proposer...";
			link.l1 = "Salut, mon ami.";
			link.l1.go = "exit";
		break;
		
		case "alchemy_1":
			dialog.text = "Tu devrais apprendre à mélanger les herbes de tes propres mains. Mais tu n'y parviendras pas sans un kit d'alchimiste. Jette un œil à ce sac. Il y a tout ce dont un alchimiste débutant a besoin - des éprouvettes, des flacons, un alambic, des spatules, des tubes en verre, un brûleur et plein d'autres trucs similaires...";
			link.l1 = "Très intéressant ! Et que puis-je préparer avec ça ?";
			link.l1.go = "alchemy_2";
		break;
		
		case "alchemy_2":
			dialog.text = "Eh bien, tu ne pourras pas transmuter le plomb en or, mais tu pourras mélanger des ingrédients selon diverses recettes et ainsi obtenir des potions et d'autres choses utiles.";
			link.l1 = "Recettes ?";
			link.l1.go = "alchemy_3";
		break;
		
		case "alchemy_3":
			dialog.text = "Vrai. Vous devez connaître une recette pour préparer une potion ou un objet. Les recettes peuvent être achetées chez les marchands ou trouvées n'importe où. Une fois que vous avez étudié une recette, vous devriez rassembler tous les ingrédients nécessaires et faire exactement ce qui est écrit là\n Utilisez vos outils d'alchimie, trouvez ou achetez un mortier et un pilon, cherchez un creuset, hélas, je n'en possède pas un de plus à vous donner. Herbes, esprits, potions, minéraux, déchets - tout fera l'affaire, à condition que vous ayez la bonne recette et les bons outils.";
			link.l1 = "Très intéressant. Et combien voulez-vous pour cet équipement ?";
			link.l1.go = "alchemy_4";
		break;
		
		case "alchemy_4":
			dialog.text = "Vingt mille pesos. C'est un très bon équipement et il couvrira son coût très rapidement.";
			link.l1 = "Tu te moques de moi, n'est-ce pas ? Un sac avec de la verrerie au prix d'un lougre ? Non, je vais passer.";
			link.l1.go = "alchemy_exit";
			if (sti(pchar.money) >= 20000)
			{
				link.l2 = "Je suis d'accord. Je pense que ce sera intéressant d'essayer de créer quelque chose de mes propres mains.";
				link.l2.go = "alchemy_5";
			}
		break;
		
		case "alchemy_5":
			AddMoneyToCharacter(pchar, -20000);
			Log_Info("You've got the alchemist's kit.");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Vous ne regretterez pas cet achat, j'en suis absolument sûr. Il est définitivement plus rentable de préparer soi-même des potions selon vos besoins, plutôt que de visiter les étals des herboristes pour acheter tout ce dont vous avez besoin pièce par pièce. De plus, il ne sera pas toujours possible d'acheter tout ce dont vous avez besoin.";
			link.l1 = "Apprenons. Je pense que je peux le faire !";
			link.l1.go = "alchemy_6";
		break;
		
		case "alchemy_6":
			DialogExit();
			PlaySound("interface\notebook.wav");
			Log_Info("In order to make your own herbs and amulets you must have the Alchemy skill!");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Tu es un "+GetSexPhrase("voleur, monsieur ! Gardes, attrapez-le","voleuse, fille ! Gardes, prenez-la")+"!!!","Regardez-moi ça! Dès que je me suis perdu en contemplation, vous avez décidé de fouiller ma malle! Attrapez le voleur!!!","Gardes ! Vol ! Attrapez le voleur !!!");
			link.l1 = "Nom de Dieu !";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
