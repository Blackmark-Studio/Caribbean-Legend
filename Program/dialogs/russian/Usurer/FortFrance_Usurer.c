// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "М-да, позвольте угадаю... Опять ничего существенного?",
                          "Послушайте, я финансами оперирую, а не на вопросы отвечаю...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Вы угадали, простите...", "Я понимаю...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Взгляните на эти серьги, месье. Я нашёл их в кармане мёртвого бандита в джунглях. Это явно работа хорошего ювелира, которого в этой глуши и быть не могло. Можете что-нибудь сказать о них?";
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = "Я знаю, что у вас есть должник по имени Фульк Делюк. Скажите, насколько велика его... провинность?";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = "Я по поводу долга Фулька Делюка.";
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = "Я выполнил ваше задание, месье. Вот ваш... испанский друг.";
                link.l1.go = "Sharlie_14";
			}
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik"))
			{
				link.l1 = "Я по поводу...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat"))
			{
				dialog.text = "Вы принесли 100 дублонов?";
				if (PCharDublonsTotal() >= 100)
				{
					link.l1 = "Вот ваши деньги, месье.";
					link.l1.go = "Del_Deluck_5";
				}
				link.l2 = "Нет, я всё ещё думаю.";
				link.l2.go = "exit";
			}
			//<-- Миниквест "Делюк"
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "А вам-то какое дело до этого, позволю себе спросить?";
			link.l1 = "Мне нужен этот человек. Причём на свободе, а не за решёткой. А поскольку в тюрьме мне сообщили, что пока долг не будет возвращён вам, то его не выпустят, я заинтересован в погашении этого долга.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "А-а, это меняет дело. Я тоже заинтересован, чтобы мои деньги вернулись ко мне... Этот Фульк Делюк - странный тип. Он взял в долг относительно небольшую сумму денег - пять тысяч песо. Вернуть он её не вернул и стал скрываться. В итоге - процентов набежало уже на размер суммы основного долга, и сам в тюрьму угодил.";
			link.l1 = "Стало быть, на сей день его долг составляет десять тысяч?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Десять тысяч четыреста пятьдесят песо, если быть точным, месье. Так что его свобода оценивается именно в эту сумму. Вы готовы оплатить мне её? Я, пожалуй, удивлён...";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Не удивляйтесь. Вот деньги.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Хм... Сумма и впрямь приличная. Послушайте, месье, может, мы попробуем с вами договориться? Ну, например, у вас есть какое-то дело, которое я бы смог выполнить, а вы бы оценили мою услугу в эти десять с половиной тысяч...";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = "Да, похоже этот моряк вам действительно нужен, раз вы готовы выложить за него такую сумму денег. Впрочем, это не моё дело, ведь так, месье? Возьмите его расписки - теперь вы обладаете правом на его долг и можете требовать свои монеты с него. Ну и, конечно, ходатайствовать о его освобождении из тюрьмы.";
			link.l1 = "Именно этого я и хотел. До свидания, "+npchar.name+"!";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			//Log_Info("Вы получили долговые расписки");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = "Услуга? Увы, но я не нуждаюсь в ваших услугах, по крайней мере - сейчас.";
			link.l1 = "Жаль. Что же, тогда я принесу деньги за Фулька. До встречи!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = "Услуга? Хм... Знаете, месье, ещё вчера бы я ответил отрицательно, но теперь... да, у меня есть дело, выполнение которого я бы оценил в эту сумму, но предупреждаю: это опасно.";
			link.l1 = "Опасно для чего?";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Для вашей драгоценной жизни, конечно. Так что подумайте, перед тем как дать согласие, готовы ли вы к такому.";
			link.l1 = "Сударь, мне не впервой смотреть в глаза опасностям разного рода. Так что давайте перейдём к описанию подробностей, и если для этого не нужно будет в одиночку вырезать гарнизон форта, возможно, я смогу выполнить то, о чём вы сейчас так загадочно намекаете.";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = "Хорошо. Тогда слушайте. Сегодня вечером из пиратского логова Ле Франсуа, что находится в восточной части нашего острова, выйдут несколько пиратов и отправятся в бухту Ле Марен. С ними будет пленник - испанский офицер, которого они собираются сдать за выкуп англичанам\nЭтот испанский офицер - замечательный специалист в фортификационном деле, и англичане намерены использовать его таланты в своих целях. За ним специально в бухту Ле Марен присылают военный корабль из Порт-Ройяла\nОфицер - мой старинный знакомый, и я бы не хотел, чтобы он попал в плен к англичанам. Как вы понимаете, к официальным властям острова я обратиться не могу, поскольку мы с Испанией находимся в состоянии вражды\nБудь у меня побольше времени, я бы, конечно, нанял соответствующих людей для перехвата испанца... кхм, моего знакомого, но увы! Мне остаётся только предложить это дело вам, а именно: отправиться в бухту Ле Марен и... убедить пиратов отдать вам пленника\nНе думаю, что они окажутся сговорчивыми, так что - решайте.";
			link.l1 = "Сколько будет пиратов в конвое испанца?";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = "Не знаю. Может, человека два, а может - три или четыре. Ну, так что скажете?";
			link.l1 = "Я уже сказал вам - мне не привыкать смотреть в лицо опасности, и я знаю, с какой стороны держать шпагу.";
			link.l1.go = "Sharlie_10";
			link.l2 = "Хм. Вы правы - дело опасное. Не буду я в одиночку нападать на отряд пиратов.";
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Дело ваше. Если чувствуете, что не по плечу ноша - то лучше сразу отказаться. Тогда жду вас с деньгами в качестве уплаты долга Делюка.";
			link.l1 = "Хорошо. Я принесу деньги за него. До встречи!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = "Очень хорошо. Рад слышать это. Тогда вам следует отправляться в бухту Ле Марен - пираты будут там приблизительно с семи вечера и до четырёх утра. Не прозевайте их! И не вздумайте идти в бухту на корабле - спугнете негодяев. Только по суше через джунгли!\nКогда освободите пленника, приведёте его ко мне - дверь будет открыта даже ночью. Будьте осторожны и удачи вам!";
			link.l1 = "Спасибо! Удача мне точно понадобится...";
			if (CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE)) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Одну минуту! Вижу, у вас нет даже пистоля. Возьмите один из моих, и несколько зарядов к нему. Думаю, это вам пригодится.";
			link.l1 = "Да, эта штучка однозначно может понадобиться. Благодарю вас, сударь.";
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			//Log_Info("Вы получили строевой пистоль");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = "А теперь ступайте, и да поможет вам Бог!";
			link.l1 = "...";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive_Tut.win_condition.l1 = "location";
			pchar.quest.Sharlie_captive_Tut.win_condition.l1.location = "Shore39";
			pchar.quest.Sharlie_captive_Tut.function = "Tutorial_Rest_Delay";
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload2_back");
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			pchar.quest.Sharlie_captive3.over = "yes";
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("shore39", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload8_back");
			DelLandQuestMark(npchar);
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = "Замечательно! Очень рад, что вам удалось успешно с этим справиться. Подробности дела, мне, пожалуй, лучше не знать, ведь так? Ну, а мой дорогой испанский гость может чувствовать себя у меня дома в безопасности...";
			link.l1 = "Что насчёт долга Фулька Делюка?";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Да, конечно. Возьмите его расписки - теперь вы обладаете правом на его долг и можете требовать свои монеты с него. Ну и, конечно, ходатайствовать о его освобождении из тюрьмы. Я всё сделал, как обещал?";
			link.l1 = "Да, месье. Всё строго согласно договору. А теперь разрешите откланяться.";
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = "Итак, вы готовы заплатить за него долг?";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Да. Вот деньги.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "К сожалению, я ещё не собрал нужной суммы...";
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Хм. Похоже, вы правы - это дорогие серьги, и сделаны в Старом Свете, несомненно... Что я могу сказать? Я могу дать вам за них тридцать... нет, даже тридцать пять золотых дублонов. Соглашайтесь, дороже вам их не продать.";
			link.l1 = "Тридцать пять дублонов? Неплохая цена. Я согласен. Забирайте.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Нет. Лучше я оставлю эту драгоценность себе.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("Вы отдали серьги");
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		//--> Миниквест "Делюк"
		case "Del_Deluck":
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			dialog.text = "Знаю-знаю, капитан. Ваш штурман умудрился наделать долгов почти в каждой колонии Франции. Правду сказать, я об этом знал, запрашивал информацию о Делюке у коллег, это стандартная практика...";
			link.l1 = "А вы не думали, что эта незначительная деталь стоит того, чтобы сразу мне о ней рассказать?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Зачем? На тот момент меня интересовал конкретно долг месье Делюка мне. Кстати, он был самым значительным. Но, как только вы уладили этот вопрос, я немедленно дал знать коллегам... Мы нанимаем лучшие курьерские суда, и в моём столе очень быстро скопилось много других долговых расписок Делюка...";
			link.l1 = "Понимаю... Вы их выкупили, зная о моей заинтересованности в этом человеке. Это ни что иное, как ловушка и шантаж, месье.";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "Это всего лишь моя работа, капитан! Весь долг вашего штурмана на сегодняшний день составляет сто дублонов, и, прошу заметить, проценты тоже набегают... Будете оплачивать?";
			link.l1 = "Я пока не готов дать вам ответ, месье. Но я подумаю. До свидания!";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik_repeat = true;
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.dialog.currentnode = "Del_Deluck";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Замечательно! Дальнейшие действия вы уже знаете. Держите документы - покажете их коменданту тюрьмы. Приятно было иметь с вами дело, капитан.";
			link.l1 = "Приятного во всей этой ситуации довольно мало, месье. Прощайте.";
			link.l1.go = "exit";
			RemoveItems(pchar, "gold_dublon", 100);
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			//Log_Info("Вы получили долговые расписки");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Del_DeluckSvoboda = true;
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

