// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
			link.l1 = RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить.");
		    link.l1.go = "exit";
			// Rebbebion, квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.Sotta") && !CheckAttribute(npchar, "questTemp.Lutter"))
			{
				if (rand(1) == 0)
				{
					link.l1 = "Вы, случайно, не общались с капитаном Эдгардо Соттой? Можете что-нибудь о нём рассказать?";
					link.l1.go = "Sotta1";
					link.l2 = "У места казни Говорливого Мэтта настоящее столпотворение, неужели вам не интересно поглядеть?";
					link.l2.go = "Lutter1";
				}
				else
				{
					link.l1 = "Скажите, а вы видели этого героя, капитана Эдгардо Сотту? А то его корабль уже отбыл. Каков же он? Просто не верится, что знаменитого Говорливого Мэтта поймал торговец!";
					link.l1.go = "Sotta1_1";
					link.l2 = "Я смотрю, весь город радуется тому, что Латтера поймали - даже те, кто никогда не выходит в море."
					link.l2.go = "Lutter1_1";
				}
			}
			// <== квест "Путеводная звезда"
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Я что, работаю на тайную агентурную сеть для "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Ну ладно... тогда пока.";
			link.l1.go = "exit";
			link.l2 = "Тогда другой вопрос";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Я вам что справочная? Не знаю. Ничего не ведаю.";

            link.l1 = "Вот бестолочь! Пока.";
			link.l1.go = "exit";
			link.l2 = "Тогда другой вопрос";
			link.l2.go = "new question";
		break;
		
		// Квест "Путеводная звезда" ==>
		case "Sotta1":
			dialog.text = "Знаете, вот тоже как-то не довелось поговорить. Зато удалось наблюдать его корабль!";
			link.l1 = "Ну, не буду более беспокоить, всего доброго.";
			link.l1.go = "Exit";
			
			npchar.questTemp.Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sotta1_1":
			dialog.text = "Вот именно, не верится! Не верьте всему, что слышите, сударь. Был он у нас, прям как вы на данный момент. Хорошо, конечно, что он изловил Латтера, но к чему этот маскарад с торговцем? У него выправка, как у военного. Я таких людей всегда узнаю - родич прослужил немало лет.";
			link.l1 = "Да вы что?! Надо же. Ну, у всех свои скелеты в шкафу. Я, пожалуй, пойду. Спасибо, что поделились своими наблюдениями.";
			link.l1.go = "Exit";
			
			npchar.questTemp.Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Да глядели уже на Мэтта этого все, кому не лень. Даже сомневаться стали, а тот ли это самый пират, что наводил страх на наших купцов несколько лет. Ну или если это и правда он, как он вообще стал капитаном? Пока его вели солдаты, он то кричал, то плакал, то смеялся, то щетинился, как ёж. Сумасшедший какой-то.";
			link.l1 = "Возможно, это поражение и осознание своей скорой гибели слишком сильно на него повлияли, не думаете? Впрочем, это уже неважно. До свидания!";
			link.l1.go = "Exit";
			
			npchar.questTemp.Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1_1":
			dialog.text = "Верно! И я тоже радуюсь - соотечественники ведь гибли от его рук, как-никак. Да и у кого-то был отец, брат или сын на каком-нибудь торговце - в общем, поняли. Слишком долго это всё длилось! Пожалуй, Мэтт был одним из самых удачливых пиратов за последние годы, если вам интересно моё мнение.";
			link.l1 = "Интересно, конечно. Однако рано или поздно удача всегда заканчивается. До встречи.";
			link.l1.go = "Exit";
			
			npchar.questTemp.Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

