void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold, NextMonth;
	string attrL, sStr, Month;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Диалог с курьером
		case "SharlieEpilog_Cureer":
			dialog.text = "Здравствуйте, "+GetTitle(NPChar, false)+". Вам письмо от аббата Бенуа.";
			link.l1 = "Спасибо!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_Cureer_2");
		break;
		
		// диалоги в ПУ
		case "SharlieEpilog_Pikar_1":
			dialog.text = "Какие люди! Сам "+GetTitle(NPChar, true)+" "+pchar.lastname+" собственной персоной!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				link.l1 = ""+npchar.name+"! Вот уж кого не ожидал увидеть... Да что уж там - не думал, что ты всё ещё жив!";
				link.l1.go = "SharlieEpilog_Pikar_2";
			}
			else
			{
				link.l1 = "Глазам своим не верю... Красавчик? Но... как?";
				link.l1.go = "SharlieEpilog_PikarResurrected_1";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\LE\Rocur\Rocur_03.wav");
		break;
		
		case "SharlieEpilog_Pikar_2":
			if (IsStateTitle())
			  {
				dialog.text = "Ха-ха! Ну это ты зря. Как видишь - живее всех живых. Вот, решил себе 'чистенький' кораблик прикупить. Ну а ты... рассказывай: как докатился до жизни такой, а, дружище?";
			  }
			  else 
			  {
				dialog.text = "Ха-ха! Ну это ты зря. Как видишь - живее всех живых. Вот, решил себе 'чистенький' кораблик прикупить. Ну а ты... рассказывай: какими судьбами здесь, а, дружище?";
			  }
			link.l1 = "Не здесь же. Идём в таверну - дела подождут.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_1":
			dialog.text = "Чш... Не кричи ты так. Красавчик - в прошлом, как, полагаю, и Принц. Не так ли?";
			link.l1 = "Но я ведь собственными глазами видел...";
			link.l1.go = "SharlieEpilog_PikarResurrected_2";
		break;

		case "SharlieEpilog_PikarResurrected_2":
			dialog.text = "Как меня прикончили? Лучше бы оно так и было, дружище. Уж поверь.";
			link.l1 = "Идём в таверну. Расскажешь мне всё.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_Captain_1":
			dialog.text = "...";
			link.l1 = "Значит, вы новый владелец пинаса '"+GetShipName("Ulysse")+"'?";
			link.l1.go = "SharlieEpilog_Captain_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\z_arest_02.wav");
		break;
		
		case "SharlieEpilog_Captain_2":
			dialog.text = "Я. "+GetFullName(npchar)+", раз уж вам так интересно. А вы кто будете?";
			link.l1 = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.lastname+", и я хотел бы выкупить у вас этот корабль.";
			link.l1.go = "SharlieEpilog_Captain_3";
		break;
		
		case "SharlieEpilog_Captain_3":
			dialog.text = "Как же, как же, наслышан. А я уж думал, что уже отбился от всех желающих заполучить эту посудину. Придётся вас разочаровать, "+GetTitle(NPChar, true)+" - '"+GetShipName("Ulysse")+"' теперь мой, и очень скоро я на нём ухожу в Бордо. Не для того в торговлю пошёл, чтобы сразу же срывать первую же сделку. Плохая примета, знаете ли.";
			link.l1 = "Бордо, говорите? Любопытно... Возможно, у меня для вас будет выгодное предложение. Может, обсудим это за кружечкой рома?";
			link.l1.go = "SharlieEpilog_Captain_4";
		break;
		
		case "SharlieEpilog_Captain_4":
			dialog.text = "Не в моих правилах отказываться ни от рома, ни от выгодных предложений. Идёмте.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		// диалоги в таверне
		case "SharlieEpilog_Pikar_5":
			if (IsStateTitle())
			  {
				dialog.text = "Ну, за тебя, "+GetTitle(npchar, false)+" "+pchar.lastname+". Знал я, что такой парень, как ты, долго у Тиракса на побегушках не задержится. Но что ты станешь такой важной птицей... умеешь удивлять, чёрт возьми.";
				link.l1 = "Ха-ха. Кто бы говорил. Так значит, ты решил податься в торгаши?";
			  }
			  else 
			  {
				dialog.text = "За встречу! Затылком чувствовал, что мы ещё увидимся.";
				link.l1 = "Ха-ха. За неё! Так значит, ты решил податься в торгаши?";
			  }
			
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;

		case "SharlieEpilog_Pikar_6":
			dialog.text = "Ну не век же глотку под нож подставлять за пару дублонов. Подмазал кого надо, закрыл рот кому не надо - и вот: я не вор и пират, а почтенный негоциант.";
			link.l1 = "Вот это поворот. Даже не знаю теперь, как предлагать тебе то, что собирался предложить новоиспечённому капитану пинаса '"+GetShipName("Ulysse")+"'.";
			link.l1.go = "SharlieEpilog_Pikar_7";
		break;

		case "SharlieEpilog_Pikar_7":
			dialog.text = "Да брось, выкладывай как есть. Мы же с тобой сто лет знакомы.";
			link.l1 = "Видишь ли... я прибыл сюда, на Карибы, на пинасе, который ты выкупил. Когда узнал, что он выставлен на аукцион, хотел выторговать его - и уйти на нём домой, во Францию.";
			link.l1.go = "SharlieEpilog_Pikar_8";
		break;

		case "SharlieEpilog_Pikar_8":
			dialog.text = "Ха-ха-ха-ха! Подожди... ах-ха-ха-ха-ха!..";
			link.l1 = "Ну, и что смешного?";
			link.l1.go = "SharlieEpilog_Pikar_9";
		break;

		case "SharlieEpilog_Pikar_9":
			dialog.text = "А то, что едва я выиграл торги, как подошёл ко мне франт - молодой, холёный: дескать, доставь меня, любезный, вместе с моими пожитками в Бордо, за звонкую монету. Да что там монету - целый чёртов мешок монет.";
			link.l1 = "Вот как? Ха-ха. И впрямь забавно. И что же ты? Согласился?";
			link.l1.go = "SharlieEpilog_Pikar_10";
		break;

		case "SharlieEpilog_Pikar_10":
			dialog.text = ""+pchar.name+", ну я же не болван отказываться от кучи золота за обычный переход через Атлантику. Да, придётся пару месяцев погрызть сухари да солонину пожевать. Но мне, знаешь ли, приходилось рисковать своей шеей и за меньшие деньги. Так что, разумеется, я в деле.";
			link.l1 = "В таком случае готов предложить тебе то же самое. Доставь меня в Бордо - и получишь такую же кучу монет.";
			link.l1.go = "SharlieEpilog_Pikar_11";
		break;

		case "SharlieEpilog_Pikar_11":
			dialog.text = "Ты готов стать пассажиром? Ты ведь знаешь наши порядки - капитан на судне один. И на моём судне - это я.";
			link.l1 = "Почему нет? Переведу дыхание, подумаю о жизни. Может, мне и вправду стоит осесть, остепениться. Сейчас мне такое даже представить сложно, но, возможно, в этом есть толк. Ведь даже ты решил держаться подальше от сражений.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Pikar_12_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Pikar_12";
			}
		break;
		
		case "SharlieEpilog_Pikar_12_wife":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				dialog.text = "Эх, будь у меня красавица жена, как у тебя, может, и сам бы бросил море, осел в какой-нибудь глуши: дом построил, да винцом торговал. Благо, жить есть на что - после того как ты вытащил меня из лап испанцев, я время зря не терял.";
			}
			else
			{
				dialog.text = "Эх, будь у меня красавица жена, как у тебя, может, и сам бы бросил море, осел в какой-нибудь глуши: дом построил, да винцом торговал. Благо, жить есть на что - наследство у вдовушки плантатора было знатное.";
			}
			link.l1 = "Жена! Дьявол, "+npchar.name+", я ведь с ней об этом пока не говорил.";
			link.l1.go = "SharlieEpilog_Pikar_13_wife";
		break;
		
		case "SharlieEpilog_Pikar_13_wife":
			dialog.text = "На это у тебя ещё предостаточно времени. Мне нужно оснастить своё корыто как следует. Как разбёрешься со всеми делами - тащи свою задницу сюда. Закатим пирушку перед отплытием.";
			link.l1 = "Вот это по мне! Не волнуйся, долго ждать не придётся.";
			link.l1.go = "SharlieEpilog_Pikar_14_wife";
		break;
		
		case "SharlieEpilog_Pikar_14_wife":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_1");}
			else {AddQuestRecord("SharlieEpilog", "11_5");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_12":
			dialog.text = "Эх, будь у меня жена, может, и сам бросил бы море, осел в какой-нибудь глуши: дом бы построил, да винцом приторговывал. Но пока... море - мой дом.";
			link.l1 = "Винцом с моих плантаций, ха-ха! В Бордо, "+npchar.name+", такие девицы - загляденье! Может и себе там кого присмотришь - в амурных делах они весьма не дурственны. Я вот что подумал: ближайшие месяцы всё, что нам с тобой придётся видеть, - это рожи твоих матросов. Нужно бы перед отплытием закатить знатную пирушку в местном борделе.";
			link.l1.go = "SharlieEpilog_Pikar_13";
		break;
		
		case "SharlieEpilog_Pikar_13":
			dialog.text = "А вы, месье, знаете что предложить. Как разбёрешься со всеми делами - тащи свою задницу сюда. А там и до борделя дойдём, уж будь уверен.";
			link.l1 = "Что ж, тогда не буду терять времени. За дело!";
			link.l1.go = "SharlieEpilog_Pikar_14";
		break;
		
		case "SharlieEpilog_Pikar_14":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_2");}
			else {AddQuestRecord("SharlieEpilog", "11_6");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_3":
			dialog.text = "За свободу!";
			link.l1 = "И за тебя, Жан! За твоё воскрешение! Всё ещё не верится. Как?";
			link.l1.go = "SharlieEpilog_PikarResurrected_4";
		break;

		case "SharlieEpilog_PikarResurrected_4":
			dialog.text = "Меня выволокли с поля боя - еле живого, в крови с головы до ног. Закинули в барак и оставили там подыхать, как падаль. Среди рабов оказался весьма ловкий малый - Моко. Он-то и спас мою шкуру: затянул рану куском моей же рубахи, дал попить.";
			link.l1 = "Хочешь сказать, испанцы оставили тебя в живых после всего?";
			link.l1.go = "SharlieEpilog_PikarResurrected_5";
		break;

		case "SharlieEpilog_PikarResurrected_5":
			dialog.text = "Как видишь. Только не по доброте душевной. Им хотелось возмездия - допрос с пристрастием, пытки. Жгли, били, резали. Грозились глаз выжечь - исключительно из большой любви ко мне. Но тут кто-то пустил слушок, что пираты готовятся за меня отомстить и уже точат ножи. У хозяина плантации аж глаз задёргался. Он не стал дожидаться визита нашего брата и поспешил в свои имения в Кампече. Нас с Моко и остальными он забрал с собой, чтоб свидетелей не осталось. Остальным объявили, что я представился - и на том поставили крест.";
			link.l1 = "И что же дальше? Как ты оказался на свободе? И как, чёрт возьми, ты оказался здесь?";
			link.l1.go = "SharlieEpilog_PikarResurrected_6";
		break;

		case "SharlieEpilog_PikarResurrected_6":
			dialog.text = "Удача, дружище. Слепая, грязная удача. Меня доставили на плантацию - и пытки продолжились. Этот ублюдок решил, что будет смаковать каждую секунду моих мучений, но с каждым днём он всё слабел... пока не сдох от лихорадки. После этого до меня уже никому не было дела. Выгнали в поле, как скотину, не забывая щедро почивать плетьми.";
			link.l1 = "Я всё ещё не понимаю, как ты вырвался оттуда?";
			link.l1.go = "SharlieEpilog_PikarResurrected_7";
		break;

		case "SharlieEpilog_PikarResurrected_7":
			dialog.text = "Слыхал о Кристофере Майнгсе?";
			link.l1 = "Алонсо что-то упоминал... Рейд на Кампече! Знатно они тогда испанцев разделали. Так это они тебя освободили?";
			link.l1.go = "SharlieEpilog_PikarResurrected_8";
		break;

		case "SharlieEpilog_PikarResurrected_8":
			dialog.text = "Не совсем. Мы сами себя освободили. Пока охрана отбивалась от англо-буканьерского отряда, мы с Моко нашли лазейку в крыше барака и подняли бунт. Захватили арсенал и казну жены покойного подонка-плантатора.";
			link.l1 = "Казну?! Вот это поворот.";
			link.l1.go = "SharlieEpilog_PikarResurrected_9";
		break;

		case "SharlieEpilog_PikarResurrected_9":
			dialog.text = "Мы не стали долго раздумывать - с оружием и добром ушли в сельву. Два дня пробирались сквозь чащу, пока не наткнулись на деревню индейцев Кан Печ. Их шаман для вида подчинялся испанцам, но особой любви к ним не питал. Моко быстро нашёл с ним общий язык - нас приютили в обмен на половину арсенала и помощь в войне с кем бы то ни было. Так я и прожил там полтора года.";
			link.l1 = "Ты, Жан, больше не тот, кем был раньше. Отныне ты - Счастливчик.";
			link.l1.go = "SharlieEpilog_PikarResurrected_10";
		break;

		case "SharlieEpilog_PikarResurrected_10":
			dialog.text = "Ха-ха. Не возражаю. Ну а дальше в наш батабиль занесло французского проповедника. Мы сразу смекнули: это шанс выбраться оттуда не в кандалах. Подкупили его эскорт - и вскоре уже плыли на Тортугу\nА дальше, как ты уже, наверняка, догадался, я решил больше не играть в догонялки со смертью. Завязал со старым ремеслом... и по случаю прикупил '"+GetShipName("Ulysse")+"'.\n"+
			"Ну а ты? Как докатился до жизни такой? Знал я, что такой лихой малый долго у Тиракса на побегушках не протянет. Но чтоб ты стал такой важной птицей... умеешь удивлять, чёрт возьми.";
			link.l1 = "Ха-ха. Кто бы говорил. Так значит, ты решил податься в торгаши?";
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;
		
		case "SharlieEpilog_Captain_5":
			dialog.text = "За тех, кто в море!";
			link.l1 = "И за госпожу удачу!";
			link.l1.go = "SharlieEpilog_Captain_6";
		break;

		case "SharlieEpilog_Captain_6":
			dialog.text = "Ну, к делу. Что вы хотели мне предложить?";
			link.l1 = "Вы отправляетесь в Бордо... Видите ли, я направляюсь туда же.";
			link.l1.go = "SharlieEpilog_Captain_7";
		break;

		case "SharlieEpilog_Captain_7":
			dialog.text = "Хотите, чтобы я взял вас на борт? Насколько мне известно, у вас должен быть свой корабль. А может, и целая флотилия. И всё же вы решили плыть на чужом судне. Я правильно понимаю?";
			link.l1 = "Именно так. Последние события заставили меня задуматься: возможно, пришло время бросить якорь, остепениться... Думаю, роль простого пассажира на вашем корабле поможет мне понять, смогу ли я принять новый ритм жизни.";
			link.l1.go = "SharlieEpilog_Captain_8";
		break;

		case "SharlieEpilog_Captain_8":
			dialog.text = "Хм... Значит, вы подустали рисковать шеей по чём зря? Знакомо. Я и сам... Впрочем, неважно. Место на корабле для вас найдётся, хоть и для всей вашей свиты. Рейс уже оплачен одним молодым франтом - и он же платит за скорость, так что трюмы грузить не стану. Что до оплаты...";
			link.l1 = "Не беспокойтесь, капитан. Я не уступаю в щедрости вашему нанимателю и готов заплатить ту же сумму.";
			link.l1.go = "SharlieEpilog_Captain_9";
		break;

		case "SharlieEpilog_Captain_9":
			dialog.text = "Превосходно! Тогда по рукам?";
			link.l1 = "По рукам! За это стоит выпить!";
			link.l1.go = "SharlieEpilog_Captain_10";
		break;

		case "SharlieEpilog_Captain_10":
			dialog.text = "Да, ром что надо... Мне понадобится две недели - довести корабль до ума и запастись всем необходимым. После этого можно отчаливать.";
			link.l1 = "Тогда встретимся здесь же через две недели. Ну, до встречи, капитан.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Captain_11_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Captain_11";
			}
		break;
		
		case "SharlieEpilog_Captain_11_wife":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_3");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Captain_11":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_4");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Ну что, дружище, разобрался с делами? Покажем этому курятнику, как нужно веселиться?";
				link.l1 = "Ещё не время, "+npchar.name+", у меня ещё остались кое-какие дела.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Капитан, вы уже готовы взойти на корабль?";
				link.l1 = "Увы, коллега, у меня ещё есть дела.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_Pikar_WaitInTavern";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				// только если знаком с Пикаром и поговорил с женой
				link.l2 = "Эй, трактирщик! Всем выпивку за мой счёт! И не что попало, а лучшее, что у тебя есть!";
				link.l2.go = "SharlieEpilog_Pikar_WaitInTavern_2";
			}
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern_2":
			dialog.text = "...";
			link.l1 = "За нас, дружище. За солёный ветер, за бескрайнее море и за горизонт - вечно манящий, вечно недосягаемый...";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_FrameInSea":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_FrameInSea");
		break;
		
		case "SharlieEpilog_Mary_1":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", милая, я хочу с тобой поговорить о моём отце.";
			link.l1.go = "SharlieEpilog_Mary_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_2":
			dialog.text = "Что случилось, дорогой? Надеюсь, с ним всё хорошо, да?";
			link.l1 = "Ну, не так хорошо, как того хотелось бы. Есть основания полагать, что он долго не протянет, и его очень тревожит мысль, что он может не увидеть меня перед тем, как отправится в последний путь.";
			link.l1.go = "SharlieEpilog_Mary_3";
		break;

		case "SharlieEpilog_Mary_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Знаю, моя милая, знаю... Но такова жизнь. Я бы хотел, чтобы вы с ним познакомились. Пусть он увидит, какая удивительная у меня жена, и даст нам своё благословение.";
			link.l1.go = "SharlieEpilog_Mary_4";
		break;

		case "SharlieEpilog_Mary_4":
			dialog.text = "А что, если я ему не понравлюсь, да? Я ведь не дворянских кровей...";
			link.l1 = "Глупости, "+npchar.name+", ну как ты можешь ему не понравиться? Ты ведь чудо! Раз ты покорила моё сердце - покоришь и его.";
			link.l1.go = "SharlieEpilog_Mary_5";
		break;

		case "SharlieEpilog_Mary_5":
			dialog.text = "Ты правда так думаешь, дорогой? Тогда нам нужно отправиться к нему как можно скорее.";
			link.l1 = "Именно это я и собираюсь сделать. Я даже подыскал нам корабль. Мы отчаливаем через две недели.";
			link.l1.go = "SharlieEpilog_Mary_6";
		break;

		case "SharlieEpilog_Mary_6":
			dialog.text = "Корабль? Мы поплывём не на нашем судне?";
			link.l1 = "Нет, милая. Мы отправимся на пинасе '"+GetShipName("Ulysse")+"'. На нём я прибыл на Карибы - на нём и покину их.";
			link.l1.go = "SharlieEpilog_Mary_7";
		break;

		case "SharlieEpilog_Mary_7":
			dialog.text = "И ты не будешь капитаном?";
			link.l1 = "Рано или поздно мне всё равно пришлось бы отказаться от этой роли. Надеюсь, сейчас - лишь временно. Но, в любом случае, мне не помешает почувствовать, что ждёт меня в будущем.";
			link.l1.go = "SharlieEpilog_Mary_8";
		break;

		case "SharlieEpilog_Mary_8":
			dialog.text = "А как же наши офицеры? Мы ведь не сможем взять их всех с собой. Да и дожидаться тебя здесь они вряд ли станут.";
			link.l1 = "Кхм... Да, ты права. Придётся поговорить с каждым из них, и, скорее всего, попрощаться навсегда. Хотя это и будет непросто - учитывая то, через что нам пришлось пройти вместе.";
			link.l1.go = "SharlieEpilog_Mary_9";
		break;
			
		case "SharlieEpilog_Mary_9":
			dialog.text = "Возможно, стоит устроит устроить на прощание небольшой пир в таверне?";
			link.l1 = "Я тоже об этом думал, дорогая. Знаешь... пожалуй, ты права. Это и впрямь хорошая мысль.";
			link.l1.go = "exit";
			link.l2 = "Не думаю, что это хорошая идея. Обойдёмся без громких прощаний... Так, пожалуй, будет лучше для всех. Разве что, пригласим только самых верных друзей...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		case "SharlieEpilog_Helena_1":
			dialog.text = "...";
			link.l1 = "Дорогая, я хотел бы поговорить с тобой о моём отце.";
			link.l1.go = "SharlieEpilog_Helena_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_2":
			dialog.text = "Конечно, "+pchar.name+". Надеюсь, с ним всё в порядке?";
			link.l1 = "Не совсем. Он уже давно болен, и, боюсь, болезнь скоро возьмёт верх... Отец переносит всё это с большим мужеством. Единственное, что его по-настоящему тревожит - он может так и не увидеть меня снова. Я хочу навестить его... и познакомить тебя с ним. Получить его благословение на наш брак.";
			link.l1.go = "SharlieEpilog_Helena_3";
		break;

		case "SharlieEpilog_Helena_3":
			dialog.text = "Я буду счастлива познакомиться с ним, любимый. Когда мы отплываем?";
			link.l1 = "Через две недели. Но это ещё не всё. Мы отправимся не на нашем корабле. В Старый Свет нас доставит пинас '"+GetShipName("Ulysse")+"' - тот самый, который когда-то привёз меня сюда.";
			link.l1.go = "SharlieEpilog_Helena_4";
		break;

		case "SharlieEpilog_Helena_4":
			dialog.text = ""+pchar.name+", но ведь менять корабль перед дальним плаванием - плохая примета.";
			link.l1 = "Мы не будем менять корабль, дорогая. Мы будем пассажирами.";
			link.l1.go = "SharlieEpilog_Helena_5";
		break;

		case "SharlieEpilog_Helena_5":
			dialog.text = "Но... любимый, я не понимаю...";
			link.l1 = "Так нужно, "+npchar.name+". Рано или поздно мне придётся оставить капитанский пост. И я хочу заранее знать, с какими чувствами мне придётся столкнуться.";
			link.l1.go = "SharlieEpilog_Helena_6";
		break;

		case "SharlieEpilog_Helena_6":
			dialog.text = "Если ты так решил... Но как же наши офицеры? Мы ведь не сможем взять их всех с собой. Да и ждать тебя здесь они, скорее всего, не станут.";
			link.l1 = "Кхм... Да, ты права. Придётся поговорить с каждым из них, и, скорее всего, попрощаться навсегда. Хотя это и будет непросто - учитывая то, через что нам пришлось пройти вместе.";
			link.l1.go = "SharlieEpilog_Helena_7";
		break;
			
		case "SharlieEpilog_Helena_7":
			dialog.text = "Возможно, стоит устроит устроить на прощание небольшой пир в таверне?";
			link.l1 = "Я тоже об этом думал, дорогая. Знаешь... пожалуй, так и сделаем. Это и впрямь хорошая мысль.";
			link.l1.go = "exit";
			link.l2 = "Не думаю, что это хорошая идея. Обойдёмся без громких прощаний... Так, пожалуй, будет лучше для всех. Разве что, пригласим только самых верных друзей...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		// Диалог с Алонсо в таверне Сен-Пьера
		case "SharlieEpilog_AlonsoInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				dialog.text = "Кэп... Я уже поговорил с трактирщиком - он приготовил лучшее пойло, что у него имеется. Когда начнём?";
				link.l1 = "Прямо сейчас! Эй, трактирщик! Всем выпивку за мой счёт!";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_1";
			}
			else
			{
				dialog.text = "Кэп, вы обещались рассказать мне о том, как узнали о 'Улиссе'.";
				link.l1 = "Помню-помню. Эй, трактирщик! Лучшего рому за этот стол.";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_3";
			}
			link.l2 = "Рано, "+npchar.name+". У меня ещё есть неотложные дела.";
			link.l2.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_AlonsoInTavern";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_1":
			dialog.text = "...";
			link.l1 = "Ну что, дружище, зови остальных - покажем Сен-Пьеру, как гуляют настоящие морские волки!";
			link.l1.go = "SharlieEpilog_AlonsoInTavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_AlonsoInTavern_2":
			dialog.text = "Ха-ха! Кэп, вы не поверите - я уже их позвал!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_FrameInSea";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_3":
			dialog.text = "...";
			link.l1 = "За нас, "+npchar.name+". За госпожу удачу и за ветер, который наполняет наши паруса!";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		// На пинасе Улисс
		case "SharlieEpilog_Alonso_1":
			dialog.text = "Ну и погром мы устроили, кэп. Ха-ха. Кажется, от полного разорения таверну спасли лишь скудные запасы рома у трактирщика.";
			link.l1 = "Не напоминай, "+npchar.name+", мне только сейчас стало немного легче.";
			link.l1.go = "SharlieEpilog_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "SharlieEpilog_Alonso_2":
			dialog.text = "Как скажете, сударь "+pchar.lastname+". Ха-ха. Зато мы попрощались с Мартиникой по-королевски. Там ещё долго будут вспоминать ваш отъезд.";
			link.l1 = "Мне кажется, мы немного перегнули палку, когда посадили трактирщика в ялик и отправили его в Ле Франсуа за выпивкой.";
			link.l1.go = "SharlieEpilog_Alonso_2_1";
		break;
		
		case "SharlieEpilog_Alonso_2_1":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2)
				{
					dialog.text = "Ха-ха-ха. За него не беспокойтесь. За эти дни он заимел столько золота, что сможет плантацию купить, да ещё и титул в придачу.";
				}
			else
				{
					dialog.text = "Ха-ха-ха. За него не беспокойтесь. За эти дни он заимел столько золота, что сможет плантацию купить, да ещё и титул в придачу. Жаль, только что вы ни с кем из офицеров так и не поговорили. Нам будет их не хватать.";
				}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;
		
		case "SharlieEpilog_Alonso_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
				{
					sld = CharacterFromID("Helena");
					locCameraFromToPos(-8.97, 6.39, -12.78, true, -8.54, 4.94, -13.90);
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
				{
					sld = CharacterFromID("Mary");
					locCameraFromToPos(-3.62, 4.03, 2.30, true, -4.98, 2.62, 3.26);
					// locCameraFromToPos(-4.13, 4.23, 2.55, true, -5.71, 2.54, 3.58);
				}
				dialog.text = "Кажется, "+sld.name+" всё ещё сердится на вас за то, что вы пропали на полночи.";
			}
			else
			{
				dialog.text = "А вот с тем торговцем… там вы, капитан, и правда, переборщили.";
			}
			link.l1 = "Дьявол, и нужно же было нам с Жаном полезть в местный магазин…";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;
		
		case "SharlieEpilog_Alonso_4":
			dialog.text = "И как вас только не поймали? Вот было бы смеху - "+GetTitle(PChar, true)+" пойман при попытке кражи нескольких бутылок вина.";
			link.l1 = "Тебе смешно, "+npchar.name+", а я и половины всего не помню. Последний раз я так напивался... примерно... примерно никогда.";
			link.l1.go = "SharlieEpilog_Alonso_5";
			locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
		break;
		
		case "SharlieEpilog_Alonso_5":
			dialog.text = "Тогда с почином, кэп. Ха-ха. А мне понравилось. Я бы повторил. Когда, говорите, мы возвращаемся?";
			link.l1 = "Иди лучше посмотри, как там наши пожитки. Мы хоть всё забрали? Я спущусь позже - трюмный воздух мне уж точно сейчас не пойдёт на пользу.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_UlysseInSea_8");
		break;
		
		// диалог с Алонсо у горы золота
		case "SharlieEpilog_Alonso_11": // этап 1
			dialog.text = "...";
			link.l1 = "Только посмотри на это... здорово же корабль встряхнуло.";
			link.l1.go = "SharlieEpilog_Alonso_12";
			SharlieEpilog_GoldInTheDeck_1_1();
		break;
		
		case "SharlieEpilog_Alonso_12":
			dialog.text = "Здесь же целая чёртова куча золота, кэп!";
			link.l1 = "Я вижу, "+npchar.name+". Нужно всё это срочно спрятать в сундуки, пока команда не увидела. Им такие искушения ни к чему.";
			link.l1.go = "SharlieEpilog_Alonso_13";
		break;
		
		case "SharlieEpilog_Alonso_13":
			dialog.text = "Нет, не удержусь...";
			link.l1 = "Что?";
			link.l1.go = "exit";
			locCameraFromToPos(-1.28, 7.70, -10.26, true, 0.74, 5.42, -9.49);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_2");
		break;
			
		case "SharlieEpilog_Alonso_21": // этап 2
			dialog.text = "...";
			link.l1 = "Эй, ты чего это?";
			link.l1.go = "SharlieEpilog_Alonso_22";
			// SharlieEpilog_GoldInTheDeck_6();
		break;
		
		case "SharlieEpilog_Alonso_22":
			dialog.text = "...";
			link.l1 = "Ну-ка вставай. Нашёл время...";
			link.l1.go = "SharlieEpilog_Alonso_23";
		break;
		
		case "SharlieEpilog_Alonso_23":
			dialog.text = "Присоединяйтесь, кэп.";
			link.l1 = "Вставай, хватит дурака валять.";
			link.l1.go = "SharlieEpilog_Alonso_24";
		break;
		
		case "SharlieEpilog_Alonso_24":
			dialog.text = "Да расслабьтесь вы. Вам нужно это почувствовать.";
			link.l1 = "Ладно, чёрт с тобой. Ну-ка, подвинься.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_7");
		break;
		
		case "SharlieEpilog_Alonso_31": // этап 3
			dialog.text = "Всегда мечтал так сделать…";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_32";
			SharlieEpilog_GoldInTheDeck_10();
		break;
		
		case "SharlieEpilog_Alonso_32":
			dialog.text = "Великолепное чувство, не так ли, кэп?";
			link.l1 = "Ха-ха-ха. Вот так посетил Карибы - всего-то узнать, как у братца дела. Отец точно не такого поворота ожидал. Ха-ха!";
			link.l1.go = "SharlieEpilog_Alonso_33";
		break;
		
		case "SharlieEpilog_Alonso_33":
			dialog.text = "Сударь "+GetTitle(NPChar, false)+" "+pchar.lastname+"... Ха-ха! Вы помните, каким вы прибыли на архипелаг?";
			link.l1 = "Ещё как помню. Ха-ха. Даже не верится, что я когда-то был таким же франтом, как тот, что сейчас разгуливает по палубе. Столько всего пережито на этих проклятых Карибах… Интриги, нежить, братец Кукулькан…";
			link.l1.go = "SharlieEpilog_Alonso_34";
		break;
		
		case "SharlieEpilog_Alonso_34":
			dialog.text = "Вы чертовски везучий, кэп. Сколотить такое состояние - и при этом остаться в живых… удаётся не каждому.";
			link.l1 = "Да уж. Ладно, хватит прохлаждаться. Не ровён час - кто-нибудь и вправду заметит.";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_11");
		break;
		
		// диалоги в катсцене с брашпилем
		case "SharlieEpilog_windlass_1":
			dialog.text = "...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Послушай, дружище, не нравится мне предохранитель брашпиля на этом судне. Слишком уж он ненадёжный. Как бы кто-то ненароком его не сорвал.";
			}
			else
			{
				link.l1 = "Послушайте, капитан, не нравится мне предохранитель брашпиля на этом судне. Слишком уж он ненадёжный. Как бы кто-то ненароком его не сорвал.";
			}
			link.l1.go = "SharlieEpilog_windlass_2";
			locCameraFromToPos(-7.57, 9.68, -21.21, true, -9.79, 7.76, -20.01);
		break;
		
		case "SharlieEpilog_windlass_2":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Да брось, "+pchar.name+", на судне каждый знает, что…";
			}
			else
			{
				dialog.text = "Да бросьте, капитан. Кому в голову придёт...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_windlass_3");
		break;
		
		case "SharlieEpilog_windlass_3": // диалог Пикара и дворянина
			dialog.text = "Эй, ты, дубина... Какого дьявола ты творишь? Тебя не учили не совать свои кривые ходули куда не следует?";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_4";
			locCameraFromToPos(-10.28, 9.94, -22.90, true, -9.29, 7.86, -21.36);
			NPCsLookEachOther("SharlieEpilog_Pikar", "SharlieEpilog_Bernard_Clone");
			CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_Bernard_Clone"));
		break;
		
		case "SharlieEpilog_windlass_4":
			dialog.text = "...";
			link.l1 = "Полегче, не забывайтесь! Я дворянин, и не потерплю…";
			link.l1.go = "SharlieEpilog_windlass_5";
		break;
		
		case "SharlieEpilog_windlass_5":
			dialog.text = "На моём корабле ты никто. У моих матросов здесь прав больше чем у тебя. Так что или ты сидишь тихо и никому не мешаешь, или я лично вышвырну тебя за борт.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_6";
		break;
		
		case "SharlieEpilog_windlass_6": // диалог Пикара и Шарля
			dialog.text = "...";
			link.l1 = "Ха-ха-ха. Я как будто на себя посмотрел со стороны.";
			link.l1.go = "SharlieEpilog_windlass_7";
			SharlieEpilog_windlass_9_1();
		break;
		
		case "SharlieEpilog_windlass_7":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Ты о чём?";
				link.l1 = "Да, не важно, "+npchar.name+". Не будь так суров к нашему пассажиру. Ему ещё всё это в новинку. В конце концов, мы с тобой тоже не за один день морскими волками стали.";
			}
			else
			{
				dialog.text = "Вы о чём?";
				link.l1 = "Не придавайте значения, "+npchar.name+". И не судите вашего пассажира слишком строго. Ему всё это в новинку. В конце концов, мы с вами тоже не сразу морскими волками стали.";
			}
			link.l1.go = "SharlieEpilog_windlass_8";
		break;
		
		case "SharlieEpilog_windlass_8":
			dialog.text = "С его талантом он скорее на брашпиль намотается, чем моряком станет. Это надо же додуматься…";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Кто знает, кто знает. Я прибыл на архипелаг таким же беспечным, любознательным и заносчивым юнцом.";
			}
			else
			{
				link.l1 = "Кто знает. Я когда прибыл на архипелаг - был таким же беспечным, любознательным заносчивым юнцом.";
			}
			link.l1.go = "SharlieEpilog_windlass_9";
		break;
		
		case "SharlieEpilog_windlass_9":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Тоже мне, сравнил.\n"+
					"Погоди\n"+ 
					"Так ты видишь в нём себя? Ха-ха-ха. Вот тогда и бери его к себе на поруки. Я с ним нянчиться не стану.";
				link.l1 = "Я пригляжу за ним. Пока ты с него шкуру не спустил. Но за якорь пусть заплатит по полной.";
			}
			else
			{
				dialog.text = "Так вы в нём себя увидели? Ха-ха. Ну что ж, капитан, тогда берите его на поруки. Я с ним нянчиться не стану.";
				link.l1 = "Я пригляжу за ним. Пока вы с него шкуру не спустили. Но за якорь - пусть расплатится как положено.";
			}
			link.l1.go = "SharlieEpilog_windlass_10";
		break;
		
		case "SharlieEpilog_windlass_10":
			dialog.text = "Выбрать якорь. Ждём ветер. Держать прежний курс.";
			link.l1 = "...";
			link.l1.go = "exit";
			SharlieEpilog_windlass_10();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_1");
		break;
		
		// диалоги Старшего матроса и Алонсо		
		case "SharlieEpilog_AlonsoTrollingHighSailor_2": // Алонсо
			dialog.text = "";
			link.l1 = "Поднять якорь. Ловим ветер. Курс - на северо-восток.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_3";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_3": // Старший матрос
			dialog.text = "";
			link.l1 = "Якорь поднять! Кливер спустить - поймаем ветер. За работу...";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_4";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_4": // Алонсо
			dialog.text = "";
			link.l1 = "Что ты делаешь?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_5";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_5": // Старший матрос
			dialog.text = "";
			link.l1 = "Что ты делаешь?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_6";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_6": // Алонсо
			dialog.text = "";
			link.l1 = "Нет, что ты делаешь?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_7";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_7": // Старший матрос
			dialog.text = "";
			link.l1 = "Аргх... Что ты делаешь? Старший матрос дублирует команды капитана.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_8";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_8": // Алонсо
			dialog.text = "";
			link.l1 = "Вот старший матрос их и дублирует.";
			link.l1.go = "exit";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_2");
		break;
		
		// Шарль ругает Алонсо
		case "SharlieEpilog_AlonsoTrollingHighSailor_9":
			dialog.text = "...";
			link.l1 = "Отставить, Алонсо. Мы здесь просто пассажиры. Ты забыл?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_10";
			locCameraFromToPos(-8.00, 4.49, -1.91, true, -9.97, 2.64, -1.90);
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_10":
			dialog.text = "Кхм... Простите, кэп. Не удержался\nНо оно того стоило. Как будто в прошлом побывал.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_5");
		break;
		
		// Диалог Шарля с Пикаром о всяком (можно попасть в Поместье де Монпе)
		case "SharlieEpilog_PikarOnUliss":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.lastname+"... Чего изволите?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A"))
				{
					link.l1 = "Ну, дружище, как ты себя чувствуешь?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_A_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_B"))
				{
					if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
					{
						link.l2 = "Признайся, "+npchar.name+", ты ведь задумал податься в торговцы ещё тогда, когда решил отколоться от Тиракса?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
					else
					{
						link.l2 = "Признайся, "+npchar.name+", ты ведь задумал податься в торговцы ещё тогда, на плантации?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_C"))
				{
					link.l3 = "Я отчётливо помню, что со мной пытался поговорить какой-то посыльный. Но хоть убей - не припомню, по какому поводу. Тебе ничего об этом не известно?";
					link.l3.go = "SharlieEpilog_PikarOnUliss_C_1";
				}
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_E"))
				{
					link.l1 = "Вы уже бывали в Бордо, капитан?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_E_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_F"))
				{
					link.l2 = "Капитан, сказать по правде, я толком не помню, как мы покинули Мартинику. Мне должны были доставить важную почту от одного человека, но, похоже, я её так и не получил. К вам никто не обращался по этому поводу?";
					link.l2.go = "SharlieEpilog_PikarOnUliss_F_1";
				}
			}
			link.l4 = "Кажется, появился лёгкий ветерок. Пора расправлять паруса. (Выйти в море)";
			link.l4.go = "SharlieEpilog_PikarOnUliss_D_1";
			link.l5 = "Пока ничего. Я пойду.";
			link.l5.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_A_1":
			dialog.text = "Ха-ха... Как никогда прежде! Полон сил и здоровья.";
			link.l1 = "Неужели? А вид у тебя, как будто тебя акула пережевала.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_A = true;
		break;

		case "SharlieEpilog_PikarOnUliss_A_2":
			dialog.text = "Кто бы говорил. Ты и сам-то выглядишь, как пёс поколоченный.";
			link.l1 = "И чувствую себя так же. Ха-ха. Дьявол, я даже не помню, как и когда мы отчалили.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_3";
		break;

		case "SharlieEpilog_PikarOnUliss_A_3":
			dialog.text = "Эх, славная была пирушка. Только чертовски дорогая. Мои олухи чуть не спалили бордель - пришлось выложить мешок монет, чтобы замять скандал. Так что теперь эти болваны до конца жизни передо мной в долгу\nНу и как тебе в роли пассажира? Ещё не начал выть от тоски?";
			link.l1 = "Есть ощущение, будто я больше не держу собственную судьбу в своих руках. Но в то же время я чувствую странное облегчение. Как будто скинул с плеч ящик с ядрами.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_4";
		break;

		case "SharlieEpilog_PikarOnUliss_A_4":
			dialog.text = "Ха-ха. Так уж и быть, если тоска тебя одолеет - я готов взять тебя к себе офицером.";
			link.l1 = "Весьма великодушно с твоей стороны, но вынужден отказаться. На всех Карибах не найдётся столько рома, чтоб наши кутежи обеспечить.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_1":
			if (IsStateTitle()) 
			{
				dialog.text = "Не совсем, дружище. Мысль такая меня временами посещала, но я ей особо не внимал. Вернулась она ко мне второй раз, когда до моих ушей дошёл слушок - мол, вся шайка верных псов Тиракса бесследно сгинула. Все до одного - Тесак, Лысый, и даже та старая вонючая подстилка Лепрекон\nНу а когда я услышал, каких успехов добился ты - решил окончательно, что хватит с меня. Вечно головой за монеты рисковать не выйдет\nЗолота у меня хватает, чтобы никогда не пресмыкаться ни перед одним ублюдком в парике. Но расставаться с морем... к этому не был готов. Вот и решил сменить род деятельности.";
			} 
			else 
			{
				dialog.text = "Не совсем, дружище. Мысль такая меня временами посещала, но я ей особо не внимал. Вернулась она ко мне второй раз, когда до моих ушей дошёл слушок - мол, вся шайка верных псов Тиракса бесследно сгинула. Все до одного - Тесак, Лысый, и даже та старая вонючая подстилка Лепрекон\nНу а когда вражеские ядра едва не вышибли мне мозги дважды за бой - я решил окончательно, что хватит с меня. Вечно головой за монеты рисковать не выйдет\nЗолота у меня хватает, чтобы никогда не пресмыкаться ни перед одним ублюдком в парике. Но расставаться с морем... к этому не был готов. Вот и решил сменить род деятельности.";
			}
			link.l1 = "Тесак, Лысый, Лепрекон... Ты знаешь, куда они пропали?";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_B = true;
		break;

		case "SharlieEpilog_PikarOnUliss_B_2":
			dialog.text = "Нет, не знаю. И честно говоря - плевать мне, куда эти твари подевались. Хоть к чёрту под хвост.";
			link.l1 = "Примерно туда я их и отправил.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_3";
		break;

		case "SharlieEpilog_PikarOnUliss_B_3":
			dialog.text = "Так это ты истребил всю их компанию? Ну и ну! И Маркус тебе это простил?";
			link.l1 = "Он об этом не знает. И, скорее всего, никогда и не узнает.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_4";
		break;

		case "SharlieEpilog_PikarOnUliss_B_4":
			dialog.text = "Значит, чёрт побери, я вовремя их покинул, ха-ха. Ты, чего доброго, и мою башку не пощадил бы\nВот только одного я понять не могу - на кой чёрт это тебе понадобилось?";
			link.l1 = "Ты был прав - за жалкий кусок золота эти подонки удавятся, предадут, убьют кого угодно. Нас заманили в одно из подземелий, на Южном Мэйне, подсунув басню о несметных сокровищах. Это была тщательно продуманная ловушка, и эти чёртовы дуболомы заглотили наживку без раздумий. Вместо того чтобы добычу делить поровну - решили, что делиться не стоит, проще прикончить меня, и забрать всё себе.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_5";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_5":
			dialog.text = "И чёрта с два у них это вышло, ха-ха! Погоди-ка, а кто вообще эту ловушку устроил?";
			if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l1 = "Некий Зорро, испанский народный мститель - в отместку за Картахену. Тот, кто бы выжил в той бойне, должен был остаться в подземелье навеки - все выходы были заперты. Но ублюдку не повезло - мой офицер перехитрил его.";
			}
			else
			{
				link.l1 = "Некий Зорро, испанский народный мститель - в отместку за Картахену. Тот, кто выжил бы в этой адской бойне, должен был навсегда остаться в подземелье - все выходы были наглухо заперты. Мне удалось оттуда выбраться. Но очень дорогой ценой.";
			}
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_6";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_6":
			dialog.text = "По крайней мере, ты остался жив. И, надо думать, забрал всё золотишко, за которое едва не расплатился собственной шкурой?";
			link.l1 = "Никакого золота там не было. Это был позолоченный свинец...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_7";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_7":
			dialog.text = "...";
			link.l1 = "После этого всего я и решил уйти от Тиракса. Ты первый, кому я это рассказываю. Если не считать моих офицеров.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_8";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_8":
			dialog.text = "Не люблю говорить 'я же предупреждал', но... я ведь предупреждал.";
			link.l1 = "Останавливаться вовремя - не моя сильная сторона. Так что тебе придётся дать мне пару уроков.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_9";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_9":
			dialog.text = "Ты же меня знаешь - тебе, за пару кружек доброго рома я и про свой тайник с золотишком расскажу, хе-хе.";
			link.l1 = "А вот от меня такой щедрости не жди, ха-ха-ха. Хватит с тебя и твоих запасов.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_C_1":
			dialog.text = "Известно. Он пытался всучить тебе письма - то ли от какого-то Бена, то ли от Бенедикта. Только ты рявкнул, что не знаешь никакого Бена и пригрозил вышвырнуть его из таверны, если он продолжит портить нам веселье.";
			link.l1 = "Дьявол... Похоже, это были письма от аббата Бенуа. Важные письма.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_C = true;
		break;

		case "SharlieEpilog_PikarOnUliss_C_2":
			dialog.text = "Ну, тогда хорошо, что я их забрал. Хе-хе.  Нутром почуял, что щенок тот не ошибся адресатом. Держи.";
			link.l1 = "Ты меня здорово выручил, "+npchar.name+", спасибо.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_3";
		break;

		case "SharlieEpilog_PikarOnUliss_C_3":
			dialog.text = "Одного 'спасибо' маловато, приятель. С тебя выпивка - и не абы какая, а лучшая, что водится в Бордо.";
			link.l1 = "Будет тебе выпивка, побирушка. Ром у нас, конечно, не ровня карибскому, зато вино... Такого ты точно ещё не пил.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_E_1":
			dialog.text = "Не приходилось...";
			link.l1 = "Завидую вам. Хотел бы снова увидеть Бордо, как в первый раз. Вы, скорее всего, предпочитаете ром, но всё же советую заглянуть на винную ярмарку возле ратуши. За наш кларет знатоки на Карибах готовы выложить целое состояние.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_E = true;
		break;

		case "SharlieEpilog_PikarOnUliss_E_2":
			dialog.text = "Благодарю за совет. Позволите вопрос?";
			link.l1 = "Разумеется.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_3";
		break;

		case "SharlieEpilog_PikarOnUliss_E_3":
			dialog.text = "Каково это - быть пассажиром после долгих лет у штурвала? Уже свыклись с новым положением?";
			link.l1 = "Хм... Меня не покидает ощущение, будто я больше не держу собственную судьбу в своих руках. Но в то же время я чувствую странное облегчение. Как будто скинул с плеч ящик с ядрами. Думаю, пока рано делать выводы.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_4";
		break;

		case "SharlieEpilog_PikarOnUliss_E_4":
			dialog.text = "Учитывая чёртов штиль, в который нас так удачно занесло, времени у вас будет хоть отбавляй.";
			link.l1 = "В хорошей компании и штиль не в тягость. А с компанией, капитан, надо признать, мне повезло.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_F_1":
			dialog.text = "Обращался. Посыльный от какого-то аббата. Всё забываю вам эти письма отдать. Вот, держите.";
			link.l1 = "Превосходно. Вы очень выручили меня, капитан. Благодарю вас.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_F = true;
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A")){dialog.text = "Твоя правда.";}
			else {dialog.text = "Ваша правда.";}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_D_2";
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_2":
			dialog.text = "Ветер с правого борта! Ставь всё, от фока до бизани! Полный ход!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InEstateDeMonpe";
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(CharacterFromID("SharlieEpilog_Pikar"), "quest", "quest10");
		break;
		
		case "SharlieEpilog_InEstateDeMonpe":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe");
		break;
		
		//Матрос 1 на верхней палубе
		case "SharlieEpilog_Sailor_1":
			dialog.text = "Отличный клинок, "+GetTitle(NPChar, true)+". Дадите посмотреть?";
			link.l1 = "Возможно, как-нибудь в другой раз.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_1";
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer05.wav");
		break;
		
		//Матрос 2 на верхней палубе
		case "SharlieEpilog_Sailor_2":
			dialog.text = "Когда уже эти склянки? Я скоро язык проглочу.";
			link.l1 = "Терпение, матрос.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-07.wav");
		break;
		
		//Матрос 3 на орудийной палубе
		case "SharlieEpilog_Sailor_3":
			dialog.text = "Видали, какая крыса пробежала? Клянусь, в жизни не видал таких огромных!";
			link.l1 = "Мда...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_3";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-04.wav");
		break;
		
		//Матрос 4 на орудийной палубе
		case "SharlieEpilog_Sailor_4":
			dialog.text = "Что же мне теперь делать, месье? Я так набрался, что и не помню, как оказался на этом судне. Я ведь и близко не моряк... А дома - жена, двое детишек.";
			link.l1 = "Меньше пить надо было. А теперь уж поздно - придётся стать моряком.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_4";
			PlaySound("Voice\" + LanguageGetLanguage() + "\Ransack_2.wav");
		break;
		
		//Старший матрос
		case "SharlieEpilog_HighSailor_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.lastname+". Для нас честь видеть вас на борту нашего судна.";
			link.l1 = "Вы весьма учтивы, месье старший матрос. Вежливость - не самое распостранённое качество среди бывалых морских волков. Но не будем смущать команду - мы ведь не при дворе Его Величества. Обращайся ко мне просто: капитан.";
			link.l1.go = "SharlieEpilog_HighSailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;

		case "SharlieEpilog_HighSailor_2":
			dialog.text = "Ну, моряком я стал не так давно. Раньше я был писарем у господина Левассера. А когда его… кхм… устранили, пришёл новый губернатор. В узких кругах быстро стало известно, каким негодяем оказался сеньор де Рене де Буадуфле де Летр. Тогда я понял: нормальной работы мне больше не найти. Люди будут думать, что я всё знал - и молчал.";
			link.l1 = "А это было не так?";
			link.l1.go = "SharlieEpilog_HighSailor_3";
		break;

		case "SharlieEpilog_HighSailor_3":
			dialog.text = "Разумеется, нет. У меня никогда не было привычки лезть не в свои дела. К тому же, Левассер жестоко наказывал за любопытство.";
			link.l1 = "В это я охотно верю.";
			link.l1.go = "SharlieEpilog_HighSailor_4";
		break;

		case "SharlieEpilog_HighSailor_4":
			dialog.text = "Так вот, когда вы его устранили, я записался матросом на первое попавшееся пиратское судно. И, как ни странно, довольно быстро освоился и преобразился. Даже смог завоевать уважение среди самых отчаянных головорезов. Но то, чем они занимались... Мне было не по душе. Так я оказался здесь.";
			link.l1 = "Значит, ты знал о моём участии в судьбе Левассера?";
			link.l1.go = "SharlieEpilog_HighSailor_5";
		break;

		case "SharlieEpilog_HighSailor_5":
			dialog.text = "Разумеется, капитан. И я рад, что вы избавили мир от этого чудовища. Заодно вытащили меня из моей затхлой каморки. Заставили взглянуть на свою жизнь по-новому.";
			link.l1 = "Удивительно, как тесен этот мир...";
			link.l1.go = "SharlieEpilog_HighSailor_6";
		break;

		case "SharlieEpilog_HighSailor_6":
			dialog.text = "Пусть это и звучит противоречиво, но мир настолько же мал, насколько он огромен.";
			link.l1 = "Забавно. Никогда об этом не задумывался.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
		break;
		
		case "SharlieEpilog_HighSailor_7":
			dialog.text = "Капитан "+pchar.lastname+"... Чудесный сегодня вечер, не правда ли?";
			link.l1 = "Пожалуй. Сделать его ещё лучше мог бы только умеренный ветер с северо-запада.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;
		
		//Диалог с боцманом Моко
		case "SharlieEpilog_Moko_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Капитан "+pchar.lastname+"...";
				link.l1 = "Вообще-то… Впрочем, не важно. Я тебя помню! Тебя зовут Моко. Это ведь ты осушил целый бочонок рома за один раз?";
				link.l1.go = "SharlieEpilog_Moko_2";
			}
			else
			{
				dialog.text = "Чего вам… месье?";
				link.l1 = "Не каждый день встретишь такого здоровяка. Как тебя зовут?";
				link.l1.go = "SharlieEpilog_Moko_4";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Kapitani Korabley-07.wav");
		break;

		case "SharlieEpilog_Moko_2":
			dialog.text = "Я... И проснулся только через два дня.";
			link.l1 = "Другой бы на твоём месте не прожил и пары часов. Если ты дерёшься так же, как пьёшь - Жану чертовски повезло с боцманом.";
			link.l1.go = "SharlieEpilog_Moko_3";
		break;

		case "SharlieEpilog_Moko_3":
			dialog.text = "Как и мне повезло с капитаном. Благодаря ему я обрёл свободу. И благодаря вам. Гнил бы я на плантациях, если бы вы не выручили Жана.";
			link.l1 = "Это было интересное приключение. И я рад, что оно закончилось лучше, чем могло бы.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_4":
			dialog.text = ""+npchar.name+". Я боцман на этом корабле.";
			link.l1 = "Ха-ха, хотел бы я взглянуть на того, кто рискнёт тебе перечить. Давно служишь у капитана?";
			link.l1.go = "SharlieEpilog_Moko_5";
		break;

		case "SharlieEpilog_Moko_5":
			dialog.text = "Несколько лет. Я многим ему обязан. Если бы не он, я бы сгнил на...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Moko_6";
		break;

		case "SharlieEpilog_Moko_6":
			dialog.text = "...";
			link.l1 = "Ты хотел сказать - на плантации?";
			link.l1.go = "SharlieEpilog_Moko_7";
		break;

		case "SharlieEpilog_Moko_7":
			dialog.text = "...";
			link.l1 = "Брось, "+npchar.name+", ты, конечно, вправе мне ничего не рассказывать, но, если ты ещё не заметил, я не из тех чистоплюев в париках. Капитан выкупил тебя?";
			link.l1.go = "SharlieEpilog_Moko_8";
		break;

		case "SharlieEpilog_Moko_8":
			dialog.text = "Мы сбежали вместе. С плантации в Маракайбо. Без Жана у нас бы ничего не вышло. С тех пор я у него в команде. Сначала матросом, а теперь - я боцман.";
			link.l1 = "Капитан был в рабстве? Никогда бы не подумал. Впрочем, и в моём шкафу найдётся пара скелетов. Рад, что вырвались из-под испанского сапога, "+npchar.name+". Ну, и каково тебе быть моряком?";
			link.l1.go = "SharlieEpilog_Moko_9";
		break;

		case "SharlieEpilog_Moko_9":
			dialog.text = "Будто до этого и не жил. Море - теперь мой дом.";
			link.l1 = "Вот тут я тебя понимаю, мой друг. Как никто другой.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_repeat":
			dialog.text = "Капитан "+pchar.lastname+"... Чем могу помочь?";
			link.l1 = "Благодарю, "+npchar.name+", пока мне ничего не нужно.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		//Диалог с дворянином Бернардом
		case "SharlieEpilog_Bernard_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! Как же я рад видеть на этом судне хоть одно разумное лицо. Эти... матросы... это варвары.";
			link.l1 = "Я бы на вашем месте не стал так выражаться на чужом корабле. Не знаю, как вы попали на Карибы, но здесь, знаете ли, действуют иные законы. Вам стоит проявлять уважение к команде.";
			link.l1.go = "SharlieEpilog_Bernard_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;

		case "SharlieEpilog_Bernard_2":
			dialog.text = "Уважение? К ним? Да это же дикари! Я дворянин, "+GetTitle(NPChar, true)+", я привык к порядку, к обслуживанию, к... цивилизации! Пусть только попробуют мне перечить - мой отец их...";
			link.l1 = "Ваш отец узнает, что вы умерли от лихорадки в пути. И вряд ли сможет доказать обратное.";
			link.l1.go = "SharlieEpilog_Bernard_3";
		break;

		case "SharlieEpilog_Bernard_3":
			dialog.text = "Будь проклят этот полковник Фокс! Всё из-за него! Ради его дочери я пересёк океан, пожертвовал комфортом, терпел эти косые взгляды, эту ужасную еду, это... раскачивание! А теперь ещё и плыву на каком-то чужом судне!";
			link.l1 = "Полковник Фокс…";
			link.l1.go = "SharlieEpilog_Bernard_4";
		break;

		case "SharlieEpilog_Bernard_4":
			dialog.text = "Вы знакомы с ним, "+GetTitle(NPChar, true)+"?";
			link.l1 = "Кхм... Я слышал о нём.";
			link.l1.go = "SharlieEpilog_Bernard_5";
		break;

		case "SharlieEpilog_Bernard_5":
			dialog.text = "Ну, значит, вы не многое потеряли. Этот человек - воплощение слепого солдатского упрямства и предрассудков.";
			link.l1 = "Он военный...";
			link.l1.go = "SharlieEpilog_Bernard_6";
		break;

		case "SharlieEpilog_Bernard_6":
			dialog.text = "Именно! И этим всё сказано. Когда я явился, чтобы просить о встрече с его дочерью, знаете что он сделал? Знаете? Выставил меня за дверь! Без единого слова!";
			link.l1 = "Но вы, видимо, не отступили?";
			link.l1.go = "SharlieEpilog_Bernard_7";
		break;

		case "SharlieEpilog_Bernard_7":
			dialog.text = "Разумеется! Я добивался приёма целую неделю! Я унижался! Я даже... предлагал взятку страже! В конце концов, мне удалось проскользнуть к нему, без приглашения. Просто хотел поговорить!";
			link.l1 = "Не думаю, что он этому обрадовался.";
			link.l1.go = "SharlieEpilog_Bernard_8";
		break;

		case "SharlieEpilog_Bernard_8":
			dialog.text = "Обрадовался? О, он устроил форменную истерику! Меня выставили, запретили приближаться к резиденции, конфисковали отцовский корабль, а потом и вовсе запретили всем английским капитанам брать меня на борт! Пришлось искать французское судно на Мартинике... Это был кошмар.";
			link.l1 = "Кажется, вы его сильно разозлили.";
			link.l1.go = "SharlieEpilog_Bernard_9";
		break;

		case "SharlieEpilog_Bernard_9":
			dialog.text = "Он всегда был против меня. Его любимая фраза: 'Дочь офицера - жена офицера'. Вас, "+GetTitle(NPChar, true)+", он счёл куда более подходящей партией.";
			link.l1 = "Возможно, на этот раз у него были и иные причины...";
			link.l1.go = "SharlieEpilog_Bernard_10";
		break;

		case "SharlieEpilog_Bernard_10":
			dialog.text = "...";
			link.l1 = "Значит, вы прибыли сюда, чтобы повидаться с возлюбленной.";
			link.l1.go = "SharlieEpilog_Bernard_11";
		break;

		case "SharlieEpilog_Bernard_11":
			dialog.text = "Да. Я не получил от неё ни строки с тех пор, как она покинула Европу. Уверен, её отец попросту перехватывает письма. Она не могла меня забыть! Конечно, она была сдержанна в отношении меня... даже холодна... Но я не верю, что она вычеркнула меня из своей жизни.";
			link.l1 = "Сочувствую вам, месье. Душевные раны лечатся куда труднее, чем телесные. Подождите... Почему, вы, англичанин, направляетесь в Бордо?";
			link.l1.go = "SharlieEpilog_Bernard_12";
		break;

		case "SharlieEpilog_Bernard_12":
			dialog.text = "Я не намерен возвращаться домой с позором. Придётся погостить у дяди в Бордо, пока всё не уляжется. Впрочем, его поместье, куда просторнее и элегантнее нашего. Да и прислуга обучена получше.";
			link.l1 = "Что ж, пожалуй, это не худший выход. Возможно, вы даже присмотрите себе другую избранницу. Бордо весьма богат на юных прелестниц, уж поверьте.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
		break;
		
		case "SharlieEpilog_Bernard_repeat":
			dialog.text = "Когда мы, наконец, прибудем, "+GetTitle(NPChar, true)+"? Я невыносимо страдаю в окружении всех этих... джентльменов. Мне просто необходимо срочно принять ванну.";
			link.l1 = "Боюсь, ближайшие два месяца вам остаётся только мечтать о ней.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;
		
		//Диалог с Книппелем на корабле Улисс
		case "SharlieEpilog_Knippel_1":
			dialog.text = "Чёртов штиль, книппель бы его побрал.";
			link.l1 = "Не ворчи, "+npchar.name+", рано или поздно ветер подымется.";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "А что делать до тех пор, сэр? Я даже ревизию пушек сделать не могу... Мы ведь на чужом корабле.";
			link.l1 = "Попробуй просто отдохнуть. Не всё же работать.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		case "SharlieEpilog_Knippel_repeat":
			dialog.text = "Проклятый штиль...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		//Диалог с Лонгвэем на корабле Улисс
		case "SharlieEpilog_Longway_1":
			dialog.text = "Неплохой корабль, господин капитан. Вы тоже так думать?";
			link.l1 = "Даже лучше, чем Мейфенг?";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = "Для "+npchar.name+" нет корабль лучше, чем Мейфенг. Этот корабль никогда не пойти так круто к ветру, как он.";
			link.l1 = "Спокойно, "+npchar.name+", я же пошутил. Конечно, Мейфенг - вне конкуренции. Но и Уллисс - хорошее судно. Добротное.";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = ""+npchar.name+" хотеть стать за штурвал. Почувствовать, как корабль слушать руку...";
			link.l1 = "Увы, мой друг, это чужое судно. Лучше предложи вон тому здоровяку поупражняться в фехтовании. Вам обоим это пойдёт на пользу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		case "SharlieEpilog_Longway_repeat":
			dialog.text = "С какой скорость мы смочь пойти, если ветер будет попутный?";
			link.l1 = "Этого я тебе точно сказать не могу, "+npchar.name+". Лучше спроси у их штурмана.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		//Диалог с Тонзагом на корабле Улисс
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "Видал, какой гигант тут за боцмана? Говорят, он одной рукой может кокос раздавить.";
			link.l1 = "Ха-ха. А ты, смотрю, его побаиваешься?";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "С чего бы это? Размер - это не главное. Ещё и не таких разделывал.";
			link.l1 = "Тогда может предложишь ему кулачный бой? Один на один - по-честному.";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "Аргх...";
			link.l1 = "Что-то ты побледнел. Ха-ха. Ну нет - так нет. Побережём твои не такие уж молодые кости.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		case "SharlieEpilog_Tonzag_repeat":
			dialog.text = "В этих водах рыбы - хоть лодкой черпай, а эти бездельники и сеть закинуть не соизволили.";
			link.l1 = "Поговори с их боцманом. Думаю, он оценит твоё замечание, хе-хе.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		//Диалог с Тичингиту, охраняющим золото
		case "SharlieEpilog_Tichingitu_21":
			dialog.text = "Золото в безопасности, капитан "+pchar.name+". Тичингиту надёжно его охранять.";
			link.l1 = "Спасибо, друг. Алонсо скоро сменит тебя.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tichingitu_21";
		break;
		
		//Диалог с Книппелем, охраняющим золото
		case "SharlieEpilog_Knippel_21":
			dialog.text = "Книппель мне в грот, сэр, на этом корыте больше крыс, чем я видел за всю свою жизнь.";
			link.l1 = "Корабль долго стоял в порту, без должного присмотра. Новая команда скоро избавится от них.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_21";
		break;
		
		//Диалог с Лонгвэем, охраняющим золото
		case "SharlieEpilog_Longway_21":
			dialog.text = "Лонгвэй слышать шум цепи. Капитан бросить якорь?";
			link.l1 = "Это наш пассажир сорвал предохранитель. Ветер пока совсем слаб, но, надеюсь, это ненадолго.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_21";
		break;
		
		//Диалог с Тонзагом, охраняющим золото
		case "SharlieEpilog_Tonzag_21":
			dialog.text = "Да, чёрт побери... Я бы сейчас не отказался от кружечки забористого рома.";
			link.l1 = "Скоро ужин, потерпи. Алонсо сменит тебя.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_21";
		break;
		
		//Диалог с Мэри перед походом в каюту
		case "SharlieEpilog_Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", любимая, как ты себя чувствуешь?";
			link.l1.go = "SharlieEpilog_Mary_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_12":
			dialog.text = "...";
			link.l1 = "Брось, дорогая, ты серьёзно обиделась на меня из-за того, что я ушёл в магазин за вином?";
			link.l1.go = "SharlieEpilog_Mary_13";
		break;

		case "SharlieEpilog_Mary_13":
			dialog.text = "В магазин за вином? Ты ведь мог хотя бы предупредить! Откуда мне знать, что ты был не в борделе - с какой-нибудь… или со всеми сразу?!";
			link.l1 = "Милая, стал бы я так рисковать? У меня самая красивая, умная и безумно ревнивая жена на всём архипелаге. Неужели я стал бы размениваться на каких-то дешёвых портовых девок?";
			link.l1.go = "SharlieEpilog_Mary_14";
		break;

		case "SharlieEpilog_Mary_14":
			dialog.text = "Ты хотя бы мог слово мне сказать, да! Я сидела там и…";
			link.l1 = "Обещаю, в следующий раз я не просто сообщу тебе - я возьму тебя с собой. А сейчас… мне вдруг стало интересно, всё ли в порядке с мебелью в капитанской каюте. Особенно с кроватью. Проверим?";
			link.l1.go = "SharlieEpilog_Mary_15";
		break;

		case "SharlieEpilog_Mary_15":
			dialog.text = ""+pchar.name+"... А если кто-нибудь войдёт?\nХм-м… теперь мне хочется этого ещё больше.";
			link.l1 = "Тогда не будем терять ни секунды.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Элен перед походом в каюту
		case "SharlieEpilog_Helena_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", любимая, как ты себя чувствуешь?";
			link.l1.go = "SharlieEpilog_Helena_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_12":
			dialog.text = "...";
			link.l1 = "Брось, дорогая, ты серьёзно обиделась на меня из-за того, что я ушёл в магазин за вином?";
			link.l1.go = "SharlieEpilog_Helena_13";
		break;

		case "SharlieEpilog_Helena_13":
			dialog.text = "Мог бы и меня с собой взять. Или думаешь, справилась бы хуже, чем твои подельнички?";
			link.l1 = "Думаю, ты без труда затмила бы их. Но тогда бы я думал вовсе не о вине.";
			link.l1.go = "SharlieEpilog_Helena_14";
		break;

		case "SharlieEpilog_Helena_14":
			dialog.text = "А о чём же?";
			link.l1 = "О том, чтобы уединиться с тобой прямо там… И эта мысль не даёт мне покоя прямо сейчас.";
			link.l1.go = "SharlieEpilog_Helena_15";
		break;

		case "SharlieEpilog_Helena_15":
			dialog.text = "Вот как? И где же ты собрался спрятаться от любопытных глаз?";
			link.l1 = "В каюте капитана. Полагаю, нам следует проверить его кровать на прочность.";
			link.l1.go = "SharlieEpilog_Helena_16";
		break;

		case "SharlieEpilog_Helena_16":
			dialog.text = "Ха-ха. А что, если капитан нас застанет?\nХотя… одна эта мысль заставляет моё сердце биться быстрее.";
			link.l1 = "Тогда не будем терять времени!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Мэри в каюте
		case "SharlieEpilog_Mary_21":
			dialog.text = "Это было прекрасно, мой капитан...\nУ меня есть новость для тебя.";
			link.l1 = "Новость? Я весь внимание.";
			link.l1.go = "SharlieEpilog_Mary_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Mary_22":
			dialog.text = ""+pchar.name+"... У нас будет ребёнок. Я беременна, да.";
			link.l1 = "Любимая... Это правда?";
			link.l1.go = "SharlieEpilog_Mary_23";
		break;

		case "SharlieEpilog_Mary_23":
			dialog.text = "Ты станешь отцом, "+pchar.name+"!";
			link.l1 = ""+npchar.name+"... Это невероятно!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Mary_31":
			dialog.text = "Ты рад, любимый?";
			link.l1 = "Рад? Ты шутишь? Чёрт возьми, да я самый счастливый человек на свете! Но... почему ты не рассказала мне раньше?";
			link.l1.go = "SharlieEpilog_Mary_32";
		break;

		case "SharlieEpilog_Mary_32":
			dialog.text = "Чтобы сорвать отплытие? Я очень хочу встретиться с твоим отцом, "+pchar.name+".";
			link.l1 = ""+npchar.name+"... Я люблю тебя!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		//Диалог с Элен в каюте
		case "SharlieEpilog_Helena_21":
			dialog.text = "Ты был, как всегда, на высоте, милый. У меня есть для тебя новость.";
			link.l1 = "Новость? Я весь внимание.";
			link.l1.go = "SharlieEpilog_Helena_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Helena_22":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", шевалье де Монпе - ты станешь отцом.";
			link.l1 = "Это... это правда?";
			link.l1.go = "SharlieEpilog_Helena_23";
		break;

		case "SharlieEpilog_Helena_23":
			dialog.text = "Такая же правда, как и то, что меня зовут "+npchar.name+". Не далее чем через полгода у нас родится ребёнок - маленький месье де Мор... или, быть может, мадемуазель.";
			link.l1 = "Элен... Это невероятно!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Helena_31":
			dialog.text = "...";
			link.l1 = "Так вот почему ты не стала пить с нами в честь отплытия! Но… почему ты не сказала мне раньше?";
			link.l1.go = "SharlieEpilog_Helena_32";
		break;

		case "SharlieEpilog_Helena_32":
			dialog.text = "Я боялась, что ты решишь не рисковать и останешься на архипелаге. Мне хотелось, чтобы ты выполнил просьбу отца. Да и... я очень хочу познакомиться с ним сама.";
			link.l1 = ""+npchar.name+"… Я люблю тебя!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		// Диалог с Пикаром
		case "SharlieEpilog_PikarInCabin_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Так-так… И что мы тут делаем? Маленьких гасконцев?";
				link.l1 = "Ха-ха-ха! У меня будет сын, "+npchar.name+"! Я стану отцом!";
				link.l1.go = "SharlieEpilog_PikarInCabin_1_1";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.lastname+". Вам не кажется, что использовать капитанскую каюту без ведома капитана - перебор, даже для человека вашего ранга?";
				link.l1 = "Прошу прощения, капитан. Но у меня есть веская причина! Я стану отцом!";
				link.l1.go = "SharlieEpilog_PikarInCabin_12";
			}
			SharlieEpilog_PikarInCabin_camera_2();
		break;
		
		case "SharlieEpilog_PikarInCabin_1_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_2":
			dialog.text = "Или дочь!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_2_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_2_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_3", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_3":
			dialog.text = "И ты скрывал это от меня, негодяй? А я ведь считал тебя своим другом!";
			link.l1 = "Я сам только узнал! Представляешь? Я! Стану! Отцом!";
			link.l1.go = "SharlieEpilog_PikarInCabin_4";
		break;

		case "SharlieEpilog_PikarInCabin_4":
			dialog.text = "Ха-ха-ха! Да ты и впрямь счастлив, дружище! Впервые вижу тебя таким\nНу, вы тут поворкуйте ещё, а я приготовлю пушки к праздничному залпу. Дашь мне знать, когда будешь готов отдать приказ.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;

		case "SharlieEpilog_PikarInCabin_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				sld = CharacterFromID("Mary");
			}
			dialog.text = "Ха… Поверьте, я догадывался, зачем вы сюда заглянули.";
			link.l1 = "Да нет же! "+sld.name+" беременна! У меня будет сын!";
			link.l1.go = "SharlieEpilog_PikarInCabin_12_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_12_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_13":
			dialog.text = "Или дочь!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_13_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_13_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_14", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_14":
			dialog.text = "Кхм... Что ж, от всей души поздравляю!\nЯ распоряжусь - дадим праздничный залп из всех орудий. Сообщите, когда будете готовы отдать приказ.\nА пока... каюта - в вашем распоряжении.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;
		
		// Диалог с Пикаром после интима с женой
		case "SharlieEpilog_PikarZalp_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Кхе-кхе... Ну, папаша... вижу, вы захотели сразу сделать ещё одного наследника, а?";
				link.l1 = "Ха-ха! Будь моя воля - я бы целую дюжину сразу сделал! Ну, дружище, дадим залп со всех орудий?";
				link.l1.go = "SharlieEpilog_PikarZalp_2";
				link.l2 = "Боюсь, дружище, это так не работает. Но мы старались.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"...";
				link.l1 = "Ну что, капитан, дадим залп из всех орудий?";
				link.l1.go = "SharlieEpilog_PikarZalp_3";
				link.l2 = "Не сейчас.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_PikarZalp_1";
		break;
		
		case "SharlieEpilog_PikarZalp_2":
			dialog.text = "Команда только этого и ждёт! Приказывайте, "+GetTitle(NPChar, true)+".";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_3":
			dialog.text = "Команда готова. Приказывайте.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_final":
			dialog.text = "...";
			link.l1 = "Канониры! Со всех орудий! Пли!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_ZalpInSea");
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(pchar, "quest", "quest10");
			CharacterTurnToLoc(npchar, "quest", "quest10");
		break;
		
		// Диалог с отцом в поместье де Монпе
		case "SharlieEpilog_HenriDeMonper_1":
			NextMonth = GetDataMonth() + 2;
			if (NextMonth == 13) NextMonth = 1;
			else if (NextMonth == 14) NextMonth = 2;
			Month = XI_ConvertString("MonthVoc_" + NextMonth);
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.lastname+"... Как же я рад тебя видеть, сын!";
			if (GetDataMonth() >= 4 && GetDataMonth() <= 10)
			{
				link.l1 = "Отец... Не верится, что я снова дома... Я уж и забыл, как выглядит снег. Кажется, здесь совсем ничего не изменилось...";
			}
			else
			{
				link.l1 = "Отец... Не верится, что я снова дома... Кажется, в эту честь даже снег решил пойти. В "+month+". Здесь совсем ничего не изменилось...";
			}
			link.l1.go = "SharlieEpilog_HenriDeMonper_2";
			locCameraFromToPos(-8.76, 7.86, 0.75, true, -7.41, 6.11, 0.18);
			Achievment_Set("ach_CL_202");
		break;
		
		case "SharlieEpilog_HenriDeMonper_2":
			dialog.text = "А вот о тебе нельзя сказать того же! Твоя выправка, походка, шрамы\n"+
							"Нет, передо мной уже не тот избалованный мальчишка, которого я провожал в дальние края.";
			link.l1 = "На карибах быстро взрослеешь, отец. Но об этом мы ещё успеем поговорить. Расскажите лучше, как ваше здоровье? Надеюсь, болезнь повернула вспять, раз вы стоите передо мной в полном боевом облачении?";
			link.l1.go = "SharlieEpilog_HenriDeMonper_3";
		break;
		
		case "SharlieEpilog_HenriDeMonper_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				dialog.text = "Увы, "+pchar.name+", она лишь крепче вцепилась в моё горло. Но разве я мог встретить своего любимого сына в обыденном наряде? Для меня это великий день, "+pchar.name+"\n"+
				"Кажется, ты должен меня кое с кем познакомить.";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_10");
			}
			else
			{
				dialog.text = "Увы, " + pchar.name + ", её хватка с годами лишь становиться сильнее. Но разве я мог встретить своего любимого сына в обыденном наряде? Для меня это великий день, "+pchar.name+"\n"+ 
				"Вижу, ты прибыл не один\n"+
				"Вы, должно быть, проголодались с дороги? Сюзанна приготовила гусиную печень по твоему любимому рецепту!\n"+
				"Прошу к столу - по дороге и познакомишь нас!";
				link.l1 = "Признаюсь, я уловил этот аромат ещё на подходе к поместью!";
				link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "...";
			link.l1 = "Отец, позвольте представить вам мою жену - "+sld.name+" "+pchar.lastname+". "+sld.name+", это мой отец - шевалье "+GetCharacterName("Henri")+" "+GetCharacterName("de Monper")+".";
			link.l1.go = "SharlieEpilog_HenriDeMonper_5";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
				dialog.text = ""+pchar.name+", я очарован! Твоя избранница вовсе не похожа на избалованную светскую даму, к коим мы здесь привыкли. Смею предположить, что она столь же уверенно управляется с кораблём, как и с сердцем моего сына.";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_1";
				CharacterTurnByChr(npchar, sld);
			}
			else
			{
				sld = CharacterFromID("Mary");
				dialog.text = "Для меня большое счастье познакомиться с вами, сударыня. Смею вас заверить, у моего сына превосходный вкус!";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_1";
				CharacterTurnByChr(npchar, sld);
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2":
			dialog.text = "Я польщена, шевалье! Вы правы, я и правду способна удержать штурвал даже в жестокий шторм. Однако, что касается сердца вашего сына - управлять ним нет нужды. Мы едины в наших целях и стремлениях.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_2_1";
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_3":
			dialog.text = "Аббат Бенуа охарактеризовал вас как девушку мудрую и отважную - и, похоже, он не преувеличил. Я счастлив, что "+pchar.name+" нашёл в тебе не только супругу, но и равную по духу спутницу\n"+
			"Вы, должно быть, проголодались с дороги? Сюзанна приготовила гусиную печень по твоему любимому рецепту!\n"+
			"Что ж, прошу всех к столу! А по пути, надеюсь, мы все познакомимся поближе.";
			link.l1 = "Признаюсь, я уловил этот аромат ещё на подходе к поместью!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2":
			dialog.text = "Я рада с вами познакомиться, шевалье! "+pchar.name+" много о вас рассказывал, и я представляла вас именно таким, да!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_2_1";
			CharacterTurnByChr(pchar, npchar);
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_3":
			sld = CharacterFromID("Mary");
			dialog.text = ""+pchar.name+", я очарован! Твоя избранница вовсе не напоминает напудренных светских дам - и в этом её истинное достоинство\n"+
			"Мне кажется, ты выбрал прекрасную розу вместо изнеженных, капризных лилий.";
			link.l1 = "Дикую розу, отец… "+sld.name+"  - истинное сокровище. Уверен, вы согласитесь со мной, когда узнаете её ближе.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_4";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_4":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "ты познакомишь меня с остальными";
			else sStr = "ты представишь меня нашему гостю";
			dialog.text = "Тогда не будем оттягивать этот момент! Вы, должно быть, проголодались с дороги? Сюзанна приготовила гусиную печень по твоему любимому рецепту!\n"+
			"Прошу всех к столу! А по пути, надеюсь, "+sStr+"";
			link.l1 = "Признаюсь, я уловил этот аромат ещё на подходе к поместью!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			CharacterTurnByChr(CharacterFromID("HenriDeMonper"), pchar);
		break;
		
		case "SharlieEpilog_HenriDeMonper_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_14");
		break;
		
		case "SharlieEpilog_HenriDeMonper_7":
			dialog.text = "...";
			link.l1 = "Дорогая, ты просто обязана это попробовать - ничто не сможет сравниться с гусиной печенью, приготовленному по нашему фамильному рецепту! Он достался нам от дедушки - а ему его привезли в качестве подарка из одной Средиземноморской страны.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_15");
		break;
		
		// диалог на ужине в поместье де Монпе
		case "SharlieEpilog_InKitchenDeMonpe":
			dialog.text = "";
			link.l1 = "Не хотелось бы начинать пир с грустного, но мы, как семья, обязаны помнить тех, кто ушёл прежде нас. Я прошу вас поднять бокалы за Мишеля. Пусть Господь дарует покой его душе.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_2":
			dialog.text = "";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "добрых друзей";
				else sStr = "соратника";
				dialog.text = "";
				link.l1 = "Мне нужно так многое у тебя спросить, "+pchar.name+"... Но прежде позволь выслушать твою супругу и "+sStr+". Прошу вас, поведайте, как вы познакомились с Шарлем.";
			}
			else
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "твоих добрых друзей";
				else sStr = "твоего друга";
				dialog.text = "";
				link.l1 = "Мне нужно так многое у тебя спросить, "+pchar.name+"... Но прежде позволь выслушать "+sStr+". Прошу вас, поведайте, как вы познакомились с Шарлем.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		// if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
		
		case "SharlieEpilog_InKitchenDeMonpe_4":
			dialog.text = "";
			link.l1 = "Мне так же как и вам не терпится это послушать!";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Мне угрожала смертельная опасность... "+pchar.name+", как настоящий джентльмен, не позволил случиться беде! Он заступился за меня и разделался с негодяями, да!";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = ""+pchar.name+" вырвал меня из рук одного английского мерзавца, осмелившегося... похитить меня. Прибудь он хоть на час позже - мы бы так и не познакомились.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5_1":
			dialog.text = "";
			link.l1 = "Не сомневался, что он поступит как подобает истинному дворянину. Честь - не просто слово для нашего рода. Я горжусь тобой, сын.";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = ""+sld.name+" залезть в дом бледнолицый, чтобы найти еда. Бледнолицый застать "+sld.name+" - и отправить в тюрьма. Капитан " +pchar.name+ " прийти, вызволить "+sld.name+" из тюрьма. С тех пор "+sld.name+" служить капитан " +pchar.name+ " и быть верен до последний вздох.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6_1":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = "Отрадно знать, что мой сын не только благородный дворянин, но и человек доброго сердца. Я рад, что рядом с ним такие верные друзья, как вы, "+sld.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Капитан как-то зашёл в мой дом - в поисках работы. Я дал ему поручение, и он справился как надо. Начальнику он пришёлся по душе, и тот всё больше втягивал капитана в свои дела, а меня отправил к нему на корабль - приглядывать... А потом этот... мистер тихо снялся с якоря, книппель мне в бороду, и покинул архипелаг, не сказав капитану ни слова. Бросил его одного в каше, которую сам и заварил. Я предложил капитану свои услуги и хоть Ричард обошёлся с ним подло, книппель ему в корму, капитан меня не прогнал.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Лонгвэй и господин капитан работали на одного человека. Но тот человек предал Лонгвэя. Тогда Лонгвэй решил: больше служить этот человек. Господин капитан взял меня к себе на корабль, офицером, и сделать для Лонгвэя очень много.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Впервые мы пересеклись в таверне Бриджтауна: " +pchar.name+ " был в поисках дела, а я - надёжного исполнителя. Это знакомство стало лишь началом - за которым последовали события, что переплели наши пути. Я стал его офицером, и теперь без колебаний могу назвать его своим другом - человеком, ради которого я готов рискнуть жизнью.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7_2":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Разглядеть человека сквозь обстоятельства - умение редкое. Это, пожалуй, говорит о том, что мой сын не лишён рассудительности.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Я рад, что мой сын не бездушный военный, а настоящий командир, который умеет заботиться о своих соратниках.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Не каждый день услышишь такие слова. Пожалуй, это лучшее доказательство того, что мой сын - не только умелый моряк, но и хороший друг.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8":
			dialog.text = "";
			link.l1 = "Мы познакомились в Бордо. Кэп сел к нам на судно в качестве пассажира и мы доставили его на Мартинику. С тех пор - и до самой отправки сюда - я оставался голосом его команды и наблюдал, как " +GetFullName(pchar)+ " шаг за шагом становился тем, кем он является сейчас.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8_1":
			dialog.text = "";
			link.l1 = "Значит, вы знаете Шарля ещё тем несносным юнцом, что, по моему настоянию, покинул родной дом? Полагаю, месье, нам с вами будет о чём поговорить.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_9";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_9":
			dialog.text = "";
			link.l1 = "Мой дорогой "+pchar.name+", ты прошёл долгий и славный путь... Ты отправился в дикую саванну лишь за кроличьей шкуркой, но сразился со львом, и возвратился с триумфом, неся его шкуру на плечах. Теперь я, как никогда прежде, спокоен за судьбу нашего поместья и всех наших земель.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_10";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_10":
			dialog.text = "";
			link.l1 = "Мне не терпится как можно скорее передать тебе бразды правления над всеми делами нашей семьи. Труда предстоит немало, но я верю - сам Господь взирает на тебя с благословением и ты сможешь не только сохранить вверенное тебе наследие, но и приумножить честь и достаток семьи де Монпе.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_11";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_11": //выбор Шарля
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = "Для меня великая честь - быть вашим сыном и наследником. Я с радостью возьму на себя все заботы о нашей семье. Уверен, что моя супруга будет мне в этом верной опорой. Я обещаю сделать всё возможное, чтобы прославить наш род ещё больше... И первым вкладом в его процветание станет рождение ребёнка!";
				link.l1.go = "SharlieEpilog_ChooseEstate_HaveWife_1";
			}
			else
			{
				link.l1 = "Для меня великая честь - быть вашим сыном и наследником. Я с радостью возьму на себя все заботы о нашей семье и обещаю сделать всё возможное, чтобы прославить наш род ещё больше.";
				link.l1.go = "SharlieEpilog_ChooseEstate_Single_1";
			}
			link.l2 = "Отец, годы в Новом Свете изменили меня. Боюсь, я больше не смогу примириться с размеренным ритмом жизни здесь, в Европе.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_HaveWife_1";
			}
			else
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_Single_1";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		// --> Выбрал остаться в поместье с женой
		case "SharlieEpilog_ChooseEstate_HaveWife_1":
			dialog.text = "";
			link.l1 = ""+pchar.name+", неужели...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_HaveWife_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Да, отец. "+sld.name+" беременна.";
			link.l1.go = "SharlieEpilog_HaveWife_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_13":
			dialog.text = "";
			link.l1 = "Это воистину великие новости, мой дорогой сын! Господь услышал мои молитвы! Пусть все присутствующие здесь будут свидетелями: в честь новорождённого - я устрою самый пышный бал, какой только знало наше поместье! Поднимем же бокалы - за наследника!";
			link.l1.go = "SharlieEpilog_HaveWife_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_HaveWife_14":
			dialog.text = "";
			link.l1 = "Или наследницу!";
			link.l1.go = "SharlieEpilog_HaveWife_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_15":
			dialog.text = "";
			link.l1 = "За новую главу в истории нашей семьи!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_16":
			dialog.text = "";
			link.l1 = "За будущий воин или добрый дочь!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_HaveWife_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "За крепкое здоровье младенца!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "За случай, который свёл вас вместе!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "За светлое будущее вашей семьи!";
			}
			link.l1.go = "SharlieEpilog_HaveWife_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_HaveWife_18":
			dialog.text = "";
			link.l1 = "За будущего Алонсо де Мора или Алонситу де Мор!";
			link.l1.go = "SharlieEpilog_HaveWife_19";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_HaveWife_19":
			dialog.text = "";
			link.l1 = "Ах-хах-ха!";
			link.l1.go = "SharlieEpilog_HaveWife_20";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_20":
			dialog.text = "";
			link.l1 = "Ха-ха!";
			link.l1.go = "SharlieEpilog_HaveWife_21";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_21":
			dialog.text = "";
			link.l1 = "Ха-ха-ха!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_toast":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_toast");
		break;
		// <-- Выбрал остаться в поместье с женой
		
		// --> Выбрал остаться в поместье будучи холостяком
		case "SharlieEpilog_ChooseEstate_Single_1":
			dialog.text = "";
			link.l1 = "Для меня великая честь - быть вашим сыном и наследником. Я с радостью возьму на себя все заботы о нашей семье и обещаю сделать всё возможное, чтобы прославить наш род ещё больше.";
			link.l1.go = "SharlieEpilog_ChooseEstate_Single_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_ChooseEstate_Single_2":
			dialog.text = "";
			link.l1 = "Скажи, "+pchar.name+", ты размышлял над моим предложением связать себя узами брака с Ивонной?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_13":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseCaribbean"))
			{
				link.l1 = "Признаюсь, отец… Ивонна никогда не была близка моему сердцу. Но в Новом Свете немало прекрасных девушек. Обещаю вам - когда встречу достойную, не стану медлить.";
			}
			else
			{
				link.l1 = "Признаюсь, отец… Ивонна никогда не была близка моему сердцу. Но во Франции немало прекрасных девушек. Обещаю вам - когда встречу достойную, не стану медлить.";
			}
			link.l1.go = "SharlieEpilog_Single_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_14":
			dialog.text = "";
			link.l1 = "Мне по душе твой настрой, мой дорогой сын. Поднимем бокалы - за тебя, за твои свершения и за достойное возвращение домой!";
			link.l1.go = "SharlieEpilog_Single_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_15":
			dialog.text = "";
			link.l1 = "За верных друзей, без которых в Новом Свете не выжить!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_Single_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_16":
			dialog.text = "";
			link.l1 = "За большое сердце капитан Шарль!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_Single_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "За железную волю капитана!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "За мудрость господина капитана!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "За преданность делу!";
			}
			link.l1.go = "SharlieEpilog_Single_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_Single_18":
			dialog.text = "";
			link.l1 = "За способность выходить сухим из воды!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		// <-- Выбрал остаться в поместье будучи холостяком
		
		// Шарль губернатор разговаривает с зелёным капитаном
		case "SharlieEpilog_GreenCaptain":
			dialog.text = "";
			link.l1 = "Я слышал, что вы очень настойчиво просили аудиенции. Итак, что вам понадобилось от губернатора Мартиники?";
			link.l1.go = "SharlieEpilog_GreenCaptain_1";
			locCameraFromToPos(-1.80, 3.84, -9.08, true, -2.38, 2.21, -7.33);
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer_common_2.wav");
		break;
		
		case "SharlieEpilog_GreenCaptain_1":
			dialog.text = "Я хочу поговорить о работе на благо короны Франции.";
			link.l1 = "Да, у меня есть поручение, для выполнения которого вам потребуется максимум расторопности, а также умение грамотно вести морской бой. Вы готовы проявить себя?";
			link.l1.go = "SharlieEpilog_GreenCaptain_2";
		break;

		case "SharlieEpilog_GreenCaptain_2":
			dialog.text = "Ваша Светлость, вы можете поподробнее изложить суть предстоящего задания?";
			link.l1 = "Конечно. Вам необходимо найти курьерский корабль испанцев под названием 'Santa Esperanza', абордировать его и привезти мне бумаги, которые найдёте в капитанской каюте. Указанное мной судно будет проходить у Тринидада примерно через двенадцать дней.";
			link.l1.go = "SharlieEpilog_GreenCaptain_3";
		break;

		case "SharlieEpilog_GreenCaptain_3":
			dialog.text = "Хорошо, я берусь за это задание. А что за бумаги следует искать?";
			link.l1 = "Почтовую корреспонденцию. Там, среди прочего, будут содержаться очень важные для меня документы. Но вам копаться в бумагах не нужно, просто доставьте мне весь пакет целиком. За эту услугу я заплачу вам пятнадцать тысяч песо... Итак, я жду вас у себя в резиденции с результатами работы.";
			link.l1.go = "SharlieEpilog_GreenCaptain_4";
		break;

		case "SharlieEpilog_GreenCaptain_4":
			dialog.text = "Полагаю, что не заставлю вас долго ждать, Ваша Светлость.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_5");
		break;
		
		//Шарль разговаривает с комендантом форта
		case "SharlieEpilog_KomendantFort":
			dialog.text = "Ваша Светлость... Разрешите доложить?";
			link.l1 = "Докладывайте, "+GetAddress_Form(NPChar)+" "+npchar.lastname+".";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) link.l1.go = "SharlieEpilog_KomendantFort_1";
			else link.l1.go = "SharlieEpilog_KomendantFort_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\military02.wav");
		break;
		
		case "SharlieEpilog_KomendantFort_1":
			dialog.text = "Кхм-кхм...";
			link.l1 = "Говорите свободно. У меня нет тайн от моей жены.";
			link.l1.go = "SharlieEpilog_KomendantFort_2";
		break;
		
		case "SharlieEpilog_KomendantFort_2":
			dialog.text = "Разведка сообщает: из Виллемстада вышла эскадра. Во главе - линейный корабль второго ранга ‘Gouden Leeuw’, настоящее морское чудовище. Общая мощь эскадры - более двух с половиной сотен орудий и свыше полутора тысяч солдат. Их цель - Сен-Пьер.";
			link.l1 = "Хм... Значит, у нас практически нет времени на подготовку.";
			link.l1.go = "SharlieEpilog_KomendantFort_3";
		break;

		case "SharlieEpilog_KomendantFort_3":
			dialog.text = "Как будем действовать, господин губернатор?";
			link.l1 = "У нас на рейде есть несколько кораблей, способных ударить противнику в тыл...";
			link.l1.go = "SharlieEpilog_KomendantFort_4";
		break;

		case "SharlieEpilog_KomendantFort_4":
			dialog.text = "Вы намерены ударить по ним с двух сторон?";
			link.l1 = "Именно. Форт примет огонь на себя. А когда наступит ночь, эскадра под моим командованием ударит с моря. Мы рассеем их внимание, и тогда с порта отправятся брандеры, начинённые смолой и досками. От их флота не останется и щепок.";
			link.l1.go = "SharlieEpilog_KomendantFort_5";
		break;

		case "SharlieEpilog_KomendantFort_5":
			dialog.text = "Превосходный план, Ваша Светлость! Разрешите отдать приказ о начале приготовлений?";
			link.l1 = "Приступайте. И да будет с нами Господь.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_11");
		break;
		
		// Стражник вызывает Алонсо
		case "SharlieEpilog_Guard":
			dialog.text = "";
			link.l1 = "Стража, вызвовите Алонсо.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoArrive");
		break;
		
		//Шарль разговаривает с Алонсо после коменданта
		case "SharlieEpilog_Alonso35":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
			{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
				dialog.text = "Господин губернатор...";
				link.l1 = ""+npchar.name+", голландская эскадра со дня на день прибудет сюда и начнёт осаду. Слушай приказ: возьми Филиппа и " + sld.name + ", и немедленно отведи их к аббату. Пусть он соберёт всех женщин, детей и стариков и позаботится об их безопасности.";
				link.l1.go = "SharlieEpilog_Alonso36_Wife";
				break;
			}
			dialog.text = "Господин губернатор...";
			link.l1 = ""+npchar.name+", голландская эскадра со дня на день прибудет сюда и осадит город. Передай аббату, пусть соберёт всех женщин, детей и стариков и позаботится об их безопасности. Что до тебя, то я планирую поручить тебе управление брандером. Подробности потом. Прежде всего нужно защитить мирных жителей.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;

		case "SharlieEpilog_Alonso36_Wife":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "Не думаю, что " + sld.name + " согласится присоединиться к остальным женщинам. Она изнывает от скуки.";
			link.l1 = "Хм... Тогда передай ей: пусть готовится к бою. Тебе тоже не придётся сидеть сложа руки - будешь командовать брандером. Подробности позже. Сейчас — позаботься о моём сыне.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;
		
		case "SharlieEpilog_Alonso37":
			dialog.text = "Почту за честь! Разрешите выполнять?";
			link.l1 = "Разрешаю. Действуй. У нас каждая секунда на счету.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_13");
		break;
		// --> Выбрал отправиться назад на Карибы с женой
		case "SharlieEpilog_ChooseCaribbean_HaveWife_1":
			dialog.text = "";
			link.l1 = "Что ж... Признаюсь, я ожидал, что ты это скажешь - и всё же надеялся на иной ответ. Но я уважаю твой выбор и не стану донимать тебя уговорами.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_2":
			dialog.text = "";
			link.l1 = "Я понимаю, что разочаровал вас. Но у меня для вас есть новость, которая, надеюсь, затьмит все, что было ранее сказано.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_3":
			dialog.text = "";
			link.l1 = "Я весь внимание.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Я собираюсь задержаться здесь как минимум на год. "+sld.name+" в её положении противопоказана качка.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_5";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_5":
			dialog.text = "";
			link.l1 = ""+pchar.name+", неужели...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		// <-- Выбрал отправиться назад на Карибы с женой
		
		// --> Выбрал отправиться назад на Карибы один
		case "SharlieEpilog_ChooseCaribbean_Single_1":
			dialog.text = "";
			link.l1 = "Что ж... Признаюсь, я ожидал, что ты это скажешь - и всё же надеялся на иной ответ. Но я уважаю твой выбор и не стану донимать тебя уговорами. Но, скажи, "+pchar.name+", ты размышлял над моим предложением связать себя узами брака с Ивонной?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		// <-- Выбрал отправиться назад на Карибы один
		
		//Диалог Шарль и Мишеля на Рифе Скелета
		case "SharlieEpilog_Mishelle_1":
			dialog.text = "Не смог остановиться, да?";
			link.l1 = "Ты?! Это сон?";
			link.l1.go = "SharlieEpilog_Mishelle_2";
			SharlieEpilog_OnReefs_6();
			PlaySound("Voice\" + LanguageGetLanguage() + "\sharlie\mishelle-04.wav");
		break;

		case "SharlieEpilog_Mishelle_2":
			dialog.text = "Жажда лёгкой наживы, власть, иллюзия неуязвимости… Что из этого тебя погубило, брат? Что затмило твой рассудок, как затмевает умы всех бледнолицых?";
			link.l1 = "Убирайся! Ты - всего лишь призрак! Тебя здесь нет!";
			link.l1.go = "SharlieEpilog_Mishelle_3";
		break;

		case "SharlieEpilog_Mishelle_3":
			dialog.text = "Так ты ещё не понял? Spectra sunt memoria peccatorum. Это ты призрак... Карибская легенда о человеке, которого пожрали алчность и слепое тщеславие. Скольких ты убил ради золота, "+pchar.name+"?";
			link.l1 = "Что ж, дорогой брат, я не против убить тебя и во второй раз! Ты сам напросился!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_OnReefs_9");
		break;
		
		
		
		
		
	}
}