// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
			link.l1 = RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить.");
		    link.l1.go = "exit";
			
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && npchar.sex == "man")
			{
				link.l1 = "Вы, случайно, не знакомы с неким Сеппом ван дер Винком?";
				link.l1.go = "PZ_1";
			}
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
		
		case "PZ_1":
			dialog.text = "Ну-у-у, лично не знакомы, но вижу его здесь время от времени. А что такое?";
			link.l1 = "Да вот найти его пытаюсь, мне поручено вручить ему лично в руки один пакет. А кого ни спрошу - никто не хочет говорить о нём, почему - непонятно... Не знаете? Он плохой человек? Поделитесь своим честным мнением, буду благодарен.";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Повторюсь, мы лично не знакомы, сударь, так что я почти ничего не знаю. Но есть у него в городе близкий друг, их часто можно увидеть вместе. Обратитесь к нему, он сам решит, что говорить вам, а что - нет. Зовут его Робер Мартэн.";
			link.l1 = "Робер Мартэн, угу... А кто он такой, где чаще всего его можно найти?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "По-разному, но прямо сейчас он у нашего маяка - чинит свой галеон после ужасного шторма. Называется 'Вольтижёр'.";
			link.l1 = "Большое вам спасибо! Вы даже не представляете, как вы мне помогли.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateRobertMartin");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

