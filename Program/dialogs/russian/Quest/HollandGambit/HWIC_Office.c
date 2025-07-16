// НПС офиса ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// офицер
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Тревога! Враг в помещении! К оружию!";
				link.l1 = "А-ать!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Ага! Кажется, я тебя знаю... Точно! Ты объявлен вне закона за преступные деяния! Ребята, хватайте его!";
				link.l1 = "А-ать!";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "Здравствуйте. Что вам угодно?";
				link.l1 = "Я заш"+GetSexPhrase("ёл","ла")+" по торговым делам. Лицензии, корабельные приборы и прочее...";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "Мне угодно предложить Компании свои услуги. В обмен на золото, конечно. Хочу наняться на работу.";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Здравствуйте. По какому вопросу вы пришли?";
				link.l1 = "Простите, кажется, я ошибся и зашёл не туда. Я уже ухожу.";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "Я заш"+GetSexPhrase("ёл","ла")+" по торговым делам. Лицензии, корабельные приборы и прочее...";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "Здравствуйте. Что вам угодно?";
			link.l1 = "Я заш"+GetSexPhrase("ёл","ла")+" по торговым делам. Лицензии, корабельные приборы и прочее...";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "Мне угодно предложить Компании свои услуги. В обмен на золото, конечно.";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "Тогда вам наверх в кабинет, к минхеру Роденбургу. Проходите.";
			link.l1 = "Спасибо, уже иду.";
			link.l1.go = "HWIC_officer_exit";
			// belamour legendary edition переехали по другому адресу
			LocatorReloadEnterDisable("GVIK", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = "В данный момент Компания не нуждается в услугах сторонних капитанов.";
			link.l1 = "Очень жаль. Извините за беспокойство.";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "Вам к минхеру Герритцу. Его стол налево от вас. Он занимается всеми делами с торговыми капитанами.";
			link.l1 = "Спасибо, офицер...";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_exit":
			DialogExit();
			// belamour legendary edition переехали
			LAi_ActorGoToLocation(npchar, "soldiers", "soldier3", "GVIK", "soldiers", "soldier3", "", 5);
			DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
			NextDiag.TempNode = "HWIC_officer";
		break;
		
		// солдаты
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Тревога! Враг в помещении! К оружию!";
				link.l1 = "А-ать!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Ага! Кажется, я тебя знаю... Точно! Ты объявлен"+GetSexPhrase("","а")+" вне закона за преступные деяния! Ребята, хватайте "+GetSexPhrase("его","её")+"!";
				link.l1 = "А-ать!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Поговорите с нашим офицером или с минхером Герритцем. Мне нечего вам сказать. Я на посту.";
			link.l1 = "Хорошо, я понял"+GetSexPhrase("","а")+".";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Тревога! Враг в помещении! Солдаты!";
				link.l1 = "А-ать!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Если вам что-то нужно - поговорите с минхером Герритцем.";
			link.l1 = "Хорошо, я понял"+GetSexPhrase("","а")+".";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Тревога! Враг в помещении! Солдаты, хватайте "+GetSexPhrase("его","её")+"!";
				link.l1 = "А-ать!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Гм. Мне кажется, что не всё тут в порядке... Точно! Вы объявлены в розыск за многочисленные преступления против Голландии! Солдаты, хватайте "+GetSexPhrase("его","её")+"!";
				link.l1 = "А-ать!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Вы что-то хотели, "+GetAddress_Form(NPChar)+"?";
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = "Я хочу приобрести торговую лицензию вашей Компании.";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "Я слышал"+GetSexPhrase("","а")+", что у вас можно приобрести корабельные приборы и прочие полезные вещи. Это так?";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "Что у вас сегодня имеется в продаже? Покажите, пожалуйста.";
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = "У меня есть один занятный документ, минхер. Прочтите его начало. Тут кое-что интересное про Голландию. Если он вас заинтересует - то я его вам отдам, там указаны точные координаты места встречи. Но, конечно, не бесплатно.";
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "У вас работает капитан по имени Реджинальд Джексон. У него шебека с названием 'Гарпия'. Не подскажете, как бы мне встретиться с этим человеком? У меня к нему важное дело.";
				link.l4.go = "caleuche";	
			}
			// Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
			{
				link.l4 = "Мне нужно срочно увидеться с господином Роденбургом. Это крайне важно. Где он?";
				link.l4.go = "PZ_RazgovorGerrits_1";
			}
			link.l9 = "Нет, пока ничего.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "Ну что же, пожалуйста, приобретайте. Но я считаю должным вас предупредить, что наша Компания дорожит своим именем, поэтому к лицензиатам предъявляются определённые требования на весь срок действия лицензии, а именно - никаких агрессивных действий в отношении торговых кораблей любой нации\nВ случае выявления такого факта ваша лицензия будет немедленно аннулирована. Также вы лишитесь документа, если по каким-то причинам, неважно каким, вступите в конфликт с Голландией. Это понятно?";
				link.l1 = "Безусловно. Я приму это к сведению.";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "Ну что же, пожалуйста, приобретайте. На какой срок вы хотите получить лицензию?";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "Лицензия даёт право беспрепятственного входа в любой порт любой нации, поскольку подтверждает ваши мирные намерения и объясняет цель вашего прибытия - торговать. Однако если у вас есть проблемы с законом у той страны, в порт которой вы намерены явиться, лицензия вам не поможет. Более того - у вас её просто изымут. Учтите это\nЕсли вы собираетесь торговать с враждебной вам державой - не забудьте перед входом в порт поднять дружественный флаг - это избавит вас от ненужных проблем, поскольку канониры фортов и патрули в городах имеют склонность сначала стрелять, и только потом разбираться\nДа, чуть не забыл: согласно устоявшейся традиции, оплата за лицензию производится исключительно золотыми дублонами... Ну, теперь, наверное, всё прояснили. На какой срок вы хотите получить лицензию?";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Извините, но мне ещё надо обдумать этот вопрос. Я загляну позже.";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "Минхер, пожалуйста, говорите чётче, не заикайтесь и не мямлите. Я вас плохо расслышал. Так на сколько дней вам нужна лицензия?";
				link.l1 = "Сейчас подумаю...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "Минимальный срок, на который мы выдаём лицензию - двадцать дней. На сколько суток вам выписать - на двадцать, или больше?";
				link.l1 = "Сейчас подумаю...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "Максимальный срок, на который мы выдаём лицензию - полгода. На сколько суток вам выписать - на сто восемьдесят, или меньше?";
				link.l1 = "Сейчас подумаю...";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "На "+FindRussianDaysString(sti(fQty))+"? Хорошо. Стоимость такой лицензии составит "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+". Вас устраивает?";
			if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "Да, конечно, устраивает.";
				link.l1.go = "licence_2";
			}
			link.l2 = "К сожалению, у меня нет сейчас с собой столько денег. Я зайду к вам за лицензией позже.";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Извините, но мне ещё надо обдумать этот вопрос. Я загляну позже.";	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "start")
			{
				if(iQty < 180) 
				{
					Log_info("Квест: 'На пару с Акулой' - срок вашей лицензии менее 180 дней");
				}
				else 
				{
					pchar.questTemp.SharkGoldFleet.LicenceOk = true;
					AddQuestRecord("SharkGoldFleet", "2");
				}
				pchar.questTemp.SharkGoldFleet = "afterGvik";
			}
			dialog.text = "Так, одну минуту... Сейчас поставим подпись и печать... Вот, готово. Получите ваш документ.";
			link.l1 = "Спасибо! До свидания, минхер.";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "Слухи вас не обманули. Здесь вы можете приобрести навигационные приборы, такие как корабельный компас, астролябия, хронометр и песочные часы для настройки хронометра по времени острова Форро. Однако в наличии они бывают не всегда, за исключением разве что песочных часов - разбирают, понимаете ли. Так что если не удалось купить, что хотели - зайдите через недельку\nТакже периодически у нас в продаже появляются карты архипелага и подзорные трубы. Желаете посмотреть ассортимент на сегодня?";
			link.l1 = "Да, будьте так любезны.";
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// депеша Кромвеля
		case "depeshe":
			dialog.text = "Хм, покажите...(читает) Так-так... Значит, Кромвелю мало того, что он устроил в Англии... Вот наглецы! Где вы достали эту депешу?";
			link.l1 = "Перехватил у одного английского курьера. Ну так что, будете её покупать?";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "Да. Питер Стайвесант будет рад её прочесть, я уверен. Как и принять адекватные меры... Я могу заплатить золотом, или выписать вам торговую лицензию на максимальный срок - полгода. Что выбираете?";
			link.l1 = "Я выбираю золото.";
			link.l1.go = "depeshe_dublon";
			link.l2 = "Я хочу торговую лицензию.";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			//Log_Info("Вы получили 700 дублонов");
			dialog.text = "Хорошо. Вот семьсот дублонов. Больше я заплатить вам за эту депешу в любом случае не смогу.";
			link.l1 = "Пожалуйста, забирайте. Вот ваша депеша.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			if (CheckCharacterItem(pchar, "HolTradeLicence")) TakeNationLicence(HOLLAND);
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "Хорошо. Вот ваша лицензия на полгода.";
			link.l1 = "Спасибо! А вот ваша депеша.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "Благодарю. Похвально, что вы проявили сознательность и лояльность по отношению к Голландии. Я сообщу о вашем поступке Матиасу Беку и Питеру Стайвесанту.";
			link.l1 = "Вы уже и так отплатили сполна, но я не возражаю. До свидания!";
			link.l1.go = "exit";
		break;
		
		// Sinistra Путеводная звезда
		case "PZ_RazgovorGerrits_1":
			dialog.text = "Боюсь, что он уже отбыл в Старый Свет вместе с семейством Шнеуров. Кажется, он даже говорил вам об этом.";
			link.l1 = "Верно, говорил. Но я надеялся, что его могли ненадолго задержать какие-нибудь последние дела на Архипелаге. Скажите, Герритц, а не поддерживаете ли вы, ну или ещё кто-либо из Компании, связь с минхером Роденбургом? Посредством почтовых судов или посланников.";
			link.l1.go = "PZ_RazgovorGerrits_2";
		break;
		
		case "PZ_RazgovorGerrits_2":
			dialog.text = "Никак нет - перед своим уходом он попросил нас всех никогда его не беспокоить - сказал, что у него начинается новая жизнь.";
			link.l1 = "Будем надеяться, что и наши с вами жизни станут лучше. До свидания.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Минхер Реджинальд Джексон совершает регулярные перевозки между Порт-Роялем и Филипсбургом. Так что ищите его на этом маршруте. Но я вас хочу предупредить, что если вы затеяли против него что-то недоброе - оставьте это, ибо данный капитан находится под нашей протекцией. Мы поняли друг друга, минхер?";
			link.l1 = "У меня к нему дело совершенно мирного порядка - обычная торговая сделка. Никаких козней против минхера Джексона я строить не намерен, даю слово.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Замечательно. В Порт-Рояле и Филипсбурге минхер Джексон подолгу не задерживается, бывает, только на время погрузочных работ, и снова выходит в рейс. Так что вам проще будет найти его именно в море.";
			link.l1 = "Спасибо за помощь, минхер Герритц.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			pchar.questTemp.Caleuche.Garpiya = "capitan";
			pchar.questTemp.Garpiya = "to_portroyal";
			AddQuestRecord("Caleuche", "19");
			DoQuestFunctionDelay("Caleuche_CreateGarpiyaInWorld", 1.0);
		break;
		
		// новый босс ГВИК
		case "HWIC_Boss":
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if (!CheckAttribute(npchar, "quest.silk_info"))
				{
					if (sti(pchar.reputation.nobility) > 60)
					{
						dialog.text = "А-а, капитан " + GetFullName(pchar) + "! Очень хорошо, что вы ко мне зашли. У меня для вас есть деловое предложение.";
						link.l1 = "Очень занятно! Внимательно вас слушаю, минхер.";
						link.l1.go = "silk_info";
						break;
					}
					else notification("Слишком низкий уровень чести! ("+XI_ConvertString(GetReputationName(61))+")", "None");
				}
			}
			dialog.text = "Здравствуйте, капитан " + GetFullName(pchar) + "! Чем могу служить?";
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
				{
					if (GetDataDay() == 1 || GetDataDay() == 15)
					{
						link.l1 = "Я по поводу корабельного шёлка...";
						link.l1.go = "trade_silk";
					}
				}
			}
			link.l2 = "Добрый день. Нет, ничего не надо - я просто зашёл поприветствовать вас.";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "Я недавно наладил торговые связи с одним купцом из Лиона и договорился о поставках на Карибы партий корабельного шёлка. Вы знаете, что это за товар? Из него изготавливают самые лучшие на свете паруса, так что вам это наверняка будет интересно.";
			link.l1 = "Согласен, это интересное предложение. Каковы условия?";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "Поставки у меня идут регулярно, но в небольших объёмах. Для вас я могу оставлять по тридцать рулонов товара каждые две недели. Стоимость одного рулона - двадцать золотых дублонов. Давайте поступим так: каждого первого и пятнадцатого числа месяца я буду придерживать для вас тридцать рулонов. Если вы не придёте за ними в эти дни - я продаю другому покупателю.";
			link.l1 = "То есть никаких обязательств я не несу?";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "Именно! Хотите - покупаете, хотите - нет. Всю партию оплачиваете полностью - шестьсот дублонов. Надеюсь, вы станете моим постоянным покупателем.";
			link.l1 = "Спасибо за предложение, минхер. Думаю, я обязательно им воспользуюсь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
			AddQuestRecordInfo("Unique_Goods", "3");
		break;
		
		// торговля шелком
		case "trade_silk":
			if (CheckAttribute(pchar, "questTemp.UpgradeSilk"))
			{
				dialog.text = "Конечно, капитан. Шёлк вас дожидается. Готовы его оплатить?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Конечно! Вот, возьмите 2550 дублонов.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Вот незадача, забыл"+GetSexPhrase("","а")+" деньги на корабле. Сейчас принесу!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Конечно, капитан. Шёлк вас дожидается. Готовы его оплатить?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Конечно! Вот, возьмите шесть сотен дублонов.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Вот незадача, забыл"+GetSexPhrase("","а")+" деньги на корабле. Сейчас принесу!";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && !CheckAttribute(pchar, "questTemp.GVIKSilkBlock")) // увеличить объём поставок шёлка
			{
				link.l4 = "Минхер "+npchar.name+", я хотел"+GetSexPhrase("","а")+" бы обсудить возможность увеличения поставок шёлка.";
				link.l4.go = "UpgradeSilk";
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && CheckAttribute(pchar, "questTemp.GVIKSilkPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок шёлка, если в первый раз не принесли
			{
				link.l4 = "Я прин"+GetSexPhrase("ёс","есла")+" ваши дублоны, минхер "+npchar.name+". Извольте получить.";
				link.l4.go = "UpgradeSilk_Agreed";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeSilk")) RemoveDublonsFromPCharTotal(2550);
			else RemoveDublonsFromPCharTotal(600);
			PlaySound("interface\important_item.wav");
			dialog.text = "Приятно иметь с вами дело, капитан. Шёлк будет доставлен баркой к вашему кораблю.";
			link.l1 = "Спасибо!";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "Надеюсь увидеть вас у себя ещё не один раз. Приходите, покупайте.";
			link.l1 = "Обязательно. До встречи!";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.UpgradeSilk")) AddCharacterGoods(pchar, GOOD_SHIPSILK, 150);
			else AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "HWIC_Boss";
			pchar.questTemp.GVIKSilk = sti(pchar.questTemp.GVIKSilk) + 1; // счётчик покупок
		break;
		
		case "UpgradeSilk": //
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Я ценю ваш деловой подход и готов рассмотреть вашу просьбу. Пожалуй, мы могли бы увеличить объём, скажем в пять раз. Однако организация таких поставок потребует значительных ресурсов. Нужно будет расширить складские площади, усилить охрану и обеспечить надёжные пути для доставки. Поскольку это выгодно и вам, я предлагаю разделить между нами эти расходы.";
				link.l1 = "Всё это звучит разумно. Какую сумму вы считаете необходимой для покрытия этих расходов?";
				link.l1.go = "UpgradeSilk_1";
				notification("Проверка пройдена", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Я понимаю ваш интерес к увеличению поставок, однако на данном этапе мне сложно идти на такие изменения. Я не сомневаюсь в вашем стремлении к развитию, но для такого рода сделок требуется гораздо больше опыта в делах торговых и уверенности в собственных действиях. Я предлагаю вам увеличить свои познания в искусстве негоции, а затем вернуться ко мне с более конкретным предложением. Когда вы будете готовы, я буду рад упрочить наше сотрудничество.";
				link.l1 = "Хм... Хорошо. Я вернусь к этому разговору позже.";
				link.l1.go = "exit";
				notification("Недостаточно развит навык (80)", SKILL_COMMERCE);
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_1":
			dialog.text = "Учитывая все нюансы, ваша доля расходов составит - три тысячи золотых дублонов. Эти средства позволят нам без промедлений организовать необходимые меры.";
			link.l1 = "Минхер "+npchar.name+", три тысячи дублонов? Это что, шутка? Я приш"+GetSexPhrase("ёл","ла")+" к вам с честным предложением, а вы хотите, чтобы я заплатил"+GetSexPhrase("","а")+" такую баснословную сумму за организацию поставок?";
			link.l1.go = "UpgradeSilk_2";
		break;
		
		case "UpgradeSilk_2":
			dialog.text = "Прошу вас понять меня правильно. Я не пытаюсь вас обмануть. Эти деньги - это сумма, которая позволит нам обеспечить должный порядок в организации поставок. Речь идёт не только о расширении складов и охране, но и о том, чтобы гарантировать доставку товара без задержек и потерь, несмотря на всю непредсказуемость этого дела. Это стандартные расходы для подобных объёмов. В конечном счёте, ваши вложения оправдают себя, и вы получите товар в надлежащем виде и в срок.";
			link.l1 = "Ваши объяснения немного успокаивают, минхер. Но всё же эта сумма остаётся слишком высокой. Я готов"+GetSexPhrase("","а")+" согласиться на ваши условия, если вы снизите цену хотя бы до двух с половиной тысяч дублонов. Я уверен"+GetSexPhrase("","а")+", что этого будет достаточно для организации поставок и соблюдения всех мер безопасности.";
			link.l1.go = "UpgradeSilk_3";
		break;
		
		case "UpgradeSilk_3":
			dialog.text = "Я понимаю, сумма велика, но, как я уже говорил, она необходима для надлежащего выполнения работы. Я не могу снизить её, так как это поставит под угрозу все наши усилия. Однако, чтобы вы не чувствовали себя обманут"+GetSexPhrase("ым","ой")+", я готов предложить вам скидку в пятнадцать процентов на все будущие поставки. Это, надеюсь, позволит вам компенсировать затраты.";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Хм, скидка в пятнадцать процентов - это, конечно, шаг навстречу. Ладно. Я готов"+GetSexPhrase("","а")+" принять ваше предложение, хоть цена и кажется мне предельно высокой. Надеюсь, наше сотрудничество оправдает мои ожидания. Вот ваши деньги.";
				link.l1.go = "UpgradeSilk_Agreed";
			}
			link.l2 = "Минхер "+npchar.name+", ваше предложение не оставляет мне выбора. Пусть будет три тысячи дублонов, хотя это и немалая сумма. Однако, сейчас я не могу заплатить всё сразу. Я вернусь, как только раздобуду деньги.";
			link.l2.go = "UpgradeSilk_5";
			link.l3 = "Скидка в пятнадцать процентов? Минхер "+npchar.name+", это не то, чего я ожидал"+GetSexPhrase("","а")+". Эта сумма - это не просто расходы, это откровенный и неприкрытый грабёж! Но, я не намерен"+GetSexPhrase("","а")+" разрывать с вами деловые отношения. Мы вернёмся к прежним условиям - 30 рулонов шёлка по 20 дублонов за каждый.";
			link.l3.go = "UpgradeSilk_4";
		break;
		
		case "UpgradeSilk_Agreed":
			dialog.text = "Рад, что вы согласились, "+pchar.name+". Теперь что касается деталей: 150 рулонов шёлка по 17 дублонов за каждый. Итого - 2550 дублонов за всю партию. Забрать товар можно будет как обычно - 1 и 15 числа каждого месяца. Думаю, эта сделка принесёт хорошую прибыль для обеих сторон.";
			link.l1 = "Отлично! Вот это - уже неплохой размах. Всего доброго, минхер. Скоро увидимся.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "3_1");
			pchar.questTemp.UpgradeSilk = true;
			pchar.questTemp.GVIKSilkBlock = true;
			DeleteAttribute(pchar, "questTemp.GVIKSilkPotom");
		break;
		
		case "UpgradeSilk_4":
			dialog.text = "Это всего лишь деловой подход, а вовсе не грабёж, как вам могло показаться. Но, как вам будет угодно. Приходите как обычно, 1 и 15 числа, за партией шёлка, буду рад новой сделке.";
			link.l1 = "Непременно, минхер. Всего доброго.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_5":
			dialog.text = "Рад, что вы приняли правильное решение. Как только вы принесёте деньги, мы с вами обсудим все детали сделки и приступим к её реализации.";
			link.l1 = "До встречи, минхер "+npchar.name+". Увидимся как только соберу нужную сумму.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			pchar.questTemp.GVIKSilkPotom = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("HWIC_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("HWIC_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}