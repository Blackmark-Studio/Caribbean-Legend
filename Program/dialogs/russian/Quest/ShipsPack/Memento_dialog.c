void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
		
		// Диалог с Алонсо после успешного абордажа
		case "Memento_MortimerGrimDead_Alonso_1":
			dialog.text = "Кэп, день - наш. Авангард заканчивает зачистку нижней палубы. Пленных нет... Ба! Вижу, вы тоже не церемонились.";
			link.l1 = "Почему-то я ожидал"+GetSexPhrase("","а")+" от него пафосной речи. А он сразу в бой кинулся.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_2";
			Achievment_Set("ach_CL_154");
		break;
		
		case "Memento_MortimerGrimDead_Alonso_2":
			dialog.text = "Разрешите высказаться?";
			link.l1 = "Разрешаю.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_3";
			link.l2 = "Нет, здесь мы закончили.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_end";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_3":
			dialog.text = "Зачем мы напали на них? Этот бриг никакой угрозы нам не представлял, товара не возил. О Гриме, конечно, слухи разные ходили, но боялись его только торговцы живым товаром. Куча народу вы сегодня положили - и непонятно ради чего.";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) >= 2)
			{
				link.l1 = "...";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_4";
			}
			else
			{
				link.l1 = "Ты сейчас от лица команды говоришь?";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
			}
		break;
		
		case "Memento_MortimerGrimDead_Alonso_4":
			dialog.text = "И это уже не в первый раз...";
			link.l1 = "Ты сейчас от лица команды говоришь?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_5":
			dialog.text = "Не-а. Уж поверьте, если бы у команды возникли такого рода вопросы, значит я плохо делаю свою работу, а вы - уже живой мертвец\n"+
			"К счастью для вас, народ заимел хороший прибыток с этой кровавой авантюры. Карманы каждого матроса на этом корабле были забиты дублонами до отказа!\n"+
			"Ценного груза, правда, никакого - одни туземные побрякушки да жуткие амулеты. Но люди все равно поживились от души. Грим, видать, хорошо им платил\n"+
			"Надеюсь, вы не станете заявлять о своих правах на долю этого золота, кэп?";
			link.l1 = "Не стану, Алонсо. Спасибо, что держишь в курсе.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_6";
			link.l2 = "Стану. Проследи, чтобы моя доля была доставлена в каюту.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_7";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_6":
			dialog.text = "Я всегда на вашей стороне, кэп. Кстати, что вы будете делать с 'Мементо'?";
			link.l1 = "Возьму призом - а как иначе?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Пока не решил"+GetSexPhrase("","а")+".";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_7":
			dialog.text = "Я всегда на вашей стороне, кэп. Кстати, что вы будете делать с 'Мементо'?";
			link.l1 = "Возьму призом - а как иначе?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Пока не решил"+GetSexPhrase("","а")+".";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
			AddCrewMorale(Pchar, -10);
			AddItems(Pchar, "gold_dublon", 500);
		break;
		
		case "Memento_MortimerGrimDead_Alonso_8":
			dialog.text = "Лучше не стоит. Он весь обвешан какими-то туземными символами. Да и ходят о нем нехорошие слухи - говорят, он когда-то пережил чудовищную эпидемию и что на палубах разве что мертвецы не танцевали\n"+
			"Про скелет на корме я уж вообще молчу: пока какой-нибудь идиот не отважится свистнуть череп куражу ради - на корме еще долго никто кроме меня вахту держать не отважится.";
			link.l1 = "Принято, Алонсо. Возвращайся к работе.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_9";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_9":
			dialog.text = "Так точно, кэп.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_end";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_end":
			DialogExit();
			AddDialogExitQuestFunction("Memento_MortimerGrimDead_Alonso_2");
		break;
		
		// Диалог с Алонсо в первую ночь
		case "Memento_Dich_EtapOne_Alonso_1":
			dialog.text = "Капитан, извините, что беспокою в такой час.";
			link.l1 = "Докладывай, Алонсо.";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_2";
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				dialog.text = "Капитан? А что вы здесь делаете? Вы что, спали здесь?";
				link.l1 = "Неважно.";
				link.l1.go = "Memento_Dich_EtapTwo_Alonso_2";
				link.l2 = "В моей каюте как-то... неуютно.";
				link.l2.go = "Memento_Dich_EtapTwo_Alonso_2";
			}
		break;
		
		case "Memento_Dich_EtapOne_Alonso_2":
			dialog.text = "Дела наши - поганые. Настроение у экипажа - ни к черту! Люди уже открыто говорят, что корабль проклят. Жалуются, что им что-то мерещится по ночам.";
			link.l1 = "Что именно мерещится?";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_3";
		break;
		
		case "Memento_Dich_EtapOne_Alonso_3":
			dialog.text = "Кошмары какие-то. Но хуже всего то, что один из наших людей умер от лихорадки. Молодой парень, здоровяк, а сгорел за пару часов.";
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				link.l1 = "Это уже врачу решать. "+sld.name+" своё дело знает.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
			else
			{
				link.l1 = "Так не бывает. Держи команду в узде, Алонсо. Это твоя работа.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
		break;
		
		case "Memento_Dich_EtapOne_Alonso_4":
			dialog.text = "Так точно!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapOne_End");
		break;
		
		// Диалог с Алонсо во вторую ночь
		case "Memento_Dich_EtapTwo_Alonso_2":
			dialog.text = "Понимаю. Многие из команды теперь спят скопом - боятся оставаться одни. Можно подумать, что на корабле вообще можно остаться одному…";
			link.l1 = "У меня, как видишь, не получилось. Что произошло?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_3";
		break;
		
		case "Memento_Dich_EtapTwo_Alonso_3":
			dialog.text = "Драка — Хосе заколол Марселя. Кричал, что тот «несёт заразу».";
			link.l1 = "Ситуация ухудшилась?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_4";
		break;
		
		case "Memento_Dich_EtapTwo_Alonso_4":
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				dialog.text = "Вам же "+sld.name+" уже докладывал утром. Одиннадцать душ потеряли. Что будем делать?";
			}
			else
			{
				dialog.text = "Ещё одиннадцать душ потеряли. Что будем делать?";
			}
			link.l1 = "Я приму решение.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_5";
		break;
		
		case "Memento_Dich_EtapTwo_Alonso_5":
			dialog.text = "Надеюсь, капитан. Как поступим с Хосе? Убийство - это не шутки.";
			link.l1 = "Повесить после склянок. Покажем, что ситуация под контролем.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_6";
			link.l2 = "Тридцать плетей. Выживет - значит Бог так рассудил.";
			link.l2.go = "Memento_Dich_EtapTwo_Alonso_7";
		break;
		
		case "Memento_Dich_EtapTwo_Alonso_6":
			dialog.text = "Так точно!";
			link.l1 = "...";
			link.l1.go = "exit";
			SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		case "Memento_Dich_EtapTwo_Alonso_7":
			dialog.text = "Так точно!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddCrewMorale(Pchar, -10);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		// Диалог с Алонсо в третью ночь
		case "Memento_Dich_EtapThree_AlonsoPrizrak_1":
			dialog.text = "Кэп! Полундра!! Вам немедленно пройти в гандек!";
			link.l1 = "Что случилось?";
			link.l1.go = "Memento_Dich_EtapThree_AlonsoPrizrak_2";
		break;
		
		case "Memento_Dich_EtapThree_AlonsoPrizrak_2":
			dialog.text = "Лучше вы сами это увидите. Идёмте, быстрее!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_4_1");
		break;
		
		// Уже утром
		case "Memento_Dich_EtapThree_Alonso_1":
			dialog.text = "Доброе утро, кэп!";
			link.l1 = "А?!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_2";
		break;
		
		case "Memento_Dich_EtapThree_Alonso_2":
			dialog.text = "Э-э, да на вас лица нет. Плохо спалось? Ну ничего, сейчас я вас обрадую. Эпидемия прекратилась. Да и не было её, как выяснилось.";
			link.l1 = "Это как?";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_3";
		break;
		
		case "Memento_Dich_EtapThree_Alonso_3":
			dialog.text = "Народ переволновался, наслушался глупых слухов про проклятый корабль. Сила самовнушения - вещь страшная, скажу я вам. Не один корабль погубила.";
			link.l1 = "Но ведь люди гибли!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_4";
		break;
		
		case "Memento_Dich_EtapThree_Alonso_4":
			dialog.text = "Бой, грязные раны, тухлая солонина — обычная морская арифметика. Если бы мы все так не накрутили друг друга россказнями про проклятые корабли, то, как знать, может потеряли бы на пару человек меньше\n"+
			"Скелет на корме тоже оптимизма не добавлял. Хорошо, что какой-то… шутник ночью стащил у него шляпу\n"+
			"Поскольку за такое кощунство в корабль не ударила молния, народ несколько оживился и моряцкая смекалка стала составлять коварные планы, как начать тревожить скелет. Вот, например…";
			link.l1 = "Скелет не трогать!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_5";
		break;
		
		case "Memento_Dich_EtapThree_Alonso_5":
			dialog.text = "Э-э.. Ну, если у вас к нему образовались нежные чувства, то конечно не будем. Хорошего вам дня, кэп\n"+
			"Кстати, отличная шляпа! Вам очень идет. Предыдущему владельцу она была явно мала.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_End");
		break;
		
		// Диалоги с командой Мементо
		case "Memento_Sailor_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Приветствую, капитан. Вам стоит обратится к капитану Гриму.";
				link.l1 = "Уж прости, матрос, но ты здесь выделяешься.";
				link.l1.go = "Memento_Sailor_1_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Что-нибудь ещё, капитан?";
				link.l1 = "Ничего.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_1";
		break;
		
		case "Memento_Sailor_1_1":
			dialog.text = "Понимаю, о чём вы, капитан. Я служил у вольного капитана — такого же, как вы. Он искал сокровища, торговал, фрахты выполнял. И вот решил торговцев между делом пощипать — да не вышло. Выживших приговорили к виселице за пиратство.";
			link.l1 = "И капитан Грим вас выкупил?";
			link.l1.go = "Memento_Sailor_1_2";
		break;
		
		case "Memento_Sailor_1_2":
			dialog.text = "Одной партией, как товар. Опытный матрос каждому нужен, а по тавернам капитан Грим народ не набирает ... Зато кормит и щедро платит. А мы служим — и участвуем в жребии.";
			link.l1 = "В жребии?";
			link.l1.go = "Memento_Sailor_1_3";
		break;
		
		case "Memento_Sailor_1_3":
			dialog.text = "Простите, нам не стоит это обсуждать.";
			link.l1 = "Почему же не уйдёте?";
			link.l1.go = "Memento_Sailor_1_4";
		break;
		
		case "Memento_Sailor_1_4":
			dialog.text = "Куда? Так хоть шанс есть. Может, повезёт. На любом судне — свой жребий. У капитана Грима свой, у вас — свой. Мы же не люди, а просто числа в корабельных книгах.";
			link.l1 = "У меня на корабле порядки другие.";
			link.l1.go = "Memento_Sailor_1_5";
		break;
		
		case "Memento_Sailor_1_5":
			dialog.text = "Как скажете, капитан. Доброго вам дня.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_1";
		break;
		
		case "Memento_Sailor_2":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Давно гостей не было на нашем славном судне!";
				link.l1 = "Ты матрос? Не похож.";
				link.l1.go = "Memento_Sailor_2_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Что-нибудь ещё, капитан?";
				link.l1 = "Ничего.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_2";
		break;
		
		case "Memento_Sailor_2_1":
			dialog.text = "Ха! Меня кэп выкупил прямо из камеры. Должны были повесить в Порт-Рояле: зарезал я одного типа — молоденький хлыщ, всё стишки свои читал. Заслужил, сволочь.";
			link.l1 = "Повезло, значит?";
			link.l1.go = "Memento_Sailor_2_2";
		break;
		
		case "Memento_Sailor_2_2":
			dialog.text = "А то! Капитан не скупится, правда, иногда приходится участвовать в его ... играх.";
			link.l1 = "В каких играх?";
			link.l1.go = "Memento_Sailor_2_3";
		break;
		
		case "Memento_Sailor_2_3":
			dialog.text = "Раз в неделю тянем палочки: короткая — идёшь на особо опасную работу или, вовсе, за борт прыгаешь. Весело, в общем. Не всем, конечно, но капитан говорит: так отсеиваются недостойные.";
			link.l1 = "Недостойные чего?";
			link.l1.go = "Memento_Sailor_2_4";
		break;
		
		case "Memento_Sailor_2_4":
			dialog.text = "А я знаю? Кэп уж горазд языком чесать, разглагольствует, что твой поп: «Только познав смерть, можно по-настоящему жить!»\n"+
			"(сплёвывает)";
			link.l1 = "За плевок на палубе положена плеть. Ты ведёшь себя как бандит, а не моряк. Прощай.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_2";
		break;
		
		case "Memento_Sailor_3":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Здравствуйте, капитан.";
				link.l1 = "Как ты попал сюда?";
				link.l1.go = "Memento_Sailor_3_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Что-нибудь ещё, капитан?";
				link.l1 = "Ничего.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_3";
		break;
		
		case "Memento_Sailor_3_1":
			dialog.text = "Капитан Грим захватил невольничий корабль, на котором я был. Я тогда болел, умирал в трюме ... многого не помню. Очнулся уже здесь, на 'Мементо'.";
			link.l1 = "И что стало с другими рабами?";
			link.l1.go = "Memento_Sailor_3_2";
		break;
		
		case "Memento_Sailor_3_2":
			dialog.text = "Не знаю. Капитан говорит, что освободил всех, но я был единственным, кого привезли на корабль. Остальные, наверное, разбежались по островам или умерли от ран. Я плохо помню тот день.";
			link.l1 = "Зато ты свободен.";
			link.l1.go = "Memento_Sailor_3_3";
		break;
		
		case "Memento_Sailor_3_3":
			dialog.text = "Свободен? Здесь никто не свободен. Капитан даёт золото, кормит, одевает, но взамен требует полной преданности — и устраивает этот жуткий жребий.";
			link.l1 = "Жребий?";
			link.l1.go = "Memento_Sailor_3_4";
		break;
		
		case "Memento_Sailor_3_4":
			dialog.text = "Каждую неделю кто-то тянет короткую палочку и получает опасную работу, с которой не все возвращаются. Капитан говорит: так отделяются живые от мёртвых.";
			link.l1 = "И вы терпите это?";
			link.l1.go = "Memento_Sailor_3_5";
		break;
		
		case "Memento_Sailor_3_5":
			dialog.text = "Каждый надеется, что повезёт именно ему. У капитана для каждого найдётся свой ключик: страх снова оказаться в петле, жадность до золота, желание отдать долг за спасённую жизнь. Мне всё это неинтересно. Деньги мне не нужны, а долг ... какой может быть долг за то, чего не помнишь?";
			link.l1 = "Не боишься говорить об этом открыто?";
			link.l1.go = "Memento_Sailor_3_6";
		break;
		
		case "Memento_Sailor_3_6":
			dialog.text = "А что мне сделают? Это корабль мертвецов, капитан, и я здесь на своём месте. А вот вы — нет.";
			link.l1 = "Как скажешь. Прощай.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_3";
		break;
		
		case "Memento_Sailor_4":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Добро пожаловать на борт 'Мементо', капитан.";
				link.l1 = "Испанский солдат на пиратском корабле? Это необычно.";
				link.l1.go = "Memento_Sailor_4_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Что-нибудь ещё, капитан?";
				link.l1 = "Ничего.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		case "Memento_Sailor_4_1":
			dialog.text = "Дезертир я. Капитан Грим выкупил меня прямо с виселицы на площади Сан-Хосе. Дорого заплатил — целый мешок дублонов за мою пыльную шкуру.";
			link.l1 = "И за что вас приговорили?";
			link.l1.go = "Memento_Sailor_4_2";
		break;
		
		case "Memento_Sailor_4_2":
			dialog.text = "Офицер Сальдо послал нас охранять рабочих в сельве, где половина умирает от лихорадки за неделю. Я решил, что моя жизнь дороже. Теперь вот ... служу тому, кто её оценил в звонкую монету.";
			link.l1 = "Не жалеете?";
			link.l1.go = "Memento_Sailor_4_3";
		break;
		
		case "Memento_Sailor_4_3":
			dialog.text = "Сколь верёвочке ни виться ... Капитан щедр к тем, кто ему верен. Правда, иногда устраивает странные испытания — жребий. Не всем везёт.";
			link.l1 = "Жребий?";
			link.l1.go = "Memento_Sailor_4_4";
		break;
		
		case "Memento_Sailor_4_4":
			dialog.text = "Ну, знаете. Кому-то выпадает работа на марсах в шторм, кому-то — место в авангарде. Капитан говорит: так проверяется, готов ли ты. Уж не знаю к чему, но надеюсь, мне повезёт.";
			link.l1 = "Удачи ... наверное.";
			link.l1.go = "Memento_Sailor_4_5";
		break;
		
		case "Memento_Sailor_4_5":
			dialog.text = "Спасибо, капитан. Смерть всё равно идёт за каждым.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		/*case "Memento_Sailor_5":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Диалог 5";
				link.l1 = "Диалог 5";
				link.l1.go = "exit";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Что-нибудь ещё, капитан?";
				link.l1 = "Ничего.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_5";
		break;*/
		
		case "Memento_MortimerGrim_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Добро пожаловать на борт 'Мементо', коллега. Меня зовут Мортимер Грим.";
				link.l1 = "Капитан "+GetFullName(pchar)+". Благодарю, что приняли...";
				link.l1.go = "Memento_MortimerGrim_2";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "О чём ещё поговорим?";
				if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
				{
					link.l1 = "У вас удивительный клинок, капитан.";
					link.l1.go = "Memento_MortimerGrim_question_1_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
				{
					link.l2 = "Ваша подзорная труба отлично смотрится со скелетом.";
					link.l2.go = "Memento_MortimerGrim_question_2_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
				{
					link.l3 = "Надо сказать, у вас очень разношёрстная команда.";
					link.l3.go = "Memento_MortimerGrim_question_3_1";
				}
				link.l4 = "Ничего... коллега. Попутного вам ветра.";
				link.l4.go = "exit";
				NextDiag.TempNode = "Memento_MortimerGrim_1";
			}
		break;
		
		case "Memento_MortimerGrim_2":
			dialog.text = "Карибы щедры к тем, кто спешит на плаху, уж я-то знаю.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_3";
		break;
		
		case "Memento_MortimerGrim_3":
			dialog.text = "Да? Вы хотели что-то спросить?";
			link.l1 = "У вас за спиной скелет висит.";
			link.l1.go = "Memento_MortimerGrim_4";
			link.l2 = "Хороший сегодня ветер, да? И погода отличная.";
			link.l2.go = "Memento_MortimerGrim_5";
		break;
		
		case "Memento_MortimerGrim_4":
			dialog.text = "Какой ещё скелет? За моей спиной — только синее Карибское море.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;
		
		case "Memento_MortimerGrim_5":
			dialog.text = "Согласен, коллега. Каждый день бы так!";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;
		
		case "Memento_MortimerGrim_6":
			dialog.text = "Ха-ха-ха! Эта шутка никогда не устаревает! Не пугайтесь: старина Йорик, как и этот корабль, сувенир из моей прошлой жизни. В буквальном смысле, разумеется.";
			link.l1 = "'Разумеется'?";
			link.l1.go = "Memento_MortimerGrim_7";
		break;
		
		case "Memento_MortimerGrim_7":
			dialog.text = "Коллега, а вы боитесь смерти? Это не угроза, мне действительно интересно.";
			link.l1 = "Разумеется. Кто говорит обратное, тот лжёт.";
			link.l1.go = "Memento_MortimerGrim_8_leadership";
			link.l2 = "Нет. Все там будем.";
			link.l2.go = "Memento_MortimerGrim_8_weapon";
			link.l3 = "А вы?";
			link.l3.go = "Memento_MortimerGrim_8_sneak";
		break;
		
		case "Memento_MortimerGrim_8_leadership":
			dialog.text = "О! Смерть — мать всех страхов. Одиночества, темноты или наказания — всё это лишь её маски.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Memento_MortimerGrim_8_weapon":
			dialog.text = "О! Смерть — мать всех страхов. Одиночества, темноты или наказания — всё это лишь её маски.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "Memento_MortimerGrim_8_sneak":
			dialog.text = "О! Смерть — мать всех страхов. Одиночества, темноты или наказания — всё это лишь её маски.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Memento_MortimerGrim_9":
			dialog.text = "Зачем далеко ходить? Вот взять старину Йорика: груда костей с фонарём в рёбрах — а даже такого грозного капитана, как вы, заставил понервничать!";
			if (startHeroType == 4)
			{
				dialog.text = "Зачем далеко ходить? Вот взять старину Йорика: груда костей с фонарём в рёбрах — а даже бесстрашную Элен, дочь великого Шона МакАртура, заставил понервничать!";
			}
			link.l1 = "Красиво говорите, только не сказали, что со всем этим делать.";
			link.l1.go = "Memento_MortimerGrim_10";
		break;
		
		case "Memento_MortimerGrim_10":
			dialog.text = "Я-то знаю, но не всем моё лекарство подходит. Попробовать всегда успеете, но сначала скажите, что думаете сами.";
			link.l1 = "Библия говорит, что смерти нет.";
			link.l1.go = "Memento_MortimerGrim_11_1";
			link.l2 = "Если начну бояться — конец кораблю.";
			link.l2.go = "Memento_MortimerGrim_11_2";
			link.l3 = "Ответ утонул на дне бутылки рома.";
			link.l3.go = "Memento_MortimerGrim_11_3";
		break;
		
		case "Memento_MortimerGrim_11_1":
			dialog.text = "Это правда. Единственное в чём я с этой книжкой согласен.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;
		
		case "Memento_MortimerGrim_11_2":
			dialog.text = "Похвально. Но зря тревожитесь: смерти нет.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;
		
		case "Memento_MortimerGrim_11_3":
			dialog.text = "Йо-хо-хо! Циник. Но и без рома скажу: смерти нет.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;
		
		case "Memento_MortimerGrim_12":
			dialog.text = "Всё просто: настоящая жизнь начинается только тогда, когда вы победите смерть. Я был там, за вуалью, и, поверьте, по-настоящему начал жить только сейчас.";
			link.l1 = "Что, простите?";
			link.l1.go = "Memento_MortimerGrim_13";
		break;
		
		case "Memento_MortimerGrim_13":
			dialog.text = "Да неважно, коллега.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
		break;
		
		case "Memento_MortimerGrim_question_1_1":
			dialog.text = "Приятно, что заметили, коллега! Позёрство мне чуждо, но какой из меня пират без устрашающего катласа?";
			link.l1 = "Разве это важно?";
			link.l1.go = "Memento_MortimerGrim_question_1_2";
		break;
		
		case "Memento_MortimerGrim_question_1_2":
			dialog.text = "Ещё бы! Единственный раз, когда я заметно облегчил корабельную казну ради личных целей, был как раз этот клинок. Две тысячи золотых дублонов, коллега! Дьявол, если бы я мог восстать из могилы второй раз, я бы ожил только от одной его цены!\n"+
			"Оружие, впрочем, превосходное. Но, как будто, ему чего-то не хватает...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_1 = true;
		break;
		
		case "Memento_MortimerGrim_question_2_1":
			dialog.text = "Подарок одного человека. Прекрасный собеседник, понимающий смерть как никто другой — и с отличной фантазией, как вы могли заметить.";
			link.l1 = "Выглядит жутко.";
			link.l1.go = "Memento_MortimerGrim_question_2_2";
		break;
		
		case "Memento_MortimerGrim_question_2_2":
			dialog.text = "Memento mori, коллега.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		case "Memento_MortimerGrim_question_3_1":
			dialog.text = "Мой экипаж имеет между собой намного больше общего, чем, например, ваш.. Все они были мною освобождены от петли и цепей, каждый ощутил дыхание смерти. Это чувство роднит людей лучше крови или флага.";
			link.l1 = "Надо думать, вы людей не в тавернах нанимаете?";
			link.l1.go = "Memento_MortimerGrim_question_3_2";
		break;
		
		case "Memento_MortimerGrim_question_3_2":
			dialog.text = "Вы удивитесь, насколько охотно идут в команду бывшие рабы и смертники: поменять трюм работорговца или эшафот на палубу 'Мементо'? У меня на корабле сейчас 178 человек — и каждый из них мне обязан.";
			link.l1 = "Но вам же как-то нужно платить экипажу и содержать корабль. Одного чувства благодарности не хватит.";
			link.l1.go = "Memento_MortimerGrim_question_3_3";
		break;
		
		case "Memento_MortimerGrim_question_3_3":
			dialog.text = "Я успешный пират, коллега. Настоящий hostis humanitatis. Так меня бы назвали истинные враги человечества — работорговцы и коронованные особы. Разница между ними только в названии\n"+
			"К счастью, золота у них немало. Монеты из сундуков торговцев живым товаром я трачу на спасение тех, кого корона приговорила к смерти. Остаток отдаю экипажу — а самому мне ничего не нужно. Зачем мертвецам золото? Скоро они это поймут...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_3 = true;
		break;
		
		// Диалог с Алонсо
		case "Memento_Alonso_phantom_11":
			dialog.text = "Такие вот у нас дела дерьмовые, кэп.";
			link.l1 = "Что это такое?!";
			link.l1.go = "Memento_Alonso_phantom_12";
		break;
		
		case "Memento_Alonso_phantom_12":
			dialog.text = "Одни вы остались. Всех скосила болезнь. Подвели вы нас.";
			link.l1 = "Этого не может быть!";
			link.l1.go = "Memento_Alonso_phantom_13";
		break;
		
		case "Memento_Alonso_phantom_13":
			dialog.text = "Вы привели нас на проклятый корабль.";
			link.l1 = "...";
			link.l1.go = "Memento_Alonso_phantom_14";
		break;
		
		case "Memento_Alonso_phantom_14":
			dialog.text = "Вы обрекли всех на смерть!";
			link.l1 = "Алонсо, что с тобой?!";
			link.l1.go = "Memento_Alonso_phantom_15";
			npchar.model = "skel1";
			npchar.model.animation = "skeleton";
			npchar.sex = "skeleton";
			Characters_RefreshModel(npchar);
			SetMusic("classic_music_retribution_1");
		break;
		
		case "Memento_Alonso_phantom_15":
			dialog.text = "Mortui vivos docent.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_6");
		break;
		
		// Диалог с Гримом
		
		case "Memento_MortimerGrim_phantom_11":
			dialog.text = "Чего остановились, коллега? Передумали? А зачем напали тогда?";
			link.l1 = "Грим? Но ты же мёртв!";
			link.l1.go = "Memento_MortimerGrim_phantom_12";
		break;
		
		case "Memento_MortimerGrim_phantom_12":
			dialog.text = "Ха! Что мертво умереть не может. И потом, что-то ты опережаешь события: абордаж ты может и выиграл, но переживёшь ли… вот сейчас и узнаем!";
			link.l1 = "Тот бой закончился недели назад! Ты мёртв!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_11");
		break;
		
		case "Memento_MortimerGrim_phantom_21":
			dialog.text = "Вот теперь всё. Поздравляю с победой.";
			link.l1 = "Грим?";
			link.l1.go = "Memento_MortimerGrim_phantom_22";
			LAi_UseAtidoteBottle(pchar);
		break;
		
		case "Memento_MortimerGrim_phantom_22":
			dialog.text = "Знаешь, я рад. Искренне рад, что ты меня убил. По-настоящему.";
			link.l1 = "О чём ты говоришь?";
			link.l1.go = "Memento_MortimerGrim_phantom_23";
		break;
		
		case "Memento_MortimerGrim_phantom_23":
			dialog.text = "Я трус, коллега. Обычный, жалкий трус, который испугался смерти - как и тысячи людей до него. Когда команда умерла от чумы... да ещё и по моей вине, я сошёл с ума от страха. Месяц дрейфовал один на корабле мертвецов.";
			link.l1 = "Что случилось на самом деле?";
			link.l1.go = "Memento_MortimerGrim_phantom_24";
		break;
		
		case "Memento_MortimerGrim_phantom_24":
			dialog.text = "Я не прошел испытание смертью. Вместо того чтобы принять её, выжить и сделать какие-то выводы, я стал её бояться ещё больше. И чтобы заглушить этот страх... я стал заставлять других проходить через то, что прошёл сам.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_25";
		break;
		
		case "Memento_MortimerGrim_phantom_25":
			dialog.text = "Спасибо тебе, коллега. За то, что освободил меня от этого... существования. Теперь я точно знаю, что смерти - нет. И я больше не боюсь. Некого винить и порабощать.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_26";
		break;
		
		case "Memento_MortimerGrim_phantom_26":
			dialog.text = "Не разлучайте 'Мементо' с его капитаном. Мортимер… Капитан Мортимер был хорошим человеком. Найдите его на Доминике. А корабль… корабль вас примет.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_27";
		break;
		
		case "Memento_MortimerGrim_phantom_27":
			dialog.text = "Mortui vivos docent, коллега. Мёртвые учат живых. Прощай.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_13");
		break;
		
	}
} 