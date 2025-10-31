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
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Послушай, не видел ли ты капера по имени Франсуа Гонтьер? Он недавно был в вашем городе.";
                link.l1.go = "Portobello_rat_1";
            }			
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "Послушай, не подскажешь, где найти торговца по имени Хайме Силисио? Он вроде как к вам собирался...";
                link.l1.go = "trial";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "Послушай, я ищу человека по имени Бертран Пинетт, не слыхал о таком? Он недавно прибыл в Порто-Белло. Солидный такой господин, торговец, в парике кручёном. Может, заходил к тебе...";
                link.l1.go = "FMQG";
            }
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Tavern_1"))
            {
                link.l1 = "Не подскажешь, где мне найти Марису Кальдера?";
                link.l1.go = "LFD_Tavern_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("Нет, не знаю. В таверну он не заходил, да и в городе я его не видел.", "Ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом, я тебе ответил.", "Я же говорю тебе, ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом Гонтьере.", "Послушай, отойди и не мешай! Совсем что ли крыша поехала?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ну что же, будем искать.", "Хм, ну да...", "Да, точно, "+ GetSexPhrase("спрашивал","спрашивала") +"...", "Извини, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			DelLandQuestMark(npchar);
			npchar.quest.trial = true;
			
			dialog.text = "Простите, сеньор, но такие дела с чужаком будет обсуждать только предатель или пьяница. Мне проблемы не нужны.";
			link.l1 = "Пьяница, говоришь... В таком случае, извини за беспокойство, приятель.";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Ничего не слышал об этом господине, приятель.";
			link.l1 = "Он знакомый дона Карлоса де Мильяра. Точно ничего не припомнишь?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Нет. Так если они с доном де Мильяром друзья, иди на приём к губернатору и попроси о встрече с сеньором Карлосом. У него и справишься о своём торговце.";
			link.l1 = "Пожалуй, так и сделаю. Спасибо за совет!";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
		
		//--> Письмо от покойника
		case "LFD_Tavern_1_1":
			dialog.text = "Марису? Хм... Давненько я её не видел. С тех пор, как её известили о гибели мужа, в городе она не показывалась.";
			link.l1 = "Значит, она вдова?";
			link.l1.go = "LFD_Tavern_1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LFD_Tavern_1_2":
			dialog.text = "Да. Её муж был капитаном торгового пинаса 'Волнорез'. Благодаря лицензии Голландской Вест-Индской Компании, ему были открыты почти все порты архипелага. Поговаривают, он не пережил нападение пиратов на пути из Белиза в Капстервиль. Подобное здесь не редкость, но для неё это стало настоящим ударом.";
			link.l1 = "И что, она просто взяла и исчезла?";
			link.l1.go = "LFD_Tavern_1_3";
		break;
		
		case "LFD_Tavern_1_3":
			dialog.text = "Ну, сказать, что исчезла - это слишком громко. Но с тех пор в городе её почти не видно. Хотя, странное дело... Время от времени разные мужчины спрашивают о ней. Как и вы, капитан. Если бы она не была такой набожной, я бы решил, что она... скрылась от глаз людских и зарабатывает как может. Но Мариса, до того как умер её муж, не пропускала ни одной Святой мессы, она буквально жила церковью, так что едва ли такое возможно.";
			link.l1 = "Это всё? Больше ты ничего не знаешь?";
			link.l1.go = "LFD_Tavern_1_4";
		break;
		
		case "LFD_Tavern_1_4":
			dialog.text = "Всё, что мне известно, капитан, я уже рассказал.";
			link.l1 = "...";
			link.l1.go = "LFD_Tavern_1_5";
		break;
		
		case "LFD_Tavern_1_5":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Tavern_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

