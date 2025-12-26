int iClockSP4PseudoGlobal = SOUND_INVALID_ID;

void ProcessDialogEvent()
{
	ref NPChar, sld, realShip;
	aref Link, NextDiag, arTmp;
	int i, n, NextMonth, idx;
	string sTemp, sStr, Month, NationName, shipType;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (HasSubStr(Dialog.CurrentNode, "chosenIdx/"))
	{
		Dialog.tmpIdx = FindStringAfterChar(Dialog.CurrentNode, "/");
		Dialog.CurrentNode = FindStringBeforeChar(Dialog.CurrentNode, "/");
	}

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
		
		// Диалог с Йоханом
		case "ClockTower_Johan_1":
			dialog.text = "Стойте, "+GetTitle(NPChar, true)+". Дальше нельзя.";
			link.l1 = "Почему?";
			link.l1.go = "ClockTower_Johan_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_2":
			dialog.text = "Башню видали? Контора Голландской Вест-Индской компании. Департамент корабельного учёта и архив. Вход только по записи.";
			link.l1 = "А как получить эту запись?";
			link.l1.go = "ClockTower_Johan_3";
		break;

		case "ClockTower_Johan_3":
			dialog.text = "Кому надо — знают. Минхер директор с кем попало не работает.";
			link.l1 = "'Минхер директор'? Кто это?";
			link.l1.go = "ClockTower_Johan_4";
		break;

		case "ClockTower_Johan_4":
			dialog.text = "Управляющий ван Дорн. Может, он и не совсем директор, но все так его называют. Десять лет здесь работает — порядок навёл. Теперь все корабли на Карибах через его контору проходят.";
			link.l1 = "Все корабли? Даже военные?";
			link.l1.go = "ClockTower_Johan_5";
		break;

		case "ClockTower_Johan_5":
			dialog.text = "Только лучшие корабли и самые богатые капитаны. Быть клиентом нашей конторы — большая честь!";
			link.l1 = "А что за услуги оказывают?";
			link.l1.go = "ClockTower_Johan_6";
		break;

		case "ClockTower_Johan_6":
			dialog.text = "Мне детали не положено знать — я только вход охраняю. Но, слышал, люди довольными выходят.";
			link.l1 = "Впечатляет.";
			link.l1.go = "ClockTower_Johan_7";
		break;
		
		case "ClockTower_Johan_7":
			dialog.text = "А вам я вот что ещё скажу. Часы видали? Европейское чудо, нигде такого в нашей глуши не найдёте. Минхер директор за ними лично следит.";
			link.l1 = "Может, договоримся?";
			link.l1.go = "ClockTower_Johan_8_1";
			link.l2 = "Неужели я ничего не могу сделать, чтобы попасть внутрь?";
			link.l2.go = "ClockTower_Johan_8_2";
		break;

		case "ClockTower_Johan_8_1":
			dialog.text = "Я взяток не беру!";
			link.l1 = "Извини. Славный ты малый. Как звать?";
			link.l1.go = "ClockTower_Johan_9";
		break;
		
		case "ClockTower_Johan_9":
			dialog.text = ""+npchar.name+"... Слушайте... Я понимаю, вы не отсюда. Но здесь порядок. Минхер директор всегда говорит: один раз слабину дашь — и башня наша обрушится. Хотите попасть внутрь? Помогите городу — вас заметят.";
			link.l1 = "Понятно. Бывай, солдат.";
			link.l1.go = "ClockTower_Johan_11";
		break;

		case "ClockTower_Johan_8_2":
			dialog.text = "Ну, даже не знаю. Минхер директор поощряет друзей Виллемстада. Помогите городу — и вас заметят. Я понимаю, вы не отсюда. Но здесь порядок. Минхер директор всегда говорит: один раз слабину дашь — и башня наша обрушится.";
			link.l1 = "Понятно. А зовут-то тебя как?";
			link.l1.go = "ClockTower_Johan_10";
		break;
		
		case "ClockTower_Johan_10":
			dialog.text = ""+npchar.name+", "+GetTitle(NPChar, true)+".";
			link.l1 = "А меня — "+GetTitle(NPChar, false)+" "+GetFullName(pchar)+". Бывай, солдат.";
			link.l1.go = "ClockTower_Johan_11";
		break;
		
		case "ClockTower_Johan_11":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_1");
		break;
		
		case "ClockTower_Johan_repeat":
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) >= 81)
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
				link.l1 = "Что-то случилось?";
				link.l1.go = "ClockTower_Johan_22";
				Notification_ReputationNation(true, 81, HOLLAND);
			}
			else 
			{
				dialog.text = ""+Greeting(true)+", "+GetTitle(NPChar, true)+". Я могу вам чем-нибудь помочь?";
				link.l1 = "Нет, "+npchar.name+". Служи дальше.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_repeat";
				Notification_ReputationNation(false, 81, HOLLAND);
			}
		break;
		
		case "ClockTower_Johan_21":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
			link.l1 = "Что-то случилось?";
			link.l1.go = "ClockTower_Johan_22";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_22":
			dialog.text = "Поздравляю вас. Вам назначена встреча.";
			link.l1 = "Встреча? С кем?";
			link.l1.go = "ClockTower_Johan_23";
		break;

		case "ClockTower_Johan_23":
			dialog.text = "С заместителем минхера директора. Люди весьма лестно отзываются о вас и о вашей деятельности в наших колониях, а, как он говорит, друг Голландии - его друг.";
			link.l1 = "А что сам директор?";
			link.l1.go = "ClockTower_Johan_24";
		break;

		case "ClockTower_Johan_24":
			dialog.text = "Э-э... Я ничего такого вам рассказать не имею права. Удачи вам там, "+GetTitle(NPChar, true)+".";
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower");
		break;
		
		// Диалог с Маартеном Виссером, заместителем директора
		case "ClockTower_Visser_1":
			dialog.text = "Добро пожаловать в департамент корабельного учёта ГВИК. "+UpperFirst(GetTitle(NPChar, false))+"?..";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_2":
			dialog.text = ""+GetFullName(NPChar)+", заместитель управляющего.\n"+
							"Я слышал, что вы принесли Виллемстаду немало пользы. Возможно, наша контора может принести пользу и вам.";
			link.l1 = "Для этого я и здесь.";
			link.l1.go = "ClockTower_Visser_3_1";
			link.l2 = "Я рад, что смог быть полезен столице Кюрасао.";
			link.l2.go = "ClockTower_Visser_3_2";
		break;
		
		case "ClockTower_Visser_3_1":
			dialog.text = "Каждый капитан - французский, испанский, голландский - может заказать у нас аудит судна. Мы проверяем оснастку, пушки, снасти. Находим слабые места, даём рекомендации";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
		break;

		case "ClockTower_Visser_3_2":
			dialog.text = "Каждый капитан - французский, испанский, голландский - может заказать у нас аудит судна. Мы проверяем оснастку, пушки, снасти. Находим слабые места, даём рекомендации";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "ClockTower_Visser_4":
			dialog.text = "А если одного аудита вам будет мало, то мы можем и судовые документы новые справить. Иными словами, работа нашей конторы сделает ваш корабль лучше - без траты драгоценного бакаута и шёлка.";
			link.l1 = "Как такое возможно?";
			link.l1.go = "ClockTower_Visser_4_1";
		break;

		case "ClockTower_Visser_4_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+", вы даже не представляете, в какое могущественное место вы попали и сколь многое может сделать простой росчерк пера.";
			link.l1 = "За дублоны, полагаю?";
			link.l1.go = "ClockTower_Visser_5";
		break;

		case "ClockTower_Visser_5":
			dialog.text = "Наши услуги недешёвы и зависят от размера вашего корабля. Но они всегда окупаются. Капитан, прошедший через нас, редко терпит неудачи\n"+
						"Впрочем, мы не только забираем ваше золото, но ещё и даём возможность его заработать. Пираты настолько расплодились, что даже на Малых Антилах капитанам приходится снаряжать эскадры, дабы отпугнуть этих вредителей. Принесёте доказательства уничтожения — получите выплату теми же дублонами.";
			link.l1 = "Какого рода доказательства?";
			link.l1.go = "ClockTower_Visser_6";
		break;

		case "ClockTower_Visser_6":
			dialog.text = "Судовые журналы. Даже это отребье вынуждено вести какие-никакие, но документы — иначе и люггером особо не покомандуешь. Помимо того что журналы являются безусловным доказательством злодеяний, им также всегда найдётся место в наших архивах. Полезно при страховых спорах\n"+
						"Если вам интересны наши услуги, то в списках клиентов освободилось место — один из капитанов недавно завершил сотрудничество. Выполните работу — и место ваше.";
			link.l1 = "Зачем такие сложности? Разве вам недостаточно моих дублонов?";
			link.l1.go = "ClockTower_Visser_7";
		break;

		case "ClockTower_Visser_7":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+", мы оперируем качеством, а не количеством. Каждый клиент конторы получает лучшее обслуживание и пристальное внимание самого минхера директора. А последнее, поверьте, стоит заметных денег даже для нашей далеко не бедной организации. Поскольку в месяце всего тридцать дней, то и клиентов мы можем себе позволить только тридцать.";
			link.l1 = "Что нужно сделать?";
			link.l1.go = "ClockTower_Visser_8";
		break;
		
		case "ClockTower_Visser_8":
			dialog.text = "Принесите пять пиратских судовых журналов — это докажет вашу эффективность. Награда зависит от опасности их владельцев.";
			link.l1 = "Хорошо. Я сделаю это.";
			link.l1.go = "ClockTower_Visser_9_1";
			link.l2 = "Мне нужно подумать.";
			link.l2.go = "ClockTower_Visser_9_2";
			link.l3 = "А где сам директор?";
			link.l3.go = "ClockTower_Visser_9_3";
		break;

		case "ClockTower_Visser_9_1":
			dialog.text = "Отлично. Жду результатов и надеюсь на сотрудничество.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_2":
			dialog.text = "Как скажете. Предложение остаётся в силе. Но ваше место могут занять быстрее, чем вы думаете.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_3":
			dialog.text = "В море. Минхер ван Дорн совмещает управление конторой и командование флагманом.";
			link.l1 = "Как ему это удаётся?";
			link.l1.go = "ClockTower_Visser_10";
		break;

		case "ClockTower_Visser_10":
			dialog.text = "Он работает по восемнадцать часов в сутки. Спит здесь, в кабинете наверху. Говорит, что сон — пустая трата времени. Четыре часа ему хватает.";
			link.l1 = "А как же грохот от этих огромных часовых механизмов? Как тут вообще можно спать?";
			link.l1.go = "ClockTower_Visser_11";
		break;

		case "ClockTower_Visser_11":
			dialog.text = "Вы сами сможете расспросить его и даже чему-то поучиться. Он всегда рад пообщаться с клиентами. Мы понимаем друг друга?";
			link.l1 = "Вполне.";
			link.l1.go = "ClockTower_Visser_12";
			link.l2 = "Не совсем...";
			link.l2.go = "ClockTower_Visser_12";
		break;

		case "ClockTower_Visser_12":
			dialog.text = "Хорошего вам дня, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;
		
		case "ClockTower_Visser_13_exit":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_2");
		break;
		
		// Йохан спрашивает про журналы
		case "ClockTower_Johan_31":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! Журналы с собой?";
			link.l1 = "Смотрю, ты хорошо осведомлён, "+npchar.name+".";
			link.l1.go = "ClockTower_Johan_32";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Johan_32":
			if (!CheckAttribute(npchar, "questTemp.ClockTower_Johan_journal"))
			{
				dialog.text = "Ха! Это же не пирс и не ворота в город, а я - не простой служака на посту, а сотрудник компании.";
				npchar.questTemp.ClockTower_Johan_journal = true;
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! Журналы с собой?";
			}
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Принёс я журналы. Пропустишь?";
				link.l1.go = "ClockTower_Johan_33";
			}
			link.l2 = "В другой раз.";
			link.l2.go = "ClockTower_Johan_34";
		break;
		
		case "ClockTower_Johan_33":
			dialog.text = "Рад, что всё получилось! Проходите, вас ожидают.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower_2");
		break;
		
		case "ClockTower_Johan_34":
			dialog.text = "Хорошего вам дня, "+GetTitle(NPChar, true)+".";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Johan_32";
		break;
		
		case "ClockTower_Visser_21":
			dialog.text = "Капитан! Вы вернулись. Журналы принесли?";
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Да. Все пять.";
				link.l1.go = "ClockTower_Visser_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "В другой раз.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Visser_21";
			}
			// link.l1.go = "ClockTower_Visser_36";	
			
		break;

		case "ClockTower_Visser_22":
			dialog.text = "Отлично. Покажите\n"+
						"Да, всё в порядке. Это настоящие пиратские суда. Работа выполнена качественно. Вам полагается " + SellJournals() + " дублонов\nПрошу, получите. И распишитесь ещё, пожалуйста.";
			link.l1 = "Значит, я в списках?";
			link.l1.go = "ClockTower_Visser_23";
			//RemoveItemsFromPCharTotal("ClockTower_PirateJournal", 5);	// 
		break;

		case "ClockTower_Visser_23":
			dialog.text = "Почти. Сначала нужно оформить документы. Это займёт несколько минут\n"+
						"Полное имя?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_24";
		break;

		case "ClockTower_Visser_24":
			dialog.text = "Подданство?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_25";
		break;

		case "ClockTower_Visser_25":
			dialog.text = "Название вашего корабля?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_26";
		break;

		case "ClockTower_Visser_26":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Тип судна?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_27";
		break;

		case "ClockTower_Visser_27":
			dialog.text = "Количество орудий?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_28";
		break;

		case "ClockTower_Visser_28":
			dialog.text = "Размер экипажа?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_29";
		break;

		case "ClockTower_Visser_29":
			dialog.text = "Хорошо. Теперь подпишите здесь. И здесь. И вот здесь тоже.";
			link.l1 = "Всё?";
			link.l1.go = "ClockTower_Visser_30";
		break;

		case "ClockTower_Visser_30":
			dialog.text = "Почти. Осталось только внести вас в реестр. Конечно, минхер директор должен сначала познакомиться с вами лично... Но это формальность — я уполномочен принимать новых клиентов\n"+
			"...Но я отвлёкся. Позвольте мне ещё раз ознакомить вас со списком услуг\n"+
			"Страховка. Стоит дорого, но ни одна военная эскадра не тронет корабли, застрахованные компанией. Сможете держать сколько угодно кораблей на сохранении в портовых управлениях без боязни потерять их при осаде колонии\n"+
			"Аудит корабля — немного увеличивает все характеристики без затрат стратегических товаров. Мы проверим всё: оснастку, трюм, места для экипажа. Дадим рекомендации. Цена зависит от размера корабля\n"+
			"Занесение корабля в наш реестр. Повышает безопасность судна в Карибском регионе, так что охотники за головами, пираты и военные дважды подумают, прежде чем нападать на вас\n"+
			"Аудит и заведение в реестр могут быть проведены только один раз для конкретного корабля. Так что если уж потратились, то берегите своё судно. Знали бы вы, как раздражает моё руководство, когда капитаны безалаберно относятся к своим судам и меняют их как перчатки!\n"+
			"Но я снова отвлёкся. Теперь что касается повторяемых услуг\n"+
			"Смена документов. Вы же знаете, что корабли могут иметь разную специализацию. Но вы даже не догадываетесь, что она зависит прежде всего от того, как оформлен корабль. Если вам не нравится, что ваш военный корабль оформлен под осаду фортов, то вы знаете, к кому обратиться\n"+
			"Ну, про награды за сдачу пиратских судовых журналов вы уже слышали... Чем опаснее пират, тем больше мы заплатим за его журнал.";
			link.l1 = "Впечатляет. Должен сказать, минхер Виссер, ваша контора действительно...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor");
		break;
		
		case "ClockTower_Visser_31":
			dialog.text = "'"+GetShipName("Amsterdam")+"' в гавани! Минхер директор вернулся!";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_31_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
			ClockTower_AmsterdamInTheHarbor_2();
		break;
		
		case "ClockTower_Visser_31_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_32", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_32":
			dialog.text = "Что?! Уже?! Но он должен был вернуться только через три дня!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_32_add";
		break;

		case "ClockTower_Visser_32_add":
			StartInstantDialog("ClockTower_Johan_clone", "ClockTower_Visser_33", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_33":
			dialog.text = "Минхер директор уже сошёл на берег! Идёт прямо сюда!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_33_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
		break;

		case "ClockTower_Visser_33_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_34", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_34":
			dialog.text = "Господи... Если он вас увидит...";
			link.l1 = "А в чём проблема? Вы же сами только что сказали, что у вас есть полномочия принимать новых клиентов.";
			link.l1.go = "ClockTower_Visser_35";
		break;
		
		case "ClockTower_Visser_35":
			dialog.text = "Есть! Но он не любит, когда... Неважно. Капитан, подождите снаружи. У входа. Минхер директор захочет с вами поговорить.";
			link.l1 = "Со мной?";
			link.l1.go = "ClockTower_Visser_36";
		break;
		
		case "ClockTower_Visser_36":
			dialog.text = "Он лично проверяет каждого нового клиента. Всегда. Идите, быстрее!";
			link.l1 = "Дублоны за журналы я не верну!";
			link.l1.go = "ClockTower_Visser_36_1";
			link.l2 = "Жаль, я бы остался и послушал.";
			link.l2.go = "ClockTower_Visser_36_2";
		break;
		
		case "ClockTower_Visser_36_1":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		case "ClockTower_Visser_36_2":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		// диалог с Йоханом, после того как мы вышли из башни
		case "ClockTower_Johan_41":
			dialog.text = "...";
			link.l1 = "Что это было, Йохан?";
			link.l1.go = "ClockTower_Johan_42";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Johan_42":
			dialog.text = "Минхер директор вернулся.";
			link.l1 = "И что в этом страшного?";
			link.l1.go = "ClockTower_Johan_43";
		break;

		case "ClockTower_Johan_43":
			dialog.text = "Да ничего страшного! Просто... Минхер директор не любит сюрпризов. Всё должно быть по плану. А тут — новый клиент, которого он ещё не проверил.";
			link.l1 = "Маартен сказал, что он имел право внести меня в реестр.";
			link.l1.go = "ClockTower_Johan_44";
		break;

		case "ClockTower_Johan_44":
			dialog.text = "Не-е, дело не в этом. Минхер директор просто... ну, он хочет контролировать всё сам. Каждую мелочь. Говорит, что иначе всё развалится. Вот увидите, сейчас снова за часы свои переживать начнёт.";
			link.l1 = "А?";
			link.l1.go = "ClockTower_Johan_45";
		break;
		
		case "ClockTower_Johan_45":
			dialog.text = "Минхер ван Дорн, коли в раздражение приходит, останавливает часы и начинает ковыряться в них. Иногда по полдня город без времени остаётся. А происходит такое...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_45_1";
		break;

		case "ClockTower_Johan_45_1":
			dialog.text = "Ой... Слышите? Началось.";
			link.l1 = "Начальство вернулось. Обычное дело.";
			link.l1.go = "ClockTower_Johan_46_1";
			link.l2 = "Слышу, как же. Маартену новую дыру в корме проделывают.";
			link.l2.go = "ClockTower_Johan_46_2";
            iClockSP4PseudoGlobal = ClockTower_PlaySound_rh2("Location/SP4_quest2");
		break;

		case "ClockTower_Johan_46_1":
			dialog.text = "К сожалению, теперь — обычное.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";

            if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
                SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
            ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_46_2":
			dialog.text = "Зря вы так. Несправедливо всё это, как по мне.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";	
			ChangeCharacterComplexReputation(pchar, "nobility", -2);

            if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
                SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
            ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;
		
		case "ClockTower_Johan_47":
			dialog.text = "Вроде затихло. Сейчас вас пригласят.";
			link.l1 = "У меня будут проблемы?";
			link.l1.go = "ClockTower_Johan_48";
		break;

		case "ClockTower_Johan_48":
			dialog.text = "Не волнуйтесь. Вы же ничего плохого не сделали.";
			link.l1 = "Утешил.";
			link.l1.go = "ClockTower_Johan_49";
		break;

		case "ClockTower_Johan_49":
			dialog.text = "Да ладно вам! Минхер директор, конечно, иногда излишне строг... Зато щедр и вежлив...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_50";
		break;
		
		case "ClockTower_Johan_50":
			dialog.text = "О, я же говорил!";
			link.l1 = "...";
			link.l1.go = "exit";
			ClockTower_VisserComingTowardsUs();
		break;
		
		case "ClockTower_Visser_37":
			dialog.text = "Минхер директор ждёт вас внутри.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VisserComingTowardsUs_2");
			DelLandQuestMark(npchar);
		break;
		
		// Первое знакомство с ван Дорном
		case "ClockTower_VanDoorn_1":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". Ваш корабль — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" пушек и "+GetMaxCrewQuantity(pchar)+" экипажа.";
			link.l1 = "Всё верно.";
			link.l1.go = "ClockTower_VanDoorn_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_VanDoorn_2":
			shipType = XI_ConvertString(GetShipTypeName(npchar));
			dialog.text = "Несправедливо, что я знаю о вас всё, а вы обо мне — ничего, кроме сплетен Йохана. Хендрик ван Дорн. Управляющий учётного департамента Голландской Вест-Индской компании на Карибах. Командир фрегата '"+GetShipName("Amsterdam")+"'. "+shipType+". "+GetCannonQuantity(npchar)+" пушек и "+GetMaxCrewQuantity(npchar)+" экипажа.";
			link.l1 = "Приятно познакомиться.";
			link.l1.go = "ClockTower_VanDoorn_3";
		break;

		case "ClockTower_VanDoorn_3":
			dialog.text = "Вы добыли пять пиратских судовых журналов. Мой заместитель высоко оценил вас, внёс в реестр клиентов и ознакомил с услугами моей конторы\n"+
						"Но окончательное решение о допуске всегда принимаю я. Лично. После собеседования. Маартен мог предложить кандидата — не более.";
			link.l1 = "Давайте начнём.";
			link.l1.go = "ClockTower_VanDoorn_4";
		break;
		
		case "ClockTower_VanDoorn_4":
			if (!CheckAttribute(npchar, "ClockTower_option"))
			{
				dialog.text = "Мне нужны капитаны, которые эффективно борются с пиратами и при этом достаточно успешны коммерчески, чтобы позволить себе наши услуги. Вы соответствуете этим критериям?";
			}
			else dialog.text = "";
			if (!CheckAttribute(npchar, "ClockTower_option_1") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				link.l1 = "Я уничтожил Мортимера Грима. Капитана брига '"+GetShipName("Memento")+"'.";
				link.l1.go = "ClockTower_VanDoorn_option_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_2") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				link.l2 = "Думаю, ваша компания высоко оценила мою победу над Альбертом Блэквудом. Шнява 'Леди Бет' была серьёзным противником.";
				link.l2.go = "ClockTower_VanDoorn_option_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_3") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				link.l3 = "Фернандо де Аламида пиратом не был, но...";
				link.l3.go = "ClockTower_VanDoorn_option_3";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_4") && CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l4 = "Я победил ужас всех ходящих под парусом. Вы должны знать.";
				link.l4.go = "ClockTower_VanDoorn_option_4";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_5") && GetCharacterShipClass(PChar) <= 3)
			{
				link.l5 = "Вы только что занесли мой корабль в реестр. Думаете, некомпетентный капитан смог бы его содержать?";
				link.l5.go = "ClockTower_VanDoorn_option_5";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_6") && sti(pchar.Money) >= 1000000)
			{
				link.l6 = "Я справляюсь с работой, а деньги на Карибах растут на деревьях.";
				link.l6.go = "ClockTower_VanDoorn_option_6";
			}
			link.l7 = "Минхер Виссер уже удостоверился в моей компетентности. Разве вам недостаточно оценки своего же заместителя?";
			link.l7.go = "ClockTower_VanDoorn_5";
			npchar.ClockTower_option = true;
		break;
		
		case "ClockTower_VanDoorn_option_1":
			dialog.text = "Грим? К Гриму у нашей организации никогда не было претензий, совсем напротив. Но к тому, кто занял его место... Я знаю, кем он был и с какой целью изначально прибыл на Карибы. Такие злодейства не имеют срока давности, и я рад, что вы покарали преступника и настоящего врага моей страны.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_1 = true;
		break;
		
		case "ClockTower_VanDoorn_option_2":
			dialog.text = "Если я правильно помню отчёт об инциденте на Каймане, то у вас не было шанса в этом убедиться. На мой взгляд, ситуация не самая однозначная, но ваша победа безусловно была компетентной.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_2 = true;
		break;
		
		case "ClockTower_VanDoorn_option_3":
			dialog.text = "Но мог стать кое-чем похуже, да-да. Достойный враг, хотя проиграл он не вам, а своему неблагодарному начальству. Я голландец, так что знаю, о чём говорю, когда дело касается войны с Кастилией.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_3 = true;
		break;
		
		case "ClockTower_VanDoorn_option_4":
			dialog.text = "'"+GetShipName("Flying Heart")+"'. Меня до сих пор удивляет, как честный люд не разбегается при виде этого чудовища, заходящего в порт. Меня вообще многое удивляет в этой истории, капитан. Но однажды она найдёт своё место в наших книгах и потеряет весь свой шарм. А вы... вы себя обессмертили.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_4 = true;
		break;
		
		case "ClockTower_VanDoorn_option_5":
			dialog.text = "Вы бы удивились. Но в вашем случае сомневаться не приходится, это правда.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_5 = true;
		break;
		
		case "ClockTower_VanDoorn_option_6":
			dialog.text = "И потому ничего не стоят. Если это не дублоны, конечно.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_6 = true;
		break;
		
		case "ClockTower_VanDoorn_5":
			dialog.text = "\nВы допущены к услугам конторы. Добро пожаловать в реестр клиентов досточтимой Голландской Вест-Индской Компании.";
			link.l1 = "Спасибо.";
			link.l1.go = "ClockTower_VanDoorn_6";
		break;
		
		case "ClockTower_VanDoorn_6":
			dialog.text = "Это взаимовыгодное сотрудничество. Вы получаете доступ к лучшим услугам на Карибах. Мы — надёжного партнёра.";
			link.l1 = "Хорошо.";
			link.l1.go = "ClockTower_VanDoorn_7";
		break;
		
		case "ClockTower_VanDoorn_7":
			dialog.text = "Подождите! Вы слышите?";
			link.l1 = "Ничего не слышу.";
			link.l1.go = "ClockTower_VanDoorn_8";
			// звук часов останавливается
            i = FindSoundEventId("Location/clocks_mechanism_inside");
            SetSoundEventPauseState(i, true);
            DelEventHandler("NextHour", "Villemstad_BigClock_Above");
		break;

		case "ClockTower_VanDoorn_8":
			dialog.text = "В том-то и дело! Стоило уехать на неделю...";
			link.l1 = "Что-то не так?";
			link.l1.go = "ClockTower_VanDoorn_9";
		break;

		case "ClockTower_VanDoorn_9":
			dialog.text = "С часами. Нужно проверить механизм. Извините. Это... важно.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
		break;
		
		case "ClockTower_VanDoorn_10":
			if (!CheckAttribute(npchar, "ClockTower_question"))
			{
				dialog.text = "Вроде всё хорошо. Ещё раз прошу прощения. У вас есть вопросы?";
				LAi_Fade("", "");
				// звук обратно
                i = FindSoundEventId("Location/clocks_mechanism_inside");
                SetSoundEventPauseState(i, false);
                SetEventHandler("NextHour", "Villemstad_BigClock_Above", 0);
			}
			else dialog.text = "Ещё вопросы?";
			if (!CheckAttribute(npchar, "ClockTower_question_1"))
			{
				link.l1 = "Ваш заместитель подробно рассказал об услугах конторы. Как это вообще возможно?";
				link.l1.go = "ClockTower_VanDoorn_question_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_2"))
			{
				link.l2 = "Как вы совмещаете две должности? Капитана и управляющего?";
				link.l2.go = "ClockTower_VanDoorn_question_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_3"))
			{
				link.l3 = "Как вам работается в таких условиях? Грохот часовых механизмов, темно, и окна закрыты плотными шторами.";
				link.l3.go = "ClockTower_VanDoorn_question_3";
			}
			link.l4 = "Нет, спасибо за ваше время. А что по поводу услуг конторы?";
			link.l4.go = "ClockTower_VanDoorn_11";
			npchar.ClockTower_question = true;
		break;
		
		case "ClockTower_VanDoorn_question_1":
			dialog.text = "Здесь нет никакого колдовства, "+GetTitle(NPChar, false)+". Перо и чернила правят миром. Церковь записывает рождение, крещение, венчание и смерть человека. Замени хоть одну строку — и его судьба изменится. Корабль чуть посложнее, но и в его случае росчерк пера меняет многое. Не буду скрывать, я горжусь тем, чего мне удалось достичь. И всё равно я знаю, что можно лучше. Что, если внести в учётные книги не только корабли и людей, а целый мир?";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_1 = true;
		break;
		
		case "ClockTower_VanDoorn_question_2":
			dialog.text = "Потому что кто-то должен. Предыдущий капитан 'Амстердама' погиб в бою против группы с Антигуа. Компания не нашла достойной замены. Я предложил себя. Прошёл обучение. Сдал экзамены. Получил патент\n"+
			"Да, капитан из меня неважный. Намного хуже, чем вы — это уж точно. Но хороший руководитель может управлять чем угодно, а не только кораблём. Сложно научиться командовать тремя людьми. Но как научитесь, сможете командовать и тремя тысячами. Контора, корабль, город или даже огромная компания — предела нет, до тех пор пока вы находите талантливых людей и доверяете им замещать вас... Последнее — самое сложное. Настоящее проклятие.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_2 = true;
		break;
		
		case "ClockTower_VanDoorn_question_3":
			dialog.text = "А ещё тут дышать нечем. "+UpperFirst(GetTitle(NPChar, false))+", человек сам формирует своё окружение. Тут меня ничто и никто не отвлекает, всё под рукой и подчинено только мне и времени. Если бы мог, общался бы с внешним миром посредством бумаги. К сожалению, это невозможно. И не принимайте на свой счёт, "+GetTitle(NPChar, false)+". Лучше быть одному, но не в одиночестве. Если вы понимаете, о чём я.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_3 = true;
		break;
		
		case "ClockTower_VanDoorn_11":
			// pchar.quest.ClockTower.date = rand(27)+1;
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Мы принимаем только по записи. Вам назначено... "+pchar.quest.ClockTower.date+" "+month+". Если не придёте в нужный день, то ничего страшного. Обратитесь к Йохану, и он сообщит вам следующую ближайшую запись.";
			link.l1 = "Зачем такие сложности?";
			link.l1.go = "ClockTower_VanDoorn_12";
		break;
		
		case "ClockTower_VanDoorn_12":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Наша работа стоит дорого, потому что мы вершим настоящие чудеса и приносим много пользы нашим клиентам. Конфликт интересов невозможен, и поэтому мы выделяем целый рабочий день под нужды конкретного человека. Ваш ближайший день: "+pchar.quest.ClockTower.date+" "+month+"\n"+
			"Если увидите Виссера... Маартен действовал правильно, предложив вашу кандидатуру. Передайте ему это. Он хороший заместитель. Пусть не сомневается.";
			link.l1 = "Хорошо.";
			link.l1.go = "ClockTower_VanDoorn_13";
		break;
		
		case "ClockTower_VanDoorn_13":
			dialog.text = "Доброго дня, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VanDoornInCabinet_3");
		break;
		
		case "ClockTower_Visser_41":
			dialog.text = "Как прошло?";
			link.l1 = "Это был долгий день, но ван Дорн подтвердил ваше решение.";
			link.l1.go = "ClockTower_Visser_42";
		break;

		case "ClockTower_Visser_42":
			dialog.text = "Слава Богу. Значит, я всё сделал правильно.";
			link.l1 = "Он велел передать, что вы хороший заместитель.";
			link.l1.go = "ClockTower_Visser_43";
		break;

		case "ClockTower_Visser_43":
			dialog.text = "Правда? Он... сказал это?";
			link.l1 = "Да.";
			link.l1.go = "ClockTower_Visser_44";
		break;

		case "ClockTower_Visser_44":
			dialog.text = "Чёрт. Лучше бы он этого не говорил. Теперь я буду чувствовать себя неблагодарной скотиной. А может, он это предвидел и всё рассчитал?";
			link.l1 = "Минхер заместитель, вы как-то резко перестали быть собой.";
			link.l1.go = "ClockTower_Visser_45";
		break;

		case "ClockTower_Visser_45":
			dialog.text = "Капитан, я деловой человек, и вы тоже, так что тянуть не буду\n"+
			"Минхер директор давно у нас не работает.";
			link.l1 = "Что, простите?!";
			link.l1.go = "ClockTower_Visser_46";
		break;

		case "ClockTower_Visser_46":
			dialog.text = "Он приехал сюда по контракту с одной целью — наладить работу корабельного учётного отдела. Справился просто блестяще, воспитал свою смену, выдвинул меня... и всё.";
			link.l1 = "Что, всё?";
			link.l1.go = "ClockTower_Visser_47";
		break;

		case "ClockTower_Visser_47":
			dialog.text = "Его контракт давно закончился. Мы не знаем, когда именно, но совершенно уверены, что этот человек более не имеет права занимать свою должность.";
			link.l1 = "Понятно. Начальство в центральном крыле этого здания нервничает.";
			link.l1.go = "ClockTower_Visser_48_1";
			link.l2 = "Понятно. Вы устали ждать, когда он для вас освободит своё кресло.";
			link.l2.go = "ClockTower_Visser_48_2";
		break;

		case "ClockTower_Visser_48_1":
			dialog.text = "Именно! И они ничего не могут с этим сделать!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_48_2":
			dialog.text = "Врать не буду. Я действительно устал. Чёрт возьми, ведь меня ван Дорн выдвинул ровно для того, чтобы я заместил его, когда контракт закончится!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_49":
			dialog.text = "И всё равно я бы никогда не стал шатать под ним это проклятое кресло только потому, что считаю себя обманутым! Видит Бог, я благодарен и восхищаюсь этим человеком!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_50";
		break;

		case "ClockTower_Visser_50":
			dialog.text = "Нет, "+GetAddress_Form(NPChar)+". Ван Дорна хочет согнать наше с ним общее начальство. То самое, что сидит за стеной башни — в центральном крыле этого самого здания! Но даже оно не способно найти на него управу!";
			link.l1 = "А что тут сложного? Вряд ли ван Дорн главнее Стайвесанта.";
			link.l1.go = "ClockTower_Visser_51";
		break;
		
		case "ClockTower_Visser_51":
			dialog.text = "Это не корабль и не королевский двор, капитан. Наша компания — это совершенно новый вид организации. Нельзя просто указать пальцем и уволить такого ценного человека.\n"+
					"Во-первых, никто не знает, где находится оригинал контракта ван Дорна. Ergo, нет никаких оснований для увольнения. Попробуй мы так сделать, он пришлёт ватагу крючкотворцев, и мы ещё должны ему останемся\n"+
					"Во-вторых, руководство допустило ошибку, когда выдало ван Дорну патент на '"+GetShipName("Amsterdam")+"'. Пусть он и слабый капитан, но команду подобрал — лучшую на весь регион. Отдаст приказ — и отборные солдаты Компании, не моргнув глазом, займут это здание\n"+
					"В-третьих, жена его просто обожает. И неважно, что он уже несколько лет её не видел. Дочь самого де Витта способна на многое ради любимого мужа. И Совет Семнадцати вынужден с этим мириться\n"+
					"Вы были свидетелем сегодняшней вспышки, капитан. Открою тайну: такое у нас происходит всё чаще и чаще. Директора опасаются, что однажды он выставит за дверь уже их. И они ничего не смогут сделать, потому что в гавани — '"+GetShipName("Amsterdam")+"', у ван Дорна в кабинете — ценный клиент, а дома — поддержка тестя, великого пенсионария Республики Свободных Провинций!\n"+
					"Иными словами, за вашу помощь директорат заплатит очень щедро. И сохранит ваши привилегии в конторе корабельного учёта.";
			link.l1 = "Впечатляет. Вы действительно деловой человек, Маартен. Продаёте мне предательство с таким же профессионализмом, с каким ещё недавно продавали услуги вашей конторы.";
			link.l1.go = "ClockTower_Visser_57";
		break;

		case "ClockTower_Visser_57":
			dialog.text = "Это несложно, когда искусству переговоров тебя учил сам ван Дорн и ты искренне веришь в то, что говоришь.";
			link.l1 = "Так что вы от меня хотите?";
			link.l1.go = "ClockTower_Visser_58";
		break;

		case "ClockTower_Visser_58":
			dialog.text = "То, что может сделать только посторонний человек. Проникните в контору ночью и найдите там оригинал контракта ван Дорна. Я прослежу, чтобы двери были открыты.";
			link.l1 = "Почему вы сами это не сделаете? И что мешает мне прямо сейчас пойти и рассказать всё вашему руководителю?";
			link.l1.go = "ClockTower_Visser_59";
		break;

		case "ClockTower_Visser_59":
			dialog.text = "Потому что ван Дорн по ночам имеет свойство принимать кого угодно, кроме сотрудников компании. Никто не удивится, если увидит вас, выходящего из этой башни в неучётное время.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_60";
		break;

		case "ClockTower_Visser_60":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "А что касается вашей угрозы... Сейчас вы к директору не попадёте, у вас же назначен другой день. "+pchar.quest.ClockTower.date+" "+month+", верно? К тому моменту срочность новостей несколько поуменьшится. Да и потом, директор никогда не награждает доносчиков. И всегда защищает своих сотрудников.";
			link.l1 = "Удобно для вас.";
			link.l1.go = "ClockTower_Visser_61";
		break;

		case "ClockTower_Visser_61":
			dialog.text = "Это не предательство, капитан. Мы просто хотим соблюсти контракт и обезопасить компанию. И Виллемстад, которому вы, кстати, так помогли.";
			link.l1 = "Я подумаю. Но ничего не обещаю.";
			link.l1.go = "ClockTower_Visser_62";
		break;

		case "ClockTower_Visser_62":
			dialog.text = "Большего я от вас и не требую, капитан. Прежде всего вы — наш клиент. Как бы оно ни обернулось, я очень горжусь, что именно я нашёл вас и внёс в реестр конторы.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_63";
		break;

		case "ClockTower_Visser_63":
			dialog.text = "Вы всегда сможете найти меня в центральном крыле. Доброго дня.";
			link.l1 = "До встречи.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Quest_3");
		break;
		
		case "ClockTower_Visser_64":
			dialog.text = "Здравствуйте, "+GetTitle(NPChar, false)+". Есть новости?";
			link.l1 = "Пока ничего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_64";
		break;
		
		case "ClockTower_Johan_51":
			if (GetHour() >= 6 && GetHour() < 24)
			{
				if (pchar.quest.ClockTower.date <= GetDataDay())
				{
					NextMonth = GetDataMonth() + 1;
					if (NextMonth == 13) NextMonth = 1;
				}
				else NextMonth = GetDataMonth();
				Month = XI_ConvertString("MonthGen_" + NextMonth);
				if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", сегодня ваш день. Проходите, пожалуйста.";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
						
						ClockTower_RightDay();
					}
					else
					{
						dialog.text = "Доброго дня, "+GetTitle(NPChar, false)+"!";
					}
				}
				else
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", вас ожидают в другой день. Будем рады видеть вас: "+pchar.quest.ClockTower.date+" "+month+".";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					}
					else
					{
						dialog.text = "Доброго дня, "+GetTitle(NPChar, false)+"!";
					}
				}
				link.l1 = "Спасибо, Йохан.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_51";
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeatnight"))
				{	// первая ночная встреча с Йоханом
					dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", вы что-то припозднились. Контора закрыта.";
					link.l1 = "Привет, "+npchar.name+". А я слышал, что она работает даже ночью.";
					link.l1.go = "ClockTower_Johan_52";
					npchar.ClockTower_repeatnight = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = ""+TimeGreeting()+", "+GetTitle(NPChar, false)+"!";
					link.l1 = "";
					link.l1.go = "ClockTower_Johan_53";
				}
			}
		break;
		
		case "ClockTower_Johan_52":
			dialog.text = "Это да. Всякие люди бывают. Даже священники иногда заходят, хе-хе. Но все они должны сначала пройти через меня. А я на ваш счёт указаний не получал.";
			link.l1 = "Погоди, ты что, тут сутками на посту стоишь? Как это возможно?";
			link.l1.go = "ClockTower_Johan_53";
		break;

		case "ClockTower_Johan_53":
			if (!CheckAttribute(npchar, "ClockTower_repeatnight_2"))
			{
				dialog.text = "Ага. Вот, минхер директор только что распорядился. Как у него это получается, я не знаю, но времени мне всё равно хватает и на отдых, и на службу. Да и жалованье подняли — грех жаловаться!";
				npchar.ClockTower_repeatnight_2 = true;
			}
			else
			{
				dialog.text = "Что-то ещё?";
			}
			if (!CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
			{
				link.l1 = "Тебе стоит меня пропустить. Я работаю на высшее руководство компании.";
				link.l1.go = "ClockTower_Johan_54";
				link.l2 = "(Убить его)";
				link.l2.go = "ClockTower_Johan_KillHim";
			}
			link.l3 = "Так держать, солдат.";
			link.l3.go = "ClockTower_Johan_NightExit";
		break;
		
		case "ClockTower_Johan_KillHim":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_KillToJohan");
		break;
		
		case "ClockTower_Johan_NightExit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_Johan_51";
		break;
		
		case "ClockTower_Johan_54":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				dialog.text = "Э-э. От меня-то что хотите, минхер капитан? Я простой солдат, я ничего не знаю.";
				link.l1 = "Всё ты знаешь, Йохан. Не так уж ты и прост. Господа в высоких кабинетах могут тебе не отчитываться, но про чёрную кошку между ними ты точно наслышан.";
				link.l1.go = "ClockTower_Johan_55";
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
			}
			else
			{
				dialog.text = "Я человек маленький, но через голову непосредственного начальства прыгать не стану. Простите, "+GetTitle(NPChar, true)+".";
				link.l1 = "Мы ещё вернёмся к этому разговору.";
				link.l1.go = "ClockTower_Johan_NightExit";
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
			}
		break;
		
		case "ClockTower_Johan_55":
			Achievment_Set("ach_CL_197");
			dialog.text = "Это правда, "+GetTitle(NPChar, true)+". Засиделся минхер директор. Грядёт буря.";
			link.l1 = "Что ты слышал?";
			link.l1.go = "ClockTower_Johan_56";
		break;
		
		case "ClockTower_Johan_56":
			dialog.text = "Все боятся, что не сегодня, так завтра он власть возьмёт. Слишком большой он человек для нашего захолустья. Душит всех своими проверками, каждую подпись через себя пропускает\nЯ вам честно скажу, да и вы сами видели: каждый раз, когда 'Амстердам' заходит в порт — сразу нехорошая суета поднимается.";
			link.l1 = "Я могу это решить, но для этого ты должен меня пропустить.";
			link.l1.go = "ClockTower_Johan_57";
		break;

		case "ClockTower_Johan_57":
			dialog.text = "Проходите, "+GetTitle(NPChar, true)+". Только прошу вас, не губите: если минхер директор узнает, то не сносить мне головы, а семью кормить надо.";
			link.l1 = "Я постараюсь.";
			// if (sti(pchar.reputation.nobility) >= 71) link.l1.go = "ClockTower_Johan_58_hint";
			// else link.l1.go = "ClockTower_Johan_NightSuccess";
			link.l1.go = "ClockTower_Johan_58_hint";
		break;

		case "ClockTower_Johan_58_hint":
			ClockTower_AddBook();
			dialog.text = "Хороший вы человек, "+GetTitle(NPChar, true)+". Может, я вам и помочь смогу: знаю, что в одной из книг минхер директор ключ хранит. От чего он — мне неведомо, но вдруг пригодится.";
			link.l1 = "Спасибо, Йохан.";
			link.l1.go = "ClockTower_Johan_NightSuccess";
			// if (sti(pchar.reputation.nobility) >= 71) Notification_Reputation(true, 71, "low");
		break;
		
		case "ClockTower_Johan_NightSuccess":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_NightFree");
			NextDiag.CurrentNode = "ClockTower_Johan_51";
			// if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
		break;
		
		case "ClockTower_Peter_50":
			dialog.text = "Стойте. Вы находитесь на территории Голландской Вест-Индской компании. Департамент корабельного учёта и архив. Вход только по записи.";
			link.l1 = "Я — "+GetTitle(NPChar, false)+" "+pchar.name+".";
			link.l1.go = "ClockTower_Peter_51";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_51":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Вы по записи? Проходите.";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					
					ClockTower_RightDay();
				}
				else
				{
					dialog.text = "...";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Ваша запись назначена в другой день: "+pchar.quest.ClockTower.date+" "+month+".";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = "...";
				}
			}
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Peter_51";
		break;
		
		case "ClockTower_Visser_71":
			dialog.text = "Здравствуйте, "+GetTitle(NPChar, false)+". Есть новости?";
			link.l1 = "Да. Вот контракт.";
			link.l1.go = "ClockTower_Visser_72";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_72":
			dialog.text = "Невероятно... Он закончился семь лет назад!";
			link.l1 = "Значит, это то, что нужно?";
			link.l1.go = "ClockTower_Visser_73";
		break;

		case "ClockTower_Visser_73":
			dialog.text = "Именно! С этим документом компания сможет отозвать его законно. Никаких зацепок. Никаких отговорок. Срок вышел — и точка.";
			link.l1 = "Что дальше?";
			link.l1.go = "ClockTower_Visser_74";
		break;

		case "ClockTower_Visser_74":
			dialog.text = "Я отправлю контракт в Амстердам. Совет Семнадцати примет решение. Дорну прикажут вернуться. Он не сможет отказаться.";
			link.l1 = "А если откажется?";
			link.l1.go = "ClockTower_Visser_75";
		break;

		case "ClockTower_Visser_75":
			dialog.text = "Не сможет. Пусть его жена — дочь пайщика, великого пенсионария, но даже её отец не пойдёт против Совета. Да и сама Катарина... Она ждёт десять лет. Если узнает, что он может вернуться, но отказывается — это её убьёт.";
			link.l1 = "Жестоко.";
			link.l1.go = "ClockTower_Visser_76";
		break;
		
		case "ClockTower_Visser_76":
			dialog.text = "Да. Но это единственный способ. Спасибо вам, капитан. Вы сделали важное дело.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_77";
		break;
		
		case "ClockTower_Visser_77":
			if (CharacterIsAlive("ClockTower_Johan"))
			{
				dialog.text = "Ваша награда — пятьсот дублонов. И даю вам своё слово: через два-три месяца, когда я займу кресло управляющего, вам будет предоставлен неограниченный доступ к услугам конторы. Без очередей. Без записей. В любое время.";
				AddItems(pchar, "gold_dublon", 500);
			}
			else
			{
				dialog.text = "И убили Йохана. Я и так предал человека, которым восхищаюсь и всем обязан. Теперь ещё и это\n"+
				"Может, на вашем корабле люди — что щепки, но компания ценит своих сотрудников. И мне отвратительно быть соучастником убийства\n"+
				"Ваши дублоны пойдут семье Йохана, но вторую часть сделки я выполню\n"+
				"Даю вам своё слово: через два-три месяца, когда я займу кресло управляющего, вам будет предоставлен неограниченный доступ к услугам конторы.";
			}
			link.l1 = "Рассчитываю на ваше слово. Доброго дня.";
			link.l1.go = "ClockTower_Visser_78";
		break;
		
		case "ClockTower_Visser_78":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_WaitFewMonths");
		break;
		
		case "ClockTower_Visser_79":
			dialog.text = "Здравствуйте, "+GetTitle(NPChar, false)+". Пока новостей нет. Не переживайте, я помню о нашем уговоре.";
			link.l1 = "Надеюсь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_79";
		break;
		
		case "ClockTower_Visser_81":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"! Заходите, заходите. Рад вас видеть.";
			link.l1 = "Поздравляю с назначением.";
			link.l1.go = "ClockTower_Visser_82";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_82":
			dialog.text = "Спасибо. Совет Семнадцати принял решение быстрее, чем я ожидал. Контракт оказался достаточным доказательством. Минхера ван Дорна отстранили от управления конторой.";
			link.l1 = "И как он это принял?";
			link.l1.go = "ClockTower_Visser_83";
		break;

		case "ClockTower_Visser_83":
			dialog.text = "Проигрывать он умеет. Просто собрал личные вещи из кабинета и ушёл. Хотя проиграл ли он?\n"+
			"Его командование 'Амстердамом' сохранили. На этот счёт компания, конечно, допустила промашку. Не надо было отдавать ему этот корабль ещё в тогда\n"+
			"Недооценили мы его. Как бы всё хуже по итогу не обернулось\n"+
			"И это ещё не всё.";
			link.l1 = "Куда уж хуже?";
			link.l1.go = "ClockTower_Visser_84";
		break;

		case "ClockTower_Visser_84":
			dialog.text = "Минхер ван Дорн знает, кто достал контракт из его кабинета.";
			link.l1 = "Откуда?!";
			link.l1.go = "ClockTower_Visser_85";
		break;

		case "ClockTower_Visser_85":
			dialog.text = "Не смотрите на меня так! Я ничего ему не сказал. Он сам всё понял.";
			link.l1 = "И что теперь?";
			link.l1.go = "ClockTower_Visser_86";
		break;

		case "ClockTower_Visser_86":
			dialog.text = "Теперь он считает вас врагом. Но пока вы не представляете угрозы Республике Свободных Провинций — он не тронет вас\n"+
			"Ван Дорн всегда умел отделить личное от рабочего. Вопрос в том, сможете ли вы?";
			link.l1 = "А что, если не смогу?";
			link.l1.go = "ClockTower_Visser_87";
		break;

		case "ClockTower_Visser_87":
			dialog.text = "Тогда он найдёт вас. И выполнит свою работу. Не давайте ему повода.";
			link.l1 = "Постараюсь.";
			link.l1.go = "ClockTower_Visser_88";
		break;

		case "ClockTower_Visser_88":
			dialog.text = "Доброго вам дня, "+GetTitle(NPChar, false)+". Обращайтесь к услугам нашей... моей конторы в любое время.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VillemstadStreet");
		break;
		
		case "ClockTower_Johan_61":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", вас ожидают. Минхер Виссер велел всех клиентов пускать свободно. Говорит, старые порядки слишком строгими были.";
			link.l1 = "Спасибо, Йохан.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_61":
			dialog.text = "Проходите в любое рабочее время. Записи упразднены.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Helena_1":
			dialog.text = "У тебя есть минутка?";
			link.l1 = "Для тебя — всегда.";
			link.l1.go = "ClockTower_Helena_2";
		break;

		case "ClockTower_Helena_2":
			dialog.text = "Ах, если бы, мой капитан. Есть у тебя и другие страсти в жизни. Вот сейчас, например, твою симпатичную голову занимаю совсем не я, верно?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Helena_3";
		break;

		case "ClockTower_Helena_3":
			dialog.text = "То-то. Своего мужчину я хорошо знаю. А азарт моряка — мне тем более знаком. Так что скажи прямо, дорогой\n"+
			"Во что нам встанет захват флагмана досточтимой Голландской Вест-Индской Торговой Компании?";
			link.l1 = "Чтобы ван Дорн сам пришёл за нами, мне придётся стать врагом Виллемстада.";
			link.l1.go = "ClockTower_Helena_4";
		break;

		case "ClockTower_Helena_4":
			dialog.text = "Ох, мой капитан... Значит, так оно и будет. Не в первый раз, а?";
			link.l1 = "Как будто ты не одобряешь.";
			link.l1.go = "ClockTower_Helena_5";
		break;

		case "ClockTower_Helena_5":
			dialog.text = "Я полюбила тебя таким, какой ты есть. И я всегда буду на твоей стороне. Просто помни про груз ответственности, который мы... то есть ты несёшь перед своими людьми.";
			link.l1 = "Впрочем, для этого есть наш Алонсо. Он-то тебе напомнит.";
			link.l1.go = "ClockTower_Helena_6";
		break;

		case "ClockTower_Helena_6":
			dialog.text = "Сразу как выйдем в море, мой капитан.";
			link.l1 = "Тогда не будем откладывать, дорогая.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Mary_1":
			dialog.text = "Шарль? Хочу спросить кое-что.";
			link.l1 = "Конечно, Мэри. Что случилось?";
			link.l1.go = "ClockTower_Mary_2";
		break;

		case "ClockTower_Mary_2":
			dialog.text = "Я... я волнуюсь за тебя, да. Я знаю этот взгляд. Ты думаешь о плохом.";
			link.l1 = "Глупости какие. Я сам не помню, о чём только что думал. Ты-то откуда знаешь?";
			link.l1.go = "ClockTower_Mary_3";
		break;

		case "ClockTower_Mary_3":
			dialog.text = "Знаю и всё тут! Я видела этот «Амстердам», да. Красивый корабль. Очень красивый. Но\n"+
			"Ты ведь уже всё решил... Как и раньше, да?";
			link.l1 = "Ван Дорн сам придёт за нами, но для этого мне придётся стать врагом Виллемстада.";
			link.l1.go = "ClockTower_Mary_4";
		break;

		case "ClockTower_Mary_4":
			dialog.text = "Стоит ли оно того, Шарль?";
			link.l1 = "Не знаю, Мэри.";
			link.l1.go = "ClockTower_Mary_5";
		break;

		case "ClockTower_Mary_5":
			dialog.text = "Я хочу, чтобы ты был счастлив, да. И всё же я попрошу Алонсо ещё поуговаривать тебя оставить это дело, да!";
			link.l1 = "С него станется. Пойдём, дорогая.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Girl_End":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Girl_DlgExit");
		break;
		
		case "ClockTower_Alonso_1":
			dialog.text = "Кэп, нам нужно поговорить.";
			link.l1 = "Слушаю.";
			link.l1.go = "ClockTower_Alonso_2";
			link.l2 = "Не сейчас, Алонсо.";
			link.l2.go = "ClockTower_Alonso_2";
		break;

		case "ClockTower_Alonso_2":
			dialog.text = "Тут такое дело, кэп, но выслушать меня придётся. Это, э-э, как его\n"+
			"Безотлагательный случай — во как!\n"+
			"В общем, птица донесла на хвосте, что вы лично вытурили одного из директоров компании с насиженного места, а тот затаил обиду и теперь охотится за нами на своём прекрасном фрегате.";
			link.l1 = "Это явное преувеличение.";
			link.l1.go = "ClockTower_Alonso_3";
		break;

		case "ClockTower_Alonso_3":
			dialog.text = "Вы же знаете, как народ любит языками молоть, кэп. Дайте слуху неделю настояться — и услышите, что ван Дорна охмурила дочка плантатора, что на 'Амстердаме' команда из живых мертвецов, а в трюме — сокровища самого Кортеса\n"+
			"Но мне больше интересно реальное положение дел. Так что, кэп, быть драке или нет?";
			link.l1 = "...";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Томми
			{
				link.l1.go = "ClockTower_Alonso_4_1";
			}
			else
			{
				link.l1.go = "ClockTower_Alonso_4_5";
			}
		break;
		
		case "ClockTower_Alonso_4_1":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin");
		break;
		
		case "ClockTower_Alonso_4_2":
			dialog.text = "Что, кстати, было бы чертовски весело, не спорю! Голландский флагман! Ха! Представляю лица этих сыроедов, когда мы...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_3";
		break;
		
		case "ClockTower_Alonso_4_3":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin_2");
		break;
		
		case "ClockTower_Alonso_4_4":
			dialog.text = "Томми, заткнись.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_5";
		break;
		
		case "ClockTower_Alonso_4_5":
			dialog.text = "...";
			link.l1 = "Если драке и быть, то нескоро. Ван Дорн мстить не будет, не такой он человек. Сначала нам придётся сильно разозлить голландцев.";
			link.l1.go = "ClockTower_Alonso_4_6";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "ClockTower_Alonso_4_6":
			dialog.text = "Спасибо, кэп, это успокоит команду.";
			link.l1 = "А тебя?";
			link.l1.go = "ClockTower_Alonso_5";
		break;
		
		case "ClockTower_Alonso_5":
			dialog.text = "Моя забота — беречь экипаж. От самих себя и... от вас, если получится. Вы же всё равно сделаете то, что задумали.";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Томми
			{
				link.l1 = "...";
				link.l1.go = "ClockTower_Alonso_5_add";
			}
			else
			{
				link.l1 = "Так держать, Алонсо.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
			}
		break;
		
		case "ClockTower_Alonso_5_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_6", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;
		
		case "ClockTower_Alonso_6":
			dialog.text = "Упрямый, как испанский мул!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_6_add";
		break;
		
		case "ClockTower_Alonso_6_add":
			StartInstantDialogTurnToNPC("ClockTower_Alonso", "ClockTower_Alonso_7", "Quest\ShipsPack\ClockTower_dialog.c", "Irons");
		break;
		
		case "ClockTower_Alonso_7":
			dialog.text = "Господи, за что мне это.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_7_add";
		break;
		
		case "ClockTower_Alonso_7_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_8", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_8":
			dialog.text = "Всё усложняешь! Кэп хочет красивый корабль — дадим ему красивый корабль! Мы же одна команда!";
			link.l1 = "Так держать, Алонсо. Томми, на выход.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
		break;
		
		// Абордаж Амстердама, перед боем с Ван Дормом
		case "ClockTower_VanDoorn_21":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". Ваш корабль — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" пушек и "+GetMaxCrewQuantity(pchar)+" экипажа.";
			link.l1 = "Вы, как всегда, точны, минхер директор.";
			link.l1.go = "ClockTower_VanDoorn_22";
		break;

		case "ClockTower_VanDoorn_22":
			dialog.text = "Этот титул мне больше не принадлежит — вашими стараниями. Но даже не думайте, что атаковал я вас из-за мелочного чувства мести. Я выполнял свою работу.\n"+
			"И, очевидно, с ней не справился. Да и не мог: я же вам когда-то говорил, что капитан из вас намного лучше, чем я.";
			link.l1 = "Вы сами взяли эту ношу! Ваш контракт истёк семь лет назад. Что мешало вам просто вернуться домой?";
			link.l1.go = "ClockTower_VanDoorn_23";
		break;

		case "ClockTower_VanDoorn_23":
			dialog.text = "Что мешает вам сделать то же самое? Вы знаете ответ, капитан. У вас есть мечта. У вас нет другой жизни. И стоит отпустить контроль — всё рухнет.\n"+
			"Я мог бы навести в этом краю порядок. Остановить бесконечный цикл насилия. Если бы не ослабил контроль. Если бы задавил свой страх и сделал то, что давно надо было сделать.\n"+
			"Но довольно патетики. Боец из меня такой же, как капитан, но людей я подбирать умею. Вы сами сделали себя моей последней работой, капитан. Сегодня в реестре конторы станет на двух капитанов меньше!";
			if (CheckCharacterItem(PChar, "CatharinaLetter"))
			{
				link.l1 = "Вы там что-то про страх говорили. Так прочтите это письмо."; // Доступно, если игрок принёс письмо
				link.l1.go = "ClockTower_VanDoorn_24";
			}
			link.l2 = "На одного. К бою!"; // бой
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_24":
			dialog.text = "От Катарины?! Как вы смеете мешать личное с работой?!";
			link.l1 = "Как видите, письмо всё ещё запечатано. Я жду.";
			link.l1.go = "ClockTower_VanDoorn_25";
			TakeItemFromCharacter(pchar, "CatharinaLetter");
			pchar.questTemp.ClockTower_GaveCatharinaLetter = true;
		break;

		case "ClockTower_VanDoorn_25":
			dialog.text = "...она больше не может ждать... уйдёт к другому... если я не вернусь?!";
			link.l1 = "Контору вы уже потеряли. Вашу команду истребляют прямо сейчас. Вы готовы потерять ещё и семью?";
			link.l1.go = "ClockTower_VanDoorn_26";
		break;

		case "ClockTower_VanDoorn_26":
			dialog.text = "Только не так. Капитан, вы принимаете мою капитуляцию?";
			link.l1 = "Да. Проваливайте на все четыре стороны."; // Отпускает, повышает честь
			link.l1.go = "ClockTower_VanDoorn_27";
			link.l2 = "Нет. Это была последняя услуга приговорённому. К бою!"; // бой
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_27":
			dialog.text = "Тогда поздравляю с победой, капитан "+GetFullName(pchar)+". Сегодня в реестре станет только на одного капитана меньше. Прощайте.";
			link.l1 = "...";
			link.l1.go = "ClockTower_cabinPeace";
			GiveItem2Character(PChar, "pistol15");
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE); // нужно два раза, чтобы сработало...
			TakeItemFromCharacter(npchar, "pistol15");
		break;
		
		// Финальный диалог с Маартеном
		case "ClockTower_Visser_101":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+". Я не ожидал, что вы осмелитесь сюда прийти.";
			link.l1 = "Почему же? Я всё ещё ваш клиент, и мне нужны услуги конторы.";
			link.l1.go = "ClockTower_Visser_102";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_102":
			dialog.text = "Услуги? УСЛУГИ?! После того, что вы сделали? Вы — враг досточтимой Голландской Вест-Индской Компании! А ваше место клиента займёт другой капитан!";
			link.l1 = "Это вряд ли. Смотрите, что я нашёл в бумагах ван Дорна.";
			link.l1.go = "ClockTower_Visser_103";
		break;
		
		case "ClockTower_Visser_103":
			dialog.text = "...";
			link.l1 = "Ваш предшественник посчитал ниже своего достоинства воспользоваться этим документом — даже когда кресло под ним зашаталось.";
			link.l1.go = "ClockTower_Visser_104";
			// отдаём Ключ к Маартену Виссеру
			TakeItemFromCharacter(pchar, "Visser_Key");
		break;
		
		case "ClockTower_Visser_104":
			dialog.text = "...";
			link.l1 = "Вам повезло, что у вас был такой начальник. За подобные художества вас ждал суд — в лучшем случае.";
			link.l1.go = "ClockTower_Visser_105";
		break;
		
		case "ClockTower_Visser_105":
			dialog.text = "...";
			link.l1 = "Вы деловой человек. Вы знаете, к чему я веду.";
			link.l1.go = "ClockTower_Visser_106";
		break;
		
		case "ClockTower_Visser_106":
			dialog.text = "Вы... Ваше место в реестре восстановлено.";
			link.l1 = "Эх, Маартен. Вы хотели занять место директора, хотя он дал вам всё. Он спас вас от суда и даже не посчитал нужным поставить вас в известность.";
			link.l1.go = "ClockTower_Visser_107";
		break;
		
		case "ClockTower_Visser_107":
			dialog.text = "...";
			link.l1 = "Этот грешок никогда не позволит вам подняться выше и оставит жить в постоянном страхе.";
			link.l1.go = "ClockTower_Visser_108";
		break;
		
		case "ClockTower_Visser_108":
			dialog.text = "...";
			link.l1 = "Теперь ваша очередь быть привязанным к этому месту. Но такого заместителя, какой был у ван Дорна, у вас точно не будет.";
			link.l1.go = "ClockTower_Visser_109";
		break;
		
		case "ClockTower_Visser_109":
			dialog.text = "Хватит. Вы хотите меня окончательно добить?!";
			link.l1 = "Не совсем. Я хочу, чтобы вы внесли в реестр мой новый корабль. Я не хочу никаких недопониманий.";
			link.l1.go = "ClockTower_Visser_110";
		break;
		
		case "ClockTower_Visser_110":
			dialog.text = "Ваш корабль — '"+GetShipName("Amsterdam")+"'. Флагман ГВИК. Его нельзя просто... перерегистрировать.";
			link.l1 = "Почему? Бумага всё стерпит. Разве не так работает ваша система?";
			link.l1.go = "ClockTower_Visser_111";
		break;
		
		case "ClockTower_Visser_111":
			dialog.text = "Господи, но у всего же есть предел!";
			link.l1 = "Я верю в силу этого места. Верьте и вы.";
			link.l1.go = "ClockTower_Visser_112";
		break;
		
		case "ClockTower_Visser_112":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_113";
		break;
		
		case "ClockTower_Visser_113":
			dialog.text = "Полное имя?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_114";
		break;
		
		case "ClockTower_Visser_114":
			dialog.text = "Подданство?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_115";
		break;

		case "ClockTower_Visser_115":
			dialog.text = "Название вашего корабля?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_116";
		break;

		case "ClockTower_Visser_116":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Тип судна?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_117";
		break;

		case "ClockTower_Visser_117":
			dialog.text = "Количество орудий?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_118";
		break;

		case "ClockTower_Visser_118":
			dialog.text = "Размер экипажа?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_119";
		break;

		case "ClockTower_Visser_119":
			dialog.text = "Хорошо. Теперь подпишите здесь. И здесь. И вот здесь тоже.";
			link.l1 = "Всё?";
			link.l1.go = "ClockTower_Visser_120";
		break;
		
		case "ClockTower_Visser_120":
			dialog.text = "Всё.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Visser_pausa_1");
		break;
		
		case "ClockTower_Visser_121":
			dialog.text = "...";
			link.l1 = "Вы забыли что-то сказать.";
			link.l1.go = "ClockTower_Visser_122";
		break;
		
		case "ClockTower_Visser_122":
			dialog.text = "\n"+
			"Добро пожаловать в реестр клиентов досточтимой Голландской Вест-Индской Компании.";
			link.l1 = "До встречи, минхер директор.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FINAL");
		break;
		

		//------------------Услуги конторы------------------//
		case "ClockTower_OfficeServices":
			if (npchar.id == "ClockTower_VanDoorn")
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.name+". Чем я и моя контора могут вам сегодня помочь?";
			}
			if (npchar.id == "ClockTower_Visser")
			{
				if (CharacterIsAlive("ClockTower_VanDoorn"))
				{
					dialog.text = "Рад вас видеть, "+GetTitle(NPChar, false)+"! Всегда к вашим услугам. Что вас сегодня интересует?";
				}
				else
				{
					dialog.text = "Ну? Что вас сегодня интересует?";
				}
			}
			link.l1 = "Проведёте аудит моего судна? Хочу повысить его характеристики.";
			link.l1.go = "ClockTower_OfficeServices_audit"; // Аудит
			link.l2 = "Меня не устраивает специализация моего корабля. Справите новые документы?";
			link.l2.go = "ClockTower_OfficeServices_changeTrait"; // Смена документов
			link.l3 = "Занесёте мой корабль в реестр компании? Пусть пираты и охотники подумают дважды.";
			link.l3.go = "ClockTower_OfficeServices_buffSpec"; // Занесение в реестр
			if (!CheckAttribute(pchar, "questTemp.ShipInsurance"))
			{
				link.l4 = "Хочу застраховать свои корабли на хранении в портовых управлениях. Текущие и будущие.";
				link.l4.go = "ClockTower_OfficeServices_Insurance"; // Страховка (пропадает после оплаты)
			}
			if(!CheckAttributeEqualTo(npchar, "last_logbook_date", LastSpeakDate()) && ClockTower_JournalsQty() > 0)
			{
				link.l5 = "Вы же принимаете судовые журналы пиратских капитанов?";
				link.l5.go = "ClockTower_OfficeServices_logbook"; // Награда за пиратов (раз в сутки)
			}
			link.l6 = "Пожалуй, не сегодня. Доброго дня.";
			link.l6.go = "ClockTower_OfficeServices_exit"; // Отказ
		break;

		// --> Аудит
		case "ClockTower_OfficeServices_audit":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Стоимость зависит от размера корабля. О каком судне речь?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.Audit")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}
 
			if (n == 0)
			{
				dialog.text = "К сожалению, аудит является однократной услугой для каждого отдельного корабля. Ещё что-нибудь?";
				link.l1 = "Тогда в другой раз.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "Audit"))
			{
				n = GetAuditShipCost(sld);
				dialog.text = "Давайте посмотрим... Это будет стоить " + n + " дублонов.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Приступайте.";
					link.l1.go = "ClockTower_OfficeServices_audit_upgradeShip";
				}
				link.l2 = "Хотя... давайте в другой раз.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Я вынужден вам отказать. Согласно реестру, ваш корабль отправился к морскому дьяволу много лет назад, и с этим призраком времени ничего нельзя сделать росчерком пера. Прежде чем мы сможем сотрудничать, вам стоит отреставрировать его. Говорят, что на Исла-Тесоро есть мастер, который возьмётся за такую работу.";
				link.l1 = "Ясно, спасибо.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$Корабль уже улучшен";
				link.l1 = "Ясно, спасибо.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetAuditShipCost(sld));
			UpgradeShipAudit(sld);
			dialog.text = "Готово.";
			link.l1 = "Спасибо.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;
		// <-- Аудит

		// --> Улучшение специализации
		case "ClockTower_OfficeServices_buffSpec":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Стоимость зависит от размера корабля. О каком судне речь?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "К сожалению, внесение в реестр является однократной услугой для каждого отдельного корабля. Ещё что-нибудь?";
				link.l1 = "Тогда в другой раз.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "SpecialityUpgrade"))
			{
				n = GetSpecialityUpgradeShipCost(sld);
				dialog.text = "Давайте посмотрим... Это будет стоить " + n + " дублонов.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Приступайте.";
					link.l1.go = "ClockTower_OfficeServices_buffSpec_upgradeShip";
				}
				link.l2 = "Хотя... давайте в другой раз.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Я вынужден вам отказать. Согласно реестру, ваш корабль отправился к морскому дьяволу много лет назад, и с этим призраком времени ничего нельзя сделать росчерком пера. Прежде чем мы сможем сотрудничать, вам стоит отреставрировать его. Говорят, что на Исла-Тесоро есть мастер, который возьмётся за такую работу.";
				link.l1 = "Ясно, спасибо.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$Корабль уже улучшен";
				link.l1 = "Ясно, спасибо.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetSpecialityUpgradeShipCost(sld));
			UpgradeShipSpeciality(sld);
			dialog.text = "Готово.";
			link.l1 = "Спасибо.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;
		// <-- Улучшение специализации

		// --> Смена трейта корабля
		case "ClockTower_OfficeServices_changeTrait":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Стоимость зависит от размера корабля. О каком судне речь?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				sTemp = "";
				ShipTraitCanBeChanged(sld, &sTemp);
				if (sTemp == "EmptyShip" || sTemp == "QuestCompanion") continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Хм. Я не вижу ваших кораблей в порту.";
				link.l1 = "Тогда в другой раз.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";

			if (ShipTraitCanBeChanged(sld, &sTemp))
			{
				n = GetChangeShipTraitCost(sld);
				dialog.text = "Давайте посмотрим... Это будет стоить " + n + " дублонов.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Приступайте.";
					link.l1.go = "ClockTower_OfficeServices_changeTrait_upgradeShip";
				}
				link.l2 = "Хотя... давайте в другой раз.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "QuestSP")
			{
				dialog.text = "К сожалению, это невозможно. Ваш корабль — уникальный экземпляр, овеянный легендами. Росчерк пера бессилен в таких случаях.";
				link.l1 = "Ясно, спасибо.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else
			{
				dialog.text = "О какой специализации вы говорите? Ваш корабль универсален, у него нет отличительных особенностей.";
				link.l1 = "Приятно знать, спасибо.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			// тут можно обработать другие причины отказа, но на данный момент таковых не будет
		break;

		case "ClockTower_OfficeServices_changeTrait_upgradeShip":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
			DialogExit();
			LaunchChangeShipTraitScreen(sld);
		break;
		// <-- Смена трейта корабля

		// --> Страховка
		case "ClockTower_OfficeServices_Insurance":
			n = GetInsuranceCost();
			dialog.text = "Давайте посмотрим... Это будет стоить " + n + " дублонов.";
			if (PCharDublonsTotal() > n)
			{
				link.l1 = "Приступайте.";
				link.l1.go = "ClockTower_OfficeServices_Insurance_done";
			}
			link.l2 = "Хотя... давайте в другой раз.";
			link.l2.go = "ClockTower_OfficeServices_exit";
		break;

		case "ClockTower_OfficeServices_Insurance_done":
			pchar.questTemp.ShipInsurance = true;
			RemoveDublonsFromPCharTotal(GetInsuranceCost());
			dialog.text = "Готово.";
			link.l1 = "Спасибо.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			Achievment_Set("ach_CL_199");
		break;
		// <-- Страховка
		
		// Награда за пиратов (раз в сутки) -->
		case "ClockTower_OfficeServices_logbook":
			dialog.text = "Совершенно верно. Вознаграждение зависит от количества журналов и от условной опасности их владельцев.\n" + 
						  "Сколько журналов вы принесли?"
			link.l1 = "" + ClockTower_JournalsQty();
			link.l1.go = "ClockTower_OfficeServices_logbook_1";
		break;
		
		case "ClockTower_OfficeServices_logbook_1":
			dialog.text = "Компания благодарит вас за работу. Вам положено " + JournalsCost() + " дублонов. Прошу, получите и распишитесь!"
			link.l1 = "Спасибо.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			npchar.last_logbook_date = LastSpeakDate();
			Achievment_Set("ach_CL_199");
		break;
		// <-- Награда за пиратов

		case "ClockTower_OfficeServices_exit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
		break;

		case "ClockTower_cabinFight":
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			ClockTower_CabinFight2();
		break;
		
		case "ClockTower_cabinPeace":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_cabinPeace");
		break;
	}
}

void ClockTower_NoShipInPort(ref link)
{
	dialog.text = "Что-то я не вижу вашего корабля в порту.";
	link.l1 = "Тогда в другой раз.";
	link.l1.go = "ClockTower_OfficeServices_exit";
}

int ClockTower_PlaySound_rh2(string name)
{
    float x = stf(loadedLocation.locators.reload.houseO2.x);
    float y = stf(loadedLocation.locators.reload.houseO2.y);
    float z = stf(loadedLocation.locators.reload.houseO2.z);
    return SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, name, 0, x, y, z);
}
