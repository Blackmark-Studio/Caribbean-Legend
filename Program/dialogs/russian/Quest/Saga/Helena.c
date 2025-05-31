// Элен МакАртур - сомнительная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "Благодарю за помощь, капитан!";
			link.l1 = "Хм... Ты ещё красивей, чем я тебя представлял по рассказам!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "Чёрт бы побрал эту красоту! Из-за неё я чуть было не сыграла в ящик. Живой бы он меня с корвета не отпустил, только с ядром на шее, потому как я слишком много знаю про этого ублюдка. Вчера он сказал, что устал ждать и намерен добиться от меня расположения вопреки моей воле\nТак что ты вовремя успел, кэп! Давай знакомиться. Меня зовут Элен МакАртур. Отец с детства называл Румбой за весёлый нрав, так это прозвище ко мне и приклеилось.";
			link.l1 = "Ну а меня зовут "+GetFullName(pchar)+". Вот уже несколько дней разыскиваю тебя по всему архипелагу по просьбе миссис Глэдис.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "Как она?";
			link.l1 = "Сильно переживает за тебя. Впрочем, скоро ты её увидишь, мы идём в Блювельд. По дороге расскажешь про свои злоключения подробнее...";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "Сказать по чести, "+pchar.name+", мне сейчас больше всего хотелось бы поесть и лечь спать. Я зверски устала за все эти кошмарные дни, проведённые на корабле этого изверга...";
			link.l1 = "Нет проблем, Элен. Я прикажу подать тебе еду и приготовить койку. Будь моей гостьей!";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "Ещё раз от всего сердца благодарю тебя, мой капитан, за чудесное спасение. Ты обязательно должен навестить нас с матушкой. Наш домик тут совсем рядом. Вот он, налево от пирса в самом конце. И учти, "+pchar.name+", если ты исчезнешь, не простившись, никогда тебе этого не прощу, так и знай!";
			link.l1 = "Зайду обязательно!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "А вот и ты, мой капитан! Как я рада, "+pchar.name+", что ты решил наконец меня проведать. Я о многом хотела бы поговорить с тобой.";
			link.l1 = "Отложим этот разговор на некоторое время. Я должен кое-что выяснить, прежде чем смогу ответить на твои вопросы. А пока убедительно прошу не показываться на людях без особой необходимости. Надеюсь, твоё ожидание будет недолгим. Верь мне и жди.";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CanDrink")) {
				link.l1.go = "drinking_refuse";
				link.l2 = "Сама же сказала, что не простишь, если к вам не загляну.";
				link.l2.go = "drinking_accept";
				
				DeleteQuestCondition("HelenDrinking_NoVisit");
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
			} else {
				link.l1.go = "exit";
				NextDiag.TempNode = "Helena_wait";
			}
		break;
		
		case "helena_hire":
			dialog.text = "А вот и ты, мой капитан! По глазам вижу, у тебя есть новости для меня!";
			link.l1 = "Свенсон сказал, что ты рвёшься ко мне в офицеры. Я очень рад твоему желанию - Глэдис говорила, что ты очень тоскуешь без моря. Добро пожаловать в мою команду, офицер Элен МакАртур!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "Свенсон сказал, что ты хочешь стать офицером на моём корабле. Я очень рад твоему желанию - Глэдис говорила, что ты очень тоскуешь без моря. Добро пожаловать в мою команду, офицер Элен Шарп!";
				link.l2.go = "Helena_hire_2";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 2;
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "Есть, мой капитан! Но учти, я девушка гордая, могу за себя постоять и никаких вольностей не потерплю.";
			link.l1 = "Не волнуйся, у нас на корабле с этим строго. Кроме того, хочу добавить ещё кое-что...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "И что же это?";
			link.l1 = "Мы с Яном Свенсоном выяснили, что у тебя есть все права на наследование острова Исла Тесоро. Да, да, именно так, хотя на первый взгляд кажется невероятным. У меня есть половинка карты, которая поможет доказать это. Хотя с этим делом всё не так просто, мы с мистером Свенсоном поможем тебе стать полноправной наследницей острова.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+", ты серьёзно? Нет, ты смеёшься над бедной девушкой! Откуда у меня могут быть права на целый остров?";
			link.l1 = "Я абсолютно серьёзен, Элен. Более того - намерен помочь тебе устроить твою жизнь. А сейчас - отправляемся в путь!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "Как ты сказал? Элен Шарп? А почему Шарп?";
			link.l1 = "Элен, ты - дочь Беатрисс Шарп, и единственная наследница по линии Шарпов. Эта половинка карты, которую бережно хранила Глэдис все эти годы, является подтверждением твоих прав на остров Исла-Тесоро и Шарптаун. Но с этим делом всё не так просто, и мы с мистером Свенсоном поможем тебе стать полноправной наследницей твоего деда.";
			link.l1.go = "Helena_hire_3";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
			notification("Элен одобряет", "Helena");
			npchar.lastname = "Шарп";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Ах... Бедная моя мама! Надеюсь когда-нибудь найти её могилку и позаботиться о ней. Но... постой! Невероятно!";
			link.l1 = "Что такое, Элен?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "Сбылось пророчество цыганки... Я только сейчас это поняла.";
			link.l1 = "Какое ещё пророчество? О чём ты это сейчас?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", ты, наверное, сочтёшь меня наивной, но я всё равно скажу тебе. Несколько лет назад цыганка на улице сказала мне: 'твоя судьба в руках того, кто не возьмёт денег вдовы, вернёт золото мертвеца и назовёт имя матери'\nТогда я подумала, что это полная чушь. Но появился ты, и не только спас меня от позорной смерти, но и умудрился выполнить все три условия пророчества, о котором не мог ничего знать заранее!";
			link.l1 = "Судьба, говоришь... Что жe, вполне может быть и так. Я постараюсь не разочаровать тебя, а могилку твоей матери мы поищем вместе. А пока... Офицер Элен Шарп! Собирайся и не опаздывай к отплытию!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "Есть, капитан!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			AddQuestUserData("Saga", "sTimer", AddDaysToDateString(367));
			if(bImCasual) NewGameTip("Режим исследования: таймер не отключён. Уложитесь в срок!");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2, false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				AddQuestRecord("HelenDrinking", "3");
				
				SetFunctionLocationCondition("HelenDrinking_IslaTesoroAmbush", "Pirates_town", false);
				sld = &locations[FindLocation("Pirates_town")];
				sld.locators_radius.quest.detector1 = 4.0;
			}
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! У меня возникла одна идея...";
			link.l1 = ""+npchar.name+"? Тут вообще-то опасно, и я велел оставаться на корабле...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", на этом корыте столько пороха, что взорвись он - и взлетит на воздух весь остров, так что разницы нет - на этом судне мы, или на нашем. Но ты выслушай меня!";
			link.l1 = "Ну? Что ты хотела сказать?";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "Корвет и фрегат. Они считают нас за своего... Валета. Мы можем этим воспользоваться. Сейчас возьмём пару самых больших бочек с порохом отсюда, приладим фитиль и поплывём к тем кораблям\nОни подпустят нас вплотную и мы незаметно скинем бочку рядом с одним из них, зажжём шнур и быстро слиняем. Главное - успеть подальше отойти. А потом понаблюдаем, как вражеское корыто взлетит к небесам... Что скажешь?";
			link.l1 = "Ну ты выдумщица! Хотя, твой план может сработать... Но только если нас не распознают.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Рискнём, "+pchar.name+"? Ведь с двумя кораблями нам будет трудно управиться, а так есть шанс...";
			link.l1 = "Хорошо. Так и сделаем! Ребята! Заберите три бочки с порохом на борт! И уходим! Ну у тебя и фантазия, "+npchar.name+"... Я бы не додумался.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "Да, конечно. О чём пойдёт речь?";
			link.l1 = "В бухте Сабу-Матила стоит корабль Джекмана, тяжёлый фрегат 'Центурион'. Это судно принадлежало раньше Хоукам, кроме того, в каюте Джекмана должны быть важные документы и вещи... в общем, его нужно брать на абордаж.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Понятно. И ты сейчас думаешь, как ухитриться сделать это на нашем полакре? У них команды больше, чем у нас, и пушек тоже.";
			link.l1 = "Именно так. У Джекмана как минимум вдвое больше людей, и все отлично обучены - отборные наёмники. Атаковать нахрапом, без артподготовки - полное безумие. Затяжная морская баталия тоже может обернуться не в нашу пользу. Вот я и ломаю голову - что бы такое придумать.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = "Ты не поверишь, "+pchar.name+", но я уже об этом думала и кое-что придумала! Они ведь нас пока ещё не узнали - считают своим, как те два олуха, на Терксе... Можно повторить операцию.";
			link.l1 = "Элен! Я же только что сказал - фрегат нельзя топить, его нужно абордировать!";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Я всё помню, "+pchar.name+". Топить не будем. Послушай: берём несколько пустых бочонков из-под рома, засыпаем туда порох, мелкую картечь и прилаживаем очень короткий фитиль. Затем подходим к борту фрегата и кидаем бочонки с нашим огненным ромом им на палубу.";
			link.l1 = "Ха! Ты думаешь, это получится?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "А почему нет? Борта у них выше, но два человека вполне забросят бочонок наверх. Крикнем - 'лови ром в подарок от Валета'! Пока они будут соображать, что да как - бочонки взорвутся.";
			link.l1 = "Картечь разлетится в стороны и буквально сметёт всех, кто будет поблизости... Чёрт возьми, звучит заманчиво. Там целые толпы наёмников слоняются по палубе от безделья! Они как раз и есть самые опасные.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Кинем не один бочонок, а штук пять в разные места. "+pchar.name+", у нас огромное преимущество - внезапность. Они ничего не подозревают! А потом сразу отходим от них подальше, чтобы не успели забросить абордажные крючья.";
			link.l1 = "Ну что же, попробуем. Главное - чтобы они не увидели раньше времени, что 'Марлин' уже не под командованием братца Джекмана... Чёрт возьми, это будет нелегко - к ним подобраться. Джекман не такой простак, как Упырь.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Рискнём, "+pchar.name+"! Если не получится - хуже не будет.";
			link.l1 = "Хуже не будет, это точно... Готовим фугасы, и к бою!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			//if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 11) {
				Achievment_Set("ach_CL_83");
			}
			
			if (sti(pchar.questTemp.Saga.HelenRelation) < 6)
			{
				dialog.text = "Ну что, мой капитан... Настало время нам с тобой проститься. Моя служба закончилась, и мне пора привыкать к роли хозяйки Исла-Тесоро. Надеюсь, я смогу стать достойной преемницей своего дяди. Благодарю тебя за помощь.";
				link.l1 = "Жаль, конечно, расставаться, но что же поделать. У тебя теперь есть дела поважнее, чем служба на моём судне.";
				link.l1.go = "result_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Mary")) {
					dialog.text = "Я бы и дальше хотела остаться у тебя на корабле. Рядом с тобой... Но это невозможно. Будь счастлив, Шарль. И лучше бы ей быть достойной тебя!";
					link.l1 = "Мне жаль, Элен.";
					link.l1.go = "result_mary";
				} else {
					dialog.text = "Как странно, "+pchar.name+"! Я только что стала владелицей целого острова, но совсем не чувствую себя хозяйкой Исла Тесоро... Полагаю, новый глава Берегового братства управится с делами колонии куда лучше меня. Мне же будет достаточно просто ренты.";
					link.l1 = "Хм. Ты уверена, Элен? Подумай, у тебя же в собственности целый остров!";
					link.l1.go = "result_9";
				}
			}
			
			DeleteQuestCondition("HelenDrinking_AtSHDN");
			DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
		break;
		
		case "result_mary":
			dialog.text = "Ну а друзьями-то мы останемся?";
			link.l1 = "Конечно... Элен, мы с тобой ещё не раз встретимся на Исла Тесоро. Тебя отвезти на твой остров?";
			link.l1.go = "result_12";
		break;
		
		case "result_1":
			dialog.text = "Ты прав... Мне тут удалось собрать немного золота - то, что я заработала на твоём корабле. Возьми его и не вздумай отказываться - я не хочу чувствовать себя твоим должником.";
			link.l1 = "Гм. Вообще-то...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "Я понимаю, что ты хочешь сказать. Безусловно, твоя помощь была намного значительней этого сундука с монетами. Но это почти всё, что у меня есть, а отблагодарить тебя я просто обязана. Бери, а если не возьмёшь сам - я оставлю его у тебя в каюте.";
			link.l1 = "Ты что, сходишь на берег прямо сейчас? Может, тебя отвезти на Исла Тесоро?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			//Log_Info("Вы получили сундук с дублонами");
			PlaySound("interface\important_item.wav");
			dialog.text = "Не стоит, "+pchar.name+". Я сама доберусь до своего острова. Некоторая сумма денег у меня есть, на первое время хватит... А хозяйке Исла Тесоро, я уверена, не придётся беспокоиться о доходах.";
			link.l1 = "Ну что же - как скажешь. Желаю тебе удачи в твоей новой жизни.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "Спасибо. Но это ещё не всё. Я вновь обрела отца, хотя и столь необычным образом. Фактически, он заплатил своим добрым именем английского дворянина за моё наследство, и меня это очень угнетает. На него объявлена охота, и я бы очень не хотела, чтобы ты, "+pchar.name+", принял в ней участие.";
			link.l1 = "Опомнись, Элен! Он же бандит и пират!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "Пират? А ты-то кто? В первую очередь он мой отец! И мне, дочери бандита и пирата, глубоко плевать, что о нём думает английское правосудие. И если ты попробуешь причинить вред моему отцу, то я забуду всё то хорошее, что ты успел для меня сделать. Учти, я тебя предупредила.";
			link.l1 = "Вот как? Вообще-то, девочка, можно было и повежливее. Что-то я не заметил от тебя критики по поводу моего пиратского поведения, когда я вытаскивал тебя из лап Донована, самым разбойничьм образом захватив его корвет!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "Извини. Я погорячилась. Но мне всё-таки хотелось бы остаться с тобой друзьями, что станет невозможным, если ты начнёшь строить козни против моего отца.";
			link.l1 = "Я услышал тебя. Но более никогда не смей угрожать мне, Элен... Белтроп. За время службы на моём корабле ты должна была понять, что я не боюсь ни чёрта, ни морского дьявола. И тебя тоже не испугаюсь, поверь мне. А теперь - прощай. И не смотря ни на что, я желаю тебе удачи.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Спасибо. Возможно, ещё когда-нибудь встретимся, "+pchar.name+"...";
			link.l1 = "А почему нет? На Исла Тесоро мне предстоит побывать ещё не раз. Там и увидимся... Пока, Элен!";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но её не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться	
			if (CheckAttribute(pchar, "questTemp.LSC.MaryWait")) {
				pchar.questTemp.LSC.Mary = "return";
			}
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашёл Мэри - выбирай, какая девушка милее
			dialog.text = "Я уже подумала. "+pchar.name+", если ты позволишь, я бы и дальше хотела остаться у тебя на корабле. Рядом с тобой...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(выбрать Мэри) Элен! Ты, похоже, не понимаешь. Ты обеспечена до конца своих дней, и можешь не беспокоиться о будущем. У меня же впереди - война, закулисные интриги и полная неизвестность. Тебе нужно устраивать свою жизнь, а не связывать её с авантюристом.";
				link.l1.go = "result_10";
				link.l2 = "(выбрать Элен) Я мог только мечтать об этом, Элен. Конечно, я не хочу терять тебя, но, возможно, тебе было бы лучше отправиться на Исла Тесоро. Кто знает, куда приведёт меня моя судьба. У меня впереди - война, закулисные интриги и полная неизвестность.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "Я мог только мечтать об этом, Элен. Конечно, я не хочу терять тебя, но, возможно, тебе было бы лучше отправиться на Исла Тесоро. Кто знает, куда приведёт меня моя судьба. У меня впереди - война, закулисные интриги и полная неизвестность.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"! Не лги мне. Ты просто не хочешь, чтобы... Скажи: это она? Та рыжая девчонка с Острова Погибших Кораблей? Да?";
			link.l1 = "Элен! Я в первую очередь думаю о тебе! Как ты этого не понимаешь?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "Я так и знала... И чем же она тебя так очаровала, а? Эх, "+pchar.name+"... Ну, раз ты так решил - то мне и впрямь больше ничего не остаётся, как отправиться на свой остров. Я не буду стоять между вами\nВ любом случае, огромное спасибо тебе за всё, что ты для меня сделал. Ты - лучший из всех, кого я только знала. Ну а друзьями-то мы останемся?";
			link.l1 = "Конечно... Элен, мы с тобой ещё не раз встретимся на Исла Тесоро. Тебя отвезти на твой остров?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "Не надо. Я куплю себе корабль. За время службы у тебя я собрала сумму, достаточную для покупки и снаряжения шхуны. У меня снова будет моя 'Радуга'.";
			link.l1 = "Очень рад, Элен, что ты оказалась такой... хозяйственной. Но владелице Исла Тесоро не пристало ходить на шхуне - думаю, в скором времени ты обзаведёшься собственным фрегатом.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Всё возможно, "+pchar.name+". Ладно. Пойду на верфь, присматривать себе новый корабль, но сначала... поцелуй меня, на прощание. Пожалуйста...";
			link.l1 = "Элен...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 0.5);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться
		break;
		
		case "result_15":
			dialog.text = "С первой же нашей встречи твоя судьба стала моей судьбой. Неужели ты до сих пор этого не понял, "+pchar.name+"? Я пойду с тобой хоть на край света!";
			link.l1 = "А твой отец? Лоуренс Белтроп? Ведь вышло так, что он оказался моим врагом...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "Мой отец - Шон МакАртур! Я любила его, и уже оплакала его смерть. Другого отца у меня нет и быть не может. А этот пират... я не хочу о нём даже говорить.";
			link.l1 = "Элен... Дорогая Элен!..";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", я давно хотела тебе сказать: ты - лучший, ты - удивительный! Ты столько сделал для меня, что мне жизни не хватит, чтобы отплатить за твоё добро. Я хочу быть с тобой рядом. Всегда. И если ты этого захочешь, я стану твоей женой... Я люблю тебя.";
			link.l1 = "Мы будем вместе. Обещаю!"; // а куда же ты теперь денешься :)
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) {
				link.l1.go = "result_17A";
			} else {
				link.l1.go = "result_18";
			}
		break;
		
		case "result_17A":
			dialog.text = "Пообещай, что сделаешь кое-что для меня прямо сейчас? И не смейся, пожалуйста!";
			link.l1 = "Обещаю, дорогая!";
			link.l1.go = "result_17A_1";
		break;
		
		case "result_17A_1":
			dialog.text = "Назови меня моим настоящим именем. Пожалуйста!";
			link.l1 = "Я люблю тебя, Элен Шарп.";
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", дорогой... Обними меня! Я так долго ждала этого момента!";
			link.l1 = "Элен, девочка моя...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, false, true);
			PlayStereoOGG("music_romantic");
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
			
			pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
			pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
			pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
			
			// Квест Лонгвея "Путеводная звезда", начало 5 этапа
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! Это было просто... замечательно! Я никуда не хочу уходить... Давай останемся тут до утра. И пусть весь мир подождёт!";
			link.l1 = "Пускай подождёт, Элен!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Следующим утром...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
			
			pchar.GenQuest.BrothelCount = 0;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
			
			// Запуск квеста Дороже золота
			SetFunctionTimerCondition("GoldenGirl_Start", 0, 0, 1, false);
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "Капитан! Джекман уничтожен... Это значит, что более ни с чьей стороны в адрес моей семьи угроз и опасностей нет?";
			link.l1 = "Да, Элен, это так. Но радости у меня мало - вместе с 'Центурионом' утонули документы и вещи, которые могли бы позволить нам найти могилу твоей мамы, и доказать твои права на Исла Тесоро. Эх... Теперь и Тортугу придётся брать в одиночку...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", не огорчайся. Ну что же теперь поделать. А из-за меня точно не печалься - я прекрасно проживу и без этого острова. Спасибо тебе за всё, что ты сделал для меня!";
			link.l1 = "Ты так говоришь, словно уходишь... да?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Да, мой капитан. Мне удалось отложить на твоей службе денег, достаточных для покупки и снаряжения шхуны. У меня снова будет моя 'Радуга'. Но мы с тобой ещё не раз увидимся в Блювельде, правда? Я возвращаюсь домой.";
			link.l1 = "Ну что же... удачи, Элен!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "Ну что же, мой капитан... Видимо, так и не удалось нам с тобой осуществить задуманное. Прощай. Я возвращаюсь домой. На заработанные у тебя деньги я куплю себе новую шхуну, так что ещё, думаю, не раз увидимся в море!";
			link.l1 = "Удачи, Элен. Мне жаль, что всё так неудачно вышло. Прощай.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "Капитан! Джекман уничтожен... Это значит, что более ни с чьей стороны в адрес моей семьи угроз и опасностей нет?";
			link.l1 = "Да, Элен, это так. Но радости у меня мало - я потерял очень много времени, и Исла Тесоро теперь - английская колония. И ты теперь без положенного наследства, и мне придётся брать Тортугу самому...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", что там сказал адвокат?";
			link.l1 = "Эх! Я потерял очень много времени, и Исла Тесоро теперь - английская колония. И ты теперь без положенного наследства, и мне придётся брать Тортугу самому... Увы, но мы проиграли.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Нет, дорогой, не выйдет.";
				link.l1 = "Ну почему?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (drand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", я себя что-то совсем неважно чувствую. Не обижайся, пожалуйста. Давай не сегодня...",""+pchar.name+", дорогой, я так устала за последние несколько дней. Честно говоря, мне хочется просто поспать. Не обижайся. Давай в другой раз.");
				link.l1 = RandPhraseSimple("Ну хорошо...","Не обижаюсь. Как скажешь...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", я с радостью поддерживаю твоё предложение! Идём!",""+pchar.name+", ну конечно же не возражаю! Идём!");
				link.l1 = RandPhraseSimple("Ты моя умничка...","Ты - просто прелесть, Элен...");
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "sex_after":
			dialog.text = LinkRandPhrase(RandPhraseSimple("Всё было отлично, "+pchar.name+"!..","Ты как всегда на высоте, дорогой..."), RandPhraseSimple("Было здорово, Шарль!","Отлично провели время, дорогой!"), RandPhraseSimple("С тобой не соскучишься, мой капитан!","Ты был прекрасен, милый!"));
			link.l1 = LinkRandPhrase("Я рад, что ты осталась довольна...", "Мне с тобой очень хорошо, Элен...", "Я люблю тебя, Элен...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", я всегда этому рада... Но сейчас немного не время - нужно отловить этого прохвоста Тибо, пока он не скрылся где-нибудь.";
				link.l1 = "Ты как всегда права, моя девочка...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Нет, дорогой, не выйдет.";
				link.l1 = "Ну почему?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (drand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", я себя что-то совсем неважно чувствую. Не обижайся, пожалуйста. Давай не сегодня...",""+pchar.name+", дорогой, я так устала за последние несколько дней. Честно говоря, мне хочется просто поспать. Не обижайся. Давай в другой раз.");
				link.l1 = RandPhraseSimple("Ну хорошо...","Не обижаюсь. Как скажешь...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", я с радостью поддержу твоё предложение! Идём!",""+pchar.name+", ну конечно же не возражаю! Идём!");
				link.l1 = RandPhraseSimple("Ты моя умничка...","Ты - просто прелесть, Элен...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;
			//npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			//npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
			DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "GiveKissInRoom");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Да, "+pchar.name+"?","Да, мой капитан?","Слушаю тебя, "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining");
				dialog.text = "Смотри, мой капитан!";
				link.l1 = "Ого, вот это хват. Вижу, ты времени даром не теряла, Элен.";
				link.l1.go = "cutlass_training";
				NextDiag.TempNode = "Helena_officer";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && sti(pchar.GenQuest.BrothelCount) > 0 && !CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Дорогой, по поводу твоих визитов к шлюхам.";
				npchar.quest.refusesex = true;
				link.l1 = "А? Элен, ты все не так поняла! Я просто...";
				link.l1.go = "brothel_found";
				NextDiag.TempNode = "Helena_officer";
				SetFunctionTimerCondition("Helena_ClearRefuseSex", 0, 0, 180, false);
				DeleteQuestCondition("Helen_GiveSex");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Элен, я собираюсь отправиться в старый индейский город Тайясаль. Не буду скрывать: это крайне опасное путешествие, и более того - необычное: через телепортационный истукан. Ты... пойдёшь со мной?";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Элен, дай мне полный отчёт о корабле.";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "Я хочу, чтобы во время стоянки в колонии ты закупала товары.";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Я прибыл по вашему распоряжению, капитан.";
				Link.l2 = "Элен, у меня есть для тебя несколько распоряжений.";
				Link.l2.go = "Companion_Tasks";
				
				sld = GetCharacter(sti(npchar.RealCompanionIdx));
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Rainbow") && sld.ship.type == pchar.questTemp.HelenDrinking.Rainbow && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
					DeleteAttribute(link, "");
					dialog.text = "Ты думаешь, это смешно?";
					link.l1 = "Хорошая посудина, разве нет? Для тебя брал, Элен! Сама посуди, какой джентльмен на Карибах дарит даме сердца настоящий корабль, а?";
					link.l1.go = "rainbow";
					
					NextDiag.TempNode = "Helena_officer";
					break;
				}
				
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Элен, я хочу с тобой посоветоваться.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Элен, у меня для тебя есть распоряжение...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Элен, может, останемся в каюте вдвоём... на ближайшие пару часов? Ты не против?","Дорогая, может, проведём следующие несколько часов тет-а-тет? Ты не против?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Элен, может, снимем комнату и останемся там вдвоём... на ближайшие пару часов? Ты не против?","Дорогая, может, проведём следующие несколько часов тет-а-тет? Снимем комнату... Ты не против?");
				Link.l2.go = "room_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "town" && sti(pchar.money) >= 1000 && GetNpcQuestPastDayWOInit(npchar, "special_sex_date") >= 30 && !CheckAttribute(npchar, "quest.refusesex"))
			{
				Link.l2 = "Элен, дорогая, позволь пригласить тебя культурно провести время в таверне?";
				Link.l2.go = "special_sex";
			}
			if (CheckAttribute(pchar, "questTemp.MysteryPortRoyal_Helena")) {
				link.l4 = "Элен, кажется я нашел последнюю волю твоего воздыхателя - Френсиса. Он завещал тебе своё наследство.";
				link.l4.go = "MysteryPortRoyal_Helena_1";
			}
			if (CheckCharacterItem(pchar, "pirate_cutlass") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
				link.l4 = "Мне кажется, что этот катлас теперь - твой. Блейз - твой названный дядя...";
				link.l4.go = "give_cutlass";
			}
			link.l9 = "Пока ничего, Элен.";
			NPChar.id = "Helena"; // лесник . Идентификация Элен на всяк. случай . если потеряет сознание.
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
	/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "Шарль, дорогой, я не буду считать крыс в трюме! Ты же знаешь...";
			Link.l1 = "О, милая, конечно, извини, я как-то не подумал...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Не моё это, сам знаешь, дорогой. Давай оставим учёт и коммерцию тем, кто в этом разбирается?";
			link.l1 = "Да, ты права.";
			Link.l1.go = "exit";
        break;			
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Внимательно слушаю.";
			Link.l1 = "Это касается абордажа.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Это касается твоего корабля.";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Пока ничего.";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Что желает мой капитан?";
			Link.l1 = "Я хочу чтобы ты не брала корабли на абордаж. Побереги себя и свою команду.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Мне нужно чтобы ты брала вражеские корабли на абордаж.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Что желает мой капитан?";
			Link.l1 = "Я хочу чтобы ты не меняла свой корабль после абордажа. Он слишком ценен.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Когда будешь брать врагов на абордаж, посмотри, вдруг кораблик приличный будет, тогда бери себе.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Ладно, я подумаю.";
			Link.l1 = "Подумает она... Да уж, тебе приказов не отдашь.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Ладно, я подумаю.";
			Link.l1 = "Подумает она... Да уж, тебе приказов не отдашь.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Ладно, я подумаю.";
			Link.l1 = "Подумает она... Да уж, тебе приказов не отдашь.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Ладно, я подумаю.";
			Link.l1 = "Подумает она... Да уж, тебе приказов не отдашь.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "Какие будут приказания?";
            Link.l1 = "Стой здесь!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Следуй за мной и не отставай!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Нужно изменить тип боеприпаса для твоего огнестрельного оружия.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Выбор типа боеприпаса:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Будет сделано, капитан!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Будет сделано, капитан!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Вот ты где спрятался! Насилу тебя нашла... Ну ты дал жару, мой капитан! Такого забега по крышам и прыжка с головокружительной высоты мне ещё не доводилось видеть! У меня чуть сердце не выпрыгнуло из груди! Ты однажды доведёшь меня своими выходками до удара, дорогой... О, так ты тут не один? Кто эта девушка?";
			link.l1 = "Это Кэтрин Фокс, дочь полковника Фокса, командира 'морских лис'. Мы отвезём её на Антигуа.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Как интересно! Добро пожаловать на борт, мисс Фокс... А теперь быстрее грузимся в шлюпку - надо убираться отсюда.";
			link.l1 = "Ты умничка, Элен! И что бы я без тебя делал?.. Кэтрин, следуй за мной!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Ну наконец-то ты очнулся, мой дорогой... Как ты себя чувствуешь? Ты очень напугал меня.";
			link.l1 = "Элен... Милая, что произошло? Аргх, голова раскалывается...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Когда мы зашли в капитанскую каюту, ты лежал на полу без движения. У меня чуть сердце не остановилось! Ребята подхватили тебя и потащили на наш корабль, и вовремя, потому что эти ужасные скелеты, что валялись на палубе, начали подниматься и снова взялись за сабли\nЭто просто кошмар! Их нельзя одолеть! Мы быстро обрубили лини и отчалили от их корабля, но далеко уйти не успели: негодяи всадили в нас залп бортовой батареи и разбили управление кораблём. А затем они подняли паруса и в мгновение ока скрылись за горизонтом\nКорабль наш налетел на мель, а все, кто выжил, добрались на лодке до берега. Хоть корабль наш чудом и уцелел, я всё же прихватила твой капитанский рундук из каюты с твоими вещами. На всякий случай. Там ведь много чего важного, я знаю... ";
			link.l1 = "Ты умничка, Элен... Что бы я без тебя делал?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Я вытащила тебя в лодку, а потом и на берег. А ты был словно мёртвый, только сердце едва билось. У меня до сих пор руки дрожат...";
			link.l1 = "Спасибо, моя милая. Я в долгу перед тобой. Сколько я здесь валялся без сознания?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Сутки. Я промыла и перевязала тебе раны, влила в рот лекарства и ром. Ты просто обязан теперь выздороветь!";
			link.l1 = "Обещаю, что не умру, моя дорогая. Хотя чувствую себя на редкость паршиво...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Не сомневаюсь... Это был 'Летучий Голландец', да? Почему они на нас напали? И почему сразу не сделали ни одного выстрела, а после абордажа одним залпом чуть нас утопили?";
			link.l1 = "Их капитану нужен был амулет, по поводу которого я ходил к Туттуатхапаку, индейскому шаману. Поэтому они и не потопили нас сразу. А как только главный мертвец забрал амулет, они и расправились с нами... Жуть какая! Корабль с командой живых мертвецов! Поверить невозможно...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Вот мы и повстречались с 'Летучим Голландцем'. В первой же колонии я пойду в церковь,  поставлю свечу из чистого воска за наше спасение, и буду молиться...";
			link.l1 = "Знаешь, Элен, я, пожалуй, тоже. Но сейчас мы пойдём назад в деревню карибов. Я должен всё рассказать Туттуатхапаку. Этот проклятый корабль напал на нас из-за амулета! Надеюсь, краснокожий дьявол сможет объяснить мне, зачем он понадобился мертвецам.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Хорошо. Но тебе нужно беречь себя - твои раны до сих пор сочатся кровью.";
			link.l1 = "Но ты же поможешь мне исцелиться, моя девочка? И, Элен: я люблю тебя...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "Я тебя тоже, дорогой...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", я как-то сказала тебе, что наши судьбы теперь едины. Твоя судьба - моя судьба. Когда мы отправляемся?";
			link.l1 = "Значит, ты согласна, моя умничка... Я очень рад. А когда выдвигаться - я скажу немного позже. Пока нам нужно подготовиться.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Я готова в любой момент, мой капитан! С тобой - хоть на край света!";
			link.l1 = "Спасибо, любимая...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "О, "+pchar.name+"! Рада тебя видеть! Какими судьбами на Исла Тесоро?";
			link.l1 = "Да всё как обычно - по делам. И, конечно, не забыл тебя проведать, Элен...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = "Ну, капитан, что там припекло в этот раз нашему дражайшему губернатору? С кем дерёмся? Испанцы, пираты, или что похуже?";
			link.l1 = "Хуже, Элен, хуже. Губернатор намерен посетить крайне дорогую куртизанку, а я при нём в качестве диковинки, обещанной хозяйке. Скучная болтовня, дорогое вино и унылые аристократы.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Ровно наоборот - необременительный приём у дамы из высшего общества. Его светлость настоятельно просит его сопровождать, совершенно неожиданно, но я рад случаю немного отдохнуть от всей этой беготни.";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Отлично, и ты как ручная обезьянка будешь прыгать на потеху вельможных бестолочей? Очень мило! Может, ну его к дьяволу? Пополним запасы и поднимем паруса? Если хочешь отдохнуть - на Исла Тесоро '"+pchar.ship.name+"' всегда желанный гость. Развеемся, поваляемся на солнышке, проведаем старых друзей.";
			link.l1 = "Послушай, это всё прекрасно звучит, и я с радостью так и сделаю, но потом. Я обещал губернатору, для старика это важно, и вообще...";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Вообще что? Ты думаешь, твоя голубая кровь для них что-то значит? Я знаю, что такое 'высшее общество': для них Шарль де Мор не капитан, которому доверяют жизнь и за которым идут в огонь. Не равный вельможа - равные сидят в кресле в канцелярии, а не скачут по вантам в пороховом дыму. Даже не человек! Он просто... необычная приправа к ужину или беседе. Знаешь, как комнатный леопард, или заморский уродец с двумя головами! Занятная безделушка, пока не надоест! С каких пор ты готов быть безделушкой?!";
			link.l1 = "Элен, не беспокойся, я способен выдержать несколько любопытных взглядов, чтобы уважить губернатора. Это проще чем идти на абордаж под картечью. Уверен, я справлюсь. И эти самые 'бестолочи' не всегда такие. Даже в высшем обществе есть достойные люди... ну, или должны быть.";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Хорошо. Но учти - ради этих 'достойных' я в платье не полезу - хотят, пусть падают в обморок или возмущённо шепчутся под веерами, мне плевать.";
			link.l1 = "Я и не собирался тебя заставлять. Не вижу смысла страдать всем вместе. Я переживу этот приём, а потом махнем на Исла Тесоро. Я помню в трюме был ящик отличной испанской мадеры...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "То есть я для такой компании не подхожу, это ты хочешь сказать? Когда обезьянка приводит с собой ещё одну, это уже перебор? Интересно. Хорошо, не забудьте одеться поприличнее, капитан. Когда на обезьянке воротник и манжеты, это приводит в умиление даже куртизанок. Удачного выступления!";
			link.l1 = "Элен, постой! Проклятье...";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Да, мы заслужили отдых, согласна. Но будь я проклята, если полезу в платье ради этого приёма. Как думаешь, долго потом будут сплетничать о твоей спутнице, заявившейся в мужской рубахе и матросских штанах, в высших кругах Сен-Пьера?";
			link.l1 = "Не думаю, что это хорошая идея. Эта маркиза из тех, на приёмы к которым мужчины своих дам не берут. Уважаемых дам.";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "Отлично - куртизанки и великосветский разврат! Мог бы и сразу сказать. Я же не ревнивая идиотка, стрелять в тебя не буду. Во всяком случае, не сразу.";
			link.l1 = "Элен, я просто буду сопровождать губернатора, по его же настоятельной просьбе. Никаких... куртизанок. Ну то есть, они там будут, но... Проклятье! Да это просто визит вежливости!";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "Рекомендую тогда одеться поприличнее, капитан. Высшее общество, дело такое. С человеком без воротника и манжет не станут разговаривать даже из вежливости. Даже куртизанки. Удачного... визита.";
			link.l1 = "Элен, постой! Проклятье...";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Воротник и манжеты, капитан. Возможно - кружева, они сейчас снова в моде.";
			link.l1 = "Элен, ну сколько можно?!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Смотрите-ка, кого мы нашли! Наш бесследно пропавший в высшем обществе капитан!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Ну, и как местным вельможам новая обезьянка? В городе болтают, что её выступление произвело настоящий фурор! Играть в карты на корабли и куртизанок, а потом бросить вызов какому то вельможному мерзавцу? Может объяснишь, что это за чертовщина?";
			link.l1 = "Элен, всё немного сложнее. Проклятье, прости меня, я не думал, что задержусь настолько, пришлось заночевать в доме мадам Бото. Одному, клянусь! И да, я выиграл в карты отменный фрегат. Представляешь?";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Отлично! Я начинаю думать, что ты либо святой, либо дурак. Но выигранных куртизанок и корабли обсудим позже - сейчас рассказывай что за дуэль и почему все говорят об этом так, словно ты дерёшься по меньшей мере с наследным принцем?";
			link.l1 = "Этот человек - бастард крайне могущественного вельможи, графа де Леви Вантадура. Он сам бросил мне вызов, и теперь придётся постараться не умереть самому, и не убить его, дабы не разгневать его отца.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Проклятье! И как мы это сделаем? А если он задумает что-то бесчестное? Мы ведь не раз такое видели!";
			link.l1 = "Вот поэтому Его Светлость дал мне секундантов из благородных офицеров гарнизона. Больше я никого с собой не возьму - если дойдёт до разбирательств и суда, не должно быть никаких сомнений, что всё было по кодексу и по закону. А тебя прошу, присмотри за фрегатом, пока меня не будет.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Давай-ка уточним, правильно ли я поняла. Ты пропал почти на сутки, выиграл в карты баснословно дорогую... даму. Теперь идёшь драться из-за неё с могущественным благородным выродком, которого даже нельзя убивать, а я... мы все, должны сидеть на заднице и ждать, чем всё закончится? Интересно, что я должна думать по этому поводу? Как считаешь?";
			link.l1 = "Элен, послушай, ты имеешь право злиться, и мне очень жаль, но всё не так просто...";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Знаешь что, хватит. Иди и делай то, что считаешь нужным. Мне здесь, судя по всему, места нет, но об этом мы поговорим, когда всё закончится. А я, пока, пойду и попытаюсь это как следует запить. За твоим новым фрегатом я присмотрю, не беспокойся. И капитан, постарайся выжить... чтоб я сама могла тебя прибить.";
			link.l1 = "Элен, да позволь мне всё объяснить, наконец! Проклятье... Опять?!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Говорят, в городе теперь новая мода - корабли и куртизанок надо выигрывать в карты, а не покупать! Причём, бывших владельцев, чтобы быть до конца утончённым, следует вызывать на дуэль. Во что ты, чёрт возьми вляпался на этот раз?";
			link.l1 = "Элен, всё немного сложнее. Проклятье, прости меня, я не думал что задержусь настолько. Этот вечер превратился в форменное сражение за карточными столами. И да, я выиграл в карты отменный фрегат. Представляешь?";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Отлично, значит и куртизанку ты действительно выиграл? А этот фрегат, что ты ставил? Неужели наш...";
			link.l1 = "Мне пришлось. Долго объяснять, но я выиграл. А теперь - мой соперник, обвинил меня в мошенничестве и вызвал на дуэль. Он бастард крайне могущественного вельможи, графа де Леви Вантадура, и мне придётся изо всех сил постараться, чтобы не убить его на дуэли.";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "А он тоже будет стараться не убить тебя? Ты совсем рехнулся, капитан? Рисковать всем кораблём, а теперь и своей жизнью из-за какой-то... мадам? Она действительно того стоит?";
			link.l1 = "Элен, для ревности нет повода, клянусь. Просто так сложилось. Я должен это сделать, и губернатор назначил мне секундантов из числа благородных офицеров, чтобы исключить любые сомнения после дуэли. Я не могу взять ни тебя ни кого-то из ребят. Прошу, присмотри за фрегатом, пока меня не будет.";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "Просто чудесно! Ты отправляешься к куртизанкам - заметь, я тебе даже в спину не выстрелила - пропадаешь неизвестно куда почти на сутки. Возвращаешься с известием, что только чудом не проиграл корабль, зато выиграл эту самую куртизанку. И теперь из-за неё будешь драться с вельможным засранцем, которого даже убивать нельзя? Интересно, что я должна думать по этому поводу? Как считаешь?";
			link.l1 = "Элен, послушай, ты имеешь право злиться, но всё не так просто...";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "Знаешь что, хватит. Иди и делай то, что считаешь нужным. Мне здесь, судя по всему, места нет, но об этом мы поговорим, когда всё закончится. А я, пока, пойду и попытаюсь это как следует запить. За твоим новым фрегатом я присмотрю, не беспокойся. Но если с тобой хоть что-то случится - клянусь Богом, я направлю пушки на город и сровняю с землёй и этот бордель и особняк нашей разлюбезной светлости.";
			link.l1 = "Элен, всё будет хорошо, поверь мне. Постой, ну куда ты?! Проклятье... Опять?!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Шарль, а теперь будь добр, объясни мне: что за чертовщина тут вообще творилась? На корабль среди ночи ворвались какие-то головорезы. Потом этот немытый хмырь, гнусно хихикая, спрашивал меня, на что ты пойдёшь, чтобы меня вернуть. А затем меня заперли в кубрике, и я потеряла счёт дням!";
			link.l1 = "Мерзавец решил посчитаться со мной за свой позор. Больше всего я боялся, что он что-нибудь с тобой сделает! Но, слава Богу, ты в порядке!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "Я так понимаю, тебе пришлось что-то сделать ради этого? Что-то плохое, ведь так?";
			link.l1 = "Главное - ты теперь снова со мной. Я так виноват перед тобой, Элен, за всю эту историю! Не знаю, сможешь ли ты меня простить!";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Уже. И ты прости меня, Шарль. Если бы я не приняла всё так близко к сердцу с этой дуэлью и маркизой, и хотя бы расставила вахту на фрегате... Глупо всё вышло!";
			link.l1 = "Всё вышло как вышло, и это уже в прошлом. Ты вернулась ко мне, и это всё, о чём я смел мечтать последние недели. Я многое понял за это время, Элен. Очень многое. Я люблю тебя, и больше никогда не оставлю. Обещаю!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Полагаю, мне лучше не знать что именно ты сделал, так? Ладно, мы снова вместе и это, главное.";
			link.l1 = "У меня нет от тебя секретов. Я расскажу тебе...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Прошло немного времени...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Ну и история вышла... Я верю, что у тебя не было иного выбора, но как мы объясним всё дю Парке и прочим? Ты же фактически поставил себя вне закона?";
				link.l1 = "Я согласился с этой ценой. И да - выбора действительно не было. Не беспокойся - я найду способ восстановить своё доброе имя. А нет - так на Исла Тессоро нам всегда рады! Если ты со мной - остальное неважно.";
			}
			else
			{
				dialog.text = "Ну и история вышла... Я верю, что у тебя не было иного выбора, но что теперь будет? Этот англичанин действительно всё уладит, или будем воевать? Не хочешь отправиться в Бас-Тер и лично полюбоваться как на заносчивого мерзавца оденут цепи?";
				link.l1 = "Знаешь, Элен, пару недель назад я бы ни за что не упустил такой шанс. Но теперь - пусть бастард отправляется к чёрту! Мне даже плевать поймают его или нет - это всё больше не моя проблема. Мы снова вместе - вот что по настоящему важно!";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Я всегда с тобой, ты же знаешь. А вместе мы и не из таких передряг выпутывались. Не впервой.";
				link.l1 = "Точно. Ну, милая, поднимаем паруса! Жизнь продолжается!";
			}
			else
			{
				dialog.text = "Мне нравится такой подход, Шарль! Французы, англичане, испанцы - пусть сами разбираются. Думаю - мы действительно заслужили немного покоя!";
				link.l1 = "Согласен. Только ты, я и никаких губернаторов и высокородных интриганов!";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Так точно, капитан!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Звучит отлично! Пойду отдам ребятам команду сниматься с якоря! И, Шарль, ты же знаешь...";
				link.l1 = "Да, Элен, я знаю. Поднимайся на палубу, я сейчас буду.";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Шарль, ты жив! У тебя получилось!! Португалец мне всё рассказал! Ну и история вышла!";
			link.l1 = "Слава Богу, ты жива, Элен. Ты не представляешь, как я рад тебя видеть!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Кстати, об этом. Ты всё мне обещал что-то рассказать? Что-то важное и сложное. Это твой шанс, капитан, я жду. Что, чёрт возьми, за безумие тут вообще произошло?!";
			link.l1 = "Я... я люблю тебя Элен. А всё остальное - неважно.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Ну да, это многое объясняет, но... Чёрт, я тоже, Шарль. Я тоже тебя люблю. Боже, как я скучала!";
			link.l1 = "И я скучал. Пойдём, сегодня я тебя не оставлю, даже если небо начнёт рушиться на этот город, будь он неладен. Я тебя вообще больше не оставлю. Никогда.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Полагаю, мне лучше не знать что именно ты сделал, так? Ладно, мы снова вместе и это, главное.";
			link.l1 = "У меня нет от тебя секретов. Я расскажу тебе...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Прошло немного времени...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Невероятно! То есть Франция сейчас на пороге войны с Англией из-за меня?";
			link.l1 = "Нет, Элен, из-за моей глупости. Я должен был тебя вернуть и всё исправить.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "Очень романтично, я даже готова забыть о том, с чего всё началось... Ну, почти готова. Ладно, чёрт с ним! Так тебя подозревали, потому что Португалец сказал тебе неверное название этой клятой бригантины?";
			link.l1 = "Наоборот, верное! И я бы дорого дал, чтобы узнать, как он об этом пронюхал, и почему вообще... Кстати, а где он сам?!";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Отплыл. Почти сразу, как доставил меня сюда. Гостеприимством твоей выигранной куртизанки я не воспользовалась, и Бартоломью снял мне комнату тут, оплатив её на пару недель, и исчез, даже не попрощавшись. Ой нет, погоди - он же оставил письмо!";
			link.l1 = "Письмо? Бартоломью Португалец? Это что-то новенькое. Меня терзают смутные сомнения...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Ладно, ты читай, а я побегу - покажусь нашим, а то мы ещё сутки тут просидим, а они же тоже волнуются. Не думала, что буду скучать по этим вечно хмурым рожам! А ты постарайся не влипнуть в очередное безобразие!";
			link.l1 = "Я бы и неделю так просидел... Проклятье, я всё таки тебя вернул! Поверить не могу!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Прибой и ветер, ты и я, хорошее вино - стоило бы почаще вот так выбираться, а Шарль?";
			link.l1 = "Рад, что тебе нравится. Думаю, у нас теперь будет больше времени на это и вообще друг на друга.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Шарль, что ты задумал, и почему ты на коленях? Это же не...";
			link.l1 = "Элен, я люблю тебя. И я хочу прожить с тобой каждый день, отпущенный мне свыше. Потому, здесь и сейчас, перед этим морем и небом, я прошу тебя: Элен Беатрисс Шарп, окажи мне честь быть со мной, перед людьми и Богом, пока смерть не разлучит нас. Я, Шарль де Мор, шевалье де Монпе, спрашиваю тебя - ты станешь моей женой?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "Ты знаешь, мне эти формальности никогда не нравились, но с тобой я хоть на край света. А что до твоего вопроса, ответим так... ой, прости!";
				link.l1 = "Ничего, это всего лишь вино, и я никогда не любил эту рубаху...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Конечно да! Шарль, Да, да, и ещё раз да! Но... мы же не отправимся в пыльный фамильный замок выращивать репу, до конца дней своих?";
				link.l1 = "Ну, замок имеется и вполне себе пыльный, но мы там не задержимся. Наша жизнь - свобода и горизонт по курсу. И с тобой я хотел бы жить её вечно!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Тогда - выпьем за тебя, мой капитан, мой муж, и моя судьба!";
			link.l1 = "За тебя, моя любовь! И за наше будущее вместе, то ли ещё будет!!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Выпьем за тебя, мой капитан, мой муж, и моя судьба!";
			link.l1 = "За тебя, моя любовь! И за наше будущее вместе, то ли ещё будет!!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Итак, аббат Бенуа вернулся в свою церковь и готов нас обвенчать. Но я не полезу в платье даже ради такого случая! Как думаешь - это будет очередной фурор в местном бомонде?";
			link.l1 = "Элен, я тебя в любом наряде люблю, а они - пусть смирятся, не впервой. Но, я как раз хотел посоветоваться с тобой о гостях и церемонии.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "Да, тут есть проблема - большинство тех, с кем мы с радостью разделили бы этот день, в город на пушечный выстрел не подпустят, не то, что в церковь. Поэтому - давай обвенчаемся здесь, ну как положено, а потом махнём на Исла Тесоро и устроим там настоящий праздник, что скажешь?";
			link.l1 = "Звучит отлично! Так и поступим. С Аббатом Бенуа я поговорю, но нам надо разослать приглашения и ещё...";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "Спокойнее, капитан. Твоя будущая жена подхватит часть твоей ноши! Я устрою всё на Исла Тесоро и напишу нашим друзьям, ты только скажи: каким ты видишь этот праздник?";
			link.l1 = "Мой идеал - ты, я и самые близкие друзья. После всех официальных рож здесь на Мартинике, захочется душевного тепла.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Мы должны запомнить этот день. Зови всех! Пусть никто не уйдёт обиженным!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Уютно и по семейному - ты читаешь мои мысли! Нам придётся заскочить в Шарптаун, и я всё подготовлю. Я уже прикидывала - думаю полсотни бочонков рома и пару десятков бочек вина будет достаточно. Также, на еду и увеселения нам потребуется тысяч триста серебром.";
			link.l1 = "Напомни - почему не ты ведёшь корабельные финансы? Я всё достану. Заскочу к аббату, и мы отплываем в Шарптаун.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Значит, будем кутить как морские волки - сделаем! Нам придётся заскочить в Шарптаун, и я всё подготовлю. Но тут придётся серьёзно запастись - думаю, сотни бочонков рома и полсотни бочек вина должно хватить. И на прочие расходы уйдёт не меньше пятисот тысяч.";
			link.l1 = "Ну, я не совсем всё Береговое Братство имел в виду... А впрочем - давай! Припасы я достану. Вот только заскочу к аббату и мы отплываем в Шарптаун.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Элен");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Шарль, я разберусь с погрузкой, а потом отнесу письма барону и договорюсь с таверной. Ты не успеешь соскучиться?";
			link.l1 = "Я буду стараться изо всех сил! Или - просто полежу на песочке... не думал, что к штурму Тортуги подготовиться проще, чем к свадьбе.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Прошло несколько часов...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Успел отдохнуть, Шарль? Представляешь - местные ребята так разгулялись неделю назад, что сожгли 'Старый Дятел', но барон обещал что к нашему приезду её отстроят больше и лучше, чем была. Об остальном я договорилась, так что можно отчаливать.";
			link.l1 = "Надеюсь, наша свадьба не оставит тут ещё пару пепелищ. Эх, а мне ведь нравился местный притон - уютно, антуражно! Ну да ладно, милая, ты права - время не ждёт.";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Ян уже в городе, с ним Глэдис, представляешь? Вот уж не думала, что старики когда-нибудь, спляшут на моей свадьбе! Ох, гром и молния! Да в том кошмарном индейском городе-храме мне не было так... страшно.";
			link.l1 = "Всё хорошо, милая, всё хорошо. Я тоже волнуюсь - это нормально. Раз гости уже собрались - мне пора к отцу Бенуа. Узнаю, когда будет служба.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Чувствую я, это будет чертовски длинный и непростой день. Ладно - ты иди, Шарль, а я пока схожу проведаю Яна и Глэдис.";
			link.l1 = "Я рад, что они смогли приехать. Старик Свенсон любит тебя как родную дочь, а мадам МакАртур и подавно. Хорошо, что сегодня они будут рядом. Иди, и не волнуйся - всё будет прекрасно.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Элен");
		break;
		
		case "LongHappy_20":
			dialog.text = "Да.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Да.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Да.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Я, Шарль, Анри де Мор, шевалье де Монпе, беру тебя, Элен Беатрисс Шарп, в законные жёны, и клянусь хранить верность в счастье и в несчастии, в болезни и в здравии, а так же любить и уважать тебя все отпущенные мне дни.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Я, Элен Беатрисс Шарп, беру тебя Шарль Анри де Мор в законные мужья, и клянусь хранить верность в счастье и в несчастии, в здравии и в болезни, а также любить тебя и уважать все дни жизни моей.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Элен Беатрисс де Мор, мадам де Монпе - а что, звучит, да муж мой?";
			link.l1 = "Не слышал ничего прекраснее, жена моя!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "Знаешь - я думала, что это ничего не изменит, и, наверное, так и есть - я любила тебя и раньше и хотела прожить с тобой остаток дней, но этот день, эта служба... Я счастлива, Шарль! Счастлива как никогда раньше, и погляди на Глэдис и Яна - они словно светятся! Вокруг вообще столько счастливых лиц! Кстати - тебе пора обойти гостей, и принимать поздравления. Возвращайся, когда закончишь - нас ждут в Шарптауне, не забывай.";
			link.l1 = "Так и сделаю, дорогая. Один поцелуй и я пошёл!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "О, муж мой, ты уже поговорил с гостями?";
			link.l1 = "Пока нет, потерпи, милая, я скоро.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Да, никогда не выслушивал столько поздравлений за раз. И знаешь что - большинство ведь говорили искренне!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "Да, этот бомонд на удивление душевный - признаться, я ожидала больше фальши и лицемерия. Или - я просто счастлива настолько, что не замечаю ничего. Но - нас ведь заждались наши друзья в Шарптауне! Когда отплываем?";
			link.l1 = "Прямо сейчас. Полетим как на крыльях, прямо к дружескому застолью. Надеюсь, жена моя, ты не против провести эту ночь в нашей каюте?";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "О да, муж мой, ты знаешь толк в романтике! И не дёргайся так - я теперь имею право целовать тебя на публике... Вот, теперь пошли!";
			link.l1 = "Главное - не забыть приказать сняться с якоря...";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Ой, мой дорогой, я так рада! Сегодня у нас замечательный день...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Давай, Шарль. Этот брехун и в стену не попадёт!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Я в порядке, Шарль, всё хорошо. Как Натан? Что с ним?";
			link.l1 = "Сколько крови... Данни, подожди, он дышит? Я вижу, он дышит!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Быстрее, дорогой, нельзя терять время на разговоры!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Шарль, ты цел? Ну и бойня... Прости - нас задержали - целая дюжина этих крыс пряталась под шканцами. Пришлось с ними повозиться!";
			link.l1 = "Не страшно, я справился. Рад, что смог закончить нашу с Жаком историю... наконец-то. Он получил по заслугам за все свои дела.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Хорошо, муж мой - давай, заканчивай тут и возвращаемся. Мне не даёт покоя Натан, как он там? Он ведь меня прикрыл от того выстрела.";
			link.l1 = "Ты права, милая, я тоже о нём беспокоюсь. Иди - я сразу за тобой.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Кстати, мы нашли Маркуса - он был в трюме, связанный и без сознания, словно подарок на рождество.";
			link.l1 = "Но он жив, ведь так?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Не беспокойся, любимый, барон Тиракс ещё всех нас переживёт. Только очнулся и уже буянить - требует саблю и на мостик.";
			link.l1 = "Узнаю старину Маркуса. Пусть отдохнёт пока. А мы закончим здесь, и на берег.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Мне так жаль, любимый. Сначала наш верный друг Тичингиту, потом Джино... Барбазона надо было убить дюжину раз за все его подлости!";
				link.l1 = "К сожалению, я сделал это лишь единожды. Мне тоже грустно... но мы победили, а Жак Добряк больше никому не сможет навредить.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Мне так жаль Джино, Шарль!! Я как узнала не поверила! Как ты, любимый?";
					link.l1 = "Тоже не укладывается в голове... глупо всё вышло, нечего сказать. Не так я себе представлял этот день.";
				}
				else
				{
					dialog.text = "Интересно, хронисты напишут о сражении в Бухте Приватира, как думаешь? Бароны Берегового братства сошлись в открытом бою - испанские власти утирают слезу умиления! Но, мы опять победили! Друзья живы, а враги мертвы - славный подарок к свадьбе!";
					link.l1 = "Да уж, тот ещё праздник вышел, но мы справились, любимая. Мы справились.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Всё это необходимо как следует запить, вот что я думаю. Пойдём, Данни нашла нам домик тут на окраине - не хочу сейчас возвращаться на корабль. Посидим, помянем наших друзей, как подобает.";
			link.l1 = "Да, Элен, пойдём.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Мне так жаль Джино, Шарль!! Я как узнала не поверила! Как ты, любимый?";
				link.l1 = "Тоже не укладывается в голове... глупо всё вышло, нечего сказать. Не так я себе представлял этот день.";
			}
			else
			{
				dialog.text = "Повидался с Хоуком, или Данни тебя не пустила? Она и меня выставила, когда Джино сказал, что опасность миновала. Хорошо, что всё обошлось. Друзья живы, а враги мертвы - славный подарок к свадьбе!";
				link.l1 = "Да, мы победили - Барбазон кормит рыб, а бароны собирают остатки своих команд на берегу. Сражение в бухте Приватира закончено.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Шарль, я понимаю, что ты на ногах, наверное, еле держишься, но я была в таверне, и, представь, чего я наслушалась от местного халдея?";
			link.l1 = "Да, я только от Яна узнал - он сюда тоже приходил. Сдаётся мне, наш суровый маског пошёл в разнос. Давай-ка прогуляемся до бухты Сабу Матила - кое-кто видел его, ушедшего в том направлении.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Ну Тичингиту, ну герой! Я едва со смеху не лопнула! Почему этот прекрасный обычай нынче не в ходу, а? Ладно - ты уже спишь на ходу, любимый. Пойдём, Данни нашла нам домик тут на окраине - тебе надо отдохнуть.";
			link.l1 = "Веди... кажется, я заснул ещё на том пляже.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "tonzag_jailed":
			dialog.text = "... Всё нормально.";
			link.l1 = "Вот и славно.";
			link.l1.go = "exit";
			link.l2 = "Точно?";
			link.l2.go = "tonzag_jailed_1";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Да.";
			link.l1 = "Вот и славно.";
			link.l1.go = "exit";
			link.l2 = "Да ладно тебе, я же вижу, что что-то не так!";
			link.l2.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Да нормальная я, чего пристал?\nШарль, иди к чёрту! Я ненавижу подземелья, ненавижу тебя и ненавижу этот сраный остров!\nВытащи меня отсюда немедленно!\nПрости меня пожалуйста... Я правда не люблю казематы, не трогай меня!";
			link.l1 = "Извини. Мы все чего-то, да боимся.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "АААА! Выпустите нас отсюда! " + pchar.name + ", сделай же что-нибудь!";
			link.l1 = "Возьми себя в руки!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Мой капитан, противник разворотил кусок обшивки на второй палубе и высадил десант. Бои идут по всему кораблю, а орудийные расчёты почти все выбиты! Надо выручать наших и спасать Эркюля! Сам пойдёшь или отправишь меня?";
			link.l1 = "В этот раз я сам, Элен! Принимай командование кораблём и уводи нас отсюда!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Так точно, мой капитан. Только умоляю, будь осторожен, а я тебя не подведу!";
			link.l1 = "Я знаю, Элен. И ты тоже, будь поосторожней там!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Победа, мой капитан! Десант уничтожен, противник предпочёл ретироваться и ушёл на юг. Состояние корабля приемлемое. Экипажа осталось в строю: " + GetCrewQuantity(pchar) + " человек. Доклад окончен!";
			link.l1 = "Спасибо, Элен, а что...";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Раздевайся, победитель, и делай со мной, что хочешь!";
			link.l1 = "Э...";
			link.l1.go = "tonzag_after_victory_2";
			link.l2 = "Давай!";
			link.l2.go = "tonzag_after_victory_2";
		break;
		
		case "tonzag_after_victory_2":
			dialog.text = "Ох, привет, Эркюль. Прости, ты нам немного мешаешь! Но, чёрт побери, я рада видеть тебя живым и в чужой крови - естественное для тебя состояние, ха!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog");
		break;
		
		case "tonzag_after_victory_3":
			dialog.text = "";
			link.l1 = "Ну, Элен, ты даёшь!";
			link.l1.go = "tonzag_after_victory_4";
		break;
		
		case "tonzag_after_victory_4":
			dialog.text = "Я ещё даже не начинала, мой капитан. Отметим?";
			link.l1 = "Меня не нужно уговаривать!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Не смотри, не смотри, не смотри... Это какой-то другой мир, мой капитан! Так нельзя!";
			link.l1 = "Я думаю, это теперь наш мир, дорогая. И ты права, давай не будем задерживаться.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Боюсь, вашим девицам придётся встать в очередь, Родриго.";
			link.l1 = "Этот разговор явно идёт не туда, ха-ха! Договорились, завтра прибудем в церковь. Помолиться, разумеется.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Я горжусь тобой, любимый!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Ну что, Шарль...";
			link.l1 = "О чём задумалась, Элен?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "О том, что теперь самой скандальной паре Кариб принадлежит уже целых два острова. Моя пиратская вольница и твоя земля обетованная - как думаешь, долго ли останется таким местам, когда в этот край окончательно придёт цивилизация?";
			link.l1 = "На наш с тобой век хватит, дорогая. А потом эту историю будут рассказывать уже другие. Главное, чтобы нам с тобой было хорошо.";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Кстати об этом... Я сейчас собираюсь пойти наверх: надо зажечь свечи, разложить постель, сделать запись в дневнике и вообще...";
			link.l1 = "Я немного задержусь здесь, а потом обязательно поднимусь к тебе, помогать.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Буду ждать...";
			link.l1 = "";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestCheckDelay("Helena_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "drinking_refuse":
			dialog.text = "Ты такой весь из себя занятой? Жаль, но я понимаю. Мне тоже сейчас будет чем заняться.";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
			
			pchar.questTemp.HelenDrinking.Result = "no_visit";
			CloseQuestHeader("HelenDrinking");
		break;
		
		case "drinking_accept":
			dialog.text = "Приятно, что помнишь. Я хотела сказать тебе, что очень благодарна. Не каждый день тебя спасают от... сам знаешь от чего. Пошли пить, я угощаю.";
			link.l1 = "Элен... Что скажет Глэдис?";
			link.l1.go = "drinking_accept_1";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToHouse");
		break;
		
		case "drinking_accept_1":
			dialog.text = "Очень смешно, " + pchar.name + ". Пойдём и не беси меня.";
			link.l1 = "Это свидание?";
			link.l1.go = "drinking_accept_1_1";
			link.l2 = "Иду, не бесись.";
			link.l2.go = "drinking_accept_1_2";
		break;
		
		case "drinking_accept_1_1":
			dialog.text = "Ха-ха! И не надейся! Я столько не выпью!";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_accept_1_2":
			dialog.text = "Вот и молодец.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_in_tavern":
			dialog.text = "";
			link.l1 = "... у неё было много достоинств, но пить она не умела. Вот так мы и познакомились.";
			link.l1.go = "drinking_in_tavern_1";
			link.l2 = "... отец настаивал на военной службе. Я поддался и поехал с рекомендательным письмом в Париж. Но до нужного адреса не донес и стал художником.";
			link.l2.go = "drinking_in_tavern_2";
		break;
				
		case "drinking_in_tavern_1":
			dialog.text = "Ага, ну я уже поняла о каких достоинствах ты говоришь. Как её звали?";
			link.l1 = "Лулу.";
			link.l1.go = "drinking_in_tavern_1_1";
		break;
		
		case "drinking_in_tavern_1_1":
			dialog.text = "Лу-лу... Ты своими рассказами окончательно убил Париж в моих глазах. Я-то думала там - жизнь, а выходит какой-то расфуфыренный бордель.";
			link.l1 = "Осуждаешь бордели?";
			link.l1.go = "drinking_in_tavern_1_2";
		break;
		
		case "drinking_in_tavern_1_2":
			dialog.text = "Да, мой капитан, и не понимаю мужчин, которые их посещают.";
			link.l1 = "(уткнуться в кружку)";
			link.l1.go = "drinking_in_tavern_1_4";
			link.l2 = "(страшно закашляться)";
			link.l2.go = "drinking_in_tavern_1_4";
			link.l3 = "Э... Каждый из мужчин выбирает для себя... Наверное?";
			link.l3.go = "drinking_in_tavern_1_4";
		break;
		
		case "drinking_in_tavern_1_4":
			dialog.text = "(смеётся) Ха! Ты бы видел своё лицо! Испугался? Давай ещё по одной! За Париж!";
			link.l1 = "За Париж!";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_2":
			dialog.text = "(смеётся) Т-ты?! Художник? То есть, краса и гордость английского флота, насильник и просто сукин сын Донован сдох от руки парижского художника? Эх, жаль, ты не надел на абордаж своё белоснежное жабо и не забил эту скотину тростью!";
			link.l1 = "Да, глупо получилось. Жабо, очень некстати, было в стирке.";
			link.l1.go = "drinking_in_tavern_2_1";
		break;
		
		case "drinking_in_tavern_2_1":
			dialog.text = "(смеётся) Ух, спасибо, Шарль. Не знаю уж, как у нас сегодня будет, но вечер уже точно прошёл не зря. Я даже, может быть, разрешу тебе нарисовать мой портрет. Но, учти, не в том же стиле, как ты своих парижских девушек рисовал!";
			link.l1 = "Ха! Это если я соглашусь ещё.";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_3":
			dialog.text = "Извини, мой капитан, вот слушаю про твои похождения и жизнь благородных... куртизанок обоих полов. Акула меня дери, ни за что не поверю, что ты ничем более полезным не занимался! Не смей даже рассказывать мне, что ты только и делал, что пачкал холсты да просаживал папины деньги. Ты бы не выжил у нас и дня, будь это так.";
			link.l1 = "У меня... были и другие увлечения.";
			link.l1.go = "drinking_in_tavern_" + pchar.HeroParam.HeroType;
		break;
		
		case "drinking_in_tavern_herotype_3":
			dialog.text = "";
			link.l1 = "Я совмещал жизнь при дворе и службу в войсках, но не так... хе-хе, как хотел отец, конечно. Пара побегов через окно и одна попойка - и вот я уже сдружился с гвардейцами. Ну и нахватался всякого, окреп телом. Старшие товарищи научили держать удар, носить доспехи, работать палашом и правильно отдыхать. Вот последний момент мне особенно удавался, конечно. Ты не поверишь, но не каждый может с утра до обеда махать мечом, а потом пить с обеда до следующего утра.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_1":
			dialog.text = "";
			link.l1 = "Думаешь, легко было в столице дворянину с худым именем и кошельком, потерявшим папенькино рекомендательное письмо в первый же день? Я должен был заявить о себе и не спускать никому насмешки в свой адрес. Домашние уроки по фехтованию не забылись, и я отвечал дуэлью на всякий косой взгляд. А потом втянулся. Понял, как шпага открывает предприимчивому человеку разные двери. Вроде никого не убил и успел уехать до того, как нарваться на опытного бретера, который меня бы и прирезал.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_4":
			dialog.text = "";
			link.l1 = "На кладбищах много времени проводил. Ты не подумай ничего - просто мода была такая в моём кругу. Для куражу шли ночью на кладбище, ставили на ограду пустые бутылки и стреляли по ним на скорость. За ночь высаживали сотню пуль и ящик шампанского. Теперь, конечно, мне стыдно за такое поведение, а тогда победитель срывал солидный куш и получал некие... преференции у женской части двора. В ход шло всё - я даже немного с пороховыми смесями мудрил. Но вот почему никто из нас не догадался научится бумажные патроны делать - до сих пор не пойму.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_2":
			dialog.text = "";
			link.l1 = "Учился, и довольно усердно - даже был близок к поступлению в Сорбонну. Поработал в конторе, пока не надоело, да и вообще - занимался всем понемногу. Учитель, старый друг отца, предпочитал практику теории, так что довелось мне увидеть Париж со всех сторон и пообщаться с разными людьми: от бандитов до вельмож. Всё это потом очень пригодилось уже тут.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_4":
			dialog.text = "И... всё? Значит что-то в тебе ещё есть, мой капитан. Что-то, что ты сам пока в себе не увидел. За тебя!";
			link.l1 = "Хороший тост!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernChange");
		break;
		
		case "drinking_my_background":
			dialog.text = "";
			link.l1 = "Расскажи мне свою историю, Элен. Мои столичные приключения меркнут в сравнении с девушкой, которая в неполные тридцать командует шхуной с сотней мужиков на борту.";
			link.l1.go = "drinking_my_background_1";
		break;
		
		case "drinking_my_background_1":
			dialog.text = "Неполные тридцать, а, Шарль? За такие сильные комментарии тебе придётся поставить следующую выпивку! Все мои парни погибли, и я больше не командую шхуной. Откровенно говоря, и не знаю, доведётся ли ещё.";
			link.l1 = "Прости, Элен, не хотел раны бередить. Но почему же ты думаешь, что с карьерой капитана покончено?";
			link.l1.go = "drinking_my_background_2";
		break;
		
		case "drinking_my_background_2":
			dialog.text = "Потому что моя команда мертва, а другая меня ни за что не примет. Эх! Ладно, мой капитан, ты много рассказывал о своей жизни, теперь моя очередь! Хватит с меня отмалчиваться и искать дно в своей кружке.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_3";
		break;
		
		case "drinking_my_background_3":
			dialog.text = "Мой случай, Шарль, уникальный. Отец был одним из лучших мореходов в этих краях, состоял на хорошем счету у Лесного Дьявола, команда его боготворила, и он любил меня больше жизни.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_4";
		break;
		
		case "drinking_my_background_4":
			dialog.text = "Убери хоть одно, и он либо отправил бы меня в Лондон жить в... цивилизации, либо оставил бы чахнуть тут, как маму. Всё сложилось: я хотела свободы, а свободу, - настоящую свободу, Шарль, - даёт только умелое командование боевым кораблём с верной командой. И отец мне дал всё это. Я ходила с ним в море с двенадцати лет, первые полгода гоняла крыс в трюме, и только после этого мне позволили работать с матросами.";
			link.l1 = "Шон МакАртур сделал тебя трюмной крысой? Извини, Элен, но оттуда же нет возврата! Как команда приняла тебя?";
			link.l1.go = "drinking_my_background_5";
		break;
		
		case "drinking_my_background_5":
			dialog.text = "Ну, возможно, я немного сгущаю краски ради красивой истории? Команда отца меня приняла, таких уж он людей набирал. Но с тех пор я боюсь... трюмов и вообще любых маленьких тёмных помещений. Ха! Свенсон отца чуть не убил, как узнал!";
			link.l1 = "Ты ему дорога. Он явно сыграл роль в твоей судьбе, не меньшую, чем Шон.";
			link.l1.go = "drinking_my_background_6";
		break;
		
		case "drinking_my_background_6":
			dialog.text = "Ага. Все бароны прямо сказали отцу, что он придурок, но именно Лесной Дьявол дал добро и пожал ему руку после того, как я побила рекорд экипажа по карабканью на марсы. Этот момент останется со мной навсегда: ликующие крики команды и, куда не глянь, чистый морской горизонт. И одобрительный взгляд отца, я не могла его видеть, но чувствовала всем сердцем.";
			link.l1 = "Мой триумф закончился падением с вант в первый же день на пути к Гваделупе.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.TakeFolke")) {
				link.l1 = link.l1 + " Взгляд моего штурмана, Делюка, тоже был очень красноречив."
			}
			link.l1.go = "drinking_my_background_7";
		break;
		
		case "drinking_my_background_7":
			dialog.text = "Ах-ха-ха! Могу себе представить! Ничего, то было давно, сейчас ты - настоящий морской волк!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_8";
		break;
		
		case "drinking_my_background_8":
			dialog.text = "За наши триумфы!";
			link.l1 = "За них!";
			link.l1.go = "drinking_my_background_12";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "... А дальше я постепенно росла в должности, прислуживала при капитанском столе на советах отца с офицерами, многому училась. В боевые походы меня начали брать только с пятнадцати, и в первом же я убила человека. Мерзкий был поход, зря мы в понедельник с якоря снялись... Ох, зря.";
			link.l1 = "В пятнадцать лет? Ты меня пугаешь, Элен.";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "Я даже не поняла, что произошло. У торгаша голландца был свой авангард - наёмники Компании. Они решили сыграть внаглую и пошли в контратаку на наш ют. А я, дура, всякий страх потеряла и высунула свою блондинистую голову наружу. Ну и получила по ней рукояткой пистолета. Правда, за секунду до того, я успела воткнуть свою шпажку в какого-то амбала из Компании.";
			link.l1 = "Господи, а что Шон? Как он не выгнал тебя на берег после такого?";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_13":
			dialog.text = "Отцу в тот день тоже сильно досталось, а вид моей разбитой дурной башки ему здоровья не добавлял. Он стал чахнуть, никто, наверное, и не замечал, кроме меня. А потом его не стало. По завещанию мне досталась 'Радуга' с командой и средства, достаточные для содержания корабля на год.";
			link.l1 = "И команда приняла тебя как капитана?";
			link.l1.go = "drinking_my_background_14";
		break;
		
		case "drinking_my_background_14":
			dialog.text = "Мы не в сказке живём, мой капитан. Некоторые встретили волю отца в штыки - дело приняло не очень приятный оборот\nЕсли бы хотя бы один матрос покинул 'Радугу', отказавшись служить под моим началом, то пришлось бы мне туго. Но вмешался Свенсон и всех приструнил. Команду тогда никто не покинул... открыто. Семь лет я командовала своей красавицей, перевозила для Лесного Дьявола товары неясного происхождения, искала клады, жила... Но теперь это всё в прошлом.";
			link.l1 = "Не в прошлом. Верю, суждено ещё тебе ходить под своим флагом! Выпьем за это!";
			link.l1.go = "drinking_my_background_sea";
			link.l2 = "Корабль мы не вернём, но твоя рапира всё ещё при тебе.";
			link.l2.go = "drinking_my_background_land";
		break;
		
		case "drinking_my_background_sea":
			dialog.text = "Знаешь, когда ты такое говоришь, я сразу верю. Выпьем!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_COMMERCE, 5);
			AddCharacterSkill(npchar, SKILL_ACCURACY, 5);
			AddCharacterSkill(npchar, SKILL_CANNONS, 5);
			AddCharacterSkill(npchar, SKILL_SAILING, 5);
			AddCharacterSkill(npchar, SKILL_REPAIR, 5);
			AddCharacterSkill(npchar, SKILL_GRAPPLING, 5);
			AddCharacterSkill(npchar, SKILL_DEFENCE, 5);
			notification("Морские навыки +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "sea";
		break;
		
		case "drinking_my_background_land":
			dialog.text = "Но принесёт ли мне счастье моя рапира? Ответ, вероятно, где-то на дне этой кружки. Выпьем!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_F_LIGHT, 5);
			AddCharacterSkill(npchar, SKILL_FENCING, 5);
			AddCharacterSkill(npchar, SKILL_F_HEAVY, 5);
			AddCharacterSkill(npchar, SKILL_PISTOL, 5);
			AddCharacterSkill(npchar, SKILL_FORTUNE, 5);
			AddCharacterSkill(npchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(npchar, SKILL_SNEAK, 5);
			notification("Личные навыки +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "land";
		break;
		
		case "drinking_my_background_15":
			dialog.text = "Я тут подумала о твоём рассказе про жизнь в Европе... Смотри, вот ты - столичный франт, а я - обычная девушка, но мы уже сделали себя имя в самом опасном уголке мира.";
			link.l1 = "Звучит как тост! Значит, нас что-то объединяет?";
			link.l1.go = "drinking_my_background_16";
		break;
		
		case "drinking_my_background_16":
			dialog.text = "Ну, я стою на плечах своего отца. Про тебя точно не знаю, но, возможно, твоя семья всё же оказала на тебя не меньшее влияние? Может, ты пока даже не осознаешь это?";
			link.l1 = "Вот вытащу родственничка из темницы, у него и спрошу.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernEmpty");
		break;
		
		case "drinking_game":
			dialog.text = "Ну вот и всё, мой капитан. Историями обменялись, пора и честь знать.";
			link.l1 = "Гм, я рассчитывал на другое окончание вечера.";
			link.l1.go = "drinking_game_1";
		break;
		
		case "drinking_game_1":
			dialog.text = "Вечер ещё не закончился. Предлагаю игру: если правильно разыграешь свои карты, то, быть может, молитвы твои будут услышаны.";
			link.l1 = "В карты будем играть? Это можно!";
			link.l1.go = "drinking_game_2";
		break;
		
		case "drinking_game_2":
			dialog.text = "Полегче, морской волк. На раздевание я с тобой играть не стану.";
			link.l1 = "Да, ты права, Элен. Тут нам не хватит приватности.";
			link.l1.go = "drinking_game_3";
		break;
		
		case "drinking_game_3":
			dialog.text = "Нам много чего не хватает, Шарль... Это не карточная игра, но не переживай, ставлю на то, что ты в ней мастер. 'Я никогда не' - знакомо?";
			link.l1 = "Знакомо. Из прошлой жизни. И часто ты в неё поигрываешь?";
			link.l1.go = "drinking_game_4";
		break;
		
		case "drinking_game_4":
			dialog.text = "Всегда хотела попробовать, но было не с кем.";
			link.l1 = "Это достаточно смелая игра для первой совместной попойки. Уверена?";
			link.l1.go = "drinking_game_5";
			link.l2 = "Кстати, а где все? Мы что, одни тут?";
			link.l2.go = "drinking_game_6";
		break;
		
		case "drinking_game_5":
			dialog.text = "Да, после недавних событий мне очень нужно пожить. Поделать глупости, понимаешь?";
			link.l1 = "Нет уж, это всегда плохо заканчивается, Румба.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Начнём! Дамы вперёд!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_6":
			dialog.text = "Отослала народ по домам - нечего посторонним уши греть.";
			link.l1 = "Нет уж, это всегда плохо заканчивается, Румба.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Начнём! Дамы вперёд!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_refuse":
			dialog.text = "Жаль, но может ты и прав. Тогда ещё по одной?";
			link.l1 = "Конечно! Спасибо за вечер!";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_refuse_1":
			dialog.text = "Я распорядилась: комната наверху - твоя. Там сидел какой-то важный французский офицер, но ребята Лесного Дьявола вежливо попросили освободить помещение. Иди спать: на улицу, или, чего доброго, в море, я тебя в таком виде не отпущу.";
			link.l1 = "Есть, мэм!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToTavernRoom");
		break;
		
		case "drinking_game_accept":
			dialog.text = "Ха! И-к! Значит, ты начинаешь!";
			link.l1 = "Аккуратней, дорогая! Гм. Я никогда не гонял крыс в трюме!";
			link.l1.go = "drinking_game_accept_1";
		break;
		
		case "drinking_game_accept_1":
			dialog.text = "Вот значит как? С тобой надо ухо востро! (пьёт)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_2";
		break;
		
		case "drinking_game_accept_2":
			dialog.text = "Брр! Как вспомню конечно... Ну держись, красавчик: я никогда не падала с вантов!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_3";
		break;
		
		case "drinking_game_accept_3":
			dialog.text = "";
			link.l1 = "Ловко! Позвольте, мадемуазель, выпить за вас! (пьёт)";
			link.l1.go = "drinking_game_accept_4";
		break;
		
		case "drinking_game_accept_4":
			dialog.text = "";
			link.l1 = "Я никогда не был суеверным.";
			link.l1.go = "drinking_game_accept_5";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 1;
			SetCamShuttle(loadedLocation);
			SetPitch(0.95);
		break;
		
		case "drinking_game_accept_5":
			dialog.text = "А ещё моряк называется! Сам знаешь, какой мы народ. Никогда не знаешь, что принесёт рейс, не знаешь, когда и где увидишь сушу, если вообще увидишь. Приходится искать ответы вне карт и навигационных инструментов! Твоё здоровье! (пьёт)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_6";
		break;
		
		case "drinking_game_accept_6":
			dialog.text = "А девиц, которых ты рисовал с натуры... Им нравился результат?";
			link.l1 = "Картины им нравились не всегда, но, ммм... результат - всегда.";
			link.l1.go = "drinking_game_accept_7";
		break;
		
		case "drinking_game_accept_7":
			dialog.text = "Шарль! Если бы мы встретились тогда, я бы тебя пристрелила или взяла в плен за выкуп. И, кстати, я кисти в руки не брала никогда.";
			link.l1 = "Эй! Ну это совсем банально. Дорогая Элен, если я начну перечислять то, что ты в руки никогда не брала...";
			link.l1.go = "drinking_game_accept_8";
		break;
		
		case "drinking_game_accept_8":
			dialog.text = "Ладно, ладно, буду играть честнее. Твой ход, мой капитан.";
			link.l1 = "(пьёт) И-ик! Кхм... Я никогда не получал от моих натурщиц рукояткой пистолета по голове.";
			link.l1.go = "drinking_game_accept_9";
		break;
		
		case "drinking_game_accept_9":
			dialog.text = "(пьёт) Уфф. Мы как-то неправильно играем в эту игру, дорогой. Я думала, мы будем пить и узнавать друг друга, а вместо этого обмениваемся колкостями и... и... И-ик! А-ать!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_10";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 2;
			SetCamShuttle(loadedLocation);
			SetPitch(0.90);
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Давай поинтересней! И желательно что-нибудь не из того, о чём мы час назад общались!";
			link.l1 = "Я никогда не просыпался в незнакомом месте после попойки.";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "А-ать! Чёрт-те что, Шарль! (пьёт)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_11":
			dialog.text = "Я... и-ик... поверить не могу. Признаю, виновна, малышка Румба доставала дна. Но никогда не сидела в тюрьме!";
			link.l1 = "Откуда ты...?";
			link.l1.go = "drinking_game_accept_12";
		break;
		
		case "drinking_game_accept_12":
			dialog.text = "Ха-ха-ха! Пей, пей!";
			link.l1 = "Я об этом пожалею. (пьёт)";
			
			if (IsCharacterEquippedArtefact(pchar, "totem_01")) {
				link.l1.go = "drinking_game_accept_13";
			} else {
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_LightsOut");
			}
		break;
		
		case "drinking_game_accept_13":
			dialog.text = "Давай, милый мой. Последний вопрос и последний шанс обыграть меня!";
			link.l1 = "Нет... Я... Давай воздухом подышим.";
			link.l1.go = "drinking_game_enough";
			link.l2 = "Я часто выпивал, но так... Я никогда так не н-напивался с д-девушкой. П-право с-слово, п-пьянство всё же в-великий грех...";
			link.l2.go = "drinking_game_accept_14";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 3;
			SetCamShuttle(loadedLocation);
			SetPitch(0.85);
		break;
		
		case "drinking_game_enough":
			dialog.text = "Эх!";
			link.l1 = "";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_accept_14":
			dialog.text = "";
			link.l1 = "П-постой... Ты не пьёшь?";
			link.l1.go = "drinking_game_accept_15";
		break;
		
		case "drinking_game_accept_15":
			dialog.text = "Ах-ха-ха! Вот умора! Высоко прицел взял, мой капитан. Да будет... и-ик! ... тебе известно...";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_16";
		break;
		
		case "drinking_game_accept_16":
			dialog.text = "Что я имею несчастье жить в мужском коллективе, и вести себя приходится осторожно. Я - честная девушка.";
			link.l1 = "Р-рад за тебя, Э-элен.";
			link.l1.go = "drinking_game_accept_17";
		break;
		
		case "drinking_game_accept_17":
			dialog.text = "Будешь рад ещё больше, ведь я победила! Но, признаться честно, я тоже никогда так не напивалась с парнем.";
			link.l1 = "(молча выпить) Т-туше. Поздравляю... у-у-у...";
			link.l1.go = "drinking_game_accept_18";
		break;
		
		case "drinking_game_accept_18":
			dialog.text = "Эй-эй-эй! Капитан, ты куда? Обиделся что-ли?";
			link.l1 = "Мне... надо... от-отлучиться. Щас вот - шпагу только найду...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_ExitTavern");
		break;
		
		case "drinking_at_svenson":
			dialog.text = "Кэп, ты готов? Обратного пути не будет, а если что пойдёт не так - жениться заставлю.";
			link.l1 = "Уф! Дай хоть свежим воздухом подышать! Ты точно этого хочешь, Элен?";
			link.l1.go = "drinking_at_svenson_1";
		break;
		
		case "drinking_at_svenson_1":
			dialog.text = "Да, чёрт возьми, и не стой столбом! Мне надо забыться, ну хоть на ночь!";
			link.l1 = "Боюсь, после этой ночи забыться захочется уже мне. Пойдём, пока весь город не разбудили.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_EnterSvenson");
		break;
		
		case "drinking_give_key":
			dialog.text = "Кэп, держи ключ и поднимайся наверх. Там должен быть сундук, ты наверняка видел его, когда у Свенсона был. Забирай бочонок и сразу дуй назад.";
			link.l1 = "Постой, дорогая, а почему это я должен грабить твоего патрона?";
			link.l1.go = "drinking_give_key_1";
			
			GiveItem2Character(pchar, "key3");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_give_key_1":
			dialog.text = "Не глупи, я тут с детства бываю: если хозяева вернутся, то смогу и отбрехаться, и тебя прикрыть. Ну же, чего парус приспустил?";
			link.l1 = "Резонно, сразу видно контрабандистку. Жди, я мигом.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GotKey");
		break;
		
		case "drinking_got_whiskey":
			dialog.text = "Достал?!";
			link.l1 = "А то! Не первый сундук, который я обчистил, и явно не последний!";
			link.l1.go = "drinking_got_whiskey_1";
		break;
		
		case "drinking_got_whiskey_1":
			dialog.text = "Я тобой горжусь! Ха! Первостатейный ирландский виски 'Бушмилс'! Такого пойла нам в таверне не подадут.";
			link.l1 = "Звучит недурно, но разве Свенсон его не хватится?";
			link.l1.go = "drinking_got_whiskey_2";
		break;
		
		case "drinking_got_whiskey_2":
			dialog.text = "Обязательно хватится, но сам он такое не пьёт. Он, кажись, припас его в подарок для своего пиратского дружка Додсона, а тот то ли сгинул, то ли убил кого-то...";
			link.l1 = "Это ужасно! Ужасно, что пропадёт такой подарок. Хватаем бочонок и срочно меняем дислокацию!";
			link.l1.go = "drinking_got_whiskey_3";
		break;
		
		case "drinking_got_whiskey_3":
			dialog.text = "Хорошо сказано, кэп. Но у нас осталось ещё одно препятствие. Скажи мне: ты что-то ещё брал из сундука? Отвечай честно.";
			if (HelenDrinking_RobbedSvenson()) {
				link.l1 = "Брал, привычка, знаешь ли.";
				link.l1.go = "drinking_got_whiskey_notbelieve";
			}
			
			link.l2 = "Нет. Уж не знаю, пират я или нет, но точно не вор.";
			link.l2.go = "drinking_got_whiskey_believe";
			
			if (HelenDrinking_RobbedSvenson()) {
				link.l2.go = "drinking_got_whiskey_notbelieve";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
				notification("Элен не одобряет", "Helena");
				pchar.questTemp.HelenDrinking.RobbedSvenson = true;
			}
		break;
		
		case "drinking_got_whiskey_believe":
			dialog.text = "Почему-то я тебе верю... дура!";
			link.l1 = "";
			link.l1.go = "drinking_get_out";
		break;
		
		case "drinking_got_whiskey_notbelieve":
			dialog.text = "Вот сходи и убедись, что точно ничего не брал.";
			link.l1 = "";
			link.l1.go = "exit";
			if (!HelenDrinking_RobbedSvenson()) {
				AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
				TakeItemFromCharacter(pchar, "cask_whisky");
				sld = ItemsFromID("cask_whisky");
				sld.price = sld.pricebak;
				DeleteAttribute(sld, "pricebak");
			}
			
			NextDiag.TempNode = "drinking_got_whiskey_notbelieve";
		break;
		
		case "drinking_get_out":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
			TakeItemFromCharacter(pchar, "cask_whisky");
			sld = ItemsFromID("cask_whisky");
			sld.price = sld.pricebak;
			DeleteAttribute(sld, "pricebak");
		break;
		
		case "drinking_at_fort":
			dialog.text = "Эй-эй, дорогой! Чего взгляд уронил? Моё овеянное морским ветром личико чуть выше!";
			link.l1 = "Уф, ну и костюм у тебя, конечно. Такой экономии на швейном материале я ещё не видел. А я... и-ик! Я видел многое! Но это... Однако, это лучшее, что я видел.";
			link.l1.go = "drinking_at_fort_1";
			locCameraFromToPos(-1.65, 44.45, 76.64, true, -5.93, 42.10, 70.13);
		break;
		
		case "drinking_at_fort_1":
			dialog.text = "Все вы так говорите, но тебе я почему-то верю! Правда нравится?";
			link.l1 = "Ну разумеется, он очень выгодно подчеркивает твои достоинства, хотя...";
			link.l1.go = "drinking_at_fort_2";
		break;
		
		case "drinking_at_fort_2":
			dialog.text = "Ну вот, всё испортил!";
			link.l1 = "... хотя не сомневаюсь, что среди простого люда он производит настоящий фурор!";
			link.l1.go = "drinking_at_fort_3";
		break;
		
		case "drinking_at_fort_3":
			dialog.text = "Странно, что фурор не производит повсеместное желание простого и не очень люда носить плотную европейскую одежду в такую жару. От этого наши деревни выглядят ещё более комично... Мне нравится мой наряд, Шарль. В нём я чувствую себя красивой, а это важно для женщины.";
			link.l1 = "Ты и без этого наряда останешься такой же красивой, Элен.";
			link.l1.go = "drinking_at_fort_4";
		break;
		
		case "drinking_at_fort_4":
			dialog.text = "Осторожней, мой капитан! А то наговоришь приятностей и совратишь бедную девушку!";
			link.l1 = "Если она не против, то и я не против.";
			link.l1.go = "drinking_at_fort_5";
		break;
		
		case "drinking_at_fort_5":
			dialog.text = "Хи-хи! Лучше поспрашивай меня ещё о чём-нибудь. Мне приятно, когда ты меня расспрашиваешь о всяком.";
			link.l1 = "Тогда давай дожмём вопрос с твоим костюмом. Я не верю, что морские волки могут серьёзно воспринимать капитана в таком наряде.";
			link.l1.go = "drinking_at_fort_6";
		break;
		
		case "drinking_at_fort_6":
			dialog.text = "А я не верю, что морские волки в принципе могут воспринимать бабу в роли капитана, так что мой наряд едва ли добавил мне проблем. А может, и не успел добавить, вещь так-то новая. Сама сшила!\nАх-ха-ха! Раньше я носила один из этих... ну как их? Наши военные ещё их носят! Б-р-р... Как увижу сейчас такой, плохо становится.";
			link.l1 = "Мундиры?";
			link.l1.go = "drinking_at_fort_7";
		break;
		
		case "drinking_at_fort_7":
			dialog.text = "О, точно, мундир! Красный мундир! Вот как у этого вот.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.GenQuest.BlockDialogCamera = true;
			AddDialogExitQuestFunction("HelenDrinking_OfficerAtFort");
		break;
		
		case "drinking_at_fort_7_1":
			dialog.text = "Ой, простите, майор, позвольте угостить вас прекрасным ирландским виски в качестве... и-ик! Комплимента, вот.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog2");
		break;
		
		case "drinking_at_fort_7_2":
			dialog.text = "У Шарля ведь не будет проблем, правда, майор? Скажите мне, что не будет, пожалуйста-пожалуйста!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog4");
		break;
		
		case "drinking_at_fort_8":
			dialog.text = "Как же я рада! Согласна!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToVillage");
		break;
		
		case "drinking_at_miskito":
			dialog.text = "У-уф. А у меня вот что есть!";
			link.l1 = "Элен... Ты что, собираешься это использовать... для поднятия настроения?!.. Даже думать не смей! Дурман способен полностью подчинить себе человека, лишить сил, подавить волю! Оглянуться не успеешь - и ты живой труп, а потом, очень быстро, совсем труп...";
			link.l1.go = "drinking_at_miskito_1";
		break;
		
		case "drinking_at_miskito_1":
			dialog.text = "Шарль, но... сейчас...";
			link.l1 = "Ни при каких обстоятельствах. Прости за резкость, но с этим не шутят. Это я у тебя забираю. Ишь чего удумала... Вот, выпей и приди в себя.";
			link.l1.go = "drinking_at_miskito_2";
			
			GiveItem2Character(pchar, "cannabis7");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_at_miskito_2":
			dialog.text = "Извини, Шарль. Ты, конечно же, прав, и сама я всё это знаю. Минутная слабость. Больше такого не повторится. Спасибо, что избавил от дьявольского  соблазна...";
			link.l1 = "Замнём для ясности... Лучше скажи, как так вышло, что тебя и в городе уважают, и с офицерами гарнизона ты на короткой ноге, да и с аборигенами дружишь?";
			link.l1.go = "drinking_at_miskito_3";
		break;
		
		case "drinking_at_miskito_3":
			dialog.text = "Свенсона они уважают, вот и мне от этого уважения перепадает. Наш городишко вообще живёт исключительно за счёт Яна и его делишек. С красными м-мундирами он делится долей от своих факторий бакаута, а мискито вообще ему обязаны по гроб жизни.";
			link.l1 = "Это как?";
			link.l1.go = "drinking_at_miskito_4";
		break;
		
		case "drinking_at_miskito_4":
			dialog.text = "Когда тут сидели кастильцы, индейцев особо никто не трогал, но потом благородных идальго выперли, и наши решили крепко взяться за местные леса. Ян тогда достаточно жёстко решил вопрос - даже в Лондон людей отправлял! Ясное дело, не по доброте душевной: добывать бакаут в лесу, в котором тебя ненавидит каждый куст, - безнадёжное предприятие. Зато теперь индейцы не просто помогают Яну двигать контрабанду от Порто-Белло до Блювельда, но ещё сами и вырубают свои же леса за гроши. Браво, Лесной Дьявол, браво!";
			link.l1 = "Звучит так, как будто ты не одобряешь его методы.";
			link.l1.go = "drinking_at_miskito_5";
		break;
		
		case "drinking_at_miskito_5":
			dialog.text = "Я люблю и уважаю народ мискито, но я уважаю и стратегию Яна. Не в сказке живём, мой капитан.";
			link.l1 = "Хм... А ваши отношения со Свенсоном сложнее, чем кажется на первый взгляд...";
			link.l1.go = "drinking_at_miskito_6";
		break;
		
		case "drinking_at_miskito_6":
			dialog.text = "А знаешь, ты прав больше, чем сам думаешь. Его жёнушка недаром так желчью исходит на мой счёт... Ян пожирал меня глазами с тех пор, как мне стукнуло лет пятнадцать. Я как раз тогда стала на равных со всеми разгуливать по палубе 'Радуги', и, видимо, у Лесного Дьявола в голове что-то тогда защёлкало... Но я непозволительно разболталась, мой капитан. Давай не будем эту тему развивать: всё-таки не очень порядочное это дело - сплетничать о нашем общем патроне.";
			link.l1 = "Тогда сменим тему. Я хотел тебе сказать, что ты явно вписываешься в эту компанию, да и принимают они тебя за свою.";
			link.l1.go = "drinking_at_miskito_7";
		break;
		
		case "drinking_at_miskito_7":
			dialog.text = "Так уж повелось, что мне намного проще в компании индейцев, цыган и прочих порядочных отщепенцев. Стряпня мамы, костры на пляже и мостик 'Радуги' - я выстроила себе уютный мирок, капитан. Жаль, что он так закончился - и именно тогда, когда я решила, что всё у меня получилось.";
			link.l1 = "В бочонке уже почти пусто... По последней?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToShipyard");
		break;
		
		case "drinking_at_perlas":
			dialog.text = "Как же хорошо... Я рада, что ты согласился провести со мной время, кэп. Мне это было очень-очень нужно. Верю, что и тебе тоже.";
			link.l1 = "Да, давно так не отдыхал. Будет, что вспомнить!";
			link.l1.go = "drinking_at_perlas_1";
		break;
		
		case "drinking_at_perlas_1":
			dialog.text = "Ты, наверное, чёрт знает что теперь обо мне думаешь. Я ведь очень закрытый человек по натуре, Шарль. Просто... дьявол, просто живой себя захотелось почувствовать! Хоть с кем-то поговорить!";
			link.l1 = "А как же Глэдис? Ян?";
			link.l1.go = "drinking_at_perlas_2";
		break;
		
		case "drinking_at_perlas_2":
			dialog.text = "Мама может только реветь, а вот Ян как будто чужим человеком стал. Может, мне уже и мерещится всякое, не знаю, но как будто он стыдится меня теперь что ли? Прости, я... (всхлипывает).\nВсё, старушка, хватит. Извини, расклеилась я немного.";
			link.l1 = "Не за что извиняться. Я всё понимаю, или, мне кажется, что понимаю.";
			link.l1.go = "drinking_at_perlas_3";
		break;
		
		case "drinking_at_perlas_3":
			dialog.text = "Я это всё к тому, что мы только познакомились, а я не привыкла так открыто себя вести даже с теми, кого давно знаю. Хоть и зовут меня Румбой за характер, да, как видишь, незаслуженно. Выпивка ведь кончилась?";
			link.l1 = "Давно уже, да и рассвет уже начинает брезжить.";
			link.l1.go = "drinking_at_perlas_4";
		break;
		
		case "drinking_at_perlas_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend") && !CheckAttribute(pchar, "questTemp.HelenDrinking.RobbedSvenson")) {
				dialog.text = "Извини, мой капитан, если у тебя были другие ожидания на наш вечер. Я... не смогу. Не сегодня.";
			} else {
				dialog.text = "Тогда спасибо за вечер, кэп. Как знать, может, ещё повторим.";
			}
			link.l1 = "Конечно, Элен.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_PoormanTalk");
		break;
		
		case "ambush":
			dialog.text = "Спасибо, что привёз, кэп. Давай осмотримся что ли? Поглядим на моё наследство.";
			link.l1 = "А ты разве здесь раньше не бывала?";
			link.l1.go = "ambush_1";
		break;
		
		case "ambush_1":
			dialog.text = "Нет, далековато, да и пиратом я никогда не была. Это место и раньше особо не блистало, а уж после того, как убили Блейза... Лучше здесь не задерживаться.";
			link.l1 = "И не будем, я уже жалею, что привёз тебя сюда.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPrepareAmbush");
		break;
		
		case "after_ambush":
			switch (pchar.questTemp.HelenDrinking.IslaTesoroAmbush) {
				case "A":
					if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB") && !CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC")) {
						dialog.text = "Зря ты так, кэп. Всегда так скор на драку? Ну да ладно, победителей не судят. Пошли, заглянем в резиденцию, больше тут всё равно ничего стоящего не наблюдается.";
						pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
						notification("Элен не одобряет", "Helena");
					} else {
						dialog.text = "Молодец, мой капитан, что попытался решить вопрос по уму, прежде чем лезть в драку. Пошли, заглянем в резиденцию, больше тут всё равно ничего стоящего не наблюдается.";
					}
					
					link.l1 = "А как же тот огромный, вытащенный на сушу, корабль?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "B":
					dialog.text = "Красиво ты развёл этих придурков, мой капитан! Я чуть не расхохоталась, честное слово! Пошли, заглянем в резиденцию, больше тут всё равно ничего стоящего не наблюдается.";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Элен одобряет", "Helena");
					
					link.l1 = "А как же тот огромный, вытащенный на сушу, корабль?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "C":
					dialog.text = "Подожди-подожди, дай девке отдышаться! Ты и правда тот самый Чарли Принц?";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Элен одобряет", "Helena");
					
					link.l1 = "Был такой период в моей биографии, да. Ты впечатлена?";
					link.l1.go = "after_ambush_c";
				break;
			}
		break;
		
		case "after_ambush_1":
			dialog.text = "Да, ты прав - мне до ужаса хочется там полазить, но, признаться честно, Шарль, побаиваюсь я его. Пойдём.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroGoToResidence");
		break;
		
		case "after_ambush_c":
			dialog.text = "О Боже мой, да! Обязательно потом расскажи мне всё, ладно? А то я слышала только байки... очень бесстыдные байки!";
			link.l1 = "Всё расскажу... почти всё.";
			link.l1.go = "after_ambush_c_1";
		break;
		
		case "after_ambush_c_1":
			dialog.text = "Буду ждать с нетерпением! Пошли, заглянем в резиденцию, больше тут всё равно ничего стоящего не наблюдается.";
			link.l1 = "А как же тот огромный, вытащенный на сушу, корабль?";
			link.l1.go = "after_ambush_1";
		break;
		
		case "ambush_inresidence":
			dialog.text = "Тесная, холодная лачуга с нелепыми претензиями. Я уже чувствую себя как в ловушке!";
			link.l1 = "Вижу, что осмотр потенциальной собственности тебя пока не радует?";
			link.l1.go = "ambush_inresidence_1";
		break;
		
		case "ambush_inresidence_1":
			dialog.text = "Нет, Шарль. Возможно, я слишком строга к этому месту, но пока оно олицетворяет всё, что я боюсь и ненавижу. Надеюсь, я смогу ограничиться только рентой... Впрочем, не уверена, что мне будет куда её тратить.";
			link.l1 = "Рента - это уже немало, у меня вот ренты нет, и приходится зачастую изворачиваться, чтобы команде заплатить. Купишь себе новый корабль: 'Радуга II' - согласись, звучит неплохо!";
			link.l1.go = "ambush_inresidence_sea";
			link.l2 = "Есть много способов потратить на себя деньги. Начни с именной шпаги и бутылки отличного вина. Порадуй себя, Элен, ты этого заслуживаешь.";
			link.l2.go = "ambush_inresidence_land";
		break;
		
		case "ambush_inresidence_sea":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "sea") {
				dialog.text = "Спасибо, мой капитан. Мне приятно это слышать. Особенно приятно слышать это во второй раз. Ты хорошо меня знаешь.";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
				notification("Элен одобряет", "Helena");
			} else {
				dialog.text = "Спасибо, мой капитан. Мне приятно это слышать.";
			}
			
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_COMMERCE, 5);
			AddCharacterSkill(sld, SKILL_ACCURACY, 5);
			AddCharacterSkill(sld, SKILL_CANNONS, 5);
			AddCharacterSkill(sld, SKILL_SAILING, 5);
			AddCharacterSkill(sld, SKILL_REPAIR, 5);
			AddCharacterSkill(sld, SKILL_GRAPPLING, 5);
			AddCharacterSkill(sld, SKILL_DEFENCE, 5);
		break;
		
		case "ambush_inresidence_land":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "land") {
				dialog.text = "Думаешь, заслуживаю? Никогда не тратила деньги на такие безделушки, но всё бывает в первый раз, а? Смотрю, ты не прекращаешь попытки заставить меня забыть о море, да, кэп? Может, ты и прав...";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 3;
				notification("Элен не одобряет", "Helena");
			} else {
				dialog.text = "Думаешь, заслуживаю? Никогда не тратила деньги на такие безделушки, но всё бывает в первый раз, а?";
			}
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_F_LIGHT, 5);
			AddCharacterSkill(sld, SKILL_FENCING, 5);
			AddCharacterSkill(sld, SKILL_F_HEAVY, 5);
			AddCharacterSkill(sld, SKILL_PISTOL, 5);
			AddCharacterSkill(sld, SKILL_FORTUNE, 5);
			AddCharacterSkill(sld, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(sld, SKILL_SNEAK, 5);
		break;
		
		case "ambush_inresidence_2":
			dialog.text = "В любом случае, осмотр закончен. Ценностей здесь вроде нет - это быдло уже успело всё растащить, а на втором этаже, уверена, картина та же.";
			link.l1 = "Ты как будто изменилась, Элен. Когда мы с тобой прошлый раз проводили время, ты была... не знаю, более открытой?";
			link.l1.go = "ambush_inresidence_3";
		break;
		
		case "ambush_inresidence_3":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Ничего не изменилось, мой капитан, но многое свалилось на бедную девушку, ха-ха! Я не хотела тебя обидеть, просто мне надо сейчас многое обдумать: cам понимаешь, такие жизненные повороты случаются не каждый день. А времени у нас с тобой будет ещё полно!";
				link.l1 = "Рад это слышать! Пойдём отсюда.";
			} else {
				dialog.text = "Многое изменилось, кэп. Боюсь, мне теперь надо быть взрослее и по-другому относится к своей жизни. Это ведь не сказка про принцессу и наследство, а большая политика, в которой мне ещё предстоит осознать своё место. И место моей семьи.";
				link.l1 = "Рад, что мы это прояснили. Пойдём отсюда.";
			}
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroBeforeExit");
		break;
		
		case "ambush_inresidence_wait":
			dialog.text = "Да?";
			if (CheckCharacterItem(pchar, "pirate_cutlass")) {
				link.l1 = "А ведь не всё обчистили! Смотри, Элен! Сабля, похоже, легендарная, раз даже местный сброд постеснялся её прикарманить.";
				link.l1.go = "ambush_inresidence_give_cutlass";
			}
			
			link.l2 = "Нет, ничего.";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "ambush_inresidence_wait";
		break;
		
		case "ambush_inresidence_give_cutlass":
			dialog.text = "Вот это да... Легендарный катлас самого Блейза! Пираты слишком его уважали, чтобы забрать саблю из его дома даже после его смерти. Деньги и драгоценности, конечно, вынесли, но даже у будущих висельников есть остатки чести...";
			link.l1 = "Да и прибирается кто-то здесь явно. Как будто хозяин ещё вернётся... Это не дом, а памятник!";
			link.l1.go = "ambush_inresidence_give_cutlass_1";
		break;
		
		case "ambush_inresidence_give_cutlass_1":
			dialog.text = "Спасибо за тонкое наблюдение, Шарль. Ты окончательно убил это место в моих глазах, ха-ха!";
			link.l1 = "Мне кажется, что этот катлас теперь - твой. Блейз - твой названный дядя...";
			link.l1.go = "ambush_inresidence_give_cutlass_2";
		break;
		
		case "ambush_inresidence_give_cutlass_2":
			dialog.text = "Ты нагоняешь на меня ещё больше жути, мой капитан. Я... не могу. Я боюсь, что если я его приму, то моей прошлой жизни окончательно настанет конец.";
			link.l1 = "Тогда прими его не как часть наследства, а как подарок от красавца-мужчины.";
			link.l1.go = "ambush_inresidence_give_cutlass_3";
		break;
		
		case "ambush_inresidence_give_cutlass_3":
			dialog.text = "А где он? Ах-ха, шучу-шучу! Спасибо, что отогнал мрачные мысли, мой капитан. Обещаю, я буду много тренироваться, чтобы стать достойной этого клинка!";
			link.l1 = "Ты достойна лучшего оружия, Элен. Пойдём, мы тут закончили.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "give_cutlass":
			dialog.text = "Вот это да... Легендарный катлас самого Блейза! Пираты слишком его уважали, чтобы забрать саблю из его дома даже после его смерти. Деньги и драгоценности, конечно, вынесли, но даже у будущих висельников есть остатки чести\nЯ... не могу. Я боюсь, что если я его приму, то моей прошлой жизни окончательно настанет конец.";
			link.l1 = "Тогда прими его не как часть наследства, а как подарок от красавца-мужчины.";
			link.l1.go = "give_cutlass_1";
		break;
		
		case "give_cutlass_1":
			dialog.text = "А где он? Ах-ха, шучу-шучу! Спасибо, что отогнал мрачные мысли, мой капитан.";
			link.l1 = "Ты достойна лучшего оружия, Элен. Рад, что тебе нравится.";
			link.l1.go = "give_cutlass_2";
		break;
		
		case "give_cutlass_2":
			dialog.text = "Обещаю, я буду много тренироваться, чтобы стать достойной этого клинка!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "arrive":
			dialog.text = "Мой капитан! Шарли!";
			link.l1 = "Шарли? Это что-то новенькое! Рад тебя видеть, дорогая.";
			link.l1.go = "arrive_1";
		break;

		case "arrive_1":
			dialog.text = "Это я случайно оговорилась, ха! И я рада тебя видеть...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog1");
		break;

		case "arrive_2":
			dialog.text = "Так вот она какая - женская солидарность? Мой капитан, я... очень переживала и правда-правда очень соскучилась!";
			link.l1 = "А зачем ты домой тогда сбежала?";
			link.l1.go = "arrive_3";
		break;

		case "arrive_3":
			dialog.text = "Чтобы... А вот! Подарочек тебе сообразила, держи!";
			link.l1 = "Три амулета... Элен, ты что? Ты за мной хотела отправиться?!";
			link.l1.go = "arrive_4";
			
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Indian);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Amulet);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Obereg);
		break;

		case "arrive_4":
			dialog.text = "Иди сюда, дурак!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FirstKiss");
		break;

		case "after_kiss":
			dialog.text = "Только не смей портить этот момент - я всю жизнь представляла, как оно будет!";
			link.l1 = "Не буду, Элен.";
			link.l1.go = "after_kiss_a";
			link.l2 = "Всю жизнь ждала встречи со мной? Польщён!";
			link.l2.go = "after_kiss_b";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l3 = "Элен, тут такое дело... На Острове Справедливости я встретил женщину, и...";
				link.l3.go = "after_kiss_c";
			}
			locCameraFromToPos(-19.00, 1.56, 19.07, true, -11.19, -0.90, 17.49);
		break;
		
		case "after_kiss_a":
			dialog.text = "Вот и правильно! Ты обязательно всё-всё мне расскажешь! Жду тебя на корабле, мой капитан!";
			link.l1 = "Подожди!..";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_b":
			dialog.text = "Дурак! Вот обижусь на тебя и всё! Всё, обиделась! Ха-ха! Пойду я пока на корабль, а то Данни сейчас прорвёт, как старую плотину...";
			link.l1 = "Подожди!..";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_c":
			dialog.text = "Дурак! Я же просила не портить момент! Встретил, ну и встретил - кольца на твоём пальце я пока не вижу. Но не думай, что тебе это сойдёт с рук - я буду ждать подробного рассказа, когда ты вернёшься на корабль.";
			link.l1 = "Подожди!..";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "loot_good":
			dialog.text = "Мой капитан, какие новости? Вижу по твоему белому лицу, что адвокат решил тебе подкинуть проблем, вместо того, чтобы решить их.";
			link.l1 = "Ты права, Элен. Локсли потребовал впечатляющий аванс, да и само дело обойдётся мне в круглую сумму. Пойду трясти Яна - хватит с меня! Как будто Братство решило взвалить все свои расходы на меня!";
			link.l1.go = "loot_good_1";
		break;
		
		case "loot_good_1":
			dialog.text = "Тут нет злого умысла, Шарль. Такие уж они люди - сами первыми руки не подадут. Уверена, что Ян тебя выручит, да и я в стороне не останусь.";
			link.l1 = "Я знаю, Элен. Рассказывай, что у тебя на уме.";
			link.l1.go = "loot_good_2";
		break;
		
		case "loot_good_2":
			dialog.text = "Я же работала на Яна - возила драгоценную древесину контрабандой по всему Мэйну. Но девушка я хозяйственная, и за все рейсы кое-что приберегла для себя любимой.";
			link.l1 = "И Ян ничего не узнал? Ловко!";
			link.l1.go = "loot_good_3";
		break;
		
		case "loot_good_3":
			dialog.text = "У меня был хороший казначей. Короче, денег я собрала прилично, да и бакаут припрятала недалеко. Тебе всё равно сейчас к Яну, так? Заглянем в Сан Хуан дель Норте? Там недалеко есть пещерка одна, только матросов захватим, чтобы не таскать всё самим.";
			link.l1 = "А ты уже всё продумала, да? Спасибо, Элен, обязательно заглянем если время будет.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "loot_bad":
			dialog.text = "Кэп, что стряслось? Вижу по твоему белому лицу, что адвокат решил тебе подкинуть проблем, вместо того, чтобы решить их.";
			link.l1 = "Ты права, Элен. Локсли потребовал солидный аванс, да и само дело обойдётся мне в круглую сумму. Пойду трясти Яна, хватит с меня - как будто Братство решило взвалить все свои расходы на меня!";
			link.l1.go = "loot_bad_1";
		break;
		
		case "loot_bad_1":
			dialog.text = "А ты думал, что в сказку попал? Не переживай, мы тут все в одной лодке, и я тебя выручу. Наследство-то мне полагается, так?";
			link.l1 = "Это верно... Рассказывай, что у тебя на уме!";
			link.l1.go = "loot_bad_2";
		break;
		
		case "loot_bad_2":
			dialog.text = "У меня тут кое-что припрятано в Сан Хуан дель Норте. Там недалеко есть пещерка одна - только матросов захватим, чтобы не таскать всё самим.";
			link.l1 = "А ты уже всё продумала, да? Спасибо, Элен, обязательно заглянем если время будет.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "shdn":
			dialog.text = "Это здесь, Шарль! Только иди один - не люблю я эти пещеры!";
			link.l1 = "Как и любые замкнутые пространства, я знаю, Элен. Жди меня тут.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoForLoot");
		break;
		
		case "shdn_ambush":
			dialog.text = "У нас проблемы! Сюда идёт отряд солдат, и вид у них грозный. Осторожней, Шарль, это не простая береговая стража - среди них есть французский офицер! Умоляю тебя, только не наделай глупостей!";
			link.l1 = "Когда это я делал глупости?!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SpawnAmbushSoldiers");
		break;
		
		case "shdn_ambush_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Ха, второе звучит, конечно, более привлекательно, но, надеюсь, ты не слишком гордишься собой, Шарль?";
			} else {
				dialog.text = "Не сказать, чтобы я была удивлена, Шарль...";
			}
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog1");
		break;
		
		case "shdn_ambush_2":
			dialog.text = "Вы закончили? Теперь я выскажусь!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_HelenKillFrancois");
		break;
		
		case "shdn_ambush_3":
			dialog.text = "Меня зовут Элен МакАртур! Капитан, вы знаете, кто я и на кого работаю! Донесите своим людям и особенно вот этому визжащему на земле расфуфыренному кретину небольшие итоги сегодняшнего дня, которые я сейчас назову!";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "richard");
			sld = CharacterFromID("HelenDrinking_Richard");
			CharacterTurnByChr(sld, npchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath2");
		break;
		
		case "shdn_ambush_4":
			dialog.text = "Протестовать? Да хоть Кромвелю пишите, мне плевать. Первое, месье де Мор чести сегодня не терял.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_5";
			CharacterTurnToLoc(npchar, "quest", "richard");
		break;
		
		case "shdn_ambush_5":
			dialog.text = "Второе, полковник де Таванн получил пулю от девчонки в очень пикантном наряде за то, что высказался о ней как о проститутке.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_6";
		break;
		
		case "shdn_ambush_6":
			dialog.text = "Третье, вы немедленно забираете своих солдат и забываете о произошедшем, если не хотите, чтобы о нём узнал Лесной Дьявол.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_7";
		break;
		
		case "shdn_ambush_7":
			locCameraSleep(false);
			dialog.text = "Вопросов, вижу, нет. Доброго вам дня, капитан.";
			link.l1 = "Господи, Элен, вот это ты даёшь!";
			link.l1.go = "shdn_ambush_8";
		break;
		
		case "shdn_ambush_8":
			dialog.text = "Потом, Шарль. Давай уходить отсюда, пока они от шока не отошли. Меня тоже всю трясет. Поговорим в Блювельде?";
			link.l1 = "Договорились.";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, pchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath3");
		break;
		
		case "duel_victory":
			dialog.text = "Давай уходить отсюда, пока они от шока не отошли. Нам ещё бакаут вытаскивать, забыл? Поговорим в Блювельде.";
			link.l1 = "Ого! Даже не поздравишь? Хорошо, так и сделаем.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory1");
		break;
		
		case "after_cave":
			dialog.text = "Вот мы и дома...";
			link.l1 = "Что скажешь о произошедшем?";
			link.l1.go = "after_cave_1";
		break;
		
		case "after_cave_1":
			dialog.text = "Не понимаю я дуэлей. Мужская забава, которая заканчивается обычно двумя трупами, а в удачный день и поболее. А честь... честь, думаю, строится на стремлении уходить от конфликта до последнего, поскольку он редко того стоит. Ха! Только послушай меня - несу какую-то чушь!";
			link.l1 = "Это интересная мысль, Элен. Хотя не все с ней согласятся.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
				link.l1.go = "after_cave_duel";
			} else {
				link.l1.go = "after_cave_notduel";
			}
		break;
		
		case "after_cave_duel":
			dialog.text = "Жаль, что ты пошёл у них на поводу. Полковник был явно одержим, а остальным только зрелищ да пищу для сплетен подавай. Впрочем, не буду тебя костерить - тебе и так сегодня досталось.";
			link.l1 = "Да, после дуэлей всегда накатывает какое-то опустошение. На сегодня приключений нам хватит. Что будем делать дальше?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_notduel":
			dialog.text = "Тьфу ты! Я просто хотела сказать, что горжусь нами. Ты проявил настоящее мужество сегодня, мой капитан. Не поддался на истерику подчинённых, которые просто хотели в кои-то веки тобой покомандовать. Устоял перед фальшью красного мундира и одержимостью синего. Полковник явно искал смерти, но получил только ранение в неподобающее место, ха-ха!";
			link.l1 = "Спасибо, Элен. Ты превосходно вывела нас из под удара - как настоящий морской офицер. Гордишься собой?";
			link.l1.go = "after_cave_notduel_1";
		break;
		
		case "after_cave_notduel_1":
			dialog.text = "Да, мне это было нужно. Жаль только, что это был не красный мундир, но хоть человек в нём сидел какой надо.";
			link.l1 = "Человек он неважный, признаю. На сегодня приключений нам хватит. Что будем делать дальше?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_mild":
			dialog.text = "Я домой, мой капитан. Соскучилась по м... по Глэдис.. Жаль, что она дома, а то бы позвала бы в гости!";
			link.l1 = "И правда, жаль!";
			link.l1.go = "after_cave_mild_1";
		break;
		
		case "after_cave_mild_1":
			dialog.text = "Не расстраивайся ты так. Скоро, дорогой. А пока...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "М-м-м, а этот ещё лучше, чем наш первый. Помнишь? У идола?";
				link.l1 = "Такое не забывается, дорогая.";
				link.l1.go = "after_second_kiss_1";
			} else {
				dialog.text = "Только не смей портить этот момент - я всю жизнь представляла, как оно будет!";
				link.l1 = "Не буду, Элен.";
				link.l1.go = "after_second_kiss_a";
				link.l2 = "Всю жизнь ждала встречи со мной? Польщён!";
				link.l2.go = "after_second_kiss_b";
			}
		break;
		
		case "after_second_kiss_1":
			dialog.text = "Да-а... Ух! Держи себя в руках, девка! До скорой встречи, мой капитан.";
			link.l1 = "До встречи, Элен.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_a":
			dialog.text = "Вот и правильно! Скоро увидимся, мой капитан.";
			link.l1 = "До встречи, Элен. Господи, что за девушка...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_b":
			dialog.text = "Дурак! Вот обижусь на тебя и всё! Всё, обиделась! Ха-ха! Скоро увидимся, мой капитан.";
			link.l1 = "До встречи, Элен. Господи, что за девушка...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_cave_cold":
			dialog.text = "Я домой, кэп. Полагаю, проблема с деньгами для адвоката теперь решена? Впереди нас ждут тяжёлые испытания, так что давай отныне держаться подальше от неприятностей. Они сами нас найдут.";
			link.l1 = "Ого, даже так?";
			link.l1.go = "after_cave_cold_1";
		break;
		
		case "after_cave_cold_1":
			dialog.text = "Извини за резкость, кэп. Сейчас решается и моя судьба тоже, ты же знаешь.";
			link.l1 = "Знаю, постараюсь её устроить максимально достойным образом. До встречи на корабле, Элен.";
			link.l1.go = "after_cave_cold_2";
		break;
		
		case "after_cave_cold_2":
			dialog.text = "Так точно, кэп!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveCold");
		break;
		
		case "after_cave_lewd":
			dialog.text = "Что дальше? Сейчас покажу...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss1":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "М-м-м, а этот ещё лучше, чем наш первый. Помнишь? У идола?";
				link.l1 = "Такое не забывается, дорогая.";
				link.l1.go = "after_second_kiss1_1";
			} else {
				dialog.text = "Только не смей портить этот момент - я всю жизнь представляла, как оно будет!";
				link.l1 = "Не буду, Элен.";
				link.l1.go = "after_second_kiss1_a";
				link.l2 = "Всю жизнь ждала встречи со мной? Польщён!";
				link.l2.go = "after_second_kiss1_b";
			}
		break;
		
		case "after_second_kiss1_1":
			dialog.text = "Да-а... Ух! М... Глэдис сейчас нет дома, зайдешь?";
			link.l1 = "В гости зовёшь? И что мы будем делать?";
			link.l1.go = "after_cave_lewd_accept";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l2 = "Нет, Элен. На Острове Справедливости меня ждёт другая женщина. Я не могу так с ней поступить.";
				link.l2.go = "after_cave_lewd_refuse_mary";
			}
			link.l3 = "В другой раз, дорогая. Я очень этого хочу, но сегодняшний день меня чуть не доконал. Мы с тобой ещё всё догоним и перегоним.";
			link.l3.go = "after_cave_lewd_refuse_head";
		break;
		
		case "after_second_kiss1_a":
			dialog.text = "Вот и правильно! Ух! Глэдис сейчас нет дома, зайдешь?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Нет, Элен. На Острове Справедливости меня ждёт другая женщина. Я не могу так с ней поступить.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "В другой раз, дорогая. Я очень этого хочу, но сегодняшний день меня чуть не доконал. Мы с тобой ещё всё догоним и перегоним.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "В гости зовёшь? И что мы будем делать?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_second_kiss1_b":
			dialog.text = "Дурак! Вот обижусь на тебя и всё! Всё, обиделась! Ха-ха! Придётся тебе исправить свой промах, мой капитан. Ух! Глэдис сейчас нет дома, зайдешь?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Нет, Элен. На Острове Справедливости меня ждёт другая женщина. Я не могу так с ней поступить.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "В другой раз, дорогая. Я очень этого хочу, но сегодняшний день меня чуть не доконал. Мы с тобой ещё всё догоним и перегоним.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "В гости зовёшь? И что мы будем делать?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_cave_lewd_refuse_mary":
			dialog.text = "Эх, не хватило мне знания женских штучек, да? А у этой хватило? Кто она?";
			link.l1 = "Её зовут Мэри Каспер, и я её люблю.";
			link.l1.go = "after_cave_lewd_refuse_mary_1";
		break;
		
		case "after_cave_lewd_refuse_mary_1":
			dialog.text = "Та рыжая девица в красном мундире? В красном мундире... Что же, если и был мне нужен знак, то вот он. Не судьба. И не переживай, капитан, это не повлияет на мою службу на твоём корабле.";
			link.l1 = "Прости, Элен.";
			link.l1.go = "exit";
			
			pchar.questTemp.HelenDrinking.Mary = true;
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMary");
		break;
		
		case "after_cave_lewd_refuse_head":
			dialog.text = "Ох, мой капитан! Опасно женщину оставлять в таком состоянии! Ловлю тебя на слове, а теперь беги... Мне надо сейчас побыть одной и попытаться справиться с проблемой... самостоятельно! Увидимся на корабле!";
			link.l1 = "Что за девушка!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMild");
		break;
		
		case "after_cave_lewd_accept":
			dialog.text = "Не переживай, дорогой, я подскажу тебе, что делать, если растеряешься.";
			link.l1 = "Однако... веди!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveAccept");
		break;
		
		case "after_cave_bedroom":
			dialog.text = "Ничего не говори, прошу тебя.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex1");
		break;
		
		case "after_cave_sex":
			dialog.text = "... конечно, до сегодняшнего дня мнение о предмете я имела только из скабрезных бесед команды 'Радуги', если их можно, конечно, назвать беседами.";
			link.l1 = "И как? Совпали ожидания с реальностью?";
			link.l1.go = "after_cave_sex_1";
		break;
		
		case "after_cave_sex_1":
			dialog.text = "Мне очень понравилось, но как будто не распробовала. А как...";
			link.l1 = "Сейчас покажу! Повторим?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex2");
		break;
		
		case "after_cave_sex_again":
			dialog.text = "Ох, теперь я поняла! Это было просто дивно, мой капитан!";
			link.l1 = "Удивила ты меня, не то слово, удивила!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysEnter");
		break;
		
		case "after_cave_gladys":
			dialog.text = "Ах-ха-ха! Вот умора, конечно! Теперь она или залепит уши воском, или сбежит на самую высокую платформу форта!";
			link.l1 = "Это было неожиданно, но очень смешно, ах-ха-ха!";
			link.l1.go = "after_cave_gladys_1";
			locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - постельная камера
		break;
		
		case "after_cave_gladys_1":
			dialog.text = "Готов, мой капитан?";
			link.l1 = "Уже?! Нет уж, Элен, пожалей меня, пожалуйста. Внезапное явление Глэдис ситуации точно не помогло.";
			link.l1.go = "after_cave_gladys_2";
		break;
		
		case "after_cave_gladys_2":
			dialog.text = "Эх, ну что тут поделаешь... Хотя...";
			link.l1 = "Нет, нет, спустить паруса!";
			link.l1.go = "after_cave_gladys_3";
		break;
		
		case "after_cave_gladys_3":
			dialog.text = "Ладно, давай тогда просто побудем вместе немного? Впереди нас ждёт такое страшное и непонятное будущее, но впервые за долгое время я больше ничего не боюсь. Я знаю, что завтра обязательно придёт какой-нибудь новый страх, но не сегодня. Не сегодня, мой капитан.";
			link.l1 = "Не сегодня, дорогая. Не сегодня.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveFin");
		break;
		
		case "give_potions":
			dialog.text = "Разрешите обратится, мой капитан.";
			link.l1 = "Да, Элен?";
			link.l1.go = "give_potions_1";
		break;
		
		case "give_potions_1":
			dialog.text = "Я знаю этого Змеиного Глаза - он хороший, но чудной: с завидной регулярностью отправляет людей на поиски неизвестно чего. Вижу, что и тебя не обошла эта сомнительная честь.";
			if (!CheckAttribute(CharacterFromID("SnakeEye"), "quest.amulet")) {
				link.l1 = "Это так, мне нужно принести ему три амулета, иначе он не сможет помочь мне добраться до Хоука. Знаешь, что забавно, они у меня уже были при себе! Может, он это знал с самого начала?";
				link.l1.go = "give_potions_already";
			} else {
				link.l1 = "Это так, мне нужно принести ему три амулета, иначе он не сможет помочь мне добраться до Хоука. Ума не приложу, где их теперь искать, а время дорого.";
				link.l1.go = "give_potions_3";
			}
		break;
		
		case "give_potions_already":
			dialog.text = "Эх, жаль! Я, конечно же, рада, что не пришлось тебе бегать за этими амулетами по смотрителям маяков, но я надеялась, что хоть в этот раз и сама смогу быть в кои-то веки тебе полезной, надеялась доказать это.";
			link.l1 = "Глупости, Элен. Тебе не нужно мне ничего доказывать.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_3":
			dialog.text = "Я тебе помогу! Признаюсь, я надеялась, что хоть в этот раз и сама смогу быть в кои-то веки тебе полезной, надеялась доказать это.";
			link.l1 = "Глупости, Элен. Тебе не нужно мне ничего доказывать.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_4":
			dialog.text = "И тем не менее, я хочу тебе помочь. Держи вот ключ от моей спальни... тьфу, то есть, от сундука в моей спальне! Там немного, но такому человеку, как ты, пригодится\nИ... Шарль, только попробуй заржать мне тут сейчас!";
			link.l1 = "Кхм, я и не собирался. Смотрю, ты увлекаешься такими вещами?";
			link.l1.go = "give_potions_5";
		break;
		
		case "give_potions_5":
			dialog.text = "Я моряк, мой капитан, как и ты. Без суеверий в нашем деле никуда.";
			link.l1 = "Спасибо, Элен. Я это очень ценю.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GivePotionsKey");
		break;
		
		case "upgrade":
			dialog.text = "Дорогой, у меня для тебя подарок!";
			link.l1 = "Я вижу, вот - стоит и улыбается!";
			link.l1.go = "upgrade_1";
		break;
		
		case "upgrade_1":
			dialog.text = "Ах-ха, перестань! Я однажды подогнала приличную партию шёлка местному корабелу, так что теперь он мне должен полную доводку корабля. Думала 'Радугу' под это дело ему отдать, да видно, что не судьба. Но нашей посудине такая забота не помешала бы, как думаешь?";
			link.l1 = "И правда, роскошный подарок, Элен, - как раз в твоём духе!";
			link.l1.go = "upgrade_2";
		break;
		
		case "upgrade_2":
			dialog.text = "Я рада, что тебе нравится. Заходи к нему в любое время и скажи, что от меня. Всё сделают в лучшем виде.";
			link.l1 = "Обязательно!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("HelenUpgradeShip1");
		break;
		
		case "give_sex":
			dialog.text = "Мой капитан, разрешите обратиться?";
			link.l1 = "Конечно, дорогая.";
			link.l1.go = "give_sex_1";
		break;
		
		case "give_sex_1":
			dialog.text = LinkRandPhrase("Ваша женщина соскучилась и требует внимания. Разрешите попросить снять комнату и уделить ей немного времени?", "Докладываю: ваше присутствие требуется на кровати в местной таверне. Всего минут пять вашего времени, но команда надеется, что вы задержитесь подольше!", "Бунт на корабле, мой капитан! Мне поручено вручить вам чёрную метку в приватной обстановке. Немедленно проследуйте за мной!");
			link.l1 = "Хе-хе, кхм! Ваша просьба удовлетворена, офицер Шарп!";
			link.l1.go = "give_sex_1_yes";
			link.l2 = "Давай не сегодня, дорогая. Дел невпроворот.";
			link.l2.go = "give_sex_1_no";
		break;
		
		case "give_sex_1_yes":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			DialogExit();
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "give_sex_1_no":
			dialog.text = "Эх, и что прикажешь делать бедной девушке, а? Ладно, дорогой, значит, в другой раз.";
			link.l1 = "";
			link.l1.go = "give_sex_2_no";
		break;
		
		case "give_sex_2_no":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			npchar.location = "None";
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			chrDisableReloadToLocation = false;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		break;
		
		case "special_sex":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			SaveCurrentNpcQuestDateParam(npchar, "special_sex_date");
			
			dialog.text = "Ха! Меня дважды просить не надо! Конечно же, идём!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "rainbow":
			dialog.text = "Сейчас я тебя за борт скину!";
			link.l1 = "Эй-эй-эй! Спокойно, дорогая!";
			link.l1.go = "rainbow_1";
		break;
		
		case "rainbow_1":
			dialog.text = "Иди сюда, скотина!";
			link.l1 = "Шутка, Элен! Я не хотел тебя обидеть!";
			link.l1.go = "rainbow_2";
		break;
		
		case "rainbow_2":
			dialog.text = "Ах так? Шутник, б...";
			link.l1 = "Ты самая красивая, и я безумно тебя люблю!";
			link.l1.go = "rainbow_3";
		break;
		
		case "rainbow_3":
			dialog.text = "Иди ты в задницу, Шарль.";
			link.l1 = "";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Rainbow");
			Achievment_Set("ach_CL_84");
		break;
		
		case "joan":
			dialog.text = "Сама ты шлёндра! Радуйся, что Ян из тебя честную бабу сделал, а то и дальше бы ноги перед каждым встречным раздвигала!";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("JS_girl"));
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog2");
		break;
		
		case "joan_1":
			dialog.text = "Полундра! Валим, Шарль!";
			link.l1 = "";
			link.l1.go = "exit";
			
			ResetSound();
			SetMusic("helendrinking_shanty");
			pchar.questTemp.lockedMusic = true;
			AddDialogExitQuestFunction("HelenDrinking_GoToFort");
		break;
		
		case "cutlass_training":
			dialog.text = "Сабля лежит в руке просто идеально! Я не знаю, как это объяснить... Шпаги и рапиры - да, а с остальными видами холодного оружия всегда ерунда у меня какая-то получалась. Но вот эта сабля - другое дело! Здорово-то как! Спасибо тебе, Шарль!";
			link.l1 = "От предназначения и правда не убежишь. Рад за тебя, Элен!";
			link.l1.go = "exit";
			notification("Среднее оружие +", "Helena");
		break;
		
		case "brothel_found":
			dialog.text = "Рассказывай сказки кому другому, но только не мне. Я разве похожа на влюблённую дурочку? Я, конечно, влюблена в тебя до одури, но дурочкой меня назвать сложно\nСмотри, дорогой, поступай, конечно, как знаешь, но учти, что лучше меня женщины тебе не найти. Хочешь искать её в борделях? Пожалуйста, но тогда я сразу ухожу.";
			link.l1 = "Элен, я...";
			link.l1.go = "brothel_found_1";
		break;
		
		case "brothel_found_1":
			dialog.text = "Я всё понимаю, Шарль. Любишь ты только меня, а это всё так - естественная потребность. А знаешь, какая моя естественная потребность? Уважение со стороны моего мужчины. Одной любви женщине может быть недостаточно, дорогой. Сейчас давай забудем об этом недоразумении, но покрути мою мысль немного в голове. Хорошо?";
			link.l1 = "Хорошо, Элен.";
			link.l1.go = "exit";
		break;
		
		case "refuse":
			dialog.text = "Сам знаешь. Дай девушке остыть сначала.";
			link.l1 = "Эх...";
			link.l1.go = "exit";
		break;
		
		// Тайна Порт-Рояля
		case "MysteryPortRoyal_Helena_1":
			dialog.text = "Френсис... припоминаю. Он всегда ждал моего прибытия в Порт-Роял и был неисправимым романтиком. Мне было приятно проводить свободное время с человеком, далёким от моря: все эти стихи и серенады - это было что-то новенькое. Отблески другого мира, которого я никогда не знала.\nФренсис был богат, умён и хорош собой - завидный жених, любая местная девушка сошла бы с ума от его ухаживаний, но тогда меня больше беспокоило, как удержать “Радугу” на плаву.";
			link.l1 = "Видимо, ранимая душа поэта не смогла стерпеть твоего отказа. Во всех письмах он только о тебе и говорил, вспоминал места ваших встреч. Я могу отдать тебе все, что он завещал, если хочешь.";
			link.l1.go = "MysteryPortRoyal_Helena_2";
		break;
		
		case "MysteryPortRoyal_Helena_2":
			dialog.text = "Я не знала, что он болен. Как-то глупо всё это. А насчёт его подарка... Хватит с меня завещаний и наследств. Поверь, сейчас у меня есть всё, что нужно, и даже больше. Лучше оставь себе.";
			link.l1 = "Его наследие, так или иначе, все равно послужит тебе во благо - значит я невольно стал исполнителем его последнего желания. Занятная история.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.MysteryPortRoyal_Helena");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenDrinking_RobbedSvenson() {
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	if (!CheckAttribute(sld, "private1.items.chest")) { 
		return true;
	}
	
	if (sti(sld.private1.items.chest) < 2) {
		return true;
	}
	
	return false;
}
