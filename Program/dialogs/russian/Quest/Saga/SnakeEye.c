// шаман команчей Змеиный Глаз
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "calendar")
			{
				dialog.text = "Привет тебе, мой бледнолицый друг.";
				link.l2 = "И тебе привет, краснокожий брат. Меня снова привело к тебе важное дело.";
				link.l2.go = "calendar";
				break;
			}
			dialog.text = "Привет тебе, мой бледнолицый друг.";
			link.l1 = "Я тоже рад тебя видеть, Змеиный Глаз.";
			link.l1.go = "exit";
			if (CheckAttribute(npchar, "quest.amulet") && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Indian) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Amulet) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Obereg))
			{
				link.l2 = "Я принёс тебе амулеты, которые ты просил. Давай меняться.";
				link.l2.go = "SnakeEye_potion";
			}
			if (CheckAttribute(pchar, "questTemp.LSC")) // был в LSC
			{
				if (CheckAttribute(npchar, "quest.LSC_hello") && CheckCharacterItem(pchar, "buben"))
				{
					link.l2 = "Я нашёл твой бубен, Змеиный Глаз. Посмотри - это он?";
					link.l2.go = "LSC_buben";
				}
				if (CheckAttribute(npchar, "quest.LSC_tube") && CheckCharacterItem(pchar, "smoking_tube"))
				{
					link.l2 = "Я нашёл интересную индейскую трубку, Змеиный Глаз. Посмотри - это твоя?";
					link.l2.go = "LSC_tube";
				}
				if (!CheckAttribute(npchar, "quest.LSC_hello"))
				{
					link.l2 = "Привет тебе, шаман. Я воспользовался статуей и совершил необыкновенное путешествие. Ты был полностью, от начала и до конца прав - я попал на кладбище кораблей. И белого капитана там нашёл. И даже трюм с припасами - это тоже было!";
					link.l2.go = "LSC_hello";
				}
				if (CheckAttribute(npchar, "quest.LSC_hello") && pchar.questTemp.Saga.BaronReturn == "shamane")
				{
					link.l3 = "Змеиный Глаз, мне нужна твоя помощь.";
					link.l3.go = "Saga_nathaniel";
				}
			}		
			NextDiag.TempNode = "First time";
		break;
		
	//---------------------------------------- первая встреча------------------------------------------------
		case "SnakeEye":
			dialog.text = "Привет тебе, мой бледнолицый друг.";
			link.l1 = "Здравствуй и ты, шаман, коли не шутишь. С чего ты взял, что я твой друг?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Я знать много, но не всегда знать, что именно. Ты прийти сюда не случайно. Тебя привести судьба, и я помочь тебе.";
			link.l1 = "Отрадно слышать! Потому что я именно за помощью к тебе и явился, краснокожий друг. Что же, не буду рассыпаться в предисловиях и перейду сразу к делу: что ты имел в виду, когда говорил жене Хоука про Кукулькана?";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "Даже мёртвая рыба может плыть по течению. А живого человека судьба вести от цели к цели. Цель пленного капитана, за которым гнаться по сельве плохой люди, мочь быть статуя Кукулькана. Если он принести себя в жертву, то может оказаться очень далеко отсюда.";
			link.l1 = "Ничего не понял, извини. При чём тут статуя вашего бога, и как Хоук мог пешком уйти так далеко, что его до сих пор никто не может найти?";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Если Хоука пожрать Кукулькан, то отрыгнуть он его мог где угодно. Может быть даже в другой мир. Моя Кукулькан жрать три раза. И каждый раз я оказываться в самых разных местах. В последний раз много лет назад я попасть сюда и решить больше не искушать судьбу. Так что в пасть местному Кукулькану я не лазить, и где он выплевывать свои жертвы, мне неведомо.";
			link.l1 = "Господи, это выше моего понимания! То есть ты хочешь сказать, что каменный идол может перемещать человека на большие расстояния?";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "И не только. Кукулькану подвластно не только пространство, но и само время. А может, и нечто большее. Я рассказать пленный капитан про золотой статуя, пожирающий людей. Возможно, он решить рискнуть, когда понять, что погоня его настигать...";
			link.l1 = "Постой, статуя-то - каменная. А ты говоришь про золотую...";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "В полночь идол на час оживать и стать золотым. В этот момент оживать в нём и дух Кукулькана. Вот тогда бойся приближаться к нему на расстояние копья, ибо можешь встретить рассвет совсем не там, где встречал закат. Даже звёзды на небе могут поменять своё расположение. И ты встретить тех, кто ещё не родился,  увидеть рождение тех, кто уже давно умереть, или вообще не рождаться.";
			link.l1 = "Загадка на загадке... Заинтриговал ты меня, Змеиный Глаз. Но раз тебе удалось целых три раза остаться в живых после общения с Кукульканом, в которого ты веришь, отчего бы и мне не испытать свою удачу у идола чужого бога, в которого я не верю?";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "А зря. Зря не верить. Возможно, именно зов Кукулькана позвать тебя в дорогу и заставить покинуть земля предков. Только ты его пока не слышать. Всему своё время. Если ты решил рискнуть, то должен знать, что каждый раз я оставаться в живых лишь потому, что иметь при себе запас чудодейственный зелье команчей.";
			link.l1 = "Команчи? Кто это?";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "Так звать враги мой народ, который я уже никогда не увидеть. Зелье восстановить силы и здоровье, а также лечить от смертельных отравлений сильными ядами. Твоя может потребоваться несколько фляжек, но у меня их остаться только три\nБыть четвертая, но я её обронить в один странный место, больше всего похожее на кладбище каноэ белых. Оттуда начаться мой путь по этому миру. Возможно, что Кукулькан отрыгнуть капитана именно туда. Если это так, то моя ему не завидовать.";
			link.l1 = "Что это ещё за место? Кладбище каноэ? То есть кораблей?";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "Странное... Его не должно было быть, но оно есть. И жить там люди, привыкшие убивать друг друга из-за цвета кожи. На большом каноэ, куда Кукулькан отрыгнуть моя, они хранить свой припасы. Так что лучше не лезть в его трюм, который они охранять от воров, не доверяя соседям. Если ты попасть туда - найди другой выход, не ходить трюм, иначе быть беда\nПомочь найти там такой же истукан тебе мочь Белый Мальчик, если он ещё жить. У него добрый сердце, но слабый голова. Подари ему этот белый бусинка. Он обрадоваться.";
			link.l1 = "Гм... Голова идёт кругом, но становится всё занятнее и занятнее. Продолжай, мой краснокожий брат.";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			//Log_Info("Вы получили большую жемчужину");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "jewelry52");
			dialog.text = "Если найти живой капитан, он может быть очень болен. Я не успеть дать ему с собой свой зелье. А ещё поискать там мой бубен. Он достаться моя от прадед. В мой седельный сумка, которую я обронить в суматохе, быть много чего, но мне нужен именно бубен. Без него мне трудно говорить с духами.";
			link.l1 = "Да уж, весёлое местечко! Будем надеяться, что Хоук попал в другое... Ты дашь мне своего зелья?";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Дать. Взамен ты отдать мне три местный амулет: "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian)+", "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet)+" и "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg)+". По один за каждый фляга. Так быть справедливо. Приходить, как собирать все. Тогда и совершить обмен. Ты не думать, я не жадный. Возможно, пока будешь искать амулеты, тебе расхотеться рисковать, и ты передумать.";
			link.l1 = "Не передумаю. Жди меня, Змеиный Глаз, я скоро вернусь.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			npchar.quest.amulet = "true";
			AddQuestRecord("BaronReturn", "3");
			AddQuestUserData("BaronReturn", "sItem1", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian));
			AddQuestUserData("BaronReturn", "sItem2", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet));
			AddQuestUserData("BaronReturn", "sItem3", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg));
			sld = characterFromId("Danielle");
			sld.quest.talk = "SnakeEye";
			pchar.quest.BaronReturn_out.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out.function = "Saga_DannyTalk";
			pchar.questTemp.HelenDrinking.GiveAmulets = true;
			
			//if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap4_Start"))
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))	// Временно так
			{
				// Квест "Путеводная звезда", начало 4 этапа
				PChar.quest.PZ_Etap4_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap4_Start.win_condition.l1.location = "Shore9";
				PChar.quest.PZ_Etap4_Start.win_condition = "PZ_Etap4_Start";
				locations[FindLocation("Shore9")].DisableEncounters = true;
			}
		break;
		
		// даёт зелья - идем на телепортацию
		case "SnakeEye_potion":
			dialog.text = "Хорошо, мой друг. То, что ты принести мне эти амулеты, есть знак того, что ты готов отправиться к Кукулькан?";
			link.l1 = "Да. Я собираюсь повторить путь Натаниэля, пленного капитана. Мне нужно найти его.";
			link.l1.go = "SnakeEye_potion_1";
		break;
		
		case "SnakeEye_potion_1":
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Indian, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Amulet, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Obereg, 1);
			TakeNItems(pchar, "Ultimate_potion", 3);
			Log_Info("Вы отдали амулеты");
			//Log_Info("Вы получили три универсальных зелья");
			PlaySound("interface\important_item.wav");
			dialog.text = "Возьми эти зелья. Помнить, после того, как Кукулькан отрыгнуть тебя, ты должен выпить это зелье немедленно, иначе ты или умереть, или сильно-сильно болеть. Также помнить: не ходить в трюм, где бледнолицые хранить припасы. Есть другой выход из каноэ.";
			link.l1 = "Я запомню это, краснокожий брат.";
			link.l1.go = "SnakeEye_potion_2";
		break;
		
		case "SnakeEye_potion_2":
			dialog.text = "Тогда иди. В полночь прикоснись к Кукулькану, и он пожрать тебя. А я буду призывать духи тебе в помощь.";
			link.l1 = "Спасибо, Змеиный Глаз. Не беспокойся за меня - всё будет в порядке. Мы ещё обязательно встретимся!";
			link.l1.go = "SnakeEye_potion_3";
		break;
		
		case "SnakeEye_potion_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Saga.BaronReturn = "first_teleport";
			pchar.questTemp.Dolly = true; // телепорты работают!
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", true); // не пускать офицеров в локу телепорта
			DeleteAttribute(npchar, "quest.amulet");
			AddQuestRecord("BaronReturn", "4");
			sld = characterFromId("Danielle");
			sld.quest.talk = "teleport";
			pchar.quest.BaronReturn_out1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out1.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out1.function = "Saga_DannyTalk";
			QuestPointerToLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		// пришёл из LSC
		case "LSC_hello":
			dialog.text = "Я рад, что всё кончиться благополучно, мой друг. Как ты вернуться назад из кладбище каноэ?";
			link.l1 = "Я нашёл там статую Кукулькана, как ты и говорил. Мне помог Белый Мальчик - Оле Кристиансен. Правда, статуя затонула, но я смог до неё добраться. Она перенесла меня в деревню карибов...";
			link.l1.go = "LSC_hello_1";
			npchar.quest.LSC_hello = "true";
		break;
		
		case "LSC_hello_1":
			dialog.text = "Тебя встретить там Монкитекуври?";
			link.l1 = "Хм. Монкитекуври? А кто это?";
			link.l1.go = "LSC_hello_2";
		break;
		
		case "LSC_hello_2":
			dialog.text = "Это вождь деревня.";
			link.l1 = "Я не спрашивал его имени. Возможно, это был Монкитекуври, а может, кто-то другой.";
			link.l1.go = "LSC_hello_3";
		break;
		
		case "LSC_hello_3":
			dialog.text = "У него быть на голове пышный убор из птичий перо?";
			link.l1 = "А как же, был. Много перьев... Наверное, у всех попугаев в лесу хвосты повыдергал.";
			link.l1.go = "LSC_hello_4";
		break;
		
		case "LSC_hello_4":
			dialog.text = "Он. Монкитекуври. Это не перо попугай. Это перо орёл. Этот убор - мой убор. Я подарить его Монкитекуври, когда Кукулькан отрыгнуть меня туда. А потом они отвести меня к ещё один истукан...";
			link.l1 = "Ну надо же! Меня они тоже 'принесли в жертву' Кукулькану! А потом я очутился здесь, у первой статуи.";
			link.l1.go = "LSC_hello_5";
		break;
		
		case "LSC_hello_5":
			dialog.text = "Да, мой белый друг. Мой путь тоже окончиться здесь.";
			link.l1 = "Истуканы телепортируют по кругу... Но какой в этом смысл? У тебя есть догадки насчёт этого, Змеиный Глаз?";
			link.l1.go = "LSC_hello_6";
		break;
		
		case "LSC_hello_6":
			dialog.text = "Я предполагать, что статуи работать не так, как надо. Они перекидывать друг к другу, а должны все отправлять в один место. Что-то заставить их сбиться с ритм.";
			link.l1 = "Почему ты так решил?";
			link.l1.go = "LSC_hello_7";
		break;
		
		case "LSC_hello_7":
			dialog.text = "Потому что в перемещении по круг нет никакой нормальный объяснение. Кукулькан должен быть собирать жертв в один место, а не бросать между истукан.";
			link.l1 = "И что же это за место?";
			link.l1.go = "LSC_hello_8";
		break;
		
		case "LSC_hello_8":
			dialog.text = "А вот это, белый брат, великий тайна, даже для моя.";
			link.l1 = "Понятно. Ладно, Бог с ними, с истуканами. Больше я к ним не подойду ни на шаг. Белого капитана я нашёл - больше в путешествиях через порталы нет нужды.";
			link.l1.go = "LSC_hello_9";
			AddQuestRecord("BaronReturn", "12");
		break;
		
		case "LSC_hello_9":
			dialog.text = "Ты быть на кладбище каноэ. Ты случайно не найти мой бубен?";
			if (CheckCharacterItem(pchar, "buben"))
			{
				link.l1 = "Я думаю, что - да. Посмотри - это он?";
				link.l1.go = "LSC_buben";
			}
			else
			{
				link.l1 = "Нет. К сожалению, бубен мне не попадался. Но я знаю, где этот Остров из погибших кораблей, и смогу добраться туда по морю. Тогда и поищу твой бубен получше.";
				link.l1.go = "LSC_hello_10";
			}
		break;
		
		case "LSC_hello_10":
			dialog.text = "Поискать, мой белый друг. Я очень просить. Без мой бубен мне трудно слышать духи.";
			link.l1 = "Хорошо, Змеиный Глаз. Увидимся!";
			link.l1.go = "exit";
		break;
		
		case "LSC_buben":
			RemoveItems(pchar, "buben", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Он. Спасибо тебе, мой белый друг. Моя не остаться в долгу. Я дарить тебе за это оружие, который ещё не быть у вас очень долгий время. Этот оружие - оружие бледнолицых мой время.";
			link.l1 = "Очень интересно! Покажи, мой краснокожий друг...";
			link.l1.go = "LSC_buben_1";
		break;
		
		case "LSC_buben_1":
			GiveItem2Character(pchar, "pistol7");
			//Log_Info("Вы получили револьвер Кольта");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 3);
			dialog.text = "Держи. В нём всего три заряд - остальные я расстрелять - но может ты научиться делать заряд для него. Я потерять на кладбище каноэ несколько десяток составных частей для заряд - может, ты что-то и находить.";
			link.l1 = "Ого! Вот это пистоль! Никогда таких не видел... что за чудное устройство? Штука какая-то крутящаяся... Пять зарядов! Здорово!";
			link.l1.go = "LSC_buben_2";
		break;
		
		case "LSC_buben_2":
			dialog.text = "Он называться - револьвер кольт. Таких больше нет ваше время. Пользовать им легко - отводить курок назад и нажимать спуск. Он очень метко стрелять.";
			link.l1 = "Спасибо! Спасибо, Змеиный Глаз! Отличный сюрприз для врагов будет. Жаль, что всего три заряда...";
			link.l1.go = "LSC_buben_3";
		break;
		
		case "LSC_buben_3":
			dialog.text = "Попробуй научить себя делать заряды для кольт. Тогда ты стать великий воин свой время. Да, мой бледнолицый брат, я совсем забыть попросить поискать тебя на кладбище каноэ кроме бубен ещё и мой курительный трубка. Это очень красивый трубка.";
			if (CheckCharacterItem(pchar, "smoking_tube"))
			{
				link.l1 = "Ха! А я-то думаю - что это за трубка расписная? Не она?";
				link.l1.go = "LSC_tube";
			}
			else
			{
				link.l1 = "Хорошо. Я поищу твою трубку. Увидимся!";
				link.l1.go = "exit";
			}
			npchar.quest.LSC_tube = "true";
		break;
		
		case "LSC_tube":
			RemoveItems(pchar, "smoking_tube", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Она, мой брат. Я рад, что ты найти её. И я тоже сделать тебе подарок: вот этот учёный книга бледнолицых мой время. Я не суметь понять, что там есть. Попробуй найти учёный муж, который суметь прочесть и понять этот мудрый книга.";
			link.l1 = "Спасибо, Змеиный Глаз. Я подумаю, где найти такого учёного мужа.";
			link.l1.go = "LSC_tube_1";
		break;
		
		case "LSC_tube_1":
			GiveItem2Character(pchar, "chemistry");
			//Log_Info("Вы получили учебник химии Лавуазье");
			PlaySound("interface\important_item.wav");
			dialog.text = "Поискать, белый брат. В этот книга сокрыт великие секреты мудрости бледнолицых.";
			link.l1 = "Хорошо. Увидимся, Змеиный Глаз!";
			link.l1.go = "exit";
		break;
		
		// лечение Натаниэля
		case "Saga_nathaniel":
			dialog.text = "Я внимательно слушать тебя, бледнолицый брат.";
			link.l1 = "Я привёл белого капитана, за которым последовал через статую Кукулькана. Он очень болен. Я знаю, что никто, кроме тебя, не сможет его вылечить...";
			link.l1.go = "Saga_nathaniel_1";
		break;
		
		case "Saga_nathaniel_1":
			dialog.text = "Кукулькан выпить здоровье белый капитан. Я помочь ему исцелить себя. Но лечение занять не меньше луны - Кукулькан пожрать капитан уже давно и болезнь сидеть глубоко...";
			link.l1 = "Ты вылечишь его, шаман? Я принесу, всё что надо!";
			link.l1.go = "Saga_nathaniel_2";
		break;
		
		case "Saga_nathaniel_2":
			dialog.text = "Я постараться, белый брат. Ничего не нести. У моя всё есть. Прошло много время - это осложнить болезнь. Я думать - я справиться. Через луну белый капитан должен быть здоров.";
			link.l1 = "Спасибо, краснокожий брат. Ты в очередной раз выручаешь меня.";
			link.l1.go = "Saga_nathaniel_3";
		break;
		
		case "Saga_nathaniel_3":
			dialog.text = "Оставлять белый капитан мой хижина, белый брат, и ступать спокойно. Забери с собой его жена - никто не должен видеть мой обряды.";
			link.l1 = "Хорошо, Змеиный Глаз. Я заберу Даниэль. До встречи!";
			link.l1.go = "Saga_nathaniel_4";
		break;
		
		case "Saga_nathaniel_4":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "treatment";
			sld = characterFromId("Nathaniel");
			RemovePassenger(Pchar, sld);
			LAi_SetStayType(sld);
			sld.location = "none";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1.location = pchar.location;
			pchar.quest.Saga_NatanTreatment1.function = "Saga_NatanTreatment";
		break;
		
		case "calendar":
			dialog.text = "Я внимательно слушать тебя, мой друг.";
			link.l1 = "Ты помнишь нашу беседу касательно статуй Кукулькана? Ты ещё тогда сказал, что они должны переносить людей не по кругу, а в какое-то одно место?";
			link.l1.go = "calendar_1";
		break;
		
		case "calendar_1":
			dialog.text = "Помнить, белый капитан.";
			link.l1 = "Я знаю, куда эти статуи должны были отправлять пожранных Кукульканом людей.";
			link.l1.go = "calendar_2";
		break;
		
		case "calendar_2":
			dialog.text = "И куда?";
			link.l1 = "В старый город майя под названием Тайясаль. Он находится в глубине Мэйна.";
			link.l1.go = "calendar_3";
		break;
		
		case "calendar_3":
			dialog.text = "Очень интересно. Откуда ты узнать?";
			link.l1 = "Это долгая история, Змеиный Глаз. Я также понял, как ты попал сюда. Ты ведь ещё не родился, верно?";
			link.l1.go = "calendar_4";
		break;
		
		case "calendar_4":
			dialog.text = "Для ваш время ещё не родиться даже мой отец. Но я существовать ваш время, и это великая загадка.";
			link.l1 = "Разгадка достаточно проста - жрец ица по имени Канек, живущий в Тайясале, призвал на землю Кукулькана, чтобы тот воплотился в смертном обличье и впитал в себя всю мудрость белой расы. Для этой же цели он создал временную воронку, в которую затянуло несколько людей из будущего...";
			link.l1.go = "calendar_5";
		break;
		
		case "calendar_5":
			dialog.text = "Чтобы Кукулькан впитал и мудрость люди будущих лет?";
			link.l1 = "Да. А затем Кукулькан отправится в прошлое через портал, похожий на тот, через который и ты, и я проходили, и принесёт знания ныне умершим индейцам майя. Благодаря этому изменится история - майя станут господствовать в Америке, а может, и не только...";
			link.l1.go = "calendar_6";
		break;
		
		case "calendar_6":
			dialog.text = "";
			link.l1 = "Но во время ритуала что-то случилось с порталами, и они стали переносить людей не в Тайясаль, а по кругу. Вот я и пришёл за советом к тебе, Змеиный Глаз.";
			link.l1.go = "calendar_7";
		break;
		
		case "calendar_7":
			dialog.text = "Почему ко мне, белый капитан?";
			link.l1 = "Потому что тебя пожирал Кукулькан. А ещё потому, что статуя Кукулькана рядом с вашей деревней обозначена странным значком на карте, имевшей самое прямое отношение к ритуалам Канека.";
			link.l1.go = "calendar_8";
		break;
		
		case "calendar_8":
			dialog.text = "Ты показать мне эта карта?";
			link.l1 = "Вот, держи...";
			link.l1.go = "calendar_9";
		break;
		
		case "calendar_9":
			RemoveItems(pchar, "skinmap", 1);
			dialog.text = "(смотрит) Вот этот круглый знак, да? И что он означать?";
			link.l1 = "Я не знаю, шаман. Мне ясно лишь то, что только одна из трёх статуй Кукулькана отмечена этим знаком - ваша. Я делаю вывод, что она какая-то особенная, отличающаяся от прочих. Может, у тебя есть какие-то догадки?";
			link.l1.go = "calendar_10";
		break;
		
		case "calendar_10":
			dialog.text = "Дать мне время подумать до завтрашний утро, белый брат. Оставить мне этот кожаный карта. Я должен спросить у духи. Приходить завтра.";
			link.l1 = "Хорошо, краснокожий брат. Я буду завтра. Спасибо, что решил помочь мне.";
			link.l1.go = "calendar_11";
		break;
		
		case "calendar_11":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarThink", 0, 0, 1, false);
			pchar.questTemp.Tieyasal = "calendar_think";
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_wait":
			dialog.text = "Приходить позже, белый брат. Не отвлекать меня сейчас.";
			link.l1 = "Конечно, шаман...";
			link.l1.go = "exit";
			NextDiag.TempNode = "calendar_wait";
		break;
		
		case "calendar_12":
			dialog.text = "У меня есть что сказать тебе, белый брат.";
			link.l1 = "Ты что-то нашёл? Или догадался?";
			link.l1.go = "calendar_13";
		break;
		
		case "calendar_13":
			dialog.text = "Духи предков показать мне видение, я пойти к Кукулькан вместе с кожаный карта и искать. И я найти. Вероятно, это то, что ты искать, белый брат.";
			link.l1 = "Что ты раскопал?";
			link.l1.go = "calendar_14";
		break;
		
		case "calendar_14":
			dialog.text = "У истукан Кукулькан спереди в наши джунгли есть два металлический скоба из камень и выемка. Она круглый и ровной форма. Оно предназначаться для круглый плоский предмет, указанный на твоей кожаный карта.";
			link.l1 = "Что это за предмет?";
			link.l1.go = "calendar_15";
		break;
		
		case "calendar_15":
			dialog.text = "Я не знать. Я знать, что он круглый, плоский, размер как небольшой тыква, толщина с палец. Ты мочь сам пойти посмотреть на выемка в камень и скоба. Скоба нужен чтобы держать он.";
			link.l1 = "У тебя есть какие-то догадки? Предположения?";
			link.l1.go = "calendar_16";
		break;
		
		case "calendar_16":
			dialog.text = "Камень по краям в один место иметь след, как от сильный огонь. Я знать, что это. Туда попасть небесный гром.";
			link.l1 = "Молния? Туда ударила молния?";
			link.l1.go = "calendar_17";
		break;
		
		case "calendar_17":
			dialog.text = "Я быть уверен в это. Я расспросить мискито об этот истукан. Один воин сказать, что возле этот статуя, давно, быть подобран несколько красивый предмет с узорами, похожий на черепки от горшок. Сказать - очень красивый красный черепки. Их купить один белый человек из селение белых.";
			link.l1 = "Хм. Если строить логическую цепь, получается, что в это круглое 'нечто' попала молния, разбила его на черепки, а потом эти куски продали какому-то белому?";
			link.l1.go = "calendar_18";
		break;
		
		case "calendar_18":
			dialog.text = "Получаться так.";
			link.l1 = "И кто этот белый человек? Твой воин не сказал?";
			link.l1.go = "calendar_19";
		break;
		
		case "calendar_19":
			dialog.text = "Сказать. Это большой друг индеец мискито, жить в поселении Блювельд. Его звать Лесной Дьявол. Я знать его, ты тоже должен знать его.";
			link.l1 = "Ян Свенсон? Постой-ка... Красные черепки с узорами, говоришь? Похоже, фортуна повернулась ко мне лицом. Ну-ка, шаман, посмотри сюда, какие у меня есть красные черепки! Их подарил мне сам Лесной Дьявол.";
			link.l1.go = "calendar_20";
		break;
		
		case "calendar_20":
			Log_Info("Вы отдали осколки с орнаментом");
			RemoveItems(pchar, "splinter_js", 1);
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			dialog.text = "Наверное, это они. Пять черепков. Смотри сюда, белый брат. Если их разместить вот так... (складывает)";
			link.l1 = "...";
			link.l1.go = "calendar_21";
		break;
		
		case "calendar_21":
			dialog.text = "... то получиться предмет как круг. Глядеть! Они совпадать один к один. Раньше они быть целый предмет.";
			link.l1 = "Чёрт возьми! Выходит, эта штуковина уже столько времени была у меня в кармане... Слушай, шаман, так если поставить эти осколки в выемку на истукане, то...";
			link.l1.go = "calendar_22";
		break;
		
		case "calendar_22":
			dialog.text = "Кукулькан может отрыгнуть жертву туда, куда ты говорить - в старый индейский город.";
			link.l1 = "Это было бы превосходно! Мне как раз туда и надо! Как думаешь, это не страшно, что этот кругляш расколот на пять частей?";
			link.l1.go = "calendar_23";
		break;
		
		case "calendar_23":
			dialog.text = "Я думать, его надо соединить, и только потом ставить в камень в скоба.";
			link.l1 = "Соединить? Но как соединить разбитые черепки?";
			link.l1.go = "calendar_24";
		break;
		
		case "calendar_24":
			dialog.text = "Оставить это мне и мудрость духи предков, белый брат. Это не просто черепки. Это чудодейственный вещь. Приходить через три ночи, белый брат. Я призвать на помощь духи, мудрость и умение живых люди и попытаться объединить осколки.";
			link.l1 = "Невероятно... И как же мне благодарить тебя, Змеиный Глаз?";
			link.l1.go = "calendar_25";
		break;
		
		case "calendar_25":
			dialog.text = "Оставить благодарности на потом, белый брат. Ступай. Возвращаться через три ночи.";
			link.l1 = "Хорошо. Надеюсь, тебе удастся осуществить задуманное...";
			link.l1.go = "calendar_26";
		break;
		
		case "calendar_26":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarDone", 0, 0, 3, false);
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_28":
			dialog.text = "Я могу порадовать тебя, белый брат.";
			link.l1 = "Тебе удалось собрать осколки в единое целое?";
			link.l1.go = "calendar_29";
		break;
		
		case "calendar_29":
			dialog.text = "Да. Это было непросто, и на календаре остаться шрамы, но он теперь един.";
			link.l1 = "Календарь? Почему ты сказал - календарь?";
			link.l1.go = "calendar_30";
		break;
		
		case "calendar_30":
			dialog.text = "Потому что этот круглый вещь - календарь. Я изучить его внимательно. На нём изображён отсчёт времён. С помощью этот предмет индейцы из древний город считать ночи, луны, годы и века.";
			link.l1 = "Удивительно... Хотя если взять в расчёт то, что умели жрецы майя - ничего особенного, что они создали календарь.";
			link.l1.go = "calendar_31";
		break;
		
		case "calendar_31":
			GiveItem2Character(pchar, "calendar_maya");
			sld = ItemsFromID("calendar_maya");
			sld.shown = "0";
			//Log_Info("Вы получили календарь майя");
			dialog.text = "Возьми, белый капитан. Установи его в скобы на камень статуи Кукулькан. И тогда возможно он отрыгнуть тебя в индейский город.";
			link.l1 = "Чем мне тебя вознаградить, Змеиный Глаз?";
			link.l1.go = "calendar_32";
		break;
		
		case "calendar_32":
			dialog.text = "Сказать 'спасибо'. Боги вести тебя этот тропа, даже если ты не понимать. Как вы белые говорить - судьба. Кукулькан звать тебя, боги направить тебя. Иди. Делать свой дело и да охранить тебя добрые духи.";
			link.l1 = "Спасибо, Змеиный Глаз! Век тебя не забуду.";
			link.l1.go = "calendar_33";
		break;
		
		case "calendar_33":
			TakeNItems(pchar, "Ultimate_potion", 4);
			//Log_Info("Вы получили четыре универсальных зелья");
			PlaySound("interface\important_item.wav");
			dialog.text = "Постой. Мы совсем забыть важный деталь. Кукулькан пожирать человек и высасывать его жизненный сок. Я суметь приготовить наш зелье. Зелье команчей. Я дать тебе его. У меня есть четыре фляга. Ты мочь взять с собой три верный спутник, кто быть смел, чтобы дать себя пожрать Кукулькан.";
			link.l1 = "Ты столько сделал для меня, краснокожий брат...";
			link.l1.go = "calendar_34";
		break;
		
		case "calendar_34":
			dialog.text = "Друг - это не просто слово для индейца племени команч. Когда вернуться из город Кукулькан, заходить наш деревня. Мы приготовить много-много кашири. Я буду рад тебя видеть.";
			link.l1 = "Обязательно, краснокожий брат! Я непременно навещу тебя!";
			link.l1.go = "calendar_35";
		break;
		
		case "calendar_35":
			DialogExit();
			pchar.questTemp.Tieyasal = "calendar_place";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Tieyasal", "17");
			sld = ItemsFromID("skinmap");
			sld.price = 100; // кожаную карту можно выкладывать 270912 
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}