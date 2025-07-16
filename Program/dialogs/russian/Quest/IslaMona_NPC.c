void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
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
		
		// Родриго Хименес
		case "Himenes_exit":
			dialog.text = "Что-то ещё, капитан?";
			link.l1 = "Пока ничего...";
			link.l1.go = "Himenes_exit_1";
		break;
		
		case "Himenes_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
		break;
		
		case "Himenes":
			dialog.text = "Х-ха-ха-ха! Сеньор Хесукристо! Слава Сантьяго Покровителю! Слава Богородице! Мы спасены! Ха-ха-ха!";
			link.l1 = "Испа-а-а-нцы! К оружию!";
			link.l1.go = "Himenes_1_1";
			link.l2 = "Приветствую. Я так понял, у вас проблемы? Кто вы?";
			link.l2.go = "Himenes_2";
		break;
		
		case "Himenes_1_1":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Х-ха-ха-ха-ха-ха-ха-ха-ха-ха-ха!";
			link.l1 = "Ладно-ладно, успокойтесь. Это я по привычке.";
			link.l1.go = "Himenes_2";
		break;
		
		case "Himenes_2":
			dialog.text = "Ха-ха! Сеньор, меня зовут Родриго Хименес. Я землемер и, волею судьбы, el jefe этих несчастных людей.";
			link.l1 = "И как же вас угораздило застрять здесь?";
			link.l1.go = "Himenes_3";
		break;
		
		case "Himenes_3":
			dialog.text = "Нас... высадили здесь. Но, сеньор, мы не преступники! Х-ха-ха-ха!";
			link.l1 = "А что смешного?";
			link.l1.go = "Himenes_4";
		break;
		
		case "Himenes_4":
			dialog.text = "Х... Простите, сеньор! Это всё мой недуг, с малых лет я смеюсь, если сильно волнуюсь. Ха.";
			link.l1 = "И вас избрали лидером?.. Ладно. На необитаемые острова просто так не высаживают, милейший. Может объяснитесь? Даю вам только одну попытку.";
			link.l1.go = "Himenes_5";
		break;
		
		case "Himenes_5":
			string nationManName[4];
			nationManName[0] = "Англичанин";
			nationManName[1] = "Француз";
			nationManName[2] = "Если ты это видишь, то это баг";
			nationManName[3] = "Испанец";
			dialog.text = "Извините, боюсь, что не расслышал вашего имени, сеньор. Вы англичанин?";
			link.l1 = nationManName[sti(pchar.BaseNation)] + ". Это так важно? А имя моё пока давайте не будем трогать.";
			link.l1.go = "Himenes_6";
		break;
		
		case "Himenes_6":
			dialog.text = "Видите ли, именем католической испанской церкви мы признаны еретиками и должны предстать перед справедливым судом священной инквизиции. Именно поэтому ваша национальность так важна для нас. Испанский капитан был бы обязан сдать нас местным властям. Снова такое мы бы не пережили! Ха-ха!";
			if (sti(pchar.BaseNation) == SPAIN) dialog.text = "Кха-ха-ха-ха-ха-х! Вот она, наша удача. Ну ладно, терять всё равно нам нечего. " + dialog.text;
			link.l1 = "Да уж. К счастью для вас, дела инквизиции меня не волнуют. И что же? Вы язычники?";
			link.l1.go = "Himenes_7";
		break;
		
		case "Himenes_7":
			dialog.text = "Нет, клянусь вам! Наша община пятьдесят лет занималась ремеслами и торговлей в славном Кадисе. Все шло успешно, мы даже приобрели корабль и лицензию на торговлю с колониями нашей Империи. Теперь я понимаю, что тогда мы перешли некую черту и были совершенно не готовы к нашим новым конкурентам... и к их методам.";
			link.l1 = "Вы с кем-то не поделили коммерцию в Европе и, как итог, всей общиной застряли на необитаемом острове на Карибах? А я-то думал, это у меня проблемы в жизни...";
			link.l1.go = "Himenes_8";
		break;
		
		case "Himenes_8":
			dialog.text = "К несчастью, всё так. Наша община была основана иудеями, принявшими новую веру, и получившие за это возможность вернуться домой в Испанию. Этой давней истории хватило для обвинения и официального разбирательства.";
			link.l1 = "И вы бежали...";
			link.l1.go = "Himenes_9";
		break;
		
		case "Himenes_9":
			dialog.text = "Да! Ха-ха-ха! На своём же корабле! Мы шли на Кюрасао строить новый дом и новое дело. Однако, мы недооценили настойчивость инквизиции и жестоко поплатились за это. Их курьер перехватил нас недалеко отсюда и передал капитану ордер с приказом вернуть нас домой...";
			link.l1 = "Вот это да!";
			link.l1.go = "Himenes_10";
		break;
		
		case "Himenes_10":
			dialog.text = "Дальше больше! Ха! Наш капитан не захотел ни тащиться с нами обратно через Атлантику, ни отпускать нас под свою ответственность в ближайшем порту. И, приняв по-настоящему соломоново решение, дал нам еды, высадил здесь и был таков.";
			link.l1 = "Трагическая история, ничего не скажешь. Подытожим: домой вам нельзя, в дружественных колониях вас найдут, а иностранные порты тоже вам не будут рады - в этом краю война не прекращается. Какие планы?";
			link.l1.go = "Himenes_11";
		break;
		
		case "Himenes_11":
			dialog.text = "Вы нарисовали настолько мрачную картину, сеньор, что я уже и не знаю. Можно подумать, для нас нет лучше места, чем этот остров.";
			link.l1 = "Я думаю, это не так. Есть остров и получше.";
			link.l1.go = "Himenes_12";
		break;
		
		case "Himenes_12":
			dialog.text = "В самом деле? Он испанский?";
			link.l1 = "Он мой. Волею судьбы, мне досталось в собственность бывшее пиратское логово на необитаемом острове. Теперь это моя база и я хочу расширить её, исследовать остров и, если выйдет, построить там факторию.";
			link.l1.go = "Himenes_13";
		break;
		
		case "Himenes_13":
			dialog.text = "Вы пират?";
			link.l1 = "Да.";
			link.l1.go = "Himenes_14_1";
			link.l2 = "Нет.";
			link.l2.go = "Himenes_14_2";
		break;
		
		case "Himenes_14_1":
			dialog.text = "Новый Свет! Воистину мы здесь. Дома про пиратов говорят, что вы сущие демоны и даже не люди. Едите детей, насилуете женщин и сдираете кожу с добрых католиков. Это правда?";
			link.l1 = "Зависит от дня недели. Давайте в другой раз это обсудим. Я ищу людей. Трудолюбивых и способных людей, готовых несколько лет прожить далеко от цивилизации. Вам такое было бы интересно?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_14_2":
			dialog.text = "Жаль, раз уж я уже преступник, хотелось бы увидеть хоть одного пирата.";
			link.l1 = "Вам ещё представится такая возможность. Давайте в другой раз это обсудим. Я ищу людей. Трудолюбивых и способных людей, готовых несколько лет прожить далеко от цивилизации. Вам такое было бы интересно?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_15":
			dialog.text = "У нас нет выхода. Но это и правда неплохой вариант. Мы примем его, если вы дадите нам жить и трудиться в мире. И обязуетесь однажды отправить нас домой! Дайте слово, сеньор, и назовите своё имя.";
			link.l1 = "Я - капитан "+GetFullName(pchar)+". Даю вам своё слово. Сколько вас?";
			link.l1.go = "Himenes_16";
		break;
		
		case "Himenes_16":
			dialog.text = "Ха-ха! Мы спасены! Так тому и быть! Нас несколько семей, около 30 человек. Все грамотны, обучены ремеслу и коммерции.";
			link.l1 = "Вот как судьба распорядилась... Прошу на борт!";
			link.l1.go = "Himenes_17";
		break;
		
		case "Himenes_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto1", "none", "", "", "", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			IslaMona_TerksHimenesOnBoard();
		break;
		
		case "Himenes_18":
			dialog.text = "Рад с вами познакомится, сеньор Родгар. Похоже, нам предстоит жить и трудиться вместе долгое время... Боже, как вы выдерживаете эту жару?";
			link.l1 = "";
			link.l1.go = "Himenes_19";
		break;
		
		case "Himenes_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_14";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_20":
			dialog.text = "Если позволите, я встряну: cеньор капитан, дайте нам день на заселение и беглый осмотр инвентаря и земли. Я уверен, у сеньора Родгара тоже есть немало идей о том, что делать с этим клочком суши. Думаю, мы сработаемся.";
			link.l1 = "А у вас выбора нет, Хименес. Ха-ха!";
			link.l1.go = "Himenes_21";
		break;
		
		case "Himenes_21":
			dialog.text = "Х-ха-ха-ха-ха-ха-ха!";
			link.l1 = "";
			link.l1.go = "Himenes_22";
		break;
		
		case "Himenes_22":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_23":
			dialog.text = "Да, капитан?";
			link.l1 = "Хименес, порадуешь меня? Как впечатления?";
			link.l1.go = "Himenes_24";
		break;
		
		case "Himenes_24":
			dialog.text = "Капитан, это кошмар. Ваш дом конечно неплох. Но в остальном... В этих лачугах жить невозможно, кругом заросли, а сеньор Родгар даже не знает что происходит на другом конце острова!! Невероятно! Ха-ха!";
			link.l1 = "Ты волнуешься сейчас или тебе и правда смешно?";
			link.l1.go = "Himenes_25";
		break;
		
		case "Himenes_25":
			dialog.text = "Конечно же смешно! Чем они тут занимались все эти годы? Первым делом нам необходимо достроить пару домов и подправить эти лачуги до приемлемого состояния. Людям надо достойно жить, чтобы усердно работать. Ещё я попрошу пиратов провести полную разведку острова, возможно это место богато не только скалами и песком. Когда всё будет сделано, я смогу точно сказать, что вам делать с этой землей.";
			link.l1 = "Звучит разумно! Что от меня требуется?";
			link.l1.go = "Himenes_26";
		break;
		
		case "Himenes_26":
			AddQuestRecordInfo("IslaMonaData", "1");
			dialog.text = "Материалы для домов, мебели и временных укрытий. Я всё подсчитал. Вот, возьмите список.";
			link.l1 = "Впечатляет...";
			link.l1.go = "Himenes_27";
		break;
		
		case "Himenes_27":
			dialog.text = "Разве? Сеньор, мы строили соборы! Вот там я вам скажу...";
			link.l1 = "Охотно верю! Только не построй мне тут случайно собор. Мне каждый раз придётся таскать сюда столько материалов?";
			link.l1.go = "Himenes_28";
		break;
		
		case "Himenes_28":
			dialog.text = "Нет, эти материалы обеспечат нас надолго, но кое-что всё равно придётся потом подвозить. Если хотите попробовать избежать подобных хлопот в будущем, привезите в два раза больше материалов.";
			link.l1 = "Ладно, убедил. Я посмотрю, что можно сделать. Я как-то ограничен в сроках?";
			link.l1.go = "Himenes_29";
		break;
		
		case "Himenes_29":
			dialog.text = "Нет, сеньор. Но я очень прошу вас не затягивать - эта та работа, без которой ничего не сдвинется. И жить людям тоже где-то надо. Материалы загружайте на склад и не забудьте сообщить мне как всё будет готово\nА, чуть не забыл же! Поговорите с сеньором Родгаром насчёт разведки острова.";
			link.l1 = "Договорились!";
			link.l1.go = "Himenes_30";
		break;
		
		case "Himenes_30":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			pchar.questTemp.IslaMona = "stalk";
			AddQuestRecord("IslaMona", "6");
		break;
		
		case "Himenes_31":
			dialog.text = "Да, капитан?";
			if (IslaMona_CheckBuild()) // привёз товары на стройку
			{
				link.l1 = "Привет, Хименес. Проверяй склад.";
				link.l1.go = "Himenes_32_1";
			}
			else // не привёз товары на стройку
			{
				link.l1 = "Привет, Хименес. Мои парни облазили весь остров. Что скажешь?";
				if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_32_2"; // привёз еду и лекарства
				else link.l1.go = "Himenes_32_3";
			}
		break;
		
		case "Himenes_32_1":
			IslaMona_RemoveBuild(); // сразу удаляем товары со склада
			dialog.text = "Уже, сеньор! Вы с блеском справились с этой ответственной задачей! Будете в Кадисе, приходите ко мне на работу кладовщиком!";
			link.l1 = "Уже бегу! Лучше расскажи мне, compadre, что ты теперь будешь делать?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_34_1"; // привёз еду и лекарства
			else link.l1.go = "Himenes_34_2";
		break;
		
		case "Himenes_32_2":
			dialog.text = "Сеньор капитан, дайте нам сначала разобраться с жильем и снабжением. Планы будем строить потом. Жду от вас на складе товары по моему списку.";
			link.l1 = "Ладно, понимаю. Сначала надо построить дома и привести это место в порядок. Товары скоро будут.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_32_3":
			dialog.text = "Сеньор капитан, дайте нам сначала разобраться с жильем и снабжением. Планы будем строить потом. Жду от вас на складе товары по моему списку. И ваш друг пират тоже ждёт провизию и лекарства.";
			link.l1 = "Ладно, понимаю. Сначала надо построить дома и привести это место в порядок. Товары скоро будут. И для моего друга пирата тоже.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_33":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_31";
		break;
		
		case "Himenes_34_1":
			dialog.text = "Дайте нам полгода, сеньор капитан, и вы не узнаете это место.";
			link.l1 = "Хочешь сказать, что через полгода тут не будет ни вас, ни посёлка, ни материалов? До встречи!";
			link.l1.go = "Himenes_37"; // все выполнил
		break;
		
		case "Himenes_34_2":
			dialog.text = "Мы приступим к работе, как только вы решите свои дела с этим разбойником. Он заказывал у вас провиант и лекарства, и я согласен с ним - это разумное требование.";
			link.l1 = "Я передам ему твои слова.";
			link.l1.go = "Himenes_35";
			AddQuestRecord("IslaMona", "11");
		break;
		
		case "Himenes_35":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_36";
		break;
		
		case "Himenes_36":
			dialog.text = "Ну, капитан? Сделали все, что просил ваш пират?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food"))
			{
				link.l1 = "Я решил все вопросы с Родгаром. Разведка острова началась, провиант и лекарства на складе. Теперь ваш ход.";
				link.l1.go = "Himenes_34_1";
			}
			else
			{
				link.l1 = "Не переживай, все решим. Я занимаюсь этим.";
				link.l1.go = "Himenes_35";
			}
		break;
		
		case "Himenes_37":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			DeleteAttribute(pchar, "questTemp.IslaMona.Food");
			pchar.questTemp.IslaMona = "build";
			AddQuestRecord("IslaMona", "12");
			SetFunctionTimerCondition("IslaMona_BuildDone", 0, 0, 180, false);
		break;
		
		case "Himenes_38":
			dialog.text = "Сеньор капитан! Ну как вам? К-ха-ха-ха?";
			link.l1 = "Стало сильно симпатичней. Докладывай, Хименес!";
			link.l1.go = "Himenes_39";
		break;
		
		case "Himenes_39":
			dialog.text = "Теперь тут таки можно жить! Мы прибрались здесь и перестроили все дома, кроме вашего, конечно. Не очень роскошно, но и не хуже чем в этом нашем Белизе.";
			link.l1 = "Белиз уже давно принадлежит Англии, Хименес.";
			link.l1.go = "Himenes_40";
		break;
		
		case "Himenes_40":
			dialog.text = "Не уверен, что дома об этом знают, капитан, ха-ха!";
			link.l1 = "Теперь вам есть где жить, а посёлок приобрёл человеческий вид. Что дальше?";
			link.l1.go = "Himenes_41";
		break;
		
		case "Himenes_41":
			dialog.text = "Осмотритесь, поговорите с сеньором Янссеном и возвращайтесь ко мне. Обсудим результаты разведки острова и наши планы.";
			link.l1 = "С каких это пор ты стал так величать Родгара? Вы же собачились постоянно?";
			link.l1.go = "Himenes_42";
		break;
		
		case "Himenes_42":
			dialog.text = "И не перестали. Но надо же как-то строить рабочие отношения.";
			link.l1 = "Спасибо, Родриго. Скоро вернусь.";
			link.l1.go = "Himenes_43";
		break;
		
		case "Himenes_43":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload6", "none", "", "", "", 10.0); // возможно будет иной локатор в новой локации
			pchar.questTemp.IslaMona = "village";
		break;
		
		case "Himenes_44":
			dialog.text = "Капитан. Сеньор Янссен.";
			link.l1 = "Давайте, расскажите мне о результатах разведки острова.";
			link.l1.go = "Himenes_45";
		break;
		
		case "Himenes_45":
			dialog.text = "Да, сеньор капитан. Некоторые места я осматривал лично вместе с нашим рудознатцем. Ну что тут сказать... Исла-Мона - островок бедный, крошечный и совсем неинтересный. Места для строительства очень мало, ландшафт сложный, крутой, плодородной земли почти нет. Три пляжа, одна затопленная пещера, глухие заросли, пара попугаев, стадо козлов и мы...";
			link.l1 = "Ты серьёзно? Ты хочешь сказать, что самый ценный актив на этом острове - стадо козлов?";
			link.l1.go = "Himenes_46";
		break;
		
		case "Himenes_46":
			dialog.text = "Кх-ха-ха-ха! Я бы попросил, сеньор! Ха-ха! Вы не дали мне закончить!";
			link.l1 = "";
			link.l1.go = "Himenes_47";
		break;
		
		case "Himenes_47":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_38";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_48":
			dialog.text = "";
			link.l1 = "Ладно, ладно, успокойся и продолжай. Ты же знаешь, я много вложил в это место.";
			link.l1.go = "Himenes_49";
		break;
		
		case "Himenes_49":
			dialog.text = "И не зря! В пещере достаточно пресной воды, почвы хватит, чтобы выращивать плодоносные деревья, а козлов можно разводить. С учётом рыбалки и усилий со стороны ваших товарищей, вопрос с едой будет закрыт очень быстро.";
			link.l1 = "То есть, больше продовольствия вам сюда не возить? Уже неплохо. Я надеялся, что это место сможет жить без моей постоянной заботы. Продолжим.";
			link.l1.go = "Himenes_50";
		break;
		
		case "Himenes_50":
			dialog.text = "Вы всё правильно говорите, сеньор. Но это не все новости! Во-первых, у сеньора Родгара возникла идея построить таверну. Я не знаю, что это вам даст, но этот ладрон что-то задумал.";
			link.l1 = "Нажраться он задумал, вот что. Пока негусто, Хименес.";
			link.l1.go = "Himenes_51";
		break;
		
		case "Himenes_51":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_40";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_52":
			dialog.text = "Во-вторых, бухта Губернатора оказалась значительно более глубокой, чем нам казалось изначально. Мы можем построить полноценную пристань.";
			link.l1 = "Не очень понимаю, что это мне даст, но уже лучше. Это ведь не всё, надеюсь?";
			link.l1.go = "Himenes_53";
		break;
		
		case "Himenes_53":
			dialog.text = "Мы обнаружили рощу бакаутовых деревьев. Идеальное место для фактории.";
			link.l1 = "Ты меня радуешь, Родриго! И впрямь, отличная новость!";
			link.l1.go = "Himenes_54";
		break;
		
		case "Himenes_54":
			dialog.text = "Пока это всё, сеньор. Не исключаю, что у нас появятся ещё мысли в будущем. Сами понимаете, лучшие идеи приходят во время работы! О чём вы хотели бы спросить?";
			link.l1 = "Расскажи мне о бакауте. Звучит многообещающе.";
			link.l1.go = "Himenes_55";
		break;
		
		case "Himenes_55":
			dialog.text = "По моим оценкам, небольшая фактория сможет добывать эту ценную породу дерева в течении нескольких лет. Запасы хоть и скромные, но ресурс-то стратегический. Мы можем расчистить площадку в центре острова и построить там дом со складом. Это для начала. Помимо строительных материалов, нам ещё понадобятся штук 15 кандалов и мушкет.";
			link.l1 = "А кандалы-то зачем?";
			link.l1.go = "Himenes_56";
		break;
		
		case "Himenes_56":
			dialog.text = "Это тяжёлый труд, сеньор. Даже, я бы сказал, рабский.";
			link.l1 = "Понимаю. Хе-хе...";
			link.l1.go = "Himenes_57_1";
			link.l2 = "Сдурел? Я не стану рабовладельцем!";
			link.l2.go = "Himenes_57_2";
		break;
		
		case "Himenes_57_1":
			dialog.text = "";
			link.l1 = "А зачем мушкет? И почему именно один?";
			link.l1.go = "Himenes_59";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Himenes_57_2":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_42";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Himenes_58":
			dialog.text = "Соглашусь с сеньором пиратом. Я не понимаю вас, капитан. Вся экономика этого региона держится на рабском труде и она останется таковой ещё долгие годы. Чем мы лучше?";
			link.l1 = "Я приму решение. А пока расскажи мне зачем вам мушкет? И почему именно один?";
			link.l1.go = "Himenes_59";
		break;
		
		case "Himenes_59":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_60":
			dialog.text = "Разумеется, фактория потребует содержание. С её постройкой этот остров получит экономику с основным торговым партнёром в вашем лице. Рабов мы прокормим сами, но охрану и производство вам придётся оплатить из своего кармана. Поселенцы возьмут сто дублонов и пять бутылок вина за каждую партию. По вопросам охраны договаривайтесь с сеньором Янссеном.";
			link.l1 = "";
			link.l1.go = "Himenes_61";
		break;
		
		case "Himenes_61":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_62":
			dialog.text = "Сорок мер каждый месяц. А золото - на будущее. Однажды вы нас заберёте отсюда, помните своё обещание? Любая работа должна быть оплачена, а вашими же дублонами мы будем платить охотникам и мастерам за работу в посёлке. Таким образом, у нас появится товарообмен, а с ним - и цивилизация!";
			link.l1 = "Вот это речь! Ладно! Пока что всё звучит достаточно убедительно...";
			link.l1.go = "Himenes_63";
		break;
		
		case "Himenes_63":
			dialog.text = "Что ещё вас интересует?";
			link.l1 = "Так что за история с таверной? Чего не театр?";
			link.l1.go = "Himenes_64";
		break;
		
		case "Himenes_64":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_65":
			dialog.text = "Капитан, я предупреждал его, что затея с домом вам не понравится. Но это единственный вариант. У вас самый большой дом в... кхм, городе, мы перестроим первый этаж под зал, поставим столы и кухню. В пещерах под домом будем хранить выпивку и еду. Есть у нас и кому готовить, и кому музыку играть. Второй этаж останется за вами и трогать мы его не будем. Все ваши вещи на первом этаже мы сами перенесем наверх.";
			link.l1 = "Допустим. Так что конкретно нам даст таверна?";
			link.l1.go = "Himenes_66";
		break;
		
		case "Himenes_66":
			dialog.text = "Мы получим какую-никакую культурную жизнь, а вы - возможность держать около трёх сотен человек резерва в самом центре Кариб.";
			link.l1 = "Интересно... Подумаю.";
			link.l1.go = "Himenes_67";
		break;
		
		case "Himenes_67":
			dialog.text = "Что ещё вас интересует?";
			link.l1 = "Так, а что с пристанью?";
			link.l1.go = "Himenes_68";
		break;
		
		case "Himenes_68":
			dialog.text = "Тут всё просто. Мы расчистим бухту Губернатора от рифов, поставим сигнальное освещение и построим пристань. Сеньор Янссен утверждает, что вы сможете укрыть в бухте уже три корабля, либо один корабль первого класса. Да и вам самим будет приятней сюда возвращаться, не таская ялик по пляжу каждый раз.";
			link.l1 = " Было бы неплохо.";
			link.l1.go = "Himenes_69";
		break;
		
		case "Himenes_69":
			dialog.text = "Что ещё вас интересует?";
			link.l1 = "Пока всё. Я вернусь как решу, что будем строить.";
			link.l1.go = "Himenes_70";
		break;
		
		case "Himenes_70":
			dialog.text = "Сеньор капитан, держите этот документ. Я взял на себя смелость записать все детали, дабы не повторять по десятку раз. Изучайте, привозите материалы и ставьте задачу.";
			link.l1 = "Спасибо, Родриго.";
			link.l1.go = "Himenes_71";
		break;
		
		case "Himenes_71":
			DialogExit();
			IslaMona_HouseDialogFin();
		break;
		
		case "Himenes_72": // нода Хименеса строителя и управляющего факторией
			if (CheckAttribute(pchar, "questTemp.IslaMona.RecordPart")) // после защиты Исла Моны - нужно ещё 10 рабов
			{
				dialog.text = "Сеньор капитан, для работы фактории нужны 10 рабов - я вам говорил, вы не забыли?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 10)
				{
					link.l1 = "Уже привёз. Принимай и запускай производство.";
					link.l1.go = "Himenes_plantation_12";
				}
				else
				{
					link.l1 = "С памятью у меня в всё в порядке. Скоро привезу.";
					link.l1.go = "Himenes_plantation_14";
				}
				break;
			}
			dialog.text = "Ну что скажете, сеньор капитан?";
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Harbour"))
			{
				link.l1 = "Хочу чистую бухту и безопасную пристань. Будет базой для моего флота.";
				link.l1.go = "Himenes_harbour";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Tavern"))
			{
				link.l2 = "Стройте уж таверну. Все оценят, а я ещё и резерв смогу тут держать.";
				link.l2.go = "Himenes_tavern";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Plantation"))
			{
				link.l3 = "Приступайте к сооружению фактории. Пора отбивать вложения.";
				link.l3.go = "Himenes_plantation";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Slave") && IslaMona_CheckSlave())
			{
				link.l4 = "Родриго, особо ценные специалисты и снаряжение доставлены на факторию. Можете начинать работу.";
				link.l4.go = "Himenes_plantation_7";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory.Part") && sti(pchar.questTemp.IslaMona.Factory.Part) > 0)
			{
				link.l4 = "Родриго, я пришёл за своим бакаутом.";
				link.l4.go = "Himenes_bacaut";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Factory") && !CheckAttribute(pchar, "questTemp.IslaMona.Church"))
			{
				link.l5 = "Родриго, неужто мы закончили наше великое строительство?";
				link.l5.go = "Himenes_church";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "start" && IslaMona_CheckChurch())
			{
				link.l5 = "Родриго, давай строить твою церковь.";
				link.l5.go = "Himenes_church_10";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "Wait_candles" && IslaMona_CheckCandles())
			{
				link.l5 = "Родриго, я привёз твоё церковное барахло.";
				link.l5.go = "Himenes_church_10_3";
			}
			link.l10 = "Пока ничего...";
			link.l10.go = "Himenes_73";
		break;
		
		case "Himenes_harbour":
			if (IslaMona_CheckHarbour())
			{
				dialog.text = "Материалы есть, всё готово. Строительство займёт 4 месяца.";
				link.l1 = "А вы не торопитесь, однако! Удачи, Родриго.";
				link.l1.go = "Himenes_harbour_1";
			}
			else
			{
				dialog.text = "Боюсь, на складе нет достаточного количества материалов. Пожалуйста, сверьтесь ещё раз с памяткой.";
				link.l1 = "Разберусь.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_tavern":
			if (IslaMona_CheckTavern())
			{
				dialog.text = "Материалы есть, всё готово. Строительство займёт 3 месяца.";
				link.l1 = "А вы не торопитесь, однако! Удачи, Родриго.";
				link.l1.go = "Himenes_tavern_1";
			}
			else
			{
				dialog.text = "Боюсь, на складе нет достаточного количества материалов. Пожалуйста, сверьтесь ещё раз с памяткой.";
				link.l1 = "Разберусь.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_plantation":
			if (IslaMona_CheckPlantation())
			{
				dialog.text = "Материалы есть, всё готово. Строительство займёт 6 месяцев.";
				link.l1 = "А вы не торопитесь, однако! Удачи, Родриго.";
				link.l1.go = "Himenes_plantation_1";
			}
			else
			{
				dialog.text = "Боюсь, на складе нет достаточного количества материалов. Пожалуйста, сверьтесь ещё раз с памяткой.";
				link.l1 = "Разберусь.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_73":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_harbour_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveHarbour();
			pchar.questTemp.IslaMona.Harbour = "true";
			SetFunctionTimerCondition("IslaMona_BuildHarbour", 0, 0, 120, false);
		break;
		
		case "Himenes_harbour_2":
			dialog.text = "Приветствую, капитан. Как вам ваш новый порт?";
			if (stf(environment.time) > 22.0 || stf(environment.time) < 5.0)
			{
				link.l1 = "Темно же, Родриго! Мы чуть твой хвалёный причал не протаранили! Молодец, хоть свет додумался зажечь!";
				link.l1.go = "Himenes_harbour_3";
			}
			else
			{
				link.l1 = "А неплохо, Родриго! Казалось бы, мелочь, а прям приятно по этим деревяшкам на берег сходить. Да и бухта стала полегче в плане навигации. Я так понимаю, теперь я смогу размещать больше кораблей в этой бухточке?";
				link.l1.go = "Himenes_harbour_4";
			}
		break;
		
		case "Himenes_harbour_3":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_51";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_harbour_4":
			sld = characterFromId("Islamona_carpenter");
			sld.portman.info = "true"; // если вдруг до сих пор не говорил об условиях стоянки
			pchar.questTemp.IslaMona.Harbour = "done"; // флаг - пристань построена и сдана
			dialog.text = "Да, капитан. Надо сказать, даже гордость какая-то берёт. Обращайтесь, как надумаете продолжить нашу большую стройку.";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "complete") // если пересеклось со сдачей фактории
			{
				link.l1 = "Кстати, о стройке. Моя фактория уже по срокам тоже должна быть готова. Так, Родриго?";
				link.l1.go = "Himenes_plantation_2";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Himenes_harbour_5";
			}
		break;
		
		case "Himenes_harbour_5":
			DialogExit();
			IslaMona_HarbourClear();
		break;
		
		case "Himenes_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveTavern();
			pchar.questTemp.IslaMona.Tavern = "true";
			SetFunctionTimerCondition("IslaMona_BuildTavern", 0, 0, 90, false);
		break;
		
		case "Himenes_tavern_2":
			dialog.text = "И-ик! Кэп! А мы тут отмечаем!";
			link.l1 = "Родгар. Родриго. А, чёрт!";
			link.l1.go = "Himenes_tavern_3";
		break;
		
		case "Himenes_tavern_3":
			dialog.text = "Что такое, и-к-капитан? Вам не понравился цвет стен, да?";
			link.l1 = "Только сейчас понял, что вы тёзки! Ха-ха-ха! Испанец и пират, причём тёзки, отстроили таверну на пустом острове и напиваются как будто завтра индейские боги всех сожрут! Ха-ха! Я с вами!";
			link.l1.go = "Himenes_tavern_4";
		break;
		
		case "Himenes_tavern_4":
			dialog.text = "Ха-ха! И правда! Вот уж точно - Новый Свет! Salud!";
			link.l1 = "Tchin-tchin!";
			link.l1.go = "Himenes_tavern_5";
		break;
		
		case "Himenes_tavern_5":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_ReloadTavern();
		break;
		
		case "Himenes_plantation_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemovePlantation();
			pchar.questTemp.IslaMona.Plantation = "true";
			SetFunctionTimerCondition("IslaMona_BuildPlantation", 0, 0, 180, false);
		break;
		
		case "Himenes_plantation_2":
			dialog.text = "Все готово. Пройдёмся? Покажу вам вашу факторию.";
			link.l1 = "Веди.";
			link.l1.go = "Himenes_plantation_3";
		break;
		
		case "Himenes_plantation_3":
			DialogExit();
			pchar.questTemp.IslaMona.Plantation.Harbour = "true"; // наложилась сдача пристани и фактории
			IslaMona_PlantationGo();
		break;
		
		case "Himenes_plantation_4":
			dialog.text = "Капитан, почти всё готово для начала промысла. Жильё для работников, склад для сырья, место для обработки - достойная фактория получилась. Мы уже пометили наиболее перспективные для сруба стволы в джунглях. Привезите пятнадцать рабочих и оговоренный инвентарь - 15 кандалов и мушкет, и мы начнём работу.";
			link.l1 = "Мы? Ты хотел сказать рабы?";
			link.l1.go = "Himenes_plantation_5";
		break;
		
		case "Himenes_plantation_5":
			dialog.text = "Ха! Рабо... рабы будут рубить, поселенцы обрабатывать, а пираты охранять. Всем найдётся работа - серьёзное предприятие вы затеяли, капитан.";
			link.l1 = "Прям земля обетованная, да. Ждите товар, а мне пора выйти на охоту.";
			link.l1.go = "Himenes_plantation_6";
		break;
		
		case "Himenes_plantation_6":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Plantation.Slave = "true"; // привезти рабов, кандалы и мушкет для запуска фактории
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "IslaMona_factoria_residence", "sit", "sit1", "IslaMona_PlantationHouse", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5);
			pchar.questTemp.IslaMona.Plantation = "done"; // флаг - фактория построена и сдана
		break;
		
		case "Himenes_plantation_7":
			dialog.text = "Печальная судьба... Ведь они никогда не покинут это место.";
			link.l1 = "Родгар... тьфу, Родриго! Во-первых, может и покинут. А во-вторых, встретили вы бы кого другого на Терксе, ваша участь была бы не лучше.";
			link.l1.go = "Himenes_plantation_8";
		break;
		
		case "Himenes_plantation_8":
			dialog.text = "Я прекрасно знаю это, капитан. И не забываю об этом. Давайте лучше я вам расскажу о работе этой фактории\nНачиная со следующего месяца, каждое пятнадцатое число мы будем сдавать сорок брёвен обработанного бакаута. Конечно же, вам вовсе не обязательно приходить за ним каждый месяц - все партии будут складироваться и ждать вас прямо здесь, на фактории.";
			link.l1 = "То есть, я смогу забрать несколько партий сразу?";
			link.l1.go = "Himenes_plantation_9";
		break;
		
		case "Himenes_plantation_9":
			dialog.text = "В разумных пределах конечно же - не пропадайте слишком надолго. Люди не будут трудиться годами без оплаты, даже не зная жив ли ещё их единственный заказчик или нет. Я думаю партий шесть мы точно сдадим перед тем как приостановить работу.";
			link.l1 = "Товар надо забирать весь и сразу? Что по цене, напомнишь?";
			link.l1.go = "Himenes_plantation_10";
		break;
		
		case "Himenes_plantation_10":
			dialog.text = "Да, сразу. Стоимость типового бревна бакаута у нас - десять дублонов. Сверх того, за каждую партию вам придётся отдать пять бутылок хорошего рома и столько же бутылок вина. Родгар утверждает, что таких цен вы не найдёте нигде в мире.";
			link.l1 = "Пожалуй, что так! Спасибо, Родриго. Приступайте к работе!";
			link.l1.go = "Himenes_plantation_11";
		break;
		
		case "Himenes_plantation_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Slave");
			AddQuestRecordInfo("Unique_Goods", "5");
			IslaMona_RemoveSlave();
		break;
		
		case "Himenes_plantation_12":
			dialog.text = "Отлично! Теперь мы снова начнём работу!";
			link.l1 = "Вот и хорошо.";
			link.l1.go = "Himenes_plantation_13";
		break;
		
		case "Himenes_plantation_13":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_FactoryReActivar(); // запустить факторию
		break;
		
		case "Himenes_plantation_14":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_bacaut":
			dialog.text = "Конечно, капитан, забирайте. У нас готово следующее число партий: "+sti(pchar.questTemp.IslaMona.Factory.Part)+", это "+sti(pchar.questTemp.IslaMona.Factory.Goods)+" брёвен. Следовательно, с вас "+sti(pchar.questTemp.IslaMona.Factory.Dublon)+" дублонов, "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" бутылок рома и "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" бутылок вина. У вас всё это есть?";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Factory.Dublon) && PCharItemsTotal("potionrum") >= sti(pchar.questTemp.IslaMona.Factory.Bottle) && PCharItemsTotal("potionwine") >= sti(pchar.questTemp.IslaMona.Factory.Bottle))
			{
				link.l1 = "Конечно. Получи заработанное.";
				link.l1.go = "Himenes_bacaut_1";
			}
			else
			{
				link.l1 = "Похоже, есть не всё. Сейчас принесу.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_1":
			if (IslaMona_CheckBacautSpace())
			{
				dialog.text = "Отлично. Бакаут с фактории мы перевезём на ваш склад, оттуда его заберёте, когда захотите.";
				link.l1 = "Вот и славно. Готовьте следующую партию.";
				link.l1.go = "Himenes_bacaut_2";
			}
			else
			{
				dialog.text = "Один момент, капитан! Ваш склад переполнен - мы не сможем туда загрузить весь добытый бакаут. Освободите часть склада - и возвращайтесь ко мне.";
				link.l1 = "Хорошо, сделаем.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_2":
			dialog.text = "Конечно, капитан!";
			link.l1 = "...";
			link.l1.go = "Himenes_73";
			IslaMona_FactoryTrade();
		break;
		
		case "Himenes_church":
			dialog.text = "Ха! Капитан, я боюсь, строить что-то ещё будет ненужной блажью и расточительством. Разве что...";
			link.l1 = "Разве что?";
			link.l1.go = "Himenes_church_1";
		break;
		
		case "Himenes_church_1":
			dialog.text = "Капитан, неловко у вас о таком просить... Вы и так вложили в это место огромную сумму!";
			link.l1 = "Бордель?";
			link.l1.go = "Himenes_church_2_1";
			link.l2 = "Церковь?";
			link.l2.go = "Himenes_church_2_2";
		break;
		
		case "Himenes_church_2_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Клянусь святым Сантьяго, а было бы неплохо! Вот только в первую же ночь его бы наши женщины и сожгли. Вместе с нами. Нет, капитан, я про церковь\nДа, у нас есть достойное жильё и оплата, море и развлечение, семьи и друзья. А всё же чего-то не хватает, понимаете?";
			link.l1 = "Могу себе представить.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_2_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Defence", 500);
			dialog.text = "Видите меня насквозь, капитан. Да, у нас есть достойное жильё и оплата, море и развлечение, семьи и друзья. А всё же чего-то не хватает, понимаете?";
			link.l1 = "Могу себе представить.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_3":
			dialog.text = "Ну вот. Дом Божий без вашего участия мы не сможем построить. Такое место должно быть особенным, оно должно быть не от сего мира. А значится, и стоить должно дорого. Нам потребуются свечи, золотые слитки, янтарь и, конечно же,  материалы для строительства, причём не из дешёвых. Никакой выгоды вам это не сулит, поэтому просить и не смею.";
			link.l1 = "Получается, вам ещё священника сюда нужно привезти?";
			link.l1.go = "Himenes_church_4";
		break;
		
		case "Himenes_church_4":
			dialog.text = "Нет.";
			link.l1 = "Среди вас уже есть священник?";
			link.l1.go = "Himenes_church_5";
		break;
		
		case "Himenes_church_5":
			dialog.text = "Нет, капитан. И я думаю, вы уже всё поняли.";
			link.l1 = "То есть, у святых отцов из инквизиции был повод преследовать вас? Вы еретики?";
			link.l1.go = "Himenes_church_6";
		break;
		
		case "Himenes_church_6":
			dialog.text = "По каноническим законам, мы - самые страшные из еретиков. Мы не верим, что для общения с Богом обязательно требуется посредник из этого мира.";
			link.l1 = "Из этого мира?";
			link.l1.go = "Himenes_church_7";
		break;
		
		case "Himenes_church_7":
			dialog.text = "Капитан, мы не сатанисты, а наша община - не секта. Мы христиане, как и вы, однако смотрим на вещи очень широким взглядом. Слишком широким, по мнению некоторых очень образованных и достойных людей. Если однажды вы найдёте в своём сердце место для открытости и понимания, то я расскажу вам больше. А пока - просто возьмите этот список. На всякий случай.";
			link.l1 = "Тебе стоило рассказать об этом раньше, Родриго. Я не хочу в один прекрасный день вернуться и увидеть на своей земле ведьминский шабаш или рождение новой веры! Пока жди - я приму решение.";
			link.l1.go = "Himenes_church_8_1";
			link.l2 = "Внушительный список. Начинаю понимать зачем святым отцам столько денег! Я подумаю над твоим предложением, Родриго, и приму решение.";
			link.l2.go = "Himenes_church_8_2";
		break;
		
		case "Himenes_church_8_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "";
			link.l1 = "Если оно будет положительным, я привезу все товары из твоего списка на склад, а драгоценности выложу тебе на стол.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_8_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			dialog.text = "";
			link.l1 = "Если оно будет положительным, я привезу все товары из твоего списка на склад, а драгоценности выложу тебе на стол.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_9":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "start";
			AddQuestRecord("IslaMona", "14");
			AddQuestRecordInfo("IslaMonaData", "3");
		break;
		
		case "Himenes_church_10":
			dialog.text = "От лица всей нашей общины я благодарю вас, капитан. Вы не пожалеете об этом, клянусь!";
			link.l1 = "Пожалею только если вы построите что-нибудь совсем убогое. Так с чего начнём?";
			link.l1.go = "Himenes_church_10_1";
		break;
		
		case "Himenes_church_10_1":
			dialog.text = "Капитан, все материалы в наличии! Мы начнём строительство, когда вы привезёте ещё и предметы роскоши указанные в списке. Они пойдут на украшения и изготовление ритуальных инструментов. Ещё раз, огромное спасибо вам, капитан! Muchas gracias!";
			link.l1 = "Не за что!";
			link.l1.go = "Himenes_church_10_2";
		break;
		
		case "Himenes_church_10_2":
			DialogExit();
			IslaMona_RemoveChurch();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "Wait_candles";
			pchar.questTemp.IslamonaChurch.GoldNugget = 50;
			pchar.questTemp.IslamonaChurch.Candle = 100;
			pchar.questTemp.IslamonaChurch.Amber = 30;
			pchar.questTemp.IslamonaChurch.BlueAmber = 1;
		break;
		
		case "Himenes_church_10_3":
			IslaMona_RemoveCandles();
			string sAdd = "";
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Candle)+ " свечей,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Amber)+ " янтаря,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
			{
				sAdd += " "+ sti(pchar.questTemp.IslamonaChurch.GoldNugget) + " золотых слитков,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
			{
				sAdd += " и голубой янтарь"
			}
			if(sAdd == "")
			{
				dialog.text = "Muchisimas gracias, капитан! Всё готово, мы начинаем строительство. Приезжайте через пару месяцев на первую службу. Да, и ещё, виноград поспел! Сделаем домашнее вино, устроим праздник и пир в вашу честь!";
				link.l1 = "Думаю, праздник все мы заслужили. Вернусь через два месяца.";
				link.l1.go = "Himenes_church_12";
			}
			else
			{
				dialog.text = "Капитан, осталось ещё "+sAdd+".";
				link.l1 = "Жди, остальное привезу. Если бы не свечи, подумал бы, что ты клад собрался зарыть.";
				link.l1.go = "Himenes_church_11";
			}
		break;
		
		case "Himenes_church_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_church_12":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "build";
			AddQuestRecord("IslaMona", "15");
			//IslaMona_RemoveChurch();
			SetFunctionTimerCondition("IslaMona_ChurchComplete", 0, 0, 60, false);
		break;
		
		case "Himenes_church_13":
			dialog.text = "Ха-ха-ха-ха-ха-ха-ха-ха-ха-ха-ха!";
			link.l1 = "А я уж думал, ты избавился от этой идиотской привычки.";
			link.l1.go = "Himenes_church_14";
		break;
		
		case "Himenes_church_14":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "что нам не придётся сидеть тут неделями, ожидая развязки событий.";
			else sTemp = "что не всем поголовно придётся участвовать в сражении.";
			dialog.text = "Ха-ха-ха-кхх... ха. Я тоже... так думал, капитан! Родгар прав, ваше присутствие уже как минимум означает, "+sTemp+"";
			link.l1 = "Я уже знаю что случилось. Потери есть?";
			if (GetCharacterIndex("Mirabella") != -1) link.l1.go = "Himenes_church_15";
			else link.l1.go = "Himenes_church_16";
		break;
		
		case "Himenes_church_15":
			DialogExit();
			sld = characterFromId("Mirabella"); 
			sld.dialog.currentnode = "mirabelle_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_16":
			dialog.text = "Не переживай так, Родгар. То не твоя вина, слишком уж быстро фузилёры явились. Держать их у себя в тылу мы в любом случае бы не смогли, а под нож всех пустить времени не было.";
			link.l1 = "А что с испанцами?";
			link.l1.go = "Himenes_church_17";
		break;
		
		case "Himenes_church_17":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) // решил проблему самостоятельно
			{
				dialog.text = "Добрались до нас всего трое, а выжил только один. Сам капитан! Судя по всему, очень серьёзный военный моряк. Но помочь он нам пока ничем не может - в отключке ему лежать ещё пару дней минимум. Кстати, капитан, мы слышали выстрелы и судя по вашему виду, вы тоже.";
				link.l1 = "Можно и так сказать. Незваные гости явно не ждали такого нежданного визита и были скинуты обратно в море.";
				link.l1.go = "Himenes_church_20";
			}
			else
			{
				dialog.text = "Добрались до нас всего трое, а выжил только один. Сам капитан! Судя по всему, очень серьёзный военный моряк. Но помочь он нам пока ничем не может - в отключке ему лежать ещё пару дней минимум.";
				if (i >= 50) 
				{
					link.l1 = "В прошлый раз я оставил тут немало своих людей на постой, так что вас должно быть намного больше, чем фузилёров. Почему вы сразу их всех не скинули обратно в море?";
					link.l1.go = "Himenes_church_17_1";
				}
				else 
				{
					link.l1 = "Ладно, давайте решать эту проблему. План такой: я вытяну их на открытый штурм, причём прямо сейчас. Не вижу смысла затягивать. Готовьте картечь и мушкеты, пираты на воротах, остальные по домам - и сидите там.";
					link.l1.go = "Himenes_church_18";
				}
			}
		break;
		
		case "Himenes_church_17_1":
			dialog.text = "Кэп, они все профессиональные солдаты, причём с командиром. А у нас даже оружия-то нормального нет. Да, конечно, массой бы их задавили, но потеряли бы минимум в два раза больше людей, а у нас каждый человек ценен и нужен.";
			link.l1 = "Ладно, давайте решать эту проблему. План такой: я вытяну их на открытый штурм, причём прямо сейчас. Не вижу смысла затягивать. Готовьте картечь и мушкеты, пираты на воротах, остальные по домам - и сидите там.";
			link.l1.go = "Himenes_church_18";
		break;
		
		case "Himenes_church_18":
			dialog.text = "Капитан, мы готовы драться!";
			link.l1 = "Я знаю, Родриго. Но ты не дал мне закончить: если хоть один противник всё же прорвётся за ворота, то вы должны всем скопом набросится на него со всех сторон. И в бою свою роль сыграете и шансов получить пулю или осколок все меньше. Ещё вопросы есть?";
			link.l1.go = "Himenes_church_19";
		break;
		
		case "Himenes_church_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_68";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_20":
			dialog.text = "Чистая работа! Неприятно, конечно, что именно вашим соотечественникам выпала такая незавидная участь. Но я благодарен, что вы в очередной раз приняли нашу сторону.";
			link.l1 = "Это было нелегко, Родриго. Нормальные люди назовут это предательством и будут правы.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Это моя земля, Родриго. Защищать её надо всегда и неважно от кого.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20a":
			dialog.text = "Да, не думал старина Родриго, когда уезжал из Кадиса, что в Новом Свете ждут его такие приключения.";
			link.l1 = "Мне-то не рассказывай. До сих пор накатывают иногда точно такие же мысли.";
			link.l1.go = "Himenes_church_20b";
		break;
		
		case "Himenes_church_20b":
			dialog.text = "Неприятно, конечно, что именно вашим соотечественникам выпала такая незавидная участь. Но я благодарен, что вы в очередной раз приняли нашу сторону.";
			link.l1 = "Это было нелегко, Родриго. Нормальные люди назовут это предательством и будут правы.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Это моя земля, Родриго. Защищать её надо всегда и неважно от кого.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Понимаю, кэп. Позвольте тогда ввести вас в краткий курс дела о состоянии нашего поселения. У нас тут кое-что случилось за время вашего отсутствия.";
			link.l1 = "Да ладно? Погоди... Кэп?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_20_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			dialog.text = "Понимаю, кэп. Позвольте тогда ввести вас в краткий курс дела о состоянии нашего поселения. У нас тут кое-что случилось за время вашего отсутствия.";
			link.l1 = "Да ладно? Погоди... Кэп?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_21":
			dialog.text = "Не хотел обидеть. Просто Родгар так вкусно произносит это слово, что мне тоже захотелось попробовать. Очень... По-пиратски.";
			link.l1 = "Без проблем, просто удивился. Так что у вас случилось?";
			link.l1.go = "Himenes_church_22";
		break;
		
		case "Himenes_church_22":
			dialog.text = "Во-первых, церковь мы построили. Будет минутка, заходите. Там есть на что посмотреть. Вы сделали большое дело, кэп. Пусть вам может так и не казаться, но для нас иметь возможность общаться с Богом - очень-очень важно. С этого дня Исла Мону мы зовем не иначе как наш hogar.";
			link.l1 = "Hogar, dulce hogar? Обязательно посмотрю. Столько свечей зря что ли таскал?";
			link.l1.go = "Himenes_church_23";
		break;
		
		case "Himenes_church_23":
			dialog.text = "Не зря! Во-вторых, фактория разорена - мы потеряли всю рабочую силу. Вам придётся привезти новую партию рабов. К счастью, после переоценки эффективности работ мы пришли к выводу, что десяти рабов хватит с избытком. Так что вам меньше мороки.";
			link.l1 = "Допустим. Что-то ещё?";
			link.l1.go = "Himenes_church_24";
		break;
		
		case "Himenes_church_24":
			dialog.text = "Всё готово к празднику. Ну, почти: надо тут прибраться, похоронить тела этих несчастных... Так что приходите завтра в церковь и мы начнём.";
			link.l1 = "В церковь? Странное место, чтобы начать попойку. Ты что же, Родг... Родриго, предложение мне сделать собрался, а? Ха!";
			link.l1.go = "Himenes_church_25";
		break;
		
		case "Himenes_church_25":
			dialog.text = "Ха-ха! Нет, кэп, хотя кое-кто из наших девиц точно был бы не прочь. Мы не возражаем, если что.";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				link.l1 = "";
				link.l1.go = "Himenes_church_25_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")))
				{
					link.l1 = "";
					link.l1.go = "Himenes_church_25_2";
				}
				else
				{
					link.l1 = "Договорились, завтра прибудем в церковь. Помолится, разумеется.";
					if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common") || CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) link.l1.go = "Himenes_church_28";
					else link.l1.go = "Himenes_church_26";
				}
			}
		break;
		
		case "Himenes_church_25_1":
			DialogExit();
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_25_2":
			DialogExit();
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_26":
			dialog.text = "И ещё одно, кэп. Перед праздником сначала сходите и решите вопрос с пленником. Решение должно быть принято, и я понимаю, что оно в любом случае будет неприятным.";
			link.l1 = "Хорошо. Прямо сейчас и пойду.";
			link.l1.go = "Himenes_church_27";
		break;
		
		case "Himenes_church_27":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefFraPrisoner"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_28":
			DialogExit();
			WaitDate("", 0, 0, 0, 3, 5); //крутим время
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			IslaMona_DefBattleLightClear();
			DoQuestReloadToLocation("IslaMona_town", "quest", "detector1", "");
		break;
		
		case "Himenes_church_29":
			dialog.text = "Все в сборе! Сеньор, мы не знаем, что вы изначально хотели от этого места и каким вы видите его для себя сейчас. Для нас же, сначала это было вынужденным убежищем, а сейчас стало настоящим домом. Тут живут ваши матросы, пираты и беглые испанские еретики. В любом другом месте на земле мы бы уже перегрызли друг другу глотки. Но здесь мы дружим, трудимся и радуемся жизни\nНи для кого из нас Исла Мона не является финальной точкой на карте этого мира, но возможно именно на ней мы проведём самые счастливые и плодотворные свои годы. И это ваша заслуга, ваша земля и ваш народ. Muchas gracias, "+pchar.name+"!";
			link.l1 = "";
			link.l1.go = "Himenes_church_30";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_30":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_86";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "Himenes_church_31":
			dialog.text = "Ладно-ладно. Кэп, мы собрали вам подарки - множество полезных и просто приятных вещей. Что-то привезли с собой, а что-то сделали сами. Примите этот подарок с чистым сердцем, а остальное мы подарим вам своим трудолюбием.";
			link.l1 = "Спасибо... не ожидал. Пока что в моей одиссее так мало было светлых моментов и простой человечности... Это многое для меня значит, поверьте.";
			link.l1.go = "Himenes_church_32";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_32":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "GunEchin", 10);
			TakeNItems(pchar, "slave_01", 10);
			TakeNItems(pchar, "grenade", 10);
			TakeNItems(pchar, "obereg_7", 1);
			TakeNItems(pchar, "purse3", 1);
			TakeNItems(pchar, "jewelry47", 1);
			TakeNItems(pchar, "jewelry52", 1);
			TakeNItems(pchar, "berserker_potion", 1);
			TakeNItems(pchar, "potion5", 10);
			TakeNItems(pchar, "cannabis7", 1);
			dialog.text = "А теперь - служба!";
			link.l1 = "Ну нет, а теперь - в кабак! Родгар, пошли!";
			link.l1.go = "Himenes_church_33_1";
			link.l2 = "Да, давайте прочувствуем этот дивный момент подольше.";
			link.l2.go = "Himenes_church_33_2";
		break;
		
		case "Himenes_church_33_1":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_33_2":
			DialogExit();
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_terrain");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("IslaMona_ChurchTavernExit", 45.0);
		break;
		
		case "Himenes_74":
			dialog.text = "Ха-ха! И-ик!";
			link.l1 = "Кстати, я смотрю, ты почти перестал дико ржать по поводу и без. Свежий воздух Кариб?";
			link.l1.go = "Himenes_75";
		break;
		
		case "Himenes_75":
			dialog.text = "Скорее Родгарово тлетворное влияние. Глядя на него, я научился mandar todo al carajo.";
			link.l1 = "";
			link.l1.go = "Himenes_76";
		break;
		
		case "Himenes_76":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_90";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_77":
			dialog.text = "Знаю немало уважаемых людей оттуда.";
			link.l1 = "";
			link.l1.go = "Himenes_78";
		break;
		
		case "Himenes_78":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_93";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_79":
			dialog.text = "Не-а, я лучше продолжу пить ром и пучить на вас глаза.";
			link.l1 = "";
			link.l1.go = "Himenes_80";
		break;
		
		case "Himenes_80":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_96";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_81":
			dialog.text = "Кэп! И-ик!";
			link.l1 = "И тебе привет, Родриго. Нескучно провёл вечер, я смотрю?";
			link.l1.go = "Himenes_82";
		break;
		
		case "Himenes_82":
			dialog.text = "Лучше... не спрашивайте. Месяц... пить не буду. Ох. У меня новости! Капитан очу... очухался.";
			link.l1 = "Тот единственный выживший испанец?";
			link.l1.go = "Himenes_83";
		break;
		
		case "Himenes_83":
			dialog.text = "И-ик! А-ать! Ага, поместили его на факторию в дом под охрану.";
			link.l1 = "Угу. Пойду к нему. Смотри не перетрудись.";
			link.l1.go = "Himenes_84";
		break;
		
		case "Himenes_84":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10); /// ОН ИДЕТ НА ВЫХОД, ПОСТАВИТЬ ПРАВИЛЬНЫЙ ЛОКАТОР
			IslaMona_ChurchSetHispanos();
		break;
		
		case "Himenes_85":
			dialog.text = "Искупался и всё как рукой! Будем жить и трудиться. Я постараюсь сделать так, чтобы фактория работала как можно дольше. Ну и заниматься починкой, мелким там строительством. Может с моей даже на детей решимся.";
			link.l1 = "Рад за всех вас! Это было очень нервное, дорогостоящее... и дивное приключение, и я рад тому, что у нас с вами получилось. Всем удачи, а нам, уходящим в море, удачи вдвойне!";
			link.l1.go = "Himenes_86";
		break;
		
		case "Himenes_86":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_Final", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// солдат в бухте
		case "Capral":
			dialog.text = "Стоять! Капрал "+GetFullName(npchar)+". Вы совершили высадку в зоне боевых действий! Немедленно назовитесь и обозначьте цель своего пребывания здесь!";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Капрал, отставить! "+GetFullName(pchar)+", капитан военно-морского флота Франции. Приказываю сопроводить меня к вашему старшему офицеру. Выполнять!";
				link.l1.go = "Capral_1";
			}
			else
			{
				link.l1 = ""+GetFullName(pchar)+", капитан корабля с именем '"+pchar.ship.name+"'. Прибыл на этот остров совершенно случайно - для возможного кренгования и набора пресной воды.";
				link.l1.go = "Capral_3";
			}
		break;
		
		case "Capral_1":
			if(IsUniformEquip())
			{
				dialog.text = "Слушаюсь, господин капитан! Прошу следовать за мной. Только умоляю вас, будьте осторожнее! Этот остров кишит бандитами.";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Прошу прощения, господин капитан. Вы не в форме, и посему я обязан проверить ваш офицерский патент.";
				link.l1 = "Смотри. Убедился? А теперь - бегом выполнять приказ, капрал!";
			}
			link.l1.go = "Capral_2";
		break;
		
		case "Capral_2":
			DialogExit();
			AddQuestRecord("IslaMona", "16");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 20.0);
		break;
		
		case "Capral_3":
			dialog.text = "Вам придётся пройти со мной, капитан. С вами будет говорить наш старший офицер. С этого момента ваш корабль считается временно реквизированным для нужд военного флота Франции. Немедленно уведомите об этом текущую вахту и следуйте за мной.";
			link.l1 = "Реквизировать корабль Чарли Принца? Я так не думаю!";
			link.l1.go = "Capral_5";
			link.l2 = "Похоже, выбора у меня нет. Сделаю всё как вы говорите.";
			link.l2.go = "Capral_4";
		break;
		
		case "Capral_4":
			DialogExit();
			AddQuestRecord("IslaMona", "18");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 5.0);
		break;
		
		case "Capral_5":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_DefKillCapral", 1.0);
		break;
		
		case "Capral_6":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Господин капитан, тропа к вражескому лагерю находится справа от нас. Я вас провожу.";
				link.l1 = "Отставить, капрал. Лучше, чтобы я шёл один.";
			}
			else
			{
				dialog.text = "Капитан, тропа к вражескому лагерю находится справа от нас. Не потеряетесь.";
				link.l1 = "Спасибо за заботу.";
			}
			link.l1.go = "Capral_7";
		break;
		
		case "Capral_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			IslaMona_DefGotoMarch();
			pchar.quest.islamona_def_killslaves.win_condition.l1 = "location";
			pchar.quest.islamona_def_killslaves.win_condition.l1.location = "IslaMona_town";
			pchar.quest.islamona_def_killslaves.function = "IslaMona_DefKillSlaves";
		break;
		
		case "FraOfficer":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Капитан "+GetFullName(pchar)+"! Слава Богу! Позвольте представится, - лейтенант "+GetFullName(npchar)+". Большой ваш поклонник! Не знаю, что вы делаете на этом убогом клочке суши, но вы как нельзя кстати!\nДолжен сказать, капитан, вы стали очень популярны в нашей офицерской среде. Хоть многих и раздражает ваш... 'особенный' стиль службы, все согласны с тем, что ваш патент делает наш флот сильнее. Сейчас мы оказались совершенно в патовой ситуации, так что помощь такого человека как вы будет сложно переоценить!";
				link.l1 = "Чем могу? И что здесь происходит?";
				link.l1.go = "FraOfficer_1";
			}
			else
			{
				dialog.text = "Капитан "+GetFullName(pchar)+". Ваше имя несколько раз упоминалось во флотских сводках. И всегда в очень сомнительном свете. Однако сейчас у вас есть шанс прервать эту мало почетную тенденцию и послужить родной стране.";
				link.l1 = "Чем могу? И что здесь происходит?";
				link.l1.go = "FraOfficer_8";
			}
		break;
		
		case "FraOfficer_1":
			dialog.text = "Шли на 'Воинственном', обычное задание - охота за особо наглыми испанскими рейдерами. Дело, в общем-то, простейшее: шпион даёт район и данные по цели, а ты уже из-под горизонта ловишь её с подветренной стороны. Рассказывать особо нечего и закончилось всё очень погано: испанцы нашли нас первыми и атаковали, даром что сами были на корвете. Были бы на чём посерьёзнее, не пошли бы на дно вместе с нами... а так хоть успели разнести им весь корпус. Спаслось только моё отделение. У кастильцев, правда, тоже кто-то выжил. Но то ненадолго, ха-ха!";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "Фрегат 'Воинственный'? Капитан Шоке погиб?";
				link.l1.go = "FraOfficer_1_1";
			}
			else
			{
				link.l1 = "";
				link.l1.go = "FraOfficer_2";
			}
		break;
		
		case "FraOfficer_1_1":
			dialog.text = "Неудивительно, что вы спросили о нём, капитан. Я слышал про ваше участие в перехвате 'Алькантары'. Большое дело, уже тогда вы заложили основу для своего патента! Командор Шоке не погиб, совсем напротив! Его повысили и, по его же просьбе, направили служить в Средиземное море. Мы только можем ему по-доброму позавидовать. Особенно в нашей-то нынешней ситуации. Так вот, собственно о нашей ситуации...";
			link.l1 = "";
			link.l1.go = "FraOfficer_2";
		break;
		
		case "FraOfficer_2":
			dialog.text = "На острове мы обнаружили поселение - довольно обжитой бандитский притон для - вы только вслушайтесь - пиратов и кастильцев. Невероятно! Сами знаете, обычно эти ублюдки только и делают, что режут да вешают друг друга, а тут - на тебе: в самом центре архипелага дружно, по-семейному, добывают бакаут. А-ать! Видели какой причал себе отгрохали? Гости к этому отродью приходят явно не на баркасах\nЗадача у нас стоит предельно ясная: с вашей помощью захватываем посёлок, забираем бакаут и пленников, вы отвозите всех в Капстервиль. Дальше уж начальство само разберется... а пока оно разбирается, мы с вами решим вопрос с бакаутом и отметим как следует с другими офицерами моей домашней эскадры!";
			link.l1 = "А что вам мешало к этому моменту уже взять посёлок самостоятельно?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_3":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "Бандитов ещё наверняка много больше нас - мы видели палатки на берегу. А кроме палаток у них ещё есть стена, ворота, пушка!";
			else sTemp = "Бандитов конечно тоже явно немного, иначе они бы уже выбили нас отсюда, но ведь у них ещё есть стена, ворота, пушка и целая куча времени!";
			dialog.text = "Что мешало?! Нас всего-то двенадцать фузилёров, да семь матросов. Все уставшие и потрепанные. Мушкетов спасли только пять, на каждый только по одному боекомплекту в лучшем случае! "+sTemp+"";
			link.l1 = "Но план же у вас есть?";
			link.l1.go = "FraOfficer_4";
		break;
		
		case "FraOfficer_4":
			dialog.text = "Послушайте, мы же время зря не теряли. Первым делом мы отбили эту факторию, тем самым захватив некоторый запас пищи и воды, а главное - полный склад бакаута и более дюжины рабов! Охранять рабов мы бы всё равно не смогли, так что немедленно устроили разведку боем, направив их в атаку на своих же бывших хозяев под прикрытием наших мушкетов. Именно так мы и узнали, что у бандитского сброда есть в наличии орудие.";
			link.l1 = "Я правильно понимаю, что теперь вы хотите натравить уже меня и моих людей на это орудие вместо рабов?";
			link.l1.go = "FraOfficer_5";
		break;
		
		case "FraOfficer_5":
			dialog.text = "Нет, но вас можно отправить к бандитам в качестве парламентёра. Ваш приезд означает, что их логово раскрыто, а у солдат короля теперь есть корабль и подкрепление. Ну, а пока они будут уши развешивать и оценивать всю глубину своей глубины, вы подберётесь как можно ближе к орудию, бросите под него пехотную бомбу и не дадите себя убить до подхода наших с вами людей. Если вы не уверены, что справитесь, то попробуйте отправить кого-нибудь из своих вместо себя.";
			link.l1 = "Давайте сначала я к ним схожу без бомбы и предложу сдаться. Осмотрюсь, пойму их настроение и силы, зароню сомнение в души. Если не сдадутся, то схожу к ним ещё раз, но уже с бомбой.";
			if (CheckCharacterItem(pchar, "patent_fra")) link.l1.go = "FraOfficer_6";
			else link.l1.go = "FraOfficer_6_1";
		break;
		
		case "FraOfficer_6":
			GiveItem2Character(pchar, "grenade");
			//Log_Info("Вы получили гранату");
			PlaySound("interface\important_item.wav");
			dialog.text = "... и к тому моменту они уже привыкнут к вам, так что будет легче устроить диверсию! Умно! Впрочем, иного я от вас не ждал, капитан. Приступайте, как будете готовы. Но, всё же, вот... Мало ли, пригодится.";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_6_1":
			dialog.text = "... и к тому моменту они уже привыкнут к вам, так что будет легче устроить диверсию. Так и поступим. Выполняйте!";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_7":
			DialogExit();
			AddQuestRecord("IslaMona", "19");
			chrDisableReloadToLocation = false;
			pchar.quest.islamona_def_goout.win_condition.l1 = "location";
			pchar.quest.islamona_def_goout.win_condition.l1.location = "IslaMona_Jungle_01";
			pchar.quest.islamona_def_goout.function = "IslaMona_DefCapralTalk";
		break;
		
		case "FraOfficer_8":
			dialog.text = "Был затяжной бой с испанцами в этом районе. Оба корабля пошли на дно, а выжившие попали сюда. В основном французы, но кое-кто и из наших врагов сумел спастись. А больше вам знать ни к чему, уж извините, капитан. Секретные сведения, сами понимаете.";
			link.l1 = "Допустим.";
			link.l1.go = "FraOfficer_9";
		break;
		
		case "FraOfficer_9":
			dialog.text = "На острове мы обнаружили поселение - довольно обжитой бандитский притон для - вы только вслушайтесь - пиратов и кастильцев. Невероятно! Сами знаете, обычно эти ублюдки только и делают, что режут да вешают друг друга, а тут - на тебе: в самом центре архипелага дружно, по-семейному, добывают бакаут. А-ать! Видели какой причал себе отгрохали? Гости к этому отродью приходят явно не на баркасах\nЗадача у нас стоит предельно ясная: с вашей помощью захватываем посёлок, забираем бакаут и пленников, вы отвозите всех в Капстервиль. Дальше уж начальство само разберется... А пока оно разбирается, я даже буду готов дать вам возможность умыкнуть немного ценной древесины для своих нужд.";
			link.l1 = "А что вам мешало к этому моменту уже взять посёлок самостоятельно?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_10":
			dialog.text = "Вот и вы! Есть новости?";
			link.l1 = "А это что - почётный караул?";
			link.l1.go = "FraOfficer_11";
		break;
		
		case "FraOfficer_11":
			dialog.text = "Очевидно, что сейчас будет приниматься решение о наших дальнейших действиях. Я бы не хотел выискивать своих людей по всему острову, чтобы раздавать новые приказы.";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Отличная инициатива! Будут вам приказы. Разведку я провёл: противник слаб, а пушка осталась без зарядов. Приказываю вам атаковать бандитское логово немедленно, лейтенант. Хватит сопли на кулак наматывать. Обычный день на флоте. Выполнять!";
				link.l1.go = "FraOfficer_12";
			}
			else
			{
				link.l1 = "Моё мнение - вы могли бы взять их сразу после 'рабской' разведки боем. Оборона их смешна, пара-тройка серьёзных бойцов. Зря вы так распереживались - уже бы пили трофейное вино, сидя на горе бакаута.";
				link.l1.go = "FraOfficer_14";
			}
		break;
		
		case "FraOfficer_12":
			dialog.text = "Так точно, господин капитан!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_13";
		break;
		
		case "FraOfficer_13":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -25);
			AddQuestRecord("IslaMona", "22");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_14":
			dialog.text = "И это все результаты вашей разведки? Я понимаю, что странно было бы ожидать слишком многого от невоенного человека, но мне нужны факты! Факты, капитан, а не ваше мнение!";
			link.l1 = "Обижаете, лейтенант. Докладываю!";
			link.l1.go = "FraOfficer_15";
		break;
		
		case "FraOfficer_15":
			dialog.text = "";
			link.l1 = "Сейчас с ними выживший капитан испанского судна, которое вы утопили. Опытный командир, который уже скоро встанет на ноги. Будете тянуть - он оклемается и организует оборону по всем правилам военной науки, и тогда туго нам придётся. Надо поспешить - я повторяю вам, что сейчас они слабы и деморализованы.";
			link.l1.go = "FraOfficer_15_1";
			link.l2 = "Скоро к ним прибудет подкрепление - забирать бакаут. Не думаю, что это блеф: вы сами видели причалы и кучу готового к сдаче товара на складе фактории. Надо поспешить - я повторяю вам, что сейчас они слабы и деморализованы. Будете тянуть - дождетесь прихода пиратского судна.";
			link.l2.go = "FraOfficer_15_2";
			link.l3 = "Почти половина обитателей этой дыры - женщины. Вы воюете даже не с ополчением: против вас всё это время стояло не больше дюжины бойцов. Они слабы и деморализованы.";
			link.l3.go = "FraOfficer_15_3";
			link.l4 = "У пушки больше нет зарядов. Я достаточно орудий повидал на своём веку и могу отличить когда расчёт готов к стрельбе, а когда не готов. Без своей артиллерии их горе-вояки ничего не стоят, они слабы и деморализованы.";
			link.l4.go = "FraOfficer_15_4";
			link.l5 = "Подумайте о трофеях и славе, лейтенант! Единоличная победа над испанским рейдером, захват бандитского гнезда и уникального источника бакаута - всё это тянет на командование собственным кораблём! Я повторяю вам, что сейчас они слабы и деморализованы, самое время раздавить их!";
			link.l5.go = "FraOfficer_15_5";
		break;
		
		case "FraOfficer_15_1":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				notification("Проверка пройдена", SKILL_LEADERSHIP);
				dialog.text = "Благодарю вас, капитан. Это полезные сведения и вы были правы, нечего тут тянуть. Мои люди все здесь, мы сильны, обучены и готовы. Через полчаса всё будет кончено. Капитан, пожалуйста подготовьтесь к приему людей, пленников и груза на свой корабль. Мы не задержимся здесь надолго.";
				link.l1 = "Уже всё готово, лейтенант. Ждали только вас. До встречи!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Недостаточно развит навык (80)", SKILL_LEADERSHIP);
				dialog.text = "Благодарю вас, капитан. Это полезные сведения. В таком случае, отправляйтесь на причал и принимайте свою абордажную роту. Будем штурмовать бандитское гнездо вместе и немедленно. В авангард войдут лучшие из моих и ваших людей - именно им предстоит захватить ворота. Остальное обсудим после общего смотра наших сил. Не подведите меня и свою страну, "+GetFullName(pchar)+".";
				link.l1 = "...Да будет так. До встречи, лейтенант.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_2":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Проверка чести пройдена", "None");
				notification("Проверка пройдена", SKILL_LEADERSHIP);
				dialog.text = "Благодарю вас, капитан. Это полезные сведения и вы были правы, нечего тут тянуть. Мои люди все здесь, мы сильны, обучены и готовы. Через полчаса всё будет кончено. Капитан, пожалуйста подготовьтесь к приему людей, пленников и груза на свой корабль. Мы не задержимся здесь надолго.";
				link.l1 = "Уже всё готово, лейтенант. Ждали только вас. До встречи!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Слишком низкий уровень чести! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Недостаточно развит навык (60)", SKILL_LEADERSHIP);
				dialog.text = "Благодарю вас, капитан. Это полезные сведения. В таком случае, отправляйтесь на причал и принимайте свою абордажную роту. Будем штурмовать бандитское гнездо вместе и немедленно. В авангард войдут лучшие из моих и ваших людей - именно им предстоит захватить ворота. Остальное обсудим после общего смотра наших сил. Не подведите меня и свою страну, "+GetFullName(pchar)+".";
				link.l1 = "...Да будет так. До встречи, лейтенант.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 70 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Проверка чести пройдена", "None");
				notification("Проверка пройдена", SKILL_LEADERSHIP);
				dialog.text = "Благодарю вас, капитан. Это полезные сведения и вы были правы, нечего тут тянуть. Мои люди все здесь, мы сильны, обучены и готовы. Через полчаса всё будет кончено. Капитан, пожалуйста подготовьтесь к приему людей, пленников и груза на свой корабль. Мы не задержимся здесь надолго.";
				link.l1 = "Уже всё готово, лейтенант. Ждали только вас. До встречи!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Слишком низкий уровень чести! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Недостаточно развит навык (70)", SKILL_LEADERSHIP);
				dialog.text = "Благодарю вас, капитан. Это полезные сведения. В таком случае, отправляйтесь на причал и принимайте свою абордажную роту. Будем штурмовать бандитское гнездо вместе и немедленно. В авангард войдут лучшие из моих и ваших людей - именно им предстоит захватить ворота. Остальное обсудим после общего смотра наших сил. Не подведите меня и свою страну, "+GetFullName(pchar)+".";
				link.l1 = "...Да будет так. До встречи, лейтенант.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Проверка чести пройдена", "None");
				notification("Проверка пройдена", SKILL_LEADERSHIP);
				dialog.text = "Благодарю вас, капитан. Это полезные сведения и вы были правы, нечего тут тянуть. Мои люди все здесь, мы сильны, обучены и готовы. Через полчаса всё будет кончено. Капитан, пожалуйста подготовьтесь к приему людей, пленников и груза на свой корабль. Мы не задержимся здесь надолго.";
				link.l1 = "Уже всё готово, лейтенант. Ждали только вас. До встречи!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Слишком низкий уровень чести! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Недостаточно развит навык (60)", SKILL_LEADERSHIP);
				dialog.text = "Благодарю вас, капитан. Это полезные сведения. В таком случае, отправляйтесь на причал и принимайте свою абордажную роту. Будем штурмовать бандитское гнездо вместе и немедленно. В авангард войдут лучшие из моих и ваших людей - именно им предстоит захватить ворота. Остальное обсудим после общего смотра наших сил. Не подведите меня и свою страну, "+GetFullName(pchar)+".";
				link.l1 = "...Да будет так. До встречи, лейтенант.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_5":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 90)
			{
				notification("Проверка пройдена", SKILL_LEADERSHIP);
				dialog.text = "Благодарю вас, капитан. Это полезные сведения и вы были правы, нечего тут тянуть. Мои люди все здесь, мы сильны, обучены и готовы. Через полчаса всё будет кончено. Капитан, пожалуйста подготовьтесь к приему людей, пленников и груза на свой корабль. Мы не задержимся здесь надолго.";
				link.l1 = "Уже всё готово, лейтенант. Ждали только вас. До встречи!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Недостаточно развит навык (90)", SKILL_LEADERSHIP);
				dialog.text = "Благодарю вас, капитан. Это полезные сведения. В таком случае, отправляйтесь на причал и принимайте свою абордажную роту. Будем штурмовать бандитское гнездо вместе и немедленно. В авангард войдут лучшие из моих и ваших людей - именно им предстоит захватить ворота. Остальное обсудим после общего смотра наших сил. Не подведите меня и свою страну, "+GetFullName(pchar)+".";
				link.l1 = "...Да будет так. До встречи, лейтенант.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_16": // французы атакуют сами
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			AddQuestRecord("IslaMona", "24");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_17": // совместная атака
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -7);
			AddQuestRecord("IslaMona", "23");
			IslaMona_DefAttackCommon();
		break;
		
		case "FraOfficer_18":
			if (CheckCharacterItem(pchar, "patent_fra")) dialog.text = "А я, идиот, восхищался тобой! А-ать! Гордость Франции, капитан "+GetFullName(pchar)+"!! Ты недостоин своего патента!!!";
			else dialog.text = ""+GetFullName(pchar)+", ублюдок, предатель и проклятый пират! Мне стоило догадаться, что этот нищий притон - твоя вонючая вотчина! Франция такого не забывает и не прощает!";
			link.l1 = "";
			link.l1.go = "FraOfficer_19";
		break;
		
		case "FraOfficer_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_75";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FraOfficer_20":
			dialog.text = "Готовы, капитан? Ваш отряд выглядит достойно!";
			link.l1 = "Спасибо, лейтенант. Начинаем?";
			link.l1.go = "FraOfficer_21";
		break;
		
		case "FraOfficer_21":
			dialog.text = "Да, давайте сразу за нами!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_22";
		break;
		
		case "FraOfficer_22":
			DialogExit();
			IslaMona_DefAttackCommonRun();
		break;
		
		// обиженный пират
		case "Pirate":
			dialog.text = "Ба! "+GetFullName(pchar)+"! Вот это встреча. Эй, хватайте его! Этому ублюдку принадлежит здесь всё! Это его остров!";
			link.l1 = "Да что же за день-то такой сегодня?!";
			link.l1.go = "Pirate_1";
		break;
		
		case "Pirate_1":
			DialogExit();
			IslaMona_DefCheckJungleFight();
		break;
		
		// Алонсо
		case "Alonso":
			dialog.text = "Кэп, какие будут приказы? Был сигнал встать на стоянку и выслать абордажную роту.";
			link.l1 = "Приказ в силе. Парни, за мной, надо очистить наш дом от незваных гостей. С меня премия, трофеи все ваши!";
			link.l1.go = "Alonso_1";
		break;
		
		case "Alonso_1":
			dialog.text = "Ура!";
			link.l1 = "К бою!";
			link.l1.go = "Alonso_2";
		break;
		
		case "Alonso_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_our_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common"))
			{
				pchar.quest.islamona_attack_common1.win_condition.l1 = "location";
				pchar.quest.islamona_attack_common1.win_condition.l1.location = "IslaMona_Jungle_01";
				pchar.quest.islamona_attack_common1.function = "IslaMona_DefAttackCommonPrepare";
			}
			else
			{
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
				pchar.quest.islamona_attack_force.win_condition.l1 = "location";
				pchar.quest.islamona_attack_force.win_condition.l1.location = "IslaMona_factoria";
				pchar.quest.islamona_attack_force.function = "IslaMona_DefAttackForce";
			}
		break;
		
		// испанский офицер
		case "SpaOfficer":
			dialog.text = "Приветствую вас, сеньор. Вы владелец этой земли? Позвольте представится, гранд Франсиско де Альба, бывший капитан корвета 'Перро Марино'.";
			link.l1 = "Да, это моя земля. "+GetFullName(pchar)+", капитан корабля '"+pchar.ship.name+"'. Гранд? Таких высоких гостей у нас тут ещё не бывало.";
			link.l1.go = "SpaOfficer_1";
		break;
		
		case "SpaOfficer_1":
			dialog.text = "О, монсеньор "+GetFullName(pchar)+"! Наслышан. Знаете, последнее время ваше имя настолько часто всплывает в отчётах Каса-де-Контратасьон, что я на полном серьёзе ждал приказа заняться вами.";
			link.l1 = "Заняться мной?";
			link.l1.go = "SpaOfficer_2";
		break;
		
		case "SpaOfficer_2":
			dialog.text = "Думаю, притворяться нет смысла. Моя работа - искать и уничтожать врагов Испании и короля Филиппа на всех морях земного шара.";
			link.l1 = "Хорошо, что такого приказа пока не пришло. Вы явно очень умелый военный моряк.";
			link.l1.go = "SpaOfficer_3";
		break;
		
		case "SpaOfficer_3":
			dialog.text = "Тот факт, что теперь я полумёртвый пленник на крошечном островке, кишащем пиратами и моими беглыми соотечественниками только подтверждает ваше умозаключение, ха-ха! Дело было очень опасное, но приказ есть приказ. У нас ведь почти получилось! Безумно жаль моих людей - всех знал по именам, не один год вместе прослужили. Но моей стране придётся пролить ещё немало крови своих сыновей, чтобы удержать статус империи. Нашей семье это известно лучше многих.";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "";
				link.l1.go = "SpaOfficer_4";
			}
			else
			{
				link.l1 = "Давайте пока вернёмся к более насущным вопросам. Что же мне с вами делать, гранд?";
				link.l1.go = "SpaOfficer_5";
			}
		break;
		
		case "SpaOfficer_4":
			dialog.text = "Кстати, месье де Мор, 'Воинственный' - знакомый был вам кораблик, а? Ваша дерзкая операция в Порто Белло не осталась незамеченной. Смело, даже самоубийственно. Очень деньги нужны были, я прав? Ха!";
			link.l1 = "Вы многое обо мне знаете, гранд. Но давайте перейдём к вашей судьбе.";
			link.l1.go = "SpaOfficer_5";
		break;
		
		case "SpaOfficer_5":
			dialog.text = "А чего тут думать? Как и в любой хорошей истории, у вас есть три варианта: убить меня, оставить здесь или отпустить. Если отпустите, то я даю вам слово семьи де Альба, что никогда и никому не расскажу об этом месте и о вашем участии в моих злоключениях. Сверх того, я буду вашим должником и пока этот долг не будет выплачен, я никогда не встану против вас в бою.";
			link.l1 = "Я не могу так рисковать, гранд.";
			link.l1.go = "SpaOfficer_6";
			link.l2 = "Вы какое-то время проведёте здесь. Будете жить и трудиться на равных с вашими соотечественниками.";
			link.l2.go = "SpaOfficer_7";
			link.l3 = "Добро пожаловать на мой корабль, гранд. Я высажу вас на маяке Сантьяго, когда придёт время. Надеюсь, вы сдержите своё слово.";
			link.l3.go = "SpaOfficer_8";
		break;
		
		case "SpaOfficer_6":
			dialog.text = "Понимаю, сеньор. Ну что же, я в любом случае уже погиб в том бою вместе со своими людьми. Это хороший конец.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_6_1";
		break;
		
		case "SpaOfficer_6_1":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_KillSpanish", 1.0);
		break;
		
		case "SpaOfficer_7":
			dialog.text = "Признаюсь, я не люблю полумер. Но в том чтобы быть пленником нет бесчестья, так что ваш дар жизни я принимаю и буду в мире жить с этими добрыми и, по-видимому, очень счастливыми людьми. Тем не менее, если я когда-нибудь покину это место, я ничего вам уже не буду должен.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_7_1";
		break;
		
		case "SpaOfficer_7_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			AddQuestRecord("IslaMona", "27");
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_8":
			dialog.text = "Я даю вам своё слово и слово семьи де Альба! До встречи на корабле!";
			link.l1 = "";
			link.l1.go = "SpaOfficer_8_1";
		break;
		
		case "SpaOfficer_8_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("IslaMona", "28");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			pchar.quest.islamona_final_mayak.win_condition.l1 = "location";
			pchar.quest.islamona_final_mayak.win_condition.l1.location = "Mayak9";
			pchar.quest.islamona_final_mayak.function = "IslaMona_FinalMayakSpanish";
			pchar.questTemp.IslaMona.Mayak = "true";
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_9": //TO_DO: Нельзя принудительно выдавать куски карты! В инвентаре могут быть обе сразу, либо первая + целая карта
			dialog.text = "Капитан "+GetFullName(pchar)+"! Вы спасли мне жизнь и вернули меня к своим. Я понимаю, что на такой риск пойти было очень нелегко - я бы точно никогда на такое не решился. Я ваш должник, сеньор. Даю вам слово, что никто никогда не услышит от меня все обстоятельства того злополучного сражения. Как вернётесь в Старый Свет - обязательно найдите меня, в нашем родовом поместье в Мадриде вам всегда будут рады. А пока вот, держите...";
			link.l1 = "Половинка карты?";
			link.l1.go = "SpaOfficer_10";
		break;
		
		case "SpaOfficer_10":
			AddMapPart();
			dialog.text = "Это всё что у меня было с собой ценного. Не сомневаюсь, что достать вторую половинку вам не составит труда. Прощайте! И удачи вам, мой друг.";
			link.l1 = "Прощайте, гранд. Помните о своём слове и удачи вам!";
			link.l1.go = "SpaOfficer_11";
		break;
		
		case "SpaOfficer_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.IslaMona.Mayak = "done";
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddQuestRecord("IslaMona", "29");
			CloseQuestHeader("IslaMona");
		break;
		
		// Диалоги обитателей Исламоны
		// мужское население
		case "island_man":
			dialog.text = LinkRandPhrase("Приветствую! Как ваши дела, капитан? У нас всё идёт неплохо.","Работать на благо общины - самая большая радость!","Остров у вас замечательный, капитан, и мы всё сделаем для его процветания.");
			link.l1 = LinkRandPhrase("Приятно слышать это.","Рад, что у вас всё хорошо.","Мне нравится ваше рвение, amigo.");
			link.l1.go = "island_man_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Не сочтите за дерзость, сеньор, но жить здесь нельзя.","Всё лучше, чем в клетках Инквизиции сидеть..."),
						                               RandPhraseSimple("Спасибо, что выручили нас, сеньор капитан.","Эти... пираты - ваши друзья?"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 1:
						dialog.text = RandPhraseSimple(RandPhraseSimple("А здесь недурно! Только скучновато.","Капитан, рад вас видеть. Заходите в гости!"),
						                               RandPhraseSimple("Недавно кто-то нашёл черепа на пляже и притащил их на утренний сбор. Тут всегда так?","Скажу вам по-секрету, сеньору Хименесу явно пошли на пользу свежий воздух и безопасность этого места."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 2:
						dialog.text = RandPhraseSimple(RandPhraseSimple("А здесь недурно! Только скучновато.","Капитан, рад вас видеть. Заходите в гости!"),
						                               RandPhraseSimple("Недавно кто-то нашёл черепа на пляже и притащил их на утренний сбор. Тут всегда так?","Скажу вам по-секрету, сеньору Хименесу явно пошли на пользу свежий воздух и безопасность этого места."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 3:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Храни вас Бог, капитан!","Раз в неделю мы устраиваем представления на пляже и в таверне. Заглядывайте как-нибудь."),
						                               RandPhraseSimple("Ваши моряки постоянно привозят нам всякую мелочевку в обмен на свежую еду. Спасибо, что поощряете это.","Удивительно как это место ещё не нашли. Надеюсь, так будет и впредь."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
				}
			}
		break;
		
		case "island_man_1":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
		break;
		
		case "island_man_2":
			dialog.text = "Спасибо, сеньор. Благодаря вам, мы увидели настоящий Новый Свет. Храни вас Бог!";
			link.l1 = "";
			link.l1.go = "island_man_3";
			locCameraFromToPos(1.64, 1.58, -5.11, false, 2.66, 0.20, -5.74);
		break;
		
		case "island_man_3":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
			sld = characterFromId("Himenes_companion_12");
			sld.dialog.currentnode = "island_woman_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// женское население
		case "island_woman":
			dialog.text = LinkRandPhrase("Безопасность и тишина - вот что мне тут нравится!","Замечательный райский уголок! Ну, почти...","Мы рады обрести здесь новый дом тут, после стольких лишений.");
			link.l1 = LinkRandPhrase("Рад за тебя и твою общину.","Да, мне тоже по душе этот островок.","Приятно знать, что вы довольны.");
			link.l1.go = "island_woman_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = LinkRandPhrase("Ой... Здравствуйте.","Сеньор, а кто эти... грубые люди с оружием?","Спасибо, что спасли нас, сеньор капитан.");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 1:
						dialog.text = LinkRandPhrase("Наши мужчины отлично поработали - дома отличные. Но и мы знатно потрудились!","Сеньор капитан, не переживайте: женщины нашего небольшого клана не боятся сложностей и временного дискомфорта.","Какой тут воздух! А море! Чувствуешь себя ближе к Богу!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 2:
						dialog.text = LinkRandPhrase("Наши мужчины отлично поработали - дома отличные. Но и мы знатно потрудились!","Сеньор капитан, не переживайте: женщины нашего небольшого клана не боятся сложностей и временного дискомфорта.","Какой тут воздух! А море! Чувствуешь себя ближе к Богу!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 3:
						dialog.text = LinkRandPhrase("Возвращайтесь почаще, сеньор капитан. Я всегда рада вас видеть.","Сеньор Родгар - потрясающий рассказчик. Заслушаться можно!","Хи-хи. Говорят, кое-кто из наших уже ждёт пополнения в семье. Даже на Исла-Моне жизнь берёт своё!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
				}
			}
		break;
		
		case "island_woman_1":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
		break;
		
		case "island_woman_2":
			dialog.text = "Вы... Muchas gracias, сеньор! Приезжайте почаще...";
			link.l1 = "";
			link.l1.go = "island_woman_3";
			locCameraFromToPos(-1.86, 1.18, 4.51, true, -1.49, 0.20, 6.13);
		break;
		
		case "island_woman_3":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// пираты Родгара
		case "fort_pirate":
			if(npchar.location == "islamona_factoria")
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Всё в порядке, кэп!","Рабы под контролем, не переживайте."),
						                                 RandPhraseSimple("Можете не волноваться, бунт исключён.","Спасибо вам за ром! Отработаем!"));
			}
			else
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Испанцы? Не ожидали мы от вас такого.","Теперь придётся топать аж до самого пляжа, чтоб поспать спокойно!"),
						                                 RandPhraseSimple("И зачем вам это всё сдалось - то а, кэп?","Старший вам поверил тогда, у пушки  - и мы не прогадали. Поверим ещё раз."));
			}
			link.l1 = "...";
			link.l1.go = "fort_pirate_1";
		break;
		
		case "fort_pirate_1":
			DialogExit();
			npchar.dialog.currentnode = "fort_pirate";
		break;
		
		// посетители таверны
		case "citizen_tavern":
			dialog.text = LinkRandPhrase("После трудов праведных не грех опрокинуть стаканчик-другой...","Скоро допиваю и иду домой, жена уже наверняка заждалась...","Эх, хорошо отдохнуть в нашей таверне после работы! Мы все вам благодарны, капитан!");
			link.l1 = LinkRandPhrase("Приятной попойки, compadre, ха-ха!","Отдыхай, приятель, только не перебери лишку, а то жёнушка заругает, ха-ха!","Расслабляйся, дружище, не всё же работать и работать!");
			link.l1.go = "citizen_tavern_1";
		break;
		
		case "citizen_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "citizen_tavern";
		break;
		
		case "sailor_tavern":
			if (GetCharacterIndex("Mirabella") != -1) sTemp = "А что это за симпатичная мулатка здесь живёт?";
				else sTemp = "Капитан, а здесь мило!";
			dialog.text = RandPhraseSimple(RandPhraseSimple("Капитан, а здесь мило!", "А что если однажды ром просто закончится? Вы же привезёте ещё?"), RandPhraseSimple("Давно о таком отпуске мечтал... ещё бы бордель! Ни на что не намекаю, кэп.", sTemp));
			link.l1 = "...";
			link.l1.go = "sailor_tavern_1";
		break;
		
		case "sailor_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_tavern";
		break;
		
		case "sailor_town":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Спасибо за отпуск, капитан!", "Неплохое местечко вы тут отстроили - не только на корабле порядок умеете держать..."), RandPhraseSimple("Свежая пища, выпивка, твердая земля под ногами - мечта!", "Я бы тут пожил, да подольше."));
			link.l1 = "...";
			link.l1.go = "sailor_town_1";
		break;
		
		case "sailor_town_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_town";
		break;
		
		// рабы
		case "slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Я так устал - просто с ног валюсь.", "Нет больше сил так жить!"), RandPhraseSimple("Эта работа слишком тяжёлая для меня.", "Надсмотрщики уже не оставили живого места на моей шкуре!"));				
			link.l1 = "";
			link.l1.go = "slave_1";
		break;
		
		case "slave_1":
			DialogExit();
			npchar.dialog.currentnode = "slave";
		break;
		
		// энкауниеры в домах
		case "HouseMan":
			dialog.text = LinkRandPhrase("Я могу вам чем-нибудь помочь, сеньор капитан?","Заходите, угоститесь местной паэльей. Только, ради Бога, не спрашивайте из чего она!","Добро пожаловать, сеньор капитан. Как вам у нас?");
			link.l1 = "...";
			link.l1.go = "HouseMan_1";
		break;
		
		case "HouseMan_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseMan";
		break;
		
		case "HouseWoman":
			dialog.text = LinkRandPhrase("Сеньор, добро пожаловать!","Здравствуйте, капитан. Может останетесь?","Вы ко мне? Прошу, заходите, только не обращайте внимание на беспорядок, сеньор.");
			link.l1 = "...";
			link.l1.go = "HouseWoman_1";
		break;
		case "HouseWoman_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseWoman";
		break;
	}
}