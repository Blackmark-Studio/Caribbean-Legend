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
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "AlonsoNaPalube":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube"))
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube2 = true;
				dialog.text = "Ваше решение, капитан? Может не стоит?";
				link.l1 = "У тебя получилось собрать больше добровольцев на дело?";
				link.l1.go = "AlonsoNaPalube_StrongGroup";
			}
			else
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube = true;
				dialog.text = "Капитан, на пару слов.";
				link.l1 = "Докладывай, Алонсо.";
				link.l1.go = "AlonsoNaPalube_2";
			}
			locCameraFromToPos(-10.33, 9.69, -22.16, true, -5.22, 7.19, -21.06);
		break;
		
		case "AlonsoNaPalube_2":
			dialog.text = "Команда интересуется какие у вас планы на Кайман. Люди волнуются.";
			link.l1 = "Я пока не решил"+GetSexPhrase("","а")+". А почему люди волнуются, Алонсо?";
			link.l1.go = "AlonsoNaPalube_3";
		break;
		
		case "AlonsoNaPalube_3":
			dialog.text = "Этот остров - вотчина капитана Блэквуда. Моряки говорят, что он словно одержимый роет его вдоль и поперёк. Что загубил десятки людей в своих раскопках.. И те, кто уходит от него... рассказывают странные вещи.";
			link.l1 = "Какие вещи?";
			link.l1.go = "AlonsoNaPalube_4";
		break;
		
		case "AlonsoNaPalube_4":
			dialog.text = "Что Блэквуд уже не тот человек, каким был раньше. Что он одержим поисками какого-то клада конкистадоров. Что готов пожертвовать всем и всеми ради него. Мы знаем насколько вы любите впутываться в хорошенькие истории, высаживаться в одиночку и попадать в ловушки... Так вот: из этой вам не выйти.";
			link.l1 = "Спасибо за доклад и предупреждение. Если я все же решу совершить высадку, то обязательно захвачу с собой авангард и отряд из наших лучших бойцов.";
			link.l1.go = "AlonsoNaPalube_5";
		break;
		
		case "AlonsoNaPalube_5":
			dialog.text = "С этим могут возникнуть сложности капитан. Абордаж - то одно, а на суше лезть под пули морских пехотинцев и сабли разного сброда, что Блэквуд, говорят, понанимал в каждой дыре Малых Антил - совсем другое. Да и слухи ходят нехорошие о Каймане... Нет, много добровольцев вы на такую работу не найдете.";
			link.l1 = "Значит, придётся обойтись кем можем. Твоё участие обязательно, Алонсо.";
			link.l1.go = "AlonsoNaPalube_LiteGroup";
			link.l2 = "По-моему, я уже доказал"+GetSexPhrase("","")+" всем всё, что можно было доказать. Пойдут все хорошие бойцы и стрелки. Это приказ.";
			link.l2.go = "AlonsoNaPalube_StrongGroup";
			link.l3 = "Хм... Что ж, мне нужно всё обдумать. Возможно, мы вернёмся к этому вопросу позже.";
			link.l3.go = "AlonsoNaPalube_Exit";
		break;
		
		case "AlonsoNaPalube_Exit":
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
			EndQuestMovie();
			bQuestDisableMapEnter = false;
			chrDisableReloadToLocation = false;
			if(UnloadLocation(loadedLocation) == true)
			{
				pchar.Ship.Pos.x = 0;
				pchar.Ship.Pos.z = 0;
				pchar.Ship.Ang.y = 0;
				Land_MapLoad();
				pchar.location = "";
			}
		break;
		
		case "AlonsoNaPalube_LiteGroup":
			dialog.text = "Так точно, кэп!";
			link.l1 = "А что с кораблём Блэквуда? Не доставит ли он проблем?";
			link.l1.go = "AlonsoNaPalube_Vpered";
			pchar.questTemp.LadyBeth_LiteGroup = true;
		break;
		
		case "AlonsoNaPalube_StrongGroup":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50 || sti(pchar.rank) >= 17)
			{
				dialog.text = "Так точно, кэп!";
				link.l1 = "А что с кораблём Блэквуда? Не доставит ли он проблем?";
				link.l1.go = "AlonsoNaPalube_Vpered";
				pchar.questTemp.LadyBeth_StrongGroup = true;
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50) notification("Проверка пройдена", SKILL_Leadership);
				if (sti(pchar.rank) >= 17) notification("Проверка уровня пройдена", "None");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube2"))
				{
					dialog.text = "Боюсь, пока нет, капитан.";
				}
				else
				{
					dialog.text = "Вам нечего доказывать ни мне, ни вашим офицерам, и мы пойдем по приказу туда, куда вы скажете, но обычный матрос мыслит по-другому. Боюсь, возникнут проблемы, капитан.";
				}
				link.l1 = "Значит, придётся обойтись кем можем. Твоё участие обязательно, Алонсо.";
				link.l1.go = "AlonsoNaPalube_LiteGroup";
				link.l2 = "Хм... Что ж, мне нужно всё обдумать. Возможно, мы вернёмся к этому вопросу позже.";
				link.l2.go = "AlonsoNaPalube_Exit";
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) < 50) notification("Недостаточно развит навык (50)", SKILL_Leadership);
				if (sti(pchar.rank) < 17) notification("Требуется 17 уровень", "None");
			}
		break;
		
		case "AlonsoNaPalube_Vpered":
			dialog.text = "Шнява. Говорят, настоящая красавица с грозным норовом. Я бы не переживал насчёт неё. Скорее всего, вся команда пашет как проклятая на суше, пока корабль надежно запрятан в складках береговой линии. Когда и если мы победим, сможем её взять призом с суши.";
			link.l1 = "Собирай людей. Сегодня хороший день - фортуна будет на нашей стороне.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_AlonsoNaPalube_Vpered");
		break;
		
		// Диалог в таверне с Блеквудом
		case "LadyBeth_DialogInCity": // главное меню
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Fourth"))
			{
				dialog.text = "Рад вас видеть, капитан. Мне кажется, мы всё уже с вами обсудили.";
				link.l1 = "И правда. Прощайте.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LadyBeth_DialogInCity_again";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Third"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", Альберт.";
				link.l1.go = "LadyBeth_DialogInCity_Third_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", капитан Блэквуд.";
				link.l1.go = "LadyBeth_DialogInCity_Second_1";
				break;
			}
			if (startHeroType == 4)
			{
				dialog.text = "...";
				link.l1 = "Здравствуйте. Вы капитан Блэквуд?";
				link.l1.go = "LadyBeth_DialogInCity_First_Helena_1";
			}
			else
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+". Вы капитан Альберт Блэквуд, верно?";
				link.l1.go = "LadyBeth_DialogInCity_First_1";
			}
		break;
		
		case "LadyBeth_DialogInCity_again": // повтор
			dialog.text = "Рад вас видеть, капитан. Мне кажется, мы всё уже с вами обсудили.";
			link.l1 = "И правда. Прощайте.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LadyBeth_DialogInCity_again";
		break;
		
		case "LadyBeth_DialogInCity_First_1": // первый диалог
			dialog.text = "Да, он самый. А вы?";
			link.l1 = "Капитан "+GetFullName(pchar)+". Командую кораблём '" + PChar.Ship.Name + "'.";
			link.l1.go = "LadyBeth_DialogInCity_First_2";
		break;
		
		case "LadyBeth_DialogInCity_First_2":
			dialog.text = "Капитан... Вы бывали на Каймане?";
			link.l1 = "Лишь проходил мимо.";
			link.l1.go = "LadyBeth_DialogInCity_First_3";
		break;
		
		case "LadyBeth_DialogInCity_First_3":
			dialog.text = "А слышали что-нибудь о сокровищах там?";
			link.l1 = "Нет, ничего конкретного.";
			link.l1.go = "LadyBeth_DialogInCity_First_4";
		break;
		
		case "LadyBeth_DialogInCity_First_4":
			dialog.text = "Следы испанцев? Старое оружие? Монеты времён конкистадоров?";
			link.l1 = "Ничего такого не находил.";
			link.l1.go = "LadyBeth_DialogInCity_First_5";
		break;
		
		case "LadyBeth_DialogInCity_First_5":
			dialog.text = "Местные легенды? Истории о Кортесе? Что-нибудь о захоронениях?";
			link.l1 = "Извините, капитан, но я не располагаю такой информацией. И это всё уже напоминает какой-то допрос.";
			link.l1.go = "LadyBeth_DialogInCity_First_6";
		break;
		
		case "LadyBeth_DialogInCity_First_6":
			dialog.text = "Прошу прощения.. Дурная привычка бывшего офицера. Просто... это крайне важно для меня.";
			link.l1 = "Почему вас так интересует именно Кайман?";
			link.l1.go = "LadyBeth_DialogInCity_First_7";
		break;
		
		case "LadyBeth_DialogInCity_First_7":
			dialog.text = "Неважно. Ещё раз, прошу меня извинить.";
			link.l1 = "Понимаю. Удачи в ваших поисках.";
			link.l1.go = "LadyBeth_DialogInCity_First_8";
		break;
		
		case "LadyBeth_DialogInCity_First_8":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Доброй ночи";
			else sStr = "Доброго вам дня";
			dialog.text = "Заходите ко мне, если появится что-то стоящее. Мне было бы приятно пообщаться с другим капитаном... с человеком, который понимает море. " + sStr + ".";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_First_9";
		break;
		
		case "LadyBeth_DialogInCity_First_9":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_1": // первый диалог с Элен
			dialog.text = "Собственной персоной. А вы... Капитан Элен МакАртур? Протеже Яна Свенсона, верно? Наслышан о вас.";
			link.l1 = "Вы хорошо осведомлены, капитан Блэквуд. Но я не удивлена, что английский офицер знает обо мне.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_2":
			dialog.text = "Бывший офицер. И все красные мундиры знают о вас и ваших... уникальных преференциях от Короны. Бакаут, как говорится, не пахнет. А история о том, как ваш отец Шон МакАртур с детства брал вас в море и сделал капитаном, стала чем-то вроде легенды на флоте.";
			link.l1 = "И каковы ощущения от встречи с этой легендой?";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_3";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_3":
			dialog.text = "Я лично восхищен. Хотя многих моих бывших коллег это, признаться, сильно раздражает. Но чтобы стать капитаном, нужно нечто большее, чем просто благородное происхождение или королевский патент, не так ли?";
			link.l1 = "Верно. Нужны знания, опыт и постоянная готовность доказывать свою компетентность. Особенно в моём случае.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_4";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_4":
			dialog.text = "Именно! В море, как и в жизни, важны не титулы, а результаты. Рад знакомству, капитан МакАртур. Надеюсь, ещё увидимся. Возможно, вы заглянете на бокал вина, когда я вернусь со своей экспедиции?";
			link.l1 = "Возможно. Удачи в ваших поисках, капитан.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_5_harizma";
			link.l2 = " Не интересует. Но удачи в ваших поисках, капитан.";
			link.l2.go = "LadyBeth_DialogInCity_First_Helena_5_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_harizma":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_oruzhie":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_1": // второй диалог
			dialog.text = "А, капитан "+pchar.lastname+"! Рад вас видеть. Присядете?";
			link.l1 = "С удовольствием.";
			link.l1.go = "LadyBeth_DialogInCity_Second_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_2":
			dialog.text = "Капитан... скажите, что для вас значат настоящие сокровища?";
			link.l1 = "Настоящее сокровище - это любовь. Правильный человек рядом. Нет ничего хуже, чем быть одному.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love";
			link.l2 = "Деньги, конечно же. Что ещё может быть сокровищем?";
			link.l2.go = "LadyBeth_DialogInCity_Second_3_sokrovisha";
			link.l3 = "Ценное и уникальное снаряжение. Хорошая шпага или пистоль стоят дороже золота.";
			link.l3.go = "LadyBeth_DialogInCity_Second_3_oruzhie";
			link.l4 = "Знания. Самое ценное сокровище - то, что у тебя в голове.";
			link.l4.go = "LadyBeth_DialogInCity_Second_3_znania";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love":
			if (startHeroType == 4)
			{
				dialog.text = "Любовь? Хм... Не ожидал такого ответа от дочери пирата. Я... я был помолвлен. С Элизабет. Дочерью плантатора с Барбадоса. Но её отец... он посчитал, что у меня недостаточно денег. Что я могу дать его дочери, кроме своей любви? Вам повезло, капитан МакАртур. У вас был отец, который ценил ваши способности выше, чем ваше приданое.";
				link.l1 = "Возможно, дело не в везении, а в том, что настоящая любовь не измеряется золотом. Мой отец это понимал. А что насчет вашей невесты? Она разделяет взгляды своего отца?";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_1";
			}
			else
			{
				dialog.text = "Любовь? Да... Возможно, вы правы. Я... я был помолвлен. На Барбадосе. Мы любили друг друга, но... её отец счёл меня недостойной партией. Ха! Недостаточно богатым. Поэтому я здесь - ищу сокровища, чтобы доказать им всем. Может и зря?";
				link.l1 = "Возможно, стоит просто поговорить с ней? К чёрту этого плантатора.";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_2";
			}
			AddComplexLandExpToScill(100, 100, 0);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_2":
			dialog.text = "Поговорить... Да, наверное. Но что я скажу? 'Прости, я не смог обеспечить тебе достойную жизнь'? Нет. Я должен вернуться победителем. Или не возвращаться вовсе.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_1":
			dialog.text = "Элизабет? Нет... она любит меня. Но я... я не мог позволить ей жить в нищете. Она заслуживает лучшего. А я должен доказать, что достоин её.";
			link.l1 = "Иногда гордость мешает счастью больше, чем бедность, капитан.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_2":
			dialog.text = "Я не могу вернуться с пустыми руками. Просто не могу. Прошу прощения, у меня много работы. Было приятно побеседовать с вами, капитан МакАртур.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha":
			dialog.text = "Какой банальный ответ. Но с ним сложно спорить. И правда, когда ты вырос в трущобах Бристоля, когда тебе приходилось драться за объедки... ты начинаешь понимать истинную ценность денег. Это не роскошь. Это свобода. Возможность не возвращаться в ту грязь, из которой ты выбрался с таким трудом.";
			link.l1 = "Соглашусь. Деньги решают большинство проблем. А если не решают - значит, их просто недостаточно.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_sokrovisha_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha_2":
			dialog.text = "Именно! Вы понимаете. Деньги не делают тебя счастливым, но их отсутствие делает тебя несчастным наверняка. Мне-то это хорошо известно...";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie":
			dialog.text = "Интересно. Практично. У меня есть аркебуза... настоящая, времён конкистадоров. Подарок одного священника. Иногда я думаю, что она стоит больше, чем все золото, которое я нашел. Но... это не решит моих проблем.";
			link.l1 = "Хорошее оружие может решить многие проблемы. И оно никогда тебя не предаст.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie_2":
			dialog.text = "В этом есть своя правда. Но некоторые битвы нельзя выиграть силой оружия.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_znania":
			dialog.text = "Знания... Да, я понимаю. Я изучил все, что мог, о конкистадорах, о кладах. Составил целый устав по поиску сокровищ. Придумал систему регулярных учений и материальных поощрений для корабельной стрелковой роты. Любой капитан был бы рад заполучить мой устав. Но все эти знания... Они бесполезны, если не привести к результату. К настоящему результату.";
			link.l1 = "Но именно знания помогают достичь результата. Без них любой поиск - просто блуждание в темноте.";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "LadyBeth_DialogInCity_Second_4":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Что ж, уже поздно, а у меня много работы";
			else sStr = "Что ж, у меня много работы";
			dialog.text = "" + sStr + "... Благодарю за беседу, капитан. Было действительно интересно.";
			link.l1 = "И вам спасибо. "+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_5":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Third = true;
		break;
		
		case "LadyBeth_DialogInCity_Third_2": // третий диалог
			dialog.text = "А, "+pchar.name+"! Рад вас видеть. У меня отличные новости - я наконец нашёл решение своих проблем. Скоро в экспедицию, и на этот раз вернусь с настоящим сокровищем! Кстати, дружеский совет - держитесь подальше от Каймана. Теперь это моя территория.";
			link.l1 = "Кайман не принадлежит вам, Альберт. У вас нет на него коронных прав. Это пиратство.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma";
			link.l2 = "Угрожаете мне, Блэквуд?";
			link.l2.go = "LadyBeth_DialogInCity_Third_3_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma":
			dialog.text = "Коронные права? Вы бы пожили в трущобах Бристоля, "+pchar.name+", тогда бы поняли, чего стоят эти бумажки. Когда ты голоден, закон - пустой звук. Впрочем... вы правы. Формально я не имею прав на остров. Но я нашёл там то, что искал годами. И я не позволю никому это отнять.";
			link.l1 = "Надеюсь, вы понимаете, что идёте по опасному пути.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma_2":
			dialog.text = "Я всегда понимал, что моя дорога не будет легкой. Прощайте, "+pchar.name+". Возможно, мы ещё встретимся.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie":
			dialog.text = "Угрожаю? Нет, что вы. Просто дружеский совет от одного капитана другому. На Каймане опасно... особенно для тех, кто вмешивается в мои дела.";
			link.l1 = "Я запомню ваш 'совет'. Удачи на Каймане.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie_2":
			dialog.text = "И вам удачи, капитан. Надеюсь, она вам не понадобится. Прощайте.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_4":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Fourth = true;
		break;
		
		// Ловушка, абордаж в каюте
		case "LadyBeth_abordage":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Вы?!! Думаете, я сдамся? Думаете, я вернусь в нищету? Лучше сдохну, чем снова буду голодать в трущобах! Никакой пощады, никакой награды, никакой победы! Под койкой бочонок с порохом... Мы все отправимся на дно!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
			else
			{
				dialog.text = "Кто вы такой, чтобы нападать на меня?! Думаете, я сдамся? Нет! Лучше сдохну, чем снова буду голодать в трущобах! Никакой пощады, никакой награды, никакой победы! Под койкой бочонок с порохом... Мы все отправимся на дно!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
		break;
		
		// Блеквуд разговаривает с ГГ перед битвой на Каймане
		case "LadyBeth_BlackWood_Boss":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Капитан! Я же предупреждал вас. Теперь вы заплатите за свое любопытство.";
			}
			else
			{
				dialog.text = "Кто вы такой и как смеете вторгаться на мою территорию?! Этот остров мой!";
			}
			link.l1 = "Увидим, Блэквуд. Сегодня одним одержимым в этом мире станет меньше.";
			link.l1.go = "LadyBeth_BlackWood_Boss_oruzhie_1";
			link.l2 = "Давайте решим это мирно, Блэквуд. Я могу уйти.";
			link.l2.go = "LadyBeth_BlackWood_Boss_torgovlya_1";
			link.l3 = "Блэквуд, вы же разумный человек! Вы офицер! У вас над лагерем реет королевский флаг, чёрт побери! Неужели мы не можем договориться?";
			link.l3.go = "LadyBeth_BlackWood_Boss_harizma_1";
		break;
		
		case "LadyBeth_BlackWood_Boss_oruzhie_1":
			dialog.text = "Одержимым? Ха! Я просто человек, который знает, чего хочет!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_1":
			dialog.text = "Уйти? После того, что вы видели? Нет, нет, нет! Никто не должен знать о том, что я нашел здесь. Никто!";
			link.l1 = "Я даю вам слово, что никому не расскажу. Клянусь честью капитана.";
			link.l1.go = "LadyBeth_BlackWood_Boss_torgovlya_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_2":
			dialog.text = "В этом мире нет чести, капитан. Есть только грязь, нищета и презрение. Я сожалею, но вы должны умереть здесь.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
		break;
		
		case "LadyBeth_BlackWood_Boss_harizma_1":
			dialog.text = "Я думал. Много думал. И понял - это мой единственный шанс. Либо я найду золото Кортеса, либо... ничего. Понимаете? НИЧЕГО! Я не вернусь к прежней жизни! Не вернусь в грязь и нищету! Лучше умереть здесь!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_2":
			dialog.text = "К бою! Буллок, Фрейзер - бейте картечью если сунутся! Хопкинс, в атаку!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_CaimanKino_11");
		break;
		
		// Диалоги с офицерами
		case "LadyBeth_Helena_1": // Элен
			dialog.text = "Ты в порядке?";
			link.l1 = "Да, всё хорошо. А ты?";
			link.l1.go = "LadyBeth_Helena_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Helena_2":
			dialog.text = "Жива. Но эти сухопутные сражения не для меня. Дай мне палубу под ногами и я разнесу любой корабль, а здесь... странное место. Заставить сотню морских волков сойти на землю, махать кирками, строить укрепления... Я бы так не смогла.";
			link.l1 = "Блэквуд умел вдохновлять свою команду.";
			link.l1.go = "LadyBeth_Helena_3";
		break;
		
		case "LadyBeth_Helena_3":
			dialog.text = "Я слышала о нём ещё в Блювельде. Многие английские моряки говорили о нём с уважением. Лучший офицер на флоте, блестящая карьера... и вдруг всё бросил ради поисков сокровищ.";
			link.l1 = "Что ты о нём думаешь?";
			link.l1.go = "LadyBeth_Helena_4";
		break;
		
		case "LadyBeth_Helena_4":
			dialog.text = "Думаю, что на примере Блэквуда хорошо виден груз ответственности, которую мы... то есть ты, несешь перед своими людьми. Прошу тебя, не стань таким же капитаном, каким стал он.";
			link.l1 = "Я постараюсь, Элен.";
			link.l1.go = "LadyBeth_Helena_5";
		break;
		
		case "LadyBeth_Helena_5":
			dialog.text = "Спасибо, мой капитан. Я знаю, что у тебя всё получится.";
			link.l1 = "У нас.";
			link.l1.go = "LadyBeth_Helena_6";
		break;
		
		case "LadyBeth_Helena_6":
			dialog.text = "У нас.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Helena_7";
		break;
		
		case "LadyBeth_Helena_7":
			DialogExit();
			Return_HelenaOfficer();
		break;
		
		case "LadyBeth_Mary_1": // Мэри
			dialog.text = "Шарль... как же здесь жутко.";
			link.l1 = "Ты в порядке, Мэри? Ты держалась как настоящий солдат.";
			link.l1.go = "LadyBeth_Mary_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Mary_2":
			dialog.text = "Нет, не в порядке, да. Посмотри на этих людей! Они работали до изнеможения, жили впроголодь, умирали от болезней... И ради чего? Ради золота, которое, возможно, даже не существует.";
			link.l1 = "Блэквуд верил, что оно здесь.";
			link.l1.go = "LadyBeth_Mary_3";
		break;
		
		case "LadyBeth_Mary_3":
			dialog.text = "Этот красный мундир... точно такой же, как у меня. Английский офицер... Знаешь, я вдруг подумала о родителях, да. О корнях... о том, чего никогда не знала. Может, я тоже из таких?";
			link.l1 = "Из каких?";
			link.l1.go = "LadyBeth_Mary_4";
		break;
		
		case "LadyBeth_Mary_4":
			dialog.text = "Из тех, кто ищет что-то, чего, возможно, и нет вовсе. А потом теряет себя в этих поисках. Я... я бы хотела поговорить об этом позже, да. Когда мы покинем это ужасное место.";
			link.l1 = "Конечно, Мэри.";
			link.l1.go = "LadyBeth_Mary_5";
		break;
		
		case "LadyBeth_Mary_5":
			dialog.text = "Давай сначала похороним его, пожалуйста? Даже если он этого не заслуживает. Ради того человека, которым он когда-то был.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Mary_6";
		break;
		
		case "LadyBeth_Mary_6":
			DialogExit();
			Return_MaryOfficer();
		break;
		
		case "LadyBeth_Tichingitu_1": // Тичингиту
			dialog.text = "Капитан, Тичингиту видеть здесь плохое место. Очень плохое место.";
			link.l1 = "Что ты имеешь в виду?";
			link.l1.go = "LadyBeth_Tichingitu_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Tichingitu_2":
			dialog.text = "Этот остров теперь быть проклят. Земля впитать слишком много крови и слёз. Каждый, кто копать здесь, вдыхать этот проклятие.";
			link.l1 = "Ты думаешь, Блэквуд был одержим?";
			link.l1.go = "LadyBeth_Tichingitu_3";
		break;
		
		case "LadyBeth_Tichingitu_3":
			dialog.text = "Не просто одержим. Он быть... как сказать... пустой сосуд. Что-то войти в него и вытеснить его душа. Мой видеть такое раньше. Когда шаман мой племя принести человеческий жертва духам. Тот шаман иметь такой же взгляд.";
			link.l1 = "Но что могло вызвать такую одержимость?";
			link.l1.go = "LadyBeth_Tichingitu_4";
		break;
		
		case "LadyBeth_Tichingitu_4":
			dialog.text = "Человек с пустотой внутри легко заполнить чужими мыслями. Кто-то найти его слабость и воспользоваться. Тичингиту почти жалеть этот человек.";
			link.l1 = "Почти?";
			link.l1.go = "LadyBeth_Tichingitu_5";
		break;
		
		case "LadyBeth_Tichingitu_5":
			dialog.text = "Да, почти. Каждый воин сам отвечать за свой выбор. Даже если демоны шептать ему на ухо.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Tichingitu_6";
		break;
		
		case "LadyBeth_Tichingitu_6":
			DialogExit();
			Return_TichingituOfficer();
		break;
		
		case "LadyBeth_Irons_1": // Томми
			dialog.text = "Чёрт возьми, капитан! Ты только глянь на это! Прям как в старые добрые!";
			link.l1 = "Ты-то хорошо знаешь, что такое война на суше.";
			link.l1.go = "LadyBeth_Irons_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Irons_2":
			dialog.text = "Напомнило мне сражение при Нейзби. Наше крыло кавалерии столкнулось с отрядом кавалеристов Рупрехта. Они дрались с такой же яростью за своего короля.";
			link.l1 = "Что ты думаешь о Блэквуде?";
			link.l1.go = "LadyBeth_Irons_3";
		break;
		
		case "LadyBeth_Irons_3":
			dialog.text = "Этот Блэквуд был либо гением, либо полным психом. Думаю, и то и другое. Знаешь, что меня удивляет? Его люди. Многие из них - бывшие военные. Не отбросы общества, а настоящие профессионалы. И все они следовали за ним в этом безумии. Даже морская пехота Фокса. Ха! Вот уж кто обрадуется сегодняшней бойне! Он так и не простил им дезертирства.";
			link.l1 = "Может, дело в деньгах?";
			link.l1.go = "LadyBeth_Irons_4";
		break;
		
		case "LadyBeth_Irons_4":
			dialog.text = "Не-а, тут что-то ещё. Этот парень имел над ними власть. Настоящую власть. А ещё я слышал, что он был помолвлен с какой-то богатой девицей с Барбадоса. Странно, что он не женился на ней, получив все эти сокровища. Типичный солдат - не знал, когда пора заканчивать войну.";
			link.l1 = "Спасибо, Томми. Ты настоящий мыслитель.";
			link.l1.go = "LadyBeth_Irons_5";
		break;
		
		case "LadyBeth_Irons_5":
			dialog.text = "А?";
			link.l1 = "Ничего.";
			link.l1.go = "LadyBeth_Irons_6";
		break;
		
		case "LadyBeth_Irons_6":
			DialogExit();
			Return_IronsOfficer();
		break;
		
		case "LadyBeth_Knippel_1": // Книппель
			dialog.text = "Как же горько это видеть, капитан. До чего мы опустились?!";
			link.l1 = "Мы?";
			link.l1.go = "LadyBeth_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Knippel_2":
			dialog.text = "Английский флот! Вы только посмотрите: маленькие точки красных мундиров, лежащие в куче этого мёртвого отребья!";
			link.l1 = "Некоторые из этого 'отребья' - наши люди, Чарли. Понимаю твои, чувства, но...";
			link.l1.go = "LadyBeth_Knippel_3";
		break;
		
		case "LadyBeth_Knippel_3":
			dialog.text = "В жопу, сэр!";
			link.l1 = "Я понимаю твои чувства, но лучше бы обратил свою праведную ярость и разочарование на Блэквуда. Это он дезертировал из твоего английского любимого флота и привёл их сюда.";
			link.l1.go = "LadyBeth_Knippel_4";
			link.l2 = "И правда. Пойдём, день ещё не закончен.";
			link.l2.go = "LadyBeth_Knippel_6";
			PlaySound("Voice\Russian\hambit\Charlie Knippel-07.wav");
		break;
		
		case "LadyBeth_Knippel_4":
			dialog.text = "Они только следовали за своим командиром!";
			link.l1 = "Как ты следовал за Флитвудом?";
			link.l1.go = "LadyBeth_Knippel_5";
			link.l2 = " И правда. Пойдём, день ещё не закончен.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_5":
			dialog.text = "Как я следую за вами!";
			link.l1 = "Надеюсь, я окажусь лучшим капитаном, чем Блэквуд и Флитвуд. Пойдём, день ещё не закончен.";
			link.l1.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_6":
			dialog.text = "Так точно, кэп. И когда он закончится - буду пить пока не закончится следующий.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Knippel_7";
		break;
		
		case "LadyBeth_Knippel_7":
			DialogExit();
			Return_KnippelOfficer();
		break;
		
		case "LadyBeth_Alonso_1": // Алонсо
			dialog.text = "Madre de Dios, капитан! Вы в порядке?";
			link.l1 = "Это ещё только предстоит выяснить. Сколько человек мы потеряли?";
			link.l1.go = "LadyBeth_Alonso_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Alonso_2":
			dialog.text = "Убитыми? В этой авантюре мы потеряли "+sti(pchar.SailorDiedInBattleInfo)+" человек. Не хочу показаться назойливым, капитан, но... я же вас предупреждал!";
			link.l1 = "Я пропущу эту ремарку мимо ушей, потому что сегодня ты проявил себя, Алонсо. Откуда в тебе столько талантов?";
			link.l1.go = "LadyBeth_Alonso_3";
		break;
		
		case "LadyBeth_Alonso_3":
			dialog.text = "Однажды я вам расскажу эту историю, капитан - если доживём конечно.";
			link.l1 = "Ещё ценные советы будут?";
			link.l1.go = "LadyBeth_Alonso_4";
		break;
		
		case "LadyBeth_Alonso_4":
			dialog.text = "Если бы тут и были сокровища - они бы уже их давно нашли. Но нам всё равно стоит обыскать остров и найти выживших, а потом решить, что с ними делать. Да и про корабль Блэквуда забывать нельзя: я слышал про эту красавицу-шняву только хорошее. Будет обидно упустить такой куш, капитан. Разумеется, я всего лишь доношу позицию команды по данному вопросу.";
			link.l1 = "Ну разумеется. Пойдём. Трофеи ждут!";
			link.l1.go = "LadyBeth_Alonso_5";
		break;
		
		case "LadyBeth_Alonso_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		// Диалог с матросом в гроте Каймана
		case "LadyBeth_MatrosyInGrot":
			dialog.text = "Не стреляйте! Мы сдаёмся!";
			link.l1 = "Кто вы такие?";
			link.l1.go = "LadyBeth_MatrosyInGrot_2";
		break;
		
		case "LadyBeth_MatrosyInGrot_2":
			dialog.text = "Мы... мы с 'Леди Бет'. Экипаж капитана Блэквуда. Он... он жив?";
			link.l1 = "Нет. Ваш капитан мёртв.";
			link.l1.go = "LadyBeth_MatrosyInGrot_3";
		break;
		
		case "LadyBeth_MatrosyInGrot_3":
			dialog.text = "Значит, всё кончено... Слава Богу.";
			link.l1 = "Вы не похожи на скорбящих по своему капитану.";
			link.l1.go = "LadyBeth_MatrosyInGrot_4";
		break;
		
		case "LadyBeth_MatrosyInGrot_4":
			dialog.text = "Вы не понимаете. Блэквуд был великим человеком. Лучшим капитаном, которого я знал. Но в последние месяцы... он изменился. Стал одержимым, жестоким. Заставлял нас работать день и ночь, искать что-то, чего, возможно, даже не существует.";
			link.l1 = "Я беру вас в свою команду. Нам нужны опытные моряки.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda";
			link.l2 = " Горе побежденным, парни. Теперь ваше место в моем трюме. Если повезет - доживёте до какой-нибудь плантации на Барбадосе.";
			link.l2.go = "LadyBeth_MatrosyInGrot_PlusRaby";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda":
			dialog.text = "Правда? Вы... вы не боитесь, что мы... что с нами что-то не так после всего этого?";
			link.l1 = "Каждый заслуживает второй шанс.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda_1";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda_1":
			dialog.text = "Спасибо, капитан. Клянусь, вы не пожалеете. Мы хорошие моряки. И... может быть, теперь кошмары прекратятся.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 30;
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusRaby":
			dialog.text = "Спасибо, спасибо! По крайней мере, мы будем живы. Увезите нас отсюда, пожалуйста. Этот остров... он словно проклят.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+30);
		break;
		
		case "LadyBeth_MatrosyInGrot_exit":
			DialogExit();
			for (i=1; i<=8; i++)
			{
				sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		// Диалог с матросом на Леди Бет
		case "LadyBeth_EnemyMatros_1":
			dialog.text = "Какого чёрта?! Как вы посмели атаковать 'Леди' и убить Джереми? Вам не уйти отсюда живыми, мерзавцы, капитан вернётся и...";
			link.l1 = "Ваш капитан мёртв. Джереми выстрелил первым, а вашу 'Леди' я забираю как законный и оплаченный кровью приз.";
			link.l1.go = "LadyBeth_EnemyMatros_2";
		break;
		
		case "LadyBeth_EnemyMatros_2":
			dialog.text = "Капитан... мёртв? Врёшь, собака! Ты не стоишь и пуговицы на его мундире!";
			link.l1 = "Если этот мундир что-то значил, то для того Блэквуда, которого уже давно нет. Вам решать - сражаться за мертвеца или сохранить свои жизни.";
			link.l1.go = "LadyBeth_EnemyMatros_3";
		break;
		
		case "LadyBeth_EnemyMatros_3":
			if (CharacterIsHere("Helena"))
			{
				StartInstantDialog("Helena", "LadyBeth_EnemyMatros_Helena_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Knippel"))
			{
				StartInstantDialog("Knippel", "LadyBeth_EnemyMatros_Knippel_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Irons"))
			{
				StartInstantDialog("Irons", "LadyBeth_EnemyMatros_Irons_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			dialog.text = "Мы не отдадим вам корабль без боя!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		case "LadyBeth_EnemyMatros_Helena_1":
			dialog.text = "Послушайте, ребята. Я знаю, что вы преданы своему капитану. Это достойно уважения. Но он мёртв, а вы живы. И должны решать, как жить дальше. Мы предлагаем вам шанс начать заново.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_Knippel_1":
			dialog.text = "Капитан, эти люди не враги. Они просто выполняли приказы. Многие из них - бывшие королевские моряки, хорошо обученные и дисциплинированные. Было бы расточительством не воспользоваться их умениями. Парни, я бывал на вашем месте не раз за свою долгую службу на флоте. И сделал правильный выбор. Сделайте его и вы.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
		break;
		
		case "LadyBeth_EnemyMatros_Irons_1":
			dialog.text = "Ну что, братцы-морячки! Выбор простой - или живёте, хоть в трюме пленниками, хоть к нам в команду с хорошим пайком и регулярной оплатой, или... (проводит пальцем по горлу) Я бы на вашем месте выбрал первое!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_10";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_5":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_6", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_6":
			dialog.text = "...";
			link.l1 = "Вы станете частью моей команды.";
			link.l1.go = "LadyBeth_EnemyMatros_7";
			link.l2 = "Горе побежденным, парни. Теперь ваше место в моём трюме. Если повезёт - доживёте до какой-нибудь плантации на Барбадосе.";
			link.l2.go = "LadyBeth_EnemyMatros_9";
		break;
		
		case "LadyBeth_EnemyMatros_7":
			dialog.text = "Вы берёте нас в свою команду? После всего?";
			link.l1 = "Хорошие моряки всегда в цене. А капитан Блэквуд умел выбирать людей.";
			link.l1.go = "LadyBeth_EnemyMatros_8";
		break;
		
		case "LadyBeth_EnemyMatros_8":
			dialog.text = "Спасибо, капитан. Мы не подведём вас.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 12;
		break;
		
		case "LadyBeth_EnemyMatros_9":
			dialog.text = "Что ж... по крайней мере, только так эта авантюра и могла закончится. Простите нас, капитан Блэквуд. Не уберегли.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+12);
		break;
		
		case "LadyBeth_EnemyMatros_10":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_11", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_11":
			dialog.text = "Мы не отдадим вам корабль без боя!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		// Диалог с Элизабет Бишоп
		case "LadyBeth_Elizabeth_1":
			dialog.text = "...";
			link.l1 = "Прошу прощения. Вы - Элизабет?";
			if (pchar.sex == "man") link.l1.go = "LadyBeth_Elizabeth_2";
			if (pchar.sex == "woman") link.l1.go = "LadyBeth_Elizabeth_Woman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Elizabeth_2":
			dialog.text = "Да, это я. А вы кто?";
			link.l1 = "Капитан "+GetFullName(pchar)+". Я... знал Альберта Блэквуда.";
			link.l1.go = "LadyBeth_Elizabeth_3";
		break;
		
		case "LadyBeth_Elizabeth_3":
			dialog.text = "Моего Альберта? Боже мой... Он... с ним всё в порядке?";
			link.l1 = "К сожалению, нет. Он погиб в бою. Сражался до последнего.";
			link.l1.go = "LadyBeth_Elizabeth_4";
		break;
		
		case "LadyBeth_Elizabeth_4":
			dialog.text = "Я... я догадывалась. Столько лет без весточки... Знаете, я ведь ждала его. Долго ждала. Отец говорил, что Альберту нужно лишь дождаться повышения в звании. Губернатор уже всё решил, это был вопрос нескольких месяцев. Но Альберт... он воспринял тот разговор совсем иначе. Сказал, что вернётся богатым, достойным моей руки. И ушёл. Просто... ушёл.";
			link.l1 = "Он до последнего дня думал о вас.";
			link.l1.go = "LadyBeth_Elizabeth_5";
		break;
		
		case "LadyBeth_Elizabeth_5":
			dialog.text = "Как же глупо. Мне не нужны были его сокровища. Я любила его, а не его деньги. Была готова бежать с ним... но он был таким гордым. Я ждала письма, весточки... А потом пришёл только этот странный устав. Такой холодный, расчётливый документ... совсем не похожий на Альберта, которого я знала. Тогда я поняла, что потеряла его.";
			link.l1 = "Среди его вещей я нашёл это.";
			link.l1.go = "LadyBeth_Elizabeth_6";
		break;
		
		case "LadyBeth_Elizabeth_6":
			dialog.text = "Карта к моему дому? Я и была его главным сокровищем? Какая ирония. Он искал богатства по всем Карибам, а единственное, что имело для него значение, всегда было здесь... Подождите. У меня есть кое-что для вас. Это устав Альберта. Он прислал мне его год назад. Говорил, что это поможет ему найти сокровища и вернуться ко мне. Теперь он вам пригодится больше.";
			link.l1 = "Спасибо, Элизабет. Мне жаль, что всё сложилось именно так.";
			link.l1.go = "LadyBeth_Elizabeth_7";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_7":
			dialog.text = "А я вышла замуж, капитан. За господина Бишопа. Отец настоял. Вы не знаете этого человека... и не хотели бы знать. Каждый день я думаю о том, как сложилась бы моя жизнь, если бы Альберт просто... вернулся.";
			link.l1 = "Теперь и я буду об этом думать.";
			link.l1.go = "LadyBeth_Elizabeth_8";
		break;
		
		case "LadyBeth_Elizabeth_8":
			dialog.text = "Прощайте, капитан. И... берегите себя. Не гонитесь за призраками.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		case "LadyBeth_Elizabeth_Woman_2":
			dialog.text = "Да, это я.";
			link.l1 = "Капитан "+GetFullName(pchar)+". Я... знала Альберта Блэквуда.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_3";
		break;
		
		case "LadyBeth_Elizabeth_Woman_3":
			dialog.text = "Моего Альберта? Боже мой... Он... А вы кто?";
			link.l1 = "Капитан "+GetFullName(pchar)+", я же сказала. Командую собственным кораблем.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_4";
		break;
		
		case "LadyBeth_Elizabeth_Woman_4":
			dialog.text = "Капитан? Женщина-капитан? Вы... Вы были с Альбертом? В каком смысле... знали его?";
			link.l1 = "Только как капитана. Мне жаль, но Альберт погиб. Я была свидетелем его последнего боя.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_5";
		break;
		
		case "LadyBeth_Elizabeth_Woman_5":
			dialog.text = "Понимаю. Простите мои подозрения. Просто... капитан Блэквуд всегда привлекал внимание женщин. Даже здесь, на Барбадосе. Особенно здесь.";
			link.l1 = "Вы любили его.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_6";
		break;
		
		case "LadyBeth_Elizabeth_Woman_6":
			dialog.text = "Всем сердцем. Отец говорил, что Альберту нужно лишь дождаться повышения. Это был вопрос нескольких месяцев. Но он понял слова отца как отказ из-за бедности. Сказал, что вернётся с сокровищами. И ушёл.";
			link.l1 = "Мужчины и их гордость!";
			link.l1.go = "LadyBeth_Elizabeth_Woman_7";
		break;
		
		case "LadyBeth_Elizabeth_Woman_7":
			dialog.text = "Вам повезло, капитан "+pchar.lastname+". Вы свободны. Плывете куда хотите. Никаких плантаторов, никаких отцов, решающих вашу судьбу. Никаких мужей, считающих вас своей собственностью.";
			link.l1 = "Свобода дорого обходится. И её приходится защищать каждый день.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_8";
		break;
		
		case "LadyBeth_Elizabeth_Woman_8":
			dialog.text = "У меня, возможно, есть кое-что, что вам поможет в этом деле. Вот, возьмите. Это его устав по поиску сокровищ. Альберт прислал мне его около года назад. Сказал, что это лучшее, что он когда-либо создал. Что это поможет ему разбогатеть и вернуться ко мне. Но с каждой страницей он всё меньше напоминал того Альберта, которого я знала.";
			link.l1 = "Спасибо. Я сохраню его.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_9";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_Woman_9":
			dialog.text = "Прошу вас, капитан... цените свою свободу. Я вышла замуж за полковника Бишопа. Человека, которого боится даже мой отец. Если бы я была свободна, как вы... Всё было бы иначе.";
			link.l1 = "Я знаю.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_10";
		break;
		
		case "LadyBeth_Elizabeth_Woman_10":
			dialog.text = "Прощайте, капитан. И попутного вам ветра.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
	}
} 