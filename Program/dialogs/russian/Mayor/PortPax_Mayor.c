// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вы хотели? Спрашивайте.", "Я слушаю вас, что за вопрос?"), "Второй раз за день вы пытаетесь задать вопрос...", "В третий раз за день вы опять пытаетесь задать вопрос...",
                          "Да когда же это кончится?! У меня полно работы по управлению делами города, а ты всё вопросы пытаешься задать!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Не сейчас, не место и не время..."), "Да, верно... Но не сейчас, позже...",
                      "Задам, задам... Только позже...", "Извините, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+", Ваша Светлость. Я прибыл по приказанию генерал-губернатора шевалье де Пуанси. В мою задачу входит доставить на Эспаньолу барона Ноэля Форже, прибывшего из метрополии с целью инспекции французских колоний для последующей огранизации Французской Вест-Индской торговой Компании. Позвольте представить вам барона... Всё дальнейшее изложит вам непосредственно он сам.";
                link.l1.go = "patria_portpax";
			}
			// Rebbebion, квест "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk"))
			{
				link.l1 = "Ваша Светлость, вы хотели меня видеть?";
				link.l1.go = "PZ1";
			}
			// Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogMayor"))
			{
				link.l1 = "Месье, у меня к вам дело весьма деликатного характера.";
				link.l1.go = "UV_1";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Вы уже всё забрали. Что вам ещё нужно?", "Неужели осталось ещё что-то, что вы не прихватили?");
            link.l1 = RandPhraseSimple("Осматриваюсь напоследок...", "Проверяю, может забыл"+ GetSexPhrase("","а") +" что забрать...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		// Jason НСО
		case "patria_portpax":
			dialog.text = "Очень рад встрече с вами, капитан Шарль де Мор, и с бароном. Я сделаю всё возможное для того, чтобы пребывание месье Форже в нашей колонии было максимально комфортным. И пользуясь тем, что столь высокопоставленные особы нанесли мне визит, я буду ходатайствовать вам об одном деле.";
			link.l1 = "Очень интересно! Излагайте, Ваша Светлость.";
			link.l1.go = "patria_portpax_1";
		break;
		
		case "patria_portpax_1":
			dialog.text = "В последние месяцы нашу колонию ни разу не посетил ни один представитель генерал-губернатора, словно про нас на Сент-Кристофере совсем забыли! А тем временем, испанцы, которые жаждут сделать всю Эспаньолу чисто испанской и которым французские поселенцы и буканьеры на западе острова как кость в горле, готовят нападение! Мои патрульные офицеры, наши торговые капитаны и даже простые рыбаки сообщали, что в Сантьяго собирается мощная испанская эскадра, и что она готовится атаковать Порт-о-Пренс!";
			link.l1 = "Сведения достоверны, Ваша Светлость?";
			link.l1.go = "patria_portpax_2";
		break;
		
		case "patria_portpax_2":
			dialog.text = "Я не располагаю точными разведданными, но такое обилие информации от совершенно разных людей не может быть просто досужими слухами. Наша колония очень важна для Франции, у нас здесь лучшие плантации, в чём барон сможет лично убедиться. Потерять эту колонию или даже подвергнуть её риску разграбления - недопустимо!";
			link.l1 = "Я приму к сведению ваши слова и обязательно сообщу шевалье де Пуанси. Уверен, он примет надлежащие меры.";
			link.l1.go = "patria_portpax_3";
		break;
		
		case "patria_portpax_3":
			dialog.text = "Благодарю, капитан...";
			link.l1 = "";
			link.l1.go = "patria_portpax_4";
		break;
		
		case "patria_portpax_4":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
		
		case "PZ1":
			DeleteAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk");
			dialog.text = "Нет, я вас не вызывал, месье. Вы что-то хотели?";
			link.l1 = "Как же? Но ведь нас встретил ваш посыльный, сказал, вы приготовили для меня один из домов города...";
			link.l1.go = "PZ2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ2":
			dialog.text = "Какой дом, какой посыльный, что за самоуправство?!";
			link.l1 = "Ну, как это - какой... Его зовут Анри Тибо, и...";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "ЧТО?.. Вы хоть знаете, кто это?.. Видимо, нет. Но это и неважно. Что племянник Левассера забыл в моём городе...";
			link.l1 = "О Боже...";
			link.l1.go = "PZ4";
		break;
		
		case "PZ4":
			dialog.text = "Месье де Мор, вы меня слышите? Месье?";
			link.l1 = "...";
			link.l1.go = "PZ5";
		break;
		
		case "PZ5":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload1", "PZ_SharleBezhitObratno", -1);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			SetMusic("music_teleport");
			pchar.questTemp.lockedMusic = true;
		break;
		
		//--> Украденное воспоминание
		case "UV_1":
			dialog.text = "Деликатного характера? Очень интересно. Внимательно вас слушаю.";
			link.l1 = "Видите ли, ваша племянница, Жюли, обратилась ко мне с просьбой помочь ей в поиске некоего ожерелья.";
			link.l1.go = "UV_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			DelLandQuestMark(npchar);
		break;
		
		case "UV_2":
			dialog.text = "Ожерелья? Не помню, чтобы у неё было ожерелье.";
			link.l1 = "Я всё объясню, господин губернатор, по порядку. Ожерелье я наш"+GetSexPhrase("ёл","ла")+". Как оказалось, воровка - это прислуга вашей племянницы по имени Жизель. Судя по поведению того, кому она сбывала украденное, это явно не её первая и, боюсь, не последняя кража.";
			link.l1.go = "UV_3";
		break;
		
		case "UV_3":
			dialog.text = "Продолжайте.";
			link.l1 = "Жюли не обратилась к вам за помощью, потому что это ожерелье - подарок от человека, с которым вы запретили ей общаться. Я же, будучи уверенн"+GetSexPhrase("ым","ой")+", что вы поступили так исключительно из самых благородных побуждений, посчитал"+GetSexPhrase("","а")+" своим долгом сообщить вам об этом и вернуть ожерелье.";
			link.l1.go = "UV_4";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
		break;
		
		case "UV_4":
			dialog.text = "Вы поступили мудро"+GetSexPhrase(", капитан","")+". Рад видеть, что вы предпочли сообщить мне правду, вместо того чтобы потакать девичьим капризам Жюли.";
			link.l1 = "Я желаю ей только лучшего и уверен"+GetSexPhrase("","а")+", что ваши намерения столь же праведны.";
			link.l1.go = "UV_5";
		break;
		
		case "UV_5":
			dialog.text = "Разумеется, капитан, я, как её дядя, желаю ей только добра. За вашу рассудительность примите мою благодарность. Вот сто пятьдесят дублонов и ещё кое-что - компас, который, надеюсь, станет для вас полезным спутником в ваших плаваниях.";
			link.l1 = "Благодарю, месье. Это было совсем не обязательно. Но за сим вынужден"+GetSexPhrase("","а")+" откланяться - дела ждут.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_End");
			AddItems(pchar, "gold_dublon", 150);
			GiveItem2Character(PChar, "compass1");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		//<-- Украденное воспоминание
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

