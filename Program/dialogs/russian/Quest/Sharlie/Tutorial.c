void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold;
	string attrL, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> Шарль на носу корабля, Алонсо подходит с диалогом
		case "StartSailor":
			dialog.text = "Красиво, правда?";
			link.l1 = "Эта красота пытается убить меня уже два месяца. Пока безуспешно.";
			link.l1.go = "StartSailor_1_fencing";
			link.l2 = "Весьма. Иногда море напоминает, насколько человек ничтожен перед природой.";
			link.l2.go = "StartSailor_1_leadership";
			link.l3 = "Я уже уяснил, что в море есть только два состояния: либо скучно, либо страшно.";
			link.l3.go = "StartSailor_1_fortune";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "StartSailor_1_fencing":
			dialog.text = "Ха! Первый раз в море, месье? Когда оно спокойно - каждый может побыть капитаном. Так что ловите момент.";
			link.l1 = "Шарль де Мор. Дворянин, между прочим. Не 'месье', а сударь.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_1_leadership":
			dialog.text = "Ха! Первый раз в море, месье? Когда оно спокойно - каждый может побыть капитаном. Так что ловите момент.";
			link.l1 = "Шарль де Мор. Дворянин, между прочим. Не 'месье', а сударь.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_1_fortune":
			dialog.text = "Ха! Первый раз в море, месье? Когда оно спокойно - каждый может побыть капитаном. Так что ловите момент.";
			link.l1 = "Шарль де Мор. Дворянин, между прочим. Не 'месье', а сударь.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_2":
			dialog.text = "Как скажете, сударь. Так, первый раз в море, сударь де Мор?";
			link.l1 = "Это так очевидно? Да, первый. И я не создан для тесных кают и гнилых сухарей.";
			link.l1.go = "StartSailor_3";
		break;
		
		case "StartSailor_3":
			dialog.text = "Сразу видно, что вы, сударь, - сухопутная крыса.";
			link.l1 = "Попридержи язык! Человеку достойному я бы бросил перчатку и вызвал на суд чести. А деревенщине вроде тебя - просто отрежу уши.";
			link.l1.go = "StartSailor_4";
		break;
		
		case "StartSailor_4":
			dialog.text = "В Париже, может, и так. А здесь за такие слова самому можно отправиться кормить рыб. Не советую махать шпагой направо и налево, сударь - и не заставляйте капитана пожалеть, что дозволил вам разгуливать по палубе с оружием. Последнего буйного он отправил в трюм - на сухари со дна бочки и воду, что даже крысы пить не стали. И знаете что? Тот ещё и доплатил за проезд, когда добрался до берега.";
			link.l1 = "Да что с тебя взять... Ладно, забудем об этом недоразумении. Мне постоянно приходится напоминать себе, что эта посудина - далеко не Лувр.";
			link.l1.go = "StartSailor_5";
		break;
		
		case "StartSailor_5":
			dialog.text = "Э? Лувр? Это ещё что такое?";
			link.l1 = "Ха! Лувр - место для избранных. Балы, приёмы, интриги...";
			link.l1.go = "StartSailor_6";
		break;
		
		case "StartSailor_6":
			dialog.text = "А-а... бордель, значит. У нас тоже такие есть. Не сказать, чтобы для избранных - плати, и всё будет.";
			link.l1 = "Ха! А ты недалёк от истины, матрос.";
			link.l1.go = "StartSailor_7";
		break;
		
		case "StartSailor_7":
			dialog.text = "Меня, кстати, Алонсо зовут. И что же вы забыли на краю света, сударь? Вряд ли вы ради препирательств с простым матросом проделали путь через Атлантику.";
			link.l1 = "Мой отец болен и не может покинуть наше поместье в Гаскони. Мне поручено найти своего... старшего брата. Он отправился сюда по делам, и от него давно нет вестей.";
			link.l1.go = "StartSailor_8";
		break;
		
		case "StartSailor_8":
			dialog.text = "Почему бы просто не послать верного человека, вместо того чтобы страдать от тягот моря самому?";
			link.l1 = "Семья - превыше всего. Я не могу доверить её судьбу первому встречному.";
			link.l1.go = "StartSailor_9_nobilityplus";
			link.l2 = "Я бы и рад - но, по мнению отца, заняться этим должен именно я. Почему - понятия не имею.";
			link.l2.go = "StartSailor_9_nobilityminus";
		break;
		
		case "StartSailor_9_nobilityplus":
			dialog.text = "И как зовут вашего брата?";
			link.l1 = "Мишель де Монпе.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "StartSailor_9_nobilityminus":
			dialog.text = "И как зовут вашего брата?";
			link.l1 = "Мишель де Монпе.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "StartSailor_10":
			dialog.text = "Де Монпе? А вы - де Мор? Как так?";
			link.l1 = "И не смотри на меня так. Я - законнорожденный сын. Просто ношу фамилию матери.";
			link.l1.go = "StartSailor_11";
		break;
		
		case "StartSailor_11":
			dialog.text = "Тут нечего стыдиться. Вы как раз впишетесь - в Новом Свете у каждого второго какая-нибудь история. Я вот, например...";
			link.l1 = "Ничего я не стыжусь! Лучше расскажи мне про Мартинику. Это большой город? Вроде Тулузы?";
			link.l1.go = "StartSailor_12";
		break;
		
		case "StartSailor_12":
			dialog.text = "Город? Ха! Мартиника - это целый остров. Один из крупнейших во владениях Франции на Карибах. Там собирают жгучий кофе, добывают адскую серу и рожают самых прекрасных женщин в мире. Отличная смесь, как по мне.";
			link.l1 = "Кофе и сера меня не интересуют. Но погоди... остров? Как же я найду брата на целом острове?";
			link.l1.go = "StartSailor_13";
		break;
		
		case "StartSailor_13":
			dialog.text = "Не переживайте так. Сен-Пьер - городок небольшой, не Лувр, конечно, но и не джунгли. А вот в бандитском Ле Франсуа, упаси Боже, - приличному человеку и делать нечего.";
			link.l1 = "Если потребуется - отправлюсь и к бандитам. Мишель всегда вытаскивал меня из неприятностей. Теперь мой черёд.";
			link.l1.go = "StartSailor_14";
		break;
		
		case "StartSailor_14":
			dialog.text = "Неплохо сказано... для сухопутной крысы.";
			link.l1 = "Опять ты за своё? Сколько ещё до этой чёртовой Мартиники?";
			link.l1.go = "StartSailor_15";
		break;
		
		case "StartSailor_15":
			dialog.text = "Дней пять.";
			link.l1 = "Пять?!";
			link.l1.go = "StartSailor_16";
		break;
		
		case "StartSailor_16":
			dialog.text = "Это как минимум. А если пираты нападут - можем и вовсе не дойти. Малые Антилы - места опасные, даже если ценного груза на борту и нет.";
			link.l1 = "Кроме пассажиров!";
			link.l1.go = "StartSailor_17";
		break;
		
		case "StartSailor_17":
			dialog.text = "Ха-ха! Не волнуйтесь. В крайнем случае, я лично спрячу вас в трюме - никакой пират не догадается искать гасконского дворянина среди бочек с ромом! Мы же не идиоты, в самом деле - смешивать живого гасконца и ром. Рванёт не хуже пороха, ха-ха!";
			link.l1 = "Ха! Хорошо, что ром закончился ещё месяц назад!";
			link.l1.go = "StartSailor_18";
		break;
		
		case "StartSailor_18":
			dialog.text = "Э... вы такие вещи лучше прилюдно не говорите. Ещё подумают, что вы стали виной нашей беды с ромом.";
			link.l1 = "Ладно, Алонсо, не буду. Всё равно эту дрянь я в жизни в рот не возьму. А что касается твоего гениального плана посадить меня в трюм перед боем - не дождёшься.";
			link.l1.go = "StartSailor_20";
		break;
		
		case "StartSailor_20":
			dialog.text = "Это почему же?";
			link.l1 = "Я - дворянин, шпагу держу уверенно и в трюме отсиживаться не стану.";
			link.l1.go = "StartSailor_21_fencing";
			link.l2 = "Если начнётся дело - буду защищать корабль и сражаться вместе со всеми. А как иначе?";
			link.l2.go = "StartSailor_21_leadership";
			link.l3 = "Я сам за себя могу решать - когда драться, а когда бежать. Посмотрим по ситуации.";
			link.l3.go = "StartSailor_21_fortune";
			locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
		break;
		
		case "StartSailor_21_fencing":
			dialog.text = "Ха. Может, в вас и правда есть что-то. Но берегитесь - Карибы любят сдирать кожу с тех, кто ходит с поднятым носом. Встречи с авангардом пиратов вы не переживёте. Что говорить - вас зарежет первый же оборванец за воротами Сен-Пьера.";
			link.l1 = "Ты меня совсем не знаешь.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_21_leadership":
			dialog.text = "Ха. Может, в вас и правда есть что-то. Но берегитесь - Карибы любят сдирать кожу с тех, кто выходит в них с поднятым носом. Встречи с авангардом пиратов вы не переживёте. Что говорить - вас зарежет первый же оборванец за воротами Сен-Пьера.";
			link.l1 = "Ты меня совсем не знаешь.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_21_fortune":
			dialog.text = "Ха. Может, в вас и правда есть что-то. Но берегитесь - Карибы любят сдирать кожу с тех, кто выходит в них с поднятым носом. Встречи с авангардом пиратов вы не переживёте. Что говорить - вас зарежет первый же оборванец за воротами Сен-Пьера.";
			link.l1 = "Ты меня совсем не знаешь.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_22":
			dialog.text = "Зато я знаю Новый Свет и его обитателей. Если вы не собираетесь чахнуть за конторскими книгами или прислуживать в доме губернатора - придётся учиться всему с нуля.";
			link.l1 = "Хорошо, что я не собираюсь здесь задерживаться.";
			link.l1.go = "StartSailor_23";
		break;
		
		case "StartSailor_23":
			dialog.text = "Это вы так думаете. Обратно в Европу мы пассажиров возим редко. Одни погибают - от лихорадки, петли или пули. Другие остаются - навсегда. Я видел, как хлипкие аристократы становились капитанами, а отъявленные разбойники - уважаемыми плантаторами. А ещё - как блестящие офицеры скатывались до нищих бродяг.";
			link.l1 = "Соблазнительно, чёрт возьми, но я вернусь во Францию. Меня там ждут.";
			link.l1.go = "StartSailor_24";
		break;
		
		case "StartSailor_24":
			dialog.text = "Ах да, точно. Больной отец?";
			link.l1 = "Скажем так... есть некая дама, чей муж очень не хочет видеть меня в Париже. Но пару месяцев - и страсти улягутся.";
			link.l1.go = "StartSailor_25";
		break;
		
		case "StartSailor_25":
			dialog.text = "Ха-ха-ха! Тогда вам и правда сюда дорога. Карибы - рай для тех, кто убегает от ревнивых мужей. А время здесь летит незаметно. Дайте срок - ещё и моряком станете!";
			link.l1 = "Скорее уж капитаном. Простой матрос из меня, боюсь, никакой. Я не создан для работы руками.";
			link.l1.go = "StartSailor_26";
		break;
		
		case "StartSailor_26":
			dialog.text = "Это во Франции люди по праву рождения правят, а на корабле - капитан: король, судья и Бог. И никто не знает, через что ему пришлось пройти, чтобы завоевать капитанскую шляпу. Здесь каждый получает по заслугам. Как говорят у нас на палубе - каждому своё.";
			link.l1 = "Бессмыслица какая-то. Кстати о капитанах - мне надо поговорить с твоим, тем более что он как раз меня искал. Бывай, Алонсо.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_StartKino_6");
		break;
		
		// <-- Шарль на носу корабля, матрос подходит с диалогом
		
		// --> С Алонсо можно в любой момент поговорить
		case "AlonsoWait":
			dialog.text = "Вы что-то спросить хотели?";
			if (PCharDublonsTotal() >= 60 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Alonso"))
			{
				link.l1 = "Я от месье Пиншона.";
				link.l1.go = "AlonsoGold_2";
			}
			link.l2 = "Ничего.";
			link.l2.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_2":
			dialog.text = "Ба! Наш четырёхглазый и вас в дело взял?";
			link.l1 = "Четырёхглазый?";
			link.l1.go = "AlonsoGold_3";
		break;
		
		case "AlonsoGold_3":
			dialog.text = "Очки его видали? То-то же! А вообще, вы не подумайте: команда месье Пиншона уважает. Хороших врачей на корабле всегда ценят. Да и казначей он недурной.";
			link.l1 = "Что за дела у вас ним?";
			link.l1.go = "AlonsoGold_4";
		break;
		
		case "AlonsoGold_4":
			dialog.text = "Э-э-э... Простите, но это дело наше, внутреннее. Да вы не бойтесь, законы корабельные мы не нарушаем.";
			link.l1 = "А законы обычные?";
			link.l1.go = "AlonsoGold_5";
		break;
		
		case "AlonsoGold_5":
			dialog.text = "А до них нам дела нет. И сколько там мне насчитали?";
			if (PCharDublonsTotal() >= 40)
			{
				link.l1 = "40 дублонов.";
				link.l1.go = "AlonsoGold_DatDeneg_3_gold40";
			}
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "50 дублонов.";
				link.l2.go = "AlonsoGold_DatDeneg_3_gold50";
			}
			if (PCharDublonsTotal() >= 60)
			{
				link.l3 = "60 дублонов.";
				link.l3.go = "AlonsoGold_DatDeneg_3_gold60";
			}
			// link.l4 = "Мне нужно всё перепроверить. Вернусь позже.";
			// link.l4.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_DatDeneg_3_gold40":
			dialog.text = "Вот оно, золотишко. Ну, держись, Сен-Пьер! Ха-ха!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(40);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold50":
			dialog.text = "Вот оно, золотишко. Ну, держись, Сен-Пьер! Ха-ха!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold60":
			dialog.text = "Вот оно, золотишко. Ну, держись, Сен-Пьер! Ха-ха!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(60);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoWait_2":
			DialogExit();
			NextDiag.CurrentNode = "AlonsoWait";
		break;
		
		// <-- С Алонсо можно в любой момент поговорить
		
		// --> капитан на корабле, который идёт из Европы
		case "Captain":
			dialog.text = "А, Шарль. Не очень-то торопились. Вы обязаны немедленно явиться, если капитан корабля изъявил желание с вами поговорить. У вас проблемы с подчинением приказам?";
			link.l1 = "Я не привык к приказам, капитан.";
			link.l1.go = "Captain_2_fencing";
			link.l2 = "Прошу прощения, капитан, меня отвлекли.";
			link.l2.go = "Captain_2_leadership";
			link.l3 = "Мне уже доходчиво объяснили, что ваш корабль - ваши правила.";
			link.l3.go = "Captain_2_sailing";
			if (bBettaTestMode)
			{
				link.l9 = "BetaTest (пропустить обучение и начать игру на Мартинике)";
				link.l9.go = "BetaTest_StartGame";
			}
			//NextDiag.TempNode = "Captain";
			pchar.questTemp.SharlieTutorial_CaptainDialog = true;
		break;
		
		case "Captain_2_fencing":
			dialog.text = "Я не позволю ставить под сомнение мой авторитет. Вы даже не представляете, как часто с пассажирами случается что-то нехорошее в море. Вам невероятно повезло, что я заинтересован в том, чтобы доставить вас в целости в Сен-Пьер.";
			link.l1 = "Вы о чём сейчас?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "Captain_2_leadership":
			dialog.text = "Извинения принимаются. Ловите момент. Вряд ли вам ещё скоро доведётся насладиться таким закатом.";
			link.l1 = "Вы о чём сейчас?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "Captain_2_sailing":
			dialog.text = "Хорошо, что хоть чему-то научились за это плавание. Власть капитана - абсолютна, и иногда она даже распространяется и на суше, далеко от корабля.";
			link.l1 = "Вы о чём сейчас?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		case "Captain_3":
			dialog.text = "Капитан. Потрудитесь обращаться ко мне согласно морскому уставу.";
			link.l1 = "Вы о чём сейчас, капитан?";
			link.l1.go = "Captain_4";
		break;
		
		case "Captain_4":
			dialog.text = "Я хотел вам сказать, что мы спустили паруса и легли в дрейф. К сожалению, ваше прибытие на Мартинику задержится на пару дней.";
			link.l1 = "Но почему, капитан?";
			link.l1.go = "Captain_5";
		break;
		
		case "Captain_5":
			dialog.text = "Потому что я так решил.";
			link.l1 = "Это как-то связано с нашей вчерашней встречей с торговым караваном, направляющимся в этот... в как его...";
			link.l1.go = "Captain_6";
		break;
		
		case "Captain_6":
			dialog.text = "Капстервиль. Вот что, Шарль: у меня к вам будет серьёзный разговор. Приглашаю вас на ужин в каюту. Сейчас отобьют склянки, и мы сможем провести время как культурные люди — допивая последнюю бутылку вина на корабле.";
			link.l1 = "Благодарю за приглашение. Почту за честь, капитан.";
			link.l1.go = "Captain_7";
		break;
		
		case "Captain_7":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Дайте мне знать, как будете готовы. Время у нас ещё есть, так что вы вольны погулять по кораблю — при условии, что не будете отвлекать моих людей от работы.";
				npchar.SharlieTutorial_question_0 = true;
				// теперь можно пострелять из пушки
				sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
				SetLocatorEvent(sld.id, "event3", "SharlieTutorial_cannon_1");
			}
			else dialog.text = "Ещё вопросы?";
			link.l1 = "(Завершить дела) Я готов, капитан. С вами — выпью даже бургундское!";
			link.l1.go = "Captain_8";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Что это вы так в трубу рассматриваете... капитан?";
				link.l2.go = "Captain_7_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Капитан, я имел удовольствие пообщаться с неким Алонсо. Какая у него должность на корабле?";
				link.l3.go = "Captain_7_question_2_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
			{
				link.l4 = "Капитан, расскажите про ваш корабль. Пинас, кажется?";
				link.l4.go = "Captain_7_question_3_1";
			}
			link.l5 = "До встречи, капитан.";
			link.l5.go = "Captain_7_exit";
		break;
		
		case "Captain_7_exit":
			DialogExit();
			NextDiag.CurrentNode = "Captain_7";
			if (!CheckAttribute(npchar, "SharlieTutorial_Zapis"))
			{
				npchar.SharlieTutorial_Zapis = true;
				AddQuestRecord("SharlieTutorial", "0.1");
			}
		break;
		
		case "Captain_7_question_1_1":
			dialog.text = "Ничего конкретного, просто изучаю горизонт. Корабль в дрейфе — так что мы лёгкая добыча.";
			link.l1 = "Ищете пиратов?";
			link.l1.go = "Captain_7_question_1_2";
		break;
		
		case "Captain_7_question_1_2":
			dialog.text = "Или испанцев. Мы идём под французским флагом и без эскорта, а Малые Антилы — это настоящий проходной двор и вотчина Жака Барбазона.";
			link.l1 = "Это кто? Губернатор?";
			link.l1.go = "Captain_7_question_1_3";
		break;
		
		case "Captain_7_question_1_3":
			dialog.text = "Хуже — один из пиратских баронов. Эти висельники создали некое подобие организации и называют себя Береговым Братством. Поделили Карибы на шесть кусков и поставили на каждый по барону, чтобы не грызться между собой.";
			link.l1 = "Почему же власти ничего не предпринимают?";
			link.l1.go = "Captain_7_question_1_4";
		break;
		
		case "Captain_7_question_1_4":
			dialog.text = "Вы наивны, Шарль. Пиратство существует только потому, что местные власти позволяют им чинить и снабжать корабли в избранных портах в обмен на большую часть добычи. Мне неприятно это признавать, но единственные, кто хоть что-то делает с этой чёрной чумой — это испанцы. Если бы не они, пришлось бы не только обвешивать корабль дорогими пушками, но ещё и эскорт нанимать.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_1 = true;
		break;
		
		case "Captain_7_question_2_1":
			dialog.text = "Старший матрос. Я мало что про него знаю, но могу сказать точно: если у каждого человека можно найти скелет в шкафу, то у Алонсо там — целое кладбище.";
			link.l1 = "Звучит так, как будто вы ему не доверяете.";
			link.l1.go = "Captain_7_question_2_2";
		break;
		
		case "Captain_7_question_2_2":
			dialog.text = "Отнюдь. Думаете, легко найти таких опытных людей в команду? Требуется как минимум год и отличный боцман, чтобы нанятый сброд из таверн начал хоть немного напоминать экипаж. К тому же, Алонсо — ещё и голос команды. Капитан не обременяет себя общением с низшими чинами, но глупо и смертельно опасно не учитывать, что у простых матросов тоже есть свои интересы. Вот их он, при случае, и отстаивает.";
			link.l1 = "И что произойдёт, если команда недовольна?";
			link.l1.go = "Captain_7_question_2_3";
		break;
		
		case "Captain_7_question_2_3":
			dialog.text = "Меня повесят, а вас — просто зарежут. Да не дрожите так. До тех пор, пока команда получает жалование, ром, провиант и лечение — контракт между капитаном и командой соблюдён. Я не рискую зря их жизнями, не наказываю из прихоти, делюсь добычей и иногда балую дармовой выпивкой и другими услугами на берегу. Таким образом хрупкое равновесие соблюдается, а корабль всегда приходит в точку назначения.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		case "Captain_7_question_3_1":
			dialog.text = "Вы задели меня за живое, Шарль! О своей красавице я могу разглагольствовать вечно. Третий ранг, двадцать пушек, прекрасная скорость — не смотрите, что 'торговец'!";
			link.l1 = "Про пушки и скорость я понял. А 'ранг'? 'Торговец'?";
			link.l1.go = "Captain_7_question_3_2";
		break;
		
		case "Captain_7_question_3_2":
			dialog.text = "Ранги — это условное деление кораблей по количеству пушек. Седьмой ранг недалеко ушёл от лодки, а первый — от форта. Но только не вздумайте повторять эту мысль в Европе, особенно в присутствии морских офицеров.";
			link.l1 = "Почему? Тут кроется какая-то моряцкая шутка?";
			link.l1.go = "Captain_7_question_3_3";
		break;
		
		case "Captain_7_question_3_3":
			dialog.text = "Вас воспримут как полного профана и поднимут на смех. Откровенно говоря, на любом серьёзном флоте разделение на ранги работает совсем не так и относится только к военным кораблям. Но у нас на Карибах, как обычно, всё по-своему.";
			link.l1 = "А что вы имели в виду, называя свой корабль 'торговцем'?";
			link.l1.go = "Captain_7_question_3_4";
		break;
		
		case "Captain_7_question_3_4":
			dialog.text = "Ещё одна условность. Военные корабли — крепче и лучше стреляют, рейдеры — грабят и удирают. Торговые — могут вместить в себя много полезного груза, команды или пушек, но приходится выбирать что-то одно в ущерб остальному, иначе скорость станет просто смехотворной. Есть ещё и многофункциональные корабли, но про них и сказать особо нечего, кроме того, что они подстраиваются под нужды своего владельца.";
			link.l1 = "Вы прямо оживились, капитан.";
			link.l1.go = "Captain_7_question_3_5";
		break;
		
		case "Captain_7_question_3_5":
			dialog.text = "Я люблю свой корабль, Шарль.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_3 = true;
		break;
			
		case "Captain_8":
			if (IsEquipCharacterByItem(pchar, "hat3"))
			{
				dialog.text = "Ну тогда вам повезло — только бургундское у меня и осталось... Постойте-ка, Шарль. Откуда на вас моя старая шляпа?!\nПодождите. Эй, на марсах! Что у вас там?";
				ChangeCharacterComplexReputation(pchar, "nobility", -1);
			}
			else dialog.text = "Ну тогда вам повезло — только бургундское у меня и осталось\nПодождите. Эй, на марсах! Что у вас там?";
			link.l1 = "...";
			link.l1.go = "Captain_9";
		break;	
		
		case "Captain_9":
			DialogExit();
			DelLandQuestMark(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga");
		break;
		
		case "BetaTest_StartGame":	// досрочный выход на сушу
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		
		// <-- капитан на корабле, который идёт из Европы
		
		// --> Диалог с охранником каюты
		case "OhrannikCabin":
			dialog.text = "Простите, сударь де Мор, но вам туда нельзя.";
			link.l1 = "В каюту капитана я вхож. Мог бы уже и запомнить.";
			link.l1.go = "OhrannikCabin_1";
			link.l2 = "Как жаль, что мой коварный план потерпел крах. Бывай, матрос.";
			link.l2.go = "exit";
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15) NextDiag.TempNode = "OhrannikCabin";
			else NextDiag.TempNode = "OhrannikCabin_again";
			if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikStay"))
			{
				LAi_SetStayType(npchar);
				npchar.SharlieTutorial_OhrannikStay = true;
				DeleteQuestCondition("SharlieTutorial_OhrannikStopaet");
			}
		break;
		
		case "OhrannikCabin_1":
			dialog.text = "Простите, сударь, но обстоятельства изменились.";
			link.l1 = "А что, собственно, случилось?";
			link.l1.go = "OhrannikCabin_2";
		break;
		
		case "OhrannikCabin_2":
			dialog.text = "До конца рейса осталось всего ничего, и капитану не хотелось бы, чтобы кто-нибудь обчистил его добро, чтобы потом, по прибытии, безнаказанно свинтить к бандитам в Ле Франсуа.";
			link.l1 = "Вряд ли капитан имел в виду меня, когда отдавал такой приказ.";
			link.l1.go = "OhrannikCabin_3";
		break;
		
		case "OhrannikCabin_3":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15)
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Ну... ваша правда. Да и трапезничали вы в капитанской каюте не раз уже. Проходите, сударь де Мор.";
					link.l1 = "То-то же!";
					link.l1.go = "OhrannikCabin_4";
					notification("Проверка пройдена", SKILL_Leadership);
				}
				else
				{
					dialog.text = "Инси... инсину-что? Я ничего такого не имел в виду, сударь де Мор!";
					link.l1 = "Значит, ты обязан меня пропустить.";
					link.l1.go = "OhrannikCabin_3_1";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Сударь, вы же сами понимаете, что капитанская каюта — это не проходной двор. И с приказами у нас строго.";
					link.l1 = "Проклятье, поскорее бы уже на сушу. Это просто унизительно!";
					npchar.SharlieTutorial_OhrannikFail = true;
				}
				else
				{
					dialog.text = "Сударь, мы уже обсуждали это. Я не могу вас пропустить.";
					link.l1 = "Вот ты упёртый, матрос. Бывай.";
				}
				link.l1.go = "exit";
				NextDiag.TempNode = "OhrannikCabin_again";
				notification("Недостаточно развит навык (15)", SKILL_Leadership);
			}
		break;
		
		case "OhrannikCabin_3_1":
			dialog.text = "Э-эх. Ну ладно, думаю, большой беды от того не будет.";
			link.l1 = "То-то же!";
			link.l1.go = "OhrannikCabin_4";
			notification("Проверка пройдена", SKILL_Leadership);
		break;
		
		case "OhrannikCabin_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			LocatorReloadEnterDisable("Quest_Ship_deck_Medium_trade", "reload_cabin", false);
		break;
		
		case "OhrannikCabin_again":
			dialog.text = "Что-то ещё, сударь? Пропустить я вас не могу — капитан опасается за своё добро.";
			link.l1 = "Ты что же, матрос, намекаешь на воровство? Осторожнее с языком. Инсинуация чистой воды!";
			if (CheckAttribute(npchar, "SharlieTutorial_OhrannikFail")) link.l1.go = "OhrannikCabin_3";
			else link.l1.go = "OhrannikCabin_1";
			link.l2 = "Ничего, матрос.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OhrannikCabin_again";
		break;
		
		// <-- Диалог с охранником каюты
		
		// --> матрос ругается на ГГ, который активировал брашпиль
		case "SailorWithWindlass_1":
			dialog.text = "Эй, благородный болван! Ты что, дьявола в брашпиль засунул?!\nНожкой своей царственной предохранитель сорвал! Ты нас всех на дно собрался спустить, а?!\nСделай одолжение, и не трогай ничего, если только это не французский насморк!";
			link.l1 = "А что это такое, собственно?";
			link.l1.go = "SailorWithWindlass_2";
		break;
		
		case "SailorWithWindlass_2":
			dialog.text = "Это брашпиль, дубина. Якорь поднимает. А если его не стопорить — он корабль порвёт к дьяволу, или кого-нибудь намотает на верёвку, как селёдку на бочку!";
			link.l1 = "Ха... А если его в другую сторону — он якорь опускает, да?";
			link.l1.go = "SailorWithWindlass_3";
		break;
		
		case "SailorWithWindlass_3":
			dialog.text = "Нет, умник, тогда он время назад мотает. Только тебе не повезло — ты уже родился!";
			link.l1 = "Ну, никто не пострадал — так ведь? Всё-таки удивительно сложная штука — корабль. Буду осторожнее.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_windlass_8");
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		// <-- матрос ругается на ГГ, который активировал брашпиль
		
		// --> матрос ругается на ГГ, который активировал пушку
		case "SailorWithCannon_1":
			dialog.text = "Вы рассматриваете длинный ствол орудия с таким же восхищением, как давеча глядели на закат.";
			link.l1 = "Ты, смотрю, любишь понаблюдать за мной, Алонсо. Лучше расскажи про это чудо военной мысли.";
			link.l1.go = "SailorWithCannon_2";
		break;
		
		case "SailorWithCannon_2":
			dialog.text = " Это — шестнадцатифунтовая пушка. Не на каждом военном корабле можно найти такую.";
			link.l1 = "И что, легко из неё попасть?";
			link.l1.go = "SailorWithCannon_3";
		break;
		
		case "SailorWithCannon_3":
			dialog.text = "В упор разнесём кого угодно. Сотня ярдов — и мы в деле. Дальше — в основном шум да пламя, но и на том спасибо.";
			link.l1 = "Сотня ярдов — и неприятель сделает то же самое.";
			link.l1.go = "SailorWithCannon_4";
		break;
		
		case "SailorWithCannon_4":
			dialog.text = "Это верно. Но тут уж у кого команда сработаннее и пушкари круче. Жаль, наш канонир сейчас дрыхнет — уж он бы вам всю науку рассказал, а потом и в пушку вас самолично зарядил, ха-ха!";
			link.l1 = "Канонир — это же офицер?";
			link.l1.go = "SailorWithCannon_5";
		break;
		
		case "SailorWithCannon_5":
			dialog.text = "Как правило. Без мало-мальски знающего канонира лучше в бой не ввязываться — проще сразу пушки за борт и дёру\nТорговые капитаны вообще редко с собой берут что-то серьёзнее шестифунтовок — уповают либо на эскорт, либо на фортуну\nТак оно вроде и правильно: без тяжёлых пушек и боеприпасов и корабль летит по волнам, и в трюм всякого добра на продажу можно больше напихать\nВот не разорился бы наш капитан на этих красавиц — глядишь, и ром бы не успел закончиться. Э-эх!";
			link.l1 = "А капитан лично не руководит стрельбой?";
			link.l1.go = "SailorWithCannon_6";
		break;
		
		case "SailorWithCannon_6":
			dialog.text = "С хорошим канониром и слаженной командой ему и не надо. Но я вам так скажу: если капитан сам берётся за прицеливание, а не просто рычит с квартердека команду “Огонь!” — дырок в бортах вражеских кораблей становится больше.";
			link.l1 = "А можно пальнуть?";
			link.l1.go = "SailorWithCannon_7";
			link.l2 = "Спасибо за увлекательную лекцию, Алонсо. Ты — настоящий кладезь морской мудрости.";
			link.l2.go = "SailorWithCannon_7_exit";
		break;
		
		case "SailorWithCannon_7_exit":
			dialog.text = "А то! Но всё же не тревожьте пушку и не нервируйте команду.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_11");
		break;
		
		case "SailorWithCannon_7":
			dialog.text = "Пальнуть — вряд ли. А произвести выстрел — надо капитана спрашивать. Сейчас спрошу!";
			link.l1 = "Не надо!";
			link.l1.go = "SailorWithCannon_8";
		break;
		
		case "SailorWithCannon_8":
			dialog.text = "Кэ-э-эп!";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieTutorial_cannon_3");
		break;
		
		case "CaptainWithCannon_1":
			dialog.text = "Что у вас тут, Алонсо?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_2";
		break;
		
		case "CaptainWithCannon_2":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_3", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_3":
			dialog.text = "Сударь Шарль предлагает выстрелить из орудия — исключительно в учебных целях.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_4";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;
		
		case "CaptainWithCannon_4":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_5", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_5":
			dialog.text = "Я думал, ты отвечаешь за интересы команды, Алонсо. А ты предлагаешь разбудить следующую вахту и переполошить всех остальных самым варварским способом?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_6";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;
		
		case "CaptainWithCannon_6":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_7", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_7":
			dialog.text = "Думается, стоит погонять им кровь и привести в готовность. Не нравится мне, что мы стоим в дрейфе у всех на виду. Кабы чего не вышло.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_8";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;
		
		case "CaptainWithCannon_8":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_9", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_9":
			dialog.text = "Не каркай!.. Ладно. Один выстрел. Холостым.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_10";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;
		
		case "CaptainWithCannon_10":
			dialog.text = "Развлекайтесь, Шарль. Поднимем команду... за ваш счёт, ха-ха!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_5");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
		break;
		
		// <-- матрос ругается на ГГ, который активировал пушку
		
		// --> Диалог с матросом, который хочет рома
		case "SailorWantRum":
			dialog.text = "Уделите пару минут, сударь?";
			link.l1 = "Говори, матрос.";
			link.l1.go = "SailorWantRum_1";
		break;
		
		case "SailorWantRum_1":
			dialog.text = "Рад знакомству, сударь. Меня зовут Анри. Хотите немного заработать?";
			link.l1 = "Немного — это сколько?";
			link.l1.go = "SailorWantRum_2";
		break;
		
		case "SailorWantRum_2":
			dialog.text = "Пять сотен песо.";
			link.l1 = "Сколько?! И что ты хочешь, чтобы я сделал за такие деньги? Надеюсь, не подстроить мятеж?";
			link.l1.go = "SailorWantRum_3";
		break;
		
		case "SailorWantRum_3":
			dialog.text = "Господи помилуй, сударь! Зачем же так об этом кричать?";
			link.l1 = "Это немалые деньги, матрос. Даже в Париже на них можно неплохо пожить.";
			link.l1.go = "SailorWantRum_4";
		break;
		
		case "SailorWantRum_4":
			dialog.text = "Э-эх, не буду я пользоваться вашим незнанием и скажу как есть: на Карибах пятьсот песо — не деньги. Капитаны и торговцы привозят столько добра, что цены взвинчены на всё, что имеет хоть какую-нибудь практическую ценность. Доходит до смешного: иногда редкий клинок стоит как небольшой корабль.";
			link.l1 = "Безумие какое-то.";
			link.l1.go = "SailorWantRum_5";
		break;
		
		case "SailorWantRum_5":
			dialog.text = "Что тут сказать? Мы все ждём, когда всё немного устаканится и цены придут в норму. Так вам интересно заработать пятьсот песо?";
			link.l1 = "Сначала я хочу послушать о сути работы.";
			link.l1.go = "SailorWantRum_6";
		break;
		
		case "SailorWantRum_6":
			dialog.text = "Вы наверняка в курсе про печальную ситуацию с ромом на корабле. И всё же я уверен, что если хорошо поискать, то можно найти ещё несколько бутылок. Ром в бутылках — это не пойло из бочки. Отличный вкус, спасает от отравлений, укрепляет руку и здоровье — в общем, нужная штука. Особенно в конце плавания, когда от горизонта с ума уже сходишь.";
			link.l1 = "И что ты будешь с ним делать? И почему сам не поищешь?";
			link.l1.go = "SailorWantRum_7";
		break;
		
		case "SailorWantRum_7":
			dialog.text = "Да когда мне? Команды у нас недобор, так что пашем за троих. А ром я перепродам — уж найду кому.";
			link.l1 = "Ну, откровенность в людях я уважаю.";
			link.l1.go = "SailorWantRum_8";
		break;
		
		case "SailorWantRum_8":
			dialog.text = "Так что, берётесь? Мне бы три бутылки.";
			link.l1 = "Постараюсь, но ничего не обещаю.";
			link.l1.go = "SailorWantRum_9";
			link.l2 = "Пожалуй, откажусь. Мне такого рода работа не к лицу.";
			link.l2.go = "SailorWantRum_10";
		break;
		
		case "SailorWantRum_9":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRum");
		break;
		
		case "SailorWantRum_10":
			dialog.text = "Жаль, но обиду держать не стану. Хорошего вам вечера, сударь.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
			npchar.SailorWantRum_Done = true;
			DelLandQuestMark(npchar);
		break;
		
		case "SailorWantRum_PrinestiRum": // ждёт ром
			dialog.text = "Да, сударь де Мор?";
			if (GetCharacterItem(pchar, "potionrum") >= 3 && !CheckAttribute(npchar, "questTemp.SailorWantRum_Done"))
			{
				link.l1 = "Вот твои три бутылки рома.";
				link.l1.go = "SailorWantRum_PrinestiRum_2";
			}
			if (PCharDublonsTotal() >= 42 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Anri"))
			{
				link.l2 = "Анри, у меня для тебя кое-что есть от месье Пиншона.";
				link.l2.go = "RumGold_2";
			}
			link.l3 = "Ничего.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "RumGold_2":
			dialog.text = "Всегда рад быть ему полезным! Сколько мне в этот раз положено?";
			if (PCharDublonsTotal() >= 28)
			{
				link.l1 = "28 дублонов.";
				link.l1.go = "RumGold_DatDeneg_gold28";
			}
			if (PCharDublonsTotal() >= 35)
			{
				link.l2 = "35 дублонов.";
				link.l2.go = "RumGold_DatDeneg_gold35";
			}
			if (PCharDublonsTotal() >= 42)
			{
				link.l3 = "42 дублонов.";
				link.l3.go = "RumGold_DatDeneg_gold42";
			}
			// link.l4 = "Мне нужно всё перепроверить. Вернусь позже.";
			// link.l4.go = "RumGold_DatDeneg_3";
		break;
		
		case "RumGold_DatDeneg_gold28":
			dialog.text = "Благодарю, сударь де Мор. Передавайте мой поклон господину казначею.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(28);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_gold35":
			dialog.text = "Благодарю, сударь де Мор. Передавайте мой поклон господину казначею.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(35);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_gold42":
			dialog.text = "Благодарю, сударь де Мор. Передавайте мой поклон господину казначею.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "SailorWantRum_PrinestiRum_2":
			dialog.text = "Спасибо, сударь де Мор. Ловко вы это провернули!";
			link.l1 = "Надеюсь, свои деньги я получу так же ловко.";
			link.l1.go = "SailorWantRum_PrinestiRum_3";
			RemoveItems(pchar, "potionrum", 3);
			npchar.SailorWantRum_Done = true;
		break;
		
		case "SailorWantRum_PrinestiRum_3":
			dialog.text = "Может, примете оплату не деньгами?";
			link.l1 = "Не такой уж ты и честный малый, я погляжу.";
			link.l1.go = "SailorWantRum_PrinestiRum_4";
		break;
		
		case "SailorWantRum_PrinestiRum_4":
			dialog.text = "Да нет же! Выберете деньги — получите деньги! Просто я, так-то, и знаниями поделиться могу.";
			link.l1 = "Какого рода знаниями?";
			link.l1.go = "SailorWantRum_PrinestiRum_5";
		break;
		
		case "SailorWantRum_PrinestiRum_5":
			dialog.text = "Я могу рассказать вам немало полезного про морское дело. В ваших учёных книжках такого не напишут.";
			link.l1 = "Ну давай, проведи самый дорогой урок в моей жизни.";
			link.l1.go = "SailorWantRum_PrinestiRum_6";
			link.l2 = "Пятьсот советов не заменят пятьсот монет. Возьму деньги.";
			link.l2.go = "SailorWantRum_PrinestiRum_money";
		break;
		
		case "SailorWantRum_PrinestiRum_money":
			dialog.text = "Пожалуйста, сударь де Мор. И спасибо вам ещё раз!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		case "SailorWantRum_PrinestiRum_6":
			dialog.text = "Я очень надеюсь, сударь Шарль, что мой урок действительно останется таковым. Вы знаете, что такое навигация?";
			link.l1 = "Ты удивишься, но знаю. И даже читать умею. Навигация — это определение положения в пространстве и расчёт пути, например, корабля.";
			link.l1.go = "SailorWantRum_PrinestiRum_7";
		break;
		
		case "SailorWantRum_PrinestiRum_7":
			dialog.text = "А-а-а. Вы про звёзды и карты. Нет, в таком я не разбираюсь. Это к штурману надо, или к капитану. А навигацией у нас принято называть способность управлять и командовать кораблём.";
			link.l1 = "У кого это — 'у нас'?";
			link.l1.go = "SailorWantRum_PrinestiRum_8";
		break;
		
		case "SailorWantRum_PrinestiRum_8":
			dialog.text = "На Карибах. Так уж повелось, не спрашивайте почему. Так вот: чем лучше вы разбираетесь в навигации, тем больше скорости и манёвренности вы можете выжать из корабля. Ну и команда быстрее с парусами управляется. Но это не самое важное.";
			link.l1 = "Смотрю, умеешь ты интригу держать.";
			link.l1.go = "SailorWantRum_PrinestiRum_9";
		break;
		
		case "SailorWantRum_PrinestiRum_9":
			dialog.text = "Чем лучше у вас с навигацией, тем большего размера корабль вы сможете взять под командование! Более того, если корабль вы взяли себе не по навыку, то от непосильной нагрузки потеряете внимание, силы и даже здоровье!";
			link.l1 = "Звучит опасно. Даже странно, как я раньше жил без этого.";
			link.l1.go = "SailorWantRum_PrinestiRum_10";
		break;
		
		case "SailorWantRum_PrinestiRum_10":
			dialog.text = "К счастью, не обязательно быть докой во всём. Всегда можно нанять хорошего штурмана, и он закроет для вас вопрос навигации. Только убедитесь, что этот человек получает зарплату вовремя и вас поддерживает. Остаться без штурмана на корабле, на который вам не хватает знания навигации — удовольствие сомнительное.";
			link.l1 = "Спасибо за лекцию, Анри. Не уверен, что мне это пригодится, но лишних знаний, наверное, не бывает.";
			link.l1.go = "SailorWantRum_PrinestiRum_11";
			AddCharacterSkillPoints(pchar, "Sailing", 3);
		break;
		
		case "SailorWantRum_PrinestiRum_11":
			dialog.text = "Пожалуйста, сударь де Мор. И спасибо вам ещё раз!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		// <-- Диалог с матросом, который хочет рома
		
		// --> Диалог со старым матросом в трюме
		case "OldSailor":
			dialog.text = "(поёт) C’est la mère Michel qui a perdu son chat... Qui crie par la fenêtre à qui le lui rendra...";
			link.l1 = "Ты что тут делаешь, матрос?";
			link.l1.go = "OldSailor_1";
			NextDiag.TempNode = "OldSailor";
		break;
		
		case "OldSailor_1":
			dialog.text = "Я, выходит, как мадам Мишель — кошку ищу. Только не кричу — она не любит, когда на неё кричат.";
			link.l1 = "Я видел её утром — она опять драла мне сапоги.";
			link.l1.go = "OldSailor_2";
		break;
		
		case "OldSailor_2":
			dialog.text = "Это ещё ничего. А вот сапогам капитана уже не так повезло. Любите кошек?";
			link.l1 = "Конечно люблю.";
			link.l1.go = "OldSailor_3";
			link.l2 = "Не особо.";
			link.l2.go = "OldSailor_4";
		break;
		
		case "OldSailor_3":
			dialog.text = "Оно и понятно. Иначе как этих чертовых крыс давить?";
			link.l1 = "Но вы же не можете вечно полагаться на кошек? Существа они весьма своевольные.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "OldSailor_4":
			dialog.text = "А зря. Кошек на кораблях любят и ценят. Иначе как этих чертовых крыс давить?";
			link.l1 = "Но вы же не можете вечно полагаться на кошек? Существа они весьма своевольные.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "OldSailor_5":
			dialog.text = "Это верно. Поэтому и приходится полагаться на мышьяк. Только попробуй его найди на Карибах. Вот и теряем товар — крысы гадят в ром, портят сухари и грызут всё остальное\nА наш казначей говорит: «Относитесь проще, это как налог на торговлю»\nНо мы-то знаем: ленится он, вот и всё. Не будь нашей дорогой Шанталь — капитан давно бы уже посадил его жить в трюме и лично крыс ловить, ха-ха!";
			link.l1 = "Удачи тебе с кошкой. Мне пора.";
			link.l1.go = "OldSailor_6";
		break;
		
		case "OldSailor_6":
			dialog.text = "Подождите, сударь. Обычно благородных пассажиров простой матрос разве что на палубе видит, а вы — в самый трюм забрались!";
			link.l1 = "Любопытство кошку сгубило, ха-ха!";
			link.l1.go = "OldSailor_7";
		break;
		
		case "OldSailor_7":
			dialog.text = "Интересуетесь морским делом?";
			link.l1 = "Кажется, каждый член экипажа поставил себе цель — отправить меня на берег настоящим моряком.";
			link.l1.go = "OldSailor_8";
		break;
		
		case "OldSailor_8":
			dialog.text = "Ничего удивительного. Пусть многим из нас море принесло одно лишь горе, но мы свою работу любим. И моряку всегда приятно, когда кто-то новенький проявляет живой интерес.";
			link.l1 = "...";
			link.l1.go = "OldSailor_9";
		break;
		
		case "OldSailor_9":
			dialog.text = "А ну-ка, скажите: какой самый важный навык для капитана?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "Навигация. От неё зависит размер корабля, которым он может командовать.";
				link.l1.go = "OldSailor_10";
				notification("Проверка пройдена", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Врать не буду, не знаю.";
				link.l1.go = "OldSailor_9_1";
				notification("Недостаточно развит навык (6)", SKILL_Sailing);
			}
		break;
		
		case "OldSailor_9_1":
			dialog.text = "Не расстраивайтесь, сударь. Поговорите с командой, погуляйте по кораблю. Если ответите — расскажу вам кое-что презанятное. Как своему.";
			link.l1 = "Буду иметь в виду. Бывай!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OldSailor_again";
		break;
		
		case "OldSailor_10":
			dialog.text = "Верно! А вот вам ещё вопросец с подвохом: что лучше — косые или прямые паруса?";
			link.l1 = "Не берусь судить, но чувствую тут подвох. Думаю, от всего есть своя польза.";
			link.l1.go = "OldSailor_11";
		break;
		
		case "OldSailor_11":
			dialog.text = "И снова верно! Прямые паруса — сила, если ветер в спину. А вот косопарусник лавирует и догоняет даже поперечный ветер. Отрадно видеть, что вы время даром не теряли, сударь.";
			link.l1 = "Не уверен, что эти знания мне когда-нибудь пригодятся... Разве что произведу впечатление перед дамами высшего света, сойдя за настоящего моряка, ха-ха!";
			link.l1.go = "OldSailor_12";
		break;
		
		case "OldSailor_12":
			dialog.text = "Ох, не знаю, сударь Шарль. Дворянин вы, может, и есть — но с нами по-человечески. А мы это ценим. Задумал что-то наш капитан. Пробежала между вами чёрная кошка.";
			link.l1 = "Глупости какие. Ты о чём, матрос?";
			link.l1.go = "OldSailor_13";
		break;
		
		case "OldSailor_13":
			dialog.text = "Да вот судачат, что не просто так он письмо в Капстервиль на днях с попутным судном отправил\nИ не зря в дрейф лёг — прямо перед концом рейса, когда народ уже воет: хоть бы на сушу поскорее.";
			link.l1 = "До слухов мне дела нет. И зачем? Я могу просто его спросить. Он не откажет дворянину в честном ответе.";
			link.l1.go = "OldSailor_14";
		break;
		
		case "OldSailor_14":
			dialog.text = "Вы его не знаете, сударь Шарль. Откажет — и ещё как. Да и зол он сейчас — ключ потерял.";
			link.l1 = "Ключ?";
			link.l1.go = "OldSailor_15";
		break;
		
		case "OldSailor_15":
			dialog.text = "От своего сундука в каюте. Думаю, найти его будет несложно. Где-то валяется, не иначе.";
			link.l1 = "Найти ключ? Мне?";
			link.l1.go = "OldSailor_16";
		break;
		
		case "OldSailor_16":
			dialog.text = "Это уж как сами решите\nКстати, сударь Шарль, у вас рому случайно не осталось? Не всё же вы Анри-то отдали, ха-ха!";
			if (GetCharacterItem(pchar, "potionrum") >= 1)
			{
				link.l1 = "Есть. Забирай.";
				link.l1.go = "OldSailor_17";
			}
			link.l2 = "К сожалению, нет. Чудо, что я те три бутылки нашёл.";
			link.l2.go = "OldSailor_16_1";
		break;
		
		case "OldSailor_16_1":
			dialog.text = "И правда. Удачи вам, сударь Шарль. Пойду эту полосатую негодницу дальше искать.";
			link.l1 = "И тебе удачи, матрос.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\Animals\Cat_01.wav");
		break;
		
		case "OldSailor_17":
			dialog.text = "Ох, удружили! Достойно вы с командой обошлись, сударь Шарль. Вот вам небольшой подарочек — на удачу!";
			link.l1 = "Камень с дыркой? Как мило.";
			link.l1.go = "OldSailor_18";
			GiveItem2Character(PChar, "talisman11");
			TakeItemFromCharacter(pchar, "potionrum");
		break;
		
		case "OldSailor_18":
			dialog.text = "Смейтесь, смейтесь. А я вам так скажу: в море от талисманов — хуже не будет.";
			link.l1 = "Суеверный вы народ, моряки. Удачи тебе, матрос.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\Animals\Cat_01.wav");
		break;
		
		case "OldSailor_again":
			dialog.text = "Уже нашли ответ? Какой самый важный навык для капитана?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "Навигация. От неё зависит размер корабля, которым он может командовать.";
				link.l1.go = "OldSailor_10";
				notification("Проверка пройдена", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Пока нет.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OldSailor_again";
				notification("Недостаточно развит навык (6)", SKILL_Sailing);
			}
		break;
		
		// <-- Диалог со старым матросом в трюме
		
		// --> Диалог с матросом, которому нужен ящик с ядрами (Поль)
		case "SailorNeedBox":
			dialog.text = "Эй, сынок!";
			link.l1 = "На моего отца ты не похож. И слава Богу.";
			link.l1.go = "SailorNeedBox_1";
		break;
		
		case "SailorNeedBox_1":
			dialog.text = "Ха! А я бы порадовался такому рослому и благородному сыну. Да родить способен только такую соль земли, как сам.";
			link.l1 = "Ладно, комплименты принимаю. Что случилось?";
			link.l1.go = "SailorNeedBox_2";
		break;
		
		case "SailorNeedBox_2":
			dialog.text = "Простой человеческой помощи не хватает, сынок. Мне велено ядра у орудий уложить — вдруг кутерьма какая случится в этих опасных водах. Полвахты из трюма таскал этих железных поганцев, и вот на последнем ящике уже спина не выдержала.";
			link.l1 = "Почему просто не попросишь товарищей? Я думал, ваша братия помогает друг другу.";
			link.l1.go = "SailorNeedBox_3";
		break;
		
		case "SailorNeedBox_3":
			dialog.text = "Вот что наша братия точно не любит — так это таскать тяжести без особой нужды. Такой мне жребий выпал сегодня — ящики с ядрами из трюма таскать. Паскудная работа, недостойная такого моряка, как я. Но что делать?";
			link.l1 = "Да не жалуйся ты так. Помогу. Хоть погляжу на трюм, которым меня тут регулярно пугают.";
			link.l1.go = "SailorNeedBox_4";
			if (IsCharacterPerkOn(pchar, "HT3"))
			{
				link.l2 = "(Атлет) Видишь мой палаш на поясе? Он один весит больше, чем ты. Схожу я за твоими ядрами, мне не сложно.";
				link.l2.go = "SailorNeedBox_4";
			}
			link.l3 = "Я не работаю руками, матрос. Сам грузи свои ящики.";
			link.l3.go = "SailorNeedBox_Net";
		break;
		
		case "SailorNeedBox_4":
			dialog.text = "Спасибо, сынок. Только не надорвись!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBalls");
		break;
		
		case "SailorNeedBox_Net":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "SailorNeedBox_PrinestiBalls":	// ждёт ядра
			dialog.text = "Как дела, сынок?";
			if (CheckCharacterItem(PChar, "BoxOfBalls"))
			{
				link.l1 = "Держи свои ядра. Я думал, они побольше будут.";
				link.l1.go = "SailorWantRum_PrinestiBalls_2";
			}
			if (PCharDublonsTotal() >= 30 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Poli"))
			{
				link.l2 = "Тебя же Поль зовут?";
				link.l2.go = "BallsGold_2";
			}
			link.l3 = "Бывай.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
		break;
		
		case "BallsGold_2":
			dialog.text = "Э-э-э. Ну д-да.";
			link.l1 = "Твоё имя есть в списке, который мне дал месье Пиншон.";
			link.l1.go = "BallsGold_3";
		break;
		
		case "BallsGold_3":
			dialog.text = "Уф, а я уж подумал... Да, Поль — это я стало быть. Сколько у вас там для меня?";
			if (PCharDublonsTotal() >= 20)
			{
				link.l1 = "20 дублонов.";
				link.l1.go = "BallsGold_DatDeneg_gold20";
			}
			if (PCharDublonsTotal() >= 25)
			{
				link.l2 = "25 дублонов.";
				link.l2.go = "BallsGold_DatDeneg_gold25";
			}
			if (PCharDublonsTotal() >= 30)
			{
				link.l3 = "30 дублонов.";
				link.l3.go = "BallsGold_DatDeneg_gold30";
			}
			// link.l4 = "Мне нужно всё перепроверить. Вернусь позже.";
			// link.l4.go = "BallsGold_DatDeneg_3";
		break;
		
		case "BallsGold_DatDeneg_gold20":
			dialog.text = "Спасибо, сынок.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(20);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;
		
		case "BallsGold_DatDeneg_gold25":
			dialog.text = "Спасибо, сынок.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(25);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;
		
		case "BallsGold_DatDeneg_gold30":
			dialog.text = "Спасибо, сынок.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(30);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;
		
		case "BallsGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorNeedBox_PrinestiBalls";
		break;
		
		case "SailorWantRum_PrinestiBalls_2":
			dialog.text = "Да куда уж больше! Хорошо, если только в борт такой подарок прилетит — так разве что осколками корпуса кого посечёт. А ну как корму пробьёт и станет как мячик скакать по всей палубе?!";
			link.l1 = "Знакомая картина?";
			link.l1.go = "SailorWantRum_PrinestiBalls_3";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
		break;
		
		case "SailorWantRum_PrinestiBalls_3":
			dialog.text = "Было дело, сынок. Человек горазд орудия смертоубийства придумывать. Вот взять картечь — бьёт недалеко, корпус не возьмёт, а дюжину человек запросто отправит на тот свет. Или книппель — коли по парусам попасть, так всё в лоскуты превратит! А про бомбы я ничего не скажу — не видел их ни разу, и слава Богу! Дьявольское изобретение. Да и дорогие они.";
			link.l1 = "В убойной силе ядер я уже смог убедиться — по твоей бедной спине.";
			link.l1.go = "SailorWantRum_PrinestiBalls_4";
		break;
		
		case "SailorWantRum_PrinestiBalls_4":
			dialog.text = "Вот уж удружил, так удружил. За мной тоже не заржавеет. Вот — бутылка первостатейного рома, почти полная, ха-ха!";
			link.l1 = "Откуда она у тебя? Я только и слышу о том, что ром на корабле закончился непозволительно рано. С таким товаром на руках ты уже мог любого члена команды упросить не просто один, а все ящики из трюма перетащить.";
			link.l1.go = "SailorWantRum_PrinestiBalls_5";
			GiveItem2Character(PChar, "potionrum");
		break;
		
		case "SailorWantRum_PrinestiBalls_5":
			dialog.text = "Ну, так уж вышло, сынок. Спасибо тебе и бывай.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBallsFinal");
		break;
		
		// <-- Диалог с матросом, которому нужен ящик с ядрами
		
		// --> Диалог с офицером-торговцем, который торгует всяким
		case "OfficerTorgovets":
			dialog.text = "А, месье де Мор. Если вы спать собрались — вам не повезло. Вашу койку занял наш канонир. Сами знаете, разбудить его у вас не выйдет.";
			link.l1 = "Надо сказать, когда ему нужно — он всё прекрасно слышит!";
			link.l1.go = "OfficerTorgovets_1";
			/*link.l2 = "Нет.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets";*/
		break;
		
		case "OfficerTorgovets_1":
			dialog.text = "Это ещё ничего. Слыхал я, что в команде Шарпа был и вовсе слепой канонир. Говорят, по звуку пушки наводил.";
			link.l1 = "Вы сегодня удивительно словоохотливы, месье боцман.";
			link.l1.go = "OfficerTorgovets_2";
		break;
		
		case "OfficerTorgovets_2":
			dialog.text = "И на то есть причина! Скоро будем на суше, а значит — пора переводить оставшийся товарец в звонкие песо. В борделе Сен-Пьера им всегда рады, ха-ха!";
			link.l1 = "Удивительно, что это вы, а не казначей, занимаетесь мелким торгом на борту.";
			link.l1.go = "OfficerTorgovets_3";
		break;
		
		case "OfficerTorgovets_3":
			dialog.text = "А он с людьми общаться не умеет! На то в команде и боцман — умеет и словом, и делом, ха-ха. Дельце у казначея, конечно, тоже имеется — только я в такую мутную водичку не полезу.";
			link.l1 = "И что у вас сегодня в продаже?";
			link.l1.go = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_4":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Последняя бутылка рома на корабле, несколько полезных амулетов... и вуаля! Цельная карта сокровищ.";
				link.l1 = "Вам бы не боцманом, а торговцем быть! Показывайте, что у вас там.";
				npchar.SharlieTutorial_question_0 = true;
			}
			else
			{
				dialog.text = "Ещё что-нибудь?";
				link.l1 = "Показывайте, что у вас там.";
			}
			link.l1.go = "OfficerTorgovets_5";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Амулеты? Такой же, как у вас на груди болтается?";
				link.l2.go = "OfficerTorgovets_6_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Простите... Карта сокровищ?";
				link.l3.go = "OfficerTorgovets_6_question_2_1";
			}
			link.l4 = "Может, в другой раз.";
			link.l4.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_5":
			DialogExit();
			NextDiag.CurrentNode = "OfficerTorgovets_4";
			sld = ItemsFromID("map_full");
			sld.price = 4000;
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "OfficerTorgovets_6_question_1_1":
			dialog.text = "А-а, зоркий глаз, месье. Да, “Коралловая голова” — вещь полезная. Особенно для меня. Если придётся, не дай Бог, вести абордаж — с ней я людей построю мигом.";
			link.l1 = "Вы и правда в это верите?";
			link.l1.go = "OfficerTorgovets_6_question_1_2";
		break;
		
		case "OfficerTorgovets_6_question_1_2":
			dialog.text = "А мне и не нужно верить. Таковы правила Кариб и нашей моряцкой доли. Амулеты — штука полезная. Так что если задержитесь у нас, советую держать при себе пару наборов — на разные случаи.";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_1 = true;
		break;
		
		case "OfficerTorgovets_6_question_2_1":
			dialog.text = "О да. На Карибах это не редкость. Кому-то улыбается удача — получает большой куш. Дальше два пути: либо платит налоги, живёт тихо и долго, либо прячет золото в пещеру — и потом от него остаётся могила, сокровища... и клочок бумаги.";
			link.l1 = "Вот так просто?";
			link.l1.go = "OfficerTorgovets_6_question_2_2";
		break;
		
		case "OfficerTorgovets_6_question_2_2":
			dialog.text = "Не совсем. Карты стоят дорого, да и привлекают к себе таких же охотников, как вы. А сама добыча иногда едва-едва покрывает хлопоты. Но даже у великого Альберта Блэквуда не сразу всё вышло. Сделайте поиск сокровищ профессией — и чем больше найдете сокровищ, тем больше будут становится награды. А если амулет на везение прикупите — дело пойдёт ещё веселее!";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_2 = true;
		break;
		// <-- Диалог с офицером-торговцем, который торгует всяким
		
		// --> Диалог с офицером-казначеем
		case "OfficerKaznachey":
			dialog.text = "Месье де Мор! Одну минуточку.";
			link.l1 = "Опять будете мне морали читать, месье Пиншон? Не трогал я ваши драгоценные чернила!";
			link.l1.go = "OfficerKaznachey_2";
		break;
		
		case "OfficerKaznachey_2":
			dialog.text = "А чем вы тогда в свою книжечку тайком что-то записываете? Святой водой? Чернил в описи пассажирского имущества не было. Впрочем, сейчас у вас проблемы посерьёзнее.";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_3";
		break;
		
		case "OfficerKaznachey_3":
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) sStr = "И ещё — двести, за повреждённый брашпиль. Якорный канат треснул.";
			dialog.text = "Напоминаю, что вы всё ещё должны корабельной казне тридцать песо — за испорченную бочку дождевой воды. Ваша комичная попытка постирать рубашку могла бы выйти ещё дороже, если бы тогда снова дождь не пошёл. "+sStr+"";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass"))
			{
				if (sti(pchar.Money) >= 230)
				{
					link.l1 = "Вот уж чего мне не хватало — так это долгов сразу по прибытии. Держите.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			else
			{
				if (sti(pchar.Money) >= 30)
				{
					link.l1 = "Вот уж чего мне не хватало — так это долгов сразу по прибытии. Держите.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			link.l2 = "И всё? Это же не карточный долг, право слово. Мне сейчас недосуг. Придётся вам обождать до прибытия в порт.";
			link.l2.go = "OfficerKaznachey_3_1";
		break;
		
		case "OfficerKaznachey_3_1":
			dialog.text = "Очень жаль. Тогда, сразу к делу — у меня для вас работа.";
			link.l1 = "Вы не очень ладите с людьми, да?";
			link.l1.go = "OfficerKaznachey_6";
		break;
		
		case "OfficerKaznachey_4":
			dialog.text = "Один момент, пересчитаю.";
			link.l1 = "После ужина не забудьте пересчитать ещё и мои хлебные крошки, что остались на столе.";
			link.l1.go = "OfficerKaznachey_5";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddMoneyToCharacter(pchar, -230);
			else AddMoneyToCharacter(pchar, -30);
		break;
		
		case "OfficerKaznachey_5":
			dialog.text = "Поздравляю. Теперь у корабельной казны к вам нет вопросов. Пока что\nСразу к делу — у меня для вас работа.";
			link.l1 = "Вы не очень ладите с людьми, да?";
			link.l1.go = "OfficerKaznachey_6";
		break;
		
		case "OfficerKaznachey_6":
			dialog.text = "С людьми — не особо. Зато я хорошо считаю\nВот вы, месье де Мор, умеете считать?";
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				link.l1 = "(Счетовод) Мне не чужды ни учётные книги, ни векселя. И понятие нуля мне тоже знакомо.";
				link.l1.go = "OfficerKaznachey_7";
			}
			else
			{
				link.l1 = "Достаточно, чтобы растянуть скудное отцовское пособие до конца сезона.";
				link.l1.go = "OfficerKaznachey_8";
			}
		break;
		
		case "OfficerKaznachey_7":
			dialog.text = "О-о-о! Жаль, что вы не рассказали мне об этом раньше — этот рейс мог бы стать куда интереснее.";
			link.l1 = "Вы что-то говорили про работу?";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_8":
			dialog.text = "Ради вашего же блага — надеюсь, вы никогда не станете судовладельцем. Разорите не только себя, но и всех, кто с вами на борту.";
			link.l1 = "Вы что-то говорили про работу?";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_9":
			dialog.text = "Да. Не знаю, в курсе ли вы, но казначей и врач — вторые после капитана\n"+
			"Выйти в море без этих двоих — значит рискнуть деньгами, а без денег корабль — это просто очень дорогой кусок дерева\n"+
			"Без казначея даже малый шлюп может разорить своего капитана. А первый же бой без врача может угробить весь экипаж, тем самым запустив утомительную и очень дорогую процедуру найма и обучения\n"+
			"На наше с вами счастье, я совмещаю обе должности. Поэтому имею возможность вести личную коммерцию и пользоваться различными мелкими услугами экипажа\n"+
			"Разумеется, услуги оплачиваются щедро — и как раз сейчас хороший момент это сделать\n"+
			"Я хочу, чтобы вы взяли этот список, сундучок с дублонами — и раздали членам экипажа их плату\n"+
			"Строго по списку! Именно поэтому я спросил, умеете ли вы считать.";
			link.l1 = "А почему вы сами этого не сделаете? В конце концов, если люди ждут выплат — пусть сами и придут.";
			link.l1.go = "OfficerKaznachey_10";
		break;
		
		case "OfficerKaznachey_10":
			dialog.text = "У меня сейчас слишком много дел. До конца рейса всего пара дней, и очень скоро тут будет стоять очередь из ста человек, настойчиво требующих своё жалованье.";
			link.l1 = "Вы упоминали дублоны...";
			link.l1.go = "OfficerKaznachey_11";
		break;
		
		case "OfficerKaznachey_11":
			dialog.text = "Испанская золотая монета. Твёрдая валюта и истинный показатель богатства. Самые редкие, дорогие и нужные услуги — только за них\n"+
			"Их хранят вот в таких вот сундучках, для удобства.";
			link.l1 = "А что я за это получу?";
			link.l1.go = "OfficerKaznachey_12";
		break;
		
		case "OfficerKaznachey_12":
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				dialog.text = "(Счетовод) 150 песо, и еще 5 дублонов сверху за то, что вы почти мой коллега. Ну и возможность обменивать песо на дублоны по достойному курсу.";
			}
			else
			{
				dialog.text = "150 песо, и возможность обменивать песо на дублоны. Это немного, но и работа простейшая.";
			}
			link.l1 = "Хорошо. Давайте список и сундук.";
			link.l1.go = "OfficerKaznachey_11_agree";
			link.l2 = "Боюсь, такая работа совсем мне не близка. Прощайте, месье Пиншон.";
			link.l2.go = "OfficerKaznachey_11_otkaz";
		break;
		
		case "OfficerKaznachey_11_otkaz":
			dialog.text = "Ваше право. В таком случае не мешайте мне работать, месье де Мор.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
		break;
		
		case "OfficerKaznachey_11_agree":
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("Chest")].weight) > GetMaxItemsWeight(pchar))
			{
				dialog.text = "Прошу. Только ради Бога — не забудьте достать дублоны из сундучка, строго сверяйтесь со списком, и не вздумайте прикарманить лишнее. Пустой сундук я тоже рассчитываю получить обратно\n"+
				"Только не надорвитесь, месье. И зачем вы столько барахла на себя взвалили? Рекомендую сложить часть вещей в какой-нибудь сундук."; 
			}
			else
			{
				dialog.text = "Прошу. Только ради Бога — не забудьте достать дублоны из сундучка, строго сверяйтесь со списком, и не вздумайте прикарманить лишнее. Пустой сундук я тоже рассчитываю получить обратно.";
			}
			link.l1 = "Как скажете. До скорой встречи, месье Пиншон.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_QuestRazdatZoloto");
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "1");
			else AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "2");
			GiveItem2Character(PChar, "chest");
			if (!isMultiObjectKnown("gold_dublon"))
			{
				SetAlchemyRecipeKnown("gold_dublon");
				SetAlchemyRecipeKnown("Chest");
			}
		break;
		
		case "OfficerKaznachey_12_Wait": // ждёт выполнения квеста
			dialog.text = "Как успехи? Плату раздали? Всё принесли? Остаток дублонов, пустой сундучок?";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuest") && sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) == 3 && CheckCharacterItem(PChar, "chest_open") && GetCharacterItem(pchar, "gold_dublon") >= 18)
			{
				link.l1 = "Всё готово.";
				link.l1.go = "OfficerKaznachey_13";
			}
			link.l2 = "Ещё нет, месье Пиншон.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerKaznachey_12_Wait";
		break;
		
		case "OfficerKaznachey_13":
			dialog.text = "Так, посмотрим...";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_14";
		break;
		
		case "OfficerKaznachey_14":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			if (addGold >= 18 && addGold <= 39)
			{
				dialog.text = "А говорили, что считать умеете. Тут меньше, чем должно быть. А это значит, что моя бухгалтерия только что усложнилась, и вы создали мне новую проблему, вместо того чтобы решить текущую\n"+
				"Таким образом, месье де Мор, оплата вам не полагается.";
				link.l1 = "А дублоны вы мне всё-таки поменяете?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold >= 41)
			{
				dialog.text = "А говорили, что считать умеете. Тут больше, чем должно быть. А это значит, что моя бухгалтерия только что усложнилась, и вы создали мне новую проблему, вместо того чтобы решить текущую\n"+
				"Таким образом, месье де Мор, оплата вам не полагается.";
				link.l1 = "А как насчёт обмена?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold == 40)
			{
				if (IsCharacterPerkOn(pchar, "HT2"))
				{
					dialog.text = "Всё точно. Отрадно видеть, что молодое поколение умеет обращаться с цифрами. Спасибо вам, месье де Мор. Вот ваша плата — и небольшая премия, как почти коллеге.";
					link.l1 = "А с обменом как?";
					link.l1.go = "OfficerKaznachey_15_gold_100";
					AddItems(pchar, "gold_dublon", 5);
				}
				else
				{
					dialog.text = "Всё точно. Отрадно видеть, что молодое поколение ответственно относится к деньгам. Спасибо вам, месье де Мор. Вот ваша плата.";
					link.l1 = "Дублоны всё ещё меняете?";
					link.l1.go = "OfficerKaznachey_15_gold_105";
				}
				AddMoneyToCharacter(pchar, 150);
				AddCharacterSkillPoints(pchar, "Commerce", 1);
			}
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "chest_open");
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", 100);
			pchar.questTemp.SharlieTutorial_KaznacheyQuestCompleted = true;
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive");
			npchar.Merchant.type = "SharlieTurorialK";
			pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
		break;
		
		case "OfficerKaznachey_15_gold_115":
			dialog.text = "Почему бы и нет. Сто пятнадцать песо за дублон. Обращайтесь, если станет интересно.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 115;
		break;
		
		case "OfficerKaznachey_15_gold_105":
			dialog.text = "Разумеется. Сто пять песо за дублон. Обращайтесь, если станет интересно\n"+
			"И позвольте совет: если, не дай Бог, судьба поставит вас командовать кораблём — наймите казначея первым делом. Даже слабый специалист сэкономит вам целое состояние.";
			link.l1 = "Спасибо, месье Пиншон.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 105;
		break;
		
		case "OfficerKaznachey_15_gold_100":
			dialog.text = "Разумеется! Сто песо за дублон — честный курс. В Карибских банках с вас содрали бы больше\n"+
			"И позвольте совет: если, не дай Бог, судьба поставит вас командовать кораблём — наймите казначея первым же делом. Даже слабый специалист сэкономит вам целое состояние.";
			link.l1 = "Спасибо, месье Пиншон.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 100;
		break;
		
		case "OfficerKaznachey_16_Proval": // Если не выполнил задание, то отбирает дублоны
			dialog.text = "Прохлаждаетесь, месье де Мор?";
			link.l1 = "Вас тоже в трюм сослали?";
			link.l1.go = "OfficerKaznachey_16_Proval_2";
		break;
		
		case "OfficerKaznachey_16_Proval_2":
			dialog.text = "Я — судовой врач, де Мор! Скоро кают-компания будет полна раненых, а я увижу больше крови, чем любой участник сражения. И даже не будь я врачом, а только казначеем — в бою стал бы в строй, как и все. Нет, единственный, кого сослали отсиживаться в уютном трюме — это вы.";
			link.l1 = "Тогда что вы тут забыли?";
			link.l1.go = "OfficerKaznachey_16_Proval_3";
		break;
		
		case "OfficerKaznachey_16_Proval_3":
			dialog.text = "Сражение начнётся только через пару часов, так что самое время закрыть дневной учёт. У вас мой сундучок с дублонами, де Мор. Потрудитесь вернуть.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 1 || GetCharacterItem(pchar, "chest") >= 1 || GetCharacterItem(pchar, "chest_open") >= 1)
			{
				link.l1 = "Забирайте. И больше сюда свою физиономию не показывайте.";
				link.l1.go = "OfficerKaznachey_16_Proval_4";
			}
			else
			{
				link.l1 = "Я оставил ваше барахло в другом месте.";
				link.l1.go = "OfficerKaznachey_16_Proval_5";
			}
		break;
		
		case "OfficerKaznachey_16_Proval_4":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			dialog.text = "И не собирался. Я же не сухопутная крыса - моё место не в трюме. Прощайте.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			if (GetCharacterItem(pchar, "gold_dublon") >= 1 || GetCharacterItem(pchar, "chest") >= 1) ChangeCharacterComplexReputation(pchar, "nobility", -3);
			else ChangeCharacterComplexReputation(pchar, "nobility", -6);
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", addGold);
			TakeItemFromCharacter(pchar, "chest");
			TakeItemFromCharacter(pchar, "chest_open");
		break;
		
		case "OfficerKaznachey_16_Proval_5":
			dialog.text = "В другом месте... Обсудим после сражения - в присутствии капитана. До встречи.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
		break;
		
		case "TreasurerTrade":
			dialog.text = "Интересуют дублоны, месье де Мор?";
			link.l1 = "Давайте поторгуемся.";
			link.l1.go = "TreasurerTrade_1";
			link.l2 = "Пока нет.";
			link.l2.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
		break;
		
		case "TreasurerTrade_1":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "TreasurerTrade";
		break;
		// <-- Диалог с офицером-казначеем
		
		// --> Матрос сообщает о приближающихся кораблях
		case "Sailor_Trevoga":
			dialog.text = "Кэп, тревога! Пираты на горизонте!";
			link.l1 = "...";
			link.l1.go = "Sailor_Trevoga_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain"));
			PlaySound("Ship\rynda_alarm.wav");
		break;
		
		case "Sailor_Trevoga_2":
			StartInstantDialog("SharlieTutorial_Captain", "Sailor_Trevoga_3", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "Sailor_Trevoga_3":
			dialog.text = "Алонсо, вежливо проводи месье де Мора в трюм. И проверь, чтобы месье Дрюссак соизволил проснуться и подготовил орудийные расчёты к бою.";
			link.l1 = "Капитан, я готов драться! Дворянин не может...";
			link.l1.go = "Sailor_Trevoga_4_fencing";
			link.l2 = "Если я могу чем-то помочь...";
			link.l2.go = "Sailor_Trevoga_4_leadership";
			link.l3 = "Так это что же, бургундского не будет?..";
			link.l3.go = "Sailor_Trevoga_4_fortune";
		break;
		
		case "Sailor_Trevoga_4_fencing":
			dialog.text = "Алонсо, убери его. За работу, лентяи! Поднять паруса!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "Sailor_Trevoga_4_leadership":
			dialog.text = "Алонсо, убери его. За работу, лентяи! Поднять паруса!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "Sailor_Trevoga_4_fortune":
			dialog.text = "Алонсо, убери его. За работу, лентяи! Поднять паруса!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		// <-- Матрос сообщает о приближающихся кораблях
		
		// --> Диалог с пиратом в трюме
		case "EnemyPirate_1":
			dialog.text = "Дьявол! Вот черти упёртые!";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_2";
			PlaySound("VOICE\Russian\OliverTrast01.wav");
			//PlaySound("VOICE\Spanish\OliverTrast01.wav"); //вставить для испанской версии
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
		break;
		
		case "EnemyPirate_2":
			dialog.text = "А ты что здесь делаешь?! Своих бросил и от боя прячешься, крыса трюмная?! Сейчас-то я тебе кишки выпущу!";
			link.l1 = "Зря ты залез в мой трюм. Сейчас я сам тебе кишки выпущу.";
			link.l1.go = "EnemyPirate_3_Fencing";
			link.l2 = "Да ты сам еле на ногах стоишь, а большая часть крови на тебе — не твоя.";
			link.l2.go = "EnemyPirate_3_Leadership";
			if (IsCharacterPerkOn(pchar, "HT1"))
			{
				link.l3 = "(Дуэлянт) Как же мне этого не хватало.";
				link.l3.go = "EnemyPirate_3_Duelyant";
			}
		break;
		
		case "EnemyPirate_3_Fencing":
			dialog.text = "Хе-хе. Ну попробуй, щегол.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "EnemyPirate_3_Leadership":
			dialog.text = "Хе-хе. Ну так и терять мне, значит, нечего.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "EnemyPirate_3_Duelyant":
			dialog.text = "Что ты несёшь?!";
			link.l1 = "Два месяца. Два месяца я был вынужден держать шпагу в ножнах. Потанцуем!";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "EnemyPirate_4":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_2");
		break;
		
		// <-- Диалог с пиратом в трюме
		
		// --> Диалог с выжившим матросом
		case "SailorAlive_1":
			dialog.text = "Ну хоть вы живы... А я всё. Скис. Крепко меня по румпелю приложили...";
			link.l1 = "Что случилось?!";
			link.l1.go = "SailorAlive_2";
			DelLandQuestMark(npchar);
		break;
		
		case "SailorAlive_2":
			dialog.text = "Абордаж случился. Ар-р-гх! Вот черти упёртые!\nСлушайте внимательно: орудийную палубу мы отстояли, но наверху веселье только начинается. Зуб даю, сейчас снова сюда полезут. Держите картечницу! Дьявол, осторожнее! Она же заряжена!";
			if (IsCharacterPerkOn(pchar, "HT4"))
			{
				link.l1 = "(Стрелок) За меня не переживай. Кто сунется — мигом дырок понаделаю.";
			}
			else link.l1 = "...";
			link.l1.go = "SailorAlive_3";
		break;
		
		case "SailorAlive_3":
			dialog.text = "Там картечь. Если грамотно всё сделать — сможете двоих-троих сразу забрать\nЯ в вас верю, Шарль. Как отобьетесь, обыщите трупы. Может найдёте какое-нибудь пойло для меня... иначе я вам не помощник.";
			link.l1 = "Держись, Алонсо. А вот и гости!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_5");
			GiveItem2Character(PChar, "pistol3");
			EquipCharacterByItem(PChar, "pistol3");
			AddItems(pchar, "grapeshot", 5);
			AddItems(pchar, "GunPowder", 5);
			LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
		break;
		
		case "SailorAlive_11":
			dialog.text = "Хорошо... Хорошо сработали, Шарль. Нашли что-нибудь для меня?";
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				link.l1 = "Думаю, это оно. Хоть и выглядит подозрительно.";
				link.l1.go = "SailorAlive_12";
			}
			link.l2 = "Ищу!";
			link.l2.go = "exit";
			NextDiag.TempNode = "SailorAlive_11";
		break;
		
		case "SailorAlive_12":
			dialog.text = "А на вкус недурно, ха-ха! Спасибо, Шарль. И тех троих вы красиво положили. Раз уж вы и взаправду такой благородный дворянин, то принимайте командование. Вдвоём мы точно палубу удержим, а если и парни наверху сдюжат — то и день за нами!";
			link.l1 = "...";
			//link.l1.go = "exit";
			link.l1.go = "SailorAlive_13";
			//AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_7");
			TakeItemFromCharacter(pchar, "quest_potion");
			PlaySound("Ambient\Tavern\glotok_001.wav");
			DelLandQuestMark(npchar);
		break;
		
		case "SailorAlive_13":
			/*if (CheckAttribute(npchar, "fighter"))
			{
				dialog.text = "Вот так то лучше. Картечницу зарядили?";
				link.l1 = "Я как раз этим занимаюсь... А почему так резко всё затихло?";
				link.l1.go = "SailorAlive_14";
				SetMusic("");
			}
			else
			{
				dialog.text = "Раз уж вы и взаправду такой благородный дворянин, то принимайте командование.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "SailorAlive_13";
			}*/
			dialog.text = "Вот так то лучше. Картечницу зарядили?";
			link.l1 = "Я как раз этим занимаюсь... А почему так резко всё затихло?";
			link.l1.go = "SailorAlive_14";
			SetMusic("");
			LAi_SetActorType(npchar);
			LAi_ActorSetGroundSitMode(npchar);
			LAi_ActorAnimation(npchar, "ground_standup", "1", -1);
		break;	
		
		case "SailorAlive_14":
			dialog.text = "А это для пущей драматичности. Сейчас начнётся.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_8");
		break;
		// <-- Диалог с выжившим матросом
		
		// --> Диалог с Алонсо после боя
		case "AfterBattle_Alonso_1":
			dialog.text = "Вот мы и заканчиваем там же, где и начали. Спасибо, что спасли мою шкуру, Шарль.";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_Ranen"))
			{
				link.l1 = "Думаю, мы квиты. Я даже не помню, как ты вытащил меня оттуда.";
			}
			else
			{
				link.l1 = "Думаю, мы квиты. Если бы не ты и парни, то я бы там и остался.";
			}
			link.l1.go = "AfterBattle_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "AfterBattle_Alonso_2":
			dialog.text = "Вы могли отсидеться в трюме, как вам было и велено. Жаль, что капитан не дожил, чтобы устроить вам выволочку.";
			link.l1 = "Нам пришлось доставать его из-под целой горы тел. Скольких мерзавцев он успел положить?";
			link.l1.go = "AfterBattle_Alonso_3";
		break;
		
		case "AfterBattle_Alonso_3":
			dialog.text = "Кто-то видел, как он завалил троих. А другие говорят, что не меньше дюжины. Думаю, только дьявол вел точный счёт.";
			link.l1 = "Ты так и не объяснил мне, почему всё так обернулось.";
			link.l1.go = "AfterBattle_Alonso_4";
		break;
		
		case "AfterBattle_Alonso_4":
			dialog.text = "А что рассказывать? Не спасли нас шестнадцатифунтовые пушки от одного пиратского брига. Вот что значит — корабль для реального дела\n"+
			"Вмиг долетел и, пока мы разворачивались, расстрелял картечью и сразу на абордаж кинулся. Вы бы видели, что на палубе творилось — нести врачу уже нечего было\n"+
			"Самое поганое в драке с пиратами — никакого прибытку с них. Голодранцы одним словом. Даже их бриг не смогли мы забрать.";
			link.l1 = "И что будет дальше?";
			link.l1.go = "AfterBattle_Alonso_5";
		break;
		
		case "AfterBattle_Alonso_5":
			dialog.text = "Корабль на плаву, а людей мы сберегли достаточно, чтобы доставить вас в Сен-Пьер по расписанию, где я буду искать себе нового капитана, а вы найдете брата и поведаете ему о своих приключениях. А что дальше — только одному Богу известно.\n"+
			"Но одно я знаю точно —  у нас вы приживетесь. Неплохо для сухопутной крысы, Шарль.";
			link.l1 = "...";
			link.l1.go = "AfterBattle_Alonso_6";
		break;
		
		case "AfterBattle_Alonso_6":
			dialog.text = "Ба-а! Да вас сейчас начнёт выворачивать наизнанку. Не стесняйтесь. Это страх из вас выходит. Добро пожаловать на Карибы!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_SeaNearMartinique");
		break;
		
		
		// <-- Диалог с Алонсо после боя
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}