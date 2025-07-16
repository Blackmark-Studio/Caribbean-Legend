// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = "Что вам угодно, месье? Я не общаюсь с незнакомыми мне людьми. А если вы зашли просто поболтать, то я вас разочарую - я не люблю, когда меня беспокоят по пустякам.";
					link.l1 = "Добрый день, месье Фадей. Я, конечно, не знаком вам, но зато вы знаете моего брата. Позвольте представиться - Шарль де Мор, брат Мишеля де Монпе.";
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = "А-а, опять вы, Шарль! Что на этот раз?";
					link.l1 = "Вы сказали, вас обокрали... Воров не нашли?";
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = "Что скажете, Шарль? Сходили посмотреть на это индейское чучело?";
					link.l1 = "Сходил... Поэтому и пришёл снова к вам.";
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = "А, это опять вы, мой дорогой друг! Ну что, принесли дублоны за индейца?";
					if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu80"))
					{
						if (PCharDublonsTotal() >= 80) // belamour legendary edition
						{
							link.l1 = "Да. Вот, держите ваши 80 дублонов.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Нет, я ещё не собрал требуемую сумму.";
							link.l1.go = "exit";
						}
					}
					else
					{
						if (PCharDublonsTotal() >= 100) // belamour legendary edition
						{
							link.l1 = "Да. Вот, держите ваши сто дублонов.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Нет, я ещё не собрал требуемую сумму.";
							link.l1.go = "exit";
						}
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = "Ха, да это сам месье де Мор! Проходите-проходите... Что вас привело в мой дом?";
					link.l1 = TimeGreeting()+", Фадей. Я к вам пришёл по совету моего брата. Он сказал, что вы обязательно сумеете помочь мне найти какую-нибудь работу.";
					link.l1.go = "trial";
					// опоздал
					if (CheckAttribute(pchar, "questTemp.Trial.late")) {
						link.l1.go = "trial_late";
					}
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = "Ха, наш старый добрый знакомый! Какими судьбами, месье де Мор?";
					link.l1 = TimeGreeting()+", Фадей. Мой брат настаивал, чтобы я с вами об этом не беседовал, но я всё-таки не удержался...";
					link.l1.go = "vodka";
					break;
				}
				// belamour legendary edition пиратская линейка -->
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "Baster")
				{
					dialog.text = "А-а, мой старый друг! Проходите, проходите, "+pchar.name+"! Как ваши дела?";
					link.l1 = TimeGreeting()+", Фадей. Рад вас видеть. Собственно, я к вам по делу.";
					link.l1.go = "Slaves";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "FindGold")
				{
					dialog.text = "А, это опять вы, мой дорогой друг! Ну что, нашли дублоны?";
					if(PCharDublonsTotal() >= 150)
					{
						link.l1 = "Пожалуйте, месье Фадей! Вот ваше золото.";
						link.l1.go = "Slaves_2";
					}
					else
					{
						link.l1 = "Нет, просто зашёл. Я ещё в поисках нужной суммы.";
						link.l1.go = "exit";
					}
					
					link.l2 = "Фадей, я, кажется, кое что придумал и мне больше не нужны рабы. Прощу прощения. До встречи!";
					link.l2.go = "Slaves_3";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Baster")
				{
					dialog.text = "А-а, мой старый друг! Проходите-проходите, "+pchar.name+"! Как ваши дела?";
					if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
					{
						if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
						{
							link.l1 = TimeGreeting()+", мне опять нужна Ваша помощь.";
						}
					}
					else
					{
						link.l1 = TimeGreeting()+", Фадей. Рад вас видеть. Собственно, я к вам по делу.";
					}
					link.l1.go = "pistols";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "А, это опять вы, мой дорогой друг! Ну что, нашли деньги?";
					if(PCharDublonsTotal() >= 300)
					{
						link.l1 = "Пожалуйте, месье Фадей! Вот ваши 300 дублонов.";
						link.l1.go = "pistols_4D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Пожалуйте, месье Фадей! Вот ваши 40 000 песо.";
						link.l2.go = "pistols_4P";
					}
					if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) 
					{
						link.l3 = "Нет, просто зашёл. Я ещё в поисках нужной суммы.";
						link.l3.go = "exit";
					}
					link.l4 = "Простите, Фадей, но это мне не по карману. Попробую обойтись своими силами. До встречи!";
					link.l4.go = "pistols_x";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Today")
				{
					dialog.text = "Проходите,проходите, "+pchar.name+"! По глазам вижу, что хотите ведать о моих успехах.";
					link.l1 = "Точно, точно, Фадей. Надеюсь, сможете меня обрадовать?";
					link.l1.go = "pistols_5";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "А, это опять вы, мой дорогой друг! Ну что, нашли деньги?";
					if(PCharDublonsTotal() >= 300)
					{
						link.l1 = "Держите 300 дублонов. Я попрошу матросов отнести этот ящик ко мне корабль. Ох, что бы я без вас делал, Фадей. Вы просто не представляете, как меня выручили?!";
						link.l1.go = "pistols_5D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Держите 40 000 песо. Я попрошу матросов отнести этот ящик ко мне корабль. Ох, что бы я без вас делал, Фадей?! Вы просто не представляете, как меня выручили?!";
						link.l2.go = "pistols_5P";
					}
					if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
					{
						link.l3 = "Нет, просто зашёл. Я ещё в поисках нужной суммы.";
						link.l3.go = "exit";
					}
					link.l4 = "Простите, Фадей, я оказался на мели. Оставьте себе задаток, надеюсь, этим вы компенсируете свои расходы, а я попробую обойтись своими силами. До встречи!";
					link.l4.go = "pistols_x";
					break;
				}
				// <-- legendary edition
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = "А-а, мой старый друг! Проходите-проходите, "+pchar.name+"! Как ваши дела?";
					link.l1 = TimeGreeting()+", Фадей. Рад вас видеть. Собственно, я к вам по делу.";
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Вам, конечно, не терпится узнать результаты моей душеспасительной беседы со священником?";
					link.l1 = "Конечно, не терпится! Как всё прошло?";
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && PCharDublonsTotal() >= 250)
				{
					dialog.text = "Слышу, слышу, как у вас позвякивает в карманах!";
					link.l1 = "Пожалуйте, месье Фадей! Вот ваше золото.";
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = "А-а, мой старый друг! Проходите-проходите, "+pchar.name+"! Как ваши дела?";
					link.l1 = "Здравствуйте, Фадей. Я снова к вам за помощью.";
					link.l1.go = "guardoftruth_14";
					break;
				}
				dialog.text = "Вы что-то хотели, "+pchar.name+"?";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = "Посмотрите, Фадей, что у меня есть. Полагаю, это персидский клинок, и возможно, один из тех, что были украдены из вашего дома?";
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = "Я могу вас порадовать. Вот, у меня есть ещё одна персидская сабля.";
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = "У меня есть третья персидская сабля. Как вы и просили - я немедленно отправился к вам.";
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = "Я по поводу лёгких доспехов, о которых мы говорили.";
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = "Фадей, я хочу прикупить у вас канатов.";
					link.l3.go = "ropes";
				}
				link.l1 = "Фадей, мне нужна ваша помощь.";
				link.l1.go = "help";
 				link.l9 = "Да нет, пока ничего.";
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = "Что вам угодно, "+GetSexPhrase("сударь","барышня")+"? Я не общаюсь с незнакомыми мне людьми.";
				link.l1 = "Да я просто заглянул"+GetSexPhrase("","а")+" посмотреть, кто здесь живёт.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
			dialog.text = "А-а, так вы брат старого доброго Мишеля! Это в корне меняет дело! Проходите-проходите, месье, присаживайтесь. Может, по стаканчику водочки за знакомство? У меня ещё осталось несколько бутылок, и я с радостью разопью одну из них с братом моего друга!";
			link.l1 = "Простите, месье Фадей, но выпивать мне сейчас совсем не с руки. Я бы предпочёл сразу перейти к делам.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Эх, жаль... Ром - ничто по сравнению с русской водкой! Вы не понимаете, от чего отказываетесь. Ладно, раз к делам - так к делам. Слушаю вас, Шарль.";
			link.l1 = "Месье, наверное то, о чём я сейчас скажу, вам не очень понравится, но я вынужден - увы! Мишель мне сообщил, что вы должны ему приличную сумму - карточный долг. Также он распорядился, чтобы вы передали деньги мне, ибо мой брат сейчас... не может лично явиться к вам.";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Ох, молодой человек! Я, безусловно, всё помню и безоговорочно согласен с тем, что должен вашему брату. Карточный долг - святое, это известно каждому дворянину. Но я прошу вас войти в моё положение. У меня здесь недавно случилась пренеприятнейшая история - меня обокрали, обокрали самым наглым образом!\nПроклятые воры вынесли почти всё, что находилось у меня в доме, всё, что я нажил за долгие годы, украли мою бесценную коллекцию, вынесли все мои сбережения! Я просто не в состоянии сейчас погасить долг перед вашим братом деньгами\nНо, месье де Мор, я ни в коем случае не отказываюсь от своих обязательств! Я просто прошу вас пойти мне навстречу. Поскольку денег у меня сейчас всё равно нет, я предлагаю вам в качестве оплаты долга вот этот великолепный раритетный кинжал. Взгляните на него!\nЭто произведение оружейного искусства, гордость моей бывшей коллекции. Кроме того, он заговорён индейскими шаманами и обладает очень сильными скрытыми свойствами. От индейцев он получил название 'Коготь вождя'\nЯ бы ни за что не согласился отдать его, поскольку я купил его за немалую сумму, намного превышающую размер моего долга, но учитывая обстоятельства, готов отдать его вам. Берите, это очень выгодная для вас сделка!";
			link.l1 = "Хм... Я предпочёл бы деньги...";
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = "Но у меня действительно их нет. Неужели вы думаете, сударь, что я предложил бы вам этот великолепный заговорённый кинжал вместо каких-то жалких монет, не окажись я в безвыходном положении? Да у меня сердце кровью обливается, когда я слышу свои слова! Но карточный долг - долг чести, поэтому я готов расстаться ради этого с дорогой для меня вещью.";
			link.l1 = "Ладно, я согласен. Раз у вас всё равно нет денег, то я возьму хотя бы этот ваш хвалёный кинжал. Надеюсь, я смогу выручить за него приличную сумму...";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "'Хотя бы!' Нет, это просто невероятно! Я отдаю свой лучший экземпляр, за который в Европе я бы получил вдесятеро больше против своего долга, а вы говорите - 'хотя бы'! Этот кинжал, молодой человек, если хотите знать, спас жизнь не одному человеку! И он...";
			link.l1 = "И в чём же его скрытая сила, о которой вы упомянули?";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Ох, сударь! Я ведь всё-таки христианин, а не индейский шаман, и не могу знать всех скрытых свойств этого клинка. Но они есть, уверяю вас. Возьмите кинжал в руку - и вы сами почувствуете это! Возьмите-возьмите! Вот так! Ничего не ощущаете?";
			link.l1 = "Гм... Нет. Хотя в руке лежит он очень удобно, ничего не скажешь...";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Вот! Но это лишь малая часть его достоинств. Если вы примените этот кинжал в бою - я уверен, он проявит свою мощь на всю катушку!.. Ну так что, берёте?";
			link.l1 = "А у меня есть выбор? Беру, раз так неудачно у вас с деньгами вышло...";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			//Log_Info("Вы получили дагу 'Коготь вождя'");
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddMapQuestMarkCity("FortFrance", false);
			dialog.text = "Разумное решение, сударь. Вы не пожалеете об этом! Вот, держите. И обязательно передайте привет Мишелю! Скажите, что я жду его в гости, как только у него появится такая возможность.";
			link.l1 = "Передам, не сомневайтесь...";
			link.l1.go = "exit";
			link.l2 = "Вы сказали, вас обокрали... Воров так и не нашли?";
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2";
			
			// Sinistra - Старт квеста "Деньги на деревьях"
			PChar.quest.MOT_BarbieSpawn.win_condition.l1 = "location";
			PChar.quest.MOT_BarbieSpawn.win_condition.l1.location = "BasTer_town";
			PChar.quest.MOT_BarbieSpawn.win_condition = "MOT_BarbieSpawn";
			//убрать запрет боёвок на Мартинике
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload2", false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload3", false);
			sld = &Locations[FindLocation("FortFrance_prison")];
			sld.locators_radius.item.detector1 = 0.5;
		break;
		
		case "Sharlie_8":
			dialog.text = "Вы представляете - нет. Негодяи обчистили весь мой дом, унесли всё серебро, золото, мои сбережения, нажитые годами и непосильным трудом, но самое ужасное - они стащили мою великолепную коллекцию восточных клинков! Такой на всех Карибах ни у кого не было. Очень, очень хорошие персидские сабли...";
			link.l1 = "Восточные клинки, говорите? Весьма презанятно. Так вы - коллекционер?";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Ну, мне нравится собирать редкие вещи... Послушайте, Шарль, может, вы сможете мне помочь в этом вопросе с клинками...";
			link.l1 = "Помочь? Но чем? Поймать воров, что ли?";
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = "Отнюдь. Воры меня мало интересуют. Мне бы хотелось, чтобы мои персидские сабли вернулись ко мне назад. Если сможете их найти - я в долгу не останусь, обещаю.";
			link.l1 = "Хм. Но где же их искать-то? По всем Карибам? Или, быть может, уже по всему свету?";
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Ну, может случайно встретите где на островах, у какого-нибудь уличного торговца - негодяи даже не представляли себе ценности этих сабель и наверняка продали за бесценок. Так что если где увидите персидские клинки - привозите мне. Сможете их опознать?";
			link.l1 = "Думаю, да. Хорошо, я буду внимательно смотреть по сторонам - если встречу что-то похожее - обязательно привезу вам.";
			link.l1.go = "Sharlie_12";
			link.l2 = "Знаете, я не эксперт в холодном оружии. Боюсь, я не смогу вам помочь. Так что будет нечестным с моей стороны напрасно обнадёживать вас.";
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = "Вот и отлично! Я надеюсь, удача улыбнётся вам. А я в долгу не останусь. Да, вы знаете, Шарль, эта кража - ещё не всё. Буквально на днях - представляете, ко мне снова залез воришка\nНу это уж слишком! Но тут он от меня не ушёл: я поймал его, задал хорошую взбучку и сдал коменданту. Думаю, его скоро повесят. И поделом ему!";
			link.l1 = "Вы думаете, он из тех, кто вынес ваши сабли?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = "Жаль, конечно. Но на нет - и суда, как говорится, нет. Да, вы знаете, Шарль, эта кража - ещё не всё. Буквально на днях - представляете, ко мне снова залез воришка\nНу это уж слишком! Но тут он от меня не ушёл: я поймал его, задал хорошую взбучку и сдал коменданту. Думаю, его скоро повесят. И поделом ему!";
			link.l1 = "Вы думаете, он из тех, кто вынес ваши сабли?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = "Нет, не думаю. Его интересовали только монеты. Такое, представляете, чучело залезло ко мне в комнату и шарилось по сундукам\nИндеец из каких-то глухих джунглей, просто чудо. Весь в наряде, раскрашенный... Можете сходить в наши казематы и посмотреть на этого шута ряженого, если вам интересно, пока он ещё жив.";
			link.l1 = "Хм... Может, и загляну.";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Сходите-сходите, посмотрите на местные ходячие диковины... Ладно, Шарль, приятно поговорили - вы же сейчас назад, на Мартинику? Желаю вам счастливого пути.";
			link.l1 = "Всего доброго, Фадей.";
			link.l1.go = "exit";
			SetQuestHeader("Tichingitu");
			AddQuestRecord("Tichingitu", "1");
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("SetTichingituJail");
			SetFunctionTimerCondition("FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Очень интересно! Ну, слушаю вас.";
			link.l1 = "Фадей, я говорил с этим индейцем. И я пришёл просить вас за него. Этот несчастный просто хотел есть...";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Ха-ха-ха, и вы поверили в эти сказки? Молодёжь-молодёжь...";
			link.l1 = "Фадей, я, конечно, моложе вас, но даже я в состоянии отличить, когда мне говорят правду, а когда лгут. К тому же вы не считаете, что повешение - не совсем адекватное наказание за его преступление?";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "А даже если и так? Этот негодяй залез в мой дом! Вот вы, что бы вы сделали? Уверен - просто проткнули бы его шпагой. Не так ли?";
			link.l1 = "Нет, не так. Фадей, я уверен, вы просто в ярости за свою похищенную коллекцию сабель. Не случись этого - вы бы просто выпороли этого краснокожего и выставили пинком под зад. Я не прав?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Эх, Шарль... Вы такой же, как и ваш брат... Ладно. Поступим по-деловому. Раз вам так нужен этот индеец - компенсируйте мне моральную неустойку за него и я напишу просьбу о помиловании, которую, конечно же, удовлетворят. Идёт?";
			link.l1 = "Сколько?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ха, вы уже начинаете кое-что понимать в жизни на Карибах, Шарль. Сто пятьдесят золотых дублонов.";
			link.l1 = "Фадей, побойтесь Бога...";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Хорошо-хорошо, сто золотых дублонов. Но это последняя цена. Причём именно дублоны, а не песо. У нашего ростовщика наверняка найдётся некоторое количество.";
			if(PCharDublonsTotal() >= 100) // belamour legendary edition
			{
				link.l1 = "У меня есть нужное количество прямо сейчас. Вот, держите ваши сто дублонов.";
				link.l1.go = "Tichingitu_7";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Вызывающий доверие", "Trustworthy");
				link.l2 = "(Вызывающий доверие) Фадей, я - единственный, кто вообще может вам этот инцидент компенсировать звонкой монетой.";
				link.l2.go = "Tichingitu_7_TW";
			}
			else notification("Не открыта способность", "Trustworthy");
			link.l3 = "Хорошо, я принесу то, что вы требуете.";
			link.l3.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_7_TW":
			dialog.text = "Ох, далеко пойдёте, мой друг. Уговорили! Восемьдесят золотых - и ни монетой меньше!";
			link.l1 = "";
			link.l1.go = "Tichingitu_6";
			pchar.questTemp.Sharlie.Tichingitu80 = true;
		break;
		
		case "Tichingitu_6":
			dialog.text = "И поторопитесь, Шарль! Дней через десять они уже не понадобятся...";
			link.l1 = "Приму к сведению. До свидания!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			if(CheckAttribute(pchar,"questTemp.Sharlie.Tichingitu80"))
			{
				RemoveDublonsFromPCharTotal(80);
				DeleteAttribute(pchar,"questTemp.Sharlie.Tichingitu80");
			}
			else RemoveDublonsFromPCharTotal(100); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Отлично! Вот это дело! Сейчас я напишу записку и приложу свою печать, подождите немного... вот, держите. Отдайте это коменданту и можете забирать своего индейца. Вот только зачем он вам понадобился - ума не приложу. Разве что на ярмарках за деньги показывать, ха-ха!";
			link.l1 = "Бог всё видит, Фадей. Спасти жизнь человеку - благое дело.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = "Это спорный вопрос, Шарль. А если вы спасаете убийцу или насильника? Впрочем, ступайте к коменданту, пока вашего краснокожего друга не вздёрнули на виселицу...";
			link.l1 = "Уже иду. Ещё увидимся, Фадей.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
			SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
			QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		break;
		
		case "vodka":
			dialog.text = "Что вы такое говорите! Глядя на ваше суровое лицо, я понимаю, что вы хотите поведать мне что-то неприятное?";
			link.l1 = "Ну, вроде того. Буду откровенным: Мишель сказал, что вы меня с этим кинжалом, 'когтем вождя', попросту надули, что это обычный хлам, который можно купить у уличного торговца за пару сотен песо. Я, кстати, поспрашивал о его цене у лоточников, торгующих железяками. Именно такую цену они и назвали.";
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = "Ох, месье де Мор... Ваш брат меня, право, удивил. Ладно - эти полуграмотные торгаши, но он, он! Вот скажите, Шарль, если бы вам кто-нибудь принёс старый двуручный рыцарский меч времён короля Артура и предложил купить, сколько бы вы за него заплатили?";
			link.l1 = "Двуручный меч? Вы издеваетесь? Да зачем мне этот лом? У нас сейчас, слава Богу, на дворе семнадцатый век! Нисколько бы я за него не дал, ни песо.";
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = "Вот видите! А принесите мне такой меч - и я заплачу вам за него три сотни дублонов. Спросите, почему? Да потому что вы его в семнадцатом веке днём с огнём не сыщете, это древняя вещь, раритет, редкость! Вы ничего не понимаете, а берётесь судить!\n'Коготь вождя' - такой же замечательный кинжал, знающие люди говорили, что он принадлежал самому Кортесу. Кортесу! Тому самому, который покорил Теночтитлан! А вы - хлам, хлам!\nКроме того, как я уже говорил, он не простой, он заговорённый! Вы ещё слишком мало пробыли на Карибах, чтобы понять, какую роль здесь играют разного рода колдовские заклятия, наветы и заговоры! Шарль, здесь - Новый Свет, здесь родина майя и ацтеков - индейских племён, чьи познания магии и потустороннего мира достигли прямо-таки потрясающих величин!\nЭтот кинжал действительно имеет скрытые способности, просто никто из ныне живущих не знает, к сожалению, какие. Вам выпала потрясающая, уникальная возможность исследовать это - а вы называете сию великолепную вещь хламом!\nДа будь у меня сейчас достаточная сумма для покрытия долга вашему брату - я бы немедленно забрал у вас эту дагу назад взамен на презренный металл... Это очень дорогая вещь, и ценность её измеряется не деньгами.";
			link.l1 = "Ладно-ладно, Фадей, я верю вам. Ваши доводы вполне убедительны, а тот пыл, с которым вы всё это рассказали, свидетельствует об искренности ваших слов.";
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = "Вот! Как хорошо сказано! Вы молодец, Шарль, что не стали таить обиду и сразу пришли ко мне за разъяснениями. Надеюсь, теперь инцидент исчерпан?";
			link.l1 = "Да, месье Фадей. Полностью. Ну а теперь разрешите откланяться...";
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\Russian\sharlie\Fadey Moskovit-04.wav");
			dialog.text = "Постойте, Шарль! Скажу честно: вы мне нравитесь. Возможно, мы даже когда-нибудь станем с вами друзьями. И я предлагаю сделать первый шаг в этом направлении. Я только-только охладил в погребке в ключевой воде две бутылочки отличной русской водки. Предлагаю распить их за наше знакомство и за здоровье вашего брата.";
			link.l1 = "Хм. Извините, месье Фадей, но мне уже пора выходить в море. Я действительно тороплюсь!";
			link.l1.go = "vodka_no";
			link.l2 = "Вы в прошлый раз предлагали, я отказался... Будет невежливо отказать ещё раз. Я согласен, Фадей, давайте выпьем за знакомство!";
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = "Ну и зря. Ром по сравнению с водкой - поганое дешёвое пойло. Но раз спешите - не буду задерживать. Удачи, Шарль!";
			link.l1 = "И вам того же, месье Фадей...";
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = "Ай, молодца! Вот и славненько! Посидим, побеседуем о жизни! Присаживайтесь, присаживайтесь, месье, а я сейчас принесу водочку. Ох, какая же она будет вкусная, холодненькая!..";
			link.l1 = "...";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = "Ох... В-вот-т, скажите м-мне, Фадей, н-ну, как так п-получается? Ик! Мы выпили с вами... д-две бут-тылочки в-водочки... кстати - отличная вещь! - и у вас ни в од-дном глаз-зу, а я.. пьян, к-как сапожник? А?";
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = "Шарль, ну вы же расслабляетесь, отдыхаете. Причём тут - как сапожник? Водочка у меня отличная, поспите немного - и будете как стеклышко, даже голова болеть не будет. Вот увидите.";
			link.l1 = "Д-да, водочка... это... это просто великолепная она, ваша водочка. Сроду такого не пил.";
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = "Ха! Ещё бы! Такую водочку делают только у нас, в России, и то не все умеют правильно. Я беру только самую лучшую. Вот, как эту, которую мы с вами изволили откушать.";
			link.l1 = "А в-вот, скаж-жите, Фадей: а вот как м-можно пить - и не напиваться? Как в-вы? А? П-поделитесь секретом - м-может, мне это п-пригодится потом... Ик!";
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = "Ха! Ну вы не сравнивайте месье, себя и меня - гляньте, какой вы стройный, что тот хлыст. Да и привычки у вас нет. Ну да ладно, расскажу я вам несколько секретов, чтобы пить да поменьше напиваться.";
			link.l1 = "Б-будьте т-так любезны... ик! месье Фадей...";
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = "Ну, чтобы пить, да не напиться, надо соблюдать несколько правил. Главное - никогда не пейте на пустой желудок. Ежели вам предстоит возлияние и вы не хотите упасть лицом в стол - предварительно откушайте хорошенько, доброй пищи\nВторое - когда пьёте, не забывайте закусывать после каждой чарки. Закусывайте доброю едою, лучше мясом, или рыбою. Чем плотнее закуска - тем меньше вас одержит хмель. Третье - не полощите рот выпивкою - глотайте сразу\nТакже если вы знаете, что вам предстоит возлияние и вам негоже остаться пьяным - загодя сделайте небольшое принятие напитка, подготовьте ваше бренное тело к приёму больших количеств алкоголя, но не более половины пинты. Остерегайтесь переборщить, ибо эффект получите совершенно оборотный\nНу, и если вы будете постоянно принимать умеренные количества рому аль иного алкоголю - сие настроит ваш организм устойчивей к выпивке, нежели абсолютное воздержание, ибо тренировка надобна во всяком деле.";
			link.l1 = "Э-м-м... В-вот оно к-как! Я обяз-зательно... ик!.. запомню все ваши н-наставления, Фадей. С-спасибо. А теперь м-мне было бы неплохо в-выспаться, а то штормит м-меня что-то сегодня.";
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = "Отдохните, Шарль. Славно мы с вами сегодня посидели! Удачи вам и до встречи!";
			link.l1 = "Д-до с-свидания, Фадей!";
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = "Что, прямо так и сказал - что обязательно помогу?";
			link.l1 = "Ну, примерно так. А разве вы не окажете помощь брату вашего старинного друга? Я же не прошу у вас денег, я прошу предоставить возможность их заработать.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_late":
			dialog.text = "Ох, Шарль! Опоздали вы. Пришли бы пораньше, нашёл бы для вас дело верное, а сейчас - прошу простить. Не переживайте, походите по городам, пообщайтесь с людьми. Работы у нас на Карибах много.";
			link.l1 = "Ясно. Жаль, конечно. До свидания!";
			link.l1.go = "trial_late_1";
		break;
		
		case "trial_late_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Trial");
		break;
		
		case "trial_1":
			dialog.text = "Хм. Нет, не откажу, конечно. Хочешь накормить человека - не давай ему рыбу, а дай удочку, так, месье де Мор? Значит, вам нужна работа... Хорошо. Я поговорю с одним человеком и рекомендую ему вас. Ну, а остальное будет зависеть только от вашей исполнительности.";
			link.l1 = "Прекрасно. И к кому же мне обратиться?";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Приходите завтра в магазин нашей колонии. Вас там будет ждать человек по имени Жерар Лекруа. От него вы и получите поручение. Он пробудет в нашей колонии только до завтрашнего вечера, так что если не встретитесь с ним завтра - считайте, что свой шанс вы упустили. Надеюсь, вы будете пунктуальны и исполнительны, и не поставите меня в неловкое положение.";
			link.l1 = "Приму к сведению. Спасибо, Фадей! Непременно приду на встречу с месье Лекруа.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		// belamour legendary edition пиратская линейка -->
		case "Slaves":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Чем я могу вам помочь, мил человек?";
			link.l1 = "Фадей, послушайте, мне очень необходимо приобрести полсотни рабов у контрабандистов. Без вас они даже слушать меня не станут, а это вопрос жизни и смерти одного важного человека.";
			link.l1.go = "Slaves_1";
		break;
		
		case "Slaves_1":
			dialog.text = "Коли так, то это благое дело, я помогу вам, дорогой друг. Но как известно, потребуется 150 золотых дублонов для убеждения ваших благих намерений по покупке товара и, конечно, немного за хлопоты мои усердные...";
			if(PCharDublonsTotal() >= 150)
			{
				link.l1 = "Пожалуйте, месье Фадей! Вот ваше золото.";
				link.l1.go = "Slaves_2";
			}
			else
			{
				link.l1 = "Я немедленно отправляюсь к ростовщику! Ждите, месье Фадей, одна нога здесь, другая там!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.GiveMeSlaves = "FindGold"; 
			}
			
			link.l2 = "Фадей, я, кажется, кое-что придумал и мне больше не нужны рабы. Прощу прощения. До встречи!";
			link.l2.go = "Slaves_3";
		break;
		
		case "Slaves_2":
			RemoveDublonsFromPCharTotal(150);
			pchar.questTemp.Mtraxx.GiveMeSlaves = "kapster";
			locations[FindLocation("Shore29")].DisableEncounters = true; //энкаутеры закрыть
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1 = "Hour";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.start.hour = 22.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.finish.hour = 23.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3 = "location";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3.location = "Shore29";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.function = "MtraxxGiveMeSlavesKapsterInShore"; // прибыли
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.hour  = 23.0; // не пришли, значит гудбай
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.function = "MtraxxGiveMeSlavesKapsterInShoreLate"; // опоздание
			AddQuestRecord("Roger_3", "23");
			dialog.text = "Превосходно, друже. Но ежели вы меня захотели провести с надобностью вашей покупки и она для негожих целей, я буду весьма огорчен вами. Завтра часов так в десять к закату на пляже Капстер я организую вам встречу, не поставьте меня в неловкое положение.";
			link.l1 = "Спасибо, Фадей! Непременно прибуду за товаром.";
			link.l1.go = "exit";
		break;
		
		case "Slaves_3":
			DialogExit();
			AddQuestRecord("Roger_3", "22");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		break;
		
		case "pistols":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Рассказывай, добрый молодец, какие нужды привели тебя в мой скромный дом?";
			link.l1 = "Мне нужно кое-что из боевого арсенала. Местные торговцы не смогут найти того объёма, который мне необходим, а вот вы, я думаю, мне сможете чем нибудь помочь.";
			link.l1.go = "pistols_1";
		break;
		
		case "pistols_1":
			dialog.text = "Вы для начала скажите, дорогой друг, что конкретно от меня требуется. А я уже прикину и точно отвечу, смогу ли вам подсобить.";
			link.l1 = "Хорошо. Мне нужно 30 строевых пистолей, два фитильных мушкета, 70 зарядов к ним и 90 лечебных зелий.";
			link.l1.go = "pistols_2";
		break;
		
		case "pistols_2":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
			{
				if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
				{
					dialog.text = pchar.name + ", вы меня пугаете. Сначала полсотни рабов, затем оружие. Вы восстание хотите поднять, друг мой?";
					link.l1 = "Вы очень проницательны, Фадей. Как я и говорил ранее, все это нужно для спасения одного важного человека. Не переживайте, его следует вырвать из лап враждебной Испании, так что ваша репутация точно не пострадает.";
					link.l1.go = "pistols_3";
					break;
				}
			}
			dialog.text = "Добро! Я помогу, чем смогу.";
			link.l1 = "Я рад это слышать. Сколько с меня?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_3":
			dialog.text = "Добро, добро, что не стали увиливать. И ежели взаправду у наших недругов, то я вам помогу. Но коли окажется, что вы меня одурачили, то я буду сильно огорчен.";
			link.l1 = "Во мне можете быть уверены, Фадей. Сколько с меня?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_4":
			dialog.text = "Так, так... Строевые пистоли и пара мушкетов, стало быть... Обещать, что в полном объёме вашу нужду исполню, не буду, но сделаю всё, что в моих силах. А пока что мне нужен задаток в размере 40 000 песо, а ежели дублоны водятся, то 300 штук этих полновесных монет.";
			if(PCharDublonsTotal() >= 300)
			{
				link.l1 = "Держите дублоны, Фадей. Так намного выгоднее.";
				link.l1.go = "pistols_4D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Перевелись все дублоны у меня, возьмите песо, Фадей.";
				link.l2.go = "pistols_4P";
			}
			if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Мне нужно отлучиться к своему казначею. Я пулей! И глазом моргнуть не успеете.";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Простите, Фадей, но это мне не по карману. Попробую обойтись своими силами. До встречи!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_4D":
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Приходите завтра, "+pchar.name+", а я похлопочу за нужный вам товар.";
			link.l1 = "Тогда не буду мешать. До завтра!";
			link.l1.go = "exit";
		break;
		
		case "pistols_4P":
			AddMoneyToCharacter(pchar, -40000);
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
            pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Приходите завтра, "+pchar.name+", а я похлопочу за нужный вам товар.";
			link.l1 = "Тогда не буду мешать. До завтра!";
			link.l1.go = "exit";
		break;
		
		case "pistols_X":
			DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
		break;
		
		case "pistols_5":
			dialog.text = "Иначе и быть не могло, молодой человек. Мне сдюжило найти всё, что вы просили. Поэтому дело за малым - за оплатой родненькой. Передайте мне ещё ровно столько, сколько давали задатком, и забирайте свой ящик с оружием.";
			if(PCharDublonsTotal() >= 300)
			{
				link.l1 = "Держите 300 дублонов. Я попрошу матросов отнести этот ящик ко мне корабль. Ох, что бы я без вас делал, Фадей?! Вы просто не представляете, как меня выручили!";
				link.l1.go = "pistols_5D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Держите 40 000 песо. Я попрошу матросов отнести этот ящик ко мне корабль. Ох, что бы я без вас делал, Фадей?! Вы просто не представляете, как меня выручили!";
				link.l2.go = "pistols_5P";
			}
			if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Ну, вот как можно быть таким нерасторопным и забыть деньги. Я скоро вернусь.";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Простите, Фадей, я оказался на мели. Оставьте себе задаток, надеюсь, этим вы компенсируете свои расходы, а я попробую обойтись своими силами. До встречи!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_5D":
			Log_Info("Сундук Фадея погружен на корабль");
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Помогать нуждающимся - это дело чести. Будете в Бас-Тере, добрый молодец - обязательно навестите поздороваться.";
			link.l1 = "Это даже немыслимо - побывать в Бас-Тере и не заглянуть к Фадею. Всего доброго!";
			link.l1.go = "exit";
		break;
		
		case "pistols_5P":
			Log_Info("Сундук Фадея погружен на корабль");
			AddMoneyToCharacter(pchar, -40000);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Помогать нуждающимся - это дело чести. Будете в Бас-Тере, добрый молодец - обязательно навестите поздороваться.";
			link.l1 = "Это даже немыслимо - побывать в Бас-Тере и не заглянуть к Фадею. Всего доброго!";
			link.l1.go = "exit";
		break;
		// <-- legendary edition
		
		case "guardoftruth":
			dialog.text = "Ну кто бы сумневался, что вы по делу, мой друг! Водочки не предлагаю - нет её, родимой, у меня нонче. Рассказывайте, что за невзгода с вами приключилась.";
			link.l1 = "Местному приходу один капер подарил за отпущение грехов наперсный золотой крест с лазуритом. Уникальная и дорогая вещь. Беда в том, что этот крест был похищен из другого прихода. Причём при грабеже был убит священник.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Да что же вы такое говорите!";
			link.l1 = "Именно так. Я в данный момент представляю интересы верующих ограбленного прихода и пытаюсь вернуть эту вещь на её законное место.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Благородное занятие, и богоугодное...";
			link.l1 = "Но святой отец отказывается мне её возвращать, несмотря на все мои доводы. Я не понимаю, как можно спокойно использовать в своём приходе вещь, которая была украдена и окроплена кровью несчастного священнослужителя? Это же фактически кощунство!";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Вы, как я понимаю, хотите, чтобы я помог вам вернуть этот крест?";
			link.l1 = "Именно! Вы в большом авторитете в Бас-Тере, вас уважают, и, возможно, святой отец прислушается к вашим увещеваниям?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+", вы рассказали историю этого креста нашему священнику?";
			link.l1 = "Конечно! Я взывал к его религиозным чувствам, к христианской солидарности, к совести, в конце концов - но он остался глух к моим доводам.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Кхм... А другие способы убеждения вы не пытались применить?";
			link.l1 = "Вы имеете в виду - подкуп? Нет... Если бы это был ростовщик, или купец, или даже губернатор - я бы попытался решить вопрос таким путём, но священник!";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Дорогой друг, если уши священника оказываются глухи к воззваниям к совести, то тогда наверняка его руки открыты для золота... И наоборот. Я помогу вам, ибо присутствие вещи, добытой кровавым путём, в нашем приходе я считаю недопустимым. Однако это потребует некоторых расходов."
			link.l1 = "Я не удивлён. Сколько?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Приходите завтра, "+pchar.name+", ибо я пока и сам не ведаю. Но вы получите свою вещь, можете быть уверены.";
			link.l1 = "Спасибо, Фадей! Тогда не буду вам мешать. До завтра!";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = "Так, как я и предполагал. Крест у меня, "+pchar.name+", а подробности... да и Бог с ними, с этими пустяками и суетой!";
			link.l1 = "Сколько я вам должен?";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Двести пятьдесят дублонов. Это на покрытие моих расходов, ну и, конечно, немного за труды мои праведные...";
			if(PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Пожалуйте, месье Фадей! Вот ваше золото.";
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = "Я немедленно их принесу!";
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = "Очень хорошо. А вот и ваш крест с лазуритом!";
			link.l1 = "Спасибо, Фадей. Вы даже не представляете, как мне помогли!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			GiveItem2Character(pchar, "jewelry34");
			//Log_Info("Вы получили золотой крест с лазуритом");
			PlaySound("interface\important_item.wav");
			dialog.text = "Для доброго, и главное - щедрого друга, я всегда готов расстараться. Заглядывайте почаще, может, выпьем водочки, когда мне её привезут из-за океана.";
			link.l1 = "Удачи!";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = "Доброму молодцу грех отказывать! Излагай, какие невзгоды на сей раз привели тебя ко мне.";
			link.l1 = "Невзгоды, или не невзгоды, а привели. Фадей, в наш первый день знакомства вы дали мне раритетный кинжал - дагу 'Коготь вождя'. Теперь я знаю, что она до этого принадлежала человеку по имени Арчибальд Колхаун. Я вас прошу - расскажите мне о нём то, что вам известно.";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "От вас ничего не утаишь, "+pchar.name+". Вы такой же проницательный, как и ваш брат. Да, я выиграл эту дагу в кости у старины Арчибальда. Кто он такой? Да я и сам толком не ведаю. Познакомились мы случайно, разговорились, выпили немного, он поведал о грехах своих тяжких...";
			link.l1 = "О каких грехах?";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Жалился Арчибальд, что через него некоего человека в инквизиции до смерти запытали. И что до этого погубил он душ невинных. Всё сравнивал себя, сердешный, с Иудой Искариотом, что продался за тридцать сребренников. И что за тот грех несёт он теперь наказание - сама инквизиция идёт за ним по пятам\nГоворил, что инквизитор гишпанский, отец Винсенто, погибели его желает, за то что ведает он дюже немало, и что наймиты гишпанские преследуют его повсеместно. А потом хмель всё более одолел им, тут мы и сыграли в кости на кинжал этот старинный.";
			link.l1 = "И всё? Потом вы больше его не видели?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Дык сгинул Арчибальд, в пучине морской! Потопили пираты окаянные его флейт, а всю команду смерти предали. И ведь поговаривали, что не пираты то были, а гишпанцы в босяков переодетые... с инквизицией, "+pchar.name+", плохи шутки.";
			link.l1 = "Арчибальд Колхаун жив. Я недавно видел его в компании некоего Вильяма Патерсона. Он у него служит первым помощником.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "О как оно бывает! А я и ведать не ведал! Ну, под крылом капитана Патерсона Арчибальд может вольно дышать, аки у Христа за пазухой. Гишпанцы боятся Патерсона пуще огня, и не осмелятся более чинить козни.";
			link.l1 = "Вы знаете Патерсона?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "А как же, друг мой. Кто же не знает сего знатного мужа! Он, как и вы, прибыл на архипелаг недавно, но уже сколотил себе славу недюжинную. Господин Патерсон - первый друг полковника Фокса, и вхож к самому лорду Виндзору, генерал-губернатору всех англицких поселений. Он частенько захаживает в Порт-Рояль в дворец губернаторский.";
			link.l1 = "Ясно. Ну что же, спасибо за рассказ, Фадей!";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Дык не за что, добрый молодец. Захаживай ещё в гости!";
			link.l1 = "Обязательно!";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = "Давайте посмотрим, "+pchar.name+"... Точно, это один из них! Где вы отыскали его, друг мой?";
			link.l1 = "Это не столь важно. Важно то, что он может снова вернуться к вам.";
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = "То есть вы хотите сказать, что можете не отдать его мне? Полноте, друг мой! Я хорошо оплачу труды ваши тяжкие. Три сотни золотых дублонов - достойная награда за ваше усердие...";
			link.l1 = "Фадей, ваше благое расположение ко мне намного дороже этих трёхсот дублонов. Хотя от них я, конечно, не откажусь. Держите вашу саблю.";
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = "Вот спасибо, добрый молодец! Вот спасибо! И за клинок сей, и за слова разумные. Вы дюже умны не по годам, "+pchar.name+", ибо глаголите истину - важней золота узы дружбы человеческой. Но и про него, родимое, забывать не моги - вот, держите ваши дублоны.";
			link.l1 = "Спасибо!";
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("Вы получили 300 дублонов");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "А теперь об узах дружбы, а именно - нашей с вами, "+pchar.name+". У меня есть нечто, что обязательно заинтересует вас.";
			link.l1 = "Неужто речь пойдёт про водочку?";
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = "Водочка - это дело дюже хорошее, но моя родная сторона славится не только одной ею. Есть один товар, который делают только у нас, в России, и который я привожу сюда для негоции. Сей товар интересен любому капитану, ибо являет собой часть корабля. Я говорю о пеньковых канатах\nЭти канаты делаются из волокон конопляных, на прядильнях, руками умелых мастеровых. Они не боятся ни влаги, ни соли морской, и посему имеют таки огромный спрос у корабельных дел мастеров. Как говорят - лучшего материала для оснастки нет на свете\nЕжемесячно купеческие суда доставляют мне сюда небольшую партию канатов этих. Обычно к середине каждого месяца мой склад пополняется на сотню-полторы бухт. Так вот, я предлагаю вам, "+pchar.name+", покупать их у меня в количестве пятьдесят бухт за один присест. Стоимость одной бухты - десять золотых дублонов\nУсловий у меня всего два: я придерживаю канаты ваши до двадцатого числа каждого месяца - раз, вы покупаете всю партию в пятьдесят бухт целиком - два. Вы мне полтыщи золотых - я вам канаты. Скажу вам по секрету, "+pchar.name+": говорят, есть места, где можно перепродать сей товар дороже, но вот беда - я не ведаю, где и кому\nОднако, меня и нонешнее положение дел устраивает полностью. А ежели вы отыщете доброго купца - то сможете иметь выгоду немалую.";
			link.l1 = "Ясно. Отличное предложение, Фадей! Думаю, буду пользоваться предоставленной возможностью. Итак, каждого двадцатого числа месяца пятьсот дублонов за полсотни бухт?";
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecordInfo("Unique_Goods", "2");
			dialog.text = "Именно так. Захаживайте за покупкой. Но погодите, погодите, мил человек! Окромя этого клинка, коий вы с истинным великодушием вернули мне, было ещё два. Очень прошу, будьте так любезны: коли отыщете их где - сразу привозите, я сполна рассчитаюсь.";
			link.l1 = "Обязательно, Фадей. Если попадутся - обязательно привезу.";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Я могу вас порадовать. Вот, у меня есть ещё одна персидская сабля.";
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = "Ох, добрый молодец! Вы просто пролили бальзам на моё сердце! Дайте мне взглянуть... да, она это, сабелька моя драгоценная! Вот, как и обещано было - триста дублонов вознаграждения за неё.";
			link.l1 = "Благодарствую!";
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("Вы получили 300 дублонов");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "Окромя примите мои искренние благодарности и вот этот скромный, но очень полезный подарок. Я решил презентовать его вам, коли вы вернёте мне ещё одну сабельку. Мне он не ко двору, а вот вам будет весьма кстати\nВот, глядите, какой пригожий перстень у меня есть! Это для вас. Но он не простой, он - заговорённый. Он помогает в плотницком деле и по части починки корабля. Многие мастеровые жаждали бы его заиметь, но я специально берёг для особого случая. Вот как сейчас. Берите, друг мой, и владейте на здоровьичко!";
			link.l1 = "Вот не ожидал! Огромное спасибо, Фадей!";
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			//Log_Info("Вы получили оберег 'Скарабей'");
			PlaySound("interface\important_item.wav");
			dialog.text = "Осталась последняя сабелька из моей коллекции утерянной. Уповаю на вас, "+pchar.name+", и на вашу удачу. Коли отыщете её - не мешкая поспешайте ко мне.";
			link.l1 = "Обязательно! До скорой встречи...";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Можно никуда не торопиться. У меня есть третья персидская сабля.";
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = "Ох, ну до чего хорошо, что я обратился к вам за помощью, "+pchar.name+". Вы просто кудесник, мой друг! Покажите мне эту сабельку... Охо-хо, она, она, родненькая! Благодарствую, добрый молодец, низкий вам поклон! Вот, вот ваши денежки, четыре сотни дублонов. Не поскуплюсь.";
			link.l1 = "Спасибо, Фадей. Рад"+GetSexPhrase("","а")+" был"+GetSexPhrase("","а")+" помочь вам.";
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			//Log_Info("Вы получили 400 дублонов");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			Achievment_Set("ach_65");
			dialog.text = "Снова моя драгоценная коллекция у меня! Теперь никто не посмеет её выкрасть, я позабочусь об этом! Ну а для вас, добрый молодец, у меня будет ещё одна награда: через две недели мне из Европы под заказ для одного дворянина родовитого должны привезти замечательные доспехи фехтовальщика. Они уникальны, в своём роде\nТак вот, ежели вы желаете, можете приобрести их у меня всего за семь сотен золотых дублонов. А дворянину тому сообщу я, что не прибыли они, и что ещё подождать надобно.";
			link.l1 = "А чем так хороши эти доспехи?";
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = "Они очень удобные и прочные, и могут соперничать с кирасою железною. Вы приходите через две недельки, поглядите на них, коли захотите - купите. Только не задерживайтесь более месяца - тогда продам я их заказчику изначальному.";
			link.l1 = "Договорились. Если надумаю - загляну к вам через две недели.";
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = "Да, привезли их мне, привезли, вас дожидаются. Денежки принесли?";
			if(PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				link.l1 = "Да. Вот, возьмите семь сотен дублонов.";
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = "Вот незадача, забыл"+GetSexPhrase("","а")+" деньги на корабле. Сейчас принесу!";
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			//Log_Info("Вы получили плетёный доспех");
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = "Ай да добрый молодец! Вот, держите. Этот плетёный доспех послужит вам верою и правдою, заверяю вас. Такой на Карибах ещё поискать надо, и навряд ли отыщете.";
			link.l1 = "Да, доспехи, видать, хорошие. Спасибо! Прямо не терпится их примерить...";
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = "А чего же терпеть? Ступайте, примерьте, они как раз вам по размеру.";
			link.l1 = "Так и поступлю. Ещё увидимся, месье Фадей!";
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			{
				dialog.text = "Пожалуйте, друг мой любезный, для вас всё готово! Двести пятьдесят бухт за 2125 дублонов.";
				if (PCharDublonsTotal() >= 2125)
				{
					link.l1 = "Всё по уговору. Вот, возьмите 2125 дублонов.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Вот незадача, забыл"+GetSexPhrase("","а")+" деньги на корабле. Сейчас принесу!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Пожалуйте, друг мой любезный, для вас всё готово! Пятьдесят бухт по десять дублонов за бухту.";
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "Всё по уговору. Вот, возьмите пять сотен дублонов.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Вот незадача, забыл"+GetSexPhrase("","а")+" деньги на корабле. Сейчас принесу!";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && !CheckAttribute(pchar, "questTemp.FadeyRopesBlock")) // увеличить объём поставок канатами
			{
				link.l4 = "Фадей, нельзя ли увеличить объём наших сделок? Я готов"+GetSexPhrase("","а")+" покупать у вас в пять раз больше товара! Думаю, это принесёт выгоду нам обоим. Как вы на это смотрите?";
				link.l4.go = "UpgradeRopes";
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && CheckAttribute(pchar, "questTemp.FadeyRopesPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок канатами, если в первый раз не принесли
			{
				link.l4 = "Фадей, я прин"+GetSexPhrase("ёс","есла")+" деньги! Три тысячи золотых дублонов, как и договаривались.";
				link.l4.go = "UpgradeRopes_Agreed";
			}
		break;
		
		case "ropes_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) RemoveDublonsFromPCharTotal(2125);
			else RemoveDublonsFromPCharTotal(500); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Приятно иметь с вами дело, "+pchar.name+". По рукам! Я прикажу перенести канаты на ваш корабль.";
			link.l1 = "Спасибо!";
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = "Ещё понадобится мой товар - захаживайте через месяц.";
			link.l1 = "Хорошо, Фадей. До встречи!";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) AddCharacterGoods(pchar, GOOD_ROPES, 250);
			else AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.FadeyRopes = sti(pchar.questTemp.FadeyRopes) + 1; // счётчик покупок
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = "Чем я могу вам помочь, дорогой друг?";
				link.l1 = "Вы влиятельный человек, Фадей, как я знаю. Вхожи к губернатору, и, по слухам, имеете связи при дворе. Не сможете ли вы походатайствовать перед властями за меня в случае... возникновения проблем с законом?";
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = "Чем я могу вам помочь, мил человек?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "У меня возникли неприятности с английскими властями.";
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "У меня возникли неприятности с французскими властями.";
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Я крупно переругался с контрабандистами.";
				Link.l5.go = "contraband";
            }
			link.l9 = "Извините, я пока обойдусь своими силами.";
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = "О-хо-хо, добрый молодец, и кто же это вам такого рассказал? Брешут всё люди... Но поелику вы - брат дорогого Мишеля де Монпе, да и мой добрый знакомый, то я могу попробовать замолвить за вас словечко. Однако связи мои не безграничны - я могу попросить за вас только французского и англицкого губернаторов. С голландцами и гишпанцами я делов не веду\nНо также предупреждаю вас: влияние моё не настолько велико, дабы загладить большую вину перед державой. Я могу уговорить пересмотреть отношение к вам в случае невеликих провинностей или несколько умерить враждебный пыл касательно вас\nИ только с одним губернатором за раз - либо англицким, либо французским, ибо я не могу разорваться на две половины. Также, конечно, потребуются монеты, дабы уплатить означенную мзду. Ежели вас такое устроит - то обращайтесь.";
			link.l1 = "Спасибо, Фадей. Приму к сведению.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			if (rate <= 10)
			{
				dialog.text = "Как же, слыхал, слыхал. Смогу я помочь вашему горюшку, это дело поправимое. Три сотни золотых дублонов - и уладим все неприятности.";
				if (PCharDublonsTotal() >= 300) // belamour legendary edition
				{
					link.l1 = "Отлично! Вот, держите золотые.";
					link.l1.go = "agree";
					iTotalTemp = 300;
				}
				link.l2 = "Тогда мне самое время отправиться за монетами.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "Как же, слыхал, слыхал. Подмочили вы свою репутацию. Однако дело поправимое. Шесть сотен золотых дублонов - и уладим все неприятности.";
					if (PCharDublonsTotal() >= 600) // belamour legendary edition
					{
						link.l1 = "Отлично! Вот, держите золотые.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "Тогда мне самое время отправиться за монетами.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Да, неприятности у вас основательные. Полностью ситуацию я выправить не сумею, но облегчить бремя грехов ваших тяжких - смогу. А там, глядишь, ещё разок мзду поднесём, коли будут у вас деньги и желание. Семь сотен золотых дублонов - и будем решать ваши проблемы.";
					if (PCharDublonsTotal() >= 700) // belamour legendary edition
					{
						link.l1 = "Отлично! Вот, держите золотые.";
						link.l1.go = "agree";
						iTotalTemp = 700;
					}
					link.l2 = "Тогда мне самое время отправиться за монетами.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iTotalTemp); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Денечков так десять-пятнадцать подождите. Пока я на приём попаду, пока пятое, десятое. Недельки через две будет результат.";
			link.l1 = "Спасибо, Фадей! Буду ждать...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            rate = 10 + rand(5);
            rate = GetIntByCondition(HasShipTrait(pchar, "trait23"), rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, rate, false);
			pchar.GenQuest.FadeyNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			dialog.Text = "Ну зачем же вы так поступили, мил человек? Контрабандисты - они не самые плохие люди в нашем мире, и доход могут вам солидный обеспечить. Ладно, помогу я вам, так и быть - умаслю кого следует... Готовьте семь сотен дублонов, мой друг, дешевле никак не получится.";
			if (PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				Link.l1 = "Хорошо, Фадей, я согласен. Вот ваши золотые.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "У меня сейчас нет столько золота. Я зайду позже!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Хорошо, я всё улажу, можете не переживать более. Они будут иметь с вами дела.";
			Link.l1 = "Спасибо!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
		break;
		
		case "UpgradeRopes":
			dialog.text = "Хо-хо, вижу, дела у вас идут не без толку, и аппетиты растут! Всё верно, товар у нас хороший, да и цены не кусючие. Учтите, однако, вложения тут нужны! Эдакое дело подхода требует серьёзного, чтобы всё на славу вышло.";
			link.l1 = "Стал"+GetSexPhrase("","а")+" бы я к вам с таким предложением приходить, не имея в запасе пары сотен дублонов?";
			link.l1.go = "UpgradeRopes_1";
		break;
		
		case "UpgradeRopes_1":
			dialog.text = "Знаю, монеты в сундуке вашем имеются, и не одна пара, а уж точно с полсотни бы влезло! Да дело наше не обыденное - тут не просто товар везти, а путь найти... так сказать, потайной. Для таких масштабов нужно будет не просто платить, а вложиться тяжко, чтоб с прибылью было! И чтоб потом денежки ваши в пустую тропку не ушли. Коли готовы вы три тысячи дублонов золотых отдать, то и слово моё берите, что с вами, как с добрым другом, всё будет сделано, и ценой не обидим.";
			if (PCharDublonsTotal() >= 3000)
			{
				Link.l1 = "Три тысячи дублонов! Ну, признаюсь, столь щедрое предложение редкий преуспевающий негоциант слышит, даже в самых фантастических историях! Немногие готовы столь щедро вложиться в подобное предприятие. Но я, к счастью, именно к их числу и отношусь. Вот ваши деньги, месье Фадей.";
				Link.l1.go = "UpgradeRopes_Agreed";
			}
			Link.l2 = "Три тысячи золотых дублонов! К такой сумме я не готов"+GetSexPhrase("","а")+", Фадей. К сожалению. Я зайду к вам позже.";
			Link.l2.go = "UpgradeRopes_Potom";
			link.l3 = "Три тысячи, говорите? Ну что ж... Сказать по правде, такая сумма заставляет уважать ваш размах. Но долж"+GetSexPhrase("ен","на")+" признаться - дело это не для меня.";
			link.l3.go = "UpgradeRopes_2";
		break;
		
		case "UpgradeRopes_2":
			dialog.text = "Экой поворот! Приходите с предложением, да тут же на попятный! Признаюсь, досада имеется, однако ж дружбы не уроню. Будь по-старому: прежний наш уговор крепок - пятьдесят бухт по десять дублонов за каждую, каждый месяц, 20-го числа.";
			link.l1 = "Хорошо, что вы понимаете меня, Фадей. Я бы и рад"+GetSexPhrase("","а")+" передумать, но такие траты не потяну. Увы, в этом вопросе мои возможности ограничены.";
			link.l1.go = "UpgradeRopes_3";
		break;
		
		case "UpgradeRopes_3":
			dialog.text = "Ну что ж, коли так решили, то нечего и обсуждать. Дружбы нашей сей поворот не отменит. Захаживайте, "+GetSexPhrase("мил человек","милая барышня")+".";
			link.l1 = "Всего доброго.";
			link.l1.go = "exit";
			pchar.questTemp.FadeyRopesBlock = true;
		break;
		
		case "UpgradeRopes_Potom":
			DialogExit();
			pchar.questTemp.FadeyRopesBlock = true;
			pchar.questTemp.FadeyRopesPotom = true;
		break;
		
		case "UpgradeRopes_Agreed":
			dialog.text = "А вот и разумно! Вы не из тех, кто только болтает, а и поступать умеет. Для деловых людей, и скидочка найдётся! Пятнадцать процентов на все грядущие партии! Таков договор наш будет: 250 бухт пеньковых канатов каждый месяц я стану для вас держать наготове. Забрать оные сможете, как и прежде, числа 20-го, уплатив 2125 дублонов за всё, без остатка.";
			link.l1 = "Безупречно, Фадей! С вами удивительно легко вести дела. Уверен"+GetSexPhrase("","а")+", нас ждёт удача. До скорой встречи!";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "2_1");
			pchar.questTemp.UpgradeRopes = true;
			pchar.questTemp.FadeyRopesBlock = true;
			DeleteAttribute(pchar, "questTemp.FadeyRopesPotom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}