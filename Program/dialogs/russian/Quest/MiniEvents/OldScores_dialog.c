void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		case "OS_Matros_sluh":
			bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			if (bOk1 || bOk2)
			{
				dialog.text = "Говорят, вчера в таверне драка была... Только вот кто дрался - чёрт его разберёт. Моя рожа-то цела. Вроде.";
				link.l1 = "Похоже, здесь была грандиозная попойка?";
				link.l1.go = "OS_Matros_sluh_2";
			}
			else
			{
				switch (rand(2))
				{
					case 0:
						dialog.text = "Эй, "+GetSexPhrase("парень","подруга")+", ты не видел"+GetSexPhrase("","а")+" мой сапог? Кто-то стащил его, пока я пьяный спал под столом в таверне.";
						link.l1 = "Смотри в оба, а то и второй сопрут.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 1:
						dialog.text = "Говорят, вчера в таверне драка была... Только вот кто дрался - чёрт его разберёт. Моя рожа-то цела. Вроде.";
						link.l1 = "Видимо, решили, что она уже и так достаточно пострадала.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
					
					case 2:
						dialog.text = "Клянусь всеми чертями, вчера у меня был кошель золота! Ну и где он теперь?!";
						link.l1 = "Для настоящего пирата золото - не главное. Важнее свобода.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
				}
			}
		break;
		
		case "OS_Matros_sluh_2":
			dialog.text = "Ещё какая! Вот же было у трактирщика работы... ик... А ещё... джин у него спёрли! Да не бутылочку, а целый бочонок, да ещё такой, что на всех Карибах не сыщешь! Говорят, аж из самой Европы привезён. Для кого старый прохвост его держал - не признаётся, но одно ясно: если эту пропажу не найдут скоро, бедолагу шторм адский накроет!";
			link.l1 = "Забавно. Ну что ж, бывай здоров, пьянчужка.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OS_Matros_sluh";
			
			SetQuestHeader("OS");
			AddQuestRecord("OS", "1");
			pchar.questTemp.OS_Start = true;
			pchar.questTemp.OS_Tavern_1 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
		break;
		
		case "OS_Matros_again":
			switch (rand(2))
			{
				case 0:
					dialog.text = "Чего тебе ещё? Не видишь, у меня башка раскалывается? Отвали.";
					link.l1 = "Меньше пить надо - глядишь и на человека стал бы похож.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Отстань от меня... У меня голова сейчас взорвётся!";
					link.l1 = "Удивительно, что она вообще до сих пор на плечах.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
				
				case 2:
					dialog.text = "Да чтоб тебя... Оставь меня в покое, не видишь, не до тебя мне сейчас!";
					link.l1 = "...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
		break;
		
		case "OS_Matros":
			dialog.text = "Оставь меня в покое! Не видишь, я на грани? Руки так и чешутся двинуть кому-нибудь по роже.";
			link.l1 = "Не кипятись, приятель. Мне просто нужно узнать, что вчера творилось в таверне.";
			link.l1.go = "OS_Matros_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OS_Matros_2":
			dialog.text = "Карамба! Ты что, "+GetSexPhrase("ещё один любовничек","родственница")+" той сумасбродной официантки? И чего тебе надо, чтоб тебя штормом смыло? На дуэль меня вызовешь? Или сразу саблей махать начнёшь?";
			if (pchar.sex == "woman")
			{
				link.l1 = "Родственница? Это едва ли. Но ты парень, похоже, не очень высокого мнения о ней?";
				link.l1.go = "OS_Matros_3_scrit";
			}
			else
			{
				link.l1 = "Любовничек? Это едва ли. Похоже, девица берёт количеством, а не качеством, не так ли?";
				link.l1.go = "OS_Matros_3_scrit";
				link.l2 = "Нет мне дела до её похождений. Просто расскажи, что там произошло, и я оставлю тебя в покое. Это ведь ты её до бешенства довёл?";
				link.l2.go = "OS_Matros_3_fortuna";
			}
		break;
		
		case "OS_Matros_3_scrit":
			dialog.text = "У этой фурии, похоже, разборчивость - как у голодного матроса: хватай, что ближе, а там разберёмся! Глазками стреляла весь вечер и кокетничала, как кошка у камбуза. А стоило мне пришвартоваться поближе - заорала так, что рыба в бухте на дно ушла!";
			link.l1 = "Может, ты перебрал и впрямь был чрезмерно настойчив?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "OS_Matros_3_fortuna":
			dialog.text = "У этой фурии, похоже, разборчивость, как у голодного матроса - хватай, что ближе, а там разберёмся! Глазками стреляла весь вечер, и кокетничала, как кошка у камбуза. А стоило мне пришвартоваться поближе - заорала так, что рыба в бухте на дно ушла!";
			link.l1 = "Может, ты перебрал и впрямь был чрезмерно настойчив?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "OS_Matros_4":
			dialog.text = "Я, может, и был пьян, но отчётливо помню всё, что там происходило. Это не я на неё охоту вёл, а она на меня бросалась, как акула на тушку. Весь день вокруг меня вертелась!";
			if (pchar.sex == "woman")
			{
				link.l1 = "И из-за такого пустяка тебе хочется избить первого встречного? Или в тот вечер случилось что-то ещё?";
			}
			else
			{
				link.l1 = "Послушай, ты сказал 'ещё один любовничек'. Тебе что-то известно о её похождениях?";
			}
			link.l1.go = "OS_Matros_5";
		break;
		
		case "OS_Matros_5":
			dialog.text = "После того как её вопли поутихли, парни из моей команды сказали, что напрасно я в её бухте якорь попытался бросить. Мол, есть у неё ухажёр в городе, который с нашим кэпом якшается.";
			link.l1 = "Забавно. Больше ты ничего странного не заметил? Может, кто к стойке бармена подходил во время ссоры?";
			link.l1.go = "OS_Matros_6";
		break;

		case "OS_Matros_6":
			dialog.text = "Дьявол... У меня башка раскалывается, а тут ещё ты со своими вопросами. Не видел я ничего и не слышал. Дал"+GetSexPhrase("","а")+" бы лучше пару песо, чем терзать морского волка вопросами.";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Держи сто песо. Смотри не напейся и опять не попади под чары официантки, хех.";
				link.l1.go = "OS_Matros_7_harizma";
			}
			link.l2 = "Обойдёшься. А то напьёшься, и опять к официантке с приставаниями пойдёшь.";
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
				dialog.text = "Эй, Джек! Да у тебя тут портовая потаскуха завелась! Ха-ха! Ты только погляди на неё - хороша ведь чертовка! Интересно, она все сундуки обшарила, или мы прервали её на самом интересном месте?";
				link.l1 = "...";
			}
			else
			{
				dialog.text = "Эй, Джек! Да у тебя тут крыса! Ха-ха! Ты только погляди на него - ну и прохвост! Видать, уже и в сундуках наших успел порыться, а, проныра?";
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
				dialog.text = "Смелая цыпочка. Влезть в логово Джека Вейлса - не каждому в голову придёт. Ну, и что ты тут забыла, крошка? Решила нас поразвлечь?";
				link.l1 = "Поразвлечь? Ха! Да вы, я смотрю, те ещё мечтатели, господа. Я здесь затем, чтобы забрать то, что вы украли. Или вы всерьёз надеялись, что ваша жалкая комедия останется незамеченной?";
			}
			else
			{
				dialog.text = "Смелый червяк. Залезть в дом Джека Вейлса не каждому в голову придёт. Ну и что ты здесь забыл?";
				link.l1 = "Скажем так, возвращаю украденное. Или вы, господа, всерьёз надеялись, что ваша жалкая постановка останется не раскрытой?";
			}
			link.l1.go = "OS_Dialog_4";
		break;
		
		case "OS_Dialog_4":
			StartInstantDialog("OS_capWolf", "OS_Dialog_5", "Quest\MiniEvents\OldScores_dialog.c");
		break;
		
		case "OS_Dialog_5":
			if (pchar.sex == "woman")
			{
				dialog.text = "Жалкая комедия?! Да чтоб мне в аду сгореть, я же с тебя сейчас кожу сниму и на парус пущу! Ха-ха! Хотя, может, перед этим стоит с тобой хорошенько... поиграть?";
				link.l1 = "Вижу, вы горите желанием отправиться на тот свет? Что ж, не буду вас томить - к бою, грязные ублюдки!";
			}
			else
			{
				dialog.text = "Жалкая постановка? Да чтоб мне в аду сгореть, я же с тебя сейчас кожу сниму и на парус пущу! Хватит болтать - конец тебе, скотина!";
				link.l1 = "Ну, раз вы так настаиваете - то к бою, мерзавцы!";
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
			dialog.text = ""+sld.name+", где мой джин?! Если он не у тебя, я лично отправлю тебя на дно рыб кормить!";
			link.l1 = "...";
			link.l1.go = "Zaharia_2";
			CharacterTurnByChr(npchar, sld);
			//locCameraFromToPos(-2.53, 2.00, 1.26, false, 0.03, 0.00, -1.11);
		break;
		
		case "Zaharia_2":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "...";
			link.l1 = "Я как раз его доставил"+GetSexPhrase("","а")+". Вот он.";
			link.l1.go = "Zaharia_3";
			CharacterTurnByChr(npchar, pchar);
			TakeItemFromCharacter(pchar, "cask_gin");
			notification("Вы отдали бочонок джина", "NONE");
		break;
		
		case "Zaharia_3":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "Хорошо, что я в тебе не ошибся, "+sld.name+". Зайди ко мне завтра - получишь свои дублоны.";
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
			dialog.text = "Капитан, насчёт таблички...";
			link.l1 = "Какой таблички? А-а, той самой... Пожалуй, мне ни к чему такие почести. Не утруждайтесь, обойдусь без этого.";
			link.l1.go = "Tavern_2";
		break;
		
		case "Tavern_2":
			dialog.text = "Я могу предложить вам кое-что получше! Отныне для вас в моей таверне всегда будет бесплатный ночлег и выпивка за счёт заведения! Такой человек, как вы, безусловно, этого заслуживает!";
			link.l1 = "Вот это уже другой разговор! Такие привилегии мне по душе! До встречи, "+npchar.name+".";
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