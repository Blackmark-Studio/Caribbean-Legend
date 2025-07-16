// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_1"))
			{
				link.l1 = "Говорят, кто-то оставил вас без драгоценного джина. Или слухи врут?";
				link.l1.go = "OS_Tavern1_1";
			}
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_3"))
			{
				link.l1 = "Хорошие новости, "+npchar.name+"! Я наш"+GetSexPhrase("ёл","ла")+" ваш бочонок!";
				link.l1.go = "OS_Tavern3_1";
			}
			//<-- Старые счёты
		break;
		
		//--> Старые счёты
		case "OS_Tavern1_1":
			dialog.text = "Увы, это правда. Что вы ещё слышали? Вам что-то известно? Умоляю, скажите, что вы знаете где его отыскать. Если я его не найду... мне придётся покинуть город. Или я сам уйду, или меня вынесут в гробу.";
			link.l1 = "Хм... Дела у вас, дружище, и правда неважные. Нет, о вашей беде я только краем уха слышал"+GetSexPhrase("","а")+". Как же вы упустили из виду столь дорогой для вас товар?";
			link.l1.go = "OS_Tavern1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OS_Tavern1_2":
			dialog.text = "Эх... Что тут сказать... Украли прямо из-под носа! Утром бочонок совершенно точно был на месте. Привезли его позавчера, и я, чтобы спать спокойно, забрал его домой на ночь. Наутро вернул сюда, поставил под прилавок. А к вечеру - его словно ветром сдуло! И никто ничего не видел, никто ничего не слышал.";
			link.l1 = "Ну и ну...";
			link.l1.go = "OS_Tavern1_3";
		break;
		
		case "OS_Tavern1_3":
			dialog.text = "Будь у меня хоть какая-то зацепка, я бы уже отправился на поиски. Но увы, ничего - словно этот бочонок был слишком хорош для нашего мира, и его просто забрали небеса. Я готов заплатить сто пятьдесят дублонов любому, кто вернёт мне его. Да что там, я размещу табличку с его именем в таверне, чтобы все знали о его подвиге!";
			link.l1 = "Я постараюсь вам помочь. А к вопросу с табличкой мы ещё вернёмся. Скажите лучше, кто знал о бочонке? И кто, кроме вас, мог оказаться за стойкой?";
			link.l1.go = "OS_Tavern1_4";
			link.l2 = "Сто пятьдесят дублонов за бочонок? Забавно. Но это не мои хлопоты. Разбирайтесь сами.";
			link.l2.go = "OS_Tavern1_end";
		break;
		
		case "OS_Tavern1_end":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			CloseQuestHeader("OS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			sld = CharacterFromID("OS_Pirate");
			sld.lifeday = 0;
		break;
		
		case "OS_Tavern1_4":
			dialog.text = "Да собственно никто! Разве что моя официантка, но это исключено. В тот день в таверне был небывалый кутёж - команда 'Морской Бестии' вернулась с охоты, да ещё и с приличной добычей. У неё и минуты присесть не было, не говоря уже о том, чтобы  за стойкой шастать.";
			link.l1 = "Вы в этом уверены?";
			link.l1.go = "OS_Tavern1_5";
		break;
		
		case "OS_Tavern1_5":
			dialog.text = "Абсолютно! Работать без передышки ей пришлось не по душе, и к вечеру она уже была на взводе. Один из матросов начал к ней приставать, так она такой крик подняла, что у всех уши заложило. Мне даже пришлось выйти из-за стойки, чтобы всех успокоить. Хотя обычно она на такие выходки реагирует куда спокойнее.";
			link.l1 = "И всё? Больше ничего примечательного в тот день?";
			link.l1.go = "OS_Tavern1_6";
		break;
		
		case "OS_Tavern1_6":
			dialog.text = "Пока я разбирался с первым скандалом, в таверне вспыхнула потасовка - двое матросов сцепились в дальнем углу таверны. Правда, драка долго не продлилась: похоже, они были из одной команды, и их быстро растащили. После этого всё действительно утихло, и ничего примечательного больше не произошло.";
			link.l1 = "Ну что ж, я готов"+GetSexPhrase("","а")+" начать поиски. Ждите. Думаю, скоро бочонок будет снова под вашим кхе-кхе... бдительным присмотром.";
			link.l1.go = "OS_Tavern1_7";
		break;
		
		case "OS_Tavern1_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			AddQuestRecord("OS", "2");
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_1", "citiz_31", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "OS_Matros";
			LAi_SetImmortal(sld, true);
			sld.City = "PuertoPrincipe";
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto14");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "OS_Tavern3_1":
			dialog.text = "Вы нашли его?! Неужели это правда? Капитан, вы буквально спасли мне жизнь! Кто за этим стоит? Я должен знать имя этого подлеца!";
			link.l1 = "Это была тщательно продуманная махинация некоего Джека Вейлса на пару с капитаном 'Морской Бестии'. Они привлекли своих матросов и разыграли настоящий спектакль, чтобы отвлечь вас. Когда вы покинули стойку, бочонок остался без присмотра - и они без труда его украли.";
			link.l1.go = "OS_Tavern3_2";
			DelLandQuestMark(npchar);
			pchar.questTemp.CameraDialogMode = true;
		break;
		
		case "OS_Tavern3_2":
			dialog.text = "Невероятно! Джек Вейлс! Значит, он снова здесь... И, похоже, решил таким образом попытаться вернуть себе таверну. Этот лис никогда не отступает!";
			link.l1 = "Так значит, он когда-то был владельцем этой таверны? Уверяю вас, больше ему не удастся провернуть нечто подобное. Я отправил"+GetSexPhrase("","а")+" его к праотцам.";
			link.l1.go = "OS_Tavern3_3";
		break;
		
		case "OS_Tavern3_3":
			dialog.text = "Капитан! Это поразительно! Вы... вы избавили меня от постоянного страха за своё будущее! Я всегда знал, что рано или поздно он вернётся... Несколько лет назад мы с ним соперничали за право владеть этой таверной, и он сумел одержать верх\nНо радость победы его и погубила - он так разошёлся с празднованиями, что даже не заметил, как проиграл её мне в карты. Конечно, наутро он прибежал, умолял вернуть таверну, обещал всё, что угодно\nНо я ведь не полный олух, чтобы пойти на такое. А потом он исчез... Я знал, что он не оставит это просто так. Чувствовал, что однажды он вернётся. И вот, этот день настал.";
			link.l1 = "Нужно отдать ему должное, ловко он всё провернул.";
			link.l1.go = "OS_Tavern3_4";
		break;
		
		case "OS_Tavern3_4":
			dialog.text = "Погодите! А откуда ему вообще стало известно о бочонке? Кажется... кажется, я начинаю понимать! Официантка! Вот почему она выбежала отсюда как ошпаренная, даже не попрощавшись. Видимо, ей удалось пронюхать, что вы разделались с Джеком. Теперь всё складывается. Капитан, я перед вами в неоплатном долгу, вы...";
			link.l1 = "...";
			link.l1.go = "OS_Tavern3_5";
		break;
		
		case "OS_Tavern3_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_3");
			ChangeShowIntarface();
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Zaharia", "Marlow", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
			sld.name = GetCharacterName("Zachary");
			sld.lastname = GetCharacterName("Marlow");
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "reload", "reload1");
			TeleportCharacterToPosAy(sld, -1.30, 0.00, -0.67, 1.50);
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "Zaharia_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

