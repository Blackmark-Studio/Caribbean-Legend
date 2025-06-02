void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		// Квест "Длинные тени старых грехов"
		case "DTSG_Knippel_1":
			dialog.text = "Ох, ну и жара сегодня. Хоть книппель обвяжи вокруг ноги и прыгай в море, лишь бы уже избавиться от этой духоты!";
			link.l1 = "Ха-ха, Чарли!.. Это какие-то уж слишком крайние меры, как по мне. А вот промочить горло я бы не отказался - сегодня и правда как-то слишком жарко. Ты в деле?";
			link.l1.go = "DTSG_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Knippel_2":
			dialog.text = "Пропустить стаканчик-другой с вами, капитан? С удовольствием!";
			link.l1 = "Вот и замечательно. Идём!";
			link.l1.go = "DTSG_Knippel_3";
		break;
		
		case "DTSG_Knippel_3":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "", "", "", "DTSG_BasTerTavern", -1);
			FreeSitLocator("BasTer_tavern", "sit_base2");
			FreeSitLocator("BasTer_tavern", "sit_front2");
		break;
		
		case "DTSG_Ohotnik_1":
			dialog.text = "Эй, моряк, ты выглядишь повидавшим всякое! Ищу себе компанию, одному скучно. Выпьем, потравим байки? Я угощаю!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_1_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
			
		break;
		
		case "DTSG_Ohotnik_1_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_2":
			dialog.text = "Э-э, нет, спасибо, приятель. Я пришёл сюда вместе с капитаном, поищи кого-нибудь ещё.";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_2_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
			locCameraFromToPos(5.57, 2.39, -4.63, true, 8.53, 2.07, 1.84);
		break;
		
		case "DTSG_Ohotnik_2_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_3", "Quest\CompanionQuests\Knippel.c");
			locCameraSleep(true);
		break;
		
		case "DTSG_Ohotnik_3":
			dialog.text = "Эге, сам оборванец, а такого о себе мнения, что меньше, чем с капитанами, не пьёшь?";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_3_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_3_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_4", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_4":
			dialog.text = "Мнения, мнения?! Да я прослужил не один десяток лет в Королевском Флоте! И воевал не за господ, а за простых ребят, как мы с тобой, чтоб везде был закон и порядок!..";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_4_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_4_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_5", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_5":
			dialog.text = "Говоришь о простых ребятах, а сам только с капитанами и благородиями пьёшь! Видать, только стволы обслуживать вас там и учат, ха!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_5_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_5_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_6":
			dialog.text = "Я за такие слова о флоте тебе книппель в глотку затолкаю, щенок...";
			link.l1 = "Чарли, не кипятись ты так, оно того не стоит.";
			link.l1.go = "DTSG_Ohotnik_7";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_7":
			dialog.text = "Позвольте разобраться мне, капитан. На кону честь флота, я должен защитить её сам и ни за кем не прятаться...";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_8";
		break;
		
		case "DTSG_Ohotnik_8":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_FadeLong("DTSG_BasTerTavern_7", "");
		break;
		
		case "DTSG_Knippel_l0":
			dialog.text = "Спасибо, что подождали, капитан. Надеюсь, я не слишком тут завозился.";
			link.l1 = "Не переживай из-за этого. Ты не ранен, Чарли? Тот мерзавец оказался довольно неплох.";
			link.l1.go = "DTSG_Knippel_l1";
		break;
		
		case "DTSG_Knippel_l1":
			dialog.text = "Не извольте беспокоиться, капитан. Главное, что теперь он получил своё...";
			link.l1 = "...";
			link.l1.go = "DTSG_Knippel_l2";
		break;
		
		case "DTSG_Knippel_l2":
			dialog.text = "Я с трупа подобрал какой-то ключ... интересно, от чего он мог бы быть?";
			link.l1 = "Элементарно, Чарли... От двери или сундука, ха-ха. Надо бы поболтать с трактирщиком об этом мерзавце, лишним не будет.";
			link.l1.go = "DTSG_Knippel_l3";
			AddItems(pchar, "Key1", 1);
			Log_info("Чарли отдал вам ключ");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_Knippel_l3":
			DialogExit();
			
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			sld.location = "None";
			pchar.questTemp.DTSG_BasTerTavern = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "DTSG_Knippel_20":
			dialog.text = "Ничего себе...";
			link.l1 = "Ты думаешь о том же, что и я, Чарли?";
			link.l1.go = "DTSG_Knippel_21";
		break;
		
		case "DTSG_Knippel_21":
			dialog.text = "Не знаю, как вы, капитан, а меня удивило, сколько здесь денег - он выглядел самым обычным человеком, ни купцом, ни дворянином.";
			link.l1 = "Не такая уж и большая сумма на самом деле, но ты прав, конечно. А вот меня удивило это странное сожжённое письмо.";
			link.l1.go = "DTSG_Knippel_22";
		break;
		
		case "DTSG_Knippel_22":
			dialog.text = "Да уж, это было не слишком умно с его стороны - всё равно, что книппелями палить по корпусу хорошего фрегата. Надо было уничтожить письмо полностью.";
			link.l1 = "Тоже верно. Но нам от этого не легче - мы не знаем, ни кем он был, ни с кем вёл переписку. Ладно, пойдём, Чарли, больше нам здесь делать нечего.";
			link.l1.go = "DTSG_Knippel_23";
		break;
		
		case "DTSG_Knippel_23":			//КОНЕЦ ЭТАПА 1
			DialogExit();
			Return_KnippelOfficer();

			AddQuestRecord("DTSG", "2");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.DTSG_Nastoroje1 = true;
		break;
		
		case "DTSG_Ohotnik_10":
			dialog.text = "Вот и весь ваш хвалёный Королевский флот, тьфу!";
			link.l1 = "Чарли был хорошим, достойным человеком. Просто он был канониром, а не морским пехотинцем.";
			link.l1.go = "DTSG_Ohotnik_11";
		break;
		
		case "DTSG_Ohotnik_11":
			dialog.text = "Канониром?! Значит, всё в точности так, как я и говорил, ха-ха-ха! А ты не зыркай - знать надо было, кого в команду к себе берёшь. Сам, поди, точно такой же, как и этот твой Чарли.";
			link.l1 = "А тебе надо было знать, с кем связываешься.";
			link.l1.go = "DTSG_Ohotnik_Agressia_1";
			link.l2 = "Ты ещё жив лишь потому, что честно победил, так что попридержи свой гнилой язык и катись отсюда.";
			link.l2.go = "DTSG_Ohotnik_Otpustil_1";
		break;
		
		case "DTSG_Ohotnik_Otpustil_1":
			dialog.text = "Надо же, я уж думал, мне теперь и с тобой драться. Приятно слышать, что для тебя честь - не пустой звук.";
			link.l1 = "Она и для Чарли таковым не была. А вот насчёт тебя сомневаюсь. Ну да это уже неважно.";
			link.l1.go = "DTSG_Ohotnik_Otpustil_2";
		break;
		
		case "DTSG_Ohotnik_Otpustil_2":			//ПРОВАЛ ЭТАПА 1
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			ChangeCharacterComplexReputation(pchar, "fame", -3);	
		break;
		
		case "DTSG_Ohotnik_Agressia_1":
			dialog.text = "И с кем же я связался, изнеженным слабаком?! Ты хоть сам свои тоненькие усики-то видел?..";
			link.l1 = "А ты знаешь, как вывести из себя... Тем приятнее будет выместить на тебе всю злобу.";
			link.l1.go = "DTSG_Ohotnik_Agressia_2";
		break;
		
		case "DTSG_Ohotnik_Agressia_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			sld = CharacterFromID("DTSG_Ohotnik");
			DeleteAttribute(sld, "CantLoot");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Ohotnik_Agressia_3");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_1":
			dialog.text = "Постойте, капитан. Я вижу, что вы достойный и благородный человек, не откажите мне в помощи в одном деле. Деле чести.";
			link.l1 = "Возможно, и не откажу, но что за дело? И почему вы обратились именно ко мне? Благородных людей в этих краях немало. С кем имею честь, кстати говоря?";
			link.l1.go = "DTSG_PiterAdams_2";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "DTSG_PiterAdams_2":
			dialog.text = "Питер. Питер Адамс. По вам видно, что вы не типичный изнеженный потомок старого рода, а надёжный человек с твёрдой рукой.";
			link.l1 = "Ох, видели бы вы меня, когда я только прибыл на Карибы, сударь. Однако излагайте суть дела. В чём вам требуется помощь?";
			link.l1.go = "DTSG_PiterAdams_3";
		break;
		
		case "DTSG_PiterAdams_3":
			dialog.text = "Вы не могли бы... сразиться за дуэли вместо меня, сэр? Один местный задира, Ральф Фаггл, оскорбил мою супругу. И приставал к ней, прилюдно. При мне. Можете себе такое представить?";
			link.l1 = "Не слишком много чести в том, чтобы назначить дуэль, а затем прятаться за чьей-либо спиной. Особенно, если дело касается не только вашей личной чести, но и чести женщины, тем более, супруги. Вам так не кажется, Адамс? Почему же, позвольте узнать, вы не в состоянии драться за свою женщину?";
			link.l1.go = "DTSG_PiterAdams_4";
		break;
		
		case "DTSG_PiterAdams_4":
			dialog.text = "И вы правы, совершенно правы. Но я недавно тяжело перенёс лихорадку, до сих пор едва стою на ногах\nПризнаться, мне нелегко просить вас о чём-то подобном. Оскорби он меня, я бы стерпел. Но не когда на кону честь моей супруги! Я не трус, сэр. Когда-то я служил в Королевском Флоте и ходил на одном корабле с самим Робертом Блейком!";
			link.l1 = "Я...";
			link.l1.go = "DTSG_PiterAdams_5";
		break;
		
		case "DTSG_PiterAdams_5":
			StartInstantDialog("Knippel", "DTSG_PiterAdams_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_6":
			dialog.text = "Мы поможем вам.";
			link.l1 = "Чарли?..";
			link.l1.go = "DTSG_PiterAdams_7";
			CharacterTurnByChr(npchar, characterFromId("DTSG_PiterAdams"))
		break;
		
		case "DTSG_PiterAdams_7":
			dialog.text = "Это достойный человек, капитан. И да греметь мне вечность книппелями, будь это не так! С адмиралом Блейком служили прекрасные люди. Они вместе боролись, чтобы никто не притеснял простой народ\nИ именно благодаря ему Ямайка была освобождена от тирании испанцев!";
			link.l1 = "Будь это хоть трижды так, я не позволю меня перебивать и, уж тем более, принимать за меня решения. Это понятно?";
			link.l1.go = "DTSG_PiterAdams_8";
			link.l2 = "Я понимаю это, правда. Однако я ведь даже ещё не успел ответить. Постарайся впредь не рубить сплеча и не перебивать меня, хорошо?";
			link.l2.go = "DTSG_PiterAdams_8";
			CharacterTurnByChr(npchar, pchar)
		break;
		
		case "DTSG_PiterAdams_8":
			dialog.text = "Я вам так скажу, капитан - если вы не поможете этому человеку, старина Чарли сам всё бросит и сразится за него на дуэли, провалиться мне на месте!";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Тише, Чарли, я ведь не отказывался помочь. Правда ведь, мистер Адамс?";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_1";
			}
			else
			{
				link.l1 = "Право, Чарли, ты выставляешь меня теперь каким-то трусом. А ведь я таковым никогда не был. Тебе ли не знать.";
				link.l1.go = "DTSG_PiterAdams_NN_1";
			}
		break;
		
		case "DTSG_PiterAdams_NN_1":
			dialog.text = "Э-э, простите, капитан, погорячился.";
			link.l1 = "Ничего. Но держи себя в руках, хорошо?";
			link.l1.go = "DTSG_PiterAdams_NN_1_1";
		break;
		
		case "DTSG_PiterAdams_NN_1_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_NN_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_NN_2":
			dialog.text = "";
			link.l1 = "Я сражусь за вас на дуэли, мистер Адамс.";
			link.l1.go = "DTSG_PiterAdams_NN_3";
		break;
		
		case "DTSG_PiterAdams_NN_3":
			dialog.text = "Благодарю вас, сэр! Храни вас Бог!";
			link.l1 = "И Лорда-Протектора заодно, верно, мистер Адамс? Не переживайте, Шарль де Мор никогда не оставит достойного человека в беде.";
			link.l1.go = "DTSG_PiterAdams_NN_4";
		break;
		
		case "DTSG_PiterAdams_NN_4":
			dialog.text = "Мы ценим это, мистер де Мор, сэр! Не хотите ли заглянуть к нам с Джейн в гости, отобедать?";
			link.l1 = "Ну, я...";
			link.l1.go = "DTSG_PiterAdams_NN_5";
		break;
		
		case "DTSG_PiterAdams_NN_5":
			dialog.text = "Я настаиваю!";
			link.l1 = "Ну только, если вы настаиваете. Благодарю, Питер. Ведите.";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_Nastoroje_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_Nastoroje_2":
			dialog.text = "Конечно, правда, сэр! А не желаете ли зайти к нам с Джейн, отдохнуть, набраться сил с дороги?";
			link.l1 = "Благодарю, конечно, но стоит ли злоупотреблять вашим гостеприимством?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_3";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_3":
			dialog.text = "О, напротив, капитан, мы обидимся, если вы к нам не заглянете.";
			link.l1 = "Как я смею. В таком случае, после вас, Питер!";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_IdemKDomu":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "houseF1", "DTSG_PiterAdams_VDom", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_1":
			dialog.text = "Мы на месте! Проходите, пожалуйста.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Спасибо вам. Я ведь могу поговорить с Джейн? Спросить, как было дело, и у неё - мне нужны все подробности.";
				link.l1.go = "DTSG_PiterAdamsRyadomSDomom_2";
			}
			link.l2 = "Я очень прошу прощения, но вынужден отказать. Мне ведь ещё к дуэли подготовиться. Кстати, о ней - скажите, где и когда вам назначено?";
			link.l2.go = "DTSG_PiterAdamsRyadomSDomom_4";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_2":
			dialog.text = "Ну конечно же, сэр. Мы оба с радостью поговорим с вами и ответим на все ваши вопросы. Следуйте за мной.";
			link.l1 = "Благодарю, Питер.";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_3";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_3":
			DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "DTSG_PiterAdams_VDom_2");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_4":
			dialog.text = "Жаль, конечно. Но лучше подготовьтесь как следует, разумеется. По моим расчётам, до неё ещё примерно два часа. Она пройдёт за городскими воротами.";
			link.l1 = "Понял, благодарю. А вот уже после дуэли я с радостью к вам загляну. До встречи!";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_5";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_5":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			npchar.location = "None";
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			sld.Dialog.CurrentNode = "Knippel_officer";
			sld.location = "None";
			
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1 = "Timer";
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.hour = sti(GetTime() + 2);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition = "DTSG_PoP_DuelTime";
			
			PChar.quest.DTSG_PoP_Duel.win_condition.l1 = "location";
			PChar.quest.DTSG_PoP_Duel.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.DTSG_PoP_Duel.win_condition = "DTSG_PoP_Duel";
			
			AddQuestRecord("DTSG", "3");
		break;
		
		case "DTSG_JeinAdams_1":
			dialog.text = "Добро пожаловать! Дорогой, ты не говорил, что приведёшь с собой гостей - я бы как следует подготовилась.";
			link.l1 = "Благодарю вас, сударыня, мы ненадолго. Шарль де Мор, к вашим услугам. Я согласился выслушать вашу с мужем историю. Расскажите, как это произошло.";
			link.l1.go = "DTSG_JeinAdams_2";
		break;
		
		case "DTSG_JeinAdams_2":
			dialog.text = "Ох, это ужасно! Ральф был совершенно пьян. Он начал приставать ко мне при соседях, даже при Питере, говорить непристойности...";
			link.l1 = "Что именно он вам сказал?";
			link.l1.go = "DTSG_JeinAdams_3";
		break;
		
		case "DTSG_JeinAdams_3":
			dialog.text = "Мне слишком неловко об этом говорить. Затем он протрезвел, и...";
			link.l1 = "Извинился и стал просить об отмене дуэли, может быть?";
			link.l1.go = "DTSG_JeinAdams_4";
		break;
		
		case "DTSG_JeinAdams_4":
			dialog.text = "Ни разу.";
			link.l1 = "Сочувствую вам. Я бы хотел узнать ещё кое-что, если позволите, сударыня.";
			link.l1.go = "DTSG_JeinAdams_5";
		break;
		
		case "DTSG_JeinAdams_5":
			dialog.text = "И что же, сэр?";
			link.l1 = "Какие жизненные обстоятельства и испытания вынудили вас с мужем начать жить именно здесь? В любом английском городе, учитывая заслуги вашего мужа, вы бы уже смогли приструнить Ральфа.";
			link.l1.go = "DTSG_JeinAdams_6";
		break;
		
		case "DTSG_JeinAdams_6":
			StartInstantDialog("Knippel", "DTSG_JeinAdams_7", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_7":
			dialog.text = "Я прошу прощения, сэр, но как вы смеете?! Не будь вы моим капитаном - взял бы в руку книппель и приложил бы вам хорошенько!\nМало того, что вы не доверяете такому достойному человеку, как мистер Адамс, так ещё и над дамой в беде посмеиваетесь...";
			link.l1 = "Ты слышал, чтобы я смеялся над дамой? Нет? Тогда не клевещи на меня. Просто свои люди могли бы им помочь, потому я и спросил.";
			link.l1.go = "DTSG_JeinAdams_8a";
			link.l1 = "Успокойся, Чарли! Как можно?.. Я лишь хотел узнать больше о горестях Джейн и Питера да посочувствовать им. Ведь в английских колониях им бы наверняка уже помогли.";
			link.l1.go = "DTSG_JeinAdams_8b";
		break;
		
		case "DTSG_JeinAdams_8a":
			dialog.text = "Да мало ли, как может сложиться жизнь?.. Разбилось судно. Или чья-то клевета, что порой может вынудить даже таких, как эти честные люди, скрываться в позоре\nЕсли же вы столь недоверчивы и подозрительны - можете поговорить с соседями. Я полностью уверен, что они подтвердят каждое их слово. Но старина Чарли на вашем месте бы не опустился до такой низости, чтобы обсуждать горе людей за их спинами!";
			link.l1 = "Ты меня не слышал? Я сказал, что помогу этим людям.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
		break;
		
		case "DTSG_JeinAdams_8b":
			dialog.text = "Да мало ли, как может сложиться жизнь?.. Разбилось судно. Или чья-то клевета, что порой может вынудить даже таких, как эти честные люди, скрываться в позоре\nЕсли же вы столь недоверчивы и подозрительны - можете поговорить с соседями. Я полностью уверен, что они подтвердят каждое их слово. Но старина Чарли на вашем месте бы не опустился до такой низости, чтобы обсуждать горе людей за их спинами!";
			link.l1 = "Ты меня не слышал? Я сказал, что помогу этим людям.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", -2);
		break;
		
		case "DTSG_JeinAdams_9":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_JeinAdams_10", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_10":
			dialog.text = "Благодарим вас от всего сердца. Мы будем поминать вас в наших молитвах.";
			link.l1 = "Это, конечно, хорошо. К слову, о нашем деле. Где и когда вы назначили дуэль, мистер Адамс?";
			link.l1.go = "DTSG_JeinAdams_11";
		break;
		
		case "DTSG_JeinAdams_11":
			dialog.text = "За городскими воротами, сэр. Осталось ещё два часа.";
			link.l1 = "Успеваю. Ожидайте меня с хорошими новостями. И не вздумайте ставить свечку за упокой за меня раньше времени!";
			link.l1.go = "DTSG_JeinAdams_13";
		break;
		
		case "DTSG_JeinAdams_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "DTSG_PiterAdams_IsDoma");
		break;
		
		case "DTSG_Knippel_30":
			dialog.text = "Вас что-то беспокоит, капитан? Выглядите крайне задумчиво.";
			link.l1 = "Ты знаешь, да. Всё-таки, кое-что в истории Адамса шито белыми нитками, и...";
			link.l1.go = "DTSG_Knippel_31";
		break;
		
		case "DTSG_Knippel_31":
			dialog.text = "Да сколько же можно, сэр?! Вы так реагируете каждый раз, когда кому-то нужна помощь?";
			link.l1 = "Бога ради, говори тише. Ты бы ещё на всю улицу крикнул. Я же сказал, что пойду на дуэль. Разве тебе этого недостаточно? А теперь слушай меня внимательно.";
			link.l1.go = "DTSG_Knippel_32";
		break;
		
		case "DTSG_Knippel_32":
			dialog.text = "Хм, хорошо, капитан. Прошу прощения за вспыльчивость - мне небезразлична судьба служивших в Королевском Флоте. Многие из нас были достойными ребятами, заслуживающими участи лучше той, что большинство в итоге получило.";
			link.l1 = "Я понимаю тебя, Чарли. А теперь запоминай, что нужно сделать. Я хочу, чтобы ты отправил нескольких ребят с корабля к городским воротам. А как будет подходить время дуэли - пусть незаметно соберутся вместе и будут готовы к моему сигналу.";
			link.l1.go = "DTSG_Knippel_33";
		break;
		
		case "DTSG_Knippel_33":
			dialog.text = "Вы собираетесь превратить честную дуэль в избиение младенца?..";
			link.l1 = "Есть у меня подозрения, что она будет не совсем уж честной. Я дам сигнал только в случае необходимости. Если же всё и правда будет чинно-благородно - буду рад ошибиться. Теперь-то ты меня понял? Неужели ты забыл, что случилось примерно с месяц назад?";
			link.l1.go = "DTSG_Knippel_34";
		break;
		
		case "DTSG_Knippel_34":
			dialog.text = "Понял, сэр. Признаться, мне это не совсем по нраву, но сделаю всё необходимое. Не извольте беспокоиться.";
			link.l1 = "Вот и хорошо, это именно то, что я и хотел услышать.";
			link.l1.go = "DTSG_Knippel_35";
		break;
		
		case "DTSG_Knippel_35":
			DialogExit();
			
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.location = "None";
			AddDialogExitQuestFunction("DTSG_Knippel_36");
		break;
		
		case "DTSG_RalfFaggl":
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			PChar.quest.DTSG_PoP_DuelTime.over = "yes";
			PChar.quest.DTSG_PoP_Duel.over = "yes";
			dialog.text = "А вот и де Мор. Рановато ты, приятель. Да и мы всё ещё в городе. Хотя плевать. Жаль только, что ты этого старого дурня с собой сюда не взял. Но ничего, как-нибудь и до него доберёмся.";
			link.l1 = "В любое время к вашим услугам. Наёмники, значит? Откуда меня знаете, кому насолил?";
			link.l1.go = "DTSG_RalfFaggl_2";
		break;
		
		case "DTSG_RalfFaggl_2":
			dialog.text = "Да в том-то и дело, что никому. Мы ищем этого старого пердуна, Чарли, а сделать это гораздо проще через тебя, поскольку во время поисков мы узнали, что теперь он на твоём корабле\nЗдесь, конечно, не сельва, так что делать всё придётся быстро, чтоб зеваки не сбежались к дому. Но тут ты хотя бы не уйдёшь от нас.";
			link.l1 = "Полагаю, вся эта история с дуэлью была ловушкой?";
			link.l1.go = "DTSG_RalfFaggl_3";
		break;
		
		case "DTSG_RalfFaggl_3":
			dialog.text = "Поздновато же ты это понял, дружище. В любом случае, нам с тобой так и так пришлось бы драться - я Ральф Фаггл, тоже в любое время к твоим услугам.";
			link.l1 = "Напротив, я уже об этом задумался, потому решил пообщаться с соседями. Кстати, Адамс тоже в этом замешан? А что насчёт Джейн? Неужто и она...";
			link.l1.go = "DTSG_RalfFaggl_4";
		break;
		
		case "DTSG_RalfFaggl_4":
			dialog.text = "Кошка от любопытства сдохла, не слышал? Сказано тебе было - явись на дуэль, значит, явись, а не ходи да разнюхивай. Там-то хоть сбежать бы смог\nСамо собой. Пробить служивого на слезу, а дюже благородного - на честь, отличный план мы придумали с Питером, как по мне. А Джейн тоже поработала на славу.";
			link.l1 = "Скажи хоть, кому понадобилось избавиться от Чарли?";
			link.l1.go = "DTSG_RalfFaggl_5";
		break;
		
		case "DTSG_RalfFaggl_5":
			dialog.text = "Угу, а ещё что тебе сказать? Обойдёшься как-нибудь. Защищайся.";
			link.l1 = "Жаль. Значит, Питера потом спрошу.";
			link.l1.go = "DTSG_RalfFaggl_6";
		break;
		
		case "DTSG_RalfFaggl_6":
			DialogExit();
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl");
			LAi_SetCheckMinHP(sld, 1, false, "DTSG_RalfFaggl_ubit");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_11":
			dialog.text = "О, я смотрю, вы приняли мою историю близко к сердцу и уже наказали Ральфа, капитан.";
			link.l1 = "Само собой, ведь я, как вы заметили, достойный и благородный человек. А сейчас мне придётся наказать и вас. За эту вероломную ловушку.";
			link.l1.go = "DTSG_PiterAdams_12";
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			GiveItem2Character(npchar, "letter_1");
			ChangeItemName("letter_1", "itmname_specialletter");
			ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
		break;
		
		case "DTSG_PiterAdams_12":
			dialog.text = "Вы вольны попытаться, капитан - наверняка вы уже устали.";
			link.l1 = "Значит, сделаем передышку. Заодно расскажете, на кого работаете.";
			link.l1.go = "DTSG_PiterAdams_13";
		break;
		
		case "DTSG_PiterAdams_13":
			dialog.text = "Не обессудьте, но моему патрону бы это не понравилось, даже успешно я разделайся с вами. Что, впрочем, и так сейчас произойдёт.";
			link.l1 = "Да что ж такое!..";
			link.l1.go = "DTSG_PiterAdams_14";
		break;
		
		case "DTSG_PiterAdams_14":
			DialogExit();
			
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, GetCharacterBaseHPValue(sld)/2, GetCharacterBaseHPValue(sld));
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			else
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
				LAi_KillCharacter(sld);
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Sosedi_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_Knippel_40":
			dialog.text = "Поверить не могу, что эти... эти негодяи не просто обманули нас, а врали нам про Королевский Флот! Да как они посмели! Не будь они мертвы, я бы заставил их проглотить по паре книппелей за такое вероломство!..";
			link.l1 = "Люди о чём только не врут, Чарли. Думал, тебе это хорошо известно. Но что тебе наверняка известно, так это то, кто их послал? Ведь это уже не первая ловушка на тебя за последнее время. У этих вон письмо с твоим детальным описанием. Кому же ты так попортил кровь?";
			link.l1.go = "DTSG_Knippel_41";
		break;
		
		case "DTSG_Knippel_41":
			dialog.text = "Ну, я... Возможно, мы найдём что-нибудь ещё в доме Адамсов, сэр?";
			link.l1 = "Уходишь от ответа? Но ты прав, конечно, я всё равно собирался туда заглянуть и перевернуть всё вверх дном. Идём, Чарли.";
			link.l1.go = "DTSG_Knippel_42";
		break;
		
		case "DTSG_Knippel_42":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1 = "ExitFromLocation";
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1.location = PChar.location;
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition = "DTSG_PoP_ProverimSunduk";
		break;
		
		case "DTSG_Knippel_50":
			dialog.text = "Пресвятые книппели, сколько же здесь золота!..";
			link.l1 = "Жаль, что ничего, кроме него, здесь уже нет. 'Джейн' тоже нигде нет. Как думаешь, она жива вообще?..";
			link.l1.go = "DTSG_Knippel_51";
		break;
		
		case "DTSG_Knippel_51":
			dialog.text = "Не знаю, сэр, такие мерзавцы способны сделать что угодно...";
			link.l1 = "Так-то оно так, но сдаётся мне, что ты знаешь всё же больше, чем говоришь. Это не первый раз, когда охотятся именно на тебя. И каждый раз мы находим у них кучу денег.";
			link.l1.go = "DTSG_Knippel_52";
		break;
		
		case "DTSG_Knippel_52":
			dialog.text = "Я не уверен, капитан, но, возможно, это мог быть ростовщик Сент-Джонса.";
			link.l1 = "Чем ты мог ему насолить?";
			link.l1.go = "DTSG_Knippel_53";
		break;
		
		case "DTSG_Knippel_53":
			dialog.text = "Ну... какое-то время назад я занял у него денег, чтобы погасить все свои долги другим людям. Ричард обещал, что уплатит мой долг, но...";
			link.l1 = "Ты думаешь, что он этого не сделал?";
			link.l1.go = "DTSG_Knippel_54";
		break;
		
		case "DTSG_Knippel_54":
			dialog.text = "Раньше бы я ни за что в это не поверил, но то, как он недавно поступил с вами и в спешке покинул Архипелаг вместе с Аби... Возможно, он и о долге забыл. Или не забывал, а попросту ушёл... Ричард поступил, как настоящий dick, сэр. Не удивлюсь, но всё же расстроюсь, если это снова окажется так.";
			link.l1 = "Не будь столь категоричен раньше времени, Чарли. Значит, Сент-Джонс.";
			link.l1.go = "DTSG_Knippel_55";
		break;
		
		case "DTSG_Knippel_55":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			TakeItemFromCharacter(pchar, "letter_1");
			AddQuestRecord("DTSG", "5");
			QuestOpenSeaExit()
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_PiterAdams_20":
			if (CheckAttribute(pchar, "questTemp.DTSG_ZovemMatrosov"))
			{
				dialog.text = "А вот и вы, сударь - похоже, все решили прийти пораньше. Судя по вашему виду, вы довольно легко настроены, вы так уверены в своих силах?";
				link.l1 = "Само собой, ведь это отнюдь не первая дуэль в моей жизни.";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_21";
				ChangeCharacterComplexReputation(pchar, "authority", 1);
			}
			else
			{
				dialog.text = "Я уж боялся, что вы не придёте, сэр. Остальные уже здесь.";
				link.l1 = "Настоящий дворянин может опоздать лишь на свою смерть.";
				link.l1.go = "DTSG_PiterAdams_NN_21";
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
			}
		break;
		
		case "DTSG_PiterAdams_NN_21":
			dialog.text = "Прекрасные слова, сударь!";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_22";
		break;
		
		case "DTSG_PiterAdams_NN_22":
			dialog.text = "Знакомьтесь...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_23":
			dialog.text = "Это наш оппонент, о котором я говорил ранее, Ральф Фаггл.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_24":
			dialog.text = "А это наш секундант, Фредерик Стоукс.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_NN_25":
			dialog.text = "...";
			link.l1 = "Так это и есть Ральф?.. Что-то он не выглядит, как типичный выпивающий сосед.";
			link.l1.go = "DTSG_PiterAdams_NN_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_26":
			dialog.text = "Никогда не знаешь, кем может оказаться твой сосед, не задумывались, господин де Мор? Хе-хе-хе.";
			link.l1 = "Так, значит, всё это - ловушка... Смотрю, вы даже потрясываться перестали. Надоело отыгрывать роль больного лихорадкой?";
			link.l1.go = "DTSG_PiterAdams_NN_27";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_NN_27":
			dialog.text = "Единственное, над чем я мог бы сейчас трястись - от смеха над вашей наивностью.";
			link.l1 = "Ну-ну. Жалею лишь, что ко мне навязался Чарли - одному было бы проще и спокойнее разобраться со всеми вами...";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_21":
			dialog.text = "Ну что ж, замечательно!";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_22";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_22":
			dialog.text = "Позвольте представить...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_23":
			dialog.text = "Это мистер Стоукс, он будет нашим секундантом.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_24":
			dialog.text = "Ну а это - Ральф Фаггл.";
			link.l1 = "Так вот он какой, этот ваш Фаггл? Признаться, я представлял его себе другим. Но ничего, и не с такими справлялся.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_25":
			dialog.text = "Хм, я вот думаю, вы просто наивны, что ничего не понимаете? Или настолько самоуверенны?";
			link.l1 = "И чего же я не понимаю, мистер Адамс? Давайте, удивите меня.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_Nastoroje_26":
			dialog.text = "Обычно они удивляются или пугаются в таких ситуациях, ну да ладно. Тем приятнее будет стереть эту самодовольную ухмылку с вашего лица, мистер де Мор.";
			link.l1 = "Какие угрозы! Разве мы с вами не на одной стороне, Питер?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_27";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_27":
			dialog.text = "Только не говорите мне, что надеетесь вместе с этим стариком одолеть всех нас. Вы в меньшинстве, мой дорогой сэр.";
			link.l1 = "Как я и сказал, это ВЫ не понимаете. Чарли, конечно, поворчал немного, но я всё равно сказал ему на всякий случай привести сюда ребят. Как оказалось, не зря. ПАРНИ, ВСЕ СЮДА!!!";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_28";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_28":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.34, 0.51, 34.93, true, -5.63, -1.20, 57.46);
			DoQuestCheckDelay("DTSG_PoP_Duel_Podkreplenie", 3.0);
			
			int DTSG_PoP_MK;
			if (MOD_SKILL_ENEMY_RATE == 2) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 4) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 6) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 8) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 10) DTSG_PoP_MK = 3;
			
			for (i=1; i<=DTSG_PoP_MK; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_PoP_Matrosy_"+i, "citiz_3"+i, "man", "man", sti(pchar.rank)-5, sti(pchar.nation), -1, false, "quest"));
				GiveItem2Character(sld, "blade_11");
				sld.equip.blade = "blade_11";
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
				LAi_SetHP(sld, 120.0, 120.0);
			}
		break;
		
		case "DTSG_PiterAdams_Nastoroje_29":
			dialog.text = "Что?..";
			link.l1 = "О, так вы из тех, кто в такие моменты удивляется, мистер Адамс? Будем знать.";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_BitvaDuel":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("DTSG_PoP_Matrosy_"+i) != -1)
				{
					sld = CharacterFromID("DTSG_PoP_Matrosy_"+i);
					LAi_SetWarriorType(sld);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_SetCheckMinHP(sld, 10, true, "KnippelRanen");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_PiterAdams_Duel_Pobeda");
		break;
		
		case "DTSG_Knippel_60":
			dialog.text = "Вот так и следует поступать с подобными лживыми мерзавцами. До сих пор не могу поверить, что им хватило духу врать про Королевский Флот! Придушить бы их книппелями!..";
			link.l1 = "Уж в свои-то годы мог бы и знать, что порой у людей нет ничего святого, Чарли. Я ведь сказал, что всё улажу, мог бы и отсидеться на корабле. Хотел убедиться, что я помогу этим 'достойным людям'? И кто опять был прав в том, что всё не так однозначно, как ты подумал?";
			link.l1.go = "DTSG_Knippel_61";
		break;
		
		case "DTSG_Knippel_61":
			dialog.text = "Вы, сэр...";
			link.l1 = "Вот-вот. Но скажи мне. С чего бы кому-то понадобилось устраивать на тебя охоту? Не в первый раз уже.";
			link.l1.go = "DTSG_Knippel_62";
		break;
		
		case "DTSG_Knippel_62":
			dialog.text = "Не знаю, капитан. Старина Чарли - простой парень.";
			link.l1 = "Хм, ну-ну. Ладно, раз уж у наших горе-дуэлянтов не было с собой ничего, что могло бы нам хоть как-то быть полезным... Нет, пойдём поищем что-нибудь в доме этого Адамса.";
			link.l1.go = "DTSG_Knippel_63";
		break;
		
		case "DTSG_Knippel_63":
			DialogExit();
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			AddDialogExitQuestFunction("DTSG_Knippel_64");
		break;
		
		case "DTSG_Knippel_70":
			dialog.text = "Что ж, этой женщины тоже след простыл... Возможно, готовились сбежать из города сразу же после той 'дуэли'? И в спешке - сколько же здесь дублонов!..";
			link.l1 = "Ты прав, потому что золото - не единственное, что они забыли. Ещё одно письмо. Так торопились, что даже забыли сжечь. Взгляни, тебе понравится его содержание.";
			link.l1.go = "DTSG_Knippel_71";
		break;
		
		case "DTSG_Knippel_71":
			TakeItemFromCharacter(pchar, "letter_1");
			dialog.text = "(читает) Ну, насчёт 'старый' я бы поспорил.";
			link.l1 = "Сейчас не об этом. Это уже второй раз, когда за тобой посылают наймитов и снабжают их деньгами и информацией. И им нужен именно ты. Ты же простой парень, кого ты мог так разозлить?";
			link.l1.go = "DTSG_Knippel_72";
		break;
		
		case "DTSG_Knippel_72":
			dialog.text = "Есть у меня одна догадка, сэр, всего одна, и мне бы очень не хотелось, чтобы она оказалась правдой.";
			link.l1 = "Значит, скорее всего, именно она и сбудется. Говори.";
			link.l1.go = "DTSG_Knippel_73";
		break;
		
		case "DTSG_Knippel_73":
			dialog.text = "У меня когда-то были долги самым разным людям в Сент-Джонсе, и...";
			link.l1 = "... и теперь ты думаешь, что они охотятся на тебя? А многие ли могут себе позволить наёмников и такие суммы заодно?";
			link.l1.go = "DTSG_Knippel_74";
		break;
		
		case "DTSG_Knippel_74":
			dialog.text = "Верно мыслите, сэр. По итогу я погасил почти все свои долги, заняв у ростовщика. Ему всё это по карману, конечно же. Но...";
			link.l1 = "Но что? Уплатим твой долг, и всё. Что тебя беспокоит?";
			link.l1.go = "DTSG_Knippel_75";
		break;
		
		case "DTSG_Knippel_75":
			dialog.text = "Видите ли, капитан, Ричард мне обещал, что непременно сам погасит его ради меня.";
			link.l1 = "Думаешь, он этого не сделал?";
			link.l1.go = "DTSG_Knippel_76";
		break;
		
		case "DTSG_Knippel_76":
			dialog.text = "Я уже не знаю, что и думать, сэр. Всё время, что мы были знакомы, я знал его, как образцового джентльмена. Но после того, как он бросил вас и сбежал с Абигайль... Удивлён уже не буду. Потому и сказал, что не хотел бы, чтобы это оказалось правдой.";
			link.l1 = "Догадки нужно сначала проверять, а потом уже только расстраиваться, Чарли. Пойдём, заодно снова побываешь в Сент-Джонсе.";
			link.l1.go = "DTSG_Knippel_77";
		break;
		
		case "DTSG_Knippel_77":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			AddQuestRecord("DTSG", "6");
			QuestOpenSeaExit()
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_Knippel_PoPDuelTime":
			dialog.text = "Капитан!!!";
			link.l1 = "Что такое, Чарли, что-то случилось?";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_2";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_2":
			dialog.text = "Случилось?! Только не говорите, что забыли про дуэль, сэр! Возможно, беднягу Адамса уже покромсали, пока вы прохлаждаетесь тут!";
			link.l1 = "Точно!.. Я немедленно отправлюсь за город.";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_3";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_3":
			DialogExit();
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			DoQuestReloadToLocation("PortPax_ExitTown", "reload", "reload3", "");
		break;
		
		case "DTSG_AntiguaArest":
			dialog.text = "Капитан Шарль де Мор? Это Чарли Книппель с вами?";
			link.l1 = "Нет, это...";
			link.l1.go = "DTSG_AntiguaArest_2";
		break;
		
		case "DTSG_AntiguaArest_2":
			dialog.text = "Не отрицайте, сэр - Чарли знают все в этом городе.";
			link.l1 = "Тогда зачем было спрашивать? Однако чем могу помочь?";
			link.l1.go = "DTSG_AntiguaArest_3";
		break;
		
		case "DTSG_AntiguaArest_3":
			dialog.text = "Ничем. Пожалуйста, просто не оказывайте сопротивление - Чарли разыскивается в этом городе. Мы вынуждены взять его под стражу.";
			link.l1 = "Могу я узнать, какие обвинения предъявлены моему человеку? Это из-за его долга? Я могу уплатить его за него. Давайте прямо сейчас сходим к ростовщику, в вашем присутствии.";
			link.l1.go = "DTSG_AntiguaArest_4";
		break;
		
		case "DTSG_AntiguaArest_4":
			dialog.text = "Долга? Впервые слышу. Я не знаю подробностей, но, прошу, вас, не усложняйте - я просто выполняю приказ.";
			link.l1 = "Ох, ну хорошо...";
			link.l1.go = "DTSG_AntiguaArest_5";
		break;
		
		case "DTSG_AntiguaArest_5":
			StartInstantDialog("Knippel", "DTSG_AntiguaArest_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_AntiguaArest_6":
			dialog.text = "Капитан...";
			link.l1 = "Чарли, если мы сейчас сбежим, награда за наши с тобой головы будет ещё выше. И не прорываться же с боем? Я постараюсь тебя вытащить, только не натвори глупостей!";
			link.l1.go = "DTSG_AntiguaArest_7";
		break;
		
		case "DTSG_AntiguaArest_7":
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "8");
			pchar.questTemp.DTSG_KnippelDolg = true;
			
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
			sld.location = "None";
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("DTSG_AntiguaSold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
				sld.location = "None";
			}
		break;
		
		case "DTSG_AntiguaStrazhBank":
			dialog.text = "Прекратите сейчас же шуметь и угрожать этому человеку, мистер. Следуйте за мной.";
			link.l1 = "Я никому не угрожал, произошла ошибка. Мне просто нужно, чтобы он ответил мне на несколько вопросов.";
			link.l1.go = "DTSG_AntiguaStrazhBank_2";
		break;
		
		case "DTSG_AntiguaStrazhBank_2":
			dialog.text = "Именно поэтому он трясётся от страха, а вы кричите на всю округу? Отвечать придётся вам, причём перед законом.";
			link.l1 = "А если я принесу извинения и выйду отсюда?";
			link.l1.go = "DTSG_AntiguaStrazhBank_3";
		break;
		
		case "DTSG_AntiguaStrazhBank_3":
			dialog.text = "Чтобы потом снова сюда проникнуть и закончить то, чему я помешал? Я, хоть и служивый, но что, дурак, что ли, по-вашему?";
			link.l1 = "Видимо, дурак, раз не хочешь решить всё мирно. Видит Бог, я не хотел до этого доводить...";
			link.l1.go = "DTSG_AntiguaStrazhBank_4";
		break;
		
		case "DTSG_AntiguaStrazhBank_4":
			DialogExit();
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_AntiguaStrazhBank_Ubili");
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki":
			dialog.text = "Вы убили его!..";
			link.l1 = "Считайте, что вашими руками, сударь. Можно было просто ответить на мои вопросы, а не орать во весь голос. Клянусь, ещё один крик - и я вышибу вам мозги.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_V1";
			link.l2 = "Да, убил. Он вынудил меня. Но у вас же голова не опилками набита, и вы его примеру не последуете, верно?";
			link.l2.go = "DTSG_AntiguaUsurer_PosleDraki_V2";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V1":
			dialog.text = "Что вам нужно?!";
			link.l1 = "Какое-то время назад Чарли Книппель занимал у вас денег. Его друг обещал уплатить его долг, но, видимо, так и не сделал этого? Я требую, чтобы вы немедленно прекратили посылать за нами наёмников. Я готов выплатить долг Чарли хоть сейчас, если эта сумма мне по карману.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexLandExpToScill(100, 0, 0);
			AddComplexSeaExpToScill(0, 0, 0, 0, 0, 0, 100);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V2":
			dialog.text = "Что вам нужно?!";
			link.l1 = "Какое-то время назад Чарли Книппель занимал у вас денег. Его друг обещал уплатить его долг, но, видимо, так и не сделал этого? Я требую, чтобы вы немедленно прекратили посылать за нами наёмников. Я готов выплатить долг Чарли хоть сейчас, если эта сумма мне по карману.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_3":
			dialog.text = "Чарли?! Я бы ни за что так с ним не поступил, он хороший, честный человек\nК тому же, его долг уже давно погашен. Мистер Флитвуд, капитан 'Валькирии', отдал всё до последнего песо.";
			link.l1 = "Вот как? Я знаю, кто он. Вот так бы и сразу. Прошу прощения за беспокойство, до свидания.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_4";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_4":
			dialog.text = "Просите прощения?! Да вы угрожали мне! И убили человека!..";
			link.l1 = "Кажется, вы забыли, что я вам сказал? Ещё один крик - и присоединитесь к нему. Всего доброго.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_5";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_5":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], true);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			npchar.dialog.filename = "Usurer_dialog.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetOwnerType(npchar);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "9");
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1 = "location";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition = "DTSG_AntiguaTrevoga";
		break;
		
		case "DTSG_Killer":
			dialog.text = "Ты всё ещё здесь, а не в петле? Ну, привет тебе от Сассекса, Чарли.";
			link.l1 = "Привет и вам, кем бы вы ни были.";
			link.l1.go = "DTSG_Killer_2";
			CharacterTurnToLoc(npchar, "goto", "goto9");
		break;
		
		case "DTSG_Killer_2":
			dialog.text = "А, Шарль де Мор. Хорошо, что вы решили навестить беднягу Чарли. Впрочем, иначе и быть не могло, мы на это и рассчитывали.";
			link.l1 = "А 'мы' - это кто?";
			link.l1.go = "DTSG_Killer_3";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "DTSG_Killer_3":
			dialog.text = "Неважно кто. Вы нас уже порядком утомили, мистер де Мор. Думаю, они не будут против, если я разберусь и с Чарли, и с вами.";
			link.l1 = "Ну, раз уж наша с Книппелем песенка спета, может, скажете нам по доброте душевной, кого мы так вывели из себя? Мы больше так не будем. Обещаем. И что за Сассекс?";
			link.l1.go = "DTSG_Killer_4";
		break;
		
		case "DTSG_Killer_4":
			dialog.text = "Долг службы не позволяет. Я, в отличие от вас, человек дела, а не слов.";
			link.l1 = "Да когда мне уже кто-нибудь всё объяснит, как следует?!";
			link.l1.go = "DTSG_Killer_5";
		break;
		
		case "DTSG_Killer_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			
			for (i=1; i<=12; i++)
			{
				if (GetCharacterIndex("SentJonsPrisoner_"+i) != -1)
				{
					sld = CharacterFromID("SentJonsPrisoner_"+i);
					sld.lifeday = 0;
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = GetCharacter(i);
				if (sld.city == "sentjons" && sld.location == "SentJons_prison")
				{
					sld.lifeday = 0;
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			
			sld = CharacterFromID("SentJonsJailOff");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_SentJonsJailOff", "off_eng_1", "man", "man", 30, PIRATE, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto18");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			GiveItem2Character(sld, "cirass3");
			EquipCharacterByItem(sld, "cirass3");
			
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_"+i, "sold_eng_"+(rand(7)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto22");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			
			for (i=4; i<=7; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_"+i, "sold_eng_"+(rand(7)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			
			/*sld = CharacterFromID("SentJons_Mayor");
			LAi_group_Attack(sld, Pchar);*/
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_TurmaDayPobeda");
		break;
		
		case "DTSG_KnippelDaySpasen":
			dialog.text = "Книппель мне в корму, ну и резню вы здесь учинили, капитан!";
			link.l1 = "Ты против? Ты бы предпочёл виселицу? Ну или гнить здесь Бог знает сколько, Чарли?";
			link.l1.go = "DTSG_KnippelDaySpasen_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_KnippelDaySpasen_2":
			dialog.text = "Нет, сэр. Благодарю вас за спасение\nПризнаться, я удивлён, что вы всё же пришли, учитывая, как легко вы позволили меня им забрать. И удивлён, как легко вы справились с тем, кто охранял меня - он был одним из морских лис.";
			link.l1 = "Я ведь сказал, что вытащу тебя, зря ты сомневался. Ну, что стоишь? Выходи из этой клетки, а то сюда сейчас весь гарнизон сбежится.";
			link.l1.go = "DTSG_KnippelDaySpasen_3";
		break;
		
		case "DTSG_KnippelDaySpasen_3":
			dialog.text = "Уже иду, капитан.";
			link.l1 = "...";
			link.l1.go = "DTSG_KnippelDaySpasen_4";
		break;
		
		case "DTSG_KnippelDaySpasen_4":
			DialogExit();
			
			Pchar.GenQuest.Hunter2Pause = true;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("DTSG_TurmaDayPobeda_2", 1.0);
		break;
		
		case "DTSG_KnippelDaySpasen_5":
			dialog.text = "О-ох, сэр, даже не верится...";
			link.l1 = "Кстати, скажи мне, что они тебе предъявили по итогу? И что ещё за Сассекс?";
			link.l1.go = "DTSG_KnippelDaySpasen_6";
		break;
		
		case "DTSG_KnippelDaySpasen_6":
			dialog.text = "Не знаю, сэр. Понятия не имею, что они хотели этим сказать...";
			link.l1 = "Ладно, позже это выясним. Сейчас нам нужно бежать отсюда.";
			link.l1.go = "DTSG_KnippelDaySpasen_7";
		break;
		
		case "DTSG_KnippelDaySpasen_7":
			DialogExit();
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddPassenger(pchar, npchar, false);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			AddQuestRecord("DTSG", "12");
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_AntiguaNightPirs":
			dialog.text = "Какие ваши дальнейшие действия, сэр? Выбивать дурь из этого кровопийцы средь бела дня - рискованное дельце. Тут есть над чем позвенеть книппелями.";
			link.l1 = "А ты как раз подкинул мне идею. Зачем выбивать из него дурь средь бела дня, если это можно сделать сейчас, под покровом ночи?";
			link.l1.go = "DTSG_AntiguaNightPirs_2";
		break;
		
		case "DTSG_AntiguaNightPirs_2":
			dialog.text = "Разрази меня гром, прекрасная идея, капитан!";
			link.l1 = "Ещё бы. Скажи, Чарли, ты ведь жил здесь раньше какое-то время. Ты знаешь, где живёт ростовщик?";
			link.l1.go = "DTSG_AntiguaNightPirs_3";
		break;
		
		case "DTSG_AntiguaNightPirs_3":
			dialog.text = "Раньше знал, сэр, но дело в том, что, когда я был здесь в последний раз, он продавал свой дом. А где находится новый - без понятия.";
			link.l1 = "Да уж, проблема...";
			link.l1.go = "DTSG_AntiguaNightPirs_4";
		break;
		
		case "DTSG_AntiguaNightPirs_4":
			dialog.text = "Я уверен, что вы что-нибудь придумаете, капитан, в конце концов, вы одолели самого Лукаса Роденбурга!";
			link.l2 = "И правда. Ладно, разберусь. Хотя, если бы ты знал, где дом ростовщика, было бы лучше!";
			link.l2.go = "DTSG_AntiguaIskat_1";
			link.l1 = "Пожалуй. Но утро вечера мудренее, Чарли. Предлагаю передохнуть с дороги и пойти днём - не убивать же мы его собираемся.";
			link.l1.go = "DTSG_AntiguaSpat_1";
		break;
		
		case "DTSG_AntiguaSpat_1":
			dialog.text = "Вы уверены в этом, сэр? Мы потеряем эффект неожиданности.";
			link.l1 = "Уверен. Я устал. К тому же, я хочу просто поговорить, максимум - припугнуть.";
			link.l1.go = "DTSG_AntiguaSpat_2";
		break;
		
		case "DTSG_AntiguaSpat_2":
			TavernWaitDate("wait_day");
			DoQuestReloadToLocation("SentJons_tavern_upstairs", "goto", "goto2", "DTSG_AntiguaSpat_3");
		break;
		
		case "DTSG_AntiguaIskat_1":
			dialog.text = "Чего не знаю - того не знаю, простите, сэр.";
			link.l1 = "А, пустое, займёмся лучше поисками.";
			link.l1.go = "DTSG_AntiguaIskat_2";
		break;
		
		case "DTSG_AntiguaIskat_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			AddQuestRecord("DTSG", "13");
			pchar.questTemp.DTSG_NightIskat = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.GenQuest.CannotWait = true;
			pchar.questTemp.TimeLock = true;
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood":
			dialog.text = "Вы думаете о том же, о чём и я, сэр?";
			link.l1 = "Боюсь, что да, Чарли. Другого столь известного капитана с этой фамилией на Архипелаге не было. К тому же, Ричард как раз отправился в Лондон. Так что вряд ли это совпадение.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_2";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_2":
			dialog.text = "Это ужасно... И хотя я тогда наговорил много ласковых про него, я никогда не желал ему чего-то подобного! А бедняжка Аби!.. Она ведь ждала малыша. Надеюсь, она жива...";
			link.l1 = "Воистину, никому не пожелаешь. Да, будем надеяться, что с Аби всё в порядке. У тебя есть предположения, кто мог так поступить с Диком? У него были какие-нибудь могущественные недоброжелатели, о которых он тебе говорил?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_3";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_3":
			dialog.text = "Вы, должно быть, шутите, капитан. Не знаю, как в старушке Европе, а здесь, на Архипелаге, едва ли не каждый голландец мечтал о смерти Ричарда, от мала до велика.";
			link.l1 = "И то верно. Возможно, кто-то из подобных людей хорошенько так затратился и послал убийц в погоню, в Старый Свет. Как думаешь, Чарли, может ли быть так, что за нападениями на тебя тоже стоит не этот крохобор ростовщик, а тот таинственный враг Ричарда?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_4";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_4":
			dialog.text = "Не знаю, сэр. Всякое может быть. Но тогда это серьёзно усложняет нам всем жизнь...";
			link.l1 = "Да, ты прав, Чарли, мне бы тоже этого не хотелось.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_5";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_5":
			DialogExit();
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "14");
			pchar.questTemp.DTSG_Nastoroje2 = true;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_NightDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_NightDom.win_condition = "DTSG_NightDom";
		break;
		
		case "DTSG_NightRostovshik":
			dialog.text = "Что, кто... ЧТО?! Что происходит?.. Кто вы?!..";
			link.l1 = "Попрошу не шуметь. Если бы я хотел убить вас - вы бы уже не проснулись. Так что давайте не будем усложнять или сокращать жизнь. Ни мою, ни вашу. Кивните, если поняли.";
			link.l1.go = "DTSG_NightRostovshik_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_NightRostovshik_2":
			dialog.text = "Угу...";
			link.l1 = "Очень хорошо. Успокойтесь - я здесь не для того, чтобы ограбить, похитить вас или ещё как-нибудь навредить.";
			link.l1.go = "DTSG_NightRostovshik_3";
		break;
		
		case "DTSG_NightRostovshik_3":
			dialog.text = "Тогда... зачем вы здесь? Почему вы просто не могли прийти утром?";
			link.l1 = "Потому что за моим другом охотится некий богатый влиятельный человек. У нас есть основания полагать, что это вы, так что, скорее всего, ему опасно разгуливать на улицах средь бела дня.";
			link.l1.go = "DTSG_NightRostovshik_4";
		break;
		
		case "DTSG_NightRostovshik_4":
			dialog.text = "Но я правда не понимаю, о чём вы, сэр...";
			link.l1 = "Чарли Книппель. Его все в городе знают. Напрягите память. Он должен вам.";
			link.l1.go = "DTSG_NightRostovshik_5";
		break;
		
		case "DTSG_NightRostovshik_5":
			dialog.text = "Наш старина Чарли?? Это, конечно, так, но его долг уже давно уплачен, пусть и не им лично.";
			link.l1 = "И кем же был этот благодетель?";
			link.l1.go = "DTSG_NightRostovshik_6";
		break;
		
		case "DTSG_NightRostovshik_6":
			dialog.text = "Его капитан, Ричард Флитвуд. Если не верите, могу показать свои записи об этом.";
			link.l1 = "Флитвуд, значит? Тогда верю. Значит, вы не посылали за Чарли наёмников?";
			link.l1.go = "DTSG_NightRostovshik_7";
		break;
		
		case "DTSG_NightRostovshik_7":
			dialog.text = "Нет, конечно, как можно?? Да и скажите, какой в этом смысл?";
			link.l1 = "Действительно. Что же, прошу прощения за столь поздний визит. Доброй ночи.";
			link.l1.go = "DTSG_NightRostovshik_8";
		break;
		
		case "DTSG_NightRostovshik_8":
			DialogExit();
			
			PChar.quest.DTSG_NightDom_3.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_NightDom_3.win_condition = "DTSG_NightDom_3";
			
			LAi_CharacterDisableDialog(npchar);
			Pchar.GenQuest.Hunter2Pause = true;
			AddQuestRecord("DTSG", "15");
		break;
		
		case "DTSG_NightKiller":
			dialog.text = "Что, Чарли, надеялся переждать эту ночь у своего бывшего покровителя? Нет его там. Ничего, вы очень скоро увидитесь. Привет тебе от Сассекса.";
			link.l1 = "Мы и так это знали. А кто такой Сассекс? И кто вы?";
			link.l1.go = "DTSG_NightKiller_2";
		break;
		
		case "DTSG_NightKiller_2":
			dialog.text = "Это вас никак не касается, мистер де Мор. И всё же, вы оказались в это вовлечены, и гораздо активнее, чем нам бы того хотелось. Слишком активно. Вы начинаете нам надоедать.";
			link.l1 = "И кому же? Только не говорите, что я переспал с жёнушкой очень влиятельного и очень рассерженного английского чиновника. Что вам нужно?";
			link.l1.go = "DTSG_NightKiller_3";
		break;
		
		case "DTSG_NightKiller_3":
			dialog.text = "Очень смешно. Нашли, когда язвить. Видимо, то, что мне о вас говорили, оказалось правдой\nЧто же нам нужно? По-хорошему, нам нужен только Чарли. Но, учитывая, сколько неудобств вы нам доставили, на этот раз это касается и вас - вы бы всё равно и дальше совали свой нос, куда не следует.";
			link.l1 = "Я так полагаю, нас берут под арест?";
			link.l1.go = "DTSG_NightKiller_4";
		break;
		
		case "DTSG_NightKiller_4":
			dialog.text = "Арест? Не-е-ет, дорогой сэр, время полумер прошло. Это казнь, капитан де Мор.";
			link.l1 = "Согласен. Вопрос только, чья.";
			link.l1.go = "DTSG_NightKiller_5";
		break;
		
		case "DTSG_NightKiller_5":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DTSG_Killers_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_NightKiller_Pobeda");
		break;
		
		case "DTSG_Knippel_80":
			dialog.text = "Не думал, что в это будут вовлечены даже морские лисы...";
			link.l1 = "Ну, всякое бывает. И всё бывает впервые. Скажи мне, Чарли, кто такой Сассекс?";
			link.l1.go = "DTSG_Knippel_81";
		break;
		
		case "DTSG_Knippel_81":
			dialog.text = "Я...";
			link.l1 = "Ты разве не видишь, как всё далеко зашло? И, похоже, мы с тобой в одной лодке, Чарли. Так что я имею право знать подробности.";
			link.l1.go = "DTSG_Knippel_82";
		break;
		
		case "DTSG_Knippel_82":
			dialog.text = "Конечно, капитан. Но не здесь же, верно? Давайте оторвёмся от острова и поговорим на корабле.";
			link.l1 = "Твоя правда. Ну хорошо, в таком случае, поспешим.";
			link.l1.go = "DTSG_Knippel_83";
		break;
		
		case "DTSG_Knippel_83":
			DialogExit();
			AddQuestRecord("DTSG", "16");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			chrDisableReloadToLocation = false;
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom":
			dialog.text = "Вызывали, капитан?";
			link.l1 = "Да, Чарли. Нам нужно поговорить. Думаю, ты уже догадываешься, о чём.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
			//LAi_LocationDisableOfficersGen("SentJons_town", true);
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_2":
			dialog.text = "Да, сэр...";
			link.l1 = "Хорошо. Расскажи, почему за тобой охотятся твои же соотечественники, в том числе элитные силы, ведь ты отнюдь не преступник или ещё кто.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_3";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_3":
			dialog.text = "Я правда не знаю, сэр...";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Это не шутки, Чарли. Тот, кто за тобой охотится, может отдавать приказы морским лисам. Вероятно, он также стоит за убийством Ричарда. Так что если у тебя есть мысли - поделись. Что за привет от Сассекса, кто это?";
			}
			else
			{
				link.l1 = "Прекрати отводить взгляд, Чарли. Я вижу, что тебе что-то известно. Как твой капитан, я приказываю тебе рассказать мне всё, как есть. Кто такой Сассекс?";
			}
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_4";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_4":
			dialog.text = "Хорошо, капитан. Сассекс - это не человек. Это... корабль.";
			link.l1 = "Привет от корабля? Это какая-то бессмыслица.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_5";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_5":
			dialog.text = "Сейчас я вам всё объясню. Позвольте, я присяду, сэр? История будет долгой и не слишком приятной.";
			link.l1 = "Конечно, Чарли. В ногах правды нет. Продолжай.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_6";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_6":
			DialogExit();
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			SetLaunchFrameFormParam(StringFromKey("Knippel_11", NewStr()), "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
			LaunchFrameForm();
			//DoQuestReloadToLocation("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
		break;
		
		case "DTSG_Kurier":
			dialog.text = "Эй, Чарли, я от капитана Флитвуда. Он хочет тебя видеть.";
			link.l1 = "Спасибо, приятель. Что-то случилось? Обычно он всё сразу с тобой передавал.";
			link.l1.go = "DTSG_Kurier_2";
		break;
		
		case "DTSG_Kurier_2":
			dialog.text = "Не знаю. Говорит, что хочет обсудить с тобой это напрямую. Так что это уже ваши дела, сами разбирайтесь.";
			link.l1 = "Ох, дрянное у меня предчувствие, книппель мне в корму...";
			link.l1.go = "DTSG_Kurier_3";
		break;
		
		case "DTSG_Kurier_3":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "DTSG_KD1", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			/*PChar.quest.DTSG_KD1.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD1.win_condition.l1.location = "SentJons_houseH1";
			PChar.quest.DTSG_KD1.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD1.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_KD1.win_condition = "DTSG_KD1";
			
			PChar.quest.DTSG_KD2.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD2.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_KD2.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD2.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_KD2.win_condition = "DTSG_KD2";*/
			
			pchar.questTemp.Knippel.Soldiers_1 = true;
		break;
		
		case "DTSG_Cortny":
			dialog.text = "...";
			link.l1 = "Доброй ночи, сэр!";
			link.l1.go = "DTSG_Cortny_2";
		break;
		
		case "DTSG_Cortny_2":
			dialog.text = "Доброй. Позвольте пройти.";
			link.l1 = "Конечно, проходите, прошу прощения, сэр.";
			link.l1.go = "DTSG_Cortny_3";
		break;
		
		case "DTSG_Cortny_3":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			/*PChar.quest.DTSG_KD4.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD4.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_KD4.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD4.win_condition.l1.locator = "reload2";
			PChar.quest.DTSG_KD4.win_condition = "DTSG_KD4";*/
			DoQuestCheckDelay("DTSG_KD3_2", 3.0);
			locCameraSleep(true);
			
			sld = CharacterFromID("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Fleetwood";
			sld.greeting = "";
		break;
		
		case "DTSG_Fleetwood":
			dialog.text = "А, это уже ты, Чарли. Заходи, заходи. Закрой за собой дверь.";
			link.l1 = "Доброй ночи, капитан. А что такое? И что это был за человек? Самовлюблённый индюк...";
			link.l1.go = "DTSG_Fleetwood_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Fleetwood_2":
			dialog.text = "Этого я сказать не могу. Как и допустить, чтобы кто-то подслушал наш с тобой разговор. Никому о нём не говори. Понял меня?";
			link.l1 = "Да, сэр. Что-то произошло? Вы выглядите на удивление встревоженным, на вас это не похоже.";
			link.l1.go = "DTSG_Fleetwood_3";
			//locCameraFromToPos(0.77, 1.87, -0.42, true, -1.34, -0.10, -1.35);
		break;
		
		case "DTSG_Fleetwood_3":
			dialog.text = "Тебе кажется. Ты тоже отнюдь не цветёшь и пахнешь - ночь, в конце концов\nНо, боюсь, на сегодня твой сон окончен, друг мой - у нас срочное и засекреченное поручение.";
			link.l1 = "И в чём оно будет состоять, капитан?";
			link.l1.go = "DTSG_Fleetwood_4";
		break;
		
		case "DTSG_Fleetwood_4":
			dialog.text = "В устранении предателя. Из своих. В скором времени у берегов Доминики покажется дипломатическое судно из Старого Света - фрегат 'Сассекс'. Официально они должны выторговать хорошее соглашение с голландцами. На деле же...";
			link.l1 = "... неужели передать данные нашим врагам, сэр?";
			link.l1.go = "DTSG_Fleetwood_5";
		break;
		
		case "DTSG_Fleetwood_5":
			dialog.text = "Бери выше. Полностью перейти на его сторону. И хотя после пересечения Атлантики они будут измотаны, в конце концов, это добрый фрегат, который наверняка попытается скрыться, напади мы на тяжёлом судне\nТак что действовать необходимо быстро и решительно. Мы можем полагаться только на 'Валькирию' - лишь ей что-то подобное по плечу.";
			link.l1 = "А справится ли старушка 'Валькирия' с фрегатом?..";
			link.l1.go = "DTSG_Fleetwood_6";
		break;
		
		case "DTSG_Fleetwood_6":
			dialog.text = "Ха-ха, Чарли, неужто ты сомневаешься в своём капитане? К тому же, как я сказал, они будут измождены. Если атакуем внезапно - все преимущества на нашей стороне.";
			link.l1 = "Да я бы никогда! Но, надеюсь, вы знаете, что делаете, сэр...";
			link.l1.go = "DTSG_Fleetwood_7";
		break;
		
		case "DTSG_Fleetwood_7":
			dialog.text = "Уверен в этом. И ещё кое-что. Этот перебежчик занимает не последнее положение в самом Парламенте, понимаешь? У него могут быть свои глаза и уши повсюду - не только дома, но и уже заранее здесь, на Архипелаге. Поэтому нигде в городе не упоминай о 'Сассексе' и иных деталях нашего задания.";
			link.l1 = "Могли бы и не говорить, сэр. Вы всегда можете положиться на старину Чарли.";
			link.l1.go = "DTSG_Fleetwood_8";
		break;
		
		case "DTSG_Fleetwood_8":
			dialog.text = "Я знаю это. Просто ставки на этот раз высоки, как никогда. Собери свои вещи и приготовься - отчаливаем на рассвете.";
			link.l1 = "Так точно. Ещё раз доброй ночи, сэр.";
			link.l1.go = "DTSG_Fleetwood_9";
		break;
		
		case "DTSG_Fleetwood_9":
			DeleteAttribute(pchar,"questTemp.TimeLock");
			SetCurrentTime(11, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("SentJons_houseH1", "reload", "reload1", "DTSG_KD6");
		break;
		
		case "DTSG_Knippel_SamSoboi":
			dialog.text = "Никогда не видел Ричарда таким... Он был так встревожен или даже... напуган?";
			link.l1 = "Вот только чем? Он даже со мной не решился поделиться этим. Ну ничего. Он отличный капитан, так что наверняка мы справимся с этим фрегатом и его уставшей командой.";
			link.l1.go = "DTSG_Knippel_SamSoboi_2";
			DeleteAttribute(pchar, "questTemp.lockedMusic");
		break;
		
		case "DTSG_Knippel_SamSoboi_2":
			DialogExit();
			SetLaunchFrameFormParam("17 августа 1654 г."+ NewStr() +"к юго-востоку от острова Доминика", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Ship_deck_Big", "reload", "reload1", "DTSG_ProshloeDominika_2");
			LaunchFrameForm();
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_1");
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_2");
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_3");
		break;
		
		case "DTSG_Fleetwood_10":
			dialog.text = "'Сассекс' на горизонте, Чарли, приготовься.";
			link.l1 = "Всегда готов, капитан.";
			link.l1.go = "DTSG_Fleetwood_11";
		break;
		
		case "DTSG_Fleetwood_11":
			dialog.text = "Очень хорошо. Рассчитываю на тебя и твои книппеля. Постарайся как можно скорее изрешетить их паруса, а лучше - и вовсе сбить мачту-другую. Ввязываться в рискованный бой на потопление нет никакого смысла, так что я постараюсь взять их на абордаж\nК тому же, нам крайне необходимо удостовериться, что предатель мёртв - так что если уж мы их потопим, потом всё равно придётся сблизиться и сделать так, чтобы выживших не осталось.";
			link.l1 = "И погубить столько соотечественников из-за одного предателя...";
			link.l1.go = "DTSG_Fleetwood_12";
		break;
		
		case "DTSG_Fleetwood_12":
			dialog.text = "Увы. Мне тоже очень тяжело, Чарли. Но приказ есть приказ. По крайней мере, мы делаем это не забавы ради. Так что давай лучше поскорее покончим с этим.";
			link.l1 = "Да, сэр...";
			link.l1.go = "DTSG_Fleetwood_13";
		break;
		
		case "DTSG_Fleetwood_13":
			DialogExit();
			//EndQuestMovie();
			AddItems(pchar, "potion4", 10);
			AddItems(pchar, "bullet", 10);
			AddItems(pchar, "GunPowder", 10);
			AddItems(pchar, "grapeshot", 10);
			AddItems(pchar, "cartridge", 10);
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
			PlaySound("interface\MusketFire1.wav");
			PlaySound("interface\MusketFire1.wav");
			
			SetLaunchFrameFormParam("2 часа спустя..."+ NewStr() +"Абордаж 'Сассекса'", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Location_reserve_06", "rld", "aloc14", "DTSG_ProshloeDominika_12");
			LaunchFrameForm();
			
			n = Findlocation("Location_reserve_06");
			DeleteAttribute(&locations[n], "IslandId");
			DeleteAttribute(&locations[n], "type");
			DeleteAttribute(&locations[n], "models");
			DeleteAttribute(&locations[n], "environment");
			DeleteAttribute(&locations[n], "Box1");
			DeleteAttribute(&locations[n], "Box2");
			DeleteAttribute(&locations[n], "Box3");
			Locations[n].id.label = "Orlop deck";
			Locations[n].filespath.models = "locations\decks\oldeck";
			Locations[n].image = "loading\Boarding_B" + rand(3) + ".tga";
			//Sound
			locations[n].type = "deck_fight";
			//Models
			//Always
			Locations[n].models.always.ODeck = "oldeck";
			Locations[n].models.always.locators = "oldeck_locators";

			//Day
			Locations[n].models.day.charactersPatch = "oldeck_patch";
			Locations[n].models.day.fonar = "oldeck_fday";
			//Night
			Locations[n].models.night.charactersPatch = "oldeck_patch";
			Locations[n].models.night.fonar = "oldeck_fnight";
			//Environment
			Locations[n].environment.sea = "true";
			Locations[n].environment.weather = "true";
		break;
		
		case "DTSG_Graf_Sheffild_1":
			//StartQuestMovie(true, false, true);
			dialog.text = "Остановитесь! Я готов сдать вам шпагу и обсудить ваши требования. Но для начала немедленно представьтесь! Кто вы такой и как посмели напасть на нас?! Это измена!";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_3":
			dialog.text = "Капитан Ричард Флитвуд. А вы, должно быть, граф Шеффилд? И вы совершенно правы, это измена.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_5";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_5":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_6":
			dialog.text = "Вы знаете, кто я? Проклятье! Так и знал, что нечто подобное произойдёт, крысы повсюду, просил, просил же выделить для меня линейный корабль...";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_7";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_7":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_8":
			dialog.text = "Он бы вас не спас, лишь продлил бы неизбежное, ибо мне пришлось бы искать другой подход. И да, говоря об измене, я подразумевал вашу, граф Шеффилд.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_9";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_9":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_10":
			dialog.text = "Тогда вы ничего обо мне не знаете, мистер! Всем известно, что нет более верного Англии человека, чем я! Вы серьёзно пожалеете о своей ошибке, попомните мои слова.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_12";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_12":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_13":
			dialog.text = "Мне не о чем жалеть, ведь это не я перехожу на сторону голландцев.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_16":
			dialog.text = "Что?! Что за чушь вы мелете?! Вами попросту воспользовались, а вы, как полоумная гончая, что взяла ложный след\nКхм, это правда, я действительно направляюсь на переговоры с Голландской Вест-Индской Торговой Компанией. Но в интересах нашей с вами Англии, капитан. Произошла страшная ошибка, но мы всё ещё можем её исправить.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_17";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_17":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_18":
			dialog.text = "Боюсь, что это не мне решать. И, уж тем более, не вам. Вы выбрали не ту сторону, джентльмены. Прощайте.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;

		case "DTSG_Graf_Sheffild_19":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Fleetwood");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Graf_Sheffild_20", 0.9);
		break;
		
		case "DTSG_Graf_Sheffild_22":
			dialog.text = "Здесь закончили. Я уж думал, этот толстяк так и не прекратит свои визги. Ох уж эти графы, да, Чарли?";
			link.l1 = "Я вот думаю, сэр, а что, если полковник ошибся? Или, упаси Господь, соврал нам, чтобы избавиться от графа?";
			link.l1.go = "DTSG_Graf_Sheffild_23";
		break;
		
		case "DTSG_Graf_Sheffild_23":
			dialog.text = "Послушай меня, мой друг. И послушай внимательно. Наша служба очень опасна и трудна, во всех смыслах. И всякое может быть в ней - печальная ошибка, нелепое совпадение или коварное предательство\nСтране служить - это тебе не только книппелями пушки заряжать, Чарли. Это принимать трудные решения. А нам - эти самые решения исполнять.";
			link.l1 = "Но что, если однажды мы прольём невинную кровь, капитан? Это будет на наших руках, нашей совести.";
			link.l1.go = "DTSG_Graf_Sheffild_24";
		break;
		
		case "DTSG_Graf_Sheffild_24":
			dialog.text = "Тогда этой крови на их руках не меньше, чем на нашей, если даже не больше. Пусть это тебя утешит. Главное, что наши намерения были чисты - устранить врага Родины\nА теперь помоги мне, Чарли, нам ещё предстоит обустроить всё так, чтобы подумали, будто это было голландское нападение.";
			link.l1 = "Хорошо, сэр...";
			link.l1.go = "DTSG_Graf_Sheffild_25";
		break;
		
		case "DTSG_Graf_Sheffild_25":
			DialogExit();
			EndQuestMovie();
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Kortni", "off_eng_5", "man", "man", 40, ENGLAND, -1, false, "quest"));
			sld.name = "Томас";
			sld.lastname = "Линч";
			sld.rank = 40;
			GiveItem2Character(sld, "blade_16");
			EquipCharacterByItem(sld, "blade_16");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterByItem(sld, "pistol6");
			SetSelfSkill(sld, 100, 100, 100, 100, 100);
			LAi_SetHP(sld, 400.0, 400.0);
			FantomMakeCoolSailor(sld, SHIP_HIMERA, "Химера", CANNON_TYPE_CANNON_LBS20, 70, 70, 70);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			sld.Ship.Mode = "war";
			sld.alwaysEnemy = true;
			sld.Coastal_Captain = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("DTSG_KortniAttack");
			Group_SetType("DTSG_KortniAttack", "pirate");
			Group_AddCharacter("DTSG_KortniAttack", "DTSG_Kortni");

			Group_SetGroupCommander("DTSG_KortniAttack", "DTSG_Kortni");
			Group_SetTaskAttack("DTSG_KortniAttack", PLAYER_GROUP);
			Group_SetAddress("DTSG_KortniAttack", "Antigua", "Quest_Ships", "Quest_Ship_10");
			Group_LockTask("DTSG_KortniAttack");
			
			SetLaunchFrameFormParam("Настоящее время"+ NewStr() +"В каюте Шарля", "DTSG_SegodnyaVremya", 0, 4.0);
			LaunchFrameForm();
		break;
		
		case "DTSG_Knippel_101":
			dialog.text = "Вот так мы оставили ложные улики, будто бы всё сделали голландцы. В дальнейшем мы с Ричардом никогда больше не обсуждали этот день.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Что ж, многое встаёт на свои места. Думаю, за смертью Ричарда стоит какой-нибудь родственник, друг или попросту сторонник графа. Но зачем устранять тебя? Ты простой канонир и не принимал никаких решений.";
				link.l1.go = "DTSG_Knippel_ZS_102";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Получен бонус опыта");
			}
			else
			{
				link.l1 = "Да уж. Дело ясное, что дело тёмное. Возможно, кто-то узнал обо всём и решил отомстить за графа. Но разве один канонир стоит таких затрат? Деньги, наёмники, приказы морским лисам... Уж извини меня, Чарли.";
				link.l1.go = "DTSG_Knippel_NS_102";
			}
		break;
		
		case "DTSG_Knippel_ZS_102":
			dialog.text = "Возможно, этот человек охотится на всех из бывшей команды Ричарда, что скажете об этом, сэр?";
			link.l1 = "Скажу, что нам не помешает отдалиться от Антигуа, и чем скорее, тем лучше.";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_NS_102":
			dialog.text = "Я тоже задавался этим вопросом, капитан, но к ответу не пришёл.";
			link.l1 = "Кто-то идёт. Просил же никого не беспокоить нас...";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_103":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Helena_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Tichingitu_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Alonso", "citiz_36", "man", "man", sti(pchar.rank), pchar.nation, 0, true, "soldier"));
				sld.name 	= "Алонсо";
				sld.lastname = "";
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Alonso_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				sld.location = "None";
			}
		break;
		
		case "DTSG_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Шарль!..";
				link.l1 = "Что случилось, Элен??";
				link.l1.go = "DTSG_Helena_2";
			}
			else
			{
				dialog.text = "Шарль, я помню, что ты просил меня никого не впускать и не мешать вам с Чарли поговорить, но...";
				link.l1 = "... поэтому ты решила прийти сама. Ладно, всё в порядке, Элен. Что такое?";
				link.l1.go = "DTSG_Helena_2";
			}
		break;
		
		case "DTSG_Helena_2":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Недавно на горизонте был английский военный корабль. Поначалу я не придала этому значения, но он сблизится с нами буквально с минуты на минуту! В жизни не видела такого быстрого корабля.";
				link.l1 = "Тогда спасибо, что сообщила. Надеюсь, успеем подготовиться ко встрече с ним. Или даже бою. Элен, Чарли, идёмте!";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
			else
			{
				dialog.text = "... но сейчас не время для разговоров. В нашу сторону движется английский боевой корабль. Я решила, что это важно.";
				link.l1 = "Что ж, пойду гляну. Спасибо, Элен.";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
		break;
		
		case "DTSG_Tichingitu_1":
			dialog.text = "Капитан, на нас идти быстрый корабль. Очень быстрый. Духи шептать мне, что их намерения - зло.";
			link.l1 = "Спасибо тебе и духам, что предупредили. Приготовься на всякий случай к бою. И передай это от меня остальным.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_Alonso_1":
			dialog.text = "Прошу прощения, сеньор капитан, что помешал, но это очень срочно.";
			link.l1 = "Ох, надеюсь, там и правда что-то важное, Алонсо. Докладывай.";
			link.l1.go = "DTSG_Alonso_2";
		break;
		
		case "DTSG_Alonso_2":
			dialog.text = "К нам приближается английский корабль. Это... 'Мираж', капитан.";
			link.l1 = "Что ты сказал? Ты... абсолютно в этом уверен? Вы там с Чарли случайно не напились до чёртиков?";
			link.l1.go = "DTSG_Alonso_3";
		break;
		
		case "DTSG_Alonso_3":
			dialog.text = "Уверен, капитан - другого такого корабля на Архипелаге нет, вы же знаете.";
			link.l1 = "Это точно. Пойду лучше сам взгляну - уж не мираж ли этот 'Мираж'.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_GotovimsyKBitve":
			DialogExit();
			AddQuestRecord("DTSG", "17");
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Saga\Helena.c";
				sld.Dialog.CurrentNode = "Helena_officer";
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
			{
				sld = characterFromId("Knippel");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
				sld.Dialog.CurrentNode = "Knippel_officer";
			}
			
			PChar.quest.DTSG_KortniPotopil.win_condition.l1 = "Character_sink";
			PChar.quest.DTSG_KortniPotopil.win_condition.l1.character = "DTSG_Kortni";
			PChar.quest.DTSG_KortniPotopil.win_condition = "DTSG_KortniPotopil";
			
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "DTSG_Kortni":
			dialog.text = "Ох-х... Но ничего ещё не кончено! Бриан, а вот и ты! И где тебя только черти носят?";
			link.l1 = "Это лишь отсрочит неизбежное.";
			link.l1.go = "DTSG_Kortni_Pikar";
		break;
		
		case "DTSG_Kortni_Pikar":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "DTSG_KortniRanen");
			LAi_SetImmortal(npchar, false);
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Mrt_Rocur", "citiz_8", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
			sld.name = "Бриан";
			sld.lastname = "Тассе";
			GiveItem2Character(sld, "blade_20");
			EquipCharacterByItem(sld, "blade_20");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterByItem(sld, "pistol5");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetHP(sld, 300.0, 300.0);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "DTSG_PikarRanen");
			sld.location = "None";
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "DTSG_Kortni_1":
			dialog.text = "Шарль де Мор. Подумать только, как далеко вы зашли. Жаль. Я надеялся застать вас врасплох на этом корабле.";
			link.l1 = "Вы знаете, кто я? Так, значит, это вы стоите за нашими недавними трудностями - вы выглядите, как птица высокого полёта, которой пришлось лично вылететь из уютного гнезда, а не посылать очередного стервятника.";
			link.l1.go = "DTSG_Kortni_2";
			
			Island_SetReloadEnableGlobal("Antigua", true);
			bQuestDisableMapEnter = false;
			LAi_LocationDisableOfficersGen("SentJons_town", false);
			DeleteQuestCondition("DTSG_KortniPotopil");
		break;
		
		case "DTSG_Kortni_2":
			dialog.text = "Верно, и на оба вопроса. Полагаю, дворянин дворянина видит издалека. Полковник Томас Линч. Кажется, пришло время поговорить, как двум джентльменам, а не пытаться уничтожить друг друга. Возможно, мы сумеем прийти к взаимовыгодному соглашению.";
			link.l1 = "Ничего не могу обещать, но даю вам слово дворянина, что, по крайней мере, мы с вами поговорим, как цивилизованные люди, полковник.";
			link.l1.go = "DTSG_Kortni_3";
		break;
		
		case "DTSG_Kortni_3":
			dialog.text = "Очень хорошо. С Флитвудом бы мне так поговорить не удалось. Впрочем, мы всё равно нашли на него рычаг давления, и больше он нас не побеспокоит. Жаль, что с вами так не вышло, ну да ладно.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Весь Архипелаг уже говорит о смерти Ричарда. Значит, это были вы. А рычагом, полагаю, стала Абигайль? Что с ней стало, кстати?";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Получен бонус опыта");
			}
			else
			{
				link.l1 = "Не побеспокоит?.. Так, значит, вы убили его? Вы один из сторонников графа?";
			}
			link.l1.go = "DTSG_Kortni_4";
		break;
		
		case "DTSG_Kortni_4":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Абигайль? А-а-а, та юная еврейка, его невеста. Вы весьма догадливы. Снова. И она жива и здорова - мы пообещали и исполнили это в обмен на... сотрудничество Флитвуда с нами.";
				link.l1 = "Да уж, хорошо сотрудничество, ничего не скажешь. Но зачем вы это сделали? Вы сторонник графа?";
			}
			else
			{
				dialog.text = "Сторонников? О, напротив. Но, видите ли, некоторые карты больше нельзя разыграть - они становятся опасны для игрока. К сожалению, Ричард стал одной из них.";
				link.l1 = "Понятно. Вы устраняете всех свидетелей. А что стало с Абигайль? Вы и её убили?";
			}
			link.l1.go = "DTSG_Kortni_5";
		break;
		
		case "DTSG_Kortni_5":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Никоим образом. Даже наоборот. Но, зная столь многое, Ричард становился опасен, будучи в Старом Свете. Ему следовало оставаться на Архипелаге, и тогда бы мы не стали лишать его жизни.";
				link.l1 = "Вы устраняете всех, кто на вас когда-либо работал, полковник?";
			}
			else
			{
				dialog.text = "Кто-кто? А, его невеста, полагаю. Она и стала рычагом давления. Его жизнь в обмен на неё. Она в порядке, клянусь честью.";
				link.l1 = "Не думаю, что вам ведома честь, учитывая, что вы сотворили, полковник.";
			}
			link.l1.go = "DTSG_Kortni_6";
		break;
		
		case "DTSG_Kortni_6":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Я не стану отвечать на эту провокацию, сударь.";
				link.l1 = "Тогда ответьте лучше на этот вопрос - как вы получили этот корабль? Это... 'Мираж'?";
			}
			else
			{
				dialog.text = "Я закрою глаза на это оскорбление, ибо в вас говорит человек, которому не приходилось быть у власти и влиять на порядок вещей.";
				link.l1 = "Кстати, о вещах. Откуда у вас 'Мираж'? Это ведь он?";
			}
			link.l1.go = "DTSG_Kortni_7";
		break;
		
		case "DTSG_Kortni_7":
			dialog.text = "Не совсем он. Прекрасное судно, не правда ли? Жаль, что оно не выполнило свою задачу супротив вас. Вам вообще известна история этого корабля, капитан де Мор?";
			link.l1 = "Вы про корабль-призрак и охоту на английских торговцев?";
			link.l1.go = "DTSG_Kortni_8";
		break;
		
		case "DTSG_Kortni_8":
			dialog.text = "Это? Ах, нет. Я говорю не об общеизвестных вещах. А о том, что скрыто от глаз. Этот кеч был спроектирован Йоханом ван Мерденом и Лукасом Роденбургом\nОни создали цепочку подставных лиц, и в итоге корабль сошёл со стапелей на верфи Гаваны. Нам повезло заполучить в руки оригинальные чертежи. И в итоге мы воссоздали 'Мираж' во всей красе и даже лучше, исправив несколько недочётов в его конструкции.";
			link.l1 = "Жаль только, как вы сами заметили, это не слишком вам помогло, полковник.";
			link.l1.go = "DTSG_Kortni_9";
		break;
		
		case "DTSG_Kortni_9":
			dialog.text = "Хотите посмеяться? Напрасно. Признаю, вы превзошли меня и как капитан, и как фехтовальщик. Но хозяином положения здесь всё ещё являюсь я.";
			link.l1 = "Уж не предсмертный ли это блеф? Или простая, уже привычная людям вроде вас, самоуверенность? Что стоит за этими словами?";
			link.l1.go = "DTSG_Kortni_10";
		break;
		
		case "DTSG_Kortni_10":
			dialog.text = "Отличный вопрос. Сдаётся мне, что вы - нечто большее, чем повеса и дуэлянт, о котором я навёл справки. Я принял меры на все исходы этой встречи. Даже тот, при котором гибну от вашего клинка, пули или шального ядра\nЕсли я сегодня погибну, то вы с Чарли пожалеете, что до сих пор не присоединились к Флитвуду.";
			link.l1 = "Очередные охотники за головами? Прошу вас. Это было неприятно и надоедливо, но не смертельно. Отбились тогда - отобьёмся и впредь.";
			link.l1.go = "DTSG_Kortni_11";
		break;
		
		case "DTSG_Kortni_11":
			dialog.text = "Не сомневаюсь в этом. Сейчас в вас снова говорит беззаботный дуэлянт, я погляжу. Не одними охотниками. Вся мощь морских лис и английской военно-морской разведки обрушится на вашу голову, как штормовая волна на рыбачью лодку.";
			link.l1 = "И что вы от меня хотите? Вы же не ждёте, что я сдамся?";
			link.l1.go = "DTSG_Kortni_12";
		break;
		
		case "DTSG_Kortni_12":
			dialog.text = "Ну что вы, конечно, нет. Мы уже успели хорошо вас изучить за всё это время. Я хочу предложить вам взаимовыгодную сделку. От которой, впрочем, будет не слишком разумно отказываться. И, как два благородных человека, я надеюсь, что мы договоримся.";
			link.l1 = "Тогда повторю вопрос, полковник, что же вам нужно? Полагаю, Чарли?.. И вы думаете, что можете что-то предложить мне взамен? Я не пойду на предательство из-за нескольких золотых.";
			link.l1.go = "DTSG_Kortni_13";
		break;
		
		case "DTSG_Kortni_13":
			dialog.text = "И снова верно. Речь, конечно, не о нескольких золотых, как вы изволили выразиться, а о целой горе - 10000 дублонов. Депозит будет вас ждать у ростовщика Порт-Ройала, в случае, если мы договоримся\nНо самое главное, что я вам предложу - вашу жизнь, капитан де Мор. Вы меня слышали. Мы прекратим всякое преследование с нашей стороны, если мы все сейчас сложим оружие, и вы нам отдадите Чарли.\nВы слышали о выражении 'человек против общества'? В вашем случае, если вы не согласитесь, это будет 'человек против государства'. Решайте, Шарль. Здесь и сейчас.";
			link.l1 = "Вы легко можете прикрываться своим титулом и влиянием, чтобы запугать дурачка-другого. Но я уже давно не дурак. И чувствую отчаяние за милю. Убирайтесь. И будьте счастливы, что я вас не убил - вы более чем этого заслуживаете.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
			link.l2 = "Вам ведь на самом деле не нужен Чарли, полковник. Вам нужно его молчание.";
			link.l2.go = "DTSG_Kortni_LT_1";
			link.l3 = "Я соглашаюсь на это ради безопасности себя и своих людей, а не из жадности до ваших денег, так и знайте.";
			link.l3.go = "DTSG_Kortni_Sdat";
		break;
		
		case "DTSG_Kortni_PkCh_1":
			dialog.text = "Вы приняли одно из самых худших решений в своей жизни, капитан де Мор. Я вам не завидую. Честно. Пеняйте на себя - более вам никто подобных предложений делать не станет. Уж особенно я. Прощайте.";
			link.l1 = "Постойте, полковник.";
			link.l1.go = "DTSG_Kortni_PkCh_2";
		break;
		
		case "DTSG_Kortni_PkCh_2":
			dialog.text = "Что, неужто передумали? Мои слова наконец-то возымели эффект?";
			link.l1 = "Верно, вот только совсем обратный.";
			link.l1.go = "DTSG_Kortni_PkCh_3";
		break;
		
		case "DTSG_Kortni_PkCh_3":
			dialog.text = "Что это вы имеете в виду? Объяснитесь.";
			link.l1 = "Что ваши слова лишь сильнее настроили меня против вас. Не смотрите так - убивать я вас не буду. И, как я сказал, даже отпущу вас. Но, думаю, вы справитесь и без шлюпки.";
			link.l1.go = "DTSG_Kortni_PkCh_4";
		break;
		
		case "DTSG_Kortni_PkCh_4":
			dialog.text = "Она мне и не нужна, ведь у меня есть корабль.";
			link.l1 = "Вы правы. Но лишь в том, что она вам не нужна. Вы действительно можете быть влиятельным человеком. Но вам неведомо чувство меры. И такта. Я сделаю то, что привыкли делать вы - побуду хозяином положения.";
			link.l1.go = "DTSG_Kortni_PkCh_5";
		break;
		
		case "DTSG_Kortni_PkCh_5":
			dialog.text = "Вы им не являетесь, капитан де Мор. Не обманывайте себя.";
			link.l1 = "В полной мере? Возможно, нет. Но в полной мере им не являетесь и вы - ваша жизнь сейчас в моих руках, полковник. Неважно, что со мной будет потом - сейчас я могу сделать что угодно. И я... забираю этот корабль. Вы свободны. До берега недалеко.";
			link.l1.go = "DTSG_Kortni_PkCh_6";
		break;
		
		case "DTSG_Kortni_PkCh_6":
			dialog.text = "Вы не посмеете. Но, судя по вашему взгляду... Наслаждайтесь своей маленькой победой. Вы приняли...";
			link.l1 = "Да, да, одно из самых худших решений в моей жизни. Я это уже слышал. Вон с этого корабля. Моего корабля. Сами выпрыгнете, или нам с ребятами выкинуть вас за борт?";
			link.l1.go = "DTSG_Kortni_PkCh_7";
		break;
		
		case "DTSG_Kortni_PkCh_7":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto4", "", "", "", "DTSG_Kortni_Vyprygnul", 7);
			npchar.lifeday = 0;
			npchar.location = "None";
		break;
		
		case "DTSG_Kortni_PkCh_8":
			dialog.text = "Никогда не думал, что увижу его вот таким - униженным, прыгающим в окно и плывущим к берегу на своих четырёх.";
			link.l1 = "Увидели? Довольны? Прекрасно. Вы следующий.";
			link.l1.go = "DTSG_Kortni_PkCh_9";
		break;
		
		case "DTSG_Kortni_PkCh_9":
			dialog.text = "Что вы такое говорите, сударь? Мы с вами не враги, я просто выполнял его приказы!.. Могу я хотя бы выпросить у вас шлюпку? И вы меня больше никогда не увидите!";
			link.l1 = "Просто выполнял приказ... Как часто это говорят. Вы бы меня не пощадили, если бы я проиграл вам ранее. Так что радуйтесь, что я вообще вас не убил. В окно. Живо. Возможно, ещё догоните своего патрона.";
			link.l1.go = "DTSG_Kortni_PkCh_10";
		break;
		
		case "DTSG_Kortni_PkCh_10":
			dialog.text = "Да я лучше умру, чем пойду на такое унижение, месье!";
			link.l1 = "Как будет угодно.";
			link.l1.go = "DTSG_Kortni_PkCh_11";
		break;
		
		case "DTSG_Kortni_PkCh_11":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Kortni_Vyprygnul_3");
		break;
		
		case "DTSG_Kortni_PkCh_12":
			dialog.text = "Это ведь был полковник, верно, капитан?";
			link.l1 = "Верно. Подойди к окну, Чарли, не пожалеешь.";
			link.l1.go = "DTSG_Kortni_PkCh_13";
		break;
		
		case "DTSG_Kortni_PkCh_13":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto4", "DTSG_Kortni_Vyprygnul_5", 6);
		break;
		
		case "DTSG_Kortni_PkCh_14":
			dialog.text = "Полковник?.. В жизни бы не подумал, что увижу что-то подобное, сэр. Что кто-то осмелится выкинуть человека с таким титулом, как простого матроса! Ричард бы на такое не пошёл - чинопочитание было его неотъемлемой частью.";
			link.l1 = "Просто это было в него вбито за годы муштры. Он военный, мышление соответствующее. Я же - нет, и мыслю шире, без подобных... ограничений.";
			link.l1.go = "DTSG_Kortni_PkCh_15";
		break;
		
		case "DTSG_Kortni_PkCh_15":
			dialog.text = "А нам ничего не будет за то, что мы с ним вот так поступили?";
			link.l1 = "Хех, винишь в этом Ричарда, а сам мыслишь таким же образом. Чарли, Чарли. Мы посмели дать отпор, думаю, какое-то время на нас ещё будет вестись охота. Но рано или поздно даже английский флот на нас плюнет. И для Линча это станет сугубо личными счётами. На которые ему не предоставят государевых средств.";
			link.l1.go = "DTSG_Kortni_PkCh_16";
		break;
		
		case "DTSG_Kortni_PkCh_16":
			dialog.text = "Знаете, капитан, с этого дня я лишь ещё больше зауважал вас. Никогда не буду жалеть о том, что не ушёл на 'Валькирии' с Диком, а решил перейти на службу к вам.";
			link.l1 = "Спасибо, дружище! Будь готов - нам ещё предстоит немало встреч с твоими разгневанными собеседниками. Но знаешь, что? Что-то мне подсказывает, что мы из всех них выйдем победителями. Идём, нам пора обратно на палубу.";
			link.l1.go = "DTSG_Kortni_PkCh_17";
		break;
		
		case "DTSG_Kortni_PkCh_17":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_7", 3.0);
			Achievment_Set("ach_CL_114");
		break;
		
		case "DTSG_Kortni_LT_1":
			dialog.text = "Это не совсем так, хотя лично в моём случае мне до Чарли нет никакого дела, если он и правда будет молчать. Но мои коллеги хотели бы видеть его тело. И они знают, как он выглядит\nЭто жизнь, Шарль, а не детская сказка или рыцарская поэма, что читали нам в детстве нянечки, и выхода, который бы устроил абсолютно всех, я не вижу.";
			link.l1 = "Однако его вижу я. Всегда можно найти похожее тело. И купить похожую одежду. А с самим Чарли я поговорю. И даю своё слово вам, в качестве гарантии.";
			link.l1.go = "DTSG_Kortni_LT_2";
		break;
		
		case "DTSG_Kortni_LT_2":
			if (sti(pchar.reputation.nobility) > 70)
			{
				notification("Проверка чести пройдена", "None");
				dialog.text = "Это... большой риск. И дело не только в том, могу ли я довериться вашему слову. А в том, поверят ли мне мои коллеги, увидев труп похожего на Чарли человека. И я не пойду на этот риск... просто так.";
				link.l1 = "Сколько?";
				link.l1.go = "DTSG_Kortni_LT_4";
			}
			else
			{
				notification("Слишком низкий уровень чести! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				dialog.text = "Слово человека вашей репутации? Вы, право, шутите. Одного лишь происхождения мало, чтобы вам доверяли.";
				link.l1 = "Слышу это от другого человека с похожими и происхождением, и поступками, уж не обессудьте, полковник.";
				link.l1.go = "DTSG_Kortni_LT_3";
			}
		break;
		
		case "DTSG_Kortni_LT_3":
			dialog.text = "Вы, конечно, правы, чего уж там. Но в данном случае речь пойдёт о моём доверии, а не чьём-либо ещё. И вы в качестве гаранта меня совершенно не устраиваете\nГоворю вам в последний раз. Отдайте мне Чарли. Если, конечно, не хотите повторить судьбу Флитвуда.";
			link.l1 = "Вы легко можете прикрываться своим титулом и влиянием, чтобы запугать дурачка-другого. Но я уже давно не дурак. И чувствую отчаяние за милю. Убирайтесь. И будьте счастливы, что я вас не убил - вы более чем этого заслуживаете.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_4":
			dialog.text = "Наконец-то, сразу к делу. Миллион песо. На меньшее даже не надейтесь.";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "Я выплачу вам эти деньги. Не знаю, что вы думали, что я бедняк, или что я не ценю жизни своих людей. Ни то, ни другое. Возьмите.";
				link.l1.go = "DTSG_Kortni_LT_7";
			}
			else
			{
				link.l1 = "У вас хороший аппетит, хотя меньшего я как раз и не ждал. Но прямо сейчас у меня при себе столько нет, и...";
				link.l1.go = "DTSG_Kortni_LT_5";
			}
		break;
		
		case "DTSG_Kortni_LT_5":
			dialog.text = "Нет дублонов - нет сделки. Вы же не думали, что я сжалюсь? Я, по-вашему, святой отец, сударь?";
			link.l1 = "Но, возможно, вы бы могли немного подождать? Где и когда вам было бы удобно снова встретиться? Я мог бы занять эти дублоны у одного из ростовщиков.";
			link.l1.go = "DTSG_Kortni_LT_6";
		break;
		
		case "DTSG_Kortni_LT_6":
			dialog.text = "Тогда вы считаете меня ещё наивнее, чем я полагал\nЯ не деревенская девица, готовая вечность ждать того, кто однажды её поматросил\nНет денег? Я и не просил. Мне нужен лишь Чарли. Вы же мне, даже при всех трудностях, что успели создать, совершенно ни к чему.";
			link.l1 = "Вы легко можете прикрываться своим титулом и влиянием, чтобы запугать дурачка-другого. Но я уже давно не дурак. И чувствую отчаяние за милю. Убирайтесь. И будьте счастливы, что я вас не убил - вы более чем этого заслуживаете.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_7":
			dialog.text = "Вы и правда так привязались к бедняге Чарли? Как бы то ни было, ваше благородство заслуживает уважения. Проследите, чтобы ваш канонир был нем, как могила. Иначе вы оба туда попадёте.";
			link.l1 = "Обещаю вам. А вы сдержите своё слово и прекратите всякое дальнейшее преследование.";
			link.l1.go = "DTSG_Kortni_LT_8";
			AddMoneyToCharacter(pchar, -1000000);
		break;
		
		case "DTSG_Kortni_LT_8":
			dialog.text = "Обещаю и я вам. И ещё кое-что. Несмотря на вашу честную победу, свой корабль я забираю вместе с собой. Штучная работа, знаете ли. И крайне дорогая.";
			link.l1 = "А как же право победителя? Однако не буду испытывать удачу. На этот раз.";
			link.l1.go = "DTSG_Kortni_LT_9";
		break;
		
		case "DTSG_Kortni_LT_9":
			DialogExit();
			
			LAi_Fade("DTSG_Kortni_Otkup_1", "");
		break;
		
		case "DTSG_Kortni_LT_10":
			dialog.text = "Мне почти жаль это говорить, Бриан, но, боюсь, наше с вами сотрудничество на этом закончено.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_11";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_11":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_12":
			dialog.text = "Я... свободен, господин полковник? Вы отмените награду за мою голову, и я смогу начать всё с чистого листа, как будто я законопослушный человек?";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_13";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_13":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_14":
			dialog.text = "Я бы сказал, что вы стали, как Флитвуд - рядом со мной и слишком многое видели. Ведь прямо сейчас я, по сути, получил взятку.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_15";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_16":
			dialog.text = "Я... я никому ничего не скажу, клянусь Богом!";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_17";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_17":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_18":
			dialog.text = "Разумеется, не скажете.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_19";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_19":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_20":
			dialog.text = "Нет!..";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_21";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_21":
			DialogExit();
			
			sld = CharacterFromID("DTSG_KortniClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Kortni_Otkup_3", 0.9);
			
			LAi_SetActorType(NPChar);
			LAi_ActorAttack(NPChar, sld, "");
		break;
		
		case "DTSG_Kortni_LT_22":
			dialog.text = "Не смотрите так на меня, Шарль. Если мне ещё постоянно беспокоиться и о том, проболтается ли Бриан - я вовсе не смогу спать.";
			link.l1 = "Даже не знаю, удивляться мне увиденному, или нет.";
			link.l1.go = "DTSG_Kortni_LT_23";
		break;
		
		case "DTSG_Kortni_LT_23":
			dialog.text = "Не стоит. Что могу вам сказать - сделаем с вами всё от нас зависящее. Вы с Чарли не болтайте о произошедшем. Я же постараюсь найти похожее тело, подправить ему как следует личико и сказать коллегам, что это храбро павший в бою канонир. Или не очень храбро.";
			link.l1 = "Благодарю вас, полковник.";
			link.l1.go = "DTSG_Kortni_LT_24";
		break;
		
		case "DTSG_Kortni_LT_24":
			dialog.text = "Опять же, не стоит. Всегда есть риск, что мне не поверят, и тогда на вас вновь откроется охота. Ну а пока - прощайте, капитан де Мор. Я отчаливаю на своём корабле. Возражения не принимаются - я и так сделал вам с Чарли огромное одолжение.";
			link.l1 = "Что ж, тогда прощайте.";
			link.l1.go = "DTSG_Kortni_LT_25";
			
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		break;
		
		case "DTSG_Kortni_LT_25":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_26";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
		break;
		
		case "DTSG_Kortni_LT_26":
			dialog.text = "Вы знаете, с кем вы разговаривали, капитан? Это полковник! Так это из-за него на нас нападали в последнее время?";
			link.l1 = "Знаю, он представился. И ты прав - всё происходящее было его рук делом.";
			link.l1.go = "DTSG_Kortni_LT_27";
		break;
		
		case "DTSG_Kortni_LT_27":
			dialog.text = "Странно это, сэр, ведь он когда-то давал поручения Ричарду. Как же так? И почему он уходит, как ни в чём не бывало? Что он вообще хотел?";
			link.l1 = "Как раз напротив, ничего странного в этом нет. Те, кто выполняют такие поручения, часто рискуют жизнью не столько из-за врагов, сколько из-за нанимателей. А хотел он твою голову, Чарли.";
			link.l1.go = "DTSG_Kortni_LT_28";
		break;
		
		case "DTSG_Kortni_LT_28":
			dialog.text = "Я не понимаю, капитан. Почему же он тогда уходит? Смирился с поражением?";
			link.l1 = "Таким, как он, это не свойственно. Мне пришлось дать ему золота примерно с твою голову весом. Даже чуть больше. Миллион песо, если быть точным.";
			link.l1.go = "DTSG_Kortni_LT_29";
		break;
		
		case "DTSG_Kortni_LT_29":
			dialog.text = "И вы... заплатили столько денег? Ради меня?..";
			link.l1 = "Ну, не только ради тебя. Ради себя тоже. И всех ребят в том числе. Но да, Чарли, прежде всего - ради тебя. Не отдавать же мне ему тебя было? А если бы мы убили его, то вечность бы потом отбивались от карательных экспедиций.";
			link.l1.go = "DTSG_Kortni_LT_30";
		break;
		
		case "DTSG_Kortni_LT_30":
			dialog.text = "Я... не могу в это поверить, сэр. Просто... спасибо. Не думаю, что Флитвуд бы так поступил на вашем месте.";
			link.l1 = "Ты слишком предвзято к нему относишься после его побега. Ричард просто хотел тихой и мирной жизни с Абигайль. И мне очень жаль, что ему это не удалось. К тому же, он сдержал слово и выплатил за тебя долг. Хех, я, Флитвуд - везёт же тебе с капитанами, да, Чарли?";
			link.l1.go = "DTSG_Kortni_LT_31";
		break;
		
		case "DTSG_Kortni_LT_31":
			dialog.text = "И не говорите, капитан. Значит, теперь всё кончено?";
			link.l1 = "Да, дружище. По крайней мере, пока. Бой окончен - можешь откатить с ребятами орудия. И пусть готовятся поднять паруса.";
			link.l1.go = "DTSG_Kortni_LT_32";
		break;
		
		case "DTSG_Kortni_LT_32":
			DialogExit();
			
			InterfaceStates.Buttons.Save.enable = true;
			LAi_SetPlayerType(pchar);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "19");
			CloseQuestHeader("DTSG");
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
			sld = CharacterFromID("Knippel");
			SetCharacterPerk(sld, "Bombardier");
			notification("Открыт 'Бомбардир'", "Knippel");
		break;
		
		case "DTSG_Kortni_Sdat":
			dialog.text = "Мне совершенно плевать, по какой причине вы там соглашаетесь - из жадности ли, страха ли, долга перед своими людьми. Главное, что соглашаетесь. Я пошлю своего человека в Порт-Ройал, с инструкциями для ростовщика.";
			link.l1 = "Хорошо. Поверить не могу, что всё это наконец-то закончилось.";
			link.l1.go = "DTSG_Kortni_Dengi_1";
			link.l2 = "А знаете, к чёрту деньги. Их всегда можно найти ещё или отнять. Есть кое-что другое, что я хотел бы получить от вас в обмен на Чарли, полковник.";
			link.l2.go = "DTSG_Kortni_Kech_1";
		break;
		
		case "DTSG_Kortni_Kech_1":
			dialog.text = "Вот как? Признаться, вы меня удивили, капитан де Мор. И что же, на ваш взгляд, будет равноценно плешивой голове старого канонира, раз гора золота вас не устраивает?";
			link.l1 = "Вы сами сказали - прекрасное судно, с исправленными недочётами конструкции. Не терпится узнать самому. У вас всё равно есть чертежи. А Чарли всего один. Да и я чтобы остался всем доволен, тоже в ваших интересах.";
			link.l1.go = "DTSG_Kortni_Kech_2";
		break;
		
		case "DTSG_Kortni_Kech_2":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				notification("Проверка чести пройдена", "None");
				notification("Вызывающий доверие", "Trustworthy");
				dialog.text = "А вам палец в рот не клади, иначе по локоть откусите. Вы хоть представляете, во сколько нам обошлось строительство одного такого?";
				link.l1 = "(Вызывающий доверие) (Честь) Прекрасно представляю, потому и прошу. Ваша рука как раз по локоть в моей пасти. Можете, конечно, попытаться пристрелить этого волка. Но о руке придётся забыть. И не только о ней.";
			}
			else
			{
				dialog.text = "Боюсь, что изготовление одного такого стоит куда больше, чем то золото, что мы для вас приготовили. Но вы меня позабавили, Шарль. В хорошем смысле.";
				link.l1 = "Попытаться стоило.";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Не открыта способность", "Trustworthy");
				if (sti(pchar.reputation.nobility) < 71) notification("Слишком низкий уровень чести! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			}
			link.l1.go = "DTSG_Kortni_Kech_3";
		break;
		
		case "DTSG_Kortni_Kech_3":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				notification("Проверка чести пройдена", "None");
				notification("Вызывающий доверие", "Trustworthy");
				dialog.text = "Я смотрю, вы знаете, чего хотите. И идёте навстречу своим целям по жизни\nНу хорошо. Кеч ваш. Но о деньгах забудьте - ростовщик вам скажет, что ни о чём не знает.";
				link.l1 = "Меня это устраивает.";
				link.l1.go = "DTSG_Kortni_Kech_4";
				pchar.questTemp.DTSG_Kech = true;
			}
			else
			{
				notification("Слишком низкий уровень чести! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				notification("Не открыта способность", "Trustworthy");
				dialog.text = "Определённо. Моя жизнь - история человека, который не упускал ни одной возможности. И обезопашивал себя от возможных рисков\nТак что приведите сюда Чарли, и мы расходимся с миром. После этого вы даже сможете забрать депозит. Но уйду я отсюда только на этом корабле.";
				link.l1 = "Что же, на этом и порешим.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
				pchar.questTemp.DTSG_depozit = true;
			}
		break;
		
		case "DTSG_Kortni_Kech_4":
			dialog.text = "Не могу сказать, что всё это в полной мере устраивает меня. Но уже хочется поскорее покончить со всем этим. Теперь отдайте мне то, что хочу я.";
			link.l1 = "Ну, не 'что', а 'кого'. Но как угодно.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		break;
		
		case "DTSG_Kortni_Dengi_1":
			dialog.text = "И я тоже. Начинаю убеждаться в том, что важно не только то, что из себя представляет человек, но и каких людей вокруг себя он собирает - простое дело по поимке старого канонира превратилась в головную боль из-за его капитана, то есть вас, Шарль\nЗовите сюда Чарли. И это всё действительно закончится - мы поднимем якоря, и наши корабли разойдутся.";
			link.l1 = "Разойдутся, говорите?";
			link.l1.go = "DTSG_Kortni_Dengi_2";
		break;
		
		case "DTSG_Kortni_Dengi_2":
			dialog.text = "Вижу, вы удивлены? Вы, должно быть, думали, что кеч - ваш законный приз? Мы с вами не пираты, капитан де Мор. Цивилизованные люди живут по другим, куда более сложным правилам. Корабль останется со мной.";
			link.l1 = "Ну хорошо...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
			pchar.questTemp.DTSG_depozit = true;
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_2";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_2":
			dialog.text = "Вы в порядке, сэр? Это... полковник?";
			link.l1 = "Да, Чарли, это полковник. Ты вовремя - я уже собирался сам идти за тобой.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_3";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_3":
			dialog.text = "Идти за мной, капитан?.. Прямо сейчас? Почему вы так долго разговариваете с этим... человеком? Я подумал, что вы в беде, и пришёл сюда сам.";
			link.l1 = "Верно. Мы до сих пор в беде, несмотря на то, что победили. И были бы в беде и дальше, но мы с полковником нашли решение.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_4";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_4":
			dialog.text = "Неужто вы смогли убедить его оставить нас в покое, сэр?";
			link.l1 = "К сожалению, лишь меня. Не нас. Ты... пойдёшь с ним, Чарли.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_5";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_5":
			dialog.text = "Что?.. Но почему?.. Победа ведь за нами!";
			link.l1 = "Ты правда не понимаешь? Нам придётся одерживать эти победы постоянно - они не успокоятся, пока не получат твою голову. И... никто не побеждает вечно. Но, боюсь, что применимо это сейчас только ко мне, а не всему английскому флоту и его разведке.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_6";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_6":
			dialog.text = "Поверить не могу, что вы так поступаете со стариной Чарли, капитан. Вы такой же, как и Дик. Оба говорили мне, что вы - мои друзья. И оба бросали всех, кто вокруг них.";
			link.l1 = "Такова ноша капитана, его ответственность. Вижу, тебе это не понять, потому что всё, что лежало на твоих плечах - это зарядить пушки книппелями.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_7";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_7":
			dialog.text = "Не понять?.. А, может, я просто не предатель, как вы? Знаете, куда вам лучше пойти?";
			link.l1 = "В Ад? Может, ты и прав. Все мы его заслуживаем.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_8";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_8":
			PlaySound("VOICE\Russian\hambit\Charlie Knippel-07.wav");
			dialog.text = "В жопу, сэр.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_9";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_9":
			DialogExit();
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			sld = CharacterFromID("KnippelClone");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_10":
			dialog.text = "Уморительно. Я почти рассмеялся. Ты слышал это, Бриан?\nДа уж, иногда простые грубые словечки даже не раздражают, и подобны свежему воздуху. Вы приняли правильное решение, Шарль. Я понимаю, как вам тяжело. Но пусть вас утешит то, что ни вы, ни кто-либо ещё из ваших людей теперь не пострадает.";
			link.l1 = "Надеюсь, вы сдержите это обещание, полковник.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_11";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_11":
			dialog.text = "Я человек слова. Вы вполне могли видеть это на примере Абигайль. Посмотрите на Бриана. Французский пират, а понял, когда пришла пора перейти на правильную сторону. И никто его и пальцем и не тронет, пока он нам верно служит. Как и он, вы движетесь в верном направлении, капитан де Мор.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				link.l1 = "Кстати, про движение. Хочу убраться отсюда поскорее. На этом, без сомнения, быстром судне, что вы мне обещали, полковник.";
			}
			else
			{
				link.l1 = "Я не пират. И вступать в английский флот пока что не собираюсь. А вот получить от него обещанную награду - вполне.";
			}
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_12";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_12":
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				dialog.text = "Не буду скрывать - словно отрываю его от сердца. Придётся потратиться на новый, но, пожалуй, оно того стоит\nВы же, если не будете болтать или совершать тяжкие преступления по отношению к Англии, можете считать, что мы с вами более не враги. Наслаждайтесь новым кораблём, он прекрасен. Прощайте, Шарль. Бриан - подготовь для нас шлюпку. Чарли - следуй за нами, выбора у тебя всё равно нет.";
				link.l1 = "Прощайте. Все вы.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_13";
			}
			else
			{
				dialog.text = "А жаль, толковые люди нам нужны всегда, неважно, какой они крови. Но, само собой, вы всё равно заслуживаете награду\nМожете смело отправляться в Порт-Ройал - я всё равно доберусь туда раньше любого другого корабля на этом кече.";
				link.l1 = "Надеюсь на это. Как и на то, что в Порт-Ройале меня не будет ждать вооружённый конвой.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_14";
			}
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_13":
			DialogExit();
			
			AddQuestRecord("DTSG", "20");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_14":
			dialog.text = "Снова сомневаетесь в моём слове? Зря. Вы заслужили благодарность всего английского военного флота. Если однажды вам будет что-нибудь нужно, или вы передумаете и решите вступить к нам - обращайтесь, капитан де Мор.";
			link.l1 = "Однажды я уже пытался заручиться поддержкой и связями с английской разведкой. Ничего из этого не вышло. Так что до свидания, полковник.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_15";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_15":
			DialogExit();
			
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				ChangeCharacterNationReputation(pchar, ENGLAND, 30);
			}
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
			AddQuestRecord("DTSG", "21");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
		break;
		
	}
} 
